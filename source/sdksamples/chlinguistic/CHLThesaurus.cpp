//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLThesaurus.cpp $
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

#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ICHLData.h"
#include "ISession.h"
#include "ISpellingMgr.h"
#include "ISpellingService.h"
#include "IThesaurusService.h"

#include "HelperInterface.h"
#include "LinguisticID.h"
#include "PMTextUtils.h"
#include "CHLID.h"
#include "CHLUtils.h"
#include "K2Vector.h"
#include "TextChar.h"
#include "UnicodeClass.h"

#include "Trace.h"		


//---------------------------------------------------------------
// Templates
//---------------------------------------------------------------

#include "TemplateDefs.h"
#include "K2Vector.tpp"

template class K2Vector<ThesDefinition>;



class CHLThesaurus : public CPMUnknown<IThesaurusService>
{
public:
	/**	Constructor.
	 *  @param boss interface ptr from boss object on which this interface is aggregated.
	 */
	CHLThesaurus(IPMUnknown * boss);

	/** Destructor.
	 */
	~CHLThesaurus();
						
	/** Get the thesaurus record for the word
	*/
	virtual	bool16 	GetThesRecord(const PMString &rWord, ThesRecord& thesRecord);
	
	/** Get the synonyms list for the lookup word
	*/
	virtual	bool16 	GetSynonyms(const PMString &rWord, WideStringList& wList);

	/** Get the antonyms list for the lookup word
	*/
	virtual	bool16 	GetAntonyms(const PMString &rWord, WideStringList& wList);

	/** Get the near synonyms (related words) list for the lookup word
	*/
	virtual	bool16 	GetNearSynonyms(const PMString &rWord, WideStringList& wList);

	/** Get the near antonyms (contrasting words) list for the lookup word
	*/
	virtual	bool16 	GetNearAntonyms(const PMString &rWord, WideStringList& wList);

	/** Get the see also list for the lookup word
	*/
	virtual	bool16 	GetSeeAlsoWords(const PMString &rWord, WideStringList& wList);
	
	/** Get the alternate suggestions list for the lookup word, 
	       normally used if the lookup word was not found
	*/
	virtual	bool16 	GetAltSuggestions(const PMString &rWord,  WideStringList& wList);

	/** Set the thesaurus filename */
	virtual	bool16 	Set(const PMString &rThesFileName);
	
private:
	/** Query the ICHLData */
	ICHLData *		QueryCHLData();

	/** Set the word list data based on the flag value */
	bool16 			GetCHLThesData(const PMString &rWord, WideStringList& wList, ThesWordListEnum flag);

	void*			fThesaurus;		// point to the thesaurus data file (not used in this example)
	PMString		fFileName;		// thes filename
	ThesRecord		fThesRecord;	// the last thesRecord
};

CREATE_PMINTERFACE(CHLThesaurus, kCHLThesaurusImpl)



/** CHLThesaurus::CHLThesaurus
*/
CHLThesaurus::CHLThesaurus(IPMUnknown * boss) :
	CPMUnknown<IThesaurusService>(boss),
		fThesaurus(nil)
{
}


/** CHLThesaurus::~CHLThesaurus
*/
CHLThesaurus::~CHLThesaurus()
{
}

/** CHLThesaurus::~CHLThesaurus
*/
bool16 CHLThesaurus::Set(const PMString &rThesFileName)
{
	fFileName = rThesFileName;
	
	return kTrue;
}

/** CHLThesaurus::GetThesRecord
*/
bool16 CHLThesaurus::GetThesRecord(const PMString &rWord, ThesRecord& thesRecord)
{
	bool16 retval = kFalse;
	InterfacePtr<ICHLData> pCHLData(this->QueryCHLData());

	do
	{
		//create and populate your thesaurus record...
       
		ThesDefinition thesDef;

		thesDef.fDefinitionStr.SetCString("My custom definition");
		thesDef.fPartOfSpeechStr.SetCString("noun");
		thesDef.fInflectionStr.SetCString("My custom inflection");
		
		WideString ws;

		ws.SetCString("Synalicious");
		thesDef.fSynonyms.push_back(ws);
		
		ws.SetCString("Anti-dote");
		thesDef.fAntonyms.push_back(ws);
		
		ws.SetCString("Comparilous");
		thesDef.fComparedWords.push_back(ws);
		
		ws.SetCString("Relationship");
		thesDef.fRelatedWords.push_back(ws);
		
		ws.SetCString("Contrastandcompare");
		thesDef.fContrastingWords.push_back(ws);

		thesRecord.fDefinitions.push_back(thesDef);

		fThesRecord = thesRecord;

		retval = kTrue;

	} while (kFalse);

	return retval;
}

