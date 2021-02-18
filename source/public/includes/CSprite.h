//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CSprite.h $
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
//========================================================================================

#pragma once
#ifndef __CSprite__
#define __CSprite__

#include "ISprite.h"
#include "ICallback.h"

#include "PMPoint.h"
#include "PMRect.h"
#include "HelperInterface.h"
#include "PMMatrix.h"
#include "IColorData.h"

class IDVOffscreenPortData;
class IGraphicsPort;
class IHandleShape;
class ISpread;
class SpriteAGMStream;
class UIDList;
class ILayoutRenderer;

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

inline bool16 IsPatientUser (int32 flags);
inline bool16 IsPatientUser (int32 flags)
{
	return flags & IShape::kPatientUser;
}

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

inline bool16 IsDynamicPause (int32 flags);
inline bool16 IsDynamicPause (int32 flags)
{
	return (flags & IShape::kPatientUser && flags & IShape::kDynamicPause);
}

#pragma export on
/** CSprite is an implementation of ISprite used by trackers to update the screen while tracking.  For example,
	when resizing a page item, a resize tracker will create a sprite.  The sprite represents the
	page item that is being resized and is called by the tracker to "Show" every time the mouse
	is moved.  Sprites can draw in wire frame mode or in "patient user" mode.  When in wire frame
	mode, the original page item continues to draw unchanged while an outline of the page item is
	dynamically updated to show the effect of the change made by the tracker.  In patient-user mode,
	the layout is continually redrawn to show the full effect of the change made by the tracker,
	as if the user released the mouse after each step.
*/
class WIDGET_DECL CSprite : public ISprite
{
public:
	/** Constructor
	*/
	CSprite(IPMUnknown *boss);

	/** Destructor
	*/
	virtual ~CSprite();

	/** Create sprite.
		@param gc - IN: A pointer to the IGraphicsContext representing the device that the sprite
			will draw to.
		@param itemList - IN: The uidlist indicates those items that the sprite is rendering.  
			It uses those items to compute the offscreen bounding box.  If drawItemList is kTrue 
			then the sprite will draw the items in the uid list during show. 
			If itemList is nil that means the sprite should draw its own paths (if any) and ignore
			the item list related drawing.  The path creation trackers use a nil item list because
			the actual page item isn't created until the end of dynamics.
		@param startPt - IN: start point.
		@param bDrawItems - IN: tells the sprite whether or not to draw the uid items during show.  
			Set to kFalse only if the sprite implementation has another way that it draws the 
			updated paths/shapes (such as spline editting).
		@return returns kFalse if low memory.  In that case, the sprite might do nothing or use
			XOR in ISprite::Show().  If returns kTrue the sprite succeed in creating offscreens.
	*/
	virtual bool16 CreateSprite(IGraphicsContext* gc, UIDList* itemList, const PMPoint& startPt, bool16 bDrawItemList);
	
	/** Releases references to offscreens and cleans up.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.  Used to issue an draw invalidations or screen redraws that may be necessary as
			part of the cleanup process.
	*/
	virtual void DestroySprite(IGraphicsContext* gc);

	/** Show the sprite.  
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return kFalse means the sprite is in low memory and that it drew the objects directly to gc.
	*/
	virtual bool16 Show(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);

	/** Scroll the sprite.  In general, this recreates the background and repaints.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param delta - IN: The amount to scroll.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return kFalse means the sprite is in low memory and that it drew the objects directly to gc.
	*/
	virtual bool16 Scroll(IGraphicsContext* gc, const PMPoint& delta, int32 flags, PMMatrix* xForm);

