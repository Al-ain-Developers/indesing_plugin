//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyXMLElementAttr.h $
//  
//  Owner: Jeff Argast
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
#ifndef __IInCopyXMLElementAttr__
#define __IInCopyXMLElementAttr__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"
#include "WideString.h"


class IInCopyXMLElementAttr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYXMLELEMENTATTR };

	// localName = the local part of the element name
	// qName 	 = the qualified element name

	//For internal use only.  Clients should not call this method
	virtual void Initialize (void* privateData) = 0;

	// return the number of attributes in the interface
	virtual int32 Length () const = 0;

	// Get the Nth localName
	virtual void GetNthLocalName (int32 n, WideString* localName) const = 0;

	// Get the Nth qualified Name
	virtual void GetNthQName (int32 n, WideString* qName) const = 0;

	// Get the Nth attribute value
	virtual void GetNthValue (int32 n, WideString* attrValue) const = 0;

	// Get the value associated with the attribute qName.  returns kTrue if found, kFalse
	// if not found
	virtual bool16 GetValue (const WideString& qName, WideString* attrValue) const = 0;
			bool16 GetValue (const UTF16TextChar* qName, WideString* attrValue) const
				{ return this->GetValue(WideString(qName), attrValue); }
};


#endif // __IInCopyWorkflow__



