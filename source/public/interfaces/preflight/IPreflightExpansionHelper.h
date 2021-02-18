//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightExpansionHelper.h $
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

class IPreflightOptions;
class IPreflightProcess;
class IPreflightObjectModelService;

/** This class works with the preflight object model services. These services provide the
	structure (the preflight DOM) that preflight rules visit. In order to create the DOM
	the preflight engine starts at the doucment node and asks the object model services to
	expand the children of each node, recursively.

	This class provides a number of services when an object model service is called back 
	via Expand(). Typically a service checks ShouldExpand() if it expands more than one
	child class for a given parent class (the Expand() call will not be made if the service
	does not purport to declare children that are interesting at the moment). It then calls
	AddChild for each child it knows about. It can also use the parent-child form of AddChild
	if it wants to expand an entire tree.

	@see IPreflightObjectModelService
	@see IPreflightOptions
*/
class IPreflightExpansionHelper
{
public:
	/** Constructor.
	*/
	IPreflightExpansionHelper() {}

	/** Virtual destructor.
	*/
	virtual ~IPreflightExpansionHelper() {}

	/** @return the preflight process this expansion is associated with.
	*/
	virtual IPreflightProcess* QueryProcess() const = 0;

	/** @return the preflight options associated with the process.
	*/
	virtual const IPreflightOptions* QueryPreflightOptions() const = 0;

	/** Results codes for the AddChild methos.
	*/
	enum 
	{ 
		/** Child wasn't in the database. */
		kAddedChildToDatabase = (1L<<1), 

		/** Child not added (and no link created) because the child (and any potential children 
			of it) are not required by the current set of rules.
		*/
		kChildNotRequired = (1L<<2),

		/** Child was removed as a TBD from another parent because a "true" parent was specified.
		*/
		kChildTBDLinkRemoved = (1L<<3),

		/** New link (either ownership, reference, or TBD, depending on call) added from parent to child.
		*/
		kNewLinkAdded = (1L<<4),

		/** There's already a link between the parent and child objects, so a new one wasn't added.
		*/
		kDuplicateLink = (1L<<5),

		/** Parent not found in the database (this can only happen for the parent/child form of AddChild).
			You'll need to anchor the parent to something that already exists in the database.
		*/
		kNoChangeBecauseParentNotFound = (1L<<6),

		/** The child was also added to the list of children to be expanded later. */
		kAddedChildToExpansionList = (1L<<8),

		/** The child was also added to the list of children to be visited later. */
		kAddedChildToVisitList = (1L<<9),

		/** Something bad happened.
		*/
		kInternalError = (1L<<30)

	};
	
	typedef uint32 AddResult; // A combination of the above flags

	/** Get the parent object, ie the one whose children should be enumerated. 
		@note You can expand as far down as is convenient via AddChild(parent, child).
		@return The object ID of the current parent.
	*/
	virtual const PreflightObjectID& GetParentObjectID() const = 0;

	/** Get the parent object, ie the one whose children should be enumerated. 
		@note You can expand as far down as is convenient via AddChild(parent, child).
		@return The IPreflightObject interface of the current parent. This is NOT refcounted (thus 'Get').
	*/
	virtual IPreflightObject* GetParentObject() const = 0;

	/** Get the database of the parent object. This is the same result as ::GetDataBase(GetParentObject()).
		@return The NON-refcounted database of the parent.
	*/
	virtual IDataBase* GetDataBase() const = 0;

	/** Given an object class ID, returns whether to expand into children of that type.
		@param childClassID IN The class you're wondering about.
		@return True if you should add objects of this class; false if not.
	*/
	virtual bool ShouldAdd(PreflightObjectClassID childClassID) const = 0;
	
	/** Given an object ID, returns whether it exists yet in the database.
		@param objID IN The object to look for.
		@return True if it exists; false if not.
	*/
	virtual bool ExistsInDatabase(const PreflightObjectID& objID) const = 0;
	
	/** Adds a child under the parent object.

		@param childID IN The child object.
		@param asReference IN True if the child is owned by the parent; false if this is simply
			a reference to the child object. One way to think of it is this: if you delete the parent,
			is the child implicitly deleted too? If so, it's ownership; if not, it's a reference.
			For example, a document owns its swatches; page items have references to those swatches.

		@return A result code indicating what change, if any, was made in the database as a result.
	*/
	virtual AddResult AddChild
		(
			const PreflightObjectID& childID, 
			bool asReference = kFalse
		) = 0;

	/** Adds an object to the database as a "owner/parent to be determined" object. In simple expansion
		cases the parent-child relationship is unambiguous and the child is always determined by 
		expanding the parent. But in more complex expansion cases you might discover children before
		the parents have been expanded; or it may be that it's much more practical to work from
		children to parents and so you need to create the parent, bind the object as a child of
		the parent, and then later discover the parents of the parents. This method allows you to
		put the object in the database with a "TBD" link from the specified anchor to the parent.
		Once a "true" parent child relationship is established later the TBD link is removed.

		@note You can call this even if the object is in the database already; in that case this
			method won't have any side effects. This saves you the trouble of calling 
			ExistsInDatabase before calling this.

		@param childID IN The child object.

		@return A result code indicating what change, if any, was made in the database as a result.
	*/
	virtual AddResult AddObjectWithTBDParent
		(
			const PreflightObjectID& childID
		) = 0;

	/** Call this method if your service was unable to expand the node in a reasonable amount of
		time or was interrupted. The node and service are placed in a queue that will be called 
		back once all othe other expansion is complete, or 'timeDelay_ms' milliseconds have elapsed,
		whichever comes last.

		Currently this is used by ID native the artwork OM service but can be used by any
		service that may take some time to complete and can be cancelled by the user. Or if you
		do some work in a thread you can use this to be called back later at some interval to see
		if the work is complete.

		@param iService IN The object model service to call back; typically just 'this'.
		@param timeDelay_ms The number of milliseconds (minimum) to wait before retrying the expansion.
			If zero the expansion will be retried as soon as all of the other (non-delayed) expansion 
			is complete.
	*/
	virtual void ExpandAgainLater(const IPreflightObjectModelService* iService, uint32 timeDelay_ms = 0) = 0;
};

