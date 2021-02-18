//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryNeedsRelinkData.h $
//  
//  Owner: Matt Ramme
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
//  A boolean to determine whether the story needs to be relinked or not
//  
//========================================================================================

#pragma once
#ifndef __IStoryNeedsRelinkData__
#define __IStoryNeedsRelinkData__

#include "IPMUnknown.h"
#include "widgetid.h"
#include "InCopyBridgeID.h"

/** Interface on kTextStoryBoss. This interface was set by ICStoriesCurrentIdleTask to indicate that this InCopy story is out-of-date
	and needs to relink.
*/
class IStoryNeedsRelinkData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTORYNEEDSRELINK };


/**	Get method to get if story needs to relinked.
	@param none
	@return bool16 
 */
	virtual bool16 Get() const = 0;

/**	Set method to set if story needs to relinked.
	@param b kTrue means that story needs relinked.
 */
	virtual void Set(bool16 b) = 0;
	
};

#endif // __IStoryNeedsRelinkData__
