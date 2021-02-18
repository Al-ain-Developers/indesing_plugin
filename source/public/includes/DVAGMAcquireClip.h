//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DVAGMAcquireClip.h $
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
#ifndef __DVAGMAcquireClip__
#define __DVAGMAcquireClip__

class IControlView;
class IViewPort;

/**
 An object that sets up the clip for a view or viewport. To be
 used when you want to draw using AGM. This is usually not used
 standalone but as a template parameter to
 AGMGraphicsContextWith.
 
 @see AGMGraphicsContext.h
 */
class PUBLIC_DECL DVAGMAcquireClip
{
	public:
		/**
		 Constructs a clipping acquisition object based on a viewport, a control 
		 view, and an optional sys region.
		 
		 @param vp			The viewport to base the clipping on
		 @param view		The control view to base the clipping on
		 @param clipRgn		The clipping region to use
		 */
		DVAGMAcquireClip(IViewPort* vp, IControlView* view, SysRgn clipRgn = nil);
	
		/**
		 Constructs a clipping acquisition object based on a viewport and an 
		 optional sys region.
		 
		 @param vp			The viewport to base the clipping on
		 @param clipRgn		The clipping region to use
		 */
		DVAGMAcquireClip(IViewPort* vp, SysRgn clipRgn);

		/**
		 Destructor
		 */
		~DVAGMAcquireClip();
		
		/**
		 Gets the clipping region for this context

		 @return The clip region
		*/
		SysRgn			GetClip() const;
		
		/**
		 Gets the clipping region for this context, adjusted for the origin

		 @return The origin-adjusted clip region
		*/
		SysRgn			GetOriginAdjustedClip() const;

		/**
		 Sets up the platform clipping
		 */
		void			SetupPlatformClip();
		
		/** 
		 Tears down the platform clipping
		 */
		void			TearDownPlatformClip();

	private:
		void			SetPlatformClipRgnFromView(IControlView* view, SysRgn clipRgn);
		void			SetPlatformClipRgn(SysRgn clipRgn);
		void			CommonInit();

	private:
		IViewPort *					fVP;
		IControlView *				fView;
		SysRgn						fClipRgn;
		SysRgn						fPrevClipRgn;
		bool16						fClipHasBeenApplied;
		bool16						fClipRgnWasCreated;	// i.e. does this object own the fClipRgn?
};

#endif
