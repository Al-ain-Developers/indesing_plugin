//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAlignContentInFrameCmdData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IALIGNCONTENTINFRAMECMDDATA__
#define __IALIGNCONTENTINFRAMECMDDATA__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMRect.h"

class IAlignContentInFrameCmdData : public IPMUnknown
{
	public:
		enum {kAlignLeftTop = 0, 
			kAlignTopCenter, 
			kAlignRightTop, 
			kAlignLeftCenter,
			kAlignCenter,
			kAlignRightCenter,
			kAlignLeftBottom,
			kAlignBottomCenter,
			kAlignRightBottom};
		
		virtual void Set(int32 alignment, const PMRect& cropAmts = kZeroRect) = 0;
		virtual int32 GetAlignment() const = 0;
		virtual void GetCropAmounts(PMRect& cropAmts) = 0;
};


#endif

