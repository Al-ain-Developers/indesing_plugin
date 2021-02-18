//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAdobeAuxMetaData.h $
//  
//  Owner: Mark VerMurlen
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
#ifndef __IAdobeAuxMetaData_h__
#define __IAdobeAuxMetaData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "K2Vector.h"
#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"


//========================================================================================
// CLASS IAdobeAuxMetaData
//========================================================================================

class IAdobeAuxMetaData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IADOBEAUXMETADATA };
	
	/** Used to specify different stock item status.
	*/
	enum eStockStatus{ kNotStock, kStockComp, kStockHighRes };
	
	/**
		Get the "Stock" item status of the object.
		@return	the status of the stock item.  The return value will be kNotStock for objects
		that don't define themselves as stock items.
	*/
	virtual eStockStatus		GetStockStatus() const = 0;
};

#endif // __IAdobeCoreMetaData_h__
