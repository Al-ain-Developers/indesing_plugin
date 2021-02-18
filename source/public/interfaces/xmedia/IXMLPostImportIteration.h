//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLPostImportIteration.h $
//  
//  Owner: Lin Xia
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
#ifndef __IXMLPostImportIteration__
#define __IXMLPostImportIteration__


#include "XMLID.h"


class IIDXMLElement;
class IPostImportResponderData;
class IIDXMLDOMNode;

/** An interface used by XMLPostImportIterationResponder.
    Client code that wants to iterate the imported elements depth-first during the post-import phase
	of XML import can regiester for	kXMLPostImportIterationService and implement this interface.

	@see kXMLImporterPostImportMappingBoss for an example
*/	
class IXMLPostImportIteration : public IPMUnknown
{
	public:
		enum	{ kDefaultIID = IID_IXMLPOSTIMPORTITERATION };

		/** This method is called by XMLPostImportIterationResponder during the setup period. 
			XMLPostImportIterationResponder asks each services on whether it wants to be iterated. 
			If yes (returns kTrue), then the callbacks for iteration will be called. If no 
			(returns kFalse), then this service will not be called during iteration. The service 
			should return kFalse if it does not plan on performing any work during the iteration
			@param responderData The responder data from kXMLImporterPostImportSignalMgrBoss.
			@return bool16 kTrue if this service should be iterated. kFalse if this service should 
			not be iterated
		*/
		virtual bool16 ShouldIterate(IPostImportResponderData* responderData) = 0;

		/** This method is called by XMLPostImportIterationResponder before the depth-first iteration.
			@param responderData The responder data from kXMLImporterPostImportSignalMgrBoss.
			@return kSuccess if succeeds. Otherwise an error code.
		*/
		virtual ErrorCode BeforeIteration(IPostImportResponderData* responderData) = 0;

		/** This method is called by XMLPostImportIterationResponder during the depth-first iteration.
			One possible usage of this method is to map the element's tag to a style.
			@param element The element being iterated.
			@param domNode The corresponding DOM node to the element, if there is one. Could be nil.
			@return kSuccess if succeeds. Otherwise an error code.
		*/
		virtual ErrorCode HandleElement(IIDXMLElement* element, IIDXMLDOMNode *domNode) = 0;

		/** This method is called by XMLPostImportIterationResponder after the depth-first iteration.
			@return kSuccess if succeeds. Otherwise an error code.
		*/
		virtual ErrorCode AfterIteration() = 0;
};


#endif	// __IXMLPostImportIteration__

