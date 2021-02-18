//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/inxerrorlogging/iinxerrlogfacade.h $
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

#ifndef __IINXErrLogFacade_h__
#define __IINXErrLogFacade_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:

// Project includes:
#include "INXErrLogID.h"



class IINXErrLogFacade : public IPMUnknown
{
public:

	enum	{ kDefaultIID = IID_INXERRLOGFACADE };
	
	/**	Get state of the INXErrorHandler.
	 *	@param items IN The state indicates INXErrorHandler on/off
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetINXErrorHandlerState(bool16 &state) = 0;
	
	/**	Create INXErrorHandler.	
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode CreateINXErrorHandler() = 0;	
	
	/**	Clear INXErrorHandler.	
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode ClearINXErrorHandler() = 0;
	
	/**	Sets the base file path which will be used to output the INX Error data.	
		Successive export/import operation will append a suffix("_1", "_2" etc) to 
		this base file path and ouput to this new path.
	* 	@return ErrorCode kSuccess if success, specific error code otherwise.
	*/
	virtual void SetBaseINXErrorHandlerPath(const PMString& path) = 0;
	
	/**	Get the base file path which is used to output the INX Error data.	
	* 	@return ErrorCode kSuccess if success, specific error code otherwise.
	*/
	virtual void GetBaseINXErrorHandlerPath(PMString& path) = 0;
};
#endif // __IINXErrLogFacade_h__