	/** For the case when the sprite fails to create an offscreen, you can still use it
		for dynamics.  But to do so requires the user to call erase so the old drawing
		is cleaned up. Erase should be called with the previous position. i.e., if the
		object is moving call show, then erase, then move the object, then show, then
		erase, then move the object, then show, etc.  Of course erase should only be
		called immediately before moving the object (and only if the object is to move).
		flags are IShape::flags
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void Erase(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);

	/** Removes any sprite-related extra drawing. Restores the screen to reflect what is in 
		the spread. This function is somewhat implementation dependent.  For instance, in path 
		creation it may be used to update with the newly created segment, or for rotation getting 
		rid of the tracker line
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param bForceRedraw - IN: Whether or not to force the gc to redraw before returning.
		@param extraXform - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void Hide(IGraphicsContext* gc, bool16 bForceRedraw, PMMatrix* extraXform);

	/** Tells the sprite that the objects bbox has changed and to recalculate the cached
		version in the sprite.
	*/
	virtual void InvalidateBBox();

	/** If called, this will disable the shapes in the uidlist from drawing in the background
		offscreen.  This is different than the bDrawItems flag in CreateSprite.  DisableShapes
		specifically affects only the items drawing during the creation of the background.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.  Necessary to obtain the IDrawMgr for the port in order to tell the IDrawMgr
			to Disable the shape.
		@param disable - IN: kTrue to disable the drawing of the shape.  kFalse to enable the drawing.
	*/
	virtual void DisableShapes (IGraphicsContext *gc, bool16 disable);

	/** Gets device bounds
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return Returns the bounds used by the sprite.  The bounds includes everything the sprite
		would draw during show given the same flags and matrix.  For CSprite, this bounds is the
		union of GetShapeDeviceBounds, GetHandleDeviceBounds and GetTrackerBounds, all clipped to
		the view.
	*/
	virtual SysRect GetDeviceBounds (IGraphicsContext* gc, int32 flags, PMMatrix* xForm);

	/** Returns whether the sprite has been initialized -- that is, that CreateSprite has been called.
	*/
	virtual bool16 ValidSprite() const
	{
		return fValidSprite;
	};

	/** Returns kTrue when sprite needs to update, kFalse otherwise. */
	virtual bool16 NeedsUpdate(const PMPoint& where, int32 flags) const
	{
		// #2910574 - we added a timer to DrawSprite to limit recomposition frequency.
		//  However if mouse moves before timer elapses this will return true and we'll
		//  continually redraw with no further movement until the timer elapses.  This is
		//  a major hit on drag performance.  So we don't signal we need to update until the mouse moves.
		// #3112261 - we now allow the sprite to recompose and update one extra time when the
		//  composition interval is reached.
		return (IsPatientUser (flags) &&
				((where != fCurrentPoint) ||
				 (where != fLastCompositionPoint && (SystemUtils::TickCount() - fLastCompositionTicks > kSubsequentCompositionThreshold))));
	}
	
protected:	
	/** Obsolete.
	*/
	virtual void DisableHandleShapes(IGraphicsContext *gc, bool16 disable);

	/** Gets shape device bounds
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@return Returns the union of the IShape::GetPaintedBBox of each of the items in the itemList
			passed to CreateSprite.
	*/
	virtual PMRect GetShapeDeviceBounds(IGraphicsContext* gc, int32 flags);

	/** Gets handle device bounds
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
		@return Returns the union of the IHandleShape::GetPaintedBBox of each of the items in the itemList
			passed to CreateSprite.
	*/
	virtual PMRect GetHandleDeviceBounds(IGraphicsContext* gc, int32 flags, PMMatrix* xForm);

	/** Allows the tracker to dynamically change the update area used by the sprite.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@return If the boss containing this sprite has an IPathGeometry, then grab that IPathGeometry and
			return its GetCtrlPointsBoundingBox.
	*/
	virtual PMRect GetTrackerBounds(IGraphicsContext* gc, int32 flags);

	/** Gets selection bounds
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.  Used to obtain the view that is passed into the GetSelectionRgn call.
		@return Returns bounds of the current selection.  Bounds are obtained by asking the ISelectionManager
			for the ISelectionDataSuite and then computing the bounds on its GetSelectionRgn.
	*/
	virtual PMRect GetSelectionBounds(IGraphicsContext* gc);
	
