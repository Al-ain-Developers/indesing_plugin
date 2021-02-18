//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PDFID.h $
//  
//  Owner: Michael Jordan
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

#ifndef __PDFID__
#define __PDFID__

// ----- Includes -----

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPDFPrefix 						RezLong( 0x2500 )

// Here is another set of prefix IDs for PDF code.  
#define kPDFExtraPrefix					RezLong( 0x11C00 )

//----------------------------------------------------------------------------------------
//
// PluginID
//

#define kPDFPluginName 					"PDF"
DECLARE_PMID(kPlugInIDSpace, kPDFPluginID, kPDFPrefix + 1)

#define kPDFUIPluginName 				"PDF UI"
DECLARE_PMID(kPlugInIDSpace, kPDFUIPluginID, kPDFPrefix + 2)


// <Start IDC>
// <Class ID>
//----------------------------------------------------------------------------------------
//
// Boss ids
//

DECLARE_PMID(kClassIDSpace, kPlacedPDFItemBoss, kPDFPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPDFPlaceProviderBoss, kPDFPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPDFPlaceCmdBoss, kPDFPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPDFTrackerRegisterBoss, kPDFPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPDFExportCmdBoss, kPDFPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPDFViewPortBoss, kPDFPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSetPDFExportPrefsCmdBoss, kPDFPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPDFExportBoss, kPDFPrefix + 8)
DECLARE_PMID(kClassIDSpace, kReadTileSrvImageStreamBoss, kPDFPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPDFErrorStringServiceBoss, kPDFPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPDFLibErrorInfoBoss, kPDFPrefix + 11)
DECLARE_PMID(kClassIDSpace, kDeletePDFItemCmdBoss, kPDFPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPDFLibVersionBoss, kPDFPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSetPDFSecurityPrefsCmdBoss, kPDFPrefix + 14)
DECLARE_PMID(kClassIDSpace, kPDFExportItemsCmdBoss, kPDFPrefix + 15)

DECLARE_PMID(kClassIDSpace, kPDFEditStyleCmdBoss, kPDFPrefix + 16)
DECLARE_PMID(kClassIDSpace, kPDFExportStyleListMgrBoss, kPDFPrefix + 17)
DECLARE_PMID(kClassIDSpace, kPDFExportStyleBoss, kPDFPrefix + 18)
DECLARE_PMID(kClassIDSpace, kPDFExportSetStyleNameCmdBoss, kPDFPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPDFExportAddStyleCmdBoss, kPDFPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPDFExportDeleteStyleCmdBoss, kPDFPrefix + 21)
DECLARE_PMID(kClassIDSpace, kPDFExportRootBoss, kPDFPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPDFConversionProviderImplBoss, kPDFPrefix + 23)
DECLARE_PMID(kClassIDSpace, kPDFAGMViewPortBoss, kPDFPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetPDFAttributesCmdBoss, kPDFPrefix + 25)
DECLARE_PMID(kClassIDSpace, kAddPDFColorsCmdBoss, kPDFPrefix + 26)
DECLARE_PMID(kClassIDSpace, kSetPDFCBPrefsCmdBoss, kPDFPrefix + 27)
DECLARE_PMID(kClassIDSpace, kDisplayTitleInfoWidgetBoss, kPDFPrefix + 28)
DECLARE_PMID(kClassIDSpace, kPDFSummaryTreeViewWidgetBoss,	kPDFPrefix + 29)
DECLARE_PMID(kClassIDSpace, kPDFSummaryTreeNodeWidgetBoss,	kPDFPrefix + 30)
DECLARE_PMID(kClassIDSpace, kPDFTreeNodeTextWidgetBoss,	kPDFPrefix + 31)
DECLARE_PMID(kClassIDSpace, kSetPDFPostProcessPrefsCmdBoss, kPDFPrefix + 32)
DECLARE_PMID(kClassIDSpace, kPDFValidateSettingsNameBoss, kPDFPrefix + 33)
DECLARE_PMID(kClassIDSpace, kLanguagePreferenceWidgetBoss, kPDFPrefix + 34)
DECLARE_PMID(kClassIDSpace, kDisplayTitleDropDownInfoWidgetBoss, kPDFPrefix + 35)

// big gap

DECLARE_PMID(kClassIDSpace, kPDFPlacePanelBoss, kPDFPrefix + 128)
DECLARE_PMID(kClassIDSpace, kPDFExportDialogBoss, kPDFPrefix + 129)
DECLARE_PMID(kClassIDSpace, kCascadePlacePDFCmdBoss, kPDFPrefix + 130)
//gap
DECLARE_PMID(kClassIDSpace, kPDFExptDialogCompPanelBoss, kPDFPrefix + 132)
DECLARE_PMID(kClassIDSpace, kPDFExptDialogOptsPanelBoss, kPDFPrefix + 133)
DECLARE_PMID(kClassIDSpace, kPDFExptDialogPagesPanelBoss, kPDFPrefix + 134)
DECLARE_PMID(kClassIDSpace, kPDFOutputPanelBoss, kPDFPrefix + 135)
DECLARE_PMID(kClassIDSpace, kPDFPagePreviewWidgetBoss, kPDFPrefix + 136)
//gap
DECLARE_PMID(kClassIDSpace, kPDFBitmapButtonWidgetBoss, kPDFPrefix + 139)
//gap
DECLARE_PMID(kClassIDSpace, kPDFExptDialogSecurityPanelBoss, kPDFPrefix + 142)
DECLARE_PMID(kClassIDSpace, kPDFPasswordDialogBoss, kPDFPrefix + 143)
DECLARE_PMID(kClassIDSpace, kSetPDFPlacePrefsCmdBoss, kPDFPrefix + 144)
DECLARE_PMID(kClassIDSpace, kPDFErrorsDialogBoss, kPDFPrefix + 145)
DECLARE_PMID(kClassIDSpace, kPDFExportEditStyleDlgBoss, kPDFPrefix + 146)
//gap
DECLARE_PMID(kClassIDSpace, kPDFExportStyleMenuActionBoss, kPDFPrefix + 154)
DECLARE_PMID(kClassIDSpace, kPDFExptDialogCJKGridPanelBoss, kPDFPrefix + 155)
DECLARE_PMID(kClassIDSpace, kPDFSelDialogTNCheckBoxWidgetBoss, kPDFPrefix + 156)
//gap
// remove DECLARE_PMID(kClassIDSpace, kPDFEditNameDialogBoss, kPDFPrefix + 158)
#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kPDFLPlugInTestMenuBoss, kPDFPrefix + 157)
DECLARE_PMID(kClassIDSpace, kOutputAsciiStringsTestMenuBoss, kPDFPrefix + 160)	// moved to PDFUI
//DECLARE_PMID(kClassIDSpace, kOutputAltWordsTestMenuBoss, kPDFPrefix + 161)	// moved to PDFUI
#endif
DECLARE_PMID(kClassIDSpace, kPDFCodeConversionProviderImplBoss, kPDFPrefix + 162)
DECLARE_PMID(kClassIDSpace, kPDFSelDialogTreeNodeWidgetBoss, kPDFPrefix + 163)
DECLARE_PMID(kClassIDSpace, kPopulateXMLStructureBoss, kPDFPrefix + 164)
#ifdef DEBUG  
//DECLARE_PMID(kClassIDSpace, kPDFHyperlinksTestMenuBoss, kPDFPrefix + 167)	// moved to PDFUI
#endif
DECLARE_PMID(kClassIDSpace, kPDFExportBookBoss, kPDFPrefix + 168)
//DECLARE_PMID(kClassIDSpace, kPDFExpStyleNewWSResponderBoss, kPDFPrefix + 169)
DECLARE_PMID(kClassIDSpace, kPDFAdvancedPanelBoss, kPDFPrefix + 170)
DECLARE_PMID(kClassIDSpace, kPDFSummaryPanelBoss, kPDFPrefix + 171)

DECLARE_PMID(kClassIDSpace, kPDFSignalMgrBoss, kPDFPrefix + 172)
DECLARE_PMID(kClassIDSpace, kIntegerPercentageEditBoxWidgetBoss, kPDFPrefix + 173)

DECLARE_PMID(kClassIDSpace, kPDFCreateMetaDataCmdBoss, kPDFPrefix + 174)
DECLARE_PMID(kClassIDSpace, kPDFUtilsBoss, kPDFPrefix + 175)

DECLARE_PMID(kClassIDSpace, kExportPDFPrefScriptProviderBoss, kPDFPrefix + 176)
DECLARE_PMID(kClassIDSpace, kPDFSelDialogTreeViewWidgetBoss, kPDFPrefix + 177)
DECLARE_PMID(kClassIDSpace, kExportPDFStyleScriptProviderBoss, kPDFPrefix + 178)
DECLARE_PMID(kClassIDSpace, kExportPDFPropScriptProviderBoss, kPDFPrefix + 179)
DECLARE_PMID(kClassIDSpace, kExptGenStyleScriptProviderBoss, kPDFPrefix + 180)
DECLARE_PMID(kClassIDSpace, kPDFPlacePrefsScriptProviderBoss, kPDFPrefix + 181)
DECLARE_PMID(kClassIDSpace, kPDFAttributesScriptProviderBoss, kPDFPrefix + 182)
DECLARE_PMID(kClassIDSpace, kPDFDirectExportBoss, kPDFPrefix + 183)
#ifdef DEBUG  
DECLARE_PMID(kClassIDSpace, kBeLikeDistillerTestMenuBoss, kPDFPrefix + 184)	// moved to PDFUI
DECLARE_PMID(kClassIDSpace, kPlaceAllPagesBoss, kPDFPrefix + 185)
#endif
DECLARE_PMID(kClassIDSpace, kPDFPreviewConfigStateBoss, kPDFPrefix + 186)
DECLARE_PMID(kClassIDSpace, kPDFPreviewFeatureServiceBoss, kPDFPrefix + 187)
DECLARE_PMID(kClassIDSpace, kPDFFormXObjectGatherProviderBoss, kPDFPrefix + 188)
//
//InCopy
DECLARE_PMID(kClassIDSpace, kExportPDFGalleyPrefScriptObjectBoss, kPDFPrefix + 196)
DECLARE_PMID(kClassIDSpace, kExportPDFLayoutPrefScriptObjectBoss, kPDFPrefix + 197)
DECLARE_PMID(kClassIDSpace, kICExptPDFGalScriptProviderBoss, kPDFPrefix + 198)
DECLARE_PMID(kClassIDSpace, kICExptPDFLayScriptProviderBoss, kPDFPrefix + 199)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptDialogCmdBoss, kPDFPrefix + 200)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptDialogBoss, kPDFPrefix + 201)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptLayoutPanelBoss, kPDFPrefix + 202)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptGalleyPanelBoss, kPDFPrefix + 203)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptPanelPickerWidgetBoss, kPDFPrefix + 204)
DECLARE_PMID(kClassIDSpace, kPDFExportPrefsBoss, kPDFPrefix + 207)
DECLARE_PMID(kClassIDSpace, kPDFSecurityPrefsBoss, kPDFPrefix + 208)
DECLARE_PMID(kClassIDSpace, kInCopyPDFExptSecurityDialogBoss, kPDFPrefix + 209)
DECLARE_PMID(kClassIDSpace, kSaveInCopyPDFSecurityPrefsCmdBoss, kPDFPrefix + 212)
DECLARE_PMID(kClassIDSpace, kInCopyPDFNoteAnnotationsBoss, kPDFPrefix + 214)
//
DECLARE_PMID(kClassIDSpace, kExportCmdBossDupPrefsBoss, kPDFPrefix + 215)
//

DECLARE_PMID(kClassIDSpace, kPDFPlaceTabbedDialogBoss, kPDFPrefix + 216)
DECLARE_PMID(kClassIDSpace, kPDFLayersPanelBoss, kPDFPrefix + 217)
DECLARE_PMID(kClassIDSpace, kPDFChangeLayerDialogBoss, kPDFPrefix + 218)
DECLARE_PMID(kClassIDSpace, kPDFStlEdtExportStylesCmdBoss, kPDFPrefix + 219)
DECLARE_PMID(kClassIDSpace, kPDFStlEdtImportJobOptionsCmdBoss, kPDFPrefix + 220)
DECLARE_PMID(kClassIDSpace, kCheckExportSettingsCmdBoss, kPDFPrefix + 221)
DECLARE_PMID(kClassIDSpace, kPDFAnnihilatorBoss, kPDFPrefix + 222)

DECLARE_PMID(kClassIDSpace, kPDFExportStyleMgrDialogBoss, kPDFPrefix + 223)
DECLARE_PMID(kClassIDSpace, kPDFExportStyleMgrListBoxBoss, kPDFPrefix + 224)
DECLARE_PMID(kClassIDSpace, kPDFExportStyleMenuBoss, kPDFPrefix + 225)
DECLARE_PMID(kClassIDSpace, kJobOptionsImportProviderBoss, kPDFPrefix + 226)
DECLARE_PMID(kClassIDSpace, kJobOptionsOpenProviderBoss, kPDFPrefix + 227)
DECLARE_PMID(kClassIDSpace, kPDFPromptForPasswordsCmdBoss, kPDFPrefix + 228)

//DECLARE_PMID(kClassIDSpace, kPDFReviewImporterBoss, kPDFPrefix + 229)			PDFComment& Review
//DECLARE_PMID(kClassIDSpace, kPDFReviewImportMenuActionBoss, kPDFPrefix + 230)	PDFComment& Review
//DECLARE_PMID(kClassIDSpace, kPDFReviewImportPanelBoss, kPDFPrefix + 231)		PDFComment& Review

