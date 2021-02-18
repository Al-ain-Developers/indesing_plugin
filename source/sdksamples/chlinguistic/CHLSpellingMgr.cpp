//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLSpellingMgr.cpp $
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
#include "ICHLFileNameTable.h"
#include "ILanguage.h"
#include "ILinguisticServiceData.h"
#include "ISpellingMgr.h"
#include "ISpellingService.h"

// General includes:
#include "CAlert.h"
#include "CPMUnknown.h"
#include "CreateObject.h"
#include "K2Vector.h"
#include "LanguageID.h"
#include "Trace.h"

// Project includes:
#include "CHLID.h"

const PMString kPMString_Null ("");


/** Implements the spelling service. You can install spelling services for one or more languages.
 *
 *  @ingroup chlinguistic
 *
*/
class CHLSpellingMgr : public CPMUnknown<ISpellingMgr>
{
	public:
		/**	Constructor.
		 *  @param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CHLSpellingMgr(IPMUnknown* boss);

		/** Destructor.
		*/
		~CHLSpellingMgr();

		/**	Installs the spelling engine.
		 *  @param rPath usually contains the path with the dictionaries.
		*/
		virtual	void Install(const PMString& rPath);

		/** Get the count of supported languages.
		 * 	@return Returns the count of supported languages.
		*/
		virtual	int32 GetLanguageCount() const;

		/** Get the language id of the nth service.
		 *  @return Returns the language of the nth service.
		*/
		virtual	ILanguage* QueryNthLanguage(int32 nNth);

		/** Ask whether the language is being supported.
		 *  @param pLanguage IN the language interface.
		 * 	@return Returns whether pLanguage is supported or not.
		*/
		virtual	bool16 HasLanguage(const ILanguage* pLanguage) const;

		/** Get the spelling service for that language.
		 *  @param pLanguage IN the language interface.
		 * 	@return the spelling service for the specified language.
		*/
		virtual	ISpellingService*	QueryServiceOfLanguage( const ILanguage * pLanguage, int32 );

		virtual	int32		GetServiceOfLanguageCount( const ILanguage * pLanguage )
			{return HasLanguage(pLanguage);}

	protected:
		K2Vector<ISpellingService*>	fServices;

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CHLSpellingMgr, kCHLSpellingMgrImpl)


/* CHLSpellingMgr constructor
*/
CHLSpellingMgr::CHLSpellingMgr(IPMUnknown* boss) : CPMUnknown<ISpellingMgr>(boss)
{
	InterfacePtr<ILinguisticServiceData>pData(this, IID_ILINGUISTICDATA);
	if (pData)
	{
		this->Install(pData->GetPath());
	}
}


/* CHLSpellingMgr destructor
*/
CHLSpellingMgr::~CHLSpellingMgr()
{
	const uint32 nMax = static_cast<uint32>(fServices.size());
	for (uint32 i = 0 ; i < nMax ; ++i)
	{
		fServices[i]->Release();
	}
}

/* CHLSpellingMgr::Install
*/
void CHLSpellingMgr::Install(const PMString& rPath)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICHLFileNameTable> iFileNameTable(this, UseDefaultIID());
		if (iFileNameTable == nil)
		{
			ASSERT_FAIL("CHLSpellingMgr::Install() iFileNameTable invalid");
			break;
		}

		iFileNameTable->Install(rPath);

		const int32 nMax = iFileNameTable->GetEntriesCount();

		// Create a spelling services as specified by the iFileNameTable entries
		PMString coreFileName;
		int32 i;
		for(i = 0; i < nMax; i++)
		{
			if (iFileNameTable->IsSpellingService(i) == kFalse)
			{
				continue;
			}

			const CHLFileNameData* fileNameData = iFileNameTable->GetNthEntry(i);
			if (fileNameData ==  nil)
			{
				break;
			}
			coreFileName = rPath;
			coreFileName.Append(fileNameData->fCoreFileName);
			ISpellingService* iSpellingService = (ISpellingService*)::CreateObject(kCHLSpellingBoss, IID_ISPELLINGSERVICE);
			if (iSpellingService == nil)
			{
				ASSERT_FAIL("CHLSpellingMgr::Install() iSpellingService invalid");
				break;
			}
			iSpellingService->Set(coreFileName, kPMString_Null, kPMString_Null, kPMString_Null);

			InterfacePtr<ILanguage> iLanguage(iSpellingService, IID_ILANGUAGE);
			if (iLanguage == nil)
			{
				ASSERT_FAIL("CHLSpellingMgr::Install() iLanguage invalid");
				break;
			}
			iLanguage->SetLanguageID(fileNameData->fLanguageID);
			iLanguage->SetLanguageName(fileNameData->fLanguageName);
			iLanguage->SetPrimaryLanguageName(fileNameData->fPrimaryLanguageName);
			iLanguage->SetSubLanguageName(fileNameData->fSubLanguageName);

			/* CS3 now add the ICU locale */
			iLanguage->SetICULocale(fileNameData->fICULocale);

			fServices.push_back(iSpellingService);
		}

		if (i < nMax)
		{
			break;
		}

		status = kSuccess;

	} while (false); // only do once

	if (status != kSuccess)
	{
		CAlert::ErrorAlert(kCHLSpellingMgrInstallFailedKey);
	}
}

