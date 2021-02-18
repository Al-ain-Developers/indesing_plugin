//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IContentIterator.h $
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
#if !defined(__IContentIterator__)
#define __IContentIterator__

// ----- Interfaces -----

#include "IPMUnknown.h"		// for INHERITFROM

class IPMStream;


//----------------------------------------------------------------------------------------
//	IContentWriteIterator
//----------------------------------------------------------------------------------------

/** This class is used by the Conversion Manager to iterate over the contents of persistent
    class or implementation's data. This iteration is a read-modify-write operation.
    IContentWriteIterator is used for the output part of the process.
*/

class  IContentWriteIterator INHERITFROM
{
public:
	/** Defines the characteristics of a nested list.
	*/
	enum ListType
	{
		/** No list */
		kNoList,
		/** A list of attributes preceeded by a 16-bit count of the number of list elements */
		kAttributeList16,
		/** A list of attributes preceeded by a 32-bit count of the number of list elements */
		kAttributeList32,
		/** A list of attribute bosses preceeded by a 16-bit count of the number of list elements
		    The length, in bytes, of each boss' data is defined by a 16-bit value. */
		kAttributeBossList1616,
		/** A list of attribute bosses preceeded by a 16-bit count of the number of list elements
		    The length, in bytes, of each boss' data is defined by a 32-bit value. */
		kAttributeBossList1632,
		/** A list of attribute bosses preceeded by a 32-bit count of the number of list elements
		    The length, in bytes, of each boss' data is defined by a 16-bit value. */
		kAttributeBossList3216,
		/** A list of attribute bosses preceeded by a 32-bit count of the number of list elements
		    The length, in bytes, of each boss' data is defined by a 32-bit value. */
		kAttributeBossList3232
	};

public:
	/** Virtual destructor
	*/
	virtual ~IContentWriteIterator()
		{}

	/** Called when starting a nested list of classes or implementations.
	    @param listType IN The type of nested list we are creating.
	*/
	virtual void BeginList(ListType listType) = 0;
	
	/** Called when a nested list is complete.
	*/
	virtual void EndList() = 0;

	/** Called when starting data output for a particular class.
	    @param id IN The class ID.
	*/
	virtual void CreateClassID(ClassID id) = 0;

	/** Called when data output for a particular class is complete.
	    @param id IN The final class ID (may be different that the value passed
	           to CreateClassID() if the class was renumbered during conversion).
	    @return The number of bytes of class data that were written.
	*/
	virtual uint32 CloseClassID(ClassID id) = 0;

	/** Called when starting data output for a particular implementation.
	    @param id IN The implementation ID.
	*/
	virtual void CreateImplementationID(ImplementationID id) = 0;

	/** Called when data output for a particular implementation is complete.
	    @param id IN The final implementation ID (may be different that the value passed
	           to CreateImplementationID() if the implementation was renumbered during conversion).
	    @return The number of bytes of implementation data that were written.
	*/
	virtual uint32 CloseImplementationID(ImplementationID id) = 0;
	
	/** Used as an alternative to CloseClassID() or CloseImplementationID() if the Conversion
	    Manager decides to delete the data rather than convert it.
	*/
	virtual void AbortID() = 0;

	/** Called when the Conversion Manager is finished with this iterator. The iterator should
	    flushing pending output, release cached resources, etc.
	*/
	virtual void Reset() = 0;

	/** Returns the initial position of the output stream associated with this iterator.
	    That is -- the stream's position at the time the iterator was bound to it.
	    @return The original stream position.
	*/
	virtual int32 GetOriginPosition() const = 0;
	
	/** Returns an interface pointer to the iterator's associated output stream.
	    The interface is add-refed prior to returning the pointer.
	    @return The stream pointer.
	*/
	virtual IPMStream *QueryContentStream() = 0;
};


//----------------------------------------------------------------------------------------
//	IContentReadIterator
//----------------------------------------------------------------------------------------

/** This class is used by the Conversion Manager to iterate over the contents of persistent
    class or implementation's data. This iteration is a read-modify-write operation.
    IContentReadIterator is used for the output part of the process.
*/

class  IContentReadIterator INHERITFROM
{
public:
	/** Virtual destructor
	*/
	virtual ~IContentReadIterator()
		{}

	/** Used to determine whether the current ID found in the input stream is a Class ID
	    or an Implementation ID.
	    @return kTrue if the current ID is a Class ID.
	*/
	virtual bool16 IsClassID() const = 0;
	
	/** Fetch the current Class ID.
	    @return The Class ID.
	*/
	virtual ClassID GetClassID() const = 0;
	
	/** Fetch the current Implementation ID.
	    @return The Implementation ID.
	*/
	virtual ImplementationID GetImplementationID() const = 0;
	
	/** Return the length (in bytes) of the data associated with the current ID.
	    @return Data length
	*/
	virtual uint32 GetLength() const = 0;
	
	/** Advance the iterator to the next ID in the input stream.
	    @return kTrue if another ID was found, kFalse if not.
	*/
	virtual bool16 Next() = 0;
	
	/** Returns kTrue when there are no more IDs in the iterated data stream
	    @return kTrue if the data has been exhausted, kFalse if there are more IDs.
	*/
	virtual bool16 EndOfList() const = 0;
	
	/** Called when the Conversion Manager wishes to reinitalize the iterator.
	    An output iterator may optionall be associated with this input iterator at this time.
	    @param out IN Used to bind an output iterator to this input iterator.
	*/
	virtual void Reset(IContentWriteIterator *out = nil) = 0;


	/** Returns the initial position of the input stream associated with this iterator.
	    That is -- the stream's position at the time the iterator was bound to it.
	    @return The original stream position.
	*/
	virtual int32 GetOriginPosition() const = 0;
	
	/** Returns an interface pointer to the iterator's associated input stream.
	    The interface is add-refed prior to returning the pointer.
	    @return The stream pointer.
	*/
	virtual IPMStream *QueryContentStream() = 0;
};

#endif	// __IContentIterator__