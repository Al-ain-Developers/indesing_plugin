//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUIDData.h $
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
//  
//  Interface for storing UIDs.
//  
//========================================================================================

#pragma once
#ifndef __IUIDData__
#define __IUIDData__

//
// If you need to store a UID persistantly, use IPersistUIDData instead of
// IUIDData
//

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "CommandID.h"

/** IUIDData is a data interface that holds onto a UIDRef (a <database, UID> pair) that can
	be used to uniquely describe a persistent object.
	@see IPersistUIDData
	@ingroup arch_coredata
*/
class IUIDData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUIDDATA };

	/**@name  Set - three alternate ways to set the value */
	//@{-----------------------------------------------------------------------------

	/** Set the value of the object. The pointer is for use inside the Set function only;
	 	the IPMUnknown* will be converted to a <database, UID> pair and held in that form,
	 	so that the object is not referenced.
	 	@param item the new object
	*/
	virtual void Set(const IPMUnknown *item) = 0;

	/** Set the value of the object.
	 	@param db the database the object is in
	 	@param UID the object within the database
	*/
	virtual void Set(IDataBase *db, UID id) = 0;

	/** Set the value of the object.
	 	@param ref the <database, UID> pair that describes the object
	*/
	virtual void Set(const UIDRef& ref) = 0;

	//@}-----------------------------------------------------------------------------

	/** Get the database of the object
		@return IDataBase* the database the object belongs to
	*/
	virtual IDataBase *GetItemDataBase() const = 0;

	/** Get the UID of the object
	*/
	virtual UID GetItemUID() const = 0;

	/** standard signature (Get()) method
	*/
	UID Get() const
		{ return GetItemUID(); }


	/** Get the UIDRef of the object
	*/
	virtual const UIDRef& GetRef() const = 0;


};



#endif // __IUIDData__
