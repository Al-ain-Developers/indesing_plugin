//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanorama.h $
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
#ifndef __IPANORAMA__
#define __IPANORAMA__

#include "PMReal.h"
#include "PMRect.h"
#include "widgetid.h"


class PMMatrix;


/** Utility class used to specify how a panorama should scroll. Should be 
    IPanorama::EdgeSpec since it is not used by anything other than IPanorama.
		
		@see IPanorama::ScrollViewEdgeTo
*/
class EdgeSpec
{
public:
	enum Edge { kLeft, kTop, kRight, kBottom, kNone };
	
	EdgeSpec(Edge horizontal = kNone, Edge vertical = kNone) :
		fHorizontal(horizontal),
		fVertical(vertical)
	{
	}

	Edge	fHorizontal, fVertical;
};



//========================================================================================
// CLASS IPanorama
/** Interface used to manage views that can scroll.
		Add an implementation of IPanorama to the view's boss object.
		
		@see CPanorama
*/
//========================================================================================

class IPanorama : public IPMUnknown
{
// ----- Message Ids
public:
	enum { kDefaultIID = IID_IPANORAMA };

/** @name Panorama attributes */
//@{
public:
	/** Get the bounds of the intrinsic content being controlled by this panorama.
	    Note the result is in content coordinates, not frame coordinates. Frame coordinates
	    are the same as the content coordinates of the _parent_ of this view except the (0,0)
		origin of Frame coordinates is at the top-left corner of _this_ widget's frame. The
		content coordinate system is the one that is transformed away from frame coordinates
		by this panorama implementation. See notes at UpdatePanoramaTransform.

		@return bounds in content coordinates.
	*/
	virtual PMRect GetBounds() const = 0;


	/** Get the central content contained on the panorama.
	    For many panorama's there is no distinction between the central content and the whole. 
	    Panoramas such as pasteboards, contain a layout which is the central content.
		
	    This distinction now appears to be obsolete. All implementations return the same
		answer as GetBounds(). Although it is still called in ScrollBarPanoramaSync::AdjustPanorama

		@return central bounds in content coordinates.
	*/
	virtual PMRect GetCentralBounds() const = 0;
	
	
	/** Get the minimum size in view coordinates of white space surrounding the central content.

		@return thickness of white border in view coordinates
	*/
	virtual PMReal GetCentralBorderWhiteSpace() const = 0;
	
	
	/** Set the primary panorama. Some panoramas need the attributes of a panorama they 
	    are synching with, called the primary panorama.

		@param panorama IN the primary panorama
	*/
	virtual void SetPrimaryPanorama(IPanorama* panorama) = 0;


	/** Get the primary panorama. */
	virtual IPanorama*	GetPrimaryPanorama() const = 0;


	/** Get the delta values to use for incremental scrolling (clicking in the scroll bar arrows). */
	virtual void GetPanoramaDelta(PMPoint& delta) const = 0;


	/** Get the delta values to use for large scale scrolling (clicking in the scroll bar background). */
	virtual void GetPanoramaDeltaMultiple(PMPoint& delta) const = 0;
	//@}


/** @name Scrolling */
//@{
public:
	/** Scroll so that a given point in content coordinates ends up at the center of the view.

		@param contentLocation IN the content-coordinate point to move to the center of the view
		@param bForceRedraw IN force redraw or not
	*/
	inline void ScrollContentLocationToFrameCenter( const PBPMPoint& contentLocation, bool16 bForceRedraw = kTrue)
	{
		ScrollViewCenterTo( contentLocation, bForceRedraw);
	}


	/** An obsolete name for ScrollContentLocationToFrameCenter. New code should call 
	    ScrollContentLocationToFrameCenter. For now, old code can still call ScrollViewCenterTo
	    but this function will go away in a future release.
	*/
	virtual void ScrollViewCenterTo(const PBPMPoint& newCenter, bool16 bForceRedraw = kTrue) = 0;


	/** Scroll so that a given content-coordinate point ends up at the top-left corner of 
	    the view. To obtain a copy of the invalidation region generated by the scroll, 
	    pass in a valid SysRgn and the invalidation region will be copied into it.

		@param contentLocation IN point to scroll to
		@param InvalRgnCopy IN/OUT nil, or region to retrieve copy of the inval region
		@return the actual amount scrolled
	*/
	inline PBPMPoint ScrollContentLocationToFrameOrigin( const PBPMPoint& contentLocation, bool16 forceRedraw = kTrue, SysRgn InvalRgnCopy = nil)
	{
		return ScrollTo_neg( -contentLocation, forceRedraw, InvalRgnCopy);
	}


