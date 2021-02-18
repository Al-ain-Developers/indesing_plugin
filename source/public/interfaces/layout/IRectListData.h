//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRectListData.h $
//  
//  Owner: Rich Gartland
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
//  Data interface for storing a list of PMRects.
//  
//========================================================================================

#pragma once
#ifndef __IRectListData__
#define __IRectListData__

#include "IPMUnknown.h"
#include "CommandID.h"
#include "PMRect.h"


class IRectListData : public IPMUnknown 
{
public:
	virtual void SetRectList(const PMRectCollection& theRect) = 0;
	virtual const PMRectCollection& GetRectList() const = 0;
};


#endif // __IRectListDataa__
