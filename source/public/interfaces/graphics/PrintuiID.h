//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PrintuiID.h $
//  
//  Owner: Michael Easter
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
//  Contains IDs used by the printing plug-in
//  
//========================================================================================

#ifndef __PRINTUIID__
#define __PRINTUIID__

// ----- Includes -----

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kPrintUIPrefix	 RezLong(0x01d200)
#define kPrintUIPrefix2	 RezLong(0x01d400)

//_______________________________________________________________________________________
// <Start IDC>
// PluginID
//_______________________________________________________________________________________
#define kPrintUIPluginName 					"PrintUI"
DECLARE_PMID(kPlugInIDSpace, kPrintUIPluginID, kPrintUIPrefix + 1)


//_______________________________________________________________________________________
// <Class ID>
// ClassIDs
//_______________________________________________________________________________________
DECLARE_PMID(kClassIDSpace, kPrintMenuActionBoss, kPrintUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kEPSExportTestMenuBoss, kPrintUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kPrtErrorsDialogBoss, kPrintUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPrtErrorsFindFontButtonBoss, kPrintUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kPrintDialogBoss, kPrintUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kGeneralPanelBoss, kPrintUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetupPanelBoss, kPrintUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kColorManagementPanelBoss, kPrintUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kOutputPanelBoss, kPrintUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kInksListElementBoss, kPrintUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kMarksAndBleedsPanelBoss, kPrintUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kGraphicsPanelBoss, kPrintUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kAdvancedPanelBoss, kPrintUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kSummaryPanelBoss, kPrintUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kPrintIconButtonBoss, kPrintUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kPaperHeightComboBoxBoss, kPrintUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kPlatformPrintDialogCmdBoss, kPrintUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kGenStlEdtNameDialogBoss, kPrintUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kPrintDialogCmdBoss, kPrintUIPrefix + 49)
DECLARE_PMID(kClassIDSpace, kInkMgrDialogBoss, kPrintUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kInkMgrInkListWidgetBoss, kPrintUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kInkMgrInkListZOrderDEHandlerBoss, kPrintUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kInkMgrStateIconButtonBoss, kPrintUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kInkMgrToProcessCheckBoxBoss, kPrintUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kAliasNameInfoStaticTextWidgetBoss, kPrintUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kInkMgrInksGroupPanelWidgetBoss, kPrintUIPrefix + 71)
DECLARE_PMID(kClassIDSpace, kPaperWidthComboBoxBoss, kPrintUIPrefix + 72)
DECLARE_PMID(kClassIDSpace, kProxyDisplayWidgetBoss, kPrintUIPrefix + 76)
DECLARE_PMID(kClassIDSpace, kProxyOffscreenGraphicsPortBoss, kPrintUIPrefix + 77)
DECLARE_PMID(kClassIDSpace, kProxyStandardViewWidgetBoss, kPrintUIPrefix + 81)
DECLARE_PMID(kClassIDSpace, kProxyTextViewWidgetBoss, kPrintUIPrefix + 82)
DECLARE_PMID(kClassIDSpace, kProxyCustomViewWidgetBoss, kPrintUIPrefix + 83)
DECLARE_PMID(kClassIDSpace, kInkScreeningEditBoxWidgetBoss, kPrintUIPrefix + 99)
DECLARE_PMID(kClassIDSpace, kInkListBoxWidgetBoss, kPrintUIPrefix + 100)
DECLARE_PMID(kClassIDSpace, kPrintIconPanelWithBorderWidgetBoss, kPrintUIPrefix + 101)
DECLARE_PMID(kClassIDSpace, kInkMgrInfoStaticTextWidgetBoss, kPrintUIPrefix + 103)
//gap
DECLARE_PMID(kClassIDSpace, kTinFontsWarningDialogBoss,	kPrintUIPrefix + 150)
//gap
DECLARE_PMID(kClassIDSpace, kInkMgrListElementBoss, kPrintUIPrefix + 211)
//
DECLARE_PMID(kClassIDSpace, kPrintUIServiceBoss, kPrintUIPrefix + 212)

// ---- Moved from Print Styles plug-in
DECLARE_PMID(kClassIDSpace, kPrStEditMenuActionBoss, 		kPrintUIPrefix + 213)
// ---- end move.

DECLARE_PMID(kClassIDSpace, kBitmapResolutionObserverBoss, kPrintUIPrefix + 215)

//For Print Booklet
DECLARE_PMID(kClassIDSpace, kPrintBookletDialogBoss, kPrintUIPrefix + 216)
DECLARE_PMID(kClassIDSpace, kPrintBookletDialogCmdBoss, kPrintUIPrefix + 217)
DECLARE_PMID(kClassIDSpace, kPBSetupPanelBoss, kPrintUIPrefix + 218)
DECLARE_PMID(kClassIDSpace, kPBPreviewPanelBoss, kPrintUIPrefix + 219)
DECLARE_PMID(kClassIDSpace, kPBSummaryPanelBoss, kPrintUIPrefix + 220)
DECLARE_PMID(kClassIDSpace, kPrintBookletSaveDataCmdBoss, kPrintUIPrefix + 221)
DECLARE_PMID(kClassIDSpace, kPBPreviewPanelSpreadWidgetBoss, kPrintUIPrefix + 222)
DECLARE_PMID(kClassIDSpace, kPrintBookletPrintDialogCmdBoss, kPrintUIPrefix + 223)
DECLARE_PMID(kClassIDSpace, kPBSelDialogTreeViewWidgetBoss, kPrintUIPrefix + 224)
DECLARE_PMID(kClassIDSpace, kPBSelDialogTreeNodeWidgetBoss, kPrintUIPrefix + 225)
DECLARE_PMID(kClassIDSpace, kPBTreeNodeTextWidgetBoss, kPrintUIPrefix + 226)

// General panel continued
DECLARE_PMID(kClassIDSpace, kPageRangeNavigateWidgetBoss, kPrintUIPrefix + 227)
DECLARE_PMID(kClassIDSpace, kFirstPageRangeWidgetBoss, kPrintUIPrefix + 228)
DECLARE_PMID(kClassIDSpace, kLastPageRangeWidgetBoss, kPrintUIPrefix + 229)
DECLARE_PMID(kClassIDSpace, kPageRangeForwardWidgetBoss, kPrintUIPrefix + 230)
DECLARE_PMID(kClassIDSpace, kPageRangeBackwardWidgetBoss, kPrintUIPrefix + 231)
DECLARE_PMID(kClassIDSpace, kPageRangeCommonSizeWidgetBoss, kPrintUIPrefix + 232)
DECLARE_PMID(kClassIDSpace, kPrintDialogInfoTextWidgetBoss, kPrintUIPrefix + 233)








