//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/IConvertToProfilesCmdData.h $
//  
//  Owner: James Jardee-Borquist
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

#ifndef __IConvertToProfilesCmdData__
#define __IConvertToProfilesCmdData__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ICMSProfile.h"
#include "ICMSSettings.h"
#include "IPMUnknown.h"

#include "ACEColorMgmtID.h"

//========================================================================================
// CLASS IConvertToProfilesCmdData
//========================================================================================

class IConvertToProfilesCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONVERTTOPROFILESCMDDATA };
	
	virtual void SetName(ICMSProfile::profileCategory category, const PMString &name) = 0;
	virtual bool16 GetName(ICMSProfile::profileCategory category, PMString &name) const = 0;
	
	virtual void SetEngineCMS(uint32 engineCMS) = 0;
	virtual uint32 GetEngineCMS() const = 0;
	
	virtual void SetEngineCMM(uint32 engineCMM) = 0;
	virtual uint32 GetEngineCMM() const = 0;
	
	virtual void SetIntent(ICMSSettings::renderingIntent intent) = 0;
	virtual ICMSSettings::renderingIntent GetIntent() const = 0;
	
	virtual void SetUseKPC(bool16 useKPC) = 0;
	virtual bool16 GetUseKPC() const = 0;
};

#endif // __IConvertToProfilesCmdData__

// End, IConvertToProfilesCmdData.h.
