//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/TblBscSuiteTextCSB.cpp $
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
#include "ITextTarget.h"
#include "ITextModel.h"
#include "ITextStoryThreadDict.h"
#include "ITextStoryThread.h"
#include "ITextParcelList.h"
#include "ITextSelectionData.h"
#include "ITextFocus.h"
#include "IComposeScanner.h"
#include "ITableTarget.h"
#include "ICellContentMgr.h"	// for kTextContentType
#include "ICellContent.h"
#include "ITableModel.h"
#include "ITableCommands.h"
#include "ITableSuite.h"
#include "ITableModelList.h"
#include "ISelectUtils.h"
#include "INewTableCmdData.h"
#include "ITextModelCmds.h"
#include "ITableTextSelection.h"

// General includes:
#include "textiterator.h"
#include "ErrorUtils.h"
#include "CmdUtils.h"
#include "TablesUIMinMaxValues.h"
#include "RangeData.h"
#include "CPMUnknown.h"

// Project includes:
#include "TblBscID.h"
#include "ITblBscSuite.h"


/** Text selection boss ITblBscSuite implementation to create
	table content when a text selection is active.

	
	@see ITblBscSuite
	@ingroup tablebasics
*/
class TblBscSuiteTextCSB : public CPMUnknown<ITblBscSuite>
{
public:
	/** Constructor.
		@param boss refers to boss class on which this is aggregated.
	*/
	TblBscSuiteTextCSB (IPMUnknown *boss);
	
	/** Destructor.
	*/
	virtual ~TblBscSuiteTextCSB (void);

public:
	/**	See ITblBscSuite::CanInsertTable.
	*/
	virtual bool16 CanInsertTable() const;

	/**	See ITblBscSuite::InsertTable.
	*/
	virtual ErrorCode InsertTable(int32 numRows, int32 numCols);

	/**	See ITblBscSuite::CanSetCellText.
	*/
	virtual bool16 CanSetCellText(int32 row, int32 col) const;

	/**	See ITblBscSuite::SetCellText.
	*/
	virtual ErrorCode SetCellText(int32 row, int32 col, const WideString& text);

	/**	See ITblBscSuite::CanGetCellText.
	*/
	virtual bool16 CanGetCellText(int32 row, int32 col) const;

	/**	See ITblBscSuite::GetCellText.
	*/
	virtual void GetCellText(int32 row, int32 col, WideString& text) const;

private:
	/**	Figure out the table associated with the text selection.
		@return reference to table model, nil otherwise.
	*/
	ITableModel* queryTableModel() const;

	/**	Figure out the table associated with the text selection and
		check the row and column are valid.
		@param row coord of row to validate
		@param col coord of column to validate
		@return reference to table model if row and column valid, nil otherwise.
	*/
	ITableModel* queryTableModelAndValidateRowCol(int32 row, int32 col) const;

	/**	Set the text of the given table cell.
		@return kSuccess if operation succeeded, kFailure otherwise.
		@param tableModel reference to the table model
		@param row 
		@param col
		@param text
	*/
	ErrorCode setCellText(InterfacePtr<ITableModel>& tableModel, 
							int32 row, int32 col, 
							const WideString& text);

	/**	Extract a string containing the text in the given text story thread.
		@param textStoryThread
		@param text 
	*/
	void getText(const ITextStoryThread* textStoryThread, WideString& text) const;

};

/*  Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TblBscSuiteTextCSB, kTblBscSuiteTextCSBImpl)


/*
*/
TblBscSuiteTextCSB::TblBscSuiteTextCSB(IPMUnknown* boss) :
	CPMUnknown<ITblBscSuite>(boss)
{
}

/*
*/
TblBscSuiteTextCSB::~TblBscSuiteTextCSB(void)
{
}

/*
*/
bool16 TblBscSuiteTextCSB::CanInsertTable() const
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableSuite> tableSuite(this, UseDefaultIID());
		ASSERT(tableSuite);
		if (!tableSuite) {
			break;
		}
		result = tableSuite->CanInsertTable();

	} while(false);
	return result;
}

/*
*/
ErrorCode TblBscSuiteTextCSB::InsertTable(int32 numRows, int32 numCols)
{
	ErrorCode result = kFailure;
	do
	{
		ASSERT(numRows>0 && numCols>0);
		if(numRows<=0 || numCols<=0) {
			break;
		}
		InterfacePtr<ITableSuite> tableSuite(this, UseDefaultIID());
		ASSERT(tableSuite);
		if (!tableSuite) {
			break;
		}

		const int32 headerRows = 0;
		const int32 footerRows = 0;
		tableSuite->InsertTable(numRows, numCols, headerRows, footerRows);

		result = kSuccess;

	} while(false);

	return result;
}

/*
*/
bool16 TblBscSuiteTextCSB::CanSetCellText(int32 row, int32 col) const
{
	bool16 result = kFalse;
	do
	{
		// If we can get a table model and the row and column are valid.
		InterfacePtr<ITableModel> tableModel(this->queryTableModelAndValidateRowCol(row, col));
		if (tableModel == nil)
		{
			break;
		}

		// And it is an anchor.
		bool16 isAnchor = tableModel->IsAnchor(GridAddress(row, col));
		if(!isAnchor) {
			break;
		}

		// We can set text for this cell.
		result = kTrue;

	} while(false);

	return result;
}

