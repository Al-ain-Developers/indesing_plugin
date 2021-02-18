//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IGridAddressData.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Purpose: Data interface for GridAddress's.
//  
//========================================================================================

#pragma once
#ifndef __IGridAddressData__
#define __IGridAddressData__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"


/**
	Carries a grid address.
*/
class IGridAddressData : public IPMUnknown {

//-----------------------------------
//	API
//
public:
	enum {kDefaultIID = IID_IGRIDADDRESSDATA};

	/**
		Set the data being carried.
		@param value grid address data to be carried.
	*/
	virtual void 			Set(const GridAddress& value) = 0;

	/**
		Get the data being carried.
		@return grid adddress data being carried.
	*/
	virtual GridAddress  	Get() const = 0;
};


#endif // __IGridAddressData__
