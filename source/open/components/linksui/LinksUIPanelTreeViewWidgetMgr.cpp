//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelTreeViewWidgetMgr.cpp $
//  
//  Owner: lance bushore
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IControlView.h"
#include "ITextControlData.h"
#include "ILayoutUIUtils.h"
#include "ILink.h"
#include "IDocument.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ILinkInfoProvider.h"
#include "ITreeViewController.h"
#include "ILinksUIPanelPrefs.h"
#include "ILinkManager.h"
#include "IIntData.h"
#include "ILinksTreeNodeList.h"
#include "IStaticTextAttributes.h"

#include "LocaleSetting.h"
#include "LinksUIResDefs.h"
#include "CTreeViewWidgetMgr.h"
#include "LinksUIID.h"
#include "LinksTreeUIDNodeID.h"
#include "CoreResTypes.h"
#include "PreferenceUtils.h"
#include "ILinksUIUtils.h"
#include "IMenuUtils.h"

#include "StdHeightWidthConstants.h"

#define INHERITED	CTreeViewWidgetMgr

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
class LinksUIPanelTreeViewWidgetMgr : public INHERITED
{
public:
	LinksUIPanelTreeViewWidgetMgr(IPMUnknown *boss);
	~LinksUIPanelTreeViewWidgetMgr();
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	WidgetID			GetWidgetTypeForNode(const NodeID& node) const;
	virtual	bool16			ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const;
	virtual PMReal				GetNodeWidgetWidth(const NodeID& node) const;
	virtual PMReal				GetNodeWidgetHeight(const NodeID& node) const 
	{ 
	#pragma unused(node)
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		return linksUIPrefs->GetCurrentRowHeight();
	}
private:
	void PositionLinkRowWidgets(const IPanelControlData* panelData, int nestingLevel) const;
	void AddWidgetsIfNeeded(IPanelControlData* panelData,const ILinksUIPanelPrefs* linksUIPrefs,const ILink* forThisLink,const ILinkResource* forThisLinkResource, int numDuplicates) const;
	void AddTextWidgetsForSingleLink(const ILink* forThisLink, const ILinkResource* forThisLinkResource, IPanelControlData* panelData, int nestingLevel, int numDuplicates) const;

};

CREATE_PMINTERFACE(LinksUIPanelTreeViewWidgetMgr, kLinksUIPanelTreeViewWidgetMgrImpl)

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
LinksUIPanelTreeViewWidgetMgr::LinksUIPanelTreeViewWidgetMgr(IPMUnknown *boss) :
	INHERITED(boss)
{
}


//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewWidgetMgr::~LinksUIPanelTreeViewWidgetMgr 
//----------------------------------------------------------------------------------------
LinksUIPanelTreeViewWidgetMgr::~LinksUIPanelTreeViewWidgetMgr()
{
}

