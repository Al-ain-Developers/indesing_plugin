//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptVersionInfo.h $
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
#ifndef __IScriptVersionInfo__
#define __IScriptVersionInfo__

#include "GUID.h"
#include "RequestContext.h"
#include "ScriptingID.h"

using namespace ScriptInfo ;

class IScriptVersionInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTVERSIONINFO };

	/** Return the version number of the scripting document object model (DOM) corresponding 
		to the current version of the application.
	*/
	virtual const ScriptVersion& GetCurrentScriptDOMVersion() const = 0 ;

	/** Return a list of known scripting DOM versions.
		@param client indicates the list should be confined to a specific client
	*/
	virtual ScriptVersionList GetKnownScriptDOMVersions( const ScriptClient& client = kInvalidClass ) const = 0 ;

	/** Get the version of the scripting DOM actually used to handle a particular request.
		For example, suppose a request specifies version 3.5 of the DOM, but the only known
		valid DOM versions are 3.0 and 4.0; 3.0 would be returned.
		@param context specifies the context of the request
	*/
	virtual const ScriptVersion& GetApplicableDOMVersion( const RequestContext& context ) const = 0 ;

	/** Get the UI string associated with a version of the scripting DOM
		@param context specifies the version of the DOM
	*/
	virtual PMString GetApplicableUIVersion( const RequestContext& context ) const = 0 ;

	/** Get the GUIDs associated with a version of the scripting DOM
		@param context specifies the version of the DOM
		@param appGUID if non-nil, returns the GUID of the application
		@param singleUserTypeLibGUID if non-nil, returns the GUID of the single-user type library
		@param multiUserTypeLibGUID if non-nil, returns the GUID of the multi-user type library
	*/
	virtual void GetApplicableGUIDs( const RequestContext& context, GUID* appGUID, GUID* singleUserTypeLibGUID = nil, GUID* multiUserTypeLibGUID = nil ) const = 0 ;

	/** Get the folder where a client should publish its description (e.g., AppleScript Dictionary, Visual Basic TypeLibrary)
		@param context specifies the version of the DOM to be published
		@param createFolder indicates whether this call should create the folder if it doesn't already exist
	*/
	virtual IDFile GetApplicableDescriptionFolder( const RequestContext& context, bool16 createFolder = kFalse ) const = 0 ;

	/**	Get the lowest DOM Version that can read files written by a given DOM Version
		@param the DOM version being used to generate INX
		@return the lowest DOM version that can read the generated INX
	*/
	virtual const ScriptVersion& GetMinimumINXImportDOMVersion( const RequestContext& context ) const = 0 ;
} ;

#endif	// __IScriptVersionInfo__
