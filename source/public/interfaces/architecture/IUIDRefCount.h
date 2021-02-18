//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUIDRefCount.h $
//  
//  Owner: jargast
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
#ifndef __IUIDRefCount__
#define __IUIDRefCount__

#include "IPMUnknown.h"

/**	A data interface to keep track of UID reference count.
*/
class IUIDRefCount : public IPMUnknown
{
public:
	/** Add one to the reference count.
	*/
	virtual void AddUIDRef() = 0;
	
	/** Subtract one from the UID reference count
	*/
	virtual void ReleaseUIDRef() = 0;
	
	/** Get the current count.
	*/
	virtual int32 GetUIDRefCount() = 0;
	
};


#endif
