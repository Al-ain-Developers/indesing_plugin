//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLSetElementTagCmdData.h $
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
#ifndef __IXMLSetElementTagCmdData__
#define __IXMLSetElementTagCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/**
	Data interface for setting tags for elements in the logical structure tree;
	 from client code- use IXMLElementCommands, which processes the low-level commands that use this interface.

*/
class IXMLSetElementTagCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXMLSETELEMENTTAGCMDDATA };

		/**	Set up target element, and tag to use
			@param xmlElementRef XML element to set tag for
			@param tagString name of XML tag to set
		 */
		virtual void Set(const XMLReference& xmlElementRef, const WideString& tagString) = 0;
		
	
		/**	Set up target element, and tag to use
			@param xmlElementRef XML element to set tag for
			@param tagUID XML tag to set (IXMLTag)
		 */
		virtual void Set(const XMLReference& xmlElementRef, UID tagUID) = 0;

		/**	Accessor for element whose tag is being set
			@return XMLReference stored in this interface 
		 */
		virtual const XMLReference& GetElementRef(void) const = 0;
		
		/**	Accessor the tag to set stored on this interface
			@return UID of tag stored on this
		 */
		virtual UID GetTagUID(void) const = 0;	
};

#endif	// __IXMLSetElementTagCmdData__

