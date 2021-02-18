//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextStylePanelID.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __TextStylePanelID__
#define __TextStylePanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// Prefix
#define kTextStylePanelPrefix	RezLong( 0x5B00 ) 	/* doublecheck with AdobePrefix.h */
// 0x5B00 Hex == 23296 Dec

// PluginID
#define kTextStylePanelPluginName 		"Text Style Panel"
DECLARE_PMID(kPlugInIDSpace, kTextStylePanelPluginID, kTextStylePanelPrefix + 1)

// Resource ID of Panel Windows
#define kTextStylePanelRsrcID			1000
#define kTextStyleDialogRsrcID 			1050
#define kTextStyleCoreDialogRsrcID 		1100
#define kTextStyleParaGeneralRsrcID 	1150
#define kTextStyleCharGeneralRsrcID 	1200
#define kTextStyleParaDialogRsrcID 		1250
#define kTextStyleCharDialogRsrcID 		1300

#define kTextStylePanelStringsRsrcID	1450
#define kTextStylePanelStringsNoTransRsrcID	1500

#define kTextStyleDialogSelRsrcID 			1550
#define kTextStyleCoreDialogSelRsrcID 		1600
#define kTextStyleParaGeneralSelRsrcID 		1650
#define kTextStyleCharGeneralSelRsrcID 		1700
#define kTextStyleParaDialogSelRsrcID 		1750
#define kTextStyleCharDialogSelRsrcID 		1800
#define kTextStyleParaCoreDialogSelRsrcID 	1850
#define kTextStyleCharCoreDialogSelRsrcID 	1900
#define kTextStylePanelStringsSelRsrcID		1950

#define kTextSelectableParaDialogRsrcID		2000
#define kTextSelectableCharDialogRsrcID		2100

#define kStyleToTagMapDialogRsrcID			2200
#define kStyleToTagMapDialogSelRsrcID		2250

//----------------------------------------------------------------------------------------
// Boss IDs
//----------------------------------------------------------------------------------------

// Panel Bosses: 0 to 9
DECLARE_PMID(kClassIDSpace, kTextStyleDialogBoss, kTextStylePanelPrefix + 2)	/* starts the dialog */
DECLARE_PMID(kClassIDSpace, kTextStyleDialogHookBoss, kTextStylePanelPrefix + 3)	/* hooks the TextStyleStyleDialog into the TextStyleDialog and the StyleDialog */
DECLARE_PMID(kClassIDSpace, kTextStyleParaGeneralHookBoss, kTextStylePanelPrefix + 4)	/* hooks the General Options Dialog into the TextStyleDialog and the StyleDialog */
DECLARE_PMID(kClassIDSpace, kTextStyleCharGeneralHookBoss, kTextStylePanelPrefix + 5)	/* hooks the General Options Dialog into the TextStyleDialog and the StyleDialog */
DECLARE_PMID(kClassIDSpace, kTextStyleTestMenuBoss, kTextStylePanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kResetToBaseStyleObserverBoss, kTextStylePanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTextStyleParaDialogBoss, kTextStylePanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTextStyleCharDialogBoss, kTextStylePanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kTextStyleSelectableDialogBoss, kTextStylePanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTextStylePanelStringRegisterBoss, kTextStylePanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kStyleShortcutEditBoxWidgetBoss, kTextStylePanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kStyleKBShortCutObserverBoss, kTextStylePanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCreateOrEditStyleCmdBoss, kTextStylePanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kStyleCurrentActionWidgetBoss, kTextStylePanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kStylePreviewColorListDDWidgetBoss, kTextStylePanelPrefix + 16)

DECLARE_PMID(kClassIDSpace, kStyleToTagMapDialogBoss, kTextStylePanelPrefix + 30)
DECLARE_PMID(kClassIDSpace, kStyleToTagMapDetailObserverBoss, kTextStylePanelPrefix + 31)


