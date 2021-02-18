//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SBOSReference.h $
//  
//  Owner: Jianlan Song
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

#include "IPMStream.h"
#include "SBOSRefInstantiate.h"

/** Represents small boss object; stored in the SBOS (small boss object
	store), and may contain SBOSID.

	Maintains a persistent reference to a small boss object, 
	which can be instantiated from one of these SBOSReference objects.

	There are two types of persistent reference; 'base' (few of these) and 'sub-item'. The base type
	is UID-based, sub-item type isn't.

	If the SBOSReference is a sub-item type, then the small boss-object store
	manager (ISBOSMgr) will instantiate the object, otherwise it's just a 'normal'
	instantiation of a UID-based object from a database.

	Note: Modified from XMLReference.

*/

template <class ISBOSObj>
class SBOSReference 
{
	public:
		/** Plain old data type; no specialized copy semantics required for K2Vector. */
	   	typedef base_type data_type;


		/**	Default constructor
		 */
		SBOSReference() :
			fBaseUIDRef(), fSubItem(kInvalidSBOSID)
			{}


		/**	Constructor
			@param baseUIDRef 
			@param subItemID  
		 */
		SBOSReference(const UIDRef& baseUIDRef, SBOSID subItemID = kInvalidSBOSID) :
			fBaseUIDRef(baseUIDRef), fSubItem(subItemID)
			{}


		/**	Accessor for base UIDRef		
			@return const UIDRef& 
		 */
		const UIDRef& GetUIDRef() const
			{ return fBaseUIDRef; }


		/**	Accessor for base UID associated with the base UIDRef		
			@return base UID associated with the reference
		 */
		UID GetUID() const
			{ return fBaseUIDRef.GetUID(); }


		/**	Accessor for database stored with the base UIDRef	
			@return IDataBase 
		 */
		IDataBase *GetDataBase() const
			{ return fBaseUIDRef.GetDataBase(); }


		/**	Accessor for the sub-item SBOSID
			@return SBOSID associated with this
		 */
		SBOSID GetLogicalID() const
			{ return fSubItem; }


		/**	Mutator for sub-item SBOSID
			@param newValue for sub-item SBOSID
		 */
		void SetLogicalID(SBOSID newValue)
			{ fSubItem = newValue; }


		/**	Instantiate an element from the database.
			@return reference-incremented interface ptr to ISBOSObj referenced
		 */
		ISBOSObj* Instantiate() const
		{ 
			IPMUnknown* obj = SBOSRefInstantiate::Instantiate(fBaseUIDRef, fSubItem, ISBOSObj::kDefaultIID);
			if (obj)
				return static_cast<ISBOSObj*>(obj);
			else
				return nil;
		}

		/**	Method to serialise object to or deserialise object from given stream
			@param s stream to read state from or write state to
			@param db 
		 */
		void ReadWrite(IPMStream *s, IDataBase *db = nil)
		{ 
			if (s->IsReading()) {
				// reset all values to default, in case this is a snapshot restore
				fBaseUIDRef = UIDRef::gNull;
				fSubItem = kInvalidSBOSID;
			}

			UID uid = fBaseUIDRef.GetUID();
			
			s->XferReference(uid); 
			if (s->IsReading() && uid != kInvalidUID)	
				fBaseUIDRef = UIDRef(db, uid);
				
			s->XferInt32((int32&)fSubItem); 
		}	

		/**	Equality operator
			@param other comparand
			@return kTrue if UIDRef and sub-item SBOSID match, kFalse otherwise
		 */
		bool16 operator == (const SBOSReference& other) const
			{ return fBaseUIDRef == other.fBaseUIDRef && fSubItem == other.fSubItem; }	


		/**	Inequality operator
			@param compareAgainst comparand
			@return kTrue if equality operation fails, kFalse otherwise
		 */
		inline bool16 operator != (const SBOSReference& compareAgainst) const
			{ return (!(*this == compareAgainst)); }

		/**	Less than operator
			@param compareAgainst comparand
			@return kTrue if this is less than compareAgainst, kFalse otherwise
		 */
		bool16 operator < (const SBOSReference& compareAgainst) const
		{
			if (this->GetDataBase() == compareAgainst.GetDataBase())
			{
				if (this->GetUID() == compareAgainst.GetUID())
					return this->GetLogicalID() < compareAgainst.GetLogicalID();
				else
					return this->GetUID() < compareAgainst.GetUID();
			}	
			
			return this->GetDataBase() < compareAgainst.GetDataBase();
		}
		
	private:
		UIDRef fBaseUIDRef;
		SBOSID fSubItem;
};

