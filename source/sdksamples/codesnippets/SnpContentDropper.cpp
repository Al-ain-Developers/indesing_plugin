//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpContentDropper.cpp $
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "Utils.h"
#include "IContentDropperFacade.h"
#include "IContentDropperAppData.h"
#include "IContentDropperDocData.h"
#include "ContentDropperTypes.h"
#include "IWorkspace.h"
#include "ILayoutTarget.h"
#include "IApplication.h"
#include "IDocumentList.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/**	How to work with the ContentDropper APIs.

	@ingroup sdk_snippet

	@see IContentDropperFacade
	@see IContentDropperAppData
	@see IContentDropperDocData
	@see CCollection
*/
class SnpContentDropper
{
public:
	/** @brief Inspects the contents of the content dropper.

		@details Iterates over the collections on the content dropper, tracing information about
		the collections and their contents to the SnippetRunner log. Additionally reports
		information about the current item at the head of the content dropper.

		@retval kSuccess on success
		@retval kFailure otherwise
	*/
	ErrorCode Inspect();

	/** @brief Loads the selected items onto the content dropper's conveyor.

		@param[in] items The items to load onto the conveyor
		@return ErrorCode returned when loading the conveyor.
	*/
	ErrorCode LoadSelectionIntoDropper(const UIDList& items);

	/** @brief Expand or collapse the collection at the head of the conveyor.

		@param expand kTrue to expand the head item, kFalse to collapse it.
		@retval kSuccess if successful.
		@retval kFailure if the head of the conveyor cannot be expanded.
	*/
	ErrorCode ExpandOrCollapseHead(const bool16 expand);

	/** @brief Examine the collections on the conveyor from each open document.

		@details For each open document, inspect the collections added to the document
		by the given document.
		@retval kSuccess
	*/
	ErrorCode InspectDocumentContributions();

	/** @brief Rotate the items on the content dropper

		@param byHowMany How many items do you want to rotate by?
		@param isForward kTrue to rotate forwards, kFalse otherwise
		@retval kSuccess if rotation is successful
		@retval kFailure otherwise
	*/
	ErrorCode RotateContentDropper(const int32 byHowMany, const bool16 isForward);

private:
	/** @brief Provide a string description of a link policy

		@param linkPolicy The link policy value to describe
		@return String label of the link policy
	*/
	std::string LinkPolicyAsString(const ContentDropperTypes::LinkPolicy linkPolicy);

	/** @brief Recursively trace information about a collection (and sub-collections)
			to the SNIPLOG

		@param collection The collection to inspect
		@param tracePrefix A spacer to include at the start of each line of output.
			Used to indent output about nested collections.
	*/
	void InspectCollection(const CCollection& collection, std::string tracePrefix);
};

ErrorCode SnpContentDropper::Inspect()
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IWorkspace> iWorkSpace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(iWorkSpace);
		if (iWorkSpace == nil)
			break;

		InterfacePtr<IContentDropperAppData> iContentDropperAppData(iWorkSpace, UseDefaultIID());
		ASSERT(iContentDropperAppData);
		if (iContentDropperAppData == nil)
			break;

		int32 numItems = iContentDropperAppData->Size();
		SNIPLOG("Content dropper contains %d items", numItems);

		// Many of the following calls only make sense if there is at least one item in the dropper,
		// and we'll get asserts if we call them with 0 items.
		if (numItems > 0)
		{
			int32 currentItem = 1;
			for (IContentDropperAppData::iterator iter = iContentDropperAppData->begin(); iter != iContentDropperAppData->end(); ++iter, ++currentItem)
			{
				CCollection* collection = *iter;
				SNIPLOG("  - Current item: %d", currentItem);
				InspectCollection(*collection, "    ");
			}

			SNIPLOG("Head %s expanded", iContentDropperAppData->IsHeadExpanded() ? "is" : "isn't");
			SNIPLOG("Head %s expandable", iContentDropperAppData->CanExpandHead() ? "is" : "isn't");
			SNIPLOG("Head %s collapsable", iContentDropperAppData->CanCollapseHead() ? "is" : "isn't");

			SNIPLOG("There are %d items in level", iContentDropperAppData->GetNumOfItemsInLevel());
			SNIPLOG("Currently selected: %s", iContentDropperAppData->GetDescriptionString().GetPlatformString().c_str());
		}

		status = kSuccess;
	}
	while(kFalse);

	return status;
}

