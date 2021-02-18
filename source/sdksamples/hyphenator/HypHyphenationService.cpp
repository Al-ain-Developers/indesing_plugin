//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypHyphenationService.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IHyphenationService.h"
#include "ISession.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ILinguisticServiceData.h"
#include "IHyphenatedWord.h"
#include "ILanguage.h"

// General includes:
#include "CPMUnknown.h"
#include "LinguisticID.h"
#include "WideString.h"
#include "Trace.h"
#include "TextCharBuffer.h"

// Project includes:
#include "HypID.h"
#include "HypAdapter.h"

/** Performs hyphenation by delegating all requests to HypAdapter::Hyphenate.

	@ingroup hyphenator

 */
class HypHyphenationService : public CPMUnknown<IHyphenationService>
{
	public:
		/** Constructor.
		 */
		HypHyphenationService(IPMUnknown* boss);

		/** Destructor.
		 */
		virtual	~HypHyphenationService();

	public:
		/** Hyphenate the given word. See HypAdapter for description of parameters.
			@param rWord
			@param nMinTail
			@param nMinHead
			@return word with hyphenation points
		 */
		virtual	IHyphenatedWord*	Hyphenate(const TextCharBuffer& rWord, LinguisticServiceMode mode, uint16 nMinTail, uint16 nMinHead, LinguisticProviderHyphenationStyle providerHyphStyle);

		/** Called during service installation to inform service of its dictionary file.
		 */
		virtual bool16				Set(const PMString& rFileName);

		virtual void		CheckUserDictionary(bool16 checkIt)
			{}

	private:
		bool16						getLanguageID(LanguageID& languageID) const;
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(HypHyphenationService, kHypHyphenationServiceImpl)

/*
*/
HypHyphenationService::HypHyphenationService(IPMUnknown* boss) : CPMUnknown<IHyphenationService>(boss)
{
	TRACEFLOW("Hyphenator", "HypHyphenationService::HypHyphenationService()\n");
}

/*
*/
HypHyphenationService::~HypHyphenationService()
{
	TRACEFLOW("Hyphenator", "HypHyphenationService::~HypHyphenationService()\n");
}

/*
*/
IHyphenatedWord* HypHyphenationService::Hyphenate(const TextCharBuffer& rWord, LinguisticServiceMode serviceMode, uint16 nMinTail, uint16 nMinHead, LinguisticProviderHyphenationStyle providerHyphStyle)
{
	IHyphenatedWord* result = nil;
	do {
		// Get the LanguageID of this service.
		LanguageID languageID;
		if (this->getLanguageID(languageID) != kTrue) {
			break;
		}

		// Hyphenate the word.
		HypAdapter hypAdapter;
		result = hypAdapter.Hyphenate(rWord, nMinTail, nMinHead, serviceMode, languageID);
	} while(false);
	return(result);
}

/*
*/
bool16 HypHyphenationService::Set(const PMString& rFileName)
{
	TRACEFLOW("Hyphenator", "HypHyphenationService::Set(\"%s\")\n", rFileName.GetUTF8String().c_str());
	return(kTrue);
}


/*
*/
bool16 HypHyphenationService::getLanguageID(LanguageID& languageID) const
{
	bool16 result = kFalse;
	InterfacePtr<ILanguage> language(this, UseDefaultIID());
	ASSERT(language != nil);
	if (language != nil) {
		languageID = language->GetLanguageID();
		result = kTrue;
	}
	return(kTrue);
}

// End, HypHyphenationService.cpp