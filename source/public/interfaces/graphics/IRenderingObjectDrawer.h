//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRenderingObjectDrawer.h $
//  
//  Owner: SusanCL
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
#ifndef __IRenderingObjectDrawer__
#define __IRenderingObjectDrawer__

#include "IPMUnknown.h"
#include "ColorSystemID.h"
#include "InterfaceFontInfo.h"

class PMRect;
class IGraphicsPort;
class IViewPort;
class IControlView;
class IGraphicsContext;

/**	A reqruied interface for all InDesign rendering objects. All rendering objects are
	represented by swatches.
	@See ISwatchList
*/
class IRenderingObjectDrawer : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRENDERINGOBJECTDRAWER };

		/**	Draw this rendering object UI.
			@param viewPort the view port in which the rendering object UI will be drawn.
			@param view the control view in which the rendering object UI will be drawn.
			@param updateRgn the affected updateRgn.
		*/
		virtual void DrawRenderObjectUI 		( IViewPort* viewPort, IControlView* view, SysRgn updateRgn, PMRect frame ) const = 0;
		
		/**	Draw the rendering object UI name in the specified graphic context.
			@param fontInfo the font to use to draw the name.
			@param frame the rectangular frame in which the name should be drawn.
			@param alignment where the name should be aligned.
			@param isHilited kTrue if the name should be drawn as highlighted.
			@param isEnabled kTrue if the name should be drawn as enabled.
		*/
		virtual void DrawRenderObjectUIName		( IGraphicsContext* gc, const InterfaceFontInfo& fontInfo, const PMRect& frame, const int16& alignment, const bool16& isHilited,const bool16& isEnabled ) const = 0;

		/**	Draw the color swatch representing the rendering object.
			@param gPort the graphic port in which to draw the color swatch.
			@param frame the size of the color swatch.
		*/
		virtual void DrawRenderObjectUISwatch	( IGraphicsPort* gPort, const PMRect& frame ) const = 0;

		/**	Draw the icons for the rendering object.
			@param gPort the graphic port in which to draw the color swatch.
			@param sysFrame the size of the frame to draw one or more icons to.
			@param brightnessAware default kTrue, icons will be brightness aware.
		*/
		virtual void DrawRenderObjectUIIcons	( IViewPort* viewPort, const SysRect& sysFrame, const bool16& brightnessAware=kTrue ) const = 0;
};

#endif
