//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/ISharedContentSuite.h $
//  
//  Owner: Gaurav Bhargava
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received 
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __ISharedContentSuite__
#define __ISharedContentSuite__

// Interfaces:
#include "IPMUnknown.h"

// Includes:
#include "SharedContentID.h"

/** Interface for the shared content(Linked Text) suite.
	This interface has basic methods for creating and
	checking if shared content creation is poosible.
*/
class ISharedContentSuite : public IPMUnknown
{
	
public:
	enum { kDefaultIID = IID_ISHAREDCONTENTSUITE };

	/**
		Return true if you can create a linked shared content within the same document from the given selection.
		@return kTrue if shared content link can be created.
	*/
	virtual	bool16	CanCreateSharedContentLink() const = 0;

	/**
		Creates a shared content link within the same document if targetDB is nil, else creates across document links.
		@param targetDB [IN] nil for internal links & destination DB for external links.
		@param uiFlags [IN] Options for the links set from UI for Shared Content.
		@return kSuccess if shared content link gets created successfully.
	*/
	virtual	ErrorCode CreateSharedContentLink(IDataBase* targetDB = nil, UIFlags uiFlags = kFullUI) const = 0;	
};

#endif	// __ISharedContentSuite__

