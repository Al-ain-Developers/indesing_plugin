//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ColorSystemID.h $
//  
//  Owner: Jack Kirstein
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

#ifndef __ColorSystemID__
#define __ColorSystemID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "IconRsrcDefs.h"

#define kColorSystemPrefix RezLong(0x1F00)


//_________________________________________________________________________
// <Start IDC>
// <Class ID>
//_________________________________________________________________________
// bosses
DECLARE_PMID(kClassIDSpace, kColorDataBoss, kColorSystemPrefix + 1)
DECLARE_PMID(kClassIDSpace, kColorRefConverterBoss, kColorSystemPrefix + 2)
DECLARE_PMID(kClassIDSpace, kNewColorCmdBoss, kColorSystemPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDeleteColorCmdBoss, kColorSystemPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPMColorBoss, kColorSystemPrefix + 5)

// Gap
DECLARE_PMID(kClassIDSpace, kPMInkDataBoss, kColorSystemPrefix + 7)
DECLARE_PMID(kClassIDSpace, kAddInkCmdBoss, kColorSystemPrefix + 8)
DECLARE_PMID(kClassIDSpace, kDeleteInkCmdBoss, kColorSystemPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSwatchListChangedNotificationCmdBoss, kColorSystemPrefix + 10)

// GAP
DECLARE_PMID(kClassIDSpace, kInkRefConverterBoss, kColorSystemPrefix + 11)
DECLARE_PMID(kClassIDSpace, kNewUIColorCmdBoss, kColorSystemPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetUIColorCmdBoss, kColorSystemPrefix + 13)
DECLARE_PMID(kClassIDSpace, kChangeColorCmdBoss, kColorSystemPrefix + 14)

DECLARE_PMID(kClassIDSpace, kSwatchListNewScrapDocResponderBoss, kColorSystemPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSwatchListNewDocResponderBoss, kColorSystemPrefix + 16)
DECLARE_PMID(kClassIDSpace, kUIColorDataBoss, kColorSystemPrefix + 17)
DECLARE_PMID(kClassIDSpace, kUIColorRefConverterBoss, kColorSystemPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSwatchCommandBoss, kColorSystemPrefix + 19)

DECLARE_PMID(kClassIDSpace, kSolidRenderProviderBoss, kColorSystemPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSolidMetaDataBoss_Obsolete, kColorSystemPrefix + 21)

DECLARE_PMID(kClassIDSpace, kSwatchListNewWSResponderBoss, kColorSystemPrefix + 22)

DECLARE_PMID(kClassIDSpace, kDuplicateSwatchCmdBoss, kColorSystemPrefix + 23)
DECLARE_PMID(kClassIDSpace, kMoveSwatchCmdBoss, kColorSystemPrefix + 24)
DECLARE_PMID(kClassIDSpace, kK2RenderObjectBoss, kColorSystemPrefix + 25)
DECLARE_PMID(kClassIDSpace, kAddSwatchesCmdBoss, kColorSystemPrefix + 26)

// GAP
DECLARE_PMID(kClassIDSpace, kInkResourceDataBoss, kColorSystemPrefix + 29)
DECLARE_PMID(kClassIDSpace, kDeleteSwatchesCmdBoss, kColorSystemPrefix + 30)
DECLARE_PMID(kClassIDSpace, kNewNoneSwatchCmdBoss, kColorSystemPrefix + 31)
DECLARE_PMID(kClassIDSpace, kNoneRenderObjectProviderBoss, kColorSystemPrefix + 32)
DECLARE_PMID(kClassIDSpace, kNoneRefConverterBoss, kColorSystemPrefix + 33)
// GAP
DECLARE_PMID(kClassIDSpace, kSetOverprintBlackCmdBoss, kColorSystemPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSwatchListPhase2ConversionResponderBoss, kColorSystemPrefix + 36)
DECLARE_PMID(kClassIDSpace, kChangeInkCmdBoss, kColorSystemPrefix + 37)
//REMOVED-MJP: DECLARE_PMID(kClassIDSpace, kColorMapDrawEventHandlerBoss, kColorSystemPrefix + 38)
DECLARE_PMID(kClassIDSpace, kInkListPhase2ConversionResponderBoss, kColorSystemPrefix + 39)
DECLARE_PMID(kClassIDSpace, kUIColorListPhase2ConversionResponderBoss, kColorSystemPrefix + 40)

