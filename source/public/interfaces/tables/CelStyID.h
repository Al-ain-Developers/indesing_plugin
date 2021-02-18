//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/CelStyID.h $
//  
//  Owner: Danielle Darling
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

#ifndef __CelStyID_h__
#define __CelStyID_h__


// Plug-in:
#define kCelStyPluginName	"CellStyles"			// Name of this plug-in.

#define kCelStyPrefixNumber_Obsolete	0xb1400 		
#define kCelStyPrefixNumber	0x20200 		// Unique prefix number for this plug-in.

#define kCelStyPrefix_Obsolete		RezLong(kCelStyPrefixNumber_Obsolete)	
#define kCelStyPrefix		RezLong(kCelStyPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCelStyPluginID_Obsolete, kCelStyPrefix_Obsolete + 0)
DECLARE_PMID(kPlugInIDSpace, kCelStyPluginID, kCelStyPrefix + 0)

// ClassIDs:

DECLARE_PMID(kClassIDSpace, kCellStyleNewDocResponderBoss,					kCelStyPrefix + 1)
DECLARE_PMID(kClassIDSpace, kMoveCellStyleCmdBoss,                          kCelStyPrefix + 2)
DECLARE_PMID(kClassIDSpace, kMoveCellStyleGroupCmdBoss,                     kCelStyPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCopyToCellStyleGroupCmdBoss,                   kCelStyPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSetCellStyleAndPriorityCmdBoss,				kCelStyPrefix + 5)

DECLARE_PMID(kClassIDSpace, kCelStyScriptObjectBoss,						kCelStyPrefix + 24)
DECLARE_PMID(kClassIDSpace, kCellStyleScriptProviderBoss,					kCelStyPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCellStyleBoss,									kCelStyPrefix + 26)
DECLARE_PMID(kClassIDSpace, kCreateCellStyleCmdBoss,						kCelStyPrefix + 28)

// Three commands moved into table model plugin
// DECLARE_PMID(kClassIDSpace, kEditCellStyleCmdBoss,						kCelStyPrefix + 30)
// DECLARE_PMID(kClassIDSpace, kDeleteCellStyleCmdBoss,						kCelStyPrefix + 31)
// DECLARE_PMID(kClassIDSpace, kBreakLinkWithCellStyleCmdBoss,					kCelStyPrefix + 36)
DECLARE_PMID(kClassIDSpace, kCelStyDocAppScriptProviderBoss,				kCelStyPrefix + 38)
DECLARE_PMID(kClassIDSpace, kCelStyDocScriptProviderBoss,					kCelStyPrefix + 39)
//gap
DECLARE_PMID(kClassIDSpace, kApplyCellStyleCmdBoss,							kCelStyPrefix + 51)
// gap
DECLARE_PMID(kClassIDSpace, kCellStyleErrorStringServiceBoss,				kCelStyPrefix + 53)
DECLARE_PMID(kClassIDSpace, kCellStylePhase2ConversionBoss,					kCelStyPrefix + 54)
DECLARE_PMID(kClassIDSpace, kClearAllCellStyleOverridesCmdBoss,             kCelStyPrefix + 55)
DECLARE_PMID(kClassIDSpace, kCopyCellStyleCmdBoss,							kCelStyPrefix + 56)
DECLARE_PMID(kClassIDSpace, kRenameCellStyleCmdBoss,						kCelStyPrefix + 57)

DECLARE_PMID(kClassIDSpace, kCellStylesParaStylesRIDXNotifierHandlerBoss,	kCelStyPrefix + 59)
DECLARE_PMID(kClassIDSpace, kCellStyleConversionProviderBoss,				kCelStyPrefix + 61)
DECLARE_PMID(kClassIDSpace, kDefaultCellStyleCmdBoss,						kCelStyPrefix + 62)
DECLARE_PMID(kClassIDSpace, kDeleteCellStyleGroupCmdBoss,					kCelStyPrefix + 63)
DECLARE_PMID(kClassIDSpace, kCellStyleSyncBoss,								kCelStyPrefix + 64)
DECLARE_PMID(kClassIDSpace, kCellStyleGroupHierarchyBoss,					kCelStyPrefix + 65)
DECLARE_PMID(kClassIDSpace, kCellStyleGroupBoss,							kCelStyPrefix + 66)
DECLARE_PMID(kClassIDSpace, kCellStyleOpenDocResponderBoss,					kCelStyPrefix + 67)
DECLARE_PMID(kClassIDSpace, kCellStyleSchemaConversionProviderBoss,			kCelStyPrefix + 68)



// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLSTYLESUITE,					kCelStyPrefix + 0 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLSTYLEDATA_OBSOLETE,			kCelStyPrefix + 1 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLSTYLESFACADE,					kCelStyPrefix + 2 )
DECLARE_PMID(kInterfaceIDSpace, IID_IREMOVEALLCELLOVERRIDES,			kCelStyPrefix + 4 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLATTRIBUTESFACADE,				kCelStyPrefix + 5 )
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYCELLSTYLEPARASTYLE,			kCelStyPrefix + 6 )




// ImplementationIDs:

DECLARE_PMID(kImplementationIDSpace, kCellStyleSuiteASBImpl,						kCelStyPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleSuiteTableCSBImpl,					kCelStyPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleNewDocResponderImpl,					kCelStyPrefix + 3 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleScriptProviderImpl,					kCelStyPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kCelStyParentUIDDataPersistImpl_Obsolete,		kCelStyPrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kDeleteCellStyleGroupCmdImpl,					kCelStyPrefix + 6 )
DECLARE_PMID(kImplementationIDSpace, kMoveCellStyleCmdImpl,							kCelStyPrefix + 7 )
DECLARE_PMID(kImplementationIDSpace, kMoveCellStyleGroupCmdImpl,					kCelStyPrefix + 8 )
DECLARE_PMID(kImplementationIDSpace, kCellAttributesFacadeImpl,						kCelStyPrefix + 9 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleSuiteDefaultCSBImpl,					kCelStyPrefix + 10 )

// Moved to table model plugin
// DECLARE_PMID(kImplementationIDSpace, kBreakLinkWithCellStyleCmdImpl,				kCelStyPrefix + 11 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleCellAttributeListImpl,				kCelStyPrefix + 12 )
DECLARE_PMID(kImplementationIDSpace, kCopyToCellStyleGroupCmdImpl,					kCelStyPrefix + 13 )
DECLARE_PMID(kImplementationIDSpace, kSetCellStyleAndPriorityCmdImpl,				kCelStyPrefix + 14 )
// gap
DECLARE_PMID(kImplementationIDSpace, kApplyCellStyleCmdImpl,						kCelStyPrefix + 17 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleScriptImpl,							kCelStyPrefix + 18 )
//gap
DECLARE_PMID(kImplementationIDSpace, kCelStyRemoveParentStyleCmdImpl,				kCelStyPrefix + 23 )
//gap
DECLARE_PMID(kImplementationIDSpace, kCelStyCellsStyleNameTableImpl_Obsolete,		kCelStyPrefix + 28 )
//gap
DECLARE_PMID(kImplementationIDSpace, kCreateCellStyleCmdImpl,						kCelStyPrefix + 30 )
// gap

// Two commands moved into table model plugin
// DECLARE_PMID(kImplementationIDSpace, kEditCellStyleCmdImpl,						kCelStyPrefix + 34 )
// DECLARE_PMID(kImplementationIDSpace, kDeleteCellStyleCmdImpl,					kCelStyPrefix + 35 )
DECLARE_PMID(kImplementationIDSpace, kCelStyCellAttrModifierImpl,					kCelStyPrefix + 37 )
DECLARE_PMID(kImplementationIDSpace, kCelStyApplyCellAttrsCmdImpl,					kCelStyPrefix + 39 )

DECLARE_PMID(kImplementationIDSpace, kCellStyleErrorStringServiceImpl,				kCelStyPrefix + 59 )
// gap
DECLARE_PMID(kImplementationIDSpace, kCellStylesFacadeImpl,							kCelStyPrefix + 62 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleConversionProviderImpl,				kCelStyPrefix + 63 )
DECLARE_PMID(kImplementationIDSpace, kClearAllCellStyleOverridesCmdImpl,			kCelStyPrefix + 64 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleSyncServiceImpl,						kCelStyPrefix + 65 )

DECLARE_PMID(kImplementationIDSpace, kCellStyleRIDXParaStylesNotifierHandlerImpl,	kCelStyPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kCellStyleGroupManagerImpl,					kCelStyPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kDefaultCellStyleCmdImpl,						kCelStyPrefix + 75)