void LinksUIPanelTreeViewWidgetMgr::AddWidgetsIfNeeded(IPanelControlData* panelData,const ILinksUIPanelPrefs* linksUIPrefs,const ILink* forThisLink,const ILinkResource* forThisLinkResource, int numDuplicates) const
{	
	//TRACE("AddWidgetsIfNeeded created widget with UID %d for link UID %d\n",::GetUID(panelData),::GetUID(forThisLink));

	IDataBase* docDB = ::GetDataBase(forThisLink);
	if(!docDB)
		docDB = ::GetDataBase(forThisLinkResource);

	const int32 numHandlers = linksUIPrefs->GetNumShowingInfoColumns();

	bool needToCreateWidgets = true;
	if(panelData->Length())
	{
		needToCreateWidgets = false;	// we've already added the appropriate widgets.
		ASSERT_MSG(numHandlers == panelData->Length(),"We have wrong number of widgets - reusing them isn't going to work");
	}
			
	
	for(int i = 0; i < numHandlers; ++i) 
	{
		InterfacePtr<const ILinkInfoProvider> infoService(linksUIPrefs->QueryNthShowingInfoColumn(i));
		PMRsrcID iconID = infoService->GetUpdatedIconForLink(forThisLink,forThisLinkResource);
		IControlView* newWidget = nil;
		if(iconID.fId == kInvalidRsrcID)
		{
			if(::GetClass(infoService) == kLinkInfoNameProviderBoss)
			{
				if(needToCreateWidgets)
					newWidget = (IControlView*) ::CreateObject(::GetDataBase(panelData),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinksUIDynamicNameEntryResID),IID_ICONTROLVIEW);
				else
					newWidget = panelData->GetWidget(i);
				
				InterfacePtr<const IPanelControlData> namePanelData(newWidget,UseDefaultIID());
				IControlView* nameView = namePanelData->FindWidget(kLinksUINameTextWidgetID);
				
				PMString linkInfoStr = infoService->GetUpdatedInfoForLink(forThisLink,forThisLinkResource,true);

				InterfacePtr<IIntData> providerIndexData(nameView,IID_LINKINFOPROVIDERINDEX);
				providerIndexData->Set(i);

				// note when we have multiple copies of the link resource
				if(numDuplicates > 1 && forThisLink == nil)
				{
					linkInfoStr.Append(" (");
					linkInfoStr.AppendNumber(numDuplicates);
					linkInfoStr.Append(")");
				}

				InterfacePtr<ITextControlData>	nodeNameData(nameView, UseDefaultIID());
				nodeNameData->SetString(linkInfoStr);	

				// handle thumbnail widget
				IControlView* thumbnailView = namePanelData->FindWidget(kLinksUILinkThumbnailWidgetID);
				thumbnailView->Resize(PMPoint(linksUIPrefs->GetCurrentRowHeight()-1,linksUIPrefs->GetCurrentRowHeight()-1));
				if(linksUIPrefs->GetShowLinkThumbnail())
					thumbnailView->ShowView();		
				else
					thumbnailView->HideView();		
				
				// hide expander if we don't need it.
				IControlView*	expanderWidget = namePanelData->FindWidget(kTreeNodeExpanderWidgetID);
				if (expanderWidget)
				{
					expanderWidget->Resize(PMPoint(expanderWidget->GetFrame().Width(),linksUIPrefs->GetCurrentRowHeight()-1));
					if((forThisLinkResource && !forThisLink) || (forThisLink && forThisLink->GetNumChildren() > 0))
					{
						//TRACE("LinksUIPanelTreeViewWidgetMgr::AddWidgetsIfNeeded - showing newly created expander widget\n");
						expanderWidget->ShowView();
					}
					else
						expanderWidget->HideView();
				}

			}
			else
			{
				if(needToCreateWidgets)
					newWidget = (IControlView*) ::CreateObject(::GetDataBase(panelData),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinksUIDynamicTextItemResID),IID_ICONTROLVIEW);
				else
					newWidget = panelData->GetWidget(i);

				PMString linkInfoStr = infoService->GetUpdatedInfoForLink(forThisLink,forThisLinkResource,true);

				// Convert & to && if user-entered style name contains &.
				// Prevents it from being interpreted as an accelerator.
				if(!linkInfoStr.IsTranslatable())
					Utils<IMenuUtils>()->InsertAmpersandForDisplay(&linkInfoStr);

				InterfacePtr<IStaticTextAttributes> textAttr(newWidget,UseDefaultIID());
				textAttr->SetAlignment(infoService->GetInfoTextAlignment());

				InterfacePtr<ITextControlData>	nodeNameData(newWidget, UseDefaultIID());
				nodeNameData->SetString(linkInfoStr);	
				
				InterfacePtr<IIntData> providerIndexData(newWidget,IID_LINKINFOPROVIDERINDEX);
				providerIndexData->Set(i);
			}
		}
		else
		{
			if(needToCreateWidgets)
				newWidget = (IControlView*) ::CreateObject(::GetDataBase(panelData),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinksUIDynamicPNGIconResID),IID_ICONTROLVIEW);
			else
				newWidget = panelData->GetWidget(i);
			newWidget->SetRsrcPluginID(iconID.fPluginId);
			newWidget->SetRsrcID(iconID.fId);	
			InterfacePtr<IIntData> providerIndexData(newWidget,IID_LINKINFOPROVIDERINDEX);
			providerIndexData->Set(i);
		}

		if(needToCreateWidgets)
		{
			panelData->AddWidget(newWidget);
			newWidget->Release();
		}
	}

}

