//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LibraryAssetObserverMsg.h $
//  
//  Owner: Mark VerMurlen
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
//  Reviewed: 9/25/98
//  
//  Purpose:
//  This class is used by the Library to specify to the Asset Observers
//  what changes were made to the Asset Collection.
//  
//========================================================================================

#pragma once
#ifndef __LibraryAssetObserverMsg__
#define __LibraryAssetObserverMsg__

#include "LibraryAssetID.h"


class ILibraryAssetCollection;

/** This class is used by the Library to specify to the Asset Observers
	what changes were made to the Asset Collection.
*/
class LibraryAssetObserverMsg
{
public:
	/** Types of things that can happen to an asset or collection.
	*/
	enum MessageType
		{
			kMsg_NewAssetCollection = 0,
			kMsg_NewAsset,
			kMsg_DeleteAsset,
			kMsg_ChangeAsset
		};
	/** What happened to the asset or collection.
	*/
	MessageType					fMsgType;

	/** Which asset it happened to.
	*/
	LibraryAssetID				fAssetID;

	/** Which collection the asset is/was in.
	*/
	ILibraryAssetCollection*	fCollection;
};

#endif	// __LibraryAssetObserverMsg__
