//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUserDict.cpp $
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

#include "ICHLData.h"
#include "IUserDictService.h"
#include "IHyphenatedWord.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "ILinguisticMgr.h"
#include "ILinguisticServiceData.h"
#include "IPanelControlData.h"
#include "ISession.h"
#include "ISetVendorCmdData.h"
#include "ISpellingMgr.h"
#include "ISpellingPrefs.h"
#include "IPrivateSpellingUtils.h"
#include "IStringListData.h"
#include "IUserDictIterator.h"
#include "IVendorList.h"
#include "IXMLOutStream.h"
#include "ICHLUserDictUtils.h"
#include "IUserDictMgr.h"

#include "CAlert.h"
#include "StringUtils.h"
#include "CPMUnknown.h"
#include "CmdUtils.h"
#include "PMString.h"
#include "PreferenceUtils.h"
#include "Utils.h"
#include "UserDictWordList.h"

#include "CHLID.h"
#include "CHLUserDict.h"



/** Implements a user dictionary.
 *  One or more user dictionaries can be contained in a user dictionary service
 *
 *  @ingroup chlinguistic
 */

CREATE_PMINTERFACE(CHLUserDict, kCHLUserDictImpl)

/* CHLUserDict::CHLUserDict
 */
CHLUserDict::CHLUserDict(IPMUnknown * boss) :
	CPMUnknown<IUserDict>(boss),
		fUDCDataFile(nil),
		fLanguageID(kLanguageNeutral)
{
}

/* CHLUserDict::~CHLUserDict
 */
CHLUserDict::~CHLUserDict()
{
	/* Flush will write out the file */
//	Flush();

	/* delete the IDFile */
	if (fUDCDataFile)
	{
		delete fUDCDataFile;
		fUDCDataFile = nil;
	}
}

/* CHLUserDict::SetFilePathName
 */
void CHLUserDict::SetFilePathName(const PMString& filePath)
{
	fFilePathName = filePath;
}

/* CHLUserDict::GetFilePathName
 */
const PMString& CHLUserDict::GetFilePathName(void) const
{
	return fFilePathName;
}

/* CHLUserDict::SetDataFile
 */
void CHLUserDict::SetDataFile(void* dataFile)
{
	if (fUDCDataFile)
		Flush();

	fUDCDataFile = static_cast<IDFile*>(dataFile);
}

/* CHLUserDict::GetDataFile
 */
void* CHLUserDict::GetDataFile(void) const
{
	return fUDCDataFile;
}

/* CHLUserDict::Flush
 */
void CHLUserDict::Flush(void)
{
	if (fUDCDataFile != nil)
	{
		IXMLOutStream::eEncodingType encoding = IXMLOutStream ::kUTF16;
		ErrorCode ec = Utils<ICHLUserDictUtils>()->ExportCHLUserDictXML(*fUDCDataFile, this, fUserDictWordList, GetLanguageID(), encoding);
	}
}

PMString	CHLUserDict::GetDisplayName()
{
	PMString userDictPathName = GetFilePathName();

	if (userDictPathName.CharCount() > 0)
	{

#ifdef MACINTOSH
		CharCounter pos = userDictPathName.LastIndexOfWChar(kTextChar_Colon); // find the last colon
		if (pos == -1)
			pos = userDictPathName.LastIndexOfWChar(kTextChar_Solidus); // proximity 10 returns colons but lilo uses slash on mac.
#else
		CharCounter pos = userDictPathName.LastIndexOfWChar(kTextChar_ReverseSolidus);  // find the last slash
#endif
		if (pos > -1)
			userDictPathName.Remove(0, pos+1);

		userDictPathName.SetTranslatable(kFalse);
	}

	return userDictPathName;
}

/* CHLUserDict::GetUserDictWordList
 */
void CHLUserDict::GetUserDictWordList(UserDictWordList& userDictWordList)
{
	userDictWordList = fUserDictWordList;
}

/* CHLUserDict::SetUserDictWordList
 */
void CHLUserDict::SetUserDictWordList(const UserDictWordList& userDictWordList)
{
	fUserDictWordList = userDictWordList;
}

/* CHLUserDict::SetLanguage
 */
void CHLUserDict::SetLanguageID(LanguageID languageID)
{
	if (languageID != fLanguageID)
	{
		fLanguageID = languageID;
	}
}

/* CHLUserDict::QueryLanguage
 */
LanguageID	CHLUserDict::GetLanguageID(void)
{
	return fLanguageID;
}



/** Implements a user dictionary service.
 *
 *
 *  @ingroup chlinguistic
 */
class CHLUserDictService : public CPMUnknown<IUserDictService>
{
public:
							CHLUserDictService(IPMUnknown * boss);
	virtual					~CHLUserDictService();

	virtual	bool16			IsReadOnly(IUserDict* userDict);
	virtual bool16 			CloseNotClamFile();
	virtual bool16 			Flush();
	virtual	bool16			IsWordInMainDict(const WideString &rWord, const HyphenPoints *pPoints);

	virtual bool16			AddToUserDict(IUserDict* userDict, const UserDictWordList &constWordList, bool16 caseSensitive, bool16 addToNotList);
	virtual	bool16			AddToUserDict(IUserDict* userDict, const WideString &rWord, const HyphenPoints *pPoints, bool16 caseSensitive);
	virtual	bool16			RemoveFromUserDict(IUserDict* userDict, const WideString &rWord);
	virtual	bool16			ClearUserDict(IUserDict* userDict);

