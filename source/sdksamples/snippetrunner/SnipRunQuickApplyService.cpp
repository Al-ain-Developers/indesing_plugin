//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunQuickApplyService.cpp $
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
#include "IQuickApplyService.h"
#include "ISelectionUtils.h"

// General includes:
#include "K2Vector.h"
#include "K2Vector.tpp"

// Project includes:
#include "SnipRunID.h"
#include "SnipRunManager.h"
#include "SnpRunnable.h"
#include "ISnipRunSuite.h"


/** Implements the quick apply service for SnippetRunner.

	@ingroup snippetrunner
*/
class SnipRunQuickApplyService : public CPMUnknown<IQuickApplyService>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	SnipRunQuickApplyService(IPMUnknown *boss);
	
	/** Called when the quick apply dialog opens to initialise the quick apply service. 
	*/
	virtual void BeginServiceSession() {fLoadComplete = kFalse;}
	
	/** Called befor ethe quick apply dialog closes to allow the service to perform clean-up activity. 
	*/
	virtual void EndServiceSession() {}
	
	/** Provide the type of items supported by this quick apply service
		@param existingItemTypes IN the set of previously registered quick apply item types. Interrogate these to ensure the choice of prefix key
		for this quick apply service provider is unique. Bad things happen if two quick apply services attempt to register with the same prefix key.
		@return the type of item that this quick apply service supports.
	*/
	virtual TypesHandledList GetItemTypesHandled(const TypesHandledList &existingItemTypes);

	/** The quick apply service can add items to the master list, the complete set of items that are displayed in the quick apply dialog. 
		This implementation adds elements that represent runnable code snippets.
		@param ac IN the current active context, used to determine the set of items that can be legally added.
		@param masterList IN/OUT the list of items to be displayed in the quick apply dialog. 
		@param timeCheck OUT an idle time, if non-nil, an implementation that is heavy-weight should save state and return when the idle timer reaches 0. This allows more responsive
			UI, and the lazy loading of the quick apply dialog. 
		@param itemTypeToLoad IN the type of item to be loaded. Some services can support multiple item types. This indicates the actual type to be loaded.
	*/
	virtual void LoadItems(IActiveContext *ac, K2Vector<QuickApplyFindListNode> *masterList, IdleTimer *timeCheck, uint32 itemTypeToLoad);

	/** Indicates that the service has completed loading the items it supports. A service can indicate that it has not completed loading items (for example,
		where the loading of items would take too long and cause the dialog to stutter). It will then be called back at the next idle loop to continue loading.
		@param id IN the type of item being tested. Some services can support miltiple item types. This indicates the actual type to be tested.
		@return kTrue if the service provider has completed loading the items, kFalse otherwise.
	*/
	virtual bool16 LoadItemsIsComplete(uint32 id);
	
	/** Indicates to the service provider that the user has selected the itemToApply for execution. 
		@param ac IN the active context.
		@param itemToApply IN the item that represents the user selected snipper.
		@param e IN the actual event that invokes the item (thisis useful for example when the behaviour might change with a modifier key).
		@param edit IN Holding down cmd/shift or cmd/alt indicates an edit of the item represented by the quick apply element is required.
		@return kTrue if the service handles the application of the quick apply item.
	*/
	virtual bool16 ApplyItem(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, IEvent *e, bool16 edit);
	
	/** Reset the provider back to the initial (unloaded) state.
	*/
	virtual void ResetProvider() { BeginServiceSession(); }
		
private:
	bool16 fLoadComplete;
};

CREATE_PMINTERFACE(SnipRunQuickApplyService, kSnippetRunnerQuickApplyServiceImpl)

/*
*/
SnipRunQuickApplyService::SnipRunQuickApplyService(IPMUnknown *boss) : CPMUnknown<IQuickApplyService>(boss), 
	fLoadComplete(kFalse)
{
}

/*
*/
bool16 SnipRunQuickApplyService::ApplyItem(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, IEvent *e, bool16 edit)
{
	if (itemToApply.fType == kSnippetRunnerQuickApplyActionID)
	{
		InterfacePtr<ISnipRunSuite> suite(Utils<ISelectionUtils>()->GetActiveSelection(), UseDefaultIID());
		PMString tmp("");
		ErrorCode status = suite->Run(itemToApply.fName, tmp, kTrue);
		return kTrue;
	} 
	return kFalse; // this is some other service provider's item.
}

/*
*/
bool16 SnipRunQuickApplyService::LoadItemsIsComplete(uint32 id)
{
	if (id == kSnippetRunnerQuickApplyActionID)
		return fLoadComplete;
	else
		return kFalse;
}

/*
*/
TypesHandledList SnipRunQuickApplyService::GetItemTypesHandled(const TypesHandledList &existingItemTypes)
{
	TypesHandledList list;
	
	// Define snippets item type
	QuickApplyItemRecord SnipRunType;	
	SnipRunType.fItemUIName = PMString(kSnipRunQuickApplyNameKey); // UI name

	// note we must make sure the key is unique to our plug-in. Bad things happen if two services attempt to 
	// register with the same key.
	// we register the key "G" (activate the filter by typing "G:" in the quick apply dialog).
	// if this key has already been taken, we do not specify a filter key for snippets.
	PMString key(kSnipRunQuickApplyFilterKey); 
	key.Translate();
	bool16 prefixUsed = kFalse;	
	for (TypesHandledList::const_iterator typesHandledListIter = existingItemTypes.begin(); typesHandledListIter != existingItemTypes.end(); typesHandledListIter++)
	{
		if ((*typesHandledListIter).fPrefixKeyString == key) // clash! break
		{
			prefixUsed = kTrue;
			break;
		}
	}
	if (prefixUsed)
	{
		key.Clear();
	}
	SnipRunType.fPrefixKeyString = key;
	

	SnipRunType.fItemID = kSnippetRunnerQuickApplyActionID;
	SnipRunType.fActive = kTrue;
	list.push_back(SnipRunType);
	
	return list; 
}

/*
*/
void SnipRunQuickApplyService::LoadItems(IActiveContext *ac, K2Vector<QuickApplyFindListNode> *masterList, IdleTimer *timeCheck, uint32 itemTypeToLoad)
{
	if (fLoadComplete==kTrue){
		return;
	}
	// first, grab the snippets
	// Get the dictionary of registered snippets.
	const SnipRunManager::SnippetDict& snippets = SnipRunManager::Instance()->GetSnippets();

	InterfacePtr<ISnipRunSuite> iSnipRunSuite(Utils<ISelectionUtils>()->GetActiveSelection(), UseDefaultIID());
	if (!iSnipRunSuite) {
		// If there's no ISnipRunSuite then no snippets can be run so we're done.
		fLoadComplete = kTrue;
		return;
	}

	// For each snippet
	for (int32 i = 0; i < snippets.size(); i++) {
		SnpRunnable* runnable = snippets [i].Value();

		if (runnable && runnable->CanLoad() && iSnipRunSuite->CanRun(ISnipRunSuite::SnippetName(runnable->GetName()))) {
			// only if we can both load and run the snippet do we actually add it to the quick apply list.
						
			QuickApplyFindListNode node;

			node.fPluginID = kSnipRunPluginID;
			node.fIconRsrcID = kSnipRunGoIconSnapResourceID;
			PMString snipName = runnable->GetName();
			snipName.SetTranslatable(kFalse);
			node.fName = ISnipRunSuite::SnippetName(snipName);
			node.fType = kSnippetRunnerQuickApplyActionID;

			masterList->push_back(node);

		}
	}
	fLoadComplete = kTrue;
}

