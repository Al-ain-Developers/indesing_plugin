//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IOversetInformationExchange.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IOversetInformationExchange__
#define __IOversetInformationExchange__

#include "GalleyInfoID.h"
#include "IPMUnknown.h"

class IFrameList;

/** An interface that is used to exchange information about which frame constitutes the start 
	of overset text. It is expected that someone who want's to use this will implement a service
	and that an implementation of this interface will be provided in the service providers
	boss. At proper times this interface will be called to ask which frame the overset text
	starts on. This interface and service is provide so that third parties can add a overset
	text frame and the internal InCopy code will respect this frame for text statistics calculations.
	@author Kevin Van Wiel
*/
class IOversetInformationExchange : public IPMUnknown
{
public:
	/** Standard enum to for use with GetDefaultIID() method.
	*/
	enum { kDefaultIID = IID_IOVERSETINFORMATIONEXCHANGE };

	
	/** 	Return the index of the first frame in the frame list to be considered overset. It is
			expected that every frame after that frame will be considered overset as well. If there
			is no overset frame present it is expected that this will return -1.
			@param frameList a pointer to the frameList we are interested in getting an index from
			@return either an index of the first overset frame or -1 if there is no overset frame.
	*/
	virtual	int32 FirstOversetFrameIndex(IFrameList *frameList) = 0;
};


#endif // __IOversetInformationExchange__
