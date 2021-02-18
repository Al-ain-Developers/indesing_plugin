//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkObjectReference.h $
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
#ifndef __ILINKOBJECTREFERENCE__
#define __ILINKOBJECTREFERENCE__

#include "LinksID.h"

/**
   A data interface to allow links to access linked object.
*/
class ILinkObjectReference : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKOBJECTREFERENCE };

	/**	Set the UID stored in the interface.
		@param id IN specifies the uid of the linked object (for direct reference )
		 or a reference object (for indirect reference)
	 */
	virtual void SetUID(UID id) = 0; 

	/**	Return the stored UID
	 */
	virtual UID GetUID() const = 0; 

	/**	Return if this is a direct reference (the stored uid specifies the linked object)
	    or an indirect reference (the stored uid specifies a reference object, which points to the linked object)
		@return bool16 kTrue for direct reference, kFalse for indirect reference.
	 */
	virtual bool16 IsDirectReference() const = 0;

	/**	Query interface on the linked object. Client code should use this method to access the linked object.
		@param iid IN interested interface ID
		@param UID of the linked object (for direct reference) or the reference object (for indirect reference).
		       The method uses the stored UID if uid is kInvalidUID (default).
		@return IPMUnkown The requested interface if the object supports it. Nil otherwise.
		 AddRef is called on the interface, caller should release it.
		 Returns nil if the link hasn't been instantiated.
	 */
	virtual IPMUnknown*	QueryLinkedObject(const PMIID& iid, const UID& uid = kInvalidUID) const = 0;

	/**	Method to serialise object to or deserialise object from given stream
		@param iPMStream IN stream to read state from or write state to
		@param id IN the implementation ID of the steam data
	 */
	virtual void ReadWrite(IPMStream* iPMStream, ImplementationID id) = 0;
};

#endif // __ILINKOBJECTREFERENCE__
