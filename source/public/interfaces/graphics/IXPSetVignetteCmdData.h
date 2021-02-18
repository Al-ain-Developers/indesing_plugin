//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPSetVignetteCmdData.h $
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
#ifndef __IXPSetVignetteCmdData__
#define __IXPSetVignetteCmdData__

#include "IPMUnknown.h"
#include "XPID.h"

#include "GraphicTypes.h"

class VignetteData
{
public:
	VignetteData() : 
			fWidth (36.),
			fInnerOpacity (100.),
			fOuterOpacity (0.),
			fNoise (0.),
			fMode(kVTMNone),
			fCorners(kVTCSharp)
		{}
	
	PMReal				fWidth;
	PMReal				fInnerOpacity;
	PMReal				fOuterOpacity;
	PMReal				fNoise;
	PMVignetteMode		fMode;
	PMVignetteCorners	fCorners;
};

class IXPSetVignetteCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXPSETVIGNETTECMDDATA };
		
		VignetteData	fData;
		int32			fSetMode,
						fSetWidth,
						fSetInnerOpacity,
						fSetOuterOpacity,
						fSetCorners,
						fSetNoise;
};

#endif