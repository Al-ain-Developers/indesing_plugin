//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterSpreadList.h $
//  
//  Owner: Brendan O'Shea
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
//  An interface off the document, contains the list of master spreads
//  defined in this document.
//  
//========================================================================================

#pragma once
#ifndef __IMASTERSPREADLIST__
#define __IMASTERSPREADLIST__

#include "IPMUnknown.h"
#include "MasterPageID.h"

class IGeometry;
class UIDList;
class IIterator;

/**
	IMasterSpreadList is an interface off the document containing a list of the IMasterSpreads in the document.
	Note that this is modeled after the ISpreadList.

	@ingroup layout_spread 
	@see ISpreadList
	@see kDocBoss

 */
class IMasterSpreadList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMASTERSPREADLIST };
	enum { kAtTheEnd = -1 };

	/**
		InsertMasterSpreads - Insert new master spread(s) into this document following 'posForInsert'. This
			is most likely to be called from the 'NewMasterSpreadCmd'. 
	
		@param	spreadToInsert
		@param	posForInsert
	*/
	virtual void InsertMasterSpreads(const UIDList& spreadToInsert, int32 posForInsert) = 0;
	
	/**
		RemoveMasterSpread - Remove a master spread at index 'index'
	
		@param	index
	*/
	virtual void RemoveMasterSpread(int32 index) = 0;

	/**
		QueryNthMasterSpread - Return the 'spreadIndex' master spread. n.b. this will add a ref count to the object
	
		@param	spreadIndex
		@return	IGeometry* - add refed master spread's IGeometry
	*/
	virtual IGeometry * QueryNthMasterSpread(int32 spreadIndex) = 0;
	
	/**
		GetNthMasterSpreadUID - Return the UID of the master spread at 'spreadIndex' in this list
	
		@param	spreadIndex
		@return	UID
	*/
	virtual UID GetNthMasterSpreadUID(int32 spreadIndex) = 0;
	
	/**
		GetMasterSpreadCount - Return the number of master spreads in this list (i.e. in this document)
	
		@return	int32 - the number of master spreads in this list (i.e. in this document)
	*/
	virtual int32 GetMasterSpreadCount() = 0;

	/**
		GetMasterSpreadIndex - Return the index of the specified master spread
	
		@param	spread
		@return	int32 - the index of the specified master spread
	*/
	virtual int32 GetMasterSpreadIndex(IGeometry * spread) = 0;

	/**
		GetMasterSpreadIndex - Return the index the master spread with the given UID
	
		@param	spreadUID
		@return	int32 - the index the master spread with the given UID
	*/
	virtual int32 GetMasterSpreadIndex(UID spreadUID) = 0;

	/**
		NewPageIterator - create a page iterator & return the generic IIterator to the caller
			NOTE : The caller is responsible for deleteing the returned iterator
	
		@return	IIterator*
	*/
	virtual IIterator *NewPageIterator() = 0;

	/**
		GenerateNewMasterName - Generates a unique master name, of the form
			"A-Master", "B-Master", ....
			if the suggested name is used, a number will be appended

		@param	IN/OUT pPrefix - on input, caller's suggestion for a prefix, on return a generated prefix 
			or the same as input, if input is not empty
		@param	IN/OUT pName - on input, caller's suggestion for a name; on output, generated name (will be 
			the same as input if input name is legal and not already used), if no input name, try to use
			"Master", if input already used a number will be appended;
		@param	IN duplicate - kTrue == if suggested prefix/name combo already used, get new prefix.
	*/
	virtual void GenerateNewMasterName(PMString* pPrefix, PMString* pName, bool16 duplicate = kFalse) = 0;
	
	/**
		FindMasterByName - return UID of master with the given name
	
		@param	IN prefix - master of interest prefix
		@param	IN basename - master of interest name
		@return	UID
	*/
	virtual UID FindMasterByName(PMString prefix, PMString basename) = 0;
};


#endif // __IMASTERSPREADLIST__

