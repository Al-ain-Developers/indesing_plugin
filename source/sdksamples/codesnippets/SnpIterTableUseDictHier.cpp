//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpIterTableUseDictHier.cpp $
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
#include "IDocument.h"
#include "ILayoutUtils.h"
#include "IStoryList.h"
#include "ITableModel.h"
#include "ITableTextContainer.h"
#include "ITextModel.h"
#include "ITextStoryThread.h"
#include "ITextStoryThreadDict.h"
#include "ITextStoryThreadDictHier.h"
#include "textiterator.h"
#include "ITableTarget.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Illustrates recommented method to iterate through tables in document.

  	@ingroup sdk_snippet
  	@ingroup sdk_table

 */
class SnpIterTableUseDictHier 
{
public:
	/** Constructor.
	*/
	SnpIterTableUseDictHier() {}

	/** Destructor.
		*/
	virtual			~SnpIterTableUseDictHier() {}
	/**	Iterates tables in document.	
		@param document The document of interest.
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode IterateAllTablesInDocument(IDocument* document);

	/** Iterate though all tables in a story, via ITextStoryDictHier on kTextStoryBoss.
		Compare with SnipTableIterStories::IterateAllTablesInStory(). 
		
		@param story UIDRef of the story to inspect.
	*/
	void IterateAllTablesInStory(UIDRef& story);

	
private:

	void inspectThreadDict(const InterfacePtr<ITextStoryThreadDict>& textStoryThreadDict);
};

/* NOTE: This is the same as SnipTableIterStories::IterateAllTablesInDocument().
*/
ErrorCode SnpIterTableUseDictHier::IterateAllTablesInDocument(IDocument* document)
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

		// Iterate through all stories on the document. There are
		// other stories which aren't user-accessible (e.g. created by XML plug-in)
		// but we'll ignore these.
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

/* 	Iterate though all tables in a story, via ITextStoryDictHier on kTextStoryBoss.
	Compare with SnipTableIterStories::IterateAllTablesInStory().
*/
void SnpIterTableUseDictHier::IterateAllTablesInStory(UIDRef& story)
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

		SNIPLOG("Story has %d chars in primary story", textModel->GetPrimaryStoryThreadSpan());
		
		// Get the text story dictionary hierarchy to enable traversing the story threads.
		// We will be using the ITextStoryThreadDictHier::NextUID() method below. 
		InterfacePtr<ITextStoryThreadDictHier> textStoryDictHier(textModel, UseDefaultIID());
		ASSERT(textStoryDictHier);
		if(textStoryDictHier == nil) 
		{
			break;
		}

		// KEY POINT: The interface ITextStoryThreadDictHier is aggregated on kTextStoryBoss.
		// Its implementation maintains a collection of ITextStoryThreadDict's, which
		// map one-to-one with tables.
		UIDRef storyUIDRef(::GetUIDRef(textStoryDictHier));

		// kTextStoryBoss aggregates both an ITextStoryThread and
		// ITextStoryThreadDictHier, along with ITextStoryThreadDict.
		
		// kTableModelBoss, on the other hand, has an ITextStoryThreadDict and ITextStoryThread
		// but not an ITextStoryThreadDictHier, as it contains only one dictionary of threads.
		UID nextUID = storyUIDRef.GetUID();
		
		// So we can start the iteration through the threads by kicking off with what is the UID
		// of the primary story thread.
		do 
		{
			if(nextUID != kInvalidUID)
			{
				InterfacePtr<ITextStoryThreadDict> textStoryThreadDict(::GetDataBase(textStoryDictHier), 
																	   nextUID, UseDefaultIID());
				ASSERT(textStoryThreadDict);
				if(textStoryThreadDict == nil) 
				{
					break;
				}

				// Given the story thread dictionary, we can find the threads associated with
				// the text model
				Text::StoryRange threadRange = textStoryThreadDict->GetThreadBlockTextRange();
				bool16 wasAnchored;
				Text::StoryRange anchorRange = textStoryThreadDict->GetAnchorTextRange(&wasAnchored);
				SNIPLOG("Was anchored = %d", wasAnchored);
				SNIPLOG("threadRange = (%d, %d)", threadRange.Start(nil), threadRange.End());
				SNIPLOG("anchorRange = (%d, %d)", anchorRange.Start(nil), anchorRange.End());
				
				// Now look at an individual dictionary of threads. 
				// ITextStoryThreadDict maps to a table's text contents, as 
				// it lives on kTableModelBoss. It's also aggregated on kTextStoryBoss
				// but we'll skip that case below.
				inspectThreadDict(textStoryThreadDict);
			}

			// Get the next text story thread dictionary in the collection
			nextUID = textStoryDictHier->NextUID(nextUID);	

		} while (nextUID != kInvalidUID); // Continue until no more text story dictionary hierarchy's

	} while(kFalse);

} // SnpIterTableUseDictHier