// Observer Bosses: 100 to 200
DECLARE_PMID(kClassIDSpace, kStyleNameObserverBoss, kTextStylePanelPrefix + 110)
DECLARE_PMID(kClassIDSpace, kStyleSelectObserverBoss, kTextStylePanelPrefix + 111)
DECLARE_PMID(kClassIDSpace, kStyleBasedOnObserverBoss, kTextStylePanelPrefix + 112)
DECLARE_PMID(kClassIDSpace, kStyleNextObserverBoss, kTextStylePanelPrefix + 113)
DECLARE_PMID(kClassIDSpace, kStyleSettingsObserverBoss, kTextStylePanelPrefix + 114)
DECLARE_PMID(kClassIDSpace, kStyleSelectPrevObserverBoss, kTextStylePanelPrefix + 115)
DECLARE_PMID(kClassIDSpace, kStyleSelectNextObserverBoss, kTextStylePanelPrefix + 116)
DECLARE_PMID(kClassIDSpace, kStyleLocationObserverBoss, kTextStylePanelPrefix + 117)
DECLARE_PMID(kClassIDSpace, kApplyStyleToSelectionCheckBoxObserverBoss, kTextStylePanelPrefix + 118)

//gap
DECLARE_PMID(kClassIDSpace, kTextStyleParaGeneralPanelBoss, kTextStylePanelPrefix + 252)
DECLARE_PMID(kClassIDSpace, kTextStyleCharGeneralPanelBoss, kTextStylePanelPrefix + 253)

// these bosses are empty they are used because the CSelectableDialogSwitcher of the kTextSelectableDialogWidgetBoss
// sets the bosses classid as the default service id.
DECLARE_PMID(kClassIDSpace, kTextSelectableParaDialogBoss, kTextStylePanelPrefix + 254)
DECLARE_PMID(kClassIDSpace, kTextSelectableCharDialogBoss, kTextStylePanelPrefix + 255)



//----------------------------------------------------------------------------------------
// Interface IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSTYLEPANELMSG, kTextStylePanelPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEACTIONDATA, kTextStylePanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IOLDTEXTSTYLENAMEDATA, kTextStylePanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYSTYLETOSELECTION, kTextStylePanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICACHEDOLDSTYLEUIDDATA, kTextStylePanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEUIDFOREXPORTTAGVALUES, kTextStylePanelPrefix + 5)


//----------------------------------------------------------------------------------------
// Implementation IDs
//----------------------------------------------------------------------------------------

// Panel Implementation: 0 to 9
//DECLARE_PMID(kImplementationIDSpace, kTextStylePanel, kTextStylePanelPrefix + 1)//available
// gap
DECLARE_PMID(kImplementationIDSpace, kTextStyleDialog, kTextStylePanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTextStyleDialogRsrcData, kTextStylePanelPrefix + 5)	/* returns kTextStyleDialogRsrcID */
DECLARE_PMID(kImplementationIDSpace, kTextStyleCoreDialogRsrcData, kTextStylePanelPrefix + 6)	/* returns kTextStyleCoreDialogRsrcID */
DECLARE_PMID(kImplementationIDSpace, kTextStyleParaGeneralRsrcData, kTextStylePanelPrefix + 7)	/* returns kTextStyleParaGeneralDialogRsrcID */
DECLARE_PMID(kImplementationIDSpace, kTextStyleCharGeneralRsrcData, kTextStylePanelPrefix + 8)	/* returns kTextStyleParaGeneralDialogRsrcID */
DECLARE_PMID(kImplementationIDSpace, kTextStyleTestMenu, kTextStylePanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kTextStyleTargetServer, kTextStylePanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTextSelectableParaDialogObserverImpl, kTextStylePanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTextSelectableCharDialogObserverImpl, kTextStylePanelPrefix + 12)
//gap
DECLARE_PMID(kImplementationIDSpace, kStyleKBShortCutObserverImpl, kTextStylePanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kStyleActionDataImpl, kTextStylePanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTextStyleGeneralControllerImpl, kTextStylePanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kStylePreviewColorObserverImpl, kTextStylePanelPrefix + 16)


