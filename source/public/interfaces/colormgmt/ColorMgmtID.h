//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ColorMgmtID.h $
//  
//  Owner: fhaberma
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

#ifndef __ColorMgmtID__
#define __ColorMgmtID__

#if PRAGMA_ONCE
#pragma once
#endif

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kColorMgmtPrefix	 RezLong(0x7c00)		//Refer also to AdobePrefix.h

// PluginID
#define kColorMgmtPluginName 					"Color Management"
DECLARE_PMID(kPlugInIDSpace, kColorMgmtPluginID, kColorMgmtPrefix + 1)


//Rsrcs
#define kColorMgmtStringsRsrcID				1001
#define kColorMgmtStringsNoTransRsrcID		1501
#define kColorMgmtErrorStringTableRsrcID	2001

// <Class ID>
// ClassIDs (i.e. bosses)
DECLARE_PMID(kClassIDSpace, kCMSOnOffCmdBoss, kColorMgmtPrefix + 1)
DECLARE_PMID(kClassIDSpace, kCMMChoiceCmdBoss, kColorMgmtPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCMSUseProfileCmdBoss, kColorMgmtPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kCMSSetRenderingIntentCmdBoss, kColorMgmtPrefix + 5)
// gap was kCMSSoftProofSetCmdBoss kColorMgmtPrefix + 6
//DECLARE_PMID(kClassIDSpace, kColorXFormChangeBoss, kColorMgmtPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCMSDefaultObjectSettingsBoss, kColorMgmtPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCMSInitDefObjSettingsCmdBoss, kColorMgmtPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCMSUseEmbeddedProfileCmdBoss, kColorMgmtPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCMSNewDocActionBoss, kColorMgmtPrefix + 11)
DECLARE_PMID(kClassIDSpace, kCMSOpenDocActionBoss, kColorMgmtPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCMSHardProofSetCmdBoss_obsolete, kColorMgmtPrefix + 13)
DECLARE_PMID(kClassIDSpace, kCMSDICSetCmdBoss_obsolete, kColorMgmtPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCMSDownloadCRDSetCmdBoss_obsolete, kColorMgmtPrefix + 15)
//gap
DECLARE_PMID(kClassIDSpace, kCMSProfileRefConverterBoss, kColorMgmtPrefix + 17)
DECLARE_PMID(kClassIDSpace, kCMSCopySettingsCmdBoss, kColorMgmtPrefix + 18)
DECLARE_PMID(kClassIDSpace, kCMSStartupSignalMgrBoss, kColorMgmtPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCMSNewDocResponderBoss, kColorMgmtPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCMSConversionProviderBoss, kColorMgmtPrefix + 21)
DECLARE_PMID(kClassIDSpace, kColorMgmtTestMenuBoss, kColorMgmtPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCheckColorSettingsCmdBoss, kColorMgmtPrefix + 23)
DECLARE_PMID(kClassIDSpace, kCMSErrorStringServiceBoss, kColorMgmtPrefix + 24)
DECLARE_PMID(kClassIDSpace, kCMSSettingsScriptProviderBoss, kColorMgmtPrefix + 25)
DECLARE_PMID(kClassIDSpace, kDocumentCMSScriptProviderBoss, kColorMgmtPrefix + 26)
DECLARE_PMID(kClassIDSpace, kPageItemCMSScriptProviderBoss, kColorMgmtPrefix + 27)
DECLARE_PMID(kClassIDSpace, kWindowCMSScriptProviderBoss, kColorMgmtPrefix + 28)
//DECLARE_PMID(kClassIDSpace, kCMSSuiteRegisterBoss, kColorMgmtPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetEmbeddedProfileNameCmdBoss, kColorMgmtPrefix + 30)
DECLARE_PMID(kClassIDSpace, kAdobeSwatchbookBoss, kColorMgmtPrefix + 31)
DECLARE_PMID(kClassIDSpace, kAdobeSwatchbookServiceBoss, kColorMgmtPrefix + 32)
DECLARE_PMID(kClassIDSpace, kEPSBookServiceBoss, kColorMgmtPrefix + 33)
DECLARE_PMID(kClassIDSpace, kEPSSwatchbookBoss, kColorMgmtPrefix + 34)
DECLARE_PMID(kClassIDSpace, kPortConfigDrawEventHandlerBoss, kColorMgmtPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSetDLItemCMSSettingsCmdBoss, kColorMgmtPrefix + 36)
DECLARE_PMID(kClassIDSpace, kSetDocProfilePolicyCmdBoss, kColorMgmtPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSetBlackConversionPrefsCmdBoss, kColorMgmtPrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetSpotToProcessPrefsCmdBoss, kColorMgmtPrefix + 39)
DECLARE_PMID(kClassIDSpace, kCMSOpenDocResponderBoss, kColorMgmtPrefix + 40)
DECLARE_PMID(kClassIDSpace, kCheckCMSSeedChangeResponderBoss, kColorMgmtPrefix + 41)
DECLARE_PMID(kClassIDSpace, kSetSpotColorHandlingPrefsCmdBoss, kColorMgmtPrefix + 42)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSMANAGER, kColorMgmtPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSCMDDATA, kColorMgmtPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILE, kColorMgmtPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILELIST, kColorMgmtPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILEUID, kColorMgmtPrefix + 5)			//This is used as a IPersistUIDData
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILECATEGORY, kColorMgmtPrefix + 6)		//One of ICMSManager::profileCategory, but used as an IIntData in commands
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSSETTINGS, kColorMgmtPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCONVERTER, kColorMgmtPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORXFORMCHANGE, kColorMgmtPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPROFILEUID, kColorMgmtPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSDEFAULTOBJECTSETTINGSUID, kColorMgmtPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSITEMPROFILESOURCE, kColorMgmtPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSUSEPROFILECMDDATA, kColorMgmtPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPROFILEAUX, kColorMgmtPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSCOPYSETTINGSCMDDATA, kColorMgmtPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSDOCLISTOBSERVER, kColorMgmtPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPRESUMEOBSERVER, kColorMgmtPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSSETPROOFINGCMDDATA, kColorMgmtPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSUTILS, kColorMgmtPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSATTRIBUTESUITE, kColorMgmtPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORXFORMCHANGEOBSERVER, kColorMgmtPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMSPRIVUTILS, kColorMgmtPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORMGMTUTILS, kColorMgmtPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHBOOKMANAGER, kColorMgmtPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHBOOKCODEC, kColorMgmtPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHBOOK, kColorMgmtPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IADOBEBOOKDATA, kColorMgmtPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORBOOKUTILS, kColorMgmtPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IPORTCONFIGURATION, kColorMgmtPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IDISPLAYLISTITEMCMSSETTINGS, kColorMgmtPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IBLACKCONVERSIONPREFS, kColorMgmtPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTPROFILEPOLICIES, kColorMgmtPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETDLITEMCMSSETTINGSCMDDATA, kColorMgmtPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETDOCPROFILEPOLICYCMDDATA, kColorMgmtPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETBLACKCONVERSIONPREFSCMDDATA, kColorMgmtPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPOTTOPROCESSPREFS, kColorMgmtPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETSPOTTOPROCESSPREFSCMDDATA, kColorMgmtPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPIPELINEUTILS, kColorMgmtPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPOTCOLORHANDLINGPREFS, kColorMgmtPrefix + 40 )

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
DECLARE_PMID(kImplementationIDSpace, kCMSOnOffCmdImpl, kColorMgmtPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCMSCmdDataImpl, kColorMgmtPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCMMChoiceCmdImpl, kColorMgmtPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCMSProfileListImpl, kColorMgmtPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCMSUseProfileCmdImpl, kColorMgmtPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCMSProfileUIDRefImpl, kColorMgmtPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kImagePipelineUtilsImpl, kColorMgmtPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCMSSettingsImpl, kColorMgmtPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCMSSetRenderIntentCmdImpl, kColorMgmtPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCMSErrorStringServiceImpl, kColorMgmtPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kColorXFormChangeImpl, kColorMgmtPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kColorXFormChangeObserverImpl, kColorMgmtPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCMSInitDefObjSettingsCmdImpl, kColorMgmtPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kColorSpaceStartupShutdownImpl, kColorMgmtPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCMSItemProfileSourceImpl, kColorMgmtPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCMSUseProfileCmdDataImpl, kColorMgmtPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCMSNewDocActionImpl, kColorMgmtPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kCMSOpenDocActionImpl, kColorMgmtPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCMSHardProofSetCmd_obsolete, kColorMgmtPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCMSDICSetCmd_obsolete, kColorMgmtPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCMSDownloadCRDSetCmd_obsolete, kColorMgmtPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCheckCMSSeedChangeResponderImpl, kColorMgmtPrefix + 23)
//gap
DECLARE_PMID(kImplementationIDSpace, kCMSProfileRefConverterImpl, kColorMgmtPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCMSProfileAuxImpl, kColorMgmtPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kCMSCopySettingsCmdImpl, kColorMgmtPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCMSCopySettingsCmdDataImpl, kColorMgmtPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCMSStartupSignalRespServiceImpl, kColorMgmtPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCMSNewDocResponderImpl, kColorMgmtPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCMSDocListObserverImpl, kColorMgmtPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kColorMgmtTestMenuImpl, kColorMgmtPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAppResumeObserverImpl, kColorMgmtPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kCheckColorSettingsCmdImpl, kColorMgmtPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kCMSSetProofingCmdDataImpl, kColorMgmtPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kCMSUtilsImpl, kColorMgmtPrefix + 40)
//gap
DECLARE_PMID(kImplementationIDSpace, kCMSSettingsScriptProviderImpl, kColorMgmtPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kDocumentCMSScriptProviderImpl, kColorMgmtPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kPageItemCMSScriptProviderImpl, kColorMgmtPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kWindowCMSScriptProviderImpl, kColorMgmtPrefix + 45)

