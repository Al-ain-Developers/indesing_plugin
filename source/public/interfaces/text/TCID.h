//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TCID.h $
//  
//  Owner: Eric Menninga
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

#ifndef __TCID__
#define __TCID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTCPrefix					RezLong(0x2000)


// ResourceIDs
#define kTCMLPanelRsrcID_Obsolete 					2000
#define kTCMLPanelStringsRsrcID_Obsolete 			2100
#define kTCMLPanelStringsNoTransRsrcID_Obsolete 		2200

#define kHLRsrcID 				3000
#define kHLStringsRsrcID 		3100


// <Start IDC>
// PluginID
// kHLPluginID replaces what used to be called kTCPluginID
#define kHLPluginName				"Paragraph Composer"

START_IDS()
DECLARE_PMID(kPlugInIDSpace, kHLPluginID, kTCPrefix + 1)


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSingleLineComposerBoss, kTCPrefix + 1)
DECLARE_PMID(kClassIDSpace, kParagraphComposerBoss, kTCPrefix + 2)		// used to be kTCMLEngineBoss
DECLARE_PMID(kClassIDSpace, kTCTextAttrComposeWidthBoss_Obsolete, kTCPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTCTextAttrComposeDepthBoss_Obsolete, kTCPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTCTextAttrHyphenFactorBoss_Obsolete, kTCPrefix + 5)
DECLARE_PMID(kClassIDSpace, kTCTextAttrHyphenMagnifierBoss_Obsolete, kTCPrefix + 6)
DECLARE_PMID(kClassIDSpace, kTCTextAttrHyphenScaleBoss_Obsolete, kTCPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTCTextAttrHyphenFixedBoss_Obsolete, kTCPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTCTextAttrLastLineHyphenBoss_Obsolete, kTCPrefix + 9)

DECLARE_PMID(kClassIDSpace, kTCTextAttrConsistencyBoss_Obsolete, kTCPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTCTextAttrFavorFactorBoss_Obsolete, kTCPrefix + 11)
DECLARE_PMID(kClassIDSpace, kTCTextAttrMaxRagCompressBoss_Obsolete, kTCPrefix + 12)
DECLARE_PMID(kClassIDSpace, kHLStartupShutdownBoss, kTCPrefix + 13)
DECLARE_PMID(kClassIDSpace, kHLCloseDocResponderBoss, kTCPrefix + 14)
//gap
DECLARE_PMID(kClassIDSpace, kJParagraphComposerBoss, kTCPrefix + 16)
DECLARE_PMID(kClassIDSpace, kJSingleComposerBoss, kTCPrefix + 17)
DECLARE_PMID(kClassIDSpace, kJParagraphComposerBoss_Oooops, kTCPrefix + 18)
DECLARE_PMID(kClassIDSpace, kJSingleComposerBoss_Oooops, kTCPrefix + 19)

DECLARE_PMID(kClassIDSpace, kHLNewStoryResponderBoss, kTCPrefix + 20)
DECLARE_PMID(kClassIDSpace, kHLPhase2ConversionBoss, kTCPrefix + 21)
DECLARE_PMID(kClassIDSpace, kHLSchemaConversionProviderBoss, kTCPrefix + 22)
DECLARE_PMID(kClassIDSpace, kBNTextAdornmentBoss, kTCPrefix + 23)
DECLARE_PMID(kClassIDSpace, kBNTextAdornmentDataBoss, kTCPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kBN2TextAdornmentBoss, kTCPrefix + 25)
//DECLARE_PMID(kClassIDSpace, kBN2TextAdornmentDataBoss, kTCPrefix + 26)
// gap

DECLARE_PMID(kClassIDSpace, kHLTableStrandBoss, kTCPrefix + 37)
//gap

DECLARE_PMID(kClassIDSpace, kWaxLeaderRunBoss_Obsolete, kTCPrefix + 75)
DECLARE_PMID(kClassIDSpace, kWaxPageNumRunBoss_Obsolete, kTCPrefix + 76)
DECLARE_PMID(kClassIDSpace, kWaxSectionNameRunBoss_Obsolete, kTCPrefix + 77)
// gap
DECLARE_PMID(kClassIDSpace, kHLTable_PastePieceBoss, kTCPrefix + 79)
//gap

//#ifdef LINNAEUS
DECLARE_PMID(kClassIDSpace, kJustificationSystemBoss, kTCPrefix + 100)
DECLARE_PMID(kClassIDSpace, kJustSystemContentHandlerBoss, kTCPrefix + 101)
DECLARE_PMID(kClassIDSpace, kLinnaeusComposerBoss, kTCPrefix + 102)
DECLARE_PMID(kClassIDSpace, kDefaultJustificationSystemBoss, kTCPrefix + 103)
//#endif
//gap

