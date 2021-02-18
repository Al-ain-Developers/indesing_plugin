//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyWorkflowID.h $
//  
//  Owner:
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __InCopyWorkflowID__
#define __InCopyWorkflowID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyWorkflowPrefix			RezLong(0x17400)

#define kInCopyWorkflowPluginName 	"InCopyWorkflow"

START_IDS()
DECLARE_PMID(kPlugInIDSpace,		kInCopyWorkflowPluginID,				kInCopyWorkflowPrefix + 1)

//gap
DECLARE_PMID(kClassIDSpace,			kInCopyWorkflowBoss,					kInCopyWorkflowPrefix + 7)
DECLARE_PMID(kClassIDSpace,			kInCopyImportCmdBoss,					kInCopyWorkflowPrefix + 8)
DECLARE_PMID(kClassIDSpace,			kInCopyXMLElementAttrBoss,				kInCopyWorkflowPrefix + 9)
DECLARE_PMID(kClassIDSpace,			kStoryElementHandlerBoss,				kInCopyWorkflowPrefix + 10)
DECLARE_PMID(kClassIDSpace,			kNoteElementHandlerBoss,				kInCopyWorkflowPrefix + 11)
DECLARE_PMID(kClassIDSpace,			kTextAttrElementHandlerBoss,			kInCopyWorkflowPrefix + 12)
DECLARE_PMID(kClassIDSpace,			kIndexElementHandlerBoss,				kInCopyWorkflowPrefix + 13)
DECLARE_PMID(kClassIDSpace,			kUTF16ConversionStreamBoss,				kInCopyWorkflowPrefix + 14)
DECLARE_PMID(kClassIDSpace,			kInCopySimpleXMLHandlerBoss,			kInCopyWorkflowPrefix + 15)
DECLARE_PMID(kClassIDSpace,			kColorElementHandlerBoss,				kInCopyWorkflowPrefix + 16)
DECLARE_PMID(kClassIDSpace,			kGradientElementHandlerBoss,			kInCopyWorkflowPrefix + 17)
DECLARE_PMID(kClassIDSpace,			kStyleListElementHandlerBoss,			kInCopyWorkflowPrefix + 18)
DECLARE_PMID(kClassIDSpace,			kSwatchListElementHandlerBoss,			kInCopyWorkflowPrefix + 19)
DECLARE_PMID(kClassIDSpace,			kStyleElementHandlerBoss,				kInCopyWorkflowPrefix + 20)
DECLARE_PMID(kClassIDSpace,			kDeleteElementHandlerBoss,				kInCopyWorkflowPrefix + 21)
DECLARE_PMID(kClassIDSpace,			kInsertElementHandlerBoss,				kInCopyWorkflowPrefix + 22)
DECLARE_PMID(kClassIDSpace,			kDocPrefsElementHandlerBoss,			kInCopyWorkflowPrefix + 23)
DECLARE_PMID(kClassIDSpace,			kHyperlinkElementHandlerBoss,			kInCopyWorkflowPrefix + 24)
DECLARE_PMID(kClassIDSpace,			kInCopyImportMetaDataCmdBoss,			kInCopyWorkflowPrefix + 25)
DECLARE_PMID(kClassIDSpace,			kTableElementHandlerBoss,				kInCopyWorkflowPrefix + 26)
DECLARE_PMID(kClassIDSpace,			kTableCellElementHandlerBoss,			kInCopyWorkflowPrefix + 27)
DECLARE_PMID(kClassIDSpace,			kUTF8ConversionStreamBoss,				kInCopyWorkflowPrefix + 28)
//gap
DECLARE_PMID(kClassIDSpace,			kInlineElementHandlerBoss, 				kInCopyWorkflowPrefix + 35)
//gap
DECLARE_PMID(kClassIDSpace,			kSPAssetElementHandlerBoss,				kInCopyWorkflowPrefix + 38)
DECLARE_PMID(kClassIDSpace,			kSetInlineDataCmdBoss,					kInCopyWorkflowPrefix + 39)
DECLARE_PMID(kClassIDSpace,			kXMLTagListElementHandlerBoss,			kInCopyWorkflowPrefix + 40)
DECLARE_PMID(kClassIDSpace,			kUserListElementHandlerBoss,			kInCopyWorkflowPrefix + 41)
//gap
DECLARE_PMID(kClassIDSpace,			kInCopyImportOptionsBoss,				kInCopyWorkflowPrefix + 43)
DECLARE_PMID(kClassIDSpace,			kEndInsertElementHandlerBoss,			kInCopyWorkflowPrefix + 44)
DECLARE_PMID(kClassIDSpace,			kICWorkflowConversionProviderBoss,		kInCopyWorkflowPrefix + 45)
DECLARE_PMID(kClassIDSpace,			kClearStoryMetaDataRefCmdBoss,			kInCopyWorkflowPrefix + 46)
DECLARE_PMID(kClassIDSpace, 		kTaggedlineElementHandlerBoss, 			kInCopyWorkflowPrefix + 47)
DECLARE_PMID(kClassIDSpace, 		kMoveStoryMetaDataCmdBoss, 				kInCopyWorkflowPrefix + 48)
//gap
DECLARE_PMID(kClassIDSpace, 		kInCopySaveDocResponderBoss, 			kInCopyWorkflowPrefix + 51)
DECLARE_PMID(kClassIDSpace, 		kInCopySaveAsDocResponderBoss, 			kInCopyWorkflowPrefix + 52)
DECLARE_PMID(kClassIDSpace, 		kInCopySaveACopyResponderBoss, 			kInCopyWorkflowPrefix + 53)
DECLARE_PMID(kClassIDSpace, 		kInCopyDocumentHandlerBoss, 			kInCopyWorkflowPrefix + 54)
DECLARE_PMID(kClassIDSpace, 		kXMPElementHandlerBoss, 				kInCopyWorkflowPrefix + 55)
DECLARE_PMID(kClassIDSpace, 		kInkListElementHandlerBoss, 			kInCopyWorkflowPrefix + 56)

