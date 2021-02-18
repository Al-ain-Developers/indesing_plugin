//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ActionSupportedEvents.h $
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
//  Comments: Implemention of ISupportedEvents for the basic form field types.
//  ISupportedEvents says whether an event type is supported.
//  
//========================================================================================

#pragma once
#ifndef __ActionSupportedEvents_h__
#define __ActionSupportedEvents_h__

#include "CPMUnknown.h"
#include "ISupportedEvents.h"
#include "FormFieldTypes.h"

//========================================================================================
// TEMPLATE ActionSupportedEvents
//========================================================================================

template <int32>
class ActionSupportedEvents : CPMUnknown<ISupportedEvents>
{
public:

	ActionSupportedEvents(IPMUnknown * boss) : CPMUnknown<ISupportedEvents>(boss) {}
	virtual bool16 SupportsMouseEvents() const { return kTrue; } //mouse up/down/over
	virtual bool16 SupportsFocusEvents() const { return kTrue; } //focus/blur
	virtual bool16 SupportsPageEvents() const { return kTrue; } //page open/close, we are kludging in support for these
																//by allowing page open/close events to be attached to form
																//fields.


	virtual bool16 SupportsDocumentEvents() const { return kFalse; } //only JavaScript actions support this event for now...

	virtual bool16 SupportsFormatEvents() const { return kFalse; }  //format
	virtual bool16 SupportsKeystrokeEvents() const { return kFalse; }  //keystroke
	virtual bool16 SupportsValidateEvents() const { return kFalse; } //validate
	virtual bool16 SupportsCalculateEvents() const{ return kFalse; }  //calculate
	virtual bool16 SupportsSignedEvents() const { return kFalse; } //signed
	virtual bool16 SupportsSelectionChangedEvents() const { return kFalse; } //selection changed
};

//-------------------------------------------------------------------------------

template <int32>
class NoSupportedEvents : CPMUnknown<ISupportedEvents>
{
public:

	NoSupportedEvents(IPMUnknown * boss) : CPMUnknown<ISupportedEvents>(boss) {}
	virtual bool16 SupportsMouseEvents() const { return kFalse; } //mouse up/down/over
	virtual bool16 SupportsFocusEvents() const { return kFalse; } //focus/blur
	virtual bool16 SupportsPageEvents() const { return kFalse; } //page open/close, we are kludging in support for these
																//by allowing page open/close events to be attached to form
																//fields.
	virtual bool16 SupportsDocumentEvents() const { return kFalse; } //only JavaScript actions support this event for now...

	virtual bool16 SupportsFormatEvents() const { return kFalse; }  //format/keystroke
	virtual bool16 SupportsKeystrokeEvents() const { return kFalse; }  //keystroke
	virtual bool16 SupportsValidateEvents() const { return kFalse; } //validate
	virtual bool16 SupportsCalculateEvents() const{ return kFalse; }  //calculate
	virtual bool16 SupportsSignedEvents() const { return kFalse; } //signed
	virtual bool16 SupportsSelectionChangedEvents() const { return kFalse; } //selection changed
};

#endif // __ActionSupportedEvents_h__
