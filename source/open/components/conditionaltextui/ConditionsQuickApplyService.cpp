//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionsQuickApplyService.cpp $
//  
//  Owner: Kevin Van Wiel
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
#include "CPMUnknown.h"

// ----- Interfaces -----
#include "IQuickApplyService.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"
#include "IDocument.h"
#include "IWorkspace.h"
#include "IEvent.h"
#include "IConditionalTextFacade.h"
#include "IConditionTagList.h"
#include "IConditionTag.h"
#include "IConditionTagSuite.h"

// ----- ID.h files -----
#include "FindChangeID.h"
#include "ConditionalTextUIID.h"
#include "ConditionalTextUIDefs.h"

// ----- Utility files -----
#include "SelectionUtils.h"
#include "EventUtilities.h"

// ----- Includes -----
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "RsrcSpec.h"
#include "keyboarddefs.h"
#include "QuickApplyFindListNode.h"

// ----- Other -----
#include "K2Vector.tpp"

using namespace Facade;

//#define kQuickApplyConditionSets

/******************************************************************************
 * class ConditionsQuickApplyService - This service provider handles conditional text in the quick apply dialog
 ******************************************************************************/
class ConditionsQuickApplyService : public CPMUnknown<IQuickApplyService>
{
public:
	ConditionsQuickApplyService(IPMUnknown *boss);
	
	virtual void BeginServiceSession() 
	{ 
		fConditionLoadComplete = kFalse; 
#if defined (kQuickApplyConditionSets)
		fConditionSetLoadComplete = kFalse; 
#endif
	}
	
	virtual void EndServiceSession() {}
	
	virtual TypesHandledList GetItemTypesHandled(const TypesHandledList &existingItemTypes);
	
	virtual void LoadItems(IActiveContext *ac, K2Vector<QuickApplyFindListNode> *masterList, IdleTimer *timeCheck, uint32 itemTypeToLoad);
	
	virtual bool16 LoadItemsIsComplete(uint32 id);
	
	virtual bool16 ApplyItem(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, IEvent *e, bool16 edit);
	
	virtual void ResetProvider() { BeginServiceSession(); }
		
private:
	void ApplyCondition(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, bool16 edit);
	void AppendUnconditionalTagItem(K2Vector<QuickApplyFindListNode> *masterList);
	bool IsUnconditional(const QuickApplyFindListNode &itemToApply) const;
	
	bool16 fConditionLoadComplete;
#if defined (kQuickApplyConditionSets)
	bool16 fConditionSetLoadComplete;
#endif
};

CREATE_PMINTERFACE(ConditionsQuickApplyService, kConditionsQuickApplyServiceImpl)


/******************************************************************************
 * ConditionsQuickApplyService::ConditionsQuickApplyService
 ******************************************************************************/
ConditionsQuickApplyService::ConditionsQuickApplyService(IPMUnknown *boss) : CPMUnknown<IQuickApplyService>(boss), 
fConditionLoadComplete(kFalse)
#if defined (kQuickApplyConditionSets)
, fConditionSetLoadComplete(kFalse)
#endif
{}

/******************************************************************************
 * ConditionsQuickApplyService::LoadItemsIsComplete
 ******************************************************************************/
bool16 ConditionsQuickApplyService::LoadItemsIsComplete(uint32 id)
{
	bool16 result = kFalse;
	
	switch (id)
	{	
		case kQuickApplyConditionsPrefActionID:
			result = fConditionLoadComplete;
			break;
		
#if defined (kQuickApplyConditionSets)
		case kQuickApplyConditionSetsPrefActionID:
			result = fConditionSetLoadComplete;
			break;
#endif

		default:
			ASSERT_FAIL("Unknown id type ConditionsQuickApplyService::LoadItemsIsComplete()");
			break;
	}
	
	return result;
}

/******************************************************************************
 * ConditionsQuickApplyService::GetItemTypesHandled
 ******************************************************************************/
