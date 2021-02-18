//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSItemProfileSource.h $
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

#ifndef __ICMSItemProfileSource__
#define __ICMSItemProfileSource__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ColorMgmtID.h"
#include "IPMUnknown.h"

class PMString;

class ICMSItemProfileSource : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSITEMPROFILESOURCE };

	enum ProfileSourceType {
				kProfileSourceNotSet,		// (implies kProfileSourceDefault)
				kProfileSourceDefault,		// CMSPROFILEUID is not used; use def for space.
				kProfileSourceExternal,		// CMSPROFILEUID points to an external profile.
				kProfileSourceEmbedded		// CMSPROFILEUID refers to embedded info.
			};	
	
	// Returns whether image is using embedded profile, not, or undecided.
	virtual ProfileSourceType GetProfileSourceType() const = 0;
	virtual void		SetProfileSourceType(ProfileSourceType newType) = 0;

	// If there is an embedded profile, these get/set its name.
	virtual void		GetEmbeddedProfileName(PMString &theString) const = 0;
	virtual void		SetEmbeddedProfileName(const PMString& newName) = 0;
};

#endif // __ICMSItemProfileSource__

// End, ICMSItemProfileSource.h.
