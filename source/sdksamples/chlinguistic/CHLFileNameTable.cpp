//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLFileNameTable.cpp $
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
#include "ILinguisticServiceData.h"
#include "IInCopyApp.h"

// General includes:
#include "CAlert.h"
#include "CPMUnknown.h"
#include "K2Vector.h"
#include "LanguageID.h"
#include "LinguisticID.h"
#include "Trace.h"

// Project includes:
#include "CHLID.h"
#include "CHLUtils.h"
#include "ICHLFileNameTable.h"

#include "LocaleSetting.h"
#include "ICUForwardDeclare.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "IWorkspace.h"
#include "UIDList.h"
#include "LocaleSetting.h"

#include <string>

// ICU includes
#include "unicode/unistr.h"
#include "unicode/brkiter.h"
#include "unicode/dbbi.h"
#include "unicode/stsearch.h"
#include "unicode/uloc.h"
#include "unicode/ucol.h"
#include "unicode/coll.h"



/** A table defining the data files that drive the linguistic services
	provided by this plug-in.
*/
struct CHDefaultData 
{
	LanguageID	fLanguageID;
	CString		fLanguageName;
	CString		fPrimaryLanguageName;
	CString		fSubLanguageName;
	CString		fCoreFileName;
	CString		fHyphFileName;
	CString		fThesaurusFileName;
	CString		fDefaultUserDictFileName;
	U_ICU_NAMESPACE::Locale		fICULocale;
};

static const int32 kCHDefaultTableLength = 2;

/** Global instance of CHDefaultData. 
 * 	@see CHDefaultData
 */
static const CHDefaultData kCHDefaultTable [kCHDefaultTableLength] =
{
	{
		// "Bulgarian" language
		MakeLanguageID(kLanguageBulgarian, kSubLanguageDefault), 
		kCHLanguageNameBulgarianKey, 
		kCHPrimaryLanguageNameBulgarian, 
		kCHSubLanguageNameBulgarianNull, 
		kCHCoreFileNameBulgarian, 
		kCHHyphFileNameBulgarian,
		kCHThesaurusFileNameBulgarian,
		kCHUserDictFileNameBulgarian,
		U_ICU_NAMESPACE::Locale("","","")
	},
	{
		// "Hungarian" language
		MakeLanguageID(kLanguageHungarian, kSubLanguageDefault), 
		kCHLanguageNameHungarianKey, 
		kCHPrimaryLanguageNameHungarian, 
		kCHSubLanguageNameHungarianNull, 
		kCHCoreFileNameHungarian, 
		kCHHyphFileNameHungarian,
		kCHThesaurusFileNameHungarian,
		kCHUserDictFileNameHungarian,
		U_ICU_NAMESPACE::Locale("","","")
	}
};

struct CHICUData 
{
	char*		fICULanguageCode;				// ISO-639 code
	char*		fICUCountryCode;				// ISO-3166 code
	char*		fICUVariantCode;

	CHDefaultData	fCHDefaultData;
};

static const int32 kCHICUTableLength = 4;

static const CHICUData kCHICUTable [kCHICUTableLength] =
{
	{
		// "English - Zambia" language
		"en", 
		"ZM", 
		"", 
	  {
		MakeLanguageID(kLanguageUseICULocale, kSubLanguageDefault), 
		nil, 
		nil, 
		nil, 
		kCHCoreFileNameEnglishZambia, 
		kCHHyphFileNameEnglishZambia,
		kCHThesaurusFileNameEnglishZambia,
		kCHUserDictFileNameEnglishZambia,
		U_ICU_NAMESPACE::Locale("","","")
	  }
	},
	{
		// "Bemba - Zambia" language
		"bem", 
		"ZM", 
		"", 
	  {
		MakeLanguageID(kLanguageUseICULocale, kSubLanguageDefault), 
		nil, 
		nil, 
		nil, 
		kCHCoreFileNameBembaZambia, 
		kCHHyphFileNameBembaZambia,
		kCHThesaurusFileNameBembaZambia,
		kCHUserDictFileNameBembaZambia,
		U_ICU_NAMESPACE::Locale("","","")
	  }
	},
	{
		// "Bemba - Botswana" language
		"bem", 
		"BW", 
		"",
	  {
		MakeLanguageID(kLanguageUseICULocale, kSubLanguageDefault), 
		nil, 
		nil, 
		nil, 
		kCHCoreFileNameBembaBotswana, 
		kCHHyphFileNameBembaBotswana,
		kCHThesaurusFileNameBembaBotswana,
		kCHUserDictFileNameBembaBotswana,
		U_ICU_NAMESPACE::Locale("","","")
	  }
	},
	{
		// "Aramaic" language
		"arc", 
		"", 
		"",
	  {
		MakeLanguageID(kLanguageUseICULocale, kSubLanguageDefault), 
		nil, 
		nil, 
		nil, 
		kCHCoreFileNameAramaic, 
		kCHHyphFileNameAramaic,
		kCHThesaurusFileNameAramaic,
		kCHUserDictFileNameAramaic,
		U_ICU_NAMESPACE::Locale("","","")
	  }
	}
};


