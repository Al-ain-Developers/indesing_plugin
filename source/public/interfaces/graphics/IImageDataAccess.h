//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageDataAccess.h $
//  
//  Owner: Dave Stephens
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
//  Purpose:
//  Each kImageItem contains a full resolution link and an embedded low resolution
//  proxy.  This interface is used to set or obtain the UID of this low resolution proxy.
//  
//========================================================================================

#pragma once
#ifndef __IImageDataAccess__
#define __IImageDataAccess__

#include "IPMUnknown.h"
#include "ImageID.h"

/** This interface stores the UID of the proxy image and lives off any boss that needs
a proxy image such as the kImageItem boss.
*/
class IImageDataAccess : public IPMUnknown
{
public:
	/** default interface IID */
	enum { kDefaultIID = IID_IIMAGEDATAACCESS };

	/** Set the UID of the proxy image for this boss.
		@param uid - IN: proxy UID
	*/
	virtual void SetLowResImageUID(UID uid) = 0;

	/** @return Retrieve the UID of the proxy image.
	*/
	virtual UID  GetLowResImageUID() const = 0;
		
};

#endif
