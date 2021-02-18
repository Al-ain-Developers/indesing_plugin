//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/EPSUIID.h $
//  
//  Owner: Graphics Team
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
//  Contains IDs used by the EPSImportUI plug-in
//  
//========================================================================================

#ifndef __EPSUIID__
#define __EPSUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kEPSUIPrefix	 RezLong(0x8f00)

// <Start IDC>
// PluginID
#define kEPSUIPluginName			"EPS UI"
DECLARE_PMID(kPlugInIDSpace, kEPSUIPluginID, kEPSUIPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kEPSImportDialogBoss, kEPSUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kEPSTestMenuBoss, kEPSUIPrefix  + 2)
DECLARE_PMID(kClassIDSpace, kEPSImportUIDialogServiceBoss, kEPSUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kEPSExportSelectableDialogBoss, kEPSUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kEPSExportDialogBoss, kEPSUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPageMarkExportDialogBoss, kEPSUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kQRCodeDialogBoss, kEPSUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kQRCodeContentDialogBoss, kEPSUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kQRCodeColorDialogBoss, kEPSUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kEPSUIMenuComponentBoss, kEPSUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kQRCodeColorWidgetBoss, kEPSUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kQRCodeColorSwatchListWidgetBoss, kEPSUIPrefix + 12)
//SVG
DECLARE_PMID(kClassIDSpace, kSVGImportDialogBoss, kEPSUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSVGImportUIDialogServiceBoss, kEPSUIPrefix + 14)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISETCOMMANDINTERFACE, kEPSUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETSTREAMINTERFACE, kEPSUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IMYFILEDATA, kEPSUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSIMPORTUIDIALOG, kEPSUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSUIUTILS, kEPSUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRCODEDITING, kEPSUIPrefix + 6)
//SVG
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGIMPORTUIDIALOG, kEPSUIPrefix + 7)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kEPSImportDialogControllerImpl, kEPSUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kEPSTestMenuImpl, kEPSUIPrefix  + 2)
DECLARE_PMID(kImplementationIDSpace, kEPSImportUIDialogServiceImpl,	kEPSUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kEPSImportUIDialogImpl,	kEPSUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kEPSExportSelDialogCreatorImpl, kEPSUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kEPSGeneralPageControllerImpl, kEPSUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kEPSGeneralPageCreatorImpl, kEPSUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kEPSAdvancedPageControllerImpl, kEPSUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kEPSAdvancedPageCreatorImpl, kEPSUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kEPSAdvancedPageObserverImpl, kEPSUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kEPSGeneralPageObserverImpl, kEPSUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kEPSUIUtilsImpl, kEPSUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kQRCodeDialogControllerImpl, kEPSUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kEPSUIMenuComponentImpl, kEPSUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kQRCodeSelDialogCreatorImpl, kEPSUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kQRCodeContentPanelCreatorImpl, kEPSUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kQRCodeColorPanelCreatorImpl, kEPSUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kQRCodeContentPanelObserverImpl, kEPSUIPrefix + 18)

DECLARE_PMID(kImplementationIDSpace, kQRCodeDialogObserverImpl, kEPSUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGeneratedGraphicTipImpl, kEPSUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kQRCodeColorProxyViewImpl, kEPSUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kQRCodeSwatchesPanelAttributesImpl, kEPSUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kQRCodeColorPanelObserverImpl, kEPSUIPrefix + 23)

//SVG
DECLARE_PMID(kImplementationIDSpace, kSVGImportUIDialogImpl, kEPSUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSVGImportUIDialogServiceImpl, kEPSUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSVGImportDialogControllerImpl, kEPSUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSVGImportDialogObserverImpl, kEPSUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSVGPreviewViewImpl, kEPSUIPrefix + 28)


