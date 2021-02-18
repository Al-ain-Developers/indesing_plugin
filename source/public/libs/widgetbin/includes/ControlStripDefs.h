//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/ControlStripDefs.h $
//  
//  Owner: Paul Sorrick
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
//  Control Strip widget priority definitions. Used in ControlStripWidgetInfo.
//  
//========================================================================================

#pragma once
#ifndef __CONTROLSTRIPDEFS__
#define __CONTROLSTRIPDEFS__

#include "ControlSetDefs.h"
#include "ControlStripPriorityDefs.h"
#include "StdHeightWidthConstants.h"

#define kControlStripActionResID					1000
#define kControlStripStringsRsrcID 					1100
#define kControlStripRsrcID 						1300

#define kControlStripCustomizeDialogRsrcID			1800
#define kControlStripTreeCategoryRsrcID				1850
#define kControlStripTreeControlSetRsrcID			1900

// PNG icon IDs
#define kContentToFrameIconRsrcId					2001
#define kFrameToContentIconRsrcId					2002
#define kCenterContentIconRsrcId					2003
#define kFitContentPropIconRsrcId					2004
// Two more fitting icon below.

#define kVJTopIconRsrcId							2005
#define kVJCenterIconRsrcId							2006
#define kVJBottomIconRsrcId							2007
#define kVJJustifyIconRsrcId						2008

#define kNumColumnsIconRsrcId						2009

#define kSelectParentIconRsrcId						2010
#define kSelectChildIconRsrcId						2011

#define kFrameGridHCharsIconRsrcId					2012
#define kFrameGridVCharsIconRsrcId					2013
#define kFrameGridCharAkiIconRsrcId					2014
#define kFrameGridLineAkiIconRsrcId					2015
#define kFrameGridVerticalScaleIconRsrcId			2016
#define kFrameGridHorizontalScaleIconRsrcId			2017
#define kFrameGridColumnsIconRsrcId					2018
#define kFrameGridGutterIconRsrcId					2019

#define kCharacterModeIconRsrcId					2020
#define kParagraphModeIconRsrcId					2021

#define kSelectPrevSiblingIconRsrcId				2022
#define kSelectNextSiblingIconRsrcId				2023

#define kNamedGridStylePopupIconRsrcId				2024
#define kJCharacterModeIconRsrcId					2025
#define kJParagraphModeIconRsrcId					2026

#define kCharacterStylePopupIconRsrcId				2027
#define kParagraphStylePopupIconRsrcId				2028

#define kVJRightIconRsrcId							2030
#define kVJCenterHorizontallyIconRsrcId				2031
#define kVJLeftIconRsrcId							2032
#define kVJJustifyHorizontallyIconRsrcId			2033

#define kFillFramePropIconRsrcId					2034

#define kJCharacterStylePopupIconRsrcId				2036
#define kJParagraphStylePopupIconRsrcId				2037

#define kGutterIconRsrcId							2038

#define kIconBalanceColumns							2039
#define kIconSpanColumn								2040
#define kIconUnbalanceColumns						2041

#define kCreateLayoutSnapshotIconRsrcId				2042
#define kDeleteLayoutSnapshotIconRsrcId				2043
#define	kCustomizeCPButtonPNGRsrcID					2044
#define kAutoCropIconRsrcId							2045
#define kViewGuidesIconRsrcId						2046
#define kLockGuidesIconRsrcId						2047
#define kUnlockGuidesIconRsrcId						2048
#define kSmartGuidesIconRsrcId						2049
#define kFrameGridCharAlignIconRsrcId               2050
#define kFrameGridLineAlignIconRsrcId               2051
#define kFrameGridGridAlignIconRsrcId               2052


//----------Properties Panel Resource IDs(3000 onwards)--------------

#define kPropertiesPanelRsrcID					3000
#define kPropertiesPanelStringsRsrcID			3001
#define kPropertiesPanelListRsrcID				3002
#define kPropertiesPanelKitExpanderIconRsrcID	3003
#define kPropertiesPaletteIconRsrcID			3004


