//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMLocaleId.h $
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
#ifndef __PMLocaleId_h__
#define __PMLocaleId_h__

#include "ICUForwardDeclare.h"
#include "PMTypes.h"
#include "IPMStream.h"
#include "PMLocaleIds.h"


#ifdef PUBLIC_BUILD
#pragma export on
#endif

#pragma export on
/**	The purpose of this class is to encapsulate a locale, which we've defined to be a combination of three things:
	1) Product feature set (i.e. kInDesignProductFS - @see FeatureSets.h)
	2) Language feature set (i.e. kRomanLanguageFS -  @see FeatureSets.h)
	3) UI language (i.e. k_enUS @see PMLocaleIds.h)
*/
class PUBLIC_DECL PMLocaleId
{
public:
	typedef base_type data_type;

/**		Various constructors for PMLocaleId
*/
	inline		PMLocaleId();
	inline		explicit PMLocaleId(int32 combinedId);
	inline		PMLocaleId(int16 featureSetId, int16 userInterfaceId);
	
/**		Equality operator. Does not check for wildcards
		@param other The PMLocaleId we're comparing this one to.
		@return kTrue if the PMLocaleId exactly matches this one.
*/
	inline		bool16 operator==(const PMLocaleId& other) const;

/**		Inequality operator. Does not check for wildcards
		@param other The PMLocaleId we're comparing this one to.
		@return kTrue if the PMLocaleId does not exactly match this one.
*/
	inline		bool16 operator!=(const PMLocaleId& other) const;
	
	
/**		Checks if one PMLocaleId matches another one. 
		Considers wildcards to be a match(i.e. kWild == any UI language, kAllLanguagesFS == any language FS, kAllProductsFS == any product FS)
		@param other The PMLocaleId we're comparing this one to.
		@return kTrue if the PMLocaleId matches this one.
*/
				bool16 Match(const PMLocaleId& other) const;	
	
/**		Combines the FeatureSetId and UserInterfaceId into a single Id. The feature set is stored in the upper word of a long and the UI is stored in the lower word.
		@return combined FeatureSet + UI language merged into an int32.
*/
	inline		int32 operator*() const;
	
/**		Streams in/out a PMLocaleId.
		@param s the stream to read/write from/to
*/
	inline		void ReadWrite(IPMStream* s);
	
/**		The Feature set ID is partitioned into a high byte for product feature sets and a low byte for language feature sets. @see FeatureSets.h
		@return combined Feature set ID.
*/
	inline		int16 GetFeatureSetId() const;
	
/**		Get just the product feature set ID (i.e. kInDesignProductFS. @see FeatureSets.h)
		@return Product Feature set ID.
*/
	inline		int16 GetProductFS() const;

/**		Get just the Language feature set ID (i.e. kRomanLanguageFS. @see FeatureSets.h)
		@return Language Feature set ID.
*/
	inline		int16 GetLanguageFS() const;
	
/**		Get just the UI Language ID (i.e. k_enUS. @see PMLocaleIds.h)
		@return UI Language ID.
*/
	inline		int16 GetUserInterfaceId() const;

/**		Get the default language. UI may be English but default language is Hebrew (i.e. k_enIL. @see PMLocaleIds.h)
		@return UI Language ID.
*/
	inline		int16 GetDefaultLanguageId() const;

/** 	Check if this PMLocaleId matches the given product FS. Will match wildcards.
		@param productFS the constant for the product FS that you'd like to know if this PMLocaleId matches.
		@return kTrue if this PMLocaleId matches the passed in product FS
*/
	inline		bool16 IsProductFS(const int16 productFS) const;

/** 	Check if this PMLocaleId matches the given language FS. Will match wildcards.
		@param languageFS the constant for the language FS that you'd like to know if this PMLocaleId matches.
		@return kTrue if this PMLocaleId matches the passed in language FS
*/
	inline		bool16 IsLanguageFS(const int16 languageFS) const;
	
/** 	Get the cooltype script associated with the LanguageFS + UI language for this PMLocaleId
		@return script for the LanguageFS + UI language combination contained in this PMLocaleId, in the form of a kCT*Script
*/
				int32	GetFeatureSetScript() const;
				
/** 	Get the cooltype script associated with the UI language for this PMLocaleId
		@return script for the UI language contained in this PMLocaleId, in the form of a kCT*Script
*/
				int32	GetUIScript() const;

/** 	Get the ICU Locale associated with the UI language for this PMLocaleId
		@return ICU Locale for the UI language contained in this PMLocaleId
*/
				ID_ICU_NAMESPACE::Locale	GetUserInterfaceICULocale() const;

/** 	True if UI is right to left like Arabic and Hebrew
		@return kTrue if UI is right to left.
*/
				bool16	IsRightToLeftUI() const;

/** 	Set the UI language for this PMLocaleId
		@param newLocale ICU Locale to set PMLocaleId to
*/
				void	SetUserInterface(ID_ICU_NAMESPACE::Locale newLocale);