DECLARE_PMID(kClassIDSpace, kInteractivePDFExportCmdBoss, kPDFPrefix + 232)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportBoss, kPDFPrefix + 233)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportBookBoss, kPDFPrefix + 234)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportDialogBoss, kPDFPrefix + 235)
DECLARE_PMID(kClassIDSpace, kSetInteractivePDFExportPrefsCmdBoss, kPDFPrefix + 236)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportPrefsScriptProviderBoss, kPDFPrefix + 237)
DECLARE_PMID(kClassIDSpace, kPageTransitionFromDocumentClassID, kPDFPrefix + 238)	// placeholder only
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportSecurityDialogBoss, kPDFPrefix + 239)
DECLARE_PMID(kClassIDSpace, kPDFLinksChangedResponderBoss, kPDFPrefix + 240)
DECLARE_PMID(kClassIDSpace, kSetPDFStructureOrderPrefCmdBoss, kPDFPrefix + 241)
DECLARE_PMID(kClassIDSpace, kTaggedPDFPrefsScriptProviderBoss, kPDFPrefix + 242)
DECLARE_PMID(kClassIDSpace, kPDFNewDocResponderBoss, kPDFPrefix + 243)
DECLARE_PMID(kClassIDSpace, kInteractivePDFGeneralDialogBoss, kPDFPrefix + 244)
DECLARE_PMID(kClassIDSpace, kInteractivePDFSelDialogTreeViewWidgetBoss, kPDFPrefix + 245)
DECLARE_PMID(kClassIDSpace, kInteractivePDFTreeViewWidgetBoss, kPDFPrefix + 246)
DECLARE_PMID(kClassIDSpace, kInteractivePDFActionComponentBoss, kPDFPrefix + 247)
DECLARE_PMID(kClassIDSpace, kInteractivePDFDialogBoss, kPDFPrefix + 248)
DECLARE_PMID(kClassIDSpace, kInteractivePDFTreeNodeWidgetBoss, kPDFPrefix + 249)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportGeneralDialogBoss, kPDFPrefix + 250)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportAdvancedDialogBoss, kPDFPrefix + 251)
DECLARE_PMID(kClassIDSpace, kInteractivePDFExportCompressionDialogBoss, kPDFPrefix + 252)

#ifdef DEBUG
// Test menus moved to PDFUI
DECLARE_PMID(kClassIDSpace, kFontNamesTestMenuBoss, kPDFPrefix + 253)
//DECLARE_PMID(kClassIDSpace, kFourByteGlyphsTestMenuBoss, kPDFPrefix + 254)
	// Keep this debug boss at the end
DECLARE_PMID(kClassIDSpace, kPDFTestMenuBoss, kPDFPrefix + 255)
#endif // DEBUG
//gap

DECLARE_PMID(kClassIDSpace, kSetPDFExportRetainFileNamePrefCmdBoss, kPDFExtraPrefix + 1)


DECLARE_PMID(kClassIDSpace, kSinglePagePDFSuffixButtonWidgetBoss, kPDFExtraPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSinglePagePDFSuffixActionComponentBoss, kPDFExtraPrefix + 3)

DECLARE_PMID(kClassIDSpace, kPDFCommentImportProviderBoss, kPDFExtraPrefix + 4)
DECLARE_PMID(kClassIDSpace, kImportPDFAnnotationBoss, kPDFExtraPrefix + 5)
DECLARE_PMID(kClassIDSpace, kStickyNoteAnnotationBoss, kPDFExtraPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHighlightAnnotationBoss, kPDFExtraPrefix + 7)
DECLARE_PMID(kClassIDSpace, kStrikethroughAnnotationBoss, kPDFExtraPrefix + 8)
DECLARE_PMID(kClassIDSpace, kUnderlineAnnotationBoss, kPDFExtraPrefix + 9)
DECLARE_PMID(kClassIDSpace, kReplaceTextAnnotationBoss, kPDFExtraPrefix + 10)
DECLARE_PMID(kClassIDSpace, kInsertTextAnnotationBoss, kPDFExtraPrefix + 11)
DECLARE_PMID(kClassIDSpace, kTextCommentAnnotationBoss, kPDFExtraPrefix + 12)
DECLARE_PMID(kClassIDSpace, kTextBoxAnnotationBoss, kPDFExtraPrefix + 13)
DECLARE_PMID(kClassIDSpace, kFreeFormAnnotationBoss, kPDFExtraPrefix + 14)
DECLARE_PMID(kClassIDSpace, kLineAnnotationBoss, kPDFExtraPrefix + 15)
DECLARE_PMID(kClassIDSpace, kArrowAnnotationBoss, kPDFExtraPrefix + 16)
DECLARE_PMID(kClassIDSpace, kRectangleAnnotationBoss, kPDFExtraPrefix + 17)
DECLARE_PMID(kClassIDSpace, kOvalAnnotationBoss, kPDFExtraPrefix + 18)
DECLARE_PMID(kClassIDSpace, kTextCalloutAnnotationBoss, kPDFExtraPrefix + 19)
DECLARE_PMID(kClassIDSpace, kBaseAnnotationDestinationBoss, kPDFExtraPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAnnotationPageDestinationBoss, kPDFExtraPrefix + 21)
DECLARE_PMID(kClassIDSpace, kAnnotationPageItemDestinationBoss, kPDFExtraPrefix + 22)
DECLARE_PMID(kClassIDSpace, kAnnotationTextDestinationBoss, kPDFExtraPrefix + 23)
DECLARE_PMID(kClassIDSpace, kAnnotationTextDestinationMementoBoss, kPDFExtraPrefix + 24)
DECLARE_PMID(kClassIDSpace, kPDFCommentAdornmentBoss, kPDFExtraPrefix + 25)
DECLARE_PMID(kClassIDSpace, kAnnnotationPointMapperBoss, kPDFExtraPrefix + 26)
DECLARE_PMID(kClassIDSpace, kAnnnotationRectMapperBoss, kPDFExtraPrefix + 27)
DECLARE_PMID(kClassIDSpace, kAnnnotationRangeMapperBoss, kPDFExtraPrefix + 28)
//annotation reply bosses
DECLARE_PMID(kClassIDSpace, kReplyBoss, kPDFExtraPrefix + 29)

//annotation cmd bosses
DECLARE_PMID(kClassIDSpace, kNewAnnotationPageDestCmdBoss, kPDFExtraPrefix + 30)
DECLARE_PMID(kClassIDSpace, kDeleteAnnotationPageDestCmdBoss, kPDFExtraPrefix + 31)
DECLARE_PMID(kClassIDSpace, kNewAnnotationPageItemDestCmdBoss, kPDFExtraPrefix + 32)
DECLARE_PMID(kClassIDSpace, kDeleteAnnotationPageItemDestCmdBoss, kPDFExtraPrefix + 33)
DECLARE_PMID(kClassIDSpace, kNewAnnotationTextDestCmdBoss, kPDFExtraPrefix + 34)
DECLARE_PMID(kClassIDSpace, kDeleteAnnotationTextDestCmdBoss, kPDFExtraPrefix + 35)
DECLARE_PMID(kClassIDSpace, kChangeAnnotationTextDestCmdBoss, kPDFExtraPrefix + 36)
DECLARE_PMID(kClassIDSpace, kDeleteAnnotationDestinationCmdBoss, kPDFExtraPrefix + 37)
DECLARE_PMID(kClassIDSpace, kNewAnnotationCmdBoss, kPDFExtraPrefix + 38)
DECLARE_PMID(kClassIDSpace, kDeleteAnnotationCmdBoss, kPDFExtraPrefix + 39)
DECLARE_PMID(kClassIDSpace, kChangeAnnotationCmdBoss, kPDFExtraPrefix + 40)
DECLARE_PMID(kClassIDSpace, kNewReplyCmdBoss, kPDFExtraPrefix + 41)
DECLARE_PMID(kClassIDSpace, kDeleteReplyCmdBoss, kPDFExtraPrefix + 42)
DECLARE_PMID(kClassIDSpace, kSquigglyAnnotationBoss, kPDFExtraPrefix + 43)

//New annotation types supported. Addition after kTextCalloutAnnotationBoss 
DECLARE_PMID(kClassIDSpace, kPolygonAnnotationBoss, kPDFExtraPrefix + 44)
DECLARE_PMID(kClassIDSpace, kConnectedLinesAnnotationBoss, kPDFExtraPrefix + 45)
DECLARE_PMID(kClassIDSpace, kCloudAnnotationBoss, kPDFExtraPrefix + 46)
DECLARE_PMID(kClassIDSpace, kPDFExportDialogClosedBoss, kPDFExtraPrefix + 47)
DECLARE_PMID(kClassIDSpace, kStampAnnotationBoss, kPDFExtraPrefix + 48)

DECLARE_PMID(kClassIDSpace, kAnnotationScriptProviderBoss, kPDFExtraPrefix + 49)
DECLARE_PMID(kClassIDSpace, kReplyScriptProviderBoss, kPDFExtraPrefix + 50)
DECLARE_PMID(kClassIDSpace, kAnnotationPageDestinationScriptProviderBoss, kPDFExtraPrefix + 51)
DECLARE_PMID(kClassIDSpace, kAnnotationPageItemDestinationScriptProviderBoss, kPDFExtraPrefix + 52)
DECLARE_PMID(kClassIDSpace, kAnnotationTextDestinationScriptProviderBoss, kPDFExtraPrefix + 53)
DECLARE_PMID(kClassIDSpace, kPDFCommentsDocScriptProviderBoss, kPDFExtraPrefix + 54)

DECLARE_PMID(kClassIDSpace, kImportPDFCommentsOptionsDialogBoss, kPDFExtraPrefix + 55)
DECLARE_PMID(kClassIDSpace, kImportPDFCommentOptionsPagePreviewWidgetBoss, kPDFExtraPrefix + 56)
//DECLARE_PMID(kClassIDSpace, kImportPDFCOPageNumberWidgetBoss, kPDFExtraPrefix + 57)
DECLARE_PMID(kClassIDSpace, kNewRCAnnotationCmdBoss, kPDFExtraPrefix + 59)
DECLARE_PMID(kClassIDSpace, kRCAnnotationBoss, kPDFExtraPrefix +60)
DECLARE_PMID(kClassIDSpace, kRCPinToolAnnotationBoss, kPDFExtraPrefix + 61)
DECLARE_PMID(kClassIDSpace, kRCFreeFormAnnotationBoss, kPDFExtraPrefix + 62)
DECLARE_PMID(kClassIDSpace, kNewRCAnnotationPageDestCmdBoss, kPDFExtraPrefix + 63)
DECLARE_PMID(kClassIDSpace, kDeleteRCAnnotationCmdBoss, kPDFExtraPrefix + 64)
DECLARE_PMID(kClassIDSpace, kDeleteRCAnnotationDestinationCmdBoss, kPDFExtraPrefix + 65)
DECLARE_PMID(kClassIDSpace, kNewRCAnnotationPageItemDestCmdBoss, kPDFExtraPrefix + 66)
DECLARE_PMID(kClassIDSpace, kRCHighlightAnnotationBoss, kPDFExtraPrefix + 67)
DECLARE_PMID(kClassIDSpace, kRCStrikethroughAnnotationBoss, kPDFExtraPrefix + 68)
DECLARE_PMID(kClassIDSpace, kNewRCAnnotationTextDestCmdBoss, kPDFExtraPrefix + 69)
DECLARE_PMID(kClassIDSpace, kRCReplaceTextAnnotationBoss, kPDFExtraPrefix + 70)

// <Interface ID>
//----------------------------------------------------------------------------------------
//
// Interface ids
//

DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEPDFCMDDATA, kPDFPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTNAMES, kPDFPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFATTRIBUTES, kPDFPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMDISPLAYLIST, kPDFPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFDOCPORT, kPDFPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTPREFSCMDDATA, kPDFPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTPREFS, kPDFPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTCONTROLLER, kPDFPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTPREFSDUP, kPDFPrefix + 9)  // another IID_IPDFEXPORTPREFS
DECLARE_PMID(kInterfaceIDSpace, IID_IREADTILESRVIMAGESTREAMDATA, kPDFPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFLIBERRORINFO, kPDFPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFDESTCMSPROFILE, kPDFPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFGSTATESTACK, kPDFPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPASSWORDINFO, kPDFPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPLACEPREFS, kPDFPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSECURITYPREFS, kPDFPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSEPROGRESSINDICATOR, kPDFPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPLACEUTILS, kPDFPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSTYLELISTMGR, kPDFPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSTYLECMDDATA, kPDFPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSTYLELASTUSED, kPDFPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPLACEPREFSDUP, kPDFPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSTYLELOCKINFO, kPDFPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXTRAREFERENCE, kPDFPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGERANGE, kPDFPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFCLIPBOARDPREFS, kPDFPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFCLIPBOARDEXPORTPREFS, kPDFPrefix + 27)		// dup of IID_IPDFEXPORTPREFS
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFCLIPBOARDPLACEPREFS, kPDFPrefix + 28)		// dup of IID_IPDFPLACEPREFS
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRUCTUREMARKS, kPDFPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETPDFCBPREFSCMDDATA, kPDFPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEPDFPLACECMDDATA, kPDFPrefix + 31)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEPDFDIALOGUI, kPDFPrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPASSWORDDIALOGDATA, kPDFPrefix + 130)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPLACEDIALOGSTATUS, kPDFPrefix + 131)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSTYLENAME, kPDFPrefix + 132)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFCOLORXFORMCHANGEOBSERVER, kPDFPrefix + 152)
DECLARE_PMID(kInterfaceIDSpace, IID_ILANGUAGELETTERCODE, kPDFPrefix + 153)
// Remove DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEDITNAMEDATA, kPDFPrefix + 154)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSTRUCTURETREE, kPDFPrefix + 155)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSTORYLIST, kPDFPrefix + 156)
DECLARE_PMID(kInterfaceIDSpace, IID_IFIGUREELEMENT, kPDFPrefix + 157)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETPDFATTRIBUTESCMDDATA, kPDFPrefix + 158)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPULATEXMLSTRUCTURE, kPDFPrefix + 159)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPMPDFTRANSPARENCYDATA, kPDFPrefix + 160)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFFLATTENERPARAMS, kPDFPrefix + 161)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDPDFCOLORSCMDDATA, kPDFPrefix + 162)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFHYPERLINKS, kPDFPrefix + 163)
DECLARE_PMID(kInterfaceIDSpace, IID_IREBUILDPROFILEPOPUP, kPDFPrefix + 164)
DECLARE_PMID(kInterfaceIDSpace, IID_IORDERTOPLEVELITEMS, kPDFPrefix + 165)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSIGNALDATA, kPDFPrefix + 166)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTUTILS, kPDFPrefix + 167)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFCREATEMETATDATACMDDATA, kPDFPrefix + 168)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFUTILS, kPDFPrefix+169)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSPY, kPDFPrefix + 170)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARENTANDCONTAINER, kPDFPrefix + 171)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPREVIEWFLAG, kPDFPrefix + 172)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPREVIEWCONFIGSTATEDATA, kPDFPrefix + 173)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTERMARKS, kPDFPrefix + 174)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTERMARKSDATA, kPDFPrefix + 175)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFTHREADREFERENCEOBSERVER, kPDFPrefix + 176)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFAPPRESUMEOBSERVER, kPDFPrefix + 177)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUMMARYINFO, kPDFPrefix + 178)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSTYLEDIALOGUTILS, kPDFPrefix + 179)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPOSTPROCESSPREFS, kPDFPrefix + 180)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPOSTPROCESSPREFSDUP, kPDFPrefix + 181)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPRESETSCRIPTUTILS, kPDFPrefix + 182)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHECKPRESET, kPDFPrefix + 183)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEDIALOGANDPANEL, kPDFPrefix + 184)
DECLARE_PMID(kInterfaceIDSpace, IID_IVALIDATENAME, kPDFPrefix + 185)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPRESETNAMEUTILS, kPDFPrefix + 186)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFLIBRARYUTILS, kPDFPrefix + 187)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTSETUPPROVIDER, kPDFPrefix + 188)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFFORMXOBJECTDATA, kPDFPrefix + 189)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFFORMXOBJECTFORMDATA, kPDFPrefix + 190)
DECLARE_PMID(kInterfaceIDSpace, IID_IMERGEEXPORTTOPDF, kPDFPrefix + 191)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFFORMXOBJECTSETUPPROVIDER, kPDFPrefix + 192)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFFORMXPDATA, kPDFPrefix + 193)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFREPOSITIONBBOXDATA, kPDFPrefix + 194 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFPRESETUTILS, kPDFPrefix + 195 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTOUTPUTPAGES, kPDFPrefix + 196 )
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEPDFEXPORTPREFS_2, kPDFPrefix + 197)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEPDFEXPORTPREFS_3, kPDFPrefix + 198)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTSINGLEPAGESINTERACTIVE, kPDFPrefix + 199)

