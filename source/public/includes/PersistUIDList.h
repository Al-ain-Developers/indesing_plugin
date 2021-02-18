//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistUIDList.h $
//  
//  Owner: Zak_Williamson
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
//  Provides an implementation of a persistent list of uids.
//  
//========================================================================================

#pragma once
#ifndef __PERSISTUIDLIST__
#define __PERSISTUIDLIST__

#include "UIDList.h"

class IPMStream;

#pragma export on

/** Persistent list of UIDs. Same as UIDList, but provides ReadWrite capabilities for streaming.
	@see UIDList
	@see IPMStream
*/
class PUBLIC_DECL PersistUIDList : public UIDList
{
public:
	/** Construct a new UIDList, for UIDs in the database.
		@param db	The database that holds the UIDs that will be put in the list.
	*/
	PersistUIDList(IDataBase *db);
	
		// same as ReadWriteObject. Please DON'T USE!
	/** For internal use only */
	void ReadWrite(IPMStream *s, ImplementationID prop);

	/** Persists the list using XferObject method of the stream for each UID in the list.
		@param s	the source or destination stream
		@param prop	this parameter is ignored
	*/
	void ReadWriteObject(IPMStream *s, ImplementationID prop);

	/** Persists the list using XferReference method of the stream for each UID in the list.
		@param s	the source or destination stream
		@param prop	this parameter is ignored
	*/
	void ReadWriteReference(IPMStream *s, ImplementationID prop);
};

#pragma export off

#endif	// __PERSISTUIDLIST__
