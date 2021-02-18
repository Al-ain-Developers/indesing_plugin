//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IAssociatedWidgetAttributes.h $
//  
//  Owner: Lin Xia
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
#ifndef __IAssociatedWidgetAttributes__
#define __IAssociatedWidgetAttributes__

#include "IPMUnknown.h"
#include "widgetid.h"

class  IAssociatedWidgetAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSOCIATEDWIDGETATTRIBUTES };

	/**	Sets the widget id of this widget's associated widget.
		@param associatedWidget - the widget id of the widget to put focus on when clicked.
		@return void 
	 */
	virtual void		SetAssociatedWidgetID(const WidgetID& associatedWidget) = 0;

	/**	Returns the WidgetID for this widget from SetAssociatedWidgetID().
		@return WidgetID 
	 */
	virtual WidgetID	GetAssociatedWidgetID() const = 0;

	/**	Sets the action id for this widget to execute when Option/Alt + clicked.
		@param associatedAction - the action id of the action to called when widget id Option/Alt clicked.
		@return void 
	 */
	virtual void		SetAssociatedActionID(const ActionID& associatedAction) = 0;

	/**	Returns the ActionID for this widget from SetAssociatedActionID().
		@return ActionID 
	 */
	virtual ActionID	GetAssociatedActionID() = 0;
};	

#endif // __IAssociatedWidgetAttributes__
