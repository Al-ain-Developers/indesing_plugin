//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunLog.cpp $
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

// Interface includes:
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ITextControlData.h"
#include "ICounterControlData.h"
#include "IPMStream.h"

// General includes:
#include "ShuksanID.h"
#include "PMString.h"
#include "K2Vector.h"
#include "IPalettePanelUtils.h"
#include "Trace.h"
#include "CmdUtils.h"

// Project includes:
#include "SnipRunLog.h"
#include "SnipRunID.h"

const PMString kSnipRunLogStartupMessage=PMString("SnippetRunner log started");

/*
	Factory methods. Single instance used.
*/
SnipRunLog* SnipRunLog::fSnipRunLog  = nil;

/*
*/
SnipRunLog* SnipRunLog::Instance()
{
	if (fSnipRunLog == nil)
	{
		fSnipRunLog = new SnipRunLog(kSnipRunPanelWidgetID, kSnipRunLogWidgetID, kSnipRunLogScrollBarWidgetID);
		ASSERT_MSG(fSnipRunLog != nil, "new SnipRunLog failed");
	}
	return fSnipRunLog;
}

/*
*/
bool16 SnipRunLog::InitPanelView()
{
	if (fPanelInit == kFalse) {
		do {
			// Find the panel.
			InterfacePtr<IPanelControlData> panelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(fLogPanelWidgetID));
			if (panelControlData == nil)
			{
				// Commented out so that when the script provider tries to access an instance
				// of SnipRunLog when the panel is closed, this assert doesn't show. 
				// (sadahiro 04-mar-2005)
				//ASSERT_FAIL("panelControlData invalid");
				break;
			}
			{
				// Cache an interface pointer to the log's text control data.
				IControlView* controlView = panelControlData->FindWidget(fLogWidgetID);
				if (controlView == nil)
				{
					ASSERT_FAIL("controlView invalid for logWidget");
					break;
				}
				InterfacePtr<ITextControlData> logTextControlData(controlView, UseDefaultIID());
				if (logTextControlData == nil)
				{
					ASSERT_FAIL("invalid logTextControlData");
					break;
				}
				fLogTextControlData = logTextControlData;
			}

			{
				// Cache an interface pointer to the log's scroll bar.
				IControlView* controlView = panelControlData->FindWidget(fScrollBarWidgetID);
				if (controlView == nil)
				{
					ASSERT_FAIL("controlView invalid for scrollBarWidget");
					break;
				}
				InterfacePtr<ICounterControlData> counterData(controlView, UseDefaultIID());
				if(counterData==nil) {
					ASSERT_FAIL("counterData nil");
					break;
				}
				fScrollBarCounterData = counterData;
			}
			fPanelInit=kTrue;
		} while (kFalse);
	}
	return fPanelInit;
}

void SnipRunLog::DetachPanelView()
{
	fPanelInit = kFalse;
	fScrollBarCounterData.reset(nil);
	fLogTextControlData.reset(nil);
}
/*
*/
void SnipRunLog::DeleteInstance()
{
	if (fSnipRunLog != nil)
		delete fSnipRunLog;
	fSnipRunLog = nil;
}

/*
*/
SnipRunLog::SnipRunLog
(
 const WidgetID& logPanelWidgetID, 
 const WidgetID& logWidgetID,
 const WidgetID& scrollBarWidgetID
) 
: 
	fLogTextControlData(nil),
	fScrollBarCounterData(nil),
	fTrace(kFalse),
	fResizeInProgress(kFalse),
	fLogWidgetID(logWidgetID),
	fLogPanelWidgetID(logPanelWidgetID),
	fScrollBarWidgetID(scrollBarWidgetID),
	fPanelInit(kFalse)
{
	TRACEFLOW(kSnipRunPluginName, "SnipRunLog ctor\n");
	do
	{
		if (this->InitPanelView() == kFalse){
			break;
		}
		// Restore the log from the widget state.
		fLog = fLogTextControlData->GetString();
		this->UpdateTextControl();

	} while (false);
}

/*
*/
SnipRunLog::~SnipRunLog()
{
	TRACEFLOW(kSnipRunPluginName, "SnipRunLog dtor\n");
}

