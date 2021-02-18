//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/FormFieldID.h $
//  
//  Owner: Mark VerMurlen
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

#ifndef __FormFieldID__
#define __FormFieldID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kFormFieldPrefix	 RezLong(0x14500)

// PluginID
#define kFormFieldPluginName			"FormField"
#define kFormFieldPluginID 				kFormFieldPrefix + 1

// Format Numbers

// Anna
#define kFormFieldAnnaRemoveImpls		kAnnaInitialMinorFormatNumber

// Add one of these for each product version.
#define kFormFieldLastAnnaMinorFormat	kFormFieldAnnaRemoveImpls

// Basil
#define kFormFieldButtonConversion		kBasilInitialMinorFormatNumber

// Rocket
#define kFormFieldStateNameConversion					kRocketInitialMinorFormatNumber + 0
#define kFormFieldSingleItemStateConversion				kRocketInitialMinorFormatNumber + 1
#define kFormFieldStateNameRemovalConversion			kRocketInitialMinorFormatNumber + 2
#define kFormFieldChangeObjectStyleImplConversion		kRocketInitialMinorFormatNumber + 3
#define kFormFieldRemoveMSOFromNamedItemListConversion	kRocketInitialMinorFormatNumber + 4
#define kFormFieldMoveMSOInitHiddenConversion			kRocketInitialMinorFormatNumber + 5
//#define kFormFieldStripMSOPrefsConversion				kRocketInitialMinorFormatNumber + 6

// Odin
#define kIORemoveSlideshowOptionsConversion				kOdinInitialMinorFormatNumber + 0

// Overall numbers.
#define	kFormFieldLatestMajorFormat		kOdinMajorFormatNumber
#define	kFormFieldLatestMinorFormat		kIORemoveSlideshowOptionsConversion

// ----- Service IDs -----

DECLARE_PMID(kServiceIDSpace, kFormFieldService,				kFormFieldPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kPDFAnnotationEventService,		kFormFieldPrefix + 2)

// ClassIDs (Boss IDs)
DECLARE_PMID(kClassIDSpace, kFormFieldLabelAdornmentBoss,	kFormFieldPrefix + 1)
DECLARE_PMID(kClassIDSpace, kFormFieldBoss,					kFormFieldPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kStyleLibraryMgrBoss,			kFormFieldPrefix + 3)
DECLARE_PMID(kClassIDSpace, kFormFieldIteratorRegBoss,		kFormFieldPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kFormFieldSuiteRegisterBoss,	kFormFieldPrefix + 5)

DECLARE_PMID(kClassIDSpace, kFormFieldNewStoryResponderBoss,kFormFieldPrefix + 6)
DECLARE_PMID(kClassIDSpace, kFormFieldPhase2ConversionBoss, kFormFieldPrefix + 7)
DECLARE_PMID(kClassIDSpace, kFormFieldConversionProviderBoss, 		kFormFieldPrefix + 8)
	
// Page items
DECLARE_PMID(kClassIDSpace, kFormFieldContentItemBoss,		kFormFieldPrefix + 9)
DECLARE_PMID(kClassIDSpace, kFormFieldItemBoss,				kFormFieldPrefix + 10)
DECLARE_PMID(kClassIDSpace, kAppearanceFormItemBoss,		kFormFieldPrefix + 11)
DECLARE_PMID(kClassIDSpace, kPushButtonItemBoss,			kFormFieldPrefix + 12)
DECLARE_PMID(kClassIDSpace, kCheckBoxItemBoss,				kFormFieldPrefix + 13)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kRadioButtonItemBoss,			kFormFieldPrefix + 14)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextFieldItemBoss,				kFormFieldPrefix + 15)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kListBoxFieldItemBoss,			kFormFieldPrefix + 16)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kComboBoxItemBoss,				kFormFieldPrefix + 17)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kSignatureFieldItemBoss,		kFormFieldPrefix + 18)		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kGenericFieldFactoryBoss,		kFormFieldPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPushButtonFactoryBoss,			kFormFieldPrefix + 20)
DECLARE_PMID(kClassIDSpace, kCheckBoxFactoryBoss,			kFormFieldPrefix + 21)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kRadioButtonFactoryBoss,		kFormFieldPrefix + 22)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextFieldFactoryBoss,			kFormFieldPrefix + 23)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kListBoxFactoryBoss,			kFormFieldPrefix + 24)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kComboBoxFactoryBoss,			kFormFieldPrefix + 25)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kSignatureFieldFactoryBoss,		kFormFieldPrefix + 26)		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kFormFieldNewDocResponderBoss,	kFormFieldPrefix + 27)
DECLARE_PMID(kClassIDSpace, kFormFieldOpenDocResponderBoss,	kFormFieldPrefix + 28)
DECLARE_PMID(kClassIDSpace, kFormFieldCloseDocResponderBoss,kFormFieldPrefix + 29)

		//Commands