	/** Draws the dynamic part of the changes when not in patient-user mode.  Draws the paths in xor mode.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
	*/
	virtual void DrawTrackerExtra(IGraphicsContext* gc, int32 flags);

	/** The first time that Show is called, ShowFirstTime will be called to set up its offscreens.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void ShowFirstTime(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);

	/** Show calls ShowSprite every time except the first time, where it calls ShowFirstTime.  ShowSprite
		uses the offscreens set up by ShowFirstTime.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void ShowSprite(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);

	/** Called by Scroll when we are not in a low memory situation.  When in a low memory situation,
		Scroll will call ScrollLowMemory.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param delta - IN: The amount to scroll.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void ScrollSprite(IGraphicsContext* gc, const PMPoint& delta, int32 flags, PMMatrix* xForm);

	/** Called by Show when in a low memory state.  Draws in XOr mode.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void ShowLowMemory(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);

	/** Same as ShowLowMemory, except that it erases and redraws the gc first.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void ShowLowMemoryFirstTime(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);
	
	/** Called by Scroll when in a low memory situation and offscreens cannot be used.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param delta - IN: The amount to scroll.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void ScrollLowMemory(IGraphicsContext* gc, const PMPoint& delta, int32 flags, PMMatrix* xForm);

	/** Called by Hide to do all the work when not in a low memory state.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param bForceRedraw - IN: Whether or not to force the gc to redraw before returning.
		@param extraXform - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void HideSprite(IGraphicsContext* gc, bool16 bForceRedraw, PMMatrix* extraXform);

	/** Called by Hide to do all the work when in a low memory state and offscreens cannot be used.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param bForceRedraw - IN: Whether or not to force the gc to redraw before returning.
		@param extraXform - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void HideLowMemory(IGraphicsContext* gc, bool16 bForceRedraw, PMMatrix* extraXform);

	/** In the provided gc, erases and redraws the update area defined by GetDeviceBounds.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param where - IN: Obsolete.  Not used.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void EraseAndRedrawShapes(IGraphicsContext* gc, const PMPoint& where, int32 flags, PMMatrix* xForm);
	
	/** Override this method if the client wants a different tracker hilite color.
		@param layerUID - IN: The UID of the layer whose layer color to use for hilighting.
	*/
	virtual void SetHiliteColor (UID layerUID);
	
	/** Draw the shapes intersecting the union of the clipRgn and any pending invalidation areas
		for the view represented by the provided GraphicsContext. 
		@param gc - IN: A pointer to the IGraphicsContext to draw into.
		@param clipRgn - IN: May be nil. Actually represents any additional area to update.
			This region gets unioned with any pending invalidations for the view represented by the gc.
		@param bDisable - IN: indicates whether to allow the sprite uid list objects to draw or not.
	*/
	virtual void DrawShapes (IGraphicsContext* gc, SysRgn clipRgn = nil, bool16 bDisable = kFalse);

	/** Draw any selection highlighting.
		@param gc - IN: A pointer to the IGraphicsContext to draw into.
	*/
	virtual void DrawSelection (IGraphicsContext* gc);

	/** Draws the itemList passed into CreateSprite to the provided gc, using the IShape::flags
		@param gc - IN: A pointer to the IGraphicsContext to draw into.
		@param flags - IN: flags are IShape::flags. @see IShape.h
	*/
	virtual void DrawSpriteShapes(IGraphicsContext* gc, int32 flags);
	
	/** Calls DrawCenterX in XOr mode for each of the items in the itemList passed into CreateSprite.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	virtual void DrawSpriteHandles(IGraphicsContext* gc, int32 flags, PMMatrix* xForm);

	/** Override CreateTrackerPaths to do something special such as the reference line
		in the rotate sprite.  CSprite's implementation walks/draws the path stored in the IPathGeometry of
		the sprite's boss and then draws the handle vectors.
		@param gc - IN: The IGraphicsContext. 
	*/
	virtual void CreateTrackerPaths(IGraphicsContext* gc);
	
