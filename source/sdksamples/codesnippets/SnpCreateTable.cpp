//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateTable.cpp $
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
#include "ITextModel.h"
#include "ITableModel.h"
#include "ITextTarget.h"
#include "IItemLockData.h"
#include "ITableUtils.h"
#include "IGalleyUtils.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpCreateTable.h"

/*
*/
bool16  SnpCreateTable::CanCreateTable(const UIDRef& storyRef, const TextIndex at)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITextModel> textModel(storyRef, UseDefaultIID());
		if (!textModel) {
			break;
		}

		// Is the story insert locked?
		InterfacePtr<IItemLockData> textLock(storyRef, UseDefaultIID());
		if (textLock && textLock->GetInsertLock() == kTrue) {
			break;
		}

		// We need ITableUtils in order to insert a table.
		Utils<ITableUtils> tableUtils;
		if (!tableUtils) {
			break;
		}

		// Can than target story thread accept tables?
		if (tableUtils->CanInsertTableAt(textModel, at) == kFalse) {
			break;
		}

		// Under InCopy we only want to insert tables under layout view.
		Utils<IGalleyUtils> galleyUtils;
		if (galleyUtils && galleyUtils->InLayout() == kFalse) {
			break;
		}

		// If we get this far we can insert a table.
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpCreateTable::CreateTable(const UIDRef& storyRef, 
										const TextIndex at,
										  const int32 numRows, 
										  const int32 numCols,
										  const PMReal rowHeight,
                                          const PMReal colWidth, 
										  const CellType cellType)
{
	ErrorCode status = kFailure;
	do {

		InterfacePtr<ITextModel> textModel(storyRef, UseDefaultIID());
		ASSERT(textModel);
		if(textModel == nil) {
			break;
		}
		
		// 1026750: Instead of processing kNewTableCmdBoss use the ITableUtils facade.
		Utils<ITableUtils> tableUtils;
		if (!tableUtils) {
			break;
		}
		tableUtils->InsertTable (textModel, at, 0, 
									 numRows, numCols, 
									 rowHeight, colWidth, 
									 cellType,
									 ITableUtils::eSetSelectionInFirstCell);
		status = kSuccess;

	} while (false);

	return status;

} // SnipCreateTable



// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpCreateTable available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
 */
class _SnpRunnerCreateTable : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerCreateTable();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCreateTable();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextTargetContext;}
};
/* Constructor.
*/
_SnpRunnerCreateTable::_SnpRunnerCreateTable() : SnpRunnable("CreateTable")
{
	// Describe what your snippet does.
	this->SetDescription("Creates a text table in currently selected text frame");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("A text selection in an existing text frame");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerCreateTable::~_SnpRunnerCreateTable()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerCreateTable::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		SnpCreateTable	instance;
		result = instance.CanCreateTable(textTarget->GetTextModel(), textTarget->GetRange().Start(nil));
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerCreateTable::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// Use runnableContext to discover the selection target or IActiveContext.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;
		Utils<ISnipRunParameterUtils> parameterUtils;
		// Get rows.
		int32 rows = parameterUtils->GetInt32(PMString("Number of Rows"), 2, 1, 999);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		// Get cols.
		int32 cols = parameterUtils->GetInt32(PMString("Number of Columns"), 3, 1, 999);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		// Get row height.
		PMReal rowHeight = parameterUtils->GetPMReal(PMString("Row Height in Points"), 60.0, 1.0, 640.0);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		// Get col width.
		PMReal colWidth = parameterUtils->GetPMReal(PMString("Column Width in Points"), 100.0, 1.0, 480.0);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}

		SnpCreateTable	instance;
		status = instance.CreateTable(textTarget->GetTextModel(), textTarget->GetRange().Start(nil), rows, cols, rowHeight, colWidth);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerCreateTable instance_SnpRunnerCreateTable;
DEFINE_SNIPPET(_SnpRunnerCreateTable) 	
// End, SnpCreateTable.cpp

