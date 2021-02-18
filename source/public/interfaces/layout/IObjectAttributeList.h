//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectAttributeList.h $
//  
//  Owner: Yeming Liu
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
//  Comments: This file is the same as ITextAttributes.h.
//  TODO: We should clean them up and make it as a base interface.
//  
//========================================================================================

#pragma once

#ifndef __IObjectAttributeList__
#define __IObjectAttributeList__

// ----- Interface files -----

#include "IPMUnknown.h"

// ----- ID files -----

#include "GenericID.h"

class AttributeBossList;

/**  This interface provides methods for accessing, apply and clear attributes.
*/
class IObjectAttributeList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOBJECTATTRIBUTELIST };
		
		/**	Get the number of total attributes.
			@return number of attributes.
		*/
		virtual int32 CountBosses() const = 0;

		/**	Get nth attribute's ClassID.
		    @param n IN index of attribute.
			@return nth attribute's ClassID.
		*/
		virtual ClassID GetClassN(int32 n) const = 0;

		/**	Query attribute's specific interface by the attribute's index and interfae id.
			@param n IN index of attribute.
			@param id IN specific interface id.
			@return the requested interface.
		*/
		virtual const IPMUnknown* QueryBossN(int32 n, PMIID id) const = 0;

		/**	Query attribute's specific interface by the attribute's ClassID and interface id.
			@param c IN ClassID of attribute.
			@param id IN specific interface id.
			@return the requested interface.
		*/
		virtual const IPMUnknown* QueryByClassID(ClassID c, PMIID prop) const = 0;
		
		/**	Apply the attribute.
		    @param newone IN the interface that contains the attribute data to apply.
			@param attrCls IN the attribute's ClassID.
		*/
		virtual void ApplyAttribute(const IPMUnknown *newone, ClassID attrCls = kInvalidClass) = 0;

		/**	Apply the passed in attribute list.
		    @param other IN the attributes to apply.
		*/
		virtual void ApplyAttributes(const AttributeBossList *other) = 0;

		/**	Clear specific attribute determined by passed in ClassID.
			@param id IN the ClassID of the attribute to be cleared.
		*/
		virtual void ClearOverride(ClassID id) = 0;

		/**	Clear the attributes determined by passed in attribute list.
			@param list IN the attribute list that is to be cleared.
		*/
		virtual void ClearOverrides(const AttributeBossList *list) = 0;

		/**	Clear all the attributes.
		*/
		virtual void ClearAllOverrides() = 0;

		/**	Check if the attribute list contains the passed in attribute or not.
			@param classID IN the ClassID of the attribute we check.
			@return bool16 kTrue indicates the attribute exists, otherwise return kFalse.
		*/
		virtual bool16 ContainsAttribute(ClassID classID) const = 0;

		/**	Get the attribute list.
			@return const AttributeBossList the attribute list.
		*/
		virtual const AttributeBossList* GetBossList() const = 0;
};

#endif	//  __IObjectAttributeList__
