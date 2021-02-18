//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrListType.h $
//  
//  Owner: Amit Batra
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
#ifndef __ITextAttrListType_h__
#define __ITextAttrListType_h__


#include "IPMUnknown.h"
#include "BNTextAttrID.h"

/** Represents the list type text attribute.
	@ingroup text_attr
*/

class ITextAttrListType : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRLISTTYPE};

		/**
			List Type
		*/
		typedef enum {
						/** No List */
						kNone, 

						/** Bulleted List */
						kBulletedList, 

						/** Numbered List */
						kNumberedList
			} ListType;

		/** Standardized alias that refers to ListType in this interface */
		typedef const ListType ValueType;

		/** Standardized alias that refers to ListType in this interface */
		typedef const ListType value_type;

		/**
			Set the list type in this text attribute
			@param flag	The list type to set
		*/
		virtual void Set(value_type flag) = 0;

		/**
			Get the list type from this text attribute. This is a standardized method name across 
			most text attribute interfaces.
			@return 		value_type, which represents a ListType
		*/
		virtual value_type Get() const = 0;

		/**
			Set the list type in this text attribute
			@param flag	The list type to set
		*/
		void SetListType(value_type flag) { Set(flag); }

		/**
			Get the list type from this text attribute
			@return 		ListType
		*/
		value_type GetListType() const { return Get(); }
};

#endif // __ITextAttrListType_h__