DECLARE_PMID(kClassIDSpace, kCreateFormFieldCmdBoss,		kFormFieldPrefix + 30)
DECLARE_PMID(kClassIDSpace, kChangeActiveStateCmdBoss,		kFormFieldPrefix + 31)
DECLARE_PMID(kClassIDSpace, kNewStateCmdBoss,				kFormFieldPrefix + 32)
DECLARE_PMID(kClassIDSpace, kDeleteStateCmdBoss,			kFormFieldPrefix + 33)
DECLARE_PMID(kClassIDSpace, kSetAppearanceCmdBoss,			kFormFieldPrefix + 34)
DECLARE_PMID(kClassIDSpace, kCopyAppearancePageItemCmdBoss,	kFormFieldPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSetAppearanceStyleCmdBoss,		kFormFieldPrefix + 36)
DECLARE_PMID(kClassIDSpace, kChangeStateCmdBoss,			kFormFieldPrefix + 37)
DECLARE_PMID(kClassIDSpace, kDestroyFormFieldCmdBoss,		kFormFieldPrefix + 38)
DECLARE_PMID(kClassIDSpace, kGetUniqueNameCmdBoss,			kFormFieldPrefix + 39)
DECLARE_PMID(kClassIDSpace, kSetTabOrderCmdBoss,			kFormFieldPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSetCalculationOrderCmdBoss,	kFormFieldPrefix + 41)
DECLARE_PMID(kClassIDSpace, kRemoveAppearancesCmdBoss,		kFormFieldPrefix + 42)
DECLARE_PMID(kClassIDSpace, kDeleteAppearancePageItemCmdBoss, kFormFieldPrefix + 43)
DECLARE_PMID(kClassIDSpace, kAddToFieldOrderCmdBoss,		kFormFieldPrefix + 44)
DECLARE_PMID(kClassIDSpace, kRemoveFromFieldOrderCmdBoss,	kFormFieldPrefix + 45)
//gap
DECLARE_PMID(kClassIDSpace, kDeleteStateContentCmdBoss,		kFormFieldPrefix + 47)

		//Atributes
