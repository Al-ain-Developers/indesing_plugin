//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrawingToolPrefs.h $
//  
//  Owner: Lin Xia
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
#ifndef __IDrawingToolPrefs__
#define __IDrawingToolPrefs__

#include "IPMUnknown.h"

/** An interface class for DrawingTool Preferences */

class IDrawingToolPrefs : public IPMUnknown
{
public:	
	
	/**
		Set method for default object width.
		@param newWidth IN default object width.
	*/
	virtual void SetWidth(const PMReal newWidth) = 0;
	/**
		Get method for default object width.
		@return default object width.
	*/
	virtual const PMReal GetWidth() = 0;

	/**
		Set method for default object height.
		@param newHeight IN default object height.
	*/
	virtual void SetHeight(const PMReal newHeight) = 0;
	/**
		Get method for default object height.
		@return default object height.
	*/
	virtual const PMReal GetHeight() = 0;

};

#endif