	virtual	bool16			RemoveFromMainDict(const WideString &rWord);
	virtual	bool16			UndoRemoveFromMainDict(const WideString &rWord);
	virtual	bool16			ClearRemovedFromMainDict(IUserDict* userDict);

	virtual	bool16			Bind(IUserDict* userDict, const WideString &rWord, const WideString &rReplace);
	virtual	bool16			Unbind(IUserDict* userDict, const WideString &rWord, const WideString &rReplace);

	virtual	UserDictType	GetCorrectedWord(IUserDict* userDict, const WideString &rWord, WideString *pCorrectedWord );
	virtual	bool16			GetHyphenatedWord(IUserDict* userDict, const WideString &rWord, WideString *pHyphenatedWord);

	virtual bool16			AddUserDictToSearchPath(IUserDict* userDict, int32 index, bool16 addToVendorList, bool16 initializing);
	virtual bool16			MoveUserDictInSearchPath(int32 oldIndex, int32 newIndex);
	virtual bool16			RemoveUserDictFromSearchPath(IUserDict* userDict);
	virtual bool16			ReplaceUserDictInSearchPath(IUserDict* originalUserDict, IUserDict* newUserDict);

 	virtual int32			QueryAllUserDictsInSearchPath(K2Vector<IUserDict*>& userDictList, bool16 bOpenFiles);
	virtual int32			RemoveAllUserDictsFromSearchPath(void);

	virtual IUserDict* 		QueryNotUserDict(void);

	virtual IUserDict* 		QueryMainUserDict(void);
	virtual bool16	 		SetMainUserDict(IUserDict* userDict);

	virtual IUserDict*		CreateNewUserDict(const PMString& filePathName, int16 createFlags);
	virtual bool16			MigrateUserDict(const IDFile& existingDictFile, const IDFile& newDictFile) {return kFalse;}

	virtual bool16			InitializePaths(void);

	virtual	void			FlushUserDicts(void);
	virtual	const PMString&	GetDefaultFilePathName(void) const;
	virtual	const PMString&	GetNotFilePathName(void) const;

private:
	K2Vector<IUserDict*>	fUserDictList;
	bool16					fPathsInitialized;
	IUserDict*				fNotUserDict;

			bool16			Add(CHLUserDict* userDict, IDFile* dataFile, const WideString &rWord, const HyphenPoints *pPoints) const;
			bool16			Remove(CHLUserDict* userDict, IDFile* dataFile, const WideString &rWord) const;

			bool16			GetHyphenWord(const WideString &rNewWord, const HyphenPoints *pPoints, WideString *pWord ) const;
			bool16			GetHyphenWord(const WideString &rNewWord, WideString *pWord) const;

			bool16			AddDefaultUserDictToPath(void);

	static	void			DamageText();
};

CREATE_PMINTERFACE(CHLUserDictService, kCHLUserDictServiceImpl)


/* CHLUserDictService::CHLUserDictService
 */
CHLUserDictService::CHLUserDictService(IPMUnknown * boss) :
	CPMUnknown<IUserDictService>(boss),
		fPathsInitialized(kFalse),
		fNotUserDict(nil)
{
	fPathsInitialized = InitializePaths();
}

/* CHLUserDictService::~CHLUserDictService
 */
CHLUserDictService::~CHLUserDictService()
{
	for (int32 i = 0; i < fUserDictList.size(); ++i)
	{
		ASSERT(fUserDictList[i]);
		fUserDictList[i]->Release();
	}

	if (fNotUserDict)
	{
		fNotUserDict->Release();
		fNotUserDict = nil;
	}
}

/* CHLUserDictService::FlushUserDicts
 */
void CHLUserDictService::FlushUserDicts(void)
{
	for (int32 i = 0; i < fUserDictList.size(); ++i)
	{
		ASSERT(fUserDictList[i]);
		fUserDictList[i]->Flush();
	}
}

/* CHLUserDictService::InitializePaths
 *
 * create a user dict object for each path saved in the vendor data
 */
bool16 CHLUserDictService::InitializePaths(void)
{
	InterfacePtr<ILanguage> language(this, UseDefaultIID());

    InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST) );
    InterfacePtr<ILanguage> sessionLanguage( sessionLangList->QueryLanguage( language->GetLanguageName() ) );
    InterfacePtr<IVendorList> spellVendor( sessionLanguage, IID_ISPELLVENDORLIST );
	IUserDict* userDict = nil;

	/* ensure the userdict mgr has loaded */
    InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
    InterfacePtr<IK2ServiceProvider> linguisticMgrService(serviceRegistry->QueryDefaultServiceProvider(kLinguisticManagerService));
    InterfacePtr<ILinguisticMgr> linguisticMgr(linguisticMgrService, IID_ILINGUISTICMGR);
    InterfacePtr<IK2ServiceProvider> provider(linguisticMgr->QueryProviderByClassID(kCHLinguisticBoss));
    if (provider)
    {
        InterfacePtr<IUserDictMgr> userDictMgr(provider,  IID_IUSERDICTMGR);
		ASSERT(userDictMgr);
	}

	if (spellVendor)
	{
		K2Vector<PMString> pathList;
		bool16 gotPathList = spellVendor->GetVendorPathList(kCHLinguisticBoss, pathList);

		if (gotPathList)
		{
			bool16 bDataMissing = kFalse;

			for (int32 i = 0; i < pathList.size(); ++i)
			{
				userDict = CreateNewUserDict(pathList[i], 0);
				if (userDict)
				{
					if (userDict->GetDataFile() == nil && pathList.size() > 1)
					{
						const PMString& pathName = userDict->GetFilePathName();
						const PMString& defaultPathName = this->GetDefaultFilePathName();

						if (i != 0 || pathName != defaultPathName)
							bDataMissing = kTrue;
					}

					bool16 bAddToVendorList = kFalse;
					bool16 bInitializing = kTrue;
					bool16 added = AddUserDictToSearchPath(userDict, -1, bAddToVendorList, bInitializing);	/* initialize the user dictionaries fUserDictionary list */
					if (!added)
						userDict->Release();
				}
			}

			if (bDataMissing)
			{
				PMString languageName = sessionLanguage->GetLanguageName();
				languageName.Translate();
				PMString warningText(kCHLMissingUserDictionaryInitKey);
				warningText.Translate();
				::ReplaceStringParameters( &warningText, languageName );
				CAlert::WarningAlert( warningText );
			}
		}
	}

	return kTrue;
}

