//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/XMLParserID.h $
//  
//  Owner: Lonnie Millett
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
//  Info:	Contains IDs used by the XMLParser plugin for access to AXE.
//  
//========================================================================================

#ifndef __XMLParserID__
#define __XMLParserID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kXMLParserPrefix	 RezLong(0x17C00)
#define kXMLParserPrefix2	 RezLong(0x10F00)
#define kXMLParserPrefix3	 RezLong(0x19300)
#define kXMLParserPrefix4	 RezLong(0x19400)

// PluginID
#define kXMLParserPluginName 					"XMLParser"
DECLARE_PMID(kPlugInIDSpace, kXMLParserPluginID, kXMLParserPrefix + 1)

// <Start IDC>

// <Class ID>
DECLARE_PMID(kClassIDSpace, kXMLParserServiceBoss, kXMLParserPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSAXAttributesBoss, kXMLParserPrefix + 2)
DECLARE_PMID(kClassIDSpace, kXMLParserErrorStringServiceBoss, kXMLParserPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSAXLocatorBoss, kXMLParserPrefix + 4)
DECLARE_PMID(kClassIDSpace, kXMLParserLocatorBoss, kXMLParserPrefix + 5)
DECLARE_PMID(kClassIDSpace, kXMLEmptyEntityResolverBoss, kXMLParserPrefix + 6)
DECLARE_PMID(kClassIDSpace, kXMLEntityResolverBoss, kXMLParserPrefix + 7)
DECLARE_PMID(kClassIDSpace, kNewlineStreamBoss, kXMLParserPrefix + 8)
DECLARE_PMID(kClassIDSpace, kXSLEntityResolverBoss, kXMLParserPrefix + 9)
DECLARE_PMID(kClassIDSpace, kXSLTransformServiceBoss, kXMLParserPrefix + 10)
DECLARE_PMID(kClassIDSpace, kXMLDOMSerializerServiceBoss, kXMLParserPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSAXAttributeListBoss, kXMLParserPrefix + 12)
DECLARE_PMID(kClassIDSpace, kXSLTransformBoss, kXMLParserPrefix + 13)
DECLARE_PMID(kClassIDSpace, kDOMParserServiceBoss, kXMLParserPrefix + 14)
DECLARE_PMID(kClassIDSpace, kXMLDOMHandlerBoss, kXMLParserPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSAXContentHandlerBoss, kXMLParserPrefix + 16)
DECLARE_PMID(kClassIDSpace, kXSLPIContentHandlerBoss, kXMLParserPrefix + 17)
DECLARE_PMID(kClassIDSpace, kXSLParamContentHandlerBoss, kXMLParserPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLParserPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLParserPrefix + 20)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXSERVICES, kXMLParserPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXCONTENTHANDLER, kXMLParserPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXATTRIBUTES, kXMLParserPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXPARSEROPTIONS, kXMLParserPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXLOCATOR, kXMLParserPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXENTITYRESOLVER, kXMLParserPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXDTDHANDLER, kXMLParserPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXDOMSERIALIZERHANDLER, kXMLParserPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDTDTOKENHANDLER, kXMLParserPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPARSINGCONTEXT, kXMLParserPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMATIONSERVICES, kXMLParserPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSERVICESERROR, kXMLParserPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPARSERUTILS, kXMLParserPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXDOMSERIALIZERSERVICES, kXMLParserPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXATTRIBUTELIST, kXMLParserPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPARSERPRIVATEUTILS, kXMLParserPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IXSLSERVICES, kXMLParserPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IXSLENABLER, kXMLParserPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMSERVICES, kXMLParserPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXCONTENTHANDLERIMPLDATA, kXMLParserPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLParserPrefix + 21)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kXMLParserService, kXMLParserPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kXMLDOMSerializerService, kXMLParserPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kXSLTransformService, kXMLParserPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kXSLEnablerService, kXMLParserPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kDOMParserService, kXMLParserPrefix + 5)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLParserPrefix + 5)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLParserPrefix + 6)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLParserPrefix + 7)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLParserPrefix + 8)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLParserPrefix + 9)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLParserPrefix + 10)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kXMLParserServiceImpl, kXMLParserPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSAXServicesImpl, kXMLParserPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXMLParserErrorStringServiceImpl, kXMLParserPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSAXAttributesImpl, kXMLParserPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSAXParserOptionsImpl, kXMLParserPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSAXLocatorImpl, kXMLParserPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kNewlineStreamImpl, kXMLParserPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kXMLParsingContextImpl, kXMLParserPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kXMLEmptyEntityResolverImpl, kXMLParserPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kXMLEntityResolverImpl, kXMLParserPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kXMLServicesErrorImpl, kXMLParserPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kXSLEntityResolverImpl, kXMLParserPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kXSLTransformImpl, kXMLParserPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kXSLServiceImpl, kXMLParserPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kXMLParserUtilsImpl, kXMLParserPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSAXDOMSerializerServicesImpl, kXMLParserPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kXMLDOMSerializerServiceImpl, kXMLParserPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSAXAttributeListImpl, kXMLParserPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kXMLParserPrivateUtilsImpl, kXMLParserPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kXSLServicesImpl, kXMLParserPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kXSLServiceProviderImpl, kXMLParserPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kXSLEnablerImpl, kXMLParserPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kXSLEnablerServiceImpl, kXMLParserPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kDOMServicesImpl, kXMLParserPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kDOMParserServiceImpl, kXMLParserPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kXMLDOMHandlerImpl, kXMLParserPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSAXContentHandlerImpl, kXMLParserPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kSAXContentHandlerImplData, kXMLParserPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kXSLPIContentHandlerImpl, kXMLParserPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kXSLParamContentHandlerImpl, kXMLParserPrefix + 31)

// <Error ID>

// -- AXE Parser errors
// -- The initial range of errors map directly to the errors reported by the AXE parser
// -- and therefore MUST be reserved and not modified

// -- Warnings: Generally for DTD validation

DECLARE_PMID(kErrorIDSpace, kXMLParserErr_W_LowBounds, kXMLParserPrefix + 1)				// kAXEParserErr_W_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NotationAlreadyExists, kXMLParserPrefix + 2)	// kAXEParserErr_NotationAlreadyExists
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AttListAlreadyExists, kXMLParserPrefix + 3)		// kAXEParserErr_AttListAlreadyExists
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ContradictoryEncoding, kXMLParserPrefix + 4)	// kAXEParserErr_ContradictoryEncoding
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UndeclaredElemInCM, kXMLParserPrefix + 5)		// kAXEParserErr_UndeclaredElemInCM
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UndeclaredElemInAttList, kXMLParserPrefix + 6)	// kAXEParserErr_UndeclaredElemInAttList
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_W_HighBounds, kXMLParserPrefix + 7)				// kAXEParserErr_W_HighBounds

// -- Errors & Fatal Errors

