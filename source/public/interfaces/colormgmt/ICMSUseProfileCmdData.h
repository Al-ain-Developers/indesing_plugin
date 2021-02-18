//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSUseProfileCmdData.h $
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

#ifndef __ICMSUseProfileCmdData__
#define __ICMSUseProfileCmdData__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ICMSProfile.h"

class ICMSUseProfileCmdData : public IPMUnknown
{
	public:
		virtual void		SetSourceType(const ICMSProfile::profileSourceType srcType) = 0;
		virtual ICMSProfile::profileSourceType	
								GetSourceType() const = 0;
		virtual void		SetProfileName(const PMString &name) = 0;
		virtual void		GetProfileName(PMString *pName) = 0;
		virtual bool32		SetEmbeddedData(const void *pData, uint32 size) = 0;
		virtual void *		GetEmbeddedDataPtr() const = 0;
		virtual uint32		GetEmbeddedDataSize() const = 0;
		virtual void		SetCategory(ICMSProfile::profileCategory category) = 0;
		virtual ICMSProfile::profileCategory 
								GetCategory() const = 0;
		
		// Set/Get the install default flag. If the install default flag is kTrue, the profile 
		// name, source type and embedded data are ignored and the default profile (specified in 
		// the application's Color Settings) will be used instead.
		virtual void		SetInstallDefaultFlag(bool installDefaultFlag) = 0;
		virtual bool16		GetInstallDefaultFlag() const = 0;
};

#endif // __ICMSUseProfileCmdData__

// End, ICMSUseProfileCmdData.h.
