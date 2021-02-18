//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightProfile.h $
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

/**	This interface sits on a preflight profile boss and provides basic information about
	the profile. The list of rules is maintained by the IPreflightProfileRules interface.
	The preferences (ie when to apply the profile) is maintained by the 
	IPreflightProfilePrefs interface.

	@see IPreflightProfileRules
	@see IPreflightProfilePrefs
*/
class IPreflightProfile : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTPROFILE };

public:
	/**	Get the profile's name (the name that is displayed in the UI).
		@return The profile name.
	*/
	virtual PMString GetName() const = 0;

	/**	Set the profile's name (the name that is displayed in the UI).
		@param newName IN The new profile name.
	*/
	virtual void SetName(const PMString& newName) = 0;

	/**	Get the profile's description -- a longer user defined field describing the profile.
		@return The profile description.
	*/
	virtual PMString GetDescription() const = 0;

	/**	Set the profile's description -- a longer user defined field describing the profile.
		@param newDesc IN The new profile description.
	*/
	virtual void SetDescription(const PMString& newDesc) = 0;

	/** Copy all of the above settings from another instance.
		@param iSrc IN The source data to copy.
	*/
	virtual void CopyFrom(const IPreflightProfile* iSrc) = 0;
};
