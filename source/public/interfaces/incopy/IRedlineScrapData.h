//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IRedlineScrapData.h $
//  
//  Owner: 
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
#ifndef __IRedlineScrapData__
#define __IRedlineScrapData__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

/** This interface is to specify the source database for the scrap contents on a cut operation.  Used by track
	changes to tell on paste if the content originated from the same document or not.  If the same document
	then the pasted content is marked as Moved Text as opposed to Added Text.
*/
class IRedlineScrapData : public IPMUnknown
{
public:
	/**	Set the source database.
		@param sourceDB the source database.
	*/
	virtual void SetSourceDB(IDataBase *sourceDB) = 0;
	
	/**	Get the source database.
		@return IDataBase* the source database.
	*/
	virtual IDataBase *GetSourceDB() = 0;
};


#endif // __IRedlineScrapData__

