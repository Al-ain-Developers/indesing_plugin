//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/defines/FormFieldUIDefs.h $
//  
//  Owner: Mark VerMurlen
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
//  Contains IDs (mostly resource ids) used by the FormFieldUI plug-in
//  
//========================================================================================

#pragma once
#ifndef __FormFieldUIDefs__
#define __FormFieldUIDefs__

#include "StdHeightWidthConstants.h"

// Panel lists
#define kPanelList_ButtonsPanelRsrcID		128
#define kPanelList_MSOPanelRsrcID			129

// String related...

#define kBehaviorUIStringsRsrcID			700
#define kFormFieldUIStringsRsrcID			800
#define kFormFieldUIStringsNoTransRsrcID	900
#define kFormFieldUIShortcutStringsRsrcID	1000

// MultiStateObject Panel

#define kMSOPanelRsrcID						7000
#define kMSOPanelIconRsrcID					7100
#define kMSOPanelTreeViewNodeRsrcID			7200
#define kMSOPanelTreeViewSmallNodeRsrcID	7300
#define kMSOPanelTreeViewLargeNodeRsrcID	7400
#define kMSOPanelTreeViewExtraLargeNodeRsrcID	7500

#define kMSOStateSmallRowHeight				kCC2016PanelTreeNodeSmallRowHeight
#define kMSOStateMediumRowHeight			kCC2016PanelTreeNodeWithThumbnailHeight
#define kMSOStateLargeRowHeight				kCC2016PanelTreeNodeWithLargeThumbnailHeight
#define kMSOStateExtraLargeRowHeight		kCC2016PanelTreeNodeWithExtraLargeThumbnailHeight

#define kMSOStateSmallRowContentHeight			kCC2016PanelTreeNodeContentSmallRowHeight
#define kMSOStateMediumRowContentHeight			kCC2016PanelTreeNodeWithThumbnailContentHeight
#define kMSOStateLargeRowContentHeight			kCC2016PanelTreeNodeWithLargeThumbnailContentHeight
#define kMSOStateExtraLargeRowContentHeight		kCC2016PanelTreeNodeWithExtraLargeThumbnailContentHeight

const uint32 kHeaderHeight							= (kCC2016StandardWidgetHeight + 2*4);
const uint32 kMSOPanelHeaderContentVerticalOffset	= (kHeaderHeight - kCC2016StandardWidgetHeight) / 2;


// These are detail levels from IListBoxDetailController on the appearance panel
// and the tree view in the multi-state object panel
const int kSmallSize = 1;
const int kMediumSize = 2;
const int kLargeSize = 3;
const int kExtraLargeSize = 4;

// ----- Resource ID of Appearance Panel

#define kAppearancePaletteRsrcID			1100
#define kStateListSmallElementRsrcID		1200
#define kStateListMediumElementRsrcID		1210
#define kStateListLargeElementRsrcID		1220
#define kStateListExtraLargeElementRsrcID	1230

// action rsrc id

// ----- Icon resource ids.
#define kStateEnabledIcon					1513
#define kStateDisabledIcon					kStateBlankIcon
#define kStateBlankIcon						1515
#define kAppearancePaletteIconRsrcID		1518
#define kAddActionIconRsrcId				1520
#define kRemoveActionIconRsrcId				1522
#define kConvertToButtonIcon				1525
#define kConvertToObjectIcon				1527
#define kShowPreviewIconRsrcID				1529

#define kCheckMarkIconRsrcID 				1600
#define kCheckBoxPanelRsrcID				1601
#define kRadioButtonPanelRsrcID				1602
#define kListBoxPanelRsrcID					1603 //Also used by ComboBox
#define kTextFieldPanelRsrcID				1604

#define kMediumThumbnailPictRsrcID			1620
#define kLargeThumbnailPictRsrcID			1630
#define kExtraLargeThumbnailPictRsrcID		1640

#define kFormFieldUIActionResID				1800

#define kShowFieldIconRsrcID 				2700
#define kHideFieldIconRsrcID		 		2701
#define kBlankIconRsrcID		 			2702

#define kChooseFileIconRsrcId				2800

#define kMSOIsSelectedIconRsrcID			2900
#define kMSOIsNotSelectedIconRsrcID			2901
#define kMSOStateIsSelectedIconRsrcID		2902
#define kPasteIntoMSOStateIconRsrcID		2903
#define kMSOStateContentIsSelectedIconRsrcID 2904
#define kAddToMSOStateIconRsrcID			2905

#define kAddListOptionIconRsrcId			2906

