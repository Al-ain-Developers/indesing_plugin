//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/utils/ErrorUtils.cpp $
//  
//  Owner: jargast
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

#include "VCPublicHeaders.h"

// ----- Interfaces -----

#include "IErrorState.h"
#include "IErrorStringService.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IExecutionContext.h"

// ----- Includes -----

#include "ErrorTableTypes.h"
#include "RsrcSpec.h"
#include "PMNew.h"

// ----- Utility files -----

#include "ErrorUtils.h"
#include "StreamUtil.h"

// global variable
#ifdef MACINTOSH
// modified only from main thread
static int16 ts_ExitCode = 0;
#endif

#ifdef WINDOWS
// see old comment in WinMain.cpp
// modified only from main thread
static int16 ts_ExitCode = -1;		// ----- Set by the frame windows event handler upon processing
						//		 WM_QUIT. [amb]
						// Roey: changed it to -1
#endif

inline IErrorState *GetErrorState()
{
	return GetExecutionContext()->GetErrorState();
}

///////////////////////////////////////////////////////////////////////
//	GlobalErrorStatePreserver                                        //
///////////////////////////////////////////////////////////////////////

GlobalErrorStatePreserver::GlobalErrorStatePreserver()
{
	IErrorState *iErrorState = GetErrorState();
	ASSERT_MSG( iErrorState != nil, "GlobalErrorStatePreserver - iErrorState is nil" ); 

	// Capture current error information. Only store the error string if
	// it was explicitly set.

	fDoRestore = kTrue;

	fErrorCode = iErrorState->GetErrorCode();
	fErrInfo = iErrorState->QueryErrorInfo();
	fContextString = iErrorState->GetContextInfo();

	fExplicitString = iErrorState->IsExplicitString();
	if (fExplicitString)
	{
		fErrorString = iErrorState->GetErrorString();
	}
}

GlobalErrorStatePreserver::~GlobalErrorStatePreserver()
{
	if(fDoRestore)
	{
		IErrorState *iErrorState = GetErrorState();
		ASSERT_MSG( iErrorState != nil, "GlobalErrorStatePreserver - iErrorState is nil" ); 

		iErrorState->Set(kSuccess);
		if(fErrorCode != kSuccess)
		{
			const PMString *errStr = (fExplicitString) ? &fErrorString : nil;
			iErrorState->Set(fErrorCode, errStr, fErrInfo, &fContextString);
		}
	}

	if (fErrInfo != nil)
	{
		fErrInfo->Release();
	}
}

void GlobalErrorStatePreserver::DoNotRestoreErrorState()
{
	fDoRestore = kFalse;
}


///////////////////////////////////////////////////////////////////////
//	ErrorUtils                                                       //
///////////////////////////////////////////////////////////////////////

// Sets the global error code on the session
void ErrorUtils::PMSetGlobalErrorCode (ErrorCode errCode, const PMString* errString, IPMUnknown* errInfo, const PMString* contextInfo)
{
	IErrorState *iErrorState = GetErrorState();
	ASSERT_MSG( iErrorState != nil, "ErrorUtils - iErrorState is nil" ); 
	iErrorState->Set (errCode, errString, errInfo, contextInfo);
}

// Gets the current global error code
ErrorCode ErrorUtils::PMGetGlobalErrorCode()
{
	IErrorState *iErrorState = GetErrorState();
	ASSERT_MSG( iErrorState != nil, "ErrorUtils - iErrorState is nil" ); 
	return iErrorState->GetErrorCode();
}

// Gets the current global error string.  May be empty
PMString ErrorUtils::PMGetGlobalErrorString()
{
	IErrorState *iErrorState = GetErrorState();
	ASSERT_MSG( iErrorState != nil, "ErrorUtils - iErrorState is nil" ); 
	return iErrorState->GetErrorString();
}

// returns the current global error info
IPMUnknown* ErrorUtils::PMQueryGlobalErrorInfo()
{
	IErrorState *iErrorState = GetErrorState();
	ASSERT_MSG( iErrorState != nil, "ErrorUtils - iErrorState is nil" ); 
	return iErrorState->QueryErrorInfo();
}

PMString ErrorUtils::PMGetGlobalContextInfo()
{
	IErrorState *iErrorState = GetErrorState();
	ASSERT_MSG( iErrorState != nil, "ErrorUtils - iErrorState is nil" ); 
	return iErrorState->GetContextInfo();
}

// finds the error string corresponding to the errCode
PMString ErrorUtils::PMGetErrorString (ErrorCode errCode, IPMUnknown* errInfo)
{
	PMString errorString;
	
	int32 numErrorServices, n;
	InterfacePtr<IK2ServiceRegistry> registry(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	
	if (registry)	{		// if we're early in startup there might not be a registry yet

		numErrorServices = registry->GetServiceProviderCount (kErrorStringService);
					
		for ( n = 0; n < numErrorServices; n++ )
		{
			InterfacePtr<IK2ServiceProvider> service(registry->QueryNthServiceProvider(kErrorStringService, n));
			InterfacePtr<IErrorStringService> iErrorStringService(service, IID_IERRORSTRINGSERVICE);
			
			if (iErrorStringService && (iErrorStringService->HasUserErrorString (errCode, errInfo)) )
			{
				errorString = iErrorStringService->GetUserErrorString(errCode, errInfo);
				if( ! errorString.empty() )
				{
					// We break if we found an error string for this error code.  
					// Otherwise we keep looking because some plug-in prefix IDs are shared,
					// and we may find the error string in another plug-in.
					break;	
				}
			}
		}		
	}
	
	return errorString;
}

// Reads the error string from the current resource fork
//

PMString ErrorUtils::PMLoadErrorStringFromRsrc
	(
		ErrorCode	 	errCode,
		PluginID		errorRsrcPluginId,
		RsrcID			errorTableId
	)
{
	int32 resType, itemErrMin, itemErrMax;
	int16 itemCount;
	uint8  itemStringSize;
	PMString errString;
	uint8 errCString[256]; // max size is 255 chars
	
	resType = kUErrorTableType;
	
	IPMStream * errStream = StreamUtil::CreateResourceStreamRead
										( RsrcSpec( errorRsrcPluginId, resType, errorTableId ) );
	if (  errStream != nil ) 
	{
		errStream->XferInt16( itemCount );

		for ( int32 i = 0; i < itemCount; ++i ) 
		{ 
			errStream->XferInt32( itemErrMin );
			
			// platform errors have a max with the min
			// user errors only have one value
			itemErrMax = itemErrMin;
				
			errStream->XferByte( itemStringSize );

			if ( errCode >= itemErrMin && errCode <= itemErrMax )
			{
				errStream->XferByte (errCString, itemStringSize);
				errCString[itemStringSize] = '\0'; // append terminator
				errString.SetKey ((char*)errCString);
				break;
			}
			
			// Otherwise, jump to the next set of error codes
			errStream->Seek (itemStringSize, kSeekFromCurrent);
		}
				
		errStream->Close();
		errStream->Release();
	}
	
	// Finally, translate the error string
	errString.Translate();
	
	return errString;
}

void ErrorUtils::SetExitCode( int16 exitCode )
{
	ASSERT_MSG(K2Memory::IsMainThread(),"ErrorUtils::SetExitCode can only be called from main thread");
	ASSERT_MSG( ts_ExitCode <= 0, FORMAT_ARGS( "ErrorUtils::SetExitCode - changing error code from %l to %l", ts_ExitCode, exitCode ) );
	ts_ExitCode = exitCode;
}

int16 ErrorUtils::GetExitCode()
{
	return ts_ExitCode;
}