#define kEVETransformPanelGeometryPnlRsrcID		5700
#define kEVETransformPanelXFormPnlRsrcID		5800
#define kEVECharPanelFontsPropPnlRsrcID			5900
#define kEVECharPanelAttrsPropPnlRsrcID			6000
#define kPropertiesPanelKitTemplateRsrcID		6100
#define kPropertiesPanelFrameOptionsRsrcID		6200
#define kEvizedAlignPanelRsrcID					6300
#define kEvizedAlignPanelExpandedRsrcID			6400
#define kEvizedTextWrapPanelRsrcID				6500
#define kEvizedTextWrapPanelExpandedRsrcID      6600
#define kBNPropertiesPanelRsrcID		        6700
#define kEveParaPanelRsrcID                     6800
#define kEveParaPanelExpandedRsrcID				6900
#define kDocumentPanelPropertiesRsrcID			7000
#define kRulersGridsPnlRsrcID 					7100		
#define kGuidesPropertiesPanelRsrcID			7200
#define kPathFinderKitRsrcID					7300
#define kCornerShapePropertiesPanelRsrcID		7400
#define kFittingControlPropertiesPanelID        7500
#define kConvertPointKitWidgetRsrcID            7600
#define kLiquidLayoutPropertiesPanelRsrcID      7700
#define kTransformPanelCheckboxWidgetRsrcID     7800
#define kPageSizeKitWidgetRsrcID                7900
#define kGuidePreviousNextRsrcID				8000
#define kEvizedAlignPanelExpandedGuideRsrcID    8100
#define kEmptyKitPropertiesPanelRsrcID			8200
#define kAppearancePanelPropertiesPanelRsrcID	8300
#define kFillColorPopupPanelRsrcID				8400
#define kDimensionsPanelRsrcID                  8500
#define kDimensionsPanelExpandedRsrcID          8700    
#define kInsetPropertiesPanelRsrcID				8800
#define kCellDivisionsPropertiesPanelRsrcID     8900
#define kOpacityPropPanelRsrcID					9000
#define kPropertiesPanelColumnsAndLinesRsrcID   9100
#define kFrameGridAlignOptionsRsrcID            9200
#define kFrameGridOptionsRsrcID                 9300
#define kFrameGridOptionsExpandedRsrcID         9400
#define kPageKitPropertiesPanelRsrcID			9500
#define kPageMarginsAndColumnKitRsrcID			9600
#define kStrokeColorPopupPanelRsrcID			9700

//-----------------------------------------------------------

// Rsrc IDs for widgets supplied by GetEnabledWidgets
#define kTransformPanelXYWHControlStripRsrcID		50000
#define kPageSizePresetControlStripRsrcID			50050
#define kPageOrientationControlStripRsrcID			50075
#define kTransformPanelScaleRotateControlStripRsrcID 50100
#define kCharPanelAttrButtonsControlStripRsrcID		50200
#define kCharPanelKerningControlStripRsrcID			50300
#define kCharPanelScalingControlStripRsrcID			50400
#define kCharPanelMojikumiControlStripRsrcID		50500
#define kParaPanelAlignButtonsControlStripRsrcID	50600
#define kParaPanelIndentsControlStripRsrcID			50700
#define kParaPanelSpacingControlStripRsrcID			50800
#define kParaPanelDropCapControlStripRsrcID			50825
#define kParaPanelJSetsControlStripRsrcID			50850
#define kFrameOptionsControlStripRsrcID				50900
#define kTablesVerticalAlignmentControlStripRsrcID	51000
#define kStrokePanelControlStripRsrcID				51100
#define kFittingControlStripRsrcID					51200
#define kBaselineGridControlStripRsrcID				51300
#define kStrokeTablePanelControlStripRsrcID			51400
#define kParentChildControlStripRsrcID				51500
#define kCharPanelFontsControlStripRsrcID			51600
#define kFrameAndCursorControlStripRsrcID			51700
#define kFrameGridAttributesControlStripRsrcID		51800
#define kTextModeControlStripRsrcID					51900
#define kAlignControlStripRsrcID					52000
#define kParaPanelTableControlStripRsrcID			52100
#define kDistributeControlStripRsrcID				52200
#define kDistributeGuidesControlStripRsrcID			52300
#define kCharStyleControlStripRsrcID				52400
#define kParaStyleControlStripRsrcID				52500
#define kTextFrameFittingControlStripRsrcID			52600
#define kObjectStyleControlStripRsrcID				52700
#define kTablesUIInsetsControlStripRsrcID			52800
#define kFlipRotateControlStripRsrcID				52900
#define kTablesRowsColumnsControlStripRsrcID		53000
#define kTablesCellOptionsControlStripRsrcID		53100
#define kBNControlStripPanelRsrcID					53200
#define kXPUIControlStripRsrcID						53300
#define kMenuControlStripRsrcID						53400
#define kTableStyleControlStripRsrcID				53500
#define kTextWrapControlStripRsrcID					53600
#define kFrameGridViewOptionsControlStripRsrcID		53700
#define kFrameGridLinesAndColumnsControlStripRsrcID	53800
#define kTablesUIMergeUnmergeControlStripRsrcID		53900
#define kTextModeSeparatorControlStripRsrcID		54000
#define kBalanceColumnsControlStripRsrcID	54050
#define kVerticalJustificationControlStripRsrcID	54100
#define kCornerShapeControlStripRsrcID				54200
#define kLayoutOptionsControlStripRsrcID			54300
#define kFillStrokeColorPanelControlStripRsrcID		54400
#define kTextFillStrokeColorPanelControlStripRsrcID		54500
#define kTableFillStrokeColorPanelControlStripRsrcID	54600
#define kSpreadAlignControlStripRsrcID				54700
#define kSpreadDistributeControlStripRsrcID			54800
#define kGraphicCellFittingControlStripRsrcID			54900
#define kGraphicCellXPUIControlStripRsrcID				55000
#define kParaBorderShadingControlStripRsrcID			56000
#define kVarFontDsgnXsDialogWidgetRsrcID		56100
#define kVarFontDsgnXsTreeNodeRsrcID				56200



