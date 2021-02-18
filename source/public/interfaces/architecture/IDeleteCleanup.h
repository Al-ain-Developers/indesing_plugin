//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDeleteCleanup.h $
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
//  A service which is used when a page item is deleted
//  
//========================================================================================

#pragma once
#ifndef __IDeleteCleanup__
#define __IDeleteCleanup__

#include "IPMUnknown.h"
#include "ICommand.h"
#include "IScrapItem.h"

/** Service interface that is called when a page item is deleted
	To use, create a Boss that implements IID_IK2SERVICEPROVIDER as kDeleteCleanupProviderImpl
	And IID_IDELETECLEANUP as a custom version of IDeleteCleanup...

	An example is kBehaviorDeleteCleanupImpl that checks the IScrapItem parameter to
	see if it is referenced by behaviors, using IPageItemBehaviorXRef @see IPageItemBehaviorXRef
	If a page item is referenced by a behavior, the behavior can then be modified so that it
	doesn't reference the page item being deleted...
*/
class IDeleteCleanup : public IPMUnknown
{
public:
	/** Get a command to be executed before scrapItem is deleted
		@param cmd The command being executed to delete scrapItem
		@param scrapItem page item being deleted
		@return a command to be executed before scrapItem is deleted */
	virtual ICommand *GetPreDeleteCommand(ICommand *cmd, IScrapItem *scrapItem) = 0;

	/** Get a command to be executed after scrapItem is deleted
		@param cmd The command being executed to delete scrapItem
		@param scrapItem page item being deleted
		@return a command to be executed after scrapItem is deleted */
	virtual ICommand *GetPostDeleteCommand(ICommand *cmd, IScrapItem *scrapItem) = 0;
};

#endif
