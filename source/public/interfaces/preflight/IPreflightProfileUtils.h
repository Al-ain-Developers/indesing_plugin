//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightProfileUtils.h $
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
#include "IPreflightObject.h"
#include "IPreflightRuleInfo.h"
#include "Utils.h"

class IPreflightProfileUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTPROFILEUTILS };

public:
	/** Create a new profile in the specified database and then copy all the parameters from
		the source profile (via CopyProfileData). 
		
		@note The new profile will NOT be added to the destination database's profile manager.
		@note If the destination datbase is nil the new profile will be an in-memory profile; it
			does NOT use the application level defaults doc. If you want to create a profile
			in the defaults doc you need to pass the database of the defaults doc!
		
		@param iSrcProfile is the profile from which the data is to be copied.
		@param destDB is the destination database in which to create the profile. If nil the
			profile will be created in memory.
		@return A refcounted IPreflightProfile interface on the new profile.
	*/
	virtual IPreflightProfile* DuplicateProfile
		(
			const IPreflightProfile* iSrcProfile, 
			IDataBase* destDB
		) const = 0;

	/** Change flags. Note that these are bitfields.
	*/
	typedef enum
	{
		kChangedNothing			= 0,
		kChangedName			= (1L<<0),
		kChangedDescription		= (1L<<1),
		kChangedRules			= (1L<<2)
	} ProfileChangeFlags;

	/** Copy the profile data from one profile to another. You can choose whether to copy only
		names, or copy names and all other data (basically, rules).
		
		@param iSrcProfile is the profile from which the data is to be copied.
		@param iDstProfile is the profile to which the data is to be copied.
		@param copyNamesOnly IN True to copy only the names in IPreflightProfile. False to do
			a complete, deep copy including rules.
		@param pChanges OUT If not nil, receives the change flags. Note that this is somewhat
			expensive to calculate if there are rule settings involved (involves deep comparisons)
			so you should pass nil unless you really care to know this.
	*/
	virtual void CopyProfileData
		(
			const IPreflightProfile* iSrcProfile, 
			IPreflightProfile* iDstProfile,
			bool copyNamesOnly = kFalse,
			ProfileChangeFlags* pChanges = nil
		) const = 0;

	/** Create a new preflight profile with no rules attached. Note that this does
		NOT automatically add the profile to the profile list for the database (if any).

		@param db The database in which to create the profile. If nil, the profile is in-memory.
	*/
	virtual IPreflightProfile* CreateEmptyProfile(IDataBase* db) const = 0;

	/** Create a new preflight profile with a full set of rules attached. Note that this does
		NOT automatically add the profile to the profile list for the database (if any).

		@param db The database in which to create the profile. If nil, the profile is in-memory.
	*/
	virtual IPreflightProfile* CreatePopulatedProfile(IDataBase* db) const = 0;

	/** Destroy a profile, ie delete all its children (rules mainly) and then delete the UID.
		The UID of the profile and all child objects (eg rules) will no longer be valid,
		so be sure it has been fully removed from any references first!

		Note that for in-memory profiles all the rules are also in memory so this method
		does not need to be called (since it takes a UIDRef you couldn't if you wanted to).
		Simply derefing the profile down to zero will auto-delete the children.

		@param profileRef The profile you want to destroy.
	*/
	virtual void DestroyProfile(const UIDRef& profileRef) const = 0;

	/**	Export the specified profile as an InDesign preflight profile file.

		@param iProfile is the preflight profile to export.
		@param exporFile is the file spec to export the profile to.
		@return kSuccess if no error; otherwise returs an error code.
	*/
	virtual ErrorCode ExportProfileAsINX (const IPreflightProfile* iProfile, const IDFile& exportFile) const = 0;
	
	/**	Import the specified source InDesign preflight profile file.

		@param sourceFile is the file spec to import.
		@return the profile created from this INX file. Returns nil if import failed.
	*/
	virtual IPreflightProfile* ImportProfileFromINX (const IDFile& sourceFile) const = 0;
};



