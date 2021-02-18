//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/TextDiagLogger.cpp $
//  
//  Owner: gxiao 
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

#include "CDiagnosticLogger.h"

#include "IDiagnosticLog.h"
#include "IDiagLogConfigManager.h"
#include "ISAXAttributes.h"
//#include "ISAXAttributes.h"

#include "FileUtils.h"
#include "FileBytesOutStream.h"
#include "CoreFileUtils.h"
#include <vector>

#include "DiagnosticLogID.h"

class TextDiagnosticLogger : public CDiagnosticLogger
{
public:
	TextDiagnosticLogger(IPMUnknown *boss);
	virtual ~TextDiagnosticLogger();

	// Logging API
	virtual void EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2);
	virtual void ExitContext(const PMString & context);
	virtual void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1 = nil);
	
	// logger
	virtual void InitializeLogger();

	// config
	virtual void LoadLoggerConfig(ISAXAttributes * attrs);
	virtual void GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs);

	// misc
	virtual void HandleAbnormalAppTermination(AppTerminationState state);
	virtual void IdleFlush();
	virtual void Reset();

private:
	void InitLogFile();
	void CloseLogFile();
	PMString MakeOutputFileName(int32 part);

private:
	IDFile fOutputPath;
	PMString fOutputFileName;

	int32 fCurrentFile;
	int32 fOutputFileSize;
	int32 fOutputFileCount;
	int32 fBufferSize;

	// other
	int32 fIndentLevel;
	int32 fOutputBytes;
	bool16 fStreamOpen;
	FileBytesOutStream * fFileStream;
	std::vector<DiagLogStackItem> fStack;
};

CREATE_PMINTERFACE(TextDiagnosticLogger, kTextDiagnosticLoggerImpl)

TextDiagnosticLogger::TextDiagnosticLogger(IPMUnknown *boss) :
	CDiagnosticLogger(boss, "text"),
	fCurrentFile(1),
	fOutputFileSize(2048),
	fOutputFileCount(3),
	fBufferSize(256),
	fOutputBytes(0),
	fIndentLevel(0),
	fStreamOpen(kFalse)
{
}

TextDiagnosticLogger::~TextDiagnosticLogger()
{
	CloseLogFile();
	delete fFileStream;
}


void TextDiagnosticLogger::InitLogFile()
{
	IDFile logFile = fOutputPath;
	FileUtils::AppendPath(&logFile, fOutputFileName);

	fFileStream->Open(logFile);
	fStreamOpen = kTrue;

	PMString text, temp;
	GlobalTime gTime;

	text.SetCString("DiagnosticLog Start : ");
	gTime.CurrentTime();
	gTime.DateToString(temp, kFalse);
	sprintf(fStringBuffer, "date=\"%s\" ", temp.GetPlatformString().c_str());
	text.Append(fStringBuffer);

	gTime.TimeToString(temp);
	sprintf(fStringBuffer, "time=\"%s\"\r\n", temp.GetPlatformString().c_str());
	text.Append(fStringBuffer);

	int32 len = (int32)text.GetPlatformString().size();
	fOutputBytes += len;
	fFileStream->Write((void*)text.GetPlatformString().c_str(), len);
	fIndentLevel++;
}

void TextDiagnosticLogger::CloseLogFile()
{
	if (fStreamOpen)
	{
		PMString text, temp;
		GlobalTime gTime;

		text.SetCString("DiagnosticLog End : ");
		gTime.CurrentTime();
		gTime.DateToString(temp, kFalse);
		sprintf(fStringBuffer, "date=\"%s\" ", temp.GetPlatformString().c_str());
		text.Append(fStringBuffer);

		gTime.TimeToString(temp);
		sprintf(fStringBuffer, "time=\"%s\"\r\n", temp.GetPlatformString().c_str());
		text.Append(fStringBuffer);

		int32 len = (int32)text.GetPlatformString().size();
		fFileStream->Write((void*)text.GetPlatformString().c_str(), len);
		fFileStream->Close();
		fStreamOpen = kFalse;

		fOutputBytes = 0;
		fIndentLevel = 0;
	}
}

PMString TextDiagnosticLogger::MakeOutputFileName(int32 part)
{
	PMString temp;
	sprintf(fStringBuffer, "_%d", part);
	temp.SetCString(fStringBuffer);
	temp.Append(".txt");

	PMString fileName;
	fileName.SetCString(kDiagLogOutputFileName);
	fileName.Append(temp);

	return fileName;
}


void TextDiagnosticLogger::EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2)
{
	DiagLogStackItem item(context, clock());
	fStack.push_back(item);

	PMString line;
	for (int32 i = 0; i < fIndentLevel; i++)
		line.Append(" ");

	line += context;
	line += "  ";

	for (int32 i=0; i<attrs.size(); i++)
	{
	    IXMLOutStream::Attribute aAttr = attrs[i];
		PMString name(aAttr.GetName());
		PMString value(aAttr.GetValue());

		sprintf(fStringBuffer, "%s=\"%s\"  ", name.GetPlatformString().c_str(), value.GetPlatformString().c_str());
		line.Append(fStringBuffer);
	}
	line.Append("\r\n");

	int32 len = (int32)line.GetPlatformString().size();
	fOutputBytes += len;
	fFileStream->Write((void*)line.GetPlatformString().c_str(), len);
	fIndentLevel++;
}

