//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ShuksanID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs for core Shuksan classes, IIDs, and ImplementationIDs.
//  
//========================================================================================

#ifndef __SHUKSANID__
#define __SHUKSANID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "GeneralBuildFlags.h"

#define kShuksanPrefix	 RezLong(0x100)
#define kShuksan2Prefix	 RezLong(0x10700)

// ID Space IDs

#define kClassIDSpace				kShuksanPrefix + 1
#define kInterfaceIDSpace			kShuksanPrefix + 2
#define kImplementationIDSpace		kShuksanPrefix + 3
#define kWidgetIDSpace				kShuksanPrefix + 4
#define kMessageIDSpace				kShuksanPrefix + 5
#define kServiceIDSpace				kShuksanPrefix + 6
#define kErrorIDSpace				kShuksanPrefix + 7
#define kPlugInIDSpace				kShuksanPrefix + 8
#define kActionIDSpace				kShuksanPrefix + 9
#define kViewPortAttrIDSpace		kShuksanPrefix + 10
#define kUIFontIDSpace				kShuksanPrefix + 11
#define kFileTypeInfoIDSpace		kShuksanPrefix + 12
#define kKitViewIDSpace				kShuksanPrefix + 13
#define kPerformanceMetricIDSpace	kShuksanPrefix + 14
#define kScriptInfoIDSpace			kShuksanPrefix + 15
#define kProductIDSpace				kShuksanPrefix + 16
#define kAsyncUIIDSpace				kShuksanPrefix + 17
#define kPaletteTypeIDSpace			kShuksanPrefix + 18
#define kScriptIDSpace				kShuksanPrefix + 19
#define kUserActionCategoryIDSpace	kShuksanPrefix + 20
#define kInvalHandlerIDSpace		kShuksanPrefix + 21
#define kRuleTargetTypeIDSpace		kShuksanPrefix + 22
#define kLinkClientIDSpace			kShuksanPrefix + 23
#define kPreflightObjClassIDSpace	kShuksanPrefix + 24
#define kPreflightObjSubpartIDSpace	kShuksanPrefix + 25
#define kPreflightCriteriaIDSpace	kShuksanPrefix + 26
#define kDontShowAgainIDSpace		kShuksanPrefix + 27


// <Start IDC>
// PluginID
#define kApplicationName 			"AppExeName"
#ifdef DEBUG
#define kPublicLibName 				"PublicDebugFileName"
#define kWidgetLibName 				"WidgetDebugFileName"
#else
#define kPublicLibName 				"PublicFileName"
#define kWidgetLibName 				"WidgetFileName"
#endif
#define kPMStringName 				kApplicationName
#define kPMPointName 				kApplicationName
#define kPMRectName 				kApplicationName
#define kPMMatrixName 				kApplicationName

DECLARE_PMID(kPlugInIDSpace, kApplicationPluginID, kShuksanPrefix + 1)
DECLARE_PMID(kPlugInIDSpace, kPublicPluginID, kShuksanPrefix + 2)
DECLARE_PMID(kPlugInIDSpace, kWidgetBinPluginID, kShuksanPrefix + 3)

// Mark the end of all the Application Plugins
// *** Keep this up to date ***
#define kFirstAppPluginID				kApplicationPluginID
#define kLastAppPluginID				kWidgetBinPluginID


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSessionBoss, kShuksanPrefix + 1)
DECLARE_PMID(kClassIDSpace, kAppBoss, kShuksanPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kPersistClassDictBoss, kShuksanPrefix + 4)
DECLARE_PMID(kClassIDSpace, kActiveContextBoss, kShuksanPrefix + 5)
DECLARE_PMID(kClassIDSpace, kMouseWatcherThreadBoss, kShuksanPrefix + 6)
DECLARE_PMID(kClassIDSpace, kAppTestMenuBoss, kShuksanPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kUnusedBoss, kShuksanPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPatientUserBoss, kShuksanPrefix + 9)
//gap
DECLARE_PMID(kClassIDSpace, kPanelManagerBoss, kShuksanPrefix + 11)
DECLARE_PMID(kClassIDSpace, kMouseTrackerBoss, kShuksanPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCallbackTimerBoss, kShuksanPrefix + 13)
DECLARE_PMID(kClassIDSpace, kAboutMenuComponentBoss, kShuksanPrefix + 14)
DECLARE_PMID(kClassIDSpace, kScrapComponentBoss, kShuksanPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTestComponentBoss, kShuksanPrefix + 16) // debugging only!
DECLARE_PMID(kClassIDSpace, kWindowBoss, kShuksanPrefix + 17)
DECLARE_PMID(kClassIDSpace, kExtensionManagerMenuComponentBoss, kShuksanPrefix + 18)
DECLARE_PMID(kClassIDSpace, kPersistClassBoss, kShuksanPrefix + 19)
DECLARE_PMID(kClassIDSpace, kAppErrorStringServiceBoss, kShuksanPrefix + 20)
DECLARE_PMID(kClassIDSpace, kFreeSomeMemoryBoss, kShuksanPrefix + 21)
DECLARE_PMID(kClassIDSpace, kDBStreamWrite_AllowPubFileWriteBoss, kShuksanPrefix + 22)
DECLARE_PMID(kClassIDSpace, kInterfaceBrightnessPrefChangeCmdBoss, kShuksanPrefix + 23)
//gap
DECLARE_PMID(kClassIDSpace, kAboutToCloseWindowMsgBoss, kShuksanPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCloseWinCmdBoss, kShuksanPrefix + 26)
DECLARE_PMID(kClassIDSpace, kResizeWinCmdBoss, kShuksanPrefix + 27)
DECLARE_PMID(kClassIDSpace, kZoomWinCmdBoss, kShuksanPrefix + 28)

// Stream bosses
DECLARE_PMID(kClassIDSpace, kCopyStreamBoss, kShuksanPrefix + 29)
DECLARE_PMID(kClassIDSpace, kDBStreamCopyBoss, kShuksanPrefix + 30)
DECLARE_PMID(kClassIDSpace, kDBStreamWriteBoss, kShuksanPrefix + 31)
DECLARE_PMID(kClassIDSpace, kDBStreamReadBoss, kShuksanPrefix + 32)
DECLARE_PMID(kClassIDSpace, kPointerStreamReadBoss, kShuksanPrefix + 33)
DECLARE_PMID(kClassIDSpace, kPointerStreamWriteBoss, kShuksanPrefix + 34)
DECLARE_PMID(kClassIDSpace, kUIDCheckStreamBoss, kShuksanPrefix + 35)
DECLARE_PMID(kClassIDSpace, kFileStreamReadBoss, kShuksanPrefix + 36)
DECLARE_PMID(kClassIDSpace, kFileStreamWriteBoss, kShuksanPrefix + 37)
DECLARE_PMID(kClassIDSpace, kResourceStreamReadBoss, kShuksanPrefix + 38)
DECLARE_PMID(kClassIDSpace, kObjectResourceStreamReadBoss, kShuksanPrefix + 39)
DECLARE_PMID(kClassIDSpace, kCStreamReadBoss, kShuksanPrefix + 40)
DECLARE_PMID(kClassIDSpace, kPMPersistDataBlobBoss, kShuksanPrefix + 41)
//gap
DECLARE_PMID(kClassIDSpace, kDocWindowBoss, kShuksanPrefix + 43) // FIXME_OWL2: obsolete - can we remove it? Replaced by kDocumentPresentationBoss
DECLARE_PMID(kClassIDSpace, kTempFileStreamReadBoss, kShuksanPrefix + 44)
DECLARE_PMID(kClassIDSpace, kCloseDialogCmdBoss, kShuksanPrefix + 45)
DECLARE_PMID(kClassIDSpace, kQuitCmdBoss, kShuksanPrefix + 46)
//gap
DECLARE_PMID(kClassIDSpace, kObjectTextFileStreamWriteBoss, kShuksanPrefix + 48)
DECLARE_PMID(kClassIDSpace, kSelectWindowComponentBoss, kShuksanPrefix + 49)
DECLARE_PMID(kClassIDSpace, kPaletteActionBoss, kShuksanPrefix + 50)
DECLARE_PMID(kClassIDSpace, kCloseAllAndQuitCmdBoss, kShuksanPrefix + 51)
DECLARE_PMID(kClassIDSpace, kDBErrorInfoBoss, kShuksanPrefix + 52)
DECLARE_PMID(kClassIDSpace, kCloseAllCmdBoss, kShuksanPrefix + 53)
DECLARE_PMID(kClassIDSpace, kShutdownNotificationServiceBoss, kShuksanPrefix + 54)
DECLARE_PMID(kClassIDSpace, kObjectRefBoss, kShuksanPrefix + 55)
DECLARE_PMID(kClassIDSpace, kEuropeanEncodingMacToWinBoss, kShuksanPrefix + 56)
DECLARE_PMID(kClassIDSpace, kEuropeanEncodingWinToMacBoss, kShuksanPrefix + 57)
DECLARE_PMID(kClassIDSpace, kBossRecyclerShutdownNotificationServiceBoss, kShuksanPrefix + 58)
DECLARE_PMID(kClassIDSpace, kMemStreamWriteRecycleBoss, kShuksanPrefix + 59)
DECLARE_PMID(kClassIDSpace, kMemStreamReadRecycleBoss, kShuksanPrefix + 60)
DECLARE_PMID(kClassIDSpace, kProgressBarDialogBoss, kShuksanPrefix + 61)
DECLARE_PMID(kClassIDSpace, kProgressBarCancelButtonBoss, kShuksanPrefix + 62)
DECLARE_PMID(kClassIDSpace, kDeleteUIDsCmdBoss, kShuksanPrefix + 63)
DECLARE_PMID(kClassIDSpace, kToolManagerBoss, kShuksanPrefix + 64)
DECLARE_PMID(kClassIDSpace, kSetToolCmdBoss, kShuksanPrefix + 65)
//gap
DECLARE_PMID(kClassIDSpace, kApplKBSCBoss, kShuksanPrefix + 69)
DECLARE_PMID(kClassIDSpace, kDBSkipPubFileSharingShieldStreamReadBoss, kShuksanPrefix + 70)
//gap
DECLARE_PMID(kClassIDSpace, kTagRegistryBoss, kShuksanPrefix + 72)
DECLARE_PMID(kClassIDSpace, kMemStreamWriteBoss, kShuksanPrefix + 73)
DECLARE_PMID(kClassIDSpace, kMemStreamReadBoss, kShuksanPrefix + 74)
DECLARE_PMID(kClassIDSpace, kHTBInterfaceAlwaysActiveBoss, kShuksanPrefix + 75)
DECLARE_PMID(kClassIDSpace, kConvertStreamBoss, kShuksanPrefix + 76)
DECLARE_PMID(kClassIDSpace, kPluginBoss, kShuksanPrefix + 77)
DECLARE_PMID(kClassIDSpace, kClassDictBoss, kShuksanPrefix + 78)
DECLARE_PMID(kClassIDSpace, kInterfaceRegistryBoss, kShuksanPrefix + 79)
DECLARE_PMID(kClassIDSpace, kIDListBoss, kShuksanPrefix + 80)
//gap
DECLARE_PMID(kClassIDSpace, kDeleteUIDsNoUndoCmdBoss, kShuksanPrefix + 85)
DECLARE_PMID(kClassIDSpace, kContentMgrBoss, kShuksanPrefix + 86)
DECLARE_PMID(kClassIDSpace, kEnvironmentCheckThreadBoss, kShuksanPrefix + 87)
DECLARE_PMID(kClassIDSpace, kDumpPubTestMenuImplBoss, kShuksanPrefix + 88)
DECLARE_PMID(kClassIDSpace, kDestroyPanelCmdBoss, kShuksanPrefix + 89)
DECLARE_PMID(kClassIDSpace, kHidePanelCmdBoss, kShuksanPrefix + 90)
//gap
DECLARE_PMID(kClassIDSpace, kDBStreamCopyOfIPMPersistObjectBoss, kShuksanPrefix + 92)
//gap
DECLARE_PMID(kClassIDSpace, kUnusedBoss, kShuksanPrefix + 94)
DECLARE_PMID(kClassIDSpace, kMissingPluginsDialogBoss, kShuksanPrefix + 95)
DECLARE_PMID(kClassIDSpace, kMissingPluginsListWidgetBoss, kShuksanPrefix + 96)
DECLARE_PMID(kClassIDSpace, kMissingPluginsWarningStaticWidgetBoss, kShuksanPrefix + 97)
DECLARE_PMID(kClassIDSpace, kMissingPluginsDialogCmdBoss, kShuksanPrefix + 98)
DECLARE_PMID(kClassIDSpace, kAppConversionProviderBoss, kShuksanPrefix + 99)
DECLARE_PMID(kClassIDSpace, kSetShowAlertRegistryCmdBoss, kShuksanPrefix + 100)
DECLARE_PMID(kClassIDSpace, kTraceMenuBoss, kShuksanPrefix + 101)
DECLARE_PMID(kClassIDSpace, kHybridTargetingBoss, kShuksanPrefix + 102)
DECLARE_PMID(kClassIDSpace, kAbstractSelectionBoss, kShuksanPrefix + 103)
DECLARE_PMID(kClassIDSpace, kSelectionStartupShutdownBoss, kShuksanPrefix + 104)
DECLARE_PMID(kClassIDSpace, kSelectionInterfaceAlwaysActiveBoss, kShuksanPrefix + 105)
DECLARE_PMID(kClassIDSpace, kMissingConversionsDialogBoss, kShuksanPrefix + 106)
DECLARE_PMID(kClassIDSpace, kFloatingTabPaletteFactoryBoss, kShuksanPrefix + 107)
//gap
DECLARE_PMID(kClassIDSpace, kControlSetDlgBoss, kShuksanPrefix + 113)
DECLARE_PMID(kClassIDSpace, kControlSetDlgListBoxBoss, kShuksanPrefix + 114)
//gap
DECLARE_PMID(kClassIDSpace, kControlSetDlgElementBoss, kShuksanPrefix + 116)
//gap
DECLARE_PMID(kClassIDSpace, kTablessKitDragWidgetBoss, kShuksanPrefix + 118)
DECLARE_PMID(kClassIDSpace, kAppCodeConversionProviderBoss, kShuksanPrefix + 119)
//gap
DECLARE_PMID(kClassIDSpace, kDVTests_TestMenuBoss, kShuksanPrefix + 121)
DECLARE_PMID(kClassIDSpace, kAddonsActionComponentBoss, kShuksanPrefix + 122)

