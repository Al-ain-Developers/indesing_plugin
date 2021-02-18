//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyXMLElementProvider.h $
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
#ifndef __IInCopyXMLElementProvider__
#define __IInCopyXMLElementProvider__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"

#include "IXMLOutStream.h"

class IInCopyXMLElementHandler;
class IInCopyXMLElementAttr;

class IInCopyXMLElementProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYXMLELEMENTPROVIDER };

	// This method is called during export of a story to the xml out stream.  During
	// import this interface is asked to handle the element.  Make sure the provider
	// uses the same element name on import and export.
	virtual void ExportData 
					(
						const UIDRef&	storyRef,
						IXMLOutStream* 	stream
					) = 0;


	// This method is called during import.  Return an IInCopyXMLElementHandler if this
	// provider supports the named element, otherwise returns nil
	virtual IInCopyXMLElementHandler* QueryElementHandler
					(
						const UIDRef&			storyRef,
						const WideString&		localName,
						const WideString&		qName,
						const WideString&		uri,
						IInCopyXMLElementAttr*	iAttrs
					) = 0;


				
};


#endif // __IInCopyWorkflow__



