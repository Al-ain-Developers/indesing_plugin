//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkInfoPanelObserver.cpp $
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

// ----- Interfaces -----

#include "IActiveContext.h"
#include "ISubject.h"
#include "ILink.h"
#include "IWidgetUtils.h"
#include "ITreeViewController.h"
#include "IPanelControlData.h"
#include "ILinkInfoProvider.h"
#include "IControlView.h"
#include "IEVEUtils.h"
#include "ITreeNodeIDData.h"
#include "ILinksUIPanelPrefs.h"
#include "ITextControlData.h"
#include "IUIFontSpec.h"
#include "ILinksUIUtils.h"
#include "ILinkResource.h"
#include "IScrollBarPanoramaSync.h"
#include "IPanorama.h"
#include "IIntData.h"
#include "IWidgetParent.h"
#include "IStaticTextAttributes.h"
#include "IImageCache.h"

// ----- Includes -----

#include "CObserver.h"
#include "LinksUIID.h"
#include "LocaleSetting.h"
#include "LinksUIResDefs.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"
#include "LinksTreeUIDNodeID.h"
#include "PreferenceUtils.h"
#include "IMenuUtils.h"
//#include "K2Vector.tpp"

//========================================================================================
// CLASS LinkInfoPanelObserver
//========================================================================================
class LinkInfoPanelObserver : public CObserver
{
	public:
		LinkInfoPanelObserver(IPMUnknown *boss);
		virtual ~LinkInfoPanelObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		
	private:
		void RefetchProviderData(const ILinkInfoProvider* whichProvider);
		void RebuildLinkInfoSection() const;
		void PopulateLinkInfoForSelectedTreeElement(const ILink* selectedLink, const ILinkResource* selectedLinkResource) const;
		void RearrangeLinkInfoWidgets(const ILink * selectedLink, const ILinkResource * selectedLinkResource) const;
		void AddAllInfoWidgets(const ILinksUIPanelPrefs* linksUIPrefs, IPanelControlData* labelColumnPanelData, IPanelControlData* valueColumnPanelData) const;
		void HideAllInfoWidgets(const IPanelControlData* labelColumnPanelData, const IPanelControlData* valueColumnPanelData) const;

		IScrollBarPanoramaSync *fScrollBarPanoramaSync;

};


CREATE_PMINTERFACE(LinkInfoPanelObserver, kLinkInfoPanelObserverImpl)

//----------------------------------------------------------------------------------------
// LinkInfoPanelObserver constructor 
//----------------------------------------------------------------------------------------

LinkInfoPanelObserver::LinkInfoPanelObserver(IPMUnknown *boss) :
	CObserver(boss),fScrollBarPanoramaSync(nil)
{
}

//----------------------------------------------------------------------------------------
// LinkInfoPanelObserver::~LinkInfoPanelObserver: 
//----------------------------------------------------------------------------------------

LinkInfoPanelObserver::~LinkInfoPanelObserver()
{
	if(fScrollBarPanoramaSync)
		fScrollBarPanoramaSync->Release();
}

//----------------------------------------------------------------------------------------
// LinkInfoPanelObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void LinkInfoPanelObserver::AutoAttach()
{
	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ISUBJECT));
	treeSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
	treeSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IDYNAMICLINKINFOCHANGE,IID_IOBSERVER);
	
	
	ASSERT_MSG(fScrollBarPanoramaSync == nil,"Scrollbar already hooked up?!");
	InterfacePtr<IPanorama> panorama(this,UseDefaultIID());
	InterfacePtr<IControlView> scrollbarView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinkInfoSectionScrollBarWidgetID,IID_ICONTROLVIEW));
	fScrollBarPanoramaSync = (IScrollBarPanoramaSync*) ::CreateObject(kScrollBarPanoramaSyncBoss, IID_ISCROLLBARPANORAMASYNC);
	fScrollBarPanoramaSync->Init(nil, scrollbarView, panorama);
	
	RebuildLinkInfoSection();
}

//----------------------------------------------------------------------------------------
// LinkInfoPanelObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void LinkInfoPanelObserver::AutoDetach()
{
	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ISUBJECT));
	treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
	treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IDYNAMICLINKINFOCHANGE,IID_IOBSERVER);

	if (fScrollBarPanoramaSync)
	{
		fScrollBarPanoramaSync->Release();
		fScrollBarPanoramaSync = nil;
	}
}

