//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogConfigManager.cpp $
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

#include "IDiagLogConfigManager.h"

#include "IDiagnosticLog.h"
#include "IXMLOutStream.h" 
#include "ISaxContentHandler.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ISAXParserOptions.h"
#include "ISAXServices.h"
#include "IXMLStreamUtils.h"
#include "IDiagLoggerManager.h"
#include "IDiagnosticLogger.h"

//#include "FileUtility.h"
#include "FileUtils.h"
//#include "Utils.h"
#include "StreamUtil.h"
#include "ErrorUtils.h"

#include "DiagnosticLogID.h"


class DiagLogConfigManager: public CPMUnknown<IDiagLogConfigManager>
{
public:
	DiagLogConfigManager(IPMUnknown *boss);
	~DiagLogConfigManager();

	// load and save config to xml file
	virtual bool16 Load();
	virtual void Save();

	// file location
	virtual IDFile GetConfigFilePath();

	virtual IDFile GetOutputPath();
	virtual void SetOutputPath(const PMString & path);

	// ID database
	virtual PMString GetIDDatabaseName();
	virtual void SetIDDatabaseName(const PMString & name);

	virtual bool16 GetLoadIDDatabase();
	virtual void SetLoadIDDatabase(bool16 load);

	// master switch for logging
	virtual bool16 GetLogging();
	virtual void SetLogging(bool16 log);

	virtual DiagLoggingLevel GetLoggingLevel() const;
	virtual void SetLoggingLevel(DiagLoggingLevel level);

	virtual bool16 GetLoggingTimeInfo();
	virtual void SetLoggingTimeInfo(bool16 timing);

	virtual int32 GetLoggingTimeThreshold() const;
	virtual void SetLoggingTimeThreshold(int32 threshold);

	// switch for category
	virtual bool16 GetCategoryLogging(DiagLogCategory category);
	virtual void SetCategoryLogging(DiagLogCategory category, bool16 log);

	virtual bool16 GetCategoryLogID(DiagLogCategory category, int32 id);

	virtual void AddCategoryList(DiagLogCategory category, ListType lType, int32 id);
	virtual void RemoveCategoryList(DiagLogCategory category, ListType lType, int32 id);

	// individual event
	virtual void SetLogEvent(IEvent::EventType eventType, bool16 bLog);	
	virtual void SetLogEvent(PMString eventName, bool16 bLog);
	virtual bool16 GetLogEvent(IEvent::EventType eventType);

	// utility
	virtual PMString GetEventName(IEvent::EventType eventType);

private:
	PMString GetDiagLogCategoryName(DiagLogCategory cate);
	PMString GetDiagLoggingLevelName(DiagLoggingLevel level);

	void SetDefaultConfigFilePath();
	void SetDefaultOutputPath();
	void BoolAttribute(IXMLOutStream::AttributeList &outList, PMString name, bool16 value, bool16 clearList = kFalse);
	void StringAttribute(IXMLOutStream::AttributeList &outList, PMString name, PMString value, bool16 clearList = kFalse);
	bool16 IsContext(DiagLogCategory cate);
	bool16 HasList(DiagLogCategory cate);

private:
	// load and save config to xml file
	IDFile fConfigFile;

	// file location
	IDFile fConfigFilePath;
	IDFile fOutputPath;

	// ID database
	PMString fIDDatabaseName;
	bool16 fLoadIDDatabase;

	// master switch for logging
	bool16 fLogging;
	DiagLoggingLevel fLoggingLevel;
	bool16 fLoggingTimeInfo;
	int32 fTimeThreshold;

	// switch for category
	bool16 fCategoryLogging[kDiagLogLastCategory];
	K2Vector<int32> * fIncludList[kDiagLogLastCategory];
	K2Vector<int32> * fExcludList[kDiagLogLastCategory];

	// individual event
	bool16 fEventLogOption[IEvent::kEndOfEventTypes];
};

CREATE_PMINTERFACE(DiagLogConfigManager, kDiagLogConfigManagerImpl)

