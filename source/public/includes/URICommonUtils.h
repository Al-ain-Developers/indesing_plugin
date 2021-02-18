//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/URICommonUtils.h $
//  
//  Owner: Sanyam Jain
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
//  Copyright 2016 Adobe 
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
#ifndef __PrivateURIUtils_h__
#define __PrivateURIUtils_h__

#ifdef PUBLIC_BUILD
	#pragma export on
#endif

#include "WideString.h"

//========================================================================================
// CLASS URICommonUtils
//========================================================================================

/**
Utility functions to operate on URI's
*/
class PUBLIC_DECL URICommonUtils
{
public:

	/**
	Converts a WideString to a URI encoded string. The string 'overrideChars', if not null, contains a list of characters that should not be encoded.
	*/
	static void WideStringToURIEncoding(const WideString& wideStr, const char* overrideChars, std::string& encodedStr);

	/**
	Converts a URI encoded string to a WideString. 
	*/
	static void URIEncodingToWideString(const std::string& encodedStr, WideString& wideStr);

	/**
	Given a URI encoded WideString, converts it to a string. Returns false and empty string in stdStr if the conversion failed.
	*/
	static bool WideStringToStdString(const WideString& wideStr, std::string& stdStr);

	/**
	Appends the character 'ch' into 'encodedStr' after URI encoding it. The string 'overrideChars', if not null, contains a list of characters that should not be encoded.
	*/
	static void PutURIChar(const uchar& ch, const char* overrideChars, std::string& encodedStr);

	/**
	URI decodes the characters starting at index 'idx' in 'encodedStr' and returns it in parameter 'ch'. The index 'idx' is appropriately adjusted.
	Returns 0 in parameter 'ch' if input index is out of string bounds. 
	*/
	static void GetURIChar(const std::string& encodedStr, uint32& idx, uint32& ch);
};

#pragma export off

#endif
