//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageFormatManager.h $
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
//  
//  IImageFormatManager is a bottleneck interface that manages requests
//  to find a particular Read or Write format object based on the input criteria.
//  
//========================================================================================

#pragma once
#ifndef __IImageFormatManager__
#define __IImageFormatManager__

#include "IPMUnknown.h"

class IImageReadFormat;
class IImageWriteFormat;
class IPMStream;

/** This interface is used to iterate over registered kImageWriteFormatService(s) and
	kImageReadFormatService(s) to obtain a pointer to a IImageWriteFormat or
	IImageWriteFormat respectively.
	@see IK2ServiceRegistry, IK2ServiceProvider, IImageReadFormat, IImageWriteFormat
*/
class IImageFormatManager : public IPMUnknown
{
public:
	/** 
		@param iPMStream - source stream
		@return Return the corresponding IImageReadFormat that can read 
			the iPMStream.  Return nil if not found.
	*/
	virtual IImageReadFormat* QueryImageReadFormat (IPMStream* iPMStream) = 0;
		
	/** @return Return the default image format as specified in the preferences
	*/
	virtual IImageWriteFormat* QueryDefaultImageWriteFormat() = 0;	
};

#endif
