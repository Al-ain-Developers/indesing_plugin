//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkPrefsCmdData.h $
//  
//  Owner: Michael Easter
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
#ifndef __ILinkPrefsCmdData__
#define __ILinkPrefsCmdData__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"

#include "ILinkPrefs.h"


/**
 Interface used to hold the command data for the LinkPrefsCmd. 
 @see ILinkPrefs
 */
class ILinkPrefsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKPREFSCMDDATA };

	/** Set the link preference flags.
	 @param db						[IN] Target database of the command.
	 @param bCheckLinksOnOpen		[IN] The "Check Links Before Opening Document" preference.
	 @param bFindMissingLinksOnOpen [IN] The "Auto-find Missing Links Before Opening Document" preference .
	 @param defaultRelinkFolder		[IN] The "Default Relink Folder" preference.
	 */
	virtual void Set(IDataBase* db, bool16 bCheckLinksOnOpen, bool16 bFindMissingLinksOnOpen) = 0;

	/** Get the target database. */
	virtual IDataBase* GetDatabase() const = 0;

	/** Get "Check Links Before Opening Document" preference. */
	virtual bool16 GetCheckLinksOnOpen() const = 0;

	/** Get the "Auto-find Missing Links Before Opening Document" preference. */
	virtual bool16 GetFindMissingLinksOnOpen() const = 0;
};

#endif