/* CHLUserDictService::AddDefaultUserDictToPath
 *
 * create a user dict object for each path saved in the vendor data
 */
bool16 CHLUserDictService::AddDefaultUserDictToPath(void)
{
	InterfacePtr<ILanguage> language(this, UseDefaultIID());

    InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST) );
    InterfacePtr<ILanguage> sessionLanguage( sessionLangList->QueryLanguage( language->GetLanguageName() ) );
    InterfacePtr<IVendorList> spellVendor( sessionLanguage, IID_ISPELLVENDORLIST );
	IUserDict* userDict = nil;

	if (spellVendor)
	{
		K2Vector<PMString> pathList;
		bool16 gotPathList = spellVendor->GetVendorPathList(kCHLinguisticBoss, pathList);

		if (gotPathList)
		{
			InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
			PMString defaultPath = chlData->GetIsWordUDCFileName();

			userDict = CreateNewUserDict(defaultPath, 0);
			if (userDict)
			{
				bool16 bAddToVendorList = kTrue;
				bool16 bInitializing = kFalse;
				bool16 added = AddUserDictToSearchPath(userDict, -1, bAddToVendorList, bInitializing);
				if (!added)
					userDict->Release();
			}
		}
	}
	return kTrue;
}

/* CHLUserDictService::Add
 */
bool16 CHLUserDictService::Add(CHLUserDict* userDict, IDFile* dataFile, const WideString &rWord, const HyphenPoints *pPoints) const
{
	ASSERT(userDict);
	ASSERT(dataFile);

	if (! userDict || !rWord.Length() || !dataFile)
		return kFalse;

	InterfacePtr<const ICHLData> chlData(this, UseDefaultIID());

	UserDictWordList userDictWordList;
	userDict->GetUserDictWordList(userDictWordList);

	/* Check to see if we are setting the hyphenation of a word */
	WideString aWord;
	if (this->GetHyphenWord(rWord, pPoints, &aWord))
	{
		/* handle any special processing for hyphen words */
		/* ... */

		userDictWordList.InsertUnique(aWord);
	}
	else
	{
		userDictWordList.InsertUnique(rWord);
	}

	userDict->SetUserDictWordList(userDictWordList);

	return kTrue;
}

/* CHLUserDictService::Remove
 */
bool16 CHLUserDictService::Remove(CHLUserDict* userDict, IDFile* dataFile, const WideString &rWord) const
{
	//ASSERT(userDict);
	ASSERT(dataFile);

	if (! userDict || !rWord.Length() || !dataFile)
		return kFalse;

	InterfacePtr<const ICHLData> chlData(this, UseDefaultIID());

	UserDictWordList userDictWordList;

	userDict->GetUserDictWordList(userDictWordList);
	int32 location = userDictWordList.ExactLocation(rWord);
	if (location >= 0)
	{
		userDictWordList.Remove(location);
		userDict->SetUserDictWordList(userDictWordList);
	}

	return kTrue;
}

/* CHLUserDictService::Flush
 */
bool16 CHLUserDictService::Flush()
{
	return kTrue;
}

/* CHLUserDictService::CloseNotClamFile
 */
bool16 CHLUserDictService::CloseNotClamFile()
{
	return kTrue;
}

/* CHLUserDictService::IsReadOnly
 */
bool16 CHLUserDictService::IsReadOnly(IUserDict* userDict)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	if (! chlData)
		return kFalse;

	bool16 bReadOnly = kFalse;
	IDFile* dataFile = nil;
	if (! userDict)
	{
		if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		{
			dataFile = static_cast<IDFile*>(fUserDictList[0]->GetDataFile());
		}
		else
		{
			dataFile = chlData->GetIsWordUDC(kFalse);	//try to get the default udc, but don't create a new one
		}
	}
	else
		dataFile = static_cast<IDFile*>(userDict->GetDataFile());

	// perform read only check ...

	return bReadOnly;
}

/* CHLUserDictService::IsWordInMainDict
 */
bool16 CHLUserDictService::IsWordInMainDict(const WideString &rWord, const HyphenPoints *pPoints)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	if (! chlData)
		return kFalse;

	PMString fileName = chlData->GetIsWordUDCFileName();

	IDFile* dataFile = nil;

	if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		dataFile = static_cast<IDFile*>(fUserDictList[0]->GetDataFile());
	else
		dataFile = chlData->GetIsWordUDC(kFalse);

	if (! dataFile)
		return kFalse;

	// handle check of the main dictionary ...

	return kFalse;
}


