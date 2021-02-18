//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PageItemDataLinkAction.h $
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
#ifndef __PageItemDataLinkAction__
#define __PageItemDataLinkAction__

#include "CPMUnknown.h"
#include "IDataLinkAction.h"
#include "AppInfo.h"

/**
	An implementation of IDataLinkAction for regular page item links.
	An implementation for a custom link could inherit from this implementation.
	@see IDataLinkAction
*/
class  PUBLIC_DECL PageItemDataLinkAction : public CPMUnknown<IDataLinkAction>
{
public:
	PageItemDataLinkAction(IPMUnknown *boss);
	virtual ~PageItemDataLinkAction();
	
	/** 
		Shows the page where the linked page item is on.
		Calls IShowPageItem::Show().
		@see IShowPageItem
		@param errorString OUT, error message if failed
		@return error code of the operation
	*/
	virtual ErrorCode	GotoLink( PMString *errorString  );
	/** 
		Returns whether the go to link is allowd.
		@return kTrue if the action is allowed, kFalse otherwise.
	*/
	virtual bool16		EnableGotoLink();

private:
	bool16		GetLinksPageItem(IDataBase **database, UID *pageitem) const;
};


#endif	// __PageItemDataLinkAction__
