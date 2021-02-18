//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDynamicMenu.h $
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
#ifndef __IDynamicMenu_h__
#define __IDynamicMenu_h__

#include "IPMUnknown.h"
#include "ActionID.h"

/**
	Provide a mechanism for menu items to rebuild before being displayed.
	Typical response is to add/remove actions, and add/remove/rename menus.
	@see IActionManager
	@see IMenuManager
*/
class IDynamicMenu : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDYNAMICMENU };

		/** Rebuild a dynamic menu to add/remove/change its items.
			@param dynamicActionID ID of menu hit just before this method is called.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
				to find widgets in a panel after its popup menu is hit. NB: Don't assume it's a widget from your panel (menu scripting may access any menu at any time).
		*/
	virtual void RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget = nil) = 0;
};

#endif // __IDynamicMenu_h__
