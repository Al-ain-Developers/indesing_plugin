//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/PDFVTExportProvider.cpp $
//
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

#include "CPMUnknown.h"
#include "IPDFExportSetupProvider.h"
#include "IPDFDPartHierarchy.h"
#include "IPDFDPartMetadataUtils.h"
#include "IViewPort.h"
#include "IStructureMarks.h"
#include "IPageList.h"
#include "IDocument.h"
#include "IDataSourceData.h"
#include "StringUtils.h"
#include "PDFVTUtils.h"

#include <queue>
#include <map>

#include "PDFVTID.h"

using namespace std;

/** Implements a service provider, which writes CIP4 metadata to the
    PDF file being exported.

	@ingroup pdfvt
*/
class PDFVTExportProvider : public CPMUnknown<IPDFExportSetupProvider>
{
public:
	/** Constructor.
			@param boss object this object is aggregated on.
	*/
	PDFVTExportProvider(IPMUnknown* boss);

	/** Destructor.
	*/
	~PDFVTExportProvider();

	virtual bool16 PDFProcessEvent(PDFExportEvent* pdfExportEvent,
		                           int32           pageNum);

private:
	/** Handle the kPDFExportEventBeginExport event during PDF export.
			@param pdfExportEvent the current event.
			@param pageNum the current page based index for the event, zero based.
	*/
	void handleBeginExport(PDFExportEvent* pdfExportEvent, int32 pageNum);

	/** Handle the kPDFExportEventDrawPage event during PDF export.
			@param pdfExportEvent the current event.
			@param pageNum the current page based index for the event, zero based.
	*/
	void handleDrawPage(PDFExportEvent* pdfExportEvent, int32 pageNum);
	
	/** Handle the kPDFExportEventEndExport event during PDF export.
			@param pdfExportEvent the current event.
			@param pageNum the current page based index for the event, zero based.
	*/
	void handleEndExport(PDFExportEvent* pdfExportEvent, int32 pageNum);

	/** Create the document part metadata for the document part.
			@param recordNum document part number.
			@param pdfExportEvent the current event.
			@return ID of the metadata
	*/
	CosObjID CreateRecordDPartCIP4MetaData(int32 recordNum, PDFExportEvent* pdfExportEvent);

	/** Create the root document part metadata.
			@param pdfExportEvent the current event.
			@return ID of the metadata
	*/
	CosObjID CreateRootDPartCIP4Metadata(PDFExportEvent* pdfExportEvent);

	/** Reset the internal state of the provider after a PDF export
		session is done.
	*/
	void Reset(void);

private:

	/** Root document part node.
	*/
	DPartNode* fRootDPartNode;

	/** Leaf document part node.
	*/
	DPartNode* fRecordDPartNode;

	/** Record number for the document part.
	*/
	int32 fRecordNum;

	/** Number of pages for each document part.
	*/
	int32 fPagesPerRecord;

	/** UIDRef for the document being exported.
	*/
	UIDRef fUidRef;

	/** Comma separated keys in the extenal datasource file.
	*/
	vector<string> fKeyList;

	/** Record list in the exernal  datasource file.
	*/
	queue<vector<string> > fRecordList;	

	/** Flag indicating if we are exporing PDFVT file.
	*/
	bool16 fIsExportingPDFVT;

	/** CIP4 metadata mapping.
	*/
	map<WideString, WideString> fCIP4Mapping;

	/** Unique id for each recipient.
	*/
	int32 fUniqueID;
};

CREATE_PMINTERFACE(PDFVTExportProvider, kPDFVTExportProviderImpl)

PDFVTExportProvider::PDFVTExportProvider(IPMUnknown* boss) : CPMUnknown<IPDFExportSetupProvider>(boss),
	fRootDPartNode(nil),
	fRecordDPartNode(nil),
	fRecordNum(0),
	fPagesPerRecord(1),
	fUidRef(UIDRef::gNull),
	fKeyList(),
	fRecordList(),
	fIsExportingPDFVT(kFalse),
	fCIP4Mapping(),
	fUniqueID(0)
{
}

PDFVTExportProvider::~PDFVTExportProvider()
{
}