//----------------------------------------------------------------------------------------
// LinkInfoPanelObserver::Update: 
//----------------------------------------------------------------------------------------
void LinkInfoPanelObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(theSubject,changedBy)
	if(protocol == IID_ITREEVIEWCONTROLLER && (theChange == kListSelectionChangedMessage || theChange == kLinksUITreeSelectionAlteredMsgBoss))
	{
		TRACEFLOW("Links:LinksUI","LinkInfoPanelObserver::Update got kListSelectionChangedMessage/kLinksUITreeSelectionAlteredMsgBoss\n");
		// if tree selection changes, have to rebuild the 'selected link info' section
		RebuildLinkInfoSection();
	}
	else if(protocol == IID_IDYNAMICLINKINFOCHANGE)
	{
		ASSERT_MSG(changedBy != nil,"IID_IDYNAMICLINKINFOCHANGE should have a vaild changedBy field");
		//TRACEFLOW("Links:LinksUI","LinkInfoPanelObserver::Update got IID_IDYNAMICLINKINFOCHANGE, provider class 0x%x\n",theChange.Get());
		RefetchProviderData((ILinkInfoProvider*) changedBy);
	}
}

void LinkInfoPanelObserver::RebuildLinkInfoSection() const
{
	InterfacePtr<const ILink> selectedLink;
	InterfacePtr<const ILinkResource> selectedLinkResource;
	InterfacePtr<const ITreeViewController> treeController((ITreeViewController*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ITREEVIEWCONTROLLER));
	NodeIDList	selectedItems;
	treeController->GetSelectedItems( selectedItems );
	NodeID selectedNode = LinksTreeUIDNodeID::Create(nil);
	if(selectedItems.size() == 1)
	{
		TreeNodePtr<const LinksTreeUIDNodeID>	selectedLinksUIDNode(selectedItems[0]);
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		InterfacePtr<const ILink> theLink(linksUIPrefs->GetCurrentDocDB(),selectedLinksUIDNode->GetLinkUIDRef().GetUID(),UseDefaultIID());
		selectedLink.reset(theLink.forget());
		InterfacePtr<const ILinkResource> theLinkResource(linksUIPrefs->GetCurrentDocDB(),selectedLinksUIDNode->GetLinkResourceUID(),UseDefaultIID());
		selectedLinkResource.reset(theLinkResource.forget());
		
		selectedNode = selectedLinksUIDNode->Clone();
	}
			// set our ITreeNodeIDData so the thumbnail widget knows what to draw.
	InterfacePtr<ITreeNodeIDData> nodeData(this,UseDefaultIID());
	nodeData->Set(selectedNode);

//	InterfacePtr<IControlView> infoThumbnailView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUILinkInfoThumbnailWidgetID,IID_ICONTROLVIEW));
//	infoThumbnailView->Invalidate();
	RearrangeLinkInfoWidgets(selectedLink,selectedLinkResource);
	InterfacePtr<IControlView> infoPanelView(this,UseDefaultIID());
	infoPanelView->Invalidate();
}
const int kSpaceBetweenInfoWidgets = 3;

void LinkInfoPanelObserver::RearrangeLinkInfoWidgets(const ILink * selectedLink, const ILinkResource * selectedLinkResource) const
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	InterfacePtr<IControlView> infoThumbnailView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUILinkInfoThumbnailWidgetID,IID_ICONTROLVIEW));
	PMReal yOffsetForInfoColumns = 0;

	InterfacePtr<const IImageCache> thumbnail(Utils<ILinksUIUtils>()->QueryThumbnailForLink(selectedLink,selectedLinkResource));
	if(linksUIPrefs->GetShowLinkInfoThumbnail() && thumbnail)
	{
		infoThumbnailView->ShowView();
		yOffsetForInfoColumns = infoThumbnailView->GetFrame().Height() + kSpaceBetweenInfoWidgets;
	}
	else
	{
		infoThumbnailView->HideView();
	}

	PopulateLinkInfoForSelectedTreeElement(selectedLink,selectedLinkResource);
	
	// use eve to make the label column fit the width of it's widgets. Then adjust the size & position of the link value column to take the rest of the available space.
	InterfacePtr<IControlView> infoLabelColumn((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinkInfoLabelColumnWidgetID,IID_ICONTROLVIEW));
	InterfacePtr<IControlView> valueLabelColumn((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinkInfoValueColumnWidgetID,IID_ICONTROLVIEW));
	Utils<IEVEUtils>()->ApplyEveLayout(infoLabelColumn);
