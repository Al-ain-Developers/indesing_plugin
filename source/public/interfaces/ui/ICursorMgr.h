//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ICursorMgr.h $
//  
//  Owner: Dave Burnard
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
#ifndef __ICURSORMGR__
#define __ICURSORMGR__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "CursorSpec.h"
#include "ISnapTo.h"


class ICursorProvider;
class ModalCursorTicket;


// ===================================================================================
//	class ICursorMgr
// ===================================================================================
/**
	Provides the interface required for maintaining the region
	associated with each cursor. Used by the application, to 
	figure out how to set the mouse cursor, and used by the 
	windows, to define what cursor should be used for which area
	of the screen.
	
	@see ICursorRegion, ICursorProvider, AcquireModalCursor, AcquireWaitCursor
*/
class ICursorMgr : public IPMUnknown 
{
	public:
		enum { kDefaultIID = IID_ICURSORMGR };

	/**
		A set of "cross platform" definitions for what effect the modifiers have.  
		For instance, is the Alt key equivalent to the Command key or the Option key?
		Luckily this "equivalence" is limited to the scope of cursor management, where
	  Alt is usually equivalent to Option.
	*/
	public:
		enum eCursorModifierState 
		{
			/** */
			kNoModifiers = 0x00, 
			/** */
			kCmdKey = 0x01, 
			/** */
			kShiftKey = 0x02, 
			/** */
			kCapsLockKey = 0x04, 
			/** */
			kOptionAltKey = 0x08, kAltKey = kOptionAltKey, kOptionKey = kOptionAltKey, 
			/** */
			kControlKey = 0x10,
			/** */
			kSpaceKey = 0x20
		};

	public:		 
		/** Get the current cursor by it's CursorID.
		*/
		virtual CursorID GetCursorID() = 0;

		/** Get the current cursor by it's CursorSpec.
		*/
		virtual CursorSpec GetCursorSpec() = 0;
			
		/** Sets the cursor provider to use for the tool area. Returns the
			old tool cursor provider. Called by the toolbox when the tool 
			is selected.
		*/
		virtual ICursorProvider* SetToolCursorProvider(ICursorProvider*) = 0;

		/** Used to lock/unlock the tool cursor provider so
			that the locked cursor is shown instead of the usual tool cursor 
		*/
		virtual void  LockToolCursor(bool16 lockit = kTrue) = 0;

		/** Used to compute a new cursor spec from an existing one given the snap type.
			Looks for a new cursor at kSnapToCrsrOffset from the currentSpec. The new CursorSpec
			is for a cursor that gives feedback to the user that the mouse is "snapped".
			If a cursor does not exist with this offset, the original cursor spec is returned.

			@param currentSpec IN the current cursor
			@param snapType IN type of snapping: kSnapX, kSnapY, kSnapXandY, kSnapNone
			@return the CursorSpec
		*/
		virtual CursorSpec GetSnapToCursorSpec(CursorSpec& currentSpec, SnapType snapType) = 0;		 

		/** Modal cursor states */
		enum {
			/** Not a modal cursor */
			kNoModalCursor = -1, 
			/** Modal cursor */
			kModalCursor = 0, 
			/** Modal busy cursor */
			kWaitCursor = 1, 
			/** Modal dialog cursor */
			kModalDialogCursor = 2, 
			/** Delayed modal busy cursor - doesn't appear for a second or so */
			kDelayedBusyCursor = 3
		};		
		/** Restoring the cursor */
		enum {
			/** Don't attempt to restore the old cursor - wait until CursorMgr decides to recompute. */
			kDontRestorePreviousCursor = 0, 
			/** Restore the previous cursor (saved when the modal state began) */
			kRestorePreviousCursor = 1, 
			/** Recompute a new cursor right away */
			kRecomputeNewCursor = 3,
		};

		/** @name INTERNAL USE ONLY
				These methods should not be called directly.
				Please use the AcquireModalCursor and AcquireWaitCursor helper classes instead.
		*/
		//@{ 
		/** Defaults to the arrow cursor*/
		virtual void BeginModalCursor(const ModalCursorTicket& callerID) = 0; 	
		/** */
		virtual void BeginModalCursor(const ModalCursorTicket& callerID, const CursorSpec& newspec) = 0;
		/** */
		virtual void ChangeModalCursor(const ModalCursorTicket& callerID, const CursorSpec& newspec) = 0;
		/** */
		virtual void EndModalCursor(const ModalCursorTicket& callerID) = 0;
		/** */
		virtual void BeginWaitCursor(const ModalCursorTicket& callerID) = 0;
		/** */
		virtual void AnimateWaitCursor(const ModalCursorTicket& callerID) = 0;
		/** */
		virtual void EndWaitCursor(const ModalCursorTicket& callerID) = 0;
		//@}
				
		/** Obtains the cursor appropriate for the given cursor provider, widgetUnderMouse,
			global coordinate, and modifier key combination, and makes it the current cursor.
		*/
		virtual void SetNewCursor(ICursorProvider *, IControlView *, GSysPoint, eCursorModifierState) = 0;

