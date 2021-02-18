//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/TblBscDialogController.cpp $
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
#include "ITextValue.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ITriStateControlData.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"

// General includes:
#include "CDialogController.h"
#include "WideString.h"

// Project includes:
#include "TblBscID.h"
#include "ITblBscSuite.h"

/** Implements a dialog that inserts a table via a custom suite, ITblBscSuite. 

	Widgets that require dynamic monitoring are handled in TblBscDialogObserver.

	
	@ingroup tablebasics
*/
class TblBscDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TblBscDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~TblBscDialogController() {}

	protected:
		/** Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
			@param ac context in which dialog is to be performed.
		*/
		virtual void InitializeDialogFields(IActiveContext* context);

		/**	Gathers the values of the widgets and queries the selection 
			manager for an ITblBscSuite inteface to create a table as 
			specified by the dialog's widgets.
			@param ac context in which dialog is to be performed.
			@param widgetId identifies the widget that caused dialog changes to be applied.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);

	private:
		bool16 isTristateSelected(const WidgetID&  widgetID);
		void fillTable(InterfacePtr<ITblBscSuite> & tblBscSuite,
						int32 numRows, int32 numCols);
		void setControlEnabled(const WidgetID&  widgetID, bool16 enabled);

		
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TblBscDialogController, kTblBscDialogControllerImpl)

/*
*/
void TblBscDialogController::InitializeDialogFields(IActiveContext* context) 
{
	InterfacePtr<ITblBscSuite> tblBscSuite(context->GetContextSelection(), UseDefaultIID());
	ASSERT(tblBscSuite);
	if (tblBscSuite) {
		ASSERT(tblBscSuite->CanInsertTable());
	}

	bool16 enabledState = this->isTristateSelected(kTblBscPreFilledCheckboxWidgetID);
	
	this->SetTriStateControlData(kTblBscAddressFillRadioWidgetID, kTrue);
	this->SetTriStateControlData(kTblBscPlaceholderFillRadioWidgetID, kFalse);


	this->setControlEnabled(kTblBscAddressFillRadioWidgetID, enabledState);
	this->setControlEnabled(kTblBscPlaceholderFillRadioWidgetID, enabledState);


	this->SetTextValue(kTblBscNumRowsEditWidgetID,PMReal(2.0));
	this->SetTextValue(kTblBscNumColsEditWidgetID,PMReal(2.0));

}

/*
*/
void TblBscDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	do {
		// InDesign 2.0 to InDesign 3.0 change.
		// Use IActiveContext parameter passed into method to get the suite
		// instead of using ISelectionUtils.
		InterfacePtr<ITblBscSuite> tblBscSuite(myContext->GetContextSelection(), UseDefaultIID());
		if (tblBscSuite == nil)
		{
			ASSERT_FAIL("Where's ITblBscSuite?");
			break;
		}

		if (tblBscSuite->CanInsertTable() == kFalse)
		{
			ASSERT_FAIL("Can't insert the table!");
			break;
		}

		int32 numRows = ToInt32(this->GetTextValue(kTblBscNumRowsEditWidgetID));
		int32 numCols = ToInt32(this->GetTextValue(kTblBscNumColsEditWidgetID));
		bool16 isFilled = this->isTristateSelected(kTblBscPreFilledCheckboxWidgetID);

		ErrorCode status = tblBscSuite->InsertTable(numRows, numCols);
		ASSERT(status == kSuccess);
		if(status != kSuccess) {
			break;
		}

		if(isFilled) 
		{
			this->fillTable(tblBscSuite,numRows, numCols);
		}
	
	} while(false);
	
}

/*
*/
void TblBscDialogController::fillTable(InterfacePtr<ITblBscSuite>& tblBscSuite, 
										int32 numRows, int32 numCols)
{
	do {
		if(tblBscSuite==nil) {
			break;
		}

		bool16 isCellAddress= this->isTristateSelected(kTblBscAddressFillRadioWidgetID);

		for (int32 row = 0; row < numRows; row++)
		{
			for (int32 col = 0; col < numCols; col++)
			{
				PMString buf("");			
				if(isCellAddress) 
				{
					buf += "(";
					buf.AppendNumber(row);
					buf += ",";
					buf.AppendNumber(col);
					buf += ")";
				} 
				else 
				{
					buf += "Lorem ipsum dolor sit amet, consectetuer adipiscing elit,"
							"sed diam nonummy nibh euismod tincidunt.";
				}

				WideString text(buf);
				if (tblBscSuite->CanSetCellText(row, col) == kTrue) 
				{
					tblBscSuite->SetCellText(row, col, text);
				}

			}
		}

	} while(false);
}



/*
*/
bool16 TblBscDialogController::isTristateSelected(const WidgetID&  widgetID) 
{
	bool16 retval = kFalse;

	do {
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(panelControlData == nil) 
		{
			break;
		}

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView == nil)
		{
			break;
		}

		InterfacePtr<ITriStateControlData> itristatecontroldata(controlView, UseDefaultIID());
		ASSERT(itristatecontroldata);
		if(itristatecontroldata==nil) 
		{
			break;
		}
		retval = itristatecontroldata->IsSelected();

	} while(false);

	return retval;
}

/*
*/
void TblBscDialogController::setControlEnabled(const WidgetID&  widgetID, bool16 enabled)
{
	bool16 retval = kFalse;

	do {
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(panelControlData == nil) 
		{
			break;
		}

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView == nil)
		{
			break;
		}

		if(enabled) 
		{
			controlView->Enable(); 
		} else 
		{
			controlView->Disable();
		}


	} while(false);

}


// End, TblBscDialogController.cpp.



