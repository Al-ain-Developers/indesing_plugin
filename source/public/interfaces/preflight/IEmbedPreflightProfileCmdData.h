//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IEmbedPreflightProfileCmdData.h $
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

/**	This interface provides the settings to accompany an EmbedPreflightProfile command.
	Note that this command can both embed *and* unembed profiles. Also, you may also 
	find it easier to use IPreflightFacade::EmbedProfile and/or 
	IPreflightFacade::UnembedProfile() than building and processing the command yourself.

	@see IPreflightProfile
*/
class IEmbedPreflightProfileCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEMBEDPREFLIGHTPROFILECMDDATA };

public:
	/** Set the database to modify.
		@param db IN The database to modify. Must be a valid document database.
	*/
	virtual void SetDataBase(IDataBase* db) = 0;

	/** @return the database to modify.
	*/
	virtual IDataBase* GetDataBase() const = 0;

	/**	For an embed operation, sets the profile data to copy into the document.
		For an unembed operation, you don't need to call this (but you can pass nil to
		force one if it's possible that it was set to non-nil at some point).

		@param iSrcProfile IN The profile data you want to embed in the document. If nil,
			clears (disposes) the existing profile, so this becomes an Unembed request.
	*/
	virtual void SetNewProfile(const IPreflightProfile* iSrcProfile) = 0;

	/** @return the (refcounted) source profile that will be added; nil if not set.
		@note this is an in-memory COPY of the data passed into the SetNew method.
	*/
	virtual IPreflightProfile* QueryNewProfile() const = 0;

	//========================================================================================== 
	// The following methods are only valid DURING AND AFTER the command has been processed. 

	/** Sets the old (previously embedded) profile's UID, if any. This should only be 
		set by the command itself during the processing of the command.
	*/
	virtual void SetOldProfileUID(UID oldProfile) = 0;

	/** @return the previously embedded profile's UID, if any. kInvalidUID if there was none.
	*/
	virtual UID GetOldProfileUID() const = 0;

	/** Sets the old (previously embedded) profile's name, if any. This should only be 
		set by the command itself during the processing of the command.
	*/
	virtual void SetOldProfileName(const PMString& oldName) = 0;

	/** @return the previously embedded profile's name, if any. Empty if there was none.
	*/
	virtual PMString GetOldProfileName() const = 0;

	/** Sets the new (newly embedded) profile's UID, if any. This should only be 
		set by the command itself during the processing of the command.
	*/
	virtual void SetNewProfileUID(UID oldProfile) = 0;

	/** @return the newly embedded profile's UID, if any. kInvalidUID if none was embedded.
	*/
	virtual UID GetNewProfileUID() const = 0;
};
