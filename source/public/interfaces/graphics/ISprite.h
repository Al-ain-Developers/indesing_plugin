//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISprite.h $
//  
//  Owner: Jack Kirstein
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
//  Purpose of interface:
//  ISprite defines how to draw and manipulate objects dynamically.
//  
//========================================================================================

#pragma once
#ifndef __ISprite__
#define __ISprite__

#include "IPMUnknown.h"
#include "GraphicsID.h"

#include "PMReal.h"
#include "IShape.h"

class UIDList;
class PMRect;
class PMMatrix;

/** ISprite is an interface used by trackers to update the screen while tracking.  For example,
	when resizing a page item, a resize tracker will create a sprite.  The sprite represents the
	page item that is being resized and is called by the tracker to "Show" every time the mouse
	is moved.  Sprites can draw in wire frame mode or in "patient user" mode.  When in wire frame
	mode, the original page item continues to draw unchanged while an outline of the page item is
	dynamically updated to show the effect of the change made by the tracker.  In patient-user mode,
	the layout is continually redrawn to show the full effect of the change made by the tracker,
	as if the user released the mouse after each step.

	@see IShape
*/
class ISprite : public IPMUnknown
{
public:
	 enum { kDefaultIID = IID_ISPRITE };

	/** Creates sprite
		@param gc - IN: A pointer to the IGraphicsContext representing the device that the sprite
			will draw to.
		@param itemList - IN: The uidlist indicates those items that the sprite is rendering.  
			It uses those items to compute the offscreen bounding box.  If drawItemList is kTrue 
			then the sprite will draw the items in the uid list during show. 
			If itemList is nil that means the sprite should draw its own paths (if any) and ignore
			the item list related drawing.  The path creation trackers use a nil item list because
			the actual page item isn't created until the end of dynamics.
		@param startPt - start point
		@param bDrawItems - IN: tells the sprite whether or not to draw the uid items during show.  
			Set to kFalse only if the sprite implementation has another way that it draws the 
			updated paths/shapes (such as spline editting).
		@return returns kFalse if low memory.  In that case the sprite might do nothing or use
			XOR in ISprite::Show().  If returns kTrue the sprite succeed in creating offscreens.
	*/
	virtual bool16 CreateSprite(IGraphicsContext* gc, UIDList* itemList, const PMPoint& startPt, bool16 bDrawItems = kTrue) = 0;

	/** Releases references to offscreens and cleans up.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.  Used to issue an draw invalidations or screen redraws that may be necessary as
			part of the cleanup process.
	*/
	virtual void DestroySprite(IGraphicsContext* gc) = 0;
	
	/** If called, this will disable the shapes in the uidlist from drawing in the background
		offscreen.  This is different than the bDrawItems flag in CreateSprite.  DisableShapes
		specifically affects only the items drawing during the creation of the background.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.  Necessary to obtain the IDrawMgr for the port in order to tell the IDrawMgr
			to Disable the shape.
		@param disable - IN: kTrue to disable the drawing of the shape.  kFalse to enable the drawing.
	*/
	virtual void DisableShapes (IGraphicsContext* gc, bool16 disable) = 0;
	
	/** Show the sprite.  
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return kFalse means the sprite is in low memory and that it drew the objects directly to gc.
	*/
	virtual bool16 Show(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm = nil) = 0;
	
	/** Scroll the sprite.  In general this recreates the background and repaints.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param delta - IN: The amount to scroll.
		@param flags - IN: flags are IShape::flags.
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return kFalse means the sprite is in low memory and that it drew the objects directly to gc.
	*/
	virtual bool16 Scroll(IGraphicsContext* gc, const PMPoint& delta, int32 flags, PMMatrix* xForm = nil) = 0;
	
	/** For the case when the sprite fails to create an offscreen you can still use it
		for dynamics.  But to do so requires the user to call erase so the old drawing
		is cleaned up. Erase should be called with the previous position. i.e., if the
		object is moving call show, then erase, then move the object, then show, then
		erase, then move the object, then show, etc.  Of course erase should only be
		called immediately before moving the object (and only if the object is to move).
		flags are IShape::flags
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags.
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void Erase(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm = nil) = 0;
	
	/** Removes any sprite related extra drawing. Restores the screen to reflect what is in 
		the spread. This function is somewhat implementation dependent.  For instance, in path 
		creation it may be used to update with the newly created segment, or for rotation getting 
		rid of the tracker line
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param bForceRedraw - IN: Whether or not to force the gc to redraw before returning.
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void Hide(IGraphicsContext* gc, bool16 bForceRedraw, PMMatrix* xForm = nil) = 0;
	
	/** Returns the bounds used by the sprite.  The bounds includes everything the sprite
		would draw during show given the same flags and matrix.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return the bounds used by the sprite.
	*/
	virtual SysRect GetDeviceBounds (IGraphicsContext* gc, int32 flags, PMMatrix* xForm = nil) = 0;

	/** Tells the sprite that the object's bbox has changed and to recalculate the cached version in the sprite.
	*/
	virtual void InvalidateBBox() = 0;
	
	/** Tells whether the sprite has been initialized -- that is, CreateSprite has been called.
	*/
	virtual bool16 ValidSprite() const = 0;

	/** Returns kTrue when sprite needs to update, kFalse otherwise. Typically a sprite won't need updating
		unless it has moved, but this hook allows clients to override.
	*/
	virtual bool16 NeedsUpdate(const PMPoint& where, int32 flags) const = 0;
};
#endif
