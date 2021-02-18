//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/ui/SplitterPanelDefs.h $
//  
//  Owner: lance bushore
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
#ifndef __SPLITTERPANELDEFS__
#define __SPLITTERPANELDEFS__

	#define kFirstWidgetIsTop					0
	#define kFirstWidgetIsLeft					0
	#define kFirstWidgetIsBottom				1
	#define kFirstWidgetIsRight					1
	

	#define kSnapSlider							kTrue
	#define kDontSnapSlider						kFalse
	#define kInvalidSplitterPosition			-1
	#define kHorizontalSplitter					kFalse
	#define kVerticalSplitter					kTrue
		
	#define kProportionalSplitterResize			-1	 // OR WidgetID of widget to lock, all scaleing happens to other widget.

	#define kSingleClickDoNothing				0 
	#define kSingleClickSnapUp					1
	#define kSingleClickSnapDown				2
	#define kSingleClickSnapBackInitPos			4	
	#define	kDrawXORSplitter					kTrue
	#define kDrawPallets						kFalse
#endif
