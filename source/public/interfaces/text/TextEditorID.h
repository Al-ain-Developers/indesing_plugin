//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextEditorID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __TextEditorID__
#define __TextEditorID__

#include "IconPNGDefs.h"

#ifndef MAC_RESOURCE_INCLUDER
	#include "CrossPlatformTypes.h"
	#include "IDFactory.h"
#endif

#define kTextEditorPrefix		RezLong(0x1d300)
#define kTextEditorPrefix2		RezLong(0xb800)
#define kTextEditorPrefix3		RezLong(0x20000)

// <Start IDC>
// PluginID
#define kTextEditorPluginName 	"Text Editor"

//---------------------------------------------------------------
// Resource IDs
//---------------------------------------------------------------

#define kIBeamToolDefRsrcID 				1800
#define kIBeamTouchToolDefRsrcID 			1801
#define kVerticalTextToolDefRsrcID 			1900

#define kIBeamIcon							1000
#define kVerticalTextToolIcon				1001
#define kOTTextWidgetIcon                   1002

//HiDPI Icons
#define kIBeamIconHiDPI						(kIBeamIcon + kHIDPIIconOffset)
#define kVerticalTextToolIconHiDPI			(kVerticalTextToolIcon + kHIDPIIconOffset)

#define kCompositionRunningIcon				1234  // debug only icon
#define kAnchoredObjectIcon					1300
#define kEndnoteAdornmentIcon				1301

//Butterfly resources
//All butterflies must be contiguous and in groups of three
#define kButterfly1							6001
#define kButterfly1a						6002
#define kButterfly1b						6003
#define kButterfly2							6004
#define kButterfly2a						6005
#define kButterfly2b						6006
#define kButterfly3							6007
#define kButterfly3a						6008
#define kButterfly3b						6009
#define kButterfly4							6010
#define kButterfly4a						6011
#define kButterfly4b						6012
#define kButterfly5							6013
#define kButterfly5a						6014
#define kButterfly5b						6015
#define kButterfly6							6016
#define kButterfly6a						6017
#define kButterfly6b						6018
#define kButterfly7							6019
#define kButterfly7a						6020
#define kButterfly7b						6021
#define kButterfly8							6022
#define kButterfly8a						6023
#define kButterfly8b						6024
#define kButterfly9							6025
#define kButterfly9a						6026
#define kButterfly9b						6027
#define kPin								6028
#define kBackground							6029

#define kNumberButterflyTypes				9

#ifndef MAC_RESOURCE_INCLUDER

DECLARE_PMID(kPlugInIDSpace, kTextEditorPluginID, kTextEditorPrefix + 1)

// <Service ID>
//---------------------------------------------------------------
// Service IDs
//---------------------------------------------------------------

DECLARE_PMID(kServiceIDSpace, kNonRomanService, kTextEditorPrefix + 1)		// see CJKID.h
DECLARE_PMID(kServiceIDSpace, kTextOffscreenService, kTextEditorPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kTextFrameDDTargetFlavorHelperService, kTextEditorPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kBeforeDragTextSignalResponderService, kTextEditorPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kBeforeDropTextSignalResponderService, kTextEditorPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kAfterDropTextSignalResponderService, kTextEditorPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kTextVariableDialogService, kTextEditorPrefix + 7)
DECLARE_PMID(kServiceIDSpace, kTextDDTargetFlavorHelperService, kTextEditorPrefix + 8)

// <Class ID>
//---------------------------------------------------------------
// Boss IDs
//---------------------------------------------------------------

