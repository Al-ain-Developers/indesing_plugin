//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISpreadList.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __ISPREADLIST__
#define __ISPREADLIST__

#include "IPMUnknown.h"
#include "SpreadID.h"

class IGeometry;
class UIDList;
class IIterator;

/** Represents a list of spreads (kSpreadBoss) in a given document (kDocBoss).

	ISpreadList is an interface off the document (kDocBoss) containing a list of the spreads (kSpreadBoss) in the document.
	Master spreads are stored in the IMasterSpreadList interface. ISpreadList stores a list of 
	spreads (as UIDs) in a given document; this list is persistent.


	@ingroup layout_spread
	@see kDocBoss
	@see kSpreadBoss
	@see ISpread
	@see IMasterSpreadList

 */
class ISpreadList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREADLIST };

	enum { kAtTheEnd = -1 };

	/**
		InsertSpreads - put the given spreads after the given position
	
		@param	spreadToInsert
		@param	posForInsert
	*/
	virtual void InsertSpreads(const UIDList& spreadToInsert, int32 posForInsert) = 0;

	/**
		InsertOneSpread - add one spread at the specified position
	
		@param	spreadToInsert
		@param	posForInsert
	*/
	virtual void InsertOneSpread(const UID  spreadToInsert, int32 posForInsert) = 0;


	/**
		RemoveSpreads - delete 'count' spreads, starting at 'firstIndex'. 
	
		@param	firstIndex
		@param	count
	*/
	virtual void RemoveSpreads(int32 firstIndex, int32 count) = 0;

	/**
		RemoveOneSpread - remove one spread at the specified position
	
		@param	posForRemove
	*/
	virtual void RemoveOneSpread(int32 posForRemove) = 0;


	/**
		MoveSpread - Move the spread at the from index to the to index in the list
			Note that the spread is first removed from the list, then
			inserted at the "to" position. Caller may need to adjust indexes
			in order to compensate for this behavior.

	
		@param	from
		@param	to
	*/
	virtual void MoveSpread(int32 from, int32 to) = 0;

	/**
		QueryNthSpread - return the IGeometry interface associated with the 'spreadIndex' spread. This
		will add a ref count, and will instantiate the spread (if necessary).
	
		@param	spreadIndex
		@return	IGeometry*
	*/
	virtual IGeometry * QueryNthSpread(int32 spreadIndex) = 0;

	/**
		GetNthSpreadUID - Returns the 'spreadIndex' spread's UID
	
		@param	spreadIndex
		@return	UID
	*/
	virtual UID GetNthSpreadUID(int32 spreadIndex) = 0;

	/**
		GetSpreadCount - Return the number of spreads in this list (ie in the document)
	
		@return	int32
	*/
	virtual int32 GetSpreadCount() const = 0;

	/**
		GetSpreadIndex - Given a spread's IGeometry, return its index into the spread list
	
		@param	spread
		@return	int32
	*/
	virtual int32 GetSpreadIndex(IGeometry * spread) = 0;

	/**
		GetSpreadIndex - Given a spread's UID, return the spread's index into the spread list.
	
		@param	spreadUID
		@return	int32
	*/
	virtual int32 GetSpreadIndex(UID spreadUID) = 0;

	
	/**
		NewPageIterator - create a page iterator & return the generic IIterator to the caller
			NOTE : The caller is responsible for deleteing the returned iterator

	
		@return	IIterator*
	*/
	virtual IIterator *NewPageIterator() = 0;
};


#endif // __ISPREADLIST__

