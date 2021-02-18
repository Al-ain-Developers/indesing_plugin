//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkItemSuite.h $
//  
//  Owner: SusanCL
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
//  Defines the interface for a Link suite to be used in the new selection architecture
//  
//========================================================================================

#pragma once
#ifndef __ILINKITEMSUITE__
#define __ILINKITEMSUITE__

// ----- Interface files
#include "IPMUnknown.h"

// ----- ID files
#include "LinksID.h"		// for IID_ILINKSUITE

class UIDList;

/** Abstract suite interface for accessing the document selection's Link data.
	@ingroup layout_suite
*/
class ILinkItemSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILINKITEMSUITE };
	
	/**	Returns a ist of ILink UID in the selection. Caller will need to delete the returned UIDList*
		@returns an UIDList* of ILink UID.
	*/
	virtual UIDList*	CreateItemsDataLinkUIDList	(void) = 0;
};

#endif		// __ILINKITEMSUITE__