// Public bosses

DECLARE_PMID(kClassIDSpace, kPublicConversionProviderBoss, kShuksanPrefix + 150)
// gap 151 - kLayoutISuiteBoss moved to GenericPageItem
DECLARE_PMID(kClassIDSpace, kDocumentDefaultSuiteBoss, kShuksanPrefix + 152)
//DECLARE_PMID(kClassIDSpace, kDocumentDefaultISuiteBoss, kShuksanPrefix + 153)
// gap 154 - kLayoutSelectionServiceBoss moved to GenericPageItem
DECLARE_PMID(kClassIDSpace, kApplicationDefaultSuiteBoss, kShuksanPrefix + 155)
//DECLARE_PMID(kClassIDSpace, kApplicationDefaultISuiteBoss, kShuksanPrefix + 156)
//DECLARE_PMID(kClassIDSpace, kIntegratorISuiteBoss, kShuksanPrefix + 157)
DECLARE_PMID(kClassIDSpace, kPhase2ConversionSignalMgrBoss, kShuksanPrefix + 158)

DECLARE_PMID(kClassIDSpace, kUnitTestBoss, kShuksanPrefix + 159)
//gap
// gap 161 - kLayoutSuiteBoss moved to GenericPageItem

//DECLARE_PMID(kClassIDSpace, kDocumentDefaultBoss, kShuksanPrefix + 162) • now kDocWorkspaceBoss
//DECLARE_PMID(kClassIDSpace, kApplicationDefaultBoss, kShuksanPrefix + 163) • now kWorkspaceBoss
DECLARE_PMID(kClassIDSpace, kIntegratorSuiteBoss, kShuksanPrefix + 164)
// gap 165 - unknown???
DECLARE_PMID(kClassIDSpace, kSwatchesSyncBoss, kShuksanPrefix + 166)
DECLARE_PMID(kClassIDSpace, kContentMgrDebugMenuBoss, kShuksanPrefix + 167)
DECLARE_PMID(kClassIDSpace, kObjectModelBoss, kShuksanPrefix + 168)
DECLARE_PMID(kClassIDSpace, kAliasConversionBoss, kShuksanPrefix + 169)
DECLARE_PMID(kClassIDSpace, kAppIteratorRegBoss, kShuksanPrefix + 170)
DECLARE_PMID(kClassIDSpace, kPublicIteratorRegBoss, kShuksanPrefix + 171)
DECLARE_PMID(kClassIDSpace, kPublicCodeConversionProviderBoss, kShuksanPrefix + 172)


DECLARE_PMID(kClassIDSpace, kSetDrawOptionsCmdBoss, kShuksanPrefix + 200)
DECLARE_PMID(kClassIDSpace, kUtilsBoss, kShuksanPrefix + 201)
//DECLARE_PMID(kClassIDSpace, kMainThreadOnly_UtilsBoss, kShuksanPrefix + 202)

DECLARE_PMID(kClassIDSpace, kWarningWithDontShowDialogBoss, kShuksanPrefix + 203)
//DECLARE_PMID(kClassIDSpace, kWorkerThreadOnly_UtilsBoss, kShuksanPrefix + 204 )
DECLARE_PMID(kClassIDSpace, kRawXMLDumpStreamBoss, kShuksanPrefix + 205 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 206 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 207 )
DECLARE_PMID(kClassIDSpace, kXReferencesSessionSignalMgrBoss, kShuksanPrefix + 208 )
DECLARE_PMID(kClassIDSpace, kRIDXObsoleteStorageBoss, kShuksanPrefix + 209 )
DECLARE_PMID(kClassIDSpace, kRIDXObsoletePagedSetStorageBoss, kShuksanPrefix + 210 )
DECLARE_PMID(kClassIDSpace, kRIDXUnderlyingQueryBoss, kShuksanPrefix + 211 )
DECLARE_PMID(kClassIDSpace, kRIDXBoss, kShuksanPrefix + 212 )
DECLARE_PMID(kClassIDSpace, kRIDXStorageBoss, kShuksanPrefix + 213 )
DECLARE_PMID(kClassIDSpace, kRIDXPagedSetStorageBoss, kShuksanPrefix + 214 )
DECLARE_PMID(kClassIDSpace, kIdleTaskThreadBoss, kShuksanPrefix + 215 )
DECLARE_PMID(kClassIDSpace, kIDThreadApplicationProxyBoss, kShuksanPrefix + 216 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 217 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 218 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 219 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 220 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 221 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 222 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 223 )
DECLARE_PMID(kClassIDSpace, kMouseWatcherIdleTaskBoss, kShuksanPrefix + 224 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 225 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 226 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 227 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 228 )
DECLARE_PMID(kClassIDSpace, kTargetingBoss, kShuksanPrefix + 229 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 230 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 231 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 232 )
DECLARE_PMID(kClassIDSpace, kSelectionExtentionInitializerBoss, kShuksanPrefix + 233 )
DECLARE_PMID(kClassIDSpace, kIDThreadSessionBoss,kShuksanPrefix + 234 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 235 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 236 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 237 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 238 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 239 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 240 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 241 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 242 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 243 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 244 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 245 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 246 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 247 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 248 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 249 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 250 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 251 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 252 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 253 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 254 )
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kShuksanPrefix + 255 )


// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IUNKNOWN, kShuksanPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISESSION, kShuksanPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLICATION, kShuksanPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTMODEL, kShuksanPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOUSEWATCHER, kShuksanPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURSORMGR, kShuksanPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHREAD, kShuksanPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IEVENTHANDLER, kShuksanPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IEVENT, kShuksanPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IEVENTDISPATCHER, kShuksanPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYBOARD, kShuksanPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLASSINFO, kShuksanPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IENVIRONMENT, kShuksanPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLUGINLIST, kShuksanPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_NEVERWRITESTODOCUMENT, kShuksanPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWLIST, kShuksanPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTMENU, kShuksanPrefix + 17) // Debugging only!
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOW, kShuksanPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOGICALFILE, kShuksanPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IDISKPAGEMGR, kShuksanPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLICATIONDELEGATE, kShuksanPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPSUITE, kShuksanPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IDBERRORINFO, kShuksanPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGEMANAGER, kShuksanPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUBJECT, kShuksanPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBSERVER, kShuksanPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESIZETRACKERDATA, kShuksanPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGMGR, kShuksanPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKERTIMER, kShuksanPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ICALLBACKTIMER, kShuksanPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTYMASTER, kShuksanPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IK2SERVICEREGISTRY, kShuksanPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IDVEVENTHANDLER, kShuksanPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVECONTEXT, kShuksanPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKER, kShuksanPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IK2SERVICEPROVIDER, kShuksanPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTTEXTFILESTREAMDATA, kShuksanPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEMORYMESSAGE, kShuksanPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOUSEPOSITIONNOTIFIER, kShuksanPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLMANAGER, kShuksanPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLREGISTER, kShuksanPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELREGISTER, kShuksanPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOL, kShuksanPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROGRESSBARMGR, kShuksanPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDREFCOUNT, kShuksanPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCECONVERTER, kShuksanPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTEVENTHANDLER, kShuksanPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMPERSIST, kShuksanPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOSSINITIALIZER, kShuksanPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLLINGUNKNOWN, kShuksanPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IPERSISTUIDDATA, kShuksanPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKERFACTORY, kShuksanPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKERREGISTER, kShuksanPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEMORYMANAGER, kShuksanPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEMORYCOMPACTIONTHREAD, kShuksanPrefix + 55)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISPECIFIERDATA, kShuksanPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_IEASTEREGG, kShuksanPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYSTREAMDATA, kShuksanPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IDBSTREAMCOPYDATA, kShuksanPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_IDBSTREAMDATA, kShuksanPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILESTREAMDATA, kShuksanPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTERSTREAMDATA, kShuksanPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESOURCESTREAMDATA, kShuksanPrefix + 63)

DECLARE_PMID(kInterfaceIDSpace, IID_IUIDCHECKSTREAMDATA, kShuksanPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMSTREAM, kShuksanPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMSTREAMIN, kShuksanPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IERRORSTATE, kShuksanPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IMONITORINFO, kShuksanPrefix + 68)

DECLARE_PMID(kInterfaceIDSpace, IID_ICONTEXTMENUSUITE, kShuksanPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_IWORDCOUNTINFODATA,	kShuksanPrefix + 70)
//DECLARE_PMID(kInterfaceIDSpace, IID_IUNUSED,	kShuksanPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWSETTINGS, kShuksanPrefix + 72)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTARTUPSHUTDOWN, kShuksanPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONSTRAINTRACKER, kShuksanPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_IERRORSTRINGSERVICE, kShuksanPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_IRENDERINGOBJECT, kShuksanPrefix + 76)
// obsolete DECLARE_PMID(kInterfaceIDSpace, IID_ISTRIPCONVERSIONDATA, kShuksanPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSERVICEMGR, kShuksanPrefix + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDLETASKMGR, kShuksanPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTMGR, kShuksanPrefix + 80)

DECLARE_PMID(kInterfaceIDSpace, IID_ISHUTDOWNNOTIFIER, kShuksanPrefix + 81)

DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTREFDATA, kShuksanPrefix + 82)

DECLARE_PMID(kInterfaceIDSpace, IID_IENCODINGCONVERTER, kShuksanPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACEFONTS, kShuksanPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace, IID_IALIASCONVERSIONDATA, kShuksanPrefix + 85)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEMORYSTREAMDATA, kShuksanPrefix + 87)

DECLARE_PMID(kInterfaceIDSpace, IID_IPANELMGR, kShuksanPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_IXREFERENCEUID, kShuksanPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTIONMODE, kShuksanPrefix + 90) // Actually IID_BOOLDATA
//DECLARE_PMID(kInterfaceIDSpace, IID_IRENDERINGOBJECTSUITE, kShuksanPrefix + 91)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGREGISTRY, kShuksanPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRISTATEDATA, kShuksanPrefix + 94)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTUTILS, kShuksanPrefix + 95)
DECLARE_PMID(kInterfaceIDSpace, IID_ISERIALNUMBER, kShuksanPrefix + 96)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERSIONMGR, kShuksanPrefix + 97)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERSIONPROVIDER, kShuksanPrefix + 98)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTTRACKER, kShuksanPrefix + 99)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPACCESS, kShuksanPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWUIDCMDDATA, kShuksanPrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWOBJECTCHANGES, kShuksanPrefix + 102)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOCUS_EH_GETTING_REMOVED, kShuksanPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONMANAGER_BROADCAST, kShuksanPrefix + 104)

