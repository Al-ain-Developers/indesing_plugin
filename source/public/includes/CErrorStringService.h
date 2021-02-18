//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CErrorStringService.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __CERRORSTRINGSERVICE__
#define __CERRORSTRINGSERVICE__

#include "CPMUnknown.h"
#include "IErrorStringService.h"

/**	Base class for implementing IErrorStringService.

	@ingroup arch_error
*/
class PUBLIC_DECL CErrorStringService : public CPMUnknown<IErrorStringService>
{
	typedef CPMUnknown<IErrorStringService> Inherited ;

public:
	CErrorStringService( IPMUnknown* boss, PluginID pluginPrefix, RsrcID errorStringTableRsrcID ) ;
	~CErrorStringService() ;
	
	virtual bool16 HasUserErrorString( ErrorCode errCode, IPMUnknown* errInfo ) const ;
	virtual PMString GetUserErrorString( ErrorCode errCode, IPMUnknown* errInfo ) const ;
	
#if 0	
	/** Not currently supported - for future use.*/
	virtual bool16 HasUserErrorDescription( ErrorCode errCode, IPMUnknown* errInfo ) const ;
	/** Not currently supported - for future use.*/
	virtual PMString GetUserErrorDescription( ErrorCode errCode, IPMUnknown* errInfo ) const ;
#endif

protected:
	PluginID	fPluginID ;
	RsrcID		fErrorStringTableRsrcID ;
} ;

#endif
