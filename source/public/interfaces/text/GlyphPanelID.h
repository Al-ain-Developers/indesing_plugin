//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/GlyphPanelID.h $
//  
//  Owner: Pascal Rubini
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

#ifndef __GlyphPanelID__
#define __GlyphPanelID__

//----------------------------------------------------------------------------------------
// String resources IDs
//----------------------------------------------------------------------------------------

#define kGlyphPanelStringsRsrcID			1100
#define kGlyphPanelStringsNoTransRsrcID		1200
#define kGlyphPanelMenusRsrcID				1300
#define kGlyphPanelErrorStringTableRrscID	1350

//----------------------------------------------------------------------------------------
// Panel resources IDs
//----------------------------------------------------------------------------------------


#define kPopoutWindowRsrcID				1400
#define kIconZoomOutRsrc				1500
#define kIconZoomInRsrc					1600
#define kGlyphPaletteIconRsrcID			1601
#define kGlyphPanelActionResID			1700
#define kGlyphPanelRsrcID				1800
#define kGlyphPanelListResID			1900
#define kFavoriteSetNameDlgRsrcID		2000
#define kFavoriteGlyphDlgRsrcID			3000

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
#ifndef MAC_RESOURCE_INCLUDER 

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGlyphPanelPrefix			RezLong(0xD100)		// AlternateGlyph2Prefix, main prefix for this plug-in. Not sure of history how AlternateGlyph2Prefix got to be the main prefix, not changing now to due to persistent impls
#define kGlyphPanelTitle			"GlyphPanel"  		// Basic name of plug-in. Use as part of other keys, not alone.
#define kGlyphPanelPrefix2			RezLong(0x9500)		// AltGlyphPanelPrefix, secondary prefix for this plug-in for overflow dynamic menus

//----------------------------------------------------------------------------------------
// PluginID
//----------------------------------------------------------------------------------------
#define kGlyphPanelPluginName 		"Glyph Panel"
DECLARE_PMID(kPlugInIDSpace, kGlyphPanelPluginID, kGlyphPanelPrefix + 1)


//----------------------------------------------------------------------------------------
// <Class ID>
//----------------------------------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kGlyphGridWidgetBoss, kGlyphPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPopoutPanelBoss, kGlyphPanelPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kGlyphFontFamilyObserverBoss, kGlyphPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kGlyphFontStyleObserverBoss, kGlyphPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kGlyphPanelModeListBoss, kGlyphPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kGlyphPanelTestMenuBoss, kGlyphPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kGlyphPanelBoss, kGlyphPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kGlyphPopupWindowBoss, kGlyphPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kGlyphPanelMenuComponentBoss, kGlyphPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kGlyphPanelSearchBoxBoss,	kGlyphPanelPrefix + 16)
//gap

DECLARE_PMID(kClassIDSpace, kZoomInObserverBoss, kGlyphPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kZoomOutObserverBoss, kGlyphPanelPrefix + 26)

DECLARE_PMID(kClassIDSpace, kJIS_04FormsObserverBoss, kGlyphPanelPrefix + 28)
DECLARE_PMID(kClassIDSpace, kJIS_90FormsObserverBoss, kGlyphPanelPrefix + 29)

DECLARE_PMID(kClassIDSpace, kGlyphSetBoss, kGlyphPanelPrefix + 30)
DECLARE_PMID(kClassIDSpace, kGlyphFavoritesMenuActionBoss, kGlyphPanelPrefix + 31)
//gap
DECLARE_PMID(kClassIDSpace, kFavoriteSetNameDlgBoss, kGlyphPanelPrefix + 33)


DECLARE_PMID(kClassIDSpace, kFavoriteGlyphDlgBoss, kGlyphPanelPrefix + 51)
DECLARE_PMID(kClassIDSpace, kFavoriteGlyphCheckBoxObserverBoss, kGlyphPanelPrefix + 53)
DECLARE_PMID(kClassIDSpace, kFavoriteGlyphDelButtonObserverBoss, kGlyphPanelPrefix + 54)
DECLARE_PMID(kClassIDSpace, kFavoriteGlyphFontFamilyObserverBoss, kGlyphPanelPrefix + 55)
DECLARE_PMID(kClassIDSpace, kFavoriteGlyphFontStyleObserverBoss, kGlyphPanelPrefix + 56)

DECLARE_PMID(kClassIDSpace, kFavoriteGlyphGridWidgetBoss, kGlyphPanelPrefix + 61)

