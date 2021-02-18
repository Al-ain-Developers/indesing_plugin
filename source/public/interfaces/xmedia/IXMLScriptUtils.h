//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLScriptUtils.h $
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

#pragma once
#ifndef __IXMLScriptUtils__
#define __IXMLScriptUtils__

#include "RequestContext.h"
#include "Utils.h"
#include "XMLID.h"
#include "XMLContentReference.h"

class IIDXMLElement;
class XMLReference;
class IScript;


/** Utilities for simplifying scripting XML items.
*/
class IXMLScriptUtils : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLSCRIPTUTILS};

		/**
		   Create a proxy script object to represent this XML item to the scripting world.
		   It may be an element, comment, or a PI.
		   @param xmlItemRef specifies XML item of interest
		   @parent the parent script. Use the default value nil if the parent is unknown.
		   @return IScript interface ptr that has its reference-count incremented 
		 */
		virtual IScript* CreateXMLItemProxyScriptObject(const ScriptInfo::RequestContext& context, const XMLReference& xmlItemRef, IPMUnknown* parent = nil) = 0;

		/**
		   Create a proxy script object to represent this XML attribute to the scripting world.
		   @param xmlItemRef specifies XML item of interest
		   @param name identifies the attribute of interest
		   @parent the parent script. Use the default value nil if the parent is unknown.
		   @return IScript interface ptr that has its reference-count incremented 
		 */
		virtual IScript* CreateXMLAttributeProxyScriptObject(const ScriptInfo::RequestContext& context, const XMLReference& xmlItemRef, const PMString& name, IPMUnknown* parent = nil) = 0;

		/**
		   Obtain the IIDXMLElement interface from a IScript interface; they are on different bosses 
		   @param script specifies interface on script boss object
		   @return IIDXMLElement interface ptr that has its reference-count incremented
		 */
		 
		virtual IIDXMLElement* QueryXMLElement(IScript* script) = 0;

		/**
		   Get the scripting object id of the specified XML item. Also get the
		   content that it points to.
		   @param xmlItemRef specifies XML item of interest
		   @param scriptID If not nil will be filled with the object's ScriptID
		   @param contentType If not nil will be filled with the object's content type
		 */
		virtual void GetXMLItemTypeAndContent(const XMLReference& xmlItemRef, ScriptID *scriptID = nil, XMLContentReference::ContentType *contentType = nil) = 0;
};
	
#endif