DECLARE_PMID(kErrorIDSpace, kXMLParserErr_E_LowBounds, kXMLParserPrefix + 8)				// kAXEParserErr_E_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedCommentOrCDATA, kXMLParserPrefix + 9)	// kAXEParserErr_ExpectedCommentOrCDATA
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedAttrName, kXMLParserPrefix + 10)		// kAXEParserErr_ExpectedAttrName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedNotationName, kXMLParserPrefix + 11)	// kAXEParserErr_ExpectedNotationName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoRepInMixed, kXMLParserPrefix + 12)			// kAXEParserErr_NoRepInMixed
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadDefAttrDecl, kXMLParserPrefix + 13)			// kAXEParserErr_BadDefAttrDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedDefAttrDecl, kXMLParserPrefix + 14)		// kAXEParserErr_ExpectedDefAttrDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AttListSyntaxError, kXMLParserPrefix + 15)		// kAXEParserErr_AttListSyntaxError
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEqSign, kXMLParserPrefix + 16)			// kAXEParserErr_ExpectedEqSign
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_DupAttrName, kXMLParserPrefix + 17)				// kAXEParserErr_DupAttrName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadIdForXMLLangAttr, kXMLParserPrefix + 18)		// kAXEParserErr_BadIdForXMLLangAttr
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedElementName, kXMLParserPrefix + 19)		// kAXEParserErr_ExpectedElementName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_MustStartWithXMLDecl, kXMLParserPrefix + 20)	// kAXEParserErr_MustStartWithXMLDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_CommentsMustStartWith, kXMLParserPrefix + 21)	// kAXEParserErr_CommentsMustStartWith
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidDocumentStructure, kXMLParserPrefix + 22)	// kAXEParserErr_InvalidDocumentStructure
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedDeclString, kXMLParserPrefix + 23)		// kAXEParserErr_ExpectedDeclString
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadXMLVersion, kXMLParserPrefix + 24)			// kAXEParserErr_BadXMLVersion
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnsupportedXMLVersion, kXMLParserPrefix + 25)	// kAXEParserErr_UnsupportedXMLVersion
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedXMLDecl, kXMLParserPrefix + 26)		// kAXEParserErr_UnterminatedXMLDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadXMLEncoding, kXMLParserPrefix + 27)			// kAXEParserErr_BadXMLEncoding
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadStandalone, kXMLParserPrefix + 28)			// kAXEParserErr_BadStandalone
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedComment, kXMLParserPrefix + 29)		// kAXEParserErr_UnterminatedComment
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PINameExpected, kXMLParserPrefix + 30)			// kAXEParserErr_PINameExpected
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedPI, kXMLParserPrefix + 31)			// kAXEParserErr_UnterminatedPI
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidCharacter, kXMLParserPrefix + 32)		// kAXEParserErr_InvalidCharacter
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnexpectedTextBeforeRoot, kXMLParserPrefix + 33)	// kAXEParserErr_UnexpectedTextBeforeRoot
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedStartTag, kXMLParserPrefix + 34)	// kAXEParserErr_UnterminatedStartTag
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedAttrValue, kXMLParserPrefix + 35)		// kAXEParserErr_ExpectedAttrValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedEndTag, kXMLParserPrefix + 36)		// kAXEParserErr_UnterminatedEndTag
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedAttributeType, kXMLParserPrefix + 37)	// kAXEParserErr_ExpectedAttributeType
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEndOfTagX, kXMLParserPrefix + 38)		// kAXEParserErr_ExpectedEndOfTagX
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedMarkup, kXMLParserPrefix + 39)			// kAXEParserErr_ExpectedMarkup
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NotValidAfterContent, kXMLParserPrefix + 40)	// kAXEParserErr_NotValidAfterContent
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedComment, kXMLParserPrefix + 41)			// kAXEParserErr_ExpectedComment
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedCommentOrPI, kXMLParserPrefix + 42)		// kAXEParserErr_ExpectedCommentOrPI
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedWhitespace, kXMLParserPrefix + 43)		// kAXEParserErr_ExpectedWhitespace
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoRootElemInDOCTYPE, kXMLParserPrefix + 44)		// kAXEParserErr_NoRootElemInDOCTYPE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedQuotedString, kXMLParserPrefix + 45)	// kAXEParserErr_ExpectedQuotedString
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedPublicId, kXMLParserPrefix + 46)		// kAXEParserErr_ExpectedPublicId
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidPublicIdChar, kXMLParserPrefix + 47)		// kAXEParserErr_InvalidPublicIdChar
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedDOCTYPE, kXMLParserPrefix + 48)		// kAXEParserErr_UnterminatedDOCTYPE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidCharacterInIntSubset, kXMLParserPrefix + 49)	// kAXEParserErr_InvalidCharacterInIntSubset
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedCDATA, kXMLParserPrefix + 50)			// kAXEParserErr_ExpectedCDATA
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidInitialNameChar, kXMLParserPrefix + 51)	// kAXEParserErr_InvalidInitialNameChar
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidNameChar, kXMLParserPrefix + 52)			// kAXEParserErr_InvalidNameChar
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnexpectedWhitespace, kXMLParserPrefix + 53)	// kAXEParserErr_UnexpectedWhitespace
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidCharacterInAttrValue, kXMLParserPrefix + 54)	// kAXEParserErr_InvalidCharacterInAttrValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedMarkupDecl, kXMLParserPrefix + 55)		// kAXEParserErr_ExpectedMarkupDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_TextDeclNotLegalHere, kXMLParserPrefix + 56)	// kAXEParserErr_TextDeclNotLegalHere
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ConditionalSectInIntSubset, kXMLParserPrefix + 57)	// kAXEParserErr_ConditionalSectInIntSubset
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedPEName, kXMLParserPrefix + 58)			// kAXEParserErr_ExpectedPEName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedEntityDecl, kXMLParserPrefix + 59)	// kAXEParserErr_UnterminatedEntityDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidCharacterRef, kXMLParserPrefix + 60)		// kAXEParserErr_InvalidCharacterRef
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedCharRef, kXMLParserPrefix + 61)		// kAXEParserErr_UnterminatedCharRef
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEntityRefName, kXMLParserPrefix + 62)	// kAXEParserErr_ExpectedEntityRefName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_EntityNotFound, kXMLParserPrefix + 63)			// kAXEParserErr_EntityNotFound
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoUnparsedEntityRefs, kXMLParserPrefix + 64)	// kAXEParserErr_NoUnparsedEntityRefs
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedEntityRef, kXMLParserPrefix + 65)	// kAXEParserErr_UnterminatedEntityRef
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_RecursiveEntity, kXMLParserPrefix + 66)			// kAXEParserErr_RecursiveEntity
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PartialMarkupInEntity, kXMLParserPrefix + 67)	// kAXEParserErr_PartialMarkupInEntity
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedElementDecl, kXMLParserPrefix + 68)	// kAXEParserErr_UnterminatedElementDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedContentSpecExpr, kXMLParserPrefix + 69)	// kAXEParserErr_ExpectedContentSpecExpr
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedAsterisk, kXMLParserPrefix + 70)		// kAXEParserErr_ExpectedAsterisk
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedContentModel, kXMLParserPrefix + 71)	// kAXEParserErr_UnterminatedContentModel
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedSystemId, kXMLParserPrefix + 72)		// kAXEParserErr_ExpectedSystemId
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedSystemOrPublicId, kXMLParserPrefix + 73)	// kAXEParserErr_ExpectedSystemOrPublicId
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedNotationDecl, kXMLParserPrefix + 74)	// kAXEParserErr_UnterminatedNotationDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedSeqChoiceLeaf, kXMLParserPrefix + 75)	// kAXEParserErr_ExpectedSeqChoiceLeaf
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedChoiceOrCloseParen, kXMLParserPrefix + 76)	// kAXEParserErr_ExpectedChoiceOrCloseParen
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedSeqOrCloseParen, kXMLParserPrefix + 77)	// kAXEParserErr_ExpectedSeqOrCloseParen
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEnumValue, kXMLParserPrefix + 78)		// kAXEParserErr_ExpectedEnumValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEnumSepOrParen, kXMLParserPrefix + 79)	// kAXEParserErr_ExpectedEnumSepOrParen
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedEntityLiteral, kXMLParserPrefix + 80)	// kAXEParserErr_UnterminatedEntityLiteral
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_MoreEndThanStartTags, kXMLParserPrefix + 81)	// kAXEParserErr_MoreEndThanStartTags
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_IllegalRefInStandalone, kXMLParserPrefix + 82)	// kAXEParserErr_IllegalRefInStandalone
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedOpenParen, kXMLParserPrefix + 83)		// kAXEParserErr_ExpectedOpenParen
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AttrAlreadyUsedInSTag, kXMLParserPrefix + 84)	// kAXEParserErr_AttrAlreadyUsedInSTag
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BracketInAttrValue, kXMLParserPrefix + 85)		// kAXEParserErr_BracketInAttrValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_Expected2ndSurrogateChar, kXMLParserPrefix + 86)	// kAXEParserErr_Expected2ndSurrogateChar
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEndOfConditional, kXMLParserPrefix + 87)	// kAXEParserErr_ExpectedEndOfConditional
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedIncOrIgn, kXMLParserPrefix + 88)		// kAXEParserErr_ExpectedIncOrIgn
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedINCLUDEBracket, kXMLParserPrefix + 89)	// kAXEParserErr_ExpectedINCLUDEBracket
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedTextDecl, kXMLParserPrefix + 90)		// kAXEParserErr_ExpectedTextDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedXMLDecl, kXMLParserPrefix + 91)			// kAXEParserErr_ExpectedXMLDecl
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnexpectedEOE, kXMLParserPrefix + 92)			// kAXEParserErr_UnexpectedEOE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PEPropogated, kXMLParserPrefix + 93)			// kAXEParserErr_PEPropogated
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExtraCloseSquare, kXMLParserPrefix + 94)		// kAXEParserErr_ExtraCloseSquare
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PERefInMarkupInIntSubset, kXMLParserPrefix + 95)	// kAXEParserErr_PERefInMarkupInIntSubset
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_EntityPropogated, kXMLParserPrefix + 96)		// kAXEParserErr_EntityPropogated
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedNumericalCharRef, kXMLParserPrefix + 97)	// kAXEParserErr_ExpectedNumericalCharRef
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedOpenSquareBracket, kXMLParserPrefix + 98)	// kAXEParserErr_ExpectedOpenSquareBracket
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadSequenceInCharData, kXMLParserPrefix + 99)	// kAXEParserErr_BadSequenceInCharData
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_IllegalSequenceInComment, kXMLParserPrefix + 100)	// kAXEParserErr_IllegalSequenceInComment
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnterminatedCDATASection, kXMLParserPrefix + 101)	// kAXEParserErr_UnterminatedCDATASection
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedNDATA, kXMLParserPrefix + 102)			// kAXEParserErr_ExpectedNDATA
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NDATANotValidForPE, kXMLParserPrefix + 103)		// kAXEParserErr_NDATANotValidForPE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_HexRadixMustBeLowerCase, kXMLParserPrefix + 104)	// kAXEParserErr_HexRadixMustBeLowerCase
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_DeclStringRep, kXMLParserPrefix + 105)			// kAXEParserErr_DeclStringRep
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_DeclStringsInWrongOrder, kXMLParserPrefix + 106)	// kAXEParserErr_DeclStringsInWrongOrder
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoExtRefsInAttValue, kXMLParserPrefix + 107)	// kAXEParserErr_NoExtRefsInAttValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_XMLDeclMustBeLowerCase, kXMLParserPrefix + 108)	// kAXEParserErr_XMLDeclMustBeLowerCase
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ExpectedEntityValue, kXMLParserPrefix + 109)	// kAXEParserErr_ExpectedEntityValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadDigitForRadix, kXMLParserPrefix + 110)		// kAXEParserErr_BadDigitForRadix
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_EndedWithTagsOnStack, kXMLParserPrefix + 111)	// kAXEParserErr_EndedWithTagsOnStack
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AmbiguousContentModel, kXMLParserPrefix + 112)	// kAXEParserErr_AmbiguousContentModel
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NestedCDATA, kXMLParserPrefix + 113)			// kAXEParserErr_NestedCDATA
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnknownPrefix, kXMLParserPrefix + 114)			// kAXEParserErr_UnknownPrefix
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PartialTagMarkupError, kXMLParserPrefix + 115)	// kAXEParserErr_PartialTagMarkupError
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_EmptyMainEntity, kXMLParserPrefix + 116)		// kAXEParserErr_EmptyMainEntity
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_CDATAOutsideOfContent, kXMLParserPrefix + 117)	// kAXEParserErr_CDATAOutsideOfContent
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_OnlyCharRefsAllowedHere, kXMLParserPrefix + 118)	// kAXEParserErr_OnlyCharRefsAllowedHere
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_Unexpected2ndSurrogateChar, kXMLParserPrefix + 119)	// kAXEParserErr_Unexpected2ndSurrogateChar
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoPIStartsWithXML, kXMLParserPrefix + 120)		// kAXEParserErr_NoPIStartsWithXML
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_XMLDeclMustBeFirst, kXMLParserPrefix + 121)		// kAXEParserErr_XMLDeclMustBeFirst
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_XMLVersionRequired, kXMLParserPrefix + 122)		// kAXEParserErr_XMLVersionRequired
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_StandaloneNotLegal, kXMLParserPrefix + 123)		// kAXEParserErr_StandaloneNotLegal
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_TooManyColonsInName, kXMLParserPrefix + 124)	// kAXEParserErr_TooManyColonsInName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidColonPos, kXMLParserPrefix + 125)		// kAXEParserErr_InvalidColonPos
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ColonNotLegalWithNS, kXMLParserPrefix + 126)	// kAXEParserErr_ColonNotLegalWithNS
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_SysException, kXMLParserPrefix + 127)			// kAXEParserErr_SysException
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_XMLException, kXMLParserPrefix + 128)			// kAXEParserErr_XMLException
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnexpectedEOF, kXMLParserPrefix + 129)			// kAXEParserErr_UnexpectedEOF
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_E_HighBounds, kXMLParserPrefix + 130)			// kAXEParserErr_E_HighBounds
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_V_LowBounds, kXMLParserPrefix + 131)			// kAXEParserErr_V_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ElementNotDefined, kXMLParserPrefix + 132)		// kAXEParserErr_ElementNotDefined
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AttNotDefined, kXMLParserPrefix + 133)			// kAXEParserErr_AttNotDefined
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NotationNotDeclared, kXMLParserPrefix + 134)	// kAXEParserErr_NotationNotDeclared
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_RootElemNotLikeDocType, kXMLParserPrefix + 135)	// kAXEParserErr_RootElemNotLikeDocType
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_RequiredAttrNotProvided, kXMLParserPrefix + 136)	// kAXEParserErr_RequiredAttrNotProvided
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ElementNotValidForContent, kXMLParserPrefix + 137)	// kAXEParserErr_ElementNotValidForContent
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadIDAttrDefType, kXMLParserPrefix + 138)		// kAXEParserErr_BadIDAttrDefType
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_InvalidEmptyAttValue, kXMLParserPrefix + 139)	// kAXEParserErr_InvalidEmptyAttValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ElementAlreadyExists, kXMLParserPrefix + 140)	// kAXEParserErr_ElementAlreadyExists
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_MultipleIdAttrs, kXMLParserPrefix + 141)			// kAXEParserErr_MultipleIdAttrs
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ReusedIDValue, kXMLParserPrefix + 142)			// kAXEParserErr_ReusedIDValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_IDNotDeclared, kXMLParserPrefix + 143)			// kAXEParserErr_IDNotDeclared
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnknownNotRefAttr, kXMLParserPrefix + 144)		// kAXEParserErr_UnknownNotRefAttr
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UndeclaredElemInDocType, kXMLParserPrefix + 145)	// kAXEParserErr_UndeclaredElemInDocType
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_EmptyNotValidForContent, kXMLParserPrefix + 146)	// kAXEParserErr_EmptyNotValidForContent
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AttNotDefinedForElement, kXMLParserPrefix + 147)	// kAXEParserErr_AttNotDefinedForElement
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BadEntityRefAttr, kXMLParserPrefix + 148)		// kAXEParserErr_BadEntityRefAttr
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UnknownEntityRefAttr, kXMLParserPrefix + 149)	// kAXEParserErr_UnknownEntityRefAttr
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NotEnoughElemsForCM, kXMLParserPrefix + 150)	// kAXEParserErr_NotEnoughElemsForCM
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoCharDataInCM, kXMLParserPrefix + 151)			// kAXEParserErr_NoCharDataInCM
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_DoesNotMatchEnumList, kXMLParserPrefix + 152)	// kAXEParserErr_DoesNotMatchEnumList
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_AttrValNotName, kXMLParserPrefix + 153)			// kAXEParserErr_AttrValNotName
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NoMultipleValues, kXMLParserPrefix + 154)		// kAXEParserErr_NoMultipleValues
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NotSameAsFixedValue, kXMLParserPrefix + 155)		// kAXEParserErr_NotSameAsFixedValue
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_RepElemInMixed, kXMLParserPrefix + 156)			// kAXEParserErr_RepElemInMixed
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_V_HighBounds, kXMLParserPrefix + 157)			// kAXEParserErr_V_HighBounds