DECLARE_PMID(kClassIDSpace, kTextEditorBoss, kTextEditorPrefix + 1)
DECLARE_PMID(kClassIDSpace, kIBeamTrackerBoss, kTextEditorPrefix + 2)
DECLARE_PMID(kClassIDSpace, kIBeamToolBoss, kTextEditorPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTextEditorTrackerRegisterBoss, kTextEditorPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTextSelectionBoss, kTextEditorPrefix + 5)
DECLARE_PMID(kClassIDSpace, kAnchoredObjectAdornmentBoss, kTextEditorPrefix + 6)
DECLARE_PMID(kClassIDSpace, kTableDragDropTextResponderBoss, kTextEditorPrefix + 7)
DECLARE_PMID(kClassIDSpace, kAnchObjDragDropTextResponderBoss, kTextEditorPrefix + 8)
DECLARE_PMID(kClassIDSpace, kFrameTrackerBoss, kTextEditorPrefix + 9)
DECLARE_PMID(kClassIDSpace, kInlineSelectionFilterBoss, kTextEditorPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTextSelectionTrackerBoss, kTextEditorPrefix + 11)
DECLARE_PMID(kClassIDSpace, kFrameToolBoss, kTextEditorPrefix + 12)
DECLARE_PMID(kClassIDSpace, kTextSelectionToolBoss, kTextEditorPrefix + 13)
DECLARE_PMID(kClassIDSpace, kTextSelectionSnapshotBoss, kTextEditorPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kActivateTextEditorCmdBoss, kTextEditorPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTextOffscreenBoss, kTextEditorPrefix + 16		)
//gap
DECLARE_PMID(kClassIDSpace, kOpenTypeAdornmentBoss, kTextEditorPrefix + 17)
DECLARE_PMID(kClassIDSpace, kILGMoveTrackerBoss, kTextEditorPrefix + 18)
DECLARE_PMID(kClassIDSpace, kILGRotateTrackerBoss, kTextEditorPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPrePlaceToolBoss, kTextEditorPrefix + 20 /* This is not a real boss, just a value to get to the PrePlaceTracker */)
DECLARE_PMID(kClassIDSpace, kVerticalTextToolBoss, kTextEditorPrefix + 21)
DECLARE_PMID(kClassIDSpace, kVerticalTextTrackerBoss, kTextEditorPrefix + 22)
DECLARE_PMID(kClassIDSpace, kVerticalFrameTrackerBoss, kTextEditorPrefix + 23)
DECLARE_PMID(kClassIDSpace, kGenericMoveTrackerBoss, kTextEditorPrefix + 24)
DECLARE_PMID(kClassIDSpace, kTextEditorKeyShortsBoss, kTextEditorPrefix + 25)
DECLARE_PMID(kClassIDSpace, kTextFrameILGMoveTrackerBoss, kTextEditorPrefix + 26)
DECLARE_PMID(kClassIDSpace, kTextTestMenuBoss, kTextEditorPrefix + 27)
DECLARE_PMID(kClassIDSpace, kLayoutDDTargetTextHelperBoss, kTextEditorPrefix + 28)
DECLARE_PMID(kClassIDSpace, kTablesDDTargetTextHelperBoss, kTextEditorPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTypeKeyShortsBoss, kTextEditorPrefix + 30)
DECLARE_PMID(kClassIDSpace, kApplyStyleShortcutsBoss, kTextEditorPrefix + 31)
DECLARE_PMID(kClassIDSpace, kTextFrameShortcutsBoss, kTextEditorPrefix + 32)
DECLARE_PMID(kClassIDSpace, kOpenTypePrefsConversionProviderBoss, kTextEditorPrefix + 33)
DECLARE_PMID(kClassIDSpace, kTextEditorMenuBoss, kTextEditorPrefix + 34)
// gap used by memory based object which moved into Text
// gap used by memory based object which moved into Text
//gap
DECLARE_PMID(kClassIDSpace, kComposerTestMenuBoss, kTextEditorPrefix + 39)
DECLARE_PMID(kClassIDSpace, kOldTextEditorShortcutContextBoss, kTextEditorPrefix + 40)
DECLARE_PMID(kClassIDSpace, kIBeamCursorHandlerBoss, kTextEditorPrefix + 41)

