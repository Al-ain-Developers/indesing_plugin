//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IMemoryStreamData.h $
//  
//  Owner: Michael Martz
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
//  Data interface for attaching an IXferBytes to a stream. 
//  
//  Streams are usually accessed via the helper functions in StreamUtils: 
//  you probably will not need direct access to this interface.
//  
//  When using the memory stream objects, it is typical to use a MemXferBytes object
//  as the underlying xferbytes. However, it is not necessary. Any xferBytes could be used
//  as long as it is self contained (initializes within its constructor.
//  
//========================================================================================

#pragma once
#ifndef _IMemoryStreamData_
#define _IMemoryStreamData_

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IXferBytes;

/** Data interface for controlling memory-based streams
	@see StreamUtil 
	@ingroup arch_db
*/
class IMemoryStreamData : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IMEMORYSTREAMDATA };
		

	/**
	   Set the stream's associated XferBytes object.
	   If the XferBytes object was dynamically allocated, responsibility for its lifetime may be
	   assigned to IMemoryStreamData.
	   @param underlyingXferBytes IN A pointer to the XferBytes object.
	   @param takeOwnership IN kTrue if IMemoryStreamData should take ownership of the XferBytes object, kFalse if not.
	 */
		virtual void 			Set(IXferBytes* underlyingXferBytes, bool16 takeOwnership = kFalse) = 0;

	/**
	   Return a pointer to the associated XferBytes object.
	   @return A pointer to the current XferBytes object, or nil.
	 */
		virtual IXferBytes* 	GetXferBytes() const = 0;

	/**
	   Determine whether we are responsible for the lifetime of the current XferBytes object, if any.
	   @return kTrue if we are responsible, kFalse if we are not (or if there is no associated XferBytes object).
	 */
		virtual bool16			IsOwnedXferBytes() const = 0;
	};


#endif // _IMemoryStreamData_
