//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageSizeList.h $
//  
//  Owner: sheridan
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
//  Data interface for storing a list of page sizes.
//  
//========================================================================================

#pragma once
#ifndef __IPageSizeList__
#define __IPageSizeList__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "K2Vector.h"
#include "PMPageSize.h"


class IPageSizeList : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IPAGESIZELIST };

	virtual void SetPageSizeList(const K2Vector<PMPageSize>& sizes) = 0;
	virtual const K2Vector<PMPageSize>& GetPageSizeList() const = 0;
};


#endif // __IPageSizeList__