DECLARE_PMID(kInterfaceIDSpace, IID_IRESPONDER, kShuksanPrefix + 105)
DECLARE_PMID(kInterfaceIDSpace, IID_ISIGNALMGR, kShuksanPrefix + 106)

#ifdef DEBUG
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACEREFCOUNT, kShuksanPrefix + 107)
#endif

DECLARE_PMID(kInterfaceIDSpace, IID_ICLASSIDDATA, kShuksanPrefix + 108)

#ifdef ID_ENABLE_DEBUGGING
DECLARE_PMID(kInterfaceIDSpace, IID_ILOGBOOLPREFS, kShuksanPrefix + 109)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTMGRACCESS, kShuksanPrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTLOG, kShuksanPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_MISSINGPLUGINSTEXTCONTROLDATA, kShuksanPrefix + 112)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONIDDATA, kShuksanPrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLUGINLISTUTILS, kShuksanPrefix + 114)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWALERTREGISTRY, kShuksanPrefix + 120)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETSHOWALERTREGISTRYCMDDATA, kShuksanPrefix + 121)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETSHOWALERTREGISTRYCMD, kShuksanPrefix + 122)

DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACEIDDATA, kShuksanPrefix + 123)
DECLARE_PMID(kInterfaceIDSpace, IID_IGATHERIDSTREAMDATA, kShuksanPrefix + 124)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROGRESSBARMANAGER, kShuksanPrefix + 125)

DECLARE_PMID(kInterfaceIDSpace, IID_ICONCRETESELECTION, kShuksanPrefix + 126)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTTARGET, kShuksanPrefix + 127)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTSELECTION_ISUITE, kShuksanPrefix + 128)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELSUITE_B, kShuksanPrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONMANAGER, kShuksanPrefix + 130)
DECLARE_PMID(kInterfaceIDSpace, IID_IWORKSPACESELECTION, kShuksanPrefix + 131)
DECLARE_PMID(kInterfaceIDSpace, IID_SELECTION_MESSAGE, kShuksanPrefix + 132)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULT_CSB, kShuksanPrefix + 134)
DECLARE_PMID(kInterfaceIDSpace, IID_IPALETTEFACTORY, kShuksanPrefix + 135)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSET, kShuksanPrefix + 136)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPHASE2CONVERSION, kShuksanPrefix + 138)

#ifdef DEBUG
DECLARE_PMID(kInterfaceIDSpace, IID_IGETINTERFACEIMPL, kShuksanPrefix + 139)
#endif

DECLARE_PMID(kInterfaceIDSpace, IID_ICACHEHINTS, kShuksanPrefix + 140)

DECLARE_PMID(kInterfaceIDSpace, IID_SELECTION_INTERNAL_MESSAGE, kShuksanPrefix + 141)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPTIONALDRAWPASS, kShuksanPrefix + 142)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARCEL, kShuksanPrefix + 143)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARCELSHAPE, kShuksanPrefix + 144)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARCELLIST, kShuksanPrefix + 145)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTBMANAGER, kShuksanPrefix + 146)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTITERATORREGISTRY, kShuksanPrefix + 147)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTITERATORREGISTER, kShuksanPrefix + 148)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARCELCONTAINER, kShuksanPrefix + 149)

DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONHIGHLIGHTER, kShuksanPrefix + 150)
DECLARE_PMID(kInterfaceIDSpace, IID_SELECTION_HIGHLIGHT_MESSAGE, kShuksanPrefix + 151)

DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWCYCLEBUTTON, kShuksanPrefix + 152)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLESYNCSERVICE, kShuksanPrefix + 153)

DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONSNAPSHOTSUITE, kShuksanPrefix + 154)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLBOXUTILS, kShuksanPrefix + 155)

DECLARE_PMID(kInterfaceIDSpace, IID_IARRANGESUITE, kShuksanPrefix + 156)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMLOCKSUITE, kShuksanPrefix + 157)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTEGRATORTARGET, kShuksanPrefix + 158)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMECONTENTSUITE, kShuksanPrefix + 159)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHOPERATIONSUITE, kShuksanPrefix + 160)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPSOURCESUITE, kShuksanPrefix + 161)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTSHAPESUITE, kShuksanPrefix + 162)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONBOXHANDLESHAPESUITE, kShuksanPrefix + 163 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTYLIST, kShuksanPrefix + 164 )

DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXSTREAMOBSERVER, kShuksanPrefix + 165 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDX, kShuksanPrefix + 166 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXINTERNAL, kShuksanPrefix + 167 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXSTORAGE, kShuksanPrefix + 168 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEDCONTAINERSTORAGE, kShuksanPrefix + 169 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXQUERY, kShuksanPrefix + 170 )
DECLARE_PMID(kInterfaceIDSpace, IID_PLUGINLOADIDLETASK, kShuksanPrefix + 171 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXACCESS, kShuksanPrefix + 172 )
// Reserved for the dense_hash_map as an invalid interface id
DECLARE_PMID(kInterfaceIDSpace, IID_DELETEDHASHMAPKEY, kShuksanPrefix + 173 )
DECLARE_PMID(kInterfaceIDSpace, IID_IURIDATA, kShuksanPrefix + 174 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDVRENDERINGOBJECT, kShuksanPrefix + 175 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEPREFSHORTCUTLAUNCH, kShuksanPrefix + 176 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTOCKUTILS, kShuksanPrefix + 177)
DECLARE_PMID(kInterfaceIDSpace, IID_ILEARNPANELUTILS, kShuksanPrefix + 178)
// gap 178 - 198 have never been used. Use these first before extending the series.

DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTHITTESTSUITE, kShuksanPrefix + 199)


DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWOPTIONS, kShuksanPrefix + 200)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETDRAWOPTIONSCMDDATA, kShuksanPrefix + 201)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWOPTIONSSETID, kShuksanPrefix + 202)

DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONDATASUITE, kShuksanPrefix + 203)
DECLARE_PMID(kInterfaceIDSpace, IID_IGEOMETRYSUITE, kShuksanPrefix + 204)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMSUITE, kShuksanPrefix + 205)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTFRAMEOPTIONS_ISUITE, kShuksanPrefix + 206)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEOUTLINES_ISUITE, kShuksanPrefix + 207)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLCHANGESUITE, kShuksanPrefix + 208)


DECLARE_PMID(kInterfaceIDSpace, IID_ISUITEREGISTER, kShuksanPrefix + 209)
DECLARE_PMID(kInterfaceIDSpace, IID_SUITEDATABASE, kShuksanPrefix + 210)
// obsolete DECLARE_PMID(kInterfaceIDSpace, IID_IPLUGINREFCOUNT, kShuksanPrefix + 211 )
DECLARE_PMID(kInterfaceIDSpace, IID_IINITIALIZER, kShuksanPrefix + 212)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEINITIALIZER, kShuksanPrefix + 213)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESPONDFORERROR, kShuksanPrefix + 214 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 215 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 216 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 217 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 218 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTLAYOUTSUITE, kShuksanPrefix + 219 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 220 )
DECLARE_PMID(kInterfaceIDSpace, IID_SELECTION_EXTENTION_REGISTRY, kShuksanPrefix + 221 )
DECLARE_PMID(kInterfaceIDSpace, IID_INEWSELECTION_OBSERVER, kShuksanPrefix + 222 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 223 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETUTILS, kShuksanPrefix + 224 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 225 )
DECLARE_PMID(kInterfaceIDSpace, IID_SELECTION_IDLETASK, kShuksanPrefix + 226 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICONCRETESELECTION_IDLETASK_DATA, kShuksanPrefix + 227 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 228 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 229 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYPROPERTIESSUITE, kShuksanPrefix + 230 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 231 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 232 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 233 )
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kShuksanPrefix + 234 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITOUCHTOOLCOLLECTOR, kShuksanPrefix + 235)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDLETASKTHREAD, kShuksanPrefix + 236 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKGRIDFACADE, kShuksanPrefix + 237 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTEFACADE, kShuksanPrefix + 238 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATESELECTIONACCESS, kShuksanPrefix + 239 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTEOPTIONS_ISUITE, kShuksanPrefix + 240)
DECLARE_PMID(kInterfaceIDSpace, IID_IZORDERSELECTIONSUITE, kShuksanPrefix + 241 )
DECLARE_PMID(kInterfaceIDSpace, IID_IIDLETASK, kShuksanPrefix + 242 )
DECLARE_PMID(kInterfaceIDSpace, IID_IEVENTWATCHER, kShuksanPrefix + 243 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTVARIABLEFACADE, kShuksanPrefix + 244 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTVARIABLE_ISUITE, kShuksanPrefix + 245)
DECLARE_PMID(kInterfaceIDSpace, IID_IALIGNANDDISTRIBUTESUITE, kShuksanPrefix + 246 )
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSUITE, kShuksanPrefix + 247 )
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCEPOINTSUITE, kShuksanPrefix + 248 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTEPANDREPEATSUITE, kShuksanPrefix + 249 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEDATASUITE, kShuksanPrefix + 250 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPITEMSUITE, kShuksanPrefix + 251 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDATA_SYSPOINT, kShuksanPrefix + 252 )
DECLARE_PMID(kInterfaceIDSpace, IID_IRENDERINGOBJECTUI, kShuksanPrefix + 253 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONFACTORY, kShuksanPrefix + 254)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNIFORMTARGETFACTORY, kShuksanPrefix + 255)

DECLARE_PMID(kInterfaceIDSpace, IID_ITOUCHCONTROL, kShuksan2Prefix + 1)

// Endnotes
DECLARE_PMID(kInterfaceIDSpace, IID_IENDNOTEFACADE, kShuksan2Prefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDNOTEOPTIONS_ISUITE, kShuksan2Prefix + 3)


// <Widget ID>
//Widget IDs
//gap
// From TabAreaDefs: [Better place for these -- IHG]
DECLARE_PMID(kWidgetIDSpace, kOldTabAreaWidgetID, kShuksanPrefix + 56)
//gap
DECLARE_PMID(kWidgetIDSpace, kOldPanelTabWidgetID, kShuksanPrefix + 58)

//gap

DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID0, kShuksanPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID1, kShuksanPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID2, kShuksanPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID3, kShuksanPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID4, kShuksanPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID5, kShuksanPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kShuksanWidgetID6, kShuksanPrefix + 67)

DECLARE_PMID(kWidgetIDSpace, kMissingPluginParentWidgetID, kShuksanPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kMissingPluginListHilitePanelWidgetID, kShuksanPrefix + 69)
//DECLARE_PMID(kWidgetIDSpace, kMissingPluginListGroupWidgetID, kShuksanPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kMissingStdListBoxWidgetID, kShuksanPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kMissingPluginWarningSignWidgetID, kShuksanPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kMissingPluginWarningMsgWidgetID, kShuksanPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kMissingPluginListWidgetID, kShuksanPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kMissingPluginListScrollBarWidgetID, kShuksanPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kDontWarnAgainButtonWidgetID, kShuksanPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kMissingConversionsParentWidgetID, kShuksanPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kMissingConversionsErrorMsgWidgetID, kShuksanPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kMissingConversionsListHilitePanelWidgetID, kShuksanPrefix + 79)
//DECLARE_PMID(kWidgetIDSpace, kMissingConversionsListGroupWidgetID, kShuksanPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kMissingConversionsListWidgetID, kShuksanPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kMissingConversionsListScrollBarWidgetID, kShuksanPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kMissingConversionsErrorSignWidgetID, kShuksanPrefix + 83)
//gap 84 - side tab widgets moved to tab station plugin (incopy)
DECLARE_PMID(kWidgetIDSpace, kCtrlSetListBorderWidgetID, kShuksanPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kControlSetDlgWidgetId, kShuksanPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kControlSetDlgListWidgetID, kShuksanPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kControlSetDlgCheckboxWidgetID, kShuksanPrefix + 88)
//gap
DECLARE_PMID(kWidgetIDSpace, kControlSetDlgListParentWidgetId, kShuksanPrefix + 90)

