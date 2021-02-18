//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICopyDeletedTextCmdData.h $
//  
//  Owner: Wai Cheuk
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
//  Purpose: Interface data for copying the deleted text story thread.
//  
//========================================================================================

#pragma once
#ifndef __ICopyDeletedTextCmdData__
#define __ICopyDeletedTextCmdData__

#include "IPMUnknown.h"
#include "NoteID.h"

class IDataBase;

/** Command data interface to get/set data for command kCopyDeletedTextCmdBoss.
*/
class ICopyDeletedTextCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOPYDELETEDTEXTCMDDATA };

		/**	Get method to get the database the deleted text will be copied to.
			@return IDataBase* the destination database.
		*/
		virtual IDataBase*	GetDestinationDB() const = 0;

		/**	Set method to set the database the deleted text will be copied to.
			@param db the destination database ptr.
		*/
		virtual void		SetDestinationDB(IDataBase* db) = 0;
		
		/**	Get method to get the story uid the deleted text will be copied to.
			@return UID the destination story UID.
		*/
		virtual UID		GetDestinationStoryUID() const = 0;
		
		/**	Set method to set the story uid the deleted text will be copied to. 
			@param destStoryUID the destination story UID.
		*/
		virtual void		SetDestinationStoryUID(UID destStoryUID) = 0;

};

#endif	// __ICopyDeletedTextCmdData__
