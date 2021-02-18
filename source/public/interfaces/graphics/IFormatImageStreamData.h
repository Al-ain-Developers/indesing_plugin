//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IFormatImageStreamData.h $
//  
//  Owner: jargast
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
#ifndef __IFormatImageStreamData__
#define __IFormatImageStreamData__

#include "IPMUnknown.h"

class IImageReadFormat;

/**
 Data interface for the IFormatImageStream segment of the IImageStreamManager.
 This segment is used to read the native data from the source image.

 @see IImageReadFormat
 @see IImageStreamManager::SetFirstImageStreamSegment
 @see kReadFormatImageStreamBoss
 */
class IFormatImageStreamData : public IPMUnknown
{
public:
	/**
	 Sets the IImageReadFormat to use to read native data from the source image.
	 
	 Note: The IImageReadFormat is *not* AddRef'd and must remain valid for the
	 lifetime of this object.
	 
	 @param iImageReadFormat	IN The IImageReadFormat to use to read the native data
	 */
	virtual void SetImageReadFormat (IImageReadFormat* iImageReadFormat) = 0;
	
	/**
	 Queries for the IImageReadFormat stored by this interface. The returned
	 interface is AddRef'd and must be released by the caller.
	 
	 @return The IImageReadFormat stored by this interface
	 */
	virtual IImageReadFormat* QueryImageReadFormat () = 0;
	
};

#endif
