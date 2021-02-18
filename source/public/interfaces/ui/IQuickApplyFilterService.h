//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IQuickApplyFilterService.h $
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
#ifndef __IQuickApplyFilterService__
#define __IQuickApplyFilterService__

#include <list>

#include "IIdleTask.h" // for IdleTimer include
#include "IQuickApplyService.h"
#include "QuickApplyFindListNode.h"

#include "FindChangeID.h"
#include "IPMUnknown.h"

class IActiveContext;
class IEvent;



/** An implementer of this interface that registers in a kQuickApplyFilterService has the opportunity to filter items as they are loaded from other
	quick apply service providers.
	@author Kevin Van Wiel
*/
class IQuickApplyFilterService : public IPMUnknown
{
public:
	/** Standard enum to for use with GetDefaultIID() method.
	*/
	enum { kDefaultIID = IID_IQUICKAPPLYFILTERSERVICE };
	
	/**
		As items are returned from kQuickApplyService providers this method is called to allow items to be removed for custom 3rd party ui's
		that disallow some items from being accessed
		@param working list is an IN and OUT parameter on in it contains the new items that are about to be added to the quick apply dialog on out the implementer should give back the filtered list 
		@return none
	*/
	virtual void FilterItems(K2Vector<QuickApplyFindListNode> &workingList) = 0;
};


#endif // __IQuickApplyFilterService__