void TextDiagnosticLogger::ExitContext(const PMString & context)
{
	fIndentLevel--;

	int32 end = clock();
	if(fStack.size()==0)
			return;
	DiagLogStackItem item = fStack.back();
	fStack.pop_back();
	ASSERT(context == item.fContext);

	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
	if (iConfigManager->GetLoggingTimeInfo())
	{
		if (end-item.fTimeStamp > iConfigManager->GetLoggingTimeThreshold())
		{
			IXMLOutStream::AttributeList attrs;
			IXMLOutStream::Attribute attr;

			attr.fName = WideString("start");
			attr.fValue = WideString(PrintToString("%d", item.fTimeStamp));
			attrs.push_back(attr);

			attr.fName = WideString("end");
			attr.fValue = WideString(PrintToString("%d", end));
			attrs.push_back(attr);

			attr.fName = WideString("elaps");
			attr.fValue = WideString(PrintToString("%d", end-item.fTimeStamp));
			attrs.push_back(attr);

			this->LogMessage("Timing", attrs);
		}
	}

	if ( (fOutputFileCount>1) && (fStack.size()==0) && (fOutputBytes>fOutputFileSize*1024) )
	{
		CloseLogFile();
		if (fCurrentFile < fOutputFileCount)
		{
			fCurrentFile++;
			fOutputFileName = MakeOutputFileName(fCurrentFile);
		}
		else //rotate file
		{
			//delete first file
			PMString firstFile = MakeOutputFileName(1);
			IDFile logFile1 = fOutputPath;
			FileUtils::AppendPath(&logFile1, firstFile);
			logFile1.Delete();

			for (int i=2; i<=fOutputFileCount; i++)
			{
				PMString oldFileName = MakeOutputFileName(i);
				IDFile logFile = fOutputPath;
				FileUtils::AppendPath(&logFile, oldFileName);
				CoreFileUtils::RenameFile(logFile, MakeOutputFileName(i-1).GetPlatformString().c_str());
			}
		}

		InitLogFile();
	}
}


void TextDiagnosticLogger::LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1)
{
	PMString line;
	for (int32 i = 0; i < fIndentLevel; i++)
		line.Append(" ");

	sprintf(fStringBuffer, "%s=\"%s\"  ", "MessageType", messageType.GetPlatformString().c_str());
	line.Append(fStringBuffer);

	for (int32 i=0; i<attrs.size(); i++)
	{
	    IXMLOutStream::Attribute aAttr = attrs[i];
		PMString name(aAttr.GetName());
		PMString value(aAttr.GetValue());

		sprintf(fStringBuffer, "%s=\"%s\"  ", name.GetPlatformString().c_str(), value.GetPlatformString().c_str());
		line.Append(fStringBuffer);
	}
	line.Append("\r\n");

	int32 len = (int32)line.GetPlatformString().size();
	fOutputBytes += len;
	fFileStream->Write((void*)line.GetPlatformString().c_str(), len);
}


void TextDiagnosticLogger::LoadLoggerConfig(ISAXAttributes * attrs)
{
	// read configuration
	PMString attrName, value;
	WideString attrNameW, valueW;
	for (int32 i = 0; i < attrs->GetLength(); i++)
	{
		attrs->GetQName(i, attrNameW);
		attrNameW.GetSystemString(&attrName);

		if (attrName == "enabled")
		{
			attrs->GetValue(i, valueW);
			valueW.GetSystemString(&value);

			if (value == "true")
				Enable(kTrue);
			else if (value == "false")
				Enable(kFalse);

			attrs->AttributeHandled(i);
		}
		else if (attrName == "outputfilesize" || attrName == "outputfilecount" || attrName == "outputfilebuffersize")
		{
			attrs->GetValue(i, valueW);
			valueW.GetSystemString(&value);

			PMString::ConversionError	err;
			int32 number = value.GetAsNumber(&err);
			if (err == PMString::kNoError)
			{
				if (attrName == "outputfilesize")
					fOutputFileSize = number;
				else if (attrName == "outputfilecount")
					fOutputFileCount = number;
				else 
					fBufferSize = number;
			}

			attrs->AttributeHandled(i);
		}
	}
}

void TextDiagnosticLogger::GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs)
{
	CDiagnosticLogger::GenerateLoggerConfig(attrs);

    IXMLOutStream::Attribute aAttr;
	PrintToString("%d", fOutputFileSize);
	aAttr.fName = WideString("outputfilesize");
	aAttr.fValue = WideString(fStringBuffer);
	attrs.push_back(aAttr);

	PrintToString("%d", fOutputFileCount);
	aAttr.fName = WideString("outputfilecount");
	aAttr.fValue = WideString(fStringBuffer);
	attrs.push_back(aAttr);

	PrintToString("%d", fBufferSize);
	aAttr.fName = WideString("outputfilebuffersize");
	aAttr.fValue = WideString(fStringBuffer);
	attrs.push_back(aAttr);
}


void TextDiagnosticLogger::InitializeLogger()
{
	fCurrentFile = 1;
	fOutputFileName = MakeOutputFileName(fCurrentFile);
	fFileStream = new FileBytesOutStream(fBufferSize*1024);

	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
	fOutputPath = iConfigManager->GetOutputPath();

	InitLogFile();
}


void TextDiagnosticLogger::Reset()
{
	;
}


void TextDiagnosticLogger::HandleAbnormalAppTermination(AppTerminationState state)
{
#ifdef WINDOWS
	OutputDebugStringA("TEXT Logger : HandleAbnormalAppTermination\n");
#endif

	if (fStreamOpen)
	{
		PMString temp;
		if (state == kUnhandledException)
			temp.SetCString("kUnhandledException"); 
		else 
			temp.SetCString("kProtectiveShutdown"); 

		sprintf(fStringBuffer, "%s=\"%s\"  ", "MessageType", temp.GetPlatformString().c_str());
		fFileStream->Write(fStringBuffer, static_cast<int32>(strlen(fStringBuffer)));
		CloseLogFile();
	}
}


void TextDiagnosticLogger::IdleFlush()
{
	if (fStreamOpen)
		fFileStream->Flush();
}