DECLARE_PMID(kImplementationIDSpace, kCMSAttributeSuiteASBImpl, kColorMgmtPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kCMSAttributeSuiteLayoutCSBImpl, kColorMgmtPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kCMSAttributeSuiteLayoutSelectionExtImpl, kColorMgmtPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kCMSPrivUtilsImpl, kColorMgmtPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSetEmbeddedProfileNameCmdImpl, kColorMgmtPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kColorMgmtUtilsImpl, kColorMgmtPrefix + 51)

DECLARE_PMID(kImplementationIDSpace, kCMSProofingPrefsImpl, kColorMgmtPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kCMSMonitorOnlyProofingImpl, kColorMgmtPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kSwatchbookManagerImpl, kColorMgmtPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kEPSBookCodecImpl, kColorMgmtPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kEPSBookProviderImpl, kColorMgmtPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kAdobeSwatchbookCodecImpl, kColorMgmtPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kAdobeSwatchbookProviderImpl, kColorMgmtPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kAdobeBookImpl, kColorMgmtPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kAdobeBookDataImpl, kColorMgmtPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kEPSSwatchbookImpl, kColorMgmtPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kColorBookUtilsImpl, kColorMgmtPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kPortConfigDrawEventHandlerImpl, kColorMgmtPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPortConfigDrwEvtServiceImpl, kColorMgmtPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPortConfigurationImpl, kColorMgmtPrefix + 65)

