//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/AboutBoxID.h $
//  
//  Owner: lance bushore
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
//  Contains IDs used by the aboutbox, appinfo dialog, doc info dialog.
//  
//========================================================================================

#ifndef __AboutBoxID__
#define __AboutBoxID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kAboutBoxPrefix	RezLong(0x9f00)

// <Start IDC>
// <Class ID>
// ClassIDs
//obsolete DECLARE_PMID(kClassIDSpace, kDocInfoDialogBoss, kAboutBoxPrefix + 1)
//obsolete DECLARE_PMID(kClassIDSpace, kAboutBoxPanelBoss, kAboutBoxPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPublicLibComponentVersionBoss, kAboutBoxPrefix + 4)
DECLARE_PMID(kClassIDSpace, kAGMComponentVersionBoss, kAboutBoxPrefix + 5)
DECLARE_PMID(kClassIDSpace, kWidgetBinComponentVersionBoss, kAboutBoxPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCoolTypeComponentVersionBoss, kAboutBoxPrefix + 7)
DECLARE_PMID(kClassIDSpace, kDV_WidgetBinComponentVersionBoss, kAboutBoxPrefix + 8)
DECLARE_PMID(kClassIDSpace, kAppInfoDialogBoss, kAboutBoxPrefix + 9)
DECLARE_PMID(kClassIDSpace, kAxeDOMVersionBoss, kAboutBoxPrefix + 12)
DECLARE_PMID(kClassIDSpace, kACEVersionBoss, kAboutBoxPrefix + 13)
DECLARE_PMID(kClassIDSpace, kBIBUtilVersionBoss, kAboutBoxPrefix + 14)
DECLARE_PMID(kClassIDSpace, kBIBVersionBoss, kAboutBoxPrefix + 15)
DECLARE_PMID(kClassIDSpace, kARMVersionBoss, kAboutBoxPrefix + 16)
//gap
DECLARE_PMID(kClassIDSpace, kOWLVersionBoss, kAboutBoxPrefix + 19)
DECLARE_PMID(kClassIDSpace, kScriptUIVersionInfoBoss, kAboutBoxPrefix + 20)


// <Interface ID>
DECLARE_PMID (kInterfaceIDSpace, IID_ICOMPONENT_VERSION, kAboutBoxPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IABOUTBOXSTATE, kAboutBoxPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IABOUTBOXSUSPENDOBSERVER, kAboutBoxPrefix + 2)


// Service Providers
DECLARE_PMID (kServiceIDSpace, kComponentVersionService, kAboutBoxPrefix +0)

// <Implementation ID>
// ImplementationIDs
//gap
DECLARE_PMID(kImplementationIDSpace, kAboutBoxDialogObserverImpl, kAboutBoxPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kAppInfoDialogControllerImpl, kAboutBoxPrefix + 7)
//gap
DECLARE_PMID(kImplementationIDSpace, kAppInfoDialogObserverImpl, kAboutBoxPrefix + 10)
//gap
DECLARE_PMID(kImplementationIDSpace, kComponentVersionServiceImpl, kAboutBoxPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPublicLibComponentVersionImpl, kAboutBoxPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAGMComponentVersionImpl, kAboutBoxPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kWidgetBinComponentVersionImpl, kAboutBoxPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCoolTypeComponentVersionImpl, kAboutBoxPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kDV_WidgetBinComponentVersionImpl, kAboutBoxPrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kAxeDOMComponentVersionImpl, kAboutBoxPrefix + 18)

DECLARE_PMID(kImplementationIDSpace, kACEComponentVersionImpl, kAboutBoxPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kBIBUtilComponentVersionImpl, kAboutBoxPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kBIBComponentVersionImpl, kAboutBoxPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kARMComponentVersionImpl, kAboutBoxPrefix + 23)
//gap
DECLARE_PMID(kImplementationIDSpace, kOWLComponentVersionImpl, kAboutBoxPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kScriptUIComponentVersionImpl, kAboutBoxPrefix + 29)

// <Widget ID>
// WidgetIDs


