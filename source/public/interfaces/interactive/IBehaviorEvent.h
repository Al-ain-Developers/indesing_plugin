//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IBehaviorEvent.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IBehaviorEvent_h__
#define __IBehaviorEvent_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"
#include "BehaviorTypes.h"

class ICommand;
class ISupportedEvents;

/** Base data interface for an Event that can have attached behaviors
	Examples are MouseDown, MouseUp, Calculate...
	@see BehaviorEvent
*/
class IBehaviorEvent : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIOREVENT };
	
	/** @return a user-readable name for the event e.g. "Mouse Down" */
	virtual PMString	GetName() const = 0;

	/** @return a unique enum for the event. Value is in kBehaviorEventIDSpace. e.g. kPageOpenEvt */
	virtual ActionEvent	GetEvent() const = 0;

	/** @return a PDF action dictionary key as a PMString for the event e.g. "U" for mouse up,
		used to generate the PDF action dictionary for actions that belong to this event */
	virtual PMString 	GetDictionaryKey() const = 0;
	
	/** @return kTrue if this is an event that applies to a page, such as Page Open or Page Close */
	virtual bool16 		IsPageEvent() const = 0;
	
	/** @return kTrue if IPMUnknown can 'respond' to events. IPMUnknown could be an IBehaviorData
		interface or a IFormField interface, but is not limited to this.  The default implementation
		queries an ISupportedEvents on the IPMUnknown to ask it if it supports event types matching
		this one.
	*/
	virtual bool16 		SupportsEvent(IPMUnknown* ) = 0;
};

#endif // __IBehaviorEvent_h__
