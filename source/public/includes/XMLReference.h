//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLReference.h $
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
#ifndef __XMLReference__
#define __XMLReference__

typedef SBOSID LSID;
const LSID kInvalidLSID = kInvalidSBOSID;

class IIDXMLElement;
class IPMStream;

/** Represents elements on the logical structure tree; stored in the SBOS (small boss object
	store), and may contain LSID (same as SBOSID).

	Maintains a persistent reference to an IIDXMLElement, 
	which can be instantiated from one of these XMLReference objects.

	There are two types of persistent reference; 'base' (few of these) and 'sub-item'. The base	type
	is UID-based, sub-item type isn't.

	If the XMLReference is a sub-item type, then the small boss-object store
	manager (ISBOSMgr) will instantiate the object, otherwise it's just a 'normal'
	instantiation of a UID-based object from a database.

*/
class PUBLIC_DECL XMLReference {
public:
	/** Plain old data type; no specialised copy semantics required for K2Vector. */
   	typedef base_type data_type;


	/**	Default constructor
	 */
	XMLReference() :
		fBaseUIDRef(), fSubItem(kInvalidLSID)
		{}


	/**	Constructor
		@param baseUIDRef 
		@param subItemID  
	 */
	XMLReference(const UIDRef& baseUIDRef, LSID subItemID = kInvalidLSID) :
		fBaseUIDRef(baseUIDRef), fSubItem(subItemID)
		{}


	/**	Copy constructor
		@param other object to cpy state from
	 */
	XMLReference(const XMLReference& other) :
		fBaseUIDRef(other.fBaseUIDRef), fSubItem(other.fSubItem)
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


	/**	Accessor for the sub-item LSID
		@return LSID associated with this
	 */
	LSID GetLogicalID() const
		{ return fSubItem; }


	/**	Mutator for sub-item LSID
		@param newValue for sub-item LSID
	 */
	void SetLogicalID(LSID newValue)
		{ fSubItem = newValue; }


	/**	Instantiate an element from the database.
		@return reference-incremented interface ptr to IIDXMLElement referenced
	 */
	IIDXMLElement* Instantiate(void) const;


	/**	Method to serialise object to or deserialise object from given stream
		@param s stream to read state from or write state to
		@param db 
	 */
	void ReadWrite(IPMStream *s, IDataBase *db = nil);
	

	/**	Equality operator
		@param other comparand
		@return kTrue if UIDRef and sub-item LSID match, kFalse otherwise
	 */
	bool16 operator == (const XMLReference& other) const
		{ return fBaseUIDRef == other.fBaseUIDRef && fSubItem == other.fSubItem; }	


	/**	Inequality operator
		@param compareAgainst comparand
		@return kTrue if equality operation fails, kFalse otherwise
	 */
	inline bool16 operator != (const XMLReference& compareAgainst) const
		{ return (!(*this == compareAgainst)); }

	/**	Equal operator
		@param other value to be copied
	 */
	inline XMLReference& operator = (const XMLReference& other)
		{ fBaseUIDRef = other.fBaseUIDRef; fSubItem = other.fSubItem; return *this;}

	/**	Less than operator
		@param compareAgainst comparand
		@return kTrue if this is less than compareAgainst, kFalse otherwise
	 */
	bool16 operator < (const XMLReference& compareAgainst) const;

private:
	UIDRef fBaseUIDRef;
	LSID fSubItem;
	};

DECLARE_BASE_TYPE(XMLReference);		// no special copy

const XMLReference kInvalidXMLReference;

#if 0
class PUBLIC_DECL XMLReferenceWrapper
{
	public:
		/** Constructor
			@param element specifies element to wrap
		*/
		XMLReferenceWrapper(XMLReference element) : fElement(element) { }
		
		/** Implementation of operator less than.
		*/bool16 operator<(const XMLReferenceWrapper& other) const
		 	{ return ((fElement.GetDataBase() <= other.fElement.GetDataBase()) &&
		 				(fElement.GetUID() <= other.fElement.GetUID()) &&
		 				(fElement.GetLogicalID() < other.fElement.GetLogicalID())); }
	
	private:
		XMLReference fElement;
};

DECLARE_BASE_TYPE(XMLReferenceWrapper);		// no special copy
#endif

#endif // __XMLReference__
