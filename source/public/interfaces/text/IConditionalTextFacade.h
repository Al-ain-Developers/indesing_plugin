//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionalTextFacade.h $
//  
//  Owner: Michele Stutzman
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

#pragma once
#ifndef __ICONDITIONALTEXTFACADE__
#define __ICONDITIONALTEXTFACADE__

#include "ConditionalTextID.h"
#include "IConditionTag.h"
#include "IConditionalTextOptions.h"
#include "RangeData.h"
#include "Utils.h"

class IConditionTagList;
class IConditionTagSetList;
class IWorkspace;

namespace Facade
{
	/** The IConditionalTextFacade provides high-level access to conditions, condition sets 
		and conditional text operations.  Please use the IConditionalTextFacade directly via the UtilsBoss
		if possible, see Utils.h:
		Utils<Facade::IConditionalTextFacade>()->method( params,... );

		Conditions are UID based objects that have a name, drawing options, and visibility sate.
		They are maintained in a list on the application and document workspaces respectively.
		They can be applied to text ranges and are represented as a style override, 
		see @IAttrReport for kConditionalTextAttributeBoss.  Multiple conditions may be applied to the
		same text.
		
		When a condition's visible state is changed to false, text with that condition applied is hidden
		if there are no other conditions applied that are visible.  Likewise, when a condition's visible
		state is change to true, hidden text with that condition applied is shown.  Hidden text is not
		searchable.

		Condition sets are UID based objects that capture visibility states for each condition.  These
		are maintained in lists on the application and document workspaces.  Visibilities for condition(s)
		created after a set is created do not change when a set is made active.  A set may be redefined to
		capture the visibilites for those conditions.

		Settings for conditional text options that are maintained at the document and application workspace
		include	show/hide condition indicators on the text and the active set.
	*/
	class IConditionalTextFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ICONDITIONALTEXTFACADE };

		/**	Creates a new condition on the workspace provided with the options and visible state specified.
			@param ws IN Workspace where to create the condition.
			@param newConditionUID OUT The UID of newly created condition if successful.
			@param name IN The name of the new condition. If empty, uses next available name (i.e. Condition 1, Condition 2) 
			@param colorUID IN The UID of the color for the new condition. If kInvalidUID, uses next available color.
			@param method IN The indicator method.
			@param appearance IN The underline indicator appearance.
			@param visibleState IN The visiblity for the new condition.
			@return ErrorCode kSuccess if the condition was created successfully.
		*/
		virtual ErrorCode CreateCondition(IWorkspace* ws, 
								UID* newConditionUID = nil,
								const WideString& name = WideString(""), 
								UID colorUID = kInvalidUID, 
								IConditionTag::IndicatorMethod method = IConditionTag::kUnderline, 
								IConditionTag::UnderlineIndicatorAppearance appearance = IConditionTag::kSingleWavy,
								bool16 visibleState = kTrue) = 0;

		/**	Deletes a condition on the workspace provided and replace with the specified conditon (if any).
			@param conditionsToDelete IN A UIDList of conditions to delete.
			@param conditionToReplaceWith IN The UID of the condition to replace with.
			@return ErrorCode kSuccess if the condition was deleted successfully.
		*/
		virtual ErrorCode DeleteConditions(const UIDList& conditionsToDelete, UID conditionToReplaceWith = kInvalidUID) = 0;

		/**	Sets the name for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition to edit.
			@param name IN The new name condition.
			@return ErrorCode kSuccess if the condition was edited successfully.
		*/
		virtual ErrorCode SetConditionName(const UIDRef& conditionRef, const WideString& name) = 0;

		/**	Gets the name for a condition on the workspace provided.
			@param ws IN Workspace where to find the condition.
			@param conditionRef IN The UIDRef of the condition.
			@param name OUT The name condition.
			@return ErrorCode kSuccess if the get value successfully.
		*/
		virtual ErrorCode GetConditionName(const UIDRef& conditionRef, WideString& name) const = 0;

		/**	Sets the color for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition to edit.
			@param colorUID IN The new color UID for the condition.
			@return ErrorCode kSuccess if the condition was edited successfully.
		*/
		virtual ErrorCode SetConditionColor(const UIDRef& conditionRef, UID colorUID) = 0;

		/**	Gets the color for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition.
			@param colorUID OUT The color UID for the condition.
			@return ErrorCode kSuccess if the get value successfully.
		*/
		virtual ErrorCode GetConditionColor(const UIDRef& conditionRef, UID& colorUID) const = 0;

		/**	Sets the indicator method for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition to edit.
			@param newMethod IN The new indicator method for the condition.
			@return ErrorCode kSuccess if the condition was edited successfully.
		*/
		virtual ErrorCode SetConditionMethod(const UIDRef& conditionRef, IConditionTag::IndicatorMethod newMethod) = 0;

		/**	Gets the indicator method for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition.
			@param method OUT The indicator method for the condition.
			@return ErrorCode kSuccess if the get value successfully.
		*/
		virtual ErrorCode GetConditionMethod(const UIDRef& conditionRef, IConditionTag::IndicatorMethod& method) const = 0;

		/**	Sets the color for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition to edit.
			@param newAppearance IN The new underline indicator appearance for the condition.
			@return ErrorCode kSuccess if the condition was edited successfully.
		*/
		virtual ErrorCode SetConditionAppearance(const UIDRef& conditionRef, IConditionTag::UnderlineIndicatorAppearance newAppearance) = 0;

		/**	Gets the color for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition.
			@param appearance OUT The new underline indicator appearance for the condition.
			@return ErrorCode kSuccess if the get value successfully.
		*/
		virtual ErrorCode GetConditionAppearance(const UIDRef& conditionRef, IConditionTag::UnderlineIndicatorAppearance& appearance) const = 0;

		/**	Sets the options for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition to edit.
			@param newName IN The new name condition.
			@param newColorUID IN The new color UID for the condition.
			@param newMethod IN The new indicator method for the condition.
			@param newAppearance IN The new underline indicator appearance for the condition.
			@return ErrorCode kSuccess if the condition was edited successfully.
		*/
		virtual ErrorCode SetConditionOptions(const UIDRef& conditionRef, 
								const WideString& newName, 
								UID newColorUID,
								IConditionTag::IndicatorMethod newMethod, 
								IConditionTag::UnderlineIndicatorAppearance newAppearance) = 0;

		/**	Gets the options for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition.
			@param name IN The name for the condition.
			@param colorUID IN The color UID for the condition.
			@parammethod IN The indicator method for the condition.
			@param appearance IN The underline indicator appearance for the condition.
			@return ErrorCode kSuccess if the get was successfully.
		*/
		virtual ErrorCode GetConditionOptions(const UIDRef& conditionRef,
								WideString& name, 
								UID& colorUID,
								IConditionTag::IndicatorMethod& method, 
								IConditionTag::UnderlineIndicatorAppearance& appearance) const = 0;

		/**	Sets the visible state for a condition on the workspace provided. Will hide or show conditional text appropriately.
			@param conditionRef IN The UIDRef of the condition to edit.
			@param visibleState IN The new visible state for the condition; kTrue to show or kFalse to hide.
			@return ErrorCode kSuccess if the condition was edited successfully.
		*/
		virtual ErrorCode SetConditionVisibleState(const UIDRef& conditionRef, bool16 visibleState) = 0;

		/**	Gets the visible state for a condition on the workspace provided.
			@param conditionRef IN The UIDRef of the condition.
			@param visibleState OUT The visible state for the condition.
			@return ErrorCode kSuccess if the get value successfully.
		*/
		virtual ErrorCode GetConditionVisibleState(const UIDRef& conditionRef, bool16& visibleState) const = 0;

		/**	Apply the condition to the specified text range.  Conditions already applied are replaced unless
			otherwise specified.  All applied conditions can be removed by passing an empty list of condition UIDs.
			@param textModelRef IN The text model containing the text to apply the condition.
			@param start IN The text index for the start of the text range.
			@param len IN The length of the text range.
			@param conditionsToApply IN The list of condition UIDs to apply to the text range.
			@param removeExisting IN Whether or not conditions already applied are removed.
			@return ErrorCode kSuccess if the condition(s) were applied successfully.
		*/
		virtual ErrorCode ApplyConditionsToText(const UIDRef& textModelRef, TextIndex start, int32 len, const K2Vector<UID>& conditionsToApply, bool16 removeExisting = kFalse) = 0;
	
		/**	Remove the specified conditions from the specified text range.
			@param textModelRef IN The text model containing the text to apply the condition.
			@param start IN The text index for the start of the text range.
			@param len IN The length of the text range.
			@param conditionsToUnapply IN The list of condition UIDs to remove from the text range.
			@return ErrorCode kSuccess if the condition(s) were applied successfully.
		*/
		virtual ErrorCode RemoveConditionsFromText(const UIDRef& textModelRef, TextIndex start, int32 len, const K2Vector<UID>& conditionsToRemove) = 0;

		/** Get the condition(s) applied at startPosition. Will join runs when this attribute is unchanged until endPosition.
			See kConditionalTextAttributeBoss.
			@param textModelRef IN The text model to examine.
			@param startPosition IN The initial text location to start from.
			@param endPosition IN The text location to not bother looking beyond.
			@param length OUT A pointer to value that will contain the number of characters after startPosition that share the same attribute value.
			@return K2Vector<UID> The list of condition UIDs that are applied.
		*/
		virtual K2Vector<UID> GetAppliedConditions(const UIDRef& textModelRef, TextIndex startPosition, TextIndex endPosition, int32 *length = nil) = 0;

		/** Get the condition(s) applied for the range of text specified and return them in the specified lists.
			See kConditionalTextAttributeBoss.
			@param textModelRef IN The text model to examine.
			@param rangeData IN The range to get applied conditions for.
			@param appliedToAllChars OUT The conditions applied to all of the characters in the range specified.
			@param appliedToSomeChars OUT The conditions applied to some of the characters in the range specified.
			@param rangeHasUnconditionalChars OUT A pointer to bool for whether or not the range has characters that are unconditional.
			@return ErrorCode kSuccess unless an error occurred.
		*/
		virtual ErrorCode GetAppliedConditions(const UIDRef& textModelRef, const RangeData& rangeData, UIDList& appliedToAllChars, UIDList& appliedToSomeChars, bool16* rangeHasUnconditionalChars = nil) = 0;

		/**	Returns the first available default condition name (Condition 1, Condition 2, etc) on the workspace 
			provided.  This name is unique with respect to existing conditions' names and can be used to create 
			a new condition with out conflict.
			@param ws IN Workspace where to create the condition.
			@param newName OUT The unique name generated.
		*/
		virtual void GetFirstAvailableDefaultConditionName(IWorkspace* ws, WideString& newName) = 0;

		/**	Returns the next default color to use for a new condition on the workspace provided. 
			See @IUIColorUtils.
			@param ws IN Workspace where to create the condition.
			@param colorUID OUT The color UID for the condition.
		*/
		virtual void GetNextDefaultConditionColor(IWorkspace* ws, UID& newColor) = 0;
		
		/**	Find the uid of a condition by the name.
			@param ws IN Workspace to get the name of the uid from.
			@param name IN name of the to find.
			@param conditionUID OUT The UID of the condition matching the name passed in.
			@return ErrorCode kSuccess if the condition was found successfully.
		*/
		virtual ErrorCode FindCondition(IWorkspace* ws, const WideString& name, UID& conditionUID) = 0;

		/** Query for the list of conditions in the specified active context.
			@param ac IN The active context to use.
			@return IConditionTagList* The condition list associated with the context.
			@see IConditionTagList
		*/
		virtual IConditionTagList* QueryActiveConditionList(IActiveContext* ac) = 0;

		/** Query for the list of conditions for the given database.
			@param db IN The database to use.
			@return IConditionTagList* The condition list associated with the database.
			@see IConditionTagList
		*/
		virtual IConditionTagList* QueryConditionList(IDataBase* db) = 0;

		/** Set the conditional text option for show condition indicators on the workspace provided.
			@param ws IN Workspace where to set the option.
			@param showIndicatorsMode IN The new setting for the show condition indications option.
			@return ErrorCode kSuccess if the option was edited successfully.
			@see IConditionalTextOptions::ConditionIndicatorsMode
		*/
		virtual ErrorCode SetShowConditionIndicators(IWorkspace* ws, IConditionalTextOptions::ConditionIndicatorsMode showIndicatorsMode) = 0;

		/** Shows or hides all of the conditions in the specified workspace based on the specified flag.
			@param ws IN Workspace containing the conditions to show/hide.
			@param showConditions IN The new setting for the conditions visible states; kTrue to show or kFalse to hide.
			@return ErrorCode kSuccess if the conditions visible states were edited successfully.
		*/
		virtual ErrorCode ShowAllConditions(IWorkspace* ws, bool16 showConditions) = 0;

		/**	Loads the conditions into the specified workspace from the specified file.  Optionally, loads the condition sets.
			@param ws IN Workspace to load the conditions and optionally the sets to.
			@param sourceFile IN The file to load the conditions from.
			@param loadConditionSets IN If kTrue then loads the condition sets; otherwise, only loads the conditions.
			@return ErrorCode kSuccess if the conditions' visible states were edited successfully.
		*/
		virtual ErrorCode LoadConditions(IWorkspace* ws, const IDFile& sourceFile, bool16 loadConditionSets) = 0;
		

		/** Typedef defining a condition set element, the first item in the pair is a UID of the condition and 
			second item is the condition's saved visible state. */
		typedef std::pair<UID, bool> ConditionSetElement;
		
		/** Typedef of a vector of ConditionSetElement(s). */
		typedef std::vector< ConditionSetElement > ConditionSetElementList;
		
		/**	Creates a new condition set on the workspace provided with the name specified.
			@param ws IN Workspace where to create the condition set.
			@param name IN The name of the new condition set.
			@param conditionSetElements IN A list of conditions and their visibility states to create a set from.
			@param newConditionSetUID OUT The UID of newly created condition set if successful.
			@return ErrorCode kSuccess if the condition set was created successfully.
		*/
		virtual ErrorCode CreateConditionSet(IWorkspace* ws, const WideString& name, const ConditionSetElementList &conditionSetElements, UID* newConditionSetUID) = 0;
	
		/**	Deletes a condition set on the workspace provided.
			@param conditionSetRef IN The UIDRef of the condition set to delete.
			@return ErrorCode kSuccess if the condition set was deleted successfully.
		*/
		virtual ErrorCode DeleteConditionSet(const UIDRef& conditionSetRef) = 0;
		
		/**	Get a uid list of all condition sets in a specific workspace
			@param ws IN Workspace where to get the set list from.
			@param conditionSets OUT A UIDList of sets.
			@return ErrorCode kSuccess if no errors were encountered getting the list otherwise an error code.
		*/		
		virtual ErrorCode GetAllConditionSets(IWorkspace* ws, UIDList *conditionSets) = 0;
		
		/**	Get the condition set currently applied to the workspace provided
			@param ws IN Workspace where to get the active set from.
			@param activeConditionSetUID OUT UID of the active condition set or kInvalidUID if no set is active.
			@return ErrorCode kSuccess if no errors were encountered getting the active condition set otherwise an error code.
		*/		
		virtual ErrorCode GetActiveConditionSet(IWorkspace* ws, UID &activeConditionSetUID) = 0;
		
		/**	Set the active condition set for the workspace.
			@param ws IN Workspace where to set the active condition set on.
			@param activeConditionSetUID IN UID of the condition set to activate.
			@return ErrorCode kSuccess if no errors were encountered setting the active condition set otherwise an error code.
		*/		
		virtual ErrorCode SetActiveConditionSet(IWorkspace* ws, UID activeConditionSetUID) = 0;
		
		/**	Given a single condition set uid this will return a list of all conditions within that set.
			@param conditionSetRef IN The UIDRef of the condition set to get individual conditions of.
			@param conditionSetElements OUT a list of conditions in the set and their associated visiblity states.
			@return ErrorCode kSuccess if no errors were encountered getting the conditions otherwise an error code.
		*/		
		virtual ErrorCode GetConditionsInConditionSet(const UIDRef& conditionSetRef, ConditionSetElementList &conditionSetElements) = 0;
		
		/**	Given a single condition set uid this redefines the list of conditions of the set.
			@param conditionSetRef IN The UIDRef of the condition set to set individual conditions for.
			@param conditionSetElements IN a list of conditions to set and their associated visiblity states.
			@return ErrorCode kSuccess if no errors were encountered setting the conditions otherwise an error code.
		*/		
		virtual ErrorCode RedefineConditionSet(const UIDRef& conditionSetRef, const ConditionSetElementList &conditionSetElements) = 0;

		/**	Sets the name for a condition set on the workspace provided.
			@param conditionSetRef IN The UIDRef of the condition set to edit.
			@param name IN The new name condition set.
			@return ErrorCode kSuccess if the condition set was edited successfully.
		*/
		virtual ErrorCode SetConditionSetName(const UIDRef& conditionSetRef, const WideString& name) = 0;
		
		/**	Sets the name for a condition set on the workspace provided.
			@param conditionSetRef IN The UIDRef of the condition set to get the name of.
			@param name OUT The name of the condition set.
			@return ErrorCode kSuccess if the condition set name was retrieved successfully.
		*/
		virtual ErrorCode GetConditionSetName(const UIDRef& conditionSetRef, WideString& name) = 0;
		
		/**	Find the uid of a condition set by the set name.
			@param ws IN Workspace to get the name of the condition set uid from.
			@param name IN name of the condition set to find.
			@param conditionSetUID OUT The UID of the condition set matching the name passed in.
			@return ErrorCode kSuccess if the condition set was retrieved successfully.
		*/
		virtual ErrorCode FindConditionSet(IWorkspace* ws, const WideString& name, UID &conditionSetUID) = 0;
		
		/**	Returns a default condition set name (Condition Set 1, Condition Set 2, etc) on the workspace provided that is unique.
			@param ws IN Workspace where to create the paragraph style.
			@param newName OUT The unique name generated.
		*/
		virtual ErrorCode GetFirstAvailableDefaultConditionSetName(IWorkspace* ws, WideString& newName) = 0;

		/** Query for the current active condition set list in the specified context.
			@param ac IN The active context to use.
			@return IConditionTagSetList* The condition set list associated with the context.
			@see IConditionTagSetList
		*/
		virtual IConditionTagSetList* QueryActiveConditionSetList(IActiveContext* ac) = 0;

		/**	Query for the condition set list of the given database.
			@param db IN The database to use.
			@return IConditionTagSetList* The condition set list associated with the database.
			@see IConditionTagSetList
		*/
		virtual IConditionTagSetList* QueryConditionSetList(IDataBase* db) = 0;

	}; // end IConditionalTextFacade interface
}
#endif // define __ICONDITIONALTEXTFACADE__

