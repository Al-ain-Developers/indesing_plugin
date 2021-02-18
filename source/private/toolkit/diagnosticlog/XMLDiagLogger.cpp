//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/XMLDiagLogger.cpp $
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

#include "ISAXAttributes.h"
//#include "IXMLStreamUtils.h"
#include "IDiagnosticLog.h"
#include "IDiagLogConfigManager.h"

#include "FileUtils.h"
#include "CoreFileUtils.h"
#include "FileBytesOutStream.h"
#include "Utils.h"
#include "GlobalTime.h"
#include <vector>

#include "DiagnosticLogID.h"

class XMLDiagnosticLogger :	public CDiagnosticLogger
{
public:
	XMLDiagnosticLogger(IPMUnknown *boss);
	virtual	~XMLDiagnosticLogger();

	// Logging API
	virtual	void EnterContext(const	PMString & context,	IXMLOutStream::AttributeList& attrs, const void	* Param1, const	void * Param2);
	virtual	void ExitContext(const PMString	& context);
	virtual	void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList&	attrs, const void *	Param1 = nil);

	// logger
	virtual	void InitializeLogger();

	// config
	virtual	void LoadLoggerConfig(ISAXAttributes * attrs);
	virtual	void GenerateLoggerConfig(IXMLOutStream::AttributeList&	attrs);

	// misc
	virtual	void HandleAbnormalAppTermination(AppTerminationState state);
	virtual	void IdleFlush();
	virtual	void Reset();

private:
	void InitLogFile();
	void CloseLogFile();
	PMString MakeOutputFileName(int32 part);

	void PushWithAttributes(const PMString & tag, IXMLOutStream::AttributeList&	attrs);
	void Pop(const PMString	& tag);

private:
	IDFile fOutputPath;
	PMString fOutputFileName;

	int32 fOutputFileSize;
	int32 fOutputFileCount;
	int32 fBufferSize;

	int32 fCurrentTime;
	int32 fCurrentFile;

	int32 fIndentLevel;
	int32 fOutputBytes;
	bool16 fStreamOpen;
	FileBytesOutStream * fFileStream;
	std::vector<DiagLogStackItem> fStack;
};

CREATE_PMINTERFACE(XMLDiagnosticLogger,	kXMLDiagnosticLoggerImpl)

XMLDiagnosticLogger::XMLDiagnosticLogger(IPMUnknown	*boss) : 
	CDiagnosticLogger(boss,	"xml"),
	fFileStream(nil),
	fCurrentFile(1),
	fOutputFileSize(2048),
	fOutputFileCount(3),
	fBufferSize(256),
	fIndentLevel(0),
	fOutputBytes(0),
	fStreamOpen(kFalse)
{
}

XMLDiagnosticLogger::~XMLDiagnosticLogger()
{
	CloseLogFile();
	delete fFileStream;
}

void XMLDiagnosticLogger::InitLogFile()
{
	IDFile logFile = fOutputPath;
	FileUtils::AppendPath(&logFile, fOutputFileName);

	fFileStream->Open(logFile);
	fStreamOpen = kTrue;

	IXMLOutStream::AttributeList attrs;
	IXMLOutStream::Attribute attr;
	PMString temp;
	GlobalTime gTime;

	gTime.CurrentTime();
	gTime.DateToString(temp, kFalse);
	attr.fName = WideString("date");
	attr.fValue = WideString(temp);
	attrs.push_back(attr);

	gTime.TimeToString(temp);
	attr.fName = WideString("time");
	attr.fValue = WideString(temp);
	attrs.push_back(attr);

	std::string text = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";	
	int32 len = (int32)text.size();
	fOutputBytes += len;
	fFileStream->Write((void*)text.c_str(), len);

	PushWithAttributes("Diagnosticlog", attrs);
	fIndentLevel++;
}

void XMLDiagnosticLogger::CloseLogFile()
{
	if (fStreamOpen)
	{
		Pop("Diagnosticlog");
		fFileStream->Close();
		fStreamOpen = kFalse;

		fOutputBytes = 0;
		fIndentLevel = 0;
	}
}

PMString XMLDiagnosticLogger::MakeOutputFileName(int32 part)
{
	PMString temp;
	temp.SetCString(PrintToString("_%d", part));
	temp.Append(".xml");

	PMString fileName;
	fileName.SetCString(kDiagLogOutputFileName);
	fileName.Append(temp);

	return fileName;
}


void XMLDiagnosticLogger::PushWithAttributes(const PMString	& tag, IXMLOutStream::AttributeList& attrs)
{
	PMString text;
	for (int32 i = 0; i < fIndentLevel; i++)
		text.Append(" ");

	// open tag
	int32 size = attrs.size();
	if (size > 0)
		sprintf(fStringBuffer, "<%s ", tag.GetPlatformString().c_str());
	else
		sprintf(fStringBuffer, "<%s>", tag.GetPlatformString().c_str());
	text.Append(fStringBuffer);

	for (int32 i=0; i<size; i++)
	{
	    IXMLOutStream::Attribute aAttr = attrs[i];
		PMString name(aAttr.GetName());
		PMString value(aAttr.GetValue());

		if (i < size-1) 
			sprintf(fStringBuffer, "%s=\"%s\"  ", name.GetPlatformString().c_str(), value.GetPlatformString().c_str());
		else
			sprintf(fStringBuffer, "%s=\"%s\">", name.GetPlatformString().c_str(), value.GetPlatformString().c_str());

		text.Append(fStringBuffer);
	}
	text.Append("\r\n");

	int32 len = (int32)text.GetPlatformString().size();
	fOutputBytes += len;
	fFileStream->Write((void*)text.GetPlatformString().c_str(), len);
}


