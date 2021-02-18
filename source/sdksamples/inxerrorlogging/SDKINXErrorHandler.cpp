//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/inxerrorlogging/SDKINXErrorHandler.cpp $
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

#include "IINXInfo.h"

#include "IINXErrorHandler.h"
#include "IFileStreamData.h"
#include "IScriptRequestData.h"
#include "IScriptUtils.h"
#include "ISysFileData.h"

#include <string>
#include <sstream>

#include "IDFile.h"
#include "StreamUtil.h"
#include "FileUtils.h"
#include "ErrorUtils.h"
#include "IStringData.h"

#include "INXErrLogID.h"
#include "TextID.h"
#include "TablesID.h"

class SDKINXErrorHandler : public CPMUnknown<IINXErrorHandler>
{
public:
	SDKINXErrorHandler( IPMUnknown *boss );
	virtual ~SDKINXErrorHandler();

	/**
		Reset the current INX error status to kINXContinue.
	*/
	virtual void ResetINXErrorStatus();

	/**
		Get the current INX error status. Set to kINXCancel in one of the 
		callbacks on this implementation to abort further processing.
		@return the current status
	*/
	virtual IINXErrorHandler::INXErrorStatus GetINXErrorStatus() const;

	/**
		Begin export session.
		@param stream The stream export to.
		@param roots The list of element to be exported.
	*/
	virtual void BeginExport(const IPMStream * stream, const IDOMElement::ElementList &roots);

	/**
		End export session.
	*/
	virtual void EndExport(); 

	/**
		Begin import session.
		@param stream The stream import from.
	*/
	virtual void BeginImport(const IPMStream *stream); 

	/**
		End import session.
	*/
	virtual void EndImport();

	/**
		Report an unknown element. Import only.
		@param parent The script id of unknown element.
		@param elem The name of unknown element
	*/
	virtual void UnknownElement(const ScriptID & parent, const WideString & elem);

	/**
		Report an unknown property on known object. Import only.
		@param parent The script id of known object.
		@param prop The name of unknown property
	*/
	virtual void UnknownProperty(const ScriptID & parent, const WideString & prop);
	/**
		Report an un-resolved reference. Import only.
		This happens when the value of an attribute refers to an object, but the object is not included in the document.
		@param selfID The self ID of referenced object
	*/
	virtual void UnresolvedReference(const WideString & selfID);

	/**
		Report parser error. Import only.
		@param err The error code
		@param errorStr The error string
	*/
	virtual void ParserError(ErrorCode err, const PMString & errorStr);

	/**
		Report scripting error.
		@param script The object on which the scripting request was invoked
		@param eventData The event data for the scripting request
		@param returnData The return data for the scripting request that failed
	*/
	virtual void ScriptingError(const IScript * script, const IScriptRequestData * eventData, const ScriptReturnData & returnData );

private:

	/**
		Writes a line to this plug-in's log file.
        @param stream for log output
        @param line to be written out to the log
    */
    void WriteLine(IPMStream* stream, const std::string& line);

	/**
		There are some known propery ErrorCodes, meaning we see a number of
		false errors.  Call this to see if you're dealing with one of those known
		errors.
		@param the error code to check
	*/
	bool IsKnownPropertyError( ErrorCode errorCode );

	/** convert int to string
	*/
	std::string IntToString(int32 i)	
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	IPMStream *fStream;

private:
	/**
		The current INX error status. Set to kINXCancel in one of the 
		callbacks on this implementation to abort further processing.
	*/
	IINXErrorHandler::INXErrorStatus fStatus;
};

CREATE_PMINTERFACE(SDKINXErrorHandler, kSDKINXErrorHandlerImpl)

SDKINXErrorHandler::SDKINXErrorHandler( IPMUnknown *boss ) :
	CPMUnknown<IINXErrorHandler>(boss), fStream(nil),
	fStatus( IINXErrorHandler::kINXContinue )
{
}

SDKINXErrorHandler::~SDKINXErrorHandler()
{
	if (fStream)
	{
		fStream->Release();
		fStream = nil;
	}
}

void SDKINXErrorHandler::ResetINXErrorStatus()
{
	fStatus = kINXContinue ;
}

IINXErrorHandler::INXErrorStatus SDKINXErrorHandler::GetINXErrorStatus() const
{
	return fStatus ;
}

