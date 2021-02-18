//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CWidgetObserver.h $
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
#ifndef __CWidgetObserver__
#define __CWidgetObserver__

#include "CObserver.h"
#include "ITriStateControlData.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

/** This class provides a few handy routines useful to observers that deal with certian kinds of widgets.
*/
class WIDGET_DECL CWidgetObserver : public CObserver
{
public:
	/**	constructor
	*/
				CWidgetObserver(IPMUnknown *boss);
	virtual		~CWidgetObserver();

protected:
	
	/** Attach Helper Method. Simplifies attaching to another widget in the same window.
		@param widgetId The widget to attach to
		@param interestedIn which IID to attach to
		@param asObserver the IID of this observer. Usually this is IID_IOBSERVER, but when there are 2 or more observers on a widget, 
			only one gets to use IID_IOBSERVER
		@param widget a widget in the same widget hierarchy as the widget to attach to. If you pass nil, it is assumed that 'this' points 
			to a widget in the same hierarchy as the widget to attach to.
	*/
	void		AttachToWidget(const WidgetID& widgetId,
							   const PMIID& interestedIn = IID_IUNKNOWN, const PMIID& asObserver = IID_IOBSERVER,
							   IPMUnknown* widget = nil);
							   
							   
	/** Detach Helper Method. Simplifies detaching from another widget in the same window.
		@param widgetId The widget to detach from
		@param interestedIn which IID to detach from
		@param asObserver the IID of this observer. Usually this is IID_IOBSERVER, but when there are 2 or more observers on a widget, 
			only one gets to use IID_IOBSERVER
		@param widget a widget in the same widget hierarchy as the widget to detach from. If you pass nil, it is assumed that 'this' points 
			to a widget in the same hierarchy as the widget to detach from.
	*/
	void		DetachFromWidget(const WidgetID& widgetId,
							     const PMIID& interestedIn = IID_IUNKNOWN, const PMIID& asObserver = IID_IOBSERVER,
							     IPMUnknown* widget = nil);

	/** Helper method to set ITextControlData string
		@param widgetId the widget whose data you want to set.
		@param text the string to put on the widget
		@param widget a widget in the same hierarchy as the widget to set the data for. If you pass nil, 'this' is assumed to be a widget in the same hierarchy.
		@param invalidate should we invalidate the view when setting the data?
		@param notifyOfChange should we send out a notification when changing the data?
	*/
	virtual void							SetTextControlData(const WidgetID& widgetId, const PMString& text, IPMUnknown* widget = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);

	/** Helper method to get the string from the ITextControlData of some widget
		@param widgetId the widget whose data you want to get.
		@param widget a widget in the same hierarchy as the widget to get the data for. If you pass nil, 'this' is assumed to be a widget in the same hierarchy.
		@return the string from the ITextControlData of the requested widget
	*/
	virtual PMString						GetTextControlData(const WidgetID& widgetId, IPMUnknown* widget = nil) const;

	/** Helper method to set ITriStateControlData
		@param widgetId the widget whose data you want to set.
		@param triState the new state for the widget
		@param widget a widget in the same hierarchy as the widget to set the data for. If you pass nil, 'this' is assumed to be a widget in the same hierarchy.
		@param invalidate should we invalidate the view when setting the data?
		@param notifyOfChange should we send out a notification when changing the data?
	*/
	virtual void							SetTriStateControlData(const WidgetID& widgetId,const ITriStateControlData::TriState& triState, IPMUnknown* widget, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);

	/** Helper method to get the state from the ITriStateControlData of some widget
		@param widgetId the widget whose data you want to get.
		@param widget a widget in the same hierarchy as the widget to get the data for. If you pass nil, 'this' is assumed to be a widget in the same hierarchy.
		@return the state from the ITriStateControlData of the requested widget
	*/
	virtual ITriStateControlData::TriState	GetTriStateControlData(const WidgetID& widgetId, IPMUnknown* widget = nil) const;
};

#pragma export off

#endif