ErrorCode SnpContentDropper::LoadSelectionIntoDropper(const UIDList& items)
{
	Utils<Facade::IContentDropperFacade> contentDropperFacade;
	ErrorCode status = contentDropperFacade->LoadContentDropper(items);
	return status;
}

ErrorCode SnpContentDropper::ExpandOrCollapseHead(const bool16 expand)
{
	bool16 succeeded = kFalse;
	do
	{
		InterfacePtr<IWorkspace> iWorkSpace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(iWorkSpace);
		if (iWorkSpace == nil)
			break;

		InterfacePtr<IContentDropperAppData> iContentDropperAppData(iWorkSpace, UseDefaultIID());
		ASSERT(iContentDropperAppData);
		if (iContentDropperAppData == nil)
			break;

		// We first need to check that there is an item at the place head, and that it can
		// be expanded/collapsed. IContentDropperFacade::ExpandCollapseItemAtHead will return
		// kTrue if there is an item at the placehead, even if it can't be expanded/collapsed.
		if (iContentDropperAppData->Size() > 0)
		{
			Utils<Facade::IContentDropperFacade> contentDropperFacade;
			if (expand)
			{
				if (iContentDropperAppData->CanExpandHead())
				{
					succeeded = contentDropperFacade->ExpandCollapseItemAtHead(expand);
				}
				else
				{
					SNIPLOG("The head item is not expandable");
				}
			}
			else
			{
				if (iContentDropperAppData->CanCollapseHead())
				{
					succeeded = contentDropperFacade->ExpandCollapseItemAtHead(expand);
				}
				else
				{
					SNIPLOG("The head item is not collapsable");
				}
			}
		}
		else
		{
			SNIPLOG("No items on the content dropper");
		}
	}
	while (kFalse);

	return succeeded ? kSuccess : kFailure;
}

ErrorCode SnpContentDropper::InspectDocumentContributions()
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application);
		if (application == nil)
			break;

		InterfacePtr<IDocumentList> documentList(application->QueryDocumentList());
		if (documentList == nil)
			break;

		// Iterate over the open documents
		for (int32 i = 0; i < documentList->GetDocCount(); i++)
		{
			IDocument* document = documentList->GetNthDoc(i);
			PMString name;
			document->GetName(name);

			InterfacePtr<IContentDropperDocData> contentDropperDocData(document, UseDefaultIID());
			ASSERT(contentDropperDocData);
			if (contentDropperDocData == nil)
				break;

			// Iterate over each collection on the conveyor from the document
			int32 numberOfCollections = contentDropperDocData->GetNumberOfCollections();
			if (numberOfCollections > 0)
			{
				SNIPLOG("- Inspecting the collections of document %s", name.GetPlatformString().c_str());
				for (int32 i = 0; i < numberOfCollections; i++)
				{
					SNIPLOG("  - Collection %d", i);
					const CCollection* collection = contentDropperDocData->CollectionAtIndex(i);
					InspectCollection(*collection, "    ");
				}
			}
			else if (numberOfCollections == 0)
			{
				SNIPLOG("- Document %s doesn't contribute any collections", name.GetPlatformString().c_str());
			}
		}

		status = kSuccess;
	}
	while (kFalse);
	
	return status;
}

ErrorCode SnpContentDropper::RotateContentDropper(const int32 byHowMany, const bool16 isForward)
{
	Utils<Facade::IContentDropperFacade> contentDropperFacade;
	bool16 succeeded = contentDropperFacade->RotateItemsBy(byHowMany, isForward);
	return succeeded ? kSuccess : kFailure;
}

void SnpContentDropper::InspectCollection(const CCollection& collection, std::string tracePrefix)
{
	int32 numItems = collection.GetNumberOfElements();
	SNIPLOG("%s- Collection contains %d items", tracePrefix.c_str(), numItems);
	SNIPLOG("%s- Collection %s expandable", tracePrefix.c_str(), collection.IsExpandable() ? "is" : "isn't");
	SNIPLOG("%s- Collection %s be unbundled", tracePrefix.c_str(), collection.CanUnbundle() ? "can" : "can't");
	SNIPLOG("%s- Collection has link policy: %s", tracePrefix.c_str(), LinkPolicyAsString(collection.GetLinkPolicy()).c_str());
	
	if (numItems > 1)
	{
		for (int16 i = 0; i < numItems; i++)
		{
			CCollection* childCollection = collection.GetNthElement(i);
			if (childCollection == nil)
				break;

			std::string prefixPaddedByTwo = tracePrefix + "  ";
			SNIPLOG("%s- Exmaning child collection %d", prefixPaddedByTwo.c_str(), i);
			InspectCollection(*childCollection, tracePrefix + "    ");
		}
	}
}

