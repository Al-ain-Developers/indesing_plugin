//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImporterDOM.h $
//  
//  Owner: Lonnie Millett
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

#ifndef __IXMLImporterDOM_h__
#define __IXMLImporterDOM_h__

#include "XMLID.h"

class IIDXMLDOMDocument;
        /**
        Used as a storage class to hold a pointer to an IIDXMLDOMDocument
		object. This class owns the pointer once it takes control. Clients
		can ask for a pointer to the data but they are expected to NOT
		delete that pointer.
        */
class IXMLImporterDOM : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLIMPORTERDOM };

	/**
		Set the current IIDXMLDOMDocument
		@param document - Pointer to the object
		NOTE: This class will own the pointer from
		Now on.
	*/
	virtual void SetDocumentDOM(IIDXMLDOMDocument *document) = 0;

	/**
		Get a pointer to the current IIDXMLDOMDocument
		@return - a pointer to the current DOM Document
		NOTE: You do NOT own this pointer. Do not delete
		it!
	*/ 
	virtual IIDXMLDOMDocument *GetDocumentDOM() const = 0;
};

#endif