//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPageItemAdornmentList.h $
//  
//  Owner: jargast
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
#ifndef __IPageItemAdornmentList__
#define __IPageItemAdornmentList__

#include "IPMUnknown.h"
#include "IAdornmentShape.h"
#include "IAdornmentHandleShape.h"
#include "GenericID.h"

/**
 *  This is a better way to do iterations on the list.  If you use the
 *  iteration mechanism that is global to the list, it is possible that
 *  some procedure you call will do an iteration itself and mess up the
 *  state of your iteration.
 *  This iterator makes a copy of the list of adornments that satisfy
 *  the iteration criteria, so that it won't get reset in the middle
 *  of the iteration.
 */
class IAdornmentIterator: public IPMUnknown
{
public:
	/** Indicates what type of iterator is being used */
	enum IteratorType
	{
		/** Iterator deals with shape adornments */
		kNormalIterator,
		/** Iterator deals with handle adornments */
		kHandleIterator
	};

public:
	/** Add an adornment to the current list.
		@param *pAdorn - The adornment to be added (must be on a boss that has an IAdornmentShape interface
	*/
	virtual void AddAdornment( IPMUnknown* pAdorn ) = 0;

	/** Returns the next adornment in the list and increments the position
		@return - The next adornment in the list. Will return nil if the current position is at the end of the list.
	*/
	virtual IPMUnknown* GetNextAdornment() = 0;

	/** Returns the number of adorments in the list.
		@return - The size of the list we are iterating
	*/
	virtual int32 GetNumberOfAdornments() = 0;

	/** Finds the adornment by class ID, if one exists.
		@param classID IN The class ID for which to look
		@return True if the given class occurs in the list; false otherwise.
	*/
	virtual bool32 HasAdornment(ClassID classID) = 0;
};


/** A list of all of the adornments currently applied to a given page item.
	This class deals with both shape adornments and handle adornments
*/
class IPageItemAdornmentList : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_IPAGEITEMADORNMENTLIST };

	//
	// First there are the shape adornments
	//

	/** Adds the adornment.  The adornment specifies its paint order bits
		@param ClassID - The ClassID of the adorment being added
		@param bool16 - kTrue will mark the document as dirty (forcing a save dialog) if the list changes
	*/
	virtual void AddAdornment(ClassID, bool16 = kTrue) = 0;

	/** Removes the adornment with the ClassID
		@param ClassID - The ClassID of the adorment being added
		@param bool16 - kTrue will mark the document as dirty (forcing a save dialog) if the list changes
	*/
	virtual void RemoveAdornment( ClassID, bool16 = kTrue ) = 0;

	//Points somewhere on the list before the first node with these
	//AdornmentDrawOrder bits.
	//virtual void ResetIterator( IAdornmentShape::AdornmentDrawOrder ) = 0;

	// Returns the next adornment matching the flags specified in the
	// above call to ResetIterator, nil if it runs out of matches
	// deprecated, use QueryIterator.
	//virtual IAdornmentShape*  QueryNextAdornment() = 0;

	/**	Returns the total number of adornments in the data structure
		@return - The number of adornments
	*/
	virtual int32 GetNumberOfAdornments() = 0; // pass flags

	/** Indicates whether this page item already contains a given adornment
		@param ClassID - The adornment to check for on the page item
		@param order - This method will only search through adornements with a given draw order.
		@return - true if the adornment is allready on the page item
	*/
	virtual bool HasAdornment (ClassID, IAdornmentShape::AdornmentDrawOrder order = IAdornmentShape::kAllAdornmentFlags) = 0;

	/** Indicates whether this page item already contains a given handle adornment
		@param ClassID - The handle adornment to check for on the page item
		@return True if the given class occurs in the list; false otherwise.
	*/
	virtual bool HasHandleAdornment(ClassID classID, IAdornmentHandleShape::AdornmentDrawOrder order = IAdornmentHandleShape::kAllAdornmentFlags) = 0;

	//
	// Next we have the handle adornments
	//

	/** Adds the adornment.  The adornment specifies its paint order bits
		@param ClassID - The ClassID of the adorment being added
		@param bool16 - kTrue will mark the document as dirty (forcing a save dialog) if the list changes
	*/
	virtual void AddHandleAdornment(ClassID, bool16 = kTrue) = 0;

	/** Removes the adornment with the ClassID
		@param ClassID - The ClassID of the adorment being added
		@param bool16 - kTrue will mark the document as dirty (forcing a save dialog) if the list changes
	*/
	virtual void RemoveHandleAdornment( ClassID, bool16 = kTrue ) = 0;

	//Points somewhere on the list before the first node with these
	//AdornmentDrawOrder bits.
	//virtual void ResetHandleIterator( IAdornmentHandleShape::AdornmentDrawOrder ) = 0;

	// Returns the next adornment matching the flags specified in the
	// above call to ResetIterator, nil if it runs out of matches
	//virtual IAdornmentHandleShape*  QueryNextHandleAdornment() = 0;

	/**	Returns the total number of adornments in the data structure
		@return - The number of adornments
	*/
	virtual int32 GetNumberOfHandleAdornments() = 0; // pass flags

	/** create a new shape iterator which can be used to quick iterate through the adornments
		@param order - The draw order to use when searching for adornments to add to the list
		@param addUniqueOnly - If true and order=all, will only add unique adornments in the 
								case where an adornment handles multiple draw orders.  Eg if an
								adornment handles beforeshape and aftershape, it'll be added
								twice to the iterator unless this parameter is true.
		@return - An iterator that contains all shape adornments with the given draw order
	*/
	virtual IAdornmentIterator* CreateIterator( IAdornmentShape::AdornmentDrawOrder order, bool32 addUniqueOnly = kFalse ) = 0;

	/** create a new handle iterator which can be used to quick iterate through the adornments
		@param order - The draw order to use when searching for adornments to add to the list
		@return - An iterator that contains all handle adornments with the given draw order
	*/
	virtual IAdornmentIterator* CreateIterator( IAdornmentHandleShape::AdornmentDrawOrder order ) = 0;
};

#endif
