//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyXMLValue.h $
//  
//  Owner: Frank Rubino
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
//  IInCopyXMLValue.h - an XML element with one attribute, named "value"
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IInCopyXMLValue__
#define __IInCopyXMLValue__

#include "InCopyWorkflowID.h"

#include "IPMUnknown.h"
#include "WideString.h"

class IInCopyXMLValue : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYXMLVALUE };
	
	/** The name of this element; this is different from the attribute name,
		which is always kXMLValueAttr. Third parties wishing to namespace their
		attribute element names must pass back a uri for their namespace.
		@param localName
		@param qName
		@param uri
	*/
	virtual void GetName(WideString *localName, WideString *qName, WideString *uri) = 0;

	/** For importing old file data.
		@param version The version to use while parsing.
	*/
	virtual void SetStoryVersion(const UIDRef& storyRef, const PMReal& version) = 0;

	/** Set the interface from the specified value.  This is done while writing the file.
		@param value The value to output.
	*/
	virtual void SetVal(const WideString& value) = 0;
	/** Create the string of the current interface's value.
		@param value The returned string.
	*/
	virtual void GetVal(WideString *value) = 0;

	/** Set the name of this element from the actual XML instead of looking it up based on the boss.
		This facilitates versioning as bosses change.
		@param name The local name as encountered in the file.
	*/
	virtual void SetLocalName(const WideString& name) = 0;
};

#endif
