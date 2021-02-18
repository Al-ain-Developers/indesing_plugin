//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ISetUserColorsCmdData.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ISetUserColorsCmdData__
#define __ISetUserColorsCmdData__
#include "CPMUnknown.h"

#include "InCopySharedID.h"

/**
	ISetUserColorsCmdData command data for kSetUserColorsCmdBoss.
*/

class ISetUserColorsCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISETUSERCOLORSCMDDATA };

		enum { kInvalidColorIndex = -1 };

		/**
			Set the current user name and color.
			@param IN newName new user name
			@param IN newColorIndex new color index for this user
			@return void
		**/
		virtual void Set(
			PMString newName,
			int32 newColorIndex
			)  = 0;

		/**
			Gets the current user name.
			@return PMString name of the current user
		**/
		virtual PMString UserName() const = 0;
		/**
			Gets the current user color.
			@return int32 index of the current user color
		**/
		virtual int32 UserColorIndex() const = 0;
};

#endif	// __ISetUserColorsCmdData__