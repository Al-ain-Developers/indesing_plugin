//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyXMLElementHandler.h $
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
#ifndef __IInCopyXMLElementHandler__
#define __IInCopyXMLElementHandler__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"

class IInCopyImportOptions;
class IInCopyXMLElementAttr;
class IInCopyStoryContext;
class WideString;

class IInCopyXMLElementHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYXMLELEMENTHANDLER };

	// Initialize the element handler with the Story
	virtual void Initialize 
				(
					const UIDRef& 				storyRef,
					IInCopyImportOptions* options
				) = 0;
				
	// localName = the local part of the element name
	// qName 	 = the qualified element name

	// the iParentHandler is the parent handler on the stack.  If this is one of the root's sibling
	// element handlers then the parent will be nil.
	
	// When this element handler is active it is asked for a child element handler
	// for each element.  If it returns an element handler, the new handler is pushed on the stack
	// and its methods are called.  If it returns nil then this element handler is called.
	virtual IInCopyXMLElementHandler* QueryElementHandler
				( 
					const WideString& 			localName,
					const WideString& 			qName,
					const WideString&			uri,
					IInCopyXMLElementAttr*		iAttrs
				) = 0;
	
	// Receive the start element call.  This method is called for the element this handler is registered
	// for as well as all of its children. The data in iAttrs is not valid after returning from StartElement
	virtual void StartElement 
				( 
					IInCopyXMLElementHandler*	iParentHandler,
					const WideString& 			localName,
					const WideString& 			qName,
					const WideString&			uri,
					IInCopyXMLElementAttr*		iAttrs
				) = 0;

	// Text data from the element.  This may be called multiple times for the content
	virtual void Characters
				(
					IInCopyXMLElementHandler*	iParentHandler,
					const WideString&			chars
				) = 0;

	// The end element call will match the start element call.  
	virtual void EndElement 
				(
					IInCopyXMLElementHandler*	iParentHandler,
					const WideString& 			localName,
					const WideString& 			qName,
					const WideString&			uri
				) = 0;

	// Passes on the processing instruction
	// The target is the XML app identifier and the pinst is the content
	// of the instruction
	virtual void ProcessingInstruction
				(
					IInCopyXMLElementHandler*	iParentHandler,
					const WideString&			target,
					const WideString&			pinst
				) = 0;

	// Passes comments
	virtual void Comment
				(
					IInCopyXMLElementHandler*	iParentHandler,
					const WideString&			commentData
				) = 0;
				
	// Called to do post processing when a child element handler has finished.
	virtual void PostProcessChildHandler
				( 
					IInCopyXMLElementHandler*	iChildElementHandler,
					const WideString& 			localName,
					const WideString& 			qName,
					const WideString&			uri
				) = 0;
		
	// Called to return the associated story context.
	virtual IInCopyStoryContext *QueryStoryContext() = 0;
};


#endif // __IInCopyWorkflow__


