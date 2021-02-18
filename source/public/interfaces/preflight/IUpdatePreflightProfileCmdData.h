//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IUpdatePreflightProfileCmdData.h $
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
#include "IPreflightProfileUtils.h"

/**	This interface provides the settings to accompany an UpdatePreflightProfile command.
	The UpdatePreflightProfile command modifies an existing profile with new settings.
	You can also perform this operation through IPreflightFacade.
*/
class IUpdatePreflightProfileCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUPDATEPREFLIGHTPROFILECMDDATA };

public:
	/** Set the destination profile.

		@param dstProfileRef IN The profile you want the command to modify.
	*/
	virtual void SetDstProfile(const UIDRef& dstProfileRef) = 0;

	/** Get the profile this command will modify.
		@return The UIDRef of the target profile.
	*/
	virtual UIDRef GetDstProfile() const = 0;

	/**	Set the "new" data for the command (ie the new profile data you want to set).
		This method MAKES A COPY of the profile data. If copyNamesOnly is false then
		it also makes a copy of the profile's other data (namely, rules).

		@param iSrcProfile IN The profile data you want to apply to the DstProfile.
		@param copyNamesOnly IN True if all you want to set are the names in the 
			IPreflightProfile interface. False if you want to make a complete copy
			of the profile data. If True then ONLY iSrcProfile is considered. If false
			then the method will Query the rules interface from iSrcProfile and make
			a copy of that too.
	*/
	virtual void SetNew(const IPreflightProfile* iSrcProfile, bool copyNamesOnly) = 0;

	/** Return whether to copy only the names (ie IPreflightProfile members); or whether
		to deep-copy the entire profile.

		@return True to do only a name-copy; False to do a deep, full copy.
	*/
	virtual bool GetCopyNamesOnly() const = 0;

	/** @return the (refcounted) source data that will be applied to the DstProfile, or
			nil if SetNew has not been called.
		@note this is an in-memory COPY of the data passed into the SetNew method.
	*/
	virtual IPreflightProfile* QueryNewProfile() const = 0;

	/** Set the old data for the DstProfile. This is set up when the command is executed.
		Only the command itself should call this method.
		@param iCurProfile IN The current state of the profile prior to making changes.
	*/
	virtual void SetOld(const IPreflightProfile* iCurProfile) = 0;

	/** Get the old data for the DstProfile. This allows observers to see the old vs the
		new data to see if the change is something they're concerned with.

		@return A refcounted interface to the old profile data.
	*/
	virtual IPreflightProfile* QueryOldProfile() const = 0;

	/** Set what changed. This is called by the command itself; you shouldn't call it.

		@param flags IN The new change flags.
	*/
	virtual void SetWhatChanged(IPreflightProfileUtils::ProfileChangeFlags flags) = 0;

	/** Get a rough idea of what the command changed. This is set up once the command
		has executed. It's useful for observers that want to know what might have changed.

		@return A set of the change flags.
	*/
	virtual IPreflightProfileUtils::ProfileChangeFlags GetWhatChanged() const = 0;
};
