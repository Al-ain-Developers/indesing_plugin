//========================================================================================
//  
//  File: WRLanguageID.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2011 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRLanguageID__
#define __WRLanguageID__

/*
	 Language IDs are combinations of a primary and a sublanguage id.
	The first 8 bits of a LanugageID (0-7) are reserved for the primary language id.
	The last  8 bits of a LanugageID (8-15) are reserved for the sublanguage id.
	The macros MakeLanguageID, GetPrimaryLanguageID and GetSubLanguageID provide creation
	and extraction.
	Notice that there are three special constants: kLanguageNeutral, kLanguageSystemDefault and 
	kLanguageUserDefault.
*/

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

#ifndef kLanguageNeutral
// Primary language IDs:
#define kLanguageNeutral					 0

#define kLanguageArabic 				1
#define kLanguageAfrikaans				2
#define kLanguageAlbanian				3
#define kLanguageBasque 				4
#define kLanguageBulgarian				5
#define kLanguageByeloRussian			6
#define kLanguageCatalan				7
#define kLanguageChinese				8
#define kLanguageCroatian				9
#define kLanguageCzech					10
#define kLanguageDanish 				11
#define kLanguageDutch					12
#define kLanguageEnglish				13
#define kLanguageEstonian				14
#define kLanguageFaeroese				15
#define kLanguageFarsi					16
#define kLanguageFinnish				17
#define kLanguageFrench 				18
#define kLanguageGerman 				19
#define kLanguageGreek					20
#define kLanguageHebrew 				21
#define kLanguageHungarian				22
#define kLanguageIcelandic				23
#define kLanguageIndonesian 			24
#define kLanguageItalian				25
#define kLanguageJapanese				26
#define kLanguageKorean 				27
#define kLanguageLatvian				28
#define kLanguageLithuanian 			29
#define kLanguageNorwegian				30
#define kLanguagePolish 				31
#define kLanguagePortuguese 			32
#define kLanguageRomanian				33
#define kLanguageRussian				34
#define kLanguageSlovak 				35
#define kLanguageSlovenian				36
#define kLanguageSorbian				37
#define kLanguageSerbian				kLanguageSorbian
#define kLanguageSpanish				38
#define kLanguageSwedish				39
#define kLanguageThai					40
#define kLanguageTurkish				41
#define kLanguageUkrainian				42
#define kLanguageHindi					43
#define kLanguageSanskrit				44
#define kLanguageMarathi				45
#define kLanguageNepali					46
#define kLanguageKashmiri				47
#define kLanguageKonkani				48
#define kLanguageSindhi					49
#define kLanguageBengali				50
#define kLanguageAssamese				51
#define kLanguageManipuri				52
#define kLanguagePunjabi				53
#define kLanguageGujarati				54
#define kLanguageOriya					55
#define kLanguageTamil					56
#define kLanguageTelugu					57
#define kLanguageKannada				58
#define kLanguageMalayalam				59
#define kLanguageSyriac					60
#define kLanguageDhivehi				61
#define kLanguageUrdu					62
#define kLanguageGeez					63
#define	kLanguageVietnamese				64
#define kLanguageLao					65
#define kLanguageKhmer					66
#define kLanguagePashto					67
#define kLanguageArmenian				68
#define kLanguageCherokee				69
#define kLanguageSorbianWendish			70
#define kLanguageMacedonian				71
#define kLanguageTibetan				72
#define kLanguageUyghur					73
#define kLanguageBurmese				74
#define kLanguageMongolian				75
#define kLanguageSinhala				76
#define kLanguageYiddish				77
// parallel tables in OptycaFontOT
#define kLanguageLast					 77 // Last language in the list.

// 
#define kSubLanguageNeutral 				 0	 /* language Neutral */
#define kSubLanguageDefault 				 1	 /* user Default */
#define kSubLanguageSystemDefault			 2	 /* system Default */

// Arabic sub languages
#define kSubLanguageArabic				1	 /* Arabic (Saudi Arabia) */
#define kSubLanguageArabicIraq			2	/* Arabic (Iraq) */
#define kSubLanguageArabicEgypt 			3	/* Arabic (Egypt) */
#define kSubLanguageArabicLibya 			4	/* Arabic (Libya) */
#define kSubLanguageArabicAlgeria			5	/* Arabic (Algeria) */
#define kSubLanguageArabicMorocco			6	/* Arabic (Morocco) */
#define kSubLanguageArabicTunisia			7	/* Arabic (Tunisia) */
#define kSubLanguageArabicOman			8	/* Arabic (Oman) */
#define kSubLanguageArabicYemen 			9	/* Arabic (Yemen) */
#define kSubLanguageArabicSyria 			10	/* Arabic (Syria) */
#define kSubLanguageArabicJordan			11	/* Arabic (Jordan) */
#define kSubLanguageArabicLebanon			12	/* Arabic (Lebanon) */
#define kSubLanguageArabicKuwait			13	/* Arabic (Kuwait) */
#define kSubLanguageArabicUAE			14	/* Arabic (United Arab Emirates) */
#define kSubLanguageArabicBahrain			15	/* Arabic (Bahrain) */
#define kSubLanguageArabicQatar 			16	/* Arabic (Qatar) */
#define kSubLanguageArabicLast	 			16

// Chinese sub languages
#define kSubLanguageChineseTraditional		1	/* Chinese (Taiwan) */
#define kSubLanguageChineseSimplified		2	/* Chinese (PR China) */
#define kSubLanguageChineseHongKong 		3	/* Chinese (Hong Kong) */
#define kSubLanguageChineseSingapore		4	/* Chinese (Singapore) */
#define kSubLanguageChineseLast				4

