//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IChromiumImportHelper.h $
//  
//  Owner: Ramnik Singh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IChromiumImportHelper__
#define __IChromiumImportHelper__

#include "IPMUnknown.h" 
#include "CSXSID.h"
#include <sstream> 

/**
A class deriving from IChromiumImportHelper interface gets invoked for importing incoming JSON data from CEP drag drop operations when the source attribute in the JSON data matches with the source attribute of that class.
*/
class IChromiumImportHelper :  public IPMUnknown
{
public:

    enum { kDefaultIID = IID_ICHROMIUMIMPORTHELPER } ;

	/**
	Whether the import helper supports the source attribute in JSON data or not. The import helper is ignored if it returns kFalse.
	@return kTrue if the import helper supports the source attribute in JSON data.
	*/
	virtual bool16 IsSupportingSourceAttributeInJsonData() = 0;

	/**
	Obtain the value of source attribute this import helper is interested in.
	@return A non-null string indicating the expected value of the source attribute that this import helper is interested in. The string is owned by the import helper.
	*/
	virtual const char* GetSourceAttribute() = 0;

	/**
	Import the incoming JSON data - only invoked if the import helper supports the source attribute and its source attribute matches the source attribute in the incoming JSON data.
	@param jsonDataStringStream is the incoming JSON data.
	@param uiFlags whether the import operation can show UI or not.
	*/
	virtual void ImportData(std::stringstream &jsonDataStringStream, UIFlags uiFlags) = 0;
};

#endif