DECLARE_PMID(kWidgetIDSpace, kWarningDontShowTextWidgetID, kShuksanPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kWarningDontShowAgainCheckBoxWidgetID, kShuksanPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kWarningDontShowDialogWidgetID, kShuksanPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kWarningDontShowIconWidgetID, kShuksanPrefix + 94)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kPageItemRectangularImpl, kShuksanPrefix + 1)

DECLARE_PMID(kImplementationIDSpace, kKeyBoardImpl, kShuksanPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kEventDispatcherImpl, kShuksanPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapImpl, kShuksanPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kObjectModelShellImpl, kShuksanPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAppWindowListImpl, kShuksanPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kActionIDFactoryImpl, kShuksanPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCSessionImpl, kShuksanPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kApplicationObserverImpl, kShuksanPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCActiveContextImpl, kShuksanPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kDVEventDispatcherImpl, kShuksanPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPlugInListShellImpl, kShuksanPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kServiceRegistryImpl, kShuksanPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kDBStreamWrite_AllowPubFileWriteImpl, kShuksanPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kNeverWritesToDocumentImpl, kShuksanPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kClassInfoImpl, kShuksanPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kObjectModelImpl, kShuksanPrefix + 17)		// tag for object model data

DECLARE_PMID(kImplementationIDSpace, kPersistPMPointDataImpl, kShuksanPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDlgEventHandlerImpl, kShuksanPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kScrapImpl, kShuksanPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kReferenceConverterProviderImpl, kShuksanPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kReferenceConverterImpl, kShuksanPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCPersistUIDRefDataImpl, kShuksanPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kUIDRefCountImpl, kShuksanPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPersistUIDDataImpl, kShuksanPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kMonitorInfoImpl, kShuksanPrefix + 26)

DECLARE_PMID(kImplementationIDSpace, kTipRegisterProviderImpl, kShuksanPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSignalMgrImpl, kShuksanPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kAliasConversionDataImpl, kShuksanPrefix + 29)

	// Widgets and related objects
DECLARE_PMID(kImplementationIDSpace, kTabAreaPanelTipImpl, kShuksanPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPanelTabWidgetTipImpl, kShuksanPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTabAreaViewImpl, kShuksanPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kTabAreaEventHandlerImpl, kShuksanPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kAbstractWindowImpl, kShuksanPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kTabPanelControlDataImpl, kShuksanPrefix + 35)
//gap
DECLARE_PMID(kImplementationIDSpace, kPanelTabViewImpl, kShuksanPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDBSkipPubFileSharingShieldStreamReadImpl, kShuksanPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPanelPtrImpl, kShuksanPrefix + 39)

//MenuGroups
DECLARE_PMID(kImplementationIDSpace, kAboutMenuComponentImpl, kShuksanPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kUndoRedoMenuComponentImpl, kShuksanPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kExtensionManagerMenuComponentImpl, kShuksanPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kScrapComponentImpl, kShuksanPrefix + 43)
//gap
DECLARE_PMID(kImplementationIDSpace, kCSubjectImpl, kShuksanPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kCPersistSubjectImpl, kShuksanPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kMainActionServiceImpl, kShuksanPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kCloseWinCmdImpl, kShuksanPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kCloseWinCmdDataImpl, kShuksanPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kResizeWinCmdImpl, kShuksanPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kResizeWinCmdDataImpl, kShuksanPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kZoomWinCmdImpl, kShuksanPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kZoomWinCmdDataImpl, kShuksanPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kInterfaceBrightnessPrefChangeCmdImpl, kShuksanPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kTriStateDataImpl, kShuksanPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSerialNumberImpl, kShuksanPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kConversionMgrImpl, kShuksanPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kConversionProviderImpl_obsolete, kShuksanPrefix + 58)
//gap
DECLARE_PMID(kImplementationIDSpace, kPersistStringDataImpl, kShuksanPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kCallbackTaskImpl, kShuksanPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kCallbackTimerImpl, kShuksanPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kMouseTrackerImpl, kShuksanPrefix + 63)

// Edge implementations
//gap
DECLARE_PMID(kImplementationIDSpace, kApplicationImpl, kShuksanPrefix + 65	)
DECLARE_PMID(kImplementationIDSpace, kDlgMgrImpl, kShuksanPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kCursorMgrImpl, kShuksanPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kAlertMgrImpl, kShuksanPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kGenericItemResizeTrackerImpl, kShuksanPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kEnvironmentImpl, kShuksanPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kAppFrameWindowImpl, kShuksanPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kAppFrameEventHandlerImpl, kShuksanPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kWindowSettingsImpl, kShuksanPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kProgressBarMgrImpl, kShuksanPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kDialogImpl, kShuksanPrefix + 77)
//gap
DECLARE_PMID(kImplementationIDSpace, kPMPersistImpl, kShuksanPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kPMPersistDataBlobImpl, kShuksanPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kPageItemTransformImpl, kShuksanPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCTrackerEventHandlerImpl, kShuksanPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kPageItemCompatibilityImpl, kShuksanPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kGeometryRectangularImpl, kShuksanPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kControlPointsRectangularImpl, kShuksanPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kPersistFillImpl_obsolete, kShuksanPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kCSpriteImpl, kShuksanPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kCRectResizeTrackerImpl, kShuksanPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kCResizeTrackerDataImpl, kShuksanPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kWindowImpl, kShuksanPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kCHierarchyNodeImpl, kShuksanPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kPersistStrokeImpl_obsolete, kShuksanPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kContentMgrAccessImpl, kShuksanPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kIEHandlerMasterImpl, kShuksanPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kIteratorEventImpl, kShuksanPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kCRotateSpriteImpl, kShuksanPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kCObserverImpl, kShuksanPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kPageItemPanoramaImpl, kShuksanPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kPlugInFileDataImpl, kShuksanPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kGeometryGraphicImpl, kShuksanPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kWindowEHImpl, kShuksanPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kSelectWindowComponentImpl, kShuksanPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kCEmptyObserverImpl, kShuksanPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kCTrackerFactoryImpl, kShuksanPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kAppTestMenuImpl, kShuksanPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kMemoryManagerImpl, kShuksanPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kMemoryCompactionThreadImpl, kShuksanPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTraceMenuImpl, kShuksanPrefix + 108)

// Stream implementations
DECLARE_PMID(kImplementationIDSpace, kCopyStreamDataImpl, kShuksanPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kDBStreamCopyDataImpl, kShuksanPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kDBStreamDataImpl, kShuksanPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kFileStreamDataImpl, kShuksanPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kPointerStreamDataImpl, kShuksanPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kResourceStreamDataImpl, kShuksanPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kUIDCheckStreamDataImpl, kShuksanPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kCopyOutStreamImpl, kShuksanPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kDBStreamCopyImpl, kShuksanPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kDBStreamWriteImpl, kShuksanPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kDBStreamReadImpl, kShuksanPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kPointerStreamReadImpl, kShuksanPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kPointerStreamWriteImpl, kShuksanPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kUIDCheckStreamImpl, kShuksanPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kFileStreamReadImpl, kShuksanPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kFileStreamWriteImpl, kShuksanPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kResourceStreamReadImpl, kShuksanPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kObjectResourceStreamReadImpl, kShuksanPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kCopyInStreamImpl, kShuksanPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kErrorStateImpl, kShuksanPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kIntegratorTargetHTBImpl, kShuksanPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kDestroyPanelCmdImpl, kShuksanPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kCloseDialogCmdImpl, kShuksanPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kIntegratorTargetASBImpl, kShuksanPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kDBErrorInfoImpl, kShuksanPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kConversionServiceImpl, kShuksanPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kDrawingFeedbackSpriteImpl, kShuksanPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kSchemaBasedConversionImpl, kShuksanPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kErrorStringProviderImpl, kShuksanPrefix + 137) // Default reusable IK2ServiceProvider impl
DECLARE_PMID(kImplementationIDSpace, kApplicationErrorStringServiceImpl, kShuksanPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kPersistPMRectDataImpl, kShuksanPrefix + 139)

#ifdef ID_ENABLE_DEBUGGING
DECLARE_PMID(kImplementationIDSpace, kTraceDynamicTestMenuImpl, kShuksanPrefix + 140)
#endif

DECLARE_PMID(kImplementationIDSpace, kObjectTextFileStreamWriteImpl, kShuksanPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kObjectTextFileStreamDataImpl, kShuksanPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kWordCountInfoDataImpl, kShuksanPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kIdleTaskMgrImpl, kShuksanPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kContentMgrImpl, kShuksanPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kQuitCmdImpl, kShuksanPrefix + 146)

DECLARE_PMID(kImplementationIDSpace, kShutdownNotifierImpl, kShuksanPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kShutdownNotificationProviderImpl, kShuksanPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kWorkspaceObserverImpl, kShuksanPrefix + 149)

DECLARE_PMID(kImplementationIDSpace, kObjectRefDataImpl, kShuksanPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kPaletteActionComponentImpl, kShuksanPrefix + 151)

DECLARE_PMID(kImplementationIDSpace, kEuropeanEncodingMacToWinConverterImpl, kShuksanPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kSelectionDocumentObserverImpl, kShuksanPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kEuropeanEncodingWinToMacConverterImpl, kShuksanPrefix + 154)

DECLARE_PMID(kImplementationIDSpace, kTempFileStreamReadImpl, kShuksanPrefix + 155)

DECLARE_PMID(kImplementationIDSpace, kInterfaceFontsImpl, kShuksanPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kSessionViewPrefBoolDataImpl, kShuksanPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kSessionViewPrefFalseInitBoolDataImpl, kShuksanPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kMemStreamWriteRecycleImpl, kShuksanPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kMemStreamReadRecycleImpl, kShuksanPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kMemStreamDataImpl, kShuksanPrefix + 161)

DECLARE_PMID(kImplementationIDSpace, kPaletteMgrObserverImpl, kShuksanPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kPaletteMgrMenuComponentImpl, kShuksanPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kPanelMgrImpl, kShuksanPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kProgressBarDialogControllerImpl, kShuksanPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kProgressBarCancelButtonObserverImpl, kShuksanPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kDeleteUIDsCmdImpl, kShuksanPrefix + 167)

DECLARE_PMID(kImplementationIDSpace, kPersistBoolDataImpl, kShuksanPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kCStartupShutdownProviderImpl, kShuksanPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kCloseAllAndQuitCmdImpl, kShuksanPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kXReferenceUIDImpl, kShuksanPrefix + 171)

DECLARE_PMID(kImplementationIDSpace, kFileStreamWriteLazyImpl, kShuksanPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kPatientUserTimerImpl, kShuksanPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kTrackerTaskImpl, kShuksanPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kFileStreamReadLazyImpl, kShuksanPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kToolManagerImpl, kShuksanPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kSetToolCmdImpl, kShuksanPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kToolCmdDataImpl, kShuksanPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kLazyStartupShutdownProviderImpl, kShuksanPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kGenericServiceProviderImpl, kShuksanPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kZeroInitPersistIntDataImpl, kShuksanPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kPersistClassIDDataImpl, kShuksanPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kPersistIntDataImpl, kShuksanPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kNoSnapshotPersistIntDataImpl, kShuksanPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kApplKBSCComponentImpl, kShuksanPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kDocumentUIStateImpl, kShuksanPrefix + 187)	// New name for kDocWindowStateImpl, same number
DECLARE_PMID(kImplementationIDSpace, kNoSnapshotZeroInitPersistIntDataImpl, kShuksanPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kTagRegistryImpl, kShuksanPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kDocViewPrefBoolDataImpl, kShuksanPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kDocViewPrefFalseInitBoolDataImpl, kShuksanPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kNewUIDCmdDataImpl, kShuksanPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kDocumentUtilsImpl, kShuksanPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kDBStreamDataForCopyImpl, kShuksanPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kDBContentTrackerImpl, kShuksanPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kConvertStreamImpl, kShuksanPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kKBSCDataImpl_unused, kShuksanPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kPersistWidgetIDDataImpl, kShuksanPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kPersistActionIDDataImpl, kShuksanPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kPersistRealNumberDataImpl, kShuksanPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kPluginLoadIdleTaskImpl, kShuksanPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kSessionViewPrefIntDataImpl, kShuksanPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kSessionViewPrefZeroInitIntDataImpl, kShuksanPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kDeleteUIDsNoUndoCmdImpl, kShuksanPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kCPersistUIDRefDataImpl2, kShuksanPrefix + 205)

