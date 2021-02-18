//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpAccessTableContent.cpp $
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
#include "ITableModel.h"
#include "ITableTextContainer.h"
#include "ITextModel.h"
#include "ITextStoryThread.h"
#include "ITextStoryThreadDict.h"
#include "textiterator.h"
#include "WideString.h"
#include "ITableTarget.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Shows how to iterate an entire table to get all the text.

  	@ingroup sdk_snippet
  	@ingroup sdk_table
	
 */
class SnpAccessTableContent 
{
	public:
		/** Constructor.
		 */
		SnpAccessTableContent() {}

		/** Destructor.
		 */
		virtual			~SnpAccessTableContent() {}


		/**
			Shows how to get text as WideString from all cells in a table.
			@param tableModel Interface pointer to the table model
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode IterTable(InterfacePtr<ITableModel>& tableModel);


		/** Shows how to extract text from a cell at a particular GridAddress in a table.
			From the table model, you get the text model via ITableTextContainer interface.
			@param tableModel Interface pointer to the table model.
			@param gridAddress GridAddress of the cell of choice.
			@return WideString The text at the GridAddress as a WideString.
		*/
		WideString GetTextFromCell(const InterfacePtr<ITableModel>& tableModel, 
								   const GridAddress& gridAddress);

	
};


/*
*/
ErrorCode SnpAccessTableContent::IterTable(InterfacePtr<ITableModel>& tableModel)	
{
	ErrorCode status = kFailure;
	do
	{	
		ITableModel::const_iterator iterTable(tableModel->begin());
		ITableModel::const_iterator end(tableModel->end());

		while(iterTable != end) 
		{
			GridAddress gridAddress = *iterTable;			
			WideString wstr = this->GetTextFromCell(tableModel, gridAddress);
			PMString sysString;
			wstr.GetSystemString(&sysString);
			
			SNIPLOG("(r=%d,c=%d): Text: %s", 
					gridAddress.row, gridAddress.col, sysString.GetPlatformString().c_str());

			// goto to the next grid address
			++iterTable;
		}
		status = kSuccess;

	} while (false);
	return status;
} // SnpAccessTableContent

/*
*/
WideString SnpAccessTableContent::GetTextFromCell(const InterfacePtr<ITableModel>& tableModel,
												   const GridAddress& gridAddress)
{
	WideString retval;	
	do {
		// Make sure we have a valid table model
		ASSERT(tableModel);
		if(tableModel == nil) 
		{
			break;
		}

		// convert the grid address to a grid ID
		const GridID gridID = tableModel->GetGridID(gridAddress);

		// get the table text container so we could get to the text model.
		InterfacePtr<ITableTextContainer> tableTextContainer(tableModel, UseDefaultIID());
		ASSERT(tableTextContainer);
		if(tableTextContainer == nil) 
		{
			break;
		}
        
		InterfacePtr<ITextModel> textModel(tableTextContainer->QueryTextModel());
		ASSERT(textModel);
		if(textModel == nil) 
		{
			break;
		}
		
		InterfacePtr<ITextStoryThreadDict> textStoryThreadDict(tableModel, UseDefaultIID());
		ASSERT(textStoryThreadDict);
		if (textStoryThreadDict == nil) 
		{
			break;
		}
		InterfacePtr<ITextStoryThread> textStoryThread(textStoryThreadDict->QueryThread(gridID));
		ASSERT(textStoryThread);
		if (textStoryThread == nil)
		{
			break;
		}
		TextIndex threadStart;
		int32 threadLength;
        threadStart = textStoryThread->GetTextStart(&threadLength);
		
		// use STL-style iterators to get text from text model (using TextIterator)
		TextIterator beginTextChunk(textModel, threadStart);
		TextIterator endTextChunk(textModel, threadStart + threadLength);
		
		// retval.reserve(threadLength);
		// Watson #1140943 
		// reserve no longer functional now strings do copy-on-write
		std::copy(beginTextChunk, endTextChunk, std::back_inserter(retval));

	} while(kFalse);
	return retval;
}
	

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpAccessTableContentavailable to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerAccessTableContent : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerAccessTableContent();

		/** Destructor.
		 */
		virtual			~_SnpRunnerAccessTableContent();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		virtual bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		virtual ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}
};
/* Constructor.
*/
_SnpRunnerAccessTableContent::_SnpRunnerAccessTableContent() : SnpRunnable("AccessTableContent")
{
	// Describe what your snippet does.
	this->SetDescription("Accesses table cell text contents and displays them to the log");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("A table with some text content");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerAccessTableContent::~_SnpRunnerAccessTableContent()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerAccessTableContent::CanRun(ISnpRunnableContext* runnableContext)
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
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerAccessTableContent::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do 
	{
		// First, get the currently selected table. 
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		ASSERT(tableTarget);
		if(tableTarget == nil) 
		{
			break;
		}
		InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
		ASSERT(tableModel);	// If it asserts have you a table in selection?
		if(tableModel == nil) 
		{
			break;
		}
		SnpAccessTableContent instance;
		status = instance.IterTable(tableModel);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerAccessTableContent instance_SnpRunnerAccessTableContent;
DEFINE_SNIPPET(_SnpRunnerAccessTableContent)
// End, SnpAccessTableContent.cpp

