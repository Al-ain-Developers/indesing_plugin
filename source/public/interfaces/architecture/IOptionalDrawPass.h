//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOptionalDrawPass.h $
//  
//  Owner: dwaterfa
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
#ifndef __IOPTIONALDRAWPASS__
#define __IOPTIONALDRAWPASS__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class GraphicsData;

class IOptionalDrawPass : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOPTIONALDRAWPASS };
	
		//
		// Returns true if the adornments would like to draw on
		// the specified pageItem and IShape flags. Also may be used to
		// optionally skip draw events, in which case pageItem may be nil.
		//
		virtual bool16 GetIsActive(IPMUnknown *pageItem,
									GraphicsData* gd,
									int32 iShapeFlags) = 0;

};

#endif
