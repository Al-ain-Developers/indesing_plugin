//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/ClosingDocumentsResponder.cpp $
//  
//  Owner: Sachin Singhal
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
//  Copyright 2020 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces
#include "IApplication.h"
#include "IDataBase.h"
#include "IDataBasePrivate.h"
#include "IDocument.h"
#include "ISubject.h" 
#include "IUIDData.h"

// Utils
#include "FileUtils.h" 
#include "StringUtils.h"
#include "Utils.h"

// Responder stuff
#include "CResponder.h"
#include "CServiceProvider.h" 
#include "isignalmgr.h"
#include "IDocumentSignalData.h"

// ID.h
#include "AppUIID.h"
#include "LinksUIID.h"

// includes
#include "InDesignSessionDataManager.h" 

/** Registers as providing the service of responding to relevant
	events for the purpose of determining closing documents in InDesign.
*/
class ClosingDocumentsServiceProvider : public CServiceProvider
{
public:
	ClosingDocumentsServiceProvider(IPMUnknown* boss);
	virtual    ~ClosingDocumentsServiceProvider() {}

	virtual void GetName(PMString* pName) { if (pName) pName->SetKey("Closing Documents Responder Service"); }
	virtual ServiceID GetServiceID() { ASSERT_UNIMPLEMENTED(); return kInvalidService; }
	virtual bool16 IsDefaultServiceProvider() { return kFalse; }
	virtual InstancePerX GetInstantiationPolicy() { return IK2ServiceProvider::kInstancePerSession; }
	virtual bool16 HasMultipleIDs() const { return kTrue; }
	virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs) { serviceIDs.insert(serviceIDs.end(), fSupportedServiceIDs.begin(), fSupportedServiceIDs.end()); }
private:
	K2Vector<ServiceID> fSupportedServiceIDs;
};

CREATE_PMINTERFACE(ClosingDocumentsServiceProvider, kClosingDocumentsServiceProviderImpl)

ClosingDocumentsServiceProvider::ClosingDocumentsServiceProvider(IPMUnknown* boss) :
	CServiceProvider(boss),
	fSupportedServiceIDs()
{
	// Adding the serviceIDs we want responder to handle. 

	//    CloseDocument 
	fSupportedServiceIDs.push_back(kBeforeCloseDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterCloseDocSignalResponderService);

	//    CloseWindow 
	fSupportedServiceIDs.push_back(kBeforeCloseWindowSignalResponderService);
}

// This responder keeps track of whether currently a non headless document is in the process of being closed or not.
class ClosingDocumentsResponder : public CResponder
{
public:
	ClosingDocumentsResponder(IPMUnknown *boss) : CResponder(boss) 
	{
	}

	virtual void Respond(ISignalMgr* iSignalMgr);
private:
	void CreateDocumentKey(IDataBase* db, WideString &key);
	static std::vector<WideString> fFilesClosingList;
	static WideString fFilePath;
};

WideString ClosingDocumentsResponder::fFilePath;
std::vector<WideString> ClosingDocumentsResponder::fFilesClosingList;

CREATE_PMINTERFACE(ClosingDocumentsResponder, kClosingDocumentsResponderImpl)

void ClosingDocumentsResponder::CreateDocumentKey(IDataBase* db, WideString &documentKey)
{
	IDataBasePrivate *dbPrivate = dynamic_cast<IDataBasePrivate *>(db);
	WideString documentPath, documentID;
	if (dbPrivate)
	{
        StringUtils::ConvertUTF8ToWideString(dbPrivate->GetDocumentID().GetUTF8String(), documentID);
	}
	const IDFile *sysFile = db->GetSysFile();
	if (sysFile)
	{
		PMString documentPathStr;
		FileUtils::IDFileToPMString(*sysFile, documentPathStr);
		StringUtils::ConvertUTF8ToWideString(documentPathStr.GetUTF8String(), documentPath);
	}
	
	documentKey.Clear();
	documentKey.Append(documentPath);
	documentKey.Append(documentID);
}

void ClosingDocumentsResponder::Respond(ISignalMgr* signalMgr)
{
	ServiceID serviceID = signalMgr->GetServiceID();
	if (serviceID == kBeforeCloseWindowSignalResponderService)
	{
		// This will let us know about the document that is being closed.
		InterfacePtr<IUIDData>	documentData(signalMgr, UseDefaultIID());
		IDataBase* db = documentData->GetItemDataBase();
		WideString documentKey;
		CreateDocumentKey(db, documentKey);

		fFilesClosingList.push_back(documentKey);							// store the document path in the list we have.

		// Set the flag to show that some document is closing.
		InDesignSessionDataManager::GetInstance().Insert(InDesignSessionDataStoreKeyType::kFilesClosing, kTrue);
	}
	else if (serviceID == kBeforeCloseDocSignalResponderService)
	{
		ASSERT_MSG(fFilePath.empty(), "Document close already in progress!");

		// It is essential to capture the file path here so as the information will not be available while responding to kAfterCloseDocSignalResponderService.
		InterfacePtr<IDocumentSignalData> signalData(signalMgr, UseDefaultIID());
		InterfacePtr<IDocument> document(signalData->GetDocument(), UseDefaultIID());

		IDataBase *db = ::GetDataBase(document);
		fFilePath.Clear();
		CreateDocumentKey(db, fFilePath);
	}
	else if (serviceID == kAfterCloseDocSignalResponderService)
	{
		// Document is null in the signal data at this point of time. Hence we can only rely on the file path being stored while responding to kBeforeCloseDocSignalResponderService.
		// If the file path is empty that means that it was an unsaved document and thus not have been captured above. So we can skip this.
		if (!fFilePath.empty())
		{
			auto itr = std::find(std::begin(fFilesClosingList), std::end(fFilesClosingList), fFilePath);
			if (itr != std::end(fFilesClosingList))
			{
				// A match has been found in the list. 
				fFilesClosingList.erase(itr);
				if (fFilesClosingList.size() == 0)
				{
					// Set the flag to show that no document is closing.
					InDesignSessionDataManager::GetInstance().Insert(InDesignSessionDataStoreKeyType::kFilesClosing, kFalse);

					InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
					InterfacePtr<ISubject> subject(app, IID_ISUBJECT);
					subject->Change(kPendingDocumentsClosedMsg, IID_IAPPLICATION);
				}
			}
			fFilePath.Clear();
		}
	}
}
