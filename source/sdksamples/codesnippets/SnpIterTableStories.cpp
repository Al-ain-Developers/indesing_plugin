//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpIterTableStories.cpp $
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
#include "ITableModelList.h"
#include "IStoryList.h"
#include "ILayoutUtils.h"
#include "IDocument.h"
#include "ITextModel.h"
#include "textiterator.h"
#include "ITableTarget.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Iterate tables in document using deprecated method; recommended method shown in  SnpIterTableUseDictHier.

	Deprecated mechanism to iterate through tables in a document.
	Ideally use the method illustrated in SnpIterTableUseDictHier rather
	than the method involving ITableModelList shown here.

  	@ingroup sdk_snippet
  	@ingroup sdk_table

  	@see ITableModelList
 */
class SnpIterTableStories 
{
public:
	/** Constructor.
		*/
	SnpIterTableStories() : fTextModel(nil) {}

	/** Destructor.
		*/
	virtual			~SnpIterTableStories() {}

	/**	Shows how to get all tables in a document by iterating through the story list.
		This uses the ITableModelList. See SnpIterTableUseDictHier::IterateAllTablesInDocument()
		for a better technique.  Also see Tables technotes for more information regarding these
		2 techniques.
		
		@param document The document of interest.
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode IterateAllTablesInDocument(IDocument* document);

	/** Iterate though all tables in a story, by iterating through 
		ITableModelList on kTextStoryBoss.
		Compare with SnpIterTableUseDictHier::IterateAllTablesInStory(). 
		
		@param story UIDRef of the story to inspect.
	*/
	void IterateAllTablesInStory(UIDRef& story);


private:
	void inspect(const InterfacePtr<ITableModel>& tableModel);

	ITextModel* fTextModel;
};


/* NOTE: This is the same as SnipTableUseDictHier::IterateAllTablesInDocument().
*/
ErrorCode SnpIterTableStories::IterateAllTablesInDocument(IDocument* document)
{
	ErrorCode status = kFailure;

	do 
	{
		// Make sure we have a valid document
		ASSERT(document);
		if(document == nil) 
		{
			break;
		}
		InterfacePtr<IStoryList> storyList(document, UseDefaultIID());
		ASSERT(storyList);
		if(storyList == nil) 
		{
			break;
		}

		int32 numStories = storyList->GetUserAccessibleStoryCount();
		for (int32 n = 0; n < numStories; n++ )
		{
			UIDRef story = storyList->GetNthUserAccessibleStoryUID(n);
			SNIPLOG("Story %d", n);
			this->IterateAllTablesInStory(story);
			status = kSuccess;
		}
		
	} while(kFalse);
	return status;
}

/*	Iterate though all tables in a story, by iterating through 
	ITableModelList on kTextStoryBoss.
	Compare with SnipTableUseDictHier::IterateAllTablesInStory().
*/
void SnpIterTableStories::IterateAllTablesInStory(UIDRef& story)
{
	do 
	{
		// Make sure we have a valid story UIDRef
		ASSERT(story != UIDRef(nil, kInvalidUID));
		if (story == UIDRef(nil, kInvalidUID)) 
		{
			SNIPLOG("Invalid story UIDRef!!!");
			break;
		}
		
	    InterfacePtr<ITextModel> textModel(story, UseDefaultIID());
		ASSERT(textModel);
		if (textModel == nil) 
		{
			break;
		}
		fTextModel = textModel;
		
		// Get the table model list on kTextStoryBoss.
		// NOTE: This is an older way of getting a table model.
		// 		See SnipTableUseDictHier.cpp for a more 'modern' way of getting the
		// 		table models.
		InterfacePtr<ITableModelList> tableModelList(story, UseDefaultIID());
		ASSERT(tableModelList);
		if(tableModelList == nil) 
		{
			break;
		}
		
		SNIPLOG("Table model list has %d tables", tableModelList->GetModelCount());
		for(int32 i = 0; i < tableModelList->GetModelCount(); i++) 
		{
			InterfacePtr<ITableModel> tableModel(tableModelList->QueryNthModel(i));
			ASSERT(tableModel);
			if(tableModel == nil)
			{ 
				continue;
			}

			inspect(tableModel);
        }


	} while (kFalse);
}

/* 
*/
void SnpIterTableStories::inspect(const InterfacePtr<ITableModel>& tableModel)
{
	do 
	{
		// Make sure the table model is valid.
		ASSERT(tableModel);
		if(tableModel == nil) 
		{
			break;
		}

		SNIPLOG("Table model has %d rows, %d columns", 
				tableModel->GetTotalRows().count, 
				tableModel->GetTotalCols().count);

		const UIDRef tableRef(::GetUIDRef(tableModel));

		// get text in all cells. 
		
		ITableModel::const_iterator iterTable(tableModel->begin());
		ITableModel::const_iterator end(tableModel->end());
		
		while(iterTable != end) 
		{
			TextIndex	 threadStart;
			int32		 threadLength;
			GridAddress gridAddress = *iterTable;

			const GridID gridID = tableModel->GetGridID(*iterTable);
			ASSERT(fTextModel);
			if(fTextModel == nil) 
			{
				break;
			}
			// This relies on the knowledge that the gridID is 
			// the key (unique only within a table) used to identify threads
			// within the thread dictionary for an individual table
			if(!fTextModel->FindStoryThread(tableRef.GetUID(), gridID, &threadStart, &threadLength)) 
			{
				break;
			}
			// RunToString debug only method in textiterator.h	
			TextIterator beginTextChunk(fTextModel, threadStart);
			TextIterator endTextChunk(fTextModel, threadStart + threadLength);
			std::auto_ptr<WideString> threadText(new WideString);
			//threadText->reserve(threadLength);
			// Watson #1140943 
			// reserve no longer functional now strings do copy-on-write
			std::copy(beginTextChunk, endTextChunk, std::back_inserter(*threadText));
			PMString sysString;
			threadText->GetSystemString(&sysString);
			
			SNIPLOG("(r=%d,c=%d): Text: %s", 
						gridAddress.row, gridAddress.col, sysString.GetPlatformString().c_str());
			
			++iterTable;
		}
	} while(kFalse);
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpIterTableStories available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerIterTableStories : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerIterTableStories();

		/** Destructor.
		 */
		virtual			~_SnpRunnerIterTableStories();

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
_SnpRunnerIterTableStories::_SnpRunnerIterTableStories() : SnpRunnable("IterTableStories") 
{
	// Describe what your snippet does.
	this->SetDescription("Iterates tables in a document using ITableModelList");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("At least 1 selected table in document");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerIterTableStories::~_SnpRunnerIterTableStories()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerIterTableStories::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerIterTableStories::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpIterTableStories instance;
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		
		status = instance.IterateAllTablesInDocument(document);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerIterTableStories instance_SnpRunnerIterTableStories;
DEFINE_SNIPPET(_SnpRunnerIterTableStories) 	

// End, SnpIterTableStories.cpp

