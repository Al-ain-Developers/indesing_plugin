//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IUIColorSpec.h $
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
#ifndef __IUIColorSpec_h__
#define __IUIColorSpec_h__

#include "IPMUnknown.h"
#include "widgetid.h"

class RealAGMColor;
//========================================================================================
// CLASS IUIColorSpec
//========================================================================================

class IUIColorSpec : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IUICOLORSPEC };
	// Get and Set the color ID. This is an ID that can be used to look up the
	// corresponding interface color in InterfaceColorDefines.h.

	/////////////
	// TEXT COLOR
	/** Set the color for this text object
		@param interfaceColorId - The color to use (by index) 
	*/
	virtual void		SetTextColorID(const int32& interfaceColorId) = 0;
	
	/** Set the color for this text object (using a RealAGMColor)
		@param newColor - The color to use 
	*/
	virtual void		SetTextColorAGM(const RealAGMColor &newColor) = 0;

	/** Get the color for this text object
		@return Index of interface color to use
	*/
	virtual int32		GetTextColorID() const = 0;

	/** Get the color for this text object
		@return color to use
	*/
	virtual RealAGMColor	GetTextColorAGM() const = 0;

	/** Set the color for this text object when it is selected
		@param interfaceColorId - The color to use (by index) 
	*/
	virtual void		SetTextHiliteColorID(const int32& interfaceColorId) = 0;

	/** Set the color for this text when it's selected (using a RealAGMColor)
		@param newColor - The color to use 
	*/
	virtual void		SetTextHiliteColorAGM(const RealAGMColor &newColor) = 0;

	/** Get the color for this text object when it is selected
		@return Index of interface color to use
	*/
	virtual int32		GetTextHiliteColorID() const = 0;
	
		/** Get the color for this text when it's selected (using a RealAGMColor)
		@return color to use
	*/
	virtual RealAGMColor	GetTextHiliteColorAGM() const = 0;


	///////////////////
	// BACKGROUND COLOR
	/** Set the background color for this text object
		@param interfaceColorId - The color to use (by index) 
	*/
	virtual void		SetBackgroundColorID(const int32& interfaceColorId) = 0;
	
	/** Set the color for this text object's background (using a RealAGMColor)
		@param newColor - The color to use 
	*/
	virtual void		SetTextBackgroundColorAGM(const RealAGMColor &newColor) = 0;

	/** Get the background color for this text object
		@return Index of interface color to use
	*/
	virtual int32		GetBackgroundColorID() const = 0;

	/** Get the color for this text object's background
		@return color to use
	*/
	virtual RealAGMColor	GetTextBackgroundColorAGM() const = 0;

	/** Set the background color for this text object when it is selected
		@param interfaceColorId - The color to use (by index) 
	*/
	virtual void		SetBackgroundHiliteColorID(const int32& interfaceColorId) = 0;

	/** Set the color for this text's background when it's selected (using a RealAGMColor)
		@param newColor - The color to use 
	*/
	virtual void		SetTextBackgroundHiliteColorAGM(const RealAGMColor &newColor) = 0;

	/** Get the background color for this text object when it is selected
		@return Index of interface color to use
	*/
	virtual int32		GetBackgroundHiliteColorID() const = 0;
	
	/** Get the color for this text's background when it's selected (using a RealAGMColor)
		@return color to use
	*/
	virtual RealAGMColor	GetTextBackgroundHiliteColorAGM() const = 0;
};

#endif // __IUIColorSpec_h__
