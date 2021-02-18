//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WidgetDefs.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __WidgetDefs_h__
#define __WidgetDefs_h__

#include "IconRsrcDefs.h"

// ----- StaticTextWidget -----

#define kAlignLeft 		5  // don't use 0,1,2 so we can catch conflicts with bools more easily
#define kAlignCenter 	6
#define kAlignRight 	7

// standard control sizes
#define kStdPaletteControlHeight 	17
#define kStdDialogControlHeight 	20

#define kStdPushButtonWidth 		80

// name length - UI limit on named items (like style, layer, swatch names, etc)
#define	kPMNamedItemMaxChars	100

// ----- Resource IDs -----
#define kOwnerDrawDDListMDef				19998

#define kWidgetActionResID					1000
#define kProgressBarDialogRsrcID			550
#define kProgressBar2DialogRsrcID			650
#define kWidgetStringsRsrcID  				500
#define kWidgetStringsNoTransRsrcID			600
#define kControlSetDialogRsrcID				800
#define kControlSetDlgElementRsrcID			9900
#define kWarningWithDontShowDialogRsrcID	1100
#define kWarningWithDontShowCancelDialogRsrcID	1200
#define kAlertWithApplyAllDialogRsrcID				1300
#define kEffectsDlgTreePanelWidgetRsrcID	1400
#define kWarningWithCancelDialogRsrcID	1150

#define kIconNew							kNewObjectButtonIcon
#define kIconDelete							kDeleteObjectButtonIcon
#define kIconCloudExport					kMigrateToCreativeCloudIcon
#define kIconCloudExportMedium				kMigrateToCreativeCloudMediumIcon

#define kIconArrowUp						kArrowUpButtonIcon
#define kIconArrowDown						kArrowDownButtonIcon

#define kCustomizeButtonIconId		kCustomizeIcon, kApplicationPluginID  // from the app

enum EllipsizeStyle 
{	
	kDontEllipsize = 9,	 // don't use 0,1,2,3 so we can catch conflicts with bools more easily
	kEllipsizeEnd = 10, 
	kEllipsizeBeginning = 11,
	kEllipsizeMiddle = 12	
};

enum InLineEditWidgetType 
{	
	kEditbox = 13,
	kDropdown = 14, 
	kCombobox = 15,
	kSliderWidget = 16
};

enum PageNameStyle
{
	kAlternateLayoutNames = 2,	// don't use 0,1,2,3 so we can catch conflicts with bools more easily
	kSectionNames = 3,
	kAlternateAndSectionNames = 4
};

#endif
