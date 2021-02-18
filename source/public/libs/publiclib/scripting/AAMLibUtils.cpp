//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/AAMLibUtils.cpp $
//  
//  Owner: tspencer
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
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "AAMLibUtils.h"
#include "LocaleSetting.h"
#include "BuildNumber.h"
#include "LocaleIDConversionUtils.h"

//========================================================================================
//  GetPPSpecifier
//========================================================================================
PMString AAMLibUtils::GetPPSpecifier( const PMLocaleId& idLocale ) 
{
    PMString ppSpecifier; 
	
	switch ( idLocale.GetProductFS() )
	{
	case (int16)kInDesignProductFS:	
		ppSpecifier = "indesign";
		break;
	case (int16)kInCopyProductFS:	
		ppSpecifier = "incopy";
		break;
	default:						
		ASSERT_FAIL( "Unknown product feature set" );
        ppSpecifier = "unknown";
		break;
	}

    // The version number string is of the format 9.0 for full release and 9.0.x for dot release.
    PMString versionStr(kXPEPSpecifierVersionNumberStr, PMString::kUnknownEncoding);
    
    ppSpecifier.AppendW(kTextChar_HyphenMinus);
    ppSpecifier.Append(versionStr);
    
#if defined(WINDOWS) && !defined(_WIN64)
    ppSpecifier.AppendNumber(32);
#else
    ppSpecifier.AppendNumber(64);
#endif
	return ppSpecifier; // returns string of format "indesign-9.032"/"incopy-9.032"

}

//========================================================================================
//  GetLocale
//========================================================================================
PMString AAMLibUtils::GetLocale()
{ 
   PMString localeString(LocaleIDConversionUtils::GetFullEnumString(LocaleSetting::GetLocale())); // enUS 
   localeString.InsertW(kTextChar_Underscore, 2); // en_US 
     
   localeString.SetTranslatable(kFalse); 
   return localeString; 
} 
