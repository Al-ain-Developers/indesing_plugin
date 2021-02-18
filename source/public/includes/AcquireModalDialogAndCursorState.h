//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AcquireModalDialogAndCursorState.h $
//  
//  Owner: Michael Easter
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
#ifndef __AcquireModalDialogAndCursorState__
#define __AcquireModalDialogAndCursorState__

#include "AcquireModalDialogState.h"

class IEventHandler;

#pragma export on

/**
 Helper object class used to acquire, manipulate, and release an external modal dialog.

 This helper can be either stack or heap allocated depending on how far flung the two
 ends of the modality are. If it all happens within the body of a single function or
 single function call chain, then stack based is preferred. If the start and end are in
 separate functions, then heap based should be used.
*/
class WIDGET_DECL AcquireModalDialogAndCursorState
{
public:
	/**
	 Constructs the object and deactivates palettes, acquires a modal dialog cursor
	 state, and grabs the cursor focus.
	 @param isDVAOwnedWindow: specifies if we setting modal windows state for DVA owned window, do not need push modal NULL modal window
	 */
	AcquireModalDialogAndCursorState(bool isDVAOwnedWindow = false);

	/**
	 Constructs the object and deactivates palettes, acquires a cursor state in the
	 specified mode, and grabs the cursor focus.
	 @param isDVAOwnedWindow: specifies if we setting modal windows state for DVA owned window, do not need push modal NULL modal window
	 @param modalCursorType	IN Cursor state mode to acquire
	 */
	AcquireModalDialogAndCursorState(int16 modalCursorType, bool isDVAOwnedWindow = false);

	/**
	 Destructs the object and reactivates palettes, releases the modal cursor state,
	 and restores the cursor focus.
	 */
	virtual ~AcquireModalDialogAndCursorState();
	
	/**
	 Signals that an external modal dialog is currently active.
	 */
	static bool IsExternalModalDialogRunning() {return fgExternalModalDialogState != 0;}

private:
	void GrabCursorFocus(bool isDVAOwnedWindow);

#if defined (MACINTOSH)
    class OSDialogActiveStackSwitch;
    OSDialogActiveStackSwitch*  fOSDialogActiveStackSwitch;
#endif
    
	AcquireModalDialogState*    fAcquireModalgState;
	
	static uint16				fgExternalModalDialogState;
};

#pragma export off

#endif 

