//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/consolelogger/ConLgrDiagnosticLogger.cpp $
//  
//  Owner: InDesign Developer Technologies
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

// Interface includes:
#include "IDiagnosticLogger.h"
#include "IDiagnosticLog.h"
#include "IDiagLogConfigManager.h"
#include "ISAXAttributes.h"
#include "IBoolData.h"

#include "FileUtils.h"
#include "CoreFileUtils.h"
#include <vector>

// Project includes:
#include "ConLgrID.h"


/** 
	A console based logger service provider.  On the mac, it outputs the log into the Console.app, the Console needs to be
	launched first before InDesign.  On the PC, it outputs the log into a command prompt window.
	
	Provides IDiagnosticLogger implementation, which is used by the application's logging dispatcher component as one of the 
	available loggers.  DiagnosticLog plugin provides 2 default loggers which are text and xml based.  The logger componenet
	provide a facility to output the logging information and is explained in Diagnostic Logger technote. 

    @ingroup consolelogger
*/
class ConLgrLoggerProvider :  public CPMUnknown<IDiagnosticLogger>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	ConLgrLoggerProvider(IPMUnknown* boss);

	/** Destructor. Does nothing.
	*/
	~ConLgrLoggerProvider();


    /**
        Enter pre-defined context, format the context string and call TraceToWindow to output the log.

        @param context The name of context ("action", "command", etc.).
        @param attrs A reference to attribute list that contains the name and value pairs about context.
        @param Param1 A generic pointer associated with context. See IDiagLoggingAPI::EnterContext
        @param Param2 A generic pointer associated with context. See IDiagLoggingAPI::EnterContext
	*/
	virtual void EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2);
    /**
        Exit pre-defined context. Log any message before exiting the context.

        @param context The name of context ("action", "command", etc.). It should match the context in
        EnterContext method.
    */
	virtual void ExitContext(const PMString & context);
    /**
        Log a message. Format the message and attributes and output to Console window with TraceToWindow.

        @param messageType The name of message ("tracking", "transaction", etc.).
        @param attrs A reference to attribute list that contains the name and value pairs about message.
        @param Param1 A generic pointer associated with message. See IDiagLoggingAPI::LogMessage
    */
	virtual void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1 = nil);
	
    /**
        Initialize logger by calling InitLogFile().
    */
	virtual void InitializeLogger();

    /**
        Load logger configuration. The configuration is the logger element in the configuration xml file.

        @param attrs AttributeList which contains configuration data
    */
	virtual void LoadLoggerConfig(ISAXAttributes * attrs);
    /**
        Generate logger configuration. The configuration is the logger element in the configuration xml file. Custom
		attributes can be put in here and load in the LoadLoggerConfig method.

        @param attrs AttributeList which contains configuration data
    */
	virtual void GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs);

    /**
        Handle application crash/protective shutdown.
    */
	virtual void HandleAbnormalAppTermination(AppTerminationState state);

    /**
        Flush data buffer when you are asked to do so, in this case, nothing to flush since data is output in real time, not held in a buffer.
    */
	virtual void IdleFlush();
    /**
        Reset logger.
    */
	virtual void Reset();

	/** store the enable/disable state of the logger */
	void Enable(bool16 enable) { fEnabled = enable;}
	/** return the enable/disable state of the logger */
	bool16 IsEnabled() const { return fEnabled;}
	/** return the name of the logger */
	const PMString GetName() const { return fName; }

private:
    /**
        Log the time stamp.
    */
	void InitLogFile();
    /**
        Log the time stamp. Do whatever clean up necessary, it is called by the dtor
    */
	void FinishLog();
    /**
        Platform specific implementation for tracing a text string to Console.app on the mac and cmd.exe on the PC.
        @param message text string to be output to the console
   */
	void TraceToWindow(const char* message);

private:
	// utility
	/** C style format string util */
	char * PrintToString(const char *str, ...);
	char * fLineBuffer;
	char * fStringBuffer;

	bool16 fEnabled;
	PMString fName;
	int32	fIndentLevel;
	std::vector<DiagLogStackItem> fStack;
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(ConLgrLoggerProvider, kConLgrDiagnosticLoggerImpl)

ConLgrLoggerProvider::ConLgrLoggerProvider(IPMUnknown *boss) :
	CPMUnknown<IDiagnosticLogger>(boss),
	fEnabled(kFalse),
	fIndentLevel(0)
{
	fName = PMString("console");
	fStringBuffer = new char[kDIAGLOGSTRINGBUFFERSIZE];
	fLineBuffer = new char[kDIAGLOGLINEBUFFERSIZE];
}

ConLgrLoggerProvider::~ConLgrLoggerProvider()
{
	FinishLog();
	delete [] fStringBuffer;
	delete [] fLineBuffer;
}

/* InitLogFile
*/
void ConLgrLoggerProvider::InitLogFile()
{
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

	int32 len = text.GetPlatformString().size();
	TraceToWindow(text.GetPlatformString().c_str());
	fIndentLevel++;
}

/* FinishLog
*/
void ConLgrLoggerProvider::FinishLog()
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

	int32 len = text.GetPlatformString().size();
	TraceToWindow(text.GetPlatformString().c_str());

	fIndentLevel = 0;
}

