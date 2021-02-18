//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/NoHandleSprite.h $
//  
//  Owner: Heath Lynn
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
#ifndef __NoHandleSprite__
#define __NoHandleSprite__

#include "CSprite.h"

#pragma export on
/** NoHandleSprite
	This implementation of CSprite is used when resizing page items.  It draws the path shapes but does
	not draw the handles.
@see CSprite
*/
class WIDGET_DECL NoHandleSprite : public CSprite
{
public:
	/** Constructor
	*/
	NoHandleSprite(IPMUnknown *boss);

	/** Destructor
	*/
	virtual ~NoHandleSprite();
	
protected:
	/** This implementation walks/draws the path stored in the IPathGeometry of
		the sprite's boss, but does not draw the handle vectors.
		@param gc - IN: The IGraphicsContext.
	*/
	virtual void CreateTrackerPaths(IGraphicsContext* gc);

	/** This implementation draws the X in the center of the sprite, but does not
		draw any of the shape's handles.
		@param gPort - IN: The IGraphicsContext.
		@param bDoDirection - IN: Include the control handles for each point?
	*/
	virtual void CreateHandlePaths(IGraphicsContext* gc, bool16 bDoDirection);		
	
	/** Obsolete.  CSprite does not currently use display lists for drawing.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@return Returns whether to use a display list or not
	*/
	virtual bool16 UseDisplayList (int32 flags);

	/** Allows the tracker to dynamically change the update area used by the sprite.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@return If the boss containing this sprite has an IPathGeometry, then grab that IPathGeometry and
			return its GetCtrlPointsBoundingBox.
	*/
	virtual PMRect GetTrackerBounds(IGraphicsContext* gc, int32 flags);

	/** Calls CSprite::DrawSpriteHandles and draws Smart Dimension guides if appropriate.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void DrawSpriteHandles(IGraphicsContext* gc, int32 flags, PMMatrix* xForm);

private:
	bool32	fSmartDimensionsDrawn;
};

#pragma export off

#endif