//_______________________________________________________________________________________
// <Interface ID>
// IIDs
//_______________________________________________________________________________________

DECLARE_PMID(kInterfaceIDSpace, IID_IINKMGRUIUTILS, kPrintUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTUIPRIVUTILS, kPrintUIPrefix + 2)
//
DECLARE_PMID(kInterfaceIDSpace, IID_IPRTERRORSDIALOGDATA, kPrintUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTLEDTNAMEDATA, kPrintUIPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IINKMGRINKLIST_ATTACHOBSERVER, kPrintUIPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROXYDISPLAYCONTROLDATA, kPrintUIPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTDIALOGDATA, kPrintUIPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROXYPANELSWITCHERCONTROLDATA, kPrintUIPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROXYPANELCONTROLDATA, kPrintUIPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTBOOKLETDIALOGDATA, kPrintUIPrefix + 42)

//_______________________________________________________________________________________
// <Implementation ID>
// ImplementationIDs
//_______________________________________________________________________________________

DECLARE_PMID(kImplementationIDSpace, kPrintMenuActionImpl, kPrintUIPrefix + 1)
//
DECLARE_PMID(kImplementationIDSpace, kInkMgrUIUtilsImpl, kPrintUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPrintUIServiceImpl, kPrintUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPrintUIPrivUtilsImpl, kPrintUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPrintUIProviderImpl, kPrintUIPrefix + 5)
//
DECLARE_PMID(kImplementationIDSpace, kEPSExportTestMenuImpl, kPrintUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPrtErrorsDialogControllerImpl, kPrintUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kPrtErrorsDialogDataImpl, kPrintUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kPrtErrorsFindFontObserverImpl, kPrintUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kPrintDialogControllerImpl, kPrintUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPrintDialogCreatorImpl, kPrintUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPrintDialogObserverImpl, kPrintUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kGeneralControllerImpl, kPrintUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kGeneralCreatorImpl, kPrintUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kGeneralObserverImpl, kPrintUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSetupControllerImpl, kPrintUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSetupCreatorImpl, kPrintUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSetupObserverImpl, kPrintUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kColorManagementControllerImpl, kPrintUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kColorManagementCreatorImpl, kPrintUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kColorManagementObserverImpl, kPrintUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kOutputControllerImpl, kPrintUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kOutputCreatorImpl, kPrintUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kOutputObserverImpl, kPrintUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kMarksAndBleedsControllerImpl, kPrintUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kMarksAndBleedsCreatorImpl, kPrintUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kMarksAndBleedsObserverImpl, kPrintUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kGraphicsControllerImpl, kPrintUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kGraphicsCreatorImpl, kPrintUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kGraphicsObserverImpl, kPrintUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kSummaryControllerImpl, kPrintUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kSummaryCreatorImpl, kPrintUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kSummaryObserverImpl, kPrintUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kPaperHeightComboBoxCalculatedValueImpl, kPrintUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kPrintIconButtonEventHandlerImpl, kPrintUIPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kPaperWidthComboBoxCalculatedValueImpl, kPrintUIPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kPlatformPrintDialogCmdImpl, kPrintUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtNameDataImpl, kPrintUIPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtNameDialogImpl, kPrintUIPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kPrintDialogCmdDataImpl, kPrintUIPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kInkMgrDialogControllerImpl, kPrintUIPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kInkMgrDialogObserverImpl, kPrintUIPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kInkMgrInkListAttachObserverImpl, kPrintUIPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kInkMgrInkListZOrderDEHandlerImpl, kPrintUIPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kInkMgrInkListZOrderDDSourceImpl, kPrintUIPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kInkMgrInkListZOrderDDTargetImpl, kPrintUIPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kInkMgrStateButtonEHImpl, kPrintUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kInkMgrInksGroupPanelViewImpl, kPrintUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kInkMgrToProcessBtnObserverImpl, kPrintUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kPaperWidthMeasureTypeImpl, kPrintUIPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kPaperHeightMeasureTypeImpl, kPrintUIPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtNameDlgCreatorImpl, kPrintUIPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kAdvancedControllerImpl, kPrintUIPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kAdvancedCreatorImpl, kPrintUIPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kAdvancedObserverImpl, kPrintUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kProxyDisplayObserverImpl, kPrintUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kProxyDisplayControlDataImpl, kPrintUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kPrintDialogDataImpl, kPrintUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kProxyPanelSwitcherControlDataImpl, kPrintUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kProxyStandardControlViewImpl, kPrintUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kProxyStandardControlDataImpl, kPrintUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kProxyTextControlViewImpl, kPrintUIPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kProxyTextControlDataImpl, kPrintUIPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kProxyCustomControlViewImpl, kPrintUIPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kProxyCustomControlDataImpl, kPrintUIPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kProxyPanelEventHandlerImpl, kPrintUIPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kInkScreeningTextValueImpl, kPrintUIPrefix + 166)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrintIconPanelViewImpl, kPrintUIPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kTinFontsWarningDialogControllerImpl, kPrintUIPrefix + 169)
//gap
DECLARE_PMID(kImplementationIDSpace, kTinFontsDialogObserverImpl,			kPrintUIPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kTinFontsDialogButtonEHImpl,			kPrintUIPrefix + 175)
//gap
DECLARE_PMID(kImplementationIDSpace, kInkMgrListElementViewImpl, kPrintUIPrefix + 233)

// ---- Moved from Print Styles plug-in
DECLARE_PMID(kImplementationIDSpace, kPrStyleDynMenuInfoImpl,		kPrintUIPrefix + 234)
// ---- end move.
DECLARE_PMID(kImplementationIDSpace, kColorManagementEventWatcherImpl,	kPrintUIPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kDPITextValueImpl,	kPrintUIPrefix + 237 )

//*
//* --- For Print Booklet
//*
//Dialog
DECLARE_PMID(kImplementationIDSpace, kPrintBookletDialogControllerImpl,	kPrintUIPrefix + 238 )
DECLARE_PMID(kImplementationIDSpace, kPrintBookletDialogCreatorImpl,	kPrintUIPrefix + 239 )
DECLARE_PMID(kImplementationIDSpace, kPrintBookletDialogObserverImpl,	kPrintUIPrefix + 240 )