DiagLogConfigManager::DiagLogConfigManager(IPMUnknown *boss) : 
	CPMUnknown<IDiagLogConfigManager>(boss),
	fIDDatabaseName("DiagnosticLogIDDB.xml")
{
	fLoadIDDatabase = kFalse;
	SetDefaultConfigFilePath();
	SetDefaultOutputPath();

	fLogging = kTrue;
	fLoggingLevel = kDiagLogMinimum;
	fLoggingTimeInfo = kFalse;
	fTimeThreshold = 10;

	for (int32 i=kDiagLogAction; i<kDiagLogLastCategory; i++)
	{
		DiagLogCategory cate = (DiagLogCategory)i;

		if (cate == kDiagLogAction)
			fCategoryLogging[i] = kTrue;
		else
			fCategoryLogging[i] = kFalse;

		if (HasList(cate))
		{
			fIncludList[i] = new K2Vector<int32>;
			fExcludList[i] = new K2Vector<int32>;
		}
		else
		{
			fIncludList[i] = nil;
			fExcludList[i] = nil;
		}
	}

	K2Vector<int32> * list = fExcludList[kDiagLogIdleTask];
	list->push_back(kDiagnosticLogIdleTaskBoss);

	for (int32 i=IEvent::kFirstEventType; i<IEvent::kEndOfEventTypes; i++)
		fEventLogOption[i] = kFalse;
}

DiagLogConfigManager::~DiagLogConfigManager()
{
	for (int32 i=kDiagLogAction; i<kDiagLogLastCategory; i++)
	{
		delete fIncludList[i];
		delete fExcludList[i];
	}
}


// load and save config to xml file
bool16 DiagLogConfigManager::Load()
{
	bool16 result = kTrue;

	PMString fileName(kDiagLogConfigFileName);
#ifdef DEBUG
	fileName.Append("_debug.xml");
#else
	fileName.Append("_release.xml");
#endif

	IDFile configFile(fConfigFilePath);
	FileUtils::AppendPath(&configFile, fileName);
	fConfigFile = configFile;

	if (configFile.Exists())
	{
 		InterfacePtr<IPMStream> fileStream((IPMStream*)StreamUtil::CreateFileStreamRead(fConfigFile, kOpenIn, 'TEXT', 'CWIE'));

		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		InterfacePtr<IK2ServiceProvider> xmlProvider(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, kXMLParserServiceBoss));

		InterfacePtr<ISAXContentHandler> handler(this, IID_ISAXCONTENTHANDLER);

		InterfacePtr<ISAXServices> saxServices(xmlProvider, UseDefaultIID());

		InterfacePtr<ISAXParserOptions> parserOptions(saxServices, UseDefaultIID());
		parserOptions->SetShowWarningAlert(kFalse);
		
		if (saxServices->ParseStream(fileStream, handler))
		{
			if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
			{
				result = kFalse;
				ASSERT_FAIL(FORMAT_ARGS("Error parsing the 'Debug Settings.xml': %s", ErrorUtils::PMGetGlobalErrorString().GetUTF8String().c_str()));
			}

			// -- As far we we are concerned the errors been handled. Don't propgate the error any further.
			// -- At this early stage leaving the global error set will cause problems with other service providers.
			// hkhalfal: (NACSR) No abortable command sequence used
			// error will not cause prior changes to get rolled back
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);
		}
	}

	return result;
}


void DiagLogConfigManager::Save()
{
	IXMLOutStream::AttributeList attrList;
    IXMLOutStream::Attribute aAttr;
	char stringBuffer[16];

#ifdef MACINTOSH
	InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamWrite(fConfigFile, kOpenOut | kOpenTrunc, 'TEXT', 'CWIE'));
#endif
#ifdef WINDOWS
	InterfacePtr<IPMStream> s(StreamUtil::CreateFileStreamWrite(fConfigFile, kOpenOut | kOpenTrunc));
