//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DragontailBuildNumber.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __DragonTailBuildNumber_h__
#define __DragonTailBuildNumber_h__


// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.

#define kDragontailVersionNumber 3.0 

// ----- This represents the product version number in the form it will
//		 be used for id-highprofile plug-in rapid releases.

#define kDragontailVersionNumberStr "3.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user.

#define kDragontailUIVersionNumberStr "CS"

// ----- Used for plug-in actual and expected version numbers
#define kDragontailMajorVersionNumber RezLong(3)
#define kDragontailMinorVersionNumber RezLong(0)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kDragontailMajorVersionNumberForResource 3
#define kDragontailMinorVersionNumberForResource 0

// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2003, 2000-2004, etc.
#ifdef MACINTOSH
#define kDragontailVersionCopyRightStr "3.0, Copyright 2000-2003 Adobe Systems Incorporated. All rights reserved."
#endif
#ifdef WINDOWS
#define kDragontailVersionCopyRightStr "Copyright 2000-2003 Adobe Systems Incorporated. All rights reserved."
#define kDragontailShortCopyRightStr "Copyright 2000-2003 Adobe Systems Incorporated."
#endif

// ----- Scripting DOM Version
#define kDragontailMajorScriptVersionNumber	RezLong(3)
#define kDragontailMinorScriptVersionNumber	RezLong(0)

// {7f5c34b5-175b-4479-a56c-73d752368a8f}
#define kInDesign3_0_CLSID			{ 0x7F5C34B5, 0x175B, 0x4479, { 0xA5, 0x6C, 0x73, 0xD7, 0x52, 0x36, 0x8A, 0x8F } }
// {6926C15F-E97E-4b13-8658-A97D8C616945}
#define kInDesignSUTypeLib3_0_CLSID	{ 0x6926c15f, 0xe97e, 0x4b13, { 0x86, 0x58, 0xa9, 0x7d, 0x8c, 0x61, 0x69, 0x45 } }
// {37C455EE-2C40-4e24-899A-7B533396FAE9}
#define kInDesignMUTypeLib3_0_CLSID	{ 0x37c455ee, 0x2c40, 0x4e24, { 0x89, 0x9a, 0x7b, 0x53, 0x33, 0x96, 0xfa, 0xe9 } }

// {B47074D9-7F10-4683-8672-00DE24D55D4B}
#define kInCopy3_0_CLSID			{ 0xb47074d9, 0x7f10, 0x4683, { 0x86, 0x72, 0x0, 0xde, 0x24, 0xd5, 0x5d, 0x4b } }
// {B8C5B92E-C373-401a-973F-9DD03FEF0490}
#define kInCopySUTypeLib3_0_CLSID	{ 0xb8c5b92e, 0xc373, 0x401a, { 0x97, 0x3f, 0x9d, 0xd0, 0x3f, 0xef, 0x4, 0x90 } }
// {6EA7F0E0-A327-4e2f-8879-60870FDEE5A2}
#define kInCopyMUTypeLib3_0_CLSID	{ 0x6ea7f0e0, 0xa327, 0x4e2f, { 0x88, 0x79, 0x60, 0x87, 0xf, 0xde, 0xe5, 0xa2 } }

#endif