DECLARE_PMID(kImplementationIDSpace, kCellStyleHierarchyImpl,						kCelStyPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kCellRootStyleGroupHierarchyImpl,				kCelStyPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCellStylePhase2ConversionImpl,				kCelStyPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kRenameCellStyleCmdImpl,						kCelStyPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kCopyCellStyleCmdImpl,							kCelStyPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCellStyleOpenDocResponderImpl,				kCelStyPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kVerticalCellStyleCellAttributeListImpl,		kCelStyPrefix + 83)

// We keep script IDs in the old prefix range for now as moving them to new range will require wide range changes
DECLARE_PMID(kScriptInfoIDSpace, kCelStyAddCellStyleMethodScriptElement,					kCelStyPrefix_Obsolete + 0)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyDeleteCellStyleMethodScriptElement,				kCelStyPrefix_Obsolete + 1)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyLoadCellStyleMethodScriptElement,				kCelStyPrefix_Obsolete + 2)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyApplyCellStyleToSelectionMethodScriptElement,	kCelStyPrefix_Obsolete + 3)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyCopyCellStyleMethodScriptElement,				kCelStyPrefix_Obsolete + 4)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyApplyCellStyleMethodScriptElement,				kCelStyPrefix_Obsolete + 5)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyRedefineCellStyleMethodScriptElement,			kCelStyPrefix_Obsolete + 6)
DECLARE_PMID(kScriptInfoIDSpace, kCellStyleObjectScriptElement,							kCelStyPrefix_Obsolete + 7)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyPropertyScriptElement,							kCelStyPrefix_Obsolete + 8)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyCellStyleSuiteScriptElement,					kCelStyPrefix_Obsolete + 9)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyParagraphStylePropertyScriptElement,			kCelStyPrefix_Obsolete + 10)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyParentPropertyScriptElement,					kCelStyPrefix_Obsolete + 11)
DECLARE_PMID(kScriptInfoIDSpace, kCelStyReplaceOptionEnumScriptElement,					kCelStyPrefix_Obsolete + 12)
DECLARE_PMID(kScriptInfoIDSpace, kCellStylePropScriptElement,							kCelStyPrefix_Obsolete + 13)
DECLARE_PMID(kScriptInfoIDSpace, kCellStyleSetObjectScriptElement,						kCelStyPrefix_Obsolete + 14)
DECLARE_PMID(kScriptInfoIDSpace, kAllCellStylesPropertyScriptElement,					kCelStyPrefix_Obsolete + 15)
DECLARE_PMID(kScriptInfoIDSpace, kRootCellStyleGroupObjectScriptElement,				kCelStyPrefix_Obsolete + 16)
DECLARE_PMID(kScriptInfoIDSpace, kAddNothingEnumToCellStylePropsMetadataScriptElement,	kCelStyPrefix_Obsolete + 17)

DECLARE_PMID(kErrorIDSpace, kMissingCellStylePropertyErrorCode,					kCelStyPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kMissingWorkspaceErrorCode,							kCelStyPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCantGetNthCellStyleErrorCode,                      kCelStyPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCantRedefineCellStyleErrorCode,					kCelStyPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCantGetCellStyleEventDataErrorCode,                kCelStyPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCantGetStyleErrorCode,								kCelStyPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kCantCreateCellStyleBasedOnExistingErrorCode,		kCelStyPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kCantGetCellStyleNameErrorCode,						kCelStyPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kCouldntCreateCellStyleErrorCode,					kCelStyPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kCantGetFileToLoadCellStylesErrorCode,				kCelStyPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetLoadCellStylesOptionErrorCode,          kCelStyPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kCouldNotLoadCellStylesErrorCode,					kCelStyPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetCellStyleToApplyErrorCode,				kCelStyPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kNoCellSelectedErrorCode,							kCelStyPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kCouldNotApplyCellStyleErrorCode,					kCelStyPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetCellStyleToDeleteErrorCode,				kCelStyPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kCouldNotDeleteCellStyleErrorCode,					kCelStyPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetCellsToApplyToErrorCode,				kCelStyPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetNamedCellStyleErrorCode,				kCelStyPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kInvalidCellStyleRealNumberPropertyErrorCode,		kCelStyPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kCannotFindCellStyleColorErrorCode,                 kCelStyPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kCantGetCellStyleGradAttrErrorCode,                 kCelStyPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kCantGetCellStyleParentErrorCode,					kCelStyPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kCannotGetCellStyleVertJustErrorCode,				kCelStyPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kCannotGetCellStyleFirstBaselineErrorCode,			kCelStyPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kCannotGetCellStyleStrokeErrorCode,					kCelStyPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kCannotGetCellStyleBoolValErrorCode,				kCelStyPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCannotGetCellStyleInt32ValErrorCode,				kCelStyPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kCantGetReplacementCellStyleErrorCode,				kCelStyPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetRemoveCellOverridesParamErrorCode,		kCelStyPrefix + 30)
/*
DECLARE_PMID(kErrorIDSpace, kCellStyleInvalidRotationAngleErrorCode,            kCelStyPrefix + 31)
*/
DECLARE_PMID(kServiceIDSpace, kDeleteCellStyleRespService, kCelStyPrefix + 0)

