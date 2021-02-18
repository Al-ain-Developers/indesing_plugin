//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IUserInfo.h $
//  
//  Owner: Michele Goodwin
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IUserInfo__
#define __IUserInfo__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

/** Interface for getting and setting user name and color.
*/
class IUserInfo : public IPMUnknown
{
public:
 	enum { kDefaultIID = IID_IUSERINFO };
 
	/** Sets user name and color.
		@param userName the user name to set.
		@param userColorIndex the user color index to set.
	*/
	virtual void SetUser(const PMString &userName, int32 userColorIndex) = 0;

	/** Sets current user name.
		@param userName the user name to set.
	*/
	virtual void SetUserName(const PMString &userName) = 0;
	
	/**	Get current user name.
		@return PMString name of the current user or "Unknown User Name" if it's never been set.
	*/
	virtual const PMString& GetUserName() const = 0;

	/**	Sets current user color index.
		@param userColorIndex the color index to set.
	*/
	virtual void SetUserColorIndex(int32 userColorIndex) = 0;
	
	/**	Gets current user color index.
		@return color index or default index which is 53 (Gold).
	*/
	virtual int32 GetUserColorIndex() const = 0;
};

#endif // __IUserInfo__