/** Provides a convenient way of encapsulating a table that defines 
	the data files on which the spelling service depends. The table stored here defines the set
	of the dictionaries, etc. that you need. At run time you can go and check that 
	these files are present. For example, if you offer a Hungarian spelling service 
	but can't find your	Hungarian dictionary then you can complain and not install 
	your Hungarian spelling service. The interface is typically used by the spelling, 
	hyphenation and dictionary manager interfaces. 

	@ingroup chlinguistic
	
*/
class CHLFileNameTable : public CPMUnknown<ICHLFileNameTable>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CHLFileNameTable(IPMUnknown* boss);
		
		/**
			It is called from Install method of CHLSpellingMgr.
			@param rPath It isn't being used by this sample.
		*/
		virtual	void					Install(const PMString& rPath);
		
		/**
			Get the count of CHLFileNameData entries.
			@return Count of CHLFileNameData entries
		*/
		virtual	int32 					GetEntriesCount() const;
		
		/**
			Get the CHLFileNameData for the specified index in the table.
			@param nIndex IN the index in the table.
			@return the CHLFileNameData associated with nInDex.
		*/
		virtual	const CHLFileNameData*	GetNthEntry(int32 nIndex) const;
		
		/**
			Tests whether nIndex entry is a spelling service.
			@param nIndex IN the index, it isn't being used by this sample.
			@return kTrue if it is.
		*/
		virtual bool16					IsSpellingService(int32 nIndex) const;
		
		/**
			Tests whether nIndex entry is a hyphenation service.
			@param nIndex IN the index, it isn't being used by this sample.
			@return kTrue if it is.
		*/
		virtual bool16					IsHyphenationService(int32 nIndex) const;
		
		/**
			Tests whether nIndex entry is a thesaurus service.
			@param nIndex IN the index, it isn't being used by this sample.
			@return kTrue if it is.
		*/
		virtual bool16					IsThesaurusService(int32 nIndex) const;

	private:
		bool16							fInstalled;

		K2Vector<CHLFileNameData>		fTable;
		
		/**
			Verifies the default data.
			@param defaultData IN the default CHDefaultData.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode						VerifyDefaultData(const CHDefaultData& defaultData) const;
			
};


/* Templates
*/
#include "TemplateDefs.h"
#include "K2Vector.tpp"

#ifdef WINDOWS
#pragma warning (disable:4660)
#endif
// TODO what is this
TEMPLATE K2Vector<CHLFileNameData>;

#ifdef WINDOWS
#pragma warning (default:4660)
#endif

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(CHLFileNameTable, kCHLFileNameTableImpl)

/* CHLFileNameTable constructor 
*/
CHLFileNameTable::CHLFileNameTable(IPMUnknown* boss) :
	CPMUnknown<ICHLFileNameTable>(boss), fInstalled(kFalse)
{
}


