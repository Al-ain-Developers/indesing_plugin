//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelView.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----
#include "IPanelControlData.h"

// ----- Includes -----
#include "CIDErasablePanelView.h"
#include "DynamicDocumentsUIDefs.h"
#include "DynamicDocumentsUIID.h"

class  TimingPanelView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;

public:
				 TimingPanelView(IPMUnknown* boss) : inherited(boss) { ; }
		virtual ~TimingPanelView() { ; }
		
		virtual PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;
};

#pragma mark TimingPanelView implementation

CREATE_PERSIST_PMINTERFACE(TimingPanelView, kTimingPanelViewImpl)

PMPoint TimingPanelView::ConstrainDimensions(const PMPoint& dimensions) const
{
	PMPoint constrainedDim( dimensions );

	constrainedDim.ConstrainTo( PMRect(kMinTimingPanelWidth, kMinTimingPanelHeight, kMaxTimingPanelWidth, kMaxTimingPanelHeight) );

	InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
	IControlView* iControlStripGroupView = panelData->FindWidget(kTimingPanelControlStripWidgetID);
	IControlView* iTreeView = panelData->FindWidget(kTimingPanelTreeWidgetID);
	
	if (iTreeView && iControlStripGroupView) 
    { 
       constrainedDim.Y(constrainedDim.Y() - (iControlStripGroupView->GetFrame().Height()+1)); 
       constrainedDim = iTreeView->ConstrainDimensions(constrainedDim); 
       constrainedDim.Y(constrainedDim.Y() + (iControlStripGroupView->GetFrame().Height()+1)); 
    } 

	return constrainedDim;
}


