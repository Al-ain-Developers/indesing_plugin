//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelView.cpp $
//  
//  Owner: Steve Flenniken
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
#include "CIDErasablePanelView.h"
#include "IAEMLinkUtils.h"
#include "IBoolData.h"
#include "ISplitterPanelControlData.h"
#include "IPanelControlData.h"
#include "ILinksUIPanelPrefs.h"
#include "ILinkManager.h"
#include "PreferenceUtils.h"
#include "LinksUIID.h"

#define kMinLinksPalWidth	240
#define kMaxLinksPalWidth	10000
#define kMaxLinksPalHeight	10000

class LinksUIPanelView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;
public:
			 LinksUIPanelView(IPMUnknown *boss) : inherited(boss) { ; }
	virtual ~LinksUIPanelView() { ; }

	virtual PMPoint ConstrainDimensions(const PMPoint& dimensions) const;
	virtual void	DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;
};

#pragma mark LinksUIPanelView implementation 

CREATE_PERSIST_PMINTERFACE(LinksUIPanelView, kLinksUIPanelViewImpl)

void LinksUIPanelView::DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));	
	IDataBase* docDB = linksUIPrefs->GetCurrentDocDB();
	InterfacePtr<IBoolData> drawDisabledFlag(this,IID_LINKSPANELDRAWINGDISABLED);
	if(docDB)
	{
		InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
		if(linkMgr->IsModelChanging())
			drawDisabledFlag->Set(kTrue);
	}

//	TRACEFLOW("Links:LinksUI","LinksUIPanelView::Draw - drawing disabled flag is %d\n",drawDisabledFlag->GetBool());
	if(!drawDisabledFlag->GetBool())
		inherited::DV_Draw(drawbotP);
	else
	{
		// drawing is disabled, and we were asked to draw. Make sure we inval when drawing is turned on again.
		InterfacePtr<IBoolData> invalWhenPossibleData(this,IID_LINKSPANELSHOULDINVALDATA);
		invalWhenPossibleData->Set(kTrue);
	}
}

PMPoint LinksUIPanelView::ConstrainDimensions(const PMPoint& desiredDimen) const
{
	InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
	IControlView* splitterWidget = panelData->FindWidget(kLinkUISplitterPanelWidgetID);
	ASSERT_MSG(splitterWidget,"LinksUIPanelView::ConstrainDimensions failed to find splitter widget");
	InterfacePtr<const ISplitterPanelControlData> splitterData(splitterWidget,UseDefaultIID());

	PMReal minHeight( splitterData->GetSplitterSnapTop() );

	if(!splitterData->IsSinglePanelVisible())
		minHeight += splitterData->GetSplitterSnapBottom() + splitterData->GetSplitterSize();
		
	PMPoint constrainedDim( desiredDimen );
    
    PMReal minWidth(kMinLinksPalWidth);
    
    // Bug Id # ID-4214016
    if (Utils<IAEMLinkUtils>()->ShouldShowAALRelinkAction())
        minWidth += 28; //kCC2016PanelIconWidth: Increased the minimum width to add "Relink using AAL action"

	constrainedDim.ConstrainTo( PMRect(minWidth, minHeight, kMaxLinksPalWidth, kMaxLinksPalHeight) );

	//TRACEFLOW("Links:LinksUI:Resize","LinksUIPanelView::ConstrainDimensions - SinglePanelVisible %d, splitter location %d. desiredDimen.Y(): %d, constrainedDim.Y(): %d\n",
	//									splitterData->IsSinglePanelVisible(),splitterData->GetSplitterEdge(),::ToInt32(desiredDimen.Y()),::ToInt32(constrainedDim.Y()));

	return constrainedDim;
}