// Default frame for control strip
#define kControlStripLeft							0
#define kControlStripTop							0
#define kControlStripRight							1250
#define kControlStripBottom							57
#define kControlStripSeparatorTop					SEPARATOR_OFFSET
#define kControlStripSeparatorBottom				kControlStripBottom - SEPARATOR_OFFSET
#define kControlStripDefaultFrame					kControlStripLeft, kControlStripTop, kControlStripRight, kControlStripBottom
#define kControlStripDimensions						kControlStripRight - kControlStripLeft, kControlStripBottom - kControlStripTop

// Menu-widget related defines
#define kControlStripMenuTop						3
#define kControlStripMenuHeight						24
#define kControlStripMenuWidth						24

// Smallest possible size for control strip
#define kControlStripMinWidth						kControlStripMenuWidth + kCC2016PanelBottomResizeWidgetWidth                        
#define kControlStripMaxWidth						5000
#define kControlStripMonitorInset					12


// Menus names for popup menu on right of control strip
#define kControlStripLayoutMenuName				"ControlStripLayoutCSB"
#define kControlStripSpreadMenuName				"ControlStripSpreadCSB"
#define kControlStripTextMenuName				"ControlStripTextCSB"
#define kControlStripTableMenuName				"ControlStripTableCSB"
#define kControlStripDefaultMenuName			kControlStripLayoutMenuName		// Same as LayoutCSB case
#define kControlStripDefaultTextMenuName		kControlStripTextMenuName		// Same as TextCSB case
#define kControlStripStructureMenuName			kControlStripDefaultMenuName	// Same as LayoutCSB case for now

// Category order for the Customize menu
const PMReal kControlStripObjectCategory = 10.0;	// For control sets that appear in LayoutCSB
const PMReal kControlStripCharacterCategory = 20.0;	// For control sets that appear in TextCSB
const PMReal kControlStripParagraphCategory = 30.0;	// For control sets that appear in TextCSB
const PMReal kControlStripTableCategory = 40.0;		// For control sets that appear in TablesCSB
const PMReal kControlStripSpreadCategory = 45.0;	// For control sets that appear in SpreadCSB
const PMReal kControlStripOtherCategory = 50.0;		// For other control sets, appear at end of dynamic Customize menu (e.g. Quick Apply and Menu widget)
const PMReal kControlStripHiddenCategory = 60.0;	// For control sets that shouldn't appear in dynamic Customize menu

// Category names for the Customize menu
#define kControlStripObjectCategoryName				"Object Control Strip Category"	// Generally LayoutCSB control strip widgets
#define kControlStripCharacterCategoryName			"Character Control Strip Category"	// Generally TextCSB control strip widgets
#define kControlStripParagraphCategoryName			"Paragraph Control Strip Category"	// Generally TextCSB control strip widgets
#define kControlStripTableCategoryName				"Tables Control Strip Category"	// Generally TableCSB control strip widgets
#define kControlStripSpreadCategoryName				"Spread Control Strip Category" // Spread CSB control strip widgets
#define kControlStripOtherCategoryName				"Other Control Strip Category"	// Generally other control sets, appear at end (e.g. Bridge widget)
#define kControlStripHiddenCategoryName				"Hidden Control Strip Category" // For control sets that shouldn't appear in dynamic Customize menu

// Control set defines for sets InDesign ships with. They are used in several places in the code, so this consolidates them into one place.
//#define kSampleControlStripSet					ControlStripWidgetInfo (RsrcID, \
//														PluginID, \
//														Priority, \
//														"Name", \
//														"Name of menu item that controls this set", \
//														Category, \
//														Associated panel ActionID)

/* Alignment widgets */
#define kAlignControlStripSet						ControlStripWidgetInfo (kAlignControlStripRsrcID, \
														kAlignPanelPluginID, \
														kAlignControlStripPriority, \
														"kAlignControlStripName", \
														"kAlignControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Bullets & Numbering widgets */
#define kBulletsNumberingControlStripSet			ControlStripWidgetInfo (kBNControlStripPanelRsrcID, \
														kBNUIPluginId, \
														kBNControlStripPriority, \
														"kBulletsNumberingControlStripName", \
														"kBulletsNumberingControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Bullets & Numbering widgets, offset version depending on text mode */
#define kBulletsNumberingOffsetControlStripSet		ControlStripWidgetInfo (kBNControlStripPanelRsrcID, \
														kBNUIPluginId, \
														kBNControlStripPriority + kCharParaModeControlStripOffset, \
														"kBulletsNumberingControlStripName", \
														"kBulletsNumberingControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Character attributes widgets */
#define kCharacterAttributesControlStripSet			ControlStripWidgetInfo (kCharPanelAttrButtonsControlStripRsrcID, \
														kCharPanelPluginID, \
														kCharPanelAttrButtonsControlStripPriority, \
														"kCharacterAttributesControlStripName", \
														"kCharacterAttributesControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Character attributes widgets, offset version depending on text mode */
