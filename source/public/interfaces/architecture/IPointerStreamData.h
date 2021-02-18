//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPointerStreamData.h $
//  
//  Owner: robin briggs
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
//  Data interface for memory-based streams.
//  
//  Streams are usually accessed via the helper functions in StreamUtils: 
//  you probably will not need direct access to this interface.
//  
//========================================================================================

#pragma once
#ifndef __IPointerStreamData__
#define __IPointerStreamData__

#include "IPMUnknown.h"
#include "ShuksanID.h"

/** Data interface for controlling a stream that writes out to memory.
	Contains a buffer and a length.
*/
class IPointerStreamData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPOINTERSTREAMDATA };

		/** Set the member values for the interface.
			@param buffer	pointer to the buffer to use
			@param length	size of the buffer in bytes
		*/
		virtual void Set(void *buffer, size_t length) = 0;
		
		/** Get the pointer (returns what it was last set to)
			@return pointer to the buffer
		*/
		virtual void *GetBuffer() const = 0;
		
		/** Get the buffer length
			@return length of the buffer in bytes.
		*/
		virtual size_t GetLength() const = 0;
};


#endif // __IPointerStreamData__
