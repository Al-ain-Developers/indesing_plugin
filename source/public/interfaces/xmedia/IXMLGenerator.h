//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLGenerator.h $
//  
//  Owner: Robin Briggs
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
#ifndef __IXMLGenerator__
#define __IXMLGenerator__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "IXMLOutStream.h"

/** Interface representing cability to generate XML content. This is used by the export handler; see IXMLHandler.  */
class IXMLGenerator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLGENERATOR };
	

	/**	Generates the beginning tag and its attributes, and then calls generate content
		@param s stream where content written to 
	 */
	virtual void GenerateBeginTag(IXMLOutStream *s) = 0;

	/**	Collects the attributes that belong to a tag.  The stream is necessary so that we
		can access cached path information for converted assets.  Converted assets will
		have their href values replaced with the updated path information.
		@param s stream where content written to 
		@param attrs [OUT] parameter containing the attributes belonging to given boss object
	 */
	virtual void CollectAttributes(IXMLOutStream *s, IXMLOutStream::AttributeList *attrs) = 0;

	/**	Item generates a string of XML code that represents itself.
		@param s [OUT] parameter, stream where content written to 
		@param beforeChildIndex Generate the XML content that goes just before the child with index beforeChildIndex
		
		  For example: 
		  <pre>
		 &lt;element&gt;before child 0&lt;child0&gt;0&lt;/child0&gt;before child1&lt;child1&gt;
		</pre> 
	*/
	virtual void GenerateContent(IXMLOutStream *s, int32 beforeChildIndex = 0) = 0;
  
	/**	Generates ending tag
		@param s stream where content written to 
	 */
	virtual void GenerateEndTag(IXMLOutStream *s) = 0;

};


#endif	// __IXMLGenerator__


