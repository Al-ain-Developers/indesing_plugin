//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/files/LocaleIndex.cpp $
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

#include "VCPublicHeaders.h"

#include "LocaleIndex.h"


//========================================================================================
// METHODS LocaleIndex
//========================================================================================

bool16 LocaleIndex::HasRsrcForLocale(const PMLocaleId& localeId) const
{
	return GetRsrcIdForLocale(localeId) ? kTrue : kFalse;
}

RsrcID LocaleIndex::GetRsrcIdForLocale(const PMLocaleId& localeId) const
{
	// ----- If there is not an exact match on feature set locale and user interface locale, then
	//		 we look for matches where either feature set or user interface locale or both can be
	//		 wild carded. Feature set wild card takes precedence over user interface wild card and
	//		 user interface takes precedence over both being wild carded. [amb 3/23/00]
	
	// ----- Changed to support additional wild cards for product and language feature sets. [jpugh 6/12/02]
	
	RsrcID rsrc[7] = {0,0,0,0,0,0,0};
	
	TRACEFLOW("Localization","LocaleIndex::GetRsrcIdForLocale has %d entries. Looking for a match for FS %d, UI %d\n",fLength.Get(),localeId.GetLanguageFS(),localeId.GetUserInterfaceId());

	for (int32 i = 0; i < fLength; i++)
	{
		PMLocaleId fromTableId = fIndexEntry[i].fLocaleId;
		TRACEFLOW("Localization","Table entry %d is FS %d, UI %d\n",i,fromTableId.GetLanguageFS(),fromTableId.GetUserInterfaceId());

		//-----
		// Make sure that a locale id is not being used as a feature set id
		// and vice versa...
		ASSERT_MSG((fromTableId.GetFeatureSetId() & 0xFF00) != 0,
		           "LocaleIndex::GetRsrcIdForLocale() - Loading resource that has a LocaleID used as a Feature Set ID");
		ASSERT_MSG((fromTableId.GetUserInterfaceId() & 0xFF00) == 0,           
					"LocaleIndex::GetRsrcIdForLocale() - Loading resource that has a Feature Set ID used as a Locale ID");
		
		// this is the preferred order these resources should be used in
		if (fromTableId == localeId)													// kInDesignRomanFS, k_enUS
		{
			TRACEFLOW("Localization","Got locale index match on both exact feature set and exact UI\n");
			return fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetProductFS() == (int16)kAllProductsFS && 
				 fromTableId.GetLanguageFS() == localeId.GetLanguageFS() &&
				 fromTableId.GetUserInterfaceId() == localeId.GetUserInterfaceId())		// kAllProductsRomanFS, k_enUS
		{
			TRACEFLOW("Localization","Got locale index match on partial feature set(i.e. kAllProductsRomanFS) and exact UI\n");
			rsrc[0] = fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetProductFS() == localeId.GetProductFS() && 
				 fromTableId.IsLanguageFS(localeId.GetLanguageFS()) &&
				 fromTableId.GetUserInterfaceId() == localeId.GetUserInterfaceId())		// kInDesignAllLanguagesFS, k_enUS
		{
			TRACEFLOW("Localization","Got locale index match on product feature set(i.e. kInDesignAllLanguagesFS) and exact UI\n");
			rsrc[1] = fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetFeatureSetId() == (int16) kWildFS && 
				 fromTableId.GetUserInterfaceId() == localeId.GetUserInterfaceId())		// kWildFS, k_enUS
		{
			TRACEFLOW("Localization","Got locale index match on wild feature set and exact UI\n");
			rsrc[2] = fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetFeatureSetId() == localeId.GetFeatureSetId() && 
				 fromTableId.GetUserInterfaceId() == (int16) k_Wild)					// kInDesignJapaneseFS, k_Wild
		{
			TRACEFLOW("Localization","Got locale index match on wild feature set language(i.e. kInDesignJapaneseFS) and wild UI\n");
			rsrc[3] = fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetProductFS() == (int16)kAllProductsFS && 
				 fromTableId.GetLanguageFS() == localeId.GetLanguageFS() &&
				 fromTableId.GetUserInterfaceId() == (int16) k_Wild)					// kAllProductsRomanFS, k_Wild
		{
			TRACEFLOW("Localization","Got locale index match on wild product feature set (i.e. kAllProductsRomanFS) and wild UI\n");
			rsrc[4] = fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetProductFS() == localeId.GetProductFS() && 
				 fromTableId.IsLanguageFS(localeId.GetLanguageFS()) &&
				 fromTableId.GetUserInterfaceId() == (int16) k_Wild)					// kInDesignAllLanguagesFS, k_Wild
		{
			TRACEFLOW("Localization","Got locale index match on wild feature set language(i.e. kInDesignAllLanguagesFS) and wild UI\n");
			rsrc[5] = fIndexEntry[i].fRsrcId;
		}
		else if (fromTableId.GetFeatureSetId() == (int16) kWildFS && 
				 fromTableId.GetUserInterfaceId() == (int16) k_Wild)					// kWildFS, k_Wild
		{
			TRACEFLOW("Localization","Got locale index match on wild feature set and wild UI(worst match possible)\n");
			rsrc[6] = fIndexEntry[i].fRsrcId;
		}
	}

	// return the first (i.e. best) resource id
	for (int32 j = 0; j < 7; j++)
	{
		if (rsrc[j] != 0)
			return rsrc[j];
	}
	return 0;
}




