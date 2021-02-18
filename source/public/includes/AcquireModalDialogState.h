//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AcquireModalDialogState.h $
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
#ifndef __AcquireModalDialogState__
#define __AcquireModalDialogState__

#include "AcquireModalCursor.h"

#include "ISession.h"
#include "IDragDropController.h"

#pragma export on


//========================================================================================
// CLASS AcquireModalDialogState

/** Helper object used to acquire, manipulate, and release a modal dialog.
		On construction it deactivates palettes and acquires a modal cursor state, on destruction it reactivates palettes and
		releases the modal cursor state

		This helper can be either stack or heap allocated depending on how far flung the two ends of the modality are. 
		If it all happens within the body of a single function or single function call chain, then stack based is preferred. 
		If the start and end are in separate functions, then heap based should be used.
*/

class WIDGET_DECL AcquireModalDialogState
{
public:
	AcquireModalDialogState();
	AcquireModalDialogState(int16 modalCursorType);
	~AcquireModalDialogState();
	
	BaseAcquireModalCursor*	fModalCursor;
	SuppressExternalDragsDuringCriticalSection	fSuppressDrags;
};

//========================================================================================
// CLASS AcquireModalDialogState2

/** Helper object used to acquire, manipulate, and release a modal dialog.
		On construction it deactivates palettes, a separate method exists to acquires the modal cursor state, 
		on destruction it reactivates palettes and releases the modal cursor state

		AcquireModalDialogState2 exists because of an ordering issue in CDialog::Open where we needed to decouple
		palette deactivation from the acquisition of the modal cursor state.

		This helper can be either stack or heap allocated depending on how far flung the two ends of the modality are. 
		If it all happens within the body of a single function or single function call chain, then stack based is preferred. 
		If the start and end are in separate functions, then heap based should be used.
*/

class WIDGET_DECL AcquireModalDialogState2
{
public:
	AcquireModalDialogState2();
	~AcquireModalDialogState2();
	
	void AcquireModalDialogCursor(int16 modalCursorType);
	
	BaseAcquireModalCursor*	fModalCursor;
	SuppressExternalDragsDuringCriticalSection	fSuppressDrags;
};


#pragma export off


#endif 