// InCopy
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPDFEXPTDIALOGDATA, kPDFPrefix + 202)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPDFNOTEANNOTATIONDATA, kPDFPrefix + 203)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPDFNOTEANNOTATIONS, kPDFPrefix + 204)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFDOCPORT2, kPDFPrefix + 205)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYABLEINMEMORYCACHE, kPDFPrefix + 206)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECURITY128BITS, kPDFPrefix + 207)

DECLARE_PMID(kInterfaceIDSpace, IID_IPDFREVIEWIMPORTER, kPDFPrefix + 208)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFLIBRARYUTILSPUBLIC, kPDFPrefix + 209)



// DEBUG ONLY
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFDEBUGFLAGS, kPDFPrefix + 210)

DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEPDFEXPORT, kPDFPrefix + 211)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEPDFEXPORTPREFS, kPDFPrefix + 212)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEPDFEXPORTPAGERANGE, kPDFPrefix + 213)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEPDFEXPORTFACADE, kPDFPrefix + 214)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFDPARTHIERARCHY, kPDFPrefix + 215)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFDPARTMETADATAUTILS, kPDFPrefix + 216)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFVTPORT, kPDFPrefix + 217)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSTRUCTUREORDERPREF, kPDFPrefix + 218)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFSTRUCTUREORDERPREFFACADE, kPDFPrefix + 219)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAMERGEPDFEXPORT, kPDFPrefix + 220)

DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTTITLE, kPDFPrefix + 221)
DECLARE_PMID(kInterfaceIDSpace, IID_ILANGUAGELISTHANDLER, kPDFPrefix + 222)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTRETAINFILENAMEDATA, kPDFPrefix + 223)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURRENTPAGEBEINGEXPORTED, kPDFPrefix + 224)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARENTDIRECTORY, kPDFPrefix + 225)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTFILENAME, kPDFPrefix + 226)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATESUFFIXFIELD, kPDFPrefix + 227)

DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTSIMPORTPROVIDER, kPDFExtraPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFUTILS, kPDFExtraPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFANNOTATION, kPDFExtraPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IICONANNOTATIONDATA, kPDFExtraPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IRANGEANNOTATIONDATA, kPDFExtraPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHANNOTATIONDATA, kPDFExtraPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONDESTINATION, kPDFExtraPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONPAGEDESTINATIONDATA, kPDFExtraPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONPAGEITEMDESTINATIONDATA, kPDFExtraPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONTEXTDESTINATIONDATA, kPDFExtraPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONPOINTMAPPERDATA, kPDFExtraPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONIMPORTMAPPER, kPDFExtraPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONRECTMAPPERDATA, kPDFExtraPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEANNOTATIONDATATOMODEL, kPDFExtraPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONRANGEMAPPERDATA, kPDFExtraPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONMAPPERUTILS, kPDFExtraPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONORCHESTRATOR, kPDFExtraPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLY, kPDFExtraPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLYLIST, kPDFExtraPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONTEXTDESTINATIONCMDDATA, kPDFExtraPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONPAGEDESTINATIONCMDDATA, kPDFExtraPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONPAGEITEMDESTINATIONCMDDATA, kPDFExtraPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTTABLE, kPDFExtraPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEANNOTATIONUTILS, kPDFExtraPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONOBSERVER, kPDFExtraPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTDESTINATIONCHANGE, kPDFExtraPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONCHANGE, kPDFExtraPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONFACADE, kPDFExtraPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONCMDDATA, kPDFExtraPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLYCMDDATA, kPDFExtraPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IISAPPLIEDBOOLDATA, kPDFExtraPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONUTILS, kPDFExtraPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIOUSHIGHLIGHTUID, kPDFExtraPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONSUITE, kPDFExtraPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTLISTCACHE, kPDFExtraPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFCOMMENTOPTIONSDIALOGSTATUS, kPDFExtraPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFCOMMENTOPTIONSPREFS, kPDFExtraPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IRCCOMMENTTABLE, kPDFExtraPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONBASE, kPDFExtraPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IRCANNOTATION, kPDFExtraPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IRCANNOTATIONCMDDATA, kPDFExtraPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IANNOTATIONUIUTILS, kPDFExtraPrefix + 42 )

// <Implementation ID>
//----------------------------------------------------------------------------------------
//
// Implementation ids
//

DECLARE_PMID(kImplementationIDSpace, kPDFPlaceProviderImpl, kPDFPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceCmdImpl, kPDFPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPDFShapeImpl, kPDFPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCPDFExportPrefsDupImpl, kPDFPrefix + 4)  // allows 2 kCPDFExportPrefsImpl on same boss.
DECLARE_PMID(kImplementationIDSpace, kPDFAttributesImpl, kPDFPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPDFTrackerRegisterImpl, kPDFPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPDFDisplayListImpl, kPDFPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPDFExportCmdImpl, kPDFPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPDFGenericGraphicsPortImpl, kPDFPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPDFDocPortImpl, kPDFPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSetPDFExportPrefsCmdImpl, kPDFPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCPDFExportPrefsImpl, kPDFPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPDFExportControllerImpl, kPDFPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kPDFLibComponentVersionImpl, kPDFPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPDFExportProviderImpl, kPDFPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSetPDFSecurityPrefsCmdImpl, kPDFPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kReadTileSrvImageStreamImpl, kPDFPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kReadTileSrvImageStreamDataImpl, kPDFPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceBehaviorImpl, kPDFPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kPDFErrorStringServiceImpl, kPDFPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPDFLibErrorInfoImpl, kPDFPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPDFGStateStackImpl, kPDFPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kDeletePDFItemCmdImpl, kPDFPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPDFItemScrapImpl, kPDFPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPDFPasswordInfoImpl, kPDFPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kPDFViewPortAttributesImpl, kPDFPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kPDFPlacePrefsImpl, kPDFPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSetPDFPlacePrefsCmdImpl, kPDFPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kPDFPlacePrefsDupImpl, kPDFPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCPDFSecurityPrefsImpl, kPDFPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPDFExportItemsCmdImpl, kPDFPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPDFEditStyleCmdImpl, kPDFPrefix + 32)

DECLARE_PMID(kImplementationIDSpace, kPDFStoreInternalImpl, kPDFPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kPDFItemInkResourcesImpl, kPDFPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kPDFCropAttributesImpl, kPDFPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPDFExptStyleListMgrImpl, kPDFPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPDFExptSetStyleNameCmdImpl, kPDFPrefix + 37	)
DECLARE_PMID(kImplementationIDSpace, kPDFExptAddStyleCmdImpl, kPDFPrefix + 38		)
DECLARE_PMID(kImplementationIDSpace, kPDFExptDeleteStyleCmdImpl, kPDFPrefix + 39		)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceUtilsImpl, kPDFPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPDFFontNamesImpl, kPDFPrefix + 41)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kFontNamesTestMenuImpl, kPDFPrefix + 42)	// moved to PDFUI
#endif
DECLARE_PMID(kImplementationIDSpace, kPageRangeImpl, kPDFPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kPDFConversionProviderImpl, kPDFPrefix + 44)

DECLARE_PMID(kImplementationIDSpace, kFigureElementOptionalImpl_Obsolete, kPDFPrefix + 45)
#ifdef DEBUG  
DECLARE_PMID(kImplementationIDSpace, kBeLikeDistillerTestMenuImpl, kPDFPrefix + 46)	// moved to PDFUI
#endif
DECLARE_PMID(kImplementationIDSpace, kCascadePlacePDFCmdImpl, kPDFPrefix + 48)
#ifdef DEBUG  
	DECLARE_PMID(kImplementationIDSpace, kPlaceAllPagesImpl, kPDFPrefix + 49)
#endif

//
//InCopy
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptDialogControllerImpl, kPDFPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptDialogCreatorImpl, kPDFPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptDialogObserverImpl, kPDFPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptDialogDataImpl, kPDFPrefix + 53)		// Print galley data for user to edit
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptGalleyControllerImpl, kPDFPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptGalleyObserverImpl, kPDFPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptGalleyCreatorImpl, kPDFPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptLayoutControllerImpl, kPDFPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptLayoutObserverImpl, kPDFPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptLayoutCreatorImpl, kPDFPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptSecurityDialogControllerImpl, kPDFPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptSecurityDialogCreatorImpl, kPDFPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptSecurityDialogObserverImpl, kPDFPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kSaveInCopyPDFSecurityPrefsCmdImpl, kPDFPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFNoteAnnotationsImpl, kPDFPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kICExptPDFGalScriptProviderImpl, kPDFPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kICExptPDFLayScriptProviderImpl, kPDFPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kPDFPostProcessPrefsImpl, kPDFPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kPDFPostProcessPrefsDupImpl, kPDFPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kSetPDFPostProcessPrefsCmdImpl, kPDFPrefix + 74)

DECLARE_PMID(kImplementationIDSpace, kDynDocsStructureMarksImpl, kPDFPrefix + 75)	// This impl should be in dynamicdocuments plugin, but in order to avoid some compile and link issues, we put it in pdf plugin.

DECLARE_PMID(kImplementationIDSpace, kPDFPreviewConfigProviderImpl, kPDFPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewConfigServiceImpl, kPDFPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewConfigStateImpl, kPDFPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewConfigStateDataImpl, kPDFPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewDrawStratDataImpl, kPDFPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewDrawStrategyImpl, kPDFPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewFeatureProviderImpl, kPDFPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kPDFPreviewFeatureServiceImpl,  kPDFPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kInCopyPDFExptSecurity128BitsImpl,  kPDFPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kParentDirImpl, kPDFPrefix + 89)
//
DECLARE_PMID(kImplementationIDSpace, kPDFPlacePanelObserverImpl, kPDFPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kPDFPlacePanelControllerImpl, kPDFPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceDialogDataImpl, kPDFPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kPDFPageNumberEventHandlerImpl, kPDFPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kPDFPagePreviewViewImpl, kPDFPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kPDFPasswordDialogDataImpl, kPDFPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kPDFPasswordDialogObserverImpl, kPDFPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kPDFPasswordDialogControllerImpl, kPDFPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceDialogStatusImpl, kPDFPrefix + 138)
//
DECLARE_PMID(kImplementationIDSpace, kPDFExportDialogControllerImpl, kPDFPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kPDFExportDialogCreatorImpl, kPDFPrefix + 141)
//#define kPDFExportDialogData				kPDFPrefix + 142
DECLARE_PMID(kImplementationIDSpace, kPDFExptCompObserverImpl, kPDFPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kPDFExptCompControllerImpl, kPDFPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kPDFExptCompPanelCreatorImpl, kPDFPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kPDFExptOptsObserverImpl, kPDFPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kPDFExptOptsControllerImpl, kPDFPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kPDFExptOptsPanelCreatorImpl, kPDFPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kPDFExptPagesObserverImpl, kPDFPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kPDFExptPagesControllerImpl, kPDFPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kPDFExptPagesPanelCreatorImpl, kPDFPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kPlacePDFDialogUIImpl, kPDFPrefix + 154)
//gap
DECLARE_PMID(kImplementationIDSpace, kPDFExptSecurityObserverImpl, kPDFPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kPDFExptSecurityControllerImpl, kPDFPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kPDFExptSecurityPanelCreatorImpl, kPDFPrefix + 159)
//gap
DECLARE_PMID(kImplementationIDSpace, kPDFColorXFormObserverImpl, kPDFPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kPDFDrawEventHandlerImpl, kPDFPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kPDFSwatchReferenceDataImpl, kPDFPrefix + 170)

DECLARE_PMID(kImplementationIDSpace, kPDFExportDialogObserverImpl, kPDFPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kPDFExportEditStyleDlgCrtrImpl, kPDFPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleNameImpl, kPDFPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleMenuActionImpl, kPDFPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kPDFExptStyleLockInfoImpl, kPDFPrefix + 175)