// -- This range errors maps to the general parser error section of AXE.  These errors start
// -- with 1000 and potentially end with 1999.  For now we are mapping them between 160 and 199.
// -- This mapping is handled in SAXErrorHandler::GetIDErrorInfo.
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_GE_LowBounds, kXMLParserPrefix + 160)			// kAXEParserErr_GE_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NO_MEMORY, kXMLParserPrefix + 161)			// kAXEParserErr_NO_MEMORY
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_SYNTAX, kXMLParserPrefix + 162)			// kAXEParserErr_SYNTAX
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NO_ELEMENTS, kXMLParserPrefix + 163)			// kAXEParserErr_NO_ELEMENTS
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_INVALID_TOKEN, kXMLParserPrefix + 164)			// kAXEParserErr_INVALID_TOKEN
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNCLOSED_TOKEN, kXMLParserPrefix + 165)			// kAXEParserErr_UNCLOSED_TOKEN
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PARTIAL_CHAR, kXMLParserPrefix + 166)			// kAXEParserErr_PARTIAL_CHAR
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_TAG_MISMATCH, kXMLParserPrefix + 167)			// kAXEParserErr_TAG_MISMATCH
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_DUPLICATE_ATTRIBUTE, kXMLParserPrefix + 168)			// kAXEParserErr_DUPLICATE_ATTRIBUTE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_JUNK_AFTER_DOC_ELEMENT, kXMLParserPrefix + 169)			// kAXEParserErr_JUNK_AFTER_DOC_ELEMENT
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_PARAM_ENTITY_REF, kXMLParserPrefix + 170)			// kAXEParserErr_PARAM_ENTITY_REF
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNDEFINED_ENTITY, kXMLParserPrefix + 171)			// kAXEParserErr_UNDEFINED_ENTITY
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_RECURSIVE_ENTITY_REF, kXMLParserPrefix + 172)			// kAXEParserErr_RECURSIVE_ENTITY_REF
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ASYNC_ENTITY, kXMLParserPrefix + 173)			// kAXEParserErr_ASYNC_ENTITY
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BAD_CHAR_REF, kXMLParserPrefix + 174)			// kAXEParserErr_BAD_CHAR_REF
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_BINARY_ENTITY_REF, kXMLParserPrefix + 175)			// kAXEParserErr_BINARY_ENTITY_REF
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ATTRIBUTE_EXTERNAL_ENTITY_REF, kXMLParserPrefix + 176)			// kAXEParserErr_ATTRIBUTE_EXTERNAL_ENTITY_REF
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_MISPLACED_XML_PI, kXMLParserPrefix + 177)			// kAXEParserErr_MISPLACED_XML_PI
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNKNOWN_ENCODING, kXMLParserPrefix + 178)			// kAXEParserErr_UNKNOWN_ENCODING
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_INCORRECT_ENCODING, kXMLParserPrefix + 179)			// kAXEParserErr_INCORRECT_ENCODING
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNCLOSED_CDATA_SECTION, kXMLParserPrefix + 180)			// kAXEParserErr_UNCLOSED_CDATA_SECTION
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_EXTERNAL_ENTITY_HANDLING, kXMLParserPrefix + 181)			// kAXEParserErr_EXTERNAL_ENTITY_HANDLING
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NOT_STANDALONE, kXMLParserPrefix + 182)			// kAXEParserErr_NOT_STANDALONE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNEXPECTED_STATE, kXMLParserPrefix + 183)			// kAXEParserErr_UNEXPECTED_STATE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_ENTITY_DECLARED_IN_PE, kXMLParserPrefix + 184)			// kAXEParserErr_ENTITY_DECLARED_IN_PE
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_FEATURE_REQUIRES_XML_DTD, kXMLParserPrefix + 185)			// kAXEParserErr_FEATURE_REQUIRES_XML_DTD
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_CANT_CHANGE_FEATURE_ONCE_PARSING, kXMLParserPrefix + 186)			// kAXEParserErr_CANT_CHANGE_FEATURE_ONCE_PARSING
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNEXPECTED_DOCTYPE_NAME, kXMLParserPrefix + 187)			// kAXEParserErr_UNEXPECTED_DOCTYPE_NAME
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_USER_HANDLER_ABORT, kXMLParserPrefix + 188)			// kAXEParserErr_USER_HANDLER_ABORT
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_UNBOUND_PREFIX, kXMLParserPrefix + 189)			// kAXEParserErr_UNBOUND_PREFIX
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NUM_GENERIC_ERROR_MESSAGES, kXMLParserPrefix + 190)			// kAXEParserErr_NUM_GENERIC_ERROR_MESSAGES
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 191)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 192)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 193)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 194)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 195)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 196)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 197)			// kAXEFutureErr
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix + 198)			// kAXEFutureErr
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_GE_HighBounds, kXMLParserPrefix + 199)			// kAXEParserErr_GE_HighBounds