DECLARE_PMID(kClassIDSpace, kFormAttrBoss,					kFormFieldPrefix + 50) //base form attr type
DECLARE_PMID(kClassIDSpace, kFormTypeAttrBoss,				kFormFieldPrefix + 51)
DECLARE_PMID(kClassIDSpace, kFormNameAttrBoss,				kFormFieldPrefix + 52)
DECLARE_PMID(kClassIDSpace, kFormDescriptionAttrBoss,		kFormFieldPrefix + 53)
DECLARE_PMID(kClassIDSpace, kFormExportMappingAttrBoss,		kFormFieldPrefix + 54)
DECLARE_PMID(kClassIDSpace, kFormValueAttrBoss,				kFormFieldPrefix + 55)
DECLARE_PMID(kClassIDSpace, kFormDefaultValueAttrBoss,		kFormFieldPrefix + 56)
DECLARE_PMID(kClassIDSpace, kFormScreenVisibleAttrBoss,		kFormFieldPrefix + 57)
DECLARE_PMID(kClassIDSpace, kFormPrintVisibleAttrBoss,		kFormFieldPrefix + 58)
DECLARE_PMID(kClassIDSpace, kFormReadOnlyAttrBoss,			kFormFieldPrefix + 59)
DECLARE_PMID(kClassIDSpace, kFormExportAttrBoss,			kFormFieldPrefix + 60)
DECLARE_PMID(kClassIDSpace, kFormExportRequiredAttrBoss,	kFormFieldPrefix + 61)
DECLARE_PMID(kClassIDSpace, kFormStyleAttrBoss,				kFormFieldPrefix + 62) 
DECLARE_PMID(kClassIDSpace, kFormSpellCheckAttrBoss,		kFormFieldPrefix + 63) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontSizeAttrBoss,			kFormFieldPrefix + 64) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontUIDAttrBoss,			kFormFieldPrefix + 65) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontStyleAttrBoss,			kFormFieldPrefix + 66) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontColorAttrBoss,			kFormFieldPrefix + 67) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontTintAttrBoss,			kFormFieldPrefix + 68) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontOverprintAttrBoss,		kFormFieldPrefix + 69) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontStrokeColorAttrBoss,	kFormFieldPrefix + 70) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontStrokeTintAttrBoss,	kFormFieldPrefix + 71) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontStrokeWeightAttrBoss,	kFormFieldPrefix + 72) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFormFontStrokeOverprintAttrBoss,kFormFieldPrefix + 73) 	// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kCheckExportValueAttrBoss,		kFormFieldPrefix + 80) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kCheckDefaultCheckedAttrBoss,	kFormFieldPrefix + 81) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kTextMultilineAttrBoss,			kFormFieldPrefix + 82) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextScrollAttrBoss,			kFormFieldPrefix + 83) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextMaxLengthAttrBoss,			kFormFieldPrefix + 84) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextHasMaxLengthAttrBoss,		kFormFieldPrefix + 85) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextPasswordAttrBoss,			kFormFieldPrefix + 86) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextUseForFileSelAttrBoss,		kFormFieldPrefix + 87) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kTextAlignmentAttrBoss,			kFormFieldPrefix + 88) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kChoiceAllowMultiSelAttrBoss,	kFormFieldPrefix + 90) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kChoiceEditableAttrBoss,		kFormFieldPrefix + 91) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kChoiceSortAttrBoss,			kFormFieldPrefix + 92) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kChoiceListAttrBoss,			kFormFieldPrefix + 93) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kClassIDSpace, kFieldOrderHandlerBoss, kFormFieldPrefix + 94)
DECLARE_PMID(kClassIDSpace, kFormFontFamilyAttrBoss, kFormFieldPrefix + 95)
DECLARE_PMID(kClassIDSpace, kFormFontFaceStyleAttrBoss, kFormFieldPrefix + 96)



//scripting
DECLARE_PMID(kClassIDSpace, kFormFieldItemScriptProviderBoss,	kFormFieldPrefix + 200)
DECLARE_PMID(kClassIDSpace, kFieldChoiceScriptObjectBoss,		kFormFieldPrefix + 201) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFieldAppearanceScriptObjectBoss,	kFormFieldPrefix + 202)
DECLARE_PMID(kClassIDSpace, kFormFieldPropsScriptProviderBoss,	kFormFieldPrefix + 203)
DECLARE_PMID(kClassIDSpace, kFieldChoiceScriptProviderBoss,		kFormFieldPrefix + 204) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kFieldAppearanceScriptProviderBoss,	kFormFieldPrefix + 205)
// gap
DECLARE_PMID(kClassIDSpace, kTabOrderScriptObjectBoss, 			kFormFieldPrefix + 208)
DECLARE_PMID(kClassIDSpace, kTabOrderScriptProviderBoss, 		kFormFieldPrefix + 209)
DECLARE_PMID(kClassIDSpace, kCalculationOrderScriptObjectBoss, 	kFormFieldPrefix + 210) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kClassIDSpace, kCalculationOrderScriptProviderBoss, kFormFieldPrefix + 211) 		// Reserved for possible future implementation, do not use
// gap
DECLARE_PMID(kClassIDSpace, kButtonPrefsScriptProviderBoss,		kFormFieldPrefix + 215)

// MSO class ids
DECLARE_PMID(kClassIDSpace,	kMultiStateObjectItemBoss,			 	kFormFieldPrefix + 216)
DECLARE_PMID(kClassIDSpace,	kMultiStateObjectFactoryBoss,		 	kFormFieldPrefix + 217)
DECLARE_PMID(kClassIDSpace, kMoveStateCmdBoss,					 	kFormFieldPrefix + 218)
DECLARE_PMID(kClassIDSpace,	kAddItemsToAppearanceCmdBoss,		 	kFormFieldPrefix + 219)
DECLARE_PMID(kClassIDSpace,	kReleaseAppearanceAsObjectCmdBoss,	 	kFormFieldPrefix + 220)
DECLARE_PMID(kClassIDSpace,	kAddItemsAsStatesCmdBoss,			 	kFormFieldPrefix + 221)
DECLARE_PMID(kClassIDSpace,	kFormFieldCodeConversionProviderBoss,	kFormFieldPrefix + 222)

