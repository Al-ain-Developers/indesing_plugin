//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogStartupShutdown.cpp $
//  
//  Owner:
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

#include "IStartupShutdownService.h"

// Interface includes:
#include "IDiagnosticLogger.h"
#include "IPlugInList.h"
#include "IDiagnosticLog.h"
#include "IDiagLogConfigManager.h"
#include "IDiagLogIDDatabase.h"
#include "IXMLStreamUtils.h"
#include "IApplication.h"
#include "IDiagLoggerManager.h"
#include "IIdleTask.h"

// General includes:
#include "CPMUnknown.h"
#include "FileUtils.h"
#include "StreamUtil.h"
#include "LocaleSetting.h"
#include "DiagnosticLogUtils.h"

// Project includes:
#include "DiagnosticLogID.h"


class DiagLogStartupShutdown : public CPMUnknown<IStartupShutdownService>
{
public:
	DiagLogStartupShutdown(IPMUnknown* boss	);

	virtual	~DiagLogStartupShutdown() {}

	virtual	void Startup();
	virtual	void Shutdown();

private:
	void GenerateRTEnvironmentReport();
	PMString GetProductFSString(const PMLocaleId& idLocale);
	PMString GetLanguageFSString(const PMLocaleId& idLocale);
	PMString GetUIString(const PMLocaleId& idLocale);
	
	void OutputTag(IXMLOutStream * out, const WideString & tag, const WideString & content);
	void OutputTag(IXMLOutStream * out, const WideString & tag, bool16 boolValue);
	void OutputTag(IXMLOutStream * out, const WideString & tag, int32 intValue);

private:
	IDiagLogIDDatabase * iDB;
	IIdleTask * fDiagLogIdleTask;
};

CREATE_PMINTERFACE(DiagLogStartupShutdown, kDiagLogStartupShutdownImpl)

DiagLogStartupShutdown::DiagLogStartupShutdown(IPMUnknown* boss) :
	CPMUnknown<IStartupShutdownService>(boss),
	iDB(nil)
	,fDiagLogIdleTask(nil)
{
}


void DiagLogStartupShutdown::Startup()
{
	ISession* session = GetExecutionContextSession();
	ASSERT(session != nil);
	InterfacePtr<IDiagnosticLog> iDiagnosticLog(session, UseDefaultIID());

	// construct logger manager before load configuration file
	InterfacePtr<IDiagLoggerManager> iLoggerManager(iDiagnosticLog->QueryDiagLoggerManager());
	InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
	iConfigManager->Load();

	// after loading config, init each logger
	for (int32 i=0; i<iLoggerManager->GetNumLoggers(); i++)
	{
		IDiagnosticLogger * logger = iLoggerManager->GetNthLogger(i);
		logger->InitializeLogger();
	}

	// ID database. BuildIDDatabase only work in debug build
	InterfacePtr<IDiagLogIDDatabase> iDiagLogIDDB(iLoggerManager, UseDefaultIID());
	iDiagLogIDDB->BuildIDDatabase();

	if (iConfigManager->GetLoadIDDatabase())
	{
		iDB = iDiagLogIDDB;
		iDB->LoadIDDatabase();
		iDB->AddRef();
	}

	GenerateRTEnvironmentReport();

	// turn on info collector
	DiagnosticLogUtils::DiagnosticLogStartup();

	fDiagLogIdleTask = (IIdleTask*) ::CreateObject (kDiagnosticLogIdleTaskBoss, IID_IIDLETASK);
	fDiagLogIdleTask->InstallTask(10000);
}


void DiagLogStartupShutdown::Shutdown()
{
	DiagnosticLogUtils::DiagnosticLogShutdown();

	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
	iConfigManager->Save();

	if(iDB)
	{
		iDB->Release();
		iDB = nil;
	}

	fDiagLogIdleTask->UninstallTask();
	fDiagLogIdleTask->Release();
}