DECLARE_PMID(kImplementationIDSpace, kClassIDDataImpl, kShuksanPrefix + 206)

DECLARE_PMID(kImplementationIDSpace, kEnvironmentCheckThreadImpl, kShuksanPrefix + 207)

DECLARE_PMID(kImplementationIDSpace, kDumpPubTestMenuImpl, kShuksanPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kHidePanelCmdImpl, kShuksanPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kSelectWindowDynamicMenuImpl, kShuksanPrefix + 210)

DECLARE_PMID(kImplementationIDSpace, kProgressBarCancelButtonEHImpl, kShuksanPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kCToolRegisterProviderImpl, kShuksanPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kCTrackerRegisterProviderImpl, kShuksanPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kCPanelRegisterProviderImpl, kShuksanPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kCloseAllCmdImpl, kShuksanPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kDocumentLogImpl, kShuksanPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kBossRecyclerShutdownNotifierImpl, kShuksanPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kDBStreamCopyOfIPMPersistObjectImpl, kShuksanPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kMissingPluginsControllerImpl, kShuksanPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kMissingPluginsDialogCmdImpl, kShuksanPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kCursorMgrImpl2, kShuksanPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kAppConversionProviderImpl, kShuksanPrefix + 222)

DECLARE_PMID(kImplementationIDSpace, kPlugInListUtilsImpl, kShuksanPrefix + 223)

DECLARE_PMID(kImplementationIDSpace, kBossRecyclerShutdownNotificationProviderImpl, kShuksanPrefix + 225)

DECLARE_PMID(kImplementationIDSpace, kShowAlertRegistryImpl, kShuksanPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kSetShowAlertRegistryCmdImpl, kShuksanPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kSetShowAlertRegistryCmdDataImpl, kShuksanPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kConversionHookServiceImpl_obsolete, kShuksanPrefix + 229)

DECLARE_PMID(kImplementationIDSpace, kCPersistUIDRefDataImpl3, kShuksanPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kInterfaceIDDataImpl, kShuksanPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kFalseInitBoolDataImpl, kShuksanPrefix + 232)
//gap
// moved in Anna 15/Dec/00 to avoid conflict with existing file format Hotaka value
//DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionSuiteImpl, kShuksanPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kSelectionSuite_BImpl, kShuksanPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kSelectionManagerImpl, kShuksanPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kSelectionStartupShutdownImpl, kShuksanPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kWorkspaceSelectionImpl, kShuksanPrefix + 237)

DECLARE_PMID(kImplementationIDSpace, kSelectionIdleTaskDataImpl, kShuksanPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kSelectionIdleTaskImpl, kShuksanPrefix + 239)

DECLARE_PMID(kImplementationIDSpace, kCheckContentTrackerImpl, kShuksanPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kGatherIDStreamDataImpl, kShuksanPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kProgressBarManagerImpl, kShuksanPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kAutoServiceProviderImpl, kShuksanPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kMissingConversionsControllerImpl, kShuksanPrefix + 244)

DECLARE_PMID(kImplementationIDSpace, kSelectionServiceProviderImpl, kShuksanPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kHTBManagerImpl, kShuksanPrefix + 246)
// gap - kLayoutSelectionServiceImpl
DECLARE_PMID(kImplementationIDSpace, kDefaultCSBImpl, kShuksanPrefix + 248)

DECLARE_PMID(kImplementationIDSpace, kPaletteFactoryServiceImpl, kShuksanPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kFloatingTabPaletteFactoryImpl, kShuksanPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kDocViewPrefIntDataImpl, kShuksanPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kKitRegisterProviderImpl, kShuksanPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kDocViewPrefZeroInitIntDataImpl, kShuksanPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kFloatingTabPaltFactoryServImpl, kShuksanPrefix + 254)
// Reserved for the dense_hash_map as an invalid implementation id
DECLARE_PMID(kImplementationIDSpace, kDeletedHashMapKeyImpl, kShuksanPrefix + 255 )




DECLARE_PMID(kImplementationIDSpace, kControlSetDlgControllerImpl, kShuksan2Prefix + 10)
DECLARE_PMID(kImplementationIDSpace, kControlSetDlgListControllerImpl, kShuksan2Prefix + 11)
//gap
DECLARE_PMID(kImplementationIDSpace, kControlSetDlgObserverImpl, kShuksan2Prefix + 13)
DECLARE_PMID(kImplementationIDSpace, kControlSetHorzImpl, kShuksan2Prefix + 14)
DECLARE_PMID(kImplementationIDSpace, kControlSetVertImpl, kShuksan2Prefix + 15)
//gap
DECLARE_PMID(kImplementationIDSpace, kControlSetDlgViewImpl, kShuksan2Prefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTablessKitDragWidgetEHImpl, kShuksan2Prefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kTablessPaletteWindowImpl, kShuksan2Prefix + 19)
DECLARE_PMID(kImplementationIDSpace, kPhase2ConversionImpl, kShuksan2Prefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPhase2ConvSignalRespServiceImpl, kShuksan2Prefix + 21)

DECLARE_PMID(kImplementationIDSpace, kUnitTestMenuImpl, kShuksan2Prefix + 22)
DECLARE_PMID(kImplementationIDSpace, kUnitTestDynamicMenuImpl, kShuksan2Prefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCSB_ObserverImpl, kShuksan2Prefix + 24)

DECLARE_PMID(kImplementationIDSpace, kCacheHintsNeverImpl, kShuksan2Prefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCacheHintsAlwaysImpl, kShuksan2Prefix + 26)

DECLARE_PMID(kImplementationIDSpace, kSwatchesSyncProviderImpl, kShuksan2Prefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSwatchesSyncServiceImpl, kShuksan2Prefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDefaultAttributeObserverImpl, kShuksan2Prefix + 29)

DECLARE_PMID(kImplementationIDSpace, kContentMgrDebugMenuComponentImpl, kShuksan2Prefix + 30)
DECLARE_PMID(kImplementationIDSpace, kAliasConversionProviderImpl, kShuksan2Prefix + 31)

DECLARE_PMID(kImplementationIDSpace, kContentIteratorRegisterServiceImpl, kShuksan2Prefix + 32)
DECLARE_PMID(kImplementationIDSpace, kContentIteratorRegistryImpl, kShuksan2Prefix + 33)

DECLARE_PMID(kImplementationIDSpace, kSelectionHighlighterASBImpl, kShuksan2Prefix + 34)
// gap - kLayoutSelectionHighlighterImpl moved to GenericPageItem
DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesSuiteDefCSBSelectionExtImpl, kShuksan2Prefix + 36)
// gap - kNetworkImpl unused and deleted in CS5
DECLARE_PMID(kImplementationIDSpace, kStyleSyncProviderImpl, kShuksan2Prefix + 38)
DECLARE_PMID(kImplementationIDSpace, kStyleSyncServiceImpl, kShuksan2Prefix + 39)
//gap - kLayoutSelectionSuiteImpl

DECLARE_PMID(kImplementationIDSpace, kSelectionSnapshotSuiteASBImpl, kShuksan2Prefix + 41)
DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesSuiteASBImpl, kShuksan2Prefix + 42)
DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesSuiteDefCSBImpl, kShuksan2Prefix + 43)

DECLARE_PMID(kImplementationIDSpace, kArrangeSuiteASBImpl, kShuksan2Prefix + 44)

DECLARE_PMID(kImplementationIDSpace, kPageItemLockSuiteASBImpl, kShuksan2Prefix + 45)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSuiteASBImpl, kShuksan2Prefix + 46)
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteASBImpl, kShuksan2Prefix + 47)
DECLARE_PMID(kImplementationIDSpace, kPathOperationSuiteASBImpl, kShuksan2Prefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSelectionBoxHandleShapeSuiteASBImpl, kShuksan2Prefix + 49)
DECLARE_PMID(kImplementationIDSpace, kConvertShapeSuiteASBImpl, kShuksan2Prefix + 50)

DECLARE_PMID(kImplementationIDSpace, kRIDXStreamObserverImpl, kShuksan2Prefix + 51)
DECLARE_PMID(kImplementationIDSpace, kRIDXImpl, kShuksan2Prefix + 52)
DECLARE_PMID(kImplementationIDSpace, kRIDXInternalImpl, kShuksan2Prefix + 53)
DECLARE_PMID(kImplementationIDSpace, kRIDXStorageImpl, kShuksan2Prefix + 54)
DECLARE_PMID(kImplementationIDSpace, kRIDXPagedSetStorageImpl, kShuksan2Prefix + 55)
DECLARE_PMID(kImplementationIDSpace, kRIDXUnderlyingQueryImpl, kShuksan2Prefix + 56)
DECLARE_PMID(kImplementationIDSpace, kRIDXAccessImpl, kShuksan2Prefix + 57)
DECLARE_PMID(kImplementationIDSpace, kURIDataImpl, kShuksan2Prefix + 58)
DECLARE_PMID(kImplementationIDSpace, kCMainThreadStartupShutdownProviderImpl, kShuksan2Prefix + 59)
DECLARE_PMID(kImplementationIDSpace, kStockUtilsImpl, kShuksan2Prefix + 60)
DECLARE_PMID(kImplementationIDSpace, kLearnPanelUtilsImpl, kShuksan2Prefix + 61)

// gap 61 - 95 have never been used. Use these before extending the series.

DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteASBExtImpl, kShuksan2Prefix + 96)
DECLARE_PMID(kImplementationIDSpace, kScrapSuiteDefaultCSBImpl, kShuksan2Prefix + 97)
DECLARE_PMID(kImplementationIDSpace, kScrapSuiteASBImpl, kShuksan2Prefix + 98)
// gap - kLayoutHitTestSuiteImpl

DECLARE_PMID(kImplementationIDSpace, kSetDrawOptionsCmdImpl, kShuksan2Prefix + 100)
DECLARE_PMID(kImplementationIDSpace, kSetDrawOptionsCmdDataImpl, kShuksan2Prefix + 101)
DECLARE_PMID(kImplementationIDSpace, kDrawOptionsImpl, kShuksan2Prefix + 102)
DECLARE_PMID(kImplementationIDSpace, kDrawOptionsSetIDImpl, kShuksan2Prefix + 103)
DECLARE_PMID(kImplementationIDSpace, kAppIteratorRegImpl, kShuksan2Prefix + 104)

DECLARE_PMID(kImplementationIDSpace, kSelectionDataSuiteASBImpl, kShuksan2Prefix + 105)
DECLARE_PMID(kImplementationIDSpace, kContextMenuSuiteDefaultCSBImpl, kShuksan2Prefix + 106)
DECLARE_PMID(kImplementationIDSpace, kContextMenuSuiteASBImpl, kShuksan2Prefix + 107)
DECLARE_PMID(kImplementationIDSpace, kGeometrySuiteASBImpl, kShuksan2Prefix + 108)
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsDefaultCSBSelectionExtImpl, kShuksan2Prefix + 109)
DECLARE_PMID(kImplementationIDSpace, kTransformSuiteASBImpl, kShuksan2Prefix + 110)
DECLARE_PMID(kImplementationIDSpace, kAlignAndDistributeSuiteASBImpl, kShuksan2Prefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsDefaultCSBImpl, kShuksan2Prefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsASBImpl, kShuksan2Prefix + 113)