DECLARE_PMID(kClassIDSpace, kCJKTypeKeyShortsBoss, kTextEditorPrefix + 42)
DECLARE_PMID(kClassIDSpace, kIBeamFCSelectionHitTestHandlerBoss, kTextEditorPrefix + 43 )
DECLARE_PMID(kClassIDSpace, kIBeamFCCursorHandlerBoss, kTextEditorPrefix + 44 )
DECLARE_PMID(kClassIDSpace, kPrePlaceTrackerBoss, kTextEditorPrefix + 45)
DECLARE_PMID(kClassIDSpace, kTextTrackerRegisterBoss, kTextEditorPrefix + 46)
DECLARE_PMID(kClassIDSpace, kTextEditorStartupShutdownBoss, kTextEditorPrefix + 47)
DECLARE_PMID(kClassIDSpace, kFootnoteTextSelectTrackerBoss, kTextEditorPrefix + 48 )
DECLARE_PMID(kClassIDSpace, kTextOffScreenOpenDocResponderBoss, kTextEditorPrefix + 49 )
DECLARE_PMID(kClassIDSpace, kTextOffScreenNewDocResponderBoss, kTextEditorPrefix + 50 )
//DECLARE_PMID(kClassIDSpace, kTextEditorSuiteRegisterBoss, kTextEditorPrefix + 51 )
DECLARE_PMID(kClassIDSpace, kTextVariableDialogBoss, kTextEditorPrefix + 52 )
DECLARE_PMID(kClassIDSpace, kTextVariableNewEditCommonPanelBoss, kTextEditorPrefix + 53 )
DECLARE_PMID(kClassIDSpace, kTextVariableListBoxEHBoss, kTextEditorPrefix + 54 )
DECLARE_PMID(kClassIDSpace, kTextVariableLoadDialogBoss, kTextEditorPrefix + 55 )
DECLARE_PMID(kClassIDSpace, kTextVariableNewEditDialogBoss, kTextEditorPrefix + 56 )
DECLARE_PMID(kClassIDSpace, kTVMetaMenuComponentBoss, kTextEditorPrefix + 57 )
DECLARE_PMID(kClassIDSpace, kTVMetaCharButtonWidgetBoss, kTextEditorPrefix + 58 )
DECLARE_PMID(kClassIDSpace, kTextVariableMenuComponentBoss, kTextEditorPrefix + 59 )
DECLARE_PMID(kClassIDSpace, kDragDropTextCmdBoss, kTextEditorPrefix + 60)
DECLARE_PMID(kClassIDSpace, kDragDropTextSignalMgrBoss, kTextEditorPrefix + 61)
DECLARE_PMID(kClassIDSpace, kHyperlinkDragDropTextResponderBoss, kTextEditorPrefix + 62)
DECLARE_PMID(kClassIDSpace, kDeletedTextBeforeDragTextResponderBoss, kTextEditorPrefix + 63)
DECLARE_PMID(kClassIDSpace, kFootnoteDragDropTextResponderBoss, kTextEditorPrefix + 64)
DECLARE_PMID(kClassIDSpace, kSmartCutPasteBeforeDragDropTextResponderBoss, kTextEditorPrefix + 65)
DECLARE_PMID(kClassIDSpace, kSmartCutPasteAfterDragDropTextResponderBoss, kTextEditorPrefix + 66)
DECLARE_PMID(kClassIDSpace, kNoteDragDropTextResponderBoss, kTextEditorPrefix + 67)
DECLARE_PMID(kClassIDSpace, kDeletedTextBeforeDropTextResponderBoss, kTextEditorPrefix + 68)
DECLARE_PMID(kClassIDSpace, kRedlineBeforeDropTextResponderBoss, kTextEditorPrefix + 69)
DECLARE_PMID(kClassIDSpace, kRedlineAfterDropTextResponderBoss, kTextEditorPrefix + 70)
DECLARE_PMID(kClassIDSpace, kTVDateTimeMetaMenuComponentBoss, kTextEditorPrefix + 71 )
DECLARE_PMID(kClassIDSpace, kQuickApplyTextVariablesServiceBoss, kTextEditorPrefix + 72 )
DECLARE_PMID(kClassIDSpace, kAnchorToolBoss, kTextEditorPrefix + 73 )
DECLARE_PMID(kClassIDSpace, kAnchorTrackerBoss, kTextEditorPrefix + 74 )
DECLARE_PMID(kClassIDSpace, kPlaceHolderOptionsDialogBoss, kTextEditorPrefix + 75 )
DECLARE_PMID(kClassIDSpace, kCharacterAlternatesPopupWindowBoss, kTextEditorPrefix + 76 )
DECLARE_PMID(kClassIDSpace, kSetTypeContextualControlsCmdBoss, kTextEditorPrefix + 77 )
DECLARE_PMID(kClassIDSpace, kTypeContextualUIScriptProviderBoss, kTextEditorPrefix + 78)
DECLARE_PMID(kClassIDSpace, kTextEditorDrawServiceBoss, kTextEditorPrefix + 79 )
DECLARE_PMID(kClassIDSpace, kOpenTypeToolBoss, kTextEditorPrefix + 80)
DECLARE_PMID(kClassIDSpace, kOpenTypeTrackerBoss, kTextEditorPrefix + 81)
DECLARE_PMID(kClassIDSpace, kEndnoteAdornmentBoss, kTextEditorPrefix + 82)
DECLARE_PMID(kClassIDSpace, kEndnoteToolBoss, kTextEditorPrefix + 83)
DECLARE_PMID(kClassIDSpace, kEndnoteTrackerBoss, kTextEditorPrefix + 84)
DECLARE_PMID(kClassIDSpace, kTextFrameDDTargetFlavorHelperBoss, kTextEditorPrefix + 85)
DECLARE_PMID(kClassIDSpace, kGalleyDDTargetFlavorHelperBoss, kTextEditorPrefix + 86)
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 87 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 88 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 89 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 90 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 91 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 92 )
DECLARE_PMID(kClassIDSpace, kTextVariableDeleteDialogBoss, kTextEditorPrefix + 93 )
DECLARE_PMID(kClassIDSpace, kTextVariablePageCountDialogBoss, kTextEditorPrefix + 94 )
DECLARE_PMID(kClassIDSpace, kTextVariableDateDialogBoss, kTextEditorPrefix + 95 )
DECLARE_PMID(kClassIDSpace, kTextVariableFileNameDialogBoss, kTextEditorPrefix + 96 )
DECLARE_PMID(kClassIDSpace, kTextVariableCPStyleDialogBoss, kTextEditorPrefix + 97 )
DECLARE_PMID(kClassIDSpace, kTextVariableCustomTextDialogBoss, kTextEditorPrefix + 98 )

