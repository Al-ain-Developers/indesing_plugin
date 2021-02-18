//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICustomPathStrokerData.h $
//  
//  Owner: Greg St. Pierre
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ICustomPathStrokerData__
#define __ICustomPathStrokerData__

#include "IPMUnknown.h"
#include "InstStrokeFillID.h"

/**
 Stores information about a custom (ie., user defined) path stroker.
 */

class ICustomPathStrokerData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICUSTOMPATHSTROKERDATA };

	/**
	 Gets the stroker's name

	 @param name OUT Set to the name of the path stroker on exit
	 */
	virtual void GetStrokerName(PMString &name) const = 0;

	/**
	 Sets the stroker's name

	 @param name IN Specifies the new name for the path stroker
	 */
	virtual void SetStrokerName(PMString const &name) = 0;

	/**
	 Gets the stroker's metadata class

	 @return Stroker's metadata class
	 */
	virtual ClassID GetMetadataClassID() const = 0;
};

#endif //!def __ICustomPathStrokerData__
