//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IEnvironment.h $
//  
//  Owner: robin briggs
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
#ifndef __IENVIRONMENT__
#define __IENVIRONMENT__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IDataBase.h"

/** Interface containing information about system configuration
*/
class IEnvironment : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IENVIRONMENT };
	
	/** Get OS major version information
		@return major OS version number. i.e. on OS X 10.3.1 this will return 10
	*/
		virtual int32 GetMajorSystemVersion() const = 0;
	/** Get OS minor version information
		@return minor OS version number. i.e. on OS X 10.3.1 this will return 31
	*/
		virtual int32 GetMinorSystemVersion() const = 0;
		
	/** Get number of writing scripts supported by the OS
		@return count of supported writing scripts
	*/
		virtual int32 GetNumberOfScripts() const = 0;
					
	/** Get the byteswap order for the current platform
		@return platform's native byte order. Should be either IDataBase::kMotorolaOrder or IDataBase::kIntelOrder
	*/
		virtual IDataBase::ByteSwapOrder GetPlatformSwap() const = 0;
	
	/** Get the current OS level user setting for what character should be used for the decimal point. 
		This is typically '.' for US english, and often ',' for european users. If you're tempted to use this function
		please look first at IWidgetUtils::FormatUserDecimal() and IWidgetUtils::StripUserDecimal(), which probably does what you want already.
		@return a string consisting of the current decimal point as set by the user at the OS level.
	*/
		virtual PMString GetCurrentDecimalPt() const = 0;
	/** Get the current OS level user setting for what character should be used for the thousands character.
		This is typically ',' for US English users, and often '.' for European users.
		@return a string consisting of the current thousands seperator as set by the user at the OS level.
	*/
		virtual PMString GetCurrentThousandsSep() const = 0;	
		
	/** Get the current OS level user setting for the current user's login name.
		@return a string consisting of the user's name
	*/
		virtual PMString GetSystemUserName() const = 0;
		
	#ifdef WINDOWS 		
	/** Get our global HINSTANCE
		@return an HINSTANCE for this app
	*/
		virtual const HINSTANCE GetInstance() const = 0;

	/** Set the app window. Client code should not call this.
	*/
		virtual void SetAppWindow( HWND ) = 0;
		
	/** Get the id for the open files message. Client code should not call this. It's used internally to handle passing a document from one instance to another.
		@return an id associated with opening a file.
	*/
		virtual const uint32 GetOpenFilesMessageId() const = 0;
	#endif
	
};


#endif	// __IENVIRONMENT__
