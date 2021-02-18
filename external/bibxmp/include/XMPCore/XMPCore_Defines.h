#ifndef __XMPCore_Defines_h__
#define __XMPCore_Defines_h__ 1

// =================================================================================================
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

// =================================================================================================
// XMPCoreDefines.h - Common Defines for XMP Core component
// ================================================================
//
// This header defines common definitions to be used in XMP Core component.
//
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm/dd/yy who Description of changes, most recent on top.
//
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 04-11-14 ADC 1.0-m019 [3739647] Find a Strategy to resolve the issues of "multiple definitions" faced
//						 by clients while integrating the new builds containing Compare and Merge.
// 01-30-14 ADC 1.0-m001 First version
//
// =================================================================================================
#endif // AdobePrivate

// =================================================================================================
// All Platform Settings
// ===========================
#include "XMPCommon/XMPCommonDefines.h"

// =================================================================================================
// Macintosh Specific Settings
// ===========================
#if XMP_MacBuild
	#define ENABLE_NEW_DOM_MODEL 1
#endif

// =================================================================================================
// IOS Specific Settings
// ===========================
#if XMP_iOSBuild
	#define ENABLE_NEW_DOM_MODEL 1
#endif

// =================================================================================================
// Windows Specific Settings
// =========================
#if XMP_WinBuild
	#define ENABLE_NEW_DOM_MODEL 1
#endif

// =================================================================================================
// UNIX Specific Settings
// ======================
#if XMP_UNIXBuild
	#define ENABLE_NEW_DOM_MODEL 0
#endif

#ifndef ENABLE_NEW_DOM_MODEL
	#define ENABLE_NEW_DOM_MODEL 0
#endif

#if ENABLE_NEW_DOM_MODEL
	#define NS_XMPCORE AdobeXMPCore
#endif

#endif  // __XMPCore_Defines_h__
