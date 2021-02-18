//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTxtUIPanelView.cpp $
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

// Interface includes:
#include "IPanelControlData.h"
#include "IPMStream.h"	

// General includes:
#include "PalettePanelView.h"		

// Project includes:
#include "CusCondTxtUIID.h"


/** CusCondTxtPanelView restrict the size of the panel when a panel draws.
	CusCondTxtPanelView implements IControlView based on the partial implementation PalettePanelView.

	@ingroup customconditionaltext
	
*/
class  CusCondTxtPanelView : public PalettePanelView 
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusCondTxtPanelView(IPMUnknown* boss);

	/**
		Destructor.
	*/
	virtual	~CusCondTxtPanelView(){};
	
	/**
		Before resizing a widget, the client can ask if the size makes
		sense by calling this method.
		@param dimensions The size of the adjusted panel is returned.
		@return  Return size constraints.
	*/
	virtual PMPoint		ConstrainDimensions(const PMPoint& dimensions) const;
	
private:
	
	// define the min width and height for the panel
	static const int	kMinimumPanelWidth	=	207;
	static const int 	kMinimumPanelHeight	=	290;
};

/* CREATE_PERSIST_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PERSIST_PMINTERFACE(CusCondTxtPanelView, kCusCondTxtUIPanelViewImpl)

/* CusCondTxtPanelView 
*/
CusCondTxtPanelView::CusCondTxtPanelView(IPMUnknown* boss) : PalettePanelView(boss)
{
}

/* ConstrainDimensions 
*/
PMPoint CusCondTxtPanelView::ConstrainDimensions(const PMPoint& desiredDimen) const
{
	PMPoint constrainedDim = desiredDimen;

	// Width can vary if not below minimum
	if(constrainedDim.X() < kMinimumPanelWidth)
	{
		constrainedDim.X(kMinimumPanelWidth);
	}

	// Height can vary if not below minimum
	if(constrainedDim.Y() < kMinimumPanelHeight)
	{
		constrainedDim.Y(kMinimumPanelHeight);
	}

	return constrainedDim;
}

