//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogIDDatabase.cpp $
//  
//  Owner: Seoras Ashby
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

#include "IDiagLogIDDatabase.h"

#include "IDiagnosticLog.h"
#include "IDiagLogConfigManager.h"
#include "IPlugInList.h"
#include "IXMLOutStream.h" 
#include "ISaxContentHandler.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ISAXParserOptions.h"
#include "ISAXServices.h"

#include "Utils.h"
#include "FileUtils.h"
#include "IXMLStreamUtils.h"
#include "StreamUtil.h"
#include "ErrorUtils.h"
#include <map>

#include "DiagnosticLogID.h"

#define kNumberOfIDSpace 20

typedef std::map<int32, char *> IDList;

class DiagLogIDDatabase: public CPMUnknown<IDiagLogIDDatabase>
{
public:		
	DiagLogIDDatabase(IPMUnknown *boss);
	~DiagLogIDDatabase();

	virtual void BuildIDDatabase();
	virtual void LoadIDDatabase();
	virtual bool16 IsDatabaseLoaded() {	return fDBLoaded ;}

	virtual void AddID(int32 idSpace, int32 id, const char * idName);
	virtual char * FindID(int32 idSpace, int32 id);

private:
	void GetBiggestPrefix();
	PMString GetIDSpaceName(int32 idSpace);

	bool16 fDBLoaded;
	IDFile fDBFile;
	int32 fHighestPrefix;
	std::map<int32, IDList *> fIDDatabase;
};

CREATE_PMINTERFACE(DiagLogIDDatabase, kDiagLogIDDatabaseImpl)


DiagLogIDDatabase::DiagLogIDDatabase(IPMUnknown *boss) : 
	CPMUnknown<IDiagLogIDDatabase>(boss),
	fHighestPrefix(0),
	fDBLoaded(kFalse)
{
	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
	PMString IDDbName = iConfigManager->GetIDDatabaseName();
	if (!IDDbName.IsEmpty())
	{
		fDBFile = iConfigManager->GetOutputPath();
		FileUtils::AppendPath(&fDBFile, IDDbName);
	}
}


DiagLogIDDatabase::~DiagLogIDDatabase()
{
	for (int32 i=1; i<=kNumberOfIDSpace; i++)
	{
		int32 idSpace = kShuksanPrefix+i;
		IDList * idList = fIDDatabase[idSpace];
		if (idList)
		{
			for (IDList::iterator it = idList->begin(); it != idList->end(); it++)
				delete [] it->second;

			idList->clear();
			delete idList;
		}
	}

	fIDDatabase.clear();
}


void DiagLogIDDatabase::BuildIDDatabase()
{
#ifdef DEBUG
	GetBiggestPrefix();


#ifdef MACINTOSH
	InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamWrite(fDBFile, kOpenOut | kOpenTrunc, 'TEXT', 'CWIE'));
#endif
#ifdef WINDOWS
	InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamWrite(fDBFile, kOpenOut | kOpenTrunc));
#endif

	if (s == nil)
		return;

	IXMLOutStream::AttributeList attrList;
    IXMLOutStream::Attribute aAttr;
	char stringBuffer[256];

    IXMLOutStream * outStream = Utils<IXMLStreamUtils>()->CreateXMLOutPMStream(s, IXMLOutStream::kUTF8);
	outStream->Indent(kTrue);
    outStream->DocHeader(WideString("1.0"), kTrue);
	outStream->Push(WideString("indesigniddatabase"), kTrue);

	InterfacePtr<IObjectModel> om(GetExecutionContextSession(), IID_IOBJECTMODEL);
	ASSERT(om != nil);
	for (int32 i=1; i<=kNumberOfIDSpace; i++)
	{
		attrList.clear();
		int32 idSpace = kShuksanPrefix+i;
		PMString idSpaceName = GetIDSpaceName(idSpace);
		int32 numChar = sprintf(stringBuffer, "%d", idSpace);

		aAttr.fName = WideString("name");
		aAttr.fValue = WideString(idSpaceName);
		attrList.push_back(aAttr);

		aAttr.fName = WideString("value");
		aAttr.fValue = WideString(stringBuffer);
		attrList.push_back(aAttr);

		outStream->PushWithAttributes(WideString("idspace"), attrList);
		for (int32 j=0; j<fHighestPrefix; j++)
		{
			attrList.clear();
			const char * name = (const char*) om->GetIDName(idSpace, j);
			if (name)
			{
				numChar = sprintf(stringBuffer, "%d", j);
				aAttr.fName = WideString("name");
				aAttr.fValue = WideString(name);
				attrList.push_back(aAttr);

				aAttr.fName = WideString("value");
				aAttr.fValue = WideString(stringBuffer);
				attrList.push_back(aAttr);

				outStream->PushWithAttributes(WideString("id"), attrList);
				outStream->Pop(kTrue);
			}
		}

		outStream->Pop(kTrue);
	}

	outStream->Pop(kTrue);
	outStream->Close();
	if (outStream)
		outStream->Release();
#endif
}