	inline		bool operator<(const PMLocaleId& other) const;

private:
	int16 fFeatureSetId;
	int16 fUserInterfaceId;
};

#pragma export off

//========================================================================================
// METHODS PMLocaleId
//========================================================================================

inline PMLocaleId::PMLocaleId() :
	fFeatureSetId(0),
	fUserInterfaceId(0)
{
}

inline PMLocaleId::PMLocaleId(int32 combinedId) :
	fFeatureSetId((combinedId & 0xFFFF0000) >> 16),
	fUserInterfaceId(combinedId & 0x0000FFFF)
{
}

inline PMLocaleId::PMLocaleId(int16 featureSetId, int16 userInterfaceId) :
	fFeatureSetId(featureSetId),
	fUserInterfaceId(userInterfaceId)
{
}

inline bool16 PMLocaleId::operator==(const PMLocaleId& other) const
{
	return fFeatureSetId == other.fFeatureSetId && fUserInterfaceId == other.fUserInterfaceId;
}

inline bool16 PMLocaleId::operator!=(const PMLocaleId& other) const
{
	return fFeatureSetId != other.fFeatureSetId || fUserInterfaceId != other.fUserInterfaceId;
}

inline int32 PMLocaleId::operator*() const
{
	return (fFeatureSetId << 16) & fUserInterfaceId;
}

inline bool PMLocaleId::operator< (const PMLocaleId& other) const
{
	if (fFeatureSetId < other.fFeatureSetId)
		return true;
	else if (fFeatureSetId ==  other.fFeatureSetId && fUserInterfaceId < other.fUserInterfaceId)
		return true;
	else
		return false;
}

inline int16 PMLocaleId::GetFeatureSetId() const
{
	return fFeatureSetId;
}

inline int16 PMLocaleId::GetUserInterfaceId() const
{
	if (fUserInterfaceId == k_enAE || fUserInterfaceId == k_enIL)
		return k_enUS;
	return fUserInterfaceId;
}

inline int16 PMLocaleId::GetDefaultLanguageId() const
{
	return fUserInterfaceId;
}

inline int16 PMLocaleId::GetProductFS() const
{
	return (fFeatureSetId & 0xFF00);
}

inline int16 PMLocaleId::GetLanguageFS() const
{
	return (fFeatureSetId & 0x00FF);
}

// if either is wild or they match
inline bool16 PMLocaleId::IsProductFS(const int16 productFS) const
{
	uint16 product = static_cast<uint16>(fFeatureSetId) & 0xFF00;
#if 1
	return ((product == kAllProductsFS) || (static_cast<uint16>(productFS) == kAllProductsFS) || (product == static_cast<uint16>(productFS)));
#else
	//11/24/03 pboctor/mburbidge - The last part of this expression was changed to allow a ScriptInfo resource to be something like this:
	//		kInDesignRomanFS | kInDesignServerRomanFS
	// In order for this to work: 1. The product feature set values must occupy unique bits 2. We can't have a product feature set value of 0
	//5/13/04 jwbrown - ScriptInfo resources no longer require/permit OR'd feature sets, so I've reverted this code
	return ((product == (int16)kAllProductsFS) || (productFS == (int16)kAllProductsFS) || ((productFS & product) != 0));
#endif
}

// if either is wild or they match
inline bool16 PMLocaleId::IsLanguageFS(const int16 languageFS) const
{
	int16 language = fFeatureSetId & 0x00FF;
	return ((language == (int16)kAllLanguagesFS) || (languageFS == (int16)kAllLanguagesFS) || (language == languageFS));
}

inline bool16 PMLocaleId::IsRightToLeftUI() const
{
	return ((GetUserInterfaceId() == k_arAE) || (GetUserInterfaceId() == k_heIL));
}



inline void PMLocaleId::ReadWrite(IPMStream* s)
{
	s->XferInt16(fFeatureSetId);
	s->XferInt16(fUserInterfaceId);
}

#endif // __PMLocaleId_h__
