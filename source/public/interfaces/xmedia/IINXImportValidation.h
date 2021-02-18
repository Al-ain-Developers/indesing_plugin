//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IINXImportValidation.h $
//  
//  Owner: Steve Pellegrin
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
//  Used to extract XML from an object, or generate an object instance from XML data.
//  
//========================================================================================

#pragma once
#ifndef __IINXImportValidation_h__
#define __IINXImportValidation_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "ScriptInfo.h"

// ----- ID.h files -----

#include "INXCoreID.h"

// ----- Forward references -----
class WideString;


/**
   Allows a client to validate that an INX file can be imported.
   IINXImportValidation methods are called at various points during INX validation and are used to override default behavior.
 */
class IINXImportValidation : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINXIMPORTVALIDATION };

public:
/**
	Called to validate the file type.
	@param The INX type as a string.
	@return kSuccess if validation should continue. Otherwise, an error code.
*/
	virtual ErrorCode ValidateINXType(const WideString &type) = 0;

/**
	Called to validate the DOM version.
	@param The INX file's DOM version.
	@return kSuccess if validation should continue. Otherwise, an error code.
*/
	virtual ErrorCode ValidateDOMVersion(const ScriptInfo::ScriptVersion &version) = 0;

/**
	Called to validate the Build number.
	NOTE: Production files do not contain build number information.
	Therefore, this method will only be called for pre-release files.
	@param The INX file's build number.
	@return kSuccess if validation should continue. Otherwise, an error code.
*/
	virtual ErrorCode ValidateBuildNumber(int32 buildNumber) = 0;

/**
	Called to validate PIs found before the first element.
	@param The PI target string.
	@param The PI data (probably a series of name-value pairs).
	@return kSuccess if validation should continue. Otherwise, an error code.
*/
	virtual ErrorCode ValidatePI(const WideString &target, const WideString &data) = 0;
};

#endif	// __IINXImportValidation_h__
