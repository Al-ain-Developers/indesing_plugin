//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FormFieldSupportedEvents.h $
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
#ifndef __FormFieldSupportedEvents_h__
#define __FormFieldSupportedEvents_h__

#include "CPMUnknown.h"
#include "ISupportedEvents.h"
#include "FormFieldTypes.h"

//========================================================================================
// TEMPLATE FormFieldSupportedEvents
//========================================================================================

template <int32>
class FormFieldSupportedEvents : CPMUnknown<ISupportedEvents>
{
public:

	FormFieldSupportedEvents(IPMUnknown * boss) : CPMUnknown<ISupportedEvents>(boss) {}
	virtual bool16 SupportsMouseEvents() const { return kTrue; } //mouse up/down/over
	virtual bool16 SupportsFocusEvents() const { return kTrue; } //focus/blur
	virtual bool16 SupportsPageEvents() const { return kFalse; } //page open/close, we are kludging in support for these
																//by allowing page open/close events to be attached to form
																//fields.

	virtual bool16 SupportsFormatEvents() const { return kFalse; }  //format
	virtual bool16 SupportsKeystrokeEvents() const { return kFalse; }  //keystroke
	virtual bool16 SupportsValidateEvents() const { return kFalse; } //validate
	virtual bool16 SupportsCalculateEvents() const{ return kFalse; }  //calculate
	virtual bool16 SupportsSignedEvents() const { return kFalse; } //signed
	virtual bool16 SupportsSelectionChangedEvents() const { return kFalse; } //selection changed
	virtual bool16 SupportsDocumentEvents()  const { return kFalse; }  //doc open/ will/did close/save/print
	
	virtual bool16 SupportsMiscEvent( IBehaviorEvent* inEvent ) const { return kFalse; } //catchall for events that don't fit into above...
};

#endif // __FormFieldSupportedEvents_h__
