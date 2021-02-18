//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IDuplicatePreflightProfileCmdData.h $
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"

/**	This interface provides the settings to accompany a DuplicatePreflightProfile command.
	@see IPreflightProfile.
	Note that you may find it easier to use IPreflightFacade::DuplicateProfile() than to
	build a command directly.
*/
class IDuplicatePreflightProfileCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDUPLICATEPREFLIGHTPROFILECMDDATA };

public:
	/** Set the database where you want the new profile to exist. If left nil the new profile
		will appear in the defaults database.

		@param iDB IN The database.
	*/
	virtual void SetDestinationDatabase(IDataBase* iDB) = 0;

	/** @return the database where you want the new profile to exist. If left nil the new profile
		will appear in the defaults database.
	*/
	virtual IDataBase* GetDestinationDatabase() const = 0;

	/** Set the source profile; ie the profile that will be duplicated.
		@param srcRef IN The source profile.
	*/
	virtual void SetSourceProfile(const UIDRef& srcRef) = 0;

	/** @return the source profile (ie the one that will be duplicated).
	*/
	virtual UIDRef GetSourceProfile() const = 0;

	/** Set the destination (the copy) profile. This should only be set by the command itself.
		@param dstRef IN The UIDRef of the destination.
	*/
	virtual void SetDestinationProfile(const UIDRef& dstRef) = 0;

	/** @return the destination (copy) profile. This is only valid AFTER the command has 
		been processed.
	*/
	virtual UIDRef GetDestinationProfile() const = 0;
};
