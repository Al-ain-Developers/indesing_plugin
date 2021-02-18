//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/CompositeFontMgrID.h $
//  
//  Owner: mjessett
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

#ifndef __CompositeFontMgrID__
#define __CompositeFontMgrID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCompositeFontMgrPrefix	 	RezLong(0xcb00)

//========================================================================================
// <PluginID>
//========================================================================================
#define kCompositeFontManagerPluginName 	"CompositeFontManager"
DECLARE_PMID(kPlugInIDSpace, kCompositeFontManagerPluginID, kCompositeFontMgrPrefix + 1)

//========================================================================================
// <Class ID>
//========================================================================================
//gap
DECLARE_PMID(kClassIDSpace, kCompositeFontBoss, kCompositeFontMgrPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCompFontDataSettingsBoss, kCompositeFontMgrPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCompFontCharRangeBoss, kCompositeFontMgrPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCompositeFontConversionProviderBoss, kCompositeFontMgrPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCompFontConversionProviderBoss, kCompositeFontMgrPrefix + 6)	//Schema-based conversion provider

DECLARE_PMID(kClassIDSpace, kNewCompositeFontCmdBoss, kCompositeFontMgrPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDeleteCompositeFontCmdBoss, kCompositeFontMgrPrefix + 11)
DECLARE_PMID(kClassIDSpace, kEditCompositeFontCmdBoss, kCompositeFontMgrPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCopyCompositeFontCmdBoss, kCompositeFontMgrPrefix + 13)
DECLARE_PMID(kClassIDSpace, kLoadCompositeFontCmdBoss, kCompositeFontMgrPrefix + 14)

DECLARE_PMID(kClassIDSpace, kCompFontNewWSResponderBoss, kCompositeFontMgrPrefix + 15)
DECLARE_PMID(kClassIDSpace, kCompFontNewDocResponderBoss, kCompositeFontMgrPrefix + 16)
DECLARE_PMID(kClassIDSpace, kCompFontOpenDocResponderBoss, kCompositeFontMgrPrefix + 17)
DECLARE_PMID(kClassIDSpace, kCompFontSaveACopyDocResponderBoss, kCompositeFontMgrPrefix + 18)
DECLARE_PMID(kClassIDSpace, kCompFontRevertDocResponderBoss, kCompositeFontMgrPrefix + 19)

DECLARE_PMID(kClassIDSpace, kCreateFontCMapCmdBoss, kCompositeFontMgrPrefix + 20)
DECLARE_PMID(kClassIDSpace, kDeleteFontCMapCmdBoss, kCompositeFontMgrPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCreateDummyFontCMapCmdBoss, kCompositeFontMgrPrefix + 22)
DECLARE_PMID(kClassIDSpace, kReadCompareCompositeFontCmdBoss, kCompositeFontMgrPrefix + 23)
DECLARE_PMID(kClassIDSpace, kReplaceCompositeFontCmdBoss, kCompositeFontMgrPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSaveCompositeFontCmdBoss, kCompositeFontMgrPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCreateFontInBookCmdBoss, kCompositeFontMgrPrefix + 26)
DECLARE_PMID(kClassIDSpace, kDeleteFontInBookCmdBoss, kCompositeFontMgrPrefix + 27)
DECLARE_PMID(kClassIDSpace, kAddCompFontClassCmdBoss, kCompositeFontMgrPrefix + 28)

DECLARE_PMID(kClassIDSpace, kCompFontStartupShutdownBoss, kCompositeFontMgrPrefix + 31)

//DECLARE_PMID(kClassIDSpace, kCompFontOpenDocResponderBoss2, kCompositeFontMgrPrefix + 32)
//DECLARE_PMID(kClassIDSpace, kCompFontNewDocResponderBoss2, kCompositeFontMgrPrefix + 33)

//// font menu
//DECLARE_PMID(kClassIDSpace, kCompFontMenuComponentBoss, kCompositeFontMgrPrefix + 31)

