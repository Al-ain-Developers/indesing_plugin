//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStoreInternal.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IStoreInternal__
#define __IStoreInternal__

class IDFile;

#include "LinksID.h"

/**
 Interface used to create and manage a data blob object with data from a file or stream.
 
 Most commonly used when embedding links into the document.
 */
class IStoreInternal : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTOREINTERNAL};
	
	/**
	Persistence-related method for saving or restoring the state of this object instance.
	@param iPMStream	IN Stream to read the instance data from
						   or write the instance data to.
	@param prop			IN The implementation id.
	*/
	virtual void ReadWrite(IPMStream *s, ImplementationID prop) = 0;

	/**
	Stores the contents of the given file into a new data blob object.
	The UID stored by this object is updated to the UID of the new data blob object
	@param file	IN File to read contents from.
	@return 0 if success.
	*/
	virtual int32 StoreFile(IDFile *file) = 0;

	/**
	Deletes the stored data blob UID.
	*/
	virtual void RemoveFile() = 0;

	/**
	 Returns the stored data blob UID.
	 */
	virtual UID GetStoredUID() = 0;

	/**
	 Sets the stored data blob UID to the given UID.
	 @param storedUID	IN Data blob UID to store in this object.
	 */
	virtual void SetStoredUID(UID storedUID) = 0;

	/**
	Stores the contents of the given stream into a new data blob object.
	The UID stored by this object is updated to the UID of the new data blob object
	@param fileStreamRead	IN Stream to read contents from.
	@return 0 if success.
	*/
	virtual int32 StoreStream(IPMStream* fileStreamRead) = 0;
};

#endif