DECLARE_PMID(kClassIDSpace, kColorScriptProviderBoss, kColorSystemPrefix + 41)
DECLARE_PMID(kClassIDSpace, kSwatchScriptProviderBoss, kColorSystemPrefix + 42)
DECLARE_PMID(kClassIDSpace, kUnusedSwatchScriptProviderBoss, kColorSystemPrefix + 43)

DECLARE_PMID(kClassIDSpace, kNewMixedInkGroupCmdBoss, kColorSystemPrefix + 44)
DECLARE_PMID(kClassIDSpace, kChangeMixedInkGroupCmdBoss, kColorSystemPrefix + 45)
DECLARE_PMID(kClassIDSpace, kPrivateAddLockedColorUIDRefCmdBoss, kColorSystemPrefix + 47)
DECLARE_PMID(kClassIDSpace, kPrivateReleaseLockedColorUIDRefCmdBoss, kColorSystemPrefix + 48)
DECLARE_PMID(kClassIDSpace, kLockSwatchRefCountPhase2ConversionResponderBoss, kColorSystemPrefix + 49)

DECLARE_PMID(kClassIDSpace, kMixedInkScriptProviderBoss, kColorSystemPrefix + 50)
//DECLARE_PMID(kClassIDSpace, kMixedInkCompScriptProviderBoss, kColorSystemPrefix + 51)
//DECLARE_PMID(kClassIDSpace, kMixedInkCompScriptObjectBoss, kColorSystemPrefix + 52)

DECLARE_PMID(kClassIDSpace, kPrivateConvertMixedInkCmdBoss, kColorSystemPrefix + 53)

DECLARE_PMID(kClassIDSpace, kColorSwatchesRIDXNotifierHandlerBoss, kColorSystemPrefix + 54)
DECLARE_PMID(kClassIDSpace, kSwatchesRIDXNotificationDataBoss, kColorSystemPrefix + 55)
DECLARE_PMID(kClassIDSpace, kInksRIDXNotifierHandlerBoss, kColorSystemPrefix + 56)


DECLARE_PMID(kClassIDSpace, kColorGroupBoss, kColorSystemPrefix + 57)
DECLARE_PMID(kClassIDSpace, kAddColorGroupCmdBoss, kColorSystemPrefix + 58)
DECLARE_PMID(kClassIDSpace, kCreateColorGroupCmdBoss, kColorSystemPrefix + 59)
DECLARE_PMID(kClassIDSpace, kAddColorGroupMemberCmdBoss, kColorSystemPrefix + 60)
DECLARE_PMID(kClassIDSpace, kRemoveColorGroupMemberCmdBoss, kColorSystemPrefix + 61)
DECLARE_PMID(kClassIDSpace, kEditColorGroupOptionsCmdBoss, kColorSystemPrefix + 62) 
DECLARE_PMID(kClassIDSpace, kDeleteColorGroupsCmdBoss, kColorSystemPrefix + 63)
DECLARE_PMID(kClassIDSpace, kMoveColorGroupsCmdBoss, kColorSystemPrefix + 64)
DECLARE_PMID(kClassIDSpace, kDuplicateColorGroupCmdBoss, kColorSystemPrefix + 65)

DECLARE_PMID(kClassIDSpace, kColorGroupScriptProviderBoss, kColorSystemPrefix + 66)
DECLARE_PMID(kClassIDSpace, kColorGroupMemberScriptBoss, kColorSystemPrefix + 67)
//_________________________________________________________________________
// <Interface ID>
//_________________________________________________________________________
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORDATA, kColorSystemPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHLIST, kColorSystemPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IUICOLORLIST, kColorSystemPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IINKDATA, kColorSystemPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IINKLIST, kColorSystemPrefix + 5)

