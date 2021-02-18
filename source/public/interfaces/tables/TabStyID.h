//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/TabStyID.h $
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

#ifndef __TabStyID_h__
#define __TabStyID_h__

// Plug-in:
#define kTabStyPluginName	"TableStyles"			// Name of this plug-in.

#define kTabStyPrefixNumber_Obsolete	0xb1300 		
#define kTabStyPrefixNumber	0x20300 		// Unique prefix number for this plug-in.


// Plug-in Prefix: (please change kTabStyPrefixNumber above to modify the prefix.)
#define kTabStyPrefix_Obsolete		RezLong(kTabStyPrefixNumber_Obsolete)				
#define kTabStyPrefix		RezLong(kTabStyPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTabStyPluginID_Obsolete, kTabStyPrefix_Obsolete + 0)
DECLARE_PMID(kPlugInIDSpace, kTabStyPluginID, kTabStyPrefix + 0)

// ClassIDs:

DECLARE_PMID(kClassIDSpace, kTableStyleNewDocResponderBoss,					kTabStyPrefix + 1)
DECLARE_PMID(kClassIDSpace, kEditTableStyleCmdBoss,                         kTabStyPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDeleteTableStyleCmdBoss,                       kTabStyPrefix + 3)
DECLARE_PMID(kClassIDSpace, kClearTableOverridesCmdBoss,					kTabStyPrefix + 4)
DECLARE_PMID(kClassIDSpace, kApplyTableStyleCmdBoss,                        kTabStyPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTableStyleCellStylesRIDXNotifierHandlerBoss,	kTabStyPrefix + 6)
DECLARE_PMID(kClassIDSpace, kTabStyScriptProviderBoss,						kTabStyPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTabStyDocAppScriptProviderBoss,				kTabStyPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTabStyDocScriptProviderBoss,					kTabStyPrefix + 9)
DECLARE_PMID(kClassIDSpace, kLoadTableStyleCmdBoss,                         kTabStyPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTableStyleTableScriptProviderBoss,				kTabStyPrefix + 11)
// DECLARE_PMID(kClassIDSpace, kCreateNewTableStyleCmdBoss,					kTabStyPrefix + 12)
DECLARE_PMID(kClassIDSpace, kLoadTableStyleNotifierCmdBoss,					kTabStyPrefix + 13)
DECLARE_PMID(kClassIDSpace, kTableStyleErrorStringServiceBoss,				kTabStyPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCopyToTableStyleGroupCmdBoss,					kTabStyPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTableStylePhase2ConversionBoss,				kTabStyPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTableStyleConversionProviderBoss,				kTabStyPrefix + 17)
DECLARE_PMID(kClassIDSpace, kChangeTableGeomCmdBoss,						kTabStyPrefix + 18)
DECLARE_PMID(kClassIDSpace, kTabStyUpdateFormattingOptionCmdBoss,			kTabStyPrefix + 19)
DECLARE_PMID(kClassIDSpace, kTabStyUpdateStrokesCmdBoss,					kTabStyPrefix + 20)
DECLARE_PMID(kClassIDSpace, kDeleteTableStyleGroupCmdBoss,					kTabStyPrefix + 21)
DECLARE_PMID(kClassIDSpace, kTableStyleSyncBoss,							kTabStyPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCopyTableStyleCmdBoss,							kTabStyPrefix + 23)
DECLARE_PMID(kClassIDSpace, kRenameTableStyleCmdBoss,						kTabStyPrefix + 24)
DECLARE_PMID(kClassIDSpace, kCopyOneTableStyleCmdBoss,						kTabStyPrefix + 25)
DECLARE_PMID(kClassIDSpace, kDefaultTableStyleCmdBoss,						kTabStyPrefix + 26)
DECLARE_PMID(kClassIDSpace, kMoveTableStyleCmdBoss,                         kTabStyPrefix + 27)
DECLARE_PMID(kClassIDSpace, kMoveTableStyleGroupCmdBoss,					kTabStyPrefix + 28)
DECLARE_PMID(kClassIDSpace, kCopyOneTableOrCellStyleCmdBoss,				kTabStyPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTableStyleSchemaConversionProviderBoss,		kTabStyPrefix + 30)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESTYLESUITE,                       kTabStyPrefix + 0 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESTYLESFACADE,                     kTabStyPrefix + 1 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGETABLEGEOMETRYCMDDATA,			kTabStyPrefix + 2 )
DECLARE_PMID(kInterfaceIDSpace, IID_IREMOVECELLSTYLE,						kTabStyPrefix + 3 )
// Move to table model plugin
// DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATETABLESTYLEUTILS,				kTabStyPrefix + 4 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEATTRIBUTESFACADE,					kTabStyPrefix + 5 )


