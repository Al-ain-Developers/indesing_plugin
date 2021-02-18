//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLServicesError.h $
//  
//  Owner: Robin Briggs
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
#ifndef __IXMLServicesError_h__
#define __IXMLServicesError_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

/** Class responsible storing the error state of an XML parse or transformation.
*/
class IXMLServicesError : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLSERVICESERROR };

	/**	Mutator for the error code associated with given parse. Look in XMLID.h for a list
		of these below "Error ID". The AXE XML parser returns a list of potential errors which get
		mapped to errors in the InDesign world.

		Setting an error code that's not kSuccess will cause the parser to abort.
		Call ClearAbort() is you don't want to abort the parsing.

		@param errCode 
	 */
	virtual void SetErrorCode(ErrorCode errCode) = 0;

	/**	Mutator for the error tag. If a error should occur while parsing the file the content handler should set the error
		code and return.  ParseStream will check for an error condition between each parseable
		element and signal an error if one occurs.  The error tag is the tag of the element being
		parsed when the error occurred.

		@param errorTag new value to set
	 */
	virtual void SetErrorTag(const PMString& errorTag) = 0;
	

	/**	Accessor for the error code associated with given parse
		
		@return ErrorCode specifying the error condition
	 */
	virtual ErrorCode GetErrorCode() const = 0;

	/**	Accessor for error tag. 
		
		@return PMString containing the error tag
	 */
	virtual PMString GetErrorTag() const = 0;

	/**	Signals the parser or the transformer to abort on the next element. 
	 */
	virtual void SignalAbort() = 0;
	
	/**	Resets the abort state of the parser or transformer. 
	 */
	virtual void ClearAbort() = 0;
	
	/**	Indicates that an abort has been signaled. 
	 */
	virtual bool16 ShouldAbort() const = 0;
};

#endif	// __IXMLServicesError_h__
