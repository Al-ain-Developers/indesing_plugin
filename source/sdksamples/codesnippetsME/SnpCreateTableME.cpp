//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippetsME/SnpCreateTableME.cpp $
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
//  
//  Usage rights licenced to Adobe Inc. 1997 - 2010.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ICellContent.h"
#include "ICommand.h"
#include "ISelectUtils.h"
#include "ITableModel.h"
#include "ITableModelList.h"
#include "ITextModel.h"
#include "ITextStoryThread.h"
#include "ITextTarget.h"
#include "ITableUtils.h"

// General includes:
#include "Utils.h"
#include "CmdUtils.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

class SnpCreateTableME : public SnpRunnable
{
	public:
		/**
			Method that attempts to create a table
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode CreateTableME(const UIDRef& storyRef, 
							  const TextIndex at, 
							  const int32 numRows = 2, 
							  const int32 numCols = 3,
							  const PMReal rowHeight = 60.0,
							  const PMReal colWidth = 100.0,
							  const CellType cellType = kTextContentType, const Tables::EDirection dir = Tables::eRTL);


	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		SnpCreateTableME();

		/** Destructor.
		 */
		virtual			~SnpCreateTableME();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}

};


ErrorCode SnpCreateTableME::CreateTableME(const UIDRef& storyRef, 
										  const TextIndex at,
										  const int32 numRows, 
										  const int32 numCols,
										  const PMReal rowHeight,
                                          const PMReal colWidth, 
										  const CellType cellType,
										  const Tables::EDirection dir)
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
									 numRows, numCols, 0, 0,
									 rowHeight, colWidth, 
									 cellType,
									 ITableUtils::eSetSelectionInFirstCell , kInvalidUID, dir);
		status = kSuccess;

	} while (false);

	return status;

} // SnipCreateTableME


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor.
*/
SnpCreateTableME::SnpCreateTableME() : SnpRunnable("CreateTableME")
{
	// Describe what your snippet does.
	this->SetDescription("Creates a text R2L table in currently selected text frame");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("Text selection in an existing text frame");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
SnpCreateTableME::~SnpCreateTableME()
{
}

/* Check if your preconditions are met.
*/
bool16	SnpCreateTableME::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {

		// check if this is running on the R2L feature set
	    if ((LocaleSetting::GetLocale().GetLanguageFS() != kRightToLeftLanguageFS))
			break;
	
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode SnpCreateTableME::Run(ISnpRunnableContext* runnableContext)
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
		
		// Get Table Direction.
		K2Vector<PMString> tableDir_choices;
		tableDir_choices.push_back(PMString("eLTR"));
		tableDir_choices.push_back(PMString("eRTL"));
		Tables::EDirection direction = (Tables::EDirection)(parameterUtils->GetChoice(PMString("Direction"), tableDir_choices, Tables::eRTL));
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

		status = this->CreateTableME(textTarget->GetTextModel(), textTarget->GetRange().Start(nil), rows, cols, rowHeight, colWidth, kTextContentType, direction);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
SnpCreateTableME instanceSnpCreateTableME;

// End, SnpCreateTable.cpp