void DiagLogIDDatabase::LoadIDDatabase()
{
	if (fDBFile.Exists())
	{
		for (int32 i=1; i<=kNumberOfIDSpace; i++)
		{
			int32 idSpace = kShuksanPrefix+i;
			IDList * idList = new IDList;
			fIDDatabase[idSpace] = idList;
		}

 		InterfacePtr<IPMStream> fileStream((IPMStream*)StreamUtil::CreateFileStreamRead(fDBFile, kOpenIn, 'TEXT', 'CWIE'));
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		InterfacePtr<IK2ServiceProvider> xmlProvider(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, kXMLParserServiceBoss));

		InterfacePtr<ISAXContentHandler> handler(this, IID_ISAXCONTENTHANDLER);
		InterfacePtr<ISAXServices> saxServices(xmlProvider, UseDefaultIID());
		InterfacePtr<ISAXParserOptions> parserOptions(saxServices, UseDefaultIID());

		parserOptions->SetShowWarningAlert(kFalse);
		
		if (saxServices->ParseStream(fileStream, handler))
		{
			if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
				ASSERT_FAIL(FORMAT_ARGS("Error parsing the xml file: %s", ErrorUtils::PMGetGlobalErrorString().GetUTF8String().c_str()));

			// -- As far we we are concerned the errors been handled. Don't propgate the error any further.
			// -- At this early stage leaving the global error set will cause problems with other service providers.
			// hkhalfal: (NACSR) No abortable command sequence used
			// error will not cause prior changes to get rolled back
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);
		}
		else
			fDBLoaded = kTrue;
	}
}


void DiagLogIDDatabase::AddID(int32 idSpace, int32 id, const char * idName)
{
	IDList * idList = fIDDatabase[idSpace];
	char * name = new char[strlen(idName) + 1];
	strcpy(name, idName);
	(*idList)[id] = name;
}


char * DiagLogIDDatabase::FindID(int32 idSpace, int32 id)
{
	if (fDBLoaded)
	{
		IDList * idList = fIDDatabase[idSpace];
		IDList::iterator it = idList->find(id);
		if (it != idList->end())
			return it->second;
	}

#ifdef DEBUG
	TRACE(FORMAT_ARGS("Cannot find ID %d(0x%x) in IDSpace %s!\n", id, id, GetIDSpaceName(idSpace).GetUTF8String().c_str()));
#endif
	return nil;
}


void DiagLogIDDatabase::GetBiggestPrefix()
{
	InterfacePtr<const IPlugInList> plugInList(GetExecutionContextSession(), IID_IPLUGINLIST);
	int32 count = plugInList->GetPluginCount();
	for (int32 i=0; i<count; i++)
	{
		PluginID pluginID = plugInList->GetNthPlugin(i);
		PMString name = plugInList->GetPluginName(pluginID);
		bool16 loaded = plugInList->HasBeenLoaded(pluginID);
		bool16 matchProduct = plugInList->MatchCurrentProduct(pluginID);
		bool16 matchFeatureSet = plugInList->MatchCurrentFeatureSet(pluginID);
		if (pluginID > fHighestPrefix)
			fHighestPrefix = pluginID.Get();
	}

	fHighestPrefix += 1024;
}


PMString DiagLogIDDatabase::GetIDSpaceName(int32 idSpace)
{
	PMString name;
	switch(idSpace)
	{
		case kClassIDSpace:
			name.SetString("kClassIDSpace");
			break;
		case kInterfaceIDSpace:
			name.SetString("kInterfaceIDSpace");
			break;
		case kImplementationIDSpace:
			name.SetString("kImplementationIDSpace");
			break;
		case kWidgetIDSpace:
			name.SetString("kWidgetIDSpace");
			break;
		case kMessageIDSpace:
			name.SetString("kMessageIDSpace");
			break;
		case kServiceIDSpace:
			name.SetString("kServiceIDSpace");
			break;
		case kErrorIDSpace:
			name.SetString("kErrorIDSpace");
			break;
		case kPlugInIDSpace:
			name.SetString("kPlugInIDSpace");
			break;
		case kActionIDSpace:
			name.SetString("kActionIDSpace");
			break;
		case kViewPortAttrIDSpace:
			name.SetString("kViewPortAttrIDSpace");
			break;
		case kUIFontIDSpace:
			name.SetString("kUIFontIDSpace");
			break;
		case kFileTypeInfoIDSpace:
			name.SetString("kFileTypeInfoIDSpace");
			break;
		case kKitViewIDSpace:
			name.SetString("kKitViewIDSpace");
			break;
		case kScriptInfoIDSpace:
			name.SetString("kScriptInfoIDSpace");
			break;
		case kProductIDSpace:
			name.SetString("kProductIDSpace");
			break;
		case kAsyncUIIDSpace:
			name.SetString("kAsyncUIIDSpace");
			break;
		case kScriptIDSpace:
			name.SetString("kScriptIDSpace");
			break;
		case kUserActionCategoryIDSpace:
			name.SetString("kUserActionCategoryIDSpace");
			break;
		default:
			name.SetString("UnknownIDSpace");
			break;
	}

	return name;
}


/*
#define	kClassIDSpace					kShuksanPrefix + 1
#define	kInterfaceIDSpace				kShuksanPrefix + 2
#define	kImplementationIDSpace			kShuksanPrefix + 3
#define	kWidgetIDSpace					kShuksanPrefix + 4
#define	kMessageIDSpace					kShuksanPrefix + 5
#define	kServiceIDSpace					kShuksanPrefix + 6
#define	kErrorIDSpace					kShuksanPrefix + 7
#define	kPlugInIDSpace					kShuksanPrefix + 8
#define	kActionIDSpace					kShuksanPrefix + 9
#define	kViewPortAttrIDSpace			kShuksanPrefix + 10
#define	kUIFontIDSpace					kShuksanPrefix + 11
#define	kFileTypeInfoIDSpace			kShuksanPrefix + 12
#define	kKitViewIDSpace					kShuksanPrefix + 13
#define	kPaletteIDSpace					kShuksanPrefix + 14
#define	kScriptInfoIDSpace				kShuksanPrefix + 15
#define	kProductIDSpace					kShuksanPrefix + 16
#define	kAsyncUIIDSpace					kShuksanPrefix + 17
#define	kUnusedIDSpace			kShuksanPrefix + 18
#define	kScriptIDSpace					kShuksanPrefix + 19
#define	kUserActionCategoryIDSpace		kShuksanPrefix + 20
*/