DECLARE_PMID(kClassIDSpace,	kFormFieldErrorStringServiceBoss,		kFormFieldPrefix + 224)
DECLARE_PMID(kClassIDSpace,	kFormMERTLEnabledAttrBoss,				kFormFieldPrefix + 225)
DECLARE_PMID(kClassIDSpace,	kModifyChoiceListCmdBoss,				kFormFieldPrefix + 226)

// IIDs (Interface IDs)

DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDSUITE,				kFormFieldPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPEARANCESUITE,				kFormFieldPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLELIBRARYMGR,				kFormFieldPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLELIBRARYOBSERVER,			kFormFieldPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDFACTORY,				kFormFieldPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDATTRIBUTE,			kFormFieldPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IFFCLOSEDOCOBSERVER,			kFormFieldPrefix + 7)

DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELD,						kFormFieldPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDPROPERTIES_DOCUMENT,	kFormFieldPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPEARANCEPROPERTIES_DOCUMENT,	kFormFieldPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGATTR,					kFormFieldPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHOICELISTATTR,				kFormFieldPrefix + 14) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPEARANCELIST,				kFormFieldPrefix + 15)

DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEFORMFIELDCMDDATA,		kFormFieldPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATEDATA,						kFormFieldPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWSTATEDATA,					kFormFieldPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPEARANCEDATA,				kFormFieldPrefix + 23)

DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDTEXTATTRIBUTES,		kFormFieldPrefix + 25)

DECLARE_PMID(kInterfaceIDSpace, IID_IPUSHBUTTONNUMBER,				kFormFieldPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHECKBOXNUMBER,				kFormFieldPrefix + 33)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_IRADIOBUTTONNUMBER,				kFormFieldPrefix + 34)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTFIELDNUMBER,				kFormFieldPrefix + 35)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXNUMBER,					kFormFieldPrefix + 36)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMBOBOXNUMBER,				kFormFieldPrefix + 37)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_ISIGNATURENUMBER,				kFormFieldPrefix + 38)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kInterfaceIDSpace, IID_IMISCFORMFIELDNUMBER,			kFormFieldPrefix + 39)		// Reserved for possible future implementation, do not use

DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADFIELDORDER,				kFormFieldPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTFIELDORDER,			kFormFieldPrefix + 42)

DECLARE_PMID(kInterfaceIDSpace, IID_ISETTABORDERCMDDATA,			kFormFieldPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETCALCULATIONORDERCMDDATA,	kFormFieldPrefix + 44)

DECLARE_PMID(kInterfaceIDSpace, IID_IGETUNIQUENAMECMDDATA,			kFormFieldPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFANNOTATION,					kFormFieldPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_FORMFIELDDOCOBSERVER,			kFormFieldPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDTEXTOBSERVER,			kFormFieldPrefix + 48)

DECLARE_PMID(kInterfaceIDSpace, IID_IPDFANNOTATIONHANDLER,			kFormFieldPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDUTILS,				kFormFieldPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLELIBUTILS,					kFormFieldPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTESUTILS,				kFormFieldPrefix + 52)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMFIELDLABELDRAWER,			kFormFieldPrefix + 54)
   
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPEARANCEITEMFACADE,			kFormFieldPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATELISTDATA,					kFormFieldPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_IMSOIDENTIFIER,					kFormFieldPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWSTATECMDDATA,				kFormFieldPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONIDENTIFIER,				kFormFieldPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCECS4BUTTONPLACEBEHAVIOR,	kFormFieldPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_IMULTISTATEOBJECTNUMBER,		kFormFieldPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IMULTISTATEOBJECTPREFS,			kFormFieldPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMSOPREFSCMDDATA,			kFormFieldPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IINVALIDFORMIDENTIFIER,			kFormFieldPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IFIXBUTTONACTIONS,				kFormFieldPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHOICELISTMODIFYCMDDATA,		kFormFieldPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTUTILDATA,					kFormFieldPrefix + 67)

// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kFormFieldPageItemImpl,		kFormFieldPrefix + 1) 
DECLARE_PMID(kImplementationIDSpace, kFormFieldLabelAdornmentImpl,	kFormFieldPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kStyleLibraryMgrImpl, 			kFormFieldPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kButtonToPolygonImpl, 			kFormFieldPrefix + 4)

DECLARE_PMID(kImplementationIDSpace, kStyleLibraryObserverImpl, 	kFormFieldPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kFormFieldIteratorRegImpl, 	kFormFieldPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kFormFieldProviderImpl,		kFormFieldPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFormFieldPhase2ConversionImpl,	kFormFieldPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kFormFieldImpl,				kFormFieldPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPushButtonImpl,				kFormFieldPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kRadioButtonImpl,				kFormFieldPrefix + 11)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kCheckBoxImpl,					kFormFieldPrefix + 12)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldImpl,				kFormFieldPrefix + 13)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kComboBoxImpl,					kFormFieldPrefix + 14)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxImpl,					kFormFieldPrefix + 15)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureFieldImpl,			kFormFieldPrefix + 16)		// Reserved for possible future implementation, do not use

DECLARE_PMID(kImplementationIDSpace, kFormFieldSuiteLayoutImpl,		kFormFieldPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kFormFieldSuiteLayoutSelExtImpl,kFormFieldPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kFormFieldSuiteDefaultImpl,	kFormFieldPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kFormFieldSuiteAbstractImpl,		kFormFieldPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kFormFieldSuiteASBSelExtImpl,		kFormFieldPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kAppearanceSuiteLayoutImpl,		kFormFieldPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kAppearanceSuiteLayoutSelExtImpl,	kFormFieldPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kAppearanceSuiteAbstractImpl,		kFormFieldPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kAppearanceSuiteASBSelExtImpl,		kFormFieldPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kFormFieldTextObserverImpl,		kFormFieldPrefix + 26)

DECLARE_PMID(kImplementationIDSpace, kFormFieldDocObserverImpl,		kFormFieldPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kFormFieldDocResponderImpl,	kFormFieldPrefix + 28)
// gap

DECLARE_PMID(kImplementationIDSpace, kFormAttrInfoImpl,				kFormFieldPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kStringAttrImpl,				kFormFieldPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kChoiceListAttrImpl,			kFormFieldPrefix + 32)

DECLARE_PMID(kImplementationIDSpace, kAppearanceListImpl,			kFormFieldPrefix + 33)

DECLARE_PMID(kImplementationIDSpace, kCreateFormFieldCmdDataImpl, 	kFormFieldPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kStateDataImpl, 				kFormFieldPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kAppearanceDataImpl, 			kFormFieldPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAppearancePageItemScrapImpl, 	kFormFieldPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kAppearanceHierarchyNodeImpl,	kFormFieldPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kAppearanceItemTransformImpl,	kFormFieldPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kPushButtonShapeImpl, 			kFormFieldPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kCheckBoxShapeImpl, 			kFormFieldPrefix + 41)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kRadioButtonShapeImpl, 		kFormFieldPrefix + 42)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldShapeImpl, 			kFormFieldPrefix + 43)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxShapeImpl, 			kFormFieldPrefix + 44)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kComboBoxShapeImpl, 			kFormFieldPrefix + 45)		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureFieldShapeImpl, 		kFormFieldPrefix + 46) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kImplementationIDSpace, kGenericFieldFactoryImpl, 		kFormFieldPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kPushButtonFactoryImpl, 		kFormFieldPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kCheckBoxFactoryImpl, 			kFormFieldPrefix + 51) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kRadioButtonFactoryImpl, 		kFormFieldPrefix + 52) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldFactoryImpl, 		kFormFieldPrefix + 53) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxFactoryImpl, 			kFormFieldPrefix + 54) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kComboBoxFactoryImpl, 			kFormFieldPrefix + 55) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureFieldFactoryImpl, 	kFormFieldPrefix + 56) 		// Reserved for possible future implementation, do not use

DECLARE_PMID(kImplementationIDSpace, kAppearanceObserverImpl,			kFormFieldPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPDFAnnotationEventProviderImpl,	kFormFieldPrefix + 58)
//gap
DECLARE_PMID(kImplementationIDSpace, kFieldOrderHandlerImpl, 			kFormFieldPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kFormFieldUtilsImpl, 				kFormFieldPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kAttributesUtilsImpl, 				kFormFieldPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kStyleLibUtilsImpl, 				kFormFieldPrefix + 63)