DECLARE_PMID(kClassIDSpace, kGlyphSetCreateSetCmdBoss, kGlyphPanelPrefix + 62)
DECLARE_PMID(kClassIDSpace, kGlyphSetDeleteSetCmdBoss, kGlyphPanelPrefix + 63)
DECLARE_PMID(kClassIDSpace, kGlyphSetAddGlyphCmdBoss, kGlyphPanelPrefix + 64)
DECLARE_PMID(kClassIDSpace, kGlyphSetDeleteGlyphCmdBoss, kGlyphPanelPrefix + 65)
DECLARE_PMID(kClassIDSpace, kGlyphSetEditSetCmdBoss, kGlyphPanelPrefix + 66)
DECLARE_PMID(kClassIDSpace, kGlyphSetDoNothingCmdBoss, kGlyphPanelPrefix + 67)
DECLARE_PMID(kClassIDSpace, kMRUGlyphGridWidgetBoss, kGlyphPanelPrefix + 68)

DECLARE_PMID(kClassIDSpace, kGlyphPanelConversionProviderBoss, kGlyphPanelPrefix + 70)
DECLARE_PMID(kClassIDSpace, kGlyphSetXMLReaderBoss, kGlyphPanelPrefix + 71)
DECLARE_PMID(kClassIDSpace, kGlyphSetXMLWriterBoss, kGlyphPanelPrefix + 72)
//gap
DECLARE_PMID(kClassIDSpace, kGlyphSetLoadSetCmdBoss, kGlyphPanelPrefix + 74)
DECLARE_PMID(kClassIDSpace, kGlyphSetPurgeSetsCmdBoss, kGlyphPanelPrefix + 75)
DECLARE_PMID(kClassIDSpace, kLameFloatingGlyphArrayBoss, kGlyphPanelPrefix + 76)
//gap
DECLARE_PMID(kClassIDSpace, kGlyphGridPlusWidgetBoss, kGlyphPanelPrefix + 80)
DECLARE_PMID(kClassIDSpace, kGlyphGridParentWidgetBoss, kGlyphPanelPrefix + 81)
DECLARE_PMID(kClassIDSpace, kGlyphSetSettingsMigrationServiceProviderBoss, kGlyphPanelPrefix + 82)



// favorite grid message NOTE - message IDs conflict with ClassIDs, so make sure these don't overlap with any ClassIDs!!!!
DECLARE_PMID(kMessageIDSpace, kFavoriteGlyphMsgSelectionChanged, kGlyphPanelPrefix + 221)
DECLARE_PMID(kMessageIDSpace, kFavoriteGlyphMsgFontChanged, kGlyphPanelPrefix + 222)
DECLARE_PMID(kMessageIDSpace, kFavoriteGlyphMsgInvalidate, kGlyphPanelPrefix + 223)
DECLARE_PMID(kMessageIDSpace, kFavoriteGlyphMsgNewSetAdded, kGlyphPanelPrefix + 224)
DECLARE_PMID(kMessageIDSpace, kFavoriteGlyphMsgNotRememberFont, kGlyphPanelPrefix + 225)


//----------------------------------------------------------------------------------------
// <Interface ID>
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSETDATA, kGlyphPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHUIUTILS, kGlyphPanelPrefix + 2 )
DECLARE_PMID(kInterfaceIDSpace, IID_IALTERNATENUMBER, kGlyphPanelPrefix + 3)		// just an IIntData
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHGRIDARRAY, kGlyphPanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMMAXISDATA, kGlyphPanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHGRIDPANELDATA, kGlyphPanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHPANELMODEDATA, kGlyphPanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDGLYPHTOSETCMDDATA, kGlyphPanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSETOBSERVER, kGlyphPanelPrefix + 9)

DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHGRIDARRAYLIST, kGlyphPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSETINFO, kGlyphPanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSETLIST, kGlyphPanelPrefix + 12)

DECLARE_PMID(kInterfaceIDSpace, IID_IFAVORITEGLYPHGRIDPANELDATA, kGlyphPanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHGRIDSELECTIONDATA, kGlyphPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFAVORITEGRIDWIDGETMSG, kGlyphPanelPrefix + 15)		// protocol id for messages

DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSETXMLWRITER, kGlyphPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSETSMANAGER, kGlyphPanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFRESHGLYPHSETLIST, kGlyphPanelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTLOADEDGLYPHSET, kGlyphPanelPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTGLYPHSET, kGlyphPanelPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLYPHSEARCHUTILS, kGlyphPanelPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIOUSCHARCOUNT, kGlyphPanelPrefix + 23)


