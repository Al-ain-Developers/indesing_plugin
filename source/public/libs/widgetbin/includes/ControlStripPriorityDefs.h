//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/ControlStripPriorityDefs.h $
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
#ifndef __CONTROLSTRIPPRIORITYDEFS__
#define __CONTROLSTRIPPRIORITYDEFS__

// Priorities

// Enabled for all CSBs
const PMReal kMenuControlStripPriority =	1000000.0;			// Last widget on the right for all CSBs.
const PMReal kQuickApplyControlStripPriority = 999998.0;		// Last widget on the right. Either menu set or menu/quick apply combo set is shown at the end.

// Layout CSB
const PMReal kTransformXYWHControlStripPriority = 1000.0;
const PMReal kTransformScaleRotateControlStripPriority = 1100.0;
const PMReal kFlipRotateControlStripPriority = 1200.0;
const PMReal kParentChildControlStripPriority = 1300.0;
const PMReal kFrameGridAttributesControlStripPriority = 1500.0;
const PMReal kFrameGridViewOptionsControlStripPriority = 1600.0;
const PMReal kFrameGridLinesAndColumnsControlStripPriority = 1700.0;
const PMReal kFillStrokeColorControlStripPriority = 1800.0;
const PMReal kStrokeControlStripPriority = 2000.0;
const PMReal kXPUIControlStripPriority = 2050.0;
const PMReal kTextWrapControlStripPriority = 2075.0;
const PMReal kCornerShapeControlStripPriority = 2200.0;
const PMReal kFittingControlStripPriority = 3000.0;
const PMReal kFrameOptionsControlStripPriority = 4000.0;
const PMReal kBalanceColumnsControlStripPriority = 4050.0;
const PMReal kVerticalJustificationControlStripPriority = 4100.0;
const PMReal kTextFrameFittingControlStripPriority = 4500.0;
const PMReal kAlignControlStripPriority = 5000.0;
const PMReal kDistributeControlStripPriority = 5200.0;
const PMReal kObjectStyleControlStripPriority = 5300.0;


// Text CSB
const PMReal kTextModeControlStripPriority = 500.0;	// First widget on left
const PMReal kFontsControlStripPriority = 1000.0;
const PMReal kCharPanelAttrButtonsControlStripPriority = 1500.0;
const PMReal kCharPanelScalingJControlStripPriority = 2000.0;
const PMReal kCharPanelKerningControlStripPriority = 3000.0;
const PMReal kCharPanelScalingControlStripPriority = 4000.0;
const PMReal kCharPanelMojikumiControlStripPriority = 5000.0;
const PMReal kParaPanelAlignButtonsControlStripPriority = 6000.0;
const PMReal kParaPanelIndentsControlStripPriority = 7000.0;
const PMReal kParaPanelSpacingControlStripPriority = 8000.0;
const PMReal kParaPanelDropCapControlStripPriority = 8500.0;
const PMReal kBNControlStripPriority = 9000.0;
const PMReal kParaPanelJSetsControlStripPriority = 10000.0;
const PMReal kTextFillStrokeColorControlStripPriority = 11000.0;
const PMReal kParaPanelShadingControlStripPriority = 11500.0;
const PMReal kParaStyleControlStripPriority = 12000.0;
const PMReal kCharStyleControlStripPriority = 12000.0;
const PMReal kBaselineGridControlStripPriority = 12500.0;
const PMReal kFrameAndCursorControlStripPriority = 13000.0;

const PMReal kTextModeSeparatorControlStripPriority = 19999.0;	// Must be less than offset value below
const PMReal kCharParaModeControlStripOffset = 20000.0;	// Offset added to character or paragraph priorities so both sets of controls will fit.

// Tables CSB
const PMReal kTablesParaPanelControlStripPriority = 1500.0;
const PMReal kTablesVerticalAlignmentControlStripPriority	= 2000.0;
const PMReal kGraphicCellFrameFittingControlStripPriority = 2200.0;
const PMReal kGraphicCellXPUIControlStripPriority = 2400.0;
const PMReal kTablesRowsColumnsControlStripPriority	= 2500.0;
const PMReal kTablesMergeUnmergeControlStripPriority = 3000.0;
const PMReal kTableFillStrokeColorControlStripPriority = 3250.0;
const PMReal kTableStrokeControlStripPriority = 3500.0;
const PMReal kTableStyleControlStripPriority = 4000.0;
const PMReal kTablesCellOptionsControlStripPriority	= 4500.0;
const PMReal kTablesInsetsControlStripPriority	= 5500.0;

// Spread CSB
//const PMReal kTransformXYWHControlStripPriority = 1000.0;
const PMReal kPageSizePresetControlStripPriority = 1100.0;
const PMReal kPageOrientationControlStripPriority = 1200.0;
const PMReal kLayoutOptionsControlStripPriority = 1300.0;
const PMReal kSpreadAlignControlStripPriority = 1400.0;
const PMReal kSpreadDistributeControlStripPriority = 1500.0;

#endif // __CONTROLSTRIPPRIORITYDEFS__
