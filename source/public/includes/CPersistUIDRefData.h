//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPersistUIDRefData.h $
//  
//  Owner: brendan
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
//  Description : Persistent UID Data, very similar to PersistUIDData, but 
//  the read/write method does a XferReference instead of a 
//  XferObject (which is what PersistUIDData does).
//  
//========================================================================================

#pragma once
#ifndef __CPersistUIDRefData__
#define __CPersistUIDRefData__

#include "IPersistUIDData.h"
#include "HelperInterface.h"

#pragma export on

class PUBLIC_DECL CPersistUIDRefData : public IPersistUIDData
{
public:
	CPersistUIDRefData(IPMUnknown* boss);

	virtual ~CPersistUIDRefData();
	
	virtual void SetUID (const UID& id) ; 

	virtual UID GetUID () const ; 

	virtual void ReadWrite (IPMStream* iPMStream, ImplementationID id);

protected:
	UID	fUID;
	
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