DECLARE_PMID(kImplementationIDSpace, kDisplayListItemCMSSettingsImpl, kColorMgmtPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kBlackConversionPrefsImpl, kColorMgmtPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kDocumentProfilePoliciesImpl, kColorMgmtPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kSetDLItemCMSSettingsCmdImpl, kColorMgmtPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kSetDLItemCMSSettingsCmdDataImpl, kColorMgmtPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kSetDocProfilePolicyCmdImpl, kColorMgmtPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kSetDocProfilePolicyCmdDataImpl, kColorMgmtPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kSetBlackConversionPrefsCmdImpl, kColorMgmtPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kSetBlackConversionPrefsCmdDataImpl, kColorMgmtPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kSpotToProcessPrefsImpl, kColorMgmtPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kSetSpotToProcessPrefsCmdImpl, kColorMgmtPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kSetSpotToProcessPrefsCmdDataImpl, kColorMgmtPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kColorXFormDocResponderImpl, kColorMgmtPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kSwatchbookManagerProxyImpl, kColorMgmtPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kSpotColorHandlingPrefsImpl, kColorMgmtPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kSetSpotColorHandlingPrefsCmdImpl, kColorMgmtPrefix + 81)

// <Service ID>
//	Service IDs
DECLARE_PMID(kServiceIDSpace, kCMSService, kColorMgmtPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kCMSStartupSignalRespService, kColorMgmtPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kSwatchbookCodecService, kColorMgmtPrefix + 3)

//_______________________________________________________________________________________
// <ViewPortAttr ID>
// ViewPortAttrIDs
//_______________________________________________________________________________________
DECLARE_PMID(kViewPortAttrIDSpace, kCMSProofingEnabled, kColorMgmtPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrPreserveNumbers, kColorMgmtPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrFastXForms, kColorMgmtPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrMaxDeviceNColorants, kColorMgmtPrefix + 4)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrPremultiplyAlpha, kColorMgmtPrefix + 5)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrDowngradeProfiles, kColorMgmtPrefix + 6)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrPreserveAllSpots, kColorMgmtPrefix + 7)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrPortRole, kColorMgmtPrefix + 8)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrPipelineStatus, kColorMgmtPrefix + 9)
DECLARE_PMID(kViewPortAttrIDSpace, kCMSProofingPaperWhite, kColorMgmtPrefix + 10)
DECLARE_PMID(kViewPortAttrIDSpace, kVPAttrPaperColorOverride, kColorMgmtPrefix + 11)

// values for kVPAttrPaperColorOverride
enum
{
	kPaperColorUseDefault = 0,
	kPaperColorForceWhite,
	kPaperColorForcePaperSwatch
};

// ErrorID
DECLARE_PMID(kErrorIDSpace, kNoEmbeddedProfileAvailableError,		kColorMgmtPrefix + 1)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kColorXFormInvalHandlerID, kColorMgmtPrefix + 1)
// anirudh, added a new InvalHandler for the color settings.
DECLARE_PMID(kInvalHandlerIDSpace, kColorSettingsInvalHandlerID, kColorMgmtPrefix + 2)

#endif // __ColorMgmtID__

// End, ColorMgmtID.h.