DECLARE_PMID(kImplementationIDSpace, kPrintBookletDialogCmdImpl,		kPrintUIPrefix + 241 )

//Setup Panel
DECLARE_PMID(kImplementationIDSpace, kPBSetupPanelCreatorImpl,			kPrintUIPrefix + 242 )
DECLARE_PMID(kImplementationIDSpace, kPBSetupPanelControllerImpl,		kPrintUIPrefix + 243 )
DECLARE_PMID(kImplementationIDSpace, kPBSetupPanelObserverImpl,			kPrintUIPrefix + 244 )

//Preview Panel
DECLARE_PMID(kImplementationIDSpace, kPBPreviewPanelCreatorImpl,		kPrintUIPrefix + 245 )
DECLARE_PMID(kImplementationIDSpace, kPBPreviewPanelControllerImpl,		kPrintUIPrefix + 246 )
DECLARE_PMID(kImplementationIDSpace, kPBPreviewPanelObserverImpl,		kPrintUIPrefix + 247 )

//Summary Panel
DECLARE_PMID(kImplementationIDSpace, kPBSummaryPanelCreatorImpl,		kPrintUIPrefix + 248 )
DECLARE_PMID(kImplementationIDSpace, kPBSummaryPanelControllerImpl,		kPrintUIPrefix + 249 )
DECLARE_PMID(kImplementationIDSpace, kPBSummaryPanelObserverImpl,		kPrintUIPrefix + 250 )

DECLARE_PMID(kImplementationIDSpace, kPBSelDialogTreeViewWidgetMgrImpl,	kPrintUIPrefix + 251 )
DECLARE_PMID(kImplementationIDSpace, kPBPreviewSpreadWidgetObsImpl,		kPrintUIPrefix + 252 )
DECLARE_PMID(kImplementationIDSpace, kPBPreviewSpreadWidgetViewImpl,	kPrintUIPrefix + 253 )
DECLARE_PMID(kImplementationIDSpace, kPBSelDialogTreeViewAdapterImpl,	kPrintUIPrefix + 254 )

// kPrintUIPrefix + 255 has been scavenged above
DECLARE_PMID(kImplementationIDSpace, kPBTreeViewSelDlgSwitcherImpl,		kPrintUIPrefix2 + 0)
DECLARE_PMID(kImplementationIDSpace, kPrintBookletDialogDataImpl,		kPrintUIPrefix2 + 1)
DECLARE_PMID(kImplementationIDSpace, kPBSelDialogTNControlViewImpl,		kPrintUIPrefix2 + 2)

DECLARE_PMID(kImplementationIDSpace, kPBPreviewPanelEventHandlerImpl,	kPrintUIPrefix2 + 3)

DECLARE_PMID(kImplementationIDSpace, kPageRangeNavigationWidgetTipImpl,	kPrintUIPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kPageRangeNavigateObserverImpl,	kPrintUIPrefix2 + 5)



//_______________________________________________________________________________________
// <Widget ID>
//	Widget IDs
//_______________________________________________________________________________________

// New for Sherpa
DECLARE_PMID(kWidgetIDSpace, kPrtUIErrorsDlgListBoxWidgetID,			kPrintUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPrtErrorsDialogWidgetID,					kPrintUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPrtErrorsFindFontButtonWidgetID,			kPrintUIPrefix + 3)
																		
// New for Anna															
//print selectable dialog															
DECLARE_PMID(kWidgetIDSpace, kPrintDialogWidgetID,						kPrintUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPrinterStyleLabelWidgetID,				kPrintUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPrinterStylePopupWidgetID,				kPrintUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPrinterLabelWidgetID,						kPrintUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPrinterPopupWidgetID,						kPrintUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPPDLabelWidgetID,							kPrintUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kPPDPopupWidgetID,							kPrintUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kProxyDisplayWidgetID,						kPrintUIPrefix + 11)
// kOKButtonWidgetID defined elsewhere									
// kCancelButton_WidgetID defined elsewhere								
DECLARE_PMID(kWidgetIDSpace, kSaveStyleButtonWidgetID,					kPrintUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kPrinterButtonWidgetID,					kPrintUIPrefix + 13)
#if defined(MACINTOSH)													
DECLARE_PMID(kWidgetIDSpace, kPageSetupButtonWidgetID,					kPrintUIPrefix + 14)
#endif
DECLARE_PMID(kWidgetIDSpace, kPrintPreviewButtonWidgetID,				kPrintUIPrefix + 39)

// kPrintUIPrefix + 15 has been scavenged below
// kSelectDialogPopupWidgetID defined elsewhere
// kDialogGroupPanelWidgetID defined elsewhere

// General panel
DECLARE_PMID(kWidgetIDSpace, kGeneralPanelWidgetID,						kPrintUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPanelLabelWidgetID,						kPrintUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kPanelDividerWidgetID,						kPrintUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kCopiesLabelWidgetID,						kPrintUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kCopiesEditWidgetID,						kPrintUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kCollateCheckBoxWidgetID,					kPrintUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kReverseOrderCheckBoxWidgetID,				kPrintUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPagesGroupPanelWidgetID,					kPrintUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPagesGroupLabelWidgetID,					kPrintUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kPagesLabelWidgetID,						kPrintUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kPagesClusterPanelWidgetID,				kPrintUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kAllRadioButtonWidgetID,					kPrintUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kRangeRadioButtonWidgetID,					kPrintUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kRangeEditWidgetID,						kPrintUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kSequenceLabelWidgetID,					kPrintUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kSequencePopupWidgetID,					kPrintUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kCurrentRadioButtonWidgetID,				kPrintUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kPrintMasterPagesCheckBoxWidgetID,			kPrintUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kOptionsGroupPanelWidgetID,				kPrintUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kOptionsLabelWidgetID,						kPrintUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kPrintNonPrintingObjectsCheckBoxWidgetID,	kPrintUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kPrintBlankPagesCheckBoxWidgetID,			kPrintUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kPrintGuidesAndGridsCheckBoxWidgetID,		kPrintUIPrefix + 38)
// + 39 has been scavenged above (kPrintPreviewButtonWidgetID)

