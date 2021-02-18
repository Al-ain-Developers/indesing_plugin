//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptErrorUtils.h $
//  
//  Owner: Jonathan W. Brown
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

#pragma once
#ifndef __IScriptErrorUtils__
#define __IScriptErrorUtils__

#include "IPMUnknown.h"

#include "ScriptData.h"
#include "ScriptingID.h"
#include "Utils.h"

class IScriptRequestData ;

class IScriptErrorUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTERRORUTILS } ;

	/**
		Prepare data required to return a required parameter missing error
		@param scriptRequestData is the IScriptRequestData associated with the script request
		@param param is the id of the missing parameter
		@return err
	*/
	virtual ErrorCode SetMissingRequiredParameterErrorData( const IScriptRequestData* scriptRequestData, const ScriptID param ) const = 0 ;

	/**
		Prepare data required to return an invalid parameter error
		@param scriptRequestData is the IScriptRequestData associated with the script request
		@param param is the id of the invalid parameter
		@param err is the desired error code
		@return err
	*/
	virtual ErrorCode SetInvalidParameterErrorData( const IScriptRequestData* scriptRequestData, const ScriptID param, ErrorCode err = kInvalidParameterError ) const = 0 ;

	/**
		Prepare data required to return an out of range error
		@param scriptRequestData is the IScriptRequestData associated with the script request
		@param param is the id of the out of range parameter
		@param value is the value of the out of range parameter
		@return err
	*/
	virtual ErrorCode SetOutOfRangeErrorData( const IScriptRequestData* scriptRequestData, const ScriptID param, const ScriptData& value ) const = 0 ;

	/**
		Prepare data required to return a read-only property error
		@param scriptRequestData is the IScriptRequestData associated with the script request
		@param param is the id of the read-only property
		@return err
	*/
	virtual ErrorCode SetReadOnlyPropertyErrorData( const IScriptRequestData* scriptRequestData, const ScriptID param ) const = 0 ;
} ;

#endif	// __IScriptErrorUtils__
