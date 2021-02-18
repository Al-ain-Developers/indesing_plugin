//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/IActionMenuManager.h $
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
#ifndef __IActionMenuManager_h__
#define __IActionMenuManager_h__

#include "IPMUnknown.h"
#include "BehaviorUIID.h"
#include "BehaviorID.h"
#include "BehaviorTypes.h"


class IDropDownListController;

//========================================================================================
// CLASS IActionMenuManager
//========================================================================================

/** Utility interface to specify a name and order for an event, when it is presented in a menu
	Also used to build an event menu. 
*/
class IActionMenuManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IACTIONMENUMANAGER };
	
	/** Specify a name and order for an ActionEvent (an event that can respond with behavior)
		@param inEvent the event being specified
		@param inName the name to be used for the event when it is in a menu.  If empty, the name
				used comes from IBehaviorEvent of the service that added the even
		@param inOrder the order to be used for the event when it is in a menu.  May be any double.
				Lower numbers mean the event appears earlier in the menu.  If zero, it will use the order
				of the kBehaviorEventService iteration order for the event item in the menu
	*/
	virtual void AddEventMenuItem(ActionEvent inEvent, const PMString& inName, double inOrder) = 0;
	
	/** Indicate that a separator should be placed before an event when it is placed in a menu.
		Used to group events by type.
		@param inEvent the event to place a separator before.
		@param inOrder not currently used.
	*/
	virtual void AddEventSeparatorItem(ActionEvent inBeforeEvent, double inOrder) = 0;

	/** Build an event menu that consists of events supported by the current selection, according
		to IBehaviorSuite.
		@see IBehaviorSuite, ISupportedEvents, ISupportedEventsService
		
		@param inDropDownList The drop down list that will contain the event menu items
		@param inSelectEvent The event to select in the menu.  If 0, the first item is left selected in the menu.
							if non-zero, that ActionEvent is selected, and the menu is disabled (used when editing an existing behavior).
	*/

	/* TODO: add methods to allow specifing the ordering of the behaviors, as well as the events... */

	virtual void BuildEventMenuSupportingSelection(IDropDownListController* inDropDownList, const ActionEvent& inSelectEvent) = 0;
};

//========================================================================================

/** Used internally by ActionMenuManager.  This is in the header file because it is used by a K2Vector template,
	which needs to be declared in Templates_BehaviorUI.cpp
*/
struct EventMenuInfo
{
  typedef object_type data_type;

	EventMenuInfo()
	: fName(),
		fOrder(0.0),
		fServiceIndex(0),
		fSeparator(false),
		fEvent(kNoEvt)
	{}
	
	EventMenuInfo(ActionEvent inEvent, const PMString& inName, double inOrder, int32 inServiceIndex, bool inSep)
		: fEvent(inEvent),
		fName(inName),
		fOrder(inOrder),
		fServiceIndex(inServiceIndex),
		fSeparator(inSep)
	{}

	ActionEvent fEvent;
	PMString fName;
	double	 fOrder;
	bool	 fSeparator;
	int32 	 fServiceIndex;
};

#endif // __IActionMenuManager_h__
