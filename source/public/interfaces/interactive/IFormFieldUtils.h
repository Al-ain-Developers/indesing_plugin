//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IFormFieldUtils.h $
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
#ifndef __IFormFieldUtils_h__
#define __IFormFieldUtils_h__

#include "AGMImageAccessor.h"
#include "FormFieldTypes.h"
#include "K2Pair.h"
#include "K2Vector.h"
#include "FormFieldID.h"
#include "Utils.h"

//=============================================================================

class IDocument;
class IHierarchy;
class IFormFieldFactory;
class ISpread;
class IGraphicStyleAttributeBossList;
class IApplyMultAttributesCmdData;
class IAppearanceList;
class ILayoutSelectionSuite;

/** Some Miscellaneous FormField related utilities.
*/
class IFormFieldUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFORMFIELDUTILS };

	typedef K2Pair<UID, Form::AppearanceState> UIDStatePair;
	typedef K2Vector<UIDStatePair> UIDStatePairs;

	/** @return kTrue if all the items in inItems could be put inside a Form Field page item */
	virtual bool16 CanPlaceInAnnotation(const UIDList *inItems) const = 0;

	/** @return kTrue if all the items in inItems could be edited (not locked) */
	virtual bool16 CanEditItems(const UIDList *inItems) const = 0;

	/** @return kTrue if all the items in inItems could be edited (not locked), and are form field page items */
	virtual bool16 CanEditFormItems(const UIDList *inItems) const = 0;

	/** @return kTrue if state can be deleted, i.e. it exists, and is not "Normal" */
	virtual bool16 CanDeleteState(Form::AppearanceState inState) const = 0;

	/** @return kTrue if state is a normal state e.g. "Normal", "Normal On", Normal Off", etc.*/
	virtual bool16 IsNormalState(Form::AppearanceState inState) const = 0;

	/** @return kTrue if state is an on state e.g. "Normal On", "Over On", etc.*/
	virtual bool16 IsOnState(Form::AppearanceState inState) const = 0;

	/** @return kTrue if state is an off state e.g. "Normal Off", "Over off", etc.*/
	virtual bool16 IsOffState(Form::AppearanceState inState) const = 0;

	/** @return kTrue if state is a defined state */
	virtual bool16 IsDefinedState(Form::AppearanceState inState) const = 0;

	/** @return The name of the state, if the state is defined; otherwise an empty string. */
	virtual PMString GetDefinedStateName(Form::AppearanceState inState) const = 0;

	/** Execute a command to change the active state of a Form Field
		@param inItemRef Page item supporting appearance states
		@param inState new active state
		@return Error from command
	*/
	virtual ErrorCode ProcessChangeStateCmd(const UIDRef& inItemRef, Form::AppearanceState inState ) const = 0;

	/** Create a new Form Field of a specified type
		@param inParent Parent item of new form field
		@param inBounds Bounds of new form field
		@param inFormFieldBoss Type of form field to create (e.g. kPushButtonItemBoss) 
		@return Form Field UIDRef created.
	*/
	virtual UIDRef CreateFormPageItem (const UIDRef& inParent, const PMRect& inBounds, ClassID inFormFieldBoss ) const = 0;

	/** Puts an invisible place holder item in the new page item.
		If the item is created as a graphic frame, it keep the empty content X from showing up,
		
		The problem is that I want the spline graphic frame hit behavior (always hit within the spline), but I don't want
		the x if the shape (CFormFieldShape) is going to be drawing something, which is the case for text items, list boxes,
		and combo boxes if they have no children in the hierarchy.
		
		@param inFormField Form field to receive the dummy content
	*/
	virtual ErrorCode AddFormFieldContent ( UIDRef& inFormField ) const = 0;
	
	/** Get the form field factory for a particular form field type (class id) */
	virtual IFormFieldFactory* QueryFormFieldFactory (ClassID inFactoryBoss) const = 0;

	/** Change the state of a form field page item using a command */
	virtual ErrorCode SetAppearanceState(UIDRef& inPageItem, Form::AppearanceState inState) const = 0;

	/** Get the state that a page item appears in
		@param inPageItem page item for which we want to know the state
		@outAppearanceParent The ancestor page item that contains an IAppearanceList
		@outActiveState On exit, the active state for outAppearanceParent
		@return The state that inPageItem appears in, under *outAppearanceParent */
	virtual Form::AppearanceState GetChildAppearanceState( IPMUnknown* inPageItem, UIDRef* outAppearanceParent, Form::AppearanceState* outActiveState ) const = 0;
	
	/** Add the attribute to the 
		@param inSrcList 
		@param inApplyAttributesCmdData 
		@param inStyleName  */
	virtual void AddFormFieldAttributes(IGraphicStyleAttributeBossList* inSrcList, IApplyMultAttributesCmdData* inApplyAttributesCmdData, const PMString& inStyleName) const = 0;

	/** Get this state's the default state name. On a Multi-State Object this will be "State " followed by a number making the name unique.
		@param inAppearanceList the appearance list that the name must be unique in 
		@param inState the state to obtain the name of
		@return the unique name */
	virtual PMString GetDefaultStateName(const IAppearanceList* inAppearanceList, Form::AppearanceState inState) const = 0;

	/** Create a state name that is unique to an appearance list, based on another name. 
	    @param inAppearanceList the appearance list to be unique within
		@param inOutName the name to start with, and after the call, the unique string that results
		@param inAppendCopy whether or not to append the work 'Copy' to the state name while making it unique */
	virtual PMString GetDuplicateName(const IAppearanceList* inAppearanceList, Form::AppearanceState inState ) const = 0;
	
	/** Make a string unique from all the state names in an appearance list.
		@param inAppearanceList the appearance list that the string should be unique in
		@param inName the string to be made unique
		@param inStartValue the number to start numering from
		@param inNamePolicy specify whether the unique name must have a number appended onto it */
	enum NumberingStartValue { kStartNumberingWithStateNumber = -2, kStartNumberingWithNextStateNumber = -1, kStartNumberingWithOne = 1, kStartNumberingWithTwo = 2 };
	enum UniqueNamePolicy { kDoesNotNeedToEndInANumber, kMustEndInANumber };
	virtual void MakeNameUniqueInAppearanceList( const IAppearanceList* inAppearanceList, PMString& inName, NumberingStartValue inStartValue, UniqueNamePolicy inNamePolicy = kDoesNotNeedToEndInANumber) const = 0;

	/** Reset the name of a state in a given appearance list
		@param inItem the item whose name is to be determined
		@param inStartingAncestorType the class of the ancestor to start naming the target from. 
				Ex. if this is kMultiStateObjectItemBoss, then the target name will start with 
				the nearest MSO's name, appending the name of each item between the MSO and inItem
		@return the name of the target */
	virtual PMString GetTargetName( const IPMUnknown* inItem, const ClassID& inStartingAncestorType ) const = 0;

	/** Determine if all of the objects in a UIDList can be added to a state of the specified form field class.
		@param inItems the list of items to check
		@param inTargetClass the ClassID of the object that the items will be added to
		@return whether the items can be added to an item of the specified state */
	virtual bool16 CanPlaceInState(const UIDList& inItems, const ClassID& inTargetClass) const = 0;

	/** Determine if a certain form field item can be created from all of the objects in a UIDList.
		@param inItems the list of items to check
		@param inTargetClass the ClassID of the form field item in question
		@return whether a form field item of the specified state can be created from the items passed in */
	virtual bool16 CanCreateFromItems(const UIDList& inItems, const ClassID& inTargetClass) const = 0;

	/** Gets a list of all form items of a specific type in a document.
		@param docRef the document
		@return a list of all the form items requested in the document */
	virtual UIDList GetAllFormItemsOfTypeInDocument(const UIDRef& docRef, const ClassID& classID) const = 0;

	/** Resets all multi-state objects to their first state.
		@param docRef the document to reset
		@return ErrorCode */
	virtual ErrorCode ResetAllMultiStateObjects(const UIDRef& docRef) const = 0;

	/** Resets all buttons to their Normal state.
		@param docRef the document to reset
		@return ErrorCode */
	virtual ErrorCode ResetAllButtons(const UIDRef& docRef) const = 0;

	/** Get the UIDRef of the group that wraps the specified state on an Appearance Item.
		@param inItemRef the appearance item
		@param inState the state
		@return the UIDRef of the group wrapping the state, if one exists; otherwise an invalid UIDRef */
	virtual UIDRef GetStateWrappingGroup(const UIDRef& inItemRef, Form::AppearanceState inState) const = 0;

	/** Determine if an item is not in any hidden states. If this returns kTrue, that implies
		that the item is able to be found while traversing the hierarchy from in a top-down fashion.
		@param inItemRef the item in question
		@param outTopmostHidingAncestor optional,   if return value is kFalse, the UID of the topmost item 
													in the hierarchy that is hiding inItemRef; otherwise kInvalidUID. */
	virtual bool16 IsItemOnlyInActiveStates(const UIDRef& inItemRef, UID* outTopmostHidingAncestor = nil) const = 0;

	/** Gets a list of appearance items and the states that must be set to active in order for
		to appear in the hierarchy. (Sorted from nearest ancestor to furthest)
		@param inItemRef the item to investigate
		@return the appearance items and the states that inItemRef resides in for those appearance items */
	virtual UIDStatePairs GetStatesForItem(const UIDRef& inItemRef) const = 0;

	/** Sets the active states of all appearance item ancestors such that inItemRef is visible in
		in the hierarchy.
		@param inItemRef the item to cause to appear in the hierarchy */
	virtual void SetStatesSoThatItemIsActive(const UIDRef& inItemRef) const = 0;

	/** Selects the group that wraps the active state of each item in inItems.
		@param inItems the items whose active states to select */
	virtual void  SelectActiveState(const UIDList& inItems) const = 0;

	//These are to help identify casting (the use of which should be minimized)
	inline int32 StateToIndex(Form::AppearanceState inState) const { return (int32)inState; }
	inline Form::AppearanceState IndexToState(int32 inIndex) const { return Form::AppearanceState(inIndex); }

	//The following are general page item utils that happened to be used by forms...
	
	/** Get the spread of a page item
		@param inPageItemHier page item to check, may be an inlined item
		@return UID of spread.
	*/	
	virtual UID GetSpreadUID(IHierarchy* inPageItemHier) const = 0;

	/** Get the pages of a page item
		@param inPageItemHier page item to check, may be an inlined item
		@param outPageUIDs On exit, the pages which inPageItemHier appears on.
	*/	
	virtual void GetPageUIDs(IHierarchy* inPageItemHier, UIDList* outPageUIDs) const = 0;

	/** Determine if a page item, inPageItemUID, is on a page in a spread, also checks to see if inPageItemUID is
		an inlined item on the page.
		@param inSpread Spread to check
		@param inPagePos which page to check on inSpread
		@param ioPageItems (must be non-null) is empty or the result of GetItemsOnPage.  If this is called
				repeatedly for the same spread, this saves extra calls to GetItemsOnPage
		@param inPageItemUID Page item that is being checked
	*/
	virtual bool16 IsOnPage(ISpread* inSpread, int32 inPagePos, UIDList* ioPageItems, UID inPageItemUID) const = 0;

	/** Get all page items under a certain page item that contain a certain interface, also checks inlines of text frames
		@param inHierarchy The page item to search under
		@param inInterfaceID The interface to search for
		@param outResultList A list of children items that have inInterfaceID
	*/
	virtual void GetDescendents( IHierarchy* inHierarchy, const PMIID& inInterfaceID, UIDList *outResultList ) const = 0;

	/** Get all page items under certain page items that contain a certain interface, also checks inlines of text frames
		@param inUIDList The page items to search under
		@param inInterfaceID The interface to search for
		@param outResultList A list of children items that have inInterfaceID
	*/
	virtual void GetDescendents( const UIDList& inUIDList, const PMIID& inInterfaceID, UIDList *outResultList ) const = 0;

	/** Filter out UIDs with a certain interface, and return them
		@param inUIDList a list of UIDs
		@param inIID The interface id to search for
		@return a UIDList of all the iterm from inUIDList that have a inIID interface
	*/
	virtual UIDList ExtractPageItemsWithIID(const UIDList& inUIDList, PMIID inIID) const = 0;
	
	/** Gets the first ancestor of a given class
		@param inItem the item whose ancestor is to be looked for
		@param inClassToFind the class of the ancestor to be looked for 
		@param outItemRef the ancestor
		@return returns kTrue if a matching ancestor was found, otherwise returns kFalse */
	virtual bool16 GetFirstAncestorOfClass( const IPMUnknown* inItem, const ClassID& inClassToFind, UIDRef& outItemRef ) const = 0;

	/** Ungroups all of the single item groups passed in.
	@param inOutItems the items to look through
	@param fixUpItemList if this is true, then when a single-item group is ungrouped, 
			the group's UID is replaced with its child UID in inOutItems
	@return kSuccess if all ungroup commands were successful, otherwise kFailure
	*/
	enum {kFixUpList = kTrue, kDontFixUpList = kFalse };
	virtual ErrorCode UngroupSingleItemGroups(UIDList& inOutItems, bool16 fixUpItemList = kDontFixUpList) const = 0;

	/** Changes the parent of an item, while preserving its transform.
	@param inItemToChange the item to move
	@param inNewParent the new parent of the item
	@return kSuccess if successful, otherwise an error code indicating the problem 
	*/
	virtual ErrorCode ChangeHierarchyPreservingTransform(UIDRef inItemToChange, UID inNewParent) const = 0;

	/** Get rendered appearance of an appearance state
		@param inAppearanceItemRef the item to get
		@param inState State to get
		@param inMaxWidth Maximum width of returned bitmap
		@param inMaxHeight Maximum height of returned bitmap
		@param pOutAGMImage [OUT]: On exit, points to address of a newly allocated AGMImageAccessor, which must be deleted by the client.  The AGMImageAccessor 
			contains the rendered appearance.
	*/
	virtual ErrorCode GetAppearanceThumbnail(UIDRef inAppearanceItemRef, Form::AppearanceState inState, int32 inMaxWidth, int32 inMaxHeight, AGMImageAccessor** pOutAGMImage) const = 0;

	/** Determine if there's another form field/button in the UIDList provided. 
		@param inItems the list of items to check
		@param inTargetClass the ClassID of the form field item in question
		@return whether a form field item of the specified state can be created from the items passed in */
	virtual bool16 HasButtonOrFormField(const UIDList& inItems, const ClassID& inTargetClass) const = 0;

	/** Take action when form's missing font adronment is clicked 
		@param iLayoutSelectionSuite - Layout selection suite
		@param item - UIDRef of form field item whose adornment is clicked
		@param shiftKeyDown - true if shift key is pressed
		@param altOptionKeyDown - true if alt/option key is presssed**/
    virtual void TakeActionOnMissingFontFormAdornment(ILayoutSelectionSuite * iLayoutSelectionSuite, UIDRef item, bool16 shiftKeyDown, bool16 altOptionKeyDown) = 0;
    
    /** Tells whether form field have font attribute. For example TextFields.
    	@param uidRef - uidRef for form field item*/
    virtual bool DoesHaveFontAttribute(const UIDRef& uidRef) = 0;
    
    /** Set font family Attr on form fields(used during PDF export). It creates a command and 
    	runs all operation whithin the sequence.
    	@param uidList - list of UID's on which font family attribute have to be applied
    	@param fontFamilyName - font family to be applied*/
    virtual ErrorCode SetFontFamilyAttrCmd(const UIDList& uidList,const PMString& fontFamilyName) const = 0;

    /** Similar to SetFontFamilyAttrCmd, but it does not create command sequence for operations.
    	@param uidList - list of UID's on which font family attribute have to be applied*/
    virtual ErrorCode SetFontFamilyAttr(const UIDList& uidList, const PMString& fontFamilyName) const = 0;
    
    /** Set Font UID on form fields. It creates a command and runs all operation within the 
    	sequence.
    	@param uidList - list of UID's on which font family attribute have to be applied
    	@param fontUID - font's UID to be applied*/
    virtual ErrorCode SetFontFamilyUIDAttrCmd(const UIDList& uidList, const UID& fontUID) const = 0;
 	
 	/** Similar to SetFontFamilyUIDAttrCmd, but it does not create command sequence for operations.
		@param uidList - list of UID's on which font family attribute have to be applied
    	@param fontUID - font's UID to be applied*/
    virtual ErrorCode SetFontFamilyUIDAttr(const UIDList& uidList, const UID& fontUID) const = 0;
    
    /** Sets font style attribute on form fields. It creates a command and runs all operation within the 
    	sequence.
    	@param uidList - list of UID's on which font family attribute have to be applied
    	@param fontUID - font style to be applied*/
    virtual ErrorCode SetFontStyleAttributeCmd(const UIDList& uidList, const PMString& fontStyleName) const = 0;

    /** Similar to SetFontStyleAttributeCmd, but it does not create command sequence for operations.
    	@param uidList - list of UID's on which font family attribute have to be applied
    	@param fontUID - font style to be applied*/
    virtual ErrorCode SetFontStyleAttribute(const UIDList& uidList, const PMString& fontStyleName) const = 0;
    
    /** Gets font's UID for a form field item.
    	@param uidRef - UID for of form field.
    	@param fontUIF - [OUT] Font UID attibute of form field. */
    virtual bool16	GetFontFamilyUIDAttr(const UIDRef& uidRef, UID& FontUID) const = 0;

    /** Gets font style for a form field item.
    	@param uidRef - UID for of form field.
    	@param fontUIF - [OUT] Font style attibute of form field. */
    virtual bool16 GetFontStyleAttribute(const UIDRef& uidRef, PMString& fontStyleName) const = 0;
};

/*	This is the preamble that appears on all default predefined apprearances that signals
	that the name should be translated.  */
#define kPredefinedAppearanceNamePreamble "$$$/PredefinedAppearanceName/"


//=============================================================================

#endif // __IFormFieldUtils_h__