//doc info widgets
DECLARE_PMID(kWidgetIDSpace, kDocInfoNameLabelWidgetID, kAboutBoxPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kDocInfoNameWidgetID, kAboutBoxPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kDocInfoSaveCountLabelWidgetID, kAboutBoxPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kDocInfoSaveCountWidgetID, kAboutBoxPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHeadingWidgetID, kAboutBoxPrefix + 5)
//gap
DECLARE_PMID(kWidgetIDSpace, kDocInfoVersionLabelWidgetID, kAboutBoxPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kDocInfoVersionWidgetID, kAboutBoxPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHighUIDLabelWidgetID, kAboutBoxPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHighUIDWidgetID, kAboutBoxPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHeirCountLabelWidgetID, kAboutBoxPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHeirCountWidgetID, kAboutBoxPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kDocInfoByteSwapLabelWidgetID, kAboutBoxPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kDocInfoByteSwapWidgetID, kAboutBoxPrefix + 14)

DECLARE_PMID(kWidgetIDSpace, kDocInfoPluginCountLabelWidgetID, kAboutBoxPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kDocInfoPluginCountWidgetID, kAboutBoxPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kDocInfoPluginPanelWidgetID, kAboutBoxPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kDocInfoPluginWidgetID, kAboutBoxPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kDocInfoPluginScrollWidgetID, kAboutBoxPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kDocInfoMisingCountLabelWidgetID, kAboutBoxPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kDocInfoMissingCountWidgetID, kAboutBoxPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kDocInfoMissingPanelWidgetID, kAboutBoxPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kDocInfoMissingWidgetID, kAboutBoxPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kDocInfoMissingScrollWidgetID, kAboutBoxPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHistoryLabelWidgetID, kAboutBoxPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHistoryPanelWidgetID, kAboutBoxPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHistoryWidgetID, kAboutBoxPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kDocInfoHistoryScrollWidgetID, kAboutBoxPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kDocInfoPanelWidgetID, kAboutBoxPrefix + 29)

//gap

//app info widgets
//gap
DECLARE_PMID(kWidgetIDSpace, kAppInfoSavedDataVersionTextWidgetID, kAboutBoxPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kAppInfoSeperatorWidgetID, kAboutBoxPrefix + 37)
//gap
DECLARE_PMID(kWidgetIDSpace, kPluginCountWidgetID, kAboutBoxPrefix + 39)
//gap
DECLARE_PMID(kWidgetIDSpace, kAppInfoDialogWidgetID, kAboutBoxPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kAppInfoAppTextWidgetID, kAboutBoxPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kAppInfoVersionTextWidgetID, kAboutBoxPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kAppInfoBuildTextWidgetID, kAboutBoxPrefix + 59)
//gap
DECLARE_PMID(kWidgetIDSpace, kAppInfoInstalledPluginTextWidgetID, kAboutBoxPrefix + 61)
//gap
DECLARE_PMID(kWidgetIDSpace, kAppInfoDefaultsVersionTextWidgetID, kAboutBoxPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kAppVersionWidgetID, kAboutBoxPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kAppBuildNumWidgetID, kAboutBoxPrefix + 66)
//gap
DECLARE_PMID(kWidgetIDSpace, kAppDefaultsVersionWidgetID, kAboutBoxPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kAppSavedDataVersionWidgetID, kAboutBoxPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kAppDepWidgetID, kAboutBoxPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kAppDepScrollWidgetID, kAboutBoxPrefix + 71)


DECLARE_PMID(kWidgetIDSpace, kAppInfoPluginVersionWidgetID, kAboutBoxPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kAppInfoPluginVersionTextWidgetID, kAboutBoxPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kAppInfoPluginVersionScrollWidgetID, kAboutBoxPrefix + 74)

//gap
DECLARE_PMID(kWidgetIDSpace, kWriteLogButtonWidgetID, kAboutBoxPrefix + 80)
//gap

//aboutbox widgets
DECLARE_PMID(kWidgetIDSpace, kAboutBoxBuildWidgetID, kAboutBoxPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxUserNameWidgetID, kAboutBoxPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxUserOrgWidgetID, kAboutBoxPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxSerialNumWidgetID, kAboutBoxPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxDialogWidgetID, kAboutBoxPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxScrollingPictureWidgetID, kAboutBoxPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxLicenseWidgetID, kAboutBoxPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxBonusVersionWidgetID, kAboutBoxPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kPatentAndLegalButtonWidgetID, kAboutBoxPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kCreditsButtonWidgetID, kAboutBoxPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kCopyrightTextWidgetID, kAboutBoxPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kAboutBoxVersionWidgetID, kAboutBoxPrefix + 101)

#endif // __AboutBoxID__




