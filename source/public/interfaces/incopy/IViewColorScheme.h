//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IViewColorScheme.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IViewColorScheme__
#define __IViewColorScheme__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"


class RealAGMColor;

/** 
	This interface is used as a place to store view specific color data for a story or galley view.
	They are also used to pass data to the GalleySettingsCommands for control of display background
	and text colors. The implementations of these on the kWritingModePanelBoss are kept in sync
	with IGalleySettings cooresponding to colors.
*/
class IViewColorScheme : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IVIEWCOLORSCHEME };
	
	/**
		Set the color to use as the text color
		@param color - RGB value defining color to display text as
		@return none.
	**/
	virtual void SetTextColor(const RealAGMColor &color) = 0;
	
	/**
		Get the current text color
		@return RGB value of defining the color of the text for story/galley views.
	**/
	virtual const RealAGMColor &GetTextColor() = 0;
	
	/**
		Set the color to use as the view background color
		@param color - RGB value defining color for view background
		@return none.
	**/
	virtual void SetBackGroundColor(const RealAGMColor &color) = 0;
	
	/**
		Get the view background color
		@return RGB value defining color for view background.
	**/
	virtual const RealAGMColor &GetBackGroundColor() = 0;

	/**
		Blend text color with background color at a given opacity give back combined color
		@param opacity - how transparent 0.0 to 1.0
		@param textOnBackground - drawing text on background color kTrue, background color on text color kFalse.
		@return RGB value for blended color.
	**/
	virtual const RealAGMColor &GetBlendedColor(const PMReal& opacity, bool16 textOnBackground = kTrue) = 0;

	/**
		Blend two arbitrary colors (foreColor on backColor) at a given opacity
		@param foreColor - color to combine with backColor
		@param backColor - color to combine with foreColor
		@param opacity - how transparent 0.0 to 1.0
		@return RGB value for blended color.
	**/
	virtual const RealAGMColor &GetBlendedColor(const RealAGMColor& foreColor, const RealAGMColor& backColor, const PMReal& opacity) = 0;
};

#endif 		// __IViewColorScheme__