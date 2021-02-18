//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectTableModel.cpp $
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
#include "ITableSuite.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li How to inspect various properties of a story's table model (ITableSuite)

	This snippet highlights those ITableSuite functions that
	answer questions about the selection or about the table 
	containing the selection. This snippet does not cover how
	to override supplied cell/table/row attributes; the 
	TableAttributes SDK sample plug-in covers this.

	For additional information regarding table attributes, look in the 
	browseable API documentation for kTableAttrXXXBoss entries.

  	@ingroup sdk_snippet
  	@ingroup sdk_table
	@see ITableSuite
*/

class SnpInspectTableModel 
{
public:
	
	/** Constructor.
	 */
	SnpInspectTableModel() {}

	/** Destructor.
	 */
	virtual ~SnpInspectTableModel() {}

	/** Inspect table containing selection.
		@param tchoice Specifies index of refined table inspection.
		@param tableSuite Supplied ITableSuite*.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectTable(
		int32 tchoice, const InterfacePtr<ITableSuite>& tableSuite);

	/** Inspect selection in table.
		@param sitchoice Specifies index of refined selection inspection.
		@param tableSuite Supplied ITableSuite*.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectSelectionInTable(
		int32 sitchoice, const InterfacePtr<ITableSuite>& tableSuite);


};

/* InspectTable
*/
ErrorCode SnpInspectTableModel::InspectTable(
	int32 tchoice, const InterfacePtr<ITableSuite>& tableSuite)
{
	ErrorCode result = kFailure;
	do
	{
		SNIPLOG("=== Inspecting table ===");
		if (tchoice == 0)
		{
			// Table model is valid
			if (tableSuite->CanGetTableProperties() == kFalse)
			{
				break;
			}

			// Underlying number of rows in table.
			int32 numrows = tableSuite->GetNumRowsInTable();
			SNIPLOG("underlying number of rows is %d", numrows);

			// Number of user rows in table (underlying rows may be combined).
			int32 usernumrows = tableSuite->GetUserNumRowsInTable();
			SNIPLOG("number of user rows is %d", usernumrows);

			// Number of header rows.
			if (tableSuite->CanGetHeader())
			{
				int32 numhrows = tableSuite->GetNumHeaderRowsInTable();
				SNIPLOG("number of header rows is %d", numhrows);
			}

			// Number of footer rows
			if (tableSuite->CanGetFooter())
			{
				int32 numfrows = tableSuite->GetNumFooterRowsInTable();
				SNIPLOG("number of footer rows is %d", numfrows);
			}
			result = kSuccess;
		}

		else if (tchoice == 1)
		{
			// Table model is valid
			if (tableSuite->CanGetTableProperties() == kFalse)
			{
				break;
			}

			// Underlying number of columns in table.
			int32 numcols = tableSuite->GetNumColsInTable();
			SNIPLOG("underlying number of columns is %d", numcols);

			// Number of user columns in table (underlying columns may be combined).
			int32 usernumcols = tableSuite->GetUserNumColsInTable();
			SNIPLOG("number of user columns is %d", usernumcols);

			result = kSuccess;
		}
	} while(false);
	return result;
}


/* InspectSelectionInTable.
*/
ErrorCode SnpInspectTableModel::InspectSelectionInTable(
	int32 sitchoice, const InterfacePtr<ITableSuite>& tableSuite)
{
	ErrorCode result = kFailure;
	do
	{
		SNIPLOG("=== Inspecting selection in table ===");
		if (sitchoice == 0)
		{
			// Row size
			if (tableSuite->CanGetRowSize())
			{
				PMReal rowsize = tableSuite->GetRowSize();
				SNIPLOG("row size is %f pts", ::ToDouble(rowsize));
				result = kSuccess;
			}
			else
			{
				SNIPLOG("row size error: selected row heights vary");
			}
			// UserRowNumber
			ITableSuite::UserRowNumber urn = tableSuite->GetUserCurrentRowNumber();
			SNIPLOG("Selection is in user row %d.", urn.rowNumber);
			if (urn.rowType == 0)
				SNIPLOG("Selection user row type is eHeader.");
			if (urn.rowType == 1)
				SNIPLOG("Selection user row type is eBody.");
			if (urn.rowType == 2)
				SNIPLOG("Selection user row type is eFooter.");
			// Max/min row size of selection
			if (tableSuite->CanGetMaxMinRowSizeOfSelection())
			{
				PMReal max = tableSuite->GetMaxRowSizeOfSelection();
				PMReal min = tableSuite->GetMinRowSizeOfSelection();
				SNIPLOG("Maximum row size of selection is %f pts.", ::ToDouble(max));
				SNIPLOG("Minimum row size of selection is %f pts.", ::ToDouble(min));
			}
		}

		else if (sitchoice == 1)
		{
			// Column size
			if (tableSuite->CanGetColumnSize())
			{
				PMReal columnsize = tableSuite->GetColumnSize();
				SNIPLOG("column size is %f pts.", ::ToDouble(columnsize));
				result = kSuccess;
			}
			else
			{
				SNIPLOG("column size error: selected column widths vary");
			}
			// User column number
			int32 colnum = tableSuite->GetUserCurrentColNumber();
			SNIPLOG("Selection is in user column %d.", colnum);
		}

		else if (sitchoice == 2)
		{
			// Cell height
			if (tableSuite->CanGetCellHeight())
			{
				PMReal cellheight = tableSuite->GetCellHeight();
				SNIPLOG("cell height is %f pts.", ::ToDouble(cellheight));
				result = kSuccess;
			}
			else
			{
				SNIPLOG("cell height error: selected cell heights vary");
				result = kFailure;
			}
			// Cell width
			if (tableSuite->CanGetCellWidth())
			{
				PMReal cellwidth = tableSuite->GetCellWidth();
				SNIPLOG("cell width is %f pts.", ::ToDouble(cellwidth));
				result = kSuccess;
			}
			else
			{
				SNIPLOG("cell width error: selected cell widths vary");
				result = kFailure;
			}
		}
		else
		{
			ASSERT("INVALID OPTION");
		}
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpInspectTableModel available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerInspectTableModel : public SnpRunnable
{
public:
	/** Inspect table containing selection.
		@param tchoice Specifies index of refined table inspection.
		@param tableSuite Supplied ITableSuite*.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectTable(
		int32 tchoice, const InterfacePtr<ITableSuite>& tableSuite);

	/** Inspect selection in table.
		@param sitchoice Specifies index of refined selection inspection.
		@param tableSuite Supplied ITableSuite*.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectSelectionInTable(
		int32 sitchoice, const InterfacePtr<ITableSuite>& tableSuite);

private:

public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerInspectTableModel();

	/** Destructor.
	 */
	virtual ~_SnpRunnerInspectTableModel();

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}
};
/* Constructor.
*/
_SnpRunnerInspectTableModel::_SnpRunnerInspectTableModel() : SnpRunnable("InspectTableModel")
{
	// Describe what your snippet does.
	this->SetDescription("Reports properties of a table or of a selection in a table.");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("Document containing selection in table");

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
}

/* Destructor.
*/
_SnpRunnerInspectTableModel::~_SnpRunnerInspectTableModel()
{
}

/* Check whether your preconditions are met.
*/
bool16	_SnpRunnerInspectTableModel::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableSuite> 
			tableSuite(runnableContext, UseDefaultIID());
		if (tableSuite != nil)
		{
			result = tableSuite->CanGetTableProperties();
		}
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerInspectTableModel::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		SnpInspectTableModel instance;

		InterfacePtr<ITableSuite> 
			tableSuite(runnableContext, UseDefaultIID());
		if (tableSuite == nil)
		{
			status = kFailure;
			break;
		}
		
		// Prompt for inspection type.
		K2Vector<PMString> choices;
		choices.push_back(PMString("about table")); //0
		choices.push_back(PMString("about selection in table")); //1
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("Which type of data do you want to inspect?"), choices);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		// Prompt for refined table inspection type.
		if (choice == 0)
		{
			K2Vector<PMString> tchoices;
			tchoices.push_back(PMString("row data")); //0
			tchoices.push_back(PMString("column data")); //1
			Utils<ISnipRunParameterUtils> parameterUtils;
			int32 tchoice = 
				parameterUtils->GetChoice(PMString("Which type of table data do you want to inspect?"), tchoices);
			if (parameterUtils->WasDialogCancelled() == kFalse)
			{
				status = instance.InspectTable(tchoice, tableSuite);
			}
		}
		// Prompt for refined selection-in-table inspection type.
		else if (choice == 1)
		{
			K2Vector<PMString> sitchoices;
			sitchoices.push_back(PMString("row selection data")); //0
			sitchoices.push_back(PMString("column selection data")); //1
			sitchoices.push_back(PMString("cell selection data")); //2
			Utils<ISnipRunParameterUtils> parameterUtils;
			int32 sitchoice = 
				parameterUtils->GetChoice(PMString("Which type of table selection data do you want to inspect?"), sitchoices);
			if (parameterUtils->WasDialogCancelled() == kFalse)
			{
				status = instance.InspectSelectionInTable(sitchoice, tableSuite);
			}
		}
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInspectTableModel instance_SnpRunnerInspectTableModel;
DEFINE_SNIPPET(_SnpRunnerInspectTableModel) 	

// End, SnpInspectTableModel.cpp

