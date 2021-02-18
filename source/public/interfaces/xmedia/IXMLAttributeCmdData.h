//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLAttributeCmdData.h $
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
//  
//========================================================================================

#pragma once
#ifndef __IXMLAttributeCmdData__
#define __IXMLAttributeCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"
#include "WideString.h"

/** Data interface for working with the attribute of an XML element; if you're writing client code, work with
	IXMLAttributeCommands, and you won't need this interface.
*/
class IXMLAttributeCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLATTRIBUTECMDDATA };

	/**	Specify the element whose attribute should be modified and parameters required to execute the command to change attribute.
		@param element specifies the target element whose attribute is going to be changed by the command
		@param name identifies the attribute
		@param value specifies the value
		@param removable kTrue if the element can be deleted from client code, kFalse otherwise 
	 */
	virtual void Set(const XMLReference& element, const WideString& name, const WideString& value, bool16 removable = kTrue) = 0;
	
	/**	Return the element that owns the attribute
		
		@return XMLReference to element owning attribute 
	 */
	virtual const XMLReference& GetElement() const = 0;

	/**	Accessor for name of element cached on this interface
		
		@return  the name of the attribute 
	 */
	virtual const WideString& GetName() const = 0;
	
	/**	Accessor for value of attribute cached on this interface
		
		@return  the value of the attribute 
	 */
	virtual const WideString& GetValue() const = 0;

	/**	Accessor for the removability of an attribute stored through this interface
		
		@return kTrue if the attribute can be deleted, kFalse otherwise
	 */
	virtual const bool16 GetRemovable() const = 0;
};

#endif
