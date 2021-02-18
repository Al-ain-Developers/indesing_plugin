//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IItemLockData.h $
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
//  Purpose of Interface:
//  IItemLockData is an interface which specifies whether or not a page item's data is
//  locked for either insert or attribute.  If it is locked for insert then it's content
//  cannot edited (inserted, deleted, etc), if it's locked for attribute then attribute changes
//  cannot be applied to the content.
//  
//  Currently, TextStoryBoss (replaces ITextLockData) and SplineItemBoss have this interface.
//  
//========================================================================================

#pragma once
#ifndef __IItemLockData__
#define __IItemLockData__

#include "IPMUnknown.h"
#include "GenericID.h"

/**
	This class is used to determine if an object is editable.  If it is locked for insert 
	then it's content cannot edited (inserted, deleted, etc), if it is locked for attribute 
	then attribute changes cannot be applied to the content.

	The object is added into the kTextStoryBoss and the kSplineItemBoss, it replaces
	the ITextLockData.
*/
class IItemLockData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IITEMLOCKDATA };
		
		/**
			Sets the insert lock used to determine is editing is allowed.
			@param lock kTrue to set the insert lock
		**/
		virtual void SetInsertLock(bool8 lock) = 0;
		/**
			Get the insert lock.  If item is an inline the parent's lock is returned
			unless otherwise specified.
			@param checkParent kFalse to return inline's lock rather than it's parent's lock
			@return kTrue if locked
		**/
		virtual bool8 GetInsertLock(bool8 checkParent = kTrue) const= 0;
		
		/**
			Sets the attribute lock used to determine is attribute changes are allowed.
			@param lock kTrue to set the attribute lock
		**/
		virtual void SetAttributeLock(bool8 lock) = 0;
		/**
			Get the attribute lock.  If item is an inline the parent's lock is returned
			unless otherwise specified.
			@param checkParent kFalse to return inline's lock rather than it's parent's lock
			@return kTrue if locked
		**/
		virtual bool8 GetAttributeLock(bool8 checkParent = kTrue) const= 0;
};
 
#endif //__IItemLockData__