//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/CelPnlPanelView.cpp $
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
#include "ITableCellData.h"

// General includes:
#include "PalettePanelView.h"		

// Project includes:
#include "CelPnlID.h"
#include "CelPnlDefines.h"


/** CelPnlPanelView restrict the size of the panel when a panel draws.
	CelPnlPanelView implements IControlView based on the partial implementation CIDErasablePanelView.

	@ingroup cellpanel
	
*/
class  CelPnlPanelView : public PalettePanelView 
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CelPnlPanelView(IPMUnknown* boss);

	/**
		Destructor.
	*/
	virtual	~CelPnlPanelView(){};
	
	/**
		Called after the widget hierarchy is created. Can be
		overriden to do initialization that may need the hierarchy
		to perform.
	*/
	virtual void		DoPostCreate ();
	
	/**
		Before resizing a widget, the client can ask if the size makes
		sense by calling this method.
		@param dimensions The size of the adjusted panel is returned.
		@return  Return size constraints.
	*/
	virtual PMPoint		ConstrainDimensions(const PMPoint& dimensions) const;
	
	/**
		Resize the widget.
		@param dimensions Specify new dimensions for the panel view.
		@param invalidate Set to kTrue if you want to invalidate the view.
	*/
	virtual void		Resize(const PMPoint& dimensions, bool16 invalidate);
	
private:
	
	typedef PalettePanelView Inherited;
};

/* CREATE_PERSIST_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PERSIST_PMINTERFACE(CelPnlPanelView, kCelPnlPanelViewImpl)

/* CelPnlPanelView 
*/
CelPnlPanelView::CelPnlPanelView(IPMUnknown* boss) : Inherited(boss)
{
}

/* DoPostCreate 
*/
void CelPnlPanelView::DoPostCreate()
{
	Inherited::DoPostCreate();
}

/* ConstrainDimensions 
*/
PMPoint CelPnlPanelView::ConstrainDimensions(const PMPoint& desiredDimen) const
{
	PMPoint constrainedDim = desiredDimen;
	
	do{

		if (constrainedDim.X() < kPanelWidth)
			constrainedDim.X(kPanelWidth);
		else if (constrainedDim.X() > 1000)
			constrainedDim.X(1000);

		if (constrainedDim.Y() < kPanelHeight)
			constrainedDim.Y(kPanelHeight);
		else if (constrainedDim.Y() > 1000)
			constrainedDim.Y(1000);
			
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		if(panelData == nil) break;
		InterfacePtr<IControlView> editBox(panelData->FindWidget(kTableCellEditBoxWidgetID), UseDefaultIID());
		if(editBox == nil) break;
		InterfacePtr<IControlView> hScrollBar(panelData->FindWidget(kTableCellHScrollWidgetID), UseDefaultIID());
		if(hScrollBar == nil) break;
		InterfacePtr<IControlView> vScrollBar(panelData->FindWidget(kTableCellScrollWidgetID), UseDefaultIID());
		if(vScrollBar == nil) break;
		
		constrainedDim.Y(constrainedDim.Y() - hScrollBar->GetFrame().Height() - editBox->GetFrame().Height() + 1);
		constrainedDim.X(constrainedDim.X() - vScrollBar->GetFrame().Width() + 1);
		
		InterfacePtr<ITableCellData> pTableCellData(this, UseDefaultIID());
		if(pTableCellData)
			constrainedDim = pTableCellData->ConstrainDimensions(constrainedDim);

		constrainedDim.Y(constrainedDim.Y() + hScrollBar->GetFrame().Height() + editBox->GetFrame().Height() - 1);
		constrainedDim.X(constrainedDim.X() + vScrollBar->GetFrame().Width() - 1);
		
	}while(false);
	return constrainedDim;
}

/* Resize 
*/
void CelPnlPanelView::Resize(const PMPoint& dimensions, bool16 invalidate)
{
	Inherited::Resize(dimensions, invalidate);
	
	do{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		if(panelData == nil) break;
		InterfacePtr<ITableCellData> pTableCellData(this, UseDefaultIID());
		if(pTableCellData == nil) break;

		pTableCellData->Invalidate();
	}while(false);
}

// End, CelPnlPanelView.cpp.
