//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/LanguageID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __LanguageID__
#define __LanguageID__

#include "BaseType.h"

typedef int16 LanguageID;

/*
	 Language IDs are combinations of a primary and a sublanguage id.
	The first 8 bits of a LanugageID (0-7) are reserved for the primary language id.
	The last  8 bits of a LanugageID (8-15) are reserved for the sublanguage id.
	The macros MakeLanguageID, GetPrimaryLanguageID and GetSubLanguageID provide creation
	and extraction.
	Notice that there are three special constants: kLanguageNeutral, kLanguageSystemDefault and
	kLanguageUserDefault.

	If the language id you need is not defined here use MakeLanguageID( kLanguageUseICULocale, kSubLanguageDefault )
	and Call ILanguage::SetICULocale with the ICULocale for your language.
*/


// Primary language IDs:
#define kLanguageNeutral					 0 // Special ID which means no language

#define kLanguageArabic 					 1
#define kLanguageAfrikaans				 2
#define kLanguageAlbanian				 3
#define kLanguageBasque 					 4
#define kLanguageBulgarian				 5
#define kLanguageByeloRussian				 6
#define kLanguageCatalan					 7
#define kLanguageChinese					 8
#define kLanguageCroatian				 9
#define kLanguageCzech					 10
#define kLanguageDanish 					 11
#define kLanguageDutch					 12
#define kLanguageEnglish					 13
#define kLanguageEstonian					 14
#define kLanguageFaeroese				 15
#define kLanguageFarsi					 16
#define kLanguageFinnish					 17
#define kLanguageFrench 					 18
#define kLanguageGerman 					 19
#define kLanguageGreek					 20
#define kLanguageHebrew 					 21
#define kLanguageHungarian				 22
#define kLanguageIcelandic				 23
#define kLanguageIndonesian 				 24
#define kLanguageItalian					 25
#define kLanguageJapanese				 26
#define kLanguageKorean 					 27
#define kLanguageLatvian					 28
#define kLanguageLithuanian 				 29
#define kLanguageNorwegian				 30
#define kLanguagePolish 					 31
#define kLanguagePortuguese 				 32
#define kLanguageRomanian				 33
#define kLanguageRussian					 34
#define kLanguageSlovak 					 35
#define kLanguageSlovenian				 36
#define kLanguageSerbian					 37
#define kLanguageSpanish					 38
#define kLanguageSwedish					 39
#define kLanguageThai					 40
#define kLanguageTurkish					 41
#define kLanguageUkrainian				 42
#define kLanguageVietnamese				43

#define kLanguageAssamese				44 /* ### */
#define kLanguageAzeri					45 /* ### */
#define kLanguageBengali				46 /* ### */
#define kLanguageBurmese				47 /* ### */
#define kLanguageFrisian				48 /* ### (Netherlands) */
#define kLanguageGaelic					49 /* ### */
#define kLanguageGalician				50 /* ### */
#define kLanguageGeorgian				51 /* ### */
#define kLanguageGujarati				52 /* ### */
#define kLanguageHindi					53 /* ### */
#define kLanguageKannada				54 /* ### */
#define kLanguageKashmiri				55 /* ### */
#define kLanguageKazakh					56 /* ### */
#define kLanguageKhmer					57 /* ### */
#define kLanguageKirghiz				58 /* ### */
#define kLanguageKonkani				59 /* ### */
#define kLanguageLao					60 /* ### */
#define kLanguageMacedonian				61 /* ### */
#define kLanguageMalay					62 /* ### */
#define kLanguageMalayalam				63 /* ### */
#define kLanguageMaltese				64 /* ### */
#define kLanguageManipuri				65 /* ### */
#define kLanguageMarathi				66 /* ### */
#define kLanguageMongolian				67 /* ### */
#define kLanguageNepali					68 /* ### */
#define kLanguageOriya					69 /* ### */
#define kLanguagePunjabi				70 /* ### */
#define kLanguageRhaetoRomanic			71 /* ### */
#define kLanguageSami					72 /* ### */
#define kLanguageSanskrit				73 /* ### */
#define kLanguageSindhi					74 /* ### */
#define kLanguageSutu					75 /* ### */
#define kLanguageSwahili				76 /* ### */
#define kLanguageTajik					77 /* ### */
#define kLanguageTamil					78 /* ### */
#define kLanguageTatar					79 /* ### */
#define kLanguageTelugu					80 /* ### */
#define kLanguageTibetan				81 /* ### */
#define kLanguageTsonga					82 /* ### */
#define kLanguageTswana					83 /* ### */
#define kLanguageTurkmen				84 /* ### */
#define kLanguageUrdu					85 /* ### */
#define kLanguageVenda					86 /* ### */
#define kLanguageArmenian				87 /* ### */
#define kLanguageWelsh					88 /* ### */
#define kLanguageXhosa					89 /* ### */
#define kLanguageZulu					90 /* ### */
#define kLanguagePedi					91 /* ### */
#define kLanguageLast					91 /* ### Last language in the list.*/
#define kLanguageUseICULocale			92 /* IDs for languages without an ID above. Uses locale id in ILanguage to sort and do case conversion */


