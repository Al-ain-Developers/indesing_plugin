//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRegPolyPrefsCmdData.h $
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
#ifndef __IRegPolyPrefsCmdData__
#define __IRegPolyPrefsCmdData__

#include "IPMUnknown.h"
#include "RegPolyID.h"

class IDataBase;

/**
 Simple data interface for regular polygon preferences commands.
 
 Regular polygon preferences include the number of sides and the star inset.
 
 @see IRegPolyPrefs
 */
class IRegPolyPrefsCmdData : public IPMUnknown
{
public:
	/**
	 Sets the preferences to use for regular polygons.
	 
	 @param numSides		IN The number of sides for the polygon
	 @param starInset		IN The star inset for the polygon
	 */
	virtual void Set(	const	int32& numSides,
						const	int32& starInset) = 0;
						
	/**
	 Retrieves the number of sides to use for regular polygons.
	 
	 @return The number of sides
	 */
	virtual const int32& GetNumSides() const = 0;
	
	/**
	 Retrieves the star inset to use for regular polygons.
	 
	 @return The star inset
	 */
	virtual const int32& GetStarInset() const = 0;
};


#endif // __IRegPolyPrefsCmdData__
