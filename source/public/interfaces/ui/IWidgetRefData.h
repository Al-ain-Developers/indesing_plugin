//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWidgetRefData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IWidgetRefData_h__
#define __IWidgetRefData_h__

#include "IPMUnknown.h"
#include "PMRect.h"

/** IWidgetRefData is an interface used to hold a reference to a widget, without holding
	the widget in memory. The referenced widget should be a child widget.
 */
class IWidgetRefData : public IPMUnknown
{
public:
	// ----- Accessors -----

	/** Set initializes the interface to reference a widget.
		@param widgetId is the id of the widget
		@param frame is the bounds of the widget
		@param visibe is the widget visible
		@param enabled is the widget enabled
	*/
	
	virtual void			Set(const WidgetID& widgetId, const PMRect& frame,
								Bool16 visible, Bool16 enabled) = 0;

	/** GetWidgetId returns the widget id
		@return the id
	*/
	
	virtual WidgetID		GetWidgetId() const = 0; 
	
	/** GetFame returns the frame
		@return the frame
	*/
	virtual PMRect			GetFrame() const = 0;
	
	/** IsVisible returns the visiblity of the widget
		@return the visibility
	*/
	
	virtual Bool16			IsVisible() const = 0;
	
	/** IsEnabled returns the enable state of the widget
		@return the state
	*/
	
	virtual Bool16			IsEnabled() const = 0;
	
	/** ApplyValuesToWidget applies the values in this reference to the widget
	*/
	virtual void			ApplyValuesToWidget() = 0;
};

#endif // __IWidgetRefData_h__