#define kCharacterAttributesOffsetControlStripSet	ControlStripWidgetInfo (kCharPanelAttrButtonsControlStripRsrcID, \
														kCharPanelPluginID, \
														kCharPanelAttrButtonsControlStripPriority + kCharParaModeControlStripOffset, \
														"kCharacterAttributesControlStripName", \
														"kCharacterAttributesControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Fonts widgets */
#define kCharacterFontsControlStripSet				ControlStripWidgetInfo (kCharPanelFontsControlStripRsrcID, \
														kCharPanelPluginID, \
														kFontsControlStripPriority, \
														"kCharacterFontsControlStripName", \
														"kCharacterFontsControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Fonts widgets, offset version depending on text mode */
#define kCharacterFontsOffsetControlStripSet		ControlStripWidgetInfo (kCharPanelFontsControlStripRsrcID, \
														kCharPanelPluginID, \
														kFontsControlStripPriority + kCharParaModeControlStripOffset, \
														"kCharacterFontsControlStripName", \
														"kCharacterFontsControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Kerning widgets */
#define kCharacterKerningControlStripSet			ControlStripWidgetInfo (kCharPanelKerningControlStripRsrcID, \
														kCharPanelPluginID, \
														kCharPanelKerningControlStripPriority, \
														"kCharacterKerningControlStripName", \
														"kCharacterKerningControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Kerning widgets, offset version depending on text mode */
#define kCharacterKerningOffsetControlStripSet		ControlStripWidgetInfo (kCharPanelKerningControlStripRsrcID, \
														kCharPanelPluginID, \
														kCharPanelKerningControlStripPriority + kCharParaModeControlStripOffset, \
														"kCharacterKerningControlStripName", \
														"kCharacterKerningControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Mojikumi widgets */
#define kCharacterMojikumiControlStripSet			ControlStripWidgetInfo (kCharPanelMojikumiControlStripRsrcID, \
														kCharPanelPluginID, \
														kCharPanelMojikumiControlStripPriority, \
														"kCharacterMojikumiControlStripName", \
														"kCharacterMojikumiControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Mojikumi widgets, offset version depending on text mode */
#define kCharacterMojikumiOffsetControlStripSet		ControlStripWidgetInfo (kCharPanelMojikumiControlStripRsrcID, \
														kCharPanelPluginID, \
														kCharPanelMojikumiControlStripPriority + kCharParaModeControlStripOffset, \
														"kCharacterMojikumiControlStripName", \
														"kCharacterMojikumiControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Character scaling widgets */
#define kCharacterScalingControlStripSet			ControlStripWidgetInfo (kCharPanelScalingControlStripRsrcID, \
														kCharPanelPluginID, \
														(LocaleSetting::GetLocale().GetLanguageFS() == kJapaneseLanguageFS) ? kCharPanelScalingJControlStripPriority : kCharPanelScalingControlStripPriority, \
														"kCharacterScalingControlStripName", \
														"kCharacterScalingControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Character scaling widgets, offset version depending on text mode */
#define kCharacterScalingOffsetControlStripSet		ControlStripWidgetInfo (kCharPanelScalingControlStripRsrcID, \
														kCharPanelPluginID, \
														(LocaleSetting::GetLocale().GetLanguageFS() == kJapaneseLanguageFS) ? kCharPanelScalingJControlStripPriority + kCharParaModeControlStripOffset : kCharPanelScalingControlStripPriority + kCharParaModeControlStripOffset, \
														"kCharacterScalingControlStripName", \
														"kCharacterScalingControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Character style widgets */
#define kCharacterStyleControlStripSet				ControlStripWidgetInfo (kCharStyleControlStripRsrcID, \
														kStylePanelPluginID, \
														kCharStyleControlStripPriority, \
														"kCharacterStyleControlStripName", \
														"kCharacterStyleControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Character style widgets, offset version depending on text mode */
#define kCharacterStyleOffsetControlStripSet		ControlStripWidgetInfo (kCharStyleControlStripRsrcID, \
														kStylePanelPluginID, \
														kCharStyleControlStripPriority + kCharParaModeControlStripOffset, \
														"kCharacterStyleControlStripName", \
														"kCharacterStyleControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Cursor position widgets */
#define kCursorPositionControlStripSet				ControlStripWidgetInfo (kFrameAndCursorControlStripRsrcID, \
														kControlStripPluginID, \
														kFrameAndCursorControlStripPriority, \
														"kCursorPositionControlStripName", \
														"kCursorPositionControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Cursor position widgets, offset version depending on text mode */
#define kCursorPositionOffsetControlStripSet		ControlStripWidgetInfo (kFrameAndCursorControlStripRsrcID, \
														kControlStripPluginID, \
														kFrameAndCursorControlStripPriority + kCharParaModeControlStripOffset, \
														"kCursorPositionControlStripName", \
														"kCursorPositionControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Object distribute widgets */
