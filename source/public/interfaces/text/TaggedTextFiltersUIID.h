//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TaggedTextFiltersUIID.h $
//  
//  Owner: Rahul Shinde
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
//  Contains IDs used by the TextExport plug-in
//  
//========================================================================================

#ifndef __TaggedTextFiltersUIID__
#define __TaggedTextFiltersUIID__

//Excluded by Manoj Gupta
//#include "TaggedTextBuildNumber.h"
#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTaggedTextFiltersUIPrefix	 RezLong(0x8b00)

// Plugin ID 
#define kTaggedTextFiltersUIPluginName			"Tagged Text Filters UI" 
DECLARE_PMID(kPlugInIDSpace, kTaggedTextFiltersUIPluginID, kTaggedTextFiltersUIPrefix + 1)

// All class IDs and implementation IDs for the plug-in are added in this file

//<Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGGEDTEXTEXPORTPREFERENCES, kTaggedTextFiltersUIPrefix + 1)

// <Class ID>
//gap
DECLARE_PMID(kClassIDSpace, kTaggedTextExportDriverMenuBoss, kTaggedTextFiltersUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTaggedTextExportSetupDialogBoss, kTaggedTextFiltersUIPrefix + 3)

// ---- Moved from Tagged Text Import Filter plug-in
DECLARE_PMID(kClassIDSpace, kTaggedTextImportSetupDialogBoss, kTaggedTextFiltersUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTaggedTextWarningListDialogBoss, kTaggedTextFiltersUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTaggedTextWarningListWidgetBoss, kTaggedTextFiltersUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kTaggedTextImportDriverMenuBoss, kTaggedTextFiltersUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTaggedTextParseSetupDialogBoss, kTaggedTextFiltersUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTaggedTextTranslatorSetupDialogBoss, kTaggedTextFiltersUIPrefix + 9)
// ---- end move.

DECLARE_PMID(kClassIDSpace, kTaggedTextWarningServiceBoss, kTaggedTextFiltersUIPrefix + 11)

// <Implementation ID>
// gap
DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportPreferences_Obsolete, kTaggedTextFiltersUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportDialogObserver, kTaggedTextFiltersUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportDialogController, kTaggedTextFiltersUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportDriverMenu, kTaggedTextFiltersUIPrefix + 7)

// ---- Moved from Tagged Text Import Filter plug-in
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportDialogObserver, kTaggedTextFiltersUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportDialogController, kTaggedTextFiltersUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextWarningListDialogObserver, kTaggedTextFiltersUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextWarningListDialogController, kTaggedTextFiltersUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportDriverMenu, kTaggedTextFiltersUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextParseDialogObserver, kTaggedTextFiltersUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextParseDialogController, kTaggedTextFiltersUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextTranslatorDialogObserver, kTaggedTextFiltersUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextTranslatorDialogController, kTaggedTextFiltersUIPrefix + 16)
// gap
// ---- end move.

DECLARE_PMID(kImplementationIDSpace, kTaggedTextExportPrefsSetupUIImpl, kTaggedTextFiltersUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextImportPrefsSetupUIImpl, kTaggedTextFiltersUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kTaggedTextWarningHandlerUIImpl, kTaggedTextFiltersUIPrefix + 20)

//<Widget ID>
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportVerboseRadioButtonId, kTaggedTextFiltersUIPrefix + 1 )
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportAbbrRadioButtonId, kTaggedTextFiltersUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportDialogEncodingPopUpId, kTaggedTextFiltersUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportDialogClusterPanel, kTaggedTextFiltersUIPrefix + 4)

DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportFilterWidgetID0, kTaggedTextFiltersUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportFilterWidgetID1, kTaggedTextFiltersUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportFilterWidgetID2, kTaggedTextFiltersUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextExportFilterWidgetID3, kTaggedTextFiltersUIPrefix + 8)

DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportDialogGroupPanel, kTaggedTextFiltersUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterTitleTextWidgetId, kTaggedTextFiltersUIPrefix + 11 )

DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportCheckBoxId, kTaggedTextFiltersUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextWarningText, kTaggedTextFiltersUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextWarningStdListBoxId, kTaggedTextFiltersUIPrefix + 14 )
DECLARE_PMID(kWidgetIDSpace, kTaggedTextUIMultilineTextBoxScrollBar, kTaggedTextFiltersUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextUIMultilineTextBox, kTaggedTextFiltersUIPrefix + 16)

DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID0, kTaggedTextFiltersUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID1, kTaggedTextFiltersUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID2, kTaggedTextFiltersUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID3, kTaggedTextFiltersUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID4, kTaggedTextFiltersUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID5, kTaggedTextFiltersUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID6, kTaggedTextFiltersUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID7, kTaggedTextFiltersUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID8, kTaggedTextFiltersUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID9, kTaggedTextFiltersUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetID10, kTaggedTextFiltersUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextParseEditBoxID, kTaggedTextFiltersUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextSourceFileEditBoxID, kTaggedTextFiltersUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextTargetFileEditBoxID, kTaggedTextFiltersUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextTranslatorDialogEncodingPopUpId, kTaggedTextFiltersUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextTranslatorDialogSourceEncodingPopUpId, kTaggedTextFiltersUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kContinueButtonWidgetID, kTaggedTextFiltersUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kSaveLogButtonId, kTaggedTextFiltersUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kWarningCancelButtonId, kTaggedTextFiltersUIPrefix + 36)

DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetTextID1, kTaggedTextFiltersUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kTaggedTextImportFilterWidgetTextID2, kTaggedTextFiltersUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kTTImportUseTypographersQuotesWidgetId, kTaggedTextFiltersUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kTTImportRetainFormattingWidgetId, kTaggedTextFiltersUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kTTImportStyleDefDropDownWidgetID, kTaggedTextFiltersUIPrefix + 41)

//<Ignore>
//Resource IDs

#define kTaggedTextExportDialogSetupPaletteRsrcID		1000
#define kTaggedTextImportDialogSetupPaletteRsrcID		1100
#define kTaggedTextWarningListPaletteRsrcID				1200
#define kTaggedTextImportParseSetupPaletteRsrcID  		1300
#define kTaggedTextImportTranslatorSetupPaletteRsrcID	1400

#define mTagTextFilterMenuID							1500
#define mTagTextExportFilterMenuID						1600	 

//Menu Ids
#define mExport		1
#define mTranslate	2
#define mExportPref 3
#define mTagTextExportFilter 4
#define mTaggedTextExportMain 5

#endif // __TaggedTextFiltersUIID__
