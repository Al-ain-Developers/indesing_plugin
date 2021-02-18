//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRIDX.h $
//  
//  Owner: Paul Messmer
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
#ifndef __IRIDX__
#define __IRIDX__

#include "ShuksanID.h"
#include "IDataBase.h"

#include <utility>
#include <vector>

//========================================================================================

/**
	Represents the source part of a reference tracked by the reference index.  It is a
	(UID,ImplementationID) pair representing some particular interface's implementation 
	on some particular UID.  Comparison operators ==, !=, and < are defined, and the
	rest are omitted by design.  Ordering for operator < is the lexicographical ordering
	of the sequence sourceUID, sourceImplementationID.
	@see RIDXTarget
	@see RIDXReference
	@see IRIDX
*/
class RIDXSource
{
private:

	UID					fUID;
	ImplementationID	fImplID;

public:

	/** Constructs an uninitialized source.
	*/
	RIDXSource ()
	{}

	/** Constructs a source.
		@param sourceUID is the UID that the reference is from.
		@param sourceImplID is the implementation on that UID that the reference is from.
	*/
	RIDXSource (UID sourceUID, ImplementationID sourceImplID) :
		fUID (sourceUID),
		fImplID (sourceImplID)
	{}

	/** Constructs a source.
		@param sourceUID is the UID that the reference is from.
		@param sourceImplID is the implementation on that UID that the reference is from.
	*/
	RIDXSource (uint32 sourceUID, uint32 sourceImplID) :
		fUID (UID (sourceUID)),
		fImplID (ImplementationID (sourceImplID))
	{}

	/** Gets the UID of the source.
		@return the UID of the source.
	*/
	UID GetUID () const { return fUID; }

	/** Gets the ImplementationID of the source.
		@return the ImplementationID of the source.
	*/
	ImplementationID GetImplID () const { return fImplID; }
};

//========================================================================================

inline bool operator == (const RIDXSource &lhs, const RIDXSource &rhs)
{
	return	lhs.GetUID () == rhs.GetUID () &&
			lhs.GetImplID () == rhs.GetImplID ();
}

inline bool operator != (const RIDXSource &lhs, const RIDXSource &rhs)
{
	return	lhs.GetUID () != rhs.GetUID () ||
			lhs.GetImplID () != rhs.GetImplID ();
}

inline bool operator < (const RIDXSource &lhs, const RIDXSource &rhs)
{
	if (lhs.GetUID () > rhs.GetUID ()) return false;
	if (lhs.GetUID () < rhs.GetUID ()) return true;
	return lhs.GetImplID () < rhs.GetImplID ();
}

//========================================================================================

/**
	Represents the target part of a reference tracked by the reference index.  
	It is a (type,value) pair representing some particular type of thing refered to 
	in some particular source.  Comparison operators ==, !=, and < are defined, and the
	rest are omitted by design.  Ordering for operator < is the lexicographical ordering
	of the sequence targetType, targetValue.
	@see RIDXSource
	@see RIDXReference
	@see IRIDX
*/
class RIDXTarget
{
public:

	/** Type of target.  
		Gives meaning and type to the value member of the RIDXTarget.
	*/
	enum Type 
	{
		/** The value is a UID that was referenced in the source's
			 ReadWrite() by stream->XferReference(value);
	    */
		kUIDAsReference = 0, 

		/** The value is a UID that was referenced in the source's
			ReadWrite() by stream->XferObject(value);
		*/
		kUIDAsObject = 1
	};

private:

	uint32				fType;
	uint32				fValue;

public:

	/** Constructs an uninitialized target.
	*/
	RIDXTarget () :
		fType(0),
		fValue(0)
	{}

	/** Constructs a target.
		@param targetType is the type of the target.
		@param targetValue is the target value, and the interpretation depends upon targetType.
	*/
	RIDXTarget (Type targetType, uint32 targetValue) :
		fType ((uint32) targetType),
		fValue (targetValue)
	{}

	/** Constructs a target.
		@param targetType is the type of the target.
		@param targetValue is the target value, and the interpretation depends upon the target's type.
	*/
	RIDXTarget (uint32 targetType, uint32 targetValue) :
		fType (targetType),
		fValue (targetValue)
	{}

	/** Gets the type of the target.
		@return the type of the target.
	*/
	RIDXTarget::Type GetType () const { return RIDXTarget::Type (fType); }

	/** Gets the value of the target. 
		@return the value of the target.  The interpretation depends upon the target's type.
	*/
	uint32 GetValue () const { return fValue; }
};

//========================================================================================

