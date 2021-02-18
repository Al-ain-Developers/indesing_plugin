//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterfaceColorDefines.h $
//  
//  Owner: brendan o'shea
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
//  Note: This file is included in .fr files, so don't add any C/C++ structures.
//  
//========================================================================================

#pragma once
#ifndef __InterfaceColorDefines__
#define __InterfaceColorDefines__

// NOTE: These enums represent the "standard" set of Adobe Interface 
//       Colors which are common to all Adobe Applications.  See Adobe 
//       UI guidelines for description of this index table.

// CAREFUL: while adding a new color constant, 
//	- keep the enum UI_Color also in sync in IDThemeColors.h
//  - add the new color resource in InterfaceColorTable.fr
//	- add the theme color in ColorTheme.xml file

const int32	  kInvalidInterfaceColor	=	-1;
const int32	  kInterfaceWhite			=	0;	// also known as kADMWhiteColor
const int32	  kInterfaceButtonUpFill	=	1;	// aka kADMButtonUpColor
const int32	  kInterfaceBevelShadow		=	2;	// aka kADMShadowColor	
const int32	  kInterfacePaletteFill		=	3;	// aka kADMBackgroundColor
const int32	  kInterfaceIconFrameDimmed	=	4;		
const int32	  kInterfaceIconFrameActive	=	5;	
const int32	  kInterfaceBevelHighlight	=	6;	
const int32	  kInterfaceButtonDownFill	=	7;	// aka kADMButtonDownColor
const int32	  kInterfaceIconFillSelected =	8;	
const int32	  kInterfaceBorder			=	9;		
const int32	  kInterfaceButtonDarkShadow =	10;	// aka kADMButtonDownShadowColor
const int32	  kInterfaceIconFrameSelected =	11;		
const int32	  kInterfaceBlack			=	12;	// aka kADMBlackColor

// NOTE: Add any custom K2 color enumerations below here:
const int32	  kInterfaceTooltipText		=	13;	// aka kADMToolTipForegroundColor
const int32	  kInterfaceTooltipBackground =	14;	// aka kADMToolTipBackgroundColor
const int32	  kInterfaceDisabledGray	=	15;	
const int32	  kInterfaceHighLight		=	16;	// aka kADMHiliteColor
const int32	  kInterfaceHighLightText	=	17;	// aka kADMHiliteTextColor
const int32   kInterfaceCntlMgrTabsPane	=	18;	
const int32	  kInterfaceAboutBoxGrayText=	19;	
const int32	  kInterfaceMenuHighLight	=	20;	// aka kADMMenuHiliteColor??
const int32   kInterfaceBlueProgressBack=   21;

// 100% Gray is WHITE, and 0% Gray is BLACK
const int32   kInterface96Gray			=   22; // 96% Gray
const int32   kInterface92Gray			=   23; // 92% Gray
const int32   kInterface88Gray			=   24; // 88% Gray
const int32   kInterface84Gray			=   25; // 84% Gray
const int32   kInterface80Gray			=   26; // 80% Gray
const int32   kInterface76Gray			=   27; // 76% Gray
const int32   kInterface72Gray			=   28; // 72% Gray
const int32   kInterface68Gray			=   29; // 68% Gray
const int32   kInterface64Gray			=   30; // 64% Gray
const int32   kInterface60Gray			=   31; // 60% Gray
const int32   kInterface56Gray			=   32; // 56% Gray
const int32   kInterface52Gray			=   33; // 52% Gray
const int32   kInterfaceGray			=   34; // 50% Gray
const int32   kInterface48Gray			=   35; // 48% Gray
const int32   kInterface44Gray			=   36; // 44% Gray
const int32   kInterface40Gray			=   37; // 40% Gray
const int32   kInterface36Gray			=   38; // 36% Gray
const int32   kInterface32Gray			=   39; // 32% Gray
const int32   kInterface28Gray			=   40; // 28% Gray			// 26.7% gray variant is mentioned below with the name kInterface26Dot7Gray
const int32   kInterface24Gray			=   41; // 24% Gray
const int32   kInterface20Gray			=   42; // 20% Gray
const int32   kInterface16Gray			=   43; // 16% Gray
const int32   kInterface12Gray			=   44; // 12% Gray
const int32   kInterface08Gray			=   45; // 08% Gray
const int32   kInterface04Gray			=   46; // 04% Gray

const int32   kInterfaceBrightnessAwareVeryLightGray	=   47;
const int32   kInterfaceBrightnessAwareLightGray		=   48;
const int32   kInterfaceBrightnessAwareMediumLightGray	=   49;
const int32   kInterfaceBrightnessAwareMediumDarkGray	=   50;
const int32   kInterfaceBrightnessAwareDarkGray			=   51;
const int32   kInterfaceBrightnessAwareVeryDarkGray		=   52;
const int32   kInterfaceBrightnessAwareWhite			=   53; // White color in Light UI, Black color in Dark UI
const int32   kInterfaceBrightnessAwareBlack			=   54; // Black color in Light UI, White color in Dark UI

const int32   kInterfaceTextColor						=	55; // Black in bright, 0.8 gray in dark (used for text Drawing)
const int32   kInterfaceLightFillColor					=	56; // White in bright, light gray in dark (used in glyph panel)
const int32	  kInterfacePanelBorderColor				=	57;	// Same as group panel border colors in drover
const int32   kInterfaceSeparatorColor					=   58; // Used in tree node separators and header separators in multicolum lists.
const int32   kInterfaceDarkFillColor					=   59; // Used in slider fill.
const int32   kInterfaceTextEditNormalBackground		=   60; // This is the same color drover uses to fill edit text boxes background.
const int32   kInterfaceItemHighLight					=   61; // Similar to kInterfaceHighLight in Light UI, and Orange color in Dark UI
const int32   kInterfaceLightHighLight					=   62; // Similar to kInterfaceHighLight in Light UI, and slightly light in Dark UI
const int32   kInterfaceUnselectedTabColor				=   63;
const int32   kInterfaceBrightnessAwareHyperlinkColor	=   64;
const int32   kInterfaceBlueSeparatorColor				=	65;
const int32   kInterface26Dot7Gray						=	66; // 26.7% gray

// Touch Color
const int32   kTouchPanelBorderColor					= 67;
const int32   kTouchTabTitleRectFillColor				= 68;
const int32   kTouchSliderThumbKnobStartGradient		= 69;
const int32   kTouchSliderThumbKnobEndGradient			= 70;
const int32   kTouchSliderThumbInnerKnobStartGradient	= 71;
const int32   kTouchSliderThumbInnerKnobEndGradient		= 72;
const int32   kInterface94Gray							= 73;
const int32   kInterfaceStructureFixHLColor				= 74;
const int32	  kInterfaceFontDropDownBorderColor			= 75;
const int32	  kInterfaceVFBOnboardingBlue				= 76;
const int32	  kInterfaceFilterHoverColor				= 77;
const int32	  kInterfaceFilterCheckedColor				= 78;
const int32   kInterfaceButtonHoverBackgroundColor      = 79;
const int32   kInterfaceButtonHoverTextColor            = 80;
const int32   kInterfaceButtonDisabledBackgroundColor   = 81;
const int32   kInterfaceButtonDisabledTextColor         = 82;
const int32   kInterfaceAdaptiveLayoutHighlightColor    = 83;




//#######################################################################
/*#####*/		const int32   kInterfaceColorCount		=   84;   //#####  this is needed for counting purpose, always set as last value
//#######################################################################

#endif
