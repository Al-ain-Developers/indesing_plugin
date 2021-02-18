//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDVOffscreenViewPortCache.h $
//  
//  Owner: rishik
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
#ifndef __IDVOffscreenViewPortCache__
#define __IDVOffscreenViewPortCache__

#include "IPMUnknown.h"
#include "GraphicsID.h"

class IControlView;
class IDVOffscreenPortData;
class PMRect;
class IGraphicsContext;

/**
 Interface for the offscreen view port cache. Manages a cached pair of offscreen ports, one for the foreground, 
 and another for the background. The purpose for these and their use by InDesign are described in the
 IOffscreenPortData interface.
 
 @see IDVOffscreenPortData
 */
class IDVOffscreenViewPortCache : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDVOFFSCREENVIEWPORTCACHE };

	/**
	 Queries for the background viewport. If one doesn't exist it will be created.
	 
	 nil indicates failure -- most likely from low memory
	 @param gc   IGraphicsContext *
	 @return the cached background viewport's IOffscreenPortData
	 @see IDVOffscreenPortData
	 */
	virtual IDVOffscreenPortData* QueryBackgroundViewPort (IGraphicsContext* gc) = 0;
	
	/**
	 Queries for the background viewport. If one doesn't exist it will be created.
	 
	 nil indicates failure -- most likely from low memory
	 @param view.   Used to determine the bounds and scale factor of the desired offscreen
	 @return the cached background viewport's IDVOffscreenPortData
	 @see IDVOffscreenPortData
	 */
	
	virtual IDVOffscreenPortData* QueryBackgroundViewPort (IControlView* view) = 0; 
		
				
	/**
	 Queries for the foreground viewport. If one doesn't exist it will be created.
	 
	 nil indicates failure -- most likely from low memory.
	
	 Special mode: if 'gc' is passed as nil, the function will simply return
	 the present cached foreground port, if any.  It will not create the port
	 if it doesn't exist already; nil is returned in this case but does not
	 indicate failure.  This is useful when trying to determine the current
	 state of the cache without affecting it.
	 
	 @param gc	The graphics context on which to base newly created port, or nil
	 @return the cached foreground viewport's IDVOffscreenPortData
	 @see IDVOffscreenPortData
	 */
	virtual IDVOffscreenPortData* QueryForegroundViewPort (IGraphicsContext* gc) = 0;
	
	/**
	 Queries for the foreground viewport. If one doesn't exist it will be created.
	 
	 nil indicates failure -- most likely from low memory.
	 
	 @param view.   Used to determine the bounds and scale factor of the desired offscreen
	 @return the cached foreground viewport's IOffscreenPortData
	 @see IDVOffscreenPortData
	 */
	
	virtual IDVOffscreenPortData* QueryForegroundViewPort (IControlView* view) = 0;

	/**
	 This tells the cache which controlview created the content in the 
	 offscreen.  It also increments the reference ID.  Users can check
	 the controlview against the front view for content validity.  Dynamic
	 users can check the control view and reference ID.  In dynamic situations
	 the reference ID will change during autoscroll, view % changes, etc.
	 The layout control view calls SetContentControlView every time the 
	 content changes, even if the control view pointer hasn't changed.
	 This increments the reference ID which uniquely indicates a new content
	 bitmap.
	 
	 This call does not bump the ref count on the control view. It only uses the pointer as an ID and not as a real pointer.
	 
	 @param iControlView	The content's control view
	 */
	virtual void SetContentControlView (IControlView* iControlView) = 0;
		
	/**
	 Returns the layout control view that the content represents.
	 
	 DO NOT USE the returned pointer as a valid control view. It is only an identifier.
	 
	 @return the layout control view
	 */
	virtual IControlView* GetContentControlView() const = 0;
	
	/** 
	 Gets the current reference ID. The reference ID increments every time someone sets the content control view. 
	
	 @return the current reference ID
	*/
	virtual int32 GetContentReferenceID() const = 0;
		
	/**
	 During low memory states our purge method will get called
	 The platform offscreen cache will release its reference to the cache.  The
	 next call to QueryPlatformOffscreen will attempt to create a new one
	 
	 @param level the purge level
	 */
	virtual void Purge (uint32 level) = 0;
	
};

#endif