#endif
    IXMLOutStream * configStream = Utils<IXMLStreamUtils>()->CreateXMLOutPMStream(s, IXMLOutStream::kUTF8);
	configStream->Indent(kTrue);
    configStream->DocHeader(WideString("1.0"), kTrue);
	configStream->Push(WideString("DiagnosticLogConfiguration"), kTrue);

	// file location
	configStream->IndentLevel(kTrue);
	//StringAttribute(attrList,"configfilepath", FileUtils::SysFileToPMString(fConfigFilePath));
	
	AString aString = fOutputPath.GetPath(false); // AFile.h
    PMString outputFilePath(aString.GrabWString(), aString.UTF16Count());

	StringAttribute(attrList,"outputpath", outputFilePath);
	configStream->PushWithAttributes(WideString("filelocation"), attrList);
	configStream->Pop(kTrue);
	{
		PMString temp("  Configuration (this) file location : \"");
		aString = fConfigFilePath.GetPath(false); // AFile.h
		temp.Append(PMString(aString.GrabWString(), aString.UTF16Count()));
		temp.Append("\"  ");
		configStream->Comment(WideString(temp), kTrue);
	}

	// iddatabase
	StringAttribute(attrList,"name", fIDDatabaseName, kTrue);
	BoolAttribute(attrList,"load", fLoadIDDatabase);
	configStream->PushWithAttributes(WideString("iddatabase"), attrList);
	configStream->Pop(kTrue);

	// logging
	BoolAttribute(attrList,"enabled", fLogging, kTrue);
	//sprintf(stringBuffer, "%d", );
	StringAttribute(attrList,"level", GetDiagLoggingLevelName(fLoggingLevel));
	BoolAttribute(attrList,"timeinfo", fLoggingTimeInfo);
	sprintf(stringBuffer, "%d", fTimeThreshold);
	StringAttribute(attrList,"timethreshold", stringBuffer);
	configStream->PushWithAttributes(WideString("logging"), attrList, kTrue);

	for (int32 i=kDiagLogAction; i<kDiagLogLastCategory; i++)
	{
		DiagLogCategory cate = (DiagLogCategory)i;

		StringAttribute(attrList,"name", GetDiagLogCategoryName(cate), kTrue);
		BoolAttribute(attrList,"enabled", fCategoryLogging[i]);
		configStream->IndentLevel(kTrue);
		configStream->PushWithAttributes(WideString("category"), attrList, kTrue);

		if (cate == kDiagLogEvents)
		{
			configStream->IndentLevel(kTrue);
			for (int32 j=IEvent::kFirstEventType; j<IEvent::kEndOfEventTypes; j++)
			{
				StringAttribute(attrList,"name", GetEventName((IEvent::EventType)j), kTrue);
				BoolAttribute(attrList,"enabled", GetLogEvent((IEvent::EventType)j));

				configStream->PushWithAttributes(WideString("eventtype"), attrList);
				configStream->Pop(kTrue);
			}
			configStream->IndentLevel(kFalse);
		}
		else
		{
			if (fIncludList[i] != nil)
			{
				ASSERT(fExcludList[i] != nil);
				for (int j=0; j<2; j++)
				{
					PMString listName;
					K2Vector<int32> * list;
					if (j==0)
					{
						listName.SetCString("includelist");
						list = fIncludList[i];
					}
					else
					{
						listName.SetCString("excludelist");
						list = fExcludList[i];
					}

					configStream->IndentLevel(kTrue);
					configStream->Push(WideString(listName), kTrue);
					for(K2Vector<int32>::const_iterator iter = list->begin(); iter != list->end(); ++iter)
					{
						sprintf(stringBuffer, "0x%x", *iter);
						StringAttribute(attrList,"value", stringBuffer, kTrue);

						configStream->IndentLevel(kTrue);
						configStream->PushWithAttributes(WideString("id"), attrList);
						configStream->Pop(kTrue);
						configStream->IndentLevel(kFalse);
					}
					configStream->Pop(kTrue);
					configStream->IndentLevel(kFalse);
				}
			}

		}

		configStream->Pop(kTrue);
		configStream->IndentLevel(kFalse);
	}

	configStream->Pop(kTrue); //logging

	// loggers
	configStream->Push(WideString("loggers"), kTrue);
	{
		PMString temp("  filesize and buffersize is in kilo bytes (KB) ");
		configStream->Comment(WideString(temp), kTrue);
	}

	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLoggerManager> iLoggerManager(iDiagnosticLog->QueryDiagLoggerManager());
	for (int32 i=0; i<iLoggerManager->GetNumLoggers(); i++)
	{
		attrList.clear();
		IDiagnosticLogger * logger = iLoggerManager->GetNthLogger(i);
		logger->GenerateLoggerConfig(attrList);

		configStream->IndentLevel(kTrue);
		configStream->PushWithAttributes(WideString("logger"), attrList, kTrue);
		configStream->Pop(kTrue);
		configStream->IndentLevel(kFalse);
	}
	configStream->Pop(kTrue);

	configStream->IndentLevel(kFalse);
	configStream->Pop(kTrue);
	configStream->Close();
	if (configStream)
		configStream->Release();
}


	// file location
IDFile DiagLogConfigManager::GetConfigFilePath()
{
	return fConfigFilePath;
}

IDFile DiagLogConfigManager::GetOutputPath()
{
	return fOutputPath;
}

void DiagLogConfigManager::SetOutputPath(const PMString & path)
{
	if (path.IsEmpty())
		return;

	fOutputPath.SetPath(AString(path.GrabUTF16Buffer(nil)));

	if (!fOutputPath.Exists())
		fOutputPath.MakeDirectory();
}

	
// ID database
PMString DiagLogConfigManager::GetIDDatabaseName()
{	
	return fIDDatabaseName;
}


void DiagLogConfigManager::SetIDDatabaseName(const PMString & name)
{	
	fIDDatabaseName = name;
}


bool16 DiagLogConfigManager::GetLoadIDDatabase()
{
	return fLoadIDDatabase;
}


