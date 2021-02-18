//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformTextAttrLanguage.cpp $
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
#include "IAttrReport.h"
#include "IComposeScanner.h"
#include "ITextAttrClassID.h"
#include "ITextAttrUID.h"
#include "ITextModelCmds.h"
#include "ITextTarget.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "IVendorList.h"
#include "IDocument.h"

// General includes:
#include "PreferenceUtils.h"
#include "TCID.h" // for composer boss class IDs
#include "TextRange.h"
#include "K2Vector.tpp"
// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpTextAttrHelper.h"

// TODO align with coding conventions
/**
 * 	This structure is designed for reporting language attribute. 
 * 	The attribute is referred by name, but UID is needed for setting.
 */
struct SnpLanguageData
{
	public:
	/** This allows the structure to be put into a K2Vector.
	 */
	typedef object_type data_type;

	/**	Equal operator
		@param other IN node reference
		@return SnpLanguageData& 
	 */
	SnpLanguageData& operator=(const SnpLanguageData& other);

	/** Compares two SnpLanguageData structures.
	 * 	@param other IN Another SnpLanguageData to compare.
	 * 	@return kTrue if equal, kFalse otherwise.
	 */
	inline bool16 operator==(const SnpLanguageData& other) const;

	/** Specifies translated language name of attribute.
	*/
	PMString    fLanguageTranslateName;

	/** Specifies language name of attribute.
	*/
	PMString    fLanguageName;

	/** Specifies language UID of attribute.
	*/
	UID         fLanguageUID;

};

/* operator=
*/
SnpLanguageData& SnpLanguageData::operator=(const SnpLanguageData& other)
{
	if (this != &other)
	{
		fLanguageTranslateName = other.fLanguageTranslateName;
		fLanguageName = other.fLanguageName;
		fLanguageUID = other.fLanguageUID;
	}
	return *this;
}

/* operator==
*/
inline bool16 SnpLanguageData::operator==(const SnpLanguageData& other) const
{
	return fLanguageName == other.fLanguageName;
}


/** 
	\li How to apply and inspect Language text attributes,
	\li How to acquire the language list which can be used.
		
	@ingroup sdk_snippet
	@ingroup sdk_text
	@see IAttrReport
	@see IComposeScanner
	@see ITextAttrClassID
	@see ITextTarget
	@see ILanguage
	@see ILanguageList
	@see IVendorList
	@see IDocument
*/
class SnpPerformTextAttrLanguage
{
public: 

	/** Constructor.  
	*/
	SnpPerformTextAttrLanguage() {}

	/** Destructor.
	*/
	virtual ~SnpPerformTextAttrLanguage() {}

	/**	Applies language attribute to the specified text model.
	 * 	@param textRange (in) The text range to which you want to apply language.
	 * 	@param languageName (in) The language name to which you want to apply language.
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode ApplyLanguage(const InDesign::TextRange& textRange, const PMString& languageName);

	/**	Inspects language attribute over the specified text model.
	 * 	The details are printed to the SNIPLOG.
	 * 	@param textRange (in) The text range from which you want to inspect lLanguage.
	 * 	@param data (out) The language data. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode InspectLanguage(const InDesign::TextRange& textRange, SnpLanguageData& data);
    
	/** Reports language data to SNIPLOG.
	 * 	@param languageData (in) The language settings.  
	 */
	void ReportLanguageData(const SnpLanguageData& languageData);

	/** Reports language list to SNIPLOG.
	 */
	void ReportLanguageList( void );


	/** Get the language list made from the current document.
	 * 	@param document (in) current document.
	 */
	void GetLanguageList(IDocument* document);
	void GetLanguagesCachedAsStringList(K2Vector<PMString>& listString) {
		listString.clear();
		K2Vector<SnpLanguageData>::const_iterator beginIter = fLanguageList.begin();
		K2Vector<SnpLanguageData>::const_iterator endIter = fLanguageList.end();
		K2Vector<SnpLanguageData>::const_iterator iter;
		for (iter = beginIter; iter != endIter; ++iter)
		{
			listString.push_back(iter->fLanguageTranslateName);
		}
	}

	PMString GetNthCachedUntranslatedLang(int32 n) {
		return (fLanguageList[n].fLanguageName);
	}

private:

	K2Vector<SnpLanguageData> fLanguageList;

};



