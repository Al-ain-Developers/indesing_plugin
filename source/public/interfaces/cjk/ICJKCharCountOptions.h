//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKCharCountOptions.h $
//  
//  Owner: Heath Lynn
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
//  Purpose: Aaggregated on a Text frames kMultiColumnItemBoss to describe the 
//  items character count options. 
//  
//========================================================================================

#pragma once
#ifndef __ICJKCJKCharCountOptions__
#define __ICJKCJKCharCountOptions__

#include "IPMUnknown.h"

#include "CJKGridID.h"

/** ICJKCharCountOptions is 
*/
class ICJKCharCountOptions : public IPMUnknown
{
public:

	//---------------------------------------
	//	enumerations
	//---------------------------------------

	enum { kDefaultIID = IID_ICJKCHARCOUNTOPTIONS };
	
	enum Location
	{
		kMixed = -1,	// Indicates mixed mode when used as command data.
		kNone,			// Turns off character count
		kLeft,
		kTop,
		kRight,
		kBottom
	};
	
	//---------------------------------------
	//	Get and Set Methods
	//---------------------------------------

	/**	Sets the location of the character count.
		@param  IN
	*/
	virtual void SetLocation( ICJKCharCountOptions::Location location ) =0;
	
	/**	Returns the location of the character count.
		@return ICJKCharCountOptions::Location for the character count.
	*/
	virtual ICJKCharCountOptions::Location GetLocation() const = 0;
	
	/** Sets the point size of the character count.
		@param size IN The new size of the character count.  
		A negative point size indicates mixed mode when used as command data.
	*/
	virtual void SetTextSize(const PMReal & size) = 0;

	/**  Returns the point size of the character count.
		@return character count size in points.
	*/
	virtual PMReal GetTextSize() const = 0;
	
	/** Copies from the source ICJKCharCountOptions.
		@param source IN The char count options to copy.  
		@param doDirty IN Should the object call dirty when copying data.
	*/
	virtual void CopyFrom(ICJKCharCountOptions *source, bool16 doDirty = kTrue) = 0;
};

#endif

