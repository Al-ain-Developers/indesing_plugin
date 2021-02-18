//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IInLineEditWidgetAttributes.h $
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
#ifndef __IInLineEditWidgetAttributes__
#define __IInLineEditWidgetAttributes__

#include "widgetid.h"

/** IInLineEditWidgetAttributes interface.
 
	InLineEdit widget consists of two parts: a static text widget and editing widget.
	Under certain event (double click, click-pause-click et al.), static text can 
	be edited by editing widget. Usually we use pre-defined widgets for both parts. 
	By implementing this interface, user can plugin custom widget for either part.
	Please see InLineEdit widget defition for detail.
*/
class IInLineEditWidgetAttributes : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IINLINEEDITWIDGETATTRIBUTES };

	/** Get class ID for static text widget. 
		@return ClassID of static text widget
	*/
	virtual ClassID		GetStaticWidgetClassID() const = 0;

	/** Get resource ID for static text widget. 
		@return resourceID of static text widget
	*/
	virtual int32		GetStaticWidgetResourceID() const = 0;

	/** Get class ID for editing widget. 
		@return ClassID of editing widget
	*/
	virtual ClassID		GetEditingWidgetClassID() const = 0;

	/** Get resource ID for editing widget. 
		@return resourceID of editing widget
	*/
	virtual int32		GetEditingWidgetResourceID() const = 0;
};

#endif