/* ApplyLanguage
*/
ErrorCode SnpPerformTextAttrLanguage::ApplyLanguage(const InDesign::TextRange& textRange, const PMString& languageName)
{
	ErrorCode status = kFailure;
	do
	{
		if (languageName.empty())
		{
			SNIPLOG("languageName is empty - you must specify a language name.");
			break;
		}

		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse)
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data.
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();

		// Get current document.
		IDataBase* db = ::GetDataBase(textModel);
		InterfacePtr<IDocument> document(db, db->GetRootUID(), UseDefaultIID());        

		// Check for valid length. 
		if (rangeData.Length() <= 0)
		{
			SNIPLOG("You must have a positive number of text characters selected. Please try again.");
			break;
		}

		InterfacePtr<ILanguageList>appLanguageList((ILanguageList*)::QuerySessionPreferences(IID_ILANGUAGELIST));
		if (appLanguageList == nil)	break;

		// Make a copy of given language name.
		// The reason for making a copy is because QueryLanguage() does not take string with translated flag is on.
		PMString languageString(languageName);
		languageString.SetTranslatable(kFalse);

		InterfacePtr<ILanguageList>docLanguageList((ILanguageList*)::QueryPreferences(IID_ILANGUAGELIST, document));
		if (docLanguageList == nil)	break;

		bool16 bInDocument = kFalse;
		InterfacePtr<const ILanguage>language(docLanguageList->QueryLanguage(languageString));
		if (language) bInDocument = kTrue;

		UID languageUID = kInvalidUID;

		// When there is no language in the language list of the document.
		if (!bInDocument)
		{
			// This part of code is for the case when the language was not found in the language list in the document,
			// the language will be copied from the application if it does exist.
			InterfacePtr<const ILanguage>appLanguage(appLanguageList->QueryLanguage(languageString));
			if (appLanguage)
			{
				InterfacePtr<ICommand>newLangCmd(CmdUtils::CreateCommand(kNewLanguageCmdBoss));
				if (newLangCmd == nil) break;

				InterfacePtr<ILanguage>cmdData(newLangCmd, UseDefaultIID());
				if (cmdData == nil)	break;

				newLangCmd->SetItemList(UIDList(docLanguageList));
				cmdData->CopyFrom(appLanguage);

				status = CmdUtils::ProcessCommand(newLangCmd);

				InterfacePtr<ILanguageList>newDocLanguageList((ILanguageList*)::QueryPreferences(IID_ILANGUAGELIST, document));
				if (newDocLanguageList == nil) break;

				InterfacePtr<const ILanguage>newLanguage(newDocLanguageList->QueryLanguage(languageString));
				if (newLanguage == nil)	break;

				languageUID = ::GetUID(newLanguage);
			}
		}
		else
		{
			languageUID = ::GetUID(language);
		}

		if (languageUID != kInvalidUID)
		{
			// Creating an AttributeBossList in order to apply number of attributes with single operation.
			boost::shared_ptr<AttributeBossList> attrList (new AttributeBossList);
			if (attrList.get() == nil)
			{
				ASSERT(attrList);
				break;
			}

			// Creating character strand attribute
			InterfacePtr<IAttrReport> attr01(
				SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, ITextAttrUID::ValueType>(kTextAttrLanguageBoss, languageUID));
			attrList->ApplyAttribute(attr01);

			// generate the command
			InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
			if (textModelCmds == nil) break;

			InterfacePtr<ICommand> applyCmd(textModelCmds->ApplyCmd(rangeData, attrList, kCharAttrStrandBoss));
			if (applyCmd == nil) break;

			// process the command
			status = CmdUtils::ProcessCommand(applyCmd);
		}
	} while (false);
	return status;
}

/* InspectLanguage
*/
ErrorCode SnpPerformTextAttrLanguage::InspectLanguage(const InDesign::TextRange& textRange, SnpLanguageData& data)
{
	ErrorCode status = kFailure;
	do
	{
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse)
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Get Language attribute of character.
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, ITextAttrUID::ValueType>(textRange, kTextAttrLanguageBoss, data.fLanguageUID);

		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		IDataBase* db = ::GetDataBase(textModel);

		InterfacePtr<const ILanguage>language(db, data.fLanguageUID, IID_ILANGUAGE);

		if (language)
		{
			PMString langName(language->GetLanguageName());
			if (language->GetLanguageID() == kLanguageNeutral)
				langName = "[No Language]";

			data.fLanguageName = langName;
			langName.Translate();
			data.fLanguageTranslateName = langName;

			status = kSuccess;
		}
		else
		{
			data.fLanguageUID = kInvalidUID;
		}   

	} while (false);
	return status;
}

