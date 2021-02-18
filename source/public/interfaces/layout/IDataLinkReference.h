//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDataLinkReference.h $
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
#ifndef __IDATALINKREFERENCE__
#define __IDATALINKREFERENCE__

#include "LinksID.h"

/** IDataLinkReference stores a reference to a data link.
	IID_IDATALINKREFERENCE interface.
*/
class IDataLinkReference : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATALINKREFERENCE };

	/** Method to set the data link UID (IDataLink).
		@param id of data link UID.
	*/ 
	virtual void SetUID(UID id) = 0; 

	/** Method to get the data link UID (IDataLink).
		@return data link UID.
	*/ 
	virtual UID GetUID() const = 0; 

	/** Method to persist this interface.
		@param iPMStream is the stream to read or write from.
		@param id is the implementation ID.
	*/ 
	virtual void ReadWrite(IPMStream* iPMStream, ImplementationID id) = 0;
};

#endif // __IDATALINKREFERENCE__
