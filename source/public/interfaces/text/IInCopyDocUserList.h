//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IInCopyDocUserList.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IInCopyDocUserList__
#define __IInCopyDocUserList__

#include "IPMUnknown.h"

#include "InCopySharedID.h"

class PMString;



/** This interface is used to add users to a list this list is used by the track changes
	and notes features. Every user has a color associated with them. No enforcement of
	a unique color per user is performed. The index for a color is assumed to be from
	the IRGBColorList interface.
	@ingroup text_other
*/
class IInCopyDocUserList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYDOCUSERLIST }; 

	// Append a user to the list
	virtual void AppendUser(const PMString & userName, int32 userColor) = 0;
	
	// Methods to search list for a specific user
	virtual PMString GetUserNameByIndex(int32 index) = 0;
	virtual int32 FindUserByName(const PMString& userName) = 0;

	virtual int32 GetUserColorIndex(int32 index) = 0;
	virtual int32 GetUserColorIndex(const PMString& userName) = 0;

	// Gets the unique user color 
	virtual int32 GetUniqueUserColorIndex(int32 index) = 0;
	virtual int32 GetUniqueUserColorIndex(const PMString& userName) = 0;
	
	// Replace an attribute in the list.
	virtual void ReplaceColorIndex(const PMString& userName, int32 newColorIndex) = 0;
	virtual void ReplaceColorIndex(const int32 userIndex, int32 newColorIndex) = 0;
	
	// Delete a specified user from the list. Returns true if successful.
	virtual bool DeleteUser(int32 index) = 0;
	virtual bool DeleteUser(const PMString& userName) = 0;
	
	// Return the number of users in the list.
	virtual int32 GetUserCount() const = 0;
	
	// Get the name of the current user in the list. The actual current user name
	// is stored as a document preference this method reads the preference and
	// finds the corespondins id to match it in this list.
	// @param added return KTrue if current user is new added, this is for the CreateUserCmd undo purpose
	virtual PMString GetCurrentUser(bool16 * added = nil) = 0;
	
	// Set the User Name
	virtual void SetUserName(const PMString& oldUserName, const PMString& newUserName) = 0;
	virtual void SetUserName(const int32 userIndex, const PMString& newUserName) = 0;
};

#endif	// __IInCopyDocUserList__
