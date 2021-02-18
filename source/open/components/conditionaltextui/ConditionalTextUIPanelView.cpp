//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextUIPanelView.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IPanelControlData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewWidgetMgr.h"

#include "CIDErasablePanelView.h"
#include "ConditionalTextUIID.h"
#include "StdHeightWidthConstants.h"

#define kMinCondTextPalWidth 240
#define kMaxCondTextPalWidth 10000
#define	kMinCondTextPalHeight 124
#define kMaxCondTextPalHeight 10000

class ConditionalTextUIPanelView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;

public:
			 ConditionalTextUIPanelView(IPMUnknown *boss) : inherited(boss) { ; }
	virtual ~ConditionalTextUIPanelView() { ; }

	virtual PMPoint ConstrainDimensions(const PMPoint& dimensions) const;
};

// =============================================================================
// *** ConditionalTextUIPanelView impl ***
// -----------------------------------------------------------------------------
#pragma mark ConditionalTextUIPanelView implementation

CREATE_PERSIST_PMINTERFACE(ConditionalTextUIPanelView, kConditionalTextUIPanelViewImpl)

// -----------------------------------------------------------------------------

PMPoint ConditionalTextUIPanelView::ConstrainDimensions(const PMPoint& desiredDimen) const
{
	PMPoint constrainedDim( desiredDimen );

	// Compute minimum height given visibility of the sets area.
	InterfacePtr<const IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	IControlView* setsArea = panelData->FindWidget(kConditionalTextUIPanelSetsAreaWidgetId);
	PMReal theMinHeight = setsArea->IsVisible() ? kMinCondTextPalHeight + 33 : kMinCondTextPalHeight;

	constrainedDim.ConstrainTo( PMRect(kMinCondTextPalWidth, theMinHeight, kMaxCondTextPalWidth, kMaxCondTextPalHeight) );

	// Now, make sure we round the palette height so that we
	// do not show half an entry:
	// 
	// First, get the height of the control strip, indicators area, and (if visible) the
	// sets area at the bottom of the palette.
	IControlView* controlStrip = panelData->FindWidget(kConditionalTextUIPanelControlStripWidgetId);
	IControlView* indicatorsArea = panelData->FindWidget(kConditionalTextUIPanelIndicatorsAreaWidgetId);
	PMReal nonListHeight = controlStrip->GetFrame().Height() + indicatorsArea->GetFrame().Height() + 10;
	if (setsArea->IsVisible())
		nonListHeight += setsArea->GetFrame().Height() + 11;

	// Next, get the height of an individual entry in the palette
	IControlView* treeView = panelData->FindWidget(kConditionTagListTreeViewWidgetID);
	InterfacePtr<ITreeViewWidgetMgr> treeViewMgr(treeView, IID_ITREEVIEWWIDGETMGR);
	InterfacePtr<ITreeViewHierarchyAdapter> treeViewHierAdapt(treeView, IID_ITREEVIEWHIERARCHYADAPTER);

	NodeID rootNode = treeViewHierAdapt->GetRootNode();
	PMReal itemHeight = kCC2016PanelTreeNodeHeight;  //default value
	if (rootNode != kInvalidNodeID)
		itemHeight = treeViewMgr->GetNodeWidgetHeight(rootNode);
	
	// Finally, round down to a full entry height so we don't show half entries.
	PMReal listHeight = constrainedDim.Y() - nonListHeight;
	listHeight = ::Floor(listHeight/itemHeight) * itemHeight;
	constrainedDim.Y(::maximum(listHeight + nonListHeight, theMinHeight));
	
	return constrainedDim;
} // end ConstrainDimensions()