// GAP
DECLARE_PMID(kInterfaceIDSpace, IID_IPMINKBOSSDATA, kColorSystemPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IALTCOLORDATA, kColorSystemPrefix + 9)

// GAP
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORMETADATA, kColorSystemPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHUIDATA, kColorSystemPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVESWATCHUIDDATA, kColorSystemPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLOROVERRIDES, kColorSystemPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETSWATCHLIST, kColorSystemPrefix + 15)

DECLARE_PMID(kInterfaceIDSpace, IID_IDUPLICATESWATCHCMDDATA, kColorSystemPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IINKMETADATA, kColorSystemPrefix + 17)

// GAP
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTTOPROCESSDATA, kColorSystemPrefix + 22)  // an IBoolListData interface
DECLARE_PMID(kInterfaceIDSpace, IID_IINKRESOURCES, kColorSystemPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IINKRESOURCEDATA, kColorSystemPrefix + 24)

DECLARE_PMID(kInterfaceIDSpace, IID_IOVERPRINTBLACKPREFERENCE, kColorSystemPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IADORNMENTINKRESOURCES, kColorSystemPrefix + 26)

//Removed DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORMAPDRAWEVENTHNDL, kColorSystemPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNLOCKSWATCHDATA, kColorSystemPrefix + 28)  // an IBoolListData interface

DECLARE_PMID(kInterfaceIDSpace, IID_INEWMIXEDINKGROUPCMDDATA, kColorSystemPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IMIXEDINKGROUPOPTIONCMDDATA, kColorSystemPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATECOLORSPACECACHE, kColorSystemPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATECOLORUIDREFCOUNT, kColorSystemPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATESWATCHCOMMANDS, kColorSystemPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHFACADE, kColorSystemPrefix + 34)

DECLARE_PMID(kInterfaceIDSpace, IID_IRENDERINGOBJECTDRAWER, kColorSystemPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESRIDXNOTIFICATIONDATA, kColorSystemPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESRIDXNOTIFICATIONUPDATEHELPER, kColorSystemPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESRIDXNOTIFICATIONUPDATER, kColorSystemPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHREFERENCEDATA, kColorSystemPrefix + 39)

DECLARE_PMID(kInterfaceIDSpace, IID_ISUPPRESSCMSALERTFORCOLORS, kColorSystemPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCMDDATAFLAGS, kColorSystemPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IDVRENDERINGOBJECTDRAWER, kColorSystemPrefix + 42)

DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPNAME, kColorSystemPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPMEMBERLIST, kColorSystemPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPLIST, kColorSystemPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPFACADE, kColorSystemPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPUTILS, kColorSystemPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPUIDDATA, kColorSystemPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPREFERENCE, kColorSystemPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITCOLORGROUPOPTIONSCMDDATA, kColorSystemPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORGROUPUIDLISTDATA, kColorSystemPrefix + 51)

//_________________________________________________________________________
// <Implementation ID>
//_________________________________________________________________________
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kColorDataImpl, kColorSystemPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSwatchListImpl, kColorSystemPrefix + 2	)
DECLARE_PMID(kImplementationIDSpace, kAppSwatchListImpl, kColorSystemPrefix + 3	)
DECLARE_PMID(kImplementationIDSpace, kAppUIColorListImpl, kColorSystemPrefix + 4	)
DECLARE_PMID(kImplementationIDSpace, kUIColorListImpl, kColorSystemPrefix + 5	)
DECLARE_PMID(kImplementationIDSpace, kColorRefConverterImpl, kColorSystemPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kNewColorCmdImpl, kColorSystemPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kDeleteColorCmdImpl, kColorSystemPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPersistInkDataImpl, kColorSystemPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kAltColorDataImpl, kColorSystemPrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kColorValueServiceReference_OldImpl, kColorSystemPrefix + 11)	// Don't reuse id
DECLARE_PMID(kImplementationIDSpace, kInkListImpl, kColorSystemPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPMInkBossDataImpl, kColorSystemPrefix + 13)

