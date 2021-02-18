//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CLinkObject.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  Pure virtual base class that all ILinkObject derived classes should inherit.
//  
//========================================================================================

#pragma once
#ifndef __CLinkObject__
#define __CLinkObject__

// ----- Includes -----
#include "CPMUnknown.h"
#include "ILinkObject.h"

#include "ILink.h"
#include "UIDList.h"

class IPMStream;


/**
 CLinkObject is a pure virtual base class that inherits from ILinkObject and maintains
 and persists a list of the links referenced by the object.  The class also stores and
 persists the client identifier of the link object.

 All classes that implement the ILinkObject interface should inherit
 from the CLinkObject class.

 @see ILinkObject
 */
class PUBLIC_DECL CLinkObject : public CPMUnknown<ILinkObject>
{
public:
    typedef CPMUnknown<ILinkObject> inherited;
	typedef object_type data_type;

	CLinkObject(IPMUnknown* boss);
	virtual ~CLinkObject();

	virtual LinkClientID GetClientID() const { return fClientId; }

	virtual bool IsDirectLink() const { return true; }
	virtual IPMUnknown* QueryLinkedObject(const PMIID& interfaceId) const;

	virtual bool CanUpdate(const ILinkResource* iResource, UID linkUID, UIFlags uiFlags, ErrorCode& err) const { return true; }

	virtual ClassID GetImportProvider(const ILinkResource* iResource, UID linkUID) const { return kInvalidClass; }
	virtual ClassID GetExportProvider(const ILinkResource* iResource, UID linkUID) const { return kInvalidClass; }
	virtual ClassID GetResolveProvider(const ILinkResource* iResource, UID linkUID) const { return kInvalidClass; }

	virtual UIDList GetLinks() const { return fLinkRefs; }

	virtual void MarkLinksModified() const;
	virtual void ClearLinksModified() const;

	/**
	 If you override this implementation, please ensure you either write the UID of 
	 any link that points to this link object, or call into this implementation. This is needed 
	 to ensure the link relationships are (re)created when copying and pasting within and between
	 documents.
	 @see ILinkObject
	 */
	virtual void ReadWrite(IPMStream* s, ImplementationID prop);

protected:
	/**
	 The object's link client identifier. Objects are only allowed to link with
	 links and resource that have the same client identifier.
	 */
	LinkClientID	fClientId;

private:
	virtual void AddLinkRef(UID linkUID);
	virtual void RemoveLinkRef(UID linkUID);

	void SetLinksObjectModificationState(ILink::ObjectModificationState modState) const;

	UIDList	fLinkRefs;
};

#endif // __CLinkObject__
