//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/IconStyleDefs.h $
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
#ifndef __IconStyleDefs_h__
#define __IconStyleDefs_h__

const PMReal kPopoutCellHeight			=	22;		// Height of tool flyout
const PMReal kSelectionProxyWidth		=	16;		// Width of selection proxy for current tool on tool flyout

const int32 kIconCentering				=	0x00;	// Use to center the icon within its frame (default).
const int32 kIconNoCentering			=	0x01;	// Use to draw the icon as is within its frame
const int32 kIconHorizontalCentering	=	0x02;	// Use to draw the icon horizontally centered in its frame
const int32 kIconVerticalCentering		=	0x04;	// Use to draw the icon vertically centered in its frame

const int32 kIconRaisedLook				=	0x00;	// Use to draw icon with raised look
const int32 kIconFlushLook				=	0x01;	// Use to draw icon with flush look
const int32 kIconBorderedLook			=	0x02;	// Use to draw icon with a border look (can be bit or'd with other look flags)
const int32 kIconWellLook				=	0x04;	// Use to draw icon with a bevel well look (can be bit or'd with other look flags)

// // WidgetID, RsrcID used by the tree control Icon.
#define  kNoWidgetResource					0,0
#define  kNoAssociatedWidgetShortcutControl 0

#define kADBEIconSuiteButtonType							kIconCentering,	kIconRaisedLook, kFalse
#define kADBEIconSuiteButtonDrawWellType					kIconCentering,	(kIconRaisedLook | kIconWellLook), kTrue
#define kADBEIconSuiteButtonBorderedType					kIconCentering,	(kIconRaisedLook | kIconBorderedLook), kFalse
#define kStyledIconSuiteFlushedButtonType 					kIconCentering,	kIconFlushLook,  kFalse
#define kADBEIconSuiteButtonNoCenteringType					kIconNoCentering, kIconRaisedLook, kFalse
#define kStyledIconHorizontalCenteringButtonFlushedType 	kIconHorizontalCentering, kIconFlushLook, kFalse

/*

	#define kADBEIconSuiteFlushButtonType	kADBEIconSuiteButtonView,	kIconCentering,	kIconFlushLook,		kNoWidgetResource,	kNoAssociatedWidgetShortcutControl //in AlignPanel
#define kIconSuiteButtonType			kIconSuiteButtonView,		kIconCentering,	kIconRaisedLook,	kNoWidgetResource,	kNoAssociatedWidgetShortcutControl //in AppUI
#define kADBEIconSuiteRaisedButtonType  kADBEIconSuiteButtonView,	kIconCentering,	kIconRaisedLook,	kNoWidgetResource,	kNoAssociatedWidgetShortcutControl //in BenchmarkPanel
#define kDestinationIconType			kDestinationIconView,		kIconCentering,	kIconFlushLook,		kNoWidgetResource,	kNoAssociatedWidgetShortcutControl //in BenchmarkPanel
#define kIconButtonType					kIconButtonView,			kIconCentering,	kIconRaisedLook,	kNoWidgetResource,	kNoAssociatedWidgetShortcutControl //in Hyper Link,
//#define kDestinationIconType			kADBEIconSuiteRaisedButtonType //in Hyper Link,
*/

#endif // __IconStyleDefs_h__
