//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/IActionMenuService.h $
//  
//  Owner: Tim Wright
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
//  Comments: Gathers menu items and order for events...
//  
//========================================================================================

#pragma once
#ifndef __IActionMenuService_h__
#define __IActionMenuService_h__

#include "IPMUnknown.h"
#include "BehaviorUIID.h"

class IActionMenuManager;

//========================================================================================
// CLASS IActionMenuService
//========================================================================================

/** A service interface that allows you to specify a menu name
	and menu order for any event or action.

	You specify names and order for any events in AddEventMenuItems
	You specify names and order for any behaviors in AddBehaviorMenuItems

	This service works in tandem with IActionMenuManager.
	@see IActionMenuManager
*/
class IActionMenuService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IACTIONMENUSERVICE };
	
	/** Specify names and order for all the menu items for all the events that this service
		is responsible for to IActionMenuManager, using AddEventMenuItem, AddEventSeparatorItem
	 	
	 	@param inEventMenuMgr call AddEventMenuItem, AddEventSeparatorItem on this interface
	 						  to specify name and ordering for the menu items
	 */ 
	virtual void AddEventMenuItems(IActionMenuManager* inEventMenuMgr) = 0;

	/** Specify names and order for all the menu items for all the behaviors that this service
	 	is responsible for.
	 	@param inEventMenuMgr call this interface to specify name and ordering for the menu items
	 */ 
	virtual void AddBehaviorMenuItems(IActionMenuManager* inEventMenuMgr) = 0;
};

#endif // __IActionMenuService_h__
