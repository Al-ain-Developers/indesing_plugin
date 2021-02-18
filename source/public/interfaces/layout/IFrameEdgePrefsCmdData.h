//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFrameEdgePrefsCmdData.h $
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
#ifndef __IFRAMEEDGEPREFSCMDDATA__
#define __IFRAMEEDGEPREFSCMDDATA__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 

class IFrameEdgePrefsCmdData : public IPMUnknown
{
public:
	virtual void Set(const	UIDRef&	doc, const	bool16	shown) = 0;
	virtual const UIDRef& GetDocument() const = 0;
	virtual const bool16 GetFrameEdgeShown() const = 0;
};


#endif
