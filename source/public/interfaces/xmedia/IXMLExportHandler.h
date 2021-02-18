//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLExportHandler.h $
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
#ifndef IXMLEXPORTHANDLER
#define IXMLEXPORTHANDLER

#include "IPMUnknown.h"
#include "XMLID.h"

class IXMLOutStream;
class IIDXMLElement;

/** Export Handler interface, gets called for every element of the structure tree, when tree is iterated.
	this interface is on a service provider that provides service for kXMLExportHandlerSignalService. It
	gets asked whether or not it wants to export each element. It can respond yes (and will get called to
	handle) or no (and will not get called)

 */
class IXMLExportHandler : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IXMLEXPORTHANDLER };
	

	/**	Called before element processed to determine whether this interface wants to handle it. 
		@param element specifies current node in structure tree during traversal
		@return kTrue - Yes I will handle it : kFalse - No I will not
	 */
	virtual bool16 CanHandleElement(IIDXMLElement *element) = 0;

	/**	Called before element processed. 
		@param stream specifies the stream out export the element to
		@param element specifies current node in structure tree during traversal
		@return kTrue - I handled this element : kFalse - I did not handle this element
	 */
	virtual bool16 HandleElementBefore(IXMLOutStream* stream, IIDXMLElement *element) = 0;

	/**	Called after each child is processed. This is the place to do stuff in
		between child elements
		@param stream specifies the stream out export the element to
		@param element specifies current node in structure tree during traversal
		@param childIndex index in parent of child 
		@return kTrue - I handled this element : kFalse - I did not handle this element
	 */
	virtual bool16 HandleAfterNthChild(IXMLOutStream* stream, IIDXMLElement *element, int32 childIndex) = 0;

	/**	Called after element processed. 
		Use this to close the element after all of its children/content has been exported.
		@param stream specifies the stream out export the element to
		@param element specifies current node in structure tree during traversal
		@return kTrue - I handled this element : kFalse - I did not handle this element
	 */
	virtual bool16 HandleElementAfter(IXMLOutStream* stream, IIDXMLElement *element) = 0;
	};

#endif //IXMLEXPORTHANDLER