/* CHLUserDictService::AddToUserDict
 * There is an implicit dependency to RemoveFromMainDict() because you don't want to allow words
 * that are removed from the main dict:

 *	AddToUserDict("car")			=> UndoRemoveFromMainDict("car");
 *	RemoveFromUserDict("car")		=> (nothing)
 */
bool16 CHLUserDictService::AddToUserDict(IUserDict* userDict, const WideString &rWord, const HyphenPoints *pPoints, bool16 caseSensitive)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());

	IDFile* dataFile = nil;
	if (! userDict)
	{
		if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		{
			userDict = fUserDictList[0];
			ASSERT(userDict);
			dataFile = static_cast<IDFile*>(userDict->GetDataFile());
		}
		else
		{
			PMString fileName = chlData->GetIsWordUDCFileName();
			int16 createFlags = 1;

			userDict = CreateNewUserDict(fileName, createFlags);	/* get the default udc and if it does not exist create it */
			if (userDict)
			{
				bool16 bAddToVendorList = kTrue;
				bool16 bInitializing = kFalse;
				bool16 added = this->AddUserDictToSearchPath(userDict, -1, bAddToVendorList, bInitializing);

				dataFile = static_cast<IDFile*>(userDict->GetDataFile());

				if (!added)
					userDict->Release();
			}
		}
	}
	else
		dataFile = static_cast<IDFile*>(userDict->GetDataFile());

	if (!dataFile && userDict)
	{
		dataFile = chlData->CreateNewUDC(userDict->GetFilePathName());
		if (dataFile)
			userDict->SetDataFile(dataFile);
	}
	if (!dataFile)
		return kFalse;

	/* now handle case insensitive words */
	if (!caseSensitive)
	{
		const_cast<WideString&>(rWord).ToLower();	/* lowercase implies "case in-sensitive" in the proximity lib */
	}

	if (!this->Add(static_cast<CHLUserDict*>(userDict), dataFile, rWord, pPoints))
		return kFalse;
	
	userDict->Flush();

	const bool16 bRemoved = this->UndoRemoveFromMainDict(rWord);

	this->DamageText();

	return kTrue;
}

/* CHLUserDictService::AddToUserDict
 *
 * Is called by the ImportUserDict code
 */
bool16 CHLUserDictService::AddToUserDict(IUserDict* userDict, const UserDictWordList& constWordList, bool16 caseSensitive, bool16 addToNotList)
{
	for (int32 i = 0; i < constWordList.Length(); i++)
	{
		bool16 added = AddToUserDict(userDict, constWordList[i], nil, caseSensitive);
	}
	return kTrue;
}

/* CHLUserDictService::GetHyphenWord
 */
bool16 CHLUserDictService::GetHyphenWord(const WideString &rNewWord, const HyphenPoints *pPoints, WideString *pWord ) const
{
	if (!pWord || !pPoints || pPoints->size() == 0 || rNewWord.Length() == 0)
		return kFalse;
	*pWord = rNewWord;

	const int32 nMax = pPoints->size();
	const int32 nLength = rNewWord.Length();
	int32 nDelta = 0;

	for(int32 i = 0; i < nMax; ++i)
	{
		int32 nIdx = (*pPoints)[i].Key();
		if (nIdx >= nLength)
			return nDelta > 0;
		nIdx += nDelta;

		const int32 nHyph = (*pPoints)[i].Value();

		uchar cUDCHyph;

		if (nHyph < IHyphenatedWord::kRegularHyphenPoint)
			cUDCHyph = HY_UNPREF;
		else if (nHyph < IHyphenatedWord::kPreferredHyphenPoint)
			cUDCHyph = HY_NORM;
		else
			cUDCHyph = HY_PREF;

		pWord->Insert(cUDCHyph, nIdx);
		++nDelta;
	}
	return nDelta > 0;
}

/* CHLUserDictService::GetHyphenWord
 */
bool16 CHLUserDictService::GetHyphenWord(const WideString &rNewWord, WideString *pWord ) const
{
    bool16 wordHasHyphens = kFalse;

	if (!pWord || rNewWord.Length() == 0)
		return kFalse;

	pWord->Clear();

	WideString wNewWord(rNewWord);

	const int32 nMax =  wNewWord.Length();
	const uchar16 cEscape = '\\';
	const uchar16 cHyph = '~';
	for(int32 i = 0; i < nMax; ++i)
	{
		UTF32TextChar cChar (wNewWord.GetChar(i));
		switch(cChar.GetValue())
		{
			case cEscape :
			{
				// skip hyphen
				if ( i+1 < nMax && (wNewWord[i+1] == cHyph || wNewWord[i+1] == cEscape))
				{
					++i;
					cChar = wNewWord.GetChar(i);
					pWord->Append(cChar);
				}
				break;
			}
			case cHyph :
			{
				int32 nHyph = 0;
				wordHasHyphens = kTrue;
				while(i < nMax && wNewWord[i] == cHyph)
				{
					++nHyph;
					++i;
				}
				uchar cUDCHyph;
				if (nHyph < IHyphenatedWord::kRegularHyphenPoint)
					cUDCHyph = HY_UNPREF;
				else if (nHyph < IHyphenatedWord::kPreferredHyphenPoint)
					cUDCHyph = HY_NORM;
				else
					cUDCHyph = HY_PREF;

				pWord->Append(cUDCHyph);
				if (i < nMax)
					--i;
				break;
			}
			default:
			{
				cChar = wNewWord.GetChar(i);
				pWord->Append(cChar);
				break;
			}
		}
	}

	return wordHasHyphens;
}

/* CHLUserDictService::RemoveFromUserDict
 */
