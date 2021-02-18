//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/INXOrderDefs.h $
//  
//  Owner: Steve Pellegrin
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

#pragma once
#ifndef __INXORDERDEFS__
#define __INXORDERDEFS__

//INX order of kDocumentObjectScriptElement children

#define kLanguageObjectScriptElementPosition					100.0
#define kColorObjectScriptElementPosition						200.0
#define kInkObjectScriptElementPosition							300.0
#define kMixedInkGroupObjectScriptElementPosition				400.0
#define kMixedInkObjectScriptElementPosition					500.0
#define kAGMBlackBoxObjectScriptElementPosition					600.0
#define kTintObjectScriptElementPosition						700.0
#define kSwatchObjectScriptElementPosition						800.0
#define kGradientObjectScriptElementPosition					900.0
#define kStrokeStyleObjectScriptElementPosition					1000.0
#define kDashStrokeStyleObjectScriptElementPosition				1000.0
#define kDotStrokeStyleObjectScriptElementPosition				1000.0
#define kStripeStrokeStyleObjectScriptElementPosition			1000.0

#define kFontFamilyObjectScriptElementPosition					1100.0
#define kCompositeFontObjectScriptElementPosition				1200.0
#define kKinsokuTableObjectScriptElementPosition				1300.0
#define kMojikumiTableObjectScriptElementPosition				1400.0
#define kCharacterStyleSetObjectScriptElementPosition			1500.0
#define kCharacterStyleObjectScriptElementPosition				1600.0
#define kBNListCollectionObjectScriptElementPosition			1700.0
#define kParagraphStyleSetObjectScriptElementPosition			1800.0
#define kParagraphStyleObjectScriptElementPosition				1900.0
#define kTOCStyleObjectScriptElementPosition					2000.0
#define kCellStyleSetObjectScriptElementPosition				2100.0
#define kCellStyleObjectScriptElementPosition					2200.0


#define kTableStyleSetObjectScriptElementPosition				2300.0
#define kTableStyleObjectScriptElementPosition					2400.0
#define kNamedGridObjectScriptElementPosition					2500.0
#define kObjectStyleGroupObjectScriptElementPosition			2600.0
#define kObjectStylesObjectScriptElementPosition				2700.0
#define kTrapStyleObjectScriptElementPosition					2800.0

#define kConditionTagObjectScriptElementPosition				2850.0
#define kConditionTagSetObjectScriptElementPosition				2851.0

// All preference child is assumed to have kPreferencesObjectScriptElementPosition. 
// It is not really added into kPreferencesObjectScriptElement as metadata. Since 
// we do stable sort, preference child object will show up in INX file in the order 
// they are encountered.

#define kPreferencesObjectScriptElementPosition					2900.0
#define kTextVariableObjectScriptElementPosition				3000.0
#define kXMLTagObjectScriptElementPosition						3100.0
#define kLayerObjectScriptElementPosition						3200.0
#define kBNBulletCollectionObjectScriptElementPosition			3300.0
#define kMasterSpreadObjectScriptElementPosition				3400.0

#define kSpreadObjectScriptElementPosition						3500.0
#define kSectionObjectScriptElementPosition						3600.0
#define kInCopyDocUserObjectScriptElementPosition				3700.0
#define kXRefFormatObjectScriptElementPosition					3750.0 // 3950.0	move before stories for IDML

#define kXMLStoryObjectScriptElementPosition					3800.0 // 3900.0
#define kStoryObjectScriptElementPosition						3900.0 // 3800.0

#define kTextDestinationObjectScriptElementPosition				4000.0
#define kPageDestinationObjectScriptElementPosition				4100.0
#define kURLDestinationObjectScriptElementPosition				4200.0
#define kExternalPageDestinationObjectScriptElementPosition		4300.0
#define kTextSourceObjectScriptElementPosition					4400.0
#define kPageItemSourceObjectScriptElementPosition				4500.0
#define kHyperlinkObjectScriptElementPosition					4600.0

#define kXMLItemObjectScriptElementPosition						5000.0
#define kXMLElementObjectScriptElementPosition					5000.0
#define kXMLDTDObjectScriptElementPosition						5000.0
#define kXMLCommentObjectScriptElementPosition					5000.0
#define kXMLPIObjectScriptElementPosition						5000.0


#define kXMLExportMapObjectScriptElementPosition				5100.0
#define kXMLImportMapObjectScriptElementPosition				5200.0
#define kIndexObjectScriptElementPosition						5300.0
#define kBookmarkObjectScriptElementPosition					5400.0

#define kAnnotationPageDestinationObjectScriptElementPosition	5500.0 
#define kAnnotationPageItemDestinationObjectScriptElementPosition	5600.0 
#define kAnnotationTextDestinationObjectScriptElementPosition	5700.0
#define kAnnotationObjectScriptElementPosition	5800.0 

#define kImagePlaceholderObjectScriptElementPosition
//#define kAssignmentObjectScriptElementPosition
//#define kHyphenationExceptionObjectScriptElementPosition	//position does not matter



//INX order of kGraphicLineObjectScriptElement children

#define kTOPObjectScriptElementPosition							100.0

// INX order story children. Story prefs must be before Grid data. see bug 1844245
#define	kStoryPrefsObjectScriptElementPosition					50.0

// INX order story and text frame children
#define	kGridDataObjectScriptElementPosition					100.0

//Please do not use any number bigger than kLastObjectScriptElementPosition
#define kLastObjectScriptElementPosition						999999.9


//========================================================================================
//	IDML story child object ranking defines
//	Defines used to determine which object takes priority over another when two objects
//  have overlapping ranges
//========================================================================================
#define kLowestObjectRank										0

#define kTextContentIterObjectRank								kLowestObjectRank
#define kCharStyleIterObjectRank								kTextContentIterObjectRank + 10
#define kParaStyleIterObjectRank								kCharStyleIterObjectRank + 10

// By default all owned items that encompass a range are ranked above paragarph and character style ranges (and content)
#define kDefaultOwnedItemRank									kParaStyleIterObjectRank + 10

// Hyperlink text source
#define kHLTextSourceObjectRank									0x3FFFFFFF;

// XML element
#define kXMLObjectRank											kHighestOjectRank

// Using this define means that when the object is written to the IDML file the resultant element 
// can not be broken into arbitrary length elements, other object representations that may overlap
// will need to break around these
#define kHighestOjectRank										0x7FFFFFFF

#endif	//#ifndef __INXORDERDEFS__

