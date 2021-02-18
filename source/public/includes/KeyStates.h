//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/KeyStates.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __KeyStates_h__
#define __KeyStates_h__

#include "VirtualKey.h"

#pragma export on

// Helper functions for keys used as modifiers.
PUBLIC_DECL bool16 IsShiftKeyPressed();
PUBLIC_DECL bool16 IsCommandKeyPressed();
PUBLIC_DECL bool16 IsOptionAltKeyPressed();
PUBLIC_DECL bool16 IsMacControlKeyPressed();
PUBLIC_DECL bool16 IsSpaceKeyPressed();

// Helper function to return state of all the keys in one int16.
// See KBSCModifierDefs.h for information on how to decipher the return value.
PUBLIC_DECL int16 GetKBSCModifierKeys();

// Check for a specific key. Should be used in response
// to a key event, or else result may be stale (Windows only).
PUBLIC_DECL bool16 IsVirtualKeyPressed(const VirtualKey& theKey);

#pragma export off

#endif