DECLARE_PMID(kInterfaceIDSpace, IID_ITABSTYXMLTAGTOSTYLEMAP_OBSOLETE,			kTabStyPrefix + 27 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITABSTYXMLSTYLETOTAGMAP_OBSOLETE,			kTabStyPrefix + 28 )

// ImplementationIDs:

DECLARE_PMID(kImplementationIDSpace, kTableStyleSuiteASBImpl,                       kTabStyPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kTableStyleSuiteTableCSBImpl,                  kTabStyPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kTableStyleNewDocResponderImpl,				kTabStyPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kTableStyleRIDXCellStylesNotifierHandlerImpl,	kTabStyPrefix + 3 )
//gap
DECLARE_PMID(kImplementationIDSpace, kTabStyUIDDataPersistImpl_Obsolete,			kTabStyPrefix + 5 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kDeleteTableStyleCmdImpl,                      kTabStyPrefix + 6 )
DECLARE_PMID(kImplementationIDSpace, kClearTableOverridesCmdImpl,					kTabStyPrefix + 7 )
DECLARE_PMID(kImplementationIDSpace, kTabStyScriptImpl,								kTabStyPrefix + 8 )
DECLARE_PMID(kImplementationIDSpace, kTabStyScriptProviderImpl,						kTabStyPrefix + 9 )
DECLARE_PMID(kImplementationIDSpace, kTabStyIntDataPersistImpl_Obsolete,			kTabStyPrefix + 10 )
DECLARE_PMID(kImplementationIDSpace, kApplyTableStyleCmdImpl,                       kTabStyPrefix + 11 )
DECLARE_PMID(kImplementationIDSpace, kTabStyAddTableStyleToNameTableCmdImpl,		kTabStyPrefix + 12 )
DECLARE_PMID(kImplementationIDSpace, kMoveTableStyleGroupCmdImpl,					kTabStyPrefix + 13 )

