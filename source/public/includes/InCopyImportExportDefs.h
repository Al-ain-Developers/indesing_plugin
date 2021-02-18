//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InCopyImportExportDefs.h $
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

#pragma once
#ifndef __InCopyImportExportDefs__
#define __InCopyImportExportDefs__

#include "CrossPlatformTypes.h"

namespace InCopy
{
// Precision value to use for all reals persisted to xml as scientific notation
extern PUBLIC_DECL const int32		kInCopyPrecision;

// constants for XML string values

extern PUBLIC_DECL ConstCString kXMLVersion;

extern PUBLIC_DECL ConstCString kInCopyStoryElementName;
extern PUBLIC_DECL ConstCString kInCopyDocumentElementName;

extern PUBLIC_DECL ConstCString kNamepaceAttr;
extern PUBLIC_DECL ConstCString kNamespaceValue;
extern PUBLIC_DECL ConstCString kNamespacePrefix;
extern PUBLIC_DECL ConstCString kNamespaceValAttr;

extern PUBLIC_DECL ConstCString	kXMLValueAttr;
extern PUBLIC_DECL ConstCString kTextAttrClassIDAttr;

extern PUBLIC_DECL ConstCString kStoryVersionAttr;
extern PUBLIC_DECL ConstCString kStoryVersionValue;
extern PUBLIC_DECL ConstCString kStoryFinalPreReleaseVersionValue; // only versions between finalPreRelease and final will open in the shipping build

extern PUBLIC_DECL ConstCString kStoryLabelAttr;

extern PUBLIC_DECL ConstCString kStoryPageSizeAttr;

extern PUBLIC_DECL ConstCString kInCopyStoryBossElementName;
extern PUBLIC_DECL ConstCString kStoryTrackChangesAttr;
extern PUBLIC_DECL ConstCString	kDefaultFontNameAttr;
extern PUBLIC_DECL ConstCString kWinDefaultFontName;
extern PUBLIC_DECL ConstCString kMacDefaultFontName;
extern PUBLIC_DECL ConstCString kOpticalMarginAttr;
extern PUBLIC_DECL ConstCString kOpticalSizeAttr;

extern PUBLIC_DECL ConstCString kInCopyParaStyleListElementName;
extern PUBLIC_DECL ConstCString kInCopyCharStyleListElementName;
extern PUBLIC_DECL ConstCString kInCopyParaStyleElementName;
extern PUBLIC_DECL ConstCString kInCopyCharStyleElementName;
extern PUBLIC_DECL ConstCString kInCopyStyleBasedOnAttr;
extern PUBLIC_DECL ConstCString kInCopyNextStyleAttr;
extern PUBLIC_DECL ConstCString kInCopyStyleImportedAttr;

extern PUBLIC_DECL ConstCString kInCopyEndAttributeElementName;

extern PUBLIC_DECL ConstCString kInCopyStyleNameAttr;
extern PUBLIC_DECL ConstCString kInCopyOverrideValueAttr;

extern PUBLIC_DECL ConstCString kInCopyUnimplemented;

extern PUBLIC_DECL ConstCString kInCopyNoteElementName;
extern PUBLIC_DECL ConstCString kInCopyNoteAuthorAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteVisibleAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteCollapseAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteSelectionStartAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteSelectionEndAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteColorAttr;

extern PUBLIC_DECL ConstCString kInCopyNoteCreationTimeAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteModifiedTimeAttr;

extern PUBLIC_DECL ConstCString kInCopyNoteLayoutAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteGalleyAttr;
extern PUBLIC_DECL ConstCString kInCopyNoteScaleAttr;


extern PUBLIC_DECL ConstCString kInCopyRedlineElementName;
extern PUBLIC_DECL ConstCString kInCopyRedlineTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyRedlineMovedAttr;
extern PUBLIC_DECL ConstCString kInCopyRedlineLengthAttr;
extern PUBLIC_DECL ConstCString kInCopyRedlineUserAttr;
extern PUBLIC_DECL ConstCString kInCopyRedlineTimeAttr;
extern PUBLIC_DECL ConstCString kInCopyEndRedlineElementName;

extern PUBLIC_DECL ConstCString kInCopySwatchListElementName;
extern PUBLIC_DECL ConstCString kInCopyInkListElementName;
extern PUBLIC_DECL ConstCString kInCopyColorElementName;
extern PUBLIC_DECL ConstCString kInCopyInkElementName;
extern PUBLIC_DECL ConstCString kInCopyTintElementName;
extern PUBLIC_DECL ConstCString kInCopyGradientElementName;
extern PUBLIC_DECL ConstCString kInCopyGradientStopElementName;
extern PUBLIC_DECL ConstCString kInCopyGradientMidpointElementName;

extern PUBLIC_DECL ConstCString kInCopyIsProcessAttr;
extern PUBLIC_DECL ConstCString kInCopyPrintInkAttr;
extern PUBLIC_DECL ConstCString kInCopyOverPrintInkAttr;
extern PUBLIC_DECL ConstCString kInCopyOverprintTholdAttr;
extern PUBLIC_DECL ConstCString kInCopyDensityAttr;
extern PUBLIC_DECL ConstCString kInCopyTrapTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyTrapOrderAttr;
extern PUBLIC_DECL ConstCString kInCopyOverridePPDAttr;
extern PUBLIC_DECL ConstCString kInCopyFrequencyAttr;
extern PUBLIC_DECL ConstCString kInCopyAngleAttr;
extern PUBLIC_DECL ConstCString kInCopySolidityAttr;
extern PUBLIC_DECL ConstCString kInCopyAsProcessAttr;
extern PUBLIC_DECL ConstCString kInCopyAliasUIDAttr;

extern PUBLIC_DECL ConstCString kInCopyXMLTagListElementName;
extern PUBLIC_DECL ConstCString kInCopyXMLTagElementName;
extern PUBLIC_DECL ConstCString kInCopyXMLTagNameAttr;
extern PUBLIC_DECL ConstCString kInCopyXMLTagColorIndexAttr;
extern PUBLIC_DECL ConstCString kInCopyXMLTagColorRGBAttr;

extern PUBLIC_DECL ConstCString kInCopyDocUserListElementName;
extern PUBLIC_DECL ConstCString kInCopyDocUserElementName;
extern PUBLIC_DECL ConstCString kInCopyDocUserNameAttr;
extern PUBLIC_DECL ConstCString kInCopyDocUserColorIndexAttr;
extern PUBLIC_DECL ConstCString kInCopyDocUserNoteIndexAttr;
extern PUBLIC_DECL ConstCString kInCopyDocUserTCIndexAttr;

extern PUBLIC_DECL ConstCString kInCopySwatchNameAttr;
extern PUBLIC_DECL ConstCString kInCopyColorTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyColorSpaceAttr;
extern PUBLIC_DECL ConstCString kInCopyColorValuesAttr;
extern PUBLIC_DECL ConstCString kInCopyBaseColorAttr;
extern PUBLIC_DECL ConstCString kInCopyTintAmountAttr;
extern PUBLIC_DECL ConstCString kInCopyGradientLocationAttr;
extern PUBLIC_DECL ConstCString kInCopyGradientTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyInksAttr;
extern PUBLIC_DECL ConstCString kInCopyColorRemarkAttr;
extern PUBLIC_DECL ConstCString kInCopyColorParentAttr;

extern PUBLIC_DECL ConstCString kInCopyProcessColorTypeAttrValue;
extern PUBLIC_DECL ConstCString kInCopySpotColorTypeAttrValue;
extern PUBLIC_DECL ConstCString kInCopyDeviceNColorTypeAttrValue;

extern PUBLIC_DECL ConstCString kInCopyRGBColorSpaceAttrValue;
extern PUBLIC_DECL ConstCString kInCopyCMYKColorSpaceAttrValue;
extern PUBLIC_DECL ConstCString kInCopyLABColorSpaceAttrValue;
extern PUBLIC_DECL ConstCString kInCopyHSBColorSpaceAttrValue;
extern PUBLIC_DECL ConstCString kInCopySeparationColorSpaceAttrValue;
extern PUBLIC_DECL ConstCString kInCopyDeviceNColorSpaceAttrValue;

extern PUBLIC_DECL ConstCString kInCopyGradientLinearAttrValue;
extern PUBLIC_DECL ConstCString kInCopyGradientRadialAttrValue;

extern PUBLIC_DECL ConstCString kInCopyTaggedInlineElementName;
extern PUBLIC_DECL ConstCString kInCopyInlineElementName;
extern PUBLIC_DECL ConstCString kInCopyInlineIDAttr;

extern PUBLIC_DECL ConstCString kInCopyTableElementName;
extern PUBLIC_DECL ConstCString kInCopyTableRowElementName;
extern PUBLIC_DECL ConstCString kInCopyCellContentElementName;
extern PUBLIC_DECL ConstCString kInCopyTableAttributeElementName;
extern PUBLIC_DECL ConstCString kInCopyRowAttributeElementName;
extern PUBLIC_DECL ConstCString kInCopyNonAnchorCellAttributeElementName;
extern PUBLIC_DECL ConstCString kInCopyRowElementName;
extern PUBLIC_DECL ConstCString kInCopyColumnAttributeElementName;
extern PUBLIC_DECL ConstCString kInCopyColumnElementName;
extern PUBLIC_DECL ConstCString kInCopyStyleAttrValue;
extern PUBLIC_DECL ConstCString kInCopyRowsAttrValue;
extern PUBLIC_DECL ConstCString kInCopyColumnsAttrValue;
extern PUBLIC_DECL ConstCString kInCopyHeadersAttrValue;
extern PUBLIC_DECL ConstCString kInCopyFootersAttrValue;
extern PUBLIC_DECL ConstCString kInCopyLeftAttrValue;	// left
extern PUBLIC_DECL ConstCString kInCopyTopAttrValue;	// top
extern PUBLIC_DECL ConstCString kInCopyWidthAttrValue;	// width
extern PUBLIC_DECL ConstCString kInCopyHeightAttrValue;	// height
extern PUBLIC_DECL ConstCString kInCopyNumAttrValue;

extern PUBLIC_DECL ConstCString kInCopyIndexPageEntryElementName;
extern PUBLIC_DECL ConstCString kInCopyPageEntryTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyPageEntryNextSAttr;	// next style
extern PUBLIC_DECL ConstCString kInCopyPageEntryNextPAttr;	// next page or paragraph
extern PUBLIC_DECL ConstCString kInCopyPageEntryStyleAttr;	// next style

extern PUBLIC_DECL ConstCString kInCopyIndexXRefEntryElementName;
extern PUBLIC_DECL ConstCString kInCopyXRefEntryTypeAttr;
extern PUBLIC_DECL ConstCString kInCopyXRefEntryCustomAttr;	// next style

extern PUBLIC_DECL ConstCString kInCopyIndexTopicEntryElementName;
extern PUBLIC_DECL ConstCString kInCopyIndexEntryDisplayAttr;
extern PUBLIC_DECL ConstCString kInCopyIndexEntrySortAttr;
extern PUBLIC_DECL ConstCString kInCopyIndexEntryLanguageAttr;
extern PUBLIC_DECL ConstCString kInCopyIndexEntryLevelAttr;

extern PUBLIC_DECL ConstCString kInCopyHyperlinkTextMarkerElementName;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkTextDestMarkerElementName;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkTextEndMarkerElementName;

extern PUBLIC_DECL ConstCString kInCopyHyperlinkSourceAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkNameAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkDestinationAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkLengthAttr;
extern PUBLIC_DECL ConstCString	kInCopyHyperlinkHiddenAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkLinkHiddenAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkVisibleAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkBorderAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkHiliteAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkColorIndexAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkRGBAttr;
extern PUBLIC_DECL ConstCString kInCopyHyperlinkOutlineAttr;

extern PUBLIC_DECL ConstCString kInCopyDocPrefsElementName;

extern PUBLIC_DECL ConstCString kInCopyCharSettingsElementName;
extern PUBLIC_DECL ConstCString kInCopySuperSizeAttr;
extern PUBLIC_DECL ConstCString kInCopySubSizeAttr;
extern PUBLIC_DECL ConstCString kInCopySuperPosAttr;
extern PUBLIC_DECL ConstCString kInCopySubPosAttr;
extern PUBLIC_DECL ConstCString kInCopySmallCapAttr;

extern PUBLIC_DECL ConstCString kInCopyTypeOptionsElementName;
extern PUBLIC_DECL ConstCString kInCopyQuotesAttr;
extern PUBLIC_DECL ConstCString kInCopyOptSizeAttr;
extern PUBLIC_DECL ConstCString kInCopyParaLeadingAttr;

extern PUBLIC_DECL ConstCString	kInCopyDisplayOptionsElementName;
extern PUBLIC_DECL ConstCString kInCopyKeepViolationsAttr;
extern PUBLIC_DECL ConstCString kInCopyHJViolationsAttr;
extern PUBLIC_DECL ConstCString kInCopyCustomKernTrackAttr;
extern PUBLIC_DECL ConstCString kInCopySubFontsAttr;
extern PUBLIC_DECL ConstCString kInCopySubGlyphsAttr;
extern PUBLIC_DECL ConstCString kInCopyJustifyWrapAttr;

extern PUBLIC_DECL ConstCString kInCopyWinStateElementName;
extern PUBLIC_DECL ConstCString	kInCopyWinFrameAttr;
extern PUBLIC_DECL ConstCString	kInCopyWinScaleXAttr;
extern PUBLIC_DECL ConstCString	kInCopyWinScaleYAttr;
extern PUBLIC_DECL ConstCString	kInCopyWinScrollAttr;
extern PUBLIC_DECL ConstCString	kInCopyWinFitAttr;
extern PUBLIC_DECL ConstCString	kInCopyWinVisibleAttr;

extern PUBLIC_DECL ConstCString kInCopyFontNameAttr;
extern PUBLIC_DECL ConstCString kInCopyFontFaceAttr;
extern PUBLIC_DECL ConstCString kInCopynAxesAttr;
extern PUBLIC_DECL ConstCString kInCopyAxisAttr;
extern PUBLIC_DECL ConstCString kInCopyInheritAxisAttr;

extern PUBLIC_DECL ConstCString kInCopyLangAttr;
extern PUBLIC_DECL ConstCString kNoLanguageStr;

extern PUBLIC_DECL ConstCString kInCopyTabPosAttr;
extern PUBLIC_DECL ConstCString kInCopyTabAlignAttr;
extern PUBLIC_DECL ConstCString kInCopyTabAlignToCharAttr;
extern PUBLIC_DECL ConstCString kInCopyTabIsDefaultAttr;
extern PUBLIC_DECL ConstCString kInCopyTabINumLeadersAttr;
extern PUBLIC_DECL ConstCString kInCopyTabLeadersAttr;
extern PUBLIC_DECL ConstCString kInCopyTabStopElemName;
extern PUBLIC_DECL ConstCString kRightStr ;
extern PUBLIC_DECL ConstCString kLeftStr ;
extern PUBLIC_DECL ConstCString kCenterStr ;
extern PUBLIC_DECL ConstCString kCharStr ;

extern PUBLIC_DECL ConstCString kXMPProcInstrStr ;
extern PUBLIC_DECL ConstCString kXMPElementStr ;
extern PUBLIC_DECL ConstCString kInCopyUIDAttr ;
extern PUBLIC_DECL ConstCString kInCopyInvalidUIDStr ;

extern PUBLIC_DECL ConstCString	kInCopySPAssetElementName;
extern PUBLIC_DECL ConstCString kInCopyURLAttr;

// XML specific values
extern PUBLIC_DECL ConstCString kXMLSpaceAttr;
extern PUBLIC_DECL ConstCString kXMLSpacePreserveValue;

extern PUBLIC_DECL ConstCString kInCopyTableDirAttrValue;
extern PUBLIC_DECL ConstCString kStoryRTLAttr;

//character attribute element names
#include "InCopyCharAttrElemNames.h"

// see InCopyStoryExportProvider
extern PUBLIC_DECL ConstCString kInCopyStoryFormatName;
extern PUBLIC_DECL ConstCString kInCopyInterchangeFormatName;
extern PUBLIC_DECL ConstCString kInCopyMarkupFormatName;
}	// namespace InCopy

#endif // __InCopyImportExportDefs__
