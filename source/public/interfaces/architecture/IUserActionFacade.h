//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUserActionFacade.h $
//  
//  Owner: Michael Martz
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
//  
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _IUserActionFacade_
#define _IUserActionFacade_

#include "IPMUnknown.h"
#include "IActionsPlaybackPreference.h"
#include "IScriptRequestData.h"
#include "IUserActionSequence.h"

#include "Utils.h"

class UserActionPlaybackContext;
class UserActionPlaybackOptions;

class IUserActionFacade : public IPMUnknown
{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
public:
	enum { kDefaultIID = IID_IUSERACTIONFACADE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
public:
	/**	Create a new user action group within the specified action group and name.
	@param groupName is the name of the new group.
	@param iUserActionSet is the user action set in which to create the new group.
	@return IPMUnknown* to the new user action group.
	*/
	virtual IPMUnknown*	CreateUserActionGroup (IUserActionSequence::UserActionSequenceName& groupName, IPMUnknown* iUserActionSet) = 0;

	/**	Return the number of child actions of the specified user action.
	@param iUserAction is the user action.
	@return the number of child actions.
	*/
	virtual int32		GetNumberUserActionChildren (IPMUnknown* iUserAction) = 0;

	/**	Return the requested interface of the specified user action's nth child.
	@param iUserAction is the user action.
	@param index specifies the nth child.
	@param wantedIID is the requested interfaceIID.
	@return IPMUnknown* to the requested interface of the user action's nth child.
	*/
	virtual IPMUnknown*	QueryNthUserActionChild (IPMUnknown* iUserAction, int32 index, const PMIID& interfaceIID = IID_IUNKNOWN) = 0;

	/**	Set the enabling state of the specified user action.
	@param iUserAction specifies the user action.
	@doEnableAction is the new enabling state.
	@return kSuccess if successfull.
	*/
	virtual ErrorCode	SetUserActionEnableState (IPMUnknown* iUserAction, bool16 doEnableAction) = 0;

	/**	Set the action name of the specified user action.
	@param iUserAction specifies the user action.
	@name is the new action name.
	@return kSuccess if successfull.
	*/
	virtual ErrorCode	SetUserActionName (IPMUnknown* iUserAction, WideString& name) = 0;	

	/**	Get the enabling state of the specified user action.
	@param iUserAction specifies the user action.
	@return kTrue is the user action is enabled. Otherwise kFalse.
	*/
	virtual bool16		GetUserActionEnableState (IPMUnknown* iUserAction) = 0;

	/**	Get the name of the specified user action.
	@param iUserAction specifies the user action.
	@return the action name in a WideString.
	*/
	virtual WideString	GetUserActionName (IPMUnknown* iUserAction) = 0;

	/**	Load the specified action file.
	@param serviceProviderClassID determines which User Action Manager to use
	@param actionSysfile is the action file to load. actionSysfile contains one single
	user action set.
	@return kSucces if load action is successful.
	*/
	virtual ErrorCode	LoadActions (ClassID serviceProviderClassID, const IDFile& actionSysfile) = 0;

	/**	Save the specified action set to a file.
	@param serviceProviderClassID determines which User Action Manager to use
	@param iActionSet is the action set to save.
	@param actionSysfile is the action file to which the set will be saved.
	@return kSucces if save action is successful.
	*/
	virtual ErrorCode	SaveActions (ClassID serviceProviderClassID, IUserActionSequence* iActionSet, IDFile& actionSysfile) = 0;

	/**	Start recording within the specified user action group or after the specified user action item.
	@param serviceProviderClassID determines which User Action Manager to use
	@param iRecordingUserSequence is the user action group where recorded events will be added.
	In this case, the new user events will be added at the end of teh group. 
	If iRecordingUserSequence specifies an user action item, then new events will be recorded
	after this user action item.
	@return kTrue if recording started successfully. Otherwise it returns kFalse.
	*/
	virtual bool16	StartRecordingUserActions (ClassID serviceProviderClassID, IPMUnknown*	iRecordingUserSequence) = 0;

	/**	Stop the active record or playback session.
	@param serviceProviderClassID determines which User Action Manager to use
	*/
	virtual void	Stop (ClassID serviceProviderClassID) = 0;

	/**	Playback a list of the specified user action items.
	@param serviceProviderClassID determines which User Action Manager to use
	@param playbackContext is the context that should be used to bind the action to whatever is the 
	current subject. This could be the selection, the doc or app workspace, etc.
	@param userActionAtomPlaybackList is the list of user action atoms.
	@return kTrue if playback is successfully. Otherwise it returns kFalse.
	*/
	virtual bool16	StartPlaybackUserActions (ClassID serviceProviderClassID, UserActionPlaybackContext& playbackContext, UserActionPlaybackOptions& playbackOptions,IUserActionSequence::UserActionList& userActionAtomPlaybackList, bool16 createOuterSequence, const PMString* sequenceName, K2Vector<PMString>* playbackErrorStrings, IScriptRequestData::TargetHandlingPolicy) = 0;

	/**	Clear the saved Transform Again actions
	*/
	virtual void	ClearTransformAgainActions (void) = 0;
	virtual void	StartRecordingTransformAgainActions (void) = 0;
	virtual void	StartPlaybackTransformAgainUserActions (UserActionPlaybackContext& playbackContext, K2Vector<PMString>* playbackErrorStrings, IScriptRequestData::TargetHandlingPolicy) = 0;
	virtual void	StartPlaybackTransformLastAgainUserActions (UserActionPlaybackContext& playbackContext, K2Vector<PMString>* playbackErrorStrings, IScriptRequestData::TargetHandlingPolicy) = 0;
	virtual int16	CountTransformAgainActions (void) = 0;
	virtual int32	GetTransformAgainGenerationID (void) = 0;
	virtual IUserActionSequence* PopLastTransformAgainAction (void) = 0;
	virtual void	 PushLastTransformAgainAction (IUserActionSequence*) = 0;

	virtual void		GetPlaybackOptionsPreferences (IActionsPlaybackPreference::PlaybackSpeed& playbackSpeed, PMReal& pauseForSeconds) = 0;
	virtual ErrorCode	SetPlaybackOptionsPreferences (IActionsPlaybackPreference::PlaybackSpeed playbackSpeed, PMReal pauseForSeconds) = 0;
};

#endif // _IUserActionFacade_