/* CHLSpellingMgr::GetLanguageCount
*/
int32 CHLSpellingMgr::GetLanguageCount() const
{
	return static_cast<int32>(fServices.size());
}


/* CHLSpellingMgr::QueryNthLanguage
*/
ILanguage* CHLSpellingMgr::QueryNthLanguage(int32 nNth)
{
	if (nNth <= fServices.size() - 1)
	{
		ISpellingService* pService = fServices[nNth];
		return (ILanguage*)pService->QueryInterface(IID_ILANGUAGE);
	}
	else
	{
		return nil;
	}
}


/* CHLSpellingMgr::HasLanguage
*/
bool16	CHLSpellingMgr::HasLanguage(const ILanguage* pLanguage) const
{
	ASSERT_MSG(pLanguage != nil, "CHLSpellingMgr - language is nil");
	if (pLanguage == nil)
	{
		return kFalse;
	}

	{
		// Debug trace
		LanguageID languageID = pLanguage->GetLanguageID();
		TRACEFLOW(kCHLPluginName, "CHLSpellingMgr::HasLanguage(): Target primaryLanguageID %d, subLanguageID %d\n", GetPrimaryLanguageID(languageID), GetSubLanguageID(languageID));
	}

	const uint32 nMax = static_cast<uint32>(fServices.size());
	for (uint32 i = 0 ; i < nMax ; ++i)
	{
		const ISpellingService* pService = fServices[i];
		InterfacePtr<ILanguage> pServiceLanguage(pService, IID_ILANGUAGE);

		if (pServiceLanguage->IsEqual(pLanguage))
		{
			return kTrue;
		}
	}
	return kFalse;
}


/* CHLSpellingMgr::QueryServiceOfLanguage
*/
ISpellingService* CHLSpellingMgr::QueryServiceOfLanguage(const ILanguage* pLanguage, int32)
{
	ASSERT_MSG(pLanguage != nil, "CHLSpellingMgr - language is nil");
	if (pLanguage == nil)
	{
		return nil;
	}

	{
		// Debug trace
		LanguageID languageID = pLanguage->GetLanguageID();
		TRACEFLOW(kCHLPluginName, "CHLSpellingMgr::QueryServiceOfLanguage(): Target primaryLanguageID %d, subLanguageID %d\n", GetPrimaryLanguageID(languageID), GetSubLanguageID(languageID));
	}

	const uint32 nMax = static_cast<uint32>(fServices.size());
	uint32 i;

	// first try: find exact Language
	for (i = 0 ; i < nMax ; ++i)
	{
		ISpellingService* pService = fServices[i];
		InterfacePtr<ILanguage> pServiceLanguage(pService, IID_ILANGUAGE);
		if (pServiceLanguage->IsEqual(pLanguage))
		{
			pService->AddRef();
			return pService;
		}
	}

	// second try: find the 'closest' language: same primary language and smallest sub language
	const LanguageID nLanguage = pLanguage->GetLanguageID();
	if (GetSubLanguageID(nLanguage) == kLanguageNeutral)
	{
		ISpellingService* pFound = 0;
		const LanguageID nPrimLang = GetPrimaryLanguageID(nLanguage);
		for (i = 0 ; i < nMax && !pFound ; ++i)
		{
			ISpellingService* pService = fServices[i];
			InterfacePtr<ILanguage> pServiceLanguage(pService, IID_ILANGUAGE);

			const LanguageID nServiceLang = pServiceLanguage->GetLanguageID();
			if (GetPrimaryLanguageID(nServiceLang) == nLanguage)
			{
				if (GetSubLanguageID(nServiceLang) == kSubLanguageDefault)
				{
					pFound = pService;
				}
			}
		}
		if (pFound)
		{
			pFound->AddRef();
			return pFound;
		}
	}
	return nil;
}

// End, CHLSpellingMgr.cpp.
