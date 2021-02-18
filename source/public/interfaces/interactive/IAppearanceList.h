//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IAppearanceList.h $
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
#ifndef __IAppearanceList_h__
#define __IAppearanceList_h__

#include "IPMUnknown.h"
#include "FormFieldTypes.h"
#include "FormFieldID.h"
#include "BravoForwardDecl.h"

//=============================================================================

/** A list of alternate appearances (states) for a page item.  Each state consists
of a state type, and a list of children (which are accessed via IHierarchy).
You may add/delete states, and set an active state.  The currently active state
determines which children of the page item are exposed via IHierarchy.  The children
belonging to inactive states are hidden, and are only accessible when their state
becomes the active state.

The implementation of IHierarchy for a page item with an IAppearanceLIst interface
uses the active state in IAppearanceList so that it only presents the children of
the active state.
@see IHierarchy
*/
class IAppearanceList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPEARANCELIST };
	enum
	{
		kInvalidate = kTrue,
		kDontInvalidate = kFalse,
		kInvalidStateID = -1,
		kLastInOrder = -1
	};

	typedef int32 StateID;


	/** Return the active state.
		@return value of last call to SetActiveStateTemp if not kInvalidState,
				otherwise value of last call to SetActiveState value  */
	virtual Form::AppearanceState GetActiveState() const = 0;

	/** Return the unique id an appearance state.  Each state has an id that remains the same for the life of the appearance,
	    which is unique from any other existing appearance.  This id may be used to id/find/track the appearance regardless
	    of any changes made to the appearance 
	    @return the unique id for inState. */
	virtual StateID GetStateID(Form::AppearanceState inState) const = 0;

	/** @return the unique id for the active state.  */
	virtual StateID GetActiveStateID() const = 0;

	/** @return the state that has inStateID.  */
	virtual Form::AppearanceState GetIDState(IAppearanceList::StateID inStateID) const = 0;

	/** Set the active state.
		@param inState a valid state in IAppearanceList that will become the active state
	*/
	virtual void SetActiveState( Form::AppearanceState inState ) = 0;

	/** Get the state that contains inChild.
		@param inChild a valid child in this items IHierarchy (may be in an inactive state, and may not be immediate child)
		@return If inChildUID is in IAppearanceList, returns the state, else  kStateInvalid
	*/
	virtual Form::AppearanceState GetChildState( const UID& inChildUID ) const = 0;

	/** Get the "temp" active state, which is the last value set by SetActiveStateTemp
		Shouldn't need to call this directly. Use StSetStateTemp instead.
	*/
	virtual Form::AppearanceState GetActiveStateTemp() const = 0;

	/** Get the appearance state whose name matches the specified name.
	 */
	virtual Form::AppearanceState GetStateFromName(const PMString& name) const = 0;

	/** Get the first supported state that does not have an appearance associated with it.
		Specifically useful for creating states on form fields that do not use the states defined in Form::DefinedAppearanceState
		@return if there is an unused supported state available, returns the state - otherwise, kStateInvalid
	*/
	virtual Form::AppearanceState GetNextAvailableState() const = 0;
	
	/** Sets a alternate, temp state, separate from GetActiveState and SetActiveState, which
	    doesn't not dirty the interface.  Used when drawing thumbnails.
	    shouldn't be called directly, use StSetStateTemp instead
	    @param inState The state that should become the active state
	    @param inInvalCaches Whether or not the thumbnails need to be invalidated, If you are sure the
	    		state is not going to be changed, pass IAppearanceList::kDontInvalidate */
	virtual void SetActiveStateTemp( Form::AppearanceState inState, bool16 inInvalCaches=IAppearanceList::kInvalidate ) = 0;

	/** @return number of valid appearance states in the IAppearanceList */
	virtual int32 NumStates() const = 0;

	/** @return true if inState has been added to this IAppearanceList */
	virtual bool16 HasAppearance(  Form::AppearanceState inState ) const = 0;

	/** Add a new appearance state to the list. Better to use kNewStateCmdBoss command, which handles
		necessary maintenance to IHierarchy, than to call this directly.
		@param inState The state to add
		@param inAppearance Parameters for the new state
	    @see kNewStateCmdBoss
	 */
	virtual void AddAppearance(  Form::AppearanceState inState, const Form::Appearance& inAppearance, int32 position = kLastInOrder ) = 0;

	/** Removes a appearance state from the list. This does not removed the children in IHierarchy
	    use kDeleteStateCmdBoss command to handle the deletion of children and other housekeeping.
	    @param inState The state to remove
	    @param outRemovedAppearance If non-nil, returns the parameters for the deleted state, Pass nil if you
	    							don't need this information.
	    @see kDeleteStateCmdBoss
	*/
	virtual void RemoveAppearance(  Form::AppearanceState inState, Form::Appearance* outRemovedAppearance ) = 0;

	/** Change an appearance state in the list.  Doesn't change page item children for state. Use IHierarchy for that
		@param inState The state to change
		@param inNewState The state to change inState to.
		 */
	virtual void ChangeState( Form::AppearanceState inState, Form::AppearanceState inNewState) = 0;

	/** Move a state to a specific position in the state-ordering.
		@param inState The state to move
		@param inPosition The position in the state-ordering to move the state to
		 */
	virtual void Move( Form::AppearanceState inState, int32 inPosition) = 0;
		
	/** Determine if a particular state is present in this IAppearanceList.
		@return true if inState is a supported state, and it doesn't already exist.
	*/
	virtual bool16 CanAddState( Form::AppearanceState inState ) const = 0;

	/** Get parameters for state. For now, this only consisted of the "enabled" property.
		Enabled says whether the state will be exported in the PDF for the page item (form field).
		@return true if inState exists, false otherwise
	*/
	virtual bool16 GetAppearance(  Form::AppearanceState inState, Form::Appearance* outAppearance  ) const = 0;

	/** Set parameters for state. For now, this only consisted of the "enabled" property.
		Enabled says whether the state will be exported in the PDF for the page item (form field).
	*/
	virtual void SetAppearance(  Form::AppearanceState inState, const Form::Appearance& inAppearance ) = 0;

	/** Get the inStateIndexth state that is the IAppearanceList.
	    Used to iterate through all the states.
	    @return nth state in this IAppearanceList
	*/
	virtual Form::AppearanceState GetNthState( int32 inStateIndex ) const = 0;

	/** Returns the index of inState IAppearanceList.
	    @return the index of inState in IAppearanceList, -1 if inState is not in the list
	*/
	virtual int32 GetStatePosition ( Form::AppearanceState inState ) const = 0;
	
	/** Delete all states in the appearance list.
		This should not be called directly, as an AppearanceList is supposed to always
		contain one or more normal states.  This method is only used internally
		when copying page items with IAppearanceLists.
		This does not removed the children in IHierarchy.
	    @see kDeleteStateCmdBoss
	*/
	virtual void Clear() = 0;	

	/** Return a bitmap of size inMaxWidth x inMaxHeight (at most) that is the rendered appearance
	    of inState.  Used to draw thumbnails in appearance palette.
	    @param inState state of thumbnail to get
	    @param inMaxWidth max width of thumbnail.  Thumb is either inMaxWidth or the actual width of the appearance.
	    @param inMaxHeight max height of thumbnail.  Thumb is either inMaxHeight or the actual height of the appearance.
	    @param outAGMRecord thumbnail is returned here.  Do not allocate or release the pixels.  They are owned by the
	           thumbnail. outAGMRecord is only valid while IAppearanceList is valid, and there are no operations that
	           change the appearance of any of the IAppearanceList states.
	*/
	virtual ErrorCode GetThumbnail(  Form::AppearanceState inState, int32 inMaxWidth, int32 inMaxHeight, AGMImageRecord* outAGMRecord ) = 0;
	
	/** Invalidate any cached thumbnails for state inState, used when anything effecting
	    the appearance of the state is changed.
	*/	
	virtual void InvalidateThumbnail( Form::AppearanceState inState ) = 0;

	/** Throw away any cached thumbnails for state inState.
	*/
	virtual void DisposeThumbnail( Form::AppearanceState inState ) = 0;

	/** Internal Use Only.
		Before one try to remove any appearance, it checks whether it can actually remove it or not.
		This API eliminates this check & just go ahead and delete appearence

		@param inState The state to remove
	    @param outRemovedAppearance If non-nil, returns the parameters for the deleted state, Pass nil if you
	    							don't need this information.
	    @see kDeleteStateCmdBoss

		WARNING : If not used in appropriate senario, it would lead to undesirable results.
	*/
	virtual void ForceRemoveAppearance(  Form::AppearanceState inState, Form::Appearance* outRemovedAppearance ) = 0;
};