//----------------------------------------------------------------------------------------
// <Implementation ID>
//----------------------------------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace, kGlyphGridPanelViewImpl, kGlyphPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridPanelEHImpl, kGlyphPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridPanelObserverImpl, kGlyphPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetDataImpl, kGlyphPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPopupGridPanelViewImpl, kGlyphPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPopupGridPanelEHImpl, kGlyphPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGlyphUIUtilsImpl, kGlyphPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridArrayImpl, kGlyphPanelPrefix + 8			)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelModeObserverImpl, kGlyphPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMMAxisDataImpl, kGlyphPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMRUGlyphGridPanelDataImpl, kGlyphPanelPrefix + 11)

DECLARE_PMID(kImplementationIDSpace, kGlyphPanelMenuComponentImpl, kGlyphPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelViewImpl, kGlyphPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kMRUGlyphGridPanelViewImpl, kGlyphPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGlyphFontFamilyObserverImpl, kGlyphPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kGlyphFontStyleObserverImpl, kGlyphPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridPanelDataImpl, kGlyphPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelModeDataImpl, kGlyphPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelTargetServerImpl, kGlyphPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridPanelTipImpl, kGlyphPanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPopupGridPanelTipImpl, kGlyphPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelTestMenuImpl, kGlyphPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGlyphSearchUtilsImpl, kGlyphPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDV_ExtendedGlyphPanelViewImpl, kGlyphPanelPrefix + 24)
//gap

DECLARE_PMID(kImplementationIDSpace, kZoomInObserver, kGlyphPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kZoomOutObserver, kGlyphPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kGlyphCBAttrImpl, kGlyphPanelPrefix + 34)
//deprecated -- DECLARE_PMID(kImplementationIDSpace, kGlyphCBDropDownViewImpl, kGlyphPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridUnicodeDataImpl, kGlyphPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kMRUGlyphSetInfoImpl, kGlyphPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kAddGlyphToSetCmdDataImpl, kGlyphPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kMRUGlyphGridPanelEHImpl, kGlyphPanelPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kGlyphGridArrayListImpl, kGlyphPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kGlyphGridSelectionDataImpl, kGlyphPanelPrefix + 41)

DECLARE_PMID(kImplementationIDSpace, kGlyphsPanelDetailControllerImpl, kGlyphPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMRUGlyphGridPanelTipImpl, kGlyphPanelPrefix + 45)

//gap
DECLARE_PMID(kImplementationIDSpace, kGlyphSetListImpl, kGlyphPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetInfoImpl, kGlyphPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kGlyphContextMenuComponentImpl, kGlyphPanelPrefix + 52)
//gap
DECLARE_PMID(kImplementationIDSpace, kFavoriteSetNameDlgControllerImpl, kGlyphPanelPrefix + 55)


DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphDlgControllerImpl, kGlyphPanelPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphFontFamilyObserverImpl, kGlyphPanelPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphFontStyleObserverImpl, kGlyphPanelPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphGridPanelDataImpl, kGlyphPanelPrefix + 74)

DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphCheckBoxObserverImpl, kGlyphPanelPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphDelButtonObserverImpl, kGlyphPanelPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphTextTargetServerImpl, kGlyphPanelPrefix + 77)

DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphGridViewImpl, kGlyphPanelPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphGridEHImpl, kGlyphPanelPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphGridObserverImpl, kGlyphPanelPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kFavoriteGlyphGridPanelTipImpl, kGlyphPanelPrefix + 84)

DECLARE_PMID(kImplementationIDSpace, kGlyphSetCreateSetCmdImpl, kGlyphPanelPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetDeleteSetCmdImpl, kGlyphPanelPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetAddGlyphCmdImpl, kGlyphPanelPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetDeleteGlyphCmdImpl, kGlyphPanelPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetEditGlyphCmdImpl, kGlyphPanelPrefix + 89)

DECLARE_PMID(kImplementationIDSpace, kGlyphPanelXMLGeneratorImpl, kGlyphPanelPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelSAXHandlerImpl, kGlyphPanelPrefix + 91)

DECLARE_PMID(kImplementationIDSpace, kGlyphFlyoutDynamicMenuImpl, kGlyphPanelPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetDoNothingCmdImpl, kGlyphPanelPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelObserverImpl, kGlyphPanelPrefix + 94)