// -- This range errors maps to the extended error section of AXE.  These errors start with 2000
// -- and potentially end with 2999.  For now we are mapping them between 200 and 254.  This
// -- mapping is handled in SAXErrorHandler::GetIDErrorInfo.
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_X_LowBounds, kXMLParserPrefix + 200)			// kAXEParserErr_X_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_CaseMismatch, kXMLParserPrefix + 201)			// kAXEParserErr_CaseMismatch
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_NUM_X_PARSER_ERRORS, kXMLParserPrefix + 202)	// kAXEParserErr_NUM_X_PARSER_ERRORS
DECLARE_PMID(kErrorIDSpace, kXMLParserErr_X_HighBounds, kXMLParserPrefix + 254)			// kAXEParserErr_X_HighBounds

// -- AXE System errors
// -- The initial range of errors map directly to the errors reported by the AXE system
// -- and therefore MUST be reserved and not modified.  These are based off of XMLPrefix2

DECLARE_PMID(kErrorIDSpace, kXMLSystemErr__E_LowBounds, kXMLParserPrefix2 + 1)				// kAXESystemErr__E_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Array_BadIndex, kXMLParserPrefix2 + 2)				// kAXESystemErr_Array_BadIndex
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Array_BadNewSize, kXMLParserPrefix2 + 3)			// kAXESystemErr_Array_BadNewSize
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_AttrList_BadIndex, kXMLParserPrefix2 + 4)			// kAXESystemErr_AttrList_BadIndex
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_AttDef_BadAttType, kXMLParserPrefix2 + 5)			// kAXESystemErr_AttDef_BadAttType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_AttDef_BadDefAttType, kXMLParserPrefix2 + 6)		// kAXESystemErr_AttDef_BadDefAttType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Bitset_BadIndex, kXMLParserPrefix2 + 7)				// kAXESystemErr_Bitset_BadIndex
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_BufMgr_NoMoreBuffers, kXMLParserPrefix2 + 8)		// kAXESystemErr_BufMgr_NoMoreBuffers
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_BufMgr_BufferNotInPool, kXMLParserPrefix2 + 9)		// kAXESystemErr_BufMgr_BufferNotInPool
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CPtr_PointerIsZero, kXMLParserPrefix2 + 10)			// kAXESystemErr_CPtr_PointerIsZero
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_BinOpHadUnaryType, kXMLParserPrefix2 + 11)		// kAXESystemErr_CM_BinOpHadUnaryType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_MustBeMixedOrChildren, kXMLParserPrefix2 + 12)	// kAXESystemErr_CM_MustBeMixedOrChildren
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_NoPCDATAHere, kXMLParserPrefix2 + 13)			// kAXESystemErr_CM_NoPCDATAHere
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_NotValidForSpecType, kXMLParserPrefix2 + 14)		// kAXESystemErr_CM_NotValidForSpecType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_UnaryOpHadBinType, kXMLParserPrefix2 + 15)		// kAXESystemErr_CM_UnaryOpHadBinType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_UnknownCMType, kXMLParserPrefix2 + 16)			// kAXESystemErr_CM_UnknownCMType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_UnknownCMSpecType, kXMLParserPrefix2 + 17)		// kAXESystemErr_CM_UnknownCMSpecType
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_CM_NoParentCSN, kXMLParserPrefix2 + 18)				// kAXESystemErr_CM_NoParentCSN
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_DTD_UnknownCreateReason, kXMLParserPrefix2 + 19)	// kAXESystemErr_DTD_UnknownCreateReason
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_ElemStack_EmptyStack, kXMLParserPrefix2 + 20)		// kAXESystemErr_ElemStack_EmptyStack
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_ElemStack_BadIndex, kXMLParserPrefix2 + 21)			// kAXESystemErr_ElemStack_BadIndex
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_ElemStack_StackUnderflow, kXMLParserPrefix2 + 22)	// kAXESystemErr_ElemStack_StackUnderflow
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_ElemStack_NoParentPushed, kXMLParserPrefix2 + 23)	// kAXESystemErr_ElemStack_NoParentPushed
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Enum_NoMoreElements, kXMLParserPrefix2 + 24)		// kAXESystemErr_Enum_NoMoreElements
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotOpenFile, kXMLParserPrefix2 + 25)		// kAXESystemErr_File_CouldNotOpenFile
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotGetCurPos, kXMLParserPrefix2 + 26)		// kAXESystemErr_File_CouldNotGetCurPos
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotCloseFile, kXMLParserPrefix2 + 27)		// kAXESystemErr_File_CouldNotCloseFile
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotSeekToEnd, kXMLParserPrefix2 + 28)		// kAXESystemErr_File_CouldNotSeekToEnd
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotSeekToPos, kXMLParserPrefix2 + 29)		// kAXESystemErr_File_CouldNotSeekToPos
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotDupHandle, kXMLParserPrefix2 + 30)		// kAXESystemErr_File_CouldNotDupHandle
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotReadFromFile, kXMLParserPrefix2 + 31)	// kAXESystemErr_File_CouldNotReadFromFile
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotResetFile, kXMLParserPrefix2 + 32)		// kAXESystemErr_File_CouldNotResetFile
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotGetSize, kXMLParserPrefix2 + 33)		// kAXESystemErr_File_CouldNotGetSize
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_CouldNotGetBasePathName, kXMLParserPrefix2 + 34)	// kAXESystemErr_File_CouldNotGetBasePathName
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_File_BasePathUnderflow, kXMLParserPrefix2 + 35)		// kAXESystemErr_File_BasePathUnderflow
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Gen_ParseInProgress, kXMLParserPrefix2 + 36)		// kAXESystemErr_Gen_ParseInProgress
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Gen_NoDTDValidator, kXMLParserPrefix2 + 37)			// kAXESystemErr_Gen_NoDTDValidator
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Gen_CouldNotOpenDTD, kXMLParserPrefix2 + 38)		// kAXESystemErr_Gen_CouldNotOpenDTD
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Gen_CouldNotOpenExtEntity, kXMLParserPrefix2 + 39)	// kAXESystemErr_Gen_CouldNotOpenExtEntity
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Gen_UnexpectedEOF, kXMLParserPrefix2 + 40)			// kAXESystemErr_Gen_UnexpectedEOF
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_HshTbl_ZeroModulus, kXMLParserPrefix2 + 41)			// kAXESystemErr_HshTbl_ZeroModulus
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_HshTbl_BadHashFromKey, kXMLParserPrefix2 + 42)		// kAXESystemErr_HshTbl_BadHashFromKey
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_HshTbl_NoSuchKeyExists, kXMLParserPrefix2 + 43)		// kAXESystemErr_HshTbl_NoSuchKeyExists
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Mutex_CouldNotCreate, kXMLParserPrefix2 + 44)		// kAXESystemErr_Mutex_CouldNotCreate
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Mutex_CouldNotClose, kXMLParserPrefix2 + 45)		// kAXESystemErr_Mutex_CouldNotClose
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Mutex_CouldNotLock, kXMLParserPrefix2 + 46)			// kAXESystemErr_Mutex_CouldNotLock
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Mutex_CouldNotUnlock, kXMLParserPrefix2 + 47)		// kAXESystemErr_Mutex_CouldNotUnlock
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Mutex_CouldNotDestroy, kXMLParserPrefix2 + 48)		// kAXESystemErr_Mutex_CouldNotDestroy
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_InternalError, kXMLParserPrefix2 + 49)		// kAXESystemErr_NetAcc_InternalError
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_InitFailed, kXMLParserPrefix2 + 50)			// kAXESystemErr_NetAcc_InitFailed
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_TargetResolution, kXMLParserPrefix2 + 51)	// kAXESystemErr_NetAcc_TargetResolution
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_CreateSocket, kXMLParserPrefix2 + 52)		// kAXESystemErr_NetAcc_CreateSocket
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_ConnSocket, kXMLParserPrefix2 + 53)			// kAXESystemErr_NetAcc_ConnSocket
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_WriteSocket, kXMLParserPrefix2 + 54)			// kAXESystemErr_NetAcc_WriteSocket
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_NetAcc_ReadSocket, kXMLParserPrefix2 + 55)			// kAXESystemErr_NetAcc_ReadSocket
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Pool_ElemAlreadyExists, kXMLParserPrefix2 + 56)		// kAXESystemErr_Pool_ElemAlreadyExists
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Pool_BadHashFromKey, kXMLParserPrefix2 + 57)		// kAXESystemErr_Pool_BadHashFromKey
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Pool_InvalidId, kXMLParserPrefix2 + 58)				// kAXESystemErr_Pool_InvalidId
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Pool_ZeroModulus, kXMLParserPrefix2 + 59)			// kAXESystemErr_Pool_ZeroModulus
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_RdrMgr_ReaderIdNotFound, kXMLParserPrefix2 + 60)	// kAXESystemErr_RdrMgr_ReaderIdNotFound
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Reader_BadAutoEncoding, kXMLParserPrefix2 + 61)		// kAXESystemErr_Reader_BadAutoEncoding
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Reader_CouldNotDecodeFirstLine, kXMLParserPrefix2 + 62)		// kAXESystemErr_Reader_CouldNotDecodeFirstLine
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Reader_EOIInMultiSeq, kXMLParserPrefix2 + 63)		// kAXESystemErr_Reader_EOIInMultiSeq
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Reader_SrcOfsNotSupported, kXMLParserPrefix2 + 64)	// kAXESystemErr_Reader_SrcOfsNotSupported
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Reader_EncodingStrRequired, kXMLParserPrefix2 + 65)	// kAXESystemErr_Reader_EncodingStrRequired
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Scan_CouldNotOpenSource, kXMLParserPrefix2 + 66)	// kAXESystemErr_Scan_CouldNotOpenSource
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Scan_UnbalancedStartEnd, kXMLParserPrefix2 + 67)	// kAXESystemErr_Scan_UnbalancedStartEnd
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Scan_BadPScanToken, kXMLParserPrefix2 + 68)			// kAXESystemErr_Scan_BadPScanToken
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Stack_BadIndex, kXMLParserPrefix2 + 69)				// kAXESystemErr_Stack_BadIndex
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Stack_EmptyStack, kXMLParserPrefix2 + 70)			// kAXESystemErr_Stack_EmptyStack
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Str_ZeroSizedTargetBuf, kXMLParserPrefix2 + 71)		// kAXESystemErr_Str_ZeroSizedTargetBuf
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Str_UnknownRadix, kXMLParserPrefix2 + 72)			// kAXESystemErr_Str_UnknownRadix
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Str_TargetBufTooSmall, kXMLParserPrefix2 + 73)		// kAXESystemErr_Str_TargetBufTooSmall
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Str_StartIndexPastEnd, kXMLParserPrefix2 + 74)		// kAXESystemErr_Str_StartIndexPastEnd
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Str_ConvertOverflow, kXMLParserPrefix2 + 75)		// kAXESystemErr_Str_ConvertOverflow
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Strm_StdErrWriteFailure, kXMLParserPrefix2 + 76)	// kAXESystemErr_Strm_StdErrWriteFailure
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Strm_StdOutWriteFailure, kXMLParserPrefix2 + 77)	// kAXESystemErr_Strm_StdOutWriteFailure
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Strm_ConWriteFailure, kXMLParserPrefix2 + 78)		// kAXESystemErr_Strm_ConWriteFailure
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_StrPool_IllegalId, kXMLParserPrefix2 + 79)			// kAXESystemErr_StrPool_IllegalId
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_CouldNotCreateDefCvtr, kXMLParserPrefix2 + 80)// kAXESystemErr_Trans_CouldNotCreateDefCvtr
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_InvalidSizeReq, kXMLParserPrefix2 + 81)		// kAXESystemErr_Trans_InvalidSizeReq
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_Unrepresentable, kXMLParserPrefix2 + 82)		// kAXESystemErr_Trans_Unrepresentable
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_NotValidForEncoding, kXMLParserPrefix2 + 83)	// kAXESystemErr_Trans_NotValidForEncoding
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_BadBlockSize, kXMLParserPrefix2 + 84)			// kAXESystemErr_Trans_BadBlockSize
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_BadSrcSeq, kXMLParserPrefix2 + 85)			// kAXESystemErr_Trans_BadSrcSeq
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_BadSrcCP, kXMLParserPrefix2 + 86)				// kAXESystemErr_Trans_BadSrcCP
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_BadTrailingSurrogate, kXMLParserPrefix2 + 87)	// kAXESystemErr_Trans_BadTrailingSurrogate
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Trans_CantCreateCvtrFor, kXMLParserPrefix2 + 88)	// kAXESystemErr_Trans_CantCreateCvtrFor
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_MalformedURL, kXMLParserPrefix2 + 89)			// kAXESystemErr_URL_MalformedURL
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_UnsupportedProto, kXMLParserPrefix2 + 90)		// kAXESystemErr_URL_UnsupportedProto
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_UnsupportedProto1, kXMLParserPrefix2 + 91)		// kAXESystemErr_URL_UnsupportedProto1
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_OnlyLocalHost, kXMLParserPrefix2 + 92)			// kAXESystemErr_URL_OnlyLocalHost
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_NoProtocolPresent, kXMLParserPrefix2 + 93)		// kAXESystemErr_URL_NoProtocolPresent
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_ExpectingTwoSlashes, kXMLParserPrefix2 + 94)	// kAXESystemErr_URL_ExpectingTwoSlashes
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_IncorrectEscapedCharRef, kXMLParserPrefix2 + 95)// kAXESystemErr_URL_IncorrectEscapedCharRef
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_UnterminatedHostComponent, kXMLParserPrefix2 + 96)	// kAXESystemErr_URL_UnterminatedHostComponent
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_RelativeBaseURL, kXMLParserPrefix2 + 97)		// kAXESystemErr_URL_RelativeBaseURL
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_BaseUnderflow, kXMLParserPrefix2 + 98)			// kAXESystemErr_URL_BaseUnderflow
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_URL_BadPortField, kXMLParserPrefix2 + 99)			// kAXESystemErr_URL_BadPortField
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Vector_BadIndex, kXMLParserPrefix2 + 100)			// kAXESystemErr_Vector_BadIndex
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Val_InvalidElemId, kXMLParserPrefix2 + 101)			// kAXESystemErr_Val_InvalidElemId
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Val_CantHaveIntSS, kXMLParserPrefix2 + 102)			// kAXESystemErr_Val_CantHaveIntSS
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_XMLRec_UnknownEncoding, kXMLParserPrefix2 + 103)	// kAXESystemErr_XMLRec_UnknownEncoding
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_E_HighBounds, kXMLParserPrefix2 + 104)				// kAXESystemErr_E_HighBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_W_LowBounds, kXMLParserPrefix2 + 105)				// kAXESystemErr_W_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_W_HighBounds, kXMLParserPrefix2 + 106)				// kAXESystemErr_W_HighBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_V_LowBounds, kXMLParserPrefix2 + 107)				// kAXESystemErr_V_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_V_HighBounds, kXMLParserPrefix2 + 108)				// kAXESystemErr_V_HighBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_LowBounds, kXMLParserPrefix2 + 109)				// kAXESystemErr_Ext_LowBounds
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_TranscoderProblem, kXMLParserPrefix2 + 110)		// kAXESystemErr_Ext_TranscoderProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_AXEProblem, kXMLParserPrefix2 + 111)			// kAXESystemErr_Ext_AXEProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_BIBProblem, kXMLParserPrefix2 + 112)			// kAXESystemErr_Ext_BIBProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_UnknownProblem, kXMLParserPrefix2 + 113)		// kAXESystemErr_Ext_UnknownProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_CouldNotWriteToFile, kXMLParserPrefix2 + 114)		// kAXESystemErr_Ext_CouldNotWriteToFile
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_AXEDOMProblem, kXMLParserPrefix2 + 115)		// kAXESystemErr_Ext_AXEDOMProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_XPathProblem, kXMLParserPrefix2 + 116)		// kAXESystemErr_Ext_XPathProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_XSLTProblem, kXMLParserPrefix2 + 117)		// kAXESystemErr_Ext_XSLTProblem
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_UnresolvedEncodingConflict, kXMLParserPrefix2 + 118)	// kAXESystemErr_Ext_UnresolvedEncodingConflict
// -- 119 through 128 are current unassigned for AXE 3.2
DECLARE_PMID(kErrorIDSpace, kXMLSystemErr_Ext_HighBounds, kXMLParserPrefix2 + 129)			// kAXESystemErr_Ext_HighBounds