#if defined (qME) && (WINDOWS)	
	bool16 isRTL = ((LocaleSetting::GetLocale().GetUserInterfaceId() == k_arAE) || (LocaleSetting::GetLocale().GetUserInterfaceId() == k_heIL));
	if (!isRTL)
#endif
	infoLabelColumn->MoveTo(PMPoint(0,yOffsetForInfoColumns));
	
	InterfacePtr<const IWidgetParent> columnsParent(valueLabelColumn,UseDefaultIID());
	InterfacePtr<const IControlView> columnsParentView(columnsParent->GetParent(),UseDefaultIID());
#if defined (qME) && (WINDOWS)	
	if (isRTL)
	{
		infoLabelColumn->MoveTo(PMPoint(columnsParentView->GetFrame().Width() - infoLabelColumn->GetFrame().Width(),yOffsetForInfoColumns));
		valueLabelColumn->MoveTo(PMPoint(0,yOffsetForInfoColumns));
		valueLabelColumn->Resize(PMPoint(columnsParentView->GetFrame().Width() - infoLabelColumn->GetFrame().Width(),infoLabelColumn->GetFrame().Height()));
		infoThumbnailView->MoveTo(PMPoint(valueLabelColumn->GetFrame().Right() - infoThumbnailView->GetFrame().Width(), 0));
	}
	else
	{
		valueLabelColumn->MoveTo(PMPoint(infoLabelColumn->GetFrame().Right(),yOffsetForInfoColumns));
		valueLabelColumn->Resize(PMPoint(columnsParentView->GetFrame().Width() - valueLabelColumn->GetFrame().Left(),infoLabelColumn->GetFrame().Height()));
		infoThumbnailView->MoveTo(PMPoint(valueLabelColumn->GetFrame().Left(), 0));
	}
#else
	valueLabelColumn->MoveTo(PMPoint(infoLabelColumn->GetFrame().Right(),yOffsetForInfoColumns));
	valueLabelColumn->Resize(PMPoint(columnsParentView->GetFrame().Width() - valueLabelColumn->GetFrame().Left(),infoLabelColumn->GetFrame().Height()));
	infoThumbnailView->MoveTo(PMPoint(valueLabelColumn->GetFrame().Left(), 0));
#endif
	if (fScrollBarPanoramaSync)
	{
		InterfacePtr<IIntData> totalInfoHeightData(this,IID_ITOTALINFOAREAHEIGHT);
		totalInfoHeightData->Set(::ToInt32(infoLabelColumn->GetFrame().Height() + yOffsetForInfoColumns));
		TRACEFLOW("Links:LinksUI:Resize","LinkInfoPanelObserver saving panel height of %d\n",totalInfoHeightData->Get());
		
//		InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
//		InterfacePtr<const IControlView> parentView(wp->GetParent(),UseDefaultIID());
//		PMPoint newDimens(parentView->GetFrame().Width() - widgetFrame.Left(),parentView->GetFrame().Height() - widgetFrame.Top());
//		view->Resize(newDimens); // fit to parent's height, subtracting 20 for our offset.
		InterfacePtr<IPanorama> panorama(this,UseDefaultIID());
		InterfacePtr<ISubject> panoramaSubj(panorama, UseDefaultIID());
		if (panoramaSubj)
			panoramaSubj->Change(kScaleToMessage, IID_IPANORAMA, (void*)this);
		panorama->ScrollTo_neg(PMPoint(0,0));
	}
}

