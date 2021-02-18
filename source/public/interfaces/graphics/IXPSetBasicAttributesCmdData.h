//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPSetBasicAttributesCmdData.h $
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
#ifndef __IXPSetBasicAttributesCmdData__
#define __IXPSetBasicAttributesCmdData__

#include "IPMUnknown.h"
#include "XPID.h"

#include "GraphicTypes.h"

class BasicAttributesData
{
	public:
		BasicAttributesData() : 
			fOpacity (100.),
			fBlendMode(kPMBlendNormal),
			fKnockoutGroup (kFalse),
			fIsolationGroup (kFalse)
			{ }
		
		PMReal					fOpacity;
		PMBlendingMode			fBlendMode;
		bool16					fKnockoutGroup;
		bool16					fIsolationGroup;
};

class IXPSetBasicAttributesCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXPSETBASICATTRIBUTESCMDDATA };
		
		BasicAttributesData		fData;
		int32					fSetBlendMode,
								fSetOpacity,
								fSetKnockoutGroup,
								fSetIsolationGroup;
};

#endif