// Setup Panels
DECLARE_PMID(kWidgetIDSpace, kSetupPanelWidgetID,						kPrintUIPrefix + 40)
// kPanelLabelWidgetID
// kPanelDividerWidgetID
DECLARE_PMID(kWidgetIDSpace, kPaperSizeGroupPanelWidgetID,				kPrintUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kPaperSizePanelWidgetID,					kPrintUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kPaperSizeLabelWidgetID,					kPrintUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kPaperSizePopupWidgetID,					kPrintUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kPaperWidthLabelWidgetID,					kPrintUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kPaperWidthNudgeWidgetID,					kPrintUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kPaperWidthEditWidgetID,					kPrintUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kPaperWidthTextWidgetID,					kPrintUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kPaperHeightLabelWidgetID,					kPrintUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kPaperHeightNudgeWidgetID,					kPrintUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kPaperHeightEditWidgetID,					kPrintUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kPaperHeightTextWidgetID,					kPrintUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kOrientationLabelWidgetID,					kPrintUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kOrientationHiliteBorderWidgetID,			kPrintUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kOrientationClusterWidgetID,				kPrintUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kPortraitIconWidgetID,						kPrintUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kLandscapeIconWidgetID,					kPrintUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kReversePortraitIconWidgetID,				kPrintUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kReverseLandscapeIconWidgetID,				kPrintUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kPaperOffsetLabelWidgetID,					kPrintUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kPaperOffsetNudgeWidgetID,					kPrintUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kPaperOffsetEditWidgetID,					kPrintUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kPaperGapLabelWidgetID,					kPrintUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kPaperGapNudgeWidgetID,					kPrintUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kPaperGapEditWidgetID,						kPrintUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kPaperTransverseCheckBoxWidgetID,			kPrintUIPrefix + 66)
// kOptionsGroupPanelWidgetID
// kOptionsLabelWidgetID
DECLARE_PMID(kWidgetIDSpace, kScaleLabelWidgetID,						kPrintUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kScaleClusterPanelWidgetID,				kPrintUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kScaleWidthRadioButtonWidgetID,			kPrintUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kScaleToFitRadioButtonWidgetID,			kPrintUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kScaleToFitLabelWidgetID,					kPrintUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kScaleWidthEditWidgetID,					kPrintUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kScaleHeightLabelWidgetID,					kPrintUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kScaleHeightEditWidgetID,					kPrintUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kConstrainProportionsCheckBoxWidgetID,		kPrintUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kPagePositionLabelWidgetID,				kPrintUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kPagePositionPopupWidgetID,				kPrintUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kThumbnailsCheckBoxWidgetID,				kPrintUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kThumbnailsPopupWidgetID,					kPrintUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kThumbnailsLabelWidgetID,					kPrintUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kTileCheckBoxWidgetID,						kPrintUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kTilePopupWidgetID,						kPrintUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kOverlapLabelWidgetID,						kPrintUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kOverlapEditWidgetID,						kPrintUIPrefix + 84)

// Marks & Bleed Panel
DECLARE_PMID(kWidgetIDSpace, kMarksAndBleedsPanelWidgetID,				kPrintUIPrefix + 85)
// kPanelLabelWidgetID
// kPanelDividerWidgetID
DECLARE_PMID(kWidgetIDSpace, kMarksGroupPanelWidgetID,					kPrintUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kMarksLabelWidgetID,						kPrintUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kAllPrintersMarksCheckBoxWidgetID,			kPrintUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kTypeLabelWidgetID,						kPrintUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kTypePopupWidgetID,						kPrintUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kCropMarksCheckBoxWidgetID,				kPrintUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kBleedMarksCheckBoxWidgetID,				kPrintUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kRegistrationMarksCheckBoxWidgetID,		kPrintUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kColorBarsCheckBoxWidgetID,				kPrintUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kPageInformationCheckBoxWidgetID,			kPrintUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kMarkWeightLabelWidgetID,					kPrintUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kMarkWeightPopupWidgetID,					kPrintUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kMarkOffsetLabelWidgetID,					kPrintUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kMarkOffsetNudgeWidgetID,					kPrintUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kMarkOffsetEditWidgetID,					kPrintUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kBleedGroupPanelWidgetID,					kPrintUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kBleedLabelWidgetID,						kPrintUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kTopLabelWidgetID,							kPrintUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kTopNudgeWidgetID,							kPrintUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kTopEditWidgetID,							kPrintUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kBottomLabelWidgetID,						kPrintUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kBottomNudgeWidgetID,						kPrintUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kBottomEditWidgetID,						kPrintUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kInsideLabelWidgetID,						kPrintUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kInsideNudgeWidgetID,						kPrintUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kInsideEditWidgetID,						kPrintUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kOutsideLabelWidgetID,						kPrintUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kOutsideNudgeWidgetID,						kPrintUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kOutsideEditWidgetID,						kPrintUIPrefix + 114)
																	
// Output Panel
DECLARE_PMID(kWidgetIDSpace, kOutputPanelWidgetID,						kPrintUIPrefix + 115)
// kPanelLabelWidgetID													
// kPanelDividerWidgetID												
DECLARE_PMID(kWidgetIDSpace, kColorLabelWidgetID,						kPrintUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kColorPopupWidgetID,						kPrintUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kColorsAsBlackCheckBoxWidgetID,			kPrintUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kTrappingLabelWidgetID,					kPrintUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kTrappingPopupWidgetID,					kPrintUIPrefix + 120) 
DECLARE_PMID(kWidgetIDSpace, kFlipLabelWidgetID,						kPrintUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kFlipPopupWidgetID,						kPrintUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kCompScreeningLabelWidgetID,				kPrintUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kCompScreeningPopupWidgetID,				kPrintUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kSepScreeningLabelWidgetID,				kPrintUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kSepScreeningPopupWidgetID,				kPrintUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kNegativeCheckBoxWidgetID,					kPrintUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kInksGroupPanelWidgetID,					kPrintUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kInksLabelWidgetID,						kPrintUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kColumnLabelWidgetID,						kPrintUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kStateIconSuiteButtonWidgetID,				kPrintUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kInnerPanelWidgetID,						kPrintUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kInksListWidgetID,							kPrintUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kInksListElementWidgetID,					kPrintUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kBorderPanel1WidgetID,						kPrintUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kPrintIconSuiteWidgetID,					kPrintUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kBorderPanel2WidgetID,						kPrintUIPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kColorSwatchWidgetID,						kPrintUIPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kPrintNameWidgetID,						kPrintUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kFrequencyWidgetID,						kPrintUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kAngleWidgetID,							kPrintUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kInkManagerButtonWidgetID,					kPrintUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kFrequencyLabelWidgetID,					kPrintUIPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kFrequencyEditWidgetID,					kPrintUIPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, klpiLabelWidgetID,							kPrintUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kAngleLabelWidgetID,						kPrintUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kAngleEditWidgetID,						kPrintUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kDegreeSymbolLabelWidgetID,				kPrintUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kStateColumnOuterPanelWidgetID,			kPrintUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kInkColumnOuterPanelWidgetID,				kPrintUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kFreqColumnOuterPanelWidgetID,				kPrintUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kAngleColumnOuterPanelWidgetID,			kPrintUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kSimulateOverprintCheckBoxWidgetID,		kPrintUIPrefix + 153)