inline bool operator == (const RIDXTarget &lhs, const RIDXTarget &rhs)
{
	return	lhs.GetType () == rhs.GetType () &&
			lhs.GetValue () == rhs.GetValue ();
}

inline bool operator != (const RIDXTarget &lhs, const RIDXTarget &rhs)
{
	return	lhs.GetType () != rhs.GetType () ||
			lhs.GetValue () != rhs.GetValue ();
}

inline bool operator < (const RIDXTarget &lhs, const RIDXTarget &rhs)
{
	if ((uint32) lhs.GetType () > (uint32) rhs.GetType ()) return false;
	if ((uint32) lhs.GetType () < (uint32) rhs.GetType ()) return true;
	return lhs.GetValue () < rhs.GetValue ();
}

//========================================================================================

/**
	Represents a reference tracked by the reference index.  It is a (source,target) pair 
	representing a reference in some particular source UID and some particular implementation 
	of an interface on that source UID to some particular target.
	Comparison operators ==, !=, and < are defined, and the rest are omitted by design.  
	Ordering for operator < is the lexicographical ordering of the sequence source, target.
	@see RIDXSource
	@see RIDXTarget
	@see IRIDX
*/
class RIDXReference
{
	RIDXSource			fSource;
	RIDXTarget			fTarget;

public:

	/** Constructs an uninitialized reference.
	*/
	RIDXReference ()
	{}

	/** Constructs a reference.
		@param source is the source of the reference.
		@param target is the target of the reference.
	*/
	RIDXReference (RIDXSource source, RIDXTarget target) :
		fSource (source),
		fTarget (target)
	{}

	/** Constructs a reference.
		@param sourceUID is the UID that the reference is from.
		@param sourceImplID is the implementation on that UID that the reference is from.
		@param targetType is the type of the target.
		@param targetValue is the target value, and the interpretation depends upon targetType.
	*/
	RIDXReference (UID sourceUID, ImplementationID sourceImplID, RIDXTarget::Type targetType, uint32 targetValue) :
		fSource (RIDXSource (sourceUID, sourceImplID)),
		fTarget (RIDXTarget (targetType, targetValue))
	{}

	/** Constructs a reference.
		@param sourceUID is the UID that the reference is from.
		@param sourceImplID is the implementation on that UID that the reference is from.
		@param targetType is the type of the target.
		@param targetValue is the target value, and the interpretation depends upon targetType.
	*/
	RIDXReference (uint32 sourceUID, uint32 sourceImplID, uint32 targetType, uint32 targetValue) :
		fSource (RIDXSource (sourceUID, sourceImplID)),
		fTarget (RIDXTarget (targetType, targetValue))
	{}
		
	/** Gets the source of the reference.
		@return the source of the reference.
	*/
	RIDXSource GetSource () const { return fSource; }

	/** Gets the target of the reference.
		@return the target of the reference.
	*/
	RIDXTarget GetTarget () const { return fTarget; }
};

//========================================================================================

inline bool operator == (const RIDXReference &lhs, const RIDXReference &rhs)
{
	return	lhs.GetSource ().GetUID () == rhs.GetSource ().GetUID () &&
			lhs.GetSource ().GetImplID () == rhs.GetSource ().GetImplID () &&
			lhs.GetTarget ().GetType () == rhs.GetTarget ().GetType () &&
			lhs.GetTarget ().GetValue () == rhs.GetTarget ().GetValue ();
}

inline bool operator != (const RIDXReference &lhs, const RIDXReference &rhs)
{
	return	lhs.GetSource ().GetUID () != rhs.GetSource ().GetUID () ||
			lhs.GetSource ().GetImplID () != rhs.GetSource ().GetImplID () ||
			lhs.GetTarget ().GetType () != rhs.GetTarget ().GetType () ||
			lhs.GetTarget ().GetValue () != rhs.GetTarget ().GetValue ();
}

inline bool operator < (const RIDXReference &lhs, const RIDXReference &rhs)
{
	if (lhs.GetSource ().GetUID () > rhs.GetSource ().GetUID ()) return false;
	if (lhs.GetSource ().GetUID () < rhs.GetSource ().GetUID ()) return true;
	if (lhs.GetSource ().GetImplID () > rhs.GetSource ().GetImplID ()) return false;
	if (lhs.GetSource ().GetImplID () < rhs.GetSource ().GetImplID ()) return true;
	if ((uint32) lhs.GetTarget ().GetType () > (uint32) rhs.GetTarget ().GetType ()) return false;
	if ((uint32) lhs.GetTarget ().GetType () < (uint32) rhs.GetTarget ().GetType ()) return true;
	return lhs.GetTarget ().GetValue () < rhs.GetTarget ().GetValue ();
}

