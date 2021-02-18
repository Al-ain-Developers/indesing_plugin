//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTag.h $
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
//  Interface for storing and accessing a XML tag
//  
//========================================================================================

#pragma once
#ifndef __IXMLTag__
#define __IXMLTag__

#include "IPMUnknown.h"
#include "XMLID.h"

class PMString;
/** Represents the tag associated with an XML element (IIDXMLElement); use IXMLTagCommands to modify.
	See <a href="http://www.w3c.org/TR/2000/REC-xml-20001006#NT-Name">XML 1.0 specification</a> for
	more detail on names for elements.

	
	
*/
class IXMLTag : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLTAG };

	/** Mutator for name; use IXMLTagCommands methods to modify name from client code.
		
		@param tagName specifies the new tag name 
	*/
	virtual void SetTagName(const WideString& tagName) = 0;
	
	/** Accessor for name of tag, minus enclosing begin/end markers. 
		For instance, this could be something like Headline; the element name 
		without any begin/end markers.
		@return the name of this tag minus begin/end markers
	*/	
	virtual const WideString& GetTagName() const = 0;	
	
	/** Accessor for the start tag, including the begin/end markers.
		For instance, this could be something like &lt;Headline&gt;. 
		This is named STag in the XML 1.0 specification.
		@return start tag
	*/
	virtual WideString GetBeginTag() const = 0;		
	
	/** Accessor for the end tag, including the begin/end markers.
		For instance, &lt;/Headline&gt;. This is named ETag in the XML 1.0 specification.
		@return end-tag
	*/
	virtual WideString GetEndTag() const = 0;	

	/** Accessor for begin-marker, i.e. &lt;
		@return character sequence "&lt;
	*/
	virtual WideString GetBeginMarker() const = 0;
	
	/** Accessor for end-tag marker, ie. &gt;
		@return character sequence "&gt;"
	*/
	virtual WideString GetEndMarker() const = 0;	
	
	/** Accessor for character sequence that marks ETag, i.e. "/"
		@return the character sequence "/"
	*/
	virtual WideString GetSlashMarker() const = 0;

	/** Mutator for locking and unlocking the tag name. Lock state is ref counted
		@param lock kTrue to apply lock. kFalse to remove lock
	*/
	virtual void LockName(bool16 lock) = 0;

	/** Accessor for determine whether the tag name is locked
		@return whether the tag name is locked
	*/
	virtual bool16 NameLocked(void) const = 0;
};



#endif