PMReal LinksUIPanelTreeViewWidgetMgr::GetNodeWidgetWidth(const NodeID& node) const
{
#pragma unused(node)
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	PMReal totalWidth = 0;
	for(int index = 0; index < linksUIPrefs->GetNumShowingInfoColumns(); ++index)
		totalWidth += linksUIPrefs->GetNthColumnWidth(index) + LinksUIUtils::kLinksUIColumnGap;

	return totalWidth;
}

void LinksUIPanelTreeViewWidgetMgr::PositionLinkRowWidgets(const IPanelControlData* panelData, int nestingLevel) const
{	
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	InterfacePtr<const ILinksTreeNodeList> prebuiltLinksTree(this,UseDefaultIID());

	PMReal newRowWidth = 0;
	const int32 kNewRowHeight = linksUIPrefs->GetCurrentRowHeight();
	for(int i = panelData->Length() - 1; i >= 0; --i) 
	{
		IControlView* existingTextWidget = panelData->GetWidget(i);

		PMRect widgetFrame = existingTextWidget->GetFrame();
		
		PMReal xLoc = i == 0 ? 0 : kCC2016StandardGapBetweenWidgets; // to compensate for 5 pixel gap in header row first header, first column entry in a row does not stat with gap to align expander icon properly
		PMReal widgetWidth = 0;

		for(int widgetIndex = 0; widgetIndex < i; ++widgetIndex)
			xLoc += linksUIPrefs->GetNthColumnWidth(widgetIndex) + LinksUIUtils::kLinksUIColumnGap;
			
		widgetWidth = linksUIPrefs->GetNthColumnWidth(i);

		InterfacePtr<const ILinkInfoProvider> linkInfoProv(linksUIPrefs->QueryNthShowingInfoColumn(i));
		if(::GetClass(linkInfoProv) == kLinkInfoNameProviderBoss) 
		{
			InterfacePtr<const IPanelControlData> namePanel(existingTextWidget,UseDefaultIID());
			IControlView *expanderView = namePanel->FindWidget(kTreeNodeExpanderWidgetID);
			IControlView *thumbView = namePanel->FindWidget(kLinksUILinkThumbnailWidgetID);
			IControlView *nameView = namePanel->FindWidget(kLinksUINameTextWidgetID);
			
			PMReal thumbXPos = 0;
			if(!prebuiltLinksTree->IsTreeFlat())
				thumbXPos += expanderView->GetFrame().Width();
			
			// indent as appropriate
			const int kChildLinkIndentAmt = 9;
			thumbXPos += nestingLevel * kChildLinkIndentAmt;

			PMPoint newThumbLocation(thumbXPos,0);
			thumbView->MoveTo(newThumbLocation);

			PMReal nameXPos = thumbXPos;
			if(linksUIPrefs->GetShowLinkThumbnail())
				nameXPos +=  kNewRowHeight + 4;
			
			PMReal nameWidth = widgetWidth - nameXPos;
			
			PMPoint newLocation(nameXPos,0);
			nameView->MoveTo(newLocation);
			nameView->Resize(PMPoint(nameWidth,kNewRowHeight-1));

//#ifdef DEBUG			
//			InterfacePtr<const ITextControlData> debugTextData(nameView,UseDefaultIID());
//			TRACEFLOW("Links:LinksUI","PositionLinkRowWidgets - for row with name '%s', nestingLevel = %d, xPos for name view =  %d\n",debugTextData->GetString().GrabCString(),nestingLevel,::ToInt32(nameXPos));
//#endif
		
		}
		
		PMPoint newLocation(xLoc,widgetFrame.Top());
		existingTextWidget->MoveTo(newLocation);
		existingTextWidget->Resize(PMPoint(widgetWidth,kNewRowHeight-1));
		
		if (i == panelData->Length() - 1)
			newRowWidth = xLoc + widgetWidth + (i == 0 ? kCC2016StandardGapBetweenWidgets * 2 : kCC2016StandardGapBetweenWidgets)/*compensate for separator distance from last item*/;
	}
	InterfacePtr<IControlView> rowView(panelData,UseDefaultIID());
	rowView->Resize(PMPoint(newRowWidth,kNewRowHeight));

}

