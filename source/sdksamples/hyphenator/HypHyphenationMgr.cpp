//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypHyphenationMgr.cpp $
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
#include "IHyphenationMgr.h"
#include "IHyphenationService.h"
#include "ILinguisticServiceData.h"
#include "ILanguage.h"

// General includes:
#include "CPMUnknown.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "CreateObject.h"
#include "LinguisticID.h"
#include "LanguageID.h"
#include "Trace.h"

// Project includes:
#include "HypID.h"
#include "HypAdapter.h"

/** Manages the hyphenation services (IHyphenationService) supported
	by this plug-in. See kHypHyphenationServiceBoss.

	Creates hyphenation service (IHyphenationService) for each supported
	language (ILanguage) and provides the application with access to 
	these services on request. 

	Vendors should tailor this code to install services for the languages
	supported.

	@ingroup hyphenator
	
 */
class HypHyphenationMgr : public CPMUnknown<IHyphenationMgr>
{
	public:
		/** Constructor.
		 */
		HypHyphenationMgr(IPMUnknown* boss);

		/** Destructor.
		 */
		virtual ~HypHyphenationMgr();

	public:
		/** Create all hyphenation services.
		 */
		virtual	void					Install(const PMString& rPath);

		/** @return the number of languages supported.
		 */
		virtual	int32					GetLanguageCount() const;

		/** @param nNth The index of the language to query.
			@return the language of the Nth service.
		 */
		virtual	ILanguage*				QueryNthLanguage(int32 nNth);

		/** @param pLanguage The language to check.
			@return kTrue if language supported, kFalse otherwise.
		 */
		virtual	bool16					HasLanguage(const ILanguage* pLanguage) const;

		/** @param pLanguage The language to check.
			@return hyphenation service for given language.
		 */
		virtual	IHyphenationService*	QueryServiceOfLanguage(const ILanguage* pLanguage, int32 );

		virtual	int32		GetServiceOfLanguageCount( const ILanguage * pLanguage )
			{return HasLanguage(pLanguage);}

	private:
		/** Collection of hyphenation services for the languages supported by this plug-in.
			See kHypHyphenationServiceBoss.
		 */
		Hyp::HyphenationServices		fHyphenationServices;
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(HypHyphenationMgr, kHypHyphenationMgrImpl)

/*
*/
HypHyphenationMgr::HypHyphenationMgr(IPMUnknown* boss) :
	CPMUnknown<IHyphenationMgr>(boss)
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::HypHyphenationMgr()->In\n");
	InterfacePtr<ILinguisticServiceData> linguisticServiceData(this, UseDefaultIID());
	ASSERT(linguisticServiceData != nil);
	if (linguisticServiceData != nil) {
		this->Install(linguisticServiceData->GetPath());
	}
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::HypHyphenationMgr()->Out\n");
}

/*
*/
HypHyphenationMgr::~HypHyphenationMgr()
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::~HypHyphenationMgr()\n");
}

/*
*/
void HypHyphenationMgr::Install(const PMString& rPath)
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::Install(rPath=\"%s\")-->In\n", rPath.GetUTF8String().c_str());

	fHyphenationServices.clear();
	HypAdapter hypAdapter;
	hypAdapter.Install(fHyphenationServices, rPath);

	TRACEFLOW("Hyphenator", "HypHyphenationMgr::Install()-->Out\n");
}

/*
*/
int32 HypHyphenationMgr::GetLanguageCount( ) const
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::GetLanguageCount()=%d\n", fHyphenationServices.size());

	// return the service count
	return(fHyphenationServices.size());
}

/*
*/
ILanguage* HypHyphenationMgr::QueryNthLanguage(int32 nNth)
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::QueryNthLanguage(%d)->In\n", nNth);
	ILanguage* result = nil;

	if (nNth >= 0 && nNth < fHyphenationServices.size()) {
		result = fHyphenationServices[nNth];
		result->AddRef();
	}

	TRACEFLOW("Hyphenator", "HypHyphenationMgr::QueryNthLanguage()->Out, result=0x%x\n", result);
	return(result);
}

/*
*/
bool16 HypHyphenationMgr::HasLanguage(const ILanguage* pLanguage) const
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::HasLanguage()-->In\n");
	bool16 result = kFalse;

	do {
		ASSERT(pLanguage != nil);
		if (pLanguage == nil) {
			break;
		}

		// Loop through the services and check for a match.
		for (uint32 i = 0; i < fHyphenationServices.size(); i++)
		{
			if (fHyphenationServices[i]->IsEqual(pLanguage)) {
				// Languages match.
				result = kTrue;
				break;
			}
		}
	} while (false);

	TRACEFLOW("Hyphenator", "HypHyphenationMgr::HasLanguage()-->Out, result=%d\n", result);
	return(result);
}

/*
*/
IHyphenationService* HypHyphenationMgr::QueryServiceOfLanguage(const ILanguage* pLanguage, int32)
{
	TRACEFLOW("Hyphenator", "HypHyphenationMgr::QueryServiceOfLanguage()-->In\n");
	IHyphenationService* result = nil;

	do {
		ASSERT(pLanguage != nil);
		if (pLanguage == nil) {
			break;
		}

		// First try: find service for this language.
		uint32 i;
		for (i = 0; i < fHyphenationServices.size(); i++)
		{
			// if a match, return its IHyphenationService interface
			if (fHyphenationServices[i]->IsEqual(pLanguage)) {
				result = static_cast<IHyphenationService*>(fHyphenationServices[i]->QueryInterface(IHyphenationService::kDefaultIID));
				break;
			}
		}
		if (result != nil) {
			break;
		}

		// Second try: find the 'closest' language by looking for a 
		// language with the same primary language ID.
		const LanguageID targetLanguageID = pLanguage->GetLanguageID();
		if (GetSubLanguageID(targetLanguageID) != kLanguageNeutral) {
			// Not a neutral language, give up.
			break;
		}
		const LanguageID targetPrimaryLanguageID = GetPrimaryLanguageID(targetLanguageID);
		for (i = 0; i < fHyphenationServices.size(); i++)
		{
			const LanguageID serviceLanguageID = fHyphenationServices[i]->GetLanguageID();
			if (GetPrimaryLanguageID(serviceLanguageID) != targetPrimaryLanguageID) {
				// Primary languages don't match.
				continue;
			}
			// Get the service's sub-language ID.
			if (GetSubLanguageID(serviceLanguageID) == kSubLanguageDefault) {
				// Match.
				result = static_cast<IHyphenationService*>(fHyphenationServices[i]->QueryInterface(IHyphenationService::kDefaultIID));
				break;
			}
		}
	} while(false);

	TRACEFLOW("Hyphenator", "HypHyphenationMgr::QueryServiceOfLanguage()-->Out, result=0x%x\n", result);

	return(result);
}

// End, HypHyphenationMgr.cpp