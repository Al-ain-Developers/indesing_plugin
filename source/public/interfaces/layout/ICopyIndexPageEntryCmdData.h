//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICopyIndexPageEntryCmdData.h $
//  
//  Owner: Michel Hutinel
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
//  Purpose: Interface data for copying an Index Page Entry
//  
//========================================================================================

#pragma once
#ifndef __ICopyIndexPageEntryCmdData__
#define __ICopyIndexPageEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"

class IDataBase;

/** Interface data for copying an index page entry.
*/
class ICopyIndexPageEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOPYINDEXPAGEENTRYCMDDATA };

		/** Gets the destination DataBase for the command.
			@return a pointer to the destination database.
		*/
		virtual IDataBase*	GetDestinationDB() const = 0;

		/** Sets the destination DataBase for the command.
			@param db [IN] - a pointer to the destination database.
		*/
		virtual void		SetDestinationDB(IDataBase* db) = 0;

		/** Retrieves the notification flag for the command.
			@return the value of the flag.
		*/ 
		virtual bool16		GetDoNotifyFlag() const = 0;

		/** Sets the notification flag for the command.
			If the flag is set to true, the command will broadcast a notification.
			@param notify [IN] - the value of the flag.
		*/
		virtual void		SetDoNotifyFlag(bool16 notify) = 0;
};

#endif	// __ICopyIndexPageEntryCmdData__