// Output run time environment
void DiagLogStartupShutdown::GenerateRTEnvironmentReport()
{
	char buffer[64];
	IXMLOutStream::AttributeList attrList;
    IXMLOutStream::Attribute aAttr;

	InterfacePtr<const IPlugInList> plugInList(GetExecutionContextSession(), IID_IPLUGINLIST);
	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());

	IDFile rteFile(iConfigManager->GetOutputPath());
	FileUtils::AppendPath(&rteFile, kDiagLogRTEnvironmentFileName);
#ifdef MACINTOSH
	InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamWrite(rteFile, kOpenOut | kOpenTrunc, 'TEXT', 'CWIE'));
#endif
#ifdef WINDOWS
	InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamWrite(rteFile, kOpenOut | kOpenTrunc));
#endif
    IXMLOutStream * outStream = Utils<IXMLStreamUtils>()->CreateXMLOutPMStream(s, IXMLOutStream::kUTF8);
	outStream->Indent(kTrue);
    outStream->DocHeader(WideString("1.0"), kTrue);
	outStream->Push(WideString("runtimeenvironment"), kTrue);

	// operating system
	outStream->Push(WideString("os"), kTrue);

	PMString temp;
#ifdef MACINTOSH
	temp = "macintosh";
#else
	temp = "windows";		
#endif
	OutputTag(outStream, WideString("platform"), WideString(temp));

	outStream->Pop(kTrue);

	// shuksan info
	outStream->Push(WideString("shuksan"), kTrue);
	PMLocaleId locale(LocaleSetting::GetLocale());
	OutputTag(outStream, WideString("product"), WideString(GetProductFSString(locale)));
	OutputTag(outStream, WideString("featureset"), WideString(GetLanguageFSString(locale)));
	OutputTag(outStream, WideString("ui"), WideString(GetUIString(locale)));

	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	if (theApp)
	{
		OutputTag(outStream, WideString("majorversion"),theApp->GetUIMajorVersion());
		OutputTag(outStream, WideString("minorversion"), theApp->GetUIMinorVersion());
		OutputTag(outStream, WideString("dotversion"), theApp->GetUIDotVersion());
	}

	outStream->IndentLevel(kFalse);
	outStream->Pop(kTrue);

	int32 count = plugInList->GetPluginCount();
	sprintf(buffer, "%d", count);

	attrList.clear();
	aAttr.fName = WideString("count");
	aAttr.fValue = WideString(buffer);
	attrList.push_back(aAttr);
	outStream->PushWithAttributes(WideString("pluginlist"), attrList, kTrue);

	for (int32 i=0; i<count; i++)
	{
		IDFile path;
		int32 majorVersion;
		int32 minorVersion;
		PluginID pluginID = plugInList->GetNthPlugin(i);

		outStream->Push(WideString("plugin"), kTrue);
		outStream->Push(WideString("pluginid"), kTrue);
		OutputTag(outStream, WideString("dec"), (int32)pluginID.Get());
		sprintf(buffer, "0x%x", pluginID.Get());
		OutputTag(outStream, WideString("hex"), WideString(buffer));

		if (iDB)
		{
			char * idName = iDB->FindID(kPlugInIDSpace, pluginID.Get());
			if (idName)
				OutputTag(outStream, WideString("string"), WideString(idName));
		}

		outStream->Pop(kTrue); //pluginid

		if (plugInList->GetVersionNumber(pluginID, majorVersion, minorVersion))
		{
			OutputTag(outStream, WideString("majorversion"), majorVersion);
			OutputTag(outStream, WideString("minorversion"), minorVersion);
		}

		OutputTag(outStream, WideString("loaded"), plugInList->HasBeenLoaded(pluginID));
		OutputTag(outStream, WideString("versionstring"), WideString(*(plugInList->GetAUMVersionString(pluginID))));
		OutputTag(outStream, WideString("matchproduct"), plugInList->MatchCurrentProduct(pluginID));
		OutputTag(outStream, WideString("matchfeatureset"), plugInList->MatchCurrentFeatureSet(pluginID));

		if (plugInList->GetPathName(pluginID, &path))
			OutputTag(outStream, WideString("path"), WideString(FileUtils::SysFileToPMString(path)));

		outStream->Pop(kTrue);
	}

	outStream->IndentLevel(kFalse);
	outStream->Pop(kTrue);
	outStream->IndentLevel(kFalse);
	outStream->Pop(kTrue);
	outStream->Close();
	if (outStream)
		outStream->Release();
}