	/** An obsolete function that was named ScrollTo in CS6 and earler. However, the 
	    implementation had a sign error. New code should call ScrollContentLocationToFrameOrigin 
	    with the corrected PMPoint. For now, old code can simply rename calls to ScrollTo 
	    to ScrollTo_neg but this function will go away in a future release.
	*/
	virtual PBPMPoint ScrollTo_neg( const PBPMPoint& to, bool16 forceRedraw = kTrue, SysRgn InvalRgnCopy = nil) = 0;


	/** Scroll the view the distance specified (in content coordinates). A positive 'by' 
	    means reveal the content below or to the right of the frame. That is, relative to 
	    the stationary frame, the origin of the content is moved up or to the left from
	    where it currently sits. The 'by' vector is in content coordinates. Hence, a 'by'
	    vector of say (100, 100) will appear to an observer sitting in frame coordinates 
	    to move the content up and left by (200, 200) if the panorama has a 2X scale factor.

	    To obtain a copy of the invalidation region generated by the scroll, pass in a 
	    valid SysRgn and the invalidation region will be copied into it.

		@param by IN A vector that specifies by how much (in content units) to move the 
		content coordinate system up or to the left in order to reveal more content below 
		or to the right of the frame currently. A "negative" by will have the opposite effect.
		@param bForceRedraw IN force redraw or not
		@param InvalRgnCopy IN/OUT nil, or region to retrieve copy of the inval region
		@return the actual amount scrolled
	*/
	virtual PBPMPoint ScrollBy(const PBPMPoint& by, bool16 bForceRedraw = kTrue, SysRgn InvalRgnCopy = nil) = 0;


	/** Get the delta value to use for scrolling if the point is outside of the 
	    controlview's bounding box.

		@param viewPoint IN point
		@return how much to scroll for each autoscroll step.
	*/
	virtual PMPoint	GetAutoScrollDelta(const PBPMPoint& viewPoint) = 0;


	/** Get the content-corrdinate location currently positioned at the top-left corner of 
	    the frame. */
	inline PMPoint GetContentLocationAtFrameOrigin()
	{
		return -GetScrollOffset_neg();
	}

	/** An obsolete function that was named GetScrollOffset in CS6 and earler. However, the 
	    implementation had a sign error. New code should call GetContentLocationAtFrameOrigin. 
	    For now, old code can simply rename calls to GetScrollOffset to GetScrollOffset_neg 
	    but this function will go away in a future release.
	*/
	virtual PMPoint GetScrollOffset_neg() const = 0;


	/** Get the content location currently scrolled to the center of the view--in content coordinates. */
	inline PMPoint GetContentLocationAtFrameCenter()
	{
		return GetViewCenter();
	}

	
	/** An obsolete name for GetContentLocationAtFrameCenter. New code should call 
	    GetContentLocationAtFrameCenter. For now, old code can still call GetViewCenter
	    but this function will go away in a future release.
	*/
	virtual PMPoint GetViewCenter() const = 0;

//@}



/** @name Scaling */
//@{
public:

	/** Replace the current scale factors with new values. The scale is changed relative to
	    the content location currently positioned at the top-left corner of the view. That is,
	    whatever content is positioned at the top-left corner of the view will remain at the
	    top-left corner of the view and all the other content will grow away from or shrink 
	    shrink toward that point in the view.
	*/
	virtual void ScalePanorama(const PMReal& xFactor, const PMReal& yFactor) = 0;


	/** This function is obsolete and will be removed in a future release. */
	virtual void ScalePanoramaBy(const PMReal& xBy, const PMReal& yBy) = 0;


	/** Get the horizontal scale factor. 
	 *	@param actualZoomLevelInsteadOfUIZoomWidgetValue [IN] Pass kFalse to get the zoom level that should be displayed to
	 *		the user By default, InDesign adjusts the layout view zoom factor to account
	 *		for the resolution of the monitor that the panorma is displayed within such that when viewed at what the user
	 *		believes is 100%, one inch of the ruler will take up one inch of monitor space. If you do not want this monitor scale
	 *		factor included, then pass kFalse.
	 */
	virtual PMReal GetXScaleFactor(bool32 actualZoomLevelInsteadOfUIZoomWidgetValue = kTrue) const = 0;
	
