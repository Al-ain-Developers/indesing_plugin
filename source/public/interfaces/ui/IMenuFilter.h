//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMenuFilter.h $
//  
//  Owner: lance bushore
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
#ifndef __IMenuFilter__
#define __IMenuFilter__

#include "IPMUnknown.h"
#include "ActionID.h"

/** This Interface allows plugin writers to change existing menus at the time they are added. Typically this is used to either remove menu items completely(usually in conjunction with an IActionFilter)
	or to move a menu item to a different location.
	To get your	menu filter implementation called, you must put it one a boss that supports kMenuFilterService, like so:
	Class
	{
		kMacOSXMenuFilterBoss,
		kInvalidClass,
		{
			IID_IK2SERVICEPROVIDER,		kMenuFilterProviderImpl,
			IID_IMENUFILTER,			kMySpiffyMenuFilterImpl,
			IID_IPMPERSIST,				kPMPersistImpl,
		}
	};

*/

class IMenuFilter : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMENUFILTER };

	/** Anything which calls IMenuManager::AddMenuItem will call all menu filters to allow them to change anything about the menu item being added.
		@param actionID This is a pointer to the ActionID. The action filter is free to change this to some other ActionID to cause this menu item to invoke a different action.
		@param menuPath This is a pointer to the menu path. The action filter is free to change this to some other path to change where in the menu this item will appear.  If the menuPath is changed to "" it will not be added.
		@param menuPos This is a pointer to the menu position. This controls where on this menu the item will appear. The menu filter is free to change this to a different value.
		@param isDynamic Indicates if this is a 'dynamic' menu item or not. Dynamic menu items are just placeholders for menus which need to be built at display time. @see IDynamicMenu
		@param isOwnerDraw Indicates if the menu item does custom drawing.
	*/
		virtual void	FilterMenuItem(ActionID* actionID, PMString* menuPath, PMReal* menuPos,bool16 isDynamic, bool16 isOwnerDraw)= 0;		
};

#endif // __IMenuFilter__
		