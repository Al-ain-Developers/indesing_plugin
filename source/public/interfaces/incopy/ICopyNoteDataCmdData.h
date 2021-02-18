//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICopyNoteDataCmdData.h $
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
//  Purpose: Interface data for copying the note data
//  
//========================================================================================

#pragma once
#ifndef __ICopyNoteDataCmdData__
#define __ICopyNoteDataCmdData__

#include "IPMUnknown.h"
#include "NoteID.h"

class IDataBase;

/** Command data interface. To set/get data for command kCopyNoteDataCmdBoss
*/
class ICopyNoteDataCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOPYNOTEDATACMDDATA };

/**	Get method to get the story database that the Note will be copies to.
	@param none
	@return IDataBase* 
 */
		virtual IDataBase*	GetDestinationDB() const = 0;

/**	Set method to set the story database that the Note will be copies to.
	@param db 
 */
		virtual void		SetDestinationDB(IDataBase* db) = 0;
		
/**	Get method to get the story that the Note will be copies to.
	@param none
	@return UID 
 */
		virtual UID			GetDestinationStoryUID() const = 0;

/**	Set method to set the story that the Note will be copies to.
	@param destStoryUID 
 */
		virtual void		SetDestinationStoryUID(UID destStoryUID) = 0;

};

#endif	// __ICopyNoteDataCmdData__