DECLARE_PMID(kImplementationIDSpace, kPDFExptCJKGridControllerImpl, kPDFPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kPDFExptCJKGridObserverImpl, kPDFPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kPDFExptCJKGridPanelCreatorImpl, kPDFPrefix + 178)

DECLARE_PMID(kImplementationIDSpace, kPDFImportPreviewImpl, kPDFPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kPDFClipboardPrefsImpl, kPDFPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kPDFClipboardExportPrefsImpl, kPDFPrefix + 181)		// alias for kCPDFExportPrefsImpl, used for clipboard
DECLARE_PMID(kImplementationIDSpace, kPDFClipboardPlacePrefsImpl, kPDFPrefix + 182)		// alias for kPDFPlacePrefsImpl, used for clipboard
DECLARE_PMID(kImplementationIDSpace, kLanguageLetterCodeImpl, kPDFPrefix + 183)

DECLARE_PMID(kImplementationIDSpace, kPDFVisitorHelperImpl, kPDFPrefix + 184)
// Remove DECLARE_PMID(kImplementationIDSpace, kPDFEditNameDataImpl, kPDFPrefix + 185)
// Remove DECLARE_PMID(kImplementationIDSpace, kPDFEditNameDialogImpl, kPDFPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kPDFStructureTreeImpl, kPDFPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kPDFStoryListImpl, kPDFPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kFigureElementImpl, kPDFPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kPMPDFTransparencyDataImpl, kPDFPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kPDFItemFlattenerUsageImpl, kPDFPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kPDFFlattenerParamsImpl, kPDFPrefix + 192)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kPDFLPlugInTestMenuImpl, kPDFPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kOutputAsciiStringsTestMenuImpl, kPDFPrefix + 194)	// moved to PDFUI
//DECLARE_PMID(kImplementationIDSpace, kOutputAltWordsTestMenuImpl, kPDFPrefix + 195)	// moved to PDFUI
#endif
DECLARE_PMID(kImplementationIDSpace, kPDFStructureMarksImpl, kPDFPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kSetPDFAttributesCmdDataImpl, kPDFPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kSetPDFAttributesCmdImpl, kPDFPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kPopulateXMLStructureImpl, kPDFPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceBehaviorUIImpl, kPDFPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kAddPDFColorsCmdImpl, kPDFPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kAddPDFColorsCmdDataImpl, kPDFPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kSetPDFClipboardPrefsCmdImpl, kPDFPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kSetPDFCBPrefsCmdDataImpl, kPDFPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kPDFHyperlinksImpl, kPDFPrefix + 208)
#ifdef DEBUG  
//	DECLARE_PMID(kImplementationIDSpace, kPDFHyperlinksTestMenuImpl, kPDFPrefix + 209)	// moved to PDFUI
#endif

	//DECLARE_PMID(kImplementationIDSpace, kPDFExpStyleNewWSResponderImpl, kPDFPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kPDFAdvancedPanelCreatorImpl, kPDFPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kPDFAdvancedControllerImpl, kPDFPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kPDFAdvancedObserverImpl, kPDFPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kRebuildProfilePopupImpl, kPDFPrefix + 214)

DECLARE_PMID(kImplementationIDSpace, kPrivatePDFPlaceCmdDataImpl, kPDFPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kPDFSummaryPanelViewImpl, kPDFPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kPDFSummaryControllerImpl, kPDFPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kPDFSummaryObserverImpl, kPDFPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kPDFSummaryCreatorImpl, kPDFPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kOrderTopLevelItemsImpl, kPDFPrefix + 220)

DECLARE_PMID(kImplementationIDSpace, kPDFSignalDataImpl, kPDFPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kStartPDFDocumentSignalResponderServiceImpl, kPDFPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kEndPDFDocumentSignalResponderServiceImpl, kPDFPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kStartPDFPageSignalResponderServiceImpl, kPDFPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kEndPDFPageSignalResponderServiceImpl, kPDFPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kIntegerPercentageEditBoxValidationImpl, kPDFPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kPDFXPPageItemDrawSetupImpl, kPDFPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kPDFExportUtilsImpl, kPDFPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kPDFCreateMetaDataCmdImpl, kPDFPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kPDFCreateMetaDataCmdDataImpl, kPDFPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kPDFUtilsImpl, kPDFPrefix + 231)

DECLARE_PMID(kImplementationIDSpace, kExportPDFPrefScriptProviderImpl, kPDFPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kPDFThreadReferenceObserverImpl, kPDFPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kPDFExtraReferenceImpl, kPDFExtraPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kExportPDFStyleScriptImpl, kPDFPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kExportPDFStyleScriptProviderImpl, kPDFPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kExportPDFPropScriptProviderImpl, kPDFPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kExptGenStyleScriptProviderImpl, kPDFPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kPDFPlacePrefsScriptProviderImpl, kPDFPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kPDFAttributesScriptProviderImpl, kPDFPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kParentAndContainerImpl, kPDFPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kPDFCacheHintsImpl, kPDFPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kPDFStyleDynMenuInfoImpl, kPDFPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kDirectPDFExportServiceImpl, kPDFPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kPDFPageItemNameImpl, kPDFPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kPrinterMarksImpl, kPDFPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kPrinterMarksDataImpl, kPDFPrefix + 247)
DECLARE_PMID(kImplementationIDSpace, kPDFCopyDisplayListInMemoryCacheImpl, kPDFPrefix + 248)

DECLARE_PMID(kImplementationIDSpace, kPDFPlaceTabbedDialogCreatorImpl, kPDFPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceTabbedDialogControllerImpl, kPDFPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kPDFPlaceTabbedDialogObserverImpl, kPDFPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kPDFPlacePanelCreatorImpl, kPDFPrefix + 252)

#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kPDFDebugFlagsImpl, kPDFPrefix + 253)	// Keep this debug implementation at the end
//DECLARE_PMID(kImplementationIDSpace, kFourByteGlyphsTestMenuImpl, kPDFPrefix + 254)	// moved to PDFUI
DECLARE_PMID(kImplementationIDSpace, kPDFTestMenuImpl, kPDFPrefix + 255)	// test menu moved to PDFUI
#endif // DEBUG

// switch over to using kPDFExtraPrefix for kImplementationIDSpace here!!! 
DECLARE_PMID(kImplementationIDSpace, kPDFLayersPanelCreatorImpl, kPDFExtraPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPDFLayersPanelControllerImpl, kPDFExtraPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPDFChangeLayerDialogControllerImpl, kPDFExtraPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPDFChangeLayerDialogObserverImpl, kPDFExtraPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPDFLayersPanelObserverImpl, kPDFExtraPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPDFPresetDynamicMenuImpl, kPDFExtraPrefix + 6)

//gap
DECLARE_PMID(kImplementationIDSpace, kPDFStlEdtExportStylesCmdImpl, kPDFExtraPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPDFStlEdtImportJobOptionsCmdImpl, kPDFExtraPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSummaryTreeViewAdapterImpl, kPDFExtraPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSummaryTreeViewWidgetMgrImpl, kPDFExtraPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSummaryInfoImpl, kPDFExtraPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPDFSummaryTNControlViewImpl, kPDFExtraPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPDFOutputPanelCreatorImpl, kPDFExtraPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kPDFOutputControllerImpl, kPDFExtraPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPDFOutputObserverImpl, kPDFExtraPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kPDFSelDialogTreeViewWidgetMgrImpl, kPDFExtraPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPDFSelDialogTreeViewAdapterImpl, kPDFExtraPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPDFTreeViewSelDlgSwitcherImpl, kPDFExtraPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleDialogControllerImpl, kPDFExtraPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleDialogObserverImpl, kPDFExtraPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleDialogListBoxEHImpl, kPDFExtraPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleDialogListBoxCtrlImpl, kPDFExtraPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleDialogUtilsImpl, kPDFExtraPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPDFExportStyleActionComponentImpl, kPDFExtraPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCheckExportSettingsCmdImpl, kPDFExtraPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kPDFAppResumeObserverImpl, kPDFExtraPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPDFStartupShutdownImpl, kPDFExtraPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPDFStartupServiceImpl, kPDFExtraPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kJobOptionsImportProviderImpl, kPDFExtraPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kPDFPresetScriptUtilsImpl, kPDFExtraPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kPDFOutputEventWatcherImpl, kPDFExtraPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPDFValidateSettingNameImpl, kPDFExtraPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPDFPresetNameUtilsImpl, kPDFExtraPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPDFPromptForPasswordsCmdImpl, kPDFExtraPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPDFLibraryUtilsImpl, kPDFExtraPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kPDFReviewImporterImpl, kPDFExtraPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPDFReviewImportMenuActionImpl, kPDFExtraPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kPDFReviewDialogObserverImpl, kPDFExtraPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kPDFReviewDialogControllerImpl, kPDFExtraPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kPDFLibraryUtilsPublicImpl, kPDFExtraPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPDFExportSetupServiceImpl, kPDFExtraPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kPDFFormXObjectDataImpl, kPDFExtraPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kPDFFormXObjectFormDataImpl, kPDFExtraPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kPDFFormXObjectGatherProviderImpl, kPDFExtraPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kPDFFormXObjectSetupServiceImpl, kPDFExtraPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportProviderImpl, kPDFExtraPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportCmdImpl, kPDFExtraPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportPrefsImpl, kPDFExtraPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSetInteractivePDFExportPrefsCmdImpl, kPDFExtraPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportPageRangeImpl, kPDFExtraPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportPrefScriptProviderImpl, kPDFExtraPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportFacadeImpl, kPDFExtraPrefix + 56)

DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportDlgControllerImpl, kPDFExtraPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportDlgObserverImpl, kPDFExtraPrefix + 58)
//gap
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFSecurityDlgControllerImpl, kPDFExtraPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFSecurityDlgObserverImpl, kPDFExtraPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kPDFFormXPDataImpl, kPDFExtraPrefix + 62)
//gap
DECLARE_PMID(kImplementationIDSpace, kPDFRepositionBBoxDataImpl, kPDFExtraPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kPDFLinkResponderImpl, kPDFExtraPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kPDFDPartHierarchyImpl, kPDFExtraPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kPDFDPartMetadataUtilsImpl, kPDFExtraPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kPDFVTPortImpl, kPDFExtraPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kPDFStructureOrderPrefImpl, kPDFExtraPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kPDFStructureOrderPrefFacadeImpl, kPDFExtraPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kSetPDFStructureOrderPrefCmdImpl, kPDFExtraPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTaggedPDFPrefsScriptProviderImpl, kPDFExtraPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kPDFNewDocResponderImpl, kPDFExtraPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kPDFPresetUtilsImpl, kPDFExtraPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kDocTitleStatusTipImpl, kPDFExtraPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportPrefs_2Impl, kPDFExtraPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kLanguageListHandlerImpl, kPDFExtraPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kAccessibilityPanelHoverInfoImpl, kPDFExtraPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportDialogCreatorImpl, kPDFPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFSecurityPanelCreatorImpl, kPDFPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFGeneralPanelCreatorImpl, kPDFPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFDialogObserverImpl, kPDFPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFTreeViewDlgSwitcherImpl, kPDFPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFTreeViewWidgetMgrImpl, kPDFPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFTreeViewAdapterImpl, kPDFPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFTreeNodeControlViewImpl, kPDFPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFAdvancedPanelCreatorImpl, kPDFPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFAdvancedDlgControllerImpl, kPDFPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFAdvancedDlgObserverImpl, kPDFPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportDialogControllerImpl, kPDFPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFCompressionPanelCreatorImpl, kPDFPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFCompressionDlgObserverImpl, kPDFPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFCompressionDlgControllerImpl, kPDFPrefix + 129)


DECLARE_PMID(kImplementationIDSpace, kSinglePagePDFSuffixActionComponentImpl, kPDFExtraPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kInteractivePDFExportPrefs_3Impl, kPDFExtraPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kPDFExportFileNameImpl, kPDFExtraPrefix + 132)

// Some work related to the PDF export retain file name
DECLARE_PMID(kImplementationIDSpace, kSetPDFExportRetainFileNamePrefCmdImpl, kPDFExtraPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kPDFExportRetainFileNameBoolDataImpl, kPDFExtraPrefix + 134)

DECLARE_PMID(kImplementationIDSpace, kPDFCommentsImportServiceImpl, kPDFExtraPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kPDFCommentsImportProviderImpl, kPDFExtraPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kImportPDFUtilsImpl, kPDFExtraPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kImportPDFAnnotationImpl, kPDFExtraPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kIconAnnotationDataImpl, kPDFExtraPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kRangeAnnotationDataImpl, kPDFExtraPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kPathAnnotationDataImpl, kPDFExtraPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageDestinationImpl, kPDFExtraPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageDestDataImpl, kPDFExtraPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageItemDestinationImpl, kPDFExtraPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageItemDestDataImpl, kPDFExtraPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestinationImpl, kPDFExtraPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestDataImpl, kPDFExtraPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kAnnotationDestTextRangeItemImpl, kPDFExtraPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestinationMementoImpl, kPDFExtraPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kPDFCommentAdornmentShapeImpl, kPDFExtraPrefix + 150)

DECLARE_PMID(kImplementationIDSpace, kAnnotationImportPointMapperServiceImpl, kPDFExtraPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kAnnotationImportPointMapperImpl, kPDFExtraPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPointMapperDataImpl, kPDFExtraPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kSavePointAnnotationDataToModelImpl, kPDFExtraPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kAnnotationImportRectMapperServiceImpl, kPDFExtraPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kAnnotationImportRectMapperImpl, kPDFExtraPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kAnnotationRectMapperDataImpl, kPDFExtraPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kSaveRectAnnotationDataToModelImpl, kPDFExtraPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kAnnotationImportRangeMapperServiceImpl, kPDFExtraPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kAnnotationImportRangeMapperImpl, kPDFExtraPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kAnnotationRangeMapperDataImpl, kPDFExtraPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kSaveRangeAnnotationDataToModelImpl, kPDFExtraPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kAnnotationMapperUtilsImpl, kPDFExtraPrefix + 163)

