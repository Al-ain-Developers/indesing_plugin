//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IContentIteratorRegister.h $
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
#if !defined(__IContentIteratorRegister__)
#define __IContentIteratorRegister__

// ----- Interfaces -----

#include "IPMUnknown.h"

class VersionID;
class IContentReadIterator;
class IContentWriteIterator;
class IPMStream;


//----------------------------------------------------------------------------------------
//	IContentIteratorRegister
//----------------------------------------------------------------------------------------

/** This interface allows a client to register a set of class and implementation Content
    Iterators. The object implementing this interface must register with the system as
	a service provider of type kContentIteratorRegisterServiceImpl.
	@see IContentReadIterator
	@see IContentWriteIterator
*/
class  IContentIteratorRegister : public IPMUnknown
{
public:
	/** Return a count of the number of classes for which iterators can be provided.
	    @return The class count
	*/
	virtual uint32 GetClassIDCount() = 0;

	/** Return the ID of the n-th class for which iterators can be provided.
	    @param n IN Which class
		@param id OUT The class ID or kInvalidClass if n is invalid.
	*/
	virtual void GetNthClassID(uint32 n, ClassID &id) = 0;
	
	/** Return a count of the number of implementations for which iterators can be provided.
	    @return The implementation count
	*/
	virtual uint32 GetImplementationIDCount() = 0;

	/** Return the ID of the n-th implementation for which iterators can be provided.
	    @param n IN Which implementation
		@param id OUT The implementation ID or kInvalidImpl if n is invalid.
	*/
	virtual void GetNthImplementationID(uint32 n, ImplementationID &id) = 0;

	/** Create a new input iterator for a particular version of a particular class.
	    @param n IN The index of the class in the list supplied via GetNthClassID()
		@param version IN The class data format
		@param s IN An input stream that contains the data in the specified format
		@return A referenced instance of IContentReadIterator
	*/
	virtual IContentReadIterator *NewNthClassReadIterator(uint32 n, const VersionID &version, IPMStream *s) = 0;

	/** Create a new output iterator for a particular version of a particular class.
	    @param n IN The index of the class in the list supplied via GetNthClassID()
		@param version IN The class data format
		@param s IN An output stream that will contain the data
		@return A referenced instance of IContentWriteIterator
	*/
	virtual IContentWriteIterator *NewNthClassWriteIterator(uint32 n, const VersionID &version, IPMStream *s) = 0;

	/** Create a new input iterator for a particular version of a particular implementation.
	    @param n IN The index of the implementation in the list supplied via GetNthImplementationID()
		@param version IN The implementation data format
		@param s IN An input stream that contains the data in the specified format
		@return A referenced instance of IContentReadIterator
	*/
	virtual IContentReadIterator *NewNthImplementationReadIterator(uint32 n, const VersionID &version, IPMStream *s) = 0;

	/** Create a new output iterator for a particular version of a particular implementation.
	    @param n IN The index of the implementation in the list supplied via GetNthImplementationID()
		@param version IN The implementation data format
		@param s IN An output stream that will contain the data
		@return A referenced instance of IContentWriteIterator
	*/
	virtual IContentWriteIterator *NewNthImplementationWriteIterator(uint32 n, const VersionID &version, IPMStream *s) = 0;
};

#endif	// __IContentIteratorRegister__