//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRenderingObjectUI.h $
//  
//  Owner: Chris Jones
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
#ifndef __IRenderingObjectUI__
#define __IRenderingObjectUI__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IGraphicsPort;

/**
 * Unless you have created your own form of rendering object --
 * the equal of a color, gradient, tint, etc -- you are unlikely
 * to be interested in this interface.  It allows the UI behavior
 * of a rendering object to be refined.
 */


class IRenderingObjectUI : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRENDERINGOBJECTUI };

		/**
		 * By default, a rendering object is assumed to be a paint that
		 * can be installed on a port, and then 'filled.'  This mechanism
		 * is used to draw the proxy control into the specified rectangle.
		 * This function, however, allows the implementation to override 
		 * the proxy draw, painting an image, icon, etc.
		 *
		 * @param gPort the port to draw into.
		 * @param r the rect to draw into.
		 */

		virtual void DrawProxy(IGraphicsPort* gPort, const PMRect& r) const = 0;

		/**
		 * Should return true if this rendering object can be applied to a stroke.
		 */

		virtual bool16 SupportsStroke() const = 0;

		/**
		 * Should return true if this rendering object can be applied to a fill.
		 */

		virtual bool16 SupportsFill() const = 0;

		/**
			Parameter used in SelectSwatchHelper().
		*/
		enum ApplyAction
		{
			/**	Unknown Action (error condition). */
			kNone = -1,

			/**	Action is to be applied to current stroke. */
			kApplyToStroke,
			
			/**	Action is to be applied to current fill. */
			kApplyToFill
		};
		
		/**
			Help determine how this swatch should be selected given the current active swatch selection
			in the graphic state and whether the selection applies to the current fill or stroke.
			@param gfxRenderUID the current active swatch UID in the graphic state.
			@param applyAction whether the action is to be applied to fill or stroke.
			@param swatchSelectionIsUnique indicate if the current selection already has the same swatch, gfxRenderUID, applied before this
			swatch is applied.
		*/
		virtual void SelectSwatchHelper (UID gfxRenderUID, ApplyAction applyAction, bool16 swatchSelectionIsUnique = kFalse) const = 0;

		/**
		 * Whether or not DrawProxy should be called to draw the proxy for this rendering object.
		 * If false, then the redering object is simply installed in the port and drawn.
		 */

		virtual bool16 CustomDrawProxy() = 0;

		/**
		 * Returns an icon ID to draw in the proxy view.  If there is none, the function returns
		 * false and the icon id is not modified.
		 */

		virtual bool16 GetProxyIconID( RsrcID& iconLarge, RsrcID& iconSmall ) = 0;
};		

#endif
