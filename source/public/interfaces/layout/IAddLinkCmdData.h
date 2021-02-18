//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAddLinkCmdData.h $
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
#ifndef __IAddLinkCmdData__
#define __IAddLinkCmdData__

#include "IPMUnknown.h"
#include "LinksID.h"

class IDataLink;

/** Command data for kAddLinkCmdBoss.
*/
class IAddLinkCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IADDLINKCMDDATA };

	/** Set data to use with a add link command.
        @param db is the data base of the document where you are adding the data link.
        @param dl is the data link you are adding.
        @param pageItemUID is the page item to associate with the link.
        @param formatName is optional string descripting the type of data link.
		This string appears in the Link Information dialog.
	*/ 
	virtual void Set(IDataBase *db, IDataLink *dl, UID pageItemUID, const PMString *formatName = nil) = 0;

	/** Method to get the stored data base.
        @return the data base.
	*/ 
	virtual IDataBase *GetDataBase() = 0;

	/** Method to get the stored data link.
        @return the data link.
	*/ 
	virtual IDataLink *GetDataLink() = 0;

	/** Method to get the stored page item.
        @return the page item.
	*/ 
	virtual UID GetPageItemUID() = 0;

	/** Method to get the stored format name string.
        @return the format name string.
	*/ 
	virtual PMString *GetFormatName() = 0;
};

#endif