void LinkInfoPanelObserver::AddAllInfoWidgets(const ILinksUIPanelPrefs* linksUIPrefs, IPanelControlData* labelColumnPanelData, IPanelControlData* valueColumnPanelData) const
{
	// add all the widgets to start
	const int32 maxNumInfos = linksUIPrefs->GetNumInfoProviders();
	InterfacePtr<const IControlView> thumbnailView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUILinkInfoThumbnailWidgetID,IID_ICONTROLVIEW));
	PMReal yWidgetLocation = thumbnailView->GetFrame().Height() + kSpaceBetweenInfoWidgets;
	InterfacePtr<const IControlView> labelColumnView(labelColumnPanelData,UseDefaultIID());
	InterfacePtr<const IControlView> valueColumnView(valueColumnPanelData,UseDefaultIID());
	
	PMRect labelFrame(0,0,labelColumnView->GetFrame().Width(),0);
	PMRect valueFrame(0,0,valueColumnView->GetFrame().Width(),0);
	
	TRACEFLOW("Links:LinksUI","AddAllInfoWidgets adding %d label widgets and %d value widgets\n",maxNumInfos,maxNumInfos);

	for(int index = 0; index < maxNumInfos; ++index)
	{
		InterfacePtr<IControlView> newLabelView ((IControlView*)::CreateObject(::GetDataBase(this),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinkInfoDynamicTextNameItemResID),IID_ICONTROLVIEW));
		labelColumnPanelData->AddWidget(newLabelView);
		labelFrame.Bottom() = labelFrame.Top() + newLabelView->GetFrame().Height();
		newLabelView->SetFrame(labelFrame);
		
		InterfacePtr<IControlView> newValueView ((IControlView*)::CreateObject(::GetDataBase(this),RsrcSpec(LocaleSetting::GetLocale(), kLinksUIPluginID, kViewRsrcType, kLinkInfoDynamicTextItemResID),IID_ICONTROLVIEW));
		valueColumnPanelData->AddWidget(newValueView);
		valueFrame.Bottom() = valueFrame.Top() + newValueView->GetFrame().Height();
		newValueView->SetFrame(valueFrame);
		newValueView->SetFrameBinding(kBindLeft|kBindRight);

		labelFrame.Top() += newLabelView->GetFrame().Height() + kSpaceBetweenInfoWidgets;
		valueFrame.Top() += newValueView->GetFrame().Height() + kSpaceBetweenInfoWidgets;
	}
}

void LinkInfoPanelObserver::HideAllInfoWidgets(const IPanelControlData* labelColumnPanelData, const IPanelControlData* valueColumnPanelData) const
{
	const int32 numExistingWidgets = valueColumnPanelData->Length() ;
	TRACEFLOW("Links:LinksUI","HideAllInfoWidgets hiding %d label widgets and %d value widgets\n",numExistingWidgets,numExistingWidgets);
	for(int index = 0; index < numExistingWidgets; ++index)
	{
		IControlView *labelView = labelColumnPanelData->GetWidget(index);
		IControlView *valueView = valueColumnPanelData->GetWidget(index); 
		labelView->HideView();
		valueView->HideView();
	}
}

static PMString CreateInfoLabelStringFromProvider(const ILinkInfoProvider *infoService)
{
	PMString linkInfoLabelStr = infoService->GetInfoDescriptionString();  
	linkInfoLabelStr.Translate();
	PMString infoLabelSuffix("#InfoLabelSuffix");
	infoLabelSuffix.Translate();
	linkInfoLabelStr.Append(infoLabelSuffix);
	return linkInfoLabelStr;
}

void LinkInfoPanelObserver::PopulateLinkInfoForSelectedTreeElement(const ILink* selectedLink, const ILinkResource* selectedLinkResource) const
{
	InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
	InterfacePtr<IPanelControlData>	labelColumnPanelData(panelData->FindWidget(kLinkInfoLabelColumnWidgetID), UseDefaultIID());
	InterfacePtr<IPanelControlData>	valueColumnPanelData(panelData->FindWidget(kLinkInfoValueColumnWidgetID), UseDefaultIID());
	
	ASSERT_MSG(valueColumnPanelData->Length() == labelColumnPanelData->Length(),"panels should contain same number of widgets!");
	const int32 numExistingWidgets = valueColumnPanelData->Length() ;
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	const int32 numProviders = linksUIPrefs->GetNumMoreInfoProviders();
	if(numExistingWidgets == 0)
		AddAllInfoWidgets(linksUIPrefs,labelColumnPanelData,valueColumnPanelData);
		
	HideAllInfoWidgets(labelColumnPanelData,valueColumnPanelData);

	if(selectedLink || selectedLinkResource)
	{
		int32 widgetIndex = 0;
		PMString descriptionString;
		for(int providerIndex = 0; providerIndex < numProviders; ++providerIndex)
		{
			InterfacePtr<const ILinkInfoProvider> infoService(linksUIPrefs->QueryNthMoreInfoProvider(providerIndex));			

			PMString linkInfoStr = infoService->GetUpdatedInfoForLink(selectedLink,selectedLinkResource,false);
				
			if(!linkInfoStr.empty())
			{
				// Convert & to && if user-entered style name contains &.
				// Prevents it from being interpreted as an accelerator.
				if(!linkInfoStr.IsTranslatable())
					Utils<IMenuUtils>()->InsertAmpersandForDisplay(&linkInfoStr);

				IControlView *labelView = labelColumnPanelData->GetWidget(widgetIndex);
				PMRect labelBounds = labelView->GetFrame();
				labelView->Resize(PMPoint(10,labelBounds.Height()),kFalse); // resize the label to be narrow, so EVE can size it appropriately.(bug 1822076)
				IControlView *valueView = valueColumnPanelData->GetWidget(widgetIndex); 
				labelView->ShowView();
				if (!labelView->IsHilited())
					labelView->Hilite();
				valueView->ShowView();
				
				// label
				InterfacePtr<ITextControlData>	labelWidgetText(labelView, UseDefaultIID());
				PMString linkInfoLabelStr = CreateInfoLabelStringFromProvider(infoService);  
				labelWidgetText->SetString(linkInfoLabelStr,kFalse);	
				
				//value
				InterfacePtr<ITextControlData>	valueWidgetText(valueView, UseDefaultIID());
				valueWidgetText->SetString(linkInfoStr,kFalse);	
				
				++widgetIndex;
				
				//TRACEFLOW("Links:LinksUI","Info Label '%s', view: 0x%x value '%s' view 0x%x\n",linkInfoLabelStr.GetPlatformString().c_str(),labelView,linkInfoStr.GetPlatformString().c_str(),valueView);
			}
		}
	}

}

