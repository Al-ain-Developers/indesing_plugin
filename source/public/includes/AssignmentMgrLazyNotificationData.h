//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AssignmentMgrLazyNotificationData.h $
//  
//  Owner: Cindy Chen
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
#ifndef __AssignmentMgrLazyNotificationData__
#define __AssignmentMgrLazyNotificationData__

#include "UIDRef.h"
#include "Utils.h"

#include "TreeLazyNotificationData.h"
#include "IAssignmentUtils.h"

/** Used by the Assignment Panel Tree Widget to dirty (and clean) particular nodes
in the tree. 
*/

class AssignmentMgrLazyNotificationData : public TreeLazyNotificationData<UID>
{
public:
	/** Constructor
	@param db : database that the assignments belong to.
	*/
	AssignmentMgrLazyNotificationData(IDataBase *db) : TreeLazyNotificationData<UID>(), fDB(db)
	{
	}

	/** Destructor
	*/
	virtual ~AssignmentMgrLazyNotificationData()
	{
	}

private:
	virtual TreeLazyNotificationData<UID> *CreateNewCookie() const
	{ return new AssignmentMgrLazyNotificationData(fDB); }

	virtual bool16 GetParent(const UID &node, UID &parent) const
	{
		bool16 bFoundParent(kFalse);
	
		if (node != kInvalidUID)
		{
			UIDRef nodeRef(fDB, node);
			UIDRef parentRef(Utils<IAssignmentUtils>()->GetParent(nodeRef));
			if (parentRef != UIDRef::gNull)
			{
				parent = parentRef.GetUID();
				bFoundParent = kTrue;
			}
		}
		else
		{
			parent = node;
			ASSERT_FAIL("Why am I getting passed an invalid reference? This will probably hang in release.");
		}

		return bFoundParent;
	}

	IDataBase * fDB;
};

#endif