/* CHLFileNameTable::Install()
*/
void CHLFileNameTable::Install(const PMString& rPath)
{
	ErrorCode status = kFailure;
	do
	{
		if (fInstalled)
		{
			status = kSuccess;
			break;
		}

		fInstalled = kTrue;
		bool16 errorFlag = kFalse;
		for (int32 i = 0 ; i < kCHDefaultTableLength ; i++)
		{
			// Get a reference to the default table entry
			const CHDefaultData& defaultData = kCHDefaultTable[i];

			// Skip entries which don't pass verification
			if (VerifyDefaultData(defaultData) != kSuccess)
			{
				errorFlag = kTrue;
				continue;
			}

			// Add this entry to our table
			CHLFileNameData filenameData;
			filenameData.fLanguageID = defaultData.fLanguageID;
			filenameData.fLanguageName = defaultData.fLanguageName;
			filenameData.fPrimaryLanguageName = defaultData.fPrimaryLanguageName;
			filenameData.fSubLanguageName = defaultData.fSubLanguageName;
			filenameData.fCoreFileName = defaultData.fCoreFileName;
			filenameData.fHyphFileName = defaultData.fHyphFileName;
			filenameData.fThesaurusFileName = defaultData.fThesaurusFileName;
			filenameData.fDefaultUserDictFileName = defaultData.fDefaultUserDictFileName;
			fTable.push_back(filenameData);
		}

		/** install ICU languages */
		for (int32 j = 0 ; j < kCHICUTableLength ; j++)
		{
			//consists of one or more pieces of ordered information:

			//Language code
				//The languages are specified using a two- or three-letter lowercase code for a particular language.
				//For example, Spanish is "es", English is "en" and French is "fr". The two-letter language code 
				//uses the ISO-639 standard.

			//Country code
				//There are often different language conventions within the same language. For example, Spanish is spoken in 
				//many countries in Central and South America but the currencies are different in each country. To allow for 
				//these differences among specific geographical, political, or cultural regions, locales are specified by 
				//two-letter, uppercase codes. For example, "ES" represents Spain and "MX" represents Mexico. The two letter 
				//country code uses the ISO-3166 standard.

			//Variant code
				//The Variant codes are vendor and browser-specific.
				//For example, use WIN for Windows, MAC for Macintosh, and POSIX for POSIX.
				//Where there are two variants, separate them with an underscore, and
				//put the most important one first. For
				//example, a Traditional Spanish collation might be referenced, with
				//"ES", "ES", "Traditional_WIN".


			// Get a reference to the default icu table entry
			const CHICUData& icuData = kCHICUTable[j];

			// Skip entries which don't pass verification
			if (VerifyDefaultData(icuData.fCHDefaultData) != kSuccess)
			{
				errorFlag = kTrue;
				continue;
			}

			std::string languageCode = icuData.fICULanguageCode;
			std::string countryCode = icuData.fICUCountryCode;
			std::string variantCode = icuData.fICUVariantCode;
	
			U_ICU_NAMESPACE::Locale icuLocale(	languageCode.c_str(), 
												countryCode.c_str(), 
												variantCode.c_str());
			
            U_ICU_NAMESPACE::UnicodeString displayName;
			PMLocaleId currlocale = LocaleSetting::GetLocale();
			icuLocale.getDisplayName(currlocale.GetUserInterfaceICULocale(), displayName);
			//WideString wsDisplayName(displayName.getBuffer(), displayName.length());
			//PMString icuTranslation(wsDisplayName);

			CHLFileNameData filenameData;
			filenameData.fLanguageID = icuData.fCHDefaultData.fLanguageID;
			//filenameData.fLanguageName = icuTranslation;
			//filenameData.fPrimaryLanguageName = icuData.fCHDefaultData.fPrimaryLanguageName;
			//filenameData.fSubLanguageName = icuData.fCHDefaultData.fSubLanguageName;
			filenameData.fCoreFileName = icuData.fCHDefaultData.fCoreFileName;
			filenameData.fHyphFileName = icuData.fCHDefaultData.fHyphFileName;
			filenameData.fThesaurusFileName = icuData.fCHDefaultData.fThesaurusFileName;
			filenameData.fDefaultUserDictFileName = icuData.fCHDefaultData.fDefaultUserDictFileName;

			filenameData.fICULocale = icuLocale;
			
			fTable.push_back(filenameData);

#if INSERT_IMMEDIATELY
			InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
			if (ws)
			{
				InterfacePtr<ILanguageList> wsLangList(ws, UseDefaultIID());
				ASSERT(wsLangList);

				InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kNewLanguageWithVendorsCmdBoss));
				if (cmd)
				{
					InterfacePtr<ILanguage> cmdLanguage(cmd, UseDefaultIID());

					/* use this to set the language name to the generated ICU */
					//cmdLanguage->SetLanguageID(MakeLanguageID( kLanguageUseICULocale, kSubLanguageDefault ));
					//cmdLanguage->SetICULocale(icuLocale);

					/* using the below code will assert in InDesign, but can still be safely used */
					//PMString langName(icuLocale.c_str(), PMString::kEncodingASCII, PMString::kNoTranslate);
					//cmdLanguage->SetLanguageName( langName );

					//PMString icuName(icuTranslation.GrabCString(), PMString::kEncodingASCII, PMString::kNoTranslate);
					
					PMString icuName(icuTranslation.GrabCString());

					cmdLanguage->SetLanguageID(MakeLanguageID(kLanguageUseICULocale, kSubLanguageDefault));
					cmdLanguage->SetICULocale(icuLocale);
					cmdLanguage->SetLanguageName(icuName);

					cmd->SetItemList(UIDList(wsLangList));

					ErrorCode ec = CmdUtils::ProcessCommand(cmd);
					ASSERT(ec == kSuccess);

					PMString name = cmdLanguage->GetLanguageName();

					InterfacePtr<const ILanguage> newLanguage(wsLangList->QueryLanguage(name));
					UID nLanguageUID = ::GetUID(newLanguage);
					ASSERT(nLanguageUID != kInvalidUID);
				}
			}
#endif
		}

		if (errorFlag == kFalse)
		{
			status = kSuccess;
		}

	} while (false); // only do once
	
	// TODO make less intrusive, shouldn't pop alert on failure during startup
	//if (status != kSuccess)
	//{
	//	CAlert::ErrorAlert(kCHLFileNameTableInstallFailedKey);
	//}

	return;
}


