//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMonitorInfo.h $
//  
//  Owner: Stacy Molitor
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
//  Core interface for getting information about the monitor.
//  
//========================================================================================

#pragma once
#ifndef __IMONITORINFO__
#define __IMONITORINFO__

#include "ShuksanID.h"

class IControlView;

class IMonitorInfo : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IMONITORINFO};
	/**
		Get rect for the main screen bounds
	
		@return GSysRect OUT screen bounds
	*/
	virtual GSysRect	GetMainScreenRect() const = 0; 
	
	/**
		Get rect for the screen which contains the passed in point.
	
		@param refPoint IN The point in question
		@return GSysRect OUT screen bounds
	*/
	virtual GSysRect	GetScreenRect( const SysPoint& refPoint ) const= 0;
	
	/**
		Calculate the effective area of the screen in which to position the 
		docking palettes.  On the mac, this is the main screen minus the menubar
		To find the area within the docking palettes, call GetGlobalDocWindowAreaRect()
	
		@return GSysRect OUT palette area bounds
	*/
	virtual GSysRect	GetPaletteAreaRect() const = 0;

	/**
		Calculate the effective area of the screen which contains the passed in point
		in which to position the docking palettes.  
		On the mac, this is the removes the menubar and dockbar if present
	
		@param refPoint IN The point in question
		@return GSysRect OUT palette area bounds
	*/
	virtual GSysRect	GetPaletteAreaRect(const SysPoint& refPoint) const = 0;
	
	/**
		Returns the area of the screen inside the app window and all docked palettes(toolbars, TabStation, etc.)
	
		@return GSysRect OUT client area bounds
	*/
	virtual GSysRect	GetClientAreaRect() const = 0;

	/**
		Calculate the effective area of the screen in which to position the 
		document windows.  This takes into account Toolbars docked to the app frame
		NOTE: This area encompasses the entire main monitor minus:
			Top: 	the Menubar height (Macintosh) 
			Bottom:	a small constant
			Right:	a small constant
			Additional space for the Dock (Macintosh) 
	
		@return GSysRect OUT doc window area bounds
	*/
	virtual GSysRect	GetGlobalDocWindowAreaRect() const = 0;
	
	/**
		Calculate the effective area of the app frame window in which to position the 
		document windows.  This is the area within the app window and all docked palettes(toolbars, TabStation)
		NOTE: This area encompasses the entire client area of the frame window.
			Macintosh - Main screen minus the menubar and dock (Same as GetPaletteAreaRect())
			Windows - The MDI client area of the application.

		@return SysRect OUT local doc window area bounds. NOTE: Rect is returned in Local Coordinates of the MDI client window(i.e. TopLeft will always be at 0,0)
	*/
	virtual SysRect		GetLocalDocWindowAreaRect() const = 0;
	
	/**
		INTERNAL USE ONLY.
		Set the size of the doc window area.  This should only be called by the PaletteMgr after sizing palettes.

	
		@param newDocWindowRect IN new document area bounds
	*/
	virtual	void		SetDocWindowAreaRect(const GSysRect& newDocWindowRect) = 0;

	/**
		Returns the bounds of the screen that best encloses the passed-in rectangle
	
		@param refRect IN the rectangle to test
		@return GSysRect OUT best screen bounds
	*/
	virtual GSysRect	GetBestScreenRect( const SysRect& refRect ) const = 0;

	/**
		Returns the number of connected and active monitors
	
		@return int32 OUT number of monitors
	*/
	virtual int32	GetNumberOfMonitors() const = 0;
	
	/**
		Returns the number of pixels per inch of the main monitor
		@param honorUserInterfacePrefs [IN] If true, then look at the IUserInterfacePreferences::GetUseCustomMonitorResolution() function.
			If it returns true, then return IUserInterfacePreferences::GetCustomMonitorResolution(). Otherwise, use system API calls to
			determine the resolution.
	 */
	virtual PMReal GetMainScreenPixelsPerInch(bool32 honorUserInterfacePrefs = kTrue) const = 0;

	/**
	 Returns the number of pixels per inch for the screen which contains the passed in point.
	 
	 @param refPoint IN The point in question
	 @param honorUserInterfacePrefs [IN] If true, then look at the IUserInterfacePreferences::GetUseCustomMonitorResolution() function.
		If it returns true, then return IUserInterfacePreferences::GetCustomMonitorResolution(). Otherwise, use system API calls to
		determine the resolution.
	 @return The number of pixels per inch
	 */
	virtual PMReal GetScreenPixelsPerInch(const SysPoint& refPoint, bool32 honorUserInterfacePrefs = kTrue) const = 0;

	/**
	 Returns the number of pixels per inch for the screen which contains the center point of the
	 passed in view.
	 
	 @param view IN The view in question
	 @param honorUserInterfacePrefs [IN] If true, then look at the IUserInterfacePreferences::GetUseCustomMonitorResolution() function.
		 If it returns true, then return IUserInterfacePreferences::GetCustomMonitorResolution(). Otherwise, use system API calls to
		 determine the resolution.
	 @return The number of pixels per inch
	 
	 */
	virtual PMReal GetScreenPixelsPerInch(const IControlView* view, bool32 honorUserInterfacePrefs = kTrue) const = 0;
};


#endif // __IMONITORINFO__