//commands
DECLARE_PMID(kImplementationIDSpace, kCopyAppearancePageItemCmdImpl,	kFormFieldPrefix + 80) 
DECLARE_PMID(kImplementationIDSpace, kDeleteAppearancePageItemCmdImpl,	kFormFieldPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCreateFormFieldCmdImpl,			kFormFieldPrefix + 82) 
DECLARE_PMID(kImplementationIDSpace, kChangeActiveStateCmdImpl,			kFormFieldPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kNewStateCmdImpl,					kFormFieldPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kDeleteStateCmdImpl,				kFormFieldPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kSetAppearanceCmdImpl,				kFormFieldPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kSetAppearanceStyleCmdImpl,		kFormFieldPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kAppearancePageItemGeometryImpl,	kFormFieldPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kChangeStateCmdImpl,				kFormFieldPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kGetUniqueNameCmdImpl,				kFormFieldPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kSetTabOrderCmdImpl,				kFormFieldPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kSetCalculationOrderCmdImpl,		kFormFieldPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kDestroyFormFieldCmdImpl,			kFormFieldPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kRemoveAppearancesCmdImpl,			kFormFieldPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kSetTabOrderCmdDataImpl,			kFormFieldPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kSetCalculationOrderCmdDataImpl,	kFormFieldPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kGetUniqueNameCmdDataImpl,			kFormFieldPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kAddToFieldOrderCmdImpl,			kFormFieldPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kRemoveFromFieldOrderCmdImpl,		kFormFieldPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kDeleteStateContentCmdImpl,		kFormFieldPrefix + 100) 
DECLARE_PMID(kImplementationIDSpace, kButtonPageItemNameImpl,		kFormFieldPrefix + 101) 
//GAP

//prefs
DECLARE_PMID(kImplementationIDSpace, kPushButtonNumberImpl,			kFormFieldPrefix + 116) 
DECLARE_PMID(kImplementationIDSpace, kCheckBoxNumberImpl,			kFormFieldPrefix + 117) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kRadioButtonNumberImpl, 		kFormFieldPrefix + 118) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kTextFieldNumberImpl, 			kFormFieldPrefix + 119) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kListBoxNumberImpl, 			kFormFieldPrefix + 120) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kComboBoxNumberImpl,			kFormFieldPrefix + 121) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kSignatureNumberImpl,			kFormFieldPrefix + 122) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kMiscFormFieldNumberImpl,		kFormFieldPrefix + 123) 		// Reserved for possible future implementation, do not use
// gap
DECLARE_PMID(kImplementationIDSpace, kSpreadFieldOrderImpl,			kFormFieldPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kDocumentFieldOrderImpl,		kFormFieldPrefix + 129)

