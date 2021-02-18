//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IApplyAttributesData.h $
//  
//  Owner: Joe Shankar
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
//  Purpose: Data interface for passing around an attribute boss list for commands.
//  
//========================================================================================

#pragma once
#ifndef __IApplyAttributesData__
#define __IApplyAttributesData__

#include "IPMUnknown.h"
#include "TablesID.h"

class AttributeBossList;

/**	A data interface used for setting and getting table related attributes.
*/
class IApplyAttributesData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPLYATTRIBUTESDATA };

	/**	Set the attributes.
		The interface takes over ownership for the passed in attributes.
		@param attrs is the list of attributes to set.
	*/
	virtual void Set(const AttributeBossList* attrs) = 0;

	/**	Returns the attributes.
	*/
	virtual const AttributeBossList* Get(void) const = 0;
};

#endif
