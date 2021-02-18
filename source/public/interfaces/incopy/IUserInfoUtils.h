//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IUserInfoUtils.h $
//  
//  Owner:
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
#ifndef __IUserInfoUtils__
#define __IUserInfoUtils__

#include "InCopySharedID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class PMString;

/** 
	Utility methods for manipulating IUserInfo data.
*/
class IUserInfoUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUSERINFOUTILS };



	/**
		Sets InCopy user name.
		@param userName IN. User name.
    */
	virtual void SetInCopyUsername( const PMString& userName ) const = 0;

	/**
		Returns InCopy user name.
		@param uiFlags IN, optional. If kFullUI and InCopy user name is empty or "Unknown User Name" the user will be asked for entering a new user name.
		@return InCopy user name.
    */
	virtual PMString GetInCopyUsername( UIFlags uiFlags = kFullUI ) const = 0;


};


#endif	// __IUserInfoUtils__