// Move to table model plugin
// DECLARE_PMID(kImplementationIDSpace, kCreateNewTableStyleCmdImpl,					kTabStyPrefix + 14 )
DECLARE_PMID(kImplementationIDSpace, kTableStyleErrorStringServiceImpl,				kTabStyPrefix + 15 )
DECLARE_PMID(kImplementationIDSpace, kCopyToTableStyleGroupCmdImpl,					kTabStyPrefix + 16 )
DECLARE_PMID(kImplementationIDSpace, kCopyOneTableOrCellStyleCmdImpl,				kTabStyPrefix + 17 )
DECLARE_PMID(kImplementationIDSpace, kTableStylesFacadeImpl,                        kTabStyPrefix + 18 )
DECLARE_PMID(kImplementationIDSpace, kTableStylePhase2ConversionImpl,				kTabStyPrefix + 19 )
DECLARE_PMID(kImplementationIDSpace, kChangeTableGeometryCmdDataImpl,				kTabStyPrefix + 20 )
DECLARE_PMID(kImplementationIDSpace, kChangeTableGeomCmdImpl,						kTabStyPrefix + 21 )
DECLARE_PMID(kImplementationIDSpace, kTabStyHeaderDataPersistImpl_Obsolete,			kTabStyPrefix + 22 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kTabStyFooterDataPersistImpl_Obsolete,			kTabStyPrefix + 23 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kLoadTableStyleCmdImpl,                        kTabStyPrefix + 24 )
DECLARE_PMID(kImplementationIDSpace, kLoadTableStyleNotifierCmdImpl,				kTabStyPrefix + 25 )
DECLARE_PMID(kImplementationIDSpace, kTableCellLoadStyleCmdInfoImpl,				kTabStyPrefix + 26 )
DECLARE_PMID(kImplementationIDSpace, kDeleteTableStyleGroupCmdImpl,                 kTabStyPrefix + 27 )
DECLARE_PMID(kImplementationIDSpace, kTableStyleTableScriptProviderImpl,			kTabStyPrefix + 29 )
DECLARE_PMID(kImplementationIDSpace, kTabStyDocScriptProviderImpl,					kTabStyPrefix + 30 )
DECLARE_PMID(kImplementationIDSpace, kMoveTableStyleCmdImpl,						kTabStyPrefix + 31 )
// Moved to table model plugin
// DECLARE_PMID(kImplementationIDSpace, kPrivateTableStyleUtilsImpl,					kTabStyPrefix + 32 )
DECLARE_PMID(kImplementationIDSpace, kTableAttributesFacadeImpl,					kTabStyPrefix + 33 )
DECLARE_PMID(kImplementationIDSpace, kTableStyleSuiteDefaultCSBImpl,				kTabStyPrefix + 34 )
// Moved to table model plugin
// DECLARE_PMID(kImplementationIDSpace, kBreakLinkWithTableStyleCmdImpl,				kTabStyPrefix + 35 )
//gap
DECLARE_PMID(kImplementationIDSpace, kTabStyXMLTagToStyleMapImpl_Obsolete,			kTabStyPrefix + 63 ) 
DECLARE_PMID(kImplementationIDSpace, kTabStyXMLStyleToTagMapImpl_Obsolete,			kTabStyPrefix + 68 ) 
//gap
DECLARE_PMID(kImplementationIDSpace, kTabStyPersistStringDataImpl_Obsolete,			kTabStyPrefix + 77 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kCopyTableStyleCmdImpl,						kTabStyPrefix + 78 )
DECLARE_PMID(kImplementationIDSpace, kRenameTableStyleCmdImpl,						kTabStyPrefix + 79 )
DECLARE_PMID(kImplementationIDSpace, kDefaultTableStyleCmdImpl,						kTabStyPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kTableStyleSyncServiceImpl,					kTabStyPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kTableStylesConversionProviderImpl,			kTabStyPrefix + 95)

// these need to use the obsolete prefix ID because they are converted and
// discarded in the phase 1 conversion provider, before the plug-in is renumbered
DECLARE_PMID(kImplementationIDSpace, kTabStyUIDDataPersistImplOld_Obsolete,				kTabStyPrefix_Obsolete + 5 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kTabStyHeaderDataPersistImplOld_Obsolete,			kTabStyPrefix_Obsolete + 22 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kTabStyFooterDataPersistImplOld_Obsolete,			kTabStyPrefix_Obsolete + 23 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kTabStyXMLTagToStyleMapImplOld_Obsolete,			kTabStyPrefix_Obsolete + 63 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kTabStyXMLStyleToTagMapImplOld_Obsolete,			kTabStyPrefix_Obsolete + 68 ) // Obsolete
DECLARE_PMID(kImplementationIDSpace, kTabStyPersistStringDataImplOld_Obsolete,			kTabStyPrefix_Obsolete + 77 ) // Obsolete

// We keep script IDs in the old prefix range for now as moving them to new range will require wide range changes
DECLARE_PMID(kScriptInfoIDSpace, kTabStyAddTableStyleMethodScriptElement,				kTabStyPrefix_Obsolete + 0)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyDeleteTableStyleMethodScriptElement,				kTabStyPrefix_Obsolete + 1)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyLoadTableStyleMethodScriptElement,				kTabStyPrefix_Obsolete + 2)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyApplyTableStyleToSelectionMethodScriptElement,	kTabStyPrefix_Obsolete + 3)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyCopyTableStyleMethodScriptElement,				kTabStyPrefix_Obsolete + 4)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyApplyTableStyleMethodScriptElement,				kTabStyPrefix_Obsolete + 5)
DECLARE_PMID(kScriptInfoIDSpace, kRedefineTableStyleMethodScriptElement,                 kTabStyPrefix_Obsolete + 6)
DECLARE_PMID(kScriptInfoIDSpace, kTableStyleSuiteScriptElement,                         kTabStyPrefix_Obsolete + 7)
DECLARE_PMID(kScriptInfoIDSpace, kTableStylePropScriptElement,							kTabStyPrefix_Obsolete + 9)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyHeaderRowsPropScriptElement,				kTabStyPrefix_Obsolete + 12)
DECLARE_PMID(kScriptInfoIDSpace, kTabStyFooterRowsPropScriptElement,				kTabStyPrefix_Obsolete + 13)
DECLARE_PMID(kScriptInfoIDSpace, kTableStyleSetObjectScriptElement,					kTabStyPrefix_Obsolete + 14)
DECLARE_PMID(kScriptInfoIDSpace, kAllTableStylesPropertyScriptElement,				kTabStyPrefix_Obsolete + 15)

