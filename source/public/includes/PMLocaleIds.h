//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMLocaleIds.h $
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
#ifndef __PMLocaleIds_h__
#define __PMLocaleIds_h__

#include "FeatureSets.h"
// ----- Feature Set

/*
#define k_FeatureSet_enUS		k_enUS
#define k_FeatureSet_enGB		k_enGB
#define k_FeatureSet_deDE		k_deDE
#define k_FeatureSet_frFR		k_frFR
#define k_FeatureSet_jaJP		k_jaJP
#define k_FeatureSet_esES		k_esES
#define k_FeatureSet_ptBR		k_ptBR
#define k_FeatureSet_svSE		k_svSE
#define k_FeatureSet_daDK		k_daDK
#define k_FeatureSet_nlNL		k_nlNL
#define k_FeatureSet_itIT		k_itIT
#define k_FeatureSet_nbNO		k_nbNO
#define k_FeatureSet_fiFI		k_fiFI
#define k_FeatureSet_Wild		k_Wild
*/

#define k_enUS				0x0001
#define k_enGB				0x0002
#define k_deDE				0x0003
#define k_frFR				0x0004
#define k_jaJP				0x0005
#define k_esES				0x0006
#define k_ptBR				0x0007
#define k_svSE				0x0008
#define k_daDK				0x0009
#define k_nlNL				0x000a
#define k_itIT				0x000b
#define k_nbNO				0x000c
#define k_fiFI				0x000d
#define k_elGR				0x000e	//Greek
#define k_csCZ				0x000f	//Czech
#define k_plPL				0x0010	//Polish
#define k_hrHR				0x0011	//Croatian
#define k_huHU				0x0012	//Hungarian
#define k_ruRU				0x0013	//Russian
#define k_skSK				0x0014	//Slovak
#define k_sqAL				0x0015	//Albanian
#define k_trTR				0x0016	//Turkish
#define k_roRO				0x0017	//Romanian
#define k_bgBG				0x0018	//Bulgarian
#define k_beBY				0x0019	//Belarussian
#define k_etEE				0x001a	//Estonian
#define k_lvLV				0x001b	//Latvian
#define k_ltLT				0x001c	//Lithuanian
#define k_slSI				0x001d	//Slovenian
#define k_ukUA				0x001e	//Ukrainian
#define k_heIL				0x001f	//Hebrew
#define k_arAE				0x0020	//Arabic
#define k_zhCN				0x0021	// Chinese Simplified
#define k_zhTW				0x0022	// Chinese Traditional
#define k_koKR				0x0023	// Korean
#define k_taIN				0x0024	// Tamil
#define k_thTH				0x0025	// Thai
#define k_viVN				0x0026	// Vietnamese
#define k_enAE				0x0027	// English UI Arabic prefs
#define k_enIL				0x0028	// English UI Hebrew prefs

#define k_Wild				0x00FE

// NOTE: If you add more locales here, make sure and also add them to the following places:
// InstallLanguagesCmd::Do() in LanguageCmd.cpp,
// DictEditorMenuComponent::QueryCurrentLanguage() in DictEditorMenuComponent.cpp,
// DictPrefsMenuComponent::QueryCurrentLanguage() in DictPrefsMenuComponent.cpp,
// and possibly XFLT_TEXT_IMP_SSFLT::SendLangID() in ssflt.cpp.

// ----- Character encoding converters are specified in the string table resources and
//		 are usually just the class ID of the service that provides the converter. But here
//		 we want to conditionally provide different converters depending on the platform.

#ifdef MACINTOSH
	#define kEuropeanWinToMacEncodingConverter kEuropeanEncodingWinToMacBoss
	#define kEuropeanMacToWinEncodingConverter 0
#elif defined WINDOWS
	#define kEuropeanMacToWinEncodingConverter kEuropeanEncodingMacToWinBoss
	#define kEuropeanWinToMacEncodingConverter 0
#endif



// ----- Locale offsets
// These signify resource IDs that must be unique to a given featureset and locale combination.

#define index_enUS				0x0001
#define index_enGB				0x0002
#define index_deDE				0x0003
#define index_frFR				0x0004
#define index_jaJP				0x0005	// Japanese featureset, Japanese locale
#define index_esES				0x0006
#define index_ptBR				0x0007
#define index_svSE				0x0008
#define index_daDK				0x0009
#define index_nlNL				0x000a
#define index_itIT				0x000b
#define index_nbNO				0x000c
#define index_fiFI				0x000d
#define index_jaJP_enUS			0x000e	// Japanese featureset, English locale
#define index_koKR				0x000f	// Japanese featureset, Korean locale
#define index_zhCN				0x0010	// Japanese featureset, Simplified Chinese locale
#define index_zhTW				0x0011	// Japanese featureset, Traditional Chinese locale

#define index_elGR		        0x0012 // was - 0x000e
#define index_csCZ				0x0013 // was - 0x000f
#define index_plPL				0x0014 // was - 0x0010
#define index_hrHR				0x0015 // was - 0x0011
#define index_huHU				0x0016 // was - 0x0012
#define index_ruRU				0x0017 // was - 0x0013
#define index_skSK				0x0018 // was - 0x0014
//#define index_k_el            0x0019 // was - 0x0015
#define index_trTR				0x001a // was - 0x0016
#define index_roRO				0x001b // was - 0x0017
#define index_bgBG				0x001c // was - 0x0018
#define index_beBY				0x001d // was - 0x0019
#define index_etEE				0x001e // was - 0x001a
#define index_lvLV				0x001f // was - 0x001b
#define index_ltLT				0x0020 // was - 0x001c
#define index_slSI				0x0021 // was - 0x001d
#define index_ukUA				0x0022 // was - 0x001e
#define index_heIL				0x0023 // was - 0x001f
#define index_arAE				0x0024 // was - 0x0020

// ----- Product based offsets for feature set interface combinations.  Note that using
//		 none of these is the same as specifying AllProducts (which is the normal situation).
//		 [jon 6/20/02]

#define index_AllProductsFS		0x0000
#define index_InDesignFS		0x0050
#define index_InCopyFS			0x0100
#define index_InDesignServerFS	0x0150


// ----- Character encoding converters are specified in the string table resources

//MAC is #define kEuropeanWinToMacEncodingConverter kEuropeanEncodingWinToMacBoss
//WIN is #define kEuropeanMacToWinEncodingConverter kEuropeanEncodingMacToWinBoss
#define kResourceUTF8Encoded 8

#endif // __PMLocaleIds_h__

