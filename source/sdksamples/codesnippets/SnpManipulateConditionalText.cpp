//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateConditionalText.cpp $
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
#include "IApplication.h"
#include "IConditionalTextFacade.h"
#include "IConditionTag.h"
#include "IConditionTagList.h"
#include "IConditionTagSet.h"
#include "IConditionTagSetList.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "ITextModel.h"
#include "ITextFocus.h"
#include "ITextTarget.h"
#include "iuicolorutils.h"
#include "IWorkspace.h"
// General
#include "SDKFileHelper.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include <map>
#include "UIDList.h"

/** 
	The SnpManipulateConditionalText snippet demonstrates the use of the ConditionalTextFacade (IConditionalTextFacade)
	to manipulate Conditions (kConditionTagBoss) and Condition Sets (kConditionTagSetBoss) in a workspace, and to apply
	conditions to text.  The following functionality is demonstrated:
	
	\li List all conditions for the session and all open documents
	\li List all condition sets for the session and all open documents
	\li List the conditions in the active workspace
	\li List the condition sets in the active workspace
	\li Load conditions and condition sets from an InDesign file
	\li Show or Hide condition indicators	
	\li Create a condition in the active workspace
	\li Delete a condition from the active workspace
	\li Set the options for a condition:  name, color, visiblity, indicator method (e.g. kUnderline), and indicator appearance (e.g. kSingleWavy)
	\li Apply a condition to the text model
	\li Remove a condition from the text model
	\li List the conditions applied to the text model
	\li Create a condition set
	\li Show or Hide all conditions in a condition set
	\li Delete a condition set
	\li Set the active condition set
	\li Rename a condition set
	\li Redefine a condition set
	
	@ingroup sdk_snippet
	@ingroup sdk_conditionaltext
	@see _SnpRunnerManipulateConditionalText::Run
	@see IConditionalTextFacade.h	
	@see IConditionTag.h	
	@see IConditionTagSet.h
*/

class SnpManipulateConditionalText {
public:

	/**	Constructor
 
	 */
	SnpManipulateConditionalText();

	/**	Destructor
 
	 */
	virtual ~SnpManipulateConditionalText() {}


	/**	Outputs information about a Condition
		@param conditionRef IN specifies Condition to inspect
		@param nameOnly IN specifies to output only the condition's name
	 */
	void OutputConditionInfo(const UIDRef conditionRef, bool16 nameOnly = kFalse) const;


	/**	Outputs information about a ConditionSet
		@param setRef IN the ConditionSet to inspect
		@param nameOnly IN specifies to output only the condition set's name
	 */
	void OutputSetInfo(const UIDRef setRef, bool16 nameOnly = kFalse) const;


	/**	Outputs information about all the Conditions in the session workspace and the open document(s) workspace
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListAllConditionInfo() const;
	
	
	/**	Outputs information about all the ConditionSets in the session workspace and the open document(s) workspace
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListAllConditionSetInfo() const;
	

	/**	Outputs information about the conditions in the active context's workspace
		@param ac IN specifies active context to list conditions for
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListActiveConditionInfo(const IActiveContext* ac) const;
	
	/**	Outputs information about all the tags in the active context's workspace
		@param ac IN specifies active context to list condition sets for
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListActiveConditionSetInfo(const IActiveContext* ac) const;
	

	/**	Outputs information about all the Conditions in the specified workspace
		@param ws IN specifies workspace to inspect
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListAllWorkspaceConditionInfo(const IWorkspace* ws) const;

	/**	Outputs information about all the ConditionSets in the specified workspace
		@param ws IN specifies workspace to inspect
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListAllWorkspaceConditionSetInfo(const IWorkspace* ws) const;


	/**	Creates a new condition using the IConditionalTextFacade default values
		@param ac IN specifies active context in which the condition is to be created
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode CreateDefaultCondition(const IActiveContext* ac) const;

	/**	Creates a new condition using the specified values
		@param ws IN specifies the workspace in which the condition is to be created
		@param name IN the name of the condition
		@param colorUID IN the color of the condition
		@param method IN the indicator method used to specify how to draw the indicator (e.g. IConditionTag::kUnderline)
		@param appearance IN the underline indicator appearance (e.g. IConditionTag::kSingleWavy)
		@param visibleState IN whether the text associated with the condition is visible
		@param newConditionTagUID OUT the UID of the new condition
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode CreateCondition( IWorkspace* ws, const WideString& name, const UID colorUID, 
							   IConditionTag::IndicatorMethod method, IConditionTag::UnderlineIndicatorAppearance appearance, 
							   const bool16 visibleState, UID* newConditionTagUID) const;

	/**	Deletes a condition, and allows replacement of that condition with another condition (applies the replacement condition
			to the text model in the places where the deleted condition had been applied.)
		@param conditionRef IN the UIDRef of the condition to delete
		@param replacementRef IN the UIDRef of the condition with which to replace the deleted condition
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode DeleteCondition(const UIDRef& conditionRef, const UIDRef& replacementRef) const;
		
	/**	Set the options for an existing condition
		@param conditionRef IN The UIDRef of the condition to edit.
		@param newName IN The new name condition.
		@param newColorUID IN The new color UID for the condition.
		@param newMethod IN The new indicator method for the condition (e.g. kHighlight).
		@param newAppearance IN The new underline indicator appearance for the condition (e.g. kSingleWavy).
		@param newVisibleState IN The new visible state for the condition.
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetConditionOptions(const UIDRef& conditionRef, const WideString& newName, UID newColorUID, IConditionTag::IndicatorMethod newMethod, 
									IConditionTag::UnderlineIndicatorAppearance newAppearance, bool16 newVisibleState) const;


	/**	Rename a condition
		@param conditionRef IN the UIDRef of the condition to modify
		@param newName IN the new name for the condition
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetConditionName(const UIDRef& conditionRef, const PMString& newName) const;
	

	/**	Set the visibility of a condition
		@param conditionRef IN the UIDRef of the condition to modify
		@param newVisibleState IN the new visibility setting for the condition
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetConditionVisibleState(const UIDRef& conditionRef, const bool16& newVisibleState) const;
	
	/**	Set the color of a condition
		@param conditionRef IN the UIDRef of the condition to modify
		@param newColorUID IN the UID of the color to use when drawing the condition indicator
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetConditionColor(const UIDRef& conditionRef, const UID& newColorUID) const;

	/**	Set the method of a condition.  The method is a constant specifying how to draw the condition indicator.
		@param conditionRef IN the UIDRef of the condition to modify
		@param method IN the method to use when drawing the condition indicator (e.g. kHighlight)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetConditionMethod(const UIDRef& conditionRef, const IConditionTag::IndicatorMethod& method) const;

	/**	Set the appearance of a condition (has no effect if conditions's indicator method is kHighlight)
		@param conditionRef IN the UIDRef of the condition to modify
		@param appearance IN the appearance to use when drawing the condition indicator (e.g. kSingleWavy) 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetConditionAppearance(const UIDRef& conditionRef, const IConditionTag::UnderlineIndicatorAppearance& appearance) const;

	
	/**	Apply Conditions to text
		@param textModelRef IN specifies text model ref on which to apply the condition
		@param rangeData IN location in the text model to apply the condition
		@param conditionsToApply IN uid list of the conditions to apply (can be empty and used with removeExisting to remove all conditions)
		@param removeExisting IN true to remove existing applied conditions
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ApplyConditions(const UIDRef& textModelRef, RangeData& rangeData, const K2Vector<UID>& conditionsToApply, bool16 removeExisting = kFalse) const;

	/**	Remove Condition Tag from text
		@param textModelRef IN specifies text model ref on which to apply the condition
		@param rangeData IN location in the text model to apply the condition
		@param conditionsToRemove IN uid list of the conditions to remove (unapply) from the text
		@param removeAll IN true to remove all applied conditions from the text
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode RemoveConditionTags(const UIDRef& textModelRef, RangeData& rangeData, const K2Vector<UID>& conditionsToRemove, bool16 removeAll = kFalse) const;


	/**	Display info about the applied Conditions in the specified text model range
		@param textModelRef IN specifies text model ref on which to inspect applied conditions
		@param rangeData IN location in the text model to inspect applied conditions
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ListAppliedConditionTags(const UIDRef& textModelRef, RangeData& rangeData) const;


	/**	Show or hide the conditional text indicators.  Indicators are drawn on text that has a condition applied.
		@param ws IN specifies workspace to modify
		@param showIndicatorsMode IN show, show and print, or hide indicators
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetShowConditionIndicators(IWorkspace* ws, IConditionalTextOptions::ConditionIndicatorsMode showIndicatorsMode) const;
	
	/**	Copy the conditions and condition sets from an InDesign file to the specified workspace.
		@param ws IN workspace to copy the conditions and sets to.
		@param sourceFile IN the InDesign file to load the conditions from.
		@param loadConditionSets IN if kTrue then loads conditions and condition sets; otherwise, only loads the conditions.
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode LoadConditions(IWorkspace* ws, const IDFile& sourceFile, bool16 loadConditionSets) const;

	
	/**	Create a new condition set.  For this example, all conditions in the specified workspace are added
			to the new set at their current visibility.
		@param ws IN the workspace to create the set in
		@param name IN the name for the condition set
		@param newConditionSetUID OUT the UID of the new set
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode CreateConditionSet(IWorkspace* ws, const WideString& name, UID* newConditionSetUID) const;


	/**	Show or Hide all the conditions present in the active condition set
		@param ws IN the workspace to get the active set from
		@param doShow IN defines whether to show or hide the conditions
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ShowAllConditionsInActiveSet(IWorkspace* ws, bool16 doShow) const;
	
	
	/**	Delete a condition set.
		@param setRef IN uid reference of the set to delete
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode DeleteConditionSet(const UIDRef& setRef) const;

	/**	Set the active condition set
		@param ws IN the workspace to create the set in
		@param setRef IN uid reference of the set to make active
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SetActiveConditionSet(IWorkspace* ws, const UIDRef& setRef) const;


	/**	Modify the specified condition set's name
		@param setRef IN uid reference to the set to modify
		@param newName IN the new name for the condition set
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ModifyConditionSetName(const UIDRef& setRef, const WideString& newName) const;

	/**	Redefine the active condition set.  For this example, the set is redefined to contain
			all conditions in the specified workspace at their current visibility.
		@param ws IN the workspace to get the active set from
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode RedefineActiveConditionSet(IWorkspace* ws) const;




	// used internally...
	
	/*	Query the available indicator appearance names
		@return const K2Vector<PMString>&  containing the names
	 */
	const K2Vector<PMString>& QueryConditionIndicatorMethodNames() const {return fIndicatorMethodNames;}

