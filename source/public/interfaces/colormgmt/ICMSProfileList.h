//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSProfileList.h $
//  
//  Owner: fhaberma
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

#ifndef __ICMSProfileList__
#define __ICMSProfileList__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ICMSProfile.h"

class ICMSProfileList : public IPMUnknown
{
public:

	virtual bool16 ShouldEmbedProfiles()=0;	//Returns whether should copy entire profile into document
	virtual void SetShouldEmbedProfiles(bool16 should)=0;	//Sets whether should copy entire profile into document
	
	virtual int32 AddProfile(ICMSProfile *newProfile, ICMSProfile::profileCategory category = ICMSProfile::kOther) = 0;
	virtual int32 AddProfile(const UID& newProfile, ICMSProfile::profileCategory category = ICMSProfile::kOther) = 0;

	virtual bool16 GetNthProfile(int32 n, UID *profile) = 0;
	virtual bool16 GetNthProfile(int32 n, UIDRef *profile) = 0;
	virtual PMString GetNthProfileName(int32 n) = 0;
	
	virtual int32 FindProfile(ICMSProfile *profile) = 0;
	virtual int32 FindProfile(const UID& profile) = 0;
	virtual int32 FindProfile(const PMString &searchName) = 0;
	
	// Assign the 'n'th profile to the speficied 'category'.
	virtual bool16 AssignProfileToCategory(int32 n, ICMSProfile::profileCategory category) = 0;
	
	// Clear the 'category'.
	virtual bool16 ClearCategory(ICMSProfile::profileCategory category) = 0;
	
	// Get the index of the profile assigned to the 'category'.
	virtual int32 GetProfileAssignedToCategory(ICMSProfile::profileCategory category) = 0;
	
	virtual int32 Length() = 0;
	
	virtual bool16 Remove(int32 n) = 0; 
	
#ifdef DEBUG
	virtual void DumpToDebugWindow() = 0;
#endif
	
};

#endif // __ICMSProfileList__

// End, ICMSProfileList.h.