/* CHLFileNameTable::GetEntriesCount()
*/
int32 CHLFileNameTable::GetEntriesCount() const
{
	return fTable.size();
}


/* CHLFileNameTable::GetNthEntry()
*/
const CHLFileNameData* CHLFileNameTable::GetNthEntry(int32 nIndex) const
{
	ASSERT_MSG(GetEntriesCount() > 0, "CHLFileNameTable - missing Install().");
	ASSERT_MSG(nIndex < GetEntriesCount(), "CHLFileNameTable - bad index.");
	return nIndex < this->GetEntriesCount() ? &(fTable[nIndex]) : nil;
}


/* CHLFileNameTable::VerifyDefaultData()
*/
ErrorCode CHLFileNameTable::VerifyDefaultData(const CHDefaultData& defaultData) const
{
	ErrorCode status = kFailure;
	do
	{
		// Get the path to where our linguistic data files are installed
		InterfacePtr<ILinguisticServiceData> iLinguisticServiceData(this, IID_ILINGUISTICDATA);
		if (iLinguisticServiceData == nil)
		{
			ASSERT_FAIL("CHLFileNameTable::VerifyDefaultData() iLinguisticServiceData invalid");
			break;
		}
		const PMString& linguisticPath = iLinguisticServiceData->GetPath();

		// Check our data files exist
		PMString dataFileName;

		// Check our core file
		dataFileName = linguisticPath;
		dataFileName.Append(defaultData.fCoreFileName);
		status = CHLUtils::FileExistsForRead(dataFileName);
		if (status != kSuccess)
		{
			// Don't ASSERT here since CHLFileNameTable::Install() will issue a CAlert
			break;
		}

		// Check our hyphenation file
		dataFileName = linguisticPath;
		dataFileName.Append(defaultData.fHyphFileName);
		status = CHLUtils::FileExistsForRead(dataFileName);
		if (status != kSuccess)
		{
			// Don't ASSERT here since CHLFileNameTable::Install() will issue a CAlert
			break;
		}	

	} while (false); // only do once

	return status;
}


/* CHLFileNameTable::IsSpellingService()
*/
bool16 CHLFileNameTable::IsSpellingService(int32 nIndex) const
{
	return kTrue;
}


/* CHLFileNameTable::IsHyphenationService()
*/
bool16 CHLFileNameTable::IsHyphenationService(int32 nIndex) const
{
	return kFalse;
}


/* CHLFileNameTable::IsThesaurusService()
*/
bool16 CHLFileNameTable::IsThesaurusService(int32 nIndex) const
{
	InterfacePtr<IInCopyApp> appIC(GetExecutionContextSession(), UseDefaultIID());
	if (appIC)
		return kTrue;

	return kFalse;
}

// End CHLFileNameTable.cpp