	/*	Query the available indicator appearance names
		@return const K2Vector<PMString>&  containing the names
	 */
	const K2Vector<PMString>& QueryConditionIndicatorAppearanceNames() const {return fIndicatorAppearanceNames;}

	/*	Query the available show condition indicators mode names
		@return const K2Vector<PMString>&  containing the names
	 */
	const K2Vector<PMString>& QueryShowIndicatorsModeNames() const {return fShowIndicatorsModeNames;}


private:
	
	K2Vector<PMString> fIndicatorMethodNames;
	K2Vector<PMString> fIndicatorAppearanceNames;
	K2Vector<PMString> fShowIndicatorsModeNames;

};



/*  Appends all condition names to the nameList. 
*/
SnpManipulateConditionalText::SnpManipulateConditionalText()
{
	fIndicatorMethodNames.push_back("kUnderline");
	fIndicatorMethodNames.push_back("kHighlight");
	
	fIndicatorAppearanceNames.push_back("kSingleWavy");
	fIndicatorAppearanceNames.push_back("kSolid");
	fIndicatorAppearanceNames.push_back("kDashed");

	fShowIndicatorsModeNames.push_back("kShow");
	fShowIndicatorsModeNames.push_back("kShowAndPrint");
	fShowIndicatorsModeNames.push_back("kHide");
}



/*  Write information about the condition to the snippet log. 
*/
void SnpManipulateConditionalText::OutputConditionInfo(const UIDRef conditionRef, bool16 nameOnly) const
{
	WideString name;
	bool16 visible;			// not set in GetConditionOptions, uses GetConditionVisibleState instead
	UID color;
	IConditionTag::IndicatorMethod method;
	IConditionTag::UnderlineIndicatorAppearance appearance;
	
	ErrorCode err = Utils<Facade::IConditionalTextFacade>()->GetConditionVisibleState(conditionRef, visible);
	if (kSuccess == err) 
	{
		err = Utils<Facade::IConditionalTextFacade>()->GetConditionOptions(conditionRef, name, color, method, appearance);

		/* if you have an IDatabase* and UID, you can get the same info by using a IConditionTag object:
			
			InterfacePtr<IConditionTag> tag(db, tagUID, UseDefaultIID());
			
			WideString name = tag->GetName();
			bool16 visible = tag->IsVisible();
			UID color = tag->GetColor();
			IConditionTag::IndicatorMethod method = tag->GetMethod();
			IConditionTag::UnderlineIndicatorAppearance appearance = tag->GetAppearance();
		*/			
		if (kSuccess == err)
		{
			// find the color name for the color UID
			IDataBase* db = conditionRef.GetDataBase();
			InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);
			int32 colorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(color, doc);  // if doc is nil, app colors are used
			PMString colorName = Utils<IUIColorUtils>()->GetUIColorName(colorIndex);

			PMString pmName;
			name.GetSystemString(&pmName);

			if (nameOnly) {
				SNIPLOG("   name:  %s", pmName.GetPlatformString().c_str());
			} else {
				SNIPLOG("   name:  %s, visible: %s, color: %s, method: %s, appearance: %s", 
						pmName.GetPlatformString().c_str(), 
						visible ? "kTrue" : "kFalse", 
						colorName.GetPlatformString().c_str(),
						fIndicatorMethodNames[method].GetPlatformString().c_str(),
						fIndicatorAppearanceNames[appearance].GetPlatformString().c_str());
			}
		}
	}

}


/*  Write information about the condition to the snippet log. 
*/
void SnpManipulateConditionalText::OutputSetInfo(const UIDRef setRef, bool16 nameOnly) const
{
	WideString setName;
	ErrorCode err = Utils<Facade::IConditionalTextFacade>()->GetConditionSetName(setRef, setName);
	if (kSuccess == err) 
	{
		PMString pmSetName;
		setName.GetSystemString(&pmSetName);
		
		if (nameOnly) {
			SNIPLOG("   set name:  %s", pmSetName.GetPlatformString().c_str());
		} 
		else 
		{
			SNIPLOG(" set name:  %s, conditions:", pmSetName.GetPlatformString().c_str());
			// write info for the tags contained in this set
			IConditionalTextFacade::ConditionSetElementList conditions;
			err = Utils<Facade::IConditionalTextFacade>()->GetConditionsInConditionSet(setRef, conditions);
			if (kSuccess == err)
			{
				// for each condition in the set, display its name and visibility within the set
				for (IConditionalTextFacade::ConditionSetElementList::iterator iter = conditions.begin(); iter != conditions.end(); ++iter)
				{
					UIDRef conditionRef(setRef.GetDataBase(), (*iter).first);
					WideString conditionName;
					err = Utils<Facade::IConditionalTextFacade>()->GetConditionName(conditionRef, conditionName);
					if (kSuccess == err) 
					{
						PMString pmConditionName;
						conditionName.GetSystemString(&pmConditionName);
						bool16 visible = (*iter).second;
						SNIPLOG("   name:  %s,  visible: %s", pmConditionName.GetPlatformString().c_str(), visible ? "true" : "false");
					}
				}
			}
		}
	}
}



/*  Write information about all the condition tags to the snippet log. 
*/
ErrorCode SnpManipulateConditionalText::ListAllConditionInfo() const
{
	ErrorCode err = kSuccess;
	
	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ListAllConditionInfo");

	InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
	if (sessionWorkspace)
	{
		// output the condition information for the session
		SNIPLOG("\n> Application Condition Info:");
		ListAllWorkspaceConditionInfo(sessionWorkspace);

		// get the application object for the session
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app)
		{
			// get the document list for the application
			InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
			if (docList)
			{
				// output the condition information for all the session application's documents
				int32 docCount = docList->GetDocCount();
				for (int32 i = 0; i < docCount; i++)
				{
					IDocument* doc = docList->GetNthDoc(i);
					if (doc)
					{
						InterfacePtr<IWorkspace> docWorkspace(doc->GetDocWorkSpace(), UseDefaultIID());
						if (docWorkspace)
						{
							PMString docName;
							doc->GetName(docName);
							SNIPLOG("\n> Document (%s) Condition Info:", docName.GetPlatformString().c_str());
							ListAllWorkspaceConditionInfo(docWorkspace);
						}
					}
				}
			}
		}
	}
	return err;
}





/*  Write information about all the ConditionSets to the snippet log. 
*/
ErrorCode SnpManipulateConditionalText::ListAllConditionSetInfo() const
{
	ErrorCode err = kSuccess;
	
	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ListAllConditionSetInfo");

	InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
	if (sessionWorkspace)
	{
		// output the condition information for the session
		SNIPLOG("\n> Application Condition Set Info:");
		ListAllWorkspaceConditionSetInfo(sessionWorkspace);

		// get the application object for the session
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app)
		{
			// get the document list for the application
			InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
			if (docList)
			{
				// output the condition information for all the session application's documents
				int32 docCount = docList->GetDocCount();
				for (int32 i = 0; i < docCount; i++)
				{
					IDocument* doc = docList->GetNthDoc(i);
					if (doc)
					{
						InterfacePtr<IWorkspace> docWorkspace(doc->GetDocWorkSpace(), UseDefaultIID());
						if (docWorkspace)
						{
							PMString docName;
							doc->GetName(docName);
							SNIPLOG("\n> Document (%s) Condition Set Info:", docName.GetPlatformString().c_str());
							ListAllWorkspaceConditionSetInfo(docWorkspace);
						}
					}
				}
			}
		}
	}
	return err;
}



/*  Write information about all the conditions in the active workspace to the snippet log. 
*/
ErrorCode SnpManipulateConditionalText::ListActiveConditionInfo(const IActiveContext* ac) const
{
	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ListActiveConditionInfo");

	ErrorCode err = kFailure;
	ASSERT(ac);
	if (ac)
	{
		IWorkspace* ws = ac->GetContextWorkspace();
		if (ws) {
			err = ListAllWorkspaceConditionInfo(ws);
		}
	}
	return err;
}


/*  Write information about all the conditions in the active workspace to the snippet log. 
*/
ErrorCode SnpManipulateConditionalText::ListActiveConditionSetInfo(const IActiveContext* ac) const
{
	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ListActiveConditionSetInfo");

	ErrorCode err = kFailure;
	ASSERT(ac);
	if (ac)
	{
		IWorkspace* ws = ac->GetContextWorkspace();
		if (ws) {
			err = ListAllWorkspaceConditionSetInfo(ws);
		}
	}
	return err;
}



/*  Write information about all the conditions in the workspace to the snippet log. 
*/
ErrorCode SnpManipulateConditionalText::ListAllWorkspaceConditionInfo(const IWorkspace* ws) const
{
	ErrorCode err = kFailure;

	ASSERT(ws);
	if (ws) 
	{
		err = kSuccess;

		// get the list of conditions for the workspace
		InterfacePtr<IConditionTagList> conditionList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(::GetDataBase(ws)));
		if (conditionList && conditionList->GetCount() > 0) 
		{
			// inspect each tag in the list
			for (int32 i = 0; i < conditionList->GetCount(); i++) 
			{
				UIDRef conditionRef(::GetDataBase(ws), conditionList->GetNthCondition(i));
				OutputConditionInfo(conditionRef);
			}
		} else {
			SNIPLOG("      No condition tags exist for the workspace");
		}
	}
	return err;
}


