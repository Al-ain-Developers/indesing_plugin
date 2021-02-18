//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelView.cpp $
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

#include "LayerPanelID.h"

#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "IBoolData.h"

#include "LayerPanelDefs.h"
#include "LocaleSetting.h"

#include "CIDErasablePanelView.h"


class  LayerPanelView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;
public:

			 LayerPanelView(IPMUnknown* boss) : inherited(boss) { ; }
	virtual ~LayerPanelView() { ; }
	
	virtual			PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;

	virtual void	WindowChanged();
};

CREATE_PERSIST_PMINTERFACE(LayerPanelView, kLayerPanelViewImpl)

PMPoint LayerPanelView::ConstrainDimensions(const PMPoint& dimensions) const
{
	PMPoint constrainedDim( dimensions );

	constrainedDim.ConstrainTo( PMRect(kMinLayerPalWidth, dimensions.Y(), kMaxLayerPalWidth, kMaxLayerPalHeight) );

	InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
	IControlView* lowerStrip = panelData->FindWidget(kLayerControlStripWidgetID);
	
	PMReal nonListHeight = lowerStrip->GetFrame().Height();
	
	IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
											   
	InterfacePtr<const IBoolData> rowSizeBool(treeView, IID_ISMALLPALETTEROWSBOOLDATA);
	PMReal h = rowSizeBool->GetBool() ? kCC2016PanelTreeNodeSmallRowHeight : kCC2016PanelTreeNodeHeight;

	//	Need to round down to a full tag width so we don't show half tags.
	PMReal listHeight = constrainedDim.Y() - nonListHeight;
	const int32 kMinNumRowsVisible = 2;
	int32 numRowsToShow = std::max(kMinNumRowsVisible,::ToInt32(::Floor(listHeight/h)));
	listHeight = numRowsToShow * h;
//	TRACEFLOW("LayerPanel","LayerPanelView::ConstrainDimensions - height was %d, list height is %d, row height %d, constrained height is %d(%d rows)\n",
//		::ToInt32(constrainedDim.Y()),::ToInt32(listHeight),::ToInt32(h),::ToInt32(listHeight + nonListHeight),numRowsToShow);
	constrainedDim.Y(listHeight + nonListHeight);

	return constrainedDim;
}

void LayerPanelView::WindowChanged()
{
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
		IControlView* newButton = panelData->FindWidget(kLayerNewButtonWidgetID);
		newButton->HideView();
		IControlView* deleteButton = panelData->FindWidget(kLayerDeleteButtonWidgetID);
		deleteButton->HideView();
	}
}