PMString DiagLogStartupShutdown::GetProductFSString( const PMLocaleId& idLocale )
{
    switch ( idLocale.GetProductFS() )
    {
    case (int16)kInDesignProductFS :        return( "InDesign" ) ;
    case (int16)kInCopyProductFS :            return( "InCopy" ) ;
    case (int16)kInDesignServerProductFS :    return( "InDesign Server" ) ;
    case (int16)kAllProductsFS :            return( "All" ) ;
    default :    ASSERT_FAIL( "Unknown product feature set" ) ; return( "Unknown" ) ;
    }
}

PMString DiagLogStartupShutdown::GetLanguageFSString( const PMLocaleId& idLocale )
{
    switch ( idLocale.GetLanguageFS() )
    {
    case (int16)kRomanLanguageFS :        return( "Roman" ) ;
    case (int16)kJapaneseLanguageFS :    return( "Japanese" ) ;
    case (int16)kRightToLeftLanguageFS :        return( "R2L" ) ;
    case (int16)kINXCoreFS :            return( "INX" ) ;
    case (int16)kAllLanguagesFS :        return( "All" ) ;
    default :    ASSERT_FAIL( "Unknown language feature set" ) ; return( "Unknown" ) ;
    }
}

PMString DiagLogStartupShutdown::GetUIString( const PMLocaleId& idLocale )
{
    PMString strLocale;
    switch (idLocale.GetUserInterfaceId())
    {
        case k_enUS:    strLocale = "English"; break;
        case k_jaJP:    strLocale = "Japanese"; break;

        case k_enGB:    strLocale = "British"; break;
        case k_deDE:    strLocale = "German"; break;
        case k_frFR:    strLocale = "French"; break;
        case k_esES:    strLocale = "Spanish"; break;
        case k_ptBR:    strLocale = "Portuguese"; break;
        case k_svSE:    strLocale = "Swedish"; break;
        case k_daDK:    strLocale = "Danish"; break;
        case k_nlNL:    strLocale = "Dutch"; break;
        case k_itIT:    strLocale = "Italian"; break;
        case k_nbNO:    strLocale = "Norwegian"; break;
        case k_fiFI:    strLocale = "Finnish"; break;
        case k_csCZ:    strLocale = "Czech"; break;
        case k_plPL:    strLocale = "Polish"; break;
        case k_huHU:    strLocale = "Hungarian"; break;
        case k_ruRU:    strLocale = "Russian"; break;
        case k_trTR:    strLocale = "Turkish"; break;
        case k_roRO:    strLocale = "Romanian"; break;
        case k_ukUA:    strLocale = "Ukrainian"; break;
        case k_elGR:    strLocale = "Greek"; break;
        case k_arAE:    strLocale = "Arabic"; break;
        case k_heIL:    strLocale = "Hebrew"; break;

        case k_koKR:    strLocale = "Korean"; break;
        case k_zhCN:    strLocale = "SimpChinese"; break;
        case k_zhTW:    strLocale = "TradChinese"; break;

        default:        strLocale = "Unknown"; break;
    }

    return strLocale;
};

void DiagLogStartupShutdown::OutputTag(IXMLOutStream * out, const WideString & tag, const WideString & content)
{
	out->Push(tag, kTrue);
	out->Write(content);
	out->Pop(kTrue);
}


void DiagLogStartupShutdown::OutputTag(IXMLOutStream * out, const WideString & tag, bool16 boolValue)
{
	out->Push(tag, kTrue);
	if (boolValue)
		out->Write(WideString("true"));
	else
		out->Write(WideString("false"));

	out->Pop(kTrue);
}

void DiagLogStartupShutdown::OutputTag(IXMLOutStream * out, const WideString & tag, int32 intValue)
{
	char buffer[64];
	out->Push(tag, kTrue);
	sprintf(buffer, "%d", intValue);
	out->Write(WideString(buffer));
	out->Pop(kTrue);
}
