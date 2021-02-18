//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLAttributeCommands.h $
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
//  Processes commands for creating, deleting, and manipulating XML element attributes.
//  
//========================================================================================

#pragma once
#ifndef __IXMLAttributeCommands__
#define __IXMLAttributeCommands__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

class ICommand;
	
/** Exposes methods to change the attributes present in the document logical structure.
*/
class IXMLAttributeCommands : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLATTRIBUTECOMMANDS};

	
		/**
		   Method for creating an XML element attribute. Some attributes are generated 
		   	automatically and should not be removed. If your attribute is one that should not be 
		   	deleted then set the removable paramter to kFalse. This and related methods may 
		   	process a command of type kXMLCreateAttributeCmdBoss behind the facade
		   @param element reference to the element the attribute will be added to
		   @param name the name of the attribute
		   @param value specifies the value of the attribute which should be added
		   @param removable set to kTrue if attribute should be able to be deleted 
		   @return ErrorCode kSucess if the operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode CreateAttribute(const XMLReference& element, const WideString& name, const WideString& value, bool16 removable = kTrue) = 0;


		/**
		   Method to delete an attribute.  This and related methods may process a command of type 
		   kXMLDeleteAttributeCmdBoss behind the facade
		   @param element reference to the element that the attribute is to be deleted from
		   @param name  the name of the attribute to delete
		   @return ErrorCode kSucess if the operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode DeleteAttribute(const XMLReference& element, const WideString& name) = 0;

		/**	Change the name of an attribute. This and related methods may process a command of 
			type kXMLSetAttributeNameCmdBoss behind the facade
			@param element reference to the element that the attribute is to be renamed
			@param name the name of the attribute to be changed
			@param newName the new name of the attribute
			@return ErrorCode kSucess if the operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode SetAttributeName(const XMLReference& element, const WideString& name, const WideString& newName) = 0;
		
		/**	Method to change the value of an attribute. This and related methods may process a 
			command of type kXMLSetAttributeValueCmdBoss behind the facade
			@param element reference to the element that the attribute value is to be changed
			@param name specifies the attribute whose value is to be changed
			@param value new value of the attribute
			@return ErrorCode  kSucess if the operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode SetAttributeValue(const XMLReference& element, const WideString& name, const WideString& value) = 0;
};
	
#endif // __IXMLElementCommands__
