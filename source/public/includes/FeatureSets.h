//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FeatureSets.h $
//  
//  Owner: Chris Parrish
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
#ifndef __FeatureSets__
#define __FeatureSets__

//------
//Feature set ID's
//	We define feature set ID's as three values, two bytes and a word in a long
//	with the first value starting at 0x0100.  
//	The first byte is the product feature set, the second byte is the language feature set
//	and the second word is the locale id (UI language).
//	Locale ID's should all be defined below kFSBase and all feature sets above it,
//	so we can quickly evaluate whether an ID belongs to a feature set
//	or a locale.

#define		kFSBaseID						0x00FF

	// language in low byte
#define		kRomanLanguageFS				0x0000
#define		kJapaneseLanguageFS				0x0001
#define		kINXCoreFS						0x0002
#define		kRightToLeftLanguageFS			0x0003
#define		kAllLanguagesFS					0x00fe
	
	// product in high byte
#define		kInDesignProductFS				0x0100
#define		kInCopyProductFS				0x0200
#define		kInDesignServerProductFS		0x0400
#define		kAllProductsFS					0xff00

	// new wild cards
#define		kInDesignAllLanguagesFS			(kInDesignProductFS | kAllLanguagesFS)
#define		kInCopyAllLanguagesFS			(kInCopyProductFS | kAllLanguagesFS)
#define		kInDesignServerAllLanguagesFS	(kInDesignServerProductFS | kAllLanguagesFS)
#define		kAllProductsRomanFS				(kAllProductsFS | kRomanLanguageFS)
#define		kAllProductsJapaneseFS			(kAllProductsFS | kJapaneseLanguageFS)
#define		kAllProductsRightToLeftFS		(kAllProductsFS | kRightToLeftLanguageFS)

	// compatibility wild cards
#define		kInDesignRomanFS				(kInDesignProductFS | kRomanLanguageFS)
#define		kInDesignJapaneseFS				(kInDesignProductFS | kJapaneseLanguageFS)
#define		kInCopyRomanFS					(kInCopyProductFS | kRomanLanguageFS)
#define		kInCopyJapaneseFS				(kInCopyProductFS | kJapaneseLanguageFS)
#define		kInDesignServerRomanFS			(kInDesignServerProductFS | kRomanLanguageFS)
#define		kInDesignServerJapaneseFS		(kInDesignServerProductFS | kJapaneseLanguageFS)
#define		kInDesignR2LFS					(kInDesignProductFS | kRightToLeftLanguageFS)
#define		kInCopyR2LFS					(kInCopyProductFS | kRightToLeftLanguageFS)
#define		kInDesignServerR2LFS			(kInDesignServerProductFS | kRightToLeftLanguageFS)

#define		kWildFS							(kAllProductsFS | kAllLanguagesFS)


#endif // __FeatureSets__