/** CHLThesaurus::GetCHLThesData
*/
bool16 CHLThesaurus::GetCHLThesData(const PMString &rWord, WideStringList& wList, ThesWordListEnum flag)
{
	bool16 retval = kFalse;
	InterfacePtr<ICHLData> pCHLData(this->QueryCHLData());

	do
	{
		// populate your thesaurus word list...

		WideString ws;

		switch (flag)
		{
			case kSynonyms:
				ws.SetCString("Synalicious");
				break;
			case kAntonyms:
				ws.SetCString("Anti-dote");
				break;
			case kComparedWords:
				ws.SetCString("Comparilous");
				break;
			case kRelatedWords:
				ws.SetCString("Relationship");
				break;
			case kContrastingWords:
				ws.SetCString("Contrastandcompare");
				break;
			default:
				break;
		}

		retval = kTrue;

	} while (kFalse);

	return retval;
}

/** CHLThesaurus::GetSynonyms
*/
bool16 CHLThesaurus::GetSynonyms(const PMString &rWord, WideStringList& wList)
{
	return GetCHLThesData(rWord, wList, kSynonyms);
}

/** CHLThesaurus::GetAntonyms
*/
bool16 CHLThesaurus::GetAntonyms(const PMString &rWord, WideStringList& wList)
{
	return GetCHLThesData(rWord, wList, kAntonyms);
}

/** CHLThesaurus::GetNearSynonyms
*/
bool16 CHLThesaurus::GetNearSynonyms(const PMString &rWord, WideStringList& wList)
{
	return GetCHLThesData(rWord, wList, kRelatedWords);
}

/** CHLThesaurus::GetNearAntonyms
*/
bool16 CHLThesaurus::GetNearAntonyms(const PMString &rWord, WideStringList& wList)
{
	return GetCHLThesData(rWord, wList, kContrastingWords);
}

/** CHLThesaurus::GetSeeAlsoWords
*/
bool16 CHLThesaurus::GetSeeAlsoWords(const PMString &rWord, WideStringList& wList)
{
	return GetCHLThesData(rWord, wList, kComparedWords);
}

/** CHLThesaurus::GetAltSuggestions
*/
bool16 CHLThesaurus::GetAltSuggestions(const PMString &rWord,  WideStringList& wList)
{
	bool16 retval = kFalse;
	InterfacePtr<ICHLData> pCHLData(this->QueryCHLData());

	do
	{
		// populate your suggestions word list...

		retval = kTrue;

	} while (kFalse);

	return retval;
}

/** CHLThesaurus::QueryCHLData
*/
ICHLData * CHLThesaurus::QueryCHLData(void)
{
	ICHLData * pData = nil;

	InterfacePtr<ILanguage> pLanguage(this, IID_ILANGUAGE);
	ASSERT_MSG(pLanguage != nil, "CHLThesaurus - language is neutral.");
	
	if (pLanguage )
	{
#ifdef	DEBUG
		const PMString rName = pLanguage->GetLanguageName();
#endif
		
		ISession* session = GetExecutionContextSession();
		ASSERT_MSG(session != nil, "CHLThesaurus - session is nil.");
		
		InterfacePtr<IK2ServiceRegistry> pServices(session, IID_IK2SERVICEREGISTRY);
		ASSERT_MSG(pServices != nil, "CHLThesaurus - missing IK2ServiceRegistry at the session.");

		if (pServices)
		{
			InterfacePtr<IK2ServiceProvider> pCHL( pServices->QueryServiceProviderByClassID( kLinguisticService, kCHLinguisticBoss ) );
			ASSERT_MSG(pCHL != nil, "CHLThesaurus - can't find the CHL service provider.");
	
			if (pCHL)
			{
				InterfacePtr<ISpellingMgr> pSpellingMgr(pCHL, IID_ISPELLINGMGR);
				ASSERT_MSG(pSpellingMgr != nil, "CHLThesaurus - can't find the CHL's spelling manager.");
				
				if (pSpellingMgr)
				{
					InterfacePtr<ISpellingService> pSpellingService( pSpellingMgr->QueryServiceOfLanguage( pLanguage ) );
					ASSERT_MSG(pSpellingService != nil, "CHLThesaurus - can't find the spelling service for that language");
					
					if (pSpellingService)
					{
						pData = (ICHLData*)pSpellingService->QueryInterface( IID_ICHLINGUISTICDATA );
						ASSERT_MSG(pData != nil, "CHLThesaurus - missing IID_ICHLDATA at ISpellingService.");
					
#if ADOBE
						if (pData)
						{
							PMString rThesFileName = pData->GetThesFileName();
							
							if (fFileName != rThesFileName)
								pData->SetThesFileName(fFileName);
						}
#endif
					}
				}
			}
		}
	}
	
	return pData;
}