DECLARE_PMID(kImplementationIDSpace, kColorRenderingObjectImpl, kColorSystemPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kAddInkCmdImpl, kColorSystemPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kDeleteInkCmdImpl, kColorSystemPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSwatchListChangedNotificationCmdImpl, kColorSystemPrefix + 19)

// GAP
DECLARE_PMID(kImplementationIDSpace, kInkRefConverterImpl, kColorSystemPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kNewUIColorCmdImpl, kColorSystemPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSetUIColorCmdImpl, kColorSystemPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kChangeColorCmdImpl, kColorSystemPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSwatchListNewDocResponderImpl, kColorSystemPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kUIColorRefConverterImpl, kColorSystemPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSwatchCommandImpl, kColorSystemPrefix + 28)

//DECLARE_PMID(kImplementationIDSpace, kSolidMetaConverterImpl_Obsolete, kColorSystemPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kSolidMetaRenderingObjectImpl_Obsolete, kColorSystemPrefix + 31)

DECLARE_PMID(kImplementationIDSpace, kSwatchListNewWSResponderImpl, kColorSystemPrefix + 32)

DECLARE_PMID(kImplementationIDSpace, kDuplicateSwatchCmdImpl, kColorSystemPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMoveSwatchCmdImpl, kColorSystemPrefix + 34)
//gap
//DECLARE_PMID(kImplementationIDSpace, kSolidMetaObjectAttrHelperImpl_Obsolete, kColorSystemPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kColorOverridesImpl, kColorSystemPrefix + 36)

DECLARE_PMID(kImplementationIDSpace, kTargetSwatchListImpl, kColorSystemPrefix + 38)

DECLARE_PMID(kImplementationIDSpace, kDuplicateSwatchCmdDataImpl, kColorSystemPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kAddSwatchesCmdImpl, kColorSystemPrefix + 40)

DECLARE_PMID(kImplementationIDSpace, kSwatchListNewScrapDocResponderImpl, kColorSystemPrefix + 41)

DECLARE_PMID(kImplementationIDSpace, kSwatchListConversionHookImpl, kColorSystemPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kInkResourceDataImpl, kColorSystemPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kColorInkResourcesImpl, kColorSystemPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kColorAttributePrePostImpl, kColorSystemPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kColorRenderObjAttrPrePostImpl, kColorSystemPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kDeleteSwatchesCmdImpl, kColorSystemPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kNoneRenderingObjectImpl, kColorSystemPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kNoneRenderObjRefConverterImpl, kColorSystemPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kNewNoneSwatchCmdImpl, kColorSystemPrefix + 50)
//DECLARE_PMID(kImplementationIDSpace, kNoneObjectMetaConverterImpl_Obsolete, kColorSystemPrefix + 51)

// Available

DECLARE_PMID(kImplementationIDSpace, kOverprintBlackPreferenceImpl, kColorSystemPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSetOverprintBlackCmdImpl, kColorSystemPrefix + 54)
//DECLARE_PMID(kImplementationIDSpace, kColorRenderingObjSuiteImpl, kColorSystemPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kColorSwatchReferenceDataImpl, kColorSystemPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSwatchListPhase2ConversionImpl, kColorSystemPrefix + 56)

DECLARE_PMID(kImplementationIDSpace, kChangeInkCmdImpl, kColorSystemPrefix + 57)

//Removed DECLARE_PMID(kImplementationIDSpace, kColorMapDrawEventHandlerImpl, kColorSystemPrefix + 58)
//Removed DECLARE_PMID(kImplementationIDSpace, kColorMapDrwEvtServiceImpl, kColorSystemPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kInkListPhase2ConversionImpl, kColorSystemPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kUIColorListPhase2ConversionImpl, kColorSystemPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kNoneRenderObjAttrPrePostImpl, kColorSystemPrefix + 62)