/*
*/
ErrorCode TblBscSuiteTextCSB::SetCellText
(
 int32 row, 
 int32 col, 
 const WideString& text
)
{
	ErrorCode result = kFailure;
	do
	{
		InterfacePtr<ITableModel> tableModel(this->queryTableModelAndValidateRowCol(row,col));
		if (tableModel == nil)
		{
			break;
		}

		// Set the text for the cell.
		result = setCellText(tableModel, row, col, text);

	} while(false);

	return result;
}


/*
*/
bool16 TblBscSuiteTextCSB::CanGetCellText(int32 row, int32 col) const
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableModel> tableModel(this->queryTableModelAndValidateRowCol(row, col));
		if (tableModel == nil){
			break;
		}

		GridAddress targetCellGridAddress(row, col);
		GridID targetCellGridID = tableModel->GetGridID(targetCellGridAddress);
		if (targetCellGridID == kInvalidGridID) {
			break;
		}

		InterfacePtr<ITextStoryThreadDict> textStoryThreadDict(tableModel, UseDefaultIID());
		ASSERT(textStoryThreadDict);
		if (textStoryThreadDict == nil) {
			break;
		}

		InterfacePtr<ITextStoryThread> textStoryThread(textStoryThreadDict->QueryThread(targetCellGridID));
		ASSERT(textStoryThread);
		if (textStoryThread == nil){
			break;
		}
		
		result = kTrue;

	} while(false);

	return result;
}

/*
*/
void TblBscSuiteTextCSB::GetCellText(int32 row, int32 col, WideString& text) const
{
	do
	{
		InterfacePtr<ITableModel> tableModel(this->queryTableModelAndValidateRowCol(row, col));
		if (tableModel == nil) {
			break;
		}

		GridAddress targetCellGridAddress(row, col);
		GridID targetCellGridID = tableModel->GetGridID(targetCellGridAddress);
		if (targetCellGridID == kInvalidGridID) {
			break;
		}

		InterfacePtr<ITextStoryThreadDict> textStoryThreadDict(tableModel, UseDefaultIID());
		ASSERT(textStoryThreadDict);
		if (textStoryThreadDict == nil) {
			break;
		}

		InterfacePtr<ITextStoryThread> textStoryThread(textStoryThreadDict->QueryThread(targetCellGridID));
		ASSERT(textStoryThread);
		if (textStoryThread == nil){
			break;
		}

		this->getText(textStoryThread, text);

	} while(false);
}

/*
*/
ITableModel* TblBscSuiteTextCSB::queryTableModel() const
{
	ITableModel* result = nil;
	do
	{
		// Aquire the table model.
		InterfacePtr<ITableTarget> tableTarget(this,UseDefaultIID());
		ASSERT(tableTarget);
		if(!tableTarget) {
			break;
		}
		UIDRef tableUIDRef = tableTarget->GetModel();
		if (tableUIDRef == UIDRef(nil, kInvalidUID))
		{
			ASSERT_FAIL("invalid tableUIDRef");
			break;
		}

		InterfacePtr<ITableModel> tableModel(tableUIDRef, UseDefaultIID());
		ASSERT(tableModel);
		if (tableModel == nil) {
			break;
		}

		result = tableModel;
		result->AddRef();
	} while(false);

	return result;
}

/*
*/
ITableModel* TblBscSuiteTextCSB::queryTableModelAndValidateRowCol(int32 row, int32 col) const
{
	ITableModel* result = nil;
	do
	{
		InterfacePtr<ITableModel> tableModel(this->queryTableModel());
		ASSERT(tableModel);
		if (tableModel == nil){
			break;
		}

		// Check the row and cell are valid for the table.
		if (tableModel->IsValidRow(row) == kFalse) {
			break;
		}

		if (tableModel->IsValidColumn(col) == kFalse) {
			break;
		}

		result = tableModel;
		result->AddRef();

	} while(false);

	return result;
}

/*
*/
ErrorCode TblBscSuiteTextCSB::setCellText(InterfacePtr<ITableModel>& tableModel, 
									int32 row, int32 col, const WideString& text)
{
	ErrorCode result = kFailure;
	do {
		ASSERT(tableModel);
		if(tableModel==nil) {
			break;
		}

		bool16 isAnchor = tableModel->IsAnchor(GridAddress(row, col));
		ASSERT(isAnchor);
		if(!isAnchor) {
			break;
		}

		InterfacePtr<ITableCommands> tableCommands(tableModel, UseDefaultIID());
		ASSERT(tableCommands);
		if(tableCommands==nil) {
			break;
		}

		result = tableCommands->SetCellText(text, GridAddress(row, col));
		ASSERT(result == kSuccess);

	} while(false);
	return result;

}


/*
*/
void TblBscSuiteTextCSB::getText(const ITextStoryThread* textStoryThread, WideString& text) const
{
	do
	{
		InterfacePtr<ITextModel> textModel(textStoryThread->QueryTextModel());
		if (textModel == nil) {
			break;
		}
		
		int32 span=(-1);
		TextIndex at = textStoryThread->GetTextStart(&span);
		TextIterator beginTextChunk(textModel, at);
		TextIterator endTextChunk(textModel, at + span);
	
		std::copy(beginTextChunk, endTextChunk, std::back_inserter(text));
	
	} while(false);
}

// End, TblBscSuiteTextCSB.cpp.



