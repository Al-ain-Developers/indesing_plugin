//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGroupCmdData.h $
//  
//  Owner: robin briggs
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
//  PageItem Grouping command data interface
//  
//========================================================================================

#pragma once
#ifndef __IGroupCmdData__
#define __IGroupCmdData__

#include "IPMUnknown.h"
#include "GroupID.h"

class UIDList;

/**
   This interface is used to cache the data for kGroupCmdBoss.

   The command data includes UIDList of items to group together.
*/
class IGroupCmdData : public IPMUnknown
{
public:
	/**
		Define the default IID for IGroupCmdData.
	*/
	enum { kDefaultIID = IID_IGROUPCMDDATA };

	/**	
		Set the UIDList of items to group together. This data interface
		owns the item list and will delete it in its destructor. The UIDList
		passed to Set should be heap-allocated (with new).

		@param UIDList refers to children to group together.
		@return void 
	 */
	virtual void Set(UIDList* children) = 0;

	/**	
		Get UIDList of items to group together. 
		@return UIDList items to group together.
	 */
	virtual const UIDList *GetChildren() = 0;

	/**	
		Sort the list of children into Z-order. Used internally by the group command.
		@return void
	 */
	virtual void SortChildren() = 0;
};

#endif