DECLARE_PMID(kImplementationIDSpace, kColorScriptProviderImpl, kColorSystemPrefix + 63)
//gap
DECLARE_PMID(kImplementationIDSpace, kSwatchScriptProviderImpl, kColorSystemPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kSwatchScriptImpl, kColorSystemPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kAGMColorSpaceCacheImpl, kColorSystemPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kUnusedSwatchScriptProviderImpl, kColorSystemPrefix + 68)

DECLARE_PMID(kImplementationIDSpace, kColorRenderObjectServiceImpl, kColorSystemPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kNoneRenderObjectServiceImpl, kColorSystemPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kColorRenderObjectUIImpl, kColorSystemPrefix + 71)

DECLARE_PMID(kImplementationIDSpace, kNewMixedInkGroupCmdImpl, kColorSystemPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kNewMixedInkGroupCmdDataImpl, kColorSystemPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kChangeMixedInkGroupCmdImpl, kColorSystemPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kMixedInkGroupOptionCmdDataImpl, kColorSystemPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kPrivateSwatchCommandsImpl, kColorSystemPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kPrivateAddLockedColorUIDRefCmdImpl, kColorSystemPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kPrivateReleaseLockedColorUIDRefCmdImpl, kColorSystemPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kLockSwatchRefCountPhase2ConverterImpl, kColorSystemPrefix + 79)

DECLARE_PMID(kImplementationIDSpace, kMixedInkScriptProviderImpl, kColorSystemPrefix + 80)
//DECLARE_PMID(kImplementationIDSpace, kMixedInkCompScriptProviderImpl, kColorSystemPrefix + 81)
//DECLARE_PMID(kImplementationIDSpace, kMixedInkCompScriptImpl, kColorSystemPrefix + 82)

DECLARE_PMID(kImplementationIDSpace, kPrivateConvertMixedInkCmdImpl, kColorSystemPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kInkDataImpl, kColorSystemPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kSwatchFacadeImpl, kColorSystemPrefix + 85)

DECLARE_PMID(kImplementationIDSpace, kRenderingObjectDrawerImpl, kColorSystemPrefix + 86)

DECLARE_PMID(kImplementationIDSpace, kColorSwatchesRIDXNotifierHandlerImpl, kColorSystemPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kSwatchesRIDXNotificationDataImpl, kColorSystemPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kSwatchesRIDXNotificationUpdateHelperImpl, kColorSystemPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kInksRIDXNotifierHandlerImpl, kColorSystemPrefix + 90)

DECLARE_PMID(kImplementationIDSpace, kColorCmdDataFlagsImpl, kColorSystemPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kColorCmdRenderDataImpl, kColorSystemPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kColorCmdUIDDataImpl, kColorSystemPrefix + 93)

DECLARE_PMID(kImplementationIDSpace, kColorGroupFacadeImpl, kColorSystemPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kColorGroupUtilsImpl, kColorSystemPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kColorGroupMemberListImpl,	kColorSystemPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kColorGroupListImpl, kColorSystemPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kAddColorGroupCmdImpl, kColorSystemPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kCreateColorGroupCmdImpl, kColorSystemPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kAddColorGroupMemberCmdImpl, kColorSystemPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kRemoveColorGroupMemberCmdImpl, kColorSystemPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kColorGroupReferenceImpl,	kColorSystemPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kEditColorGroupOptionsCmdImpl, kColorSystemPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kEditColorGroupOptionsCmdDataImpl, kColorSystemPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kDeleteColorGroupsCmdImpl, kColorSystemPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kMoveColorGroupsCmdImpl, kColorSystemPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kDuplicateColorGroupCmdImpl, kColorSystemPrefix + 107)
// gap

DECLARE_PMID(kImplementationIDSpace, kColorGroupScriptProviderImpl, kColorSystemPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kColorGroupScriptImpl, kColorSystemPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kColorGroupMemberScriptImpl, kColorSystemPrefix + 123)