void LinkInfoPanelObserver::RefetchProviderData(const ILinkInfoProvider* whichProvider)
{
	InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
	
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	
	InterfacePtr<const IPanelControlData>	labelColumnPanelData(panelData->FindWidget(kLinkInfoLabelColumnWidgetID), UseDefaultIID());
	PMString changedInfoLabelStr = CreateInfoLabelStringFromProvider(whichProvider);  
	TRACEFLOW("Links:LinksUI","LinkInfoPanelObserver::RefetchProviderData called for provider class 0x%x(label '%s').\n",::GetClass(whichProvider).Get(),changedInfoLabelStr.GetUTF8String().c_str());
	for(int widgetIndex = 0; widgetIndex < labelColumnPanelData->Length(); ++widgetIndex)
	{
		IControlView *labelView = labelColumnPanelData->GetWidget(widgetIndex);
		InterfacePtr<const ITextControlData>	labelWidgetTextData(labelView, UseDefaultIID());
		PMString labelString = labelWidgetTextData->GetString();
		if(labelString == changedInfoLabelStr)
		{
			InterfacePtr<const IPanelControlData>	valueColumnPanelData(panelData->FindWidget(kLinkInfoValueColumnWidgetID), UseDefaultIID());
			ASSERT_MSG(valueColumnPanelData->Length() == labelColumnPanelData->Length(),"panels should contain same number of widgets!");
			InterfacePtr<const ILink> selectedLink;
			UIDList listOfLinks = Utils<ILinksUIUtils>()->GetLinksSelectedInPanel();
			if(listOfLinks.size() == 1 && listOfLinks.GetDataBase()->IsValidUID(listOfLinks[0])) // HACK - need to figure out a way to get link add/delete lazy notifications before other notifications. Can't run BA with link info section showing without this check.
			{
				InterfacePtr<const ILink> oneLink(listOfLinks.GetRef(0),UseDefaultIID());
				selectedLink.reset(oneLink.forget());
			}
			InterfacePtr<const ILinkResource> selectedLinkResource;
			UIDList listOfResources = Utils<ILinksUIUtils>()->GetLinkResourcesSelectedInPanel();
			if(listOfResources.size() == 1 && listOfResources.GetDataBase()->IsValidUID(listOfResources[0]))  // HACK - need to figure out a way to get link add/delete lazy notifications before other notifications. Can't run BA with link info section showing without this check.
			{
				InterfacePtr<const ILinkResource> oneLinkResource(listOfResources.GetRef(0),UseDefaultIID());
				selectedLinkResource.reset(oneLinkResource.forget());
			}
			if(selectedLink || selectedLinkResource)
			{
				IControlView *valueView = valueColumnPanelData->GetWidget(widgetIndex); 
				PMString linkInfoStr = whichProvider->GetUpdatedInfoForLink(selectedLink,selectedLinkResource,false);
				InterfacePtr<ITextControlData>	valueWidgetText(valueView, UseDefaultIID());
				TRACEFLOW("Links:LinksUI","Found field to update. Changing value text from '%s' to '%s'\n",valueWidgetText->GetString().GetUTF8String().c_str(),linkInfoStr.GetUTF8String().c_str());
				if(linkInfoStr != valueWidgetText->GetString())
					valueWidgetText->SetString(linkInfoStr,kTrue);	
			}
			return;
		}

	}

}

