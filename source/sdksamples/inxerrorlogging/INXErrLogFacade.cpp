//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/inxerrorlogging/INXErrLogFacade.cpp $
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
#include "iinxerrlogfacade.h"
#include "IINXManager.h"
#include "IINXErrorHandler.h"
#include "IStringData.h"

#include "Utils.h"
#include "SDKFileUtils.h"

class INXErrLogFacade : public CPMUnknown<IINXErrLogFacade> 
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	INXErrLogFacade(IPMUnknown*  boss) : CPMUnknown<IINXErrLogFacade>(boss) {}
	
	/** 
		Destructor.
	*/
	virtual ~INXErrLogFacade() {}

	/**	Get state of the INXErrorHandler.
	 *	@param items IN The state indicates INXErrorHandler on/off
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetINXErrorHandlerState(bool16 &state);

	/**	Create INXErrorHandler.	
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode CreateINXErrorHandler();	

	/**	Clear INXErrorHandler.	
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode ClearINXErrorHandler();

	/**	Set path of INXErrorHandler.	
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */

	virtual void SetBaseINXErrorHandlerPath(const PMString& path) { 
		SDKFileUtils::SetBaseFilePath(path);}
	
	virtual void GetBaseINXErrorHandlerPath(PMString& path){
		SDKFileUtils::GetBaseFilePath(path);}
	
private:
	static IINXErrorHandler* INXErrorHandlerCreator();	
};

CREATE_PMINTERFACE(INXErrLogFacade, kINXErrLogFacadeImpl)

IINXErrorHandler* INXErrLogFacade::INXErrorHandlerCreator()
{
	IINXErrorHandler* handler((IINXErrorHandler*)::CreateObject(kSDKINXErrorHandlerBoss, IID_IINXERRORHANDLER));
	if (handler == nil)
	{
		ASSERT_FAIL("INXErrLogFacade::IINXErrorHandler: invalid");
		return nil;
	}

	PMString path;
	SDKFileUtils::GetNextFilePath(path);
	InterfacePtr<IStringData> errorLogStringData(handler, IID_INXERRORPATHGDATA);
	errorLogStringData->Set(path);

	return handler;
}

ErrorCode INXErrLogFacade::GetINXErrorHandlerState(bool16 &state)
{	
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<IINXManager> iINXManager( GetExecutionContextSession()->QueryINXManager() ) ;
		if (iINXManager == nil)
		{
			ASSERT_FAIL("INXErrLogFacade::IINXManager: invalid");
			break; 
		}
		error = kSuccess;
		if (iINXManager->GetINXErrorHandler())
		{
			state = kTrue;
		}
		else
		{
			state = kFalse;
		}
	}while (false);
	
	return error;

}

ErrorCode INXErrLogFacade::ClearINXErrorHandler()
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<IINXManager> iINXManager( GetExecutionContextSession()->QueryINXManager() ) ;
		if (iINXManager == nil)
		{
			ASSERT_FAIL("INXErrLogFacade::IINXManager: invalid");
			break; 
		}
		iINXManager->SetINXErrorHandler(nil);
		error = kSuccess;
	}while (false);

	return error;
}

ErrorCode INXErrLogFacade::CreateINXErrorHandler()
{
	ErrorCode error = kFailure;
	
	do
	{
		InterfacePtr<IINXManager> iINXManager( GetExecutionContextSession()->QueryINXManager() ) ;
		if (iINXManager == nil)
		{
			ASSERT_FAIL("INXErrLogFacade::IINXManager: invalid");
			break; 
		}
		iINXManager->SetINXErrorHandler(INXErrLogFacade::INXErrorHandlerCreator);
		error = kSuccess;
	} while(false);

	return error;
}