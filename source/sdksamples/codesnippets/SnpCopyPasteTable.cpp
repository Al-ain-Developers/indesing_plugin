//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCopyPasteTable.cpp $
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
#include "IActiveContext.h"
#include "IControlView.h"
#include "ITableSuite.h"
#include "ITableTarget.h"
#include "ITableModel.h"
#include "ILayoutControlData.h"
#include "ITableCopyPasteCmdData.h"
#include "ITextTarget.h"
#include "IHierarchy.h"
#include "ITool.h"
#include "IGraphicFrameData.h"
#include "ISelectionManager.h"
#include "IToolBoxUtils.h"
#include "ITextSelectionSuite.h"

// General includes:
#include "Utils.h"
#include "TextEditorID.h"	// kIBeamToolBoss
#include "RangeData.h"	// kIBeamToolBoss

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpCreateTable.h"
#include "SDKLayoutHelper.h"

// TODO align with coding conventions
#define ASSERT_BREAK_IF_NIL(p) { ASSERT(p); if (p == nil) { break; } }

/** 
	\li	Copy paste a table content into another table
	\li	How to create a new text frame and activate the corresponding tool

	Illustrates use of command that allows a table to be copied and pasted.
	
	Precondition: There is one table selected.  The snippet will create a table in a new text frame with proper 
	text focus and tool selected, then copy the selected table contents and paste into the new table.

  	@ingroup sdk_snippet
  	@ingroup sdk_table
  	@ingroup sdk_layout
	
	@see kTableCopyPasteCmdBoss
	@see ITool
	@see ILayoutControlData
	@see IGraphicFrameData
	@see SDKLayoutHelper
 */
class SnpCopyPasteTable
{
	public:
		/** Constructor.
		 */
		SnpCopyPasteTable() {}

		/** Destructor.
		 */
		virtual			~SnpCopyPasteTable() {}

		/** Shows how to copy a table to another table, by using CopyPasteTableCmd.

			@param fromTable The source table model to copy from.
			@param toTable The destination table model to copy to.
			@param pasteAt The target grid address to copy to.
			@param whatState EWhatState enum that specifies what to copy. 
					See \Ref{ITableModel::EWhatState} for details.
			@return @return kSuccess on success, kFailure otherwise. 
		*/
		ErrorCode DoCopyPaste(const ITableModel* fromTable, 
						  ITableModel* toTable, 
						  const GridAddress& pasteAt,
						  ITableModel::EWhatState whatState = ITableModel::eAll) const;

	
};

