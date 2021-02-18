//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/IPstLstUIDList.h $
//  
//  Owner: Adobe Developer Technologies
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
//  IPstLstUIDList provides the list interface for the page item.
//  
//========================================================================================

#ifndef __IPstLstUIDList_h__
#define __IPstLstUIDList_h__

#include "IPMUnknown.h"
#include "IDataBase.h"
#include "UIDList.h"
#include "PstLstID.h"

/**	An interface that maintains a list of UIDs of kPstLstDataBoss data objects
	created by this plug-in.

	@ingroup persistentlist
*/
class IPstLstUIDList : public IPMUnknown
{
public:	
	enum	{kDefaultIID = IID_IPSTLSTUIDLIST};
	
	/**
		@return UID list this class maintains.
	*/
	virtual const UIDList* GetUIDList() = 0;
		
	/**
		Given an index, this routine will returns its corresponding UIDRef of the object as referenced by the
		index.
		@param index the index of the object in the UID list that the user is interested in.
		@return the UIDRef of the object that the user is inquiring about.
	*/
	virtual UIDRef GetRef(int32 index) = 0;
		
	/** 
		@return the database that stores the UID list 
	*/
	virtual IDataBase* GetDataBase() = 0;
		
	/**
		This function appends an uid of an object onto the UID list that it maintains.
		@param uid the UID of the object to be appened to the UID list.
	*/
	virtual void Append(const UID& uid) = 0;
		
	/**
		This function removes an uid of an object from the UID list that it maintains.
		@param uid the UID of the object to be removed from the UID list.
	*/
	virtual void Remove(const UID& uid) = 0;
};

#endif // __IPstLstUIDList_h__

// End, IPstLstUIDList.h.