bool16 PDFVTExportProvider::PDFProcessEvent(PDFExportEvent* pdfExportEvent, int32 pageNum)
{	
	PDFExportEventID id = pdfExportEvent->id;

	if (fUidRef == UIDRef::gNull)
	{
		switch (id)
		{
		case kPDFExportEventBeginExport:
			{
				InterfacePtr<IDocument> doc(pdfExportEvent->db, (pdfExportEvent->db)->GetRootUID(), IID_IDOCUMENT);
				InterfacePtr<IPageList> pageList(doc, UseDefaultIID());
				int32 numberOfPages = pageList->GetPageCount();
				fPagesPerRecord = numberOfPages;

				InterfacePtr<IDataSourceData> dataSourceData(doc, UseDefaultIID());

				if (dataSourceData == nil || (dataSourceData->GetPath()).empty())
				{
					return kTrue;
				}

				fCIP4Mapping = dataSourceData->GetCIP4Mapping();
				
				fIsExportingPDFVT = PDFVTUtils::ReadDataSource(dataSourceData->GetPath(), fKeyList, fRecordList);				

				UIDRef uidRef = ::GetUIDRef(doc);
				fUidRef = UIDRef(uidRef);
				handleBeginExport(pdfExportEvent, pageNum);

				break;
			}

		default:			
			break;
		}
	}
	else
	{
		switch (id)
		{
		case kPDFExportEventDrawPage:
			{
				InterfacePtr<IDocument> doc(pdfExportEvent->db, (pdfExportEvent->db)->GetRootUID(), IID_IDOCUMENT);
				UIDRef uidRef = ::GetUIDRef(doc);			
				if (fUidRef == uidRef)
				{
					handleDrawPage(pdfExportEvent, pageNum);
				}
				break;
			}

		case kPDFExportEventEndExport:
			{
				handleEndExport(pdfExportEvent, pageNum);
				fUidRef = UIDRef::gNull;
				break;
			}

		default:
			break;
		}
	}

	return kTrue;
}

void PDFVTExportProvider::handleBeginExport(PDFExportEvent* pdfExportEvent, int32 pageNum)
{
	if (fIsExportingPDFVT)
	{
		InterfacePtr<IPDFDPartHierarchy> iHier(pdfExportEvent->targetPort, UseDefaultIID());
		NodeNameList nodeNames;
		nodeNames.push_back(PMString(L"Root"));
		nodeNames.push_back(PMString(L"Record"));
		iHier->SetNodeNameList(nodeNames);
		iHier->SetRecordLevel(1);
		fRootDPartNode = iHier->CreateDPartRootNode(IPDFDPartHierarchy::kNonLeafNode);

		CosObjID dpmObj = CreateRootDPartCIP4Metadata(pdfExportEvent);		
		iHier->SetMetadata(fRootDPartNode, dpmObj);
	}
}

void PDFVTExportProvider::handleDrawPage(PDFExportEvent* pdfExportEvent, int32 pageNum)
{
	if (fIsExportingPDFVT)
	{
		bool16 recordChange = ((pageNum % fPagesPerRecord) == 0) ? kTrue : kFalse;
		InterfacePtr<IPDFDPartHierarchy> iHier(pdfExportEvent->targetPort, UseDefaultIID());
		if (pageNum > 0)
		{			
			iHier->AddPage(fRecordDPartNode, pageNum - 1, recordChange);			
		}

		if (recordChange)
		{
			fRecordNum++;
			fRecordDPartNode = iHier->CreateChildDPart(fRootDPartNode, IPDFDPartHierarchy::kLeafNode);			
			CosObjID dpmObj = CreateRecordDPartCIP4MetaData(fRecordNum, pdfExportEvent);			
			iHier->SetMetadata(fRecordDPartNode, dpmObj);
		}
	}
}

void PDFVTExportProvider::handleEndExport(PDFExportEvent* pdfExportEvent, int32 pageNum)
{
	if (fIsExportingPDFVT)
	{
		if (pageNum > 0)
		{
			InterfacePtr<IPDFDPartHierarchy> iHier(pdfExportEvent->targetPort, UseDefaultIID());
			iHier->AddPage(fRecordDPartNode, pageNum - 1, kTrue);			
		}
	}
	Reset();
}