DECLARE_PMID(kImplementationIDSpace, kAnnotationOrchestratorImpl, kPDFExtraPrefix + 164)

DECLARE_PMID(kImplementationIDSpace, kAnnotationPageDestScrapImpl, kPDFExtraPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageItemDestScrapImpl, kPDFExtraPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestScrapImpl, kPDFExtraPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kNewAnnotationPageDestCmdImpl, kPDFExtraPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kDeleteAnnotationPageDestCmdImpl, kPDFExtraPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kNewAnnotationPageItemDestCmdImpl, kPDFExtraPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kDeleteAnnotationPageItemDestCmdImpl, kPDFExtraPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kNewAnnotationTextDestCmdImpl, kPDFExtraPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kDeleteAnnotationTextDestCmdImpl, kPDFExtraPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kChangeAnnotationTextDestCmdImpl, kPDFExtraPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kDeleteAnnotationDestCmdImpl, kPDFExtraPrefix + 175)

DECLARE_PMID(kImplementationIDSpace, kReplyImpl, kPDFExtraPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kReplyListImpl, kPDFExtraPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestinationCmdDataImpl, kPDFExtraPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageDestinationCmdDataImpl, kPDFExtraPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageItemDestinationCmdDataImpl, kPDFExtraPrefix + 180)

DECLARE_PMID(kImplementationIDSpace, kCommentTableImpl, kPDFExtraPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kPrivateAnnotationUtilsImpl, kPDFExtraPrefix + 182)
//DECLARE_PMID(kImplementationIDSpace, kAnnotationObserverImpl, kPDFExtraPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kAnnotationFacadeImpl, kPDFExtraPrefix + 184)

DECLARE_PMID(kImplementationIDSpace, kNewAnnotationCmdImpl, kPDFExtraPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kAnnotationCmdDataImpl, kPDFExtraPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kDeleteAnnotationCmdImpl, kPDFExtraPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kChangeAnnotationCmdImpl, kPDFExtraPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kNewReplyCmdImpl, kPDFExtraPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kReplyCmdDataImpl, kPDFExtraPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kDeleteReplyCmdImpl, kPDFExtraPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kAnnotationImportRangeStringMapperImpl, kPDFExtraPrefix + 192)

DECLARE_PMID(kImplementationIDSpace, kAnnotationUtilsImpl, kPDFExtraPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kAnnotationSuiteASBImpl, kPDFExtraPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kAnnotationSuiteTextCSBImpl, kPDFExtraPrefix + 195)

DECLARE_PMID(kImplementationIDSpace, kCommentListCacheImpl, kPDFExtraPrefix + 196)

DECLARE_PMID(kImplementationIDSpace, kAnnotationScriptProviderImpl, kPDFExtraPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kAnnotationScriptImpl, kPDFExtraPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kReplyScriptProviderImpl, kPDFExtraPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kReplyScriptImpl, kPDFExtraPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageDestinationScriptProviderImpl, kPDFExtraPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageDestinationScriptImpl, kPDFExtraPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageItemDestinationScriptProviderImpl, kPDFExtraPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kAnnotationPageItemDestinationScriptImpl, kPDFExtraPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestinationScriptProviderImpl, kPDFExtraPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kAnnotationTextDestinationScriptImpl, kPDFExtraPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kPDFCommentsDocScriptProviderImpl, kPDFExtraPrefix + 207)

DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentsOptionsDlgControllerImpl, kPDFExtraPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentsOptionsDlgObserverImpl, kPDFExtraPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentOptionsDialogStatusImpl, kPDFExtraPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentOptionsPrefsImpl, kPDFExtraPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentOptionsPagePreviewViewImpl, kPDFExtraPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kRCCommentTableImpl, kPDFExtraPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kNewRCAnnotationCmdImpl, kPDFExtraPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kNewRCAnnotationPageDestCmdImpl, kPDFExtraPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kDeleteRCAnnotationCmdImpl, kPDFExtraPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kDeleteRCAnnotationDestCmdImpl, kPDFExtraPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kRCAnnotationImpl, kPDFExtraPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kAnnotationBaseImpl, kPDFExtraPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kRCAnnotationCmdDataImpl, kPDFExtraPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kNewRCAnnotationPageItemDestCmdImpl, kPDFExtraPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kAnnotationUIUtilsImpl, kPDFExtraPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kNewRCAnnotationTextDestCmdImpl, kPDFExtraPrefix + 223)

//----------------------------------------------------------------------------------------
//
// Widget ids
//
DECLARE_PMID(kWidgetIDSpace, kPDFExportMainDlgWidgetID, kPDFPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_StartPageWidgetId, kPDFPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_EndPageWidgetId, kPDFPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_PageMinusWidgetId, kPDFPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_PagePlusWidgetId, kPDFPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_PreviewWidgetId, kPDFPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_PreserveScreensWidgetId, kPDFPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_CropToWidgetId, kPDFPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_PageNumberWidgetId, kPDFPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_OptionsGroupWidgetId, kPDFPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_PageReferenceWidgetId, kPDFPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_TransparentBackgroundWidgetId, kPDFPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kPDFColorImagesAboveTextWidgetId, kPDFPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_ParentWidgetId, kPDFPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPDFPlace_GroupPanelWidgetId, kPDFPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPDFPageReflowProblemWidgetID, kPDFPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kPDFColorImagesAboveEditWidgetId, kPDFPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPDFGrayImagesAboveTextWidgetId, kPDFPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptPanelWidgetId, kPDFPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptEmbedAllFontsWidgetId, kPDFPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptAcroCompatWidgetId, kPDFPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptSubsetBelowPctWidgetId, kPDFPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptImageResWidgetId, kPDFPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kPDFGrayImagesAboveEditWidgetId, kPDFPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptColorSpaceWidgetId, kPDFPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptGenThumbnailsWidgetId, kPDFPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptOptimizePDFWidgetId, kPDFPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptViewAfterExportWidgetId, kPDFPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptGroupWidgetId, kPDFPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptIncludeICCWidgetId, kPDFPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptCroppedImageWidgetId, kPDFPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kPDFSelectDialogPopupGroupWidgetID, kPDFPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptImportedGroupWidgetId, kPDFPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptOmitGroupWidgetId, kPDFPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptOmitEPSWidgetId, kPDFPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptOmitPDFWidgetId, kPDFPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptOmitBitmapWidgetId, kPDFPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kSubsetFontsBelowTextWidgetId, kPDFPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesPanelWidgetId, kPDFPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesAllBtnWidgetId, kPDFPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesRangeBtnWidgetId, kPDFPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesRangeEditWidgetId, kPDFPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kPDFColorDPITextWidgetId, kPDFPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesRadioButtonWidgetId, kPDFPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SpreadsRadioButtonWidgetId, kPDFPrefix + 46)
//DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesReaderSpreadWidgetId, kPDFPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kPDFGrayDPITextWidgetId, kPDFPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kPDFTypeLabelWidgetID, kPDFPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kPDFTypePopupWidgetID, kPDFPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesAllPageMarksWidgetId, kPDFPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesCropMarksWidgetId, kPDFPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kCornerMarksLabelWidgetId, kPDFPrefix + 52)
//gap
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesIncludeBleedMarksWidgetId, kPDFPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesPageInformationWidgetId, kPDFPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesRegistrationMarksWidgetId, kPDFPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesColorBarsWidgetId, kPDFPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesPageMarkGroupWidgetId, kPDFPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesOutsetAmtWidgetId, kPDFPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompPanelWidgetId, kPDFPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorWidgetId, kPDFPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorSampleWidgetId, kPDFPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorSampleEditWidgetId, kPDFPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorCompressionWidgetId, kPDFPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorQualityWidgetId, kPDFPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorZipQualityWidgetId, kPDFPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompColorNonQualityWidgetId, kPDFPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGrayWidgetId, kPDFPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGraySampleWidgetId, kPDFPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGraySampleEditWidgetId, kPDFPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGrayCompressionWidgetId, kPDFPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGrayQualityWidgetId, kPDFPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGrayZipQualityWidgetId, kPDFPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompGrayNonQualityWidgetId, kPDFPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompMonoWidgetId, kPDFPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompMonoSampleWidgetId, kPDFPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompMonoSampleEditWidgetId, kPDFPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompMonoCompressionWidgetId, kPDFPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CompTextLineArtWidgetId, kPDFPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityPanelWidgetId, kPDFPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kOldUI_SecurityPasswordGroupWidgetId, kPDFPrefix + 81) // InCopy only
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityOpenPasswordWidgetId, kPDFPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityChangePasswordWidgetId, kPDFPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityDisallowGroupWidgetId, kPDFPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kOldUI_SecurityNoPrintingWidgetId, kPDFPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kOldUI_SecurityNoChangingDocumentWidgetId, kPDFPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kOldUI_SecurityNoCopyingWidgetId, kPDFPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kOldUI_SecurityNoChangingNotesWidgetId, kPDFPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityUseUserPasswordWidgetId, kPDFPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kOldUI_SecurityPasswordFrameWidgetId, kPDFPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityDisallowFrameWidgetId, kPDFPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SecurityUseMasterPasswordWidgetId, kPDFPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ViewLabelWidgetId,	kPDFPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kPDFExptGalleyPanelWidgetId, kPDFPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_AnnotationNotesWidgetId, kPDFPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_FontStyleDropDownWidgetId,	kPDFPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_FontLeadingDropDownWidgetId,	kPDFPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kInCopyExptSecurityButtonWidgetId,	kPDFPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kPDFOpenInFullscreenCheckboxWidgetId, kPDFPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kPDFMagnificationDropDownWidgetId,	kPDFPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kPDFLayoutDropDownWidgetId,	kPDFPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kPDFViewingGroupWidgetID,	kPDFPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kPDFColorTileSizeTextWidgetId, kPDFPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kPDFDisplayTitleDropDownWidgetId, kPDFPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kPDFDisplayTitleInfoWidgetId, kPDFPrefix + 105)
//gap
DECLARE_PMID(kWidgetIDSpace, kPDFColorTextWidgetId, kPDFPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kGroup1WidgetId, kPDFPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kImagesTextWidgetId, kPDFPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kGroup2WidgetId, kPDFPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kGroup3WidgetId, kPDFPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kGroup4WidgetId, kPDFPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kNoteTextWidgetId, kPDFPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kNotePart2TextWidgetId, kPDFPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kPDF_DPITextWidgetId, kPDFPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kCompressionTextWidgetId, kPDFPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kQualityTextWidgetId, kPDFPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kDPI2TextWidgetId, kPDFPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kCompression2TextWidgetId, kPDFPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kQuality2TextWidgetId, kPDFPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kDPI3TextWidgetId, kPDFPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kCompression3TextWidgetId, kPDFPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kPageRangeClusterWidgetId, kPDFPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kOffsetTextWidgetId, kPDFPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kPDFColorTileSizeEditWidgetId, kPDFPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kOpenDocTextWidgetId, kPDFPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kChangeSecurityTextWidgetId, kPDFPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kCropToTextWidgetId, kPDFPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kImportDialogWidgetId, kPDFPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kPDFImportErrorDialogWidgetId, kPDFPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kPasswordText1WidgetId, kPDFPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kPasswordText2WidgetId, kPDFPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kPDFErrorsDialogWidgetId, kPDFPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleDropdownWidgetId, kPDFPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleLabelWidgetId, kPDFPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleNameEditWidgetId, kPDFPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleSaveButtonWidgetId, kPDFPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kChangeSecurityPasswordTextWidgetId, kPDFPrefix + 144)
//gap
DECLARE_PMID(kWidgetIDSpace, kPDFGrayTileSizeTextWidgetId, kPDFPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kPDFGrayTileSizeEditWidgetId, kPDFPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kPDFMonochromeImagesAboveTextWidgetId, kPDFPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kPDFMonochromeImagesAboveEditWidgetId, kPDFPrefix + 149)
//gap
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ColumnsLabelWidgetId, kPDFPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ColumnsEditWidgetId, kPDFPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_LineRangeLabelWidgetId, kPDFPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kInCopyPDFExptDialogWidgetId, kPDFPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kInCopyPDFExptPanelPickerPopupWidgetId, kPDFPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_FontSizeDropDownWidgetId, kPDFPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_NotesBackgroundCheckBoxWidgetId, kPDFPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_TrackChangesBackgroundCheckBoxWidgetId, kPDFPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kPDFPassword_PasswordWidgetId, kPDFPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kPDFPassword_ParentWidgetId, kPDFPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_AllStoriesRadioButtonWidgetId, kPDFPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CurrentStoryRadioButtonWidgetId, kPDFPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_NotesTypePopupWidgetId,	kPDFPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_TrackChangesTypePopupWidgetId,	kPDFPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_StoryInfoWidgetId,	kPDFPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ScopeClusterWidgetId,	kPDFPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ColumnWidthTypePopupWidgetId,	kPDFPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ExpandedStoryRadioButtonWidgetId, kPDFPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kPDFUIErrorsDlgListBoxWidget, kPDFPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kPDFExpCJKGridGroup1WidgetId, kPDFPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CJKGridPanelWidgetId, kPDFPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_WithCJKGridWidgetId, kPDFPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kPDFMonochromeDPITextWidgetId, kPDFPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kPDFEmbedTextWidgetId, kPDFPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CJKGridBorderWidgetId, kPDFPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_WithLayoutCJKGridChkBxWidgetId, kPDFPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_WithFrameCJKGridChkBxWidgetId, kPDFPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_WithTextCJKGridChkBxWidgetId, kPDFPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_WithPageItemsCJKGridChkBxWidgetId, kPDFPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_FrameViewCJKGridWidgetId, kPDFPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_WhenFrameCJKGridWidgetId, kPDFPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kPDFExpCJKGridGroup2WidgetId, kPDFPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CJKGridViewTextWidgetId, kPDFPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kPDFAcroCompatTextWidgetId, kPDFPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CustomUnitEditWidgetId, kPDFPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_CustomUnitLabelWidgetId, kPDFPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kPDFExptLayoutPanelWidgetId, kPDFPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptFontsGroupWidgetId, kPDFPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptIncludeStructureWidgetId, kPDFPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptColorGroupWidgetId, kPDFPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptDestProfileTextWidgetId, kPDFPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptDestProfileWidgetId, kPDFPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedTopTextWidgetId, kPDFPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedTopWidgetId, kPDFPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedInsideTextWidgetId, kPDFPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedInsideWidgetId, kPDFPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedBottomTextWidgetId, kPDFPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedBottomWidgetId, kPDFPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedOutsideTextWidgetId, kPDFPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedOutsideWidgetId, kPDFPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesWeightTextWidgetId, kPDFPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesWeightWidgetId, kPDFPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesPagesTextWidgetId, kPDFPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptSpotOverPrintTextWidgetId, kPDFPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptSpotOverPrintWidgetId, kPDFPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kPDFEmbedDropDownWidgetId, kPDFPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kPDFExcessFlattenerResolutionWarning, kPDFPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptIncludeHyperlinksWidgetId, kPDFPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kPDFIncludeLayersWidgetId, kPDFPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptFlatSetGroupWID, kPDFPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptFlatSetGroupTitleWID, kPDFPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptFlatSetStyleLabelWID, kPDFPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptFlatSetStylePopupWID, kPDFPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptFlatSetIgnoreSprOversWID, kPDFPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kPDFMarksLabelWidgetID, kPDFPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kPDFMarkWeightPopupWidgetID, kPDFPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kPDFMarkOffsetEditWidgetID, kPDFPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kPDFMarkOffsetNudgeWidgetID, kPDFPrefix + 219)
DECLARE_PMID(kWidgetIDSpace, kPDFTopNudgeWidgetID, kPDFPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kPDFBottomNudgeWidgetID, kPDFPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kPDFInsideNudgeWidgetID, kPDFPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kPDFOutsideNudgeWidgetID, kPDFPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kPDFAdvancedPanelWidgetId, kPDFPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kPDFVisibleGridsGuidesWidgetId, kPDFPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kPDFInkManagerButtonWidgetId, kPDFPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptIncludeBookmarksWidgetId, kPDFPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kPDFNonprintingObjectsWidgetId, kPDFPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryPanelWidgetID, kPDFPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryGroupPanelWidgetID, kPDFPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryScrollBarWidgetID, kPDFPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kPDFStandardsTextWidgetId, kPDFPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kPDFStandardsDropDownWidgetId, kPDFPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryTextWidgetID, kPDFPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kPDFExportSummaryButtonWidgetID, kPDFPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kPDFPlaceNoTransparencySupportWarningWidgetID, kPDFPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kV2ToV4DowngradeWarning, kPDFPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kFlattenerReflowWarning, kPDFPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kPDFExportBlendSpaceConflictWarning, kPDFPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kPlaceExceedsMaxVersionWarning, kPDFPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ScopeLabelWidgetId, kPDFPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kLineRangeClusterWidgetId, kPDFPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_LineAllBtnWidgetId, kPDFPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_LineRangeBtnWidgetId, kPDFPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_LineRangeEditWidgetId, kPDFPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_ALEWidgetId, kPDFPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_StyleWidgetId, kPDFPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_LineNumberWidgetId, kPDFPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_InlineNotesWidgetId, kPDFPrefix + 249)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_TrackChangesWidgetId, kPDFPrefix + 250)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_FillWidgetId, kPDFPrefix + 251)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_FontNameDropDownWidgetId, kPDFPrefix + 252)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PageInfoWidgetId, kPDFPrefix + 253)
DECLARE_PMID(kWidgetIDSpace, kPDFPreviewButtonWidgetId, kPDFPrefix + 254)
DECLARE_PMID(kWidgetIDSpace, kPDFCompatibilityTextWidgetId, kPDFPrefix + 255)
// We have room for 255 more widgets!
DECLARE_PMID(kWidgetIDSpace, kPDFXGroupWidgetId, kPDFExtraPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPDFRegistryComboWidgetID, kPDFExtraPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPDFPrintingTextWidgetId, kPDFExtraPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPDFPrintingWidgetId, kPDFExtraPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPDFAccessToScreenReaderWidgetId, kPDFExtraPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPDFEnableCopyingWidgetId, kPDFExtraPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPDFEncryptionLevelWidgetId, kPDFExtraPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPDFRequirePasswordWidgetId, kPDFExtraPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPDFDocumentOpenPasswordTextWidgetId, kPDFExtraPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kPDFDocumentOpenPasswordWidgetId, kPDFExtraPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kPDFPasswordNoteTextWidgetId, kPDFExtraPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kPDFChangesAllowedTextWidgetId, kPDFExtraPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kPDFChangesAllowedWidgetId, kPDFExtraPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kPDFEncryptionLevelTextWidgetId, kPDFExtraPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kPDFColorQualityJPEG2000WidgetId, kPDFExtraPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPDFGrayQualityJPEG2000WidgetId, kPDFExtraPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPDFOutputConditionComboWidgetID, kPDFExtraPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kPDFOutputCondidionTextWidgetId, kPDFExtraPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPDFInteractiveElementsWidgetId, kPDFExtraPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPDFUseDocumentBleedWidgetId, kPDFExtraPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPDFIncludeSlugWidgetId, kPDFExtraPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kEncryptionLevelWidgetId, kPDFExtraPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPasswordReguiredWidgetId, kPDFExtraPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPasswordRequiredToEditWidgetId, kPDFExtraPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kChangesAllowedWidgetId, kPDFExtraPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kPDFChangesAllowedPopupWidgetId, kPDFExtraPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPDFPrintingAllowedPopupWidgetId, kPDFExtraPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kPDFEnableCopyingTextWidgetId, kPDFExtraPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kPDFEnableTextAccessWidgetId, kPDFExtraPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPDFEnablePlaintextMetadataWidgetId, kPDFExtraPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPrintingAllowedTextWidgetId, kPDFExtraPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPDFPreviewEnableDisableWidgetId, kPDFExtraPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kPDFBleedTextWidgetId, kPDFExtraPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kPDFBleedChainWidgetId, kPDFExtraPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kPDFExportHiddenLayerWarning, kPDFExtraPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kPDFOpenGroupWidgetID, kPDFExtraPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kPDFPermissionsGroupWidgetID, kPDFExtraPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kPDFPlaceAllPagesWidgetID, kPDFExtraPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kPDFPlaceRangeWidgetID, kPDFExtraPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kPDFPlaceRangeEditboxWidgetID, kPDFExtraPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kPDFPlaceOnePageWidgetID, kPDFExtraPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kPDFPlacePagesGroupWidgetId, kPDFExtraPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kPDFPlacePagesGroupTextWidgetId, kPDFExtraPrefix + 43)

