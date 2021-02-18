//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DrawStringUtils.h $
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
//========================================================================================

#pragma once
#ifndef __DRAWSTRINGUTILS__
#define __DRAWSTRINGUTILS__
							  
#include "IPMUnknown.h"
#include "PMString.h"
#include "IInterfaceColors.h"
#include "InterfaceFontInfo.h"
#include "WidgetDefs.h"
#include <string>

#include "DVAForwardDeclarations.h"
#include "DVPublicUtilities.h"

class IGraphicsContext;

#pragma export on

namespace StringUtils
{
	/** Draw the string on screen
		@param gc the Graphics context to use to draw.
		@param textBBox the bbox to draw into
		@param alignment the alignment to use when drawing the text. One of kAlignLeft,kAlignRight,kAlignCenter
		@param str the string to draw. It will be translated before drawing to screen.
		@param fontInfo the font to use when drawing the string
		@param color the color to use when drawing the string
		@param convertAmpersandToUnderline true if you want to convert a '&' character in the string to be an underline of the next char. False to draw the '&' char.			
		@param underlineText true if you want to underline the text			
	*/
	DV_WIDGET_DECL void PMDrawString(IGraphicsContext* gc, const PMRect& textBBox, int16 alignment, const PMString& str, const InterfaceFontInfo& fontInfo,
						  IInterfaceColors::InterfaceColor color = kInterfaceTextColor, bool16 convertAmpersandToUnderline = kFalse, bool16 centerVertically = kTrue, bool16 underlineText = kFalse);

	/** Draw the string on screen
		@param gc the Graphics context to use to draw.
		@param startPt where to start drawing the text.
		@param str the string to draw. It will be translated before drawing to screen.
		@param fontInfo the font to use when drawing the string
		@param color the color to use when drawing the string
		@param convertAmpersandToUnderline true if you want to convert a '&' character in the string to be an underline of the next char. False to draw the '&' char.			
		@param underlineText true if you want to underline the text			
	*/
	DV_WIDGET_DECL void PMDrawString(IGraphicsContext* gc, const PMPoint& startPt, const PMString& str, const InterfaceFontInfo& fontInfo,
						  IInterfaceColors::InterfaceColor color = kInterfaceTextColor, bool16 convertAmpersandToUnderline = kFalse, bool16 underlineText = kFalse);
	
	/** Draw the string on screen
		@param gc the Graphics context to use to draw.
		@param textBBox the bbox to draw into
		@param alignment the alignment to use when drawing the text. One of kAlignLeft,kAlignRight,kAlignCenter
		@param str the string to draw. It will be translated before drawing to screen.
		@param fontInfo the font to use when drawing the string
		@param rgbColor the color to use when drawing the string
		@param convertAmpersandToUnderline true if you want to convert a '&' character in the string to be an underline of the next char. False to draw the '&' char.			
		@param underlineText true if you want to underline the text			
	*/
	DV_WIDGET_DECL void PMDrawStringRGB (IGraphicsContext* gc, const PMRect& textBBox, int16 alignment, const PMString& str,
										 const InterfaceFontInfo& fontInfo, const RealAGMColor & rgbColor, bool16 convertAmpersandToUnderline = kFalse, bool16 centerVertically = kTrue, bool16 underlineText = kFalse, dv_utils::AntiAliasPolicy aa_policy = dv_utils::kAntiAliasPolicy_Med);
	DV_WIDGET_DECL void PMDrawStringRGB (IGraphicsContext* gc, const PMPoint& startPt, const PMString& str,
						  const InterfaceFontInfo& fontInfo, const RealAGMColor & rgbColor, bool16 convertAmpersandToUnderline = kFalse, bool16 underlineText = kFalse, dv_utils::AntiAliasPolicy aa_policy = dv_utils::kAntiAliasPolicy_Med);

	DV_WIDGET_DECL void PostTransformPMDrawStringRGB (IGraphicsContext* gc, const PMRect& textBBox, int16 alignment, const PMString& str,
					  const InterfaceFontInfo& fontInfo, const RealAGMColor & rgbColor, bool16 convertAmpersandToUnderline = kFalse, bool16 centerVertically = kFalse, bool16 underlineText = kFalse);

	DV_WIDGET_DECL PMPoint PMMeasureString(IGraphicsContext* gc, const PMString& str, const InterfaceFontInfo& fontInfo,
						  bool16 convertAmpersandToUnderline = kTrue);
	DV_WIDGET_DECL PMPoint PMMeasureString(const PMString& str, const InterfaceFontInfo& fontInfo,
						  bool16 convertAmpersandToUnderline = kTrue);

	DV_WIDGET_DECL PMString PMEllipsizeString(IGraphicsContext* gc, PMReal width, const PMString& str, const InterfaceFontInfo& fontInfo,
						  bool16* didTruncate = nil, bool16 convertAmpersandToUnderline = kTrue);
	DV_WIDGET_DECL PMString PMEllipsizeString(IGraphicsContext* gc, PMReal width, const PMString& str, const InterfaceFontInfo& fontInfo, 
						  EllipsizeStyle truncateWhere, bool16* didTruncate = nil, bool16 convertAmpersandToUnderline = kTrue);
	DV_WIDGET_DECL PMString PMEllipsizeString(PMReal width, const PMString& str, const InterfaceFontInfo& fontInfo,	EllipsizeStyle truncateWhere, 
						  bool16* didTruncate, bool16 convertAmpersand  = kTrue);
	
	//========================================================================================
	// PMDrawStringRGB
	//
	// Drawbot based utility function to draw the text at the specified draw point using specified
	// color and font information. Also draws underline if specified.
	//========================================================================================
	DV_WIDGET_DECL void PMDrawStringRGB (
		dvaui::drawbot::Drawbot*	pDrawbot,
		const PMPoint &				drawPt,
		int16						alignment, 
		const PMString &			str,
		const InterfaceFontInfo &	fontInfo, 
		const RealAGMColor &		realColor,
		bool16						convertAmpersandToUnderline,
		bool16						drawUnderline, 
		dv_utils::AntiAliasPolicy aa_policy = dv_utils::kAntiAliasPolicy_Med);

	DV_WIDGET_DECL void PMDrawStringRGB (
		dvaui::drawbot::Drawbot*	pDrawbot,
		const PMRect&				textBBox,
		int16						alignment, 
		const PMString &			str,
		const InterfaceFontInfo &	fontInfo, 
		const RealAGMColor &		realColor,
		bool16						convertAmpersandToUnderline,
		bool16						centerVertically,
		bool16						underlineText,
		dv_utils::AntiAliasPolicy	aa_policy = dv_utils::kAntiAliasPolicy_Med);
	
	//========================================================================================
	// PMMeasureStringDroverized
	//
	// Drawbot based utility function to obtain text dimension based on specified font info.
	//========================================================================================
	DV_WIDGET_DECL PMPoint PMMeasureStringDroverized(
		const PMString &			str,
		const InterfaceFontInfo &	fontInfo,
		bool16						convertAmpersandToUnderline);
}	

#pragma export off

#endif
