//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/INewPreflightProfileCmdData.h $
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

/**	This interface provides the settings to accompany a NewPreflightProfile command.
	@see IPreflightProfile
*/
class INewPreflightProfileCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INEWPREFLIGHTPROFILECMDDATA };

public:
	/** Set the database where you want the new profile to exist. If left nil the new profile
		will appear in the defaults database.
	*/
	virtual void SetDestinationDatabase(IDataBase* iDB) = 0;

	/** @return the database where you want the new profile to exist. If left nil the new profile
		will appear in the defaults database.
	*/
	virtual IDataBase* GetDestinationDatabase() const = 0;

	/** Set whether to prepopulate the profile with all registered rules.
		@param populated IN True to prepopulate with default rule data; false to create an empty profile.
	*/
	virtual void SetCreatePopulated(bool populated) = 0;

	/** @return whether to prepopulate the profile with all registered rules.
	*/
	virtual bool GetCreatePopulated() const = 0;

	/** Set the new profile's name.
		@param x IN The name to use.
	*/
	virtual void SetName(const PMString& x) = 0;

	/** @return the new profile's name.
	*/
	virtual PMString GetName() const = 0;

	/** Set the new profile's description.
		@param x IN The name to use.
	*/
	virtual void SetDescription(const PMString& x) = 0;

	/** @return the new profile's description.
	*/
	virtual PMString GetDescription() const = 0;

	/** Set the destination (newly created) profile. This should only be set by the command itself.
		@param dstRef IN The UIDRef of the destination.
	*/
	virtual void SetDestinationProfile(const UIDRef& dstRef) = 0;

	/** @return the destination (newly created) profile. This is only valid AFTER the command has 
		been processed.
	*/
	virtual UIDRef GetDestinationProfile() const = 0;
};