DECLARE_PMID(kWidgetIDSpace, kPDFPlaceTabbedDialogWidgetID, kPDFExtraPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kPDFChangeLayerDialogParentWidgetID, kPDFExtraPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryTreeNodeWidgetId, kPDFExtraPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryListElementWidgetId, kPDFExtraPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryTreeWidgetID, kPDFExtraPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionWidgetId, kPDFExtraPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kPDFDescritionTextWidgetID, kPDFExtraPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionScrollBarWidgetID, kPDFExtraPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kPDFOutputPanelWidgetId, kPDFExtraPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kOutputConditionTextWidgetId, kPDFExtraPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kPDFOutputConditionWidgetId, kPDFExtraPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kOutputIdentifierTextWidgetId, kPDFExtraPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kPDFOutputIdentifierWidgetId, kPDFExtraPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kRegistryNameTextWidgetId, kPDFExtraPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kPDFRegistryNameWidgetId, kPDFExtraPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kPDFInclusionTextWidgetId, kPDFExtraPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kPDFInclusionWidgetId, kPDFExtraPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kIconRepurposeWidgetId, kPDFExtraPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kRepurposeTextWidgetId, kPDFExtraPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kPDFSelDialogTreeViewWidgetID, kPDFExtraPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kPDFSelDialogTreeNodeWidgetID, kPDFExtraPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kPDFSelDialogTreeNodeCheckBoxWidgetID, kPDFExtraPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kPDFSelDialogTreeNodeStaticTextWidgetID, kPDFExtraPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kSummaryTreeTextWidgetId, kPDFExtraPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kWarningTreeTextWidgetId, kPDFExtraPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kPDFWarningTreeWidgetID, kPDFExtraPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kPDFWarningGroupPanelWidgetID, kPDFExtraPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionGroupPanelWidgetID, kPDFExtraPrefix + 71)

DECLARE_PMID(kWidgetIDSpace, kPDFSummaryDescriptionWidgetId, kPDFExtraPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryDescritionTextWidgetID, kPDFExtraPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryDescriptionScrollBarWidgetID, kPDFExtraPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kPDFSummaryDescriptionGroupPanelWidgetID, kPDFExtraPrefix + 75)

DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleDialogWID, kPDFExtraPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleListTitleWID, kPDFExtraPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleListWID, kPDFExtraPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleNewButtonWID, kPDFExtraPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleEditButtonWID, kPDFExtraPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleDeleteButtonWID, kPDFExtraPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleImportButtonWID, kPDFExtraPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStyleExportButtonWID, kPDFExtraPrefix + 83)

DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetDescTitleWID, kPDFExtraPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetDescWID, kPDFExtraPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetDescScrollWID, kPDFExtraPrefix + 86)

DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetSummaryTitleWID, kPDFExtraPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetSummaryWID, kPDFExtraPrefix + 88)

DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetWarningsTitleWID, kPDFExtraPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetWarningsWID, kPDFExtraPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStylePresetWarningsScrollWID, kPDFExtraPrefix + 91)
//gap
//gap

DECLARE_PMID(kWidgetIDSpace, kPDFDescGroupPanelWidgetID, kPDFExtraPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionLabelWidgetID, kPDFExtraPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionIconWidgetID, kPDFExtraPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionSmallWidgetID, kPDFExtraPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kPDFDescriptionLargeWidgetID, kPDFExtraPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kPDFWarningLabelWidgetID, kPDFExtraPrefix + 99)

DECLARE_PMID(kWidgetIDSpace, kPDFLayersLabelWidgetID, kPDFExtraPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kPDFLayersPopupWidgetID, kPDFExtraPrefix + 101)

DECLARE_PMID(kWidgetIDSpace, kPDFReviewImportDialogWidgetID, kPDFExtraPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kChooseFilesGroupWidgetID, kPDFExtraPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kChooseFilesGroupTextWidgetID, kPDFExtraPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kPDFFileEditBoxWidgetID, kPDFExtraPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kPDFFileBrowseButtonWidgetID, kPDFExtraPrefix + 106)

DECLARE_PMID(kWidgetIDSpace, kIPDFExportDialogWidgetID, kPDFExtraPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kIPDF_MainColumnWidgetID, kPDFExtraPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kIPDF_FieldNamesWidgetID, kPDFExtraPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PagesStrWidgetID, kPDFExtraPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kIPDF_FieldsWidgetID, kPDFExtraPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kIPDF_Pages_GroupWidgetID, kPDFExtraPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kIPDF_All_RadioButtonWidgetID, kPDFExtraPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kIPDF_Range_RadioButtonWidgetID, kPDFExtraPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kIPDF_OKCancelWID, kPDFExtraPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PagesPageRangeEditWID, kPDFExtraPrefix + 116)
//DECLARE_PMID(kWidgetIDSpace, kIPDF_SpreadsCheckboxWID, kPDFExtraPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ViewAfterExportingCheckboxWID, kPDFExtraPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kIPDF_EmbedThumbnailsCheckboxWID, kPDFExtraPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kIPDF_TaggedPDFCheckboxWID, kPDFExtraPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kIPDF_MagnificationStrWidgetID, kPDFExtraPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kIPDF_MagnificationPopupWID, kPDFExtraPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kIPDF_SpaceWidgetID, kPDFExtraPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PageLayoutStrWidgetID, kPDFExtraPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PageLayoutPopupWID, kPDFExtraPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kIPDF_FullScreenCheckboxWID, kPDFExtraPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PresentationStrWidgetID, kPDFExtraPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kIPDF_FlipGroupWidgetID, kPDFExtraPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kIPDF_FlipPagesCheckboxWID, kPDFExtraPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kIPDF_FlipPagesSpeedWID, kPDFExtraPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kIPDF_SecStrWidgetID, kPDFExtraPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kIPDF_CompressionPopupWID, kPDFExtraPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kIPDF_CompressionStrWidgetID, kPDFExtraPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kIPDF_JPEGQualityPopupWID, kPDFExtraPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kIPDF_JPEGQualityStrWidgetID, kPDFExtraPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ResolutionComboWID, kPDFExtraPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ResolutionStrWidgetID, kPDFExtraPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kIPDF_Pages_ClusterWidgetID, kPDFExtraPrefix + 138)

DECLARE_PMID(kWidgetIDSpace, kPDFInteractiveWidgetId, kPDFExtraPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kPDFInteractiveDropDownWidgetId, kPDFExtraPrefix + 140)

DECLARE_PMID(kWidgetIDSpace, kIPDF_ImageCompressGroupWidgetId, kPDFExtraPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ImageCompressBorderWidgetID, kPDFExtraPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ImageCompressColWidgetID, kPDFExtraPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ICFieldNamesWidgetID, kPDFExtraPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ICFieldsWidgetID, kPDFExtraPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PageTransStrWidgetID, kPDFExtraPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PageTransPopupWID, kPDFExtraPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ButtonMediaStrWidgetID, kPDFExtraPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ButtonMediaClusterWidgetID, kPDFExtraPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kIPDF_CreateLayersCheckboxWID, kPDFExtraPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kIPDF_IncludeAll_RadioButtonWidgetID, kPDFExtraPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kIPDF_AppearanceOnly_RadioButtonWidgetID, kPDFExtraPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kIPDF_SecurityButtonWidgetID, kPDFExtraPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kIPDF_SecurityContainerPanelWID, kPDFExtraPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kInteractivePDFExportBlendSpaceConflictWarning, kPDFExtraPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kIPDF_TaggedPDFStrWidgetID, kPDFExtraPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kIPDF_TabOrderCheckboxWID, kPDFExtraPrefix + 157)

DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesOrSpreadsClusterWidgetId, kPDFExtraPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SpreadBleedWidgetID, kPDFExtraPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedWidgetID, kPDFExtraPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedRightTextWidgetId, kPDFExtraPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PagesBleedLeftTextWidgetId, kPDFExtraPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kIPDF_DisplayTitlePopupWID, kPDFExtraPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kIPDF_DisplayTitleStrWidgetID, kPDFExtraPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kIPDF_DisplayTitleInfoWidgetId, kPDFExtraPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kIPDF_LanguagePreferencePopupWID, kPDFExtraPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kIPDF_LanguagePreferenceStrWidgetID, kPDFExtraPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptAccessibilityGroupWID, kPDFExtraPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptAccessibilityTitleWID, kPDFExtraPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptLanguagePreferenceLabelWID, kPDFExtraPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptLanguagePreferencePopupWID, kPDFExtraPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_OptAccessibilityDescriptionGroupWID, kPDFExtraPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kAccessibilityDescriptionLabelWidgetID, kPDFExtraPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kAccessibilityDescriptionWidgetId, kPDFExtraPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kInteractivePDFExportMainDlgWidgetID, kPDFExtraPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kInteractivePDFSelDialogTreeViewWidgetID, kPDFExtraPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kInteractivePDFTreeNodeNameWidgetID, kPDFExtraPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kInteractivePDFTreeNodeWidgetID, kPDFExtraPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kIPDFExportSecurityDialogWidgetID, kPDFExtraPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kIPDFExportAdvancedDialogWidgetID, kPDFExtraPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PagesGroupWidgetId, kPDFExtraPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kIPDF_PagesBorderWidgetID, kPDFExtraPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ViewingGroupWidgetId, kPDFExtraPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kIPDF_ViewingBorderWidgetID, kPDFExtraPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kIPDF_OptionsGroupWidgetId, kPDFExtraPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kIPDF_OptionsBorderWidgetID, kPDFExtraPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kIPDFExportCompressionDialogWidgetID, kPDFExtraPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SinglePagesPDFCheckboxWidgetId, kPDFExtraPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_TextAfterEditBoxWidgetId, kPDFExtraPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_PreviewTextBoxWidgetId, kPDFExtraPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SinglePagePDFSuffixButtonWidgetId, kPDFExtraPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kIPDF_SinglePagesPDFCheckboxWidgetID, kPDFExtraPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kPDFExp_SuffixStaticTextWidgetId, kPDFExtraPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentsOptionsDialogWidgetID, kPDFExtraPrefix + 194)

DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_StartPageWidgetId, kPDFExtraPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_EndPageWidgetId, kPDFExtraPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_PageMinusWidgetId, kPDFExtraPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_PagePlusWidgetId, kPDFExtraPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_PreviewWidgetId, kPDFExtraPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_PageNumberWidgetId, kPDFExtraPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptionsGroupTextWidgetId, kPDFExtraPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptionsGroupWidgetId, kPDFExtraPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kImportCommentPDFPagesGroupWidgetId, kPDFExtraPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kImportCommentPDFPagesGroupTextWidgetId, kPDFExtraPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptionsAllPagesWidgetID, kPDFExtraPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptionsRangeWidgetID, kPDFExtraPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptionsRangeEditboxWidgetID, kPDFExtraPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptionsPreviewPageBarGroupWidgetId, kPDFExtraPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kImportPDFCommentOptions_PageReferenceWidgetId, kPDFExtraPrefix + 209)




//----------------------------------------------------------------------------------------
//
// Service IDs
DECLARE_PMID(kServiceIDSpace, kPDFExportDialogService, kPDFPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kPDFExportEditStyleDlgService, kPDFPrefix + 2)

DECLARE_PMID(kServiceIDSpace, kStartPDFDocumentSignalResponderService, kPDFPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kEndPDFDocumentSignalResponderService, kPDFPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kStartPDFPageSignalResponderService, kPDFPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kEndPDFPageSignalResponderService, kPDFPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kExportPDFDirectService, kPDFPrefix + 7)

//InCopy
DECLARE_PMID(kServiceIDSpace, kInCopyPDFExportDialogService, kPDFPrefix + 8)

DECLARE_PMID(kServiceIDSpace, kPDFPlaceDialogService, kPDFPrefix + 9)
DECLARE_PMID(kServiceIDSpace, kPDFExportSetupService, kPDFPrefix + 10)
DECLARE_PMID(kServiceIDSpace, kPDFFormXObjectSetupService, kPDFPrefix + 11)

DECLARE_PMID(kServiceIDSpace, kInteractivePDFExportDialogService, kPDFPrefix + 12)
DECLARE_PMID(kServiceIDSpace, kCommentsImportProviderService, kPDFPrefix + 13)
DECLARE_PMID(kServiceIDSpace, kAnnotationMapperService, kPDFPrefix + 14)


DECLARE_PMID(kServiceIDSpace, kAfterPDFExportSignalResponderService, kPDFPrefix + 15)

// <Error ID>
//----------------------------------------------------------------------------------------
//
// Error Codes
DECLARE_PMID(kErrorIDSpace, kPDFLibraryError, kPDFPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kPDFLibraryNotPresentError, kPDFPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kPDFPageRectTooBig, kPDFPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kPDFPageRectTooSmall, kPDFPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kPDFExptStyleErrIndexOutOfRange, kPDFPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kPDFExptStyleErrNameConflict, kPDFPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kPDFExptStyleErrNullParameter, kPDFPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kPDFExptStyleErrPersonalityMissing, kPDFPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kPDFExptStyleErrCommandCreationError, kPDFPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kPDFPageReflowDrawOrderError, kPDFPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kPDFPageReflowTextTransError, kPDFPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kPDFPageReflowFigureTransError, kPDFPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kPDFExportFailed, kPDFPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kPDFPageReflowFlattenError, kPDFPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kPDFCreateThumbnailError, kPDFPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kPDFAttachToTreeError, kPDFPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kPDFPlayDisplayListError, kPDFPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kAcrobatNotFoundError, kPDFPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kFileAlreadyOpenError, kPDFPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kCannotAccessPasswordPropertyError, kPDFPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kPDFBookExportNoDocumentsError, kPDFPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kPDFInvalidPasswordError, kPDFPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kCannotPlacePDFError, kPDFPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kPDFExportReadOnlyJDFExistError, kPDFPrefix + 24)

//Import PDF comments specific error
DECLARE_PMID(kErrorIDSpace, kAnnotationDestinationInvalid, kPDFPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kAnnotationInvalid, kPDFPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kAnnotationWrongDocumentErr, kPDFPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kReplyInvalid, kPDFPrefix + 28)

// Action ID
DECLARE_PMID(kActionIDSpace, kPDFStyleSepActionID, kPDFPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPDFEditActionID, kPDFPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPDFStyleMenuDynamicActionID, kPDFPrefix + 3)
DECLARE_PMID(kActionIDSpace, kFirstPDFStyleActionID, (kPDFPrefix + 4))
// ids between kFirstPDFStyleActionID and kLastPDFStyleActionID are reserved
DECLARE_PMID(kActionIDSpace, kLastPDFStyleActionID, (kPDFPrefix + 220))
DECLARE_PMID(kActionIDSpace, kPDFReviewImportMenuActionID, (kPDFPrefix + 221))
DECLARE_PMID(kActionIDSpace, kSinglePagePDFSuffixPageNumActionID, kPDFPrefix + 222)
DECLARE_PMID(kActionIDSpace, kSinglePagePDFSuffixPageSizeActionID, kPDFPrefix + 226)
DECLARE_PMID(kActionIDSpace, kSinglePagesPDFSuffixIncrementalNumActionID, kPDFPrefix + 227)

// ViewPortAttr ID
DECLARE_PMID(kViewPortAttrIDSpace, kPDFExportVPAttr, kPDFPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kPDFIsFlattenerTargetVPAttr, kPDFPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kPDFPreviewVPAttr, kPDFPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kInteractivePDFExportVPAttr, kPDFPrefix + 4)
DECLARE_PMID(kViewPortAttrIDSpace, kInteractiveAppearanceOnlyVPAttr, kPDFPrefix + 5)
DECLARE_PMID(kViewPortAttrIDSpace, kDataMergePDFExportVPAttr, kPDFPrefix + 6)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportPreferenceObjectScriptElement, kPDFPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportStyleObjectScriptElement, kPDFPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kPDFPlacePreferencesObjectScriptElement, kPDFPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kPDFAttributesObjectScriptElement, kPDFPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kGalleyPDFObjectScriptElement, kPDFPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutPDFObjectScriptElement, kPDFPrefix + 10)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportPreferencePropertyScriptElement, kPDFPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowFormFillInScriptElement, kPDFPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kUseSecurityPropertyScriptElement, kPDFPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kOpenDocumentPasswordPropertyScriptElement, kPDFPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kChangeDocumentPasswordPropertyScriptElement, kPDFPrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowPrintingPropertyScriptElement, kPDFPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowChangingPropertyScriptElement, kPDFPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowCopyingPropertyScriptElement, kPDFPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowNotesPropertyScriptElement, kPDFPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kSubsetFontsBelowPropertyScriptElement, kPDFPrefix + 39)
DECLARE_PMID(kScriptInfoIDSpace, kPDFColorSpacePropertyScriptElement, kPDFPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeICCProfilesPropertyScriptElement, kPDFPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kExportStyleMethodScriptElement, kPDFPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kImportStyleMethodScriptElement, kPDFPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kPDFPlacePreferencePropertyScriptElement, kPDFPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kCropImagesToFramesPropertyScriptElement, kPDFPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kGenerateThumbnailsPropertyScriptElement, kPDFPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kOptimizePDFPropertyScriptElement, kPDFPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kViewPDFPropertyScriptElement, kPDFPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeStructurePropertyScriptElement, kPDFPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kAcrobatCompatibilityPropertyScriptElement, kPDFPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kPDFDestinationProfilePropertyScriptElement, kPDFPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeHyperLinksPropertyScriptElement, kPDFPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeBookmarksPropertyScriptElement, kPDFPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kExportNonprintingObjectsPropertyScriptElement, kPDFPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kExportGuidesAndGridsPropertyScriptElement, kPDFPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kColorBitmapSamplingPropertyScriptElement, kPDFPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kColorBitmapSamplingDPIPropertyScriptElement, kPDFPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kColorBitmapCompressionPropertyScriptElement, kPDFPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kColorBitmapQualityPropertyScriptElement, kPDFPrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kGrayscaleBitmapSamplingPropertyScriptElement, kPDFPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kGrayscaleBitmapSamplingDPIPropertyScriptElement, kPDFPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kGrayscaleBitmapCompressionPropertyScriptElement, kPDFPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kGrayscaleBitmapQualityPropertyScriptElement, kPDFPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kMonochromeBitmapSamplingPropertyScriptElement, kPDFPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kMonochromeBitmapSamplingDPIPropertyScriptElement, kPDFPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kMonochromeBitmapCompressionPropertyScriptElement, kPDFPrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kCompressTextLineArtPropertyScriptElement, kPDFPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kExportReaderSpreadsPropertyScriptElement, kPDFPrefix + 68)
DECLARE_PMID(kScriptInfoIDSpace, kPageMarksOffsetPropertyScriptElement, kPDFPrefix + 69)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberPropertyScriptElement, kPDFPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kExtractionForAccessibilityScriptElement, kPDFPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kPreserveHalftonePropertyScriptElement, kPDFPrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kTransparentBackgroundPropertyScriptElement, kPDFPrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kPDFCropPropertyScriptElement, kPDFPrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kPrinterMarkWeightPropertyScriptElement, kPDFPrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kContentToEmbedEnumScriptElement, kPDFPrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kContentToEmbedPropertyScriptElement, kPDFPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowDocumentAssemblyScriptElement, kPDFPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowPrintHiResScriptElement, kPDFPrefix + 79)
DECLARE_PMID(kScriptInfoIDSpace, kDisallowPlaintextMetadataScriptElement, kPDFPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerStylePropertyScriptElement, kPDFPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kPDFMarkTypePropertyScriptElement, kPDFPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kExportIncludeLayersPropertyScriptElement, kPDFPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kCompressColorAbovePropertyScriptElement, kPDFPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kCompressGrayAbovePropertyScriptElement, kPDFPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kCompressMonochromeAbovePropertyScriptElement, kPDFPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kPDFXProfilePropertyScriptElement, kPDFPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kColorLowestCompressionPropertyScriptElement, kPDFPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kColorTileSizePropertyScriptElement, kPDFPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kGrayLowestCompressionPropertyScriptElement, kPDFPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kGrayTileSizePropertyScriptElement, kPDFPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kPDFUseDocumentBleedScriptElement, kPDFPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeSlugPropertyScriptElement, kPDFPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kCompressionTypePropertyScriptElement, kPDFPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kStandardsCompliancePropertyScriptElement, kPDFPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kOutputConditionPropertyScriptElement, kPDFPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kOCRegistryPropertyScriptElement, kPDFPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kInteractiveElementsPropertyScriptElement, kPDFPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kPDFAttributePropertyScriptElement, kPDFPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kTextFontPropertyScriptElement, kPDFPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kGalTextFontStylePropertyScriptElement, kPDFPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kTextSizePropertyScriptElement, kPDFPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kSizeLeadingPropertyScriptElement, kPDFPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kAccurateLineEndingsPropertyScriptElement, kPDFPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kLineRangePropertyScriptElement, kPDFPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kColumnsPropertyScriptElement, kPDFPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kLineNumbersPropertyScriptElement, kPDFPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeNotesPropertyScriptElement, kPDFPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeChangesPropertyScriptElement, kPDFPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kUseParagraphStylesPropertyScriptElement, kPDFPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kPageInfoPropertyScriptElement, kPDFPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kStoryInfoPropertyScriptElement, kPDFPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kAllNotesPropertyScriptElement, kPDFPrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kAllStoriesPropertyScriptElement, kPDFPrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kAllChangesPropertyScriptElement, kPDFPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kNoteBackgroundPropertyScriptElement, kPDFPrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kChangeBackgroundPropertyScriptElement, kPDFPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kPrPageInformationMarksPropertyScriptElement, kPDFPrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kGalleyPDFPropertyScriptElement, kPDFPrefix + 119)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutPDFPropertyScriptElement, kPDFPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kExportPageRangePropertyScriptElement, kPDFPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kOutputConditionHumanPropertyScriptElement, kPDFPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kViewJDFPropertyScriptElement, kPDFPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kEffectiveDestinationProfilePropertyScriptElement, kPDFPrefix+124)
DECLARE_PMID(kScriptInfoIDSpace, kEffectiveOutputConditionPropertyScriptElement, kPDFPrefix+125)
DECLARE_PMID(kScriptInfoIDSpace, kEffectiveOCRegistryPropertyScriptElement, kPDFPrefix+126)
DECLARE_PMID(kScriptInfoIDSpace, kEffectivePDFXProfilePropertyScriptElement, kPDFPrefix+127)
DECLARE_PMID(kScriptInfoIDSpace, kExportLayersPropertyScriptElement, kPDFPrefix + 128)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kPDFColorSpaceEnumScriptElement, kPDFPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kAcrobatCompatibilityEnumScriptElement, kPDFPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kPDFICCProfilesEnumScriptElement, kPDFPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kImageCompressionEnumScriptElement, kPDFPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kCompressionQualityEnumScriptElement, kPDFPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kMonoChromeCompressionEnumScriptElement, kPDFPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kPrinterMarkWeightEnumScriptElement, kPDFPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kImageSamplingEnumScriptElement, kPDFPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kExportImportFormatEnumScriptElement, kPDFPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kCropOptionsEnumScriptElement, kPDFPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kCompressionTypeEnumScriptElement, kPDFPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kPDFProfileEnumScriptElement, kPDFPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kStandardsComplianceEnumScriptElement, kPDFPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kOutputConditionEnumScriptElement, kPDFPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kOCRegistryEnumScriptElement, kPDFPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kLineRangeEnumScriptElement, kPDFPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutLineRangeEnumScriptElement, kPDFPrefix + 217)
DECLARE_PMID(kScriptInfoIDSpace, kPDFPageRangeEnumScriptElement, kPDFPrefix + 218)
DECLARE_PMID(kScriptInfoIDSpace, kExportLayersEnumScriptElement, kPDFPrefix + 219)

DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFExportPreferenceObjectScriptElement, kPDFPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFExportPreferencePropertyScriptElement, kPDFPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportMagnificationPropertyScriptElement, kPDFPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportPageLayoutPropertyScriptElement, kPDFPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportOpenInFullScreenPropertyScriptElement, kPDFPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportFlipPagesPropertyScriptElement, kPDFPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportFlipPagesSpeedPropertyScriptElement, kPDFPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportPreserveAnimationsPropertyScriptElement, kPDFPrefix + 227)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportVideoAudioPropertyScriptElement, kPDFPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportMagnificationEnumScriptElement, kPDFPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportPageLayoutEnumScriptElement, kPDFPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportRasterResolutionEnumScriptElement, kPDFPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportResolutionPropertyScriptElement, kPDFPrefix + 232)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFRasterCompressionEnumScriptElement, kPDFPrefix + 233)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFRasterCompressionPropertyScriptElement, kPDFPrefix + 234)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFJPEGQualityEnumScriptElement, kPDFPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFJPEGQualityPropertyScriptElement, kPDFPrefix + 236)

DECLARE_PMID(kScriptInfoIDSpace, kInteractiveElementsOptionsEnumScriptElement, kPDFPrefix + 237)
DECLARE_PMID(kScriptInfoIDSpace, kInteractiveElementsOptionPropertyScriptElement, kPDFPrefix + 238)

DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFInteractiveElementsOptionsEnumScriptElement, kPDFPrefix + 239)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFInteractiveElementsOptionPropertyScriptElement, kPDFPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionOverrideEnumScriptElement, kPDFPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionOverridePropertyScriptElement, kPDFPrefix + 242)

// Tagged PDF structure order
//
DECLARE_PMID(kScriptInfoIDSpace, kTaggedPDFPrefsObjectScriptElement, kPDFPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kTaggedPDFPrefsPropertyScriptElement, kPDFPrefix + 244)
DECLARE_PMID(kScriptInfoIDSpace, kPDFStructureOrderEnumScriptElement, kPDFPrefix + 245)
DECLARE_PMID(kScriptInfoIDSpace, kPDFStructureOrderPropertyScriptElement, kPDFPrefix + 246)
DECLARE_PMID(kScriptInfoIDSpace, kInteractivePDFUseStructureForTabsPropertyScriptElement, kPDFPrefix + 247)

// Display title
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportDisplayTitlePropertyScriptElement, kPDFPrefix + 248)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportDisplayTitleEnumScriptElement, kPDFPrefix + 249)

//Default Document Language...
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportLanguagePreferencePropertyScriptElement, kPDFPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportSinglePagesPDFPropertyScriptElement, kPDFPrefix + 251)
DECLARE_PMID(kScriptInfoIDSpace, kPDFExportSinglePagesPDFSuffixPropertyScriptElement, kPDFPrefix + 252)

//Import PDF Comments
DECLARE_PMID(kScriptInfoIDSpace, kPDFImportCommentSuiteScriptElement, kPDFPrefix + 253)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationObjectScriptElement, kPDFPrefix + 254)
DECLARE_PMID(kScriptInfoIDSpace, kReplyObjectScriptElement, kPDFPrefix + 255)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationStatusEnumScriptElement, kPDFExtraPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationTypeEnumScriptElement, kPDFExtraPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationReviewerPropertyScriptElement, kPDFExtraPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationContentPropertyScriptElement, kPDFExtraPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationDatePropertyScriptElement, kPDFExtraPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationStatusPropertyScriptElement, kPDFExtraPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationTypePropertyScriptElement, kPDFExtraPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationIsOrphanPropertyScriptElement, kPDFExtraPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationIsAppliedPropertyScriptElement, kPDFExtraPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kReplyReviewerPropertyScriptElement, kPDFExtraPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kReplyContentPropertyScriptElement, kPDFExtraPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kReplyDatePropertyScriptElement, kPDFExtraPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageDestinationObjectScriptElement, kPDFExtraPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageItemDestinationObjectScriptElement, kPDFExtraPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationTextDestinationObjectScriptElement, kPDFExtraPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationDestinationPropertyScriptElement, kPDFExtraPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageDestinationPagePropertyScriptElement, kPDFExtraPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageDestinationHighlightRectPropertyScriptElement, kPDFExtraPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageDestinationTargetPointPropertyScriptElement, kPDFExtraPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageItemDestinationPageItemPropertyScriptElement, kPDFExtraPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageItemDestinationHighlightRectPropertyScriptElement, kPDFExtraPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPageItemDestinationTargetPointPropertyScriptElement, kPDFExtraPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationTextDestinationStoryPropertyScriptElement, kPDFExtraPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationTextDestinationStartIndexPropertyScriptElement, kPDFExtraPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationTextDestinationEndIndexPropertyScriptElement, kPDFExtraPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kCreateAnnotationMethodScriptElement, kPDFExtraPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kCreateReplyMethodScriptElement, kPDFExtraPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kCreateAnnotationPageDestinationMethodScriptElement, kPDFExtraPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kCreateAnnotationPageItemDestinationtMethodScriptElement, kPDFExtraPrefix + 29)
DECLARE_PMID(kScriptInfoIDSpace, kCreateAnnotationTextDestinationMethodScriptElement, kPDFExtraPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationPathGeometryPropertyScriptElement, kPDFExtraPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kAnnotationFilePathPropertyScriptElement, kPDFExtraPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kPDFImportCommentsMethodScriptElement, kPDFExtraPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kChangeAnnotationStatusMethodScriptElement, kPDFExtraPrefix + 34)

//GUIDS
// {496F0BE0-7834-11d2-AAF0-00C04FA37726}
#define kExportPdfPref_CLSID { 0x496f0be0, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {A3736549-4F5C-11d2-AB07-00C04FA349C7}
#define kExportPdfStyle_CLSID { 0xa3736549, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A373654A-4F5C-11d2-AB07-00C04FA349C7}
#define kExportPdfStyles_CLSID { 0xa373654a, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A373654B-4F5C-11d2-AB07-00C04FA349C7}
#define kPDFPlacePref_CLSID { 0xa373654b, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {5D94D6F9-13F3-4cf5-A1E7-B67F7102F69D}
#define kPDFAttribute_CLSID { 0x5d94d6f9, 0x13f3, 0x4cf5, { 0xa1, 0xe7, 0xb6, 0x7f, 0x71, 0x2, 0xf6, 0x9d } }
// {F4D7E523-5ED7-42b4-A601-C8B93C54EFFC}
#define kGalleyPDFExportPref_CLSID { 0xf4d7e523, 0x5ed7, 0x42b4, { 0xa6, 0x1, 0xc8, 0xb9, 0x3c, 0x54, 0xef, 0xfc } }
// {92E3E965-465F-4d84-9810-838658D5895A}
#define kLayoutPDFExportPref_CLSID { 0x92e3e965, 0x465f, 0x4d84, { 0x98, 0x10, 0x83, 0x86, 0x58, 0xd5, 0x89, 0x5a } }
// {E6E07CAE-624C-4367-9746-6431E949631A}
#define kInteractivePDFExportPref_CLSID { 0xe6e07cae, 0x624c, 0x4367, { 0x97, 0x46, 0x64, 0x31, 0xe9, 0x49, 0x63, 0x1a } }
// {BDF91FB2-51D9-475a-B71A-A2C570A2B07E}
#define kTaggedPDFPref_CLSID { 0xbdf91fb2, 0x51d9, 0x475a, { 0xb7, 0x1a, 0xa2, 0xc5, 0x70, 0xa2, 0xb0, 0x7e } }

// {2E896C89-288F-4635-A4F9-208E90B38CDC}
#define kAnnotation_CLSID { 0x2e896c89, 0x288f, 0x4635, { 0xa4, 0xf9, 0x20, 0x8e, 0x90, 0xb3, 0x8c, 0xdc } }
// {12DBB49A-1C97-46B9-8EDD-EE80F7486215}
#define kAnnotations_CLSID { 0x12dbb49a, 0x1c97, 0x46b9, { 0x8e, 0xdd, 0xee, 0x80, 0xf7, 0x48, 0x62, 0x15 } }
// {CE717876-9EC6-4374-8D0D-73ECA2060629}
#define kReply_CLSID { 0xce717876, 0x9ec6, 0x4374, { 0x8d, 0x0d, 0x73, 0xec, 0xa2, 0x06, 0x06, 0x29 } }
// {6F7C2BDF-236B-463B-98B1-AF3428827D27}
#define kReplies_CLSID {0x6f7c2bdf, 0x236b, 0x463b, { 0x98, 0xb1, 0xaf, 0x34, 0x28, 0x82, 0x7d, 0x27 } }
// {15BAA68B-72E2-49DF-9C49-51A3BACCF503}
#define kAnnotationPageDestination_CLSID {0x15baa68b, 0x72e2, 0x49df, { 0x9c, 0x49, 0x51, 0xa3, 0xba, 0xcc, 0xf5, 0x03 } }
// {A61D0A17-51EF-40C3-858C-EF0A9A1B9B40}
#define kAnnotationPageDestinations_CLSID {0xa61d0a17, 0x51ef, 0x40c3, { 0x85, 0x8c, 0xef, 0x0a, 0x9a, 0x1b, 0x9b, 0x40 } }
// {330F023A-2814-4198-8BC5-8CA1FBEEED79}
#define kAnnotationPageItemDestination_CLSID {0x330f023a, 0x2814, 0x4198, { 0x8b, 0xcf, 0x8c, 0xa1, 0xfb, 0xee, 0xed, 0x79 } }
// {30EE1B4E-7FB5-443E-9E37-8D36005BD5D9}
#define kAnnotationPageItemDestinations_CLSID {0x30ee1b4e, 0x7fb5, 0x443e, { 0x9e, 0x37, 0x8d, 0x36, 0x00, 0x5b, 0xd5, 0xd9 } }
// {3DF8B9A8-38FD-4BFF-B193-90CE602E3466}
#define kAnnotationTextDestination_CLSID {0x3df8b9a8, 0x38fd, 0x4bff, { 0xb1, 0x93, 0x90, 0xce, 0x60, 0x2e, 0x34, 0x66 } }
// {43EEFC76-2FCC-48B0-B37E-B5B21A238C20}
#define kAnnotationTextDestinations_CLSID {0x43eefc76, 0x2fcc, 0x48b0, { 0xb3, 0x7e, 0xb5, 0xb2, 0x1a, 0x23, 0x8c, 0x20 } }

//ScriptIDs
enum PDFScriptIDs
{
	c_PDF =				'PDF ',
	c_PDFs =			'PDFs',
	en_PDF				= c_PDF,
};

//Misc
#define kPDFSelDialogNodeID   kPDFPrefix + 1

#define kMaxFlipPagesSpeed					32767
#define kDefaultFlipPagesSpeed				5
#define kMinFlipPagesSpeed					0
#define kMaxInteractivePDFResolution		300
#define kDefaultInteractivePDFResolution	72
#define kMinInteractivePDFResolution		72
#define kPageTransitionFromDocument			kPageTransitionFromDocumentClassID

// for Interactive PDF, used in setting
// the extension level for the PDF produced
#define kBaseVersion_1_7					"1.7"
#define kExtension_Version_3				3

// Values from Rich Media Content Spec page 10/11
#define kDefaultPDFAnnotWindowWidth			288
#define kMaxPDFAnnotWindowWidth				576
#define kMinPDFAnnotWindowWidth				72
#define kDefaultPDFAnnotWindowHeight		216
#define kMaxPDFAnnotWindowHeight			432
#define kMinPDFAnnotWindowHeight			72
#define kDefaultPDFAnnotWindowOffset		18


#endif // __PDFID__



