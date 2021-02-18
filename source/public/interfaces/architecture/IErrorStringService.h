//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IErrorStringService.h $
//  
//  Owner: jargast
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
#ifndef __IErrorStringService__
#define __IErrorStringService__


#include "IPMUnknown.h"
#include "PMString.h"

/** Interface which translates error codes based on the developer prefix of a plugin
	into error strings (and for later versions a detailed error description).
	
	This class is the hook for any plug-in that wishes to have a resource-based mapping
	between error codes and error strings.
	
	Here's how you would set up the mapping. First, define a boss in your plug-in that
	provides an error string service, for instance:

	<pre>
Class
{
	kFooErrorStringServiceBoss,
	kInvalidClass,
	{
		IID_IK2SERVICEPROVIDER, kErrorStringProviderImpl,
		IID_IERRORSTRINGSERVICE, kFooErrorStringServiceImpl,
	}
}
	</pre>
	
	Then you need to provide an implementation of the error string service interface.
	Here's an example of what that might look like:

	<pre>
#include "CErrorStringService.h"

class FooErrorStringService : public CErrorStringService
{
public:
	FooErrorStringService(IPMUnknown * boss) :
	: CErrorStringService(boss, kFooPluginID, kFooErrorStringTableRsrcID)
};

CREATE_PMINTERFACE(FooErrorStringService, kFooErrorStringServiceImpl)
	</pre>

	Then you need to define the error codes that you want to map to error strings
	in your ID.h file. For instance:
<pre>
DECLARE_PMID(kErrorIDSpace, kFooAwfulHorribleError, kFooPrefix + xx)
DECLARE_PMID(kErrorIDSpace, kFooEvenWorseError, kFooPrefix + xx)
</pre>

	Lastly, you need to have a UserErrorTable resource that provides the
	mapping between an error code and its associated string:

	<pre>
resource UserErrorTable( kFooErrorStringTableRsrcID ) 
{
	{ 
		// err 						// error string
		kFooAwfulHorribleError, "Oh No! Something awful has happened!",
		kFooEvenWorseError, "Oh Dear! Please don't do that",
	}
};
	</pre>

	Note that the string provided in the UserErrorTable is not localized.
	To localize it, you can provide a localization in the localized string 
	files, then it will be automatically translated for the current language.
	
	Once you've done all this, then when you set the error code (see ErrorUtils::PMSetGlobalErrorCode), 
	you can skip passing a string along, but when you (or anyone else) later request the
	string, it will be there. The advantage to this is if you set the error code
	the same way in multiple places, you insure that the error string will be
	the same no matter where it gets set from.
	
	@ingroup arch_error
	@see IK2ServiceProvider, CErrorStringService, ErrorUtils
*/
class IErrorStringService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IERRORSTRINGSERVICE };

	/** See if the service provider has a string for errCode.
		When searching for an error string, the application may iterate over all
		the services asking for a string.  A quick check to see if it is even 
		your prefix is advised.  It could be that it is your error, yet you don't
		have a string for it, then return kFalse.
		@param errCode the error code we're looking up
		@param errInfo whatever errInfo is currently in the error state
		@return kTrue if the service supplies a string for errCode, kFalse otherwise
	*/
	virtual bool16 HasUserErrorString (ErrorCode errCode, IPMUnknown* errInfo) const = 0;
	
	/** Return the string associated with the error code.  If there isn't one
		return an empty string.
		@param errCode the error code we're looking up
		@param errInfo whatever errInfo is currently in the error state
		@return PMString the user string for errCode, kFalse otherwise
	*/
	virtual PMString GetUserErrorString (ErrorCode errCode, IPMUnknown* errInfo) const = 0;

#if 0	
	/** Not currently supported - for future use. 
		See if the service has a detailed error description for the corresponding errorcode.
		When searching for an error description, the application may iterate over all
		the services asking for a string.  A quick check to see if it is even 
		your prefix is advised.  It could be that it is your error, yet you don't
		have a string for it, then return kFalse.
		@param errCode the error code we're looking up
		@param errInfo whatever errInfo is currently in the error state
		@return kTrue if the service has a detailed error description for the corresponding errorcode.
	*/
	virtual bool16 HasUserErrorDescription (ErrorCode errCode, IPMUnknown* errInfo) const = 0;
	
	/** Not currently supported - for future use. 
		Return the detailed description associated with the error code.  If there isn't one
		return an empty string.
		@param errCode the error code we're looking up
		@param errInfo whatever errInfo is currently in the error state
		@return PMString the user description for errCode, kFalse otherwise
	*/
	virtual PMString GetUserErrorDescription (ErrorCode errCode, IPMUnknown* errInfo) const = 0;	
#endif
};

#endif
