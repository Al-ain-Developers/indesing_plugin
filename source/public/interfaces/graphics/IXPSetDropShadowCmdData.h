//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPSetDropShadowCmdData.h $
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
#ifndef __IXPSetDropShadowCmdData__
#define __IXPSetDropShadowCmdData__

#include "IPMUnknown.h"
#include "XPID.h"

#include "GraphicTypes.h"

class DropShadowData
{
public:
	DropShadowData() : 
			fMode (kDSMNone),
			fBlendMode (kPMBlendNormal),
			fOffsetX (0.),
			fOffsetY (0.),
			fColorUID (kInvalidUID),
			fOpacity (0.),
			fBlurRadius (0.),
			fSpread (0.),
			fNoise (0.),
			fUseGlobalLight(kFalse),
			fKnockout(kFalse)
			{}
	
	PMDropShadowMode		fMode;
	PMBlendingMode			fBlendMode;
	PMReal					fOffsetX;
	PMReal					fOffsetY;
	UID						fColorUID;
	PMReal					fOpacity;
	PMReal					fBlurRadius;
	PMReal					fSpread;
	PMReal					fNoise;
	bool32					fUseGlobalLight;
	bool32					fKnockout;
};

class IXPSetDropShadowCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXPSETDROPSHADOWCMDDATA };
	
		DropShadowData		fData;
		int32				fSetMode,
							fSetBlendMode,
							fSetOffsetX,
							fSetOffsetY,
							fSetColorUID,
							fSetOpacity,
							fSetBlurRadius,
							fSetSpread,
							fSetNoise,
							fSetUseGlobalLight,
							fSetKnockout;
};

#endif