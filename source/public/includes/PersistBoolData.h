//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistBoolData.h $
//  
//  Owner: Tommy Donovan
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
//  Interface for storing booleans persistently.
//  
//========================================================================================

#pragma once
#ifndef __PersistBoolData__
#define __PersistBoolData__

#include "IBoolData.h"
#include "HelperInterface.h"

class PersistBoolData : public IBoolData
{
public:
	PersistBoolData(IPMUnknown *boss);
	virtual ~PersistBoolData();

	virtual void Set(bool16 b); 
	virtual bool16 GetBool() const;
	virtual void ReadWrite(IPMStream *s, ImplementationID prop);
	
protected:
	bool16 fBool;

DECLARE_HELPER_METHODS()
};

//
// FalseInitPersistBoolData is initialized to kFalse
//
class FalseInitPersistBoolData : public PersistBoolData
{
public:
	FalseInitPersistBoolData(IPMUnknown *boss) : PersistBoolData(boss)
	{ 
		fBool = kFalse;	
	}
};

#endif // __PersistBoolData__

