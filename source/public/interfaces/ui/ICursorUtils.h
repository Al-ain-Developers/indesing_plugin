//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ICursorUtils.h $
//  
//  Owner: Dave Stephens
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
#ifndef __ICursorUtils__
#define __ICursorUtils__

#include "IPMUnknown.h"

#include "CursorSpec.h"
#include "PMString.h"

#include "Utils.h"

#include "AppUIID.h"

class IControlView;
class IDynamicTrackerData;
class IDynamicTransformData;
class IGraphicsPort;

/**
	ICursorUtils is a utility class used to create custom bitmap based cursors.
	Please use the ICursorUtils directly via the UtilsBoss if possible, see Utils.h:
	i.e. Utils<ICursorUtils>()->DrawStringIntoOffscreen( ... ) ;
*/
class ICursorUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICURSORUTILS };

	enum CursorOptions
	{
		kDefaultCursor = 0,		// do not modify the cursor
		kShowWidthHeight,		// Add width/height information to cursor
		kShowXPosition,			// Add X Position information to cursor (useful for vertical guides)
		kShowYPosition,			// Add Y Position information to cursor (useful for horizontal guides)
		kShowXYPosition,        // Add X,Y Position information to cursor
		kShowLineLength,		// Add Line length information to cursor
		kShowScale,				// Add Scale information to cursor
		kShowRotation,			// Rotation in degrees
		kShowLiveCornerRadius,   // Add live corner radius info to cursor
		kShowWidth,				// Width only -- no height (for Gap Tool)
		kShowHeight,			// Height only -- no width (for Gap Tool)
		kShowZoomFactor			//show current layout zoom factor
	};

	/** Initialize a new custom cursor that shows the current width/height of a sprite.
		@param option [IN]: Type of information you want updated and displayed dynamically within the cursor.
	*/
	virtual void InitCursor(const CursorOptions option) = 0;


	/** Create a new custom cursor showing the information specified by InitCursor of a sprite with the provided cursor
		superimposed on top-left of the new cursor.
		@param adjustedCursorSpec [IN/OUT]: on input,the cursor to super-impose. On output, the new custom cursor.
	*/
	virtual void UpdateCursor(CursorSpec& adjustedCursorSpec) const = 0;

	/** Release any interfaces held due to calls to InitCursor and/or one of the Update methods.
	*/
	virtual void ReleaseCursor() = 0;

	/** Utility routine which creates a graphics port around a bitmap, so we can draw to it with AGM 
	 @param bitmapBuffer [IN]: pointer to the bitmap buffer to be used. Buffers length is width * height * 4;
	 @param bitmapWidth [IN]: width, in pixels, of the bitmap.
	 @param bitmapHeight [IN]: height, in pixels, of the bitmap.
	 @param hasAlpha [IN]: on input,the cursor to super-impose. On output, the new custom cursor.
	 @param hiRes [IN]: whether the bitmap is at regular 72dpi or high/retina resolution (144dpi), in which case the returned IGraphicsPort will be scaled accordingly.
	 @return pointer to an IGraphicsPort interface can be used to draw into the bitmapped buffer.
	 */
	virtual IGraphicsPort* QueryGraphicsPortForBitmap(uchar* bitmapBuffer, uint32 bitmapWidth, uint32 bitmapHeight, bool16 hasAlpha, bool16 hiRes) const = 0;

	/** Utility routine which creates a graphics port around a bitmap, so we can draw to it with AGM
	@param bitmapBuffer [IN]: pointer to the bitmap buffer to be used. Buffers length is width * height * 4;
	@param bitmapWidth [IN]: width, in pixels, of the bitmap.
	@param bitmapHeight [IN]: height, in pixels, of the bitmap.
	@param hasAlpha [IN]: on input,the cursor to super-impose. On output, the new custom cursor.
	@param hiRes [IN]: whether the bitmap is at regular 72dpi or high/retina resolution (144dpi), in which case the returned IGraphicsPort will be scaled by passed scaleFactor.
	@return pointer to an IGraphicsPort interface can be used to draw into the bitmapped buffer.
	*/
	virtual IGraphicsPort* QueryGraphicsPortForBitmap(uchar* bitmapBuffer, uint32 bitmapWidth, uint32 bitmapHeight, bool16 hasAlpha, bool16 hiRes, float scaleFactor) const = 0;
};


#endif	// __ICursorUtils__
