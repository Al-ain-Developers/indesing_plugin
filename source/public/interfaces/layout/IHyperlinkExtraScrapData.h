//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkExtraScrapData.h $
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
//  An interface off the scrap document, contains a list of extra info needed for 
//  copying unnamed page destinations around
//  
//========================================================================================

#pragma once
#ifndef __IHyperlinkExtraScrapData__
#define __IHyperlinkExtraScrapData__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

class UIDList;

/**
	@ingroup layout_hyper
	@ingroup arch_scrap
*/
class IHyperlinkExtraScrapData : public IPMUnknown
{
public:

	/**	Add a new hyperlink source
		@param *originatingDB - The initial database of the hyperlink
		@param hyperlinkExtraData - The UID of the extra data to copy
	 */
	virtual void Add(IDataBase *originatingDB, const UID hyperlinkExtraData) = 0;

	/**	return the nth UID stored
		@param n - The UID to Return
		@return UID - The UID
	 */
	virtual UID GetNthExtraStuffUID(int32 n) = 0;

	/**	return the nth database stored
		@param n - Which database to return
		@return IDataBase - The database
	 */
	virtual IDataBase *GetNthExtraStuffDB(int32 n) = 0;

	/**	how many entries?
		@param none
		@return int32 - Number of entries
	 */
	virtual int32 Length() = 0;
};


#endif // __IHyperlinkExtraScrapData__