//scripting
DECLARE_PMID(kImplementationIDSpace, kFormFieldItemScriptImpl,			kFormFieldPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kFormFieldItemScriptProviderImpl,	kFormFieldPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kFieldChoiceScriptProviderImpl,	kFormFieldPrefix + 132) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kFieldAppearanceScriptProviderImpl,kFormFieldPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kFieldChoiceProxyScriptImpl,		kFormFieldPrefix + 134) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kImplementationIDSpace, kFieldAppearanceProxyScriptImpl,	kFormFieldPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kButtonPrefsScriptProviderImpl,	kFormFieldPrefix + 136) 
DECLARE_PMID(kImplementationIDSpace, kFormFieldPropsScriptProviderImpl,	kFormFieldPrefix + 137)
// gap 
DECLARE_PMID(kImplementationIDSpace, kPDFAnnotationImpl,				kFormFieldPrefix + 145) 
//gap
DECLARE_PMID(kImplementationIDSpace, kTabOrderScriptProviderImpl,		kFormFieldPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kCalculationOrderScriptProviderImpl,	kFormFieldPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kFormFieldPasteBehaviorImpl,			kFormFieldPrefix + 150) 
DECLARE_PMID(kImplementationIDSpace, kAppearancePasteBehaviorImpl,			kFormFieldPrefix + 151) 
DECLARE_PMID(kImplementationIDSpace, kFormFieldPlaceBehaviorImpl,			kFormFieldPrefix + 152) 
DECLARE_PMID(kImplementationIDSpace, kAppearancePlaceBehaviorImpl,			kFormFieldPrefix + 153) 
//gap
DECLARE_PMID(kImplementationIDSpace, kAppearanceSwatchReferenceDataImpl,	kFormFieldPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kFormFieldGraphicsAttrInfoImpl,		kFormFieldPrefix + 156) 
//gap
DECLARE_PMID(kImplementationIDSpace, kFormFieldAttributeImpl,				kFormFieldPrefix + 200)
// MSO implementation ids
DECLARE_PMID(kImplementationIDSpace, kMultiStateObjectImpl,					kFormFieldPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kMultiStateObjectFactoryImpl,			kFormFieldPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kMoveStateCmdImpl,						kFormFieldPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kAddItemsToAppearanceCmdImpl,			kFormFieldPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kReleaseAppearanceAsObjectCmdImpl,		kFormFieldPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kAppearanceItemFacadeImpl,				kFormFieldPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kStateListDataImpl,					kFormFieldPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kAddItemsAsStatesCmdImpl,				kFormFieldPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kChangeStateNameCmdImpl,				kFormFieldPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kMSOIdentifierImpl,					kFormFieldPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kNewStateCmdDataImpl,					kFormFieldPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kButtonIdentifierImpl,					kFormFieldPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kAppearanceObjStyleDataImpl,			kFormFieldPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kFormFieldCodeConversionImpl,			kFormFieldPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kMultiStateObjectNumberImpl,			kFormFieldPrefix + 215) 
DECLARE_PMID(kImplementationIDSpace, kMultiStateObjectPrefsImpl,			kFormFieldPrefix + 216) 
DECLARE_PMID(kImplementationIDSpace, kMSOSlideshowOverlayDataImpl_Obsolete,	kFormFieldPrefix + 217) 

DECLARE_PMID(kImplementationIDSpace, kFormFieldErrorStringServiceImpl,		kFormFieldPrefix + 219) 
DECLARE_PMID(kImplementationIDSpace, kChoiceListModifyCmdImpl,				kFormFieldPrefix + 220) 
DECLARE_PMID(kImplementationIDSpace, kChoiceListModifyCmdDataImpl,			kFormFieldPrefix + 221) 
DECLARE_PMID(kImplementationIDSpace, kFontUtilDataImpl,						kFormFieldPrefix + 222)

// Error Ids

DECLARE_PMID(kErrorIDSpace, kAppearanceStateMissing, 					kFormFieldPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kUnableToAddToStateError,					kFormFieldPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kNoStatesAvailableError,					kFormFieldPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCustomStateNamesNotSupported,				kFormFieldPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kErrorSameNameDifferentFieldType,	  		kFormFieldPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kErrorInternalNameAsTerminalFieldName,		kFormFieldPrefix + 6)

//
//Script Element IDs
//

//Suite
DECLARE_PMID(kScriptInfoIDSpace, kInteractiveElementsSuiteScriptElement,		kFormFieldPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kFormFieldObjectScriptElement,					kFormFieldPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kPushButtonObjectScriptElement,				kFormFieldPrefix + 21)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kConvertButtonToObjectMethodScriptElement,		kFormFieldPrefix + 28) 		// Reserved for possible future implementation, do not use
DECLARE_PMID(kScriptInfoIDSpace, kAppearanceObjectScriptElement,				kFormFieldPrefix + 29)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kButtonPrefsObjectScriptElement,				kFormFieldPrefix + 40)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kApplyAppearanceStyleMethodScriptElement,		kFormFieldPrefix + 100)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kVisibleInPDFPropertyScriptElement,			kFormFieldPrefix + 166)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kAppearanceNamePropertyScriptElement,			kFormFieldPrefix + 171)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kActivePropertyScriptElement,					kFormFieldPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kAppearanceEnabledPropertyScriptElement,		kFormFieldPrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kStatePropertyScriptElement,					kFormFieldPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kTabOrderPropertyScriptElement,				kFormFieldPrefix + 201)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kButtonPrefsPropertyScriptElement,				kFormFieldPrefix + 220)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kAppearanceStateEnumScriptElement,				kFormFieldPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kVisibilityInPDFEnumScriptElement,				kFormFieldPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kMultiStateObjectScriptElement,				kFormFieldPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kReleaseAsObjectMethodScriptElement,			kFormFieldPrefix + 244)
DECLARE_PMID(kScriptInfoIDSpace, kReleaseAllStatesMethodScriptElement,			kFormFieldPrefix + 245)
DECLARE_PMID(kScriptInfoIDSpace, kMoveStateMethodScriptElement,					kFormFieldPrefix + 246)
DECLARE_PMID(kScriptInfoIDSpace, kResetAllMultiStateObjectsScriptElement,		kFormFieldPrefix + 247)
DECLARE_PMID(kScriptInfoIDSpace, kResetAllButtonsScriptElement,					kFormFieldPrefix + 248)
DECLARE_PMID(kScriptInfoIDSpace, kActiveStateIndexPropertyScriptElement,		kFormFieldPrefix + 249)
DECLARE_PMID(kScriptInfoIDSpace, kFormFieldPlaceMethodScriptElement,			kFormFieldPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kInitiallyHiddenPropertyScriptElement,			kFormFieldPrefix + 251)
DECLARE_PMID(kScriptInfoIDSpace, kAddItemsAsStateMethodScriptElement,			kFormFieldPrefix + 252)
DECLARE_PMID(kScriptInfoIDSpace, kAddItemsToStateMethodScriptElement,			kFormFieldPrefix + 253)

