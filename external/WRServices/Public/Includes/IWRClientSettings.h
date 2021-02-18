//========================================================================================
//  
//  File: IWRClinetSettings.h
//  
//  Owner: Stéphane BOEUF
//  
//  Copyright 2007 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================
#ifndef __IWRCLIENTSETTINGS__
#define __IWRCLIENTSETTINGS__

#include "WRFontContextComponent.h"
#include "WRAttributes.h"

/// Interface to retrieve session-wide client settings
/** 
	This class is used as a relay to allow communication between WRServices and the client.
	Tags are defined in WRAttributes.h. It works in the same way as the StyleClientControl::GetAttribute
	but it can be called outside the context of a shaping and therefore is suitable to pass
	session-wide settings, such as the font fallback method or whether specific script are enabled or not.
	Not implementing this interface or not responding to some tags should give a normal default behavior
	( all scripts are enabled, complementary font is allowed, by-script fallback is disabled)
*/
class IWRClientSettings : public WRFontContextComponent
{
public :
	/**
		Query the client for a specific session-wide setting
		@param owner a WRTag defining the category; can be kWROwnerTag_All (all responder must be called, no break after the first answer)
		@param attr a WRTag specifying the requested info
		@param data a memory block, can be NULL to get the buffer size if unknown or variable
		@param len an WRInt32, the length of data
		@return a WRInt32, 0 is not handled, otherwise the number of byte written in data (or that would be written in data if data is NULL)
	*/
	virtual WRInt32 GetSettings(WRTag owner, WRTag attr, void* data, WRInt32 len) = 0 ;
} ;

#endif