/* GetLanguageList
*/
void SnpPerformTextAttrLanguage::GetLanguageList(IDocument* document)
{
	// call clear() method.
	fLanguageList.clear();

	do
	{
		if (document == nil) break;

		InterfacePtr<ILanguageList>docLanguageList((ILanguageList*)::QueryPreferences(IID_ILANGUAGELIST, document));
		if (docLanguageList == nil)
		{
			ASSERT(docLanguageList);
			break;
		}
		InterfacePtr<ILanguageList>sessionLanguageList((ILanguageList*)::QuerySessionPreferences(IID_ILANGUAGELIST));
		if (sessionLanguageList == nil)
		{
			ASSERT(sessionLanguageList);
			break;
		}

		int32 count = docLanguageList->GetLanguageCount();

		PMString langString;

		// Add language list of document
		for (int32 docIndex = 0; docIndex < count; docIndex++)
		{
			InterfacePtr<const ILanguage>language(docLanguageList->QueryNthLanguage(docIndex));
			if (language)
			{
				if (language->GetLanguageID() != kLanguageNeutral)
				{
					// In order to check if the language is available,
					// check  whether there is at least a hyphenation or spell checker for the language.
					langString = language->GetLanguageName();

					InterfacePtr<const ILanguage>findInSession(sessionLanguageList->QueryLanguage(langString));
					bool16 bAvailable = kTrue;

					if (findInSession)
					{
						InterfacePtr<const IVendorList>hyphVendor(findInSession, IID_IHYPHVENDORLIST);
						if (!hyphVendor || hyphVendor->GetVendorCount() == 0)
						{
							InterfacePtr<const IVendorList>spellVendor(findInSession, IID_ISPELLVENDORLIST);
							bAvailable = spellVendor && spellVendor->GetVendorCount() > 0;
						}
					}

					if (!bAvailable)
					{
						langString.Insert(char('('), 0);
						langString.Insert(char(')'), langString.CharCount());
					}

				}
				else
				{
					langString = "[No Language]";
				}


				SnpLanguageData langData;
				langData.fLanguageName = langString;

				langString.Translate();
				langString.SetTranslatable(kFalse);

				langData.fLanguageTranslateName = langString;
				langData.fLanguageUID = ::GetUID(language);

				fLanguageList.push_back(langData);
			}
		}

		// clear used lunguage string.
		langString.Clear();

		// Add language list of session.
		count = sessionLanguageList->GetLanguageCount();

		for (int32 appIndex = 0; appIndex < count; appIndex++)
		{
			InterfacePtr<const ILanguage>language(sessionLanguageList->QueryNthLanguage(appIndex));
			if (language)
			{
				if (language->GetLanguageID() != kLanguageNeutral)
				{
					bool16 bAvailable = kTrue;
					InterfacePtr<const IVendorList>hyphVendor(language, IID_IHYPHVENDORLIST);
					if (!hyphVendor || hyphVendor->GetVendorCount() == 0)
					{
						InterfacePtr<const IVendorList>spellVendor(language, IID_ISPELLVENDORLIST);
						bAvailable = spellVendor && spellVendor->GetVendorCount() > 0;
					}

					langString = language->GetLanguageName();

					if (!bAvailable)
					{
						langString.Insert(char('('), 0);
						langString.Insert(char(')'), langString.CharCount());
					}

					SnpLanguageData langData;
					langData.fLanguageName = langString;

					langString.Translate();
					langString.SetTranslatable(kFalse);

					langData.fLanguageTranslateName = langString;
					langData.fLanguageUID = ::GetUID(language);

					K2Vector<SnpLanguageData>::const_iterator iter = K2find(fLanguageList.begin(), fLanguageList.end(), langData);
					if (iter == fLanguageList.end())
					{
						fLanguageList.push_back(langData);
					}
				}
			}
		}


	}while (false);
}

/* ReportLanguageData
*/
void SnpPerformTextAttrLanguage::ReportLanguageData(const SnpLanguageData& SnpLanguageData)
{
	SNIPLOG("=== Selected range LanguageSetting (begin) ===");
	SNIPLOG("*UID: 0x%X", SnpLanguageData.fLanguageUID.Get());
	SNIPLOG("*Language: %s (%s)",SnpLanguageData.fLanguageName.GetPlatformString().c_str(), SnpLanguageData.fLanguageTranslateName.GetPlatformString().c_str());
	SNIPLOG("=== (end) ===");
}

