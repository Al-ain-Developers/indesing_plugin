//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IZoomWinCmdData.h $
//  
//  Owner: Michael_Burbidge
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
//  Data interface for the ZoomWinCmd.
//  
//========================================================================================

#pragma once
#ifndef __IZoomWinCmdData__
#define __IZoomWinCmdData__

class IWindow;

/**
   This interface is used to cache the data for kZoomToCmdBoss.

   One of the command data is the zoom direction(zoom in or zoom out),
   the other is the window that we operate on.
*/

class IZoomWinCmdData : public IPMUnknown {
public:

	/**
		Define enumerated ZoomDirection(kZoomOut = zoom out, kZoomIn = zoom in).
	*/

	enum ZoomDirection { kZoomOut, kZoomIn };
	
	/**
		Set the command data(window and zoom direction).

		@param win refers to the window we operate on.
		@param zoomDir refers to the zoom direction(zoom in or zoom out).
		@return void.
	*/

	virtual void Set(IWindow *win, const ZoomDirection& zoomDir) = 0;

	/**
		Get the window we operate on.

		@return IWindow, the window we operate on.
	*/

	virtual IWindow *GetWindow() const = 0;

	/**
		Get zoom direction.
		
		@return ZoomDirection, kZoomOut = zoom out, kZoomIn = zoom in.
	*/

	virtual ZoomDirection GetZoomDirection() const = 0;
};

#endif // __IZoomWinCmdData__