bool16 CHLUserDictService::RemoveFromUserDict(IUserDict* userDict, const WideString &rWord)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());

	IDFile* dataFile = nil;
	if (! userDict)
	{
		if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		{
			dataFile = static_cast<IDFile*>(fUserDictList[0]->GetDataFile());
		}
		else
		{
			dataFile = chlData->GetIsWordUDC(kFalse);
		}
	}
	else
		dataFile = static_cast<IDFile*>(userDict->GetDataFile());

	bool16 status = this->Remove(static_cast<CHLUserDict*>(userDict), dataFile, rWord);
	userDict->Flush();	// write out to file
	
 	this->DamageText();
	
	return status;
}

/* CHLUserDictService::RemoveFromMainDict
 *
 *  Usually you cannot remove words from the main dict. The trick is that a special user dict contains
 *  words that need to be ignored before the spelling ist started.
 *  Implicit dependency to AddToUserDict():
 *
 *  RemoveFromMainDict("car")		=> RemoveFromUserDict("car");
 *  UndoRemoveFromMainDict("car")	=> (nothing)
 */
bool16 CHLUserDictService::RemoveFromMainDict(const WideString &rWord)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	InterfacePtr<IUserDict> notUserDict(QueryNotUserDict());

	IDFile* dataFile = static_cast<IDFile*>(notUserDict->GetDataFile());
	if (!dataFile && notUserDict)
	{
		dataFile = chlData->CreateNewUDC(notUserDict->GetFilePathName());
		if (dataFile)
			notUserDict->SetDataFile(dataFile);
	}

	if (!this->Add(static_cast<CHLUserDict*>((IUserDict*)notUserDict), dataFile /*chlData->GetNotWordUDC(kTrue)*/, rWord, nil))
		return kFalse;

	const bool16 bRemoved = this->RemoveFromUserDict(nil, rWord);
    return kTrue;
}

/* CHLUserDictService::UndoRemoveFromMainDict
 */
bool16 CHLUserDictService::UndoRemoveFromMainDict(const WideString &rWord)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	return this->Remove(nil, chlData->GetNotWordUDC(kFalse), rWord);
}

/* CHLUserDictService::Bind
 */
bool16 CHLUserDictService::Bind(IUserDict* userDict, const WideString &rFrom, const WideString &rTo)
{
	return kFalse;
}


/* CHLUserDictService::Unbind
 */
bool16 CHLUserDictService::Unbind(IUserDict* userDict, const WideString &rFrom, const WideString &rTo)
{
	return kFalse;
}

/* CHLUserDictService::GetCorrectedWord
 */
IUserDictService::UserDictType CHLUserDictService::GetCorrectedWord(IUserDict* userDict, const WideString &rWord, WideString *pCorrectedWord )
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());

	IDFile* dataFile = nil;
	if (! userDict)
	{
		if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		{
			userDict = fUserDictList[0];
			dataFile = static_cast<IDFile*>(userDict->GetDataFile());
		}
		else
		{
			dataFile = chlData->GetIsWordUDC(kTrue);
		}
	}
	else
	{
		dataFile = static_cast<IDFile*>(userDict->GetDataFile());
	}

	if (!dataFile && userDict)
	{
		dataFile = chlData->CreateNewUDC(userDict->GetFilePathName());
		if (dataFile)
			userDict->SetDataFile(dataFile);
	}
	if (!dataFile)
		return kNone;

	pCorrectedWord->Clear();

	// Your service should return the user dict type the word matches...

	// if we don't know it return kNone
	*pCorrectedWord = rWord;

	return kNone;
}

/* CHLUserDictService::GetHyphenatedWord
 */
bool16 CHLUserDictService::GetHyphenatedWord(IUserDict* userDict, const WideString& rWord, WideString* pHyphenatedWord)
{
	pHyphenatedWord->Clear();

	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());

	IDFile* dataFile = nil;
	if (! userDict)
	{
		if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		{
			userDict = fUserDictList[0];
			dataFile = static_cast<IDFile*>(userDict->GetDataFile());
		}
		else
		{
			dataFile = static_cast<IDFile*>(chlData->GetIsWordUDC(kTrue));
		}
	}
	else
		dataFile = static_cast<IDFile*>(userDict->GetDataFile());

	if (!dataFile && userDict)
	{
		dataFile = chlData->CreateNewUDC(userDict->GetFilePathName());
		if (dataFile)
			userDict->SetDataFile(dataFile);
	}
	if (!dataFile)
		return kFalse;

	//handle setting the hyphen points (if any) ...

	*pHyphenatedWord = rWord;

	return kTrue;
}

/* CHLUserDictService::ClearUserDict
 */
bool16 CHLUserDictService::ClearUserDict(IUserDict* userDict)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	if (! chlData)
		return kFalse;

	IDFile* dataFile = nil;
	if (! userDict)
	{
		if (fUserDictList.size() > 0 && fUserDictList[0] != nil)
		{
			dataFile = static_cast<IDFile*>(fUserDictList[0]->GetDataFile());
		}
		else
		{
			dataFile = chlData->GetIsWordUDC(kFalse);
		}
	}
	else
	{
		dataFile = static_cast<IDFile*>(userDict->GetDataFile());
	}

	if (! dataFile)
		return kFalse;

	bool16 done = kFalse;
	bool16 retval = kTrue;
	WideString wWord;
	bool16 wordRemoved = kFalse;

	do
	{
		InterfacePtr<IUserDictIterator> udIterator(this, IID_IUSERDICTITERATOR);
		if (udIterator->First(this, userDict, IUserDictService::kIsAWord, &wWord))
		{
			bool16 removed = this->Remove(static_cast<CHLUserDict*>(userDict), dataFile, wWord);
			ASSERT(removed);	//we expect this to succeed so for now assert
			if (!removed)
			{
				done = kTrue;
				retval = kFalse;
			}
			wordRemoved |= removed;
		}
		else
			done = kTrue;
	} while (! done);
	
	
	if (retval){
		userDict->Flush();	// write out to file
		this->DamageText();
	}
	

	return retval;
}