	/** Helpers to draw the handles and paths
		@param gc - IN: The IGraphicsContext.  
		@param bDoDirectionHandles - IN: Include the control handles for each point?
	*/
	virtual void CreateHandlePaths(IGraphicsContext* gc, bool16 bDoDirectionHandles = kTrue);
	
	/** Given a rectangle, clip it to the view referenced by the provided IGraphicsContext.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite draws.
		@param bounds - IN/OUT: The rectangle to intersect with the view bounds.
	*/
	virtual void ClipToView(IGraphicsContext* gc, SysRect* bounds);

	/** Given a rectangle, clip it to the view referenced by the provided IGraphicsContext.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param bounds - IN/OUT: The rectangle to intersect with the view bounds.
	*/
	virtual void ClipToView(IGraphicsContext* gc, PMRect& bounds);

	/** Gets standOff bounding box
		@param pShape - IN: The page item whose text wrap we are interested in.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@param bBox - IN: The rect to return if there is no text wrap.
		@return If the provided page item has a text wrap, return the wrap's bounding box in the coordinates
		of the provided IGraphicsContext (i.e. in screen coordinates).  Otherwise, return the
		provided bBox.
	*/
	virtual PMRect GetStandOffBBox( IShape *pShape, IGraphicsContext *gc, int32 flags, const PMRect &bBox );
	
	/** Returns the draw flags to use when when calling DrawMgr::Draw.  For standard sprites this value is cached
		during CreateSprite.  However, some sprites (TextOffscreen) may need to calculate the draw flags more
		often than that
	*/
	virtual int32 GetDrawFlags() const;
	
	/** Obsolete.  CSprite does not currently use display lists for drawing.
		@param flags - IN: flags are IShape::flags. @see IShape.h
		@return Returns whether to use a display list or not
	*/
	virtual bool16 UseDisplayList (int32 flags);
	
	/** Called when we are setting up our offscreens to obtain pending invals for the offscreen.
		Only used in offscreen mode (i.e., not in low memory mode).
		@param iView - IN: Used to obtain offscreen's pending inval areas.
		@param invalidBounds - OUT: Pending invals for the provided offscreen are unioned with invalidBounds.
	*/
	void AddInvalidOffscreenBounds (IControlView* iView, PMRect* invalidBounds);
	
	/** Called when we are setting up our offscreens to obtain any additional area to be updated.
		Only used in offscreen mode (i.e., not in low memory mode).
		@param iView - IN: Used to obtain pending invals for the offscreen.
		@param invalidBounds - OUT: Pending invals for the provided view are unioned with invalidBounds.
	*/
	void AddInvalidLayoutBounds (IControlView* iView, PMRect* invalidBounds);

	/** Draws dragging a wire frame sprite, a small X is drawn in XOr mode at the center of each page item.
		@param gPort - IN: The port to draw into.
		@param center - IN: Where, in pasteboard coordinates, to draw the X.
	*/
	static void DrawCenterX( IGraphicsPort* gPort, const PBPMPoint& center ) ;

	/** Draw smart alignment guides.
		@param gc - IN: A pointer to the IGraphicsContext representing the device to which the sprite
			draws.
		@param xForm - IN: The matrix represents the transformation that is passed into all the IHandleShapes
			in the item list (See CreateSprite). The matrix is a pasteboard relative transformation.
	*/
	void DrawSmartGuides(IGraphicsContext *gc, const PBPMPoint where, const PMMatrix *xForm);

	PMMatrix	fXformFromLastShow;
	SysRect fLastBounds;
	ColorArray	fRGBColorValue;
	PMPoint fStartPoint;
	PMPoint fCurrentPoint;
	SysPoint fLastMouseLoc;

	IControlView* fControlView;
	UIDList* fItemList;
	IDVOffscreenPortData* fBackgroundVP;
	IDVOffscreenPortData* fForegroundVP;
	IDataBase*	fDataBase;

	int32 fDrawFlags;

