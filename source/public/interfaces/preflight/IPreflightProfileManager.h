//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightProfileManager.h $
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
//  
//  Manages a list of profiles at the application or document level.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "IPreflightProfile.h"
#include "PackageAndPreflightID.h"

/** Manages a list of profiles at the application or document level. To get one of these
	interfaces you'd normally use IPreflightUtils::QueryProfileManager().

	@see IPreflightProfile
	@see IPrefilghtUtils
*/
class IPreflightProfileManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTPROFILEMANAGER };

public:
	/** Get the number of profiles in the list.
		@return The number of profiles in the list.
	*/
	virtual int32 GetProfileCount() const = 0;

	/** Get the Nth profile in the list.
		@param n The index of the profile you want.
		@return A refcounted profile interface or nil if n is out of range.
	*/
	virtual IPreflightProfile* QueryNthProfile(int32 n) const = 0;

	/** Get the Nth profile in the list.
		@param n The index of the profile you want.
		@return The UID of the nth profile.
	*/
	virtual UID GetNthProfileUID(int32 n) const = 0;

	/** Get the whole profile list.
		@param theList OUT The UIDList to accept the profile list.
	*/
	virtual void GetAllProfiles(UIDList* theList) const = 0;

	/** Find a profile by its UID.
		@param profileUID The UID of the profile you want.
		@return The index of the profile or -1 if no match was found.
	*/
	virtual int32 FindProfile(UID profileUID) const = 0;

	/** Find a profile by its interface.
		@param iProfile The profile you want to find.
		@return The index of the profile or -1 if no match was found.
	*/
	virtual int32 FindProfile(const IPreflightProfile* iProfile) const = 0;

	/** Find a profile by its name.
		@param profileName The name of the profile you want.
		@return The index of the profile or -1 if no match was found.
	*/
	virtual int32 FindProfile(const PMString& profileName) const = 0;

	/** Insert a particular profile; must be in the same DB as the manager.
		@note The profile name is NOT checked for conflicts.

		@param iProfile The profile you want to add to the list of profiles.
		@param beforeIndex The location of the profile. -1 = at end.
	*/
	virtual void InsertProfile(IPreflightProfile* iProfile, int32 beforeIndex = -1) = 0;

	/** Insert a *copy* of a profile. The source can be in the same DB, another DB, or in memory.
		Note that the profile name is not checked for conflicts.
		
		@param iProfile The profile you want to add to the list of profiles.
		@param beforeIndex The location of the profile. -1 = at end.
	*/
	virtual void InsertCopyOfProfile(IPreflightProfile* iProfile, int32 beforeIndex = -1) = 0;

	/** Remove a profile from the list, optionally destroying it.

		@param n The index of the profile you want to delete.
		@param deleteIt kTrue if you want to delete the profile (ie delete its UID) or kFalse to 
			simply detach it. In the latter case be sure you establish a new owner for the profile. 
	*/
	virtual void RemoveNthProfile(int32 n, bool deleteIt = kTrue) = 0;

	/** Remove all profiles from the list, optionally destroying them.

		@param deleteThem kTrue if you want to delete the profiles (ie delete their UIDs) or kFalse to 
			simply detach them. In the latter case be sure you establish a new owner for the profiles. 
	*/
	virtual void RemoveAllProfiles(bool deleteThem = kTrue) = 0;

	/**	Return a unique profile name within the specified profile manager based on "name".
		@note If 'name' is already unique, it's simply returned without any decoration.

		@param name is the base name from which to create an unique profile name. If this is 
			empty then the returned string is the default new-profile name plus any decoration
			needed to make it unique. 
		@return the unique profile name.
	*/	
	virtual PMString GetUniqueProfileName(const PMString& name) const = 0;

	/** Called by the preflight manager at application startup; do not call.
	*/
	virtual void Startup() = 0;
};