/*
*/
ErrorCode SnpCopyPasteTable::DoCopyPaste(const ITableModel* fromTable, 
										  ITableModel* toTable, 
										  const GridAddress& pasteAt, 
										  ITableModel::EWhatState whatState) const
{
	ErrorCode result = kFailure;
	do 
	{
		InterfacePtr<ICommand> CopyPasteTableCmd(CmdUtils::CreateCommand(kTableCopyPasteCmdBoss));
		ASSERT_BREAK_IF_NIL(CopyPasteTableCmd);
		
		InterfacePtr<ITableCopyPasteCmdData> cmdData(CopyPasteTableCmd, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(cmdData);
		
		// Set a default if the grid address is bad
		GridAddress pasteDestination = 
			(pasteAt == kBadGridAddress) ? GridAddress(0,0) : pasteAt;

		cmdData->Set(::GetUIDRef(fromTable), fromTable->GetTotalArea(), ::GetUIDRef(toTable), pasteDestination, whatState);
		
		result = CmdUtils::ProcessCommand(CopyPasteTableCmd);
		ASSERT(result == kSuccess);

	} while (kFalse);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpCopyPasteTable available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerCopyPasteTable : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerCopyPasteTable();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCopyPasteTable();

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
/* Constructor.
*/
_SnpRunnerCopyPasteTable::_SnpRunnerCopyPasteTable() : SnpRunnable("CopyPasteTable")
{
	// Describe what your snippet does.
	this->SetDescription("Copy/pastes the current table contents to a newly created one");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("A document with a text cursor in a table cell");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerCopyPasteTable::~_SnpRunnerCopyPasteTable()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerCopyPasteTable::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableTarget> 
			tableTarget(runnableContext, UseDefaultIID());
		if (tableTarget != nil)
		{
			InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
			if (tableModel)
				result = kTrue;
		}
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil)
			result = kFalse;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerCopyPasteTable::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do 
	{
		// TODO this is a lot of code, can we refactor into above snippet or another snippet
		SnpCopyPasteTable instance;
		// First, get the currently selected table. 
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(tableTarget);
		InterfacePtr<ITableModel> fromTable(tableTarget->QueryModel());
		ASSERT_BREAK_IF_NIL(fromTable);

		// Create a new text frame

		// ILayoutControlData is required to determine the active spread layer and the current page.
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		ASSERT_BREAK_IF_NIL(layoutControlData);
		UIDRef frameUIDRef = UIDRef::gNull;

		// Parent the frame on the active spread layer.
		InterfacePtr<IHierarchy> activeSpreadLayerHierarchy(layoutControlData->QueryActiveLayer());
		ASSERT_BREAK_IF_NIL(activeSpreadLayerHierarchy);
		UIDRef parentUIDRef = ::GetUIDRef(activeSpreadLayerHierarchy);

		// Transform the bounds of the frame from page co-ordinates
		// into the parent co-ordinates, i.e. the spread.
		ASSERT(layoutControlData->GetPage() != kInvalidUID);
		if (layoutControlData->GetPage() == kInvalidUID) {
			break;
		}
		UIDRef pageUIDRef(parentUIDRef.GetDataBase(), layoutControlData->GetPage());
		SDKLayoutHelper layoutHelper;
		PMRect boundsInParentCoords = layoutHelper.PageToSpread(pageUIDRef, PMRect(10, 10, 500, 500));
		// Create the frame.
		frameUIDRef = layoutHelper.CreateTextFrame(parentUIDRef, boundsInParentCoords, 1, kFalse);
		// put the blicking cursor into the newly created text frame, code copied from SnpCreateFrame::SelectFrame
		ISelectionManager*	selectionManager = runnableContext->GetActiveContext()->GetContextSelection();
		ASSERT_BREAK_IF_NIL(selectionManager);
		// Deselect everything.
		selectionManager->DeselectAll(nil); // deselect every active CSB

		InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
		if (!activeTool->IsTextTool()) {
			InterfacePtr<ITool> iBeamTool(Utils<IToolBoxUtils>()->QueryTool(kIBeamToolBoss));
			ASSERT_BREAK_IF_NIL(iBeamTool);
			status = Utils<IToolBoxUtils>()->SetActiveTool(iBeamTool);
		}

		// Find the story associated with the frame.
		InterfacePtr<IGraphicFrameData> graphicFrameData(frameUIDRef, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(graphicFrameData);
		UIDRef storyUIDRef = layoutHelper.GetTextModelRef(graphicFrameData);

		// Make a text selection to set the text caret blinking at the start of the story.
		InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(textSelectionSuite);
		status = textSelectionSuite->SetTextSelection(storyUIDRef, 
			RangeData(0, RangeData::kLeanForward),
			Selection::kScrollIntoView, 
			nil); // scrollTo


		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(textTarget);

		// Make a new table with the same rows & cols as the fromTable
		SnpCreateTable	instanceSnpCreateTable;
		status = instanceSnpCreateTable.CreateTable(textTarget->GetTextModel(),
											textTarget->GetRange().Start(nil),
											fromTable->GetTotalRows().count,
											fromTable->GetTotalCols().count); 
		

											
		// Get the table model of the newly created table
		InterfacePtr<ITableTarget> newTableTarget(runnableContext, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(newTableTarget);
		InterfacePtr<ITableModel> toTable(newTableTarget->QueryModel());
		ASSERT_BREAK_IF_NIL(toTable);

		// Copy/Paste the fromTable to toTable at the top left
		
		instance.DoCopyPaste(fromTable, toTable, GridAddress(0,0));
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerCopyPasteTable instance_SnpRunnerCopyPasteTable;
DEFINE_SNIPPET(_SnpRunnerCopyPasteTable) 	
// End, SnpCopyPasteTable.cpp

