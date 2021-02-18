//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterOverrideable.h $
//  
//  Owner: Melissa Cheng
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
//  Purpose of Interface:
//  IMasterOverrideable is an interface which specifies whether or not a master page item is
//  overrideable.  If it is not overrideable, it will not be selectable on non-master pages.
//  
//  All master page items should have this interface, though if it's missing the page item 
//  is assumed to be overrideable.
//  
//========================================================================================

#pragma once
#ifndef __IMasterOverrideable__
#define __IMasterOverrideable__

#include "IPMUnknown.h"
#include "MasterPageID.h"

/** Page item interface that controls if any item can be overrideable or not.
*/
class IMasterOverrideable : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMASTEROVERRIDEABLE };

	enum MasterOverrideableType { kMasterOverrideable = 0x00, kMasterNotOverrideable = 0x01 };
	
	/**	 Set the master overrideable flag See kSetMasterOverrideableCmdBoss for more info.
		@param int32 - must be kMasterOverrideable or kMasterNotOverrideable.
	 */
	virtual void Set(int32 masterOverrideableFlag) = 0;
	
	/**	 Return the master overrideable flag. In general, returns kMasterOverrideable or 
		 kMasterNotOverrideable based on the setting. However, for managed frames, additional 
		 logic comes into play. A content item is considered not overrideable whenever 
		 its parent frame is not overrideable.
		@return bool16 Returns kMasterOverrideable or kMasterNotOverrideable
	 */
	virtual int32 GetMasterOverrideable() const = 0;
	
	/**	 Return kTrue if the master page item is overrideable.
		@return bool16 Returns kTrue if GetMasterOverrideable returns kMasterOverrideable, kFalse otherwise.
	 */
	virtual bool16 IsMasterOverrideable() const = 0;
	
	/**	 Return kTrue if the master page item is not overrideable.
		@return bool16 Returns kTrue if GetMasterOverrideable returns kMasterNotOverrideable, kFalse otherwise.
	 */
	virtual bool16 IsMasterNotOverrideable() const = 0;
};

#endif //__IMasterOverrideable__
