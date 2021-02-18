//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptProvider.h $
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
#ifndef __IScriptProvider__
#define __IScriptProvider__

#include "ScriptingID.h"
#include "ScriptData.h"

class IScript;
class IScriptRequestData;

/**
	Provides the code to handle one or more specific methods or properties on a specific exposed scripting object.

	For every exposed object there is one or more ScriptProviders. Only one ScriptProvider represents an 
	object and implements GetObject. Other ScriptProviders implement new methods or properties.

	Most implementations will want to inherit from CScriptProvider or RepresentScriptProvider.
	Implementations representing a singleton object (e.g., preferences) will want to subclass PrefsScriptProvider.
*/
class IScriptProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTPROVIDER };

	/** Obtain a list of child objects, as specified by the data, that are contained in the parent object. 
		@param data is the request data. The implementation must call AppendReturnData before returning.
		@param parent is the parent object
	*/
	virtual void	GetObject( IScriptRequestData* data, IScript* parent ) = 0 ;

	/**	Handle the specified method using the provided data for the target objects. 
		@param methodID is the request ID
		@param data is the request data. The implementation must call AppendReturnData before returning.
		@param scriptList is the target objects
	*/
	virtual void	HandleMethodOnObjects( ScriptID methodID, IScriptRequestData* data, const ScriptList& scriptList ) = 0 ;

	/**	Access the specified property using the provided data for the target objects. 
		@param propID is the request ID
		@param data is the request data. The implementation must call AppendReturnData before returning.
		@param scriptList is the target objects
	*/
	virtual void	AccessPropertyOnObjects( ScriptID propID, IScriptRequestData* data, const ScriptList& scriptList ) = 0 ;

	/**	Access multiple properties using the provided data for the target object. 
		@param data is the request data. The implementation must call AppendReturnData before returning.
		@param script is the target object
	*/
	virtual void	AccessProperties( IScriptRequestData* data, IScript* script ) = 0 ;
};

#endif
