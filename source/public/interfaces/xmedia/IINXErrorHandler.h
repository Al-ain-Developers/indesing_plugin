//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IINXErrorHandler.h $
//  
//  Owner: Gang Xiao
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
#ifndef __IINXErrorHandler_h__
#define __IINXErrorHandler_h__

#include "IPMUnknown.h"
#include "IDOMElement.h"

class IScript;
class IScriptRequestData;
class ScriptReturnData;

/** Provides error information during INX operation for new IDML format.
	
	3rd party developer can implement this interface to receive error infromatiom from
	inx core. Please see SDK sample INXErrorLogging.sdk.vcproj for detail.
*/
class IINXErrorHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINXERRORHANDLER };

public:
	typedef enum
	{
		kINXContinue = 0,
		kINXCancel
	} INXErrorStatus;

	/**
		Reset the current INX error status to kINXContinue.
	*/
	virtual void ResetINXErrorStatus() = 0;

	/**
		Get the current INX error status. Set to kINXCancel in one of the 
		callbacks on this implementation to abort further processing.
		@return the current status
	*/
	virtual IINXErrorHandler::INXErrorStatus GetINXErrorStatus() const = 0;

	/**
		Begin export session.
		@param stream The stream export to.
		@param roots The list of element to be exported.
	*/
	virtual void BeginExport(const IPMStream * stream, const IDOMElement::ElementList &roots) = 0;

	/**
		End export session.
	*/
	virtual void EndExport() = 0;

	/**
		Begin import session.
		@param stream The stream import from.
	*/
	virtual void BeginImport(const IPMStream *stream) = 0;

	/**
		End import session.
	*/
	virtual void EndImport() = 0;

	/**
		Report an unknown element. Import only.
		@param parent The script id of unknown element.
		@param elem The name of unknown element
	*/
	virtual void UnknownElement(const ScriptID & parent, const WideString & elem) = 0;

	/**
		Report an unknown property on known object. Import only.
		@param parent The script id of known object.
		@param prop The name of unknown property
	*/
	virtual void UnknownProperty(const ScriptID & parent, const WideString & prop) = 0;

	/**
		Report an un-resolved reference. Import only.
		@param selfID The self ID of referenced object
	*/
	virtual void UnresolvedReference(const WideString & selfID) = 0;

	/**
		Report parser error. Import only.
		@param err The error code
		@param errorStr The error string
	*/
	virtual void ParserError(ErrorCode err, const PMString & errorStr) = 0;

	/**
		Report scripting error.
		@param script The object on which the scripting request was invoked
		@param scriptRequestData The event data for the scripting request
		@param returnData The return data for the scripting request that failed

		Following error codes are not considered as problem: kPropertyNotApplicableError, kCellStyleAttributeNotDefinedError, 
		kTableStyleAttributeNotDefinedError, kInvalidRequestForRootStyleError, kGraphicAttrNotSupportedError, 
		kImageInfoNotAvailableError, kObsoleteScriptingRequestError, kReadOnlyPropertyError, kGraphicAttrMixedSelectionError, 
		kDefaultKinsokuReadOnlyError, kDefaultMojikumiReadOnlyError
	*/
	virtual void ScriptingError(const IScript * script, const IScriptRequestData * scriptRequestData, const ScriptReturnData & returnData ) = 0;
};

#endif	// __IINXErrorHandler_h__
