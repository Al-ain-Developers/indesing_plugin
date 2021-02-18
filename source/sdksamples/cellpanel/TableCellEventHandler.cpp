//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/TableCellEventHandler.cpp $
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
#include "IEventDispatcher.h"
#include "ITextControlData.h"
#include "IPanelControlData.h"			/* <IPanelControlData> */
#include "IWidgetParent.h"				/* <IWidgetParent>     */
#include "ITableCellData.h"

// General includes:
#include "DVControlEventHandler.h"

// Project includes:
#include "CelPnlID.h"


/** 
	When the user clicks on the table, this implementation calculates the coordinate of the clicked cell in the table.
	
	@ingroup cellpanel
	
	DV_Note: As a widget eventhandler this should now derive from DVControlEventHandler rather than CEventHandler	
*/
class TableCellEventHandler : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TableCellEventHandler(IPMUnknown *boss): inherited(boss),
													fColCount(0), fRowCount(0),
													fCellWidth(0), fCellHeight(0)
		{};
		/**
			Destructor.
		*/
		~TableCellEventHandler();
		/**
			Left mouse button released.
			param e Contains data about the mouse event.
		*/
		virtual bool16	LButtonUp(IEvent* e);
	
	private:
		/** Private method */
		bool16			FindWhichPane(IEvent* e, bool16 drawSelection);
		void			GetTableCellValues(void);
		void			InvalHiliteBox(IControlView *myView);
		
	private:
		/** Private data member */		
		int32			fColCount, fRowCount;
		int32			fCellWidth,	fCellHeight;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(TableCellEventHandler, kTableCellEventHImpl)

/* TableCellEventHandler
*/
TableCellEventHandler::~TableCellEventHandler()
{
	
}

/* LButtonUp
*/
bool16 TableCellEventHandler::LButtonUp(IEvent* e)
{
	GetTableCellValues();
	
	if (FindWhichPane(e, kTrue)){
 		return kTrue;
	}else
		return kFalse;
}

/* FindWhichPane
*/
bool16 TableCellEventHandler::FindWhichPane(IEvent *e, bool16 drawSelection)
{
	do{

		InterfacePtr<IControlView>		myView(this, UseDefaultIID());
		if(myView == nil) break;
		
		int32	maxViewRow		= fRowCount - 1;
		int32	maxViewColumn	= fColCount - 1;
		
		SysPoint	pt = e->GlobalWhere();
		SysPoint	localWhere = ::ToSys(myView->GlobalToWindow(pt));

		SysRect		viewBBox = myView->GetBBox();
		
		int32	column = (int32)(SysPointH(localWhere) - SysRectLeft(viewBBox));
		int32	row = (int32)(SysPointV(localWhere) - SysRectTop(viewBBox));
		
		column /= fCellWidth;
		row /= fCellHeight;

		if (!((0 <= row) && (0 <= column) && (row < fRowCount) && (column < fColCount)))
		{
			row = column = -1;
			drawSelection = kFalse;
		}
		
		if(!drawSelection) break;
		
		InterfacePtr<IWidgetParent>		myParent(this, UseDefaultIID());
		if(myParent == nil) break;
		
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)myParent->QueryParentFor(IID_ITABLECELLDATA));
		if(pTableCellData == nil) break;
		
		InvalHiliteBox(myView);
		
		pTableCellData->SetSelectRow(row);
		pTableCellData->SetSelectColumn(column);
		
		InvalHiliteBox(myView);
					
		InterfacePtr<IPanelControlData>	panel((IPanelControlData*)myParent->QueryParentFor(IID_IPANELCONTROLDATA)) ;
		if(pTableCellData == nil) break;
		
		InterfacePtr<IControlView>		editBoxView(panel->FindWidget(kTableCellEditBoxWidgetID), UseDefaultIID());
		if(editBoxView == nil) break;
		
		InterfacePtr<ITextControlData>	selectedChar(editBoxView, UseDefaultIID());
		if(selectedChar == nil) break;
		
		row = pTableCellData->GetSelectRow();
		column = pTableCellData->GetSelectColumn();
		
		PMString s = pTableCellData->GetCellString(column, row);
		s.SetTranslatable(kFalse);

		selectedChar->SetString(s, kTrue, kFalse);
		
	}while(false);
	
	return drawSelection;
}

/* GetTableCellValues
*/
void TableCellEventHandler::GetTableCellValues(void)
{
	do{
		InterfacePtr<IWidgetParent>		myParent(this, UseDefaultIID());
		if(myParent == nil) break;
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)myParent->QueryParentFor(IID_ITABLECELLDATA));
		if(pTableCellData == nil) break;
		
		fColCount	=	pTableCellData->GetCellNumberOfColumns();
		fRowCount	=	pTableCellData->GetCellNumberOfRows();
		fCellWidth	=	pTableCellData->GetCellWidth();
		fCellHeight	=	pTableCellData->GetCellHeight();
	}while(false);
}

/* InvalHiliteBox
*/
void TableCellEventHandler::InvalHiliteBox(IControlView* myView)
{
	if(myView == nil) return;
	
	do{
		InterfacePtr<IWidgetParent>		myParent(this, UseDefaultIID());
		if(myParent == nil) break;
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)myParent->QueryParentFor(IID_ITABLECELLDATA));
		if(pTableCellData == nil)break;
		
		int32	top = fCellHeight * (pTableCellData->GetSelectRow() - pTableCellData->GetViewTopRow());
		int32	left = fCellWidth * (pTableCellData->GetSelectColumn() - pTableCellData->GetViewLeftColumn());
		
		PMRect frame(left, top, left + fCellWidth, top + fCellHeight);
							
		myView->Invalidate(&frame);
	}while(false);
}

// End, TableCellEventH.cpp.
