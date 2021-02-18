//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDistributeOffsetData.h $
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
#ifndef __IDistributeOffsetData__
#define __IDistributeOffsetData__

#include "IPMUnknown.h"
#include "GenericID.h"

/**
	Used by align and scripting for distributing of objects for user customized distribute options.
*/
class IDistributeOffsetData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IDISTRIBUTEOFFSETDATA };

	/**
		Whether distribute offset value is active or not.
		@return kTrue if should pay attention to offset value when distributing
	*/
	virtual bool16 GetActive() const = 0;
	
	/**
		Set whether distribute offset value is active or not.
		@param kTrue if should pay attention to offset value when distributing
		@return none
	*/
	virtual void SetActive(bool16 active) = 0;
	
	/**
		Get the actual offset value for distributing items.
		@return offset value between items when distributing
	*/
	virtual PMReal GetOffset() const = 0;
	
	/**
		Set the actual offset value for distributing items.
		@param offset value between items when distributing
		@return none
	*/
	virtual void SetOffset(PMReal offset) = 0;
};

#endif // __IDistributeOffsetData__
