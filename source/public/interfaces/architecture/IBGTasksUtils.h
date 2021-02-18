//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBGTasksUtils.h $
//  
//  Owner: Steve Balensiefer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __IBGTasksUtils__
#define __IBGTasksUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "PMString.h"
#include "UIDRef.h"

/** This interface provides utility routines for detecting usage conflicts between tasks
	i.e. Utils<IBGTasksUtils>()->IsDocumentInUseByBGTasks( ... ) ;
*/

class IDocument;

#define ALLOW_SAVE_WITH_CLONES

class IBGTasksUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBGTASKSUTILS};

	/**
	  Check if any background task is using the document described by documentRef.
	  
	  @note If documentRef is kInvalidUIDRef it checks if there are any user tasks.

	  @param documentRef a UIDRef for the document
	  @param bDoDetailChecking if kTrue, perform additional checks to confirm that no running background thread is still using the document

	  @return kTrue if any background tasks is using the document
	*/
	virtual bool16  IsDocumentInUseByBGTasks( const UIDRef& documentRef, bool bDoDetailChecking = false) const = 0;

	/**
	  Check if any background task is using a database or its clones
	  @param db the IDataBase in question
	  @param bDoDetailChecking if kTrue, perform additional checks to confirm that no running background thread is still using the db
	  @return kTrue if any background tasks is using the database
	*/
	virtual bool16  IsDataBaseInUseByBGTasks( IDataBase* db, bool bDoDetailChecking = false) const = 0;

	/**
	  Check if any background task is exporting to the file targetFile.
	  Intended to prevent export filename collisions.
	  @param targetFile The file to check
	  @return kTrue if any background tasks have registered interest in the file
	*/
	virtual bool16  IsTargetFileInUseByBGTasks( const IDFile& targetFile ) const = 0;

	/**
	  Create the error string for a document action that fails because the
	  document is in use by background tasks.

	  @param item [IN]: the document
	  @param action [IN]: the failed action

	  @return a PMString containing an error string with the action and document inserted
	  */
	virtual PMString CreateDocActionWarningAboutBGTasks( const UIDRef& item, const ActionID& action ) const = 0;
};

#endif	// __IBGTasksUtils__