// Graphics Panel
DECLARE_PMID(kWidgetIDSpace, kGraphicsPanelWidgetID,					kPrintUIPrefix + 154)
// kPanelLabelWidgetID													
// kPanelDividerWidgetID												
DECLARE_PMID(kWidgetIDSpace, kGraphicsGroupPanelWidgetID,				kPrintUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kGraphicsLabelWidgetID,					kPrintUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kSendDataLabelWidgetID,					kPrintUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kSendDataPopupWidgetID,					kPrintUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kDownloadLabelWidgetID,					kPrintUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kDownloadPopupWidgetID,					kPrintUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kDownloadPPDFontsCheckBoxWidgetID,			kPrintUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kPostScriptLabelWidgetID,					kPrintUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kPostScriptPopupWidgetID,					kPrintUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kDataFormatLabelWidgetID,					kPrintUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kDataFormatPopupWidgetID,					kPrintUIPrefix + 165)
																		
// Color Management Panel
DECLARE_PMID(kWidgetIDSpace, kColorManagementPanelWidgetID,				kPrintUIPrefix + 166)
// kPanelLabelWidgetID													
// kPanelDividerWidgetID
// NOTE: the following IDs are not used anymore in Firedrake enUS reworked CMS panel
DECLARE_PMID(kWidgetIDSpace, kSourceSpaceGroupPanelWidgetID,			kPrintUIPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kPrintSourceSpaceLabelWidgetID,			kPrintUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kSourceSpaceClusterPanelWidgetID,			kPrintUIPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kDocumentRadioButtonWidgetID,				kPrintUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kProofRadioButtonWidgetID,					kPrintUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kProofTextWidgetID,						kPrintUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kPrintSpaceGroupPanelWidgetID,				kPrintUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kPrintSpaceLabelWidgetID,					kPrintUIPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kPrintProfileLabelWidgetID,				kPrintUIPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kPrintProfilePopupWidgetID,				kPrintUIPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kCRDLabelWidgetID,							kPrintUIPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kCRDPopupWidgetID,							kPrintUIPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kPrintIntentLabelWidgetID,					kPrintUIPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kPrintIntentPopupWidgetID,					kPrintUIPrefix + 180)
// NOTE: the preceeding IDs are not used anymore in Firedrake enUS reworked CMS panel

// Advanced Panel
DECLARE_PMID(kWidgetIDSpace, kAdvancedPanelWidgetID,					kPrintUIPrefix + 181)
// kPanelLabelWidgetID													
// kPanelDividerWidgetID												
DECLARE_PMID(kWidgetIDSpace, kOPIGroupPanelWidgetID,					kPrintUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kOPILabelWidgetID,							kPrintUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kImageReplacementCheckBoxWidgetID,			kPrintUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kOmitForOPILabelWidgetID,					kPrintUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kEPSCheckBoxWidgetID,						kPrintUIPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kPDFCheckBoxWidgetID,						kPrintUIPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kBitmapImagesCheckBoxWidgetID,				kPrintUIPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kFontsGroupPanelWidgetID,					kPrintUIPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kFontsLabelWidgetID,						kPrintUIPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kGradientsGroupPanelWidgetID,				kPrintUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kGradientsLabelWidgetID,					kPrintUIPrefix + 192)
// kContinuousToneCheckBoxWidgetID - depreciated
DECLARE_PMID(kWidgetIDSpace, kFlattenerGroupPanelWidgetID,				kPrintUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kFlattenerLabelWidgetID,					kPrintUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kStyleLabelWidgetID,						kPrintUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kStylePopupWidgetID,						kPrintUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kIgnoreSpreadOverridesCheckBoxWidgetID,	kPrintUIPrefix + 198)
// kPrintUIPrefix + 199 has been scavenged below
// kPrintUIPrefix + 200 has been scavenged below

// Summary Panel																	
DECLARE_PMID(kWidgetIDSpace, kSummaryPanelWidgetID,						kPrintUIPrefix + 201)
// kPanelLabelWidgetID													
// kPanelDividerWidgetID												
DECLARE_PMID(kWidgetIDSpace, kSummaryGroupPanelWidgetID,				kPrintUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kSummaryTextWidgetID,						kPrintUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kSummaryScrollBarWidgetID,					kPrintUIPrefix + 204)

// For name dialog
DECLARE_PMID(kWidgetIDSpace, kEditNameDialogWidgetID,					kPrintUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kPrintNameLabelWidgetID,					kPrintUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kNameEditWidgetID,							kPrintUIPrefix + 207)

// Print proxy alternate views
DECLARE_PMID(kWidgetIDSpace, kProxyStandardViewWidgetID,				kPrintUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kProxyTextViewWidgetID,					kPrintUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace, kProxyCustomViewWidgetID,					kPrintUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow1LabelWidgetID,				kPrintUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow1ValueWidgetID,				kPrintUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow2LabelWidgetID,				kPrintUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow2ValueWidgetID,				kPrintUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow3LabelWidgetID,				kPrintUIPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow3ValueWidgetID,				kPrintUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow4LabelWidgetID,				kPrintUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow4ValueWidgetID,				kPrintUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow5LabelWidgetID,				kPrintUIPrefix + 219)
// TODO: Fix this WidgetID scavenging!!!
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow5ValueWidgetID,				kPrintUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow6ValueWidgetID,				kPrintUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow7ValueWidgetID,				kPrintUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kProxyTextRow8ValueWidgetID,				kPrintUIPrefix + 255)