// -- AXE XPath errors
// -- The initial range of errors map directly to the errors reported by the AXE system
// -- and therefore MUST be reserved and not modified.  These are based off of XMLPrefix3
//DECLARE_PMID(kErrorIDSpace, kXMLXPathErr_FUTURE_ERROR, kXMLParserPrefix3 + 50)			
DECLARE_PMID(kErrorIDSpace, kXMLXPathErr_INVALID_EXPRESSION_ERR, kXMLParserPrefix3 + 51)	// kAXEXPathErr_INVALID_EXPRESSION_ERR
DECLARE_PMID(kErrorIDSpace, kXMLXPathErr_TYPE_ERR, kXMLParserPrefix3 + 52)					// kAXEXPathErr_TYPE_ERR
DECLARE_PMID(kErrorIDSpace, kXMLXPathUnknown_ERR, kXMLParserPrefix3 + 53)					// kAXEXPathUnknown_ERR
DECLARE_PMID(kErrorIDSpace, kXMLXPathErr_NUM_ERRORS, kXMLParserPrefix3 + 54)				// kAXEXPathErr_NUM_ERRORS

// -- AXE DOM errors
// -- This range errors maps to the DOM error section of AXE.  
// -- For now we are mapping them starting from 55
// -- This mapping is handled in SAXErrorHandler::GetIDErrorInfo.
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_LowBounds, kXMLParserPrefix3 + 55)							
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_INDEX_SIZE_ERR, kXMLParserPrefix3 + 56)						// kAXEDOMErr_INDEX_SIZE_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_DOMSTRING_SIZE_ERR, kXMLParserPrefix3 + 57)					// kAXEDOMErr_DOMSTRING_SIZE_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_HIERARCHY_REQUEST_ERR, kXMLParserPrefix3 + 58)				// kAXEDOMErr_HIERARCHY_REQUEST_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_WRONG_DOCUMENT_ERR, kXMLParserPrefix3 + 59)					// kAXEDOMErr_WRONG_DOCUMENT_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_INVALID_CHARACTER_ERR, kXMLParserPrefix3 + 60)				// kAXEDOMErr_INVALID_CHARACTER_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_NO_DATA_ALLOWED_ERR, kXMLParserPrefix3 + 61)					// kAXEDOMErr_NO_DATA_ALLOWED_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_NO_MODIFICATION_ALLOWED_ERR, kXMLParserPrefix3 + 62)			// kAXEDOMErr_NO_MODIFICATION_ALLOWED_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_NOT_FOUND_ERR, kXMLParserPrefix3 + 63)						// kAXEDOMErr_NOT_FOUND_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_NOT_SUPPORTED_ERR, kXMLParserPrefix3 + 64)					// kAXEDOMErr_NOT_SUPPORTED_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_INUSE_ATTRIBUTE_ERR, kXMLParserPrefix3 + 65)					// kAXEDOMErr_INUSE_ATTRIBUTE_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_INVALID_STATE_ERR, kXMLParserPrefix3 + 66)					// kAXEDOMErr_INVALID_STATE_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_SYNTAX_ERR, kXMLParserPrefix3 + 67)							// kAXEDOMErr_SYNTAX_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_INVALID_MODIFICATION_ERR, kXMLParserPrefix3 + 68)			// kAXEDOMErr_INVALID_MODIFICATION_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_NAMESPACE_ERR, kXMLParserPrefix3 + 69)						// kAXEDOMErr_NAMESPACE_ERR
DECLARE_PMID(kErrorIDSpace, kXMLDOMErr_INVALID_ACCESS_ERR, kXMLParserPrefix3 + 70)					// kAXEDOMErr_INVALID_ACCESS_ERR

