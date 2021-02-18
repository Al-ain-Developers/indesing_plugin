//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUserDictUtils.cpp $
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

// ----- Interfaces -----
#include "ICHLUserDictUtils.h"
#include "ILanguageList.h"
#include "ILanguage.h"
#include "ISaxContentHandler.h"
#include "ISAXServices.h"
#include "ISAXParserOptions.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IUserDictService.h"
#include "IXMLOutStream.h"
#include "IXMLStreamUtils.h"
#include "ICHLFileNameTable.h"

#include "CHLID.h"
#include "SDKFileHelper.h"
#include "FileUtils.h"
#include "PreferenceUtils.h"
#include "StreamUtil.h"
#include "ErrorUtils.h"
#include "UserDictWordList.h"
#include "CHLUserDict.h"
#include "LocaleSetting.h"

#include "unicode/unistr.h"
#include "unicode/brkiter.h"
#include "unicode/dbbi.h"
#include "unicode/stsearch.h"
#include "unicode/uloc.h"
#include "unicode/ucol.h"
#include "unicode/coll.h"

/** Implements a utilities class to handle importing and exporting the user dictionary xml format. 
 *  
 * 	
 *  @ingroup chlinguistic
*/
class CHLUserDictUtils : public CPMUnknown<ICHLUserDictUtils>
{
public :
    CHLUserDictUtils(IPMUnknown *boss);

	virtual ErrorCode ExportCHLUserDictXML(const IDFile& file, IUserDict* userDict, const UserDictWordList& udWordList, LanguageID languageID, IXMLOutStream::eEncodingType encoding);
	virtual ErrorCode ImportCHLUserDictXML(const IDFile& file, IUserDict* userDict);
};

CREATE_PMINTERFACE(CHLUserDictUtils, kCHLUserDictUtilsImpl)

/* CHLUserDictUtils::CHLUserDictUtils
 */
CHLUserDictUtils::CHLUserDictUtils(IPMUnknown* boss) :
    CPMUnknown<ICHLUserDictUtils>(boss)
{
}

/* CHLUserDictUtils::ExportCHLUserDictXML
 */
ErrorCode CHLUserDictUtils::ExportCHLUserDictXML(const IDFile& file, IUserDict* userDict, const UserDictWordList& userDictWordList, LanguageID languageID, IXMLOutStream::eEncodingType encoding)
{
    U_ICU_NAMESPACE::Locale icuLocale;
	PMString languageName = "";	
    InterfacePtr<ILanguageList> languageList((ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST));   
	InterfacePtr<ILanguage> language(languageList->QueryLanguageByID(languageID));
	if(language)
	{
		languageName = language->GetLanguageName();
		icuLocale = language->GetICULocale();
	}
	else
	{	

		InterfacePtr<IK2ServiceRegistry> registry(GetExecutionContextSession(), UseDefaultIID());
		InterfacePtr<IK2ServiceProvider> chlService(registry->QueryServiceProviderByClassID(kLinguisticService, kCHLinguisticBoss));
		ASSERT_MSG(chlService != nil, "CHLData - can't find service provider ");
	
		InterfacePtr<ICHLFileNameTable> iFileNameTable(chlService, IID_ICHLFILENAMETABLE);	
		const int32 entriesCount = iFileNameTable->GetEntriesCount();

		for(int32 i = 0; i < entriesCount; i++)
		{
			const CHLFileNameData* fileNameData = iFileNameTable->GetNthEntry(i);
			if (fileNameData == nil)
			{
				break;
			}			
			if(fileNameData->fLanguageID == languageID)	
			{
				languageName = fileNameData->fLanguageName;
				icuLocale = fileNameData->fICULocale;
				break;
			}
		}				
	}

    if(languageName == "")
	{
		ASSERT(languageName == "");	
		return kFailure;
	}	

	InterfacePtr<IXMLOutStream> xmlOutStream(Utils<IXMLStreamUtils>()->CreateXMLOutFileStream(file, encoding));
	if (xmlOutStream != nil)
	{
		xmlOutStream->Indent(kTrue);
    
		// -- Write out the file header
		WideString versionString(L"1.0", 3);
		xmlOutStream->DocHeader(versionString);
	    
		// Write the root element
		WideString ud("chlUserDict");
		xmlOutStream->Push(ud, kTrue);

		int32 bufferLength = 0;
		IXMLOutStream::Attribute attr1;
		IXMLOutStream::Attribute attr2;
		IXMLOutStream::AttributeList xmlAttrList;

		attr1.fName.SetX16String(L"name");
		attr1.fValue.SetX16String(languageName.GrabUTF16Buffer(&bufferLength));
		xmlAttrList.push_back(IXMLOutStream::Attribute(attr1));

		//UnicodeString displayName;
		//PMLocaleId currlocale = LocaleSetting::GetLocale();
		//icuLocale.getDisplayName(currlocale.GetUserInterfaceICULocale(), displayName);
		//WideString wsDisplayName(displayName.getBuffer(), displayName.length());

		WideString localeName(icuLocale.getName());

		attr2.fName.SetX16String(L"icuLocale");
		attr2.fValue.SetX16String(localeName.GrabUTF16Buffer(&bufferLength));
		xmlAttrList.push_back(IXMLOutStream::Attribute(attr2));

		xmlOutStream->IndentLevel(kTrue);
		
		// write out the language element
		xmlOutStream->WriteEmptyWithAttributes( WideString("language"), xmlAttrList, kTrue );

		// Write the word pairs list element
		WideString wl( "wordlist" );
		xmlOutStream->Push(wl, kTrue);

		xmlOutStream->IndentLevel(kTrue);

		UserDictWordList udWordList;

		CHLUserDict* chlUserDict = static_cast<CHLUserDict*>(userDict);
		if (chlUserDict)
		{
			chlUserDict->GetUserDictWordList(udWordList);
		}
		
		if (udWordList.Length() > 0)
		{
			for (int32 i = 0; i < udWordList.Length(); ++i)
			{
				const WideString& word = udWordList[i];
				
				IXMLOutStream::Attribute attr;
				IXMLOutStream::AttributeList list;
				int32 length;

				attr.fName.SetX16String(L"word");
				attr.fValue.SetX16String(word.GrabUTF16Buffer(&length));
				list.push_back(IXMLOutStream::Attribute(attr));
				
				// Write out each udc entry
				xmlOutStream->WriteEmptyWithAttributes(WideString("udcEntry"), list, kTrue);
			}
		}

		xmlOutStream->IndentLevel(kFalse);

		xmlOutStream->Pop(kTrue);
		xmlOutStream->IndentLevel(kFalse);

		xmlOutStream->Pop(kTrue);

		xmlOutStream->Close();
	}

	return kSuccess;
}

