//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CContentIterator.h $
//  
//  Owner: Steve Pellegrin
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
#if !defined(__CContentIterator__)
#define __CContentIterator__

// ----- Interfaces -----

#include "IContentIterator.h"
#include "IPMStream.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif


//----------------------------------------------------------------------------
// CContentIterator
//----------------------------------------------------------------------------

/** This class provides basic support for both input and output
    content iterators. Much of its functionality must be
	provided by a subclass (see comments, below).
*/
class PUBLIC_DECL CContentIterator
{
public:
	/** ctor
	    @param owner IN Owning Boss
		@param s IN Input or output stream associated with this iterator
	*/
	CContentIterator(IPMUnknown *owner, IPMStream *s);

	/** dtor */
	virtual ~CContentIterator();

	/** Determine whether the ID currently being processed
	    is a class or implementation.
	    Must be supplied by a subclass.
		@return kTrue if a class, kFalse if an implementation
	*/
	virtual bool16 IsClassID() const = 0;

	/** Return a referenced pointer to the stream associated with the iterator.
	    Must be supplied by a subclass.
	    @return The stream
	*/
	virtual IPMStream *QueryContentStream() = 0;

	/** Return the ID of the current class being processed
	    @return The class ID or kInvalidClass if there is no current class
	    Must be supplied by a subclass.
	*/
	virtual ClassID GetClassID() const = 0;

	/** Return the ID of the current implementation being processed
	    @return The implementation ID or kInvalidImpl if there is no current implementation
	    Must be supplied by a subclass.
	*/
	virtual ImplementationID GetImplementationID() const = 0;

	/** Return the length of the data associated with the current class or implementation
	    (Only meaningful for Input iterators)
	    Must be supplied by a subclass.
		@return The data length in bytes
	*/
	virtual uint32 GetLength() const = 0;

	/** Advance to the next class or implementation ID
	    (Only meaningful for Input iterators)
	    Must be supplied by a subclass.
		@return kTrue if another ID was found, kFalse if not
	*/
	virtual bool16 Next() = 0;

	/** Resets an input iterator to the state that it was in when constructed
	    and optionally associates an output iterator with it.
	    (Only meaningful for Input iterators)
	    Must be supplied by a subclass.
		@param out IN An output iterator
	*/
	virtual void ResetRead(IContentWriteIterator *out = nil) = 0;

	/** Add a class ID to the output iterator.
	    (Only meaningful for Output iterators)
	    Must be supplied by a subclass.
		@param id IN The class ID
	*/
	virtual void CreateClassID(ClassID id) = 0;

	/** Finish processing output for the most recent class ID.
	    If the supplied ID differs from the one supplied to
		CreateClassID(), the class is renumbered in the database.
	    (Only meaningful for Output iterators)
	    Must be supplied by a subclass.
		@param id IN The class ID
	*/
	virtual uint32 CloseClassID(ClassID id) = 0;


	/** Add an implementation ID to the output iterator.
	    (Only meaningful for Output iterators)
	    Must be supplied by a subclass.
		@param id IN The implementation ID
	*/
	virtual void CreateImplementationID(ImplementationID id) = 0;


	/** Finish processing output for the most recent implementation ID.
	    If the supplied ID differs from the one supplied to
		CreateImplementationID(), the implementation is renumbered in the database.
	    (Only meaningful for Output iterators)
	    Must be supplied by a subclass.
		@param id IN The implementation ID
	*/
	virtual uint32 CloseImplementationID(ImplementationID id) = 0;

	/** Abandon process output for the most recent class or implementation ID.
	    (Only meaningful for Output iterators)
	    Must be supplied by a subclass.
	*/
	virtual void AbortID() = 0;

	/** Reset an output iterator to its initial, empty state.
	    (Only meaningful for Output iterators)
	    Must be supplied by a subclass.
	*/
	virtual void ResetWrite() = 0;

	/**
	    Notification method: Called when we start processing a list.
	    May be overridden by a subclass.
		@param listType IN The type of list being processed.
	*/
	virtual void BeginList(IContentWriteIterator::ListType /*listType*/)
		{}

	/**
	    A notification method: Called when we are finished processing a list.
	    May be overridden by a subclass.
	*/
	virtual void EndList()
		{}

	/** Determines whether we are at the end of the data.
	    (Only meaningful for Input iterators)
		@return kTrue if at the end, kFalse otherwise.
	*/
	bool16 EndOfList() const
		{return fEOF;}