DECLARE_PMID(kScriptInfoIDSpace, kCheckBoxObjectScriptElement,				kFormFieldPrefix + 254)
DECLARE_PMID(kScriptInfoIDSpace, kComboBoxObjectScriptElement,				kFormFieldPrefix + 255)
DECLARE_PMID(kScriptInfoIDSpace, kListBoxObjectScriptElement,				kFormFieldPrefix + 256)
DECLARE_PMID(kScriptInfoIDSpace, kRadioButtonObjectScriptElement,			kFormFieldPrefix + 257)
DECLARE_PMID(kScriptInfoIDSpace, kTextFieldObjectScriptElement,				kFormFieldPrefix + 258)
DECLARE_PMID(kScriptInfoIDSpace, kSignatureFieldObjectScriptElement,		kFormFieldPrefix + 259)
DECLARE_PMID(kScriptInfoIDSpace, kReadOnlyScriptElement,					kFormFieldPrefix + 260)
DECLARE_PMID(kScriptInfoIDSpace, kRequiredScriptElement,					kFormFieldPrefix + 261)
DECLARE_PMID(kScriptInfoIDSpace, kCheckedByDefaultScriptElement,			kFormFieldPrefix + 262)
DECLARE_PMID(kScriptInfoIDSpace, kMultilineTextFieldScriptElement,			kFormFieldPrefix + 263)
DECLARE_PMID(kScriptInfoIDSpace, kPasswordTextFieldScriptElement,			kFormFieldPrefix + 264)
DECLARE_PMID(kScriptInfoIDSpace, kScrollableTextFieldScriptElement,			kFormFieldPrefix + 265)
DECLARE_PMID(kScriptInfoIDSpace, kFontSizeScriptElement,					kFormFieldPrefix + 266)
DECLARE_PMID(kScriptInfoIDSpace, kMultipleSelectionScriptElement,			kFormFieldPrefix + 267)
DECLARE_PMID(kScriptInfoIDSpace, kSortItemsScriptElement,					kFormFieldPrefix + 268)
DECLARE_PMID(kScriptInfoIDSpace, kChoiceListScriptElement,					kFormFieldPrefix + 269)
DECLARE_PMID(kScriptInfoIDSpace, kMERTLScriptElement,						kFormFieldPrefix + 270)
DECLARE_PMID(kScriptInfoIDSpace, kPrintableInPDFScriptElement,				kFormFieldPrefix + 271)
DECLARE_PMID(kScriptInfoIDSpace, kHiddenUntilTriggeredScriptElement,		kFormFieldPrefix + 272)
DECLARE_PMID(kScriptInfoIDSpace, kExportValueScriptElement,					kFormFieldPrefix + 273)
DECLARE_PMID(kScriptInfoIDSpace, kFontStyleScriptElement,					kFormFieldPrefix + 274)
DECLARE_PMID(kScriptInfoIDSpace, kFontFamilyScriptElement,					kFormFieldPrefix + 275)

//Widget IDs
DECLARE_PMID(kWidgetIDSpace, kDeletedMSOInfoAlertWidgetID, kFormFieldPrefix + 1)

#endif // __FormFieldID__
