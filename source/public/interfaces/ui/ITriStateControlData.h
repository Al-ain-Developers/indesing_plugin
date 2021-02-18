//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITriStateControlData.h $
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
#ifndef __ITriStateControlData__
#define __ITriStateControlData__

#include "widgetid.h"
/** 	This interface handles the data for widgets with 3 possible states. The most common widgets that use this data interface are
	Radio buttons and Checkboxes.
	@see ITriStateData
*/
class ITriStateControlData : public IPMUnknown
{
	public:
		/** enum for DefaultIID to make UseDefaultIID() work for this interface */
		enum	{ kDefaultIID = IID_ITRISTATECONTROLDATA };
		
		/** 3 possible states for the widget */
		typedef enum { kUnselected, kUnknown, kSelected } TriState;

	/**	Set the state of the widget to be kSelected. Optionally invalidate and notify observers */
	virtual void		Select(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**	Set the state of the widget to be kUnselected. Optionally invalidate and notify observers */
	virtual void		Deselect(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**	Set the state of the widget to be kUnknown. Optionally invalidate and notify observers */
	virtual void		SetUnknown(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	/**	Set the state of the widget to a new state. Optionally invalidate and notify observers */
	virtual void		SetState(TriState newState,bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
	
	/** Check if the state of the widget is currently kSelected */
	virtual bool16		IsSelected() const = 0;

	/** Check if the state of the widget is currently kUnselected */
	virtual bool16		IsDeselected() const = 0;

	/** Check if the state of the widget is currently kUnknown */
	virtual bool16		IsUnknown() const = 0;
	
	/** Get the current state of the widget */
	virtual TriState	GetState() const = 0;
};

#endif