DECLARE_PMID(kClassIDSpace, kCharacterAlternateAdornmentBoss, kTextEditorPrefix + 99)

DECLARE_PMID(kClassIDSpace, kCopyEditorFeedbackDialogBoss, kTextEditorPrefix + 100)
DECLARE_PMID(kClassIDSpace, kSetCopyEditorAlertShownCountCmdBoss, kTextEditorPrefix + 101)
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 102 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 103 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 104 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 105 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 106 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 107 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 108 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 109 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 110 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 111 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 112 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 113 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 114 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 115 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 116 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 117 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 118 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 119 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 120 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 121 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 122 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 123 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 124 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 125 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 126 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 127 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 128 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 129 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 130 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 131 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 132 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 133 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 134 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 135 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 136 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 137 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 138 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 139 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 140 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 141 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 142 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 143 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 144 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 145 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 146 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 147 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 148 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 149 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 150 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 151 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 152 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 153 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 154 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 155 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 156 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 157 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 158 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 159 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 160 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 161 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 162 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 163 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 164 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 165 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 166 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 167 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 168 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 169 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 170 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 171 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 172 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 173 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 174 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 175 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 176 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 177 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 178 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 179 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 180 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 181 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 182 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 183 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 184 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 185 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 186 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 187 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 188 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 189 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 190 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 191 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 192 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 193 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 194 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 195 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 196 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 197 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 198 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 199 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 200 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 201 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 202 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 203 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 204 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 205 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 206 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 207 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 208 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 209 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 210 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 211 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 212 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 213 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 214 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 215 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 216 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 217 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 218 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 219 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 220 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 221 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 222 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 223 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 224 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 225 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 226 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 227 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 228 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 229 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 230 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 231 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 232 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 233 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 234 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 235 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 236 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 237 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 238 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 239 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 240 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 241 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 242 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 243 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 244 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 245 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 246 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 247 )
DECLARE_PMID(kClassIDSpace, kShowHideTouchKeyBoardIdleTaskBoss, kTextEditorPrefix + 248)
DECLARE_PMID(kClassIDSpace, kFontSliderAdornmentBoss, kTextEditorPrefix + 249)
DECLARE_PMID(kClassIDSpace, kButterflyEasterEggBoss, kTextEditorPrefix + 250)
DECLARE_PMID(kClassIDSpace, kClusterBreakIteratorBoss, kTextEditorPrefix + 251 )
DECLARE_PMID(kClassIDSpace, kFontSliderTrackerRegisterBoss, kTextEditorPrefix + 252 )
DECLARE_PMID(kClassIDSpace, kFontSliderTrackerBoss, kTextEditorPrefix + 253 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 254 )
//DECLARE_PMID(kClassIDSpace, kFancyNameBoss, kTextEditorPrefix + 255 )


