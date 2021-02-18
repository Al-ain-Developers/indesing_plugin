//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IReplaceCmdData.h $
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
#ifndef __IReplaceCmdData__
#define __IReplaceCmdData__

#include "IPMUnknown.h"

/** Data interface for the ReplaceCmd and other similar commands.
*/
class IReplaceCmdData : public IPMUnknown
{
public:
	/** Initialize the command data.

		@param db IN database where the replace will occur.
		@param oldPageItem IN UID of the page item to be replaced.
		@param newPageItem IN UID of the new page item.
		@param useClippingFrame IN retain the clipping frame.
	*/
	virtual void Set(IDataBase *db, UID oldPageItem, UID newPageItem, bool16 useClippingFrame) = 0;
	
	/** Get the affected database. */
	virtual IDataBase *GetDataBase() = 0;
	/** Get the old pageitem. */
	virtual UID GetOldPageItem() = 0;
	/** Get the new pageitem. */
	virtual UID GetNewPageItem() = 0;
	/** Get the use clipping frame flag. */
	virtual bool16 GetUseClippingFrame() = 0;
};

#endif