#define kDistributeControlStripSet					ControlStripWidgetInfo (kDistributeControlStripRsrcID, \
														kAlignPanelPluginID, \
														kDistributeControlStripPriority, \
														"kDistributeControlStripName", \
														"kDistributeControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Guide distribute widgets, visibility controlled via kDistributeControlStripSet */
#define kDistributeGuidesControlStripSet			ControlStripWidgetInfo (kDistributeGuidesControlStripRsrcID, \
														kAlignPanelPluginID, \
														kDistributeControlStripPriority, \
														"kDistributeGuidesControlStripName", \
														"kDistributeControlStripName", \
														kControlStripHiddenCategoryName, \
														kControlStripHiddenCategory)

/* Flip/rotate widgets */
#define kFlipRotateControlStripSet					ControlStripWidgetInfo (kFlipRotateControlStripRsrcID, \
														kTransformPanelPluginID, \
														kFlipRotateControlStripPriority, \
														"kFlipRotateControlStripName", \
														"kFlipRotateControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Frame fitting widgets */
#define kFrameFittingObjectControlStripSet			ControlStripWidgetInfo (kFittingControlStripRsrcID, \
														kControlStripPluginID, \
														kFittingControlStripPriority, \
														"kFrameFittingObjectControlStripName", \
														"kFrameFittingObjectControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Frame fitting widgets for text frames */
#define kFrameFittingTextControlStripSet			ControlStripWidgetInfo (kTextFrameFittingControlStripRsrcID, \
														kControlStripPluginID, \
														kTextFrameFittingControlStripPriority, \
														"kFrameFittingTextControlStripName", \
														"kFrameFittingTextControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Layout Adjustment widget  */
#define kLayoutOptionsControlStripSet			ControlStripWidgetInfo (kLayoutOptionsControlStripRsrcID, \
														kControlStripPluginID, \
														kLayoutOptionsControlStripPriority, \
														"kLayoutOptionsControlStripName", \
														"kLayoutOptionsControlStripName", \
														kControlStripSpreadCategoryName, \
														kControlStripSpreadCategory)

/* Frame grid attributes widgets */
#define kFrameGridAttributesControlStripSet				ControlStripWidgetInfo (kFrameGridAttributesControlStripRsrcID, \
														kControlStripPluginID, \
														kFrameGridAttributesControlStripPriority, \
														"kFrameGridAttributesControlStripName", \
														"kFrameGridAttributesControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Frame grid view options widgets */
#define kFrameGridViewOptionsControlStripSet			ControlStripWidgetInfo (kFrameGridViewOptionsControlStripRsrcID, \
														kControlStripPluginID, \
														kFrameGridViewOptionsControlStripPriority, \
														"kFrameGridViewOptionsControlStripName", \
														"kFrameGridViewOptionsControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Frame grid lines and columns widgets */
#define kFrameGridLinesAndColumnsControlStripSet		ControlStripWidgetInfo (kFrameGridLinesAndColumnsControlStripRsrcID, \
														kControlStripPluginID, \
														kFrameGridLinesAndColumnsControlStripPriority, \
														"kFrameGridLinesAndColumnsControlStripName", \
														"kFrameGridLinesAndColumnsControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* J Sets widgets */
#define kKinsokuMojikumiSetsControlStripSet			ControlStripWidgetInfo (kParaPanelJSetsControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelJSetsControlStripPriority, \
														"kKinsokuMojikumiSetsControlStripName", \
														"kKinsokuMojikumiSetsControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* J Sets widgets, offset version depending on text mode */
#define kKinsokuMojikumiSetsOffsetControlStripSet	ControlStripWidgetInfo (kParaPanelJSetsControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelJSetsControlStripPriority + kCharParaModeControlStripOffset, \
														"kKinsokuMojikumiSetsControlStripName", \
														"kKinsokuMojikumiSetsControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Menu widget, never shows up in Customize dialog. */
#define kMenuControlStripSet						ControlStripWidgetInfo (kMenuControlStripRsrcID, \
														kControlStripPluginID, \
														kMenuControlStripPriority, \
														"kMenuControlStripName", \
														"kMenuControlStripName", \
														kControlStripHiddenCategoryName, \
														kControlStripHiddenCategory)

/* Object styles widgets */
#define kObjectStyleControlStripSet					ControlStripWidgetInfo (kObjectStyleControlStripRsrcID, \
														kObjStylesUIPluginID, \
														kObjectStyleControlStripPriority, \
														"kObjectStyleControlStripName", \
														"kObjectStyleControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Corner widgets */
#define kCornerShapeControlStripSet					ControlStripWidgetInfo (kCornerShapeControlStripRsrcID, \
														kGraphicPanelsPluginID, \
														kCornerShapeControlStripPriority, \
														"kCornerShapeControlStripName", \
														"kCornerShapeControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)