	bool16 fValidDeviceBounds;

	bool16 fFirstTime;
	bool16 fValidSprite;
	bool16 fLowMemory;
	bool16 fIsFrontView;

	
	bool16 	fDrawItemList;
	bool16 fIsPathSelection;
	bool16 fHandlesDisabled;
	
	bool16	fDoRevealAllImageData;
	bool16	fSmartGuidesDrawn;
	bool16	fDrawSmartGuides;

private:
	//-------------------------------------------------------------------------------
	/**@name Private
		These reuse a global set of offscreens. If a client of CSprite wishes to 
		replace these, override SetupBackgroundPort and SetupForegroundPort instead.
	*/
	//@{-----------------------------------------------------------------------------
	void DrawBackgroundFirstTime (IGraphicsContext* gc);	
	
	void CreateItemDisplayList (IGraphicsContext* gc, int32 flags);
	
	UIDRef GetPageGuideColor();
	UIDRef GetSmartGuideColor();
	
	void	CreateTimer();
	void	CleanupTimer();

	void DrawSelectionPort(ILayoutRenderer* renderer, SysRgn updateRgn, const PMPoint& where, int32 flags, PMMatrix* xForm);
	void DrawSpriteGfx(IGraphicsContext* oc, const PMPoint& where, int32 flags, PMMatrix* xForm);

	PMMatrix			fOriginalMat;
	PMMatrix			fLastMatrix;
	PMRect				fHandleDeviceBounds;
	PMRect 				fLastShapeDeviceBounds;
	PMPoint				fLastCompositionPoint;
	UIDRef				fSmartGuideColor;
	UIDRef				fPageGuideColor;
	SpriteAGMStream*	fAGMStream;
	void*				fItemDLPort;
	uint32				fStartTicks;
	uint32				fLastCompositionTicks;
	bool16				fUseDisplayList;

#ifdef DEBUG
public:
	bool16 gDebugDontUseOffscreen;
#endif
	//@} -----------------------------------------------------------------------------

DECLARE_HELPER_METHODS()
};

/** FindMasterItemsIterator is used to walk the hierarchy looking for master page items that belong to the 'candidates.'
	When such a page item is found, it is appended to the 'masterItemsFound' list and a Matrix that can be used to
	transform the master page item into pasteboard coordinates for the target drawing spread is appended to 'masterInner2DrawingSpreadPBList.'
*/
class WIDGET_DECL FindMasterItemsIterator : public ICallback 
{ 		
public: 
	/**
		@param drawingSpread [IN]: the target spread
		@param masterItemsFound [OUT]: master page items from 'candidates' that are encountered while iterating the drawingSpread's draw hierarchy.
		@param candidates [IN]: If the page item is not in 'candidates,' then it is ignored.
		@param masterInner2DrawingSpreadPBList [OUT]: list of Matrices that can be used to
			transform the corresponding master page item in 'masterItemsFound' into pasteboard coordinates for the 
			target drawing spread.
	*/
	FindMasterItemsIterator(const ISpread *drawingSpread, UIDList *masterItemsFound, const UIDList *candidates, PMMatrixCollection *masterInner2DrawingSpreadPBList); 
	
	/** Callback is where all the logic lives */
	virtual void ExecuteCallback(const PMMatrix *xform, IPMUnknown *iThing, int32 flags);
	
	/** IterateChildren triggers the walking of the hierarchy. */
	virtual int32 IterateChildren();
	
	/** Grab the IDrawMgr for this iterator. */
	virtual IDrawMgr* GetCallbackDrawManager();

private: 
	const ISpread* fSpread; 
	IDrawMgr* fDrawMgr; 
	UIDList *fVisibleMasterItems; 
	const UIDList* fCandidates;
	PMMatrixCollection *fMatrices;
	bool	fMasterItemsDone;
}; 

#ifdef DEBUG
WIDGET_DECL void ToggleDebugSpriteLowMem();
#endif
#pragma export off

#endif