// Observer Bosses: 100 to 200
DECLARE_PMID(kImplementationIDSpace, kStyleNameObserverImpl, kTextStylePanelPrefix + 110)		/* kEditBoxWidget */
DECLARE_PMID(kImplementationIDSpace, kStyleSelectObserverImpl, kTextStylePanelPrefix + 111)		/* kPopupWidgetBoss */
DECLARE_PMID(kImplementationIDSpace, kStyleBasedOnObserverImpl, kTextStylePanelPrefix + 112)		/* kPopupWidgetBoss */
DECLARE_PMID(kImplementationIDSpace, kStyleNextObserverImpl, kTextStylePanelPrefix + 113)		/* kPopupWidgetBoss */
DECLARE_PMID(kImplementationIDSpace, kStyleSettingsObserverImpl, kTextStylePanelPrefix + 114)		/* kStaticTextWidgetBoss */
DECLARE_PMID(kImplementationIDSpace, kStyleSelectPrevObserverImpl, kTextStylePanelPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kStyleSelectNextObserverImpl, kTextStylePanelPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kStyleLocationObserverImpl, kTextStylePanelPrefix + 117)

DECLARE_PMID(kImplementationIDSpace, kTextStyleParaDialogRsrcData, kTextStylePanelPrefix + 120) /* returns kTextStyleParaDialogRsrcID */
DECLARE_PMID(kImplementationIDSpace, kTextStyleCharDialogRsrcData, kTextStylePanelPrefix + 121) /* returns kTextStyleCharDialogRsrcID */
//gap

DECLARE_PMID(kImplementationIDSpace, kTextStyleParaDialogService, kTextStylePanelPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kTextStyleCharDialogService, kTextStylePanelPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kTextSelectableParaDialogRsrcData, kTextStylePanelPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kTextSelectableCharDialogRsrcData, kTextStylePanelPrefix + 127)

DECLARE_PMID(kImplementationIDSpace, kParaCharStyleNameValidation, kTextStylePanelPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kCreateOrEditStyleCmdImpl,	   kTextStylePanelPrefix +  141)
DECLARE_PMID(kImplementationIDSpace, kStyleCurrentActionObserverImpl, kTextStylePanelPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kResetToBaseStyleObserverImpl, kTextStylePanelPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kApplyStyleToSelectionCheckBoxObserverImpl, kTextStylePanelPrefix + 144)

DECLARE_PMID(kImplementationIDSpace, kStyleToTagMapDialogRsrcData, kTextStylePanelPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kStyleToTagMapControllerImpl, kTextStylePanelPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kStyleToTagMapDetailObserverImpl, kTextStylePanelPrefix + 152)


// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kStyleNameObserverWID, kTextStylePanelPrefix + 110)		/* kEditBoxWidget */
DECLARE_PMID(kWidgetIDSpace, kStyleSelectObserverWID, kTextStylePanelPrefix + 111)		/* kPopupWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleBasedOnObserverWID, kTextStylePanelPrefix + 112)		/* kPopupWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleNextObserverWID, kTextStylePanelPrefix + 113)		/* kPopupWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleSettingsObserverWID, kTextStylePanelPrefix + 114)		/* kStaticTextWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleSelectPrevObserverWID, kTextStylePanelPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kStyleSelectNextObserverWID, kTextStylePanelPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kStyleLocationObserverWID, kTextStylePanelPrefix + 117)
//gap
DECLARE_PMID(kWidgetIDSpace, kAddStyleToCCLibrariesPanelWidgetID, kTextStylePanelPrefix + 119)
//gap
DECLARE_PMID(kWidgetIDSpace, kStylePluginCCLibraryHyperlinkTextWidgetID, kTextStylePanelPrefix + 121)

// Additional Widget IDs: 200 - 255
DECLARE_PMID(kWidgetIDSpace, kStyleSelectGroupWID, kTextStylePanelPrefix + 200)		/* kGroupPanelWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleSettingsGroupWID, kTextStylePanelPrefix + 201)		/* kGroupPanelWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleTxtBasedOnWID, kTextStylePanelPrefix + 202)		/* kStaticTextWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleTxtNextWID, kTextStylePanelPrefix + 203)		/* kStaticTextWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleTxtSettingsWID, kTextStylePanelPrefix + 204)		/* kStaticTextWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleTxtSettingsWidgetID, kTextStylePanelPrefix + 205)		/* kStaticTextWidgetBoss */
DECLARE_PMID(kWidgetIDSpace, kStyleSettingsScrollWidgetID, kTextStylePanelPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kStyleShortCutEditBoxWidgetID, kTextStylePanelPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kStyleShortcutTextWidgetID, kTextStylePanelPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kStyleShortcut2TextWidgetID, kTextStylePanelPrefix + 209)

