//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CPanorama.h $
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
#ifndef __CPANORAMA__
#define __CPANORAMA__

#include "IPanorama.h"
#include "HelperInterface.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif



class CTransform;

/** Shared default implementation of the IPanorama interface.
		Implementers of IPanorama should derive from CPanorama.
		@see IPanorama
*/

class WIDGET_DECL CPanorama : public IPanorama
{
// ----- Constructors/destructors
public:
	CPanorama( IPMUnknown *boss, bool16 push_changes_into_drover = kFalse);
	virtual ~CPanorama();

/** @name Panorama attributes */
//@{
public:

	/** Note that GetBounds is pure virtual in IPanorama and is not implemented 
	    here. It must be implemented by derived classes of course as this base 
	    class can have no idea what the intrinsic content bounds is.
	*/
	//virtual PMRect GetBounds() const = 0;


	/** Override to provide the central content contained in the panorama.
	    Default implementation returns GetBounds() - so no special central content.
	*/
	virtual PMRect GetCentralBounds() const;


	/** Override to provide the white space surrounding the central content.
	    This implementation returns 0.
	*/
	virtual PMReal GetCentralBorderWhiteSpace() const;


	/** Set the primary panorama. This implementation attaches the seconday 
	    panorama (this) to the primary panorama as an observer, and makes sure 
	    they are initially in sync.
	*/
	virtual void SetPrimaryPanorama(IPanorama* panorama);


	/** Get the primary panorama. */
	virtual IPanorama* GetPrimaryPanorama() const;


	/** Override to change the deltas used for incremental scrolling (clicking 
	    in the scroll bar arrows). This implementation returns 1/12th the size 
	    of the view.
	*/
	virtual void GetPanoramaDelta(PMPoint& delta) const;


	/** Override to change the deltas used for large scale scrolling (clicking 
	    in the scroll bar background). This implementation returns the size of 
	    the view.
	*/
	virtual void GetPanoramaDeltaMultiple(PMPoint& delta) const;
	
//@}

/** @name Scrolling */
//@{
public:
	/** See comments in IPanorama.h */
	virtual void ScrollViewCenterTo(const PBPMPoint& newCenter, bool16 bForceRedraw = kTrue);


	/** See comments in IPanorama.h */
	virtual PBPMPoint ScrollTo_neg(const PBPMPoint& to, bool16 forceRedraw = kTrue, SysRgn InvalRgnCopy = nil);


	/** Override to change or augment default implementation. The default 
	    implementation does approximately the following:
	
			fScrollOffset -= by * fScaleFactors;
	
	    Note that fScrollOffset is the location of the content origin in frame 
	    coordinates. Hence the 'by' vector is provided in content units and must 
	    be converted to frame units before adjusting fScrollOffset. Note also 
	    that a positive 'by' means move the content up/left in the frame so the 
	    user can see more of the content below/right of the frame currently. See 
	    comments in IPanorama.h
	*/
	virtual PBPMPoint ScrollBy(const PBPMPoint& by, bool16 bForceRedraw = kTrue, SysRgn InvalRgnCopy = nil);


	/** Override to change the deltas used for auto scrolling. This implementation returns 0.
	*/
	virtual PMPoint	GetAutoScrollDelta(const PBPMPoint& viewPoint);


	/** See comments in IPanorama.h*/
	virtual PMPoint	GetViewCenter() const;


	/** See comments in IPanorama.h*/
	virtual PMPoint	GetScrollOffset_neg() const;
//@}



/** @name Scaling */
//@{
public:
	
	/** See comments in IPanorama.h*/
	virtual void ScalePanorama(const PMReal& xFactor, const PMReal& yFactor);

	/** See comments in IPanorama.h*/
	virtual void ScalePanoramaBy(const PMReal& xBy, const PMReal& yBy);
	
	/** See comments in IPanorama.h*/
	virtual PMReal GetXScaleFactor(bool32 actualZoomLevelInsteadOfUIZoomWidgetValue = kTrue) const;

	/** See comments in IPanorama.h*/
	virtual PMReal GetYScaleFactor(bool32 actualZoomLevelInsteadOfUIZoomWidgetValue = kTrue) const;
	
	/** See comments in IPanorama.h*/
	virtual PMReal GetPreviousScaleFactor() const;

	/** See comments in IPanorama.h*/
	virtual void SetPreviousScaleFactor(PMReal scaleFactor);

	/** See comments in IPanorama.h*/
	virtual PMPoint GetPreviousViewCenter() const;
	