TypesHandledList ConditionsQuickApplyService::GetItemTypesHandled(const TypesHandledList &existingItemTypes)
{
	TypesHandledList list;
	
	// Define conditions item type
	QuickApplyItemRecord conditionType;	
	conditionType.fItemUIName = PMString("#QuickApplyConditions");
	PMString conditionKey("#Conditions_Filter_Key");
	conditionKey.Translate();
	conditionType.fPrefixKeyString = conditionKey;
	conditionType.fItemID = kQuickApplyConditionsPrefActionID;
	conditionType.fActive = kTrue;
	list.push_back(conditionType);
	
#if defined (kQuickApplyConditionSets)
	QuickApplyItemRecord conditionSetType;	
	conditionSetType.fItemUIName = PMString("#QuickApplyConditionSets");
	PMString conditionSetKey("#QuickApplyConditionSets_Filter_Key");
	conditionSetKey.Translate();
	conditionSetType.fPrefixKeyString = conditionSetKey;
	conditionSetType.fItemID = kQuickApplyConditionSetsPrefActionID;
	conditionSetType.fActive = kTrue;
	list.push_back(conditionSetType);
#endif

	return list; 
}

/******************************************************************************
 * ConditionsQuickApplyService::AppendUnconditionalTagItem
 ******************************************************************************/
void ConditionsQuickApplyService::AppendUnconditionalTagItem(K2Vector<QuickApplyFindListNode> *masterList)
{
	// Special case add the unconditional type
	QuickApplyFindListNode node;				
	node.fPluginID = kConditionalTextUIPluginID;
	node.fIconRsrcID = kQuickApplyConditionPNGRsrcID;
	PMString name("#ConditionTag_Unconditional");
	name.Translate();
	name.SetTranslatable(kFalse);
	node.fName = name;
	node.fType = kQuickApplyConditionsPrefActionID;
	node.fReference = (uint32) 0;
	masterList->push_back(node);
}

/******************************************************************************
 * ConditionsQuickApplyService::LoadItems
 ******************************************************************************/
void ConditionsQuickApplyService::LoadItems(IActiveContext *ac, K2Vector<QuickApplyFindListNode> *masterList, IdleTimer *timeCheck, uint32 itemTypeToLoad)
{
	IWorkspace *ws = ac->GetContextWorkspace();
	
	switch (itemTypeToLoad)
	{
		case kQuickApplyConditionsPrefActionID:
		{
			AppendUnconditionalTagItem(masterList);

			InterfacePtr<IConditionTagList> tagList(Utils<IConditionalTextFacade>()->QueryActiveConditionList(ac));
	
			for (int32 i = 0; i < tagList->GetCount(); i++)
			{
				InterfacePtr<IConditionTag> tag(::GetDataBase(ws), tagList->GetNthCondition(i), UseDefaultIID());
							
				QuickApplyFindListNode node;
				
				node.fPluginID = kConditionalTextUIPluginID;
				node.fIconRsrcID = kQuickApplyConditionPNGRsrcID;
				
				//the style path Format 1 is already translated
				PMString name(tag->GetName());
				name.SetTranslatable(kFalse);
				node.fName = name;

				node.fType = kQuickApplyConditionsPrefActionID;
				node.fReference = (uint32) (tagList->GetNthCondition(i)).Get();

				masterList->push_back(node);
			}

			fConditionLoadComplete = kTrue;
		}
			break;

#if defined (kQuickApplyConditionSets)
		case kQuickApplyConditionSetsPrefActionID:
		{
			UIDList tagSets;
			Utils<IConditionalTextFacade>()->GetAllConditionSets(ac->GetContextWorkspace(), &tagSets);
			for (UIDList::iterator iter = tagSets.begin(); iter != tagSets.end(); iter++)
			{
				QuickApplyFindListNode setNode;
				
				setNode.fPluginID = kConditionalTextUIPluginID;
				setNode.fIconRsrcID = kQuickApplyConditionSetPNGRsrcID;
				
				//the style path Format 1 is already translated
				WideString wName;
				Utils<IConditionalTextFacade>()->GetConditionSetName(UIDRef(tagSets.GetDataBase(), *iter), wName);
				PMString name(wName);
				name.SetTranslatable(kFalse);
				setNode.fName = name;

				setNode.fType = kQuickApplyConditionSetsPrefActionID;
				setNode.fReference = (uint32) (*iter).Get();

				masterList->push_back(setNode);				
			}
			
			fConditionSetLoadComplete = kTrue;
		}
			break;
#endif
	}
}

