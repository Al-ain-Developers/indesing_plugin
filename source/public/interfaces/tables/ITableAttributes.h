//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttributes.h $
//  
//  Owner: Joe Shankar
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
#ifndef __ITableAttributes__
#define __ITableAttributes__

#include "IPMUnknown.h"
#include "TablesID.h"

class AttributeBossList;

/** An interface wrapper for AttributeBossList. 
	This interface is similar to ITextAttributes.
*/
class ITableAttributes : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ITABLEATTRIBUTES };

		/** Determine the count of attribute overrides in the AttributeBossList.
		*/
		virtual int32 		CountBosses() const = 0;

		/** Determine the type of the override at the nth position in the AttributeBossList.
			@param n index of override 
			@return ClassID of entry at given index
		*/
		virtual ClassID 	GetClassN(int32 n) const = 0;
		
		/** 
			@return reference-incremented interface ptr of specified type, refers to override at given index. 
			@precondition 0 <= n < CountBosses
		*/
		virtual const IPMUnknown* QueryBossN(int32 n, PMIID iid) const = 0;

		/** Query for an override by ClassID.
			@return reference-incremented interface ptr of specified type
			@precondition classID should be in set returned by a GetClassN call
		*/
		virtual const IPMUnknown* QueryByClassID(ClassID classID, PMIID iid) const = 0;

		/** Updates the value of a specific override of corresponding class ID to the given boss object 
			@param newAttribute interface ptr on an attribute boss object to be added to the list of overrides
		*/
		virtual void ApplyAttribute(const IPMUnknown* newAttribute) = 0;

		/** Update values of overrides a list of attributes given
			@param other list of overrides to apply
		*/
		virtual void ApplyAttributes(const AttributeBossList* other) = 0;

		/** Remove an override associated with a given ClassID.
			@param id specifies the class of override that is to be removed from the AttributeBossList
		*/
		virtual void ClearOverride(ClassID id) = 0;

		/**	Remove the specified overrides
			@param list overrides to remove
		*/
		virtual void ClearOverrides(const AttributeBossList* list) = 0;

		/** Remove all the overrides.
		*/
		virtual void ClearAllOverrides() = 0;

		/**	Accessor for the AttributeBossList.

			@return this encapsulated AttributeBossList
		*/
		virtual const AttributeBossList* GetBossList() const = 0;
};



#endif	//  __ITableAttributes__