/* ReportLanguageList
*/
void SnpPerformTextAttrLanguage::ReportLanguageList( void )
{
	SNIPLOG("=== Language List (begin) ===");

	K2Vector<SnpLanguageData>::const_iterator beginIter = fLanguageList.begin();
	K2Vector<SnpLanguageData>::const_iterator endIter = fLanguageList.end();
	K2Vector<SnpLanguageData>::const_iterator iter;
	for (iter = beginIter; iter != endIter; ++iter)
	{
		SNIPLOG("*UID: 0x%X", iter->fLanguageUID.Get());
		SNIPLOG("*Language: %s (%s)", iter->fLanguageName.GetPlatformString().c_str(), iter->fLanguageTranslateName.GetPlatformString().c_str());
	}

	SNIPLOG("=== (end) ===");
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerPerformTextAttrLanguage : public SnpRunnable
{
public:

	// SnippetRunner framework hooks.

	/** Constructor.  
	*/
	_SnpRunnerPerformTextAttrLanguage(void);

	/** Destructor.
	*/
	virtual ~_SnpRunnerPerformTextAttrLanguage(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@pre SnipRun::CanRun is kTrue
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
};

/* Constructor.
*/
_SnpRunnerPerformTextAttrLanguage::_SnpRunnerPerformTextAttrLanguage(void) 
	: SnpRunnable("PerformTextAttrLanguage")
{
	this->SetDescription("Shows how to apply and inspect Language text attributes.");
	this->SetPreconditions("some text must be selected");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformTextAttrLanguage::~_SnpRunnerPerformTextAttrLanguage(void)	
{
	// do nothing.
}

/* CanRun
*/
bool16 _SnpRunnerPerformTextAttrLanguage::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	// we need a text focus in order to run this snippet
	do
	{
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil)
		{
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil)
		{
			break;
		}

		// Get the text range
		InDesign::TextRange textRange(textFocus);
		if (textRange.IsValid() == kFalse)
		{
			break;
		}

		// if we got to this point, we can run this snippet.
		result = kTrue;
	} while (false);
	return result;
}

/* Run
*/
ErrorCode _SnpRunnerPerformTextAttrLanguage::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do
	{
		SnpPerformTextAttrLanguage instance;
		// we need a text focus in order to run this snippet
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil)
		{
			ASSERT(textTarget);
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil)
		{
			SNIPLOG("You do not have any text selection - please select some text first.");
			break;
		}

		// Get the text range
		InDesign::TextRange textRange(textFocus);
		if (textRange.IsValid() == kFalse)
		{
			SNIPLOG("The textRange is invalid!");
			break;
		}

		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> choices;

		// first, get a choice of operations
		choices.clear();
		choices.push_back(PMString("inspect language (default)"));		// 0 - shows Language attribute details on sniplog.
		choices.push_back(PMString("apply language via menu"));			// 1 - specify the Language by menu. 
		choices.push_back(PMString("list all registered languages"));	// 2 - shows all language of current document and application work space.


		enum
		{
			kInspect, kApplyByMenu, kListAllLanguages
		};

		int32 opcode = parameterUtils->GetChoice(PMString("What operation do you want to perform?"), choices, 0);
		if (parameterUtils->WasDialogCancelled())
		{
			status = kCancel;
			break;
		}


		// Get front document.
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();

		// get the current list of Languages on the workspace
		instance.GetLanguageList(document);


		switch (opcode)
		{
		case kApplyByMenu:
			{

				K2Vector<PMString> listString;
				// +
				instance.GetLanguagesCachedAsStringList(listString);
				// -
				int32 choice = parameterUtils->GetChoice("Which language do you want to apply?", listString, 0);
				if (parameterUtils->WasDialogCancelled())
				{
					// user cancelled! get out of do-while loop
					status = kCancel;
					break;
				}

				PMString languageName = instance.GetNthCachedUntranslatedLang(choice);

				status = instance.ApplyLanguage(textRange, languageName);

				if (status != kSuccess)
				{
					SNIPLOG("ApplyLanguage failed!");
				}
			}
			break;

		case kInspect:
			{
				// create a local SnpLanguageData strcture to pass around.
				SnpLanguageData data;

				status = instance.InspectLanguage(textRange, data);
				// report this to SnipLog
				instance.ReportLanguageData(data);
			}
			break;

		case kListAllLanguages:
			{
				// report all languages to SnipLog.
				instance.ReportLanguageList();

				status = kSuccess;
			}
			break;
		default:
			{
				SNIPLOG("Invalid option. Skipping.");
			}
			break;
		}

	} while (false);
	return status;
}


/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPerformTextAttrLanguage instance_SnpRunnerPerformTextAttrLanguage;
DEFINE_SNIPPET(_SnpRunnerPerformTextAttrLanguage) 	

//End, SnpPerformTextAttrLanguage.cpp