void SDKINXErrorHandler::BeginExport(const IPMStream * stream, const IDOMElement::ElementList &roots)
{
    
	InterfacePtr<IStringData> errorLogStringData(this, IID_INXERRORPATHGDATA);
	ASSERT(errorLogStringData);
	if (!errorLogStringData) {
			ASSERT_MSG(kFalse, "Log file not exists!");;
	}
	IDFile logFilePath;
	FileUtils::PMStringToIDFile(errorLogStringData->GetString(), logFilePath);

	if (fStream)
	{
		ASSERT_MSG(kFalse, "fStream already exists");
		fStream->Release();
		fStream = nil;
	}

    fStream = StreamUtil::CreateFileStreamWrite(logFilePath, kOpenOut | kOpenApp, 'CWIE', 'TEXT');
    if (fStream)
    {
		this->WriteLine(fStream, "Begin a new INX Export Error Log\r\n"); 
		//May add a date time here
		//Add file info if the export stream is file based. Not IDML package import/export is not file based.
		PMString exportTo;
		InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
		if (fileData != nil)
		{
			const IDFile &outFile = fileData->GetSysFile();
			exportTo = FileUtils::SysFileToPMString(outFile);
			this->WriteLine(fStream, "Export to " + exportTo.GetUTF8String() + "\r\n"); //May add a date time here
		}

	}
	else
	{
        ASSERT_MSG(kFalse, "Couldn't create stream for error logging");
    }
}

void SDKINXErrorHandler::EndExport() 
{
	if (fStream)
	{
        this->WriteLine(fStream, "End of a session \r\n"); //May add a date time here

		// Close the log.
        fStream->Flush();
        fStream->Close();

		//release
		fStream->Release();
		fStream = nil;
	}
}
void SDKINXErrorHandler::BeginImport(const IPMStream *stream) 
{
	InterfacePtr<IStringData> errorLogStringData(this, IID_INXERRORPATHGDATA);
	ASSERT(errorLogStringData);
	if (!errorLogStringData) {
			ASSERT_MSG(kFalse, "Log file not exists!");;
	}
	IDFile logFilePath;
	FileUtils::PMStringToIDFile(errorLogStringData->GetString(), logFilePath);

	if (fStream)
	{
		ASSERT_MSG(kFalse, "fStream already exists");
		fStream->Release();
		fStream = nil;
	}

    fStream = StreamUtil::CreateFileStreamWrite(logFilePath, kOpenOut | kOpenApp, 'CWIE', 'TEXT');
    if (fStream)
    {
		this->WriteLine(fStream, "Begin a new INX Import Error Log\r\n"); 
		//May add a date time here
		//May add file info if the import stream is file based. Not IDML package import/export is not file based.
		PMString importFile;
		InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
		if (fileData != nil)
		{
			const IDFile &inFile = fileData->GetSysFile();
			importFile = FileUtils::SysFileToPMString(inFile);
			this->WriteLine(fStream, "Import from " + importFile.GetUTF8String() + "\r\n"); //May add a date time here
		}
	}
	else
	{
        ASSERT_MSG(kFalse, "Couldn't create stream for error logging");
    }

}
void SDKINXErrorHandler::EndImport() 
{
	if (fStream)
	{
        this->WriteLine(fStream, "End of a session \r\n"); //May add a date time here

		// Close the log.
        fStream->Flush();
        fStream->Close();

		//release
		fStream->Release();
		fStream = nil;
	}
}

void SDKINXErrorHandler::UnknownProperty(const ScriptID & parent, const WideString & prop)
{
	std::string elementName(PMString(Utils<IINXInfo>()->GetElementName(parent)).GetUTF8String());
	std::string propName(PMString(prop).GetUTF8String());
	this->WriteLine(fStream, "Unknown property: '" + propName + "'" +" on element " + "'" + elementName + "'"); 
}

void SDKINXErrorHandler::UnknownElement(const ScriptID & parent, const WideString & elem)
{
	std::string parentName(PMString(Utils<IINXInfo>()->GetElementName(parent)).GetUTF8String());
	std::string elemName(PMString(elem).GetUTF8String());
	this->WriteLine(fStream, "Unknown element: '" + elemName + "'" +" on parent " + "'" + parentName + "'"); 
}

void SDKINXErrorHandler::UnresolvedReference(const WideString & selfID)
{
	this->WriteLine(fStream, "Unresolved Reference: " + PMString(selfID).GetUTF8String() + " can not be resolved" ); 
}

void SDKINXErrorHandler::ParserError(ErrorCode err, const PMString & errorStr)
{
	this->WriteLine(fStream, "Parser Error: " + errorStr.GetUTF8String()); 
}

bool SDKINXErrorHandler::IsKnownPropertyError( ErrorCode errorCode )
{
	bool result = true;

	switch(errorCode)
	{
		case kPropertyNotApplicableError:
		case kInvalidRequestForRootStyleError:
		case kCellStyleAttributeNotDefinedError:
		case kInvalidScriptTargetError:
		case kTableStyleAttributeNotDefinedError:
			result = true;
	}

	return result;
}