void XMLDiagnosticLogger::Pop(const	PMString & tag)
{
	PMString text;
	for (int32 i = 0; i < fIndentLevel; i++)
		text.Append(" ");

	// close tag
	sprintf(fStringBuffer, "</%s>", tag.GetPlatformString().c_str());
	text.Append(fStringBuffer);
	text.Append("\r\n");

	int32 len = (int32)text.GetPlatformString().size();
	fOutputBytes += len;
	fFileStream->Write((void*)text.GetPlatformString().c_str(), len);
}


void XMLDiagnosticLogger::EnterContext(const PMString &	context, IXMLOutStream::AttributeList& attrs, const	void * Param1, const void *	Param2)
{
	DiagLogStackItem item(context, clock());
	fStack.push_back(item);

	PushWithAttributes(context,	attrs);

	fIndentLevel++;
}


void XMLDiagnosticLogger::ExitContext(const PMString & context)
{
#if 0 //def DEBUG
	std::vector<DiagLogStackItem>::iterator iter = fStack.begin();
	while (iter != fStack.end())
	{
		TRACE("stack item = %s\n", (*iter).fContext.GetPlatformString().c_str());
		iter++;
	}
	TRACE("\n\n");
#endif

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

			this->LogMessage("timing", attrs);
		}
	}

	fIndentLevel--;
	Pop(context);

	if ( (fOutputFileCount>1) && (fOutputBytes>fOutputFileSize*1024) && (fStack.size()==0) )
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
		fCurrentTime = end;
	}
}


void XMLDiagnosticLogger::LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1)
{
	IXMLOutStream::Attribute attr;

	attr.fName = WideString("type");
	attr.fValue = WideString(messageType);

	K2Vector<IXMLOutStream::Attribute>::iterator iter = attrs.begin();
	attrs.insert(iter, attr);

	PushWithAttributes("Message", attrs);
	Pop("Message");
}


void XMLDiagnosticLogger::LoadLoggerConfig(ISAXAttributes *	attrs)
{
	// read	configuration
	WideString attrNameW, valueW;
	PMString attrName, value;
	for	(int32 i = 0; i	< attrs->GetLength(); i++)
	{
		attrs->GetQName(i, attrNameW);
		attrNameW.GetSystemString(&attrName);

		if (attrName ==	"enabled")
		{
			attrs->GetValue(i, valueW);
			valueW.GetSystemString(&value);

			if (value == "true")
				Enable(kTrue);
			else if	(value == "false")
				Enable(kFalse);

			attrs->AttributeHandled(i);
		}
		else if	(attrName == "outputfilesize" || attrName == "outputfilecount" || attrName == "outputfilebuffersize")
		{
			attrs->GetValue(i, valueW);
			valueW.GetSystemString(&value);

			PMString::ConversionError	err;
			int32 number = value.GetAsNumber(&err);
			if (err	== PMString::kNoError)
			{
				if (attrName ==	"outputfilesize")
					fOutputFileSize	= number;
				else if	(attrName == "outputfilecount")
					fOutputFileCount = number;
				else 
					fBufferSize	= number;
			}

			attrs->AttributeHandled(i);
		}
	}
}

void XMLDiagnosticLogger::GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs)
{
	CDiagnosticLogger::GenerateLoggerConfig(attrs);

	IXMLOutStream::Attribute aAttr;
	PrintToString("%d",	fOutputFileSize);
	aAttr.fName	= WideString("outputfilesize");
	aAttr.fValue = WideString(fStringBuffer);
	attrs.push_back(aAttr);

	PrintToString("%d",	fOutputFileCount);
	aAttr.fName	= WideString("outputfilecount");
	aAttr.fValue = WideString(fStringBuffer);
	attrs.push_back(aAttr);

	PrintToString("%d",	fBufferSize);
	aAttr.fName	= WideString("outputfilebuffersize");
	aAttr.fValue = WideString(fStringBuffer);
	attrs.push_back(aAttr);
}


void XMLDiagnosticLogger::InitializeLogger()
{
	fCurrentTime = clock();
	fCurrentFile = 1;

	fOutputFileName	= MakeOutputFileName(fCurrentFile);
	fFileStream = new FileBytesOutStream(fBufferSize*1024);

	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLogConfigManager>	iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
	fOutputPath	= iConfigManager->GetOutputPath();

	InitLogFile();
}


void XMLDiagnosticLogger::Reset()
{
	;
}


void XMLDiagnosticLogger::HandleAbnormalAppTermination(AppTerminationState state)
{
#ifdef WINDOWS
	OutputDebugStringA("XML Logger : HandleAbnormalAppTermination\n");
#endif

	if (fStreamOpen)
	{
		PMString temp;
		if (state == kUnhandledException)
			temp.SetCString("kUnhandledException"); 
		else 
			temp.SetCString("kProtectiveShutdown"); 

		while (fStack.size() > 0)
		{
			DiagLogStackItem item = fStack.back();
			fStack.pop_back();

			fIndentLevel--;
			Pop(item.fContext);
		}

		IXMLOutStream::Attribute attr;
		IXMLOutStream::AttributeList attrs;

		attr.fName = WideString("type");
		attr.fValue = WideString(temp);

		attrs.push_back(attr);

		PushWithAttributes("Message", attrs);
		Pop("Message");

		CloseLogFile();
	}
}


void XMLDiagnosticLogger::IdleFlush()
{
	if (fStreamOpen)
		fFileStream->Flush();
}