// -- AXE XSLT errors
// -- The initial range of errors map directly to the errors reported by the AXE system
// -- and therefore MUST be reserved and not modified.  These are based off of XMLPrefix4

DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NoError, kXMLParserPrefix4 + 0)			// kAXEXSLTransformerErr_NoError
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NOT_OK, kXMLParserPrefix4 + 1)			// kAXEXSLTransformerErr_NOT_OK
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_XML, kXMLParserPrefix4 + 2)			// kAXEXSLTransformerErr_XML
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_CHAR, kXMLParserPrefix4 + 3)			// kAXEXSLTransformerErr_BAD_CHAR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FILE_OPEN, kXMLParserPrefix4 + 4)			// kAXEXSLTransformerErr_FILE_OPEN
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_MEMORY, kXMLParserPrefix4 + 5)			// kAXEXSLTransformerErr_MEMORY
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_UNSUPP_XSL, kXMLParserPrefix4 + 6)			// kAXEXSLTransformerErr_UNSUPP_XSL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_XSL, kXMLParserPrefix4 + 7)			// kAXEXSLTransformerErr_BAD_XSL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_REQ_ATTR, kXMLParserPrefix4 + 8)			// kAXEXSLTransformerErr_REQ_ATTR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_ATTR, kXMLParserPrefix4 + 9)			// kAXEXSLTransformerErr_BAD_ATTR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_UNKNOWN_AXIS, kXMLParserPrefix4 + 10)			// kAXEXSLTransformerErr_UNKNOWN_AXIS
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_EXPR_SYNTAX, kXMLParserPrefix4 + 11)			// kAXEXSLTransformerErr_EXPR_SYNTAX
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_NUMBER, kXMLParserPrefix4 + 12)			// kAXEXSLTransformerErr_BAD_NUMBER
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_VAR, kXMLParserPrefix4 + 13)			// kAXEXSLTransformerErr_BAD_VAR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_INFINITE_LITERAL, kXMLParserPrefix4 + 14)			// kAXEXSLTransformerErr_INFINITE_LITERAL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_LPAREN_EXP, kXMLParserPrefix4 + 15)			// kAXEXSLTransformerErr_LPAREN_EXP
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_RPAREN_EXP, kXMLParserPrefix4 + 16)			// kAXEXSLTransformerErr_RPAREN_EXP
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_LPARCKET_EXP, kXMLParserPrefix4 + 17)			// kAXEXSLTransformerErr_LPARCKET_EXP
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_RBRACKET_EXP, kXMLParserPrefix4 + 18)			// kAXEXSLTransformerErr_RBRACKET_EXP
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_EMPTY_PATT, kXMLParserPrefix4 + 19)			// kAXEXSLTransformerErr_EMPTY_PATT
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_TOKEN, kXMLParserPrefix4 + 20)			// kAXEXSLTransformerErr_BAD_TOKEN
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_AXIS_IN_PATTERN, kXMLParserPrefix4 + 21)			// kAXEXSLTransformerErr_BAD_AXIS_IN_PATTERN
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_PATTERN, kXMLParserPrefix4 + 22)			// kAXEXSLTransformerErr_BAD_PATTERN
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_VAR_IN_MATCH, kXMLParserPrefix4 + 23)			// kAXEXSLTransformerErr_VAR_IN_MATCH
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_PREFIX, kXMLParserPrefix4 + 24)			// kAXEXSLTransformerErr_BAD_PREFIX
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_EXTRA_COLON, kXMLParserPrefix4 + 25)			// kAXEXSLTransformerErr_EXTRA_COLON
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ELEM_MUST_EMPTY, kXMLParserPrefix4 + 26)			// kAXEXSLTransformerErr_ELEM_MUST_EMPTY
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ELEM_CONT_TEXT_OR_LRE, kXMLParserPrefix4 + 27)			// kAXEXSLTransformerErr_ELEM_CONT_TEXT_OR_LRE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ELEM_CONTAINS_ELEM, kXMLParserPrefix4 + 28)			// kAXEXSLTransformerErr_ELEM_CONTAINS_ELEM
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ELEM_MUST_BE_PCDATA, kXMLParserPrefix4 + 29)			// kAXEXSLTransformerErr_ELEM_MUST_BE_PCDATA
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ELEM_TOPLEVEL, kXMLParserPrefix4 + 30)			// kAXEXSLTransformerErr_ELEM_TOPLEVEL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_ELEM_CONTENT, kXMLParserPrefix4 + 31)			// kAXEXSLTransformerErr_BAD_ELEM_CONTENT
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_DUPLICATE_RULE_NAME, kXMLParserPrefix4 + 32)			// kAXEXSLTransformerErr_DUPLICATE_RULE_NAME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_DUPLICATE_ASET_NAME, kXMLParserPrefix4 + 33)			// kAXEXSLTransformerErr_DUPLICATE_ASET_NAME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NONEX_ASET_NAME, kXMLParserPrefix4 + 34)			// kAXEXSLTransformerErr_NONEX_ASET_NAME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_CIRCULAR_ASET_REF, kXMLParserPrefix4 + 35)			// kAXEXSLTransformerErr_CIRCULAR_ASET_REF
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_DUPLICIT_KEY, kXMLParserPrefix4 + 36)			// kAXEXSLTransformerErr_DUPLICIT_KEY
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_KEY_NOT_FOUND, kXMLParserPrefix4 + 37)			// kAXEXSLTransformerErr_KEY_NOT_FOUND
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FORMAT_DUPLICIT_OPTION, kXMLParserPrefix4 + 38)			// kAXEXSLTransformerErr_FORMAT_DUPLICIT_OPTION
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FORMAT_OPTION_CHAR, kXMLParserPrefix4 + 39)			// kAXEXSLTransformerErr_FORMAT_OPTION_CHAR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FORMAT_DUPLICIT_NAME, kXMLParserPrefix4 + 40)			// kAXEXSLTransformerErr_FORMAT_DUPLICIT_NAME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FORMAT_NOT_FOUND, kXMLParserPrefix4 + 41)			// kAXEXSLTransformerErr_FORMAT_NOT_FOUND
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FORMAT_INVALID, kXMLParserPrefix4 + 42)			// kAXEXSLTransformerErr_FORMAT_INVALID
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NUMBER_LEVEL, kXMLParserPrefix4 + 43)			// kAXEXSLTransformerErr_NUMBER_LEVEL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NUMBER_LETTER_VALUE, kXMLParserPrefix4 + 44)			// kAXEXSLTransformerErr_NUMBER_LETTER_VALUE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_CIRCULAR_INCLUSION, kXMLParserPrefix4 + 45)			// kAXEXSLTransformerErr_CIRCULAR_INCLUSION
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_VAR_NOT_FOUND, kXMLParserPrefix4 + 46)			// kAXEXSLTransformerErr_VAR_NOT_FOUND
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_VAR_CIRCULAR_REF, kXMLParserPrefix4 + 47)			// kAXEXSLTransformerErr_VAR_CIRCULAR_REF
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_CONTEXT_FOR_BAD_EXPR, kXMLParserPrefix4 + 48)			// kAXEXSLTransformerErr_CONTEXT_FOR_BAD_EXPR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_ARGS_N, kXMLParserPrefix4 + 49)			// kAXEXSLTransformerErr_BAD_ARGS_N
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_ARG_TYPE, kXMLParserPrefix4 + 50)			// kAXEXSLTransformerErr_BAD_ARG_TYPE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_FUNC_NOT_SUPPORTED, kXMLParserPrefix4 + 51)			// kAXEXSLTransformerErr_FUNC_NOT_SUPPORTED
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_RULE_NOT_FOUND, kXMLParserPrefix4 + 52)			// kAXEXSLTransformerErr_RULE_NOT_FOUND
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_MULT_ASSIGNMENT, kXMLParserPrefix4 + 53)			// kAXEXSLTransformerErr_MULT_ASSIGNMENT
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ATTR_YES_NO, kXMLParserPrefix4 + 54)			// kAXEXSLTransformerErr_ATTR_YES_NO
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ATTRIBUTE_TOO_LATE, kXMLParserPrefix4 + 55)			// kAXEXSLTransformerErr_ATTRIBUTE_TOO_LATE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ATTRIBUTE_OUTSIDE, kXMLParserPrefix4 + 56)			// kAXEXSLTransformerErr_ATTRIBUTE_OUTSIDE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_BAD_CHAR_IN_ENC, kXMLParserPrefix4 + 57)			// kAXEXSLTransformerErr_BAD_CHAR_IN_ENC
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_PI_TARGET, kXMLParserPrefix4 + 58)			// kAXEXSLTransformerErr_PI_TARGET
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ELEM_IN_COMMENT_PI, kXMLParserPrefix4 + 59)			// kAXEXSLTransformerErr_ELEM_IN_COMMENT_PI
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_XSL_MESSAGE_TERM, kXMLParserPrefix4 + 60)			// kAXEXSLTransformerErr_XSL_MESSAGE_TERM
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_URI_OPEN, kXMLParserPrefix4 + 61)			// kAXEXSLTransformerErr_URI_OPEN
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_URI_CLOSE, kXMLParserPrefix4 + 62)			// kAXEXSLTransformerErr_URI_CLOSE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_URI_READ, kXMLParserPrefix4 + 63)			// kAXEXSLTransformerErr_URI_READ
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_URI_WRITE, kXMLParserPrefix4 + 64)			// kAXEXSLTransformerErr_URI_WRITE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ARG_NOT_FOUND, kXMLParserPrefix4 + 65)			// kAXEXSLTransformerErr_ARG_NOT_FOUND
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_DUPLICATE_ARG, kXMLParserPrefix4 + 66)			// kAXEXSLTransformerErr_DUPLICATE_ARG
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_UNSUPPORTED_SCHEME, kXMLParserPrefix4 + 67)			// kAXEXSLTransformerErr_UNSUPPORTED_SCHEME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_INVALID_HLR_TYPE, kXMLParserPrefix4 + 68)			// kAXEXSLTransformerErr_INVALID_HLR_TYPE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_UNKNOWN_ENC, kXMLParserPrefix4 + 69)			// kAXEXSLTransformerErr_UNKNOWN_ENC
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_SDOM, kXMLParserPrefix4 + 70)			// kAXEXSLTransformerErr_SDOM
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NONE, kXMLParserPrefix4 + 71)			// kAXEXSLTransformerErr_NONE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_EX_NAMESPACE_UNKNOWN, kXMLParserPrefix4 + 72)			// kAXEXSLTransformerErr_EX_NAMESPACE_UNKNOWN
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_INVALID_DATA_IN_PI, kXMLParserPrefix4 + 73)			// kAXEXSLTransformerErr_INVALID_DATA_IN_PI
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_UNSUPPORTED_EXELEMENT, kXMLParserPrefix4 + 74)			// kAXEXSLTransformerErr_UNSUPPORTED_EXELEMENT
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ATTR_MISSING, kXMLParserPrefix4 + 75)			// kAXEXSLTransformerErr_ATTR_MISSING
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_JS_EVAL_ERROR, kXMLParserPrefix4 + 76)			// kAXEXSLTransformerErr_JS_EVAL_ERROR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_UNSUPP_LANG, kXMLParserPrefix4 + 77)			// kAXEXSLTransformerErr_W_UNSUPP_LANG
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_NO_STYLESHEET, kXMLParserPrefix4 + 78)			// kAXEXSLTransformerErr_W_NO_STYLESHEET
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_HLR_REGISTERED, kXMLParserPrefix4 + 79)			// kAXEXSLTransformerErr_W_HLR_REGISTERED
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_HLR_NOT_REGISTERED, kXMLParserPrefix4 + 80)			// kAXEXSLTransformerErr_W_HLR_NOT_REGISTERED
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_OLD_NS_USED, kXMLParserPrefix4 + 81)			// kAXEXSLTransformerErr_W_OLD_NS_USED
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_XSL_NOT_XSL, kXMLParserPrefix4 + 82)			// kAXEXSLTransformerErr_W_XSL_NOT_XSL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_OUTPUT_ATTR, kXMLParserPrefix4 + 83)			// kAXEXSLTransformerErr_W_OUTPUT_ATTR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_DISABLE_OUTPUT_ESC, kXMLParserPrefix4 + 84)			// kAXEXSLTransformerErr_W_DISABLE_OUTPUT_ESC
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_UNSUPP_OUT_ENCODING, kXMLParserPrefix4 + 85)			// kAXEXSLTransformerErr_W_UNSUPP_OUT_ENCODING
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_UNSUPP_XSL, kXMLParserPrefix4 + 86)			// kAXEXSLTransformerErr_W_UNSUPP_XSL
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_XSL_MESSAGE_NOTERM, kXMLParserPrefix4 + 87)			// kAXEXSLTransformerErr_W_XSL_MESSAGE_NOTERM
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_SORT_DATA_TYPE, kXMLParserPrefix4 + 88)			// kAXEXSLTransformerErr_W_SORT_DATA_TYPE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_SORT_ORDER, kXMLParserPrefix4 + 89)			// kAXEXSLTransformerErr_W_SORT_ORDER
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_SORT_CASE_ORDER, kXMLParserPrefix4 + 90)			// kAXEXSLTransformerErr_W_SORT_CASE_ORDER
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_LANG, kXMLParserPrefix4 + 91)			// kAXEXSLTransformerErr_W_LANG
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_NO_WCSXFRM, kXMLParserPrefix4 + 92)			// kAXEXSLTransformerErr_W_NO_WCSXFRM
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_BAD_START, kXMLParserPrefix4 + 93)			// kAXEXSLTransformerErr_W_BAD_START
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_NUMBER_GROUPING, kXMLParserPrefix4 + 94)			// kAXEXSLTransformerErr_W_NUMBER_GROUPING
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_NUMBER_NOT_POSITIVE, kXMLParserPrefix4 + 95)			// kAXEXSLTransformerErr_W_NUMBER_NOT_POSITIVE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_ATTSET_REDEF, kXMLParserPrefix4 + 96)			// kAXEXSLTransformerErr_W_ATTSET_REDEF
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_ALIAS_REDEF, kXMLParserPrefix4 + 97)			// kAXEXSLTransformerErr_W_ALIAS_REDEF
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_INVALID_QNAME, kXMLParserPrefix4 + 98)			// kAXEXSLTransformerErr_W_INVALID_QNAME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_INVALID_NCNAME, kXMLParserPrefix4 + 99)			// kAXEXSLTransformerErr_W_INVALID_NCNAME
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_DOC_FRAGMENT, kXMLParserPrefix4 + 100)			// kAXEXSLTransformerErr_W_DOC_FRAGMENT
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_NONE, kXMLParserPrefix4 + 101)			// kAXEXSLTransformerErr_W_NONE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_PI_SYNTAX_ERROR, kXMLParserPrefix4 + 102)		// kAXEXSLTransformerErr_PI_SYNTAX_ERROR
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_W_UNSUPP_OUTPUT_METH, kXMLParserPrefix4 + 103)	// kAXEXSLTransformerErr_W_UNSUPP_OUTPUT_METH
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_DUPLICATE_ATTRIBUTE, kXMLParserPrefix4 + 104)	// kAXEXSLTransformerErr_DUPLICATE_ATTRIBUTE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_INVALID_OPERAND_TYPE, kXMLParserPrefix4 + 105)	// kAXEXSLTransformerErr_INVALID_OPERAND_TYPE
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_INVALID_DOM_OUTPUT_METH, kXMLParserPrefix4 + 106)// kAXEXSLTransformerErr_INVALID_DOM_OUTPUT_METH
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NO_CLIENT_ENTITY_RESOLVER, kXMLParserPrefix4 + 107)	// kAXEXSLTransformerErr_NO_CLIENT_ENTITY_RESOLVER
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NOSUPP_STYLESHEET_IN_STYLESHEET, kXMLParserPrefix4 + 108) // kAXEXSLTransformerErr_NOSUPP_STYLESHEET_IN_STYLESHEET
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_DUPLICATE_OUTDOC, kXMLParserPrefix4 + 109)		// kAXEXSLTransformerErr_DUPLICATE_OUTDOC
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_ATTRIBUTE_MISPLACED, kXMLParserPrefix4 + 110)	// kAXEXSLTransformerErr_ATTRIBUTE_MISPLACED
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_USER_ABORT, kXMLParserPrefix4 + 111)				// kAXEXSLTTransformerErr_USER_ABORT
DECLARE_PMID(kErrorIDSpace, kXMLTransformerErr_NUM_ERRORS, kXMLParserPrefix4 + 112)				// kAXEXSLTransformerErr_NUM_ERRORS

