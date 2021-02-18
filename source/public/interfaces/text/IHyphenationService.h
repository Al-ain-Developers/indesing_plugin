//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphenationService.h $
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

#pragma once
#ifndef __IHyphenationService__
#define __IHyphenationService__

#include "IPMUnknown.h"
#include "LinguisticID.h"

class TextCharBuffer;

//----------------------------------------------------------------------------------------
// Interface IHyphenationService
//----------------------------------------------------------------------------------------
class IHyphenatedWord;

/**
	Service mode
*/
enum LinguisticServiceMode {
	kLinguisticService_Nothing = 0x00,	/** nothing */
	kLinguisticService_ManualBit = 0x01,	/** manual */
	kLinguisticService_UserDictBit = 0x02,	/** user */
	kLinguisticService_DictionaryBit = 0x04,	/** dictionary */
	kLinguisticService_AlgorithmBit = 0x08,	/** algorithem */

	kLinguisticService_ManualOnly = 0x01,
	kLinguisticService_UserDict = 0x03,		/** user + manual	*/
	kLinguisticService_Dictionary = 0x07,		/** dict + user + manual */
	kLinguisticService_Algorithm = 0x0F		/** algorithm + dict + user + manual */
};

/**
Provider Hyphenation Style. Currently only used by the Duden hyphenation provider.
*/
enum LinguisticProviderHyphenationStyle {
	kLinguisticProviderHyphenation_All,
	kLinguisticProviderHyphenation_AllButUnaesthetic,
	kLinguisticProviderHyphenation_Aesthetic,
	kLinguisticProviderHyphenation_PreferredAesthetic
};


/**
	@ingroup text_hyphen
*/
class IHyphenationService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPHENATIONSERVICE };

	/**	
		returns nil or a new HyphenatedWord with further information.
		
                @param rWord				word to hyphenate
                @param hyphenMode			how to hyphenate word
                @param nMinTail				number of characters at end without hyphen point
                @param nMinHead				number of characters at beginning without hyphen point
				@param providerHyphStyle	style of the provider to be used for hyphenation

		@return IHyphenatedWord*	New hyphenated word with specified information or nil.
	 */
	virtual	IHyphenatedWord*	Hyphenate(const TextCharBuffer &rWord, LinguisticServiceMode hyphenMode, uint16 nMinTail = 0, uint16 nMinHead = 0, LinguisticProviderHyphenationStyle providerHyphStyle = kLinguisticProviderHyphenation_All) = 0;

	/**	
		Sets file name in hyphenation service.
		
		@param rFileName		File name to set to.

		@return bool16	kTrue if successfully set the file name.
	 */
	virtual	bool16	Set( const PMString &rFileName ) = 0;

	/**	
		Sets check user dictionary flag.
		
		@param checkIt		kTrue to turn on check user dictionary flag.
	 */
	virtual	void		CheckUserDictionary(bool16 checkIt) = 0;
};

#endif
