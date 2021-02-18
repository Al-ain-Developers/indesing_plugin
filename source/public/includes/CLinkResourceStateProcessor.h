//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CLinkResourceStateProcessor.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  
//========================================================================================

#pragma once
#ifndef __CLinkResourceStateProcessor__
#define __CLinkResourceStateProcessor__

// ----- Includes -----
#include "AsyncWork.h"

class LinkResourceStatePacket;


/**
 Pure virtual base implementation of AsyncWorkProcessor for link resource state and stamp
 updating via the AsyncWorkManager.  Classes that want to update link resource states and
 stamps asynchronously by using the AsyncWorkManager should implement a processor class
 that inherits from the CLinkResourceStateProcessor class.
 @see AsyncWorkProcessor
 @see IAsyncWorkManager
 @see LinkResourceStatePacket
 */
class PUBLIC_DECL CLinkResourceStateProcessor : public AsyncWorkProcessor
{
public:
	virtual ~CLinkResourceStateProcessor();

	/**
	 Called by the AsyncWorkManager to update a link resource's state and stamp.
	 @param packet [IN] Link resource state packet of type LinkResourceStatePacket.
	 */
	virtual void ProcessPacket(AsyncWorkPacket* packet);

protected:
	/**
	 Called in reponse to a ProcessPacket call to update the link resource's state
	 and stamp.
	 @param packet [IN] Link resource state packet.
	 */
	virtual void UpdateState(LinkResourceStatePacket& packet) = 0;
};

#endif // __CLinkResourceStateProcessor__
