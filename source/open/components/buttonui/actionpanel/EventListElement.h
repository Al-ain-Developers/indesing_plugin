//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/EventListElement.h $
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
#ifndef __EventListElement_h__
#define __EventListElement_h__

#include "PMString.h"
#include "BehaviorTypes.h"

//========================================================================================
// CLASS EventListElement
//========================================================================================

class EventListElement
{
public:
	typedef object_type data_type;

	EventListElement() :
		fEvent(0)
	{
	}
	
	EventListElement(const ActionEvent& event, const PMString& name) :
		fEvent(event),
		fName(name)
	{
	}
	
	EventListElement(const EventListElement& other) :
		fEvent(other.fEvent),
		fName(other.fName)
	{
	}
	
	EventListElement& operator=(const EventListElement& other)
	{
		if (this != &other)
		{
			fEvent = other.fEvent;
			fName = other.fName;
		}
		
		return *this;
	}

	ActionEvent GetEvent() const
	{
		return fEvent;
	}

	PMString GetName() const
	{
		return fName;
	}
	
public:
	ActionEvent		fEvent;
	PMString		fName;
};

#endif // __EventListElement_h__