/*  CHLUserDictService::ClearRemovedFromMainDict
 */
bool16 CHLUserDictService::ClearRemovedFromMainDict(IUserDict* userDict)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	if (! chlData)
		return kFalse;

	IDFile *dataFile = chlData->GetNotWordUDC(kFalse);
	if (! dataFile)
		return kFalse;

	bool16 done = kFalse;
	bool16 retval = kTrue;
	WideString wWord;
	bool16 wordRemoved = kFalse;

	do
	{
		InterfacePtr<IUserDictIterator> udIterator(this, IID_IUSERDICTITERATOR);
		if (udIterator->First(this, userDict, IUserDictService::kNotAWord, &wWord))
		{
			bool16 removed = this->Remove(static_cast<CHLUserDict*>(userDict), dataFile, wWord);
			ASSERT(removed);	//we expect this to succeed so for now assert
			if (!removed)
			{
				done = kTrue;
				retval = kFalse;
			}
			wordRemoved |= removed;
		}
		else
			done = kTrue;
	} while (! done);

	return retval;
}

/* CHLUserDictService::AddUserDictToSearchPath
 */
bool16	CHLUserDictService::AddUserDictToSearchPath(IUserDict* userDict, int32 index, bool16 addToVendorList, bool16 initializing)
{
	ASSERT(userDict != nil);
	ASSERT(index <= (int32)fUserDictList.size());

	if (! userDict || index > (int32)fUserDictList.size())
		return kFalse;

	const PMString& filePath = userDict->GetFilePathName();

	for (int32 i = 0; i < fUserDictList.size();  ++i)
	{
		ASSERT(fUserDictList[i]);
		if (filePath == fUserDictList[i]->GetFilePathName())
			return kFalse;
	}

	if (index < 0)
		fUserDictList.push_back(userDict);
	else
		fUserDictList.insert(fUserDictList.begin() + index, userDict);

	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	chlData->AddSearchPath(! initializing);

	if (addToVendorList)
	{
		InterfacePtr<ILanguage> language(this, UseDefaultIID());

		/* grab the session language, which contains the vendor */
		InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST) );
		InterfacePtr<ILanguage> sessionLanguage( sessionLangList->QueryLanguage( language->GetLanguageName() ) );
		InterfacePtr<IVendorList> spellVendor( sessionLanguage, IID_ISPELLVENDORLIST );

		if (spellVendor)
		{
			const PMString& fileName = userDict->GetFilePathName();

			K2Vector<PMString> pathList;
			bool16 gotPathList = spellVendor->GetVendorPathList(kCHLinguisticBoss, pathList);
			if (gotPathList)
			{
				if (index < 0)
					pathList.push_back(fileName);
				else
					pathList.insert(pathList.begin() + index, fileName);

				ASSERT(pathList.size() == fUserDictList.size());

				InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetVendorPathListCmdBoss));
				InterfacePtr<ILanguage> cmdLanguage(cmd, UseDefaultIID());
				if (cmdLanguage)
					cmdLanguage->CopyFrom(language);
				InterfacePtr<IStringListData> stringListData(cmd, UseDefaultIID());
				stringListData->SetStringList(pathList);
				InterfacePtr<ISetVendorCmdData> vendorCmdData(cmd, IID_IVENDORCMDDATA);
				vendorCmdData->SetDefaultVendor(kCHLinguisticBoss);
				vendorCmdData->SetVendorID(IID_ISPELLVENDORLIST);

				do
				{
					ErrorCode errCode;
					{
						InterfacePtr<ICommand> enableCommandPassThrough(CmdUtils::CreateCommand(kEnableCommandPassThroughCmdBoss));
						CmdUtils::ProcessCommand (enableCommandPassThrough);
					}
					if (initializing)
						errCode = CmdUtils::ProcessCommand(cmd);
					else
					{
						cmd->SetUndoability(ICommand::kAutoUndo);
						errCode = CmdUtils::ProcessCommand(cmd);
					}
					ASSERT(errCode == kSuccess);
					{
						InterfacePtr<ICommand> disableCommandPassThrough(CmdUtils::CreateCommand(kDisableCommandPassThroughCmdBoss));
						CmdUtils::ProcessCommand (disableCommandPassThrough);
					}
				} while (kFalse);

			}
		}
	}

	return kTrue;
}

bool16	CHLUserDictService::MoveUserDictInSearchPath(int32 oldIndex, int32 newIndex)
{
	ASSERT(oldIndex <= static_cast<int32>(fUserDictList.size()) && oldIndex >= 0);
	ASSERT(newIndex <= static_cast<int32>(fUserDictList.size()));

	if ((oldIndex > static_cast<int32>(fUserDictList.size()) || oldIndex < 0) || newIndex > static_cast<int32>(fUserDictList.size()))
		return kFalse;

	/* re-order the dictionaries */
	IUserDict* dictToMove = fUserDictList[oldIndex];
	
	/* remove the dictionary, and re-insert it */
	fUserDictList.erase(fUserDictList.begin() + oldIndex);
	bool16 moved = RemoveUserDictFromSearchPath(dictToMove);

	moved = AddUserDictToSearchPath(dictToMove, newIndex, kTrue, kFalse);
	ASSERT(moved);

	return moved;
}

