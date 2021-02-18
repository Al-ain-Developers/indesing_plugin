//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLThesaurusMgr.cpp $
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

#include "VCPlugInHeaders.h"		// must be the first header file to include

#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILinguisticMgr.h"
#include "ILinguisticServiceData.h"
#include "ICHLFileNameTable.h"
#include "ISession.h"
#include "IThesaurusMgr.h"
#include "IThesaurusService.h"

#include "CreateObject.h"
#include "CrossPlatformTypes.h"
#include "HelperInterface.h"
#include "K2Vector.h"
#include "LanguageID.h"
#include "LinguisticID.h"
#include "PMString.h"
#include "CHLID.h"



/** Implements the thesaurus service. You can install thesaurus services for one or more languages.
 *
 *  @ingroup chlinguistic
 *
*/
class CHLThesaurusMgr : public CPMUnknown<IThesaurusMgr>
{
public:
	/**	Constructor.
	 *  @param boss interface ptr from boss object on which this interface is aggregated.
	 */
	CHLThesaurusMgr(IPMUnknown * boss);

	/** Destructor.
	 */
	~CHLThesaurusMgr();

	/**	Installs the thesaurus engine.
	 *  @param rPath usually contains the path with the data files.
	 */
	virtual	void		Install(const PMString &rPath);

	/** Get the count of supported languages.
	 * 	@return Returns the count of supported languages.
	 */
	virtual	int32		GetLanguageCount() const;

	/** Get the language of the nth service.
	 *  @return Returns the language of the nth service.
	 */
	virtual	ILanguage *	QueryNthLanguage(int32 nNth);

	/** Ask whether the language is being supported.
	 *  @param pLanguage IN the language interface.
	 * 	@return Returns whether pLanguage is supported or not.
	 */
	virtual	bool16		HasLanguage(const ILanguage * pLanguage) const;

	/** Get the thesaurus service for the language.
	 *  @param pLanguage IN the language interface.
	 * 	@return the thesaurus service for the specified language.
	*/
	virtual	IThesaurusService*	QueryServiceOfLanguage(const ILanguage * pLanguage, int32 );

	virtual	int32		GetServiceOfLanguageCount( const ILanguage * pLanguage ) {return HasLanguage(pLanguage);}

protected:
	K2Vector<IThesaurusService*>	fServices;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CHLThesaurusMgr, kCHLThesaurusMgrImpl)



/* CHLThesaurusMgr constructor
*/
CHLThesaurusMgr::CHLThesaurusMgr(IPMUnknown *boss) :
	CPMUnknown<IThesaurusMgr>(boss)
{
	InterfacePtr<ILinguisticServiceData> pData(this, IID_ILINGUISTICDATA);
	this->Install(pData->GetPath());
}

/* CHLThesaurusMgr destructor
*/
CHLThesaurusMgr::~CHLThesaurusMgr()
{
	const uint32 nMax = static_cast<uint32>(fServices.size());
	for (uint32 i = 0; i < nMax; ++i)
		fServices[i]->Release();
}

/* CHLThesaurusMgr::Install
*/
void CHLThesaurusMgr::Install(const PMString &rPath)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICHLFileNameTable>pTable(this, UseDefaultIID());
		pTable->Install(rPath);

		const int32 nMax = pTable->GetEntriesCount();

		PMString aName, aPrimName, aSubName;

		InterfacePtr<IK2ServiceRegistry> pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
		InterfacePtr<IK2ServiceProvider> pLinguMgrService(pServices->QueryDefaultServiceProvider(kLinguisticManagerService));
		InterfacePtr<ILinguisticMgr> pLinguMgr(pLinguMgrService, IID_ILINGUISTICMGR);

		for (int32 i = 0; i < nMax; ++i)
		{
			if (pTable->IsThesaurusService(i) == kFalse)
			{
				continue;
			}

			const CHLFileNameData* pData = pTable->GetNthEntry(i);
			if (pData ==  nil)
			{
				break;
			}
			const PMString aThesFileName(pData->fThesaurusFileName);

			if (aThesFileName.IsEmpty())
				continue;

			PMString aFileName(rPath);
			aFileName.Append(aThesFileName);

			const LanguageID nLanguage = pData->fLanguageID;
			IThesaurusService* thesaurusService = (IThesaurusService*)::CreateObject(kCHLThesaurusBoss, IID_ITHESAURUSSERVICE);
			thesaurusService->Set(aFileName);

			InterfacePtr<ILanguage> pLanguage(thesaurusService, UseDefaultIID());

			pLinguMgr->GetLanguageName(nLanguage, &aName, &aPrimName, &aSubName);

			pLanguage->SetLanguageID(nLanguage);
			pLanguage->SetLanguageName(pData->fLanguageName);
			pLanguage->SetPrimaryLanguageName(pData->fPrimaryLanguageName);
			pLanguage->SetSubLanguageName(pData->fSubLanguageName);
			pLanguage->SetICULocale(pData->fICULocale);

			fServices.push_back(thesaurusService);
		}

		status = kSuccess;

	} while (false); // only do once

}

/* CHLThesaurusMgr::GetLanguageCount
*/
int32 CHLThesaurusMgr::GetLanguageCount() const
{
	return static_cast<int32>(fServices.size());
}

/* CHLThesaurusMgr::QueryNthLanguage
*/
ILanguage *CHLThesaurusMgr::QueryNthLanguage(int32 nNth)
{
	IThesaurusService *pService = fServices[nNth];
	return (ILanguage*)pService->QueryInterface(IID_ILANGUAGE);
}

/* CHLThesaurusMgr::HasLanguage
*/
bool16	CHLThesaurusMgr::HasLanguage(const ILanguage *pLanguage) const
{
	const uint32 nMax = static_cast<uint32>(fServices.size());
	for (uint32 i = 0; i < nMax; ++i)
	{
		const IThesaurusService *pService = fServices[i];
		InterfacePtr<ILanguage> pServiceLanguage(pService, UseDefaultIID());
		if (pServiceLanguage->IsEqual(pLanguage))
			return kTrue;
	}
	return kFalse;
}

/* CHLThesaurusMgr::QueryServiceOfLanguage
*/
IThesaurusService* CHLThesaurusMgr::QueryServiceOfLanguage(const ILanguage *pLanguage, int32)
{
	ASSERT_MSG(pLanguage != nil, "CHLThesaurusMgr - language is nil");
	if (!pLanguage)
		return nil;

	const uint32 nMax = static_cast<uint32>(fServices.size());
	uint32 i;

	// first try: find exact Language
	for (i = 0; i < nMax; ++i)
	{
		IThesaurusService *pService = fServices[i];
		InterfacePtr<ILanguage> pServiceLanguage(pService, UseDefaultIID());
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
		IThesaurusService *pFound = 0;
		const LanguageID nPrimLang = GetPrimaryLanguageID(nLanguage);
		for (i = 0; i < nMax && !pFound; ++i)
		{
			IThesaurusService *pService = fServices[i];
			InterfacePtr<ILanguage> pServiceLanguage(pService, UseDefaultIID());
			const LanguageID nServiceLang =  pServiceLanguage->GetLanguageID();
			if (GetPrimaryLanguageID(nServiceLang) == nLanguage)
			{
				if (GetSubLanguageID(nServiceLang) == kSubLanguageDefault)
					pFound = pService;
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

