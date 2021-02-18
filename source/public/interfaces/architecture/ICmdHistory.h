//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICmdHistory.h $
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
//  
//  Reviewed:	10/06/98
//  
//========================================================================================

#pragma once
#ifndef __ICMDHISTORY__
#define __ICMDHISTORY__

#include "CommandID.h"
#include "IPMUnknown.h"

class PMString;
class CmdStackItem;

/** The CmdHistory of a given target is the collection of all undoable
	and redoable steps that are currently available for this target.
	It hides single commands (ICommand) and command sequences (ICommandSequence). You can only access 
	history steps, which are the undo/redo steps available via the
	undo/redo menu items.
	There is only one global CmdHistory. In order to use it you have
	to specify the target (ICommandMgr) you are interested in.

	@see ICommand
	@see ICommandMgr
	@ingroup arch_cmd
*/
class ICmdHistory : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICMDHISTORY };

		// ---- In all the methods below, if target == UIDRef::gNull the application defaults
		//		document will be used as the target. Otherwise the target should be valid. These
		//		methods no longer target the front document when pass UIDRef::gNull. Callers
		//		should get the front document if that is the intended target. [mburbidg 11-14-03]
		
		// the undo history
		virtual bool16 CanUndo(const UIDRef &target) = 0;	
		virtual int32 GetUndoStepCount(const UIDRef &target) = 0;
		virtual void GetNthUndoStepName(PMString *text, int32 n, const UIDRef &target) = 0;
		virtual ErrorCode Undo(int32 steps, const UIDRef &target) = 0;
		
		// the redo history
		virtual bool16 CanRedo(const UIDRef &target) = 0;
		virtual int32 GetRedoStepCount(const UIDRef &target) = 0;
		virtual void GetNthRedoStepName(PMString *text, int32 n, const UIDRef &target) = 0;
		virtual ErrorCode Redo(int32 steps, const UIDRef &target) = 0;
		
		// delete all history data for the given target
		virtual void Discard(const UIDRef &target) = 0;
		virtual void Disable(const UIDRef &target) = 0;
		virtual void Enable(const UIDRef &target) = 0;		
		virtual bool16 BeginPush(int32 numItems) = 0;
		virtual void Push(const CmdStackItem &item) = 0;
		virtual void EndPush() = 0;		
		virtual bool16 Enabled(const UIDRef &target) const = 0;

		// For Internal use only.
		virtual bool16 DiscardRedo(const UIDRef &target) = 0;
};

#endif // __ICMDHISTORY__