/* CHLUserDictService::RemoveUserDictFromSearchPath
 */
bool16	CHLUserDictService::RemoveUserDictFromSearchPath(IUserDict* userDict)
{
	const PMString& fileName = userDict->GetFilePathName();

	for (int32 i = 0; i < fUserDictList.size(); ++i)
	{
		if (userDict == fUserDictList[i])
		{
			fUserDictList.erase(fUserDictList.begin() + i);

			userDict->Flush();	/* write out file */
			userDict->Release();

			InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
			chlData->RemoveSearchPath(kTrue);

			InterfacePtr<ILanguage> language(this, UseDefaultIID());

			/* grab the session language, which contains the vendor */
			InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST) );
			InterfacePtr<ILanguage> sessionLanguage( sessionLangList->QueryLanguage( language->GetLanguageName() ) );
			InterfacePtr<IVendorList> spellVendor( sessionLanguage, IID_ISPELLVENDORLIST );

			if (spellVendor)
			{
				//const PMString& fileName = userDict->GetFilePathName();
				//bool16	pathRemoved = spellVendor->RemovePathFromVendorList(kCHLinguisticBoss, fileName);
				//ASSERT(pathRemoved);

				K2Vector<PMString> pathList;
				bool16 gotPathList = spellVendor->GetVendorPathList(kCHLinguisticBoss, pathList);
				if (gotPathList)
				{
					bool16 foundPath = kFalse;
					for (int32 j = 0; j < pathList.size(); ++j)
					{
						if (fileName == pathList[j])
						{
							pathList.erase(pathList.begin() + j);
							foundPath = kTrue;
							break;
						}
					}

					ASSERT(pathList.size() == fUserDictList.size());

					if (foundPath)
					{
						InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetVendorPathListCmdBoss));
						InterfacePtr<ILanguage> cmdLanguage(cmd, UseDefaultIID());
						if (cmdLanguage)
							cmdLanguage->CopyFrom(language);
						InterfacePtr<IStringListData> stringListData(cmd, UseDefaultIID());
						stringListData->SetStringList(pathList);
						InterfacePtr<ISetVendorCmdData> vendorCmdData(cmd, IID_IVENDORCMDDATA);
						vendorCmdData->SetDefaultVendor(kCHLinguisticBoss);
						vendorCmdData->SetVendorID(IID_ISPELLVENDORLIST);
						{
							{
								InterfacePtr<ICommand> enableCommandPassThrough(CmdUtils::CreateCommand(kEnableCommandPassThroughCmdBoss));
								CmdUtils::ProcessCommand (enableCommandPassThrough);
							}
							cmd->SetUndoability(ICommand::kAutoUndo);
							ErrorCode errCode = CmdUtils::ProcessCommand(cmd);

							{
								InterfacePtr<ICommand> disableCommandPassThrough(CmdUtils::CreateCommand(kDisableCommandPassThroughCmdBoss));
								CmdUtils::ProcessCommand (disableCommandPassThrough);
							}
							ASSERT(errCode == kSuccess);
						}
					}
				}
			}
			break;
		}
	}

	return kTrue;
}

/* CHLUserDictService::ReplaceUserDictInSearchPath
 */
bool16	CHLUserDictService::ReplaceUserDictInSearchPath(IUserDict* originalUserDict, IUserDict* newUserDict)
{
	ASSERT(originalUserDict);
	ASSERT(newUserDict);

	bool16 bFound = kFalse;

	for (int32 i = 0; i < fUserDictList.size(); ++i)
	{
		if (originalUserDict == fUserDictList[i])
		{
			bFound = kTrue;

			fUserDictList[i] = newUserDict;

			originalUserDict->Flush();	/* write out file */
			originalUserDict->Release();

			InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
			chlData->RemoveSearchPath(kTrue);

			InterfacePtr<ILanguage> language(this, UseDefaultIID());

			/* grab the session language, which contains the vendor */
			InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST) );
			InterfacePtr<ILanguage> sessionLanguage( sessionLangList->QueryLanguage( language->GetLanguageName() ) );
			InterfacePtr<IVendorList> spellVendor( sessionLanguage, IID_ISPELLVENDORLIST );

			if (spellVendor)
			{
				const PMString& newFileName = newUserDict->GetFilePathName();
				const PMString& origFileName = originalUserDict->GetFilePathName();

				K2Vector<PMString> pathList;
				bool16 gotPathList = spellVendor->GetVendorPathList(kCHLinguisticBoss, pathList);
				if (gotPathList)
				{
					bool16 foundPath = kFalse;
					for (int32 j = 0; j < pathList.size(); ++j)
					{
						if (origFileName == pathList[j])
						{
							pathList[j] = newFileName;
							foundPath = kTrue;
							break;
						}
					}

					if (pathList.size() == 0)
					{
						pathList.push_back(newFileName);
						foundPath = kTrue;
					}

					if (foundPath)
					{
						InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetVendorPathListCmdBoss));
						InterfacePtr<ILanguage> cmdLanguage(cmd, UseDefaultIID());
						if (cmdLanguage)
							cmdLanguage->CopyFrom(language);
						InterfacePtr<IStringListData> stringListData(cmd, UseDefaultIID());
						stringListData->SetStringList(pathList);
						InterfacePtr<ISetVendorCmdData> vendorCmdData(cmd, IID_IVENDORCMDDATA);
						vendorCmdData->SetDefaultVendor(kCHLinguisticBoss);
						vendorCmdData->SetVendorID(IID_ISPELLVENDORLIST);

						do
						{
							{
								InterfacePtr<ICommand> enableCommandPassThrough(CmdUtils::CreateCommand(kEnableCommandPassThroughCmdBoss));
								CmdUtils::ProcessCommand (enableCommandPassThrough);
							}
							cmd->SetUndoability(ICommand::kAutoUndo);
							ErrorCode errCode = CmdUtils::ProcessCommand(cmd);
							{
								InterfacePtr<ICommand> disableCommandPassThrough(CmdUtils::CreateCommand(kDisableCommandPassThroughCmdBoss));
								CmdUtils::ProcessCommand (disableCommandPassThrough);
							}
							ASSERT(errCode == kSuccess);
						} while (kFalse);

					}
				}
			}

			break;
		}
	}

	return bFound;
}

