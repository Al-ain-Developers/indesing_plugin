//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOpenDocAction.h $
//  
//  Owner: Roey Horns
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

obsolete;
#if 0
#pragma once
#ifndef __IOPENDOCACTION__
#define __IOPENDOCACTION__

#include "IPMUnknown.h"

class ICommand;
class IDocument;

/**	An interface that allows plugins to do any desired action when a document gets opened or recovered.
		OpenDocActions that change the document should do this using an "optional" Dirty(..., kFalse).
*/
class IOpenDocAction : public IPMUnknown
{
public:
	enum { kActionNotDone = 0,
			kActionInProgress,
			kActionDone };

	/** The DoAction callback, triggered when a document is opened or recovered.
			This is called after the document has been opened/recovered but
			before any window has been opened.

			DoAction can return kFalse in order to cancel the open. If it
			does so it should set the global error state.

		@param cmd IN the command that triggered the callback. Can be either be a OpenDocCmd or a RecoverDocumentCmd.
		@param theDoc IN the document
		@param actionClassID IN which action
		@param isRecovered IN the the document being recovered
		@return true usually, can also return false to cancel the open.
	*/
	virtual bool16 DoAction(ICommand* cmd, IDocument* theDoc, ClassID actionClassID, bool16 isRecovered) = 0;

	/**	Returns a flag indicating whether or not the action has not yet
			been done, is in progress, or is done. The implementing class is
			REQUIRED to set the flag to kActionNotDone in its constructor,
			kActionInProgress at the start of DoAction(), and kActionDone at
			the end of DoAction().
			This state information allows us to manage dependencies between
			different NewDocAction services.
	*/
	virtual int32 GetState() = 0;

	/** Set the internal "done-ness" state flag to newState. This should
			only be called by internal code for bookkeeping.
	*/
	virtual void SetState(int32 newState) = 0;
};


#endif // __IOPENDOCACTION__
#endif