//gap
DECLARE_PMID(kInterfaceIDSpace,		IID_IDATASTRINGUTILS,			kInCopyWorkflowPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYXMLVALUE,			kInCopyWorkflowPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYWORKFLOW,			kInCopyWorkflowPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,		IID_IICIMPORTCMDDATA,			kInCopyWorkflowPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYXMLELEMENTHANDLER,	kInCopyWorkflowPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYXMLELEMENTATTR,		kInCopyWorkflowPrefix + 8)
//gap
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYXMLELEMENTPROVIDER,	kInCopyWorkflowPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYSTORYCONTEXT,		kInCopyWorkflowPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,		IID_IIINCOPYWORKFLOWUTILS,		kInCopyWorkflowPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYSTYLECONTEXT,		kInCopyWorkflowPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYSWATCHCONTEXT,		kInCopyWorkflowPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYTABLECONTEXT,		kInCopyWorkflowPrefix + 15)
//gap
DECLARE_PMID(kInterfaceIDSpace,		IID_IMAPMISSINGUTILS,			kInCopyWorkflowPrefix + 17)
//gap
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYDOCUTILS,			kInCopyWorkflowPrefix + 19)
//gap
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYISOPENDATA,			kInCopyWorkflowPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYFILEINFO,			kInCopyWorkflowPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYIMPORTOPTIONS,		kInCopyWorkflowPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYIMPORTSUPPORT,		kInCopyWorkflowPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYDOCUMENTHANDLERDATA,	kInCopyWorkflowPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace,		IID_ISWATCHMAPPER, 				kInCopyWorkflowPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTSUITE,			kInCopyWorkflowPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTLAYERSUITE,	kInCopyWorkflowPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTALLSUITE,		kInCopyWorkflowPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTALLSTORIESSUITE,	kInCopyWorkflowPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTALLGRAPHICSSUITE,	kInCopyWorkflowPrefix + 31)
//gap
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYTABLECONTEXTME_OBSOLETE,		kInCopyWorkflowPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTALLCONCURRENCY,	kInCopyWorkflowPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace,		IID_IINCOPYEXPORTDOCUMENTSAVETRIGGER,	kInCopyWorkflowPrefix + 35)