DECLARE_PMID(kImplementationIDSpace, kGlyphSetXMLReaderImpl, kGlyphPanelPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetXMLWriterImpl, kGlyphPanelPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetsManagerImpl, kGlyphPanelPrefix + 97)
//gap
DECLARE_PMID(kImplementationIDSpace, kGlyphSetLoadSetCmdImpl, kGlyphPanelPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetPurgeSetsCmdImpl, kGlyphPanelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetAppObserverImpl, kGlyphPanelPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kGlyphSetSettingsMigrationImpl, kGlyphPanelPrefix + 102)

DECLARE_PMID(kImplementationIDSpace, kGlyphPanelSearchBoxObserverImpl, kGlyphPanelPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kGlyphPanelSearchBoxEHImpl, kGlyphPanelPrefix + 104)

//----------------------------------------------------------------------------------------
// <Widget ID>
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelWidgetId, kGlyphPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelScrollWidgetID, kGlyphPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kGlyphGridPanelWidgetId, kGlyphPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kGlyphFontFamilyWidgetId, kGlyphPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kGlyphZoomInWidgetId, kGlyphPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kGlyphZoomOutWidgetId, kGlyphPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kGlyphFontVariantWidgetId, kGlyphPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kGlyphGroup1WidgetId, kGlyphPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kGlyphGroup2WidgetId, kGlyphPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kGlyphGroup3WidgetId, kGlyphPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kGlyphGroup4WidgetId, kGlyphPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelControlStripWidgetId, kGlyphPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kShowSetTextWidgetId, kGlyphPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelModeListWidgetID, kGlyphPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelWidgetID, kGlyphPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kFavoriteNameTextWidgetId, kGlyphPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kFavoriteNameEditBoxWidgetID, kGlyphPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kFavoriteSetNameDlgID, kGlyphPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kMRUGlyphLabelWidgetID, kGlyphPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kGlyphMRUGroupWidgetId, kGlyphPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kMRUGlyphGridPanelWidgetId, kGlyphPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kInsertOrderLabelWidgetId, kGlyphPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kInsertOrderDropDownWidgetID, kGlyphPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelSearchBoxWidgetID, kGlyphPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kGlyphGroup0WidgetId, kGlyphPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kGlyphPanelSpacer1WidgetID, kGlyphPanelPrefix + 26)

//gap
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphDlgID, kGlyphPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphGroupPanelWidgetID, kGlyphPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphBoarderWidgetID, kGlyphPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphStaticWidgetID, kGlyphPanelPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphCheckBoxWidgetID, kGlyphPanelPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphFontFamilyWidgetID, kGlyphPanelPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphFontStyleWidgetID, kGlyphPanelPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphSizePanelWidgetID, kGlyphPanelPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphFontSizeWidgetID, kGlyphPanelPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphFontSizeNudgeWidgetID, kGlyphPanelPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphDelButtonWidgetID, kGlyphPanelPrefix + 62)

DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphUnicodeInfoWidgetID, kGlyphPanelPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphCID_GIDWidgetID, kGlyphPanelPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphCIDInfoWidgetID, kGlyphPanelPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphSJISInfoWidgetID, kGlyphPanelPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphUnicodeNameWidgetID, kGlyphPanelPrefix + 67)


DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphGridPanelWidgetID, kGlyphPanelPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphGridWidgetID, kGlyphPanelPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kFavoriteGlyphGridScrollWidgetID, kGlyphPanelPrefix + 83)

//----------------------------------------------------------------------------------------
// <Action ID>
//----------------------------------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kGlyphPanelActionID, kGlyphPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kExpertFormsActionID, kGlyphPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kJIS78FormsActionID, kGlyphPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kJIS83FormsActionID, kGlyphPanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kMonospacedHalfWidthFormsActionID, kGlyphPanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kRevertToDefaultFormsActionID, kGlyphPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kTraditionalFormsActionID, kGlyphPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kGlyphPopupSep3ActionID, kGlyphPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kThirdWidthFormsActionID, kGlyphPanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kQuarterWidthFormsActionID, kGlyphPanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kNLCFormsActionID, kGlyphPanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kShowHideGlyphOptionsActionID, kGlyphPanelPrefix + 12)

DECLARE_PMID(kActionIDSpace, kNewGlyphFavoritesActionID, kGlyphPanelPrefix + 13)
DECLARE_PMID(kActionIDSpace, kGlyphPopupSep1ActionID, kGlyphPanelPrefix + 14)