/*  Write information about all the ConditionSets in the workspace to the snippet log. 
*/
ErrorCode SnpManipulateConditionalText::ListAllWorkspaceConditionSetInfo(const IWorkspace* ws) const
{
	ErrorCode err = kFailure;

	ASSERT(ws);
	if (ws) 
	{
		err = kSuccess;

		// get the list of condition sets for the workspace
		InterfacePtr<IConditionTagSetList> setList(Utils<Facade::IConditionalTextFacade>()->QueryConditionSetList(::GetDataBase(ws)));
		if (setList && setList->GetCount() > 0) 
		{
			// inspect each tag in the list
			for (int32 i = 0; i < setList->GetCount(); i++) 
			{
				UIDRef setRef(::GetDataBase(ws), setList->GetNthSet(i));
				OutputSetInfo(setRef);
			}
		} else {
			SNIPLOG("      No condition sets exist for the workspace");
		}

	}
	return err;
}


/*  Create a new condition in the workspace using the default values
*/
ErrorCode SnpManipulateConditionalText::CreateDefaultCondition(const IActiveContext* ac) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::CreateDefaultCondition");

	ASSERT(ac);
	if(ac) 
	{
		IWorkspace* ws = ac->GetContextWorkspace();
		if (ws) 
		{
			UID newConditionUID;
			err = Utils<Facade::IConditionalTextFacade>()->CreateCondition( ws, &newConditionUID );
			if (kSuccess == err) 
			{
				SNIPLOG("      Success.  New condition info:  /n");
				UIDRef conditionRef(::GetDataBase(ac), newConditionUID);
				OutputConditionInfo(conditionRef);
			} 
		}
	}

	return err;
}




/*  Create a new condition in the workspace.  If name is empty, a unique name will be generated.  
	If colorUID is kInvalidUID, a unique color will be chosen. 
*/
ErrorCode SnpManipulateConditionalText::CreateCondition(IWorkspace* ws, const WideString& name, const UID colorUID, 
		IConditionTag::IndicatorMethod method, IConditionTag::UnderlineIndicatorAppearance appearance, const bool16 visibleState, UID* newConditionUID) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::CreateCondition");

	ASSERT(ws);
	if(ws) 
	{
        err = Utils<Facade::IConditionalTextFacade>()->CreateCondition( ws, newConditionUID, name, colorUID, method, appearance, visibleState);
		if (kSuccess == err) 
		{
			SNIPLOG("      Success.  New condition info:  /n");
			UIDRef conditionRef(::GetDataBase(ws), *newConditionUID);
			OutputConditionInfo(conditionRef);
		} 
		else 
		{
			SNIPLOG("      Error:  error (%d) encountered while creating condition \n", err);
		}
	}

	return err;
}



/*  Delete a condition specified by the UIDRef. 
*/
ErrorCode SnpManipulateConditionalText::DeleteCondition(const UIDRef& conditionRef, const UIDRef& replacementRef) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::DeleteCondition");
	SNIPLOG(">     Deleting Condition:");
	OutputConditionInfo(conditionRef);
	if (replacementRef.GetUID() != kInvalidUID) {
		SNIPLOG(">     Replacing with Condition:");
		OutputConditionInfo(replacementRef);
	}
	
	UIDList tagsToDelete(conditionRef);		// just one tag tag to delete, so only one in this list

	err = Utils<Facade::IConditionalTextFacade>()->DeleteConditions(tagsToDelete, replacementRef.GetUID());
	
	if (kSuccess == err) {
		SNIPLOG("      Success:  condition deleted");
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}


/*  Set ConditionTag options for a ConditionTag
*/
ErrorCode SnpManipulateConditionalText::SetConditionOptions(const UIDRef& conditionRef, const WideString& newName, UID newColorUID, IConditionTag::IndicatorMethod newMethod, 
								IConditionTag::UnderlineIndicatorAppearance newAppearance, bool16 newVisibleState) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetConditionOptions");
	SNIPLOG(">     Setting Condition Options for:");
	OutputConditionInfo(conditionRef);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionVisibleState(conditionRef, newVisibleState);
	if (kSuccess == err) {
		err = Utils<Facade::IConditionalTextFacade>()->SetConditionOptions(conditionRef, newName, newColorUID, newMethod, newAppearance);
	}
	
	if (kSuccess == err) {
		SNIPLOG("      Success.  Condition options changed:  /n");
		OutputConditionInfo(conditionRef);
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}


/*  Rename a condition 
*/
ErrorCode SnpManipulateConditionalText::SetConditionName(const UIDRef& conditionRef, const PMString& newName) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetConditionName");
	SNIPLOG(">     Renaming condition:");
	OutputConditionInfo(conditionRef);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionName(conditionRef, WideString(newName));

	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition renamed:");
		OutputConditionInfo(conditionRef);
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}
	

/*  Set the visible state of a condition
*/
ErrorCode SnpManipulateConditionalText::SetConditionVisibleState(const UIDRef& conditionRef, const bool16& newVisibleState) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetConditionVisibleState");
	SNIPLOG(">     Setting visible state of condition:");
	OutputConditionInfo(conditionRef);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionVisibleState( conditionRef, newVisibleState);

	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition visiblility changed:");
		OutputConditionInfo(conditionRef);
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}
	

/*  Set the color of a condition
*/
ErrorCode SnpManipulateConditionalText::SetConditionColor(const UIDRef& conditionRef, const UID& newColorUID) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetConditionColor");
	SNIPLOG(">     Setting color of condition:");
	OutputConditionInfo(conditionRef);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionColor(conditionRef, newColorUID);

	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition color changed:");
		OutputConditionInfo(conditionRef);
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}


/*  Set the color of a condition
*/
ErrorCode SnpManipulateConditionalText::SetConditionMethod(const UIDRef& conditionRef, const IConditionTag::IndicatorMethod& method) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetConditionMethod");
	SNIPLOG(">     Setting indicator method of condition:");
	OutputConditionInfo(conditionRef);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionMethod(conditionRef, method);

	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition indicator method changed:");
		OutputConditionInfo(conditionRef);
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}



/*  Set the appearance of a condition
*/
ErrorCode SnpManipulateConditionalText::SetConditionAppearance(const UIDRef& conditionRef, const IConditionTag::UnderlineIndicatorAppearance& appearance) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetConditionAppearance");
	SNIPLOG(">     Setting indicator appearance of condition:");
	OutputConditionInfo(conditionRef);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionAppearance(conditionRef, appearance);

	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition appearance changed:");
		OutputConditionInfo(conditionRef);
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}



/*  Apply a condition tag to the text model. 
*/
ErrorCode SnpManipulateConditionalText::ApplyConditions(const UIDRef& textModelRef, RangeData& rangeData, const K2Vector<UID>& conditionsToApply, bool16 removeExisting) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ApplyConditions");
	SNIPLOG("      Applying condition tags:  /n");
	for (int32 i = 0; i < conditionsToApply.size(); i++) {
		OutputConditionInfo(UIDRef(textModelRef.GetDataBase(), conditionsToApply[i]));
	}
	
	err = Utils<Facade::IConditionalTextFacade>()->ApplyConditionsToText(textModelRef, rangeData.Start(nil), rangeData.Length(), conditionsToApply, removeExisting);

	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition applied to text");
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}




/*  Apply a condition tag to the text model. 
*/
ErrorCode SnpManipulateConditionalText::RemoveConditionTags(const UIDRef& textModelRef, RangeData& rangeData, const K2Vector<UID>& conditionsToRemove, bool16 removeAll) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::RemoveConditionTags");
	
	if (removeAll) 
	{
		SNIPLOG("      Removing all condition tags /n");
		// remove all condition tags by applying none (an empty list of UIDs) and removing existing (true param at end)
		K2Vector<UID> emptyList;
		err = Utils<Facade::IConditionalTextFacade>()->ApplyConditionsToText(textModelRef, rangeData.Start(nil), rangeData.Length(), emptyList, true);
	} 
	else 
	{
		SNIPLOG("      Removing condition tags: /n");
		for (int32 i = 0; i < conditionsToRemove.size(); i++) {
			OutputConditionInfo(UIDRef(textModelRef.GetDataBase(), conditionsToRemove[i]));
		}
		err = Utils<Facade::IConditionalTextFacade>()->RemoveConditionsFromText(textModelRef, rangeData.Start(nil), rangeData.Length(), conditionsToRemove);
	}
	
	if (kSuccess == err) {
		SNIPLOG("      Success:  Condition removed from text");
	} else {
		SNIPLOG("      Error:  %d", err);
	}

	return err;
}



