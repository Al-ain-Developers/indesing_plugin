//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLParsingContext.h $
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
//  
//  Purpose:
//  An interface for keeping track of the parsing information when importing XML content.
//  
//========================================================================================

#pragma once
#ifndef __IXMLParsingContext_h__
#define __IXMLParsingContext_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"
#include "XMLReference.h"
#include "XMLID.h"

/**
Interface for tracking the parsing context information necessary to
add XML content to an InDesign document.

When importing XML content, information about the current element, story,
and text insertion point are stored in an instance of this interface.  The
current parsing context information as well as a stack of previous parent
elements are managed and mainted by ISAXServices.

IParsingContext is an interface of the kXMLParserLocatorBoss and additional
parsing information can be stored by adding interfaces to this boss object.
        */

class IXMLParsingContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXMLPARSINGCONTEXT };
		
	    /**
	    Specify the context information

	    @param element			A reference to the XML Element being created.

	    @param tagName      	The tag name of the element.
	                            
	    @param childIndex		The index of where the element resides in its parent.
	    
	   	@param storyRef      	The story where the element will be created.
    
	   	@param insertPos      	The current insertion position for new elements or content in the context's story.
	    */
		virtual void Set(const XMLReference& element, const WideString& tagName, int32 childIndex, const UIDRef& storyRef, TextIndex insertPos, bool16 shouldInsert = kFalse) = 0;

	    /**
	    Specify the context information by copying another context.

	    @param parsingContext	The parsing context to be copied.
	    */
		virtual void Set(IXMLParsingContext* parsingContext) = 0;

	    /** Returns the element referred to by this context */
		virtual XMLReference GetElement() const = 0;
		
	    /** Specify the element that has been created.
	    
	    @param element	The newly created element.
	    */
		virtual void SetElement(const XMLReference& element) = 0;
		
	    /** Returns the tag name currently being parsed.  This will be the tag
	    name of the newly created element. */
		virtual WideString GetTagName() const = 0;
		
	    /** Specify the tag name of the newly created element.
	    
	    @param tagName	The tag name.
	    */
		virtual void SetTagName(const WideString& tagName) = 0;
		
	    /** Returns the index of where the element can be found in its parent. */
		virtual int32 GetChildIndex() const = 0;
		
	    /** Specify the child index of where the element can be found.
	    
	    @param childIndex	The child index of the element.
	    */
		virtual void SetChildIndex(int32 childIndex) = 0;

	    /** Returns a reference to the story that contains the element. */
		virtual UIDRef GetStoryRef() const = 0;
		
	    /** Specify the story which will be used when creating the element.
	    
	    @param storyRef	A reference to a story.
	    */
		virtual void SetStoryRef(const UIDRef& storyRef) = 0;
		
	    /** Returns the text index elements and content will be inserted into the story. */
		virtual TextIndex GetInsertPos() const = 0;

	    /** Specify the current insertion position for elements and content in context's story.
	    
	    @param insertPos	The current insertion position.
	    */
		virtual void SetInsertPos(TextIndex insertPos) = 0;

		virtual bool16 ShouldInsert() const = 0;
		virtual void SetShouldInsert(bool16 doInsert) = 0;
};

#endif