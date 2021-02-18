//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IScaleObject.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Purpose: Owned items can use this interface to update themselves when a text frame is scaled.
//  
//========================================================================================

#pragma once
#ifndef __IScaleObject__
#define __IScaleObject__

#include "PMReal.h"
#include "GenericID.h"


// ===================================================================================
//	class IScaleObject		
// ===================================================================================
class IScaleObject : public IPMUnknown {

//-----------------------------------
//	API
//
public:
	enum {kDefaultIID = IID_ISCALEOBJECT};

	class ScaleContext  /* an API used internally by implementations of IScaleObject */
	{
		public:
			virtual bool16	IsScaled (UID uid) const = 0; 
			virtual void	SetScaled(UID uid) = 0;
	};

	/** Scale is called by the RedefineScalingCmd in order to move scaling off of an item's transform
	    onto its content.
		@param passdownXscale - the horizontal scale factor that is being removed from the transform and must be realized in the content.
		@param passdownYscale - the vertical scale factor that is being removed from the transform and must be realized in the content.
		@param context -  Most objects should ignore the context. It's purpose is to allow multiple objects that represent portions of a
		                  single model (such as the table model) to store state information and scale the underlying model once. The context
		                  is reset on each scale operation.
	*/
	
	virtual ErrorCode 	Scale(const PMReal& passdownXscale, const PMReal& passdownYscale, ScaleContext& context) = 0;
};


#endif // __IScaleObject__