	/** Returns the stream offset when the iterator was
	    first constructed, or after the most recent reset.
		@return The stream offset
	*/
	virtual int32 GetOriginPosition() const
		{return fOriginPosition;}

protected:	// For use by subclasses
	/** Return an unreferenced pointer to the input or output
	    stream associated with this iterator.
		@return The stream
	*/
	IPMStream *GetStream() const
		{return fStream;}

	/** Determine whether this is an input or output iterator.
	    @return kTrue if input, kFalse if output
	*/
	bool IsReadIterator() const
		{return fIsRead;}

	/** Return the current stream position relative to the
	    iterator's origin. For input iterators, this means the number
		of bytes already consumed. For output iterators, it means the
		number of bytes written.
		@return The position
	*/
	int32 CurrentPosition(IPMStream *s) const
		{return s->Seek(0, kSeekFromCurrent);}

	/** Sets the iterator's end-of-file status.
	    @param atEnd IN kTrue if at eof, kFalse if not
	*/
	void SetEndOfList(bool16 atEnd)
		{fEOF = atEnd;}

private:
	bool16			fEOF;
	int32			fOriginPosition;
	IPMStream *		fStream;
	bool			fIsRead;
};

#ifdef PUBLIC_BUILD
#pragma export off
#endif


//----------------------------------------------------------------------------
// CContentReadIterator and CContentWriteIterator
//    These classes are not exported because their implementations
//    are included below.
//----------------------------------------------------------------------------

/** This class provides a generic implementation of the
    IContentReadIterator interface. It uses an aggregated instance
	of CContentIterator to perform the actual work.

	The individual methods are not documented here, they correspond
	exactly to those documented for IContentReadIterator.
	@see IContentReadIterator
	@see CContentIterator
*/
class CContentReadIterator : public IContentReadIterator
{
public:
	CContentReadIterator()
		: fIterator(nil)
		{}
	CContentReadIterator(CContentIterator &iterator)
		: fIterator(&iterator)
		{}

	void SetIterator(CContentIterator *iterator)
		{fIterator = iterator;}

	bool16 IsClassID() const
		{return fIterator->IsClassID();}
	ClassID GetClassID() const
		{return fIterator->GetClassID();}
	ImplementationID GetImplementationID() const
		{return fIterator->GetImplementationID();}
	uint32 GetLength() const
		{return fIterator->GetLength();}
	bool16 Next()
		{return fIterator->Next();}
	bool16 EndOfList() const
		{return fIterator->EndOfList();}
	void Reset(IContentWriteIterator *out = nil)
		{fIterator->ResetRead(out);}
	IPMStream *QueryContentStream()
		{return fIterator->QueryContentStream();}
	int32 GetOriginPosition() const
		{return fIterator->GetOriginPosition();}

private:
	CContentIterator	*fIterator;
};


/** This class provides a generic implementation of the
    IContentWriteIterator interface. It uses an aggregated instance
	of CContentIterator to perform the actual work.

	The individual methods are not documented here, they correspond
	exactly to those documented for IContentWriteIterator.
	@see IContentWriteIterator
	@see CContentIterator
*/
class CContentWriteIterator : public IContentWriteIterator
{
public:
	CContentWriteIterator()
		: fIterator(nil)
		{}
	CContentWriteIterator(CContentIterator &iterator)
		: fIterator(&iterator)
		{}

	void SetIterator(CContentIterator *iterator)
		{fIterator = iterator;}
		
	void BeginList(ListType listType)
		{fIterator->BeginList(listType);}
	void EndList()
		{fIterator->EndList();}

	void CreateClassID(ClassID id)
		{fIterator->CreateClassID(id);}
	uint32 CloseClassID(ClassID id)
		{return fIterator->CloseClassID(id);}
	void CreateImplementationID(ImplementationID id)
		{fIterator->CreateImplementationID(id);}
	uint32 CloseImplementationID(ImplementationID id)
		{return fIterator->CloseImplementationID(id);}
	void AbortID()
		{fIterator->AbortID();}
	void Reset()
		{fIterator->ResetWrite();}
	IPMStream *QueryContentStream()
		{return fIterator->QueryContentStream();}
	int32 GetOriginPosition() const
		{return fIterator->GetOriginPosition();}

private:
	CContentIterator	*fIterator;
};

#endif	// __CContentIterator__