/* Paragraph alignment widgets */
#define kParagraphAlignmentControlStripSet			ControlStripWidgetInfo (kParaPanelAlignButtonsControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelAlignButtonsControlStripPriority, \
														"kParagraphAlignmentControlStripName", \
														"kParagraphAlignmentControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph alignment widgets, offset version depending on text mode */
#define kParagraphAlignmentOffsetControlStripSet	ControlStripWidgetInfo (kParaPanelAlignButtonsControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelAlignButtonsControlStripPriority + kCharParaModeControlStripOffset, \
														"kParagraphAlignmentControlStripName", \
														"kParagraphAlignmentControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph indents widgets */
#define kParagraphIndentsControlStripSet			ControlStripWidgetInfo (kParaPanelIndentsControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelIndentsControlStripPriority, \
														"kParagraphIndentsControlStripName", \
														"kParagraphIndentsControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph indents widgets, offset version depending on text mode */
#define kParagraphIndentsOffsetControlStripSet		ControlStripWidgetInfo (kParaPanelIndentsControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelIndentsControlStripPriority + kCharParaModeControlStripOffset, \
														"kParagraphIndentsControlStripName", \
														"kParagraphIndentsControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph spacing widgets */
#define kParagraphSpacingControlStripSet			ControlStripWidgetInfo (kParaPanelSpacingControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelSpacingControlStripPriority, \
														"kParagraphSpacingControlStripName", \
														"kParagraphSpacingControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph spacing widgets, offset version depending on text mode */
#define kParagraphSpacingOffsetControlStripSet		ControlStripWidgetInfo (kParaPanelSpacingControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelSpacingControlStripPriority + kCharParaModeControlStripOffset, \
														"kParagraphSpacingControlStripName", \
														"kParagraphSpacingControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)
/* Paragraph drop cap widgets */
#define kParagraphDropCapControlStripSet           	ControlStripWidgetInfo (kParaPanelDropCapControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelDropCapControlStripPriority, \
														"kParagraphDropCapControlStripName", \
														"kParagraphDropCapControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph drop cap widgets, offset version depending on text mode */
#define kParagraphDropCapOffsetControlStripSet      ControlStripWidgetInfo (kParaPanelDropCapControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelDropCapControlStripPriority + kCharParaModeControlStripOffset, \
														"kParagraphDropCapControlStripName", \
														"kParagraphDropCapControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)
/* Paragraph style widgets */
#define kParagraphStyleControlStripSet				ControlStripWidgetInfo (kParaStyleControlStripRsrcID, \
														kStylePanelPluginID, \
														kParaStyleControlStripPriority, \
														"kParagraphStyleControlStripName", \
														"kParagraphStyleControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph style widgets, offset version depending on text mode */
#define kParagraphStyleOffsetControlStripSet		ControlStripWidgetInfo (kParaStyleControlStripRsrcID, \
														kStylePanelPluginID, \
														kParaStyleControlStripPriority + kCharParaModeControlStripOffset, \
														"kParagraphStyleControlStripName", \
														"kParagraphStyleControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Baseline grid widgets */
#define kBaselineGridControlStripSet				ControlStripWidgetInfo (kBaselineGridControlStripRsrcID, \
														kStylePanelPluginID, \
														kBaselineGridControlStripPriority, \
														"kBaselineGridControlStripName", \
														"kBaselineGridControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Baseline grid widgets, offset version depending on text mode */
#define kBaselineGridOffsetControlStripSet		ControlStripWidgetInfo (kBaselineGridControlStripRsrcID, \
														kStylePanelPluginID, \
														kBaselineGridControlStripPriority + kCharParaModeControlStripOffset, \
														"kBaselineGridControlStripName", \
														"kBaselineGridControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Quick Apply widget */
#define kQuickApplyControlStripSet					ControlStripWidgetInfo (kInvalidRsrcID, \
														kControlStripPluginID, \
														kQuickApplyControlStripPriority, \
														"kQuickApplyControlStripName", \
														"kQuickApplyControlStripName", \
														kControlStripOtherCategoryName, \
														kControlStripOtherCategory)

/* Selection widgets */
#define kSelectContainerContentControlStripSet		ControlStripWidgetInfo (kParentChildControlStripRsrcID, \
														kControlStripPluginID, \
														kParentChildControlStripPriority, \
														"kSelectContainerContentControlStripName", \
														"kSelectContainerContentControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Stroke widgets */
#define kStrokeControlStripSet						ControlStripWidgetInfo (kStrokePanelControlStripRsrcID, \
														kStrokePanelPluginID, \
														kStrokeControlStripPriority, \
														"kStrokeControlStripName", \
														"kStrokeControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Table alignment widgets */
#define kTableCellAlignmentControlStripSet			ControlStripWidgetInfo (kParaPanelTableControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kTablesParaPanelControlStripPriority, \
														"kTableCellAlignmentControlStripName", \
														"kTableCellAlignmentControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table cell options widgets */
