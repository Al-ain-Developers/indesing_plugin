//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UIDRef.h $
//  
//  Owner: ?
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
#ifndef __UIDREF__
#define __UIDREF__

#include "IPMUnknown.h"

class IDataBase; 

/** UIDRef

	A UIDRef is a reference to a persistent object. Persistent objects are created in databases, 
	by creating new UIDs. An open InDesign document is associated with a database, and the persistent
	objects stored with the document are managed and maintained by the database. If you have a 
	pointer to the object in memory (for instance, a pointer to an interface of the object), that
	pointer is only good as long as the object is in memory. When it's released, the pointer can 
	no longer be used to refer to the object. A UID is a persistent reference to an object that is
	good across instantations, and can be stored in the document as well. A UIDRef is a pair of
	<database, UID> that gives us a way to refer to an object as long as the document it is in 
	is open.
*/
class UIDRef
{
	public:
			/** This declares that UIDRef's have binary copy semantics. This means they
				can be copied byte-wise if necessary for performance reasons.
			*/
		typedef base_type data_type;
		
			/*  UIDRef's constructed without parameters are invalid. They can be used, but
				attempts to instantiate them will fail.
			*/
		UIDRef() :
			fDB(nil), fUID(kInvalidUID)
			{}

			/** Create a new UIDRef to the specified object in the database.
			*/
		UIDRef(IDataBase *db, UID id) :
			fDB(db), fUID(id)	
			{}

			/** Get the database.
			
				@return IDataBase* the database the UIDRef is in
			*/
		IDataBase *GetDataBase() const
			{ return fDB; }
			
			/** Get the UID
			
				@return UID of the UIDRef
			*/
		UID GetUID() const
			{ return fUID; }
			
			/** Reset the value of the UIDRef, so it refers to a different object
				in the same database.
			
				@param newUID new value for the UIDRef.
			*/
		void ResetUID(UID newUID)
			{ fUID = newUID; }
		
// Don't remove these next two. Even though we are just POD (plain old data) and
// seem unnecessary (and slow). Otherwise Metrowerks will generate horrendous code 
// for the operator! and operator void* below. Yuck.
			/** Compare two UIDRefs for equality
			
				@param other the UIDRef to compare to
				@return kTrue if the UIDRefs are the same
			*/ 
 		bool16 operator==(const UIDRef& other) const
		 	{	//An open question here--there are 3 ways to have an invalid UIDRef. Should any invalid UIDRef compare equal to any other?
				//Assert for now that we only use "doubly-invalid" invalid UIDRefs when comparing and see what shows up.

				//ASSERT( fDB || fUID == kInvalidUID);
				//ASSERT( other.fDB || other.fUID == kInvalidUID);
//				ASSERT( fDB == other.fDB || fUID != kInvalidUID || other.fUID != kInvalidUID);

//				ASSERT( fDB == nil && fUID == kInvalidUID || fDB != nil && fUID != kInvalidUID);
//				ASSERT( other.fDB == nil && other.fUID == kInvalidUID || other.fDB != nil && other.fUID != kInvalidUID);
				return fUID == other.fUID && fDB == other.fDB;
			}
			/** Compare two UIDRefs for inequality
			
				@param other the UIDRef to compare to
				@return kTrue if the UIDRefs are not the same
			*/ 
		bool16 operator!=(const UIDRef& other) const
		 	{ return !(*this == other); }


   		/** Compare two UIDRefs for inequality
   		
   			@param other the UIDRef to compare to
   			@return kTrue if this < other
   		*/ 
		bool16 operator<(const UIDRef& other) const
		{ return fDB == other.fDB ? fUID < other.fUID : fDB < other.fDB; }

// The next two functions allow testing of UIDRefs in conditionals, e.g. :
//
//		UIDRef myUIDRef(aDB, aUID);
//		...
//		if(!myUIDRef) {
//			myUIDRef = giveMeAnotherUIDRef();
//		}
//		ASSERT_MSG(myUIDRef, "nil");
//	

			/** Test to see if the UIDRef is nil
			
				@return kTrue if the UIDRef has nil database or kInvalidUID.
			*/
		bool16 operator!() const; 	// true if bad
			/** Returns a nil pointer if the UIDRef is nil, non-nil otherwise.
			
				@return nil pointer if the UIDRef has nil database or kInvalidUID.
			*/
		operator void*() const;	 	// nonzero if good

		
			/** ---- This function returns kTrue if the UIDRef is valid
					and the UID exists in its database. Else returns kFalse
					Common usage is to check and see if a UID can be
					instantiated.
					e.g.		
					<pre>
					UID myUIDRef(aDB, aUID);
					if (myUIDRef.IsExistsInDB()	{
						 // OK to instantiate UIDRef					
						InterfacePtr<ISomeInterface> theIFace(myUIDRef, IID_ISOMEINTERFACE);
						theIFace->DoWork();
					}
					else {
						// UID ref is invalid or does not exist
						myUIDRef = UIDRef::gNull
					}
					</pre>
				@return kTrue if the UIDRef is valid and the UID exists in its database
			*/
		bool16 ExistsInDB() const;

			/** Get a pointer to the object in memory, reading it from disk if necessary.
			
				@param iid which interface of the object to return (use IID_IUNKNOWN if you don't care).
				@return IPMUnknown* a pointer to the requested interface of the object, or nil if
				the object couldn't be found.
			*/
		IPMUnknown* Instantiate( PMIID iid ) const ;

public:		

// For convenience we provide a null UIDRef. E.g.:
//		UIDRef myUID(UIDRef::gNull);

#pragma export on
		PUBLIC_DECL static const UIDRef gNull;
#pragma export reset

// Debugger cannot handle long symbol names
// disable warning again
#ifdef WIN32
#pragma warning(disable : 4786)

#endif // WIN32

private:
	IDataBase *fDB;
	UID fUID;
};

/** A "nil" value for UIDRefs -- a valid UIDRef will never be equal to kInvalidUIDRef. */
extern PUBLIC_DECL const UIDRef kInvalidUIDRef;

inline bool16 UIDRef::operator!() const
{ 
	//return *this == UIDRef::gNull; 
	return fDB == nil || fUID == kInvalidUID;
}

inline UIDRef::operator void*() const
{ 
		// Is there a cleaner way to do this?
	//return *this == UIDRef::gNull ? nil : const_cast<UIDRef*>(this);
		
		// Require both members to be valid:
	return (fDB == nil || fUID == kInvalidUID) ? nil : const_cast<UIDRef*>(this);
}

inline bool16 UIDRef::ExistsInDB() const
{
	if (!(*this))			// use operator! for validity test
		return kFalse;
	else
		return (fDB->GetClass(fUID) != kInvalidClass ? kTrue : kFalse);
}

inline IPMUnknown* UIDRef::Instantiate( PMIID iid ) const
{
	return ( fDB ? fDB->Instantiate( fUID, iid ) : nil ) ;
}

#endif // __UIDREF__
