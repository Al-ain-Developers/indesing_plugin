//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IAppearanceSuite.h $
//  
//  Owner: Tim Wright
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
#ifndef _IAppearanceSuite_
#define _IAppearanceSuite_

#include "FormFieldID.h"
#include "IAppearanceList.h"
#include "IAppearanceItemFacade.h"
#include "FormFieldTypes.h"
#include "BravoForwardDecl.h"

//================================================================================================

class IAppearanceList;
class ILibrary;
class AGMImageAccessor;

/** Selection suite for manipulating appearances on page items that have appearances (form fields
	This is currently implemented only for concrete selections (page items). There isn't
	a default selection suite for Appearances.
	
	This suite also doesn't operate on multiple selections.
	
	Most of these methods call through to IAppearanceList (GetActiveState, GetNthState, GetAppearance,
	HasAppearance, etc) or call an appearance state-related
	command (SetActiveState, NewState, DeleteState, RemoveAppearances, SetAppearanceStyle)
	
@see IAppearanceList
*/
class IAppearanceSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPEARANCESUITE };

	enum HowToAddStates { kAddItemsAsIndividualStates, kAddAllItemsToOneNewState, kAddItemsToActiveState };
	enum { kInvalidIndex = -1 };

	/** return active state of selection, kStateInvalid if selection doesn't have appearances or is multiple selection */
	virtual Form::AppearanceState GetActiveState() const = 0;
	
	/** Perform kChangeActiveStateCmdBoss command on the selection */
	virtual ErrorCode SetActiveState( Form::AppearanceState inState ) const = 0;

	/** Selects the group that wraps the active states of appearance items in the selection */
	virtual void SelectActiveState() const = 0;
	
	/** @return 'inStateIndexth' zero indexed state in selection. Useful for enumerating states.
				kStateInvalid if inStateIndex >= NumStates() */
	virtual Form::AppearanceState GetNthState( int32 inStateIndex ) const = 0;
	
	/** Get parameters for inState
		@param inState State to get
		@param outAppearance Points to inState appearance params on exit
	*/
	virtual bool16 GetAppearance(  Form::AppearanceState inState, Form::Appearance* outAppearance  ) const = 0;
	
	/** @return kTrue if inState is a valid appearance in the selection */
	virtual bool16 HasAppearance(  Form::AppearanceState inState ) const = 0;
	
	/** @return kTrue if inState has content in the selection */
	virtual bool16 HasAppearanceContent(  Form::AppearanceState inState ) const = 0;
	
	/** Change parameters for state inState
		@param inState State to change
		@param inNewState State to change it to (may be == inState)
		@param inAppearance New parameters for state
	*/
	virtual ErrorCode SetAppearance( Form::AppearanceState inState, Form::AppearanceState inNewState, const Form::Appearance& inAppearance  ) const = 0;
	
	/** Add a new state to selection
		@param inState State to add
		@param inPosition Position in the appearance list to add the state
	*/
	virtual ErrorCode NewState(  Form::AppearanceState inState, int32 inPosition = IAppearanceList::kLastInOrder ) const = 0;
	
	/** Remove a state from the selection
		@param inState State to remove
	*/
	virtual ErrorCode DeleteState(  Form::AppearanceState inState ) const = 0;
	
	/** Remove the state content from the selection
		@param inState State to remove content
	*/
	virtual ErrorCode DeleteStateContent(  Form::AppearanceState inState ) const = 0;
	
	/** @return The next state that can be added (in order of the AppearanceState enum) */
	virtual Form::AppearanceState GetNewState() const = 0;
	
	/** @return kTrue if selection supports appearances, and inState doesn't already exist */
	virtual bool16 CanAddState(  Form::AppearanceState inState ) const = 0;

	/** Get rendered appearance of an appearance state
		@param inState State to get
		@param inMaxWidth Maximum width of returned bitmap
		@param inMaxHeight Maximum height of returned bitmap
		@param pOutAGMImage [OUT]: On exit, points to address of a newly allocated AGMImageAccessor, which must be deleted by the client.  The AGMImageAccessor 
			contains the rendered appearance.
	*/
	virtual ErrorCode GetAppearanceThumbnail(  Form::AppearanceState inState, int32 inMaxWidth, int32 inMaxHeight, AGMImageAccessor** pOutAGMImage  ) const = 0;
	
	/** Set form field appearance from an Assert in an Asset Library
		All of the page item children from the asset are copied over, as
		well as the Form Field related graphic attributes (read only, export, etc.)
		i.e. all the attributes that can be set in the Form Field Properties dialog
		The size, and transform, and non form field graphic attributes are preserved.
		
		@param inLibrary Asset library to use
		@param Which asset to use in inLibrary
	*/
	virtual ErrorCode SetAppearanceStyle(ILibrary* inLibrary, int32 inStyleIndex) const = 0;
	
	/** Remove all page item children of all the states (but retain the states themselves) */
	virtual ErrorCode RemoveAppearances() const = 0;

	/** @return number of appearance states in the selection */
	virtual int32 NumStates() const = 0;
	
	/** @return kTrue if the selection has content in any of its appearance states. */
	virtual bool16 SelectionHasContentInAnyState() const = 0;
	
	/** @return kTrue if the selection has content in its active appearance state. */
	virtual bool16 SelectionHasContentInActiveState() const = 0;
	
	/** @param inState the state to check for seleciton
		@return kTrue if the selection has content in the specified state, kFalse otherwise or if selections in multiple appearance items. */
	virtual bool16 SelectionHasContentInState(Form::AppearanceState inState) const = 0;
	
	/** @return kTrue if the selection supports appearance states. i.e. has an IAppearanceList interface */
	virtual bool16 HasStates() const = 0;

	/** @return User-readable name for inState e.g. "Normal", "Over", "Down", etc.
	*/
	virtual PMString GetStateName(  Form::AppearanceState inState ) const = 0;

	/** Get the name of the currently selected Field.
		@param name [OUT]: User-readable name of the selected Field/Page Item.
		@return 'true' if successful, 'false' otherwise.
	*/
	virtual bool GetName(PMString& name) const = 0;

	/** Gets the name of the only page item with the specified class in the current selection.
		@param name [OUT]: User-readable name of the selected Field/Page Item of the specified class.
		@param classID class of the item whose name to retrieve
		@return 'true' if there is only one page item in the current selection of the 
			specified class and its name was successfully retrieved, 'false' otherwise.
	*/
	virtual bool GetNameOfOnlyItemOfClass(PMString& name, const ClassID& classID) const = 0;
	
	/** Set the name of the selected field.
		@param newName [IN]: The name to assign to the button/field.
		@return kSuccess or an error.
	*/
	virtual ErrorCode SetName(const PMString& newName) const = 0;

	/** Set the name of the specified state for the selected field.
		@param state [IN]: The state to rename.
		@param newName [IN]: The name to assign to the state.
		@return kSuccess or an error.
	*/
	virtual ErrorCode SetStateName(Form::AppearanceState state, const PMString& newName) const = 0;

	enum MultiItemSelectionPolicy {kHandleItemsAsAGroup, kHandleItemsIndividually};
	virtual ErrorCode CreateAppearanceItem (const ClassID& formFieldType, MultiItemSelectionPolicy multiItemSelectionPolicy = kHandleItemsIndividually) const = 0;

	/** Move the state of an item to a new position in the item's state ordering.
		@param state [IN]: The state to move.
		@param position [IN]: The new position for the state.
		@return kSuccess or an error.
	*/
	virtual ErrorCode MoveState ( Form::AppearanceState state, int32 position ) const = 0;

	/** Move the state of an item to a new position in the item's state ordering.
		@param state [IN]: The state to move.
		@param position [IN]: The new position for the state.
		@return kSuccess or an error.
	*/
	virtual ErrorCode DeleteAppearance( Form::AppearanceState state ) const = 0;

	/** Release objects that represent the appearance of the selected item's specified 
		state to be children of the spread, and then delete the state.
		@param state [IN]: The state to release
		@return kSuccess or an error.
	*/
	virtual ErrorCode ReleaseAppearanceAsObject( Form::AppearanceState state ) const = 0;
	
	/** Release all of the objects that represent the appearances of each of the selected item's
		states to be children of the spread, and then delete the appearance item.
		@return kSuccess or an error.
	*/
	virtual ErrorCode ReleaseAllAppearancesAsObjects( ) const = 0;

	/** Get the index of the specified state in the selected object's state ordering.
		@param state [IN]: the state whose position will be returned
		@return if the current selection is an appearance item and the state exists, 
				the index of the state is returned; otherwise, kInvalidIndex
	*/	
	virtual int32 GetStatePosition(Form::AppearanceState state) const = 0;

	/** Determine whether the current contents of the clipboard can be pasted into
		the selected item of the specified class. This will return false if there
		are more than one item in the current selection.
		@param inAppearanceItemClass [IN]: the class of the appearance item of interest
		@return whether the clipboard contents can be pasted
	*/	
	virtual bool16 CanPasteIntoState( const ClassID inAppearanceItemClass ) const = 0;
	
	/** Paste the contents of the clipboard into the specified state of an appearance
		item in the current selection.
		@param inAppearanceItemClass [IN]: the class of the appearance item to paste into
		@param inState [IN]: the state of the appearance item to paste into
		@return kSuccess or an error
	*/	
	virtual ErrorCode PasteIntoState(const ClassID inAppearanceItemClass, Form::AppearanceState inState) const = 0;

	/** Set whether the selected appearance item is hidden until triggered on export.
		@return kSuccess or an error
	*/	
	virtual ErrorCode SetIsInitiallyHidden(bool16 inHidden) const = 0;

	/** Determines whether the selected appearance item is hidden until triggered on export.
		@return whether the selected appearance item is hidden until triggered on export 
	*/	
	virtual bool16 GetIsInitiallyHidden() const = 0;

	/** Examines the selected item for the specified appearance item class.
		@param inAppearanceItemClass [IN]: The desired appearance item class.
		@return bool16 kTrue if the item is of the specified appearance item class, kFalse otherwise.
	*/
	virtual bool16 IsAppearanceItemOfTypeSelected(const ClassID inAppearanceItemClass) const = 0;

	/** Selects the appearance item that is associated with the current selection.
		@param inAppearanceItemClass [IN]: The desired appearance item class.
		@return kSuccess or an error
	*/
	virtual ErrorCode SelectAssociatedAppearanceItemOfType(const ClassID inAppearanceItemClass) = 0;

	/** Returns whether the group that wraps the active states for the specified appearance item class in the selection is selected.
		@param inAppearanceItemClass [IN]: The desired appearance item class.
	*/
	virtual bool16 IsActiveStateOfAppearanceItemOfTypeSelected(const ClassID inAppearanceItemClass) const = 0;
	
	/** Determines if there is a unique appearance item in the selection of class inClassToAddTo, and if
		all of the other items can be placed into one of that item's states.
		@param inClassToAddTo [IN]: the class of the appearance item
		@return whether the items in the selection can be added to the only item of inAppearanceItemClass
	*/
	virtual bool16 CanAddItemsAsStates(const ClassID& inClassToAddTo) const = 0;

	/** Finds a unique appearance item of class inClassToAddTo in the selection, and then adds all of the
		other items in the selection to one or more of that item's states.
		@param inClassToAddTo [IN]: the class of the appearance item
		@param inHowToAddStates [IN]: how to add the non-appearance items to the appearance item
		@return kSuccess or an error
	*/
	virtual ErrorCode AddItemsAsStates(const ClassID& inClassToAddTo, HowToAddStates inHowToAddStates) const = 0;

};

#endif // _IFormFieldSuite_
