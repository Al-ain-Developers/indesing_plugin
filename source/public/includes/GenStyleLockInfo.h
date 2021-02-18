//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GenStyleLockInfo.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __CGenStyleLockInfo__
#define __CGenStyleLockInfo__

#include "IGenStyleLockInfo.h"
#include "HelperInterface.h"

#pragma export on

class PUBLIC_DECL CGenStyleLockInfo: public IGenStyleLockInfo
{
public:
	// Constructors and Destructors
	CGenStyleLockInfo(IPMUnknown* pBoss);
	virtual ~CGenStyleLockInfo();

	virtual bool16		IsEditLocked() const;
	virtual void 		SetEditLocked(bool16 lock);
	
	virtual bool16 	    IsDeleteLocked() const;
	virtual void 		SetDeleteLocked(bool16 lock);

	virtual bool16      IsNameLocked() const;
	virtual void        SetNameLocked(bool16 lock);

	enum 
	{
		kNameLockFlag					= (1 << 0),
		kEditLockFlag					= (1 << 1),
		kDeleteLockFlag					= (1 << 2)
	};
	
	virtual bool16 GetFlag(int32 inFlag) const;

protected:
	// Member Variables
	bool16 fbEditLocked;
	bool16 fbDeleteLocked;
	bool16 fbNameLocked;

DECLARE_HELPER_METHODS()
};

#pragma export off
#endif

// End, GenStyleListMgr.h.
