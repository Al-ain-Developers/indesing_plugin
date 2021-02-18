//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpModifyTable.cpp $
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
#include "TableTypes.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// TODO please make into something that has code other than in the Run method
/** 
	\li Code showing modification of a table using ITableSuite.

	This snippet highlights those ITableSuite functions that
	perform actions on the selection or on the table containing
	the selection. This snippet does not cover creating a table 
	and filling its cells with text; the TableBasics SDK sample
	plug-in covers this.

	For additional information regarding table attributes, look in the 
	browseable API documentation for kTableAttrXXXBoss entries.

	@ingroup sdk_snippet
  	@ingroup sdk_table
	@see ITableSuite
	@see ITableModel
*/
class SnpModifyTable
{
public:
	/** facade to ITableSuite::InsertRows. 
	 * 	@see ITableSuite::InsertRows
	 */
	ErrorCode InsertRows(ITableSuite* tableSuite, int32 howMany, Tables::ERelativePosition pos, const PMReal& rowHeight);

	/** facade to ITableSuite::InsertColumns. 
	 * 	@see ITableSuite::InsertColumns
	 */
	ErrorCode InsertColumns(ITableSuite* tableSuite, int32 howMany, Tables::ERelativePosition pos, const PMReal&  colWidth);

	/** facade to ITableSuite::DeleteRows.
	 * 	@see ITableSuite::DeleteRows
	 */
	ErrorCode DeleteRows(ITableSuite* tableSuite);

	/** facade to ITableSuite::DeleteColumns.
	 * 	@see ITableSuite::DeleteColumns
	 */
	ErrorCode DeleteColumns(ITableSuite* tableSuite);

	/** facade to ITableSuite::MergeCells.
	 * 	@see ITableSuite::MergeCells
	 */
	ErrorCode MergeCells(ITableSuite* tableSuite);

	/** facade to ITableSuite::UnmergeCell.
	 * 	@see ITableSuite::UnmergeCell
	 */
	ErrorCode UnmergeCell(ITableSuite* tableSuite);
};

/* InsertRows
*/
ErrorCode SnpModifyTable::InsertRows(ITableSuite* tableSuite, int32 howMany, Tables::ERelativePosition pos, const PMReal& rowHeight)
{
	ErrorCode status = kFailure;
	do
	{
		if (tableSuite == nil)
		{
			ASSERT("TableSuite is nil!");
			break;
		}

		if (tableSuite->CanInsertRows(pos))
		{
			tableSuite->InsertRows(howMany, pos, rowHeight);
			SNIPLOG("InsertRows: %d rows, rowheight=%f pts.", howMany, ::ToDouble(rowHeight));
			status = kSuccess;
		}
		else
		{
			SNIPLOG("Could not insert rows.");
		}
	} while (false);
	return status;
}

/* InsertColumns 
*/
ErrorCode SnpModifyTable::InsertColumns(ITableSuite* tableSuite, int32 howMany, Tables::ERelativePosition pos, const PMReal&  colWidth)
{
	ErrorCode status = kFailure;
	do
	{
		if (tableSuite == nil)
		{
			ASSERT("TableSuite is nil!");
			break;
		}
	
		if (tableSuite->CanInsertColumns(pos))
		{
			tableSuite->InsertColumns(howMany, pos, colWidth);
			SNIPLOG("InsertColumns: %d cols, colwidth=%f pts.", howMany, ::ToDouble(colWidth));
			status = kSuccess;
		}
		else
		{
			SNIPLOG("Could not insert columns.");
		}
	} while (false);
	return status;
}

/* DeleteRows
*/
ErrorCode SnpModifyTable::DeleteRows(ITableSuite* tableSuite)
{
	ErrorCode status = kFailure;
	do
	{
		if (tableSuite == nil)
		{
			ASSERT("TableSuite is nil!");
			break;
		}

		if (tableSuite->CanDeleteRows())
		{
			tableSuite->DeleteRows();
			SNIPLOG("Deleted row");
			status = kSuccess;
		}
		else
		{
			SNIPLOG("Could not delete rows.");
		}
	} while (false);
	return status;
}

/* DeleteColumns
*/
ErrorCode SnpModifyTable::DeleteColumns(ITableSuite* tableSuite)
{
	ErrorCode status = kFailure;
	do
	{
		if (tableSuite == nil)
		{
			ASSERT("TableSuite is nil!");
			break;
		}

		if (tableSuite->CanDeleteColumns())
		{
			tableSuite->DeleteColumns();
			SNIPLOG("Deleted column");
			status = kSuccess;
		}
		else
		{
			SNIPLOG("Could not delete columns.");
		}
	} while (false);
	return status;
}

