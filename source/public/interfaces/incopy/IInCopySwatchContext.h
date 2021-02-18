//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopySwatchContext.h $
//  
//  Owner: Jeff Argast
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
#ifndef __IInCopySwatchContext__
#define __IInCopySwatchContext__

#include "IPMUnknown.h"

#include "GraphicTypes.h"
#include "InCopyWorkflowID.h"

class WideString;


//================================================================================================
//	Class InCopySwatchContext
//================================================================================================
class IInCopySwatchContext : public IPMUnknown
{
	public:
	enum { kDefaultIID = IID_IINCOPYSWATCHCONTEXT };


        //----------------------------------------------------------------------------------------
        //  Public Member Functions
        //----------------------------------------------------------------------------------------

		
        //----------------------------------------------------------------------------------------
		virtual void Initialize (
			const UIDRef& storyRef
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void AddTint(
			const PMString& tintName,
			const PMReal tintPercent,
			const int32 id = 0,
			const bool16 visible = kFalse
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void AddGradient(
			const PMString& gradientName,
			const GradientType gradientType,
			K2Vector<UID> stopColor,
			K2Vector<PMReal> stopPos,
			K2Vector<PMReal> midPoint,
			const int32 id = 0,
			const bool16 visible = kFalse
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void CreateSwatches() = 0;
};

#endif // __IInCopySwatchContext__