//gap
DECLARE_PMID(kImplementationIDSpace,	kDataStringUtilsImpl,			kInCopyWorkflowPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kInCopyWorkflowImpl,			kInCopyWorkflowPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kInCopyImportCmdImpl,			kInCopyWorkflowPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kInCopyImportCmdDataImpl,		kInCopyWorkflowPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLElementAttrImpl,		kInCopyWorkflowPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kStoryElementHandlerImpl,		kInCopyWorkflowPrefix + 14)
//gap
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLHandlerServiceImpl, 	kInCopyWorkflowPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,	kNoteElementHandlerImpl, 		kInCopyWorkflowPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,	kTextAttrElementHandlerImpl, 	kInCopyWorkflowPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,	kStoryContextImpl, 				kInCopyWorkflowPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kIndexElementHandlerImpl,		kInCopyWorkflowPrefix + 32)
//gap
DECLARE_PMID(kImplementationIDSpace,	kUTF16PMStreamImpl, 			kInCopyWorkflowPrefix + 38)
DECLARE_PMID(kImplementationIDSpace,	kInCopySimpleXMLHandlerImpl, 	kInCopyWorkflowPrefix + 39)
DECLARE_PMID(kImplementationIDSpace,	kInCopyWorkflowUtilsImpl, 		kInCopyWorkflowPrefix + 40)
DECLARE_PMID(kImplementationIDSpace,	kColorElementHandlerImpl, 		kInCopyWorkflowPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kGradientElementHandlerImpl, 	kInCopyWorkflowPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,	kTextUIDAttrElementHandlerImpl,	kInCopyWorkflowPrefix + 43)
DECLARE_PMID(kImplementationIDSpace,	kStyleListElementHandlerImpl, 	kInCopyWorkflowPrefix + 44)
DECLARE_PMID(kImplementationIDSpace,	kSwatchListElementHandlerImpl, 	kInCopyWorkflowPrefix + 45)
DECLARE_PMID(kImplementationIDSpace,	kStyleElementHandlerImpl, 		kInCopyWorkflowPrefix + 46)
DECLARE_PMID(kImplementationIDSpace,	kInCopyStyleContextImpl, 		kInCopyWorkflowPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kDeleteElementHandlerImpl, 		kInCopyWorkflowPrefix + 48)
DECLARE_PMID(kImplementationIDSpace,	kInsertElementHandlerImpl,		kInCopyWorkflowPrefix + 49)
DECLARE_PMID(kImplementationIDSpace,	kDocPrefsElementHandlerImpl, 	kInCopyWorkflowPrefix + 50)
DECLARE_PMID(kImplementationIDSpace,	kInCopySwatchContextImpl,		kInCopyWorkflowPrefix + 51)
//gap
DECLARE_PMID(kImplementationIDSpace,	kFontElementHandlerImpl, 		kInCopyWorkflowPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,	kFontStyleElementHandlerImpl, 	kInCopyWorkflowPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,	kLangElementHandlerImpl, 		kInCopyWorkflowPrefix + 55)
DECLARE_PMID(kImplementationIDSpace,	kTabElementHandlerImpl, 		kInCopyWorkflowPrefix + 56)
DECLARE_PMID(kImplementationIDSpace,	kHyperlinkElementHandlerImpl, 	kInCopyWorkflowPrefix + 57)
DECLARE_PMID(kImplementationIDSpace,	kInCopyImportMetaDataCmdImpl,	kInCopyWorkflowPrefix + 58)
DECLARE_PMID(kImplementationIDSpace,	kTableElementHandlerImpl, 		kInCopyWorkflowPrefix + 59)
DECLARE_PMID(kImplementationIDSpace,	kTableContextImpl, 				kInCopyWorkflowPrefix + 60)
DECLARE_PMID(kImplementationIDSpace,	kTableCellElementHandlerImpl, 	kInCopyWorkflowPrefix + 61)
//gap
DECLARE_PMID(kImplementationIDSpace,	kUTF8PMStreamImpl, 				kInCopyWorkflowPrefix + 63)
//gap
DECLARE_PMID(kImplementationIDSpace,	kInlineElementHandlerImpl, 		kInCopyWorkflowPrefix + 71)
//gap
DECLARE_PMID(kImplementationIDSpace,	kSPAssetElementHandlerImpl, 	kInCopyWorkflowPrefix + 73)
DECLARE_PMID(kImplementationIDSpace,	kSetInlineDataCmdImpl, 			kInCopyWorkflowPrefix + 74)
DECLARE_PMID(kImplementationIDSpace,	kXMLTagListElementHandlerImpl, 	kInCopyWorkflowPrefix + 75)
DECLARE_PMID(kImplementationIDSpace,	kUserListElementHandlerImpl, 	kInCopyWorkflowPrefix + 76)
// gap
DECLARE_PMID(kImplementationIDSpace,	kInCopyFileInfoImpl,				kInCopyWorkflowPrefix + 79)
DECLARE_PMID(kImplementationIDSpace,	kInCopyDesignFileDataImpl,			kInCopyWorkflowPrefix + 80)
DECLARE_PMID(kImplementationIDSpace,	kInCopyImportOptionsImpl,			kInCopyWorkflowPrefix + 81)
DECLARE_PMID(kImplementationIDSpace,	kEndInsertElementHandlerImpl,		kInCopyWorkflowPrefix + 82)
DECLARE_PMID(kImplementationIDSpace,	kClearStoryMetaDataRefCmdImpl, 		kInCopyWorkflowPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, 	kTaggedInlineElementHandlerImpl, 	kInCopyWorkflowPrefix + 84)
DECLARE_PMID(kImplementationIDSpace,	kMoveStoryMetaDataCmdImpl, 			kInCopyWorkflowPrefix + 85)
//gap
DECLARE_PMID(kImplementationIDSpace,	kInCopySaveDocResponderImpl, 				kInCopyWorkflowPrefix + 88)
DECLARE_PMID(kImplementationIDSpace,	kXMPElementHandlerImpl, 		kInCopyWorkflowPrefix + 89)
DECLARE_PMID(kImplementationIDSpace,	kInCopyDocumentHandlerImpl, 	kInCopyWorkflowPrefix + 90)
DECLARE_PMID(kImplementationIDSpace,	kInCopyDocumentHandlerDataImpl, kInCopyWorkflowPrefix + 91)
DECLARE_PMID(kImplementationIDSpace,	kSwatchMapperImpl,		 		kInCopyWorkflowPrefix + 92)
DECLARE_PMID(kImplementationIDSpace,	kInkListElementHandlerImpl, 	kInCopyWorkflowPrefix + 93)
//gap
DECLARE_PMID(kImplementationIDSpace,	kTableContextMEImpl_Obsolete,	kInCopyWorkflowPrefix + 95)
DECLARE_PMID(kImplementationIDSpace,	kICExportLayerStoriesImpl,		kInCopyWorkflowPrefix + 96)
DECLARE_PMID(kImplementationIDSpace,	kICExportAllSuiteImpl,			kInCopyWorkflowPrefix + 97)
DECLARE_PMID(kImplementationIDSpace,	kICExportAllStoriesSuiteImpl,	kInCopyWorkflowPrefix + 98)
DECLARE_PMID(kImplementationIDSpace,	kICExportAllGraphicsSuiteImpl,	kInCopyWorkflowPrefix + 99)
//gap
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueUIDImpl,			kInCopyWorkflowPrefix + 200)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueBoolImpl,		kInCopyWorkflowPrefix + 201)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueLeadModImpl,		kInCopyWorkflowPrefix + 202)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueInt16Impl,		kInCopyWorkflowPrefix + 203)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueAltGlyphStImpl,	kInCopyWorkflowPrefix + 204)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueGlyphFormImpl,	kInCopyWorkflowPrefix + 205)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueAlignImpl,		kInCopyWorkflowPrefix + 206)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueRealImpl,		kInCopyWorkflowPrefix + 207)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueGridAlignImpl,	kInCopyWorkflowPrefix + 208)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueFontImpl,		kInCopyWorkflowPrefix + 209)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueRubyOHangImpl,	kInCopyWorkflowPrefix + 210)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueRubyAParImpl,	kInCopyWorkflowPrefix + 211)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueRubyAlignImpl,	kInCopyWorkflowPrefix + 212)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueWStrImpl,		kInCopyWorkflowPrefix + 213)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueKinsoHngImpl,	kInCopyWorkflowPrefix + 214)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueKinsoImpl,		kInCopyWorkflowPrefix + 215)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueBrkBfrImpl,		kInCopyWorkflowPrefix + 216)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueRubySpecGlyphImpl,	kInCopyWorkflowPrefix + 217)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueParaRuleImpl,	kInCopyWorkflowPrefix + 218)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValuePointImpl,		kInCopyWorkflowPrefix + 219)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueInt32Impl,		kInCopyWorkflowPrefix + 220)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueCharHangImpl,	kInCopyWorkflowPrefix + 221)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValuePosModeImpl,		kInCopyWorkflowPrefix + 222)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueFigStyImpl,		kInCopyWorkflowPrefix + 223)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueULineImpl,		kInCopyWorkflowPrefix + 224)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTabsImpl,		kInCopyWorkflowPrefix + 225)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueHypModeImpl,		kInCopyWorkflowPrefix + 226)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueCapModeImpl,		kInCopyWorkflowPrefix + 227)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueClassIDImpl,		kInCopyWorkflowPrefix + 228)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueDataPosImpl,		kInCopyWorkflowPrefix + 229)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTInt32Impl,		kInCopyWorkflowPrefix + 230)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTRealImpl,		kInCopyWorkflowPrefix + 231)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTInt16Impl,		kInCopyWorkflowPrefix + 232)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTUIDImpl,		kInCopyWorkflowPrefix + 233)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTLineTypeImpl,	kInCopyWorkflowPrefix + 234)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTGradImpl,		kInCopyWorkflowPrefix + 235)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueTClassIDImpl,	kInCopyWorkflowPrefix + 236)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueStrokeTypeIDImpl,kInCopyWorkflowPrefix + 237)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueRunInStylesImpl,	kInCopyWorkflowPrefix + 238)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueOTFeatureListImpl,	kInCopyWorkflowPrefix + 239)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueBalanceLineImpl,	kInCopyWorkflowPrefix + 240)

DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueParagraphDirImpl,kInCopyWorkflowPrefix + 241)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueJustifMethodImpl,kInCopyWorkflowPrefix + 242)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueKashidaImpl,		kInCopyWorkflowPrefix + 243)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueDigitsImpl,		kInCopyWorkflowPrefix + 244)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueDiacVPosImpl,	kInCopyWorkflowPrefix + 245)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueDirOverrideImpl,	kInCopyWorkflowPrefix + 246)
DECLARE_PMID(kImplementationIDSpace,	kInCopyXMLValueKbdDirOverrideImpl,	kInCopyWorkflowPrefix + 247)

DECLARE_PMID(kImplementationIDSpace, kInCopyXMLValueProviderHyphStyleImpl, kInCopyWorkflowPrefix + 248)

DECLARE_PMID(kMessageIDSpace,	kInCopyExportNotifyMsg, 			kInCopyWorkflowPrefix + 1)

//gap
DECLARE_PMID(kServiceIDSpace,	kInCopyXMLHandlerService, 			kInCopyWorkflowPrefix + 2)

END_IDS()

#endif // __InCopyWorkflowID__
