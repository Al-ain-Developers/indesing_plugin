//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/SectionID.h $
//  
//  Owner: Tommy Donovan
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
//  Contains IDs used by the section plug-in
//  
//========================================================================================

#ifndef __SectionID__
#define __SectionID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSectionPrefix	 RezLong(0x4c00)

// RsrcID
#define kSectionStringsRsrcID 1000
#define kSectionErrorStringTableRsrcID 1100
#define kSectionStringsNoTransRsrcID 1200

// <Start IDC>
// PluginID
#define kSectionPluginName 			"Sections"
DECLARE_PMID(kPlugInIDSpace, kSectionPluginID, kSectionPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSectionBoss, kSectionPrefix + 1)
DECLARE_PMID(kClassIDSpace, kNewSectionCmdBoss, kSectionPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDeleteSectionCmdBoss, kSectionPrefix + 3)
DECLARE_PMID(kClassIDSpace, kModifySectionSettingsCmdBoss, kSectionPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSetSectionPaginationOptionsCmdBoss, kSectionPrefix + 5)

// Following boss has been obsoleted. It will not be removed since a code converter will refer to it.
DECLARE_PMID(kClassIDSpace, kSectionStylesServiceBoss_obsolete, kSectionPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSectionNewDocResponderBoss, kSectionPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSectionCodeConversionProviderBoss, kSectionPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSectionErrorStringServiceBoss,  kSectionPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSetPageNumberPrefsCmdBoss, kSectionPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSectionStartupShutdownBoss, kSectionPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSectionOpenAppActionBoss, kSectionPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSectionConversionProviderBoss, kSectionPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSectionIteratorRegBoss, kSectionPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSectionPhase2ConversionResponderBoss, kSectionPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSectionScriptProviderBoss, kSectionPrefix + 16)
// Following boss has been obsoleted. It will not be removed since a code converter will refer to it.
DECLARE_PMID(kClassIDSpace, kJapaneseSectionStylesServicesBoss_again_obsolete,  kSectionPrefix + 17)
// New page numbering style bosses. Do not change the Ids, since these are persisted in the document.
DECLARE_PMID(kClassIDSpace, kKanjiPageNumberingStyleServiceBoss, kSectionPrefix + 18)
DECLARE_PMID(kClassIDSpace, kDoubleZeroPageNumberingStyleServiceBoss, kSectionPrefix + 19)
DECLARE_PMID(kClassIDSpace, kTripleZeroPageNumberingStyleServiceBoss, kSectionPrefix + 20)
DECLARE_PMID(kClassIDSpace, kArabicPageNumberingStyleServiceBoss, kSectionPrefix + 21)
DECLARE_PMID(kClassIDSpace, kRomanUpperPageNumberingStyleServiceBoss, kSectionPrefix + 22)
DECLARE_PMID(kClassIDSpace, kRomanLowerPageNumberingStyleServiceBoss, kSectionPrefix + 23)
DECLARE_PMID(kClassIDSpace, kLettersUpperPageNumberingStyleServiceBoss, kSectionPrefix + 24)
DECLARE_PMID(kClassIDSpace, kLettersLowerPageNumberingStyleServiceBoss, kSectionPrefix + 25)
DECLARE_PMID(kClassIDSpace, kSingleZeroPageNumberingStyleServiceBoss, kSectionPrefix + 26)
DECLARE_PMID(kClassIDSpace, kFullWidthPageNumberingStyleServiceBoss, kSectionPrefix + 27)
DECLARE_PMID(kClassIDSpace, kHindiPageNumberingStyleServiceBoss, kSectionPrefix + 28)
DECLARE_PMID(kClassIDSpace, kFarsiPageNumberingStyleServiceBoss, kSectionPrefix + 29)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISECTION, kSectionPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECTIONLIST, kSectionPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECTIONCMDDATA, kSectionPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBERCONVERTER, kSectionPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGENUMBERPREFS, kSectionPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGENUMBERPREFSCMDDATA, kSectionPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECTIONOBSERVER, kSectionPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECTIONCMDOUTPUTDATA, kSectionPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATECONVERTER, kSectionPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGCONVERTER, kSectionPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECTIONUTILS, kSectionPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTML5REPAGINATIONOPTIONSCMDDATA, kSectionPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISKIPSHUFFLEBOOLDATA, kSectionPrefix + 14)



// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kSectionListImpl, kSectionPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSectionImpl, kSectionPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kNewSectionCmdImpl, kSectionPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSectionCmdDataImpl, kSectionPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDeleteSectionCmdImpl, kSectionPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kModifySectionSettingsCmdImpl, kSectionPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSectionObserverImpl, kSectionPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSkipShuffleFlagImpl, kSectionPrefix + 8)
// gap
DECLARE_PMID(kImplementationIDSpace, kSectionNewDocResponderImpl, kSectionPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSectionCmdOutputDataImpl, kSectionPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSectionUtilsImpl, kSectionPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetSectionPaginationOptionsCmdImpl, kSectionPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSetPageNumberPrefsCmdImpl, kSectionPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCPageNumberPrefsImpl, kSectionPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPageNumberPrefsCmdDataImpl, kSectionPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSectionStartupShutdownImpl, kSectionPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSectionIteratorRegImpl, kSectionPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSectionPhase2ConversionImpl, kSectionPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSectionScriptProviderImpl, kSectionPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSectionScriptImpl, kSectionPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSectionCodeConversionProviderImpl, kSectionPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSectionErrorStringServiceImpl, kSectionPrefix + 24)

DECLARE_PMID(kImplementationIDSpace, kPageNumberingStylesService, kSectionPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kDefaultPageNumberingStylesService, kSectionPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kArabicNumberConverterImpl, kSectionPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kRomanUpperNumberConverterImpl, kSectionPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kRomanLowerNumberConverterImpl, kSectionPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kLettersUpperNumberConverterImpl, kSectionPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kLettersLowerNumberConverterImpl, kSectionPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kKanjiNumberConverterImpl, kSectionPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDoubleZeroNumberConverterImpl, kSectionPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTripleZeroNumberConverterImpl, kSectionPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kFullWidthNumberConverterImpl, kSectionPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSingleZeroNumberConverterImpl, kSectionPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAsterixNumberConverterImpl, kSectionPrefix + 37)

// <Service ID>
// Service Provider IDs
DECLARE_PMID(kServiceIDSpace, kService_PageNumberingStyles, kSectionPrefix + 2)

// Error Codes
DECLARE_PMID(kErrorIDSpace, kConflictSectionSettingError,				kSectionPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kDuplicateSectionError,						kSectionPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kEmptySectionNameError,						kSectionPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kSectionContainsSpaceError,					kSectionPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kBadSectionCharacterError,					kSectionPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCantDeleteDefaultSection,					kSectionPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kBadSectionStartPageNumber,					kSectionPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kDuplicateSectionStartPageError,			kSectionPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kNoAvailablePageSectionError,				kSectionPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kEmptyAlternateLayoutNameError,				kSectionPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kDuplicateAlternateLayoutNameError,			kSectionPrefix + 11)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kSectionObjectScriptElement,						kSectionPrefix + 40)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateSectionMethodScriptElement,					kSectionPrefix + 80)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberStylePropertyScriptElement,				kSectionPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kContinueNumberingPropertyScriptElement,			kSectionPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberStartPropertyScriptElement,				kSectionPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kMarkerPropertyScriptElement,						kSectionPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kPageStartPropertyScriptElement,					kSectionPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kSectionLengthPropertyScriptElement,				kSectionPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberIncludeSectionPrefixPropertyScriptElement,	kSectionPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kSectionPrefixPropertyScriptElement,				kSectionPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kSectionAlternateLayoutPropertyScriptElement,		kSectionPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kSectionPaginationPropertyScriptElement,			kSectionPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kSectionRemovePagePaginationPropertyScriptElement,	kSectionPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kSectionPaginationMasterPropertyScriptElement,		kSectionPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kSectionAlternateLayoutLengthPropertyScriptElement,kSectionPrefix + 112)


//Enums
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberStyleEnumScriptElement,					kSectionPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kPaginationOptionEnumScriptElement,				kSectionPrefix + 201)



//GUIDS
// {EE96406F-06C6-11d2-AAC9-00C04FA349C7}
#define kSection_CLSID { 0xee96406f, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964070-06C6-11d2-AAC9-00C04FA349C7}
#define kSections_CLSID { 0xee964070, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }

#endif // __SectionID__