/* CHLUserDictUtils::ImportCHLUserDictXML
 */
ErrorCode CHLUserDictUtils::ImportCHLUserDictXML(const IDFile& file, IUserDict* userDict)
{
    InterfacePtr<IPMStream> fileStream((IPMStream*)StreamUtil::CreateFileStreamRead(file));
	if (! fileStream)
		return kFailure;

    InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
    InterfacePtr<IK2ServiceProvider> xmlProvider(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, kXMLParserServiceBoss));
	ASSERT_MSG(xmlProvider != nil, "CHLData - can't find service provider ");
	if(! xmlProvider)
		return kFailure;	 
	InterfacePtr<ISAXContentHandler> handler((ISAXContentHandler*)::CreateObject(kCHLUserDictContentHandlerBoss, IID_ISAXCONTENTHANDLER));
    InterfacePtr<ISAXServices> saxServices(xmlProvider, UseDefaultIID());
    if (saxServices)
    {
        InterfacePtr<ISAXParserOptions> parserOptions(saxServices, UseDefaultIID());
        parserOptions->SetShowWarningAlert(kFalse);

        if (saxServices->ParseStream(fileStream, handler))
        {
            if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
                ASSERT_FAIL(FORMAT_ARGS("Error parsing the 'CHLUserDict.xml': %s", ErrorUtils::PMGetGlobalErrorString().GetUTF8String().c_str()));

            // -- As far we we are concerned the errors been handled. Don't propgate the error any further.
            // -- At this early stage leaving the global error set will cause problems with other service providers.

            ErrorUtils::PMSetGlobalErrorCode(kSuccess);
        }
		
		CHLUserDict* chlUserDict = static_cast<CHLUserDict*>(userDict);
		if (chlUserDict)
		{
			InterfacePtr<IUserDict> saxUserDict(handler, UseDefaultIID());
			CHLUserDict* chlSaxUserDict = static_cast<CHLUserDict*>((IUserDict*)saxUserDict);
			if (chlSaxUserDict)
			{
				UserDictWordList udWordList;
				chlSaxUserDict->GetUserDictWordList(udWordList);
				chlUserDict->SetUserDictWordList(udWordList);
			}
		}
    }

	return kSuccess;
}