// Sub languages
#define kSubLanguageNeutral 				 0	 /* language Neutral */
#define kSubLanguageDefault 				 1	 /* user Default */
#define kSubLanguageSystemDefault			 2	 /* system Default */

// Arabic sub languages
#define kSubLanguageArabic					1	/* Arabic */
#define kSubLanguageArabicSaudi				2	/* Arabic (Saudi Arabia) */
#define kSubLanguageArabicIraq				3	/* Arabic (Iraq) */
#define kSubLanguageArabicEgypt 			4	/* Arabic (Egypt) */
#define kSubLanguageArabicLibya 			5	/* Arabic (Libya) */
#define kSubLanguageArabicAlgeria			6	/* Arabic (Algeria) */
#define kSubLanguageArabicMorocco			7	/* Arabic (Morocco) */
#define kSubLanguageArabicTunisia			8	/* Arabic (Tunisia) */
#define kSubLanguageArabicOman				9	/* Arabic (Oman) */
#define kSubLanguageArabicYemen 			10	/* Arabic (Yemen) */
#define kSubLanguageArabicSyria 			11	/* Arabic (Syria) */
#define kSubLanguageArabicJordan			12	/* Arabic (Jordan) */
#define kSubLanguageArabicLebanon			13	/* Arabic (Lebanon) */
#define kSubLanguageArabicKuwait			14	/* Arabic (Kuwait) */
#define kSubLanguageArabicUAE				15	/* Arabic (United Arab Emirates) */
#define kSubLanguageArabicBahrain			16	/* Arabic (Bahrain) */
#define kSubLanguageArabicQatar 			17	/* Arabic (Qatar) */
#define kSubLanguageArabicLast	 			17

// Azeri sub languages
#define kSubLanguageAzeriLatin				 1	/* ### Azeri (Latin) */
#define kSubLanguageAzeriCyrillic			 2	/* ### Azeri (Cyrillic) */
#define kSubLanguageAzeriLast				 2	/* ### */

// Chinese sub languages
#define kSubLanguageChineseTraditional		1	/* Chinese (Taiwan) */
#define kSubLanguageChineseSimplified		2	/* Chinese (PR China) */
#define kSubLanguageChineseHongKong 		3	/* Chinese (Hong Kong) */
#define kSubLanguageChineseSingapore		4	/* Chinese (Singapore) */
#define kSubLanguageChineseMacao			 5	/* ### Chinese (Macao) */
#define kSubLanguageChineseLast				 5	/* ### */

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
#define kSubLanguageEnglishBelize			10	/* ### English (Belize) */
#define kSubLanguageEnglishTrinidad			11	/* ### English (Trinidad) */
#define kSubLanguageEnglishZimbabwe			12	/* ### English (Zimbabwe) */
#define kSubLanguageEnglishPhilippines		13	/* ### English (Philippines) */
#define kSubLanguageEnglishLast				13	/* ### */

// French sub languages
#define kSubLanguageFrench				 1	 /* French */
#define kSubLanguageFrenchBelgian			 2	 /* French (Belgian) */
#define kSubLanguageFrenchCanadian			 3	 /* French (Canadian) */
#define kSubLanguageFrenchSwiss 			 4	 /* French (Swiss) */
#define kSubLanguageFrenchLuxembourg		 5	 /* French (Luxembourg) */
#define kSubLanguageFrenchMonaco			 6	/* ### French (Monaco) */
#define kSubLanguageFrenchWestIndies		 7	/* ### French (West Indies) */
#define kSubLanguageFrenchReunion			 8	/* ### French (Reunion) */
#define kSubLanguageFrenchZaire				 9	/* ### French (Zaire) */
#define kSubLanguageFrenchSenegal			10	/* ### French (Senegal) */
#define kSubLanguageFrenchCameroon			11	/* ### French (Cameroon) */
#define kSubLanguageFrenchCoteDIvoire		12	/* ### French (Cote d'Ivoire) */
#define kSubLanguageFrenchMali				13	/* ### French (Mali) */
#define kSubLanguageFrenchLast				13	/* ### */

