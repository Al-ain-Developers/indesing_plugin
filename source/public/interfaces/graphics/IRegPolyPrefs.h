//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRegPolyPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __IRegPolyPrefs__
#define __IRegPolyPrefs__

const int32 kMinPolygonSides = 3;
const int32 kMaxPolygonSides = 100;
const int32 kMinPolygonInset = 0;
const int32 kMaxPolygonInset = 100;

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "GenericID.h"

/**
 Simple data interface for regular polygon preferences.
 
 Regular polygon preferences include the number of sides and the star inset.
 
 @see IRegPolyPrefsCmdData
 */
class IRegPolyPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IREGPOLYPREFERENCES };

	/**
	 Sets the number of sides to use for regular polygons.
	 
	 @param numSides		IN The default number of sides
	 */
	virtual void SetNumSides(const int32& numSides) = 0;
	
	/**
	 Retrieves the number of sides to use for regular polygons.
	 
	 @return The number of sides
	 */
	virtual int32 GetNumSides() = 0;

	/**
	 Sets the star inset to use for regular polygons.
	 
	 @param numSides		IN The default star inset
	 */
	virtual void SetStarInset(const int32& starInset) = 0;
	
	/**
	 Retrieves the star inset to use for regular polygons.
	 
	 @return The star inset
	 */
	virtual int32 GetStarInset() = 0;

};

#endif	// __ODFRC__
#endif	// __IRegPolyPrefs__