DECLARE_PMID(kWidgetIDSpace, kStyleCharParentWidgetID, kTextStylePanelPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kSelectDialogPopupGroupWidgetID, kTextStylePanelPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kTextStylePanelWidgetID, kTextStylePanelPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kStyleCurrentActionLabelWidgetID, kTextStylePanelPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kStyleCurrentActionTextWidgetID, kTextStylePanelPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kStyleCurrentActionPanelWidgetID, kTextStylePanelPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kStyleCurrentAction2PanelWidgetID, kTextStylePanelPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kResetStyleToBaseButtonWID, kTextStylePanelPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kStyleParaParentWidgetID, kTextStylePanelPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kStyleCharGeneralParentWidgetID, kTextStylePanelPrefix + 219)

DECLARE_PMID(kWidgetIDSpace, kStyleParaGeneralParentWidgetID, kTextStylePanelPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kResetStyleToBaseButton2WID, kTextStylePanelPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kStyleLocationWidgetID, kTextStylePanelPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kStyleLocationValueWidgetID, kTextStylePanelPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kApplyStyleToSelectionButtonWidgetID, kTextStylePanelPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kStylePreviewColorDropDownWidgetID, kTextStylePanelPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kStylePreviewColorStaticWidgetID, kTextStylePanelPrefix + 226)

DECLARE_PMID(kWidgetIDSpace, kStyleToTagMapPanelWidgetId, kTextStylePanelPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kPDFStaticTextWidgetId, kTextStylePanelPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kPDFTagEditBoxWidgetID, kTextStylePanelPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kEPUBStaticTextWidgetId, kTextStylePanelPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kEPUBTagEditBoxWidgetID, kTextStylePanelPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kEPUBClassStaticTextWidgetID, kTextStylePanelPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kEPUBClassEditBoxWidgetID, kTextStylePanelPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kEPUBAttrStaticTextWidgetID, kTextStylePanelPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kEPUBAttrEditBoxWidgetID, kTextStylePanelPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kStyleToTagSeparatorWidgetId, kTextStylePanelPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kPDFTextWidgetID, kTextStylePanelPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kEPUBTextWidgetID, kTextStylePanelPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kPDFGroupPanelWidgetID, kTextStylePanelPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kBreakHTMLFileInEPUBWidgetID, kTextStylePanelPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kStyleToTagMapDetailWidgetID, kTextStylePanelPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kEmitCSSForStyleWidgetID, kTextStylePanelPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kIncludeClassInHTMLCheckboxWidgetID, kTextStylePanelPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kStyleClassWidgetID, kTextStylePanelPrefix + 247)


//----------------------------------------------------------------------------------------
// Message IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kMessageIDSpace, kTextStyleMsgBasedOnChanged, kTextStylePanelPrefix + 1)	/* send by kStyleBasedOnObserver on IID_ITEXTSTYLEPANELMSG */
DECLARE_PMID(kMessageIDSpace, kTextStyleMsgNextChanged, kTextStylePanelPrefix + 2)	/* send by kStyleBasedOnObserver on IID_ITEXTSTYLEPANELMSG */
DECLARE_PMID(kMessageIDSpace, kTextStyleMsgSelectPrev, kTextStylePanelPrefix + 3)	/* send by kStyleSelectPrevObserver on IID_ITEXTSTYLEPANELMSG */
DECLARE_PMID(kMessageIDSpace, kTextStyleMsgSelectNext, kTextStylePanelPrefix + 4)	/* send by kStyleSelectNextObserver on IID_ITEXTSTYLEPANELMSG */

#endif // __TextStylePanelID__