void SDKINXErrorHandler::ScriptingError(const IScript * script, const IScriptRequestData * eventData, const ScriptReturnData & returnData)
{
	ErrorCode errorCode = returnData.GetErrorCode();
	std::string errorCodeStr;

	#if DEBUG
			
			DebugClassUtilsBuffer buffer;
			errorCodeStr = DebugClassUtils::GetIDName(&buffer, errorCode, kErrorIDSpace);
			
	#else
			std::ostringstream errorCodeOStream;
			if (errorCodeOStream << "0x" << std::hex << errorCode)
				errorCodeStr = errorCodeOStream.str();
	#endif

	switch ( eventData->GetRequestType() )
	{
		case IScriptRequestData::kGetObjectRequest :
		{
			std::string parentName = eventData->GetTargetInfo()->GetName().GetUTF8String() ;
			std::string childName = eventData->GetRequestInfo()->GetName().GetUTF8String() ;
			this->WriteLine(fStream, "Scripting Object Error: can not get child '" + childName + "' on parent '" + parentName + "'" ) ; 
			break ;
		}
		case IScriptRequestData::kMethodRequest :
		{
			std::string errorInfo = returnData.GetErrorString().GetUTF8String() ;
			if ( returnData.GetRequestID() == e_Create )
			{
				std::string parentName = script->GetObjectInfo(eventData->GetRequestContext())->GetName().GetUTF8String() ;
				std::string childName = eventData->GetTargetInfo()->GetName().GetUTF8String() ;
				this->WriteLine(fStream, "Scripting Create Error: create '" + childName + "' on parent '" + parentName + "' failed with error " + errorCodeStr + " '" + errorInfo + "'" ) ; 
			}
			else
			{
				std::string objectName = eventData->GetTargetInfo()->GetName().GetUTF8String() ;
				std::string eventName = eventData->GetRequestInfo()->GetName().GetUTF8String() ;
				this->WriteLine(fStream, "Scripting Event Error: event '" + eventName + "' on object '" + objectName + "' failed with error " + errorCodeStr + " '" + errorInfo + "'" ) ; 
			}
			break ;
		}
		case IScriptRequestData::kGetPropertyRequest :
		case IScriptRequestData::kPutPropertyRequest :
		{
			///if( IsKnownPropertyError(errorCode) )
			///	return;

			std::string operation;
			if (eventData->GetRequestType() == IScriptRequestData::kGetPropertyRequest)
				operation = "get";
			else
				operation = "set";

			std::string objectName = eventData->GetTargetInfo()->GetName().GetUTF8String() ;
			std::string propName = eventData->GetRequestInfo()->GetName().GetUTF8String() ;
			if ( eventData->GetRequestInfo()->GetScriptID() != returnData.GetRequestID() )
			{
				//Should be an AccessProperties request
				ASSERT( eventData->GetRequestInfo()->GetScriptID() == p_Properties ) ;
				const ScriptInfo::PropertyProviderPacket* pPPP = eventData->GetTargetInfo()->FindProperty( returnData.GetRequestID() ) ;
				if ( pPPP )
					propName = pPPP->Element()->GetName().GetUTF8String() ;
				else
					propName = PMString(Utils<IINXInfo>()->GetPropertyName( eventData->GetTargetInfo()->GetScriptID(), returnData.GetRequestID())).GetUTF8String() ;
			}
			
			std::string errorInfo = returnData.GetErrorString().GetUTF8String() ;
			this->WriteLine(fStream, "Scripting Property Error: " + operation + " property '" + propName + "' on object '" + objectName + "' failed with error " + errorCodeStr + " '" + errorInfo + "'" ) ; 
			break ;
		}
		case IScriptRequestData::kUnknownRequest :
		{
			std::string request = Utils<IScriptUtils>()->GetScriptID( returnData.GetRequestID() ).GetUTF8String() ;
			std::string objectName = script->GetObjectInfo(eventData->GetRequestContext())->GetName().GetUTF8String() ;
			std::string errorInfo = returnData.GetErrorString().GetUTF8String() ;
			this->WriteLine(fStream, "Scripting Error: request '" + request + "' on object '" + objectName + "' failed with error " + errorCodeStr + " '" + errorInfo + "'" ) ; 
			break ;
		}
		default :
		{
			ASSERT_UNIMPLEMENTED() ;
			break ;
		}
	}
}

void SDKINXErrorHandler::WriteLine(IPMStream* stream, const std::string& line)
{
	if ( !stream ){
		return;
	}

    uchar ch;
    std::string::const_iterator iter=line.begin();
    while (iter != line.end() && stream->GetStreamState() == kStreamStateGood)
    {
        ch = (uchar)*iter;
        stream->XferByte(ch);
        iter++;
    }
    stream->XferByte((uchar*)"\r\n", 2);

	if (fStream) {
	    fStream->Flush();  //To ensure every line is written out, even if the error handler is not uninstalled.
	}
}