/******************************************************************************
 * ConditionsQuickApplyService::ApplyItem
 ******************************************************************************/
bool16 ConditionsQuickApplyService::ApplyItem(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, IEvent *e, bool16 edit)
{
	bool16 handled = kFalse;
	
	ISelectionManager *selectionManager = ac->GetContextSelection();
	if (selectionManager)
	{
		switch (itemToApply.fType)
		{
			case kQuickApplyConditionsPrefActionID:
			{
				ApplyCondition(ac, itemToApply, edit);
				handled = kTrue;
			}
				break;
		
#if defined (kQuickApplyConditionSets)
			case kQuickApplyConditionSetsPrefActionID:
			{
				Utils<IConditionalTextFacade>()->SetActiveConditionSet(ac->GetContextWorkspace(), (UID)(itemToApply.fReference));
				handled = kTrue;
			}
				break;
#endif
				
			default:
				break;
		}
	}
	
	return handled;
}

/******************************************************************************
 * ConditionsQuickApplyService::IsUnconditional
 ******************************************************************************/
bool ConditionsQuickApplyService::IsUnconditional(const QuickApplyFindListNode &itemToApply) const
{
	bool unconditional = false;
	
	if (itemToApply.fReference == 0)
	{
		PMString name("#ConditionTag_Unconditional");
		name.Translate();
		name.SetTranslatable(kFalse);
		if (name == itemToApply.fName) unconditional = true;
	}
	
	return unconditional;
}

/******************************************************************************
 * ConditionsQuickApplyService::ApplyItem
 ******************************************************************************/
void ConditionsQuickApplyService::ApplyCondition(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, bool16 edit)
{
	ISelectionManager* selMgr = ac->GetContextSelection();
	InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(selMgr->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
	if (conditionsSuite)
	{
		if (IsUnconditional(itemToApply))
		{
			// Unapply all conditions
			K2Vector<UID> emptyTags;
			conditionsSuite->ApplyConditionTags(emptyTags, kTrue /* remove others */);
		}
		else
		{ 
			K2Vector<UID> tags;
			UID tagUID = (UID)(itemToApply.fReference);
			tags.push_back(tagUID);

			if (::IsOptionAltKeyPressed() && !(::IsShiftKeyPressed()))
			{
				// User pressed option-key so apply the condition tag and remove others (if any).
				conditionsSuite->ApplyConditionTags(tags, kTrue /* remove others */);
			}
			else 
			{
				// If the condition tag clicked is not already applied then apply it; otherwise, remove it.
				// Does not remove other condition tags.
				UIDList appliedToAllChars;
				UIDList appliedToSomeChars;
				conditionsSuite->GetAppliedConditionTags(appliedToAllChars, appliedToSomeChars);
	
				if (K2find(appliedToAllChars, tagUID) == appliedToAllChars.end() && K2find(appliedToSomeChars, tagUID) == appliedToSomeChars.end())
				{
					// Apply the condition tag.
					conditionsSuite->ApplyConditionTags(tags, kFalse);
				}
				else if (::IsShiftKeyPressed())
				{
					// Unapply the condition tag.
					conditionsSuite->UnapplyConditionTags(tags);
				}
			}
		}
	}
}