// CompFontNewNameDlg
// gap
// gap
// gap
// gap

#ifdef DEBUG
//DECLARE_PMID(kClassIDSpace, kCompFontTestMenuBoss, kCompositeFontMgrPrefix + 100)	// moved to CompFontDlg
#endif

DECLARE_PMID(kClassIDSpace, kCompositeFontScriptProviderBoss, kCompositeFontMgrPrefix + 182)
DECLARE_PMID(kClassIDSpace, kCompositeFontEntryScriptProviderBoss, kCompositeFontMgrPrefix + 183)
DECLARE_PMID(kClassIDSpace, kCompositeFontSettingsMigrationBoss, kCompositeFontMgrPrefix + 184)

//========================================================================================
// ----- Interface IDs -----
//========================================================================================
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITEFONT, kCompositeFontMgrPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPFONTDATASETTINGS, kCompositeFontMgrPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPFONTCHARRANGE, kCompositeFontMgrPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITEFONTLIST, kCompositeFontMgrPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPFONTTEXTOBSERVER, kCompositeFontMgrPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITEFONTMGR, kCompositeFontMgrPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPFONTOPENDOCOBSERVER, kCompositeFontMgrPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITEFONTUTILS, kCompositeFontMgrPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITEFONTDLGPREFS, kCompositeFontMgrPrefix + 9)

//========================================================================================
// ----- Implementation IDs -----
//========================================================================================

// gap
DECLARE_PMID(kImplementationIDSpace, kCompositeFontImpl, kCompositeFontMgrPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCompFontDataSettingsImpl, kCompositeFontMgrPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCompFontCharRangeImpl, kCompositeFontMgrPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontListImpl, kCompositeFontMgrPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontDlgPrefsImpl, kCompositeFontMgrPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontConversionImpl, kCompositeFontMgrPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontMgrImpl, kCompositeFontMgrPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kNewCompositeFontCmdImpl, kCompositeFontMgrPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kDeleteCompositeFontCmdImpl, kCompositeFontMgrPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kEditCompositeFontCmdImpl, kCompositeFontMgrPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCopyCompositeFontCmdImpl, kCompositeFontMgrPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kLoadCompositeFontCmdImpl, kCompositeFontMgrPrefix + 14)

DECLARE_PMID(kImplementationIDSpace, kCompFontNewWSResponderImpl, kCompositeFontMgrPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCompFontNewDocResponderImpl, kCompositeFontMgrPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCompFontDocResponderImpl, kCompositeFontMgrPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCompFontSaveACopyDocResponderImpl, kCompositeFontMgrPrefix + 18)
//gap

DECLARE_PMID(kImplementationIDSpace, kCreateFontCMapCmdImpl, kCompositeFontMgrPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kDeleteFontCMapCmdImpl, kCompositeFontMgrPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCreateDummyFontCMapCmdImpl, kCompositeFontMgrPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kReadCompareCompositeFontCmdImpl, kCompositeFontMgrPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kReplaceCompositeFontCmdImpl, kCompositeFontMgrPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSaveCompositeFontCmdImpl, kCompositeFontMgrPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCreateFontInBookCmdImpl, kCompositeFontMgrPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kDeleteFontInBookCmdImpl, kCompositeFontMgrPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kAddCompFontClassCmdImpl, kCompositeFontMgrPrefix + 28)

DECLARE_PMID(kImplementationIDSpace, kCompFontTextObserverImpl, kCompositeFontMgrPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCompFontOpenDocObserverImpl, kCompositeFontMgrPrefix + 32)

DECLARE_PMID(kImplementationIDSpace, kCompFontStartupShutdownImpl, kCompositeFontMgrPrefix + 35)

#ifdef DEBUG
//DECLARE_PMID(kImplementationIDSpace, kCompFontTestMenuImpl, kCompositeFontMgrPrefix + 100)	// moved to CompFontDlg
#endif

