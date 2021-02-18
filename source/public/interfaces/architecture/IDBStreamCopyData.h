//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDBStreamCopyData.h $
//  
//  Owner: robin briggs
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
#ifndef __IDBStreamCopyData__
#define __IDBStreamCopyData__

#include "ShuksanID.h"

/** Data interface for controlling a copy database stream. Used for direct object-to-object copy
	in the database. You shouldn't need to use this interface.
@see StreamUtil
@see IDBStreamData
@ingroup arch_db
*/
class IDBStreamCopyData : public IPMUnknown
{
	public:

		/** Set which objects we're copying from and to.
			@param srcDB	Database we're copying from
			@param destDB	Database we're copying to
			@param id		UID of the object we're copying to
			@param pmobject	A helper object in the copy (contains optional extra info for the copy)
		*/
		virtual void Set(IDataBase *srcDB, IDataBase *destDB, UID id, IPMUnknown* pmobject) = 0;

		/** Return the source database
			@return the source database
		*/
		virtual IDataBase *GetSourceDataBase() const = 0;

		/** Return the destination database
			@return the destination database
		*/
		virtual IDataBase *GetDestinationDataBase() const = 0;

		/** Return the destination UID
			@return the destination UID
		*/
		virtual UID GetUID() const = 0;

		/** Return a pointer to the helper object. The pointer is not AddRef'd, so its lifetime is still owned
			by the stream.
			@return a pointer to the helper object
		*/
		virtual IPMUnknown *GetPMObject() const = 0;
};


#endif // __IDBStreamCopyData__
