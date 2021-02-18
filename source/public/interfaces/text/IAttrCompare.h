//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAttrCompare.h $
//  
//  Owner: Habib Khalfallah
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
#ifndef __IAttrCompare__
#define __IAttrCompare__

#include "IPMUnknown.h"
#include "TextAttrID.h"


/** 
	Normally text attributes are compared by calling the ReadWrite on their persistent
	interfaces and comparing what is written.  A text attribute can optionally aggregate
	an implementation of this interface to get special compare semantics.  For example, if
	an object has multiple values that should be treated as equivalent, it's necessary
	to override the comparison behavior via this interface.
	
	@ingroup text_attr
*/
class IAttrCompare : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IATTRCOMPARE};

		/**
			This method is used to compare the value of two instances of a text attribute.
			This method differs from MemCmp below in that the purpose of MemCmp is to provide
			an ordering/sorting for a list of attributes of this type.  In some cases MemCmp
			may return not equal for two attributes when Compare would have considered them
			equal.  (An example is the font style attribute, where a nil font style name is considered
			equivalent to the "Regular/Roman/Plain/Etc." face in a font by Compare, but are
			sorted as separate values by MemCmp().)  Assuming this different is not important
			and this method cannot be implemented in a significantly faster way than
			MemCmp, a typical implementation would be "return this->MemCmp(db, theOther) == 0;"
			This method assumes the caller has insured the ClassID of this attribute and
			"theOther" match before calling Compare.
			@return bool16 indicating whether the attribute values are equivalent
			@param db IN database that the attributes are in.  This may be need to look up objects the
			attribute refers to internally (e.g. colors, fonts, etc.).
			@param theOther IN any interface on the attribute to be compared to.
		*/
		virtual bool16 Compare(IDataBase *db, const IPMUnknown *theOther) const = 0;
		
		/**
			This method is used to compare one attribute to another and may be used to
			create an ordered list of attributes.  This method assumes the caller has
			insured the ClassID of this attribute and "theOther" match before calling MemCmp.
			@return -1, 0 or 1 indicating this attribute is less than, equal to, or greater than "theOther".
			This is used for sorting purposes when maintaining lists of attributes.
			@param db IN database that the attributes are in.  This may be need to look up objects the
			attribute refers to internally (e.g. colors, fonts, etc.).
			@param theOther IN any interface on the attribute to be compared to.
		*/
		virtual int16 MemCmp(IDataBase *db, const IPMUnknown *theOther) const = 0;
};



#endif		// __IAttrCompare__