//========================================================================================

class IRIDXQuery;

class IRIDX;

//========================================================================================

/** Gets access to the reference index of a document.  This is a non-persistent interface
	on the root object of every database which is reference indexed.
*/
class IRIDXAccess : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IRIDXACCESS };
		
	/** Obtains the reference index for the database
		@return The reference index boss for the database, AddRef-ed.
	*/
	virtual IRIDX *QueryRIDX() = 0;
	
	/** Obtains the reference index UIDRef for the database
		@return The UIDRef of the reference index
	*/
	virtual UIDRef GetRIDX() = 0;
};

//========================================================================================

namespace RIDXAccess
{
	inline IRIDX *QueryRIDX (IDataBase *db)
	{
		InterfacePtr<IRIDXAccess> ridxAccess (db, db->GetRootUID(), UseDefaultIID());
		return ridxAccess ? ridxAccess->QueryRIDX () : 0;
	}
}

//========================================================================================

/**	The public interface of the reference index.

	<pre>
		One index to hold them all
		One query to find them
		One interface to observe them all
		And during persistence bind them
	</pre>

	Particular database types (e.g. documents) are reference indexed, which means
	that the object model automatically tracks which UIDs in the database are referred
	to by which other UIDs, and you may query for this information instead of iterating
	the database somehow to obtain it.  A particular database has a reference index if the
	IRIDXAccess interface is available off of the root object of the database (e.g. kDocBoss in
	the case of documents).  You can check a reference index as follows:

	<pre>
		InterfacePtr<IRIDX> ridx (RIDXAccess::QueryRIDX());
		if (ridx) ridx->UseSomeFunction();
	</pre>

	If you are only interested in querying the reference index, you may safely stop reading
	further here and refer to CreateQuery().

	While the presence of IRIDXAccess on the database's root object means that type of
	database is reference indexed, that fact alone does not _create_ the reference
	index itself in the database.  This is something that must be done when
	new databases are created, or when existing ones are opened that could have
	been created before reference indexing was performed on that type of database.
	Also, each time a database is opened, you must request that the reference index 
	process any pending indexing that was deferred due to missing plug-ins.  For example, 
	imagine the OpenDoc() function for some database type that is reference indexed.
	It should have logic that looks something like the following:

	<pre>
		InterfacePtr<IRIDX> ridx (RIDXAccess::QueryRIDX());
		ridx->Intialize ();
		// Call Converison Manager HERE if necessary 
		ridx->ProcessScheduledIndexing ();
	</pre>

	In the NewDoc() function, handling would be largely identical except there would
	never be need to call the conversion manager.
*/
class IRIDX : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IRIDX };

	typedef std::vector<RIDXTarget>		Targets;		// These typedefs are not Doc++ commented
	typedef std::vector<RIDXSource>		Sources;		// because they are not used in the current
	typedef std::vector<RIDXReference>	References;		// set of public APIs.

	/**	Initalize the reference index for the database.  This will create the
	    reference index storage if necessary.  This function must be called EVERY TIME
		a reference indexed database is created or opened (but BEFORE conversion).
	*/
	virtual void Initialize () = 0;

	/** Processes any pending indexing that has been scheduled.  This function must be
		called EVERY TIME a reference indexed database is created or opened (but AFTER
		conversion).  
	*/
	virtual void ProcessScheduledIndexing () = 0;

	/** Specifies whether changes made to the model are reflected in the reference index
	    state during the lifetime of a query
	*/
	enum QueryType
	{
		/** None, some, or all of the model changes made during the query lifetime are visible to the query */
		kDynamicQuery = 0,

		/** No model changes made during the query lifetime are visible to the query */
		kLockedQuery = 1
	};

	/** Specifies whether a query requires the reference index to be brought up to date
		always, or only if it is outmost query
	*/
	enum CoherencyType
	{
		/** Reference index is updated to reflect model state only at start of the of outermost query */
		kCoherentAtOutermostQueryCreation = 0,

		/** Reference index is updated to reflect model state at the start of this query */
		kCoherentAtThisQueryCreation = 1
	};

	/** Starts a query operation on the reference index.

		To query the reference index, call this function.  It creates a query and returns
		a query object that can subsequently be used to interrogate the reference index.
		The lifetime of the query is the lifetime of the IRIDXQuery object - when the
		reference count of that object drops to zero the query ends.  It is acceptable
		to aquire one or more additional query objects before the first one is destroyed.

		There are two considerations when creating a query:  The first is where to require
		coherency (the reference index is said to be coherent when its state reflects
		exactly that state of the object model).  The second is whether object model
		changes made during a query may be reflected in the reference index state during
		the query lifetime (a dynamic query) or not (a locked query).

		When you begin to interrogate the reference index by creating the first outstanding
		query object, the reference index state must be made coherent by forcing all dirty objects
		in the database to persist themselves.  This is a non-trivial amount of work.  After
        this persistence completes, not all dirty objects may be considered "clean," and thus
		the next time you require coherency (even if the model has not changed in between) you
		will still force some objects to persist themselves - again a non-trivial overhead.

		When you create a query object, you must specify whether to force the reference
		index coherent only if this query is the outermost query, or whether to always force
		it consistent.  Prefer usage patterns that only require coherency at the outmost
		query context.  If you need to interrogate the reference index multiple times within
		a small scope, prefer usage patterns that re-use a query object or keep an active
		query versus creating a single query, releasing it, create a single query, releasing
		it, etc..., which adds substantial overhead by repeatedly forcing coherency.

		If you create a dynamic query, then during the query lifetime if you make changes
		to the model you may see none, some, or all of your changes reflected in the
		state of the reference index.  This may require some defensive programming to
		properly handle, but this type of query is the most efficient and permits
		an arbitrary number of model changes during the query lifetime.  Prefer usage
		patterns that can utilize dynamic queries.

		If you create a locked query, then any changes you make to the model during
		the query lifetime are not reflected in the reference index during the query
		lifetime.  The state of the reference index is frozen when the first locked query
		is created, and remains frozen until the last outstanding locked query is
		released.  However, because an outstanding locked query freezes its state,
		changing the model will cause change records for the reference index to be queued
		up in memory and not applied until later no locked queries are actuve.  An arbitrarily
		large number of model changes during a locked query could exhaust memory and cause 
		failure.  Future implementations may be capable of spilling change records to disk
		to avoid this problem.

		There is no such thing as a "coherent query" - i.e. where the reference index
		constantly reflects the exact state of the model.

		It is best to to keep a query object around over a small scope of repeated
		use, but certainly not much longer than necessary.  It is not permissible to keep 
		a query active beyond the end of the outermost executing command or sequence, for 
		example, and this restriction will be enforced via protective shutdown by the architecture.

		@param queryType specifies a locked or dynamic query
		@param coherencyType specifies the coherency constraints at the start of the query
		@return A new query object boss with a reference count of 1.
		@see IRIDXQuery
	*/
	virtual IRIDXQuery *CreateQuery (QueryType queryType, CoherencyType coherencyType) const = 0;

	/** Determines if there are any outstanding queries (either dynamic or locked).
		@return true if queries of any type are currently outstanding on the reference index.
	*/
	virtual bool HasOutstandingQuery () const = 0;

	/** Determines if there are any outstanding locked queries.
		@return true if locked queries are currently outstanding on the reference index.
	*/
	virtual bool HasOutstandingLockedQuery () const = 0;

	/** Tells the reference index that we are closing a reference indexed database very early (it's not
		going to be saved), that we won't actually call ProcessScheduledIndexing(), and
		to suppress the assert it would normally give in that case telling you you forgot the call
		to ProcessScheduledIndexing().
	*/
	virtual void WontProcessScheduledIndexing () = 0;

	/** Find out if update is in progress.
		@return true if reference index is updating. Calls like CreateQuery will cause protective
			shutdown if this is true.
	*/
	virtual bool UpdateInProgress () const = 0;
};

//========================================================================================

/**	Query object to use to interrogate the reference index.

	Created by IRIDX::CreateQuery(), an instance of this boss object represents an
	active query on a reference index.  It can be used to find out what sources reference 
	specified targets.
*/
class IRIDXQuery : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRIDXQUERY };

	/**	Returns the database holding the reference index on which the query is running.
		@return the database holding the reference index on which the query is running.
	*/
	virtual IDataBase *GetDataBase () = 0;

	/** Sets up the query object (initializes an iterator) to begin enumerating sources
	    for that reference a target.  After calling StartTarget(), call GetNextSource() 
		repeatedly to get the sources referencing the specified target.

		@param target is the target to start enumerating sources for
	*/
	virtual void StartTarget (RIDXTarget target) = 0;

	/** Gets the next source that references the target previously specified
	    by calling StartTarget().

		@param source is where to return the next source
		@return true if there was another source, false otherwise
	*/
	virtual bool GetNextSource (RIDXSource &source) = 0;
};

//========================================================================================

#endif	// __IRIDX__