//SPAM twright 03/07/2001 Don't know what the legal range for these
//default palette ids are, but apparently they are only magic numbers
//that need to be unique in order for panels to go in unique palettes
//That is, they aren't registered or referenced anywhere but PanelList
//resources in .fr files.

#define kDefaultFormsPalette	99


// Unique string keys for buttons.  Translation is provided by host so do NOT include it
// in your string translation table:
#define kButtonOK					"OK"
#define kButtonCancel				"Cancel"
#define kButtonReset				"Reset"
#define kButtonApply				"Apply"
#define kButtonPrevious				"Pre&v"
#define kButtonNext					"Ne&xt"

#define kBehaviorsPanelActionResID 						1300
#define kBehaviorsActionNodeWidgetRsrcID 				1500
#define kEditBehaviorsDialogRsrcID 						1700
#define kSimpleEditBehaviorsDialogRsrcID 				1720
#define kEditDocumentJavaScriptDialogRsrcID 			1740
#define kChooseBehaviorDialogRsrcID 					1800
#define kBehaviorsListNodeWidgetRsrcID 					1900
#define kMoviePanelRsrcID 								2000
#define kGoToFirstPagePanelRsrcID 						2100
#define kGoToPagePanelRsrcID							2150
#define kGoToLastPagePanelRsrcID 						2200
#define kGoToNextPagePanelRsrcID 						2300
#define kGoToPreviousPagePanelRsrcID 					2400
#define kShowHideFieldsPanelRsrcID 						2500
#define kFieldsTreeNodeWidgetRsrcID 					2600
#define kGoToURLPanelRsrcID		 						2900
#define kImportDataPanelRsrcID		 					3000
#define kResetFormPanelRsrcID		 					3200
#define kResetFieldTreeNodeWidgetRsrcID		 			3300
#define kSubmitFormPanelRsrcID		 					3400
#define kSubmitFieldTreeNodeWidgetRsrcID		 		3500
#define kOpenFilePanelRsrcID		 					3600
//gap
#define kJavaScriptPanelRsrcID		 					3900
#define kFormatNumberPanelRsrcID		 				4000
#define kFormatPercentPanelRsrcID		 				4100
#define kFormatDatePanelRsrcID		 					4200
#define kFormatTimePanelRsrcID		 					4300
#define kFormatSpecialPanelRsrcID		 				4400
#define kFormulaPanelRsrcID		 						4500
#define kFormulaFieldTreeNodeWidgetRsrcID		 		4510
#define kMarkReadOnlyPanelRsrcID		 				4600
#define kMarkReadOnlyFieldTreeNodeWidgetRsrcID		 	4610
#define kValidateRangePanelRsrcID		 				4700
#define kGoToAnchorPanelRsrcID							4800
#define kGoToNextViewPanelRsrcID 						4900
#define kGoToPreviousViewPanelRsrcID 					5000
#define kViewZoomPanelRsrcID 							5100
#define kSoundPanelRsrcID 								5200

#define kBehaviorsDialogCreatorRsrcID 					5300
#define kBehaviorsDlgRsrcID 							5400

#define kBehaviorUIErrorStringTableRsrcID 				5600

#define kFormFieldPropertiesDlgRsrcID		5700
#define kCreateFormDialogRsrcID				5750
#define kFormTextColorDialogRsrcID			5800
#define kAppearancePanelPrefsDialogRsrcID	5850
#define kStateOptionsDialogRsrcID			5900
#define kCalculationOrderDialogRsrcID		5950
#define kTabOrderDialogRsrcID				6000
#define kButtonPDFOptionsDialogRsrcID		6100

// Form Options Selectable Dialog

#define kFormOptionsPanelOrderingRsrcID			6300
#define kFormOptionsDialogRsrcID 				6400
#define kFormFieldPropertiesDialogCreatorRsrcID 6500

// New behaviors for Rocket
#define kAnimationPanelRsrcID							6600
#define kSwitchToMSOStatePanelRsrcID					6700
#define kSwitchToNextMSOStatePanelRsrcID				6800
#define kSwitchToPrevMSOStatePanelRsrcID				6900

#define kBehaviorUIActionResID							9000

#define kListItemsNodeWidgetRsrcID 						9100

#define kButtonPanelMinWidth				270 // ID standard is 207
#define kButtonPanelMinWidth_JP				290 // ID standard is 207
#define kButtonPanelTextWidth_JP				77 
#define kButtonPanelButtonWidth				20
#define kButtonPanelWidgetsWidth			185
#define kActionChoiceWidgetsWidth			185
#define kButtonStaticWidgetsWidth			65

#endif // __FormFieldDefs__