// For Ink Manager dialog panel
DECLARE_PMID(kWidgetIDSpace, kInkMgrDialogWidgetID,						kPrintUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kDensityColumnOuterPanelWidgetID,			kPrintUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kTypeColumnOuterPanelWidgetID,				kPrintUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kSolidityColumnOuterPanelWidgetID,			kPrintUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kSequenceColumnOuterPanelWidgetID,			kPrintUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kInkMgrInkListWidgetID,					kPrintUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kInkMgrInkListElementWidgetID,				kPrintUIPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kInkListElementNormalWidgetID,				kPrintUIPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kInkListElementAliasedWidgetID,			kPrintUIPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kInkMgrStateIconWidgetID,					kPrintUIPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kAliasNameWidgetID,						kPrintUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kInkTypeWidgetID,							kPrintUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace, kDensityWidgetID,							kPrintUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kSolidityWidgetID,							kPrintUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kInkNameLabelWidgetID,						kPrintUIPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kInkTypeLabelWidgetID,						kPrintUIPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kInkTypePopupWidgetID,						kPrintUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kDensityLabelWidgetID,						kPrintUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kDensityEditWidgetID,						kPrintUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kSolidityLabelWidgetID,					kPrintUIPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kSolidityEditWidgetID,						kPrintUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kInkOrderLabelWidgetID,					kPrintUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kInkOrderEditWidgetID,						kPrintUIPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kInkAliasLabelWidgetID,					kPrintUIPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kInkAliasPopupWidgetID,					kPrintUIPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kInkMgrToProcessCheckBoxWidgetID,			kPrintUIPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kPrintStyleNameEditWidgetId,				kPrintUIPrefix + 246)

DECLARE_PMID(kWidgetIDSpace, kNameListComboBoxWidgetID,					kPrintUIPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kStyleNameStaticWidgetID,					kPrintUIPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kPrintExportSummaryButtonWidgetID,			kPrintUIPrefix + 249)

DECLARE_PMID(kWidgetIDSpace, kTrapSequenceWidgetID,						kPrintUIPrefix + 250)

DECLARE_PMID(kWidgetIDSpace, kCornerLabelWidgetID,						kPrintUIPrefix + 251)

// For DontShowAgain warning alerts
DECLARE_PMID(kWidgetIDSpace, kGenericPPDWarningWidgetId,				kPrintUIPrefix + 252)
DECLARE_PMID(kWidgetIDSpace, kNoPrintersWarningWidgetId,				kPrintUIPrefix + 253)
DECLARE_PMID(kWidgetIDSpace, kDefaultPDFWriterWarningWidgetId,			kPrintUIPrefix + 254)

// kPrintUIPrefix + 255 has been scavenged above
DECLARE_PMID(kWidgetIDSpace, kDriverSynchronizationWarningWidgetId,		kPrintUIPrefix2 + 0)
DECLARE_PMID(kWidgetIDSpace, kPrintExcessFlattenerResolutionWarning,    kPrintUIPrefix2 + 1)

// adding UsDocumentBleed, IncludeSlug and PrintBleedChain in pagemarkspanel_enus.fr
DECLARE_PMID(kWidgetIDSpace, kPrintUseDocBleedCheckBoxWidgetID,    kPrintUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace, kPrintBleedChainWidgetID,    kPrintUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace, kSlugGroupPanelWidgetID,    kPrintUIPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace, kSlugLabelWidgetID,    kPrintUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace, kPrintIncludeSlugCheckBoxWidgetID,    kPrintUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace, kBleedSlugLabelWidgetID,						kPrintUIPrefix2 + 7)

// ---- Moved from Printer Styles plug-in
DECLARE_PMID(kWidgetIDSpace, kPrStWarningDialogWID,		kPrintUIPrefix2 + 8)
DECLARE_PMID(kWidgetIDSpace, kPrStWarnIconWID,			kPrintUIPrefix2 + 9)
DECLARE_PMID(kWidgetIDSpace, kPrStWarnMessageWID,		kPrintUIPrefix2 + 10)
// ---- end move.

// new for reworked CMS panel for Firedrake
DECLARE_PMID(kWidgetIDSpace, kPrintMethodGroupPanelWidgetID,	kPrintUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace, kPrintMethodLabelWidgetID,			kPrintUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace, kOutputColorLabelWidgetID,			kPrintUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace, kOutputColorWidgetID,				kPrintUIPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace, kDocProfileLabelWidgetID,			kPrintUIPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace, kDocProfileWidgetID,				kPrintUIPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace, kColorHandlingLabelWidgetID,		kPrintUIPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace, kColorHandlingPopupWidgetID,		kPrintUIPrefix2 + 19)
DECLARE_PMID(kWidgetIDSpace, kPrinterProfileLabelWidgetID,		kPrintUIPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace, kPrinterProfilePopupWidgetID,		kPrintUIPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace, kPreserveColorCheckBoxWidgetID,	kPrintUIPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace, kColorHintInfoIconWidgetId,		kPrintUIPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace, kColorHintTextWidgetID,			kPrintUIPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace, kProofProfileLabelWidgetID,		kPrintUIPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace, kProofProfileWidgetID,				kPrintUIPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace, kSimPaperColorCheckBoxWidgetID,	kPrintUIPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace, kProofHintInfoIconWidgetId,		kPrintUIPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace, kProofHintTextWidgetID,			kPrintUIPrefix2 + 29)
DECLARE_PMID(kWidgetIDSpace, kPrintReminderInfoIconWidgetId,	kPrintUIPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace, kPrintReminderTextWidgetID,		kPrintUIPrefix2 + 31)

DECLARE_PMID(kWidgetIDSpace, kInkMgrLegacyS2PCheckBoxWidgetID,	kPrintUIPrefix2 + 32)

DECLARE_PMID(kWidgetIDSpace, kPrintGroupPanelWidgetID,			kPrintUIPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace, kPrintLabelWidgetID,			kPrintUIPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace, kPrintClusterPanelWidgetID,			kPrintUIPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace, kPrintColorHandleIconWidgetID,			kPrintUIPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace, kPrintPreserveWarnIconWidgetID,			kPrintUIPrefix2 + 37)

DECLARE_PMID(kWidgetIDSpace, kDescriptionGroupPanelWidgetID,			kPrintUIPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace, kPrtDescriptionLabelWidgetID,			kPrintUIPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace, kDescriptionIconWidgetID,			kPrintUIPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace, kDescriptionSmallWidgetID,			kPrintUIPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace, kDescriptionLargeWidgetID,			kPrintUIPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace, kPrtWarningLabelWidgetID,			kPrintUIPrefix2 + 43)

