//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MLocaleSetting.h $
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
#ifndef __MLocaleSetting_h__
#define __MLocaleSetting_h__

#include "PMLocaleId.h"

#ifdef PUBLIC_BUILD
//#pragma export on
#endif

/** Provides the macintosh implementation for getting the current Locale setting for the application.
*/
class PUBLIC_DECL MLocaleSetting
{
public:
	MLocaleSetting();

	/** Get the current locale setting. This encapsulates UI language, Feature set language, and application feature set. 
		@see PMLocaleIds.h and @see PMLocaleId.h
		@return the current locale
	*/
	static PMLocaleId		GetLocale();
	
	/** Get the locale setting that seems most appropriate for the user's OS. Mostly useful for determining if the user is on a non-Roman OS.
		@see PMLocaleIds.h and @see PMLocaleId.h
		@return locale that best matches the OS
	*/
	static PMLocaleId		GetSystemLocale();

	/** Get the cooltype script that best matches the system script of the OS.
		@return script that best matches OS. Return values are kCT*Script.
	*/
	static int16			GetSystemScript();

	/** Internal use only
	*/
	static void				SetLocale(const PMLocaleId& locale);

private:
	static PMLocaleId		scriptLookup(int script);
    static bool16           ReadPreferenceFile(const PMLocaleId& locale, int32& outFeatureSet);
    static bool16           GetPreference(const PMLocaleId& locale, PMLocaleId& newLocale);
    static bool16           GetPreferenceFileName(const PMLocaleId& locale, PMString& outStrPrefFileName);
    
private:
	bool16					fInitialized;
	PMLocaleId				fLocale;
	int32					fSystemScript;
	
	static void				Initialize();
};

//#pragma export off

#endif //__MLocaleSetting_h__
