//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IWindowPort.h $
//  
//  Owner: jack_kirstein
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
#ifndef __IWINDOWPORT__
#define __IWINDOWPORT__
#include "PMRect.h"

/**
 IWindowPort is a viewport interface which defines some generic operations
 which can be done to a window, or which require a window (ie, GlobalToLocal).
 
 Note: This interface dates back to the beginning of Shuksan (it was called 
 ICanvas originally), and should be re-examined.
 
 @see IWindow
 */
class IWindowPort : public IPMUnknown 
{
	public:
		/**
		 Invalidates the specified rectangular area of the window (ie., adds
		 it to the system update region).
		 
		 Note: Does not erase the specified rectangle.
		 
		 @param invalidRect		IN The rectangle to invalidate
		 */
		virtual void InvalRect(const PMRect& invalidRect) = 0;
		
		/**
		 Validates the specified rectangular area of the window (ie. removes
		 it from the system update region).
		 
		 @param goodRect		IN The rectangle to validate
		 */
		virtual void ValidRect(const PMRect& goodRect) = 0; 
		
		/**
		 Invalidates the specified region of the window (ie., adds it to the
		 system update region).
		 
		 Note: Does not erase the specified region.
		 
		 @param invalidRgn		IN The region to invalidate
		 */
		virtual void InvalRgn(SysRgn invalidRgn) = 0;

		/**
		 Validates the specified region of the window (ie., removes it from the
		 system update region).
		 
		 @param goodRgn			IN The region to validate
		 */
		virtual void ValidRgn(SysRgn goodRgn) = 0;
		
		/**
		 Invalidates the entire window (ie., adds it to the system update 
		 region).
		 
		 Note: Does not erase.
		 */
		virtual void InvalAll() = 0;
		
		/**
		 Validates the entire window (ie., removes it from the system update 
		 region).
		 
		 Note: Does not erase.
		 */
		virtual void ValidAll() = 0;
		
		/**
		 Converts the specified rectangle from global (screen) coordinates to
		 local (window) coordinates.
		 
		 @param convertRect		IN The rectangle (in global coordinates) to convert
		 @return The rectangle in local coordinates
		 */
		virtual PMRect GlobalToLocal(const PMRect& convertRect) = 0;

		/**
		 Converts the specified point from global (screen) coordinates to local
		 (window) coordinates.
		 
		 @param convertPoint	IN The point (in global coordinates) to convert
		 @return The point in local coordinates
		 */
		virtual PMPoint GlobalToLocal(const PMPoint& convertPoint) = 0;

		/**
		 Converts the specified rectangle from local (window) coordinates to
		 global (screen) coordinates.
		 
		 @param convertRect		IN The rectangle (in local coordinates) to convert
		 @return The rectangle in global coordinates
		 */
		virtual PMRect LocalToGlobal(const PMRect& convertRect) = 0;

		/**
		 Converts the specified point from local (window) coordinates to global
		 (screen) coordinates.
		 
		 @param convertPoint		IN The point (in local coordinates) to convert
		 @return The point in global coordinates
		 */
		virtual PMPoint LocalToGlobal(const PMPoint& convertPoint) = 0;

		/**
		 Invalidates the specified rectangular area of the window (ie., adds
		 it to the system update region).
		 
		 Note: Does not erase the specified rectangle.
		 
		 @param invalidRect		IN The rectangle to invalidate
		 */
		virtual void InvalRect(const SysRect& invalidRect) = 0;

		/**
		 Validates the specified rectangular area of the window (ie. removes
		 it from the system update region).
		 
		 @param goodRect		IN The rectangle to validate
		 */
		virtual void ValidRect(const SysRect& goodRect) = 0;

		/**
		 Converts the specified rectangle from global (screen) coordinates to
		 local (window) coordinates.
		 
		 @param convertRect		IN The rectangle (in global coordinates) to convert
		 @return The rectangle in local coordinates
		 */
		virtual SysRect GlobalToLocal(const SysRect& convertRect) = 0;

		/**
		 Converts the specified point from global (screen) coordinates to local
		 (window) coordinates.
		 
		 @param convertPoint	IN The point (in global coordinates) to convert
		 @return The point in local coordinates
		 */
		virtual SysPoint GlobalToLocal(const SysPoint& convertPoint) = 0;

		/**
		 Converts the specified rectangle from local (window) coordinates to
		 global (screen) coordinates.
		 
		 @param convertRect		IN The rectangle (in local coordinates) to convert
		 @return The rectangle in global coordinates
		 */
		virtual SysRect LocalToGlobal(const SysRect& convertRect) = 0;

		/**
		 Converts the specified point from local (window) coordinates to global
		 (screen) coordinates.
		 
		 @param convertPoint		IN The point (in local coordinates) to convert
		 @return The point in global coordinates
		 */
		virtual SysPoint LocalToGlobal(const SysPoint& convertPoint) = 0;
};

#endif