std::string SnpContentDropper::LinkPolicyAsString(const ContentDropperTypes::LinkPolicy linkPolicy)
{
	std::string result = "";
	switch(linkPolicy)
	{
		case ContentDropperTypes::kNoLink:
			result = "No link";
			break;

		case ContentDropperTypes::kCreateLinkPageItem:
			result = "Create link page item";
			break;

		case ContentDropperTypes::kCreateLinkStory:
			result = "Create link story";
			break;

		case ContentDropperTypes::kUnknownPolicy:
			result = "Unknown";
			break;

		default:
			result = "Unrecognised";
			break;
	}

	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpContentDropper available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerContentDropper : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerContentDropper();

		/** Destructor.
		 */
		virtual			~_SnpRunnerContentDropper();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}

};

/* Describe your snippet to the framework here.
*/
_SnpRunnerContentDropper::_SnpRunnerContentDropper()
: SnpRunnable("ContentDropper")
{
	this->SetDescription("Work with the content dropper");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerContentDropper::~_SnpRunnerContentDropper()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerContentDropper::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerContentDropper::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		SnpContentDropper instance;

		// Prompt for parameter values.
		K2Vector<PMString> choices;
		choices.push_back(PMString("Inspect Content Dropper"));
		choices.push_back(PMString("Load selection"));
		choices.push_back(PMString("Place content"));
		choices.push_back(PMString("Expand/Collapse the head item"));
		choices.push_back(PMString("Inspect by document"));
		choices.push_back(PMString("Rotate conveyor items"));
		enum {kInspect, kLoad, kPlace, kExpandCollapse, kInspectDocs, kRotate};

		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What would you like to do?"), choices);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		switch (choice)
		{
		case kInspect: // Inspect content dropper
			status = instance.Inspect();
			break;

		case kLoad: // Load selection into content dropper
			{
				// Get a list of selected items
				InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());

				if (layoutTarget == nil)
				{
					SNIPLOG("Please make a selection and try again");
					break;
				}

				status = instance.LoadSelectionIntoDropper(layoutTarget->GetUIDList(kStripStandoffs));
				break;
			}

		case kExpandCollapse: // Expand or collapse the item at the place head
			{
				K2Vector<PMString> expandChoices;
				expandChoices.push_back(PMString("Expand placehead item"));
				expandChoices.push_back(PMString("Collapse placehead item"));
				enum {kExpand, kCollapse};

				int32 choice = parameterUtils->GetChoice(PMString("What would you like to do?"), expandChoices);
				if (parameterUtils->WasDialogCancelled())
				{
					break;
				}

				status = instance.ExpandOrCollapseHead(choice == kExpand ? kTrue : kFalse);

				break;
			}
			
		case kInspectDocs: // Inspect the collections contributed by each of the open documents
			{
				status = instance.InspectDocumentContributions();
				break;
			}

		case kRotate: // Rotate the items on the conveyor
			{
				int32 howMany = parameterUtils->GetInt32(PMString("How many would you like to rotate by?"));
				if (parameterUtils->WasDialogCancelled())
				{
					break;
				}

				K2Vector<PMString> directionChoices;
				directionChoices.push_back(PMString("Forwards"));
				directionChoices.push_back(PMString("Backwards"));
				enum {kForwards, kBackwards};
				int32 directionChoice = parameterUtils->GetChoice(PMString("Which direction would you like to rotate in?"), directionChoices);
				if (parameterUtils->WasDialogCancelled())
				{
					break;
				}

				status = instance.RotateContentDropper(howMany, directionChoice == kForwards);
				break;
			}

		default:
			break;
		}		
	}
	while(false);

	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerContentDropper instance_SnpRunnerContentDropper;
DEFINE_SNIPPET(_SnpRunnerContentDropper) 	

// End, SnpContentDropper.cpp