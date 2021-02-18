//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ConditionalTextID.h $
//  
//  Owner: Michele Stutzman
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

#ifndef __ConditionalTextID__
#define __ConditionalTextID__

#pragma once

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kConditionalTextPrefix			RezLong(0x20700)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

//PlugInID
#define kConditionalTextPluginName		"ConditionalText"
DECLARE_PMID(kPlugInIDSpace,			kConditionalTextPluginID,				kConditionalTextPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kClassIDSpace,				kConditionTagBoss,						kConditionalTextPrefix + 1)
DECLARE_PMID(kClassIDSpace,				kConditionalTextErrorStringServiceBoss,	kConditionalTextPrefix + 2)
DECLARE_PMID(kClassIDSpace,				kConditionTagConverterBoss,				kConditionalTextPrefix + 3)
DECLARE_PMID(kClassIDSpace,				kHiddenTextBoss,						kConditionalTextPrefix + 4)
DECLARE_PMID(kClassIDSpace,				kHiddenTextMementoBoss,					kConditionalTextPrefix + 5)
DECLARE_PMID(kClassIDSpace,				kHiddenTextCreateCmdBoss,				kConditionalTextPrefix + 6)
DECLARE_PMID(kClassIDSpace,				kHiddenTextDeleteCmdBoss,				kConditionalTextPrefix + 7)
DECLARE_PMID(kClassIDSpace,				kHiddenTextAdornmentBoss,				kConditionalTextPrefix + 8)
DECLARE_PMID(kClassIDSpace,				kHiddenTextRestoreCmdBoss,				kConditionalTextPrefix + 9)
DECLARE_PMID(kClassIDSpace,				kConditionTagCreateCmdBoss,				kConditionalTextPrefix + 10)
DECLARE_PMID(kClassIDSpace,				kConditionTagDeleteCmdBoss,				kConditionalTextPrefix + 11)
DECLARE_PMID(kClassIDSpace,				kConditionTagEditNameCmdBoss,			kConditionalTextPrefix + 12)
DECLARE_PMID(kClassIDSpace,				kConditionTagEditVisibleStateCmdBoss,	kConditionalTextPrefix + 13)
DECLARE_PMID(kClassIDSpace,				kConditionTagEditColorCmdBoss,			kConditionalTextPrefix + 14)
DECLARE_PMID(kClassIDSpace,				kConditionTagApplyCmdBoss,				kConditionalTextPrefix + 15)
DECLARE_PMID(kClassIDSpace,				kShowConditionIndicatorsCmdBoss,		kConditionalTextPrefix + 16)
DECLARE_PMID(kClassIDSpace,				kConditionalTextOptionsScriptProviderBoss,kConditionalTextPrefix + 17)
DECLARE_PMID(kClassIDSpace,				kConditionTagUnapplyCmdBoss,			kConditionalTextPrefix + 18)
DECLARE_PMID(kClassIDSpace,				kConditionalTextHideHelperCmdBoss,		kConditionalTextPrefix + 19)
DECLARE_PMID(kClassIDSpace,				kConditionalTextAttributeBoss,			kConditionalTextPrefix + 20)
DECLARE_PMID(kClassIDSpace,				kConditionalTextAdornmentBoss,			kConditionalTextPrefix + 21)
DECLARE_PMID(kClassIDSpace,				kConditionalTextShowHelperCmdBoss,		kConditionalTextPrefix + 22)
DECLARE_PMID(kClassIDSpace,				kConditionTagEditMethodCmdBoss,			kConditionalTextPrefix + 23)
DECLARE_PMID(kClassIDSpace,				kConditionTagEditAppearanceCmdBoss,		kConditionalTextPrefix + 24)
DECLARE_PMID(kClassIDSpace,				kConditionTagEditOptionsCmdBoss,		kConditionalTextPrefix + 25)
DECLARE_PMID(kClassIDSpace,				kConditionalTextConversionProviderBoss,	kConditionalTextPrefix + 26)
DECLARE_PMID(kClassIDSpace,				kLoadConditionTagsCmdBoss,				kConditionalTextPrefix + 27)
DECLARE_PMID(kClassIDSpace,				kConditionalTextSyncBoss,				kConditionalTextPrefix + 28)
DECLARE_PMID(kClassIDSpace,				kConditionalTextPostProcessBoss,		kConditionalTextPrefix + 29)
//gap
DECLARE_PMID(kClassIDSpace,				kConditionalTextScriptProviderBoss,		kConditionalTextPrefix + 50)
DECLARE_PMID(kClassIDSpace,				kConditionalTextNewDocResponderBoss,	kConditionalTextPrefix + 51)
DECLARE_PMID(kClassIDSpace,				kConditionTagSetBoss,					kConditionalTextPrefix + 52)
DECLARE_PMID(kClassIDSpace,				kConditionTagSetCreateCmdBoss,			kConditionalTextPrefix + 53)
DECLARE_PMID(kClassIDSpace,				kConditionTagSetScriptProviderBoss,		kConditionalTextPrefix + 54)
DECLARE_PMID(kClassIDSpace,				kConditionTagSetDeleteCmdBoss,			kConditionalTextPrefix + 55)
DECLARE_PMID(kClassIDSpace,				kConditionTagSetApplyCmdBoss,			kConditionalTextPrefix + 56)
DECLARE_PMID(kClassIDSpace,				kConditionTagSetRedefineCmdBoss,		kConditionalTextPrefix + 57)
DECLARE_PMID(kClassIDSpace,				kConditionalTextFrameAdornmentBoss,		kConditionalTextPrefix + 58)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONTAG,						kConditionalTextPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONTAGLIST,					kConditionalTextPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONALTEXTFACADE,				kConditionalTextPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONALTEXTGALLEYADORNMENT,	kConditionalTextPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,			IID_IHIDDENTEXTDATA,					kConditionalTextPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONALTEXTOPTIONS,			kConditionalTextPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISHOWCONDITIONINDICATORSOPTION,		kConditionalTextPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONTAGSUITE,					kConditionalTextPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,			IID_ITEXTMODELUIDDATA,					kConditionalTextPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace,			IID_IHIDDENTEXT_DOCUMENT,				kConditionalTextPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICOLORUIDDATA,						kConditionalTextPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONTAGSET,					kConditionalTextPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace,			IID_IINDICATORMETHODDATA,				kConditionalTextPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,			IID_IUNDERLINEINDICATORAPPEARANCEDATA,	kConditionalTextPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONALTEXTSCRIPTUTILS,		kConditionalTextPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONTAGSETLIST,				kConditionalTextPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONTAGSETDATA,				kConditionalTextPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONALTEXTHELPER_DOCUMENT,	kConditionalTextPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICONDITIONALTEXTUTILS,				kConditionalTextPrefix + 19)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace,	kConditionTagImpl, 						kConditionalTextPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagListImpl,					kConditionalTextPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextFacadeImpl,				kConditionalTextPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextErrorStringServiceImpl,	kConditionalTextPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagRefConverterImpl,			kConditionalTextPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextOptionsImpl,			kConditionalTextPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kDocShowConditionIndicatorsOptionImpl_Obsolete,	kConditionalTextPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kShowConditionIndicatorsCmdImpl,		kConditionalTextPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kSessionShowConditionIndicatorsOptionImpl_Obsolete,	kConditionalTextPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagCreateCmdImpl,				kConditionalTextPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagCreateCmdDataImpl,			kConditionalTextPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagDeleteCmdImpl,				kConditionalTextPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagEditNameCmdImpl,			kConditionalTextPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagEditVisibleStateCmdImpl,	kConditionalTextPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagEditColorCmdImpl,			kConditionalTextPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagApplyCmdImpl,				kConditionalTextPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextCreateCmdImpl,				kConditionalTextPrefix + 17)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextDeleteCmdImpl,				kConditionalTextPrefix + 18)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextAdornmentImpl,				kConditionalTextPrefix + 19)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextAttrReportImpl,			kConditionalTextPrefix + 20)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextAdornmentImpl,			kConditionalTextPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextGalleyAdornmentImpl,	kConditionalTextPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextOwnedItemImpl,				kConditionalTextPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextDataImpl,					kConditionalTextPrefix + 24)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextStoryThreadImpl,				kConditionalTextPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextStoryThreadDictImpl,			kConditionalTextPrefix + 26)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextParcelListImpl,				kConditionalTextPrefix + 27)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextPLDataImpl,					kConditionalTextPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextPLComposerImpl,				kConditionalTextPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextObjectParentImpl,			kConditionalTextPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextMementoImpl,					kConditionalTextPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextScriptImpl,					kConditionalTextPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,	kHiddenTextRestoreCmdImpl,				kConditionalTextPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextOptionsScriptProviderImpl,kConditionalTextPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSuiteASBImpl,				kConditionalTextPrefix + 35)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSuiteTextCSBImpl,			kConditionalTextPrefix + 36)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSuiteTextCSBExtImpl,		kConditionalTextPrefix + 37)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagUnapplyCmdImpl,			kConditionalTextPrefix + 38)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextHideHelperCmdImpl,		kConditionalTextPrefix + 39)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextShowHelperCmdImpl,		kConditionalTextPrefix + 40)
DECLARE_PMID(kImplementationIDSpace,	kTextModelUIDDataImpl,					kConditionalTextPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kIndicatorMethodDataImpl,				kConditionalTextPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,	kUnderlineIndicatorAppearanceDataImpl,	kConditionalTextPrefix + 43)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagEditMethodCmdImpl,			kConditionalTextPrefix + 44)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagEditAppearanceCmdImpl,		kConditionalTextPrefix + 45)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagEditOptionsCmdImpl,		kConditionalTextPrefix + 46)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextScriptUtilsImpl,		kConditionalTextPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kLoadConditionTagsCmdImpl,				kConditionalTextPrefix + 48)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextSyncServiceImpl,		kConditionalTextPrefix + 49)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextScriptProviderImpl,		kConditionalTextPrefix + 50)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagScriptImpl,				kConditionalTextPrefix + 51)
DECLARE_PMID(kImplementationIDSpace,	kColorUIDDataImpl,						kConditionalTextPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextNewDocResponderImpl,	kConditionalTextPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetImpl,					kConditionalTextPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetListImpl,				kConditionalTextPrefix + 55)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetCreateCmdImpl,			kConditionalTextPrefix + 56)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetDataImpl,				kConditionalTextPrefix + 57)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetScriptProviderImpl,		kConditionalTextPrefix + 58)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetScriptImpl,				kConditionalTextPrefix + 59)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetDeleteCmdImpl,			kConditionalTextPrefix + 60)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetApplyCmdImpl,			kConditionalTextPrefix + 61)
DECLARE_PMID(kImplementationIDSpace,	kConditionTagSetRedefineCmdImpl,		kConditionalTextPrefix + 62)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextFrameAdornmentImpl,		kConditionalTextPrefix + 63)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextUtilsImpl,				kConditionalTextPrefix + 64)
DECLARE_PMID(kImplementationIDSpace,	kDocShowConditionIndicatorsOptionImpl,	kConditionalTextPrefix + 65)
DECLARE_PMID(kImplementationIDSpace,	kSessionShowConditionIndicatorsOptionImpl,	kConditionalTextPrefix + 66)
DECLARE_PMID(kImplementationIDSpace,	kConditionalTextPostProcessImpl,		kConditionalTextPrefix + 67)

//----------------------------------------------------------------------------------------
// Error identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kErrorIDSpace,				kConditionTag_NameExistsAlreadyErr, 	kConditionalTextPrefix + 1)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_DoesntExistErr,			kConditionalTextPrefix + 2)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_ReplacementDoesntExistErr,kConditionalTextPrefix + 3)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_InvalidColorErr,			kConditionalTextPrefix + 4)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_LockedContentErr,			kConditionalTextPrefix + 5)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_HiddenTextErr,			kConditionalTextPrefix + 6)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_LoadSameDocErr,			kConditionalTextPrefix + 7)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_LoadOpenDocErr,			kConditionalTextPrefix + 8)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_EmptyNameErr, 			kConditionalTextPrefix + 9)
DECLARE_PMID(kErrorIDSpace,				kConditionTag_HiddenTextAnchorErr,		kConditionalTextPrefix + 10)
DECLARE_PMID(kErrorIDSpace,				kDeleteHiddenTextDontShowID,			kConditionalTextPrefix + 11)

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------
//DECLARE_PMID(kActionIDSpace,			kMyActionID, 							kConditionalTextPrefix + 1)

#endif //  __ConditionalTextID__