// -- InDesign errors

DECLARE_PMID(kErrorIDSpace, kStylesheetEntityNotResolved, kXMLParserPrefix3 + 202)
DECLARE_PMID(kErrorIDSpace, kStylesheetNotFoundErr, kXMLParserPrefix3 + 203)
DECLARE_PMID(kErrorIDSpace, kStylesheetIncludeNotFoundErr, kXMLParserPrefix3 + 204)
DECLARE_PMID(kErrorIDSpace, kStylesheetImportNotFoundErr, kXMLParserPrefix3 + 205)
DECLARE_PMID(kErrorIDSpace, kXMLStylesheetPIFoundErr, kXMLParserPrefix3 + 206)
DECLARE_PMID(kErrorIDSpace, kXMLStylesheetPINotFoundErr, kXMLParserPrefix3 + 207)
DECLARE_PMID(kErrorIDSpace, kXMLIDFatalErrorErr, kXMLParserPrefix3 + 208)
DECLARE_PMID(kErrorIDSpace, kStylesheetNotFoundOnImportErr, kXMLParserPrefix3 + 209)

// DTD validity errors, note some of them are defined in AXE parser errors.
// See XMLDTDTokenHandler.cpp
DECLARE_PMID(kErrorIDSpace, kXMLDTDValidityErr_MultiNotation, kXMLParserPrefix3 + 210)
DECLARE_PMID(kErrorIDSpace, kXMLDTDValidityErr_NotationOnEmptyElement, kXMLParserPrefix3 + 211)
DECLARE_PMID(kErrorIDSpace, kXMLDTDValidityErr_DuplicateToken, kXMLParserPrefix3 + 212)

//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 213)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 214)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 215)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 216)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 217)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 218)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 219)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 220)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 221)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 222)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 223)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 224)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 225)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 226)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 227)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 228)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 229)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 230)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 231)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 232)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 233)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 234)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 235)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 236)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 237)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 238)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 239)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 240)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 241)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 242)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 243)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 244)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 245)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 246)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 247)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 248)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 249)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 250)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 251)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 252)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 253)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 254)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLParserPrefix3 + 255)


// Messages
DECLARE_PMID(kMessageIDSpace, kXMLEntityNotResolved, kXMLParserPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kXMLPublicIDsNotSupported, kXMLParserPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kXMLLineColumnInfo, kXMLParserPrefix + 3)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 4)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 5)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 6)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 7)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 8)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 9)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 10)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 11)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 12)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 13)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 14)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 15)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 16)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 17)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 18)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 19)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLParserPrefix + 20)


#endif
