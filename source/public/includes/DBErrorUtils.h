//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DBErrorUtils.h $
//  
//  Owner: Roey Horns
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
#ifndef __DBERRORUTILS__
#define __DBERRORUTILS__

// ----- Interfaces -----

#include "IDBErrorInfo.h"
#include "IDocument.h"

// ----- Includes -----

#include "CreateObject.h"
#include "InterfacePtr.h"

// ----- Utility files -----

#include "ErrorUtils.h"
#include "PersistUtils.h"

// ----- ID.h files -----

#include "ShuksanID.h"


class DBErrorUtils
{
	// Helper methods to copy the local error of a database to the global error state.
	// Each method clears the local error of the database.
	
	public:
	
	static void SetDBError(ErrorCode errCode, IDataBase::DBResultCode dbErr)
	{
		if(dbErr == IDataBase::kUserCanceled)
		{
			ErrorUtils::PMSetGlobalErrorCode(kCancel);
		}
		else
		{
			IDBErrorInfo *errInfo = (IDBErrorInfo *)::CreateObject(kDBErrorInfoBoss, IID_IDBERRORINFO);
			
			if(errInfo != nil)
				errInfo->SetInfo(dbErr);
			
			ErrorUtils::PMSetGlobalErrorCode(errCode, nil, errInfo);
			
			if(errInfo != nil)
				errInfo->Release();
		}
	}
	
	static void SetDBError(ErrorCode errCode, IDataBase* db)
	{		
		if(db && db->GetErrorCode() == IDataBase::kUserCanceled)
		{
			ErrorUtils::PMSetGlobalErrorCode(kCancel);
		}
		else
		{
			IDBErrorInfo *errInfo = (IDBErrorInfo *)::CreateObject(kDBErrorInfoBoss, IID_IDBERRORINFO);
		
			if(errInfo != nil)
				errInfo->SetInfo(db);
			
			ErrorUtils::PMSetGlobalErrorCode(errCode, nil, errInfo);
			
			
			if(errInfo != nil)
				errInfo->Release();
		}
		if(db != nil)
			db->ClearError();
	}
	
	static void SetDBError(ErrorCode errCode, IDocument* doc)
	{		
		IDataBase *db = ::GetDataBase(doc);
		
		if(db && (db->GetErrorCode() == IDataBase::kUserCanceled))
		{
			ErrorUtils::PMSetGlobalErrorCode(kCancel);
		}
		else
		{
			IDBErrorInfo *errInfo = (IDBErrorInfo *)::CreateObject(kDBErrorInfoBoss, IID_IDBERRORINFO);
		
			if(errInfo != nil)
				errInfo->SetInfo(doc);
			
			ErrorUtils::PMSetGlobalErrorCode(errCode, nil, errInfo);
			
			
			if(errInfo != nil)
				errInfo->Release();
		}
		if(doc != nil)
		{
			if(db != nil)
				db->ClearError();
		}
	}
	
	static void SetDBError(ErrorCode errCode, const IDFile *file)
	{	
		if (file != nil)
		{
			InterfacePtr<IDBErrorInfo> errInfo((IDBErrorInfo *)::CreateObject(kDBErrorInfoBoss, IID_IDBERRORINFO));
			if(errInfo != nil)
			{
				errInfo->SetInfo(*file);
			}
			ErrorUtils::PMSetGlobalErrorCode(errCode, nil, errInfo);
		}
		else
		{
			ErrorUtils::PMSetGlobalErrorCode(errCode);
		}
	}
};

#endif // __DBERRORUTILS__