CosObjID PDFVTExportProvider::CreateRecordDPartCIP4MetaData(int32 recordNum, PDFExportEvent* pdfExportEvent)
{
	InterfacePtr<IPDFDPartMetadataUtils> metadataUtils(pdfExportEvent->targetPort, UseDefaultIID());

	CosObjID dpmObj = metadataUtils->CreateNewDict(1);	
	CosObjID cip4RootDictObj = metadataUtils->CreateNewDict(1);
	CosObjID cip4RecipientLevelDictObj = metadataUtils->CreateNewDict(1);
	CosObjID cip4ContactDictObj = metadataUtils->CreateNewDict(1);
	CosObjID cip4PersonDictObj = metadataUtils->CreateNewDict(1);
	CosObjID cip4AddressDictObj = metadataUtils->CreateNewDict(1);	

	if (!fRecordList.empty())
	{
		const vector<string> record = fRecordList.front();
		for (size_t i = 0; i < fKeyList.size(); i++)
		{
			string key = fKeyList[i];
			string value = "";
			if (i < record.size())
			{
				value = record[i];
			}

			WideString wKey;
			StringUtils::ConvertUTF8ToWideString(key, wKey);
			map<WideString, WideString>::const_iterator it = fCIP4Mapping.find(wKey);
			if (it != fCIP4Mapping.end())
			{
				if ((it->second) == WideString("FirstName") ||
					(it->second) == WideString("LastName"))
				{
					WideString ws;
					StringUtils::ConvertUTF8ToWideString(value, ws);
					metadataUtils->PutString(cip4PersonDictObj, PMString(it->second).GetPlatformString().c_str(), PMString(ws));
				}
				else if ((it->second) == WideString("City") ||
					     (it->second) == WideString("PostalCode") ||
						 (it->second) == WideString("Country"))
				{
					WideString ws;
					StringUtils::ConvertUTF8ToWideString(value, ws);
					metadataUtils->PutString(cip4AddressDictObj, PMString(it->second).GetPlatformString().c_str(), PMString(ws));
				}
			}
		}

		string id = PDFVTUtils::ToString<int32>(fUniqueID++);
		metadataUtils->PutString(cip4RecipientLevelDictObj, "UniqueId", id.c_str());

		fRecordList.pop();
	}

	metadataUtils->PutDict(cip4ContactDictObj, "Person", cip4PersonDictObj);
	metadataUtils->PutDict(cip4ContactDictObj, "Address", cip4AddressDictObj);

	metadataUtils->PutDict(cip4RecipientLevelDictObj, "Contact", cip4ContactDictObj);
	
	metadataUtils->PutDict(cip4RootDictObj, "Recipient", cip4RecipientLevelDictObj);

	metadataUtils->PutDict(dpmObj, "CIP4:Root", cip4RootDictObj);

	return dpmObj;	
}

CosObjID PDFVTExportProvider::CreateRootDPartCIP4Metadata(PDFExportEvent* pdfExportEvent)
{
	InterfacePtr<IPDFDPartMetadataUtils> metadataUtils(pdfExportEvent->targetPort, UseDefaultIID());
	CosObjID dpmDictObj = metadataUtils->CreateNewDict(1);
	CosObjID cip4RootDictObj = metadataUtils->CreateNewDict(1);
	CosObjID metadataDictObj = metadataUtils->CreateNewDict(1);

	metadataUtils->PutString(metadataDictObj, "Conformance", "base");
	metadataUtils->PutString(metadataDictObj, "Creator", kPDFVTPluginName);
	metadataUtils->PutString(metadataDictObj, "ModificationDate", "MODIFICATION_DATE_PLACEHOLDER");
	metadataUtils->PutString(metadataDictObj, "JobID", "JOB_ID_PLACEHOLDER");

	metadataUtils->PutDict(cip4RootDictObj, "Metadata", metadataDictObj);

	metadataUtils->PutDict(dpmDictObj, "CIP4:Root", cip4RootDictObj);

	return dpmDictObj;
}

void PDFVTExportProvider::Reset(void)
{
	fRecordNum = 0;
	fPagesPerRecord = 1;
	fUidRef = UIDRef::gNull;
	fIsExportingPDFVT = kFalse;

	fKeyList.clear();	
	
	while (!fRecordList.empty())
	{
		fRecordList.pop();
	}

	fCIP4Mapping.clear();
	fUniqueID = 0;
}