DECLARE_PMID(kImplementationIDSpace, kCreateOutlinesASBImpl, kShuksan2Prefix + 114)
DECLARE_PMID(kImplementationIDSpace, kToolChangeSuiteASBImpl, kShuksan2Prefix + 115)
DECLARE_PMID(kImplementationIDSpace, kZOrderSelectionSuiteASBImpl, kShuksan2Prefix + 116)
DECLARE_PMID(kImplementationIDSpace, kAutoSuiteRegisterImpl, kShuksan2Prefix + 117)
DECLARE_PMID(kImplementationIDSpace, kSuiteDataBaseImpl, kShuksan2Prefix + 118)
DECLARE_PMID(kImplementationIDSpace, kWarningWithDontShowDCImpl, kShuksan2Prefix + 119)
DECLARE_PMID(kImplementationIDSpace, kToolChangeSuiteDefaultCSBImpl, kShuksan2Prefix + 120 )
// obsolete DECLARE_PMID(kImplementationIDSpace, kPlugInRefCountShellImpl, kShuksan2Prefix + 121 )
DECLARE_PMID(kImplementationIDSpace, kPublicIteratorRegImpl, kShuksan2Prefix + 122)
DECLARE_PMID(kImplementationIDSpace, kResponderServiceProviderImpl, kShuksan2Prefix + 123 )
DECLARE_PMID(kImplementationIDSpace, kToolBoxUtilsImpl, kShuksan2Prefix + 124 )
DECLARE_PMID(kImplementationIDSpace, kSelectionHighlighterASBSelectionExtImpl, kShuksan2Prefix + 125 )
//DECLARE_PMID(kImplementationIDSpace, kSurrogateRegistryImpl, kShuksan2Prefix + 126 )
//DECLARE_PMID(kImplementationIDSpace, kSurrogateImpl, kShuksan2Prefix + 127 )
DECLARE_PMID(kImplementationIDSpace, kObjectModelIteratorRegImpl, kShuksan2Prefix + 128 )
DECLARE_PMID(kImplementationIDSpace, kSelectionExtentionRegistryImpl, kShuksan2Prefix + 129 )
// obsolete DECLARE_PMID(kImplementationIDSpace, kStripPhase2ConverterImpl, kShuksan2Prefix + 130 )
DECLARE_PMID(kImplementationIDSpace, kRawXMLDumpStreamImpl, kShuksan2Prefix + 131 )
DECLARE_PMID(kImplementationIDSpace, kMemStreamWriteImpl, kShuksan2Prefix + 132)
DECLARE_PMID(kImplementationIDSpace, kMemStreamReadImpl, kShuksan2Prefix + 133)
DECLARE_PMID(kImplementationIDSpace, kStepAndRepeatSuiteASBImpl, kShuksan2Prefix + 134 )
DECLARE_PMID(kImplementationIDSpace, kGuideDataSuiteASBImpl, kShuksan2Prefix + 135 )
DECLARE_PMID(kImplementationIDSpace, kGroupItemSuiteASBImpl, kShuksan2Prefix + 136 )
DECLARE_PMID(kImplementationIDSpace, kDragDropSourceSuiteASBImpl, kShuksan2Prefix + 137 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 138 )
DECLARE_PMID(kImplementationIDSpace, kDocumentLayoutSuiteASBImpl, kShuksan2Prefix + 139 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 140 )
DECLARE_PMID(kImplementationIDSpace, kFalseInitPersistBoolDataImpl, kShuksan2Prefix + 141 )
DECLARE_PMID(kImplementationIDSpace, kFootnoteOptionsDefaultCSBImpl, kShuksan2Prefix + 142)
DECLARE_PMID(kImplementationIDSpace, kFootnoteOptionsASBImpl, kShuksan2Prefix + 143)
DECLARE_PMID(kImplementationIDSpace, kFootnoteOptionsDefaultCSBSelectionExtImpl, kShuksan2Prefix + 144)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 145 )
DECLARE_PMID(kImplementationIDSpace, kSelectionExtentionInitializerImpl, kShuksan2Prefix + 146 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 147 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 148 )
DECLARE_PMID(kImplementationIDSpace, kTransformSuiteASBSelectionExtImpl, kShuksan2Prefix + 149 )
DECLARE_PMID(kImplementationIDSpace, kTextVariableASBImpl, kShuksan2Prefix + 150 )
DECLARE_PMID(kImplementationIDSpace, kTextVariableDefaultCSBImpl, kShuksan2Prefix + 151 )
DECLARE_PMID(kImplementationIDSpace, kTextVariableDefaultCSBSelectionExtImpl, kShuksan2Prefix + 152 )

DECLARE_PMID(kImplementationIDSpace, kIDThreadApplicationProxyImpl, kShuksan2Prefix + 153 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 154 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 155 )
DECLARE_PMID(kImplementationIDSpace, kPrivateSelectionAccessImpl, kShuksan2Prefix + 156 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 157 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 158 )
DECLARE_PMID(kImplementationIDSpace, kPublicCodeConversionImpl, kShuksan2Prefix + 159)
DECLARE_PMID(kImplementationIDSpace, kIDThreadSessionImpl, kShuksan2Prefix + 160 )
DECLARE_PMID(kImplementationIDSpace, kEnvironmentProxyImpl, kShuksan2Prefix + 161 )
DECLARE_PMID(kImplementationIDSpace, kObjectModelProxyImpl, kShuksan2Prefix + 162 )
DECLARE_PMID(kImplementationIDSpace, kCMTStartupShutdownProviderImpl, kShuksan2Prefix + 163 )
DECLARE_PMID(kImplementationIDSpace, kObjectExportOptionsSuiteASBImpl, kShuksan2Prefix + 164 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 165 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 166 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 167 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 168 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 169 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 170 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 171 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 172 )
DECLARE_PMID(kImplementationIDSpace, kTargetUtilsImpl, kShuksan2Prefix + 173 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 174 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 175 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 176 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 177 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 178 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 179 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 180 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 181 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 182 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 183 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 184 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 185 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 186 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 187 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 188 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 189 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 190 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 191 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 192 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 193 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 194 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 195 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 196 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 197 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 198 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 199 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 200 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 201 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 202 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 203 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 204 )
DECLARE_PMID(kImplementationIDSpace, kIdleTaskThreadImpl, kShuksan2Prefix + 205 )
DECLARE_PMID(kImplementationIDSpace, kMouseWatcherIdleTaskImpl, kShuksan2Prefix + 206 )
DECLARE_PMID(kImplementationIDSpace, kDataSysPointImpl, kShuksan2Prefix + 207 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 208 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 209 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 210 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 211 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 212 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 213 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 214 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 215 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 216 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 217 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 218 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 219 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 220 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 221 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 222 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 223 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 224 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 225 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 226 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 227 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 228 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 229 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 230 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 231 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 232 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 233 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 234 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 235 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 236 )
DECLARE_PMID(kImplementationIDSpace, kForegroundBackgroundEventWatcherImpl, kShuksan2Prefix + 237 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 238 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 239 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 240 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 241 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 242 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 243 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 244 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 245 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 246 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 247 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 248 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 249 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kShuksan2Prefix + 250 )
DECLARE_PMID(kImplementationIDSpace, kEndnoteOptionsASBImpl, kShuksan2Prefix + 251)
DECLARE_PMID(kImplementationIDSpace, kEndnoteOptionsDefaultCSBImpl, kShuksan2Prefix + 252)
DECLARE_PMID(kImplementationIDSpace, kEndnoteOptionsDefaultCSBSelectionExtImpl, kShuksan2Prefix + 253)
DECLARE_PMID(kImplementationIDSpace, kPersistInt64DataImpl, kShuksan2Prefix + 254)
DECLARE_PMID(kImplementationIDSpace, kTouchToolCollectorImpl, kShuksan2Prefix + 255)

// <Message ID>

DECLARE_PMID(kMessageIDSpace, kApplicationResumeMsg, kShuksanPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kApplicationSuspendMsg, kShuksanPrefix + 2)
//gap
DECLARE_PMID(kMessageIDSpace, kDocumentCloseAllMsg, kShuksanPrefix + 4)
DECLARE_PMID(kMessageIDSpace, kDocumentClosedMsg, kShuksanPrefix + 5)

// <Service ID>

// Service IDs
DECLARE_PMID(kServiceIDSpace, kErrorStringService, kShuksanPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kMousePositionService, kShuksanPrefix + 2)
// gap
DECLARE_PMID(kServiceIDSpace, kReferenceConverterService, kShuksanPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kAppLazyStartupShutdownService, kShuksanPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kStartupShutdownService, kShuksanPrefix + 7)
DECLARE_PMID(kServiceIDSpace, kShutdownNotificationService, kShuksanPrefix + 8)
DECLARE_PMID(kServiceIDSpace, kEasterEggService, kShuksanPrefix + 9)
DECLARE_PMID(kServiceIDSpace, kEncodingConverterService, kShuksanPrefix + 10)
DECLARE_PMID(kServiceIDSpace, kRenderingObjectSuiteService, kShuksanPrefix + 11)
DECLARE_PMID(kServiceIDSpace, kConversionService, kShuksanPrefix + 12)
DECLARE_PMID(kServiceIDSpace, kToolRegisterService, kShuksanPrefix + 13)
DECLARE_PMID(kServiceIDSpace, kTrackerRegisterService, kShuksanPrefix + 14)
DECLARE_PMID(kServiceIDSpace, kPanelRegisterService, kShuksanPrefix + 15)
//DECLARE_PMID(kServiceIDSpace, kUnusedService, kShuksanPrefix + 16)

DECLARE_PMID(kServiceIDSpace, kConversionHookService_obsolete, kShuksanPrefix + 17)
DECLARE_PMID(kServiceIDSpace, kSelectionService, kShuksanPrefix + 18)
DECLARE_PMID(kServiceIDSpace, kPaletteFactoryService, kShuksanPrefix + 19)
DECLARE_PMID(kServiceIDSpace, kKitRegisterService, kShuksanPrefix + 20)
DECLARE_PMID(kServiceIDSpace, kPhase2ConversionSignalResponderService, kShuksanPrefix + 21)
DECLARE_PMID(kServiceIDSpace, kContentIteratorRegisterService, kShuksanPrefix + 22)
DECLARE_PMID(kServiceIDSpace, kStyleSyncService, kShuksanPrefix + 23)
DECLARE_PMID(kServiceIDSpace, kISuiteRegisterService, kShuksanPrefix + 25)

DECLARE_PMID(kServiceIDSpace, kBeginXReferenceSessionRespService, kShuksanPrefix + 26)
DECLARE_PMID(kServiceIDSpace, kEndXReferenceSessionRespService, kShuksanPrefix + 27)

DECLARE_PMID(kServiceIDSpace, kAsyncWorkProcessorFactoryService, kShuksanPrefix + 28)
DECLARE_PMID(kServiceIDSpace, kBossRecyclerShutdownNotificationService, kShuksanPrefix + 29)
DECLARE_PMID(kServiceIDSpace, kTouchControlRegisterService, kShuksanPrefix + 30)

// <Error ID>
// Error Codes
// NOTE:  The offset is used to find the corresponding error string
// Look in ApplStrings.fr resource UserErrorTable( kApplErrorStringTableRsrcID ) for the string definitions.
DECLARE_PMID(kErrorIDSpace, kProgramError, kShuksanPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kDirectoryNotFoundError, kShuksanPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kMemoryFullError, kShuksanPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kFileNotFound, kShuksanPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kSharedLibraryNotFoundError, kShuksanPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kMemoryLowError, kShuksanPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kMemoryFailedError, kShuksanPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kResourceFileOpenError, kShuksanPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kPlugInConflictError, kShuksanPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kUnknownResponderError, kShuksanPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kResponderIsBusyError, kShuksanPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kTooManyOpenFilesError, kShuksanPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCouldntResolveAliasError, kShuksanPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kItemsDontFitError, kShuksanPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kMissingPluginPageItem, kShuksanPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kRevertScrapFailedError, kShuksanPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kMissingPluginOpenError, kShuksanPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kSchemaConversionError, kShuksanPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kCantCreateRecoverCmdError, kShuksanPrefix + 19)

// <Ignore>
//========================================================================================
// ----- Kit View IDs -----
//========================================================================================
DECLARE_PMID(kKitViewIDSpace, kSelectablePanelKitViewID, kShuksanPrefix + 1)
DECLARE_PMID(kKitViewIDSpace, kTablessFloaterKitViewID, kShuksanPrefix + 2)
DECLARE_PMID(kKitViewIDSpace, kHBarKitViewID, kShuksanPrefix + 3)
DECLARE_PMID(kKitViewIDSpace, kVBarKitViewID, kShuksanPrefix + 4)

// Interface font IDs