	/** Get the vertical scale factor. 
	 *	@param actualZoomLevelInsteadOfUIZoomWidgetValue [IN] Pass kFalse to get the zoom level that should be displayed to
	 *		the user By default, InDesign adjusts the layout view zoom factor to account
	 *		for the resolution of the monitor that the panorma is displayed within such that when viewed at what the user
	 *		believes is 100%, one inch of the ruler will take up one inch of monitor space. If you do not want this monitor scale
	 *		factor included, then pass kFalse.
	 */
	virtual PMReal GetYScaleFactor(bool32 actualZoomLevelInsteadOfUIZoomWidgetValue = kTrue) const = 0;


	/** Get the previous scale factor (why is there only one?). */
	virtual PMReal GetPreviousScaleFactor() const = 0;


	/** Set the previous scale factor (why is there only one?). */
	virtual	void SetPreviousScaleFactor(PMReal scaleFactor) = 0;


	/** Get the previous view center */
	virtual PMPoint GetPreviousViewCenter() const = 0;


	/** Get the minimum allowable scale factor. */
	virtual PMReal GetMinScaleFactor() const = 0;


	/** Get the maximum allowable scale factor. */
	virtual PMReal GetMaxScaleFactor() const = 0;

//@}



/** @name Combinations */
//@{
public:
	/** Adjust the panorama to fill the view with the active content. */
	virtual void FitInView() = 0;

	/** Adjust the panorama to fill the view with the entire content desribed by GetBounds(). */
	virtual void FullView() = 0;

//@}

/** @name Transform */
//@{
public:
	/** Modify the passed in transformation by prepending the content to frame matrix
	    embodied by the IPanorama. Two typical use cases are to pass a pointer to the
	    identity matrix to simply get the content to frame transformation that represents
	    how the content coordinate system has been tranformed away from the coordinate
	    system of the frame containing the content. (The frame coordinate system has its
	    (0,0) origin at the top left corner of the frame and has an orientation and scale
	    identical to the content coordinates of the parent widget containing this widget.
		In other words, Frame coordinates are simply parent content coordinates translated
	    by GetFrame().TopLeft()). The other typical use case is to pass a pointer to a 
	    matrix that already has the frame-to-parent transform (from GetFrame().TopLeft())
	    perhaps appended further with parent-to-grandparent matrix an on up all the way to 
	    some outer coordinate system like the window.
		
		See further comments in CPanorama.h
	*/
	virtual void UpdatePanoramaTransform( PMMatrix* transform) const = 0;


//@}

/** @name Persistence */
//@{
public:
	/** Save the current perspective. */
	virtual void SavePerspective() const = 0;

	/** Restore from the previous perspective. */
	virtual void RestorePerspective() = 0;
//@}

/** @name Scrolling */
//@{
	/** Scroll such that the given panorama point is at the specified edge of the view.

		@param edgeSpec IN where should the scrolled point end up
		@param pt IN panorama point to scroll
		@param bForceRedraw IN force redraw or not
	*/
	virtual void ScrollViewEdgeTo(const EdgeSpec& edgeSpec, const PBPMPoint& pt, bool16 bForceRedraw = kTrue) = 0;
//@}
};





//========================================================================================
//	class PanoramaUpdateParams
/** Utility class used to notify observers how a panorama has scrolled.
		Panoramas notify interested observers when a change in perspective occurrs. 
		In order to support live scrolling and hardware scrolling, observers need more information
		than just a pointer to the panorama. A pointer to the following structure is placed in the changedBy parameter
		of update when observers are notified of changes.
		
		Currently there is a bug when InDesign broadcasts kScrollToMessage, the offset value is the negative
		of what it should be so current observers need to take this into account.
*/
//========================================================================================
class PanoramaUpdateParams
{
public:
	/** scroll constructor */
	PanoramaUpdateParams(IPanorama* panorama, const PMPoint& offset) :
		fPanorama(panorama),
		fOffset(offset),
		fXScaleFactor(1.0),
		fYScaleFactor(1.0)
	{
	}
	
	/** scale constructor */
	PanoramaUpdateParams(IPanorama* panorama, const PMReal& xScaleFactor, const PMReal& yScaleFactor) :
		fPanorama(panorama),
		fXScaleFactor(xScaleFactor),
		fYScaleFactor(yScaleFactor)
	{
	}
	
	/** the panorama */
	IPanorama*	fPanorama;
	/** scroll offset */
	PMPoint		fOffset;
	/** X scale factor */
	PMReal	fXScaleFactor;
	/** Y scale factor */
	PMReal	fYScaleFactor;
};

#endif