void DiagLogConfigManager::SetLoadIDDatabase(bool16 load)
{
	fLoadIDDatabase = load;
}


// master switch for logging
bool16 DiagLogConfigManager::GetLogging()
{
	return fLogging;
}


void DiagLogConfigManager::SetLogging(bool16 log)
{
	fLogging = log;
}


DiagLogConfigManager::DiagLoggingLevel DiagLogConfigManager::GetLoggingLevel() const
{
	return fLoggingLevel;
}

void DiagLogConfigManager::SetLoggingLevel(DiagLoggingLevel level)
{
	fLoggingLevel = level;
}

bool16 DiagLogConfigManager::GetLoggingTimeInfo()
{
	return fLoggingTimeInfo;
}

void DiagLogConfigManager::SetLoggingTimeInfo(bool16 timing)
{
	fLoggingTimeInfo = timing;
}

int32 DiagLogConfigManager::GetLoggingTimeThreshold() const
{
	return fTimeThreshold;
}

void DiagLogConfigManager::SetLoggingTimeThreshold(int32 threshold)
{
	fTimeThreshold = threshold;
}

// switch for category
bool16 DiagLogConfigManager::GetCategoryLogging(DiagLogCategory category)
{
	if (fLogging)
		return fCategoryLogging[category];
	
	return fLogging;
}

void DiagLogConfigManager::SetCategoryLogging(DiagLogCategory category, bool16 log)
{
	fCategoryLogging[category] = log;
}

bool16 DiagLogConfigManager::GetCategoryLogID(DiagLogCategory category, int32 id)
{
	if (fLogging)
	{
		bool16 log = fCategoryLogging[category];
		if (log && id) // check if we should log this id
		{
			K2Vector<int32> * list = fIncludList[category];
			if (list && !list->empty())
			{
				for(K2Vector<int32>::const_iterator iter = list->begin(); iter != list->end(); ++iter)
				{
					if (id == *iter)
						return kTrue;
				}

				return kFalse;
			}
			else
			{
				list = fExcludList[category];
				if (list && !list->empty())
				{
					for(K2Vector<int32>::const_iterator iter = list->begin(); iter != list->end(); ++iter)
					{
						if (id == *iter)
							return kFalse;
					}

					return kTrue;
				}
			}
		}

		return log;
	}

	return fLogging;
}


void DiagLogConfigManager::AddCategoryList(DiagLogCategory category, ListType lType, int32 id)
{
	K2Vector<int32> * list;
	if (lType == kIncludeList)
		list = fIncludList[category];
	else if (lType == kExcludeList)
		list = fExcludList[category];
	else 
		return;

	for(K2Vector<int32>::const_iterator iter = list->begin(); iter != list->end(); ++iter)
	{
		if (id == *iter)
			return;
	}

	list->push_back(id);
}

void DiagLogConfigManager::RemoveCategoryList(DiagLogCategory category, ListType lType, int32 id)
{
	K2Vector<int32> * list;
	if (lType == kIncludeList)
		list = fIncludList[category];
	else if (lType == kExcludeList)
		list = fExcludList[category];
	else 
		return;

	for(K2Vector<int32>::iterator iter = list->begin(); iter != list->end(); ++iter)
		if (id == *iter)
			list->erase(iter);
}


// individual event
void DiagLogConfigManager::SetLogEvent(IEvent::EventType eType, bool16 bLog)
{
	if (fEventLogOption[eType] != bLog)
		fEventLogOption[eType] = bLog;
}


void DiagLogConfigManager::SetLogEvent(PMString eventName, bool16 bLog)
{
	int32 i;

	for (i=IEvent::kFirstEventType; i<IEvent::kEndOfEventTypes; i++)
	{
		if (GetEventName((IEvent::EventType)i) == eventName)
			break;
	}

	if (i < IEvent::kEndOfEventTypes)
		SetLogEvent((IEvent::EventType)i, bLog);
}


bool16 DiagLogConfigManager::GetLogEvent(IEvent::EventType eType)
{
	return fEventLogOption[eType];
}


// utility
PMString DiagLogConfigManager::GetEventName(IEvent::EventType eType)
{
	switch(eType)
	{
		case IEvent::kNull:
			return "kNull";	
		case IEvent::kActivate:		
			return "kActivate";
		case IEvent::kDeactivate:
			return "kDeactivate";	
		case IEvent::kSuspend:
			return "kSuspend";
		case IEvent::kResume:
			return "kResume";			
		case IEvent::kMouseMove:
			return "kMouseMove";	
		case IEvent::kMouseDrag:
			return "kMouseDrag";		
		case IEvent::kLButtonDn:
			return "kLButtonDn";		
		case IEvent::kRButtonDn:
			return "kRButtonDn";	
		case IEvent::kMButtonDn:
			return "kMButtonDn";			
		case IEvent::kLButtonUp:
			return "kLButtonUp";	
		case IEvent::kRButtonUp:
			return "kRButtonUp";			
		case IEvent::kMButtonUp:
			return "kMButtonUp";		
		case IEvent::kDoubleClick:
			return "kDoubleClick";	
		case IEvent::kTripleClick:
			return "kTripleClick";		
		case IEvent::kQuadrupleClick:
			return "kQuadrupleClick";	
		case IEvent::kQuintupleClick:
			return "kQuintupleClick";
		case IEvent::kMouseWheel:
			return "kMouseWheel";
		case IEvent::kControlCmd:
			return "kControlCmd";		
		case IEvent::kKeyDown:
			return "kKeyDown";		
		case IEvent::kKey:
			return "kKey";	
		case IEvent::kKeyUp:
			return "kKeyUp";	
		case IEvent::kInvalid:
			return "kInvalid";			
		case IEvent::kMouseExit:
			return "kMouseExit";
		case IEvent::kTabletEvent:
			return "kTabletEvent";		
		case IEvent::kGestureEvent:
			return "kGestureEvent";		
		case IEvent::kEndOfEventTypes:
			return "";
		
	}
	return "";
}


// private utility function
PMString DiagLogConfigManager::GetDiagLogCategoryName(DiagLogCategory cate)
{
	static char *kCategoryString[] =
	{
		"kDiagLogAction",
		"kDiagLogCommand",
		"kDiagLogIdleTask",
		"kDiagLogObserver",
		"kDiagLogResponder",
		"kDiagLogEvents",
		"kDiagLogTracking",
		"kDiagLogTransaction",
		"kDiagLogMemoryPurge",
		"kDiagLogGlobalErrorState",
		"kDiagLogTextDamageMark"
	};

	PMString category(kCategoryString[cate]);
	return category;
}

PMString DiagLogConfigManager::GetDiagLoggingLevelName(DiagLoggingLevel level)
{
	PMString name;
	switch(level)
	{
	case kDiagLogMinimum: name.SetCString("kDiagLogMinimum");
		break;

	case kDiagLogMedium: name.SetCString("kDiagLogMedium");
		break;

	case kDiagLogMaximum: name.SetCString("kDiagLogMaximum");
		break;
	}

	return name;
}


void DiagLogConfigManager::SetDefaultConfigFilePath()
{
	FileUtils::GetAppLocalCachedDataFolder(&fConfigFilePath, "DiagLog");

	if (!fConfigFilePath.Exists())
		fConfigFilePath.MakeDirectory();
}

void DiagLogConfigManager::SetDefaultOutputPath()
{
	FileUtils::GetAppLocalCachedDataFolder(&fOutputPath, "DiagLog");

	if (!fOutputPath.Exists())
		fOutputPath.MakeDirectory();
}


bool16 DiagLogConfigManager::IsContext(DiagLogCategory cate)
{
	if (cate ==	kDiagLogAction ||
		cate ==	kDiagLogCommand ||
		cate ==	kDiagLogIdleTask ||
		cate ==	kDiagLogObserver ||
		cate ==	kDiagLogEvents ||
		cate ==	kDiagLogResponder)
		return kTrue;
	
	return kFalse;
}

bool16 DiagLogConfigManager::HasList(DiagLogCategory cate)
{
	if (cate ==	kDiagLogAction ||
		cate ==	kDiagLogCommand ||
		cate ==	kDiagLogIdleTask ||
		cate ==	kDiagLogObserver ||
		cate ==	kDiagLogResponder ||
		cate ==	kDiagLogTracking)
		return kTrue;
	
	return kFalse;
}


void DiagLogConfigManager::BoolAttribute(IXMLOutStream::AttributeList &outList, PMString name, bool16 value, bool16 clearList)
{
    IXMLOutStream::Attribute aAttr;

	if (clearList)
		outList.clear();

	PMString temp = value ? "true" : "false";
	aAttr.fName = WideString(name);
	aAttr.fValue = WideString(temp);
	outList.push_back(aAttr);
}


void DiagLogConfigManager::StringAttribute(IXMLOutStream::AttributeList &outList, PMString name, PMString value, bool16 clearList)
{
    IXMLOutStream::Attribute aAttr;

	if (clearList)
		outList.clear();

	aAttr.fName = WideString(name);
	aAttr.fValue = WideString(value);
	outList.push_back(aAttr);
}
