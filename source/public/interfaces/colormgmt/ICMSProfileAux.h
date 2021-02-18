//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSProfileAux.h $
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

#ifndef __ICMSProfileAux__
#define __ICMSProfileAux__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ColorMgmtID.h" // IID_ICMSPROFILEAUX

class ICMSProfileAux : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSPROFILEAUX };

	virtual int32 GetSourceType() const = 0;  // ICMSProfile::sourceType		
	virtual void SetSourceType(int32 sourceType) = 0;
	virtual int32 GetColorSpace() const = 0;  // ICMSProfile::profileSpace		
	virtual void SetColorSpace(int32 colorSpace) = 0;
	virtual int32 GetClass() const = 0;  // ICMSProfile::profileClass		
	virtual void SetClass(int32 theClass) = 0;
};

#endif // __ICMSProfileAux__

// End, ICMSProfileAux.h.