	/** See comments in IPanorama.h*/
	virtual PMReal GetMinScaleFactor() const;

	/** See comments in IPanorama.h*/
	virtual PMReal GetMaxScaleFactor() const;

	/** See comments in IPanorama.h*/
	virtual PMPoint GetViewScrollOffset() const;

	/** This function is for internal use only and will be removed in a future release.*/
	virtual void SetScrollOffset_neg(PMPoint scrollBy);
//@}



/** @name Combinations */
//@{
public:
	/** Adjust the panorama to fill the view with the active spread. Override to 
	    change default implementation. In particular, override this if the content 
	    is not the layout view
	*/
	virtual void		FitInView();

	/** See comments in IPanorama.h. Override to change default implementation. */
	virtual void		FullView();

//@}

/** @name Transform */
//@{
public:
	/** Modify the passed in transform to match the current panorama scroll 
	    offset and scaling

	The only geometric data a widget stores (publicly) is its frame -- accessible 
	via IControlView::GetFrame(). This is a PMRect stored in the parent widget's 
	content coordinate system. This means an IControlView has no intrinsic size 
	or shape--it is simply expected to draw only in this allowed parent region. 
	Most widgets "grow" or "shrink" their content exactly into this rectangle. A 
	widget that has larger content that is to be viewed _through_ this frame can 
	add an IPanorama impl on its boss. This panorama can be used to scroll and 
	zoom the widget content within the parent frame and to define some intrinsic 
	size for the sake of scroll bars.

	The panorama maintains the transform from the inner (or content) coordinates 
	of this view (the boss containing the panorama impl) to what I'll here call 
	"frame coordinates". Frame coordinates are aligned with and have the same 
	scale as the content coordinates of the parent view but have its (0,0) point 
	at the top-left corner of this view's frame. (In other words, to transform 
	from frame coordinates to parent-content coordinates one simply translates 
	by GetFrame().TopLeft().)
	
	UpdatePanoramaTransform is expected to prepend onto the passed-in transform 
	this incremental panorama effect--the content-to-frame transfrom. The matrix 
	parameter is assumed to already contain the frame-coordinates to parent-content 
	coordinates translation--as that much of the child-to-parent transform is 
	assumed for all IControlViews and is available directly from GetFrame(). If 
	one passes the identity matrix to UpdatePanoramaTransform, the result will 
	be only the content-to-frame transfrom.
	
	Note that the implementation of UpdatePanoramaTransform in CPanorama.cpp is 
	simply:

		transform = fScaleFactors * fScrollOffset * transform;

	where fScaleFactors and fScrollOffset are, in effect, CPanorama's data members 
	(really there are separate fXScaleFactor and fYScaleFactor, not a single member 
	fScaleFactors). This means that fScrollOffset moves the content axes off the 
	top-left frame corner first (in frame units) and then the content axes are 
	stretched from that new origin location. (A positive offset stored in 
	fScrollOffset means the content's origin is down or to the right from the 
	top left corner of the frame--in our left-hand UI coordinate systems anyway.)
	
	(Recall that from the point of view of moving coordinate axes around by the 
	transform (leaving the inner (x,y) geometry alone), you work through the 
	matrix from right to left. From the point of view of an (x,y) pair getting 
	modified by the transform (leaving the axes alone), you work from left to 
	right. So if you wanted to see where a point in content coordinates will end 
	up in frame coordinates, you would scale the coordinate first by fScaleFactors 
	and then translate by fScrollOffset. In other words, fScrollOffset is the 
	location of the content's origin in frame coordinates.)
		
	However, even though the panorama transform is stored as a pair of offsets 
	(fScrollOffset) and a pair of scale factor (fXScaleFactor, fYScaleFactor) 
	data members such that the total affect is the inner to frame matrix: 
	fScaleFactors*fScrollOffset, the meaning of the rest of the API suggests a 
	better implementation of the inner to frame matrix might have been: 
	fScrollOffset*fScaleFactors. Or it may have been better to make the API take 
	frame coordinates as parameters. In other words, it's odd that this 
	implementation chose to implement the panorama like this: (considering just 
	the x-coordinate in this sample)
	
		xFrame = xInner*fXScaleFactor + fScrollOffset.X(); //scale inner coordinate first, then translate to get to frame coordinates
		
	instead of like this:
	
		xFame = (xInner + fScrollOffset.X())*fXScaleFactor; //translate inner coordinate first, then scale to get to frame coordinates
	
	when, for example, the ScrollContentLocationToFrameOrigin method takes a 
	location parameter in inner coordinates. 

	So in order to get the specified inner location to show up at the top-left 
	corner of the frame (0,0) in frame coordinates, (the job of 
	ScrollContentLocationToFrameOrigin), it needs to multiply the passed in 
	parameter by the scale factor. That is, requiring:
	
		0 = specified_value * fXScaleFactor + fScrollOffset.X()

	And solving for fScrollOffset.X(), means that the implementation of 
	ScrollContentLocationToFrameOrigin must be:
	
		fScrollOffset.X() = -specified_value * fXScaleFactor;

	The implementation code would have been more natural if the data members had 
	the transposed meaning or if the API was in terms of frame locations instead 
	of inner locations like so:

		0 = (specified_value + fScrollOffset.X())*fXScaleFactor
	 
	And solved for fScrollOffset.X() would have simply been:

		fScrollOffset.X() = -specified_value;

	Oh, well...be warned as you'll see several contrivances multiplying and 
	dividing by scale factors both in the CPanormama implementation and in 
	clients of ITransform. (Is this worth fixing? Well it would be if the 
	meaning of the API proved "wrong".)
	  
	For example, ScrollContentLocationToFrameOrigin expects its 'to' argument to 
	be in the inner coordinate system of the view with the outcome that the 
	location 'to' in the inner view be positioned at the origin of the frame
	coordinate systems, i.e. at the top-left corner of the view's frame. Since 
	the panorama data members are interpreted "in the wrong order", the 'to' 
	value must be multiplied internally by the scale before storing the result 
	in fScrollOffset.
	
	*/	