void LinksUIPanelTreeViewWidgetMgr::AddTextWidgetsForSingleLink(const ILink* forThisLink, const ILinkResource* forThisLinkResource, IPanelControlData* panelData, int nestingLevel, int numDuplicates) const
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));	
	// create & position the additional text widgets we need for the labels
	AddWidgetsIfNeeded(panelData,linksUIPrefs,forThisLink,forThisLinkResource,numDuplicates);
	PositionLinkRowWidgets(panelData,nestingLevel);
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewWidgetMgr::ApplyNodeIDToWidget
//----------------------------------------------------------------------------------------
bool16 LinksUIPanelTreeViewWidgetMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 ) const
{		
	TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(node);
	InterfacePtr<IPanelControlData>	panelData(widget, UseDefaultIID());		

	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	widget->Resize(PMPoint(widget->GetFrame().Width(),linksUIPrefs->GetCurrentRowHeight()));
	
	ASSERT_MSG(widget->GetWidgetID() == kLinksUIElementRowWidgetID,"unexpected widget");
	InterfacePtr<const ILink> theLink(linksUIPrefs->GetCurrentDocDB(),linksUIDNode->GetLinkUIDRef().GetUID(),UseDefaultIID());
	InterfacePtr<const ILinkResource> theLinkResource(linksUIPrefs->GetCurrentDocDB(),linksUIDNode->GetLinkResourceUID(),UseDefaultIID());
//	TRACEFLOW("Links:LinksUI","ApplyNodeIDToWidget node has link UID %d, link resource UID %d\n",linksUIDNode->GetLinkUID(),linksUIDNode->GetLinkResourceUID());
//	
	// determine nesting level to use.
	const LinkTreeEntry* linkEntry = linksUIDNode->GetTreeEntry();
	int32 numDuplicates = 1;
	if(linkEntry->GetLinkUIDRef().GetUID() == kInvalidUID && linkEntry->GetLinkResourceUID() != kInvalidUID)
	{
		numDuplicates = K2length(linkEntry->GetChildEntries());
	}


	const LinkTreeEntry* parentEntry = linkEntry->GetParentEntry();
	int nestingLevel = 0;
	while(parentEntry && parentEntry->GetLinkUIDRef().GetUID() != kRootDocumentLinksNodeUID)
	{
		++nestingLevel;
		parentEntry = parentEntry->GetParentEntry();
	}

	
	AddTextWidgetsForSingleLink(theLink,theLinkResource,panelData,nestingLevel,numDuplicates);

	//Call base class for hilite selection
	INHERITED::ApplyNodeIDToWidget( node, widget );
		
		
	return kTrue;
}


//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewWidgetMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------
IControlView* LinksUIPanelTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
//	TRACEFLOW("Links:LinksUI","LinksUIPanelTreeViewWidgetMgr::CreateWidgetForNode\n");

	TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(node);
	ASSERT_MSG(linksUIDNode->GetLinkUIDRef().GetUID() != kRootDocumentLinksNodeUID,"Why are we creating this root node widget?");

	IControlView* view =  (IControlView*) ::CreateObject(::GetDataBase(this),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinksUITreeLinkElementResID),IID_ICONTROLVIEW);
	
	
//#ifdef DEBUG
//	TreeNodePtr<const LinksTreeUIDNodeID>	debugParentNode(linksUIDNode->GetParentNode());
//	TRACEFLOW("Links:LinksUI","CreateWidgetForNode created widget with UID %d for link UID %d, link resource UID %d. Parent node link UID %d, link resource UID %d\n",
//		::GetUID(view),linksUIDNode->GetLinkUID(),linksUIDNode->GetLinkResourceUID(),debugParentNode->GetLinkUID(),debugParentNode->GetLinkResourceUID());
//#endif
		
	return view;
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewWidgetMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------
WidgetID LinksUIPanelTreeViewWidgetMgr::GetWidgetTypeForNode(const NodeID& node) const
{	
	TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(node);
	ASSERT_MSG(linksUIDNode->GetLinkUIDRef().GetUID() != kRootDocumentLinksNodeUID,"Why are we getting widget type for root node?");
	return kLinksUIElementRowWidgetID;

}

