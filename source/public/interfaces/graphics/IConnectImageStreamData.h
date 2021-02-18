//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IConnectImageStreamData.h $
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
#ifndef __IConnectImageStreamData__
#define __IConnectImageStreamData__

#include "IPMUnknown.h"

class IImageStream;

/**
 Interface used to connect the various segments of the image stream created and 
 managed by the image stream manager
 
 @see IImageStreamManager
 @see IImageStream
 */
class IConnectImageStreamData : public IPMUnknown
{
public:
	/**
	 Sets the next segment in the image stream.
	 
	 Note: This does not cause an AddRef on the iImageStream
	 
	 @param iImageStream		The next segment in the stream
	 */
	virtual void SetNextSegment (IImageStream* iImageStream) = 0;
	
	/**
	 Queries for the next segment in the image stream
	 
	 Note: This does cause an AddRef on the iImageStream
	 
	 @return the next segment in the stream
	 */
	virtual IImageStream* QueryNextSegment() = 0;
};

#endif
