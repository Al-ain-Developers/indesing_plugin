//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IOffscreenPortData.h $
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
//  This is the OffscreenPort specific interface attached to offscreen view ports.
//  It is a shell over the AGM API for setting up offscreen ports.
//  In order to use an offscreen port, you have to create an IPlatformBitmap and
//  then load that into the port via SetTargetBitmap. This is analogous to setting
//  the targetwindow on a window view port.
//  
//========================================================================================

#pragma once
#ifndef __IOffscreenPortData__
#define __IOffscreenPortData__

#include "IPMUnknown.h"
#include "GraphicsID.h"
#include "HelperInterface.h"

#include "IDVOffscreenPortData.h"

class PMMatrix;
class IPlatformOffscreen;

/** IOffscreenPortData is an interface for creating and updating platform offscreens.

	InDesign uses platform offscreen for two reasons: 1) to reduce screen flicker;
	2) as a cache to avoid having to instantiate an item on a page in order to ask it to draw.

	On Mac OS X, the screen flicker case is handled by the OS so we don't need platform
	offscreens for that case.  However, the optimizations that reason 2 provides forces us
	to continue using offscreens.

	This interface has methods to maintain 1 or more offscreens as used by the IOffscreenViewPortCache. 
	The IOffscreenViewPortCache maintains two IOffscreenPortData ptrs: 1 for the background and 1 for the foreground.
	In the case	of the layout window, the background offscreen is the contents of the window/document in an 
	unselected state.  The foreground is used as a composite.  That is, if an update event
	occurs, we do the following:
	1.  Make sure the background offscreen is up to date.  If nobody has called 
	ILayoutController->InvalidateContent(), then there is nothing to do in this step.
	Typically, InvalidateContent() gets called by a document observer after a command has
	been processed which changes a page item or the layout in some way.
	2.  Copy the area to update from the background to the foreground.
	3.  Draw the selection into the foreground.
	4.  Draw the foreground to the window.

	With the introduction of Mac OS X, the foreground buffer is not needed.  Rather, the OS provided
	back buffer can serve the purpose of the foreground/composite buffer.  Hence, we need two different
	update methods in the IOffscreenPortData interface.  One (the original UpdateTargetBitmap()) which
	allocates a new platform offscreen if the bounds are larger than the current one, and another,
	UpdateTargetBitmapIfDiffSize(), which allocates a new platform offscreen if the bounds are different.

	History:  
	
	Prior to InDesign 3.0, there was 1 background and 1 foreground offscreen shared
	among all layout windows.  As a result, if you had multiple documents open, switching between
	documents/windows caused a performance hit as we updated the contents of the bitmap.  In addition,
	the size of the offscreen was the size of the largest window.  Also, the IOffscreenViewPortCache
	interface lived on the Session boss since it was not associated with any window.

	For InDesign 3.0, I wanted to provide an offscreen per layout window.  Hence, I added
	the IOffscreenViewPortCache to kLayoutWidgetBoss.  As a result, we no longer need to have the 
	background offscreen be the size of the largest window.  However, since the foreground offscreen
	is simply a compositing buffer, I did not want to add a foreground offscreen per window.  Therefore,
	the IOffscreenViewPortCache::QueryForegroundViewPort() implementation on the layout boss will simply
	query for the foreground viewport on the session boss.  And, when it is time to update it due to
	a window resize, then the original UpdateTargetBitmap() function will be called.
	
	@see IOffscreenViewPortCache (now IDVOffscreenViewPortCache)
	*/

typedef IDVOffscreenPortData IOffscreenPortData;

#endif