		/** Call this function when you need to reevaluate the cursor with
			it's default parameters
		*/
		virtual void SetNewCursor() = 0;
			
		/** Utility function that returns the constant that represents the
			tool cursor provider. So, for example:
			<code>UseToolCursorProvider(r);</code>
			is simply a shortcut for
			<code>UseCursorProvider(TheToolCursorProvider(), r);</code>
		*/
		virtual ICursorProvider* TheToolCursorProvider() const = 0; 
			
		/** Hide the cursor */
		virtual void Hide() = 0;
		/** Show the cursor */
		virtual void Show() = 0;
		/** Is the cursor hidden */
		virtual bool16 IsHidden() const = 0;
			
		/** Suspend the cursor manager. Called when the application has been suspended (no longer frontmost). */
		virtual void Suspend() = 0;
		/** Is the cursor manager suspended */
		virtual bool16 IsSuspended() const= 0;
		/** Resume the cursor manager. Called when the application has become frontmost again. */
		virtual void Resume() = 0;

		/** Stop all cursor tracking and reset the cursor to the arrow. Called during application shutdown.
		*/
		virtual void StopTrackingCursor() =0;
		 
			
		/** */
		virtual void Init() = 0;
		/** */
		virtual void Shutdown() = 0;
		
	public:
		enum {kSpinningBeachBall = 200, kSpinningWatch = 210, kCyclingArrow = 220};
		
		/** Hide the cursor until the user moves the mouse (this is most useful
			when the user begins to edit text).
		*/
		virtual void ObscureCursor() = 0;
			 
		/** To cancel effect of ObscureCursor without waiting for mouse to move
		*/
		virtual void UnobscureCursor() = 0;
			
		/** Call this periodically to ensure that the cursor keeps spinning.
		*/
		virtual void AnimateWaitCursor() = 0;
		

#if MACINTOSH
		/** Mac only: On the Mac the busy cursor will, by default, essentially spin as long as it takes for
			an operation needs to complete. You can control the amount of time the cursor will spin
			using this function. Note that timeout is in milliseconds. 
			Also, if Animate() is called the timeout counter will be reset.
		*/
		virtual void SetBusyCursorTimeout(int32 timeout) = 0;
		
			
		/** Mac only: On the Mac the automatic busy cursor will, by default, not appear until 1/4 second after
			the initial call. This prevents a series of commands from rapidly flashing the cursor.
			Note that the delay is specified in milliseconds.
		*/
		virtual void SetBusyCursorDelay(int32 delay) = 0;
		
			
		/** Mac only: The busy cursor defaults to kSpinningWatch (like PhotoShop). However
			you can specify a new 'acur' resource using this function.
		*/
		virtual void SetBusyCursorID(ResID id) = 0;
			
#endif

	protected:
		/** Utility function that returns whether keyboard modifiers affect the current cursor provider
		*/
		virtual bool16 ModifiersAffectProvider(IControlView *view) const = 0;

		/** Utility function that returns whether location information affects the current cursor provider
		*/
		virtual bool16 LocationAffectsProvider(IControlView *view) const = 0;

		/** Utility functions to compare modifiers to the cached ones.  NOTE: For now,
			HaveModifiersChanged should really only be called in one place in all of the program.  That's because
			HaveModifiersChanged resets the cached modifiers.  If HaveModifiersChanged is called in more than
			one place, you'll get unpredictable results.
		*/
		virtual bool16 HaveModifiersChanged(eCursorModifierState& oldModifiers, eCursorModifierState& newModifiers) = 0;
};


// ===================================================================================
//	class ModalCursorTicket
// ===================================================================================
/**	Used internally by the Cursor manager to keep track of modal cursor state transitions.
*/
class ModalCursorTicket {
	public:
	typedef base_type data_type;
		ModalCursorTicket(uint32 caller = 0xFFFFFFFF, int16 restore = ICursorMgr::kRestorePreviousCursor, int16 modalType = ICursorMgr::kModalCursor) :
			fModalType(modalType), fRestoreCursor(restore), fCallerID(caller) {}
		ModalCursorTicket(const ModalCursorTicket& other) :
			fModalType(other.fModalType), fRestoreCursor(other.fRestoreCursor), fCallerID(other.fCallerID)
		{
		}
		
		ModalCursorTicket& operator=(const ModalCursorTicket& other)
		{
			if (this != &other)
			{
				fModalType = other.fModalType;
				fRestoreCursor = other.fRestoreCursor;
				fCallerID = other.fCallerID;
			}
			return *this;
		}
		
		bool operator==(const ModalCursorTicket& other) const
		{
			if ((char*) this == (char*) &other)
				return kTrue;
			else if ((fCallerID == other.fCallerID) && (fModalType == other.fModalType))
				return kTrue;
			else 
				return kFalse;
		}

		int16	fModalType;
		int16	fRestoreCursor;
		uint32	fCallerID;
};

#endif // __ICURSORMGR__