// <Interface ID>
//---------------------------------------------------------------
// Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTEDITOR, kTextEditorPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCARET, kTextEditorPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCARETDATA, kTextEditorPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSELECTIONDATA, kTextEditorPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IINPUTENGINE, kTextEditorPrefix + 5)		// see CJKID.h
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSELECTIONDRAWER, kTextEditorPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTEDITORUTILS, kTextEditorPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTOFFSCREEN, kTextEditorPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTOFFSCREENOBSERVER, kTextEditorPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ILGMOVETRACKER, kTextEditorPrefix + 10)		// is an IID_ITRACKER
DECLARE_PMID(kInterfaceIDSpace, IID_IVERTICALFRAME, kTextEditorPrefix + 11)		// is an IID_IBOOLDATA
//DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEDTEXTSELECTION, kTextEditorPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSELECTIONNAVIGATOR, kTextEditorPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSELECTION_SUITE, kTextEditorPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICMOVERESIZEOBJECTDATA, kTextEditorPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABPANELSUITE, kTextEditorPrefix + 17 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITIONTHREAD, kTextEditorPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITIONTHREADRUNNING, kTextEditorPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTEXTSUITE, kTextEditorPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCROLLVIEWTOCENTERFLAG, kTextEditorPrefix + 21 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTEXTSIGNALDATA, kTextEditorPrefix + 22 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTEXTUTILS, kTextEditorPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTEXTHELPER, kTextEditorPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IHITTESTOBJECTWITHNONEFLAG, kTextEditorPrefix + 25 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSELECTIONTYPE, kTextEditorPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCARETTYPE, kTextEditorPrefix + 27 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRTLFRAME, kTextEditorPrefix + 28 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTSLIDERADORNMENTDATA, kTextEditorPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ISLIDERADORNMENTUTILS, kTextEditorPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPECONTEXTUALCONTROLSPREFS, kTextEditorPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTTYPED, kTextEditorPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENTYPEWIDGETHELPER, kTextEditorPrefix + 33 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTPDFCOMMENTDRAWUTILS, kTextEditorPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYEDITORALERTSHOWNCOUNT, kTextEditorPrefix + 35)