/*
*/
void SnpIterTableUseDictHier::inspectThreadDict(const InterfacePtr<ITextStoryThreadDict>& textStoryThreadDict)
{
	do 
	{
		// Make sure we have a valid text story thread dictionary.
		ASSERT(textStoryThreadDict);
		if(textStoryThreadDict == nil) 
		{
			break;
		}

		// Is this a dictionary on a table?
		InterfacePtr<ITableModel> tableModel(textStoryThreadDict, UseDefaultIID());
		if (tableModel == nil) 
		{
			SNIPLOG("textStoryThreadDict but not on a table");
			break;
		} 
		else 
		{
			SNIPLOG("textStoryThreadDict found on kTableModelBoss: it has an ITableModel");
	   		
			// Get the connection to the text model in which this table is embedded
			InterfacePtr<ITableTextContainer> tableTextContainer(textStoryThreadDict, UseDefaultIID());
			ASSERT(tableTextContainer);
			if (tableTextContainer == nil) 
			{
				break;
			}
			// This QueryTextModel allows navigation from the table back to the embedding text model
			InterfacePtr<ITextModel> textModel(tableTextContainer->QueryTextModel());
			ASSERT(textModel);
			if (textModel == nil) 
			{
				break;
			}

			// get text in all cells. 
			// ------ code borrowed from SnipTableContentAccess.cpp - Start here ------
			ITableModel::const_iterator iterTable(tableModel->begin());
			ITableModel::const_iterator end(tableModel->end());
			
			while(iterTable != end) 
			{
				GridAddress gridAddress = *iterTable;
				
				// convert the grid address to a grid ID
				const GridID gridID = tableModel->GetGridID(gridAddress);
				InterfacePtr<ITextStoryThread> textStoryThread(textStoryThreadDict->QueryThread(gridID));
				
				// get the text at grid address as a widestring
				// get the range of the text in the story thread
				TextIndex threadStart;
				int32 threadLength = -1;
				threadStart = textStoryThread->GetTextStart(&threadLength);
				
				// use STL-style iterators to get text from text model (using TextIterator)
				WideString wstr;
				TextIterator beginTextChunk(textModel, threadStart);
				TextIterator endTextChunk(textModel, threadStart + threadLength);
				// wstr.reserve(threadLength);
				// Watson #1140943 
				// reserve no longer functional now strings do copy-on-write
				std::copy(beginTextChunk, endTextChunk, std::back_inserter(wstr));

				PMString sysString;
				wstr.GetSystemString(&sysString);
				
				SNIPLOG("(r=%d,c=%d): Text: %s", 
						gridAddress.row, gridAddress.col, sysString.GetPlatformString().c_str());
	
				// goto to the next grid address
				++iterTable;
			}
			// ------ code borrowed from SnipTableContentAccess.cpp - End here ------
		}

	} while(kFalse);
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpIterTableUseDictHier available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerIterTableUseDictHier : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerIterTableUseDictHier();

		/** Destructor.
		 */
		virtual			~_SnpRunnerIterTableUseDictHier();

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
_SnpRunnerIterTableUseDictHier::_SnpRunnerIterTableUseDictHier() : SnpRunnable("IterTableUseDictHier")
{
	// Describe what your snippet does.
	this->SetDescription("Iterates tables in a document using IStoryThreadDictHier");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("Document with 1 or more tables in 1 or more text frames");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerIterTableUseDictHier::~_SnpRunnerIterTableUseDictHier()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerIterTableUseDictHier::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerIterTableUseDictHier::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpIterTableUseDictHier instance;
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();

		status = instance.IterateAllTablesInDocument(document);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerIterTableUseDictHier instance_SnpRunnerIterTableUseDictHier;
DEFINE_SNIPPET(_SnpRunnerIterTableUseDictHier) 	

// End, SnpIterTableUseDictHier.cpp

