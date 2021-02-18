//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightObject.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PreflightObjectID.h"
#include "PackageAndPreflightID.h"

class IDocument;
class IDataBase;

/**	This interface is used to access various bits of information for a preflight object
	referene. A preflight object is simply a reference to something in the preflight model; 
	it could be a document, a spread, a page item, some text, part of an AGM artwork tree,
	whatever. The association between a PO and a 'physical' element that you can 
	ask questions of is provided by a preflight object association service. That
	service provider will create one of these interfaces via the service manager,
	typically by passing it a string that contains a sort of URL to the object.

	Typically you get one of these from the preflight manager, which given a class ID
	and object ID will ask the appropriate service to inflate one. Or you may get
	one passed into a method, such as when a rule is asked to evaluate a preflight
	object.

	Bear in mind that this reference can only be used for very short periods of time
	-- in particular, if the document changes in any way, you may be hosed.
	Realistically you shouldn't hold onto one of these.

	Note that depending on the service provider, this interface could be boss-based
	or not. It might be an interface on a real UID-based object, or just a temporary
	data structure.
*/

class IPreflightObject : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTOBJECT };

public:
	/** Set the object ID this interface is referring to.
		@param objID IN The object ID.
	*/
	virtual void SetID(const PreflightObjectID& objID) = 0;
	
	/** Get the object ID from which this interface was created.
		@return The object ID.
	*/
	virtual PreflightObjectID GetID() const = 0;
	
	/** Get the database to which this object belongs.
		@param forceIntoMemory IN If true, forces the document to be loaded if not in memory.
			If false, will return nil if the document isn't currently in memory.
		@return The database.
	*/
	virtual IDataBase* GetDataBase(bool forceIntoMemory = kFalse) const = 0;

	/** Get the document to which this object belongs.
		@param forceIntoMemory IN If true, forces the document to be loaded if not in memory.
			If false, will return nil if the document isn't currently in memory.
		@return The refcounted document interface.
	*/
	virtual IDocument* QueryDocument(bool forceIntoMemory = kFalse) const = 0;

	/** Iff this object maps directly into an InDesign model object, set the related object's 
		UIDRef. 

		@param modelRef IN The new UIDRef.
	*/
	virtual void SetModelRef(const UIDRef& modelRef) = 0;

	/** Iff this object maps directly into an InDesign model object, get the related object's 
		UIDRef. For example, a kPreflightOM_Document preflight object will return the UIDRef 
		of the document. A kPreflightOM_ArtworkMark preflight object will always return a
		nil UIDRef because there is no corresponding object.

		If this object doesn't map into an InDesign object, or does so only through a more
		complex mechanism, the object should provide an info interface which will provide
		a more explicit mapping.

		@param forceIntoMemory IN If true, force the document to be loaded in order
			to satisfy the request. If false, will return UIDRef() if the document is
			not currently open.
		@return A valid UIDRef, or UIDRef() if the document is not in memory or there is
			no corresponding model object.
	*/
	virtual UIDRef GetModelRef(bool forceIntoMemory = kFalse) const = 0;
};