//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 36 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 37 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 38 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 39 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 40 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 41 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 42 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 43 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 44 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 45 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 46 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 47 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 48 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 49 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 50 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 51 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 52 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 53 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 54 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 55 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 56 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 57 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 58 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 59 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 60 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 61 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 62 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 63 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 64 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 65 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 66 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 67 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 68 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 69 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 70 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 71 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 72 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 73 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 74 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 75 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 76 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 77 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 78 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 79 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 80 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 81 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 82 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 83 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 84 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 85 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 86 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 87 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 88 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 89 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 90 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 91 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 92 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 93 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 94 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 95 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 96 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 97 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 98 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 99 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 100 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 101 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 102 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 103 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 104 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 105 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 106 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 107 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 108 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 109 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 110 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 111 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONDOCUMENTOBSERVER, kTextEditorPrefix + 112 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 113 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 114 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 115 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 116 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 117 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 118 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 119 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 120 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 121 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 122 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 123 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 124 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 125 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 126 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 127 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 128 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 129 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 130 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 131 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 132 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 133 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 134 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 135 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 136 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 137 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 138 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 139 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 140 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 141 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 142 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 143 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 144 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 145 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 146 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 147 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 148 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 149 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 150 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 151 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 152 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 153 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 154 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 155 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 156 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 157 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 158 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 159 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 160 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 161 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 162 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 163 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 164 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 165 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 166 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 167 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 168 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 169 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 170 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 171 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 172 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 173 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 174 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 175 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 176 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 177 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 178 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 179 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 180 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 181 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 182 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 183 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 184 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 185 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 186 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 187 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 188 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 189 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 190 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 191 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 192 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 193 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 194 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 195 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 196 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 197 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 198 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 199 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 200 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 201 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 202 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 203 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 204 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 205 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 206 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 207 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 208 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 209 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 210 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 211 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 212 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 213 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 214 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 215 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 216 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 217 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 218 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 219 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 220 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 221 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 222 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 223 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 224 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 225 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 226 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 227 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 228 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 229 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 230 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 231 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 232 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 233 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 234 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 235 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 236 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 237 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 238 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 239 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 240 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 241 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 242 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 243 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 244 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 245 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 246 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 247 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 248 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 249 )
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTERFLYENGINE, kTextEditorPrefix + 250 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICLUSTERBREAKITERATOR, kTextEditorPrefix + 251 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITOUCHKEYBOARDSTATE, kTextEditorPrefix + 252)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPSTORYUIDREFLISTDATA, kTextEditorPrefix + 253)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPRANGEDATA, kTextEditorPrefix + 254)
//DECLARE_PMID(kInterfaceIDSpace, IID_IFANCYNAME, kTextEditorPrefix + 255 )

// <Implementation ID>
// specified in "TextEditorImplID.h"

// <Action ID>
// specified in "TextEditorActionID.h"

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kTextOffscreenInvalHandlerID, kTextEditorPrefix + 1 )

//---------------------------------------------------
// kScriptInfoIDSpace
//---------------------------------------------------
DECLARE_PMID(kScriptInfoIDSpace, kTypeContextualUIPreferenceObjectScriptElement, kTextEditorPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kShowAlternatesUIPropertyScriptElement, kTextEditorPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kShowFractionsUIPropertyScriptElement, kTextEditorPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kTypeContextualUIPrefsPropertyScriptElement, kTextEditorPrefix + 4)



// {017BD3B8-99C8-4A24-BCF6-10B402CA0E8A}
#define kTypeContextualUIPref_CLSID { 0x017BD3B8, 0x99c8, 0x4a24, { 0xbc, 0xf6, 0x10, 0xb4, 0x2, 0xca, 0xe, 0x8a } }

#endif

#endif
