//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/BNTextAttrID.h $
//  
//  Owner: vbatra
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

#ifndef __BNTextAttrID__
#define __BNTextAttrID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// Plug-In:
#define kBNCorePrefix		RezLong(0x1A400)
#define kBNCoreStringPrefix	"0x1A400"
#define kBNCorePluginName	"BNCore" // Name of this plug-in.

// Plugin ID:
DECLARE_PMID(kPlugInIDSpace, kBNCorePluginID, kBNCorePrefix + 0)

// Class IDs:
DECLARE_PMID(kClassIDSpace, kBNListTypeBoss, kBNCorePrefix + 1)

DECLARE_PMID(kClassIDSpace, kBNFontUIDBoss_obsolete, kBNCorePrefix + 2)
DECLARE_PMID(kClassIDSpace, kBNFontStyleBoss_obsolete, kBNCorePrefix + 3)

DECLARE_PMID(kClassIDSpace, kBNSizeBoss, kBNCorePrefix + 4)
DECLARE_PMID(kClassIDSpace, kBNColorBoss, kBNCorePrefix + 5)
DECLARE_PMID(kClassIDSpace, kBNBulletCharacterBoss, kBNCorePrefix + 6)
DECLARE_PMID(kClassIDSpace, kBNNumberStartAtBoss, kBNCorePrefix + 7)
DECLARE_PMID(kClassIDSpace, kBNNumberSeparatorBoss, kBNCorePrefix + 8)
//DECLARE_PMID(kClassIDSpace, kBNTextAdornmentBoss, kBNCorePrefix + 9)
//DECLARE_PMID(kClassIDSpace, kBNTextAdornmentDataBoss, kBNCorePrefix + 10)
DECLARE_PMID(kClassIDSpace, kBNNumberingStyleBoss, kBNCorePrefix + 11)
DECLARE_PMID(kClassIDSpace, kBNIteratorRegBoss, kBNCorePrefix + 18)

DECLARE_PMID(kClassIDSpace, kBNBulletFontUIDBoss, kBNCorePrefix + 19)
DECLARE_PMID(kClassIDSpace, kBNBulletFontStyleBoss, kBNCorePrefix + 20)
DECLARE_PMID(kClassIDSpace, kBNNumberingFontUIDBoss, kBNCorePrefix + 21)
DECLARE_PMID(kClassIDSpace, kBNNumberingFontStyleBoss, kBNCorePrefix + 22)
DECLARE_PMID(kClassIDSpace, kBNListStyleBoss,		kBNCorePrefix + 23)
DECLARE_PMID(kClassIDSpace, kBNListLevelBoss,		kBNCorePrefix + 24)

DECLARE_PMID(kClassIDSpace, kBNNumberingCFPreviousBoss,		kBNCorePrefix + 25)
DECLARE_PMID(kClassIDSpace, kBNShouldRestartBoss,	kBNCorePrefix + 29)
DECLARE_PMID(kClassIDSpace, kBNRestartPolicyBoss,	kBNCorePrefix + 30)
DECLARE_PMID(kClassIDSpace, kBNBulletCharStyleBoss,	kBNCorePrefix + 31)
DECLARE_PMID(kClassIDSpace, kBNNumberCharStyleBoss,	kBNCorePrefix + 32)
DECLARE_PMID(kClassIDSpace, kBNBulletAlignmentBoss,	kBNCorePrefix + 33)
DECLARE_PMID(kClassIDSpace, kBNNumberAlignmentBoss,	kBNCorePrefix + 34)
DECLARE_PMID(kClassIDSpace, kBNNumberingNumberBoss,		kBNCorePrefix + 35)
DECLARE_PMID(kClassIDSpace, kBNBulletTextAfterBoss,		kBNCorePrefix + 36)

// Interface IDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRNUMBERINGSTYLE, kBNCorePrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRLISTTYPE, kBNCorePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNDRAWINGSTYLE, kBNCorePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRBULLETCHARACTER, kBNCorePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRLISTALIGNMENT,	   kBNCorePrefix + 4)
//gap 5-7
DECLARE_PMID(kInterfaceIDSpace, IID_IBULLETSANDNUMBERINGSUITE, kBNCorePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRRESTARTPOLICY,	   kBNCorePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IISLOCALEINDEPENDENT,	   kBNCorePrefix + 200)

#define kBNSizeBoss_obsolete kBNSizeBoss
#define kBNColorBoss_obsolete kBNColorBoss
#define kBNNumberSeparatorBoss_obsolete kBNNumberSeparatorBoss
#define kBNNumberingFontUIDBoss_obsolete kBNNumberingFontUIDBoss
#define kBNNumberingFontStyleBoss_obsolete kBNNumberingFontStyleBoss

// Implementation IDs (to reuse numbering styles):
DECLARE_PMID(kImplementationIDSpace, kKatakanaModernNumberConverterImpl, kBNCorePrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kKatakanaTraditionalNumberConverterImpl, kBNCorePrefix + 201)
// Korean numbering Providers
DECLARE_PMID(kImplementationIDSpace, kKoreanNumbering1ConverterImpl,  kBNCorePrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kKoreanNumbering2ConverterImpl,  kBNCorePrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kKoreanDoubleByteNumbering2ConverterImpl,  kBNCorePrefix + 204)
// Obsoleted, hence reusing for Chinese Numbering - 4
//DECLARE_PMID(kImplementationIDSpace, kKoreanDoubleByteNumbering4ConverterImpl,  kBNCorePrefix + 205)
// Four new Chinese Numbering Styles
DECLARE_PMID(kImplementationIDSpace, kChineseNumbering4ConverterImpl,  kBNCorePrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kCircleNumberingConverterImpl,  kBNCorePrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kChineseZodiacNumbering1ConverterImpl,  kBNCorePrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kChineseZodiacNumbering2ConverterImpl,  kBNCorePrefix + 208)
// New Taiwanese Style
DECLARE_PMID(kImplementationIDSpace, kTaiwaneseDoubleByteNumbering2ConverterImpl,  kBNCorePrefix + 209)



// ServiceIDs:
DECLARE_PMID(kServiceIDSpace, kService_ParagraphNumberingStyles, kBNCorePrefix + 0)

#endif // __BNTextAttrID__