// <Widget ID>
// Widget IDs for EPS Import Dialog
DECLARE_PMID(kWidgetIDSpace, kOPICheckBoxWidgetId, kEPSUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kClippingPathCheckBoxWidgetId, kEPSUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kEPSImportParentWidgetId, kEPSUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kProxyGroupWidgetId, kEPSUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kReadPreviewWidgetId, kEPSUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kGenerateFromPSWidgetId, kEPSUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kResolutionWidgetId, kEPSUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kProxyGroupTitleWidgetId, kEPSUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kProxyClusterWidgetId, kEPSUIPrefix + 9)
// Widget IDs for EPS Export Dialog
DECLARE_PMID(kWidgetIDSpace, kEPSExportSelDialogWidgetID, kEPSUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kEPSExportDialogWidgetId, kEPSUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kEPSACSIIButtonWidgetID, kEPSUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kEPSBinaryButtonWidgetID, kEPSUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kEPSCompatibleDropDownWidgetId, kEPSUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kEPSEmbedFontsDropDownWidgetId, kEPSUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kEPSImagesDropDownWidgetId, kEPSUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kEPSOPICheckBoxWidgetId, kEPSUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kEPSColorDropDownWidgetId, kEPSUIPrefix + 18)
// Widget IDs for Pages and Page Mark Dialog
DECLARE_PMID(kWidgetIDSpace, kPageMarkExportDialogWidgetId, kEPSUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPMAllPagesButtonWidgetId, kEPSUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPMRangesButtonWidgetId, kEPSUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kPMRangesEditBoxWidgetId, kEPSUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPMBleedEditBoxWidgetId, kEPSUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kBleed1TextWidgetId, kEPSUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kBleed2TextWidgetId, kEPSUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kEPSPagesGroupWidgetId, kEPSUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kEPSFormatTextWidgetId, kEPSUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kEPSCompatibilityTextWidgetId, kEPSUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kEPSEmbedFontsTextWidgetId, kEPSUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kEPSImageTextWidgetId, kEPSUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kEPSColorTextWidgetId, kEPSUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPmExportClusterWidgetId, kEPSUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kPageMarksGroupWidgetId, kEPSUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kPMSelectParentWidgetId, kEPSUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kBleedGroupWidgetId, kEPSUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kBleedTitleTextWidgetId, kEPSUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kPMOffsetEditBoxWidgetId, kEPSUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kEPSImportGraphicsGroupWidgetId, kEPSUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kEPSOmitGroupWidgetId, kEPSUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kEPSOmitEPSWidgetId, kEPSUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kEPSOmitPDFWidgetId, kEPSUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kEPSOmitBitmapWidgetId, kEPSUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kEPSExportGroup1WidgetId, kEPSUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kEPSExportGroup2WidgetId, kEPSUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kEPSPreviewTextWidgetId, kEPSUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kEPSPreviewDropDownWidgetId, kEPSUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OptFlatSetGroupWID, kEPSUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OptFlatSetGroupTitleWID, kEPSUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OptFlatSetStyleLabelWID, kEPSUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OptFlatSetStylePopupWID, kEPSUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OptFlatSetIgnoreSprOversWID, kEPSUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PageRangeClusterWidgetId, kEPSUIPrefix + 52)
//DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesReaderSpreadWidgetId, kEPSUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_TypeDropDownsClusterWidgetId, kEPSUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesPageMarkGroupWidgetId, kEPSUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedClusterWidgetID, kEPSUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedTopTextWidgetId, kEPSUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedTopWidgetId, kEPSUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedInsideTextWidgetId, kEPSUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedInsideWidgetId, kEPSUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedBottomTextWidgetId, kEPSUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedBottomWidgetId, kEPSUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedOutsideTextWidgetId, kEPSUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedOutsideWidgetId, kEPSUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_DataFormatTextWidgetId, kEPSUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_DataFormatDropDownWidgetId, kEPSUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OPIGroupLabelWidgetId, kEPSUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_SendDataLabelWidgetId, kEPSUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_ImagesGroupLabelWidgetId, kEPSUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_Group3WidgetId, kEPSUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_OmitForOPILabelWidgetID, kEPSUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kEPSInkManagerButtonWidgetId, kEPSUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_BleedChainWidgetID, kEPSUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_BleedMarkGroupWidgetId, kEPSUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesOrSpreadsClusterWidgetId, kEPSUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesRadioButtonWidgetId, kEPSUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_SpreadsRadioButtonWidgetId, kEPSUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedWidgetId, kEPSUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_SpreadBleedWidgetId, kEPSUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedLeftTextWidgetId, kEPSUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kEPSExp_PagesBleedRightTextWidgetId, kEPSUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kQRCodeTypeStaticWID, kEPSUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kQRCodeTypeDropDownWidgetID, kEPSUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kQRCodeSelDialogWidgetID, kEPSUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kQRCodeContentPanelWidgetId, kEPSUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kQRCodeColorPanelWidgetId, kEPSUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kQRCodeVCardWidgetID, kEPSUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kQRCodeHyperlinkOptionsWidgetID, kEPSUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kQRCodeTextOptionsWidgetID, kEPSUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kQRCodeEmailOptionsWidgetID, kEPSUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kQRCodeTextStringWidgetID, kEPSUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kQRCodeURLStaticWID, kEPSUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kQRCodeURLWidgetID, kEPSUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kQRCodeToWidgetID, kEPSUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kQRCodeSubjectWidgetID, kEPSUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kQRCodeEmailWidgetID, kEPSUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kQRCodeSMSNumberWidgetID, kEPSUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kQRCodeMessageWidgetID, kEPSUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kQRCodeSMSOptionsWidgetID, kEPSUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kQRCodeFirstNameWidgetID, kEPSUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kQRCodeLastNameWidgetID, kEPSUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kQRCodeTitleWidgetID, kEPSUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kQRCodeCellNoWidgetID, kEPSUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kQRCodePhoneNoWidgetID, kEPSUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kQRCodeEmailIdWidgetID, kEPSUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kQRCodeOrganizationWidgetID, kEPSUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kQRCodeAddressWidgetID, kEPSUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kQRCodeCityWidgetID, kEPSUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kQRCodeCountryWidgetID, kEPSUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kQRCodePINWidgetID, kEPSUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kQRCodePersonalURLWidgetID, kEPSUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kQRCodeFillWidgetId, kEPSUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kQRCodeStateWidgetID, kEPSUIPrefix + 116)
// Widget IDs for SVG Import Dialog
DECLARE_PMID(kWidgetIDSpace, kSVGCropToTextWidgetId, kEPSUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kSVGBoundingBoxWidgetId, kEPSUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kSVGArtWidgetId, kEPSUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kSVGClippingPathWidgetId, kEPSUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kSVGPlacePreviewGroupWidgetId, kEPSUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kSVGPlacePreviewGroupTextWidgetId, kEPSUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kSVGPreviewButtonWidgetID, kEPSUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kSVGImportParentWidgetId, kEPSUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kSVGPlacePreviewWidgetId, kEPSUIPrefix + 125)

// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kEPSImportUIDialogService, kEPSUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kEPSExportSelDialogService, kEPSUIPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kQRCodeSelDialogService, kEPSUIPrefix + 3)
//SVG
DECLARE_PMID(kServiceIDSpace, kSVGImportUIDialogService, kEPSUIPrefix + 4)


// <Action ID>
// Action IDs for barcodes.
DECLARE_PMID(kActionIDSpace, kCreateQRCodeActionID, kEPSUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kCreateQRCodeSepActionID, kEPSUIPrefix + 2)

#endif // __EPSUIID__