// Dutch sub languages
#define kSubLanguageDutch				 1	 /* Dutch */
#define kSubLanguageDutchBelgian			 2	 /* Dutch (Belgian) */
#define kSubLanguageDutchLast				 2

// English sub languages
#define kSubLanguageEnglishUS				1	/* English (USA) */
#define kSubLanguageEnglishUK				2	/* English (UK) */
#define kSubLanguageEnglishAustralian		3	/* English (Australian) */
#define kSubLanguageEnglishCanadian 		4	/* English (Canadian) */
#define kSubLanguageEnglishNewZealand		5	/* English (New Zealand) */
#define kSubLanguageEnglishEire			6	/* English (Irish) */
#define kSubLanguageEnglishSouthAfrica		7	/* English (South Africa) */
#define kSubLanguageEnglishJamaica			8	/* English (Jamaica) */
#define kSubLanguageEnglishCarribean		9	/* English (Carribean) */
#define kSubLanguageEnglishLast				9

// French sub languages
#define kSubLanguageFrench				 1	 /* French */
#define kSubLanguageFrenchBelgian			 2	 /* French (Belgian) */
#define kSubLanguageFrenchCanadian			 3	 /* French (Canadian) */
#define kSubLanguageFrenchSwiss 			 4	 /* French (Swiss) */
#define kSubLanguageFrenchLuxembourg		 5	 /* French (Luxembourg) */
#define kSubLanguageFrenchLast				 5

// German sub languages
#define kSubLanguageGerman				 1	 /* German */
#define kSubLanguageGermanSwiss 			 2	 /* German (Swiss) */
#define kSubLanguageGermanAustrian		 3	 /* German (Austrian) */
#define kSubLanguageGermanLuxembourg		 4	 /* German (Luxembourg) */
#define kSubLanguageGermanLiechtenstein 	 5	 /* German (Liechtenstein) */
#define kSubLanguageGermanLast			 	 5

// Italian sub languages
#define kSubLanguageItalian 				 1	 /* Italian */
#define kSubLanguageItalianSwiss			 2	 /* Italian (Swiss) */
#define kSubLanguageItalianLast				 2

// Korean sub languages
#define kSubLanguageKorean				 1	 /* Korean */
#define kSubLanguageKoreanJohab 			 2	 /* Korean (Johab) */
#define kSubLanguageKoreanLast	 			 2

// Norwegian sub languages
#define kSubLanguageNorwegianBokmal 		 1	 /* Norwegian (Bokmal) */
#define kSubLanguageNorwegianNynorsk		 2	 /* Norwegian (Nynorsk) */
#define kSubLanguageNorwegianLast			 2

// Portuguese sub languages
#define kSubLanguagePortuguese			 1	 /* Portuguese */
#define kSubLanguagePortugueseBrazilian 	 	 2	 /* Portuguese (Brazilian) */
#define kSubLanguagePortugueseLast		 	 	 2

// Spanish sub languages
#define kSubLanguageSpanish 				1	 /* Spanish (Castilian) */
#define kSubLanguageSpanishMexican		2	/* Spanish (Mexican) */
#define kSubLanguageSpanishModern			3	/* Spanish (Modern) */
#define kSubLanguageSpanishGuatemala		4	/* Spanish (Guatemala) */
#define kSubLanguageSpanishCostaRica		5	/* Spanish (Costa Rica) */
#define kSubLanguageSpanishPanama			6	/* Spanish (Panama) */
#define kSubLanguageSpanishDominican		7	/* Spanish (Dominican Republic) */
#define kSubLanguageSpanishVenezuela		8	/* Spanish (Venezuela) */
#define kSubLanguageSpanishColombia 		9	/* Spanish (Colombia) */
#define kSubLanguageSpanishPeru 			10	/* Spanish (Peru) */
#define kSubLanguageSpanishArgentina		11	/* Spanish (Argentina) */
#define kSubLanguageSpanishEcuador			12	/* Spanish (Ecuador) */
#define kSubLanguageSpanishChile			13	/* Spanish (Chile) */
#define kSubLanguageSpanishUruguay		14	/* Spanish (Uruguay) */
#define kSubLanguageSpanishParaguay 		15	/* Spanish (Paraguay) */
#define kSubLanguageSpanishBolivia			16	/* Spanish (Bolivia) */
#define kSubLanguageSpanishLast				16

//Serbian sub languages
#define kSubLanguageSerbianCyrillic	1
#define kSubLanguageSerbianLatin	2
#define kSubLanguageSerbianLast		2

// Urdu sub languages
#define kSubLanguageUrduPakistan	1
#define kSubLanguageUrduIndia		2
#define kSubLanguageUrduLast		2


//SorbianWendish sub languages
#define kSubLanguageSWUpper			1
#define kSubLanguageSWLower			2
#define kSubLanguageSWLast			2
 
#define WRMakeLanguageID( nPrimaryID, nSubID)      	 ((((WRLanguageID)(nSubID)) << 8) | (WRLanguageID)(nPrimaryID))
#define WRGetPrimaryLanguageID( nID )    			((WRLanguageID)(nID) & 0xFF)
#define WRGetSubLanguageID(nID)        				((WRLanguageID)(nID) >> 8)

//  Default System and User IDs for language.
#define kLanguageSystemDefault    	(WRMakeLanguageID(kLanguageNeutral, kSubLanguageSystemDefault))
#define kLanguageUserDefault	   	(WRMakeLanguageID(kLanguageNeutral, kSubLanguageDefault))

#define kLanguageUnknown			((WRLanguageID)(-1))

#endif

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
