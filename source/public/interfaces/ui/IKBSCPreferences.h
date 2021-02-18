//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IKBSCPreferences.h $
//  
//  Owner: Michel hutinel
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
#ifndef __IKBSCPreferences__
#define __IKBSCPreferences__


#include "IPMUnknown.h"

#include "PMString.h"
#include "IKBSCSetsManager.h"

/** This interface maintains the current user selection for which Keyboard shortcut set to use.
*/
class IKBSCPreferences : public IPMUnknown
{
public:
	/** Get the name of the current set in use.
		@param setName The returned set name.
		@return kFalse if set name has not been set, else kTrue
	*/
	virtual bool16	GetCurrentSetName(PMString& setName) const = 0;

	/** Get the area of the current set in use */
	virtual IKBSCSetsManager::KBSCArea	GetCurrentSetKBSCArea() const = 0;

	/** Record the name of the current used set and its area
		@param setName The new current set name.
		@param area The new current set area, kUserKBSCArea or kDefaultKBSCArea.
		@see IKBSCSetsManager.h
	*/
	virtual void	SetCurrentSetName(const PMString& setName, const IKBSCSetsManager::KBSCArea area) = 0;
};


#endif
		// __IKBSCPreferences__
		
		