/*
*/
void SnipRunLog::Log(const PMString& message)
{
	PMString kNewLine;
	kNewLine.AppendW('\n');
	do
	{
		if (fTrace == kTrue)
			TRACE("%s\n", message.GetUTF8String().c_str());

		// Break out if the log is not available.
		if (fLogTextControlData == nil)
			break;

		// Log each message on a line.
		PMString logMessage(message);

		// Check for a string that only has Carriage Returns, without any
		// Line Feeds. If found, convert all CR to LF. Watson 1008391.
		CharCounter CRPos = logMessage.IndexOfCharacter('\r');
		if (CRPos >= 0)
		{
			CRPos = 0;
			while ((CRPos = logMessage.IndexOfCharacter('\r', CRPos)) >= 0)
			{
				logMessage.Remove(CRPos);
				logMessage.Insert('\n', CRPos);
			}
		}

		logMessage.AppendW('\n');

		// Append message to the foot of the log.
		fLog.Append(logMessage);
		fLog.SetTranslatable(kFalse);

		// Note that to update the view of the log UpdateTextControl must
		// be called.

	} while(false);
}

/*
*/
void SnipRunLog::UpdateTextControl()
{
	do {
		if (this->InitPanelView() == kFalse) {
			break;
		}
		// Seems that for this to work correctly with the control,
		// it's necessary to scroll the widget to the top before appending- otherwise
		// some odd behaviour is observed.
		this->ScrollToTop();
		fLogTextControlData->SetString(fLog);
		this->ScrollToBottom();

	} while(false);
}

/*
*/
void SnipRunLog::Clear()
{
	fLog.Clear();
	this->UpdateTextControl();
}

/*
*/
void SnipRunLog::Resize()
{
	if (fResizeInProgress == kFalse) {
		fResizeInProgress = kTrue;
		fSavedLog = fLog;
		this->Clear();
		InterfacePtr<ICommand> restoreLogCmd(CmdUtils::CreateCommand(kSnipRunRestoreLogCmdBoss));
		ErrorCode status = CmdUtils::ScheduleCommand(restoreLogCmd);
		ASSERT(status == kSuccess);
	}
}

/*
*/
void SnipRunLog::ResizeComplete()
{
	fLog = fSavedLog;
	this->UpdateTextControl();
	fResizeInProgress = kFalse;
}

/*
*/
void SnipRunLog::SaveLog(InterfacePtr<IPMStream> stream)
{
	const uchar kInternalNewLine='\n';
#ifdef MACINTOSH
		const char* kExternalNewLine="\r";
#else
		const char* kExternalNewLine="\r\n";
#endif
	for (int32 i = 0; i < fLog.CharCount(); i++)
	{
		PlatformChar pc = fLog[i];

		// if dual-byte char, output as is, highbyte first.
		if (pc.IsTwoByte()) 
		{
			uchar	hb = pc.HighByte(), 
					lb = pc.LowByte();
			stream->XferByte(&hb, 1);
			stream->XferByte(&lb, 1);
		}
		else // non-dualbyte char
		{
			uchar c = pc.GetAsOneByteChar();
			if (c == kInternalNewLine)
			{
#ifdef MACINTOSH
			stream->XferByte((uchar*)kExternalNewLine, 1);
#else
			stream->XferByte((uchar*)kExternalNewLine, 2);
#endif
			}
			else
			{
				stream->XferByte(&c, 1);
			}
		}
	}
}
/*
*/
void SnipRunLog::ScrollToTop()
{
	do {
		if(fScrollBarCounterData==nil) {
			ASSERT_FAIL("fScrollBarCounterData nil");
			break;
		}
		int32 minValue = fScrollBarCounterData->GetMinimum();	
		fScrollBarCounterData->SetValue(minValue);
	} while(false);
}

/*
*/
void SnipRunLog::ScrollToBottom()
{
	do {
		if(fScrollBarCounterData==nil) {
			ASSERT_FAIL("fScrollBarCounterData nil");
			break;
		}
		int32 maxValue = fScrollBarCounterData->GetMaximum();	
		fScrollBarCounterData->SetValue(maxValue);
	} while(false);
}


/*
*/
static char gBuffer[2048];
#ifdef WINDOWS
#define vsnprintf _vsnprintf
namespace std {
	using ::_vsnprintf;
}
#endif

/*
*/
void SNIPLOG(const char* str, ...)
{
    va_list args;
    va_start(args, str);
	std::vsnprintf(gBuffer, sizeof(gBuffer) - 1, str, args);
    va_end(args);

	PMString pmstr;
	pmstr.SetCString(gBuffer, PMString::kUnknownEncoding);
	SnipRunLog::Instance()->Log(pmstr);
}

/*
*/
void SNIPLOG_ASSERT_FAIL(const char* str, ...)
{
    va_list args;
    va_start(args, str);
	std::vsnprintf(gBuffer, sizeof(gBuffer) - 1, str, args);
    va_end(args);

	PMString pmstr;
	pmstr.SetCString(gBuffer, PMString::kUnknownEncoding);
	SnipRunLog::Instance()->Log(pmstr);
	ASSERT_FAIL(gBuffer);
}
// End, SnipRunLog.cpp.


