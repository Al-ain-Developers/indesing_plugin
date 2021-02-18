//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AttributeBossList.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __AttributeBossList__
#define __AttributeBossList__

#include "K2Vector.h"
#include "KeyValuePair.h"
#include "K2SmartPtr.h"

class IPMUnknown;
class IObjectModel;
class IPMStream;
class IClassInfo;
class IAttrBossReferencing;

	// sorted list by ClassID
	// each value has a pointer to the boss, and whether the boss can be 
	// copied to other AttributeBossLists (is it "missing").
typedef KeyValuePair<ClassID, std::pair<IPMUnknown*, bool16> > BossInfo;
typedef K2Vector<BossInfo >	BossLookup;


#pragma export on

/** AttributeBossList is a data structure that groups a set of attributes with distinct classes.
    AttributeBossList is used both in the model and in the user interface to collect lists of attributes.
	The class supports the following basic operations:
	<ol>
	<li>query for particular attributes,
	<li>apply overrides,
	<li>clear overrides, 
	<li> copy, and 
	<li> read write.
	</ol>
	@ingroup text_story
*/
class PUBLIC_DECL AttributeBossList
{
	public:
   		typedef object_type data_type;
		AttributeBossList();
		AttributeBossList(const AttributeBossList& copy);
		~AttributeBossList();

		AttributeBossList& operator=(const AttributeBossList& other);

		enum ReadWriteStatus { kSuccess, kListChangedOnRead };
		ReadWriteStatus ReadWrite(IPMStream* stream);
		
        AttributeBossList(AttributeBossList&& copy) noexcept
#ifdef DEBUG
        :fMirror(nil)
#endif
        {
            swap(*this, copy);
        }
    
        AttributeBossList &operator =(AttributeBossList&& copy) noexcept
        {
            swap(*this, copy);
            
            return *this;
        }
    
        friend inline void swap(AttributeBossList &a, AttributeBossList &b) noexcept
        {
            using std::swap;
            swap(a.fBosses, b.fBosses);
#ifdef DEBUG
            swap(a.fMirror, b.fMirror);
#endif
#ifdef INTERFACEPROXIES_SUPPORTED
            swap(a.fTokens, b.fTokens);
#endif
        }
    
		/** @return the number of attributes in the list. 
		*/
		int32 CountBosses() const;

		/** @return the class of the Nth attribute in the list.
		@param n IN attribute number in the list.
		*/
		ClassID GetClassN(int32 n) const;
	
		/** @return a pointer to an interface on the Nth attribute in the list.
			@param n IN attribute number in the list.
		   @param id IN id of the interface queried for. When id is equal IID_IUNKNOWN, 
		   a pointer to the attribute boss is returned.
		*/
		const IPMUnknown* QueryBossN(int32 n, PMIID id) const;

		/** @return a pointer to an interface on the attribute that has class c
			@param c IN attribute class.
		    @param id IN id of the interface queried for. When id is equal IID_IUNKNOWN, 
		    a pointer to the attribute boss is returned.
		*/
		const IPMUnknown* QueryByClassID(ClassID c, PMIID id) const;

		/** Apply a single attribute.
			@param newone IN is a pointer to the attribute boss or an interface on the attribute boss to apply. 
			@param attrClass IN the class of the attribute to apply. When attrClass is
			equal kInvalidClass, the function queries the object model for the class.
		*/
		void ApplyAttribute(const IPMUnknown *newone, const ClassID attrClass = kInvalidClass);

		/** Apply a list of attributes. 
		@param list IN attribute boss list to apply.
		*/
		void ApplyAttributes(const AttributeBossList *list);

		/** Remove the attribute that has class id from the list.
		@param id IN class of attribute to remove.
		*/
		void ClearOverride(ClassID id);

		/**  Remove the attributes that have the classes of the attributes in list.
		@param list IN attribute boss list to clear from list. when list is nil
		this function clears all attributes.
		*/
		void ClearOverrides(const AttributeBossList *list);

		/** Remove attributes that are not allowed to exist in styles (ie: pair kern amounts).
		*/
		void ClearNonStyleOverrides();

		/** Remove all attributes in the list.
		*/
		void ClearAllOverrides();
		
		/** @return a copy of the attribute boss list. 
		The attributes in the list are subject to a shallow copy 
		(their reference count is incremented).
		*/
		AttributeBossList* Duplicate() const;

		/** Create a copy of the attributes in the list of which classes appear in filter.
		@param filter IN attributes to copy from the list.
		@return list of attributes copied. The attributes are subject to a shallow copy
		(their reference count is incremented).
		*/
		AttributeBossList* CopyTheseAttributes(const AttributeBossList *filter) const;
		
		/** @return whether there is an attribute with class klas in the list.
		@param klas IN class of attribute. 
		*/
		bool16 ContainsAttribute(ClassID klas) const;

		/** @return whether a copy identical to an attribute exists in 
			the attribute boss list (this is a deep compare).
		@param check IN to attribute searched for. 
		@param klas IN of attribute. When klas is equal kInvalidClass,
		the function queries the model to get the class.
		*/
		bool16 ContainsExact(IDataBase *db, const IPMUnknown *check, ClassID klas = kInvalidClass) const;	

		/** @return whether all attributes in both lists are identical (deep compare).
		@param other IN list to compare against. 
		*/
		bool16 IsEqual(IDataBase *db, const AttributeBossList* other) const;		

		/** @return true when both boss lists have at least one attribute with same classe.
			@param other IN attribute boss list to intersect with. 
		*/
		bool16 Intersects(const AttributeBossList* other) const;	

		/** @return kTrue if the two lists share attributes in common and at least one of those
			attributes has different values in the two lists.  Otherwise return kFalse.
			If there is no intersection, this method returns kFalse.
			@param db IN The database the attribute lists are "in".
			@param other IN attribute boss list to intersect with.
		*/
		bool16 IntersectionContainsDifferences(IDataBase * db, const AttributeBossList * other) const;

		/**
			Used in legacy conversion of attribute boss lists. Converts attribute boss list ifstreams
			have different revision numbers.
			@param inStream IN  source stream to convert from.
			@param outStream IN target stream to convert to.
		*/
		static uint32 ConvertAttributeList(IPMStream *inStream, IPMStream *outStream, ImplementationID context);

		/**
			Used in legacy conversion of attribute boss lists.
			Copies attribute boss list from inStream to outStream.
			@param inStream IN  source stream to copy from.
			@param outStream IN target stream to copying to.
		*/
		static uint32 CopyAttributeList(IPMStream *inStream, IPMStream *outStream);

		/**
			For Internal use only.
		*/
#ifdef DEBUG
		static bool16		 ts_DebugAttributeBossList;

		bool16	CheckAttributeBossList() const;
		inline	bool16 IsChecking() const { return fMirror != nil; }
		
	private:
				AttributeBossList *fMirror;
#endif
				
	protected:
		ReadWriteStatus DoWrite(IPMStream* stream);
		ReadWriteStatus DoRead(IPMStream* stream);

		void CopyInto(AttributeBossList *) const;		

		bool16 AllowCopy(ClassID attrClass, IPMUnknown *boss) const;
		
#ifdef DEBUG
		void _ReferenceAttribute(ClassID cls, IPMUnknown *attr);
		void _DereferenceAttribute(ClassID cls, IPMUnknown *attr);
#endif
	
	private:
		BossLookup				fBosses;
#ifdef INTERFACEPROXIES_SUPPORTED
		BossLookup				fTokens;
#endif

private:
		/** 
			Remove any attributes that are supplied by plug-ins that are not loaded.
		*/
		void StripMissingAttributes();

		bool16 operator==(const AttributeBossList& other) const;
		bool16 operator!=(const AttributeBossList& other) const;

public:
	/**
	Use this static to pass a K2:shared_pointer of a nil attribute boss list. 
	*/
	static boost::shared_ptr<AttributeBossList> kNil_shared_ptr;
};

/* IDAttributeList class is used to also associate a data base with attribute boss list */
class  PUBLIC_DECL IDAttributeList {
public:
	typedef object_type data_type;

	IDAttributeList() : fAttributeList(nil), fDB(nil) {}

	IDAttributeList(const AttributeBossList * attrList, IDataBase * db) : fAttributeList(attrList), fDB(db) {}

	const AttributeBossList * GetAttributeList() const { return fAttributeList; }
	IDataBase * GetDataBase() const { return fDB; }

private:
	IDataBase * fDB;
	const AttributeBossList * fAttributeList;
};

#pragma export off

#endif
		//  __AttributeBossList__
