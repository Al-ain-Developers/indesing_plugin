//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGrabBehavior.h $
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
#ifndef __IGrabBehavior__
#define __IGrabBehavior__

#include "IPMUnknown.h"
#include "ContentDropperID.h"

/** Interface used to determine how a grab operation behaves over a particular page item.
	A base implementation is defined in CGrabBehavior; most subclassers should start there.
*/
class IGrabBehavior : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IGRABBEHAVIOR};

	/** Types of place given various UI gestures */
	enum eGrabType {
		/** Grab as a single item */
		kGrabSingle, 
		/**  */
		kGrabNeedfulSet 
	};


	/** Can the source item be grabbed as NeedfulSet 
		@return true if "this" could have items in NeedfulSet
	*/
	virtual bool16		CanFormNeedfulSet() const = 0;	

	/** Returns UIDList of elements that would be part of the NeedfulSet for this item.
		It does not include the item's own UID. 
		Only the items that should be part of set for this item are returned
	*/

	virtual UIDList		GetNeedfulSet() const = 0;


	/** Returns UID of the outermost element that has IID_IGRABBEHAVIOR interface defined on it
	*/
	virtual UID			GetRootUID() const = 0;

};

#endif //__IGrabBehavior__