DECLARE_PMID(kUIFontIDSpace, kPaletteWindowFontId, kShuksanPrefix + 1)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowHiliteFontId, kShuksanPrefix + 2)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowFontId, kShuksanPrefix + 3)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowHiliteFontId, kShuksanPrefix + 4)
DECLARE_PMID(kUIFontIDSpace, kDocWindowFontId, kShuksanPrefix + 5)
DECLARE_PMID(kUIFontIDSpace, kDocWindowHiliteFontId, kShuksanPrefix + 6)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowSystemScriptFontId, kShuksanPrefix + 7)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowSystemScriptHiliteFontId, kShuksanPrefix + 8)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowSystemScriptFontId, kShuksanPrefix + 9)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowSystemScriptHiliteFontId, kShuksanPrefix + 10)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowFontForUseInDialogId, kShuksanPrefix + 11)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowItalicsFontId, kShuksanPrefix + 12)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowBoldItalicsFontId, kShuksanPrefix + 13)
DECLARE_PMID(kUIFontIDSpace, kTipsWindowFontId, kShuksanPrefix + 14)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowItalicsFontId, kShuksanPrefix + 15)
DECLARE_PMID(kUIFontIDSpace, kPoint20BoldWindowFontId, kShuksanPrefix + 16)
DECLARE_PMID(kUIFontIDSpace, kPoint14PlainWindowFontId, kShuksanPrefix + 17)
DECLARE_PMID(kUIFontIDSpace, kPoint20PlainWindowFontId, kShuksanPrefix + 18)
DECLARE_PMID(kUIFontIDSpace, kPoint12BoldWindowFontId, kShuksanPrefix + 19)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowSmallFontId, kShuksanPrefix + 20)
DECLARE_PMID(kUIFontIDSpace, kDialogWindowSmallHiliteFontId, kShuksanPrefix + 21)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowSmallFontId, kShuksanPrefix + 22)
DECLARE_PMID(kUIFontIDSpace, kPaletteWindowSmallHiliteFontId, kShuksanPrefix + 23)
DECLARE_PMID(kUIFontIDSpace, kPoint10PlainFontId, kShuksanPrefix + 24)
DECLARE_PMID(kUIFontIDSpace, kPoint19BoldFontId, kShuksanPrefix + 25)
// could add other SystemScriptFontIds here if we need them.


// <Global ID>
// ActionIDs

DECLARE_PMID(kActionIDSpace, kNewActionID, kShuksanPrefix + 1)
DECLARE_PMID(kActionIDSpace, kNewWindowActionID, kShuksanPrefix + 2)
DECLARE_PMID(kActionIDSpace, kOpenActionID, kShuksanPrefix + 3)
DECLARE_PMID(kActionIDSpace, kSaveActionID, kShuksanPrefix + 4)
DECLARE_PMID(kActionIDSpace, kSaveAsActionID, kShuksanPrefix + 5)
DECLARE_PMID(kActionIDSpace, kSaveACopyActionID, kShuksanPrefix + 6)
DECLARE_PMID(kActionIDSpace, kCloseActionID, kShuksanPrefix + 7)
DECLARE_PMID(kActionIDSpace, kRevertActionID, kShuksanPrefix + 8)
DECLARE_PMID(kActionIDSpace, kUndoActionID, kShuksanPrefix + 9)
DECLARE_PMID(kActionIDSpace, kRedoActionID, kShuksanPrefix + 10)
DECLARE_PMID(kActionIDSpace, kQuitActionID, kShuksanPrefix + 11)
DECLARE_PMID(kActionIDSpace, kAboutActionID, kShuksanPrefix + 12)
DECLARE_PMID(kActionIDSpace, kCutActionID, kShuksanPrefix + 13)
DECLARE_PMID(kActionIDSpace, kCopyActionID, kShuksanPrefix + 14)
DECLARE_PMID(kActionIDSpace, kPasteActionID, kShuksanPrefix + 15)
DECLARE_PMID(kActionIDSpace, kClearActionID, kShuksanPrefix + 16)
DECLARE_PMID(kActionIDSpace, kPowerPasteActionID, kShuksanPrefix + 17)
DECLARE_PMID(kActionIDSpace, kPasteInsideActionID, kShuksanPrefix + 18)
DECLARE_PMID(kActionIDSpace, kDuplicateActionID, kShuksanPrefix + 19)
DECLARE_PMID(kActionIDSpace, kSelectAllActionID, kShuksanPrefix + 20)
DECLARE_PMID(kActionIDSpace, kDeselectAllActionID, kShuksanPrefix + 22)
DECLARE_PMID(kActionIDSpace, kAlienDeleteActionID, kShuksanPrefix + 23)
DECLARE_PMID(kActionIDSpace, kNudgeUpActionID, kShuksanPrefix + 24)
DECLARE_PMID(kActionIDSpace, kNudgeDownActionID, kShuksanPrefix + 25)
DECLARE_PMID(kActionIDSpace, kNudgeLeftActionID, kShuksanPrefix + 26)
DECLARE_PMID(kActionIDSpace, kNudgeRightActionID, kShuksanPrefix + 27)
DECLARE_PMID(kActionIDSpace, kCascadeActionID, kShuksanPrefix + 28)
DECLARE_PMID(kActionIDSpace, kTileActionID, kShuksanPrefix + 29)
DECLARE_PMID(kActionIDSpace, kOpenWindowSeperatorActionID, kShuksanPrefix + 30)
DECLARE_PMID(kActionIDSpace, kSelectWindowDynamicActionID, kShuksanPrefix + 31)
DECLARE_PMID(kActionIDSpace, kDuplicateSepActionID, kShuksanPrefix + 32)
DECLARE_PMID(kActionIDSpace, kMinimizeWindowActionID, kShuksanPrefix + 33)
DECLARE_PMID(kActionIDSpace, kBringAllToFrontActionID, kShuksanPrefix + 34) // mac only
DECLARE_PMID(kActionIDSpace, kPasteInsideAtPointActionID, kShuksanPrefix + 35)
DECLARE_PMID(kActionIDSpace, kBrowseActionID, kShuksanPrefix + 36)
DECLARE_PMID(kActionIDSpace, kHideApplicationActionID, kShuksanPrefix + 37) // mac only
DECLARE_PMID(kActionIDSpace, kBrowseNewWindowActionID, kShuksanPrefix + 38)
//DECLARE_PMID(kActionIDSpace, kNewFromTemplateActionID, kShuksanPrefix + 39)
DECLARE_PMID(kActionIDSpace, kPasteUnformattedActionID, kShuksanPrefix + 40)
//DECLARE_PMID(kActionIDSpace, kTileHorizontalActionID, kShuksanPrefix + 41)
DECLARE_PMID(kActionIDSpace, kSearchAdobeStockActionID, kShuksanPrefix + 42)

//gap
DECLARE_PMID(kActionIDSpace, kForceRedrawActionID, kShuksanPrefix + 62)
DECLARE_PMID(kActionIDSpace, kNoDialogNewActionID, kShuksanPrefix + 63)
//gap
DECLARE_PMID(kActionIDSpace, kRestoreKeyboardTargetActionID, kShuksanPrefix + 68)
DECLARE_PMID(kActionIDSpace, kCloseAllActionID, kShuksanPrefix + 69)
DECLARE_PMID(kActionIDSpace, kSaveAllActionID, kShuksanPrefix + 70)
DECLARE_PMID(kActionIDSpace, kCloseDocActionID, kShuksanPrefix + 71)
DECLARE_PMID(kActionIDSpace, kOpenContextMenuActionID, kShuksanPrefix + 72)
DECLARE_PMID(kActionIDSpace, kNextDocActionID, kShuksanPrefix + 73)
DECLARE_PMID(kActionIDSpace, kPreviousDocActionID, kShuksanPrefix + 74)
//gap
DECLARE_PMID(kActionIDSpace, kFirstPanelSepActionID, kShuksanPrefix + 78)
// all those in between kFirstPanelSepActionID and kLastPanelSepActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastPanelSepActionID, kShuksanPrefix + 118)
//gap
DECLARE_PMID(kActionIDSpace, kFirstDocActionID, kShuksanPrefix + 130)
// all those in between kFirstDocActionID and kLastDocActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastDocActionID, kShuksanPrefix + 160)
DECLARE_PMID(kActionIDSpace, kEditSep1ActionID, kShuksanPrefix + 161)
DECLARE_PMID(kActionIDSpace, kEditSep2ActionID, kShuksanPrefix + 162)
DECLARE_PMID(kActionIDSpace, kEditSep3ActionID, kShuksanPrefix + 163)
DECLARE_PMID(kActionIDSpace, kNewWindowSepActionID, kShuksanPrefix + 164)
DECLARE_PMID(kActionIDSpace, kMinimizeSepActionID, kShuksanPrefix + 165)
DECLARE_PMID(kActionIDSpace, kFileSep1ActionID, kShuksanPrefix + 166)
DECLARE_PMID(kActionIDSpace, kFileSep2ActionID, kShuksanPrefix + 167)
DECLARE_PMID(kActionIDSpace, kRecentDocsDynamicActionID, kShuksanPrefix + 168)
DECLARE_PMID(kActionIDSpace, kNudgeUpSmallActionID, kShuksanPrefix + 169)
DECLARE_PMID(kActionIDSpace, kNudgeDownSmallActionID, kShuksanPrefix + 170)
DECLARE_PMID(kActionIDSpace, kNudgeLeftSmallActionID, kShuksanPrefix + 171)
DECLARE_PMID(kActionIDSpace, kNudgeRightSmallActionID, kShuksanPrefix + 172)
DECLARE_PMID(kActionIDSpace, kNudgeUpLargeActionID, kShuksanPrefix + 173)
DECLARE_PMID(kActionIDSpace, kNudgeDownLargeActionID, kShuksanPrefix + 174)
DECLARE_PMID(kActionIDSpace, kNudgeLeftLargeActionID, kShuksanPrefix + 175)
DECLARE_PMID(kActionIDSpace, kNudgeRightLargeActionID, kShuksanPrefix + 176)
DECLARE_PMID(kActionIDSpace, kFileSep3ActionID, kShuksanPrefix + 177)
DECLARE_PMID(kActionIDSpace, kTileSepActionID, kShuksanPrefix + 178)
//gap
DECLARE_PMID(kActionIDSpace, kInvalidateActionID, kShuksanPrefix + 180)
DECLARE_PMID(kActionIDSpace, kNoProtectionActionID, kShuksanPrefix + 181)
DECLARE_PMID(kActionIDSpace, kProtectedSaveActionID, kShuksanPrefix + 182)
DECLARE_PMID(kActionIDSpace, kProtectedMiniSaveActionID, kShuksanPrefix + 183)
DECLARE_PMID(kActionIDSpace, kInstantMiniSaveActionID, kShuksanPrefix + 184)
DECLARE_PMID(kActionIDSpace, k1SecondMiniSaveActionID, kShuksanPrefix + 185)
DECLARE_PMID(kActionIDSpace, k5SecondsMiniSaveActionID, kShuksanPrefix + 186)
DECLARE_PMID(kActionIDSpace, k20SecondsMiniSaveActionID, kShuksanPrefix + 187)
DECLARE_PMID(kActionIDSpace, k1MinuteMiniSaveActionID, kShuksanPrefix + 188)
DECLARE_PMID(kActionIDSpace, k5MinutesMiniSaveActionID, kShuksanPrefix + 189)
DECLARE_PMID(kActionIDSpace, k20MinutesMiniSaveActionID, kShuksanPrefix + 190)
DECLARE_PMID(kActionIDSpace, kRegularPasteSeqActionID, kShuksanPrefix + 191)
DECLARE_PMID(kActionIDSpace, kNestedPasteSeqActionID, kShuksanPrefix + 192)
DECLARE_PMID(kActionIDSpace, kAutoUndoPasteSeqActionID, kShuksanPrefix + 193)
DECLARE_PMID(kActionIDSpace, kFailPasteSeqActionID, kShuksanPrefix + 194)
//gap
DECLARE_PMID(kActionIDSpace, kNudgeUpDuplicateActionID, kShuksanPrefix + 201)
DECLARE_PMID(kActionIDSpace, kNudgeDownDuplicateActionID, kShuksanPrefix + 202)
DECLARE_PMID(kActionIDSpace, kNudgeLeftDuplicateActionID, kShuksanPrefix + 203)
DECLARE_PMID(kActionIDSpace, kNudgeRightDuplicateActionID, kShuksanPrefix + 204)
DECLARE_PMID(kActionIDSpace, kNudgeUpSmallDuplicateActionID, kShuksanPrefix + 205)
DECLARE_PMID(kActionIDSpace, kNudgeDownSmallDuplicateActionID, kShuksanPrefix + 206)
DECLARE_PMID(kActionIDSpace, kNudgeLeftSmallDuplicateActionID, kShuksanPrefix + 207)
DECLARE_PMID(kActionIDSpace, kNudgeRightSmallDuplicateActionID, kShuksanPrefix + 208)
DECLARE_PMID(kActionIDSpace, kNudgeUpLargeDuplicateActionID, kShuksanPrefix + 209)
DECLARE_PMID(kActionIDSpace, kNudgeDownLargeDuplicateActionID, kShuksanPrefix + 210)
DECLARE_PMID(kActionIDSpace, kNudgeLeftLargeDuplicateActionID, kShuksanPrefix + 211)
DECLARE_PMID(kActionIDSpace, kNudgeRightLargeDuplicateActionID, kShuksanPrefix + 212)
//gap
DECLARE_PMID(kActionIDSpace, kCustomizeKitActionID, kShuksanPrefix + 214)
DECLARE_PMID(kActionIDSpace, kCustomizeKitSepActionID, kShuksanPrefix + 215)
DECLARE_PMID(kActionIDSpace, kRunAllUnitTestActionID, kShuksanPrefix + 216)
DECLARE_PMID(kActionIDSpace, kUnitTestSepActionID, kShuksanPrefix + 217)
DECLARE_PMID(kActionIDSpace, kUnitTestDynamicActionID, kShuksanPrefix + 218)
DECLARE_PMID(kActionIDSpace, kSaveAllStoriesActionID, kShuksanPrefix + 219)
DECLARE_PMID(kActionIDSpace, kRevertStoryActionID, kShuksanPrefix + 220)
DECLARE_PMID(kActionIDSpace, kDumpContentMgrToFileActionID, kShuksanPrefix + 221)
DECLARE_PMID(kActionIDSpace, kInCopyNewButtonActionID, kShuksanPrefix + 222)
//gap

DECLARE_PMID(kActionIDSpace, kFirstUnitTestActionID, kShuksan2Prefix + 1)
// ids in here reserved
DECLARE_PMID(kActionIDSpace, kLastUnitTestActionID, kShuksan2Prefix + 50)

// DO NOT renumber the following two action ids, other KBSC for show/hide all palettes won't work!
DECLARE_PMID(kActionIDSpace, kShowHideAllPalettesActionID, kShuksan2Prefix + 55)
DECLARE_PMID(kActionIDSpace, kShowHideFloatingPalettesActionID, kShuksan2Prefix + 56)

DECLARE_PMID(kActionIDSpace, kFirstWindowActionID, kShuksan2Prefix + 165)
// all those in between kFirstWindowActionID and kLastWindowActionID are reserved....
DECLARE_PMID(kActionIDSpace, kLastWindowActionID, kShuksan2Prefix + 255)

// User Action Categories
DECLARE_PMID(kUserActionCategoryIDSpace, kSelectionCategory, kShuksanPrefix + 1)


// FileTypeInfoIDs

DECLARE_PMID(kFileTypeInfoIDSpace, kPublicationFileTypeInfoID, kShuksanPrefix + 1)
DECLARE_PMID(kFileTypeInfoIDSpace, kTemplateFileTypeInfoID, kShuksanPrefix + 2)
DECLARE_PMID(kFileTypeInfoIDSpace, kDefaultsFileTypeInfoID, kShuksanPrefix + 3)
DECLARE_PMID(kFileTypeInfoIDSpace, kDictionaryFileTypeInfoID, kShuksanPrefix + 4)
DECLARE_PMID(kFileTypeInfoIDSpace, kUserDictionaryFileTypeInfoID, kShuksanPrefix + 5)
DECLARE_PMID(kFileTypeInfoIDSpace, kKBSCFileTypeInfoID, kShuksanPrefix + 6)
DECLARE_PMID(kFileTypeInfoIDSpace, kBookFileTypeInfoID, kShuksanPrefix + 7)
DECLARE_PMID(kFileTypeInfoIDSpace, kLibraryFileTypeInfoID, kShuksanPrefix + 8)
DECLARE_PMID(kFileTypeInfoIDSpace, kPluginFileTypeInfoID, kShuksanPrefix + 9)
DECLARE_PMID(kFileTypeInfoIDSpace, kRequiredPluginFileTypeInfoID, kShuksanPrefix + 10)
DECLARE_PMID(kFileTypeInfoIDSpace, k3rdPartyPluginFileTypeInfoID, kShuksanPrefix + 11)
DECLARE_PMID(kFileTypeInfoIDSpace, kLockFileTypeInfoID, kShuksanPrefix + 12)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyFileTypeInfoID, kShuksanPrefix + 13)
DECLARE_PMID(kFileTypeInfoIDSpace, kRecoveryDataTypeInfoID, kShuksanPrefix + 14)
DECLARE_PMID(kFileTypeInfoIDSpace, kSavedDataTypeInfoID, kShuksanPrefix + 15)
DECLARE_PMID(kFileTypeInfoIDSpace, kPluginSetFileTypeInfoID, kShuksanPrefix + 16)
DECLARE_PMID(kFileTypeInfoIDSpace, kInDesignFileTypeInfoID, kShuksanPrefix + 17)
DECLARE_PMID(kFileTypeInfoIDSpace, kIDTemplateFileTypeInfoID, kShuksanPrefix + 18)
DECLARE_PMID(kFileTypeInfoIDSpace, kFlattenerStyleFileTypeInfoID, kShuksanPrefix + 19)
DECLARE_PMID(kFileTypeInfoIDSpace, kPDFStyleFileTypeInfoID, kShuksanPrefix + 20)
DECLARE_PMID(kFileTypeInfoIDSpace, kPrinterStyleFileTypeInfoID, kShuksanPrefix + 21)
DECLARE_PMID(kFileTypeInfoIDSpace, kXMLFileTypeInfoID, kShuksanPrefix + 22)

DECLARE_PMID(kFileTypeInfoIDSpace, kQuarkFileTypeInfoID, kShuksanPrefix + 23)
DECLARE_PMID(kFileTypeInfoIDSpace, kPhotoshopFileTypeInfoID, kShuksanPrefix + 24)
DECLARE_PMID(kFileTypeInfoIDSpace, kPDFFileTypeInfoID, kShuksanPrefix + 25)
DECLARE_PMID(kFileTypeInfoIDSpace, kJPEGFileTypeInfoID, kShuksanPrefix + 26)
DECLARE_PMID(kFileTypeInfoIDSpace, kPICTFileTypeInfoID, kShuksanPrefix + 27)
DECLARE_PMID(kFileTypeInfoIDSpace, kTIFFFileTypeInfoID, kShuksanPrefix + 28)
DECLARE_PMID(kFileTypeInfoIDSpace, kGIFFileTypeInfoID, kShuksanPrefix + 29)
DECLARE_PMID(kFileTypeInfoIDSpace, kEPSFFileTypeInfoID, kShuksanPrefix + 30)
DECLARE_PMID(kFileTypeInfoIDSpace, kHTMLFileTypeInfoID, kShuksanPrefix + 31)
DECLARE_PMID(kFileTypeInfoIDSpace, kSGMLFileTypeInfoID, kShuksanPrefix + 32)
DECLARE_PMID(kFileTypeInfoIDSpace, kCSVFileTypeInfoID, kShuksanPrefix + 33)
DECLARE_PMID(kFileTypeInfoIDSpace, kRTFFileTypeInfoID, kShuksanPrefix + 34)
DECLARE_PMID(kFileTypeInfoIDSpace, kTEXTFileTypeInfoID, kShuksanPrefix + 35)
DECLARE_PMID(kFileTypeInfoIDSpace, kTSVFileTypeInfoID, kShuksanPrefix + 36)
DECLARE_PMID(kFileTypeInfoIDSpace, kRichTextFileTypeInfoID, kShuksanPrefix + 37)
DECLARE_PMID(kFileTypeInfoIDSpace, kUnknownFileTypeInfoID, kShuksanPrefix + 38)
DECLARE_PMID(kFileTypeInfoIDSpace, kXMLInterchangeFileTypeInfoID, kShuksanPrefix + 39)
DECLARE_PMID(kFileTypeInfoIDSpace, kLineStyleFileTypeInfoID, kShuksanPrefix + 40)
DECLARE_PMID(kFileTypeInfoIDSpace, kDocumentStyleFileTypeInfoID, kShuksanPrefix + 41)
DECLARE_PMID(kFileTypeInfoIDSpace, kActionsFileTypeInfoID, kShuksanPrefix + 42)
DECLARE_PMID(kFileTypeInfoIDSpace, kAssignmentFileTypeInfoID, kShuksanPrefix + 43)
DECLARE_PMID(kFileTypeInfoIDSpace, kObjectStyleFileTypeInfoID, kShuksanPrefix + 44)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyXMLInterchangeFileTypeInfoID, kShuksanPrefix + 45)
DECLARE_PMID(kFileTypeInfoIDSpace, kJobOptionsFileTypeInfoID, kShuksanPrefix + 46)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyDocumentPresetFileTypeInfoID, kShuksanPrefix + 47)
DECLARE_PMID(kFileTypeInfoIDSpace, kAdobeColorBookExchangeFileTypeInfoID, kShuksanPrefix + 48)
DECLARE_PMID(kFileTypeInfoIDSpace, kGoLiveSectionFileTypeInfoID, kShuksanPrefix + 49)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyTemplateFileTypeInfoID, kShuksanPrefix + 50)
DECLARE_PMID(kFileTypeInfoIDSpace, kConnectionFileTypeInfoID, kShuksanPrefix + 51)
DECLARE_PMID(kFileTypeInfoIDSpace, kMSWordFileTypeInfoID, kShuksanPrefix + 52) //InCopy can direct open MS Word file as untitled
DECLARE_PMID(kFileTypeInfoIDSpace, kSnippetFileTypeInfoID, kShuksanPrefix + 53)
DECLARE_PMID(kFileTypeInfoIDSpace, kPFGFileTypeInfoID, kShuksanPrefix + 54)		// Package for GoLive's package.idpk
DECLARE_PMID(kFileTypeInfoIDSpace, kJBXResourceFileTypeInfoID, kShuksanPrefix + 55)
DECLARE_PMID(kFileTypeInfoIDSpace, kJBXContainerFileTypeInfoID, kShuksanPrefix + 56)
DECLARE_PMID(kFileTypeInfoIDSpace, kJBXManifestFileTypeInfoID, kShuksanPrefix + 57)
DECLARE_PMID(kFileTypeInfoIDSpace, kMenuSetFileTypeInfoID, kShuksanPrefix + 58)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyPackageFileTypeInfoID, kShuksanPrefix + 59)
DECLARE_PMID(kFileTypeInfoIDSpace, kInDesignPackageFileTypeInfoID, kShuksanPrefix + 60)
DECLARE_PMID(kFileTypeInfoIDSpace, kINXAltPackageFileTypeInfoID, kShuksanPrefix + 61)
DECLARE_PMID(kFileTypeInfoIDSpace, kInDesignPreflightProfileFileTypeInfoID, kShuksanPrefix + 62)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyXMLMarkupFileTypeInfoID, kShuksanPrefix + 63)
DECLARE_PMID(kFileTypeInfoIDSpace, kAssignmentMarkupFileTypeInfoID, kShuksanPrefix + 64)
DECLARE_PMID(kFileTypeInfoIDSpace, kInCopyPackageMarkupFileTypeInfoID, kShuksanPrefix + 65)
DECLARE_PMID(kFileTypeInfoIDSpace, kInDesignPackageMarkupFileTypeInfoID, kShuksanPrefix + 66)
DECLARE_PMID(kFileTypeInfoIDSpace, kMP3FileTypeInfoID, kShuksanPrefix + 67)
DECLARE_PMID(kFileTypeInfoIDSpace, kPNGFileTypeInfoID, kShuksanPrefix + 68)
DECLARE_PMID(kFileTypeInfoIDSpace, kSVGFileTypeInfoID, kShuksanPrefix + 69)

DECLARE_PMID(kLinkClientIDSpace, kIDLinkClientID, kShuksanPrefix + 1)

DECLARE_PMID(kProductIDSpace, kInDesignProduct, kShuksanPrefix + 1)
DECLARE_PMID(kProductIDSpace, kInCopyProduct, kShuksanPrefix + 2)
DECLARE_PMID(kProductIDSpace, kInDesignServerProduct, kShuksanPrefix + 3)

#endif //__ShuskanID__
