//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLHandler.h $
//  
//  Owner: robin briggs
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
#ifndef IXMLHANDLER
#define IXMLHANDLER

#include "IPMUnknown.h"
#include "XMLID.h"

class IIDXMLElement;

/**  Handler interface, gets called for every element of the structure tree, when tree is iterated.
	One example is the export handler, which works in tandem with an IXMLGenerator, calling the methods on IXMLGenerator interfaces on
	elements (and heir content items, if they can generate XML to) in the
	structure tree interface to generate the XML output; e.g. when the handler gets HandleElementBefore, 
	it calls IXMLGenerator::GenerateBeginTag on the element, and then on the content item, if it has an IXMLGenerator.

 */
class IXMLHandler : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IXMLHANDLER };
	

	/**	Called before element processed. 
		@param element specifies current node in structure tree during traversal
	 */
	virtual void HandleElementBefore(IIDXMLElement *element) = 0;

	/**	Called after each child is processed. This is the place to do stuff in
		between child elements
		@param element specifies current node in structure tree during traversal
		@param childIndex index in parent of child 
	 */
	virtual void HandleAfterNthChild(IIDXMLElement *element, int32 childIndex) = 0;

	/**	Called after element processed. 
		For instance, the export handler calls IXMLGenerator::GenerateEndTag on the content item, then the element on this message.
		@param element specifies current node in structure tree during traversal
	 */
	virtual void HandleElementAfter(IIDXMLElement *element) = 0;
	};

#endif //IXMLHANDLER

