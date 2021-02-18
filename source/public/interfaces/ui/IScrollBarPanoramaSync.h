//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IScrollBarPanoramaSync.h $
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
#ifndef __ISCROLLBARPANORAMASYNC__
#define __ISCROLLBARPANORAMASYNC__

//========================================================================================
// Forward declarations
//========================================================================================

class IControlView;
class ICounterControlData;
class IPanorama;

//========================================================================================
// CLASS IScrollBarPanoramaSync
/** Interface used to keep a panorama synced with the scrollbar widget(s) controlling it.

		An IScrollBarPanoramaSync implementation is combined with an IObserver implementation,
		as in kScrollBarPanoramaSyncBoss or kGridScrollBarPanoramaSyncBoss.
		
		@see IPanorama
*/
//========================================================================================

class IScrollBarPanoramaSync : public IPMUnknown
{
public:
	/** Initialize the interface, and attach the associated observer to the panorama, window and scroll bar(s).

		@param scrollBarX IN the horizontal scroll bar view
		@param scrollBarY IN the vertical scroll bar view
		@param panorama IN the panorama to be scrolled
		@param bInhibitCentering IN if true, inhibit centering the panorama as it grows or shrinks.
	*/
	virtual void		Init(IControlView* scrollBarX, IControlView* scrollBarY,
							 IPanorama* panorama, bool16 bInhibitCentering = kFalse) = 0;

public:
	/** Adjust the scroll bars and panorama after the size of the panorama has changed. */
	virtual void		SizeChanged() = 0;

	/** Update the scroll bars to match the panorama (after a resize). 
			Includes enabling and disabling the scroll bars as necessary if the entire panorama becomes visible.
	*/
	virtual void		UpdateScrollBars() = 0;

	/** Update the panorama to match the scroll bars.
		@param isVertical IN scroll vertically or horizontally
		@param scrollDelta IN how much to scroll
	*/
	virtual void 		UpdatePanorama(bool16 isVertical, int32 scrollDelta) = 0;

// ----- Accessors
public:
	/** Get the horizontal scroll bar. */
	virtual ICounterControlData*	GetScrollBarX() const = 0;
	/** Get the vertical scroll bar. */
	virtual ICounterControlData*	GetScrollBarY() const = 0;
	/** Get the panorama. */
	virtual IPanorama*				GetPanorama() const = 0;
};

#endif