DECLARE_PMID(kActionIDSpace, kJIS04FormsActionID, kGlyphPanelPrefix + 15)

DECLARE_PMID(kActionIDSpace, kAddGlyphFavoritesActionID, kGlyphPanelPrefix + 16)
DECLARE_PMID(kActionIDSpace, kEditGlyphFavoritesActionID, kGlyphPanelPrefix + 17)
DECLARE_PMID(kActionIDSpace, kViewGlyphFavoritesActionID, kGlyphPanelPrefix + 18)
DECLARE_PMID(kActionIDSpace, kDeleteGlyphFavoritesActionID, kGlyphPanelPrefix + 19)
DECLARE_PMID(kActionIDSpace, kDelGlyphFromFavoritesActionID, kGlyphPanelPrefix + 20)

DECLARE_PMID(kActionIDSpace, kFirstEditGlyphFavoritesActionID, kGlyphPanelPrefix + 21)
// all those in between kFirstEditGlyphFavoritesActionID and kLastEditGlyphFavoritesActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastEditGlyphFavoritesActionID, kGlyphPanelPrefix + 81)

DECLARE_PMID(kActionIDSpace, kFirstAddGlyphFavoritesActionID, kGlyphPanelPrefix + 82)
// all those in between kFirstAddGlyphFavoritesActionID and kLastAddGlyphFavoritesActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastAddGlyphFavoritesActionID, kGlyphPanelPrefix + 142)

DECLARE_PMID(kActionIDSpace, kFirstViewGlyphFavoritesActionID, kGlyphPanelPrefix + 143)
// all those in between kFirstViewGlyphFavoritesActionID and kLastViewGlyphFavoritesActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastViewGlyphFavoritesActionID, kGlyphPanelPrefix + 203)

DECLARE_PMID(kActionIDSpace, kJIS90FormsActionID, kGlyphPanelPrefix + 204)

// gap
DECLARE_PMID(kActionIDSpace, kProportionalWidthFormsActionID, kGlyphPanelPrefix + 206)
DECLARE_PMID(kActionIDSpace, kFullWidthFormsActionID, kGlyphPanelPrefix + 207)

DECLARE_PMID(kActionIDSpace, kInsertMRU1GlyphActionID, kGlyphPanelPrefix + 208)
DECLARE_PMID(kActionIDSpace, kInsertMRU2GlyphActionID, kGlyphPanelPrefix + 209)
DECLARE_PMID(kActionIDSpace, kInsertMRU3GlyphActionID, kGlyphPanelPrefix + 210)
DECLARE_PMID(kActionIDSpace, kInsertMRU4GlyphActionID, kGlyphPanelPrefix + 211)
DECLARE_PMID(kActionIDSpace, kInsertMRU5GlyphActionID, kGlyphPanelPrefix + 212)
DECLARE_PMID(kActionIDSpace, kGlyphPopupSep2ActionID, kGlyphPanelPrefix + 213)
DECLARE_PMID(kActionIDSpace, kGlyphPopupSep4ActionID, kGlyphPanelPrefix + 214)
DECLARE_PMID(kActionIDSpace, kGlyphPopupSep5ActionID, kGlyphPanelPrefix + 215)
DECLARE_PMID(kActionIDSpace, kGlyphSortByCIDActionID, kGlyphPanelPrefix + 216)
DECLARE_PMID(kActionIDSpace, kGlyphSortByUnicodeActionID, kGlyphPanelPrefix + 217)
DECLARE_PMID(kActionIDSpace, kDelGlyphFromMRUActionID, kGlyphPanelPrefix + 218)
DECLARE_PMID(kActionIDSpace, kClearMRUActionID, kGlyphPanelPrefix + 219)
// gap

// NOTE: Second Prefix for more dynamic menu items!!!
DECLARE_PMID(kActionIDSpace, kFirstDeleteGlyphFavoritesActionID, kGlyphPanelPrefix2 + 1)	
// all those in between kFirstDeleteGlyphFavoritesActionID and kLastDeleteGlyphFavoritesActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastDeleteGlyphFavoritesActionID, kGlyphPanelPrefix2 + 61)

// Error ID space
DECLARE_PMID(kErrorIDSpace, kGlyphSetSaveError,          kGlyphPanelPrefix + 1)


#endif
#endif // __GlyphPanelID__