/* EnterContext
*/
void ConLgrLoggerProvider::EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2)
{
	//create the DiagLogStackItem and push back it to stack
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

	int32 len = line.GetPlatformString().size();
	TraceToWindow(line.GetPlatformString().c_str());
	fIndentLevel++;
}

/* ExitContext
*/
void ConLgrLoggerProvider::ExitContext(const PMString & context)
{
	do 
	{
		fIndentLevel--;

		//pop up item from stack
		int32 end = clock();
		if(fStack.size()==0)
			break;
		DiagLogStackItem item = fStack.back();
		fStack.pop_back();
		ASSERT(context == item.fContext);

		InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(iDiagnosticLog != nil);
		if (iDiagnosticLog == nil)
		{
			break;
		}
		InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
		ASSERT(iConfigManager != nil);
		if (iConfigManager == nil)
		{
			break;
		}
		//get the logging time info
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
	} while (false);
}

/* LogMessage
*/
void ConLgrLoggerProvider::LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1)
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

	int32 len = line.GetPlatformString().size();
	TraceToWindow(line.GetPlatformString().c_str());
}

/* LoadLoggerConfig
*/
void ConLgrLoggerProvider::LoadLoggerConfig(ISAXAttributes * attrs)
{
	// read configuration
	WideString attrName, value;
	for (int32 i = 0; i < attrs->GetLength(); i++)
	{
		attrs->GetQName(i, attrName);
		PMString	enabledStr("enabled"), falseStr("false"), trueStr("true");
		WideString	sEnabled(enabledStr), sFalse(falseStr), sTrue(trueStr);
		if (attrName == sEnabled)
		{
			attrs->GetValue(i, value);
			if (value == sTrue) 
			{
				Enable(kTrue);
			}
			else if (value == sFalse) 
			{
				Enable(kFalse);
			}

			attrs->AttributeHandled(i);
		}
	}
}

/* GenerateLoggerConfig
*/
void ConLgrLoggerProvider::GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs)
{
    IXMLOutStream::Attribute aAttr;

	aAttr.fName = WideString("name");
	aAttr.fValue = WideString(fName);
	attrs.push_back(aAttr);

	PMString temp = fEnabled ? "true" : "false";
	aAttr.fName = WideString("enabled");
	aAttr.fValue = WideString(temp);
	attrs.push_back(aAttr);
}

/* InitializeLogger
*/
void ConLgrLoggerProvider::InitializeLogger()
{
	InitLogFile();
}

/* Reset
*/
void ConLgrLoggerProvider::Reset()
{
}

/* HandleAbnormalAppTermination
*/
void ConLgrLoggerProvider::HandleAbnormalAppTermination(AppTerminationState state)
{
	PMString text, temp;
	if (state == kUnhandledException)
		temp.SetCString("kUnhandledException"); 
	else 
		temp.SetCString("kProtectiveShutdown"); 

	sprintf(fStringBuffer, "%s=\"%s\"  ", "MessageType", temp.GetPlatformString().c_str());
	text.Append(fStringBuffer);
	TraceToWindow(text.GetPlatformString().c_str());
	// this method gets called in the event of crash or shutdown, better finish up the log right here.
	FinishLog();
}

/* IdleFlush
*/
void ConLgrLoggerProvider::IdleFlush()
{
	// do nothing, this logger does not use any buffer, it writes out to the consol in real time
}



/* TraceToWindow
 send the message to the Mac Console application
*/
void ConLgrLoggerProvider::TraceToWindow(const char* message)
{
#ifdef MACINTOSH
	if ( message && message[0] )
	{
		// convert the message to pascal
		static unsigned char mesg[256];
		long	len = strlen(message);
		if ( len > 255 ) 
		{
			len = 255;
		}
	
		BlockMoveData(message,mesg+1,len);
		
		// remove any trailing line feed
		//  Mac console automatically adds a line feed to every message
		if ( mesg[len] == '\n' ) 
		{
			len--;
		}	
		
		mesg[0] = len;
		
		DebugStr(mesg);
	}
#endif
#ifdef WINDOWS
	static HANDLE	consoleH = INVALID_HANDLE_VALUE;
	
	if (consoleH == INVALID_HANDLE_VALUE) 
	{
		// Create the console window
		BOOL	success;

		if (::AllocConsole()) 
		{
			// Get the console window's handle
			consoleH = ::GetStdHandle(STD_ERROR_HANDLE);
			
			// Set some options
			if (consoleH != INVALID_HANDLE_VALUE) 
			{
				success = ::SetConsoleTitle(TEXT("Debug Log"));
			
				COORD size = {180, 120};
				success = ::SetConsoleScreenBufferSize(consoleH, size);
			}
		}
	}
	
	if (consoleH != INVALID_HANDLE_VALUE) 
	{
		unsigned long written;
		BOOL success = WriteConsoleA( consoleH, message, (DWORD)strlen(message), &written, NULL );
	}

#endif
}

/* PrintToString
*/
char* ConLgrLoggerProvider::PrintToString(const char *str, ...)
{
	va_list args;
	va_start(args, str);
#ifdef MACINTOSH
	std::vsnprintf(fStringBuffer, kDIAGLOGSTRINGBUFFERSIZE-1, str, args);
#endif
#ifdef WINDOWS
	_vsnprintf(fStringBuffer, kDIAGLOGSTRINGBUFFERSIZE-1, str, args);
#endif
	va_end(args);
	
	return fStringBuffer;
}

//  Code generated by DollyXs code generator
