//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/StdHeightWidthConstants.h $
//  
//  Owner: Sanyam
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __StdHeightWidth__
#define __StdHeightWidth__


// Standard constants defining the typical width and height for different type of UI controls used in InDesign.

//gaps
const uint32 kCC2016NudgeEditBoxGap = 0;																			// Gap between nudge control and edit box
const uint32 kCC2016CheckBoxTextGap = 19;																			// Gap between checkbox and associated text
const uint16 kCC2016StandardGapBetweenWidgets = 5;																			// Standard gap between any two controls

// Height constants
const uint32 kCC2016StandardWidgetHeight								= 21;																			// Standard height of any widget
const uint32 kCC2016NudgeControlHeight									= kCC2016StandardWidgetHeight;											// Standard height for nudge control associated with edit box
const uint32 kCC2016StandardButtonHeight								= 26;																			// Standard height of any button widget
const uint32 kCC2016StdWidgetHeightNoApplyEve_Dialog					= kCC2016StandardWidgetHeight;													// MANISH TO ADD COMMENT HERE
const uint32 kCC2016ControlStripIconHeight								= 26;																			// Standard height of control strip icons
const uint32 kCC2016PanelIconHeight										= 24;																			// Standard height of panel icons
const uint32 kCC2016PanelTreeNodeHeight									= (kCC2016StandardWidgetHeight + 1);											// Standard height of tree node
const uint32 kCC2016PanelTreeNodeContentHeight							= (kCC2016PanelTreeNodeHeight - 1);												// Standard height of tree node's content
const uint32 kCC2016PanelTreeNodeSmallRowHeight							= 16;																			// Standard height of smaller tree node
const uint32 kCC2016PanelTreeNodeContentSmallRowHeight					= (kCC2016PanelTreeNodeSmallRowHeight - 1);										// Standard height of smaller tree node's content
const uint32 kCC2016PanelTreeNodeWithThumbnailHeight					= (40);																			// Standard height of tree node with thumbnail
const uint32 kCC2016PanelTreeNodeWithThumbnailContentHeight				= (kCC2016PanelTreeNodeWithThumbnailHeight - 1);								// Standard height of tree node's content with thumbnail
const uint32 kCC2016PanelTreeNodeWithLargeThumbnailHeight				= (50);																			// Standard height of tree node with large thumbnail
const uint32 kCC2016PanelTreeNodeWithLargeThumbnailContentHeight		= (kCC2016PanelTreeNodeWithLargeThumbnailHeight - 1);							// Standard height of tree node's content with large thumbnail
const uint32 kCC2016PanelTreeNodeWithExtraLargeThumbnailHeight			= (60);																			// Standard height of tree node with extra large thumbnail
const uint32 kCC2016PanelTreeNodeWithExtraLargeThumbnailContentHeight	= (kCC2016PanelTreeNodeWithExtraLargeThumbnailHeight - 1);						// Standard height of tree node's content with extra large thumbnail
const uint32 kCC2016PanelTreeNodeWithControlsHeight						= (kCC2016PanelTreeNodeHeight + 2 * kCC2016StandardGapBetweenWidgets);
const uint32 kCC2016PanelStandardTreeWidgetHeight						= (5*kCC2016PanelTreeNodeHeight);												// Standard height of tree widget with 6 tree nodes
const uint32 kCC2016PanelWithTreeWidgetAndHeaderFooterHeight			= (kCC2016PanelStandardTreeWidgetHeight + 2 * kCC2016PanelIconHeight);			// Standard height of panel with tree widget and header/footer
const uint32 kCC2016PanelWithTreeWidgetAndFooterHeight					= (kCC2016PanelStandardTreeWidgetHeight + kCC2016PanelIconHeight);				// Standard height of panel with tree widget and footer
const uint32 kCC2016PanelWithTreeWidgetAndHeaderHeight					= (kCC2016PanelStandardTreeWidgetHeight + kCC2016PanelIconHeight);				// Standard height of panel with tree widget and header
const uint32 kCC2016InCopyControlStripHeight							= 33;																			// Standard height of Incopy Control Strip
const uint32 kCC2016ProgressBarHeight									= 15;
const uint32 kCC2016TreeNodeTitleRowHeight								= 24;

// Width constants
const uint32 kCC2016StandardWidgetWidth									= 100;																			// Standard width of any widget
const uint32 kCC2016DropDownListWidth									= 95;																			// Standard width of drop down list 
const uint32 kCC2016NudgeControlWidth									= 17;																			// Standard width of nudge control
const uint32 kCC2016SeparatorDefaultWidth								= 1;																			// Standard width of separator
const uint32 kCC2016ControlStripIconWidth								= 26;																			// Standard width of control strip icon
const uint32 kCC2016PanelIconWidth										= 28;																			// Standard width of panel's icon
const uint32 kCC2016PanelPushIconWidth									= 24;																			// Standard width of panel's pushable icon
const uint32 kCC2016PanelStandardWidth									= 240;																			// Standard width of panels
const uint16 kCC2016PanelBottomResizeWidgetWidth						= 15;																			// Standard width of resize widget in panels
const uint16 kCC2016ResizablePanelBottomBottomBarWidth					= (kCC2016PanelStandardWidth - kCC2016PanelBottomResizeWidgetWidth);			// Standard width for resizable panel's bottom bar 
const uint16 kCC2016InlineEditBoxMinimumWidth							= 120;
const uint32 kCC2016ProgressBarWidth									= 310;

// Owner drawn drop down constants.
const uint16 kCC2016ColorGroupAdjustment								= 14.0;																			// MANISH TO ADD COMMENT HERE
const uint16 kCC2016OwnerDDItemLeftMargin								= 4.0;																			// MANISH TO ADD COMMENT HERE
const uint16 kCC2016OwnerDDIconTextGap									= 4.0;																			// MANISH TO ADD COMMENT HERE

const uint16 kCC2016OwnerDrawDDItemMinWidth								= 220.0;																		// MANISH TO ADD COMMENT HERE
const uint16 kCC2016OwnerDrawDDItemMaxWidth								= 320.0;																		// MANISH TO ADD COMMENT HERE
const uint16 kCC2016OwnerDrawDDItemMinHeight							= 21.0;																			// MANISH TO ADD COMMENT HERE


const double kCC2017SpectrumSliderThumbWidth							= 12.0;
const double kCC2017SpectrumColorThumbHeight							= 9.0;

const double kCC2017SpectrumPopupSliderComboBoxWidth					= 123.0;
const double kCC2017SpectrumPopupSliderComboBoxHeight					= 29.0;

const double kCC2017SpectrumPopupSliderComboBoxThumbWidth				= 13.5;
const double kCC2017SpectrumPopupSliderComboBoxThumbHeight				= 13.5;

//Below are the constants used for the border info.
const int16 kLeftBorder = 1 << 0;
const int16 kRightBorder = 1 << 1;
const int16 kTopBorder = 1 << 2;
const int16 kBottomBorder = 1 << 3;
const int16 kAllBorder = kLeftBorder | kRightBorder | kTopBorder | kBottomBorder;
const int16 kInvalidBorderInfo = kAllBorder + 1;

const int16 kCC2017SpectrumCornerRadius = 2;
const int16 kCC2017SpectrumScrollBarWidth = 13;


//Resizing gripper icon size for resizable dialogs
#define kResizingGripperIconSize	15

#endif