	virtual void UpdatePanoramaTransform(PMMatrix* transform) const;

//@}




/** @name Persistence */
//@{
public:
	/** Override to save perspective - default implementation is empty. */
	virtual void SavePerspective() const;

	/** Override to restore perspective - default implementation is empty. */
	virtual void RestorePerspective();
//@}

/** @name Scrolling */
//@{
	/** Override to change or augment default implementation */
	virtual void ScrollViewEdgeTo(const EdgeSpec& edgeSpec, const PBPMPoint& newCenter, bool16 bForceRedraw);
//@}

/** @name Implementation */
//@{
protected:


	/** Utility routine to compute the scale factor required to display a rectangular area, with a border. */
	virtual PMReal GetScaleToShowRect(const PMRect& r, const PMReal& whiteSpace) const;

	/** A ClassID, such as kScrollToMessage, kScrollByMessage, kScaleToMessage, or kScaleByMessage. See also IPanorama.h for information on PanoramaUpdateParams */
	virtual void DoNotify(ClassID messageID, const PanoramaUpdateParams& params) const;

	/** Adjust the given bounds rectangle, outside of which you'd like to autoscroll. */
	virtual void GetBoundsForAutoScroll(PMRect&) const;
	
	/** Override to constrain scrolling - default implementation is empty. */
	virtual PBPMPoint ConstrainTo(const PBPMPoint& value) const;

	/** Override to constrain scrolling - default implementation is empty. */
	virtual PBPMPoint ConstrainBy(const PBPMPoint& delta) const;

	virtual SysRgn SystemScroll(const SysPoint& sysDelta, bool16 bDoInval, GSysRect *bbox);

//@}

// ----- Object state
private:
	PMReal			fXScaleFactor; //zooming in increases these scale factors. That is, fXScaleFactor > 1 <==> 1 unit in content coordinates takes up more that 1 unit in frame coordinates 
	PMReal			fYScaleFactor;
	PMReal			fPreviousScaleFactor;
	PMPoint			fPreviousViewCenter;
	PMReal			fMinScaleFactor;	// Min and max allowable scale factor
	PMReal			fMaxScaleFactor;
	PMPoint			fScrollOffset;		//fScrollOffset is the location of the content origin in frame coordinates
	bool16			fPushPanoramaChangesIntoDrover;
	
	IPanorama*			fPrimaryPanorama;

	void DroverPreScroll();
	void DroverPostScroll();

	virtual PBPMPoint ScrollTo_(const PBPMPoint& to, bool16 forceRedraw, SysRgn InvalRgnCopy);
	virtual PBPMPoint ScrollBy_(const PBPMPoint& by, bool16 bForceRedraw, SysRgn InvalRgnCopy);
	virtual void SetScrollOffset_( PMPoint scrollBy);
	virtual void ScalePanorama_( const PMReal& xFactor, const PMReal& yFactor);


DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