#define kTableCellOptionsControlStripSet			ControlStripWidgetInfo (kTablesCellOptionsControlStripRsrcID, \
														kTablesUIPluginID, \
														kTablesCellOptionsControlStripPriority, \
														"kTableCellOptionsControlStripName", \
														"kTableCellOptionsControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table cell insets widgets */
#define kTableInsetsControlStripSet					ControlStripWidgetInfo (kTablesUIInsetsControlStripRsrcID, \
														kTablesUIPluginID, \
														kTablesInsetsControlStripPriority, \
														"kTableInsetsControlStripName", \
														"kTableInsetsControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table merge/unmerge widgets */
#define kTableMergeUnmergeControlStripSet			ControlStripWidgetInfo (kTablesUIMergeUnmergeControlStripRsrcID, \
														kTablesUIPluginID, \
														kTablesMergeUnmergeControlStripPriority, \
														"kTableMergeUnmergeControlStripName", \
														"kTableMergeUnmergeControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table rows/columns widgets */
#define kTableRowsColumnsControlStripSet			ControlStripWidgetInfo (kTablesRowsColumnsControlStripRsrcID, \
														kTablesUIPluginID, \
														kTablesRowsColumnsControlStripPriority, \
														"kTableRowsColumnsControlStripName", \
														"kTableRowsColumnsControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table stroke widgets */
#define kTableStrokeControlStripSet					ControlStripWidgetInfo (kStrokeTablePanelControlStripRsrcID, \
														kStrokePanelPluginID, \
														kTableStrokeControlStripPriority, \
														"kTableStrokeControlStripName", \
														"kTableStrokeControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table vertical alignment widgets */
#define kTableVerticalAlignmentControlStripSet		ControlStripWidgetInfo (kTablesVerticalAlignmentControlStripRsrcID, \
														kTablesUIPluginID, \
														kTablesVerticalAlignmentControlStripPriority, \
														"kTableVerticalAlignmentControlStripName", \
														"kTableVerticalAlignmentControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Table and cell styles widgets */
#define kTableStyleControlStripSet					ControlStripWidgetInfo (kTableStyleControlStripRsrcID, \
														kTabStyUIPluginID, \
														kTableStyleControlStripPriority, \
														"kTableStyleControlStripName", \
														"kTableStyleControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Text frame options widgets */
#define kTextFrameOptionsControlStripSet			ControlStripWidgetInfo (kFrameOptionsControlStripRsrcID, \
														kControlStripPluginID, \
														kFrameOptionsControlStripPriority, \
														"kTextFrameOptionsControlStripName", \
														"kTextFrameOptionsControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Vertical justification widgets */
#define kVerticalJustificationControlStripSet		ControlStripWidgetInfo (kVerticalJustificationControlStripRsrcID, \
														kControlStripPluginID, \
														kVerticalJustificationControlStripPriority, \
														"kVerticalJustificationControlStripName", \
														"kVerticalJustificationControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Balance Columns widgets */
#define kBalanceColumnsControlStripSet		ControlStripWidgetInfo (kBalanceColumnsControlStripRsrcID, \
														kControlStripPluginID, \
														kBalanceColumnsControlStripPriority, \
														"kBalanceColumnsControlStripName", \
														"kBalanceColumnsControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Text mode widget */
#define kTextModeControlStripSet					ControlStripWidgetInfo (kTextModeControlStripRsrcID, \
														kControlStripPluginID, \
														kTextModeControlStripPriority, \
														"kTextModeControlStripName", \
														"kTextModeControlStripName", \
														kControlStripHiddenCategoryName, \
														kControlStripHiddenCategory)

/* Text mode separator widget */
#define kTextModeSeparatorControlStripSet			ControlStripWidgetInfo (kTextModeSeparatorControlStripRsrcID, \
														kControlStripPluginID, \
														kTextModeSeparatorControlStripPriority, \
														"kTextModeSeparatorControlStripName", \
														"kTextModeSeparatorControlStripName", \
														kControlStripHiddenCategoryName, \
														kControlStripHiddenCategory)

/* Transfrom scale/rotation widgets */
#define kTransformScaleRotateControlStripSet		ControlStripWidgetInfo (kTransformPanelScaleRotateControlStripRsrcID, \
														kTransformPanelPluginID, \
														kTransformScaleRotateControlStripPriority, \
														"kTransformScaleRotateControlStripName", \
														"kTransformScaleRotateControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Transform position/dimension widgets */
#define kTransformXYWHControlStripSet				ControlStripWidgetInfo (kTransformPanelXYWHControlStripRsrcID, \
														kTransformPanelPluginID, \
														kTransformXYWHControlStripPriority, \
														"kTransformXYWHControlStripName", \
														"kTransformXYWHControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Spread position/dimension widgets */
#define kPageSizePresetControlStripSet				ControlStripWidgetInfo (kPageSizePresetControlStripRsrcID, \
														kTransformPanelPluginID, \
														kPageSizePresetControlStripPriority, \
														"kTransformPageSizePresetControlStripName", \
														"kTransformPageSizePresetControlStripName", \
														kControlStripSpreadCategoryName, \
														kControlStripSpreadCategory)

