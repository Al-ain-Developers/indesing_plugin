//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UIDPairRef.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __UIDPAIRREF__
#define __UIDPAIRREF__

#include "IPMUnknown.h"

class IDataBase; 

/**	Contains a pair of UIDs
 */
class UIDPairRef
{
	public:
	/**	Constructor
		@return  
	 */
		UIDPairRef(IDataBase *db, UID key, UID value) :
			fDB(db), fKeyUID(key), fValueUID(value)	
			{}
	/**	Constructor
		@return  
	 */
		UIDPairRef(const UIDPairRef& ref) :
			fDB(ref.GetDataBase()),
			fKeyUID(ref.GetKeyUID()),
			fValueUID(ref.GetValueUID())
			{}
	/**	Return the database
		@return  IDataBase
	 */
		IDataBase *GetDataBase() const
			{ return fDB; }
	/**	Return the key UID
		@return  UID
	 */
		UID GetKeyUID() const
			{ return fKeyUID; }
	/**	Return the value UID
		@return  UID
	 */
		UID GetValueUID() const
			{ return fValueUID; }
	/**	Operator ==
		@return  bool16
	 */
		bool16 operator==(const UIDPairRef& other) const
		 	{ return fKeyUID == other.fKeyUID && fValueUID == other.fValueUID && fDB == other.fDB; }
	/**	Operator !=
		@return  bool16
	 */
		bool16 operator!=(const UIDPairRef& other) const
		 	{ return ((fKeyUID != other.fKeyUID) || (fValueUID != other.fValueUID) || (fDB != other.fDB)); }
private:
	IDataBase *fDB;
	UID fKeyUID;
	UID fValueUID;
};


#endif // __UIDPAIRREF__
