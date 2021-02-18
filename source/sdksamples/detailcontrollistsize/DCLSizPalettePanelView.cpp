//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizPalettePanelView.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interfaces:
#include "IPanelControlData.h"
#include "IPalettePanelUtils.h"

// Includes:
#include "CIDErasablePanelView.h"
#include "IDCLSizPanelOptions.h"
#include "DCLSizID.h"

/**
	Implements IControlView for the panel, based on CIDErasablePanelView. This is required to 
	support the correct behaviour on ConstrainDimensions being sent to the view.

	@ingroup detailcontrollistsize
	
*/
class  DCLSizPalettePanelView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;

public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is being aggregated.
	*/
			 DCLSizPalettePanelView(IPMUnknown* boss) : inherited(boss) { ; }

	/**
		Destructor.
	*/
	virtual ~DCLSizPalettePanelView() { ; }
	

	/**
		Override CIDErasablePanelView::ConstrainDimensions. This ensures that the list box
		does not become smaller when the list-element size is reduced.
		@param dimensions set up the dimension through this out-parameter.
	*/
	virtual PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;
};


const int kMinDCLSizPalWidth	=	207;
const int kMaxDCLSizPalWidth	=	10000;
const int kMinDCLSizPalHeight	=	(19 * 2) + 17;
const int kMaxDCLSizPalHeight	=	10000;

#pragma mark DCLSizPalettePanelView implementation

/* CREATE_PERSIST_PMINTERFACE
 Binds the C++ persistent implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PERSIST_PMINTERFACE(DCLSizPalettePanelView, kDCLSizPalettePanelViewImpl)

/* ConstrainDimensions
*/
PMPoint DCLSizPalettePanelView::ConstrainDimensions(const PMPoint& dimensions) const
{
	PMPoint constrainedDim( dimensions );

	constrainedDim.ConstrainTo( PMRect(kMinDCLSizPalWidth, kMinDCLSizPalHeight, kMaxDCLSizPalWidth, kMaxDCLSizPalHeight) );

	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
	IControlView* treeWidget = panelData->FindWidget(kDCLSizListBoxWidgetID);

	if(treeWidget != nil) 
	{
		// The list-box widget itself may further constrain the dimensions, so give it the chance.
		constrainedDim = treeWidget->ConstrainDimensions(constrainedDim);	
	}
	return constrainedDim;
}

// End, DCLSizPalettePanelView.cpp.