DECLARE_PMID(kClassIDSpace, kOptycaParagraphComposerBoss, kTCPrefix + 120)
DECLARE_PMID(kClassIDSpace, kOptycaSingleComposerBoss, kTCPrefix + 121)


// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IMULTILINESTYLE_OBSOLETE, kTCPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITCCENTRALDATA_OBSOLETE, kTCPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSERDEBUGFLAGS, kTCPrefix + 3)
//#ifdef LINNAEUS
DECLARE_PMID(kInterfaceIDSpace, IID_IJUSTIFICATIONSYSTEM, kTCPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IJUSTSYSTEMNAMETABLE, kTCPrefix + 5)
//#endif
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITIONUTILS, kTCPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IHLTABLEMASTERCACHE, kTCPrefix + 7)



// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kSingleLineComposerImpl, kTCPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kParagraphComposerImpl, kTCPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSingleLineServiceImpl, kTCPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kParagraphServiceImpl, kTCPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kTCCentralDataImpl_Obsolete, kTCPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kMultilineStyleImpl_Obsolete, kTCPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kTAComposeDepthReportImpl_Obsolete, kTCPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kTAComposeWidthReportImpl_Obsolete, kTCPrefix + 9)

DECLARE_PMID(kImplementationIDSpace, kTextAttrRN_0Impl_Obsolete, kTCPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRN_0p05Impl_Obsolete, kTCPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRN_15Impl_Obsolete, kTCPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRN_75Impl_Obsolete, kTCPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRN_12Impl_Obsolete, kTCPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTAHyphenFactorReportImpl_Obsolete, kTCPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kTAHyphenMagnifierReportImpl_Obsolete, kTCPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTAHyphenScaleReportImpl_Obsolete, kTCPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTAHyphenFixedReportImpl_Obsolete, kTCPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kTALastLineHyphenReportImpl_Obsolete, kTCPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kTAConsistencyReportImpl_Obsolete, kTCPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTAFavorFactorReportImpl_Obsolete, kTCPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kTAMaxRagCompressReportImpl_Obsolete, kTCPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kJParagraphServiceImpl, kTCPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kJParagraphComposerImpl, kTCPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kJSingleServiceImpl, kTCPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kJSingleComposerImpl, kTCPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kHLTableStrandImpl, kTCPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kHLTableAttrStrandImpl, kTCPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kHLNewStoryResponderImpl, kTCPrefix + 29)

DECLARE_PMID(kImplementationIDSpace, kWaxLeaderRunTextImpl_Obsolete, kTCPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kWaxLeaderGlyphsImpl_Obsolete, kTCPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPageNumberTextImpl_Obsolete, kTCPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kSectionNameTextImpl_Obsolete, kTCPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kComposerDebugFlagsImpl, kTCPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCompositionUtilsImpl, kTCPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kHLStartupShutdownImpl, kTCPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kHLCloseDocResponderImpl, kTCPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kHLTableMasterCacheImpl, kTCPrefix + 38)

// gap
DECLARE_PMID(kImplementationIDSpace, kCJKTCSingleLineComposerImpl_Obsolete, kTCPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kCJKTCMLComposerImpl_Obsolete, kTCPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kCJKTCSingleLineServiceImpl_Obsolete, kTCPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kCJKTCMultiEngineServiceImpl_Obsolete, kTCPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kHLPhase2ConversionImpl, kTCPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kHLNewStoryRespServiceImpl, kTCPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kHLTable_PastePieceImpl, kTCPrefix + 45)
//DECLARE_PMID(kImplementationIDSpace, kBNTextAdornmentImpl, kTCPrefix + 46)
//DECLARE_PMID(kImplementationIDSpace, kBNAdornmentDataImpl, kTCPrefix + 47)
//DECLARE_PMID(kImplementationIDSpace, kBNWaxRunImpl, kTCPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kBNTextAdornmentDataImpl, kTCPrefix + 49)

//#ifdef LINNAEUS
DECLARE_PMID(kImplementationIDSpace, kJustificationSystemImpl, kTCPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kXMLJustifyContentHandlerImpl, kTCPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kJustSystemNameTableImpl, kTCPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kLinnaeusComposerImpl, kTCPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kLinnaeusComposerServiceImpl, kTCPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kDefaultJustificationSystemImpl, kTCPrefix + 55)
//#endif

//gap

DECLARE_PMID(kImplementationIDSpace, kOptycaParagraphServiceImpl, kTCPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kOptycaParagraphComposerImpl, kTCPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kOptycaSingleServiceImpl, kTCPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kOptycaSingleComposerImpl, kTCPrefix + 73)

END_IDS()

#endif // __TCID__
