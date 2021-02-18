//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPointListData.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IPointListData__
#define __IPointListData__

#include "IPMUnknown.h"
#include "CommandID.h"
#include "PMPoint.h"

/** Data interface for storing a list of points.
	@ingroup arch_coredata 
*/
class IPointListData : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IPOINTLISTDATA } ;

	/**	Set the new list of PMPoint data.
		@param thePoint specifies the list of PMPoint to set.
		@see also PMPoint

	*/
	virtual void Set(const PMPointList& thePoint) = 0;
	/**	Returns the current list of PMPoint data.
		@return a const reference to the current list of PMPoint.
	*/
	virtual const PMPointList& GetPointList() const = 0;
};


#endif // __IPointListData__