// Obsolete IDs for persisted bosses and impls which we need to convert from old prefix range to new one
DECLARE_PMID(kClassIDSpace, kCellStyleBoss_Obsolete,									kCelStyPrefix_Obsolete + 26)
DECLARE_PMID(kClassIDSpace, kCellStyleGroupHierarchyBoss_Obsolete,					kCelStyPrefix_Obsolete + 65)

DECLARE_PMID(kImplementationIDSpace, kCellStyleCellAttributeListImpl_Obsolete,				kCelStyPrefix_Obsolete + 12 )
DECLARE_PMID(kImplementationIDSpace, kCelStyCellAttrModifierImpl_Obsolete,					kCelStyPrefix_Obsolete + 37 )
DECLARE_PMID(kImplementationIDSpace, kCellStyleGroupManagerImpl_Obsolete,					kCelStyPrefix_Obsolete + 74)
DECLARE_PMID(kImplementationIDSpace, kCellStyleHierarchyImpl_Obsolete,						kCelStyPrefix_Obsolete + 77)
DECLARE_PMID(kImplementationIDSpace, kCellRootStyleGroupHierarchyImpl_Obsolete,				kCelStyPrefix_Obsolete + 78)
DECLARE_PMID(kImplementationIDSpace, kVerticalCellStyleCellAttributeListImpl_Obsolete,		kCelStyPrefix_Obsolete + 83)
// the following IDs are stripped out of CS-2 docs in the phase 1
// conversion providers, and so need to keep the old prefix
DECLARE_PMID(kImplementationIDSpace, kCelStyParagrahStyleUIDPersistImpl_Obsolete,			kCelStyPrefix_Obsolete + 19 )
DECLARE_PMID(kImplementationIDSpace, kCelStyCellsStyleNameTableImplOld_Obsolete,				kCelStyPrefix_Obsolete + 28 )
DECLARE_PMID(kImplementationIDSpace, kCelStyCellAttributesPersistImpl_Obsolete,				kCelStyPrefix_Obsolete + 31 )
DECLARE_PMID(kImplementationIDSpace, kCelStyCellStyleInfoPersistImpl_Obsolete,				kCelStyPrefix_Obsolete + 32 )


//GUIDs
#define kCelSty_CLSID				{0x95d1fbcf, 0x3ecf, 0x4fe2, { 0xb1, 0x85, 0x57, 0xe3, 0xa9, 0xa3, 0x7a, 0x99 }}
#define kCelStys_CLSID				{0x6612dcbf, 0x9fe0, 0x4d5d, { 0xb9, 0x20, 0x58, 0xd7, 0x33, 0xaa, 0x95, 0x72 }}
#define kCellStyleGroup_CLSID		{0xd70909e8, 0xb5cd, 0x4901, { 0x82, 0xbd, 0xe0, 0x93, 0xef, 0x33, 0x73, 0x28 }}
#define kCellStyleGroups_CLSID		{0x91c566e3, 0x202f, 0x4f41, { 0x8f, 0x9c, 0x56, 0x5f, 0xb6, 0xac, 0x42, 0x25 }}
// {731E3B0D-3E49-44a2-87CE-227524AE8547}
#define kRootCellStyleGroup_CLSID		{ 0x731e3b0d, 0x3e49, 0x44a2, { 0x87, 0xce, 0x22, 0x75, 0x24, 0xae, 0x85, 0x47 } }

#endif // __CelStyID_h__

//  Code generated by DollyXS code generator