/*  Report the condition tags in the text model. 
*/
ErrorCode SnpManipulateConditionalText::ListAppliedConditionTags(const UIDRef& textModelRef, RangeData& rangeData) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ListAppliedConditionTags");

	IDataBase* db = textModelRef.GetDataBase();
	ASSERT(db);
	if(db) 
	{
		err = kSuccess;
		
		// Get the conditions applied to the start of the text run.  Will join runs when the condition is unchanged until endPosition
		SNIPLOG("\n >> Applied Conditions from Start:");
		int32 length;
		K2Vector<UID> conditionList = Utils<Facade::IConditionalTextFacade>()->GetAppliedConditions(textModelRef, rangeData.Start(nil), rangeData.End(), &length);
		if (conditionList.size() > 0) 
		{
			if (length != 0) {
				SNIPLOG("     (length of text using conditions = %d)", length);
			}
			for (int32 i = 0; i < conditionList.size(); i++) 
			{
				UIDRef conditionRef(db, conditionList[i]);
				OutputConditionInfo(conditionRef);
			}
		} 
		else 
		{
			SNIPLOG("     No conditions applied to start of text run.");
		}
		
		
		// Get the conditions applied to entire text run
		SNIPLOG("\n >> Applied Conditions to entire run:");
		
		UIDList appliedToAllChars;
		UIDList appliedToSomeChars;
		bool16 rangeHasUnconditionalChars;
		err = Utils<Facade::IConditionalTextFacade>()->GetAppliedConditions(textModelRef, rangeData, appliedToAllChars, appliedToSomeChars, &rangeHasUnconditionalChars);
		if (kSuccess == err)
		{
			if (rangeHasUnconditionalChars) {
				SNIPLOG("     * text run contains some unconditional chars");
			}
			if (appliedToAllChars.size() > 0) 
			{
				SNIPLOG("\n   conditions applied to ALL text in run:");
				for (int32 i = 0; i < appliedToAllChars.size(); i++) 
				{
					UIDRef conditionRef(db, appliedToAllChars[i]);
					OutputConditionInfo(conditionRef);
				}
			} 
			if (appliedToSomeChars.size() > 0) 
			{
				SNIPLOG("\n   conditions applied to SOME text in run:");
				for (int32 i = 0; i < appliedToSomeChars.size(); i++) 
				{
					UIDRef conditionRef(db, appliedToSomeChars[i]);
					OutputConditionInfo(conditionRef);
				}
			} 
			if (appliedToAllChars.size() == 0 && appliedToSomeChars.size() == 0)
			{
				SNIPLOG("     No conditions applied to text run.");
			}
		}
	}
	return err;
}




/*  show or hide the conditional text indicators
*/
ErrorCode SnpManipulateConditionalText::SetShowConditionIndicators(IWorkspace* ws, IConditionalTextOptions::ConditionIndicatorsMode showIndicators) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetShowConditionIndicators");
	if (showIndicators == IConditionalTextOptions::kShow)
	{
		SNIPLOG("      Setting showIndicators to:  show");
	}
	else if (showIndicators == IConditionalTextOptions::kShowAndPrint)
	{
		SNIPLOG("      Setting showIndicators to:  show and print");
	}
	else if (showIndicators == IConditionalTextOptions::kHide)
	{
		SNIPLOG("      Setting showIndicators to:  hide");
	}
	
	ASSERT(ws);
	if (ws) 
	{
		err = Utils<Facade::IConditionalTextFacade>()->SetShowConditionIndicators(ws, showIndicators);
	}
	
	return err;
}



/*  Attempts to load the conditions, and optionally, the condition sets from the specified file
*/
ErrorCode SnpManipulateConditionalText::LoadConditions(IWorkspace* ws, const IDFile& sourceFile, bool16 loadConditionSets) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::LoadConditions");
	SNIPLOG("      Loading conditions from:  %s", sourceFile.GetFileName().GetPlatformString().c_str());
	
	ASSERT(ws);
	if (ws) 
	{
		err = Utils<Facade::IConditionalTextFacade>()->LoadConditions(ws, sourceFile, loadConditionSets);
	}
	return err;
}


/*  show or hide the conditional text indicators
*/
ErrorCode SnpManipulateConditionalText::CreateConditionSet(IWorkspace* ws, const WideString& name, UID* newConditionSetUID) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::CreateConditionSet");

	// for the purposes of this example, the condition set is redefined to contain all conditions
	// in the specified workspace, at their current visibility.
	// In your own code, you need to choose whichever conditions are appropriate for your situation.
	
	ASSERT(ws);
	if (ws) 
	{
		IConditionalTextFacade::ConditionSetElementList visibleConditionsList;

		// get all the conditions in the provided workspace, then find the visible ones
		InterfacePtr<IConditionTagList> conditionList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(::GetDataBase(ws)));
		if (conditionList) 
		{
			// build a list of condition/visibility pairs to send to the create method
			for (int32 i = 0; i < conditionList->GetCount(); i++) 
			{
				InterfacePtr<IConditionTag> condition(::GetDataBase(ws), conditionList->GetNthCondition(i), UseDefaultIID());
				if (condition) {
					// add condition/visibility pair to the list
					IConditionalTextFacade::ConditionSetElement elem(::GetUID(condition), condition->IsVisible());
					visibleConditionsList.push_back(elem);
				}
			}
		}

		err = Utils<Facade::IConditionalTextFacade>()->CreateConditionSet(ws, name, visibleConditionsList, newConditionSetUID);
		if (kSuccess == err)
		{
			SNIPLOG("   Success.  Created condition set:");
			OutputSetInfo( UIDRef(::GetDataBase(ws), *newConditionSetUID) );
		}
	}
	return err;
}


/*  show or hide the conditional text indicators
*/
ErrorCode SnpManipulateConditionalText::ShowAllConditionsInActiveSet(IWorkspace* ws, bool16 doShow) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ShowAllConditionsInActiveSet");

	ASSERT(ws);
	if (ws) 
	{
		UID activeSet;
		err = Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(ws, activeSet);
		if (kSuccess == err)
		{
			IDataBase* db = ::GetDataBase(ws);
			UIDRef activeSetRef(db, activeSet);
			
			SNIPLOG(">     Setting visibility of all conditions in set to %s.  Current status:", doShow ? "true" : "false");
			OutputSetInfo(activeSetRef);

			// for each condition in the Set, set its visibility as requested
			IConditionalTextFacade::ConditionSetElementList conditions;
			err = Utils<Facade::IConditionalTextFacade>()->GetConditionsInConditionSet(activeSetRef, conditions);
			if (kSuccess == err)
			{
				for (IConditionalTextFacade::ConditionSetElementList::iterator iter = conditions.begin(); iter != conditions.end() && kSuccess == err; ++iter)
				{
					err = Utils<Facade::IConditionalTextFacade>()->SetConditionVisibleState(UIDRef(db, (*iter).first), doShow);
				}
				if (kSuccess == err )
				{
					SNIPLOG(">     New status:");
					OutputSetInfo(activeSetRef);
				}
			}
		}
	}
	return err;
}


/*  Delete the specified condition set
*/
ErrorCode SnpManipulateConditionalText::DeleteConditionSet(const UIDRef& setRef) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::DeleteConditionSet");
	SNIPLOG(">     Deleting Condition Set:");
	OutputSetInfo(setRef);

	err = Utils<Facade::IConditionalTextFacade>()->DeleteConditionSet(setRef);
	
	return err;
}


/*  Make the specified condition set the active condition set
*/
ErrorCode SnpManipulateConditionalText::SetActiveConditionSet(IWorkspace* ws, const UIDRef& setRef) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::SetActiveConditionSet");
	SNIPLOG(">     Setting active set to:");
	OutputSetInfo(setRef);

	ASSERT(ws);
	if (ws) 
	{
		err = Utils<Facade::IConditionalTextFacade>()->SetActiveConditionSet(ws, setRef.GetUID());
	}
	return err;
}



/*  Make the specified condition set the active condition set
*/
ErrorCode SnpManipulateConditionalText::ModifyConditionSetName(const UIDRef& setRef, const WideString& newName) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::ModifyConditionSetName");
	SNIPLOG(">     Modifying set name:");
	OutputSetInfo(setRef, true);

	err = Utils<Facade::IConditionalTextFacade>()->SetConditionSetName(setRef, newName);
	if (kSuccess == err )
	{
		SNIPLOG(">     Modified to:");
		OutputSetInfo(setRef, true);
	}
	
	return err;
}



/*  Make the specified condition set the active condition set
*/
ErrorCode SnpManipulateConditionalText::RedefineActiveConditionSet(IWorkspace* ws) const
{
	ErrorCode err = kFailure;

	SNIPLOG("--------------------------------------------------------------------------------");
	SNIPLOG("> SnpManipulateConditionalText::RedefineActiveConditionSet");

	// for the purposes of this example, the condition set is redefined to contain all conditions
	// in the specified workspace, at their current visibility.
	// In your own code, you need to choose whichever conditions are appropriate for your situation.

	ASSERT(ws);
	if (ws) 
	{
		UID activeSet;
		err = Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(ws, activeSet);
		if (kSuccess == err)
		{
			IDataBase* db = ::GetDataBase(ws);
			UIDRef activeSetRef(db, activeSet);

			SNIPLOG(">     Redefining set:");
			OutputSetInfo(activeSetRef);

			IConditionalTextFacade::ConditionSetElementList visibleConditionsList;

			// get all the conditions in the provided workspace, then find the visible ones
			InterfacePtr<IConditionTagList> conditionList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(::GetDataBase(ws)));
			if (conditionList) 
			{
				// build a list of condition/visibility pairs to send to the redefine method
				for (int32 i = 0; i < conditionList->GetCount(); i++) 
				{
					InterfacePtr<IConditionTag> condition(::GetDataBase(ws), conditionList->GetNthCondition(i), UseDefaultIID());
					if (condition) {
						// add condition/visibility pair to the list
						IConditionalTextFacade::ConditionSetElement elem(::GetUID(condition), condition->IsVisible());
						visibleConditionsList.push_back(elem);
					}
				}
			}

			err = Utils<Facade::IConditionalTextFacade>()->RedefineConditionSet(activeSetRef, visibleConditionsList);
			if (kSuccess == err )
			{
				SNIPLOG(">     Redefined to:");
				OutputSetInfo(activeSetRef);
			}
		}
	}
	return err;
}






// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateConditionalText available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateConditionalText : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateConditionalText();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateConditionalText();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param rc see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* rc);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
		
		
	private:
		
		void		PopulateConditionNameChoices(const IConditionTagList* conditionList, IDataBase* db, K2Vector<PMString>& choices) const;
		void		PopulateConditionSetNameChoices(const IConditionTagSetList* conditionSetList, IDataBase* db, K2Vector<PMString>& choices) const;
		void		PopulateIndicatorChoices(K2Vector<PMString>& choices) const;
		void		PopulateAppearanceChoices(K2Vector<PMString>& choices) const;
		void		PopulateActionChoices(ISnpRunnableContext* runnableContext, IActiveContext* ac, K2Vector<int32>& menuItemEnums, K2Vector<PMString>& menuItemNames);
		void		PopulateShowIndicatorsModeChoices(K2Vector<PMString>& choices) const;
		
		ErrorCode	RequestBoolean(const PMString& prompt, bool16& boolValue) const;
		ErrorCode	RequestString(const PMString& prompt, WideString& stringValue) const;
		ErrorCode	RequestString(const PMString& prompt, PMString& stringValue) const;
		ErrorCode	RequestMethodChoice(IConditionTag::IndicatorMethod& method) const;
		ErrorCode	RequestAppearanceChoice(IConditionTag::UnderlineIndicatorAppearance& appearance) const;
		ErrorCode	RequestColorChoice(const IWorkspace* ws, UID& color) const;
		ErrorCode	RequestConditionChoice(const PMString& prompt, IActiveContext* ac, UIDRef& conditionRef, bool16 allowNone = kFalse, const PMString* nonePrompt = nil) const;
		ErrorCode	RequestConditionSetChoice(const PMString& prompt, IActiveContext* ac, UIDRef& setRef) const;
		ErrorCode	RequestConditionOptions(IActiveContext* ac, WideString& name, bool16& visible, UID& color,
							IConditionTag::IndicatorMethod& method,  IConditionTag::UnderlineIndicatorAppearance& appearance) const;
		ErrorCode	RequestShowIndicatorsMode(IConditionalTextOptions::ConditionIndicatorsMode& showIndicatorsMode) const;
		
		ErrorCode	HandleLoadConditions(IActiveContext* ac) const;
		ErrorCode	HandleShowConditionIndicators(IActiveContext* ac) const;
		ErrorCode	HandleCreateCondition(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionOptions(IActiveContext* ac) const;
		ErrorCode	HandleDeleteCondition(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionName(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionVisibility(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionColor(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionMethod(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionAppearance(IActiveContext* ac) const;
		ErrorCode	HandleApplyCondition(ISnpRunnableContext* runnableContext) const;
		ErrorCode	HandleRemoveCondition(ISnpRunnableContext* rc) const;
		ErrorCode	HandleListAppliedConditions(ISnpRunnableContext* runnableContext) const;
		ErrorCode	HandleCreateConditionSet(IActiveContext* ac) const;
		ErrorCode	HandleShowAllConditionsInActiveSet(IActiveContext* ac) const;
		ErrorCode	HandleDeleteConditionSet(IActiveContext* ac) const;
		ErrorCode	HandleSetActiveConditionSet(IActiveContext* ac) const;
		ErrorCode	HandleModifyConditionSetName(IActiveContext* ac) const;
		ErrorCode	HandleRedefineActiveConditionSet(IActiveContext* ac) const;
		
		ErrorCode	GetTextRange(ITextTarget* textTarget, RangeData& rangeData) const;
		
		
		SnpManipulateConditionalText	fSnippetInstance;

		typedef std::map<int32, PMString> TMenuValueMap;
		typedef std::pair<int32, PMString> TMenuValuePair;
		TMenuValueMap	fMenuValuesMap;

		enum eActionChoices
		{
			en_ListAllConditions = 0, 
			en_ListAllConditionSets,
			en_ListActiveConditions,
			en_ListActiveConditionSets,
			
			en_LoadConditions,
			en_ShowConditionIndicators,

			en_CreateConditionDefault, 
			en_CreateConditionUser, 
			en_DeleteCondition, 
			en_SetConditionOptions,
			en_SetConditionName, 
			en_SetConditionVisible, 
			en_SetConditionColor,
			en_SetConditionMethod,
			en_SetConditionAppearance,
			
			en_ApplyCondition, 
			en_RemoveCondition,
			en_ListAppliedConditions,
			
			en_CreateConditionSet, 
			en_ShowAllConditionsInActiveSet,
			en_DeleteConditionSet,
			en_SetActiveConditionSet,
			en_SetConditionSetName,
			en_RedefineActiveConditionSet
		};
						
			
};




/* Describe your snippet to the framework here.
*/
_SnpRunnerManipulateConditionalText::_SnpRunnerManipulateConditionalText() : SnpRunnable("ManipulateConditionalText")
{
	this->SetDescription("Manipulate conditional text");
	this->SetCategories("sdk_snippet, sdk_conditionaltext");

	
	// fMenuValuesMap stores all possible menu items as a pair of enum/string values.
	// When creating the popup menu for the snippet, the appropriate menu items are 
	// added to a list of menu items.  When a selection comes back from the parameterUtils,
	// the map is used to evaluate the selection as an enum.
	fMenuValuesMap.insert(TMenuValuePair(en_ListAllConditions, "List All Conditions"));
	fMenuValuesMap.insert(TMenuValuePair(en_ListAllConditionSets, "List All ConditionSets"));
	fMenuValuesMap.insert(TMenuValuePair(en_ListActiveConditions, "List Conditions in ActiveContext"));
	fMenuValuesMap.insert(TMenuValuePair(en_ListActiveConditionSets, "List ConditionSets in ActiveContext"));
	
	fMenuValuesMap.insert(TMenuValuePair(en_LoadConditions, "Load Conditions"));
	fMenuValuesMap.insert(TMenuValuePair(en_ShowConditionIndicators, "Show/Hide Condition Indicators"));
	
	fMenuValuesMap.insert(TMenuValuePair(en_CreateConditionDefault, "Create Condition (default values)"));
	fMenuValuesMap.insert(TMenuValuePair(en_CreateConditionUser, "Create Condition"));
	fMenuValuesMap.insert(TMenuValuePair(en_DeleteCondition, "Delete Condition"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionOptions, "Set Condition Options"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionName, "Set Condition Name"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionVisible, "Set Condition Visible"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionColor, "Set Condition Color"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionMethod, "Set Condition Method"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionAppearance, "Set Condition Appearance"));

	fMenuValuesMap.insert(TMenuValuePair(en_ApplyCondition, "Apply Condition to text"));
	fMenuValuesMap.insert(TMenuValuePair(en_RemoveCondition, "Remove Condition from text"));
	fMenuValuesMap.insert(TMenuValuePair(en_ListAppliedConditions, "List Applied Conditions"));

	fMenuValuesMap.insert(TMenuValuePair(en_CreateConditionSet, "Create ConditionSet"));
	fMenuValuesMap.insert(TMenuValuePair(en_ShowAllConditionsInActiveSet, "Show/Hide All Conditions in Active Set"));
	fMenuValuesMap.insert(TMenuValuePair(en_DeleteConditionSet, "Delete ConditionSet"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetActiveConditionSet, "Set Active ConditionSet"));
	fMenuValuesMap.insert(TMenuValuePair(en_SetConditionSetName, "Rename ConditionSet"));
	fMenuValuesMap.insert(TMenuValuePair(en_RedefineActiveConditionSet, "Redefine Active ConditionSet"));
}

/* Destructor.
*/
_SnpRunnerManipulateConditionalText::~_SnpRunnerManipulateConditionalText()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateConditionalText::CanRun(ISnpRunnableContext* runnableContext)
{
	return (runnableContext && runnableContext->GetActiveContext() != nil);
}


/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateConditionalText::Run(ISnpRunnableContext* rc)
{
	ErrorCode err = kFailure;

	ASSERT(rc);
	if (rc)
	{
		IActiveContext* ac = rc->GetActiveContext();
		ASSERT(ac);
		if (ac)
		{
			// create a popup list of actions to choose from
			K2Vector<int32> actionEnums;
			K2Vector<PMString> actionNames;
			PopulateActionChoices(rc, ac, actionEnums, actionNames);

			// display the dialog and get the user's Action choice
			Utils<ISnipRunParameterUtils> parameterUtils;
			int32 choice = parameterUtils->GetChoice(PMString("Choose an action"), actionNames);
			if (!parameterUtils->WasDialogCancelled()) 
			{
				switch(actionEnums[choice]) 
				{
					case en_ListAllConditions:
					{
						err = fSnippetInstance.ListAllConditionInfo();
						break;
					}
					case en_ListAllConditionSets:
					{
						err = fSnippetInstance.ListAllConditionSetInfo();
						break;
					}
					case en_ListActiveConditions:
					{
						err = fSnippetInstance.ListActiveConditionInfo(ac);
						break;
					}
					case en_ListActiveConditionSets:
					{
						err = fSnippetInstance.ListActiveConditionSetInfo(ac);
						break;
					}
					case en_LoadConditions:
					{
						err = HandleLoadConditions(ac);
						break;
					}
					case en_ShowConditionIndicators:
					{
						err = HandleShowConditionIndicators(ac);
						break;
					}
					case en_CreateConditionDefault:
					{
						err = fSnippetInstance.CreateDefaultCondition(ac);
						break;
					}
					case en_CreateConditionUser:
					{
						err = HandleCreateCondition(ac);
						break;
					}
					case en_DeleteCondition:
					{
						err = HandleDeleteCondition(ac);
						break;
					}
					case en_SetConditionOptions:
					{
						err = HandleModifyConditionOptions(ac);
						break;
					} 
					case en_SetConditionName:
					{
						err = HandleModifyConditionName(ac);
						break;
					} 
					case en_SetConditionVisible:
					{
						err = HandleModifyConditionVisibility(ac);
						break;
					} 
					case en_SetConditionColor:
					{
						err = HandleModifyConditionColor(ac);
						break;
					} 
					case en_SetConditionMethod:
					{
						err = HandleModifyConditionMethod(ac);
						break;
					} 
					case en_SetConditionAppearance:
					{
						err = HandleModifyConditionAppearance(ac);
						break;
					} 
					case en_ApplyCondition:
					{
						err = HandleApplyCondition(rc);
						break;
					} 
					case en_RemoveCondition:
					{
						err = HandleRemoveCondition(rc);
						break;
					} 
					case en_ListAppliedConditions:
					{
						err = HandleListAppliedConditions(rc);
						break;
					} 
					case en_CreateConditionSet:
					{
						err = HandleCreateConditionSet(ac);
						break;
					} 
					case en_ShowAllConditionsInActiveSet:
					{
						err = HandleShowAllConditionsInActiveSet(ac);
						break;
					} 
					case en_DeleteConditionSet:
					{
						err = HandleDeleteConditionSet(ac);
						break;
					} 
					case en_SetActiveConditionSet:
					{
						err = HandleSetActiveConditionSet(ac);
						break;
					} 
					case en_SetConditionSetName:
					{
						err = HandleModifyConditionSetName(ac);
						break;
					} 
					case en_RedefineActiveConditionSet:
					{
						err = HandleRedefineActiveConditionSet(ac);
						break;
					} 
					default:
					{
						break;
					}
				}
			}
			else 
			{
				err = kCancel;
			}
		}
	}
	SNIPLOG("");
	return err;
}






/*  Populates the list names of active conditions. 
*/
void _SnpRunnerManipulateConditionalText::PopulateConditionNameChoices(const IConditionTagList* conditionList, IDataBase* db, K2Vector<PMString>& choices) const
{
	choices.clear();

	ASSERT(conditionList);
	if (conditionList) 
	{
		for (int32 i = 0; i < conditionList->GetCount(); i++) 
		{
			InterfacePtr<IConditionTag> condition(db, conditionList->GetNthCondition(i), UseDefaultIID());
			if (condition) 
			{
				PMString name;
				condition->GetName().GetSystemString(&name);
				choices.push_back(name);
			}
		}
	}
}



/*  Populates the list names of active conditions. 
*/
void _SnpRunnerManipulateConditionalText::PopulateConditionSetNameChoices(const IConditionTagSetList* conditionSetList, IDataBase* db, K2Vector<PMString>& choices) const
{
	choices.clear();

	ASSERT(conditionSetList);
	if (conditionSetList) 
	{
		for (int32 i = 0; i < conditionSetList->GetCount(); i++) 
		{
			InterfacePtr<IConditionTagSet> conditionSet(db, conditionSetList->GetNthSet(i), UseDefaultIID());
			if (conditionSet) 
			{
				WideString wideName;
				if (kSuccess == conditionSet->GetName(wideName)) {
					PMString name;
					wideName.GetSystemString(&name);
					choices.push_back(name);
				}
			}
		}
	}
}


/* Populates the main popup menu for this snippet
*/
void _SnpRunnerManipulateConditionalText::PopulateIndicatorChoices(K2Vector<PMString>& choices) const
{
	choices.clear();

	const K2Vector<PMString>& names = fSnippetInstance.QueryConditionIndicatorMethodNames();
	for (K2Vector<PMString>::const_iterator iter = names.begin(); iter != names.end(); ++iter)
	{
		choices.push_back(*iter);
	}	
}


/* Populates the main popup menu for this snippet
*/
void _SnpRunnerManipulateConditionalText::PopulateAppearanceChoices(K2Vector<PMString>& choices) const
{
	const K2Vector<PMString>& names = fSnippetInstance.QueryConditionIndicatorAppearanceNames();

	choices.clear();
	for (K2Vector<PMString>::const_iterator iter = names.begin(); iter != names.end(); ++iter)
	{
		choices.push_back(*iter);
	}
}


/* Populates the main popup menu for this snippet
*/
void _SnpRunnerManipulateConditionalText::PopulateShowIndicatorsModeChoices(K2Vector<PMString>& choices) const
{
	const K2Vector<PMString>& names = fSnippetInstance.QueryShowIndicatorsModeNames();

	choices.clear();
	for (K2Vector<PMString>::const_iterator iter = names.begin(); iter != names.end(); ++iter)
	{
		choices.push_back(*iter);
	}
}


/* Populates the main popup menu for this snippet
*/
void _SnpRunnerManipulateConditionalText::PopulateActionChoices(ISnpRunnableContext* runnableContext, IActiveContext* ac, K2Vector<int32>& menuItemEnums, K2Vector<PMString>& menuItemNames)
{
	menuItemNames.clear();
	menuItemEnums.clear();


	// general items...
	menuItemEnums.push_back(en_ListAllConditions);
	menuItemEnums.push_back(en_ListAllConditionSets);
	menuItemEnums.push_back(en_ListActiveConditions);
	menuItemEnums.push_back(en_ListActiveConditionSets);
	menuItemEnums.push_back(en_LoadConditions);
	menuItemEnums.push_back(en_ShowConditionIndicators);
	
	// general condition items...
	menuItemEnums.push_back(en_CreateConditionDefault);
	menuItemEnums.push_back(en_CreateConditionUser);

	// items requiring the existence of a Condition...
	InterfacePtr<IConditionTagList> conditionList(Utils<IConditionalTextFacade>()->QueryActiveConditionList(ac));
	if (conditionList && conditionList->GetCount() > 0) 
	{
		menuItemEnums.push_back(en_DeleteCondition);
		menuItemEnums.push_back(en_SetConditionOptions);
		menuItemEnums.push_back(en_SetConditionName);
		menuItemEnums.push_back(en_SetConditionVisible);
		menuItemEnums.push_back(en_SetConditionColor);
		menuItemEnums.push_back(en_SetConditionMethod);
		menuItemEnums.push_back(en_SetConditionAppearance);
		
		// items requiring the existence of a textTarget...

		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if( textTarget ) 
		{
			InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
			if (textModel != nil && textModel->TotalLength() > 1)
			{
				menuItemEnums.push_back(en_ApplyCondition);
				menuItemEnums.push_back(en_RemoveCondition);
				menuItemEnums.push_back(en_ListAppliedConditions);
			}
		}
	}
	
	// general ConditionSet items...
	menuItemEnums.push_back(en_CreateConditionSet);

	// items requiring the existence of a ConditionSet...
	InterfacePtr<IConditionTagSetList> setList(Utils<Facade::IConditionalTextFacade>()->QueryActiveConditionSetList(ac));
	if (setList && setList->GetCount() > 0)
	{
		menuItemEnums.push_back(en_DeleteConditionSet);
		menuItemEnums.push_back(en_SetActiveConditionSet);
		menuItemEnums.push_back(en_SetConditionSetName);
		
		UID activeSetUID;
		ErrorCode err = Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(ac->GetContextWorkspace(), activeSetUID);
		if (kSuccess == err && kInvalidUID != activeSetUID) {
			menuItemEnums.push_back(en_ShowAllConditionsInActiveSet);
			menuItemEnums.push_back(en_RedefineActiveConditionSet);
		}
	}


	// transfer the strings for the current menu items into the menuItemNames vector
	for (int32 i = 0; i < menuItemEnums.size(); i++)
	{
		menuItemNames.push_back((fMenuValuesMap.find(menuItemEnums[i]))->second);
	}

	
}



/* Populates the main popup menu for this snippet
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestBoolean(const PMString& prompt, bool16& boolValue) const
{
	ErrorCode err = kFailure;

	K2Vector<PMString> boolChoices;
	boolChoices.push_back("kTrue");		// choice index 0
	boolChoices.push_back("kFalse");	// choice index 1

	Utils<ISnipRunParameterUtils> parameterUtils;
	if (parameterUtils)
	{
		bool16 theBoolValue = parameterUtils->GetChoice(prompt, boolChoices, (boolValue ? 0 : 1)) == 0 ? kTrue : kFalse;
		if (parameterUtils->WasDialogCancelled())
		{
			err = kCancel;
		}
		else
		{
			boolValue = theBoolValue;
			err = kSuccess;
		}
	}
	return err;
}


/* Get information about the text target.
	sets start and end to the start and end values of the current text range
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestString(const PMString& prompt, WideString& stringValue) const
{
	ErrorCode err = kFailure;

	Utils<ISnipRunParameterUtils> parameterUtils;
	if (parameterUtils)
	{
		PMString theStringValue;
		stringValue.GetSystemString(&theStringValue);
		
		// request a new PMString from the user, showing the stringValue as a default
		theStringValue = parameterUtils->GetPMString(prompt, theStringValue);
		if (parameterUtils->WasDialogCancelled())
		{
			err = kCancel;
		}
		else
		{
			stringValue = WideString(theStringValue);
			err = kSuccess;
		}
	}
	return err;
}


/* Get information about the text target.
	sets start and end to the start and end values of the current text range
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestString(const PMString& prompt, PMString& stringValue) const
{
	ErrorCode err = kFailure;

	Utils<ISnipRunParameterUtils> parameterUtils;
	if (parameterUtils)
	{
		PMString theStringValue(stringValue);
		
		// request a new PMString from the user, showing the stringValue as a default
		theStringValue = parameterUtils->GetPMString(prompt, theStringValue);
		if (parameterUtils->WasDialogCancelled())
		{
			err = kCancel;
		}
		else
		{
			stringValue = theStringValue;
			err = kSuccess;
		}
	}
	return err;
}


/*  Request the indicator method from the user
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestMethodChoice(IConditionTag::IndicatorMethod& method) const
{
	ErrorCode err = kFailure;
	
	// create a popup list of actions to choose from
	K2Vector<PMString> choices;
	PopulateIndicatorChoices(choices);

	// display the dialog and get the user's Action choice
	Utils<ISnipRunParameterUtils> parameterUtils;
	int32 choice = parameterUtils->GetChoice(PMString("Choose an indicator method"), choices, static_cast<int32>(method));
	if (parameterUtils->WasDialogCancelled()) 
	{
		err = kCancel;
	}
	else
	{
		err = kSuccess;
		method = static_cast<IConditionTag::IndicatorMethod>(choice);
	}
	
	return err;
}


/*  Request the indicator method from the user
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestAppearanceChoice(IConditionTag::UnderlineIndicatorAppearance& appearance) const
{
	ErrorCode err = kFailure;
	
	// create a popup list of actions to choose from
	K2Vector<PMString> choices;
	PopulateAppearanceChoices(choices);

	// display the dialog and get the user's Action choice
	Utils<ISnipRunParameterUtils> parameterUtils;
	int32 choice = parameterUtils->GetChoice(PMString("Choose an indicator appearance"), choices, static_cast<int32>(appearance));
	if (parameterUtils->WasDialogCancelled()) 
	{
		err = kCancel;
	}
	else
	{
		err = kSuccess;
		appearance = static_cast<IConditionTag::UnderlineIndicatorAppearance>(choice);
	}
	
	return err;
}


/*  Request the show condition indicators mode from the user
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestShowIndicatorsMode(IConditionalTextOptions::ConditionIndicatorsMode& showIndicatorsMode) const
{
	ErrorCode err = kFailure;
	
	// create a popup list of actions to choose from
	K2Vector<PMString> choices;
	PopulateShowIndicatorsModeChoices(choices);

	// display the dialog and get the user's Action choice
	Utils<ISnipRunParameterUtils> parameterUtils;
	int32 choice = parameterUtils->GetChoice(PMString("Choose show condition indicators mode"), choices, static_cast<int32>(showIndicatorsMode));
	if (parameterUtils->WasDialogCancelled()) 
	{
		err = kCancel;
	}
	else
	{
		err = kSuccess;
		showIndicatorsMode = static_cast<IConditionalTextOptions::ConditionIndicatorsMode>(choice);
	}
	
	return err;
}


/* Show color selection dialog to user, and return UID of selected color.
	if doc is nil, colors are from application
	if color contains a valid UID (not kInvalidUID), the color's index is selected as the default
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestColorChoice(const IWorkspace* ws, UID& color) const
{
	ErrorCode err = kFailure;

	ASSERT(ws);
	if (ws)
	{
		// if doc is nil, GetUIColorIndex will use the app's color list instead
		InterfacePtr<IDocument> doc(::GetDataBase(ws), ::GetDataBase(ws)->GetRootUID(), IID_IDOCUMENT);
		
		// build a list of ui colors
		K2Vector<PMString> colorChoices;
		int32 numColors = Utils<IUIColorUtils>()->GetUIColorNum();
		for (int32 i = 0; i < numColors; i++) {
			colorChoices.push_back(Utils<IUIColorUtils>()->GetUIColorName(i));
		}
		
		// show the "color" dialog to the user
		int32 colorIndex = (color == kInvalidUID) ? 0 : Utils<IUIColorUtils>()->GetUIColorIndex(color, doc);		// calculate default color index
		Utils<ISnipRunParameterUtils> parameterUtils;
		if (parameterUtils)
		{
			colorIndex = parameterUtils->GetChoice(PMString("Choose new color"), colorChoices, colorIndex);
			if (parameterUtils->WasDialogCancelled()) 
			{
				err = kCancel;
			}
			else
			{
				color = Utils<IUIColorUtils>()->GetUIColor(colorIndex, doc).GetUID();
				err = kSuccess;
			}
		}
	}
	return err;
}



/* Allow the user to select a condition from a list of the active condition names
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestConditionChoice(const PMString& prompt, IActiveContext* ac, UIDRef& conditionRef, bool16 allowNone, const PMString* nonePrompt) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			IDataBase* db = ::GetDataBase(ws);
			ASSERT(db);
			if (db)
			{
				InterfacePtr<IConditionTagList> conditionList(Utils<IConditionalTextFacade>()->QueryActiveConditionList(ac));
				ASSERT(conditionList);
				if (conditionList)
				{
					K2Vector<PMString> names;
					PopulateConditionNameChoices(conditionList, db, names);
					
					if (allowNone)
					{
						PMString noneString("<none>");
						if (nonePrompt != nil) {
							noneString = *nonePrompt;
						}
						names.insert(names.begin(), noneString);			// add <none>
					}

					// display the "choose condition" dialog
					Utils<ISnipRunParameterUtils> parameterUtils;
					int32 index = parameterUtils->GetChoice(prompt, names);
					if (!parameterUtils->WasDialogCancelled()) 
					{
						if (allowNone && index == 0) {
							conditionRef = UIDRef(nil, kInvalidUID);
						} else {
							if (allowNone){
								index--;
							}
							UID conditionUID = conditionList->GetNthCondition(index);
							conditionRef = UIDRef(db, conditionUID);
						}
						err = kSuccess;
					}
					else
					{
						err = kCancel;
					}
				}
			}
		}
	}
	
	return err;
}


/* Allow the user to select a condition from a list of the active condition names
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestConditionSetChoice(const PMString& prompt, IActiveContext* ac, UIDRef& setRef) const
{
	ErrorCode err = kFailure;
		
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			IDataBase* db = ::GetDataBase(ws);
			ASSERT(db);
			if (db)
			{
				InterfacePtr<IConditionTagSetList> setList(Utils<IConditionalTextFacade>()->QueryActiveConditionSetList(ac));
				ASSERT(setList);
				if (setList)
				{
					K2Vector<PMString> names;
					PopulateConditionSetNameChoices(setList, db, names);

					// display the "choose condition" dialog
					Utils<ISnipRunParameterUtils> parameterUtils;
					int32 index = parameterUtils->GetChoice(prompt, names);
					if (!parameterUtils->WasDialogCancelled()) 
					{
						UID setUID = setList->GetNthSet(index);
						setRef = UIDRef(db, setUID);
						err = kSuccess;
					}
					else
					{
						err = kCancel;
					}
				}
			}
		}
	}
	return err;
}





/* Gather the information necessary to create a condition from the user, then create the condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::RequestConditionOptions(IActiveContext* ac,
								WideString& name, 
								bool16& visible,
								UID& color,
								IConditionTag::IndicatorMethod& method, 
								IConditionTag::UnderlineIndicatorAppearance& appearance) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			// request the "name" 
			err = RequestString(PMString("Enter Condition name"), name);

			// request the "visibility" 
			if (kSuccess == err) {
				err = RequestBoolean(PMString("Choose visibility setting"), visible);
			}
			// request the "color" 
			if (kSuccess == err) {
				err = RequestColorChoice(ws, color);
			}
			// request "indicator method" 
			if (kSuccess == err) {
				err = RequestMethodChoice(method);
			}
			// request "indicator appearance" - if method chosen is not kHighlight
			if (kSuccess == err && method != IConditionTag::kHighlight) {
				err = RequestAppearanceChoice(appearance);
			}
		}
	}
	return err;
}



/* Gather the information necessary to create a condition from the user, then create the condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleCreateCondition(IActiveContext* ac) const
{
	ErrorCode err = kFailure;

	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			WideString name;
			Utils<Facade::IConditionalTextFacade>()->GetFirstAvailableDefaultConditionName(ws, name);
			bool16 visible = kTrue;
			UID color;
			Utils<Facade::IConditionalTextFacade>()->GetNextDefaultConditionColor(ws, color);
			IConditionTag::IndicatorMethod method = IConditionTag::kUnderline;
			IConditionTag::UnderlineIndicatorAppearance appearance = IConditionTag::kSingleWavy;

			// get user input for options values
			err = RequestConditionOptions(ac, name, visible, color, method, appearance);
			if (kSuccess == err)
			{
				// create the condition
				UID newConditionUID;
				err = fSnippetInstance.CreateCondition(ws, name, color, method, appearance, visible, &newConditionUID);
			}	
		}
	}

	return err;
}



/* Gather the information necessary to create a condition from the user, then create the condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionOptions(IActiveContext* ac) const
{
	UIDRef conditionRef;
	ErrorCode err = RequestConditionChoice(PMString("Choose condition to modify"), ac, conditionRef);
	if (kSuccess == err) 
	{
		WideString name;
		bool16 visible;			// not set in GetConditionOptions, use GetConditionVisibleState instead
		UID color;
		IConditionTag::IndicatorMethod method;
		IConditionTag::UnderlineIndicatorAppearance appearance;
		
		// get the current information on the tag so default values can be set in the request dialogs
		err = Utils<Facade::IConditionalTextFacade>()->GetConditionVisibleState(conditionRef, visible);
		if (kSuccess == err) 
		{
			err = Utils<Facade::IConditionalTextFacade>()->GetConditionOptions(conditionRef, name, color, method, appearance);
			if (kSuccess == err) 
			{
				// get user input for options values
				err = RequestConditionOptions(ac, name, visible, color, method, appearance);
				if (kSuccess == err) 
				{
					// modify the condition accordingly
					err = fSnippetInstance.SetConditionOptions(conditionRef, name, color, method, appearance, visible);
				}
			}
		}
	}
	return err;
}


/* Request whether to hide or show condition indicators
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleShowConditionIndicators(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			InterfacePtr<IConditionalTextOptions> options(ws, UseDefaultIID());
			ASSERT(options);
			if (options)
			{
				IConditionalTextOptions::ConditionIndicatorsMode showIndicatorsMode = options->GetShowConditionIndicators();
				err = RequestShowIndicatorsMode(showIndicatorsMode);
				if (kSuccess == err) {
					err = fSnippetInstance.SetShowConditionIndicators(ws, showIndicatorsMode);
				}
			}
		}
	}
	return err;
}


/* Request an indesign file for the user to load conditions from
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleLoadConditions(IActiveContext* ac) const
{
	ErrorCode err = kCancel;

	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			// Browse for a document
			SDKFileDocumentChooser fileChooser;
			fileChooser.ShowDialog();
			if (fileChooser.IsChosen()) 
			{
				IDFile chosenFile = fileChooser.GetIDFile();
				
				bool16 doLoadSets = kFalse;
				err = RequestBoolean(PMString("Load Sets?"), doLoadSets);
				if (kSuccess == err) {
					err = fSnippetInstance.LoadConditions(ws, chosenFile, doLoadSets);
				}
			}
		}
	}
	return err;
}



/* Ask user which condition to delete, and which condition to replace it with (none or existing condition), then delete the condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleDeleteCondition(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	Utils<ISnipRunParameterUtils> parameterUtils;

	UIDRef conditionRef;
	err = RequestConditionChoice(PMString("Choose condition to delete"), ac, conditionRef);
	if (kSuccess == err) 
	{		
		UIDRef replacementRef;
		err = RequestConditionChoice(PMString("Choose replacement condition"), ac, replacementRef, kTrue);
		if (kSuccess == err) 
		{		
			// attempt to delete the tag
			err = fSnippetInstance.DeleteCondition(conditionRef, replacementRef);
		}
	}
	return err;
}


/* Allow user to choose a new name for a condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionName(IActiveContext* ac) const
{
	UIDRef conditionRef;
	ErrorCode err = RequestConditionChoice(PMString("Choose condition to modify"), ac, conditionRef);
	if (kSuccess == err) 
	{
		PMString newName;
		err = RequestString(PMString("Enter new Condition name"), newName);
		if (kSuccess == err) {
			err = fSnippetInstance.SetConditionName(conditionRef, newName);
		}
	}
	return err;
}


/* Allow user to choose a new name for a condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionVisibility(IActiveContext* ac) const
{
	UIDRef conditionRef;
	ErrorCode err = RequestConditionChoice(PMString("Choose condition to modify"), ac, conditionRef);
	if (kSuccess == err) 
	{
		bool16 visible;
		err = Utils<Facade::IConditionalTextFacade>()->GetConditionVisibleState(conditionRef, visible);
		if (kSuccess == err)
		{
			err = RequestBoolean(PMString("Show Condition?"), visible);
			if (kSuccess == err) {
				err = fSnippetInstance.SetConditionVisibleState(conditionRef, visible);
			}
		}
	}
	return err;
}


/* Allow user to choose a new name for a condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionColor(IActiveContext* ac) const
{
	UIDRef conditionRef;
	ErrorCode err = RequestConditionChoice(PMString("Choose condition to modify"), ac, conditionRef);
	if (kSuccess == err) 
	{
		UID color;
		err = Utils<Facade::IConditionalTextFacade>()->GetConditionColor(conditionRef, color);
		if (kSuccess == err) 
		{
			// display the "choose color" dialog and get the user's choice
			InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
			if (kSuccess == RequestColorChoice(ws, color)) {
				err = fSnippetInstance.SetConditionColor(conditionRef, color);
			}
		}
	}
	return err;
}


/* Allow user to choose an indicator method for a condition
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionMethod(IActiveContext* ac) const
{
	UIDRef conditionRef;
	ErrorCode err = RequestConditionChoice(PMString("Choose condition to modify"), ac, conditionRef);
	if (kSuccess == err) 
	{
		IConditionTag::IndicatorMethod method;
		err = Utils<Facade::IConditionalTextFacade>()->GetConditionMethod(conditionRef, method);
		if (kSuccess == err)
		{
			err = RequestMethodChoice(method);
			if (kSuccess == err) {
				err = fSnippetInstance.SetConditionMethod(conditionRef, method);
			}
		}
	}
	return err;
}



/* Allow user to choose an indicator appearance for a condition
		NOTE:  This dialog will display even if the Condition uses kHighlight for its method
			   in which case, nothing will change visibly.
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionAppearance(IActiveContext* ac) const
{
	UIDRef conditionRef;
	ErrorCode err = RequestConditionChoice(PMString("Choose condition to modify"), ac, conditionRef);
	if (kSuccess == err) 
	{
		IConditionTag::UnderlineIndicatorAppearance appearance;
		err = Utils<Facade::IConditionalTextFacade>()->GetConditionAppearance(conditionRef, appearance);
		if (kSuccess == err)
		{
			err = RequestAppearanceChoice(appearance);
			if (kSuccess == err) {
				err = fSnippetInstance.SetConditionAppearance(conditionRef, appearance);
			}
		}
	}
	return err;
}


/* Allow user to choose a condition to apply to the active text
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleApplyCondition(ISnpRunnableContext* rc) const
{
	ErrorCode err = kFailure;
	
	InterfacePtr<ITextTarget> textTarget(rc, UseDefaultIID());
	if (textTarget)
	{
		UIDRef conditionRef;
		err = RequestConditionChoice(PMString("Choose condition to apply"), rc->GetActiveContext(), conditionRef);
		if (kSuccess == err) 
		{	
			// request "remove existing conditions"
			bool16 removeExisting = kFalse;
			err = RequestBoolean(PMString("Remove existing conditions?"), removeExisting); 
			if (kSuccess == err)
			{
				// set up the text range info
				RangeData rangeData(0, 1);
				err = GetTextRange(textTarget, rangeData);
				if (kSuccess == err) 
				{
					// attempt to apply the tag to the selected text
					InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
					
					K2Vector<UID> conditionsToApply;
					conditionsToApply.push_back(conditionRef.GetUID());

					err = fSnippetInstance.ApplyConditions(::GetUIDRef(textModel), rangeData, conditionsToApply, removeExisting);
				}
			}
		}
	}
	return err;
}

/* Allow user to remove a condition to apply to the active text
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleRemoveCondition(ISnpRunnableContext* rc) const
{
	ErrorCode err = kFailure;
	
	InterfacePtr<ITextTarget> textTarget(rc, UseDefaultIID());
	if (textTarget)
	{
		UIDRef conditionRef;
		PMString all("<All>");
		err = RequestConditionChoice(PMString("Choose condition to remove from text"), rc->GetActiveContext(), conditionRef, kTrue, &all);
		if (kSuccess == err) 
		{	
			// set up the text range info
			RangeData rangeData(0, 1);
			err = GetTextRange(textTarget, rangeData);
			if (kSuccess == err) 
			{
				// attempt to apply the tag to the selected text
				InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
				
				K2Vector<UID> conditionsToRemove;
				conditionsToRemove.push_back(conditionRef.GetUID());

				err = fSnippetInstance.RemoveConditionTags(::GetUIDRef(textModel), rangeData, conditionsToRemove, conditionRef.GetUID() == kInvalidUID);
			}
		}
	}
	return err;
}


/* Allow user to choose a condition to apply to the active text
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleListAppliedConditions(ISnpRunnableContext* rc) const
{
	ErrorCode err = kFailure;
	
	InterfacePtr<ITextTarget> textTarget(rc, UseDefaultIID());
	if (textTarget)
	{
		RangeData rangeData(0, 1);
		err = GetTextRange(textTarget, rangeData);
		if (kSuccess == err) 
		{
			InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
			err = fSnippetInstance.ListAppliedConditionTags(::GetUIDRef(textModel), rangeData);
		}
	}
	return err;
}


/* Create a condition set, allowing user to choose name
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleCreateConditionSet(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			WideString name;
			Utils<Facade::IConditionalTextFacade>()->GetFirstAvailableDefaultConditionSetName(ws, name);

			// get user input for name value
			err = RequestString(PMString("Enter Condition Set name"), name);
			if (kSuccess == err)
			{
				// create the condition set
				UID newSetUID;
				err = fSnippetInstance.CreateConditionSet(ws, name, &newSetUID);
			}	
		}
	}
	return err;
}

	
/* Choose to either show or hide all condition sets
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleShowAllConditionsInActiveSet(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			bool16 show = kFalse;
			if (kSuccess == RequestBoolean(PMString("Choose doShow parameter."), show)) {
				err = fSnippetInstance.ShowAllConditionsInActiveSet(ws, show);
			}
		}
	}
	return err;
}

	
/* Choose a condition set to delete
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleDeleteConditionSet(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	UIDRef setRef;
	err = RequestConditionSetChoice(PMString("Choose condition set to delete"), ac, setRef);
	if (kSuccess == err) 
	{
		err = fSnippetInstance.DeleteConditionSet(setRef);
	}

	return err;
}
	

	
/* Change the active condition set to one the user specifies
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleSetActiveConditionSet(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			UIDRef setRef;
			err = RequestConditionSetChoice(PMString("Choose condition set to make active"), ac, setRef);
			if (kSuccess == err) 
			{
				err = fSnippetInstance.SetActiveConditionSet(ws, setRef);
			}
		}
	}
	return err;
}
	

	
/* Change the name of a condition set
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleModifyConditionSetName(IActiveContext* ac) const
{
	ErrorCode err = kFailure;

	UIDRef setRef;
	err = RequestConditionSetChoice(PMString("Choose condition set to modify"), ac, setRef);
	if (kSuccess == err) 
	{
		WideString newName;
		err = RequestString(PMString("Enter new Condition Set name"), newName);
		if (kSuccess == err)
		{
			// change name of condition set
			err = fSnippetInstance.ModifyConditionSetName(setRef, newName);
		}
	}
	
	return err;
}

	
/* redefine a condition set to contain all the currently visible conditions
*/
ErrorCode _SnpRunnerManipulateConditionalText::HandleRedefineActiveConditionSet(IActiveContext* ac) const
{
	ErrorCode err = kFailure;
	
	ASSERT(ac);
	if (ac)
	{
		InterfacePtr<IWorkspace> ws(ac->GetContextWorkspace(), UseDefaultIID());
		ASSERT(ws);
		if (ws) 
		{
			err = fSnippetInstance.RedefineActiveConditionSet(ws);
		}
	}
	return err;
}


/* Get information about the text target.
	sets start and end to the start and end values of the current text range
*/
ErrorCode _SnpRunnerManipulateConditionalText::GetTextRange(ITextTarget* textTarget, RangeData& rangeData) const
{
	ErrorCode err = kFailure;
	
	ASSERT(textTarget);
	if (textTarget != nil) 
	{
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus != nil) 
		{
			err = kSuccess;
			rangeData = textFocus->GetCurrentRange();
		}
	}
	return err;
}





/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateConditionalText instance_SnpRunnerManipulateConditionalText;
DEFINE_SNIPPET(_SnpRunnerManipulateConditionalText) 	