// The following widgets are used in TinFontsWarningDialog
DECLARE_PMID(kWidgetIDSpace, kTinFontsWarningDialogWidgetID,	kPrintUIPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace, kTinFontsCancelButtonWidgetID,		kPrintUIPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace, kTinFontsPBMinorTaskEditBoxWidgetID, kPrintUIPrefix2 + 46)
//DECLARE_PMID(kWidgetIDSpace, kTinFontsProgressBarWidgetID,		  kPrintUIPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace, kTinFontsPBTaskStatusEditBoxWidgetID,kPrintUIPrefix2 + 48)
DECLARE_PMID(kWidgetIDSpace, kTinFongsWarningIconWidgetID,		  kPrintUIPrefix2 + 49)
DECLARE_PMID(kWidgetIDSpace, kTinFongsWarningTextWidgetID,		  kPrintUIPrefix2 + 50)

// Changes for Cobalt
DECLARE_PMID(kWidgetIDSpace, kPrintAsBitmapCheckBoxWidgetID,	  kPrintUIPrefix2 + 52)
DECLARE_PMID(kWidgetIDSpace, kBitmapResolutionWidgetId,			  kPrintUIPrefix2 + 53)
DECLARE_PMID(kWidgetIDSpace, kPrintLayersLabelWidgetID,			  kPrintUIPrefix2 + 54)
DECLARE_PMID(kWidgetIDSpace, kPrintLayersPopupWidgetID,			  kPrintUIPrefix2 + 55)

//--- For Print Booklet
DECLARE_PMID(kWidgetIDSpace, kPrintBookletDialogWidgetID,		kPrintUIPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace, kPBSetupPanelWidgetID,				kPrintUIPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace, kPBSetupGroupPanelWidgetID,		kPrintUIPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace, kPBSetupGroupLabelWidgetID,		kPrintUIPrefix2 + 59)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewPanelWidgetID,			kPrintUIPrefix2 + 60)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewGroupPanelWidgetID,		kPrintUIPrefix2 + 61)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewGroupLabelWidgetID,		kPrintUIPrefix2 + 62)
DECLARE_PMID(kWidgetIDSpace, kPBBookletTypeGroupPanelWidgetID,	kPrintUIPrefix2 + 63)
DECLARE_PMID(kWidgetIDSpace, kPBBookletTypeLabelWidgetID,		kPrintUIPrefix2 + 64)
DECLARE_PMID(kWidgetIDSpace, kPBBookletTypePopupWidgetID,		kPrintUIPrefix2 + 65)
DECLARE_PMID(kWidgetIDSpace, kPBMarginsGroupPanelWidgetID,		kPrintUIPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace, kPBMarginsGroupLabelWidgetID,		kPrintUIPrefix2 + 67)
DECLARE_PMID(kWidgetIDSpace, kPBPagesLabelWidgetID,				kPrintUIPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace, kPBPagesClusterPanelWidgetID,		kPrintUIPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace, kPBAllRadioButtonWidgetID,			kPrintUIPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace, kPBRangeRadioButtonWidgetID,		kPrintUIPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace, kPBRangeEditWidgetID,				kPrintUIPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace, kPBTopLabelWidgetID,				kPrintUIPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace, kPBTopEditWidgetID,				kPrintUIPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace, kPBTopNudgeWidgetID,				kPrintUIPrefix2 + 75)
DECLARE_PMID(kWidgetIDSpace, kPBBottomLabelWidgetID,			kPrintUIPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace, kPBBottomEditWidgetID,				kPrintUIPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace, kPBBottomNudgeWidgetID,			kPrintUIPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace, kPBLeftLabelWidgetID,				kPrintUIPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace, kPBLeftEditWidgetID,				kPrintUIPrefix2 + 80)
DECLARE_PMID(kWidgetIDSpace, kPBLeftNudgeWidgetID,				kPrintUIPrefix2 + 81)
DECLARE_PMID(kWidgetIDSpace, kPBRightLabelWidgetID,				kPrintUIPrefix2 + 82)
DECLARE_PMID(kWidgetIDSpace, kPBRightEditWidgetID,				kPrintUIPrefix2 + 83)
DECLARE_PMID(kWidgetIDSpace, kPBRightNudgeWidgetID,				kPrintUIPrefix2 + 84)
DECLARE_PMID(kWidgetIDSpace, kPBPageGapLabelWidgetID,			kPrintUIPrefix2 + 85)
DECLARE_PMID(kWidgetIDSpace, kPBPageGapEditWidgetID,			kPrintUIPrefix2 + 86)
DECLARE_PMID(kWidgetIDSpace, kPBPageGapNudgeWidgetID,			kPrintUIPrefix2 + 87)
DECLARE_PMID(kWidgetIDSpace, kPBCreepLabelWidgetID,				kPrintUIPrefix2 + 88)
DECLARE_PMID(kWidgetIDSpace, kPBCreepEditWidgetID,				kPrintUIPrefix2 + 89)
DECLARE_PMID(kWidgetIDSpace, kPBCreepNudgeWidgetID,				kPrintUIPrefix2 + 90)
DECLARE_PMID(kWidgetIDSpace, kPBSigSizeLabelWidgetID,			kPrintUIPrefix2 + 91)
DECLARE_PMID(kWidgetIDSpace, kPBSigSizePopupWidgetID,			kPrintUIPrefix2 + 92)
DECLARE_PMID(kWidgetIDSpace, kPBCrossoverLabelWidgetID,			kPrintUIPrefix2 + 93)
DECLARE_PMID(kWidgetIDSpace, kPBCrossoverEditWidgetID,			kPrintUIPrefix2 + 94)
DECLARE_PMID(kWidgetIDSpace, kPBCrossoverNudgeWidgetID,			kPrintUIPrefix2 + 95)
DECLARE_PMID(kWidgetIDSpace, kPBTextLabelWidgetID,				kPrintUIPrefix2 + 96)
DECLARE_PMID(kWidgetIDSpace, kPBTextEditWidgetID,				kPrintUIPrefix2 + 97)
DECLARE_PMID(kWidgetIDSpace, kPBCreateNewDocCheckBoxWidgetID,	kPrintUIPrefix2 + 98)
DECLARE_PMID(kWidgetIDSpace, kPBPrintSettingsButtonWidgetID,	kPrintUIPrefix2 + 99)
DECLARE_PMID(kWidgetIDSpace, kPBPrinterLabelWidgetID,			kPrintUIPrefix2 + 100)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryPanelWidgetID,			kPrintUIPrefix2 + 101)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryGroupPanelWidgetID,		kPrintUIPrefix2 + 102)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryTextWidgetID,			kPrintUIPrefix2 + 103)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryScrollBarWidgetID,		kPrintUIPrefix2 + 104)
DECLARE_PMID(kWidgetIDSpace, kPBMarginsChainWidgetID,			kPrintUIPrefix2 + 105)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewPanelSpreadWidgetID,		kPrintUIPrefix2 + 106)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewStaticTextWidgetID,		kPrintUIPrefix2 + 107)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewScrollBarWidgetID,		kPrintUIPrefix2 + 108)
DECLARE_PMID(kWidgetIDSpace, kPBPrintPresetPopupWidgetID,		kPrintUIPrefix2 + 109)
DECLARE_PMID(kWidgetIDSpace, kPBPrintPresetLabelWidgetID,		kPrintUIPrefix2 + 110)
DECLARE_PMID(kWidgetIDSpace, kPBMessagesGroupPanelWidgetID,		kPrintUIPrefix2 + 111)
DECLARE_PMID(kWidgetIDSpace, kPBMessagesGroupLabelWidgetID,		kPrintUIPrefix2 + 112)
DECLARE_PMID(kWidgetIDSpace, kPBMessagesTextWidgetID,			kPrintUIPrefix2 + 113)
DECLARE_PMID(kWidgetIDSpace, kPBWarningGroupPanelWidgetID,		kPrintUIPrefix2 + 114)
DECLARE_PMID(kWidgetIDSpace, kPBWarningGroupLabelWidgetID,		kPrintUIPrefix2 + 115)
DECLARE_PMID(kWidgetIDSpace, kPBWarningTextWidgetID,			kPrintUIPrefix2 + 116)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryMsgGroupPanelWidgetID,	kPrintUIPrefix2 + 117)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryMsgGroupLabelWidgetID,	kPrintUIPrefix2 + 118)
DECLARE_PMID(kWidgetIDSpace, kPBSummaryMsgTextWidgetID,			kPrintUIPrefix2 + 119)
DECLARE_PMID(kWidgetIDSpace, kPBAutoCalcMarginsCheckBoxWidgetID,kPrintUIPrefix2 + 120)
DECLARE_PMID(kWidgetIDSpace, kPBPrintBlankPrinterSpreadsCheckBoxWidgetID, kPrintUIPrefix2 + 121)
DECLARE_PMID(kWidgetIDSpace, kPBPrinterStringLabelWidgetID,		kPrintUIPrefix2 + 122)
DECLARE_PMID(kWidgetIDSpace, kPBSelDialogTreeViewWidgetID,		kPrintUIPrefix2 + 123)
DECLARE_PMID(kWidgetIDSpace, kPBSelDialogTreeNodeWidgetID,		kPrintUIPrefix2 + 124)
DECLARE_PMID(kWidgetIDSpace, kPBSelDialogTreeNodeStaticTextWidgetID, kPrintUIPrefix2 + 125)
DECLARE_PMID(kWidgetIDSpace, kPBSelDialogTreeNodeCheckBoxWidgetID, kPrintUIPrefix2 + 126)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewWarningIconWidgetID,		kPrintUIPrefix2 + 127)
DECLARE_PMID(kWidgetIDSpace, kPBSaveSummaryButtonWidgetID,		kPrintUIPrefix2 + 128)
DECLARE_PMID(kWidgetIDSpace, kPBPreviewMsgsScrollBarWidgetID,	kPrintUIPrefix2 + 129)
DECLARE_PMID(kWidgetIDSpace, kPBBookletTypePanelWidgetID,		kPrintUIPrefix2 + 130)