DECLARE_PMID(kImplementationIDSpace, kCompositeFontScriptProviderImpl, kCompositeFontMgrPrefix + 222)
//gap
DECLARE_PMID(kImplementationIDSpace, kCompositeFontScriptImpl, kCompositeFontMgrPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontEntryScriptProviderImpl, kCompositeFontMgrPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontUtilsImpl, kCompositeFontMgrPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontEntryScriptImpl, kCompositeFontMgrPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kCompositeFontSettingsMigrationImpl, kCompositeFontMgrPrefix + 228)

//========================================================================================
// ----- Widget IDs -----
//========================================================================================
// CompFontNewNameDlg

//========================================================================================
// ----- Error IDs -----
//========================================================================================
// CompositeFont::ReadWriteRffFile
DECLARE_PMID(kErrorIDSpace, kCompFontReadWritePSStringErr, kCompositeFontMgrPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCompFontReadWriteLineErr, kCompositeFontMgrPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kCompFontGetPSFontNameErr, kCompositeFontMgrPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCompFontReadWriteRffFileErr, kCompositeFontMgrPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCompFontSetFontUIDandStyleErr, kCompositeFontMgrPrefix + 5)

// CreateFontCMapCmd
DECLARE_PMID(kErrorIDSpace, kGetCompositeFontFolderErr, kCompositeFontMgrPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kGetCompositeFontFilenameErr, kCompositeFontMgrPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCompFontCreateSetFolderErr, kCompositeFontMgrPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kCompFontCanNotOpenFileErr, kCompositeFontMgrPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kCreateFontCMapCmdErr, kCompositeFontMgrPrefix + 15)

// DeleteFontCMapCmd
DECLARE_PMID(kErrorIDSpace, kCompFontDeleteFontCMapCmdErr, kCompositeFontMgrPrefix + 21)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kCompFontInvalHandlerID, kCompositeFontMgrPrefix + 1 )

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFontObjectScriptElement,			kCompositeFontMgrPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kCompositeFontEntryObjectScriptElement,	kCompositeFontMgrPrefix + 51)

//Events
//DECLARE_PMID(kScriptInfoIDSpace, ,		kCompositeFontMgrPrefix + 150)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kRelativeSizePropertyScriptElement,			kCompositeFontMgrPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kCharactersPropertyScriptElement,				kCompositeFontMgrPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kScaleAdjustmentPropertyScriptElement,			kCompositeFontMgrPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kCompFontBaselineShiftPropertyScriptElement,	kCompositeFontMgrPrefix + 163)

//Enums


//GUIDS
// {CF1DB2C0-DDB1-11d3-9D01-00C04F99131A},
#define kCompositeFont_CLSID {0xCF1DB2C0, 0xDDB1, 0x11d3, { 0x9D, 0x01, 0x00, 0xC0, 0x4F, 0x99, 0x13, 0x1A } }
// {CF1DB2BF-DDB1-11d3-9D01-00C04F99131A}
#define kCompositeFonts_CLSID {0xcf1db2bf, 0xddb1, 0x11d3, { 0x9d, 0x01, 0x00, 0xc0, 0x4f, 0x99, 0x13, 0x1a } }
// {33F7ECF2-F944-11d3-BF66-00004C374EFD}
#define kCompositeFontEntry_CLSID { 0x33f7ecf2, 0xf944, 0x11d3, { 0xbf, 0x66, 0x0, 0x0, 0x4c, 0x37, 0x4e, 0xfd } }
// {C33267E8-E8B0-11d3-9D01-00C04F99131A}
#define kCompositeFontEntries_CLSID { 0xc33267e8, 0xe8b0, 0x11d3, { 0x9d, 0x1, 0x0, 0xc0, 0x4f, 0x99, 0x13, 0x1a } }

#endif // __CompositeFontMgrID__
