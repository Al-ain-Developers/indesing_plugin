//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IResizeWinCmdData.h $
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
//  Data interface for the ResizeWinCmd.
//  
//========================================================================================

#pragma once
#ifndef __IResizeWinCmdData__
#define __IResizeWinCmdData__

class IWindow;

/**
   This interface is used to cache the data for kResizeWinCmdBoss.

   The command data includes: 1) window that we operate on;
							  2) width of the window we resize to;
							  3) height of the window we resize to.
*/

class IResizeWinCmdData : public IPMUnknown {
public:

	/**
		Set the command data(window, width/height of window).

		@param win refers to the window we operate on.
		@param width refers to the width of the window we resize to.
		@param height refers to the height of the window we resize to.
		@return void.
	*/

	virtual void Set(IWindow *win, const SysCoord& width, const SysCoord& height) = 0;

	/**
		Get the window we operate on.

		@return IWindow, the window we operate on.
	*/

	virtual IWindow *GetWindow() const = 0;

	/**
		Get the window's dimension(width/height) which is passed out 
		through parameters(width/height).
		
		@param width pass out the width of the window we resize to.
		@param height pass out the height of the window we resize to.
		@return void.
	*/

	virtual void GetDimensions(SysCoord& width, SysCoord& height) const = 0;

	/**
		Get the delta of window's dimension which is passed out through 
		parameters(widthDelta/heightDelta). 

		@param widthDelta pass out the delta of window's width which refers to (newWidth - oldWidth).
		@param heightDelta pass out the delta of window's height which refers to (newHeight - oldHeight).
		@return void.
	*/

	virtual void GetDimensionsDelta( SysCoord& widthDelta, SysCoord& heightDelta) const = 0;
};


#endif // __IResizeWinCmdData__