// General panel continued
DECLARE_PMID(kWidgetIDSpace, kPageRangeNavigateWidgetID,		kPrintUIPrefix2 + 131)
DECLARE_PMID(kWidgetIDSpace, kFirstPageRangeIconWidgetID,		kPrintUIPrefix2 + 132)
DECLARE_PMID(kWidgetIDSpace, kPageRangeBackwardIconWidgetID,	kPrintUIPrefix2 + 133)
DECLARE_PMID(kWidgetIDSpace, kPageRangeForwardIconWidgetID,		kPrintUIPrefix2 + 134)
DECLARE_PMID(kWidgetIDSpace, kLastPageRangeIconWidgetID,		kPrintUIPrefix2 + 135)
DECLARE_PMID(kWidgetIDSpace, kPageRangeCommonSizeIconWidgetID,	kPrintUIPrefix2 + 136)

DECLARE_PMID(kWidgetIDSpace, kPagesOrSpreadsClusterWidgetId,	kPrintUIPrefix2 + 137)
DECLARE_PMID(kWidgetIDSpace, kPagesRadioButtonWidgetId,			kPrintUIPrefix2 + 138)
DECLARE_PMID(kWidgetIDSpace, kSpreadsRadioButtonWidgetId,		kPrintUIPrefix2 + 139)



//_______________________________________________________________________________________
// <Service ID>
//	Service IDs
//_______________________________________________________________________________________
DECLARE_PMID(kServiceIDSpace, kPrintBookletSelectableDialogService, kPrintUIPrefix + 1)

//_______________________________________________________________________________________
// <Error ID>
//	Error IDs
//_______________________________________________________________________________________

//_______________________________________________________________________________________
// <Action ID>
// ActionIDs
//_______________________________________________________________________________________

// ---- Moved from Printer Styles plug-in
DECLARE_PMID(kActionIDSpace, kPrStyleSepActionID, kPrintUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPrStEditActionID, kPrintUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPrStyleMenuDynamicActionID, kPrintUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kFirstPrinterStyleActionID, (kPrintUIPrefix + 5))
// ids between kFirstPrinterStyleActionID and kLastPrinterStyleActionID are reserved
DECLARE_PMID(kActionIDSpace, kLastPrinterStyleActionID, (kPrintUIPrefix + 220))
DECLARE_PMID(kActionIDSpace, kPrintBookletActionID, kPrintUIPrefix + 221) //vsethi PR_BL
// ---- end move.

//_______________________________________________________________________________________
// <ViewPortAttr ID>
// ViewPortAttrIDs
//_______________________________________________________________________________________

//Misc
#define kPBSelDialogNodeID   kPrintUIPrefix + 1

#endif // __PrintUIID__

// End, PrintUIID.h.
