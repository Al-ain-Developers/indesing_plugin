//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AcquireModalCursor.h $
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
#ifndef __AcquireModalCursor__
#define __AcquireModalCursor__

#include "CursorSpec.h"
#include "ICursorMgr.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

class PUBLIC_DECL BaseAcquireModalCursor
{
	public:
		virtual ~BaseAcquireModalCursor();
		virtual void ChangeCursor(const CursorSpec& newspec) = 0;

};

//========================================================================================
// CLASS AcquireModalCursor

/** Helper object used to acquire, manipulate, and release a modal cursor.

	This helper can be either stack or heap allocated depending on how far flung the two ends of the cursor modality are. 
	If it all happens within the body of a single function or single function call chain, then stack based is preferred. 
	If the start and end are in separate functions, then heap based should be used.
*/
class PUBLIC_DECL AcquireModalCursor : public BaseAcquireModalCursor
{
	public:
		/** Installs the modal cursor. */
		AcquireModalCursor(const CursorSpec& newspec, int16 restoreCursor = ICursorMgr::kRecomputeNewCursor);
		/** Installs a modal arrow cursor. */
		AcquireModalCursor(int16 restoreCursor = ICursorMgr::kRecomputeNewCursor);
		/** Removes the modal cursor, and restores the previous cursor or recomputes a new one. */
		virtual ~AcquireModalCursor();

		/** Sets the cursor */
		virtual void ChangeCursor(const CursorSpec& newspec);
		
	protected:
		ModalCursorTicket	fTicket;
		ICursorMgr*		fCursorMgr;
};

//========================================================================================
// CLASS AcquireWaitCursor

/** Helper object used to acquire, manipulate, and release a wait cursor.

		AcquireWaitCursor should be used for changing the cursor to a watch for well understood intervals.

		This helper can be either stack or heap allocated depending on how far flung the two ends of the cursor wait period are. 
		If it all happens within the body of a single function or single function call chain, then stack based is preferred. 
		If the start and end are in separate functions, then heap based should be used.
*/
class PUBLIC_DECL AcquireWaitCursor : public BaseAcquireModalCursor
{
	public:
		/** Installs the busy cursor. */
		AcquireWaitCursor(); 
		/** Removes the busy cursor, and restores the previous cursor. */
		virtual ~AcquireWaitCursor();

		/** Calls Animate */
		virtual void ChangeCursor(const CursorSpec& newspec);	
		/** Call periodcally to ensure that the cursor continues to spin. */
		void Animate();			
		
	protected:
		ModalCursorTicket	fTicket;
		ICursorMgr*			fCursorMgr;
};

//========================================================================================
// CLASS AcquireDelayedBusyCursor

/**	Helper object used to acquire, manipulate, and release a automatic busy/wait cursor.

		AcquireDelayedBusyCursor should be used for situations where the amount of time to be spent is unknown, and the desired
		effect is to change the cursor to an animated busy cursor only after a predetermined amount of time elapses. Otherwise use
		AcquireWaitCursor.

		This helper can be either stack or heap allocated depending on how far flung the two ends of the cursor wait period are. 
		If it all happens within the body of a single function or single function call chain, then stack based is preferred. 
		If the start and end are in separate functions, then heap based should be used.
*/

class PUBLIC_DECL AcquireDelayedBusyCursor : public BaseAcquireModalCursor
{
	public:
		/** Installs the busy cursor after a finite delay. */
		AcquireDelayedBusyCursor();
		/** Removes the busy cursor, and restores the previous cursor. */
		virtual ~AcquireDelayedBusyCursor();

		/** Default implementation simply calls Animate */
		virtual void ChangeCursor(const CursorSpec& newspec);
		/** Call periodcally to ensure that the cursor continues to spin. */
		void Animate();
		
	protected:
		ModalCursorTicket	fTicket;
		ICursorMgr*			fCursorMgr;
};

//========================================================================================
// CLASS AcquireModalDialogCursor

/**	Helper object used to acquire, manipulate, and release the cursor for Modal Dialogs.

		The only difference between this class and AcquireModalCursor above, it that this one will override an existing AcquireWaitCursor.
		Since if a modal dialog appears in the middle of a long running command, it needs to be able to set it's cursor over that of say
		a progress bar.

		This helper can be either stack or heap allocated depending on how far flung the two ends of the cursor modality are. 
		If it all happens within the body of a single function or single function call chain, then stack based is preferred. 
		If the start and end are in separate functions, then heap based should be used.
*/

class PUBLIC_DECL AcquireModalDialogCursor : public BaseAcquireModalCursor
{
	public:
		/** Installs the modal cursor - superceding an active busy cursor if necessary. */
		AcquireModalDialogCursor(const CursorSpec& newspec, int16 restoreCursor = ICursorMgr::kRestorePreviousCursor);
		/** Installs a modal arrow cursor - superceding an active busy cursor if necessary.  */
		AcquireModalDialogCursor(int16 restoreCursor = ICursorMgr::kRestorePreviousCursor);
		/** Removes the modal cursor, and restores the previous cursor or recomputes a new one. */
		virtual ~AcquireModalDialogCursor();
		
		/** Sets the cursor */
		virtual void ChangeCursor(const CursorSpec& newspec);
		
	protected:
		ModalCursorTicket	fTicket;
		ICursorMgr*			fCursorMgr;
};



#pragma export off

#endif