/* Spread position/dimension widgets */
#define kPageOrientationControlStripSet				ControlStripWidgetInfo (kPageOrientationControlStripRsrcID, \
														kTransformPanelPluginID, \
														kPageOrientationControlStripPriority, \
														"kTransformOrientationControlStripName", \
														"kTransformOrientationControlStripName", \
														kControlStripSpreadCategoryName, \
														kControlStripSpreadCategory)

/* Transparency widgets */
#define kXPUIControlStripSet						ControlStripWidgetInfo (kXPUIControlStripRsrcID, \
														kXPUIPluginID, \
														kXPUIControlStripPriority, \
														"kXPUIControlStripName", \
														"kXPUIControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Text Wrap widgets */
#define kTextWrapControlStripSet					ControlStripWidgetInfo (kTextWrapControlStripRsrcID, \
														kStandOffPanelPluginID, \
														kTextWrapControlStripPriority, \
														"kTextWrapControlStripName", \
														"kTextWrapControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Fill/Stroke Color widgets */
#define kFillStrokeColorControlStripSet				ControlStripWidgetInfo (kFillStrokeColorPanelControlStripRsrcID, \
														kColorPickerPluginID, \
														kFillStrokeColorControlStripPriority, \
														"kFillStrokeColorControlStripName", \
														"kFillStrokeColorControlStripName", \
														kControlStripObjectCategoryName, \
														kControlStripObjectCategory)

/* Fill/Stroke Color widgets for Text mode */
#define kTextFillStrokeColorControlStripSet				ControlStripWidgetInfo (kTextFillStrokeColorPanelControlStripRsrcID, \
														kColorPickerPluginID, \
														kTextFillStrokeColorControlStripPriority, \
														"kTextFillStrokeColorControlStripName", \
														"kTextFillStrokeColorControlStripName", \
														kControlStripCharacterCategoryName, \
														kControlStripCharacterCategory)

/* Fill/Stroke Color widgets for Tables mode */
#define kTableFillStrokeColorControlStripSet				ControlStripWidgetInfo (kTableFillStrokeColorPanelControlStripRsrcID, \
														kColorPickerPluginID, \
														kTableFillStrokeColorControlStripPriority, \
														"kTableFillStrokeColorControlStripName", \
														"kTableFillStrokeColorControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Frame fitting widgets for table graphic cells */
#define kGraphicCellFrameFittingControlStripSet			ControlStripWidgetInfo (kGraphicCellFittingControlStripRsrcID, \
														kControlStripPluginID, \
														kGraphicCellFrameFittingControlStripPriority, \
														"kGraphicCellFrameFittingControlStripName", \
														"kGraphicCellFrameFittingControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)

/* Transparency widgets for table graphic cells */
#define kGraphicCellXPUIControlStripSet						ControlStripWidgetInfo (kGraphicCellXPUIControlStripRsrcID, \
														kXPUIPluginID, \
														kGraphicCellXPUIControlStripPriority, \
														"kGraphicCellXPUIControlStripName", \
														"kGraphicCellXPUIControlStripName", \
														kControlStripTableCategoryName, \
														kControlStripTableCategory)


/* Align Widgets for Spread mode */
#define kSpreadAlignControlStripSet				ControlStripWidgetInfo (kSpreadAlignControlStripRsrcID, \
														kAlignPanelPluginID, \
														kSpreadAlignControlStripPriority, \
														"kSpreadAlignControlStripName", \
														"kSpreadAlignControlStripName", \
														kControlStripSpreadCategoryName, \
														kControlStripSpreadCategory)


/* Distribute Widgets for Spread mode */
#define kSpreadDistributeControlStripSet				ControlStripWidgetInfo (kSpreadDistributeControlStripRsrcID, \
														kAlignPanelPluginID, \
														kSpreadDistributeControlStripPriority, \
														"kSpreadDistributeControlStripName", \
														"kSpreadDistributeControlStripName", \
														kControlStripSpreadCategoryName, \
														kControlStripSpreadCategory)

/* Paragraph Shading widgets */
#define kParagraphShadingControlStripSet			ControlStripWidgetInfo (kParaBorderShadingControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelShadingControlStripPriority, \
														"kParagraphShadingControlStripName", \
														"kParagraphShadingControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)

/* Paragraph Shading widgets, offset version depending on text mode */
#define kParagraphShadingOffsetControlStripSet		ControlStripWidgetInfo (kParaBorderShadingControlStripRsrcID, \
														kParagraphPanelPluginID, \
														kParaPanelShadingControlStripPriority + kCharParaModeControlStripOffset, \
														"kParagraphShadingControlStripName", \
														"kParagraphShadingControlStripName", \
														kControlStripParagraphCategoryName, \
														kControlStripParagraphCategory)
#endif // __CONTROLSTRIPDEFS__