/* MergeCells
*/
ErrorCode SnpModifyTable::MergeCells(ITableSuite* tableSuite)
{
	ErrorCode status = kFailure;
	do
	{
		if (tableSuite == nil)
		{
			ASSERT("TableSuite is nil!");
			break;
		}

		if (tableSuite->CanMergeCells())
		{
			tableSuite->MergeCells();
			SNIPLOG("Merged cells");
			status = kSuccess;
		}
		else
		{
			SNIPLOG("Could not merge cells. Need a selection of cells.");
		}
	} while (false);
	return status;
}

/* UnmergeCell
*/
ErrorCode SnpModifyTable::UnmergeCell(ITableSuite* tableSuite)
{
	ErrorCode status = kFailure;
	do
	{
		if (tableSuite == nil)
		{
			ASSERT("TableSuite is nil!");
			break;
		}

		if (tableSuite->CanUnmergeCell())
		{
			tableSuite->UnmergeCell();
			SNIPLOG("Unmerged cells");
			status = kSuccess;
		}
		else
		{
			SNIPLOG("Could not unmerge cells.");
		}
	} while (false);
	return status;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpModifyTable available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerModifyTable : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerModifyTable();

	/** Destructor.
	 */
	virtual ~_SnpRunnerModifyTable();

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


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor.
*/
_SnpRunnerModifyTable::_SnpRunnerModifyTable() : SnpRunnable("ModifyTable")
{
	// Describe what your snippet does.
	this->SetDescription("Modifies a table.");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("Selection in a table");

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
}

/* Destructor.
*/
_SnpRunnerModifyTable::~_SnpRunnerModifyTable()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerModifyTable::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerModifyTable::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	SnpModifyTable instance;

	do
	{
		InterfacePtr<ITableSuite> 
			tableSuite(runnableContext, UseDefaultIID());
		if (tableSuite == nil)
		{
			status = kFailure;
			break;
		}
		
		// Prompt for inspection type.
		K2Vector<PMString> choices;
		choices.push_back(PMString("insert rows")); //0
		choices.push_back(PMString("insert columns")); //1
		choices.push_back(PMString("delete rows")); //2
		choices.push_back(PMString("delete columns")); //3
		choices.push_back(PMString("merge cells")); //4
		choices.push_back(PMString("unmerge cell")); //5
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = 
			parameterUtils->GetChoice(PMString("What table modification do you want to make?"), choices);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		// Prompt for parameters.
		if (choice == 0)	// insert rows
		{
			// Get number of rows to insert.
			int32 numrows = 
				parameterUtils->GetInt32(PMString("Number of rows to insert"), 1, 1, 30);
			if (parameterUtils->WasDialogCancelled())
			{
				break;
			}

			// Get relative position for insert.
			K2Vector<PMString> poschoices;
			poschoices.push_back(PMString("eBefore"));
			poschoices.push_back(PMString("eAfter"));
			Tables::ERelativePosition pos = 
				(Tables::ERelativePosition)(parameterUtils->GetChoice(
				PMString("Relative position"), poschoices, Tables::eBefore));
			if (parameterUtils->WasDialogCancelled())
			{
				break;
			}

			// Get row height.
			PMReal rowheight = 
				parameterUtils->GetPMReal(PMString("Height of rows to insert"), 10.0, 5.0, 40.0);
			if (parameterUtils->WasDialogCancelled())
			{
				break;
			}

			status = instance.InsertRows(tableSuite, numrows, pos, rowheight);
		}

		else if (choice == 1)	// insert columns
		{
			// Get number of columns to insert.
			int32 numcols = 
				parameterUtils->GetInt32(PMString("Number of columns to insert"), 1, 1, 10);
			if (parameterUtils->WasDialogCancelled())
			{
				break;
			}

			// Get relative position for insert.
			K2Vector<PMString> poschoices;
			poschoices.push_back(PMString("eBefore"));
			poschoices.push_back(PMString("eAfter"));
			Tables::ERelativePosition pos = 
				(Tables::ERelativePosition)(parameterUtils->GetChoice(
				PMString("Relative position"), poschoices, Tables::eBefore));
			if (parameterUtils->WasDialogCancelled())
			{
				break;
			}

			// Get column width.
			PMReal colwidth = 
				parameterUtils->GetPMReal(PMString("Width of columns to insert"), 10.0, 5.0, 40.0);
			if (parameterUtils->WasDialogCancelled())
			{
				break;
			}
			status = instance.InsertColumns(tableSuite, numcols, pos, colwidth);
		}

		else if (choice == 2)	// delete rows
		{
			status = instance.DeleteRows(tableSuite);
		}

		else if (choice == 3)	// delete columns
		{
			status = instance.DeleteColumns(tableSuite);
		}

		else if (choice == 4)	// merge cells
		{
			status = instance.MergeCells(tableSuite);
		}

		else if (choice == 5)	// unmerge cells
		{
			status = instance.UnmergeCell(tableSuite);
		}

		else
		{
			ASSERT("INVALID OPTION");
		}

	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerModifyTable instance_SnpRunnerModifyTable;
DEFINE_SNIPPET(_SnpRunnerModifyTable) 	

// End, SnpModifyTable.cpp

