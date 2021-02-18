//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDataLinkListReference.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __DataLinkListReference__
#define __DataLinkListReference__

// IID_DATALINKLISTREFERENCE interface.
class UIDList;

/** IDataLinkListReference stores references to multiple data links.
*/
class IDataLinkListReference : public IPMUnknown
{
public:
	/** Method to set a list of UIDs to data links (IDataLink).
		@param list of UIDs of data links.
	*/ 
	virtual void SetList(const UIDList &list) = 0;

	/** Method to get a list of UIDs to data links (IDataLink).
		@return a list of UIDs of data links.
	*/ 
	virtual const UIDList &GetList() = 0;

	/** Method to persist the list of data links.
		@param iPMStream is the stream to read or write from.
		@param id is the implementation ID.
	*/ 
	virtual void ReadWrite(IPMStream* iPMStream, ImplementationID id) = 0;

	/** Method to add a data link UID to the list.
		@param uid to add to the list. Only valid UIDs and non-duplicates are added.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 AddUID(UID uid) = 0;

	/** Method to remove a data link UID from the list.
		@param uid to remove from the list.
		@return 0 when the method succeeds and non-zero otherwise.
	*/ 
	virtual int32 RemoveUID(UID uid) = 0;
};

#endif // __DataLinkListReference__