DECLARE_PMID(kErrorIDSpace, kCouldNotAppendTableStylesErrorCode,			kTabStyPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kMissingTableStylePropertyErrorCode,			kTabStyPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCouldNotAppendNthTableStyleErrorCode,			kTabStyPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kCantGetTableStyleEventDataErrorCode,			kTabStyPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCantGetTableStyleErrorCode,					kTabStyPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kNoTablesErrorCode,								kTabStyPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCouldNotApplyTableStyleErrorCode,				kTabStyPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kCouldNotCopyTableStyleErrorCode,				kTabStyPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kNoTableSelectionErrorCode,						kTabStyPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kCouldNotCreateTableStyleErrorCode,				kTabStyPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetFileToLoadTableStylesErrorCode,		kTabStyPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kCouldNotLoadTableStylesErrorCode,				kTabStyPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetLoadTableStylesOptionErrorCode,		kTabStyPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kTabStyCouldNotDeleteTableStyleErrorCode,		kTabStyPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleErrorCode,				kTabStyPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kInvalidTableStyleRealValueErrorCode,			kTabStyPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleFootersBreakErrorCode,	kTabStyPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleHeadersBreakErrorCode,	kTabStyPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleStrokeOrderErrorCode,		kTabStyPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleStrokeErrorCode,			kTabStyPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleColorErrorCode,			kTabStyPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleBoolValErrorCode,			kTabStyPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleInt32ValErrorCode,		kTabStyPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleNameErrorCode,			kTabStyPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetParentTableStyleNameErrorCode,		kTabStyPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleHeaderRowsErrorCode,		kTabStyPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kCouldNotGetTableStyleFooterRowsErrorCode,		kTabStyPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCantGetRemoveTableOverridesParamErrorCode,		kTabStyPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kCantGetReplacementTableStyleErrorCode,			kTabStyPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kTableStyleHeaderRowsInvalidErrorCode,			kTabStyPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kTableStyleInvalidInt32ErrorCode,				kTabStyPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kTableStyleFooterRowsInvalidErrorCode,			kTabStyPrefix + 32)
DECLARE_PMID(kErrorIDSpace,	kTableStylePropertyNotDefinedErrorCode,			kTabStyPrefix + 33)
DECLARE_PMID(kErrorIDSpace,	kCantRedefineStyleErrorCode,					kTabStyPrefix + 34)

DECLARE_PMID(kServiceIDSpace,	kDeleteTableStyleRespService,					kTabStyPrefix + 0)

//GUIDs
#define kTabSty_CLSID				{0x80e2bf1d, 0xdb29, 0x4ccd, { 0xab, 0x4, 0x77, 0x7f, 0x68, 0x20, 0x49, 0xba }}
#define kTabStys_CLSID				{0x4ffa073, 0xaecb, 0x43a0, { 0x89, 0xbf, 0x42, 0x63, 0xde, 0x37, 0xa3, 0x9e }}
#define	kTableStyleGroups_CLSID		{0x8a87fd5a, 0xa7a7, 0x4267, { 0x87, 0x13, 0x9a, 0x11, 0xa3, 0xf7, 0x95, 0x5b }}
#define kTableStyleGroup_CLSID		{0xcb826153, 0x2600, 0x475e, { 0xb0, 0xee, 0x3, 0xd2, 0x69, 0x65, 0x5e, 0x75 }}


#endif // __TabStyID_h__

//  Code generated by DollyXS code generator
