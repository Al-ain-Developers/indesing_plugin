//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WLocaleSetting.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __WLocaleSetting_h__
#define __WLocaleSetting_h__

#include "PMLocaleId.h"

/** Provides the windows implementation for getting the current Locale setting for the application.
*/
class PUBLIC_DECL WLocaleSetting
{
public:
	/** Get the current locale setting. This encapsulates UI language, Feature set language, and application feature set. 
		@see PMLocaleIds.h and @see PMLocaleId.h
		@return the current locale
	*/
	static PMLocaleId	GetLocale();

	/** Get the locale setting that seems most appropriate for the user's OS. Mostly useful for determining if the user is on a non-Roman OS.
		@see PMLocaleIds.h and @see PMLocaleId.h
		@return locale that best matches the OS
	*/
	static PMLocaleId	GetSystemLocale();

	/** Get the cooltype script that best matches the system script of the OS.
		@return script that best matches OS. Return values are kCT*Script.
	*/
	static int16			GetSystemScript();
	
	/** Internal use only.
	*/
	static void			SetLocale(const PMLocaleId& locale);

private:
	static PMLocaleId	LookupCountryID(LCID WindowsLocaleId);
	static HKEY			GetAppKey(const PMLocaleId locale);

	static int32		ts_SystemScript;
	
	static bool16		ts_LocaleCacheValid;
	static PMLocaleId	ts_LocaleCacheContent;
};

#endif __WLocaleSetting_h__
