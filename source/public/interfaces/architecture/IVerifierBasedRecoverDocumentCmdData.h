//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IVerifierBasedRecoverDocumentCmdData.h $
//  
//  Owner: Roey Horns
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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
#ifndef __IVerifierBasedRecoverDocumentCmdData__
#define __IVerifierBasedRecoverDocumentCmdData__

#include "IPMUnknown.h"

#ifndef __IDATABASE__
#include "IDataBase.h"
#endif
#include "PMString.h"
#include "IDocument.h"
#include "DocumentID.h"
#include "IDataBasePrivate.h"
#include <map>


class IVerifierBasedRecoverDocumentCmdData : public IPMUnknown
{
public:
    typedef std::map<std::string, std::string> FileLogParamMap;

	enum {kDefaultIID = IID_IVERIFIERBASEDRECOVERDOCUMENTCMDDATA}; 
	virtual void SetPubFilePath(const PMString &path) = 0;
	virtual void SetMiniSaveFilePath(const PMString &path) = 0;
	virtual void SetProtectionLevel(IDataBase::ProtectionLevel level) = 0;
	virtual void SetOpenUIFlag(const bool16& bOpen) = 0;
	virtual void SetIsFauxUserFile(bool bIsFauxUserFile) = 0;
    virtual void SetUserFileName(const PMString &fileName) = 0;
    virtual void SetOperateOnFileType(const IDataBasePrivate::OperateOnFileType fileType) = 0;
    virtual void SetFileLoggingParams(const FileLogParamMap& fileLoggingParamsMap) = 0;
    virtual void SetDocVerifyRecoveryStartTime(const double docVerifyRecoveryInitiateTime) = 0;
    virtual void SetDocIDStr(const std::string& docIDStr) = 0;

	/**
		Set the undo support option @see IDocument.
		@param IDocument::UndoSupport.  
	*/
	virtual void SetUndoSupport(IDocument::UndoSupport undoSupport) = 0;

	
	virtual const PMString& PubFilePath() const = 0;
	virtual const PMString& MiniSaveFilePath() const = 0;
	virtual IDataBase::ProtectionLevel ProtectionLevel() const = 0;
	virtual const bool16& GetOpenUIFlag() const = 0;
	virtual bool16 GetIsFauxUserFile() const = 0;
    virtual const PMString& GetUserFileName() const = 0;
    virtual const IDataBasePrivate::OperateOnFileType GetOperateOnFileType() = 0;
    virtual const FileLogParamMap& GetFileLoggingParams() const = 0;
    virtual const double GetDocVerifyRecoveryStartTime() const = 0;
    virtual const std::string& GetDocIDStr() const = 0;
	/**
		Get the undo support option @see IDocument.
		@return IDocument::UndoSupport.  
	*/
	virtual IDocument::UndoSupport GetUndoSupport() const = 0;
};


#endif // __IDocProtectionPrefsCmdData__