/* CHLUserDictService::QueryAllUserDictsInSearchPath
 */
int32	CHLUserDictService::QueryAllUserDictsInSearchPath(K2Vector<IUserDict*>& userDictList, bool16 bOpenFiles)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());

	for (int32 i = 0; i < fUserDictList.size(); ++i)
	{
		if (fUserDictList[i])
		{
			if (! fUserDictList[i]->GetDataFile() && bOpenFiles)
			{
				void* udc = chlData->GetUDC(fUserDictList[i]->GetFilePathName());
				if (udc)
				{
					fUserDictList[i]->SetDataFile(udc);
				}
			}
		}
	}

	userDictList = fUserDictList;

	return static_cast<int32>(userDictList.size());
}

/* CHLUserDictService::RemoveAllUserDictsFromSearchPath
 */
int32	CHLUserDictService::RemoveAllUserDictsFromSearchPath(void)
{
	int32 numUserDictionariesRemoved = 0;

	return numUserDictionariesRemoved;
}

/* CHLUserDictService::QueryNotUserDict
 */
IUserDict*	CHLUserDictService::QueryNotUserDict(void)
{
	if (! fNotUserDict)
		fNotUserDict = CreateNewUserDict(GetNotFilePathName(), 0);

	if (fNotUserDict)
		fNotUserDict->AddRef();

	return fNotUserDict;
}

/* CHLUserDictService::QueryMainUserDict
 */
IUserDict*	CHLUserDictService::QueryMainUserDict(void)
{
	IUserDict* userDict = nil;

	if (fUserDictList.size() > 0)
	{
		userDict = fUserDictList[0];	/* it's the first one in the search path */
		ASSERT(userDict);
		if (userDict)
			userDict->AddRef();
	}

	return userDict;
}

/* CHLUserDictService::SetMainUserDict
 */
bool16 CHLUserDictService::SetMainUserDict(IUserDict* userDict)
{
	return kFalse;
}

/* CHLUserDictService::CreateNewUserDict
 * create flags	0 = do not create, 1 = create if not found, 2 = always create
 */
IUserDict*	CHLUserDictService::CreateNewUserDict(const PMString& filePathName, int16 createFlags)
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());

	IUserDict* userDict = (IUserDict*)::CreateObject(kCHLUserDictBoss, IID_IUSERDICT);
	ASSERT(userDict != nil);

	/* Now add it to the search path */
	userDict->SetFilePathName(filePathName);
	IDFile* dataFile = nil;

	if (createFlags == 0 || createFlags == 1)
	{
		dataFile = chlData->GetUDC(filePathName);

		if (dataFile && dataFile->Exists())
		{
			IXMLOutStream::eEncodingType encoding = IXMLOutStream ::kUTF16;
			ErrorCode ec = Utils<ICHLUserDictUtils>()->ImportCHLUserDictXML(*dataFile, userDict /*, fUserDictWordList, fLanguage, encoding*/);
		}
	}
	if (!dataFile && createFlags > 0)
	{
		dataFile = chlData->CreateNewUDC(filePathName);
	}

	//may be nil
	//ASSERT(dataFile);

	userDict->SetDataFile((void*)dataFile);

	//InterfacePtr<ILanguage> language(userDict, UseDefaultIID());
	//if (language)
	//{
	//	InterfacePtr<ILanguage> serviceLanguage(this, UseDefaultIID());
	//	language->CopyFrom(serviceLanguage);
	//}

	CHLUserDict* chlUserDict = static_cast<CHLUserDict*>(userDict);
	if (chlUserDict)
	{
		InterfacePtr<ILanguage> serviceLanguage(this, UseDefaultIID());
		chlUserDict->SetLanguageID(serviceLanguage->GetLanguageID());
	}

	return userDict;
}

/* CHLUserDictService::DamageText
 */
void CHLUserDictService::DamageText()
{
	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	bool16 dsc = spellingPrefs->GetDynamicSpellCheck();
	if (dsc) {
		Utils<IPrivateSpellingUtils>()->DeleteCacheAndInvalAllDocWindows(kTrue);
	}
}


/* CHLUserDictService::GetDefaultFilePathName
*/
const PMString&	CHLUserDictService::GetDefaultFilePathName(void) const
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	return chlData->GetIsWordUDCFileName();
}

/* CHLUserDictService::GetNotFilePathName
*/
const PMString&	CHLUserDictService::GetNotFilePathName(void) const
{
	InterfacePtr<ICHLData> chlData(this, UseDefaultIID());
	return chlData->GetNotWordUDCFileName();
}