//=============================================================================

/**
Stack based class for 'temporarily' changing the active state of an IAppearanceList.
Used to iterate through states, when the IAppearanceList interface itself doesn't need
to be dirtied.  That is, when you need to access all the children page items of all
the appearances states.
*/
class StSetStateTemp
{

public:
	/** Temporarily set the active state on an appearance list
		@param inAppList appearance list to change
		@param inState state to make active
		@param inInvalCaches invalidate thumbnails of inAppList.  If you plan on modifying the children
		       of inAppList, pass in true (the default).  If you are certain none of the appearances of any of the states will
		       be changed, false may be used.
		
	*/
	StSetStateTemp(IAppearanceList* inAppList, Form::AppearanceState inState, bool16 inInvalCaches=IAppearanceList::kInvalidate )
	:
		fAppList(inAppList), fInvalCaches(inInvalCaches), fOrigState(Form::kStateInvalid)
	{
		if ( fAppList ) {
			fOrigState = inAppList->GetActiveStateTemp();
			fAppList->SetActiveStateTemp(inState,fInvalCaches);
			fAppList->AddRef();
		}
	}
	
	/** Upon destruction, set state back to what it was previously
	*/
	~StSetStateTemp()
	{
		if ( fAppList ) {
			fAppList->SetActiveStateTemp(fOrigState,fInvalCaches);
			fAppList->Release();
		}
	}
	
private:
	IAppearanceList* fAppList;
	Form::AppearanceState fOrigState;
	bool16 fInvalCaches;
};

//=============================================================================

#endif // __IAppearanceList_h__

//  IAppearanceList.h.
