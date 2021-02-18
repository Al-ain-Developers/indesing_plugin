//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLAccess.h $
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
#ifndef IXMLACCESS
#define IXMLACCESS

#include "IPMUnknown.h"
#include "XMLID.h"

class IXMLHandler;
class IIDXMLElement;

/** Contains utilities for navigating and operating on the XML structure tree.
	Based around the Visitor pattern.
	
	One way to implement an operation that involves objects in a complex structure is to 
	provide logic in each of their classes to support the operation. 

	The Visitor pattern provides an alternative way to implement such operations 
	that avoids complicating the classes of the objects in the structure by putting 
	all of the necessary logic in a separate visitor class. 
	The Visitor pattern also allows the logic to be varied by using different visitor classes. 

	It can be regarded as a generalisation of the Iterator pattern; The Iterator pattern is an 
	alternative to the Visitor pattern when the object structure to be navigated has a linear structure; for
	instance, Iterator is used in IIDXMLElement to traverse only the children. Here we're interested in the entire
	sub-tree of dependents.


*/
class IXMLAccess : public IPMUnknown {
public:
	
	enum { kDefaultIID = IID_IXMLACCESS };
	

	/**	This method does the traverse of the subtree of the logical structure starting from rootElement.
		The methods on the handler (type IXMLHandler) will get called in sequence; every time an element (IIDXMLElement)
		gets visited, the same sequence of method calls will be sent out to the handler
		<ul>
		<li>HandleElementBefore sent to the handler
		<li>iterate over children; HandleAfterNthChild sent to the handler for each child
		<li>HandleElementAfter
		</ul>

		@param rootElement where to start traversing the tree from
		@param handler specifies the entity that will receive 'callbacks' (method calls on IXMLHandler) as each element is visited
	 */
	virtual void VisitAllElements(IIDXMLElement *rootElement, IXMLHandler *handler) = 0;
};


#endif //IXMLACCESS
