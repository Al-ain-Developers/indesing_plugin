//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/keyboarddefs.h $
//  
//  Owner: Frits Habermann
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
//  This file lists a number of helpful defines for typical keyboard character codes.
//  
//========================================================================================

#pragma once
#ifndef __KEYBOARDDEFS__
#define __KEYBOARDDEFS__

#include "VirtualKey.h"

// special virtual key
extern PUBLIC_DECL const VirtualKey kVirtualNullKey;

extern PUBLIC_DECL const VirtualKey kVirtualInsertKey;
extern PUBLIC_DECL const VirtualKey kVirtualBackspaceKey;
extern PUBLIC_DECL const VirtualKey kVirtualDeleteKey;
extern PUBLIC_DECL const VirtualKey kVirtualTabKey;
extern PUBLIC_DECL const VirtualKey kVirtualReturnKey;
extern PUBLIC_DECL const VirtualKey kVirtualEnterKey;
extern PUBLIC_DECL const VirtualKey kVirtualHelpKey;
extern PUBLIC_DECL const VirtualKey kVirtualPageUpKey;
extern PUBLIC_DECL const VirtualKey kVirtualPageDownKey;
extern PUBLIC_DECL const VirtualKey kVirtualHomeKey;
extern PUBLIC_DECL const VirtualKey kVirtualEndKey;
extern PUBLIC_DECL const VirtualKey kVirtualUpArrowKey;
extern PUBLIC_DECL const VirtualKey kVirtualDownArrowKey;
extern PUBLIC_DECL const VirtualKey kVirtualRightArrowKey;
extern PUBLIC_DECL const VirtualKey kVirtualLeftArrowKey;

extern PUBLIC_DECL const VirtualKey kVirtualEscapeKey;
extern PUBLIC_DECL const VirtualKey kVirtualClearKey;
extern PUBLIC_DECL const VirtualKey kVirtualNumLockKey;
extern PUBLIC_DECL const VirtualKey kVirtualScrollLockKey;
extern PUBLIC_DECL const VirtualKey kVirtualPauseKey;
extern PUBLIC_DECL const VirtualKey kVirtualSpaceKey;

extern PUBLIC_DECL const VirtualKey kFunctionKey1;
extern PUBLIC_DECL const VirtualKey kFunctionKey2;
extern PUBLIC_DECL const VirtualKey kFunctionKey3;
extern PUBLIC_DECL const VirtualKey kFunctionKey4;
extern PUBLIC_DECL const VirtualKey kFunctionKey5;
extern PUBLIC_DECL const VirtualKey kFunctionKey6;
extern PUBLIC_DECL const VirtualKey kFunctionKey7;
extern PUBLIC_DECL const VirtualKey kFunctionKey8;
extern PUBLIC_DECL const VirtualKey kFunctionKey9;
extern PUBLIC_DECL const VirtualKey kFunctionKey10;
extern PUBLIC_DECL const VirtualKey kFunctionKey11;
extern PUBLIC_DECL const VirtualKey kFunctionKey12;
extern PUBLIC_DECL const VirtualKey kFunctionKey13;
extern PUBLIC_DECL const VirtualKey kFunctionKey14;
extern PUBLIC_DECL const VirtualKey kFunctionKey15;
extern PUBLIC_DECL const VirtualKey kFunctionKey16;
extern PUBLIC_DECL const VirtualKey kFunctionKey17;
extern PUBLIC_DECL const VirtualKey kFunctionKey18;
extern PUBLIC_DECL const VirtualKey kFunctionKey19;
extern PUBLIC_DECL const VirtualKey kFunctionKey20;
extern PUBLIC_DECL const VirtualKey kFunctionKey21;
extern PUBLIC_DECL const VirtualKey kFunctionKey22;
extern PUBLIC_DECL const VirtualKey kFunctionKey23;
extern PUBLIC_DECL const VirtualKey kFunctionKey24;

// Keypad Keys
extern PUBLIC_DECL const VirtualKey kNumericPad0;
extern PUBLIC_DECL const VirtualKey	kNumericPad1;
extern PUBLIC_DECL const VirtualKey	kNumericPad2;
extern PUBLIC_DECL const VirtualKey	kNumericPad3;
extern PUBLIC_DECL const VirtualKey	kNumericPad4;
extern PUBLIC_DECL const VirtualKey	kNumericPad5;
extern PUBLIC_DECL const VirtualKey	kNumericPad6;
extern PUBLIC_DECL const VirtualKey	kNumericPad7;
extern PUBLIC_DECL const VirtualKey	kNumericPad8;
extern PUBLIC_DECL const VirtualKey	kNumericPad9;
extern PUBLIC_DECL const VirtualKey	kNumericPadPeriod;
extern PUBLIC_DECL const VirtualKey	kNumericPadSubtract;
extern PUBLIC_DECL const VirtualKey	kNumericPadAdd;
extern PUBLIC_DECL const VirtualKey	kNumericPadMultiply;
extern PUBLIC_DECL const VirtualKey	kNumericPadDivide;

// Modifiers Keys
// 
extern PUBLIC_DECL const VirtualKey	kVirtualMacControlKey;	// no equivalent on Windows
extern PUBLIC_DECL const VirtualKey	kVirtualShiftKey;
extern PUBLIC_DECL const VirtualKey	kVirtualOptionAltKey;			// this is a WM_SYSKEYDOWN / WM_SYSKEYUP message
extern PUBLIC_DECL const VirtualKey	kVirtualCapsLockKey;
extern PUBLIC_DECL const VirtualKey	kVirtualCmdKey; // this is Command key on Mac and Ctrl on Windows

#endif
