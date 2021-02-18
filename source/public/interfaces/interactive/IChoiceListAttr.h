//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IChoiceListAttr.h $
//  
//  Owner: Tim Wright
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
#ifndef __IChoiceListAttr_h__
#define __IChoiceListAttr_h__

#include "IPMUnknown.h"
#include "FormFieldTypes.h"

//===================================================================================

/**
This is the data interface for a Choice List graphic attribute.
The Choice List attribute is used to store the choices in List Box and
Combo Box form field page items.
*/
class IChoiceListAttr : public IPMUnknown
{
public:

	/** Insert a new choice into the choice list */
	virtual void Insert( int32 inBeforeIndex, const PMString& inChoice ) = 0;

	/** Add a choice to the end of the list */
	virtual void Append( const PMString& inChoice ) = 0;

	/** Remove a choice at an index */
	virtual void Remove( int32 inAtIndex ) = 0;

	/** Erase all choices in the list */
	virtual void Clear() = 0;

	/** Change a choice at an index */
	virtual void Set( int32 inIndex, const PMString& inChoice ) = 0;

	/** Get a choice at an index
		@param inIndex, position of choice
		@outChoice, on exit the Choice information
	 */
	virtual void Get( int32 inIndex, PMString* outChoice ) const = 0;

	/** @return number of choices */
	virtual int32 Size() const = 0;

	/** @return the index of the choice if the choice exists. If the choice
	does not exist, it will return -1. */
	virtual int32 Index(PMString& inChoice) const = 0;

	/** Sort the choices in the list */
	virtual void Sort() = 0;

	/** @return the index at which the choice should be inserted in a sorted list.  */
	virtual int32 GetSortedIndex(PMString& choice) const = 0;
};

//===================================================================================

#endif // __IChoiceListAttr_h__

