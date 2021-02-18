//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/NamedAttribute.h $
//  
//  Owner: wtislar
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __NamedAttribute__
#define __NamedAttribute__


#include "IPMStream.h"

#include <vector>

/** 
	Represents an attribute of type int32 that has a user-defined name.
*/
class NamedUint32Attribute
{
public:
	/** Default contructor. */
	NamedUint32Attribute()
	:	fValue(0) {}

	/** Constructs a NamedAttribute object with a named value. */
	NamedUint32Attribute( PMString name, uint32 value )
	:	fName(name),
		fValue(value) {}

	/** Copy constructor. */
	NamedUint32Attribute( const NamedUint32Attribute& orig ) { Set( orig ); }

		//----------OPERATORS---------------
	
	/** Assignment operator for NamedAttribute variables. */		
	NamedUint32Attribute& operator = (const NamedUint32Attribute &copy)
		{ Set(copy); return *this; }

	/** Equivalence operator for NamedAttribute variables. */
	inline bool operator == (const NamedUint32Attribute &na) const
		{ return fName == na.fName &&
				 fValue == na.fValue; }

	/** Non-equivalence operator for NamedAttribute variables. */
	inline bool operator != (const NamedUint32Attribute &na) const
		{ return (!(*this == na)); }

	/** Accesses the name string.
		@return a PMString object of the attribute name.
	*/
	virtual PMString GetName() const { return fName; }
	
	virtual void GetValue( uint32 & value ) const { value = fValue; }
	virtual void ReadWrite( IPMStream* iPMStream )
	{
		fName.ReadWrite( iPMStream );
		int32 int32Value = int32(fValue);
		iPMStream->XferInt32( int32Value );
		fValue = uint32(int32Value);
	} 
	
private:
	PMString fName;
	uint32 fValue;

	void Set( const NamedUint32Attribute & copy )
		{ fName = copy.fName; fValue = copy.fValue; }
	
}; // end NamedUint32Attribute class


/**
	Represents a persistent list of NamedUint32Attributes.
*/
class NamedUint32AttributeList
{
public:
	/** Default contructor. */
	NamedUint32AttributeList() {}

	/** Copy constructor. */
	NamedUint32AttributeList( const NamedUint32AttributeList& orig ) { Set( orig ); }

		//----------OPERATORS---------------
	
	NamedUint32AttributeList& operator = (const NamedUint32AttributeList &copy)
	{ Set(copy); return *this; }

	inline bool operator == (const NamedUint32AttributeList &list) const
	{
		if ( fList.size() == list.fList.size() )
		{
			int listSize = int(fList.size());
			for ( int i = 0; i < listSize; i++ )
				if ( fList[i] != list.fList[i] )
					return false;
			return true;
		}
		return false;
	}

	inline bool operator != (const NamedUint32AttributeList & list) const { return (!(*this == list)); }

	inline NamedUint32Attribute & operator [] (int i) { return fList[i]; }
	
	void Add( NamedUint32Attribute na ) { fList.push_back( na ); }
	
	void Add( int32 i, NamedUint32Attribute na )
	{
		int32 listSize((int32)fList.size());
		if ( i >= 0 && i <= listSize )
			fList.insert( fList.begin() + i, na );
	} 
	
	void Clear() { fList.clear(); }
	
	void RemoveAt( int32 i ) { fList.erase( fList.begin() + i ); }
		
	int32 Length() { return int32(fList.size()); }
	uint32 GetLength() const { return uint32(fList.size()); }
	
	void ReadWrite( IPMStream* iPMStream )
	{
		int32 listSize((int32)fList.size());
		iPMStream->XferInt32( listSize );			
		if ( iPMStream->IsReading() )
		{
			fList.clear();
			for ( int32 i = 0; i < listSize; i++ )
			{
				NamedUint32Attribute na;
				na.ReadWrite( iPMStream );
				fList.push_back( na );
			}	
		}
		else
		{
			for ( std::vector<NamedUint32Attribute>::const_iterator iter = fList.begin(); iter != fList.end(); ++iter )
			{
				NamedUint32Attribute na = *iter;
				na.ReadWrite( iPMStream );
			}					
		}
	} // end ReadWrite()

private:
	std::vector<NamedUint32Attribute> fList;

	void Set( const NamedUint32AttributeList & copy )
	{
		fList.clear();
		int listSize = int(copy.fList.size());
		for ( int i = 0; i < listSize; i++ )
			fList.push_back( copy.fList[i] );
	}
}; // end NamedUint32AttributeList class

#endif // __NamedUint32AttributeList__
