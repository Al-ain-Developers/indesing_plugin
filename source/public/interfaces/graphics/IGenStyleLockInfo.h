//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGenStyleLockInfo.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IGenStyleLockInfo__
#define __IGenStyleLockInfo__

#include "GenStlEdtID.h"

class IGenStyleLockInfo : public IPMUnknown

{
public:
	enum { kDefaultIID = IID_IGENSTYLELOCKINFO };

	virtual bool16		IsEditLocked() const = 0;
	virtual void 		SetEditLocked(bool16 lock) = 0;
	
	virtual bool16 	    IsDeleteLocked() const = 0;
	virtual void 		SetDeleteLocked(bool16 lock) = 0;

	virtual bool16      IsNameLocked() const = 0;
	virtual void        SetNameLocked(bool16 lock) = 0;

	enum 
	{
		kNameLockFlag					= (1 << 0),
		kEditLockFlag					= (1 << 1),
		kDeleteLockFlag					= (1 << 2)
	};
	
	virtual bool16 GetFlag(int32 inFlag) const = 0;
};

#endif