// Gaelic sub languages
#define kSubLanguageGaelicScotland			 1	/* ### Gaelic (Scotland) */
#define kSubLanguageGaelicIreland			 2	/* ### Gaelic (Ireland) */
#define kSubLanguageGaelicLast				 2	/* ### */

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

// Kashmiri sub languages
#define kSubLanguageKashmiri				 1	/* ### Kashmiri */
#define kSubLanguageKashmiriIndia			 2	/* ### Kashmiri (India) */
#define kSubLanguageKashmiriLast			 2	/* ### */

// Korean sub languages
#define kSubLanguageKorean				 1	 /* Korean */
#define kSubLanguageKoreanJohab 			 2	 /* Korean (Johab) */
#define kSubLanguageKoreanLast	 			 2

// Lithuanian sub languages
#define kSubLanguageLithuanian				 1	/* ### Lithuanian */
#define kSubLanguageLithuanianClassic		 2	/* ### Lithuanian (Classic) */
#define kSubLanguageLithuanianLast			 2	/* ### */

// Malay sub languages
#define kSubLanguageMalayMalaysia			 1	/* ### Malay (Malaysia) */
#define kSubLanguageMalayBurneiDarussalam	 2	/* ### Malay (Burnei-Darussalam) */
#define kSubLanguageMalayLast				 2	/* ### */

// Nepali sub languages
#define kSubLanguageNepali					 1	/* ### Nepali */
#define kSubLanguageNepaliIndia				 2	/* ### Nepali (India) */
#define kSubLanguageNepaliLast				 2	/* ### */

// Norwegian sub languages
#define kSubLanguageNorwegianBokmal 		 1	 /* Norwegian (Bokmal) */
#define kSubLanguageNorwegianNynorsk		 2	 /* Norwegian (Nynorsk) */
#define kSubLanguageNorwegianLast			 2

// Portuguese sub languages
#define kSubLanguagePortuguese			 1	 /* Portuguese */
#define kSubLanguagePortugueseBrazilian 	 	 2	 /* Portuguese (Brazilian) */
#define kSubLanguagePortugueseLast		 	 	 2

// Serbian sub languages
#define kSubLanguageSerbian					 1	/* ### Serbian  */
#define kSubLanguageSerbianLatin			 2	/* ### Serbian (Latin) */
#define kSubLanguageSerbianCyrillic			 3	/* ### Serbian (Cyrillic) */
#define kSubLanguageSerbianLast				 3	/* ### */


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
#define kSubLanguageSpanishElSalvador		17	/* ### Spanish (El Salvador) */
#define kSubLanguageSpanishHonduras			18	/* ### Spanish (Honduras) */
#define kSubLanguageSpanishNicaragua		19	/* ### Spanish (Nicaragua) */
#define kSubLanguageSpanishPuertoRico		20	/* ### Spanish (Puerto Rico) */
#define kSubLanguageSpanishLast				20	/* ### */

// Swedish sub languages
#define kSubLanguageSwedish					 1	/* ### Swedish (Sweden) */
#define kSubLanguageSwedishFinland			 2	/* ### Swedish (Finland) */
#define kSubLanguageSwedishLast				 2	/* ### */

// Urdu sub languages
#define kSubLanguageUrduPakistan			 1	/* ### Urdu (Pakistan) */
#define kSubLanguageUrduIndia				 2	/* ### Urdu (India) */
#define kSubLanguageUrduLast				 2	/* ### */

// Uzbek sub languages
#define kSubLanguageUzbekLatin				 1	/* ### Uzbek (Latin) */
#define kSubLanguageUzbekCyrillic			 2	/* ### Uzbek (Cyrillic) */
#define kSubLanguageUzbekLast				 2	/* ### */



//inline LanguageID MakeLanguageID(char nPrimaryID, char nSubID)
//{ return ((((int16)(nSubID)) << 8) | (int16)(nPrimaryID)); }
// HAVE TO USE THE MACRO because there are << case MakeLanguageID(xxx, yyy): >> codes in places
#define MakeLanguageID(nPrimaryID, nSubID)	((((int16)(nSubID)) << 8) | (int16)(nPrimaryID))

inline LanguageID GetPrimaryLanguageID(LanguageID nID)
{ return ((int16)(nID) & 0xFF); }

inline LanguageID GetSubLanguageID(LanguageID nID)
{ return ((int16)(nID) >> 8); }

//  Default System and User IDs for language.
const LanguageID kLanguageSystemDefault = (MakeLanguageID(kLanguageNeutral, kSubLanguageSystemDefault));
const LanguageID kLanguageUserDefault = (MakeLanguageID(kLanguageNeutral, kSubLanguageDefault));

#endif