//_________________________________________________________________________
//	<Error ID>
//_________________________________________________________________________
// Error Codes
// NOTE:  Internal errorcoes, no associated error strings.
DECLARE_PMID(kErrorIDSpace, kPrivateCantReplaceBaseColorWithTintError, kColorSystemPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kPrivateCantReplaceMixedInkGroupError, kColorSystemPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kPrivateCantReplaceTintSwatchError, kColorSystemPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kPrivateCantCreateSwatchError, kColorSystemPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kPrivateCantEditSwatchError, kColorSystemPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kPrivateLoadSwatchesFailedError, kColorSystemPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kPrivateChangeColorCmdError, kColorSystemPrefix + 7)

// NOTE:  public errorcoes.

//_________________________________________________________________________
//	<Script Element ID>
//_________________________________________________________________________
// Script Element IDs

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMixedInkObjectScriptElement,				kColorSystemPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kMixedInkGroupObjectScriptElement,			kColorSystemPrefix + 51)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateMixedInkMethodScriptElement,			kColorSystemPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kCreateMixedInkGroupMethodScriptElement,	kColorSystemPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kAddSwatchBookSpotColorMethodScriptElement,	kColorSystemPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kAddSwatchBookProcessColorMethodScriptElement,	kColorSystemPrefix + 103)
//DECLARE_PMID(kScriptInfoIDSpace, kAddSwatchBookSwatchMethodScriptElement,	kColorSystemPrefix + 104)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kInkArrayPropertyScriptElement,			kColorSystemPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kInkValuesPropertyScriptElement,			kColorSystemPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kInitialValuesPropertyScriptElement,		kColorSystemPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kRepeatValuesPropertyScriptElement,		kColorSystemPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kStepValuesPropertyScriptElement,			kColorSystemPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kInkNameArrayPropertyScriptElement,		kColorSystemPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kMixedInkSpotNameArrayPropertyScriptElement,	kColorSystemPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kMixedInkSpotColorArrayPropertyScriptElement,	kColorSystemPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kAliasSpotColorRefPropertyScriptElement,	kColorSystemPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kAlternateColorSpacePropertyScriptElement,	kColorSystemPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kAlternateColorValuePropertyScriptElement,	kColorSystemPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kCreatorIDPropertyScriptElement,			kColorSystemPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kSwatchColorGroupMemberPropertyScriptElement,	kColorSystemPrefix + 162)

//Enums

//_________________________________________________________________________
// <Service ID>
//_________________________________________________________________________
// Service IDs

// <Ignore>
// Default color space definition
// See GraphicTypes.h
// Default color value ranges for the following color spaces:
//		RGB:	[0, 1]
//		CMYK:	[0, 1]%
//		LAB:	[-128, 127]

//	Defines the creator ID for InDesign native swatches
#define	kInDesignNativeSwatchCreatorID	kColorSystemPrefix + 1


//_________________________________________________________________________
// Other useful global definitions
//_________________________________________________________________________
#define	kDefaultTintPercent				100.0					// Default tint percentage
#define	kInvalidTintPercent				-1.0					// Invalid tint percentage
#define kRgbIcon						kRGBIcon				// Resource ID of RGB icon
#define kCmykIcon						kCYMKIcon				// Resource ID of CMYK icon
#define kQuestionMarkIcon				kQuestionMarkBigIcon	// Resource ID of question mark icon
#define kRegistrationIcon				kRegistrationMarkIcon	// Resource ID of registration icon
#define kNoneSwatchIcon					kNoneIcon				// Resource ID of none swatch icon
#define kLabIcon						kLabColorIcon			// Resource ID of Lab swatch icon
#define kMixedInkIcon					kMixedInkIconID			// Resource ID of mixed ink swatch icon
#define kMixedInkParentIcon				kMixedInkParentIconID	// Resource ID of mixed ink parent swatch icon

// Special color swatch edit definition
#define	kCanNotEditColorName			0x00000001
#define	kCanNotEditColorMode			0x00000002	// Will remove this for Anna, the name is confusing
#define	kCanNotEditColorData			0x00000004
#define	kCanNotEditTintValue			0x00000008
#define	kCanNotEditColorType			kCanNotEditColorMode
#define	kCanNotEditColorSpace			0x00000010
#endif 
