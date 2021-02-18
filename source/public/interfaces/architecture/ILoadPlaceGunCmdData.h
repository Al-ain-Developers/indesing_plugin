//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILoadPlaceGunCmdData.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __ILoadPlaceGunCmdData__
#define __ILoadPlaceGunCmdData__

#include "IPMUnknown.h"
#include "IPlaceGun.h"
#include "OpenPlaceID.h"

/** Interface to hold data for LoadPlaceGunCmd
*/
class ILoadPlaceGunCmdData : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_ILOADPLACEGUNCMDDATA };

	/** Set where to load the item in the list
		@param where IN where to load the item in the place gun - usually the back, but can be the front in some cases.
	*/
	virtual void SetPlaceGunLoadLocation(IPlaceGun::PlaceGunLocation where) = 0;

	/** Get where to load the item in the list
		@return where to load the item in the place gun
	*/
	virtual IPlaceGun::PlaceGunLocation GetPlaceGunLoadLocation() const = 0;
};

#endif
