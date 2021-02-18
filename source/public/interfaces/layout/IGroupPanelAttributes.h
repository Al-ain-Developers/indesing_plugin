//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGroupPanelAttributes.h $
//  
//  Owner: Dave Burnard (was Tom Taylor)
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
#ifndef __IGroupPanelAttributes__
#define __IGroupPanelAttributes__

#include "IControlView.h"

/** An interface used in conjunction with the Group Panel widget (kGroupPanelWidgetBoss).
		For example a group of related checkbox controls with a titled frame, here, the border widget draws the title.
*/
class IGroupPanelAttributes : public IPMUnknown
{
public:
	// ----- Query -----
	enum { kDefaultIID = IID_IGROUPPANELATTRIBUTES };
	
	/** Get the widget id of the widget to use in the top left border of the GroupPanel.  
			The widget can have sub-widgets.  If GetBorderWidgetID returns 0,
			a simple framed border will be drawn.

		@return the widget id
	*/
	virtual WidgetID	GetBorderWidgetID() const = 0;

	/**	Sets the widget id of the widget to use in the top left border of the GroupPanel.
			Note: Setting the widgetID does not automatically cause the GroupPanel to position
			the border widget. To ensure that the new widget is used, you must force the
			dialog to re-layout.
		@param widgetID  - the widget id of the widget to use in the top left border of the GroupPanel.
		@return void 
	 */
	virtual void		SetBorderWidgetID(const WidgetID& widgetID) = 0;
};

#endif
