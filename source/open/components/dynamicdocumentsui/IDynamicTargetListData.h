//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/IDynamicTargetListData.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IDynamicTargetDataList__
#define __IDynamicTargetDataList__

// ----- Interface files -----

#include "IDynamicEventTimingMgr.h"
#include "IPMUnknown.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

/** IDynamicTargetData is a data interface that holds onto data for DynamicTarget class defined in IDynamicEventTimingMgr.h.
*/
class IDynamicTargetListData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDYNAMICTARGETLISTDATA };

		virtual void Append(IDynamicEventTimingMgr::DynamicTargetPtr const &target) = 0;
		virtual void GetDynamicTargetList(IDynamicEventTimingMgr::DynamicTargetList &targetList) = 0;

		virtual size_t size() = 0;
		virtual void Clear() = 0;
};

#endif // __IDynamicTargetDataList__
