//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUserDictContentHandler.cpp $
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

#include "ILanguage.h"
#include "ILanguageList.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ISAXAttributes.h"
#include "ISAXServices.h"
#include "ISession.h"
#include "IXMLOutStream.h"

// ----- Includes -----

#include "CHLUserDict.h"
#include "CHLID.h"
#include "CSAXContentHandler.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "PreferenceUtils.h"

/** Implements a sax content handler to read the user dictionary xml format. 
 *  
 * 	
 *  @ingroup chlinguistic
*/
class CHLUserDictContentHandler : public CSAXContentHandler
{
public:
	CHLUserDictContentHandler(IPMUnknown *boss);
	virtual ~CHLUserDictContentHandler();

	virtual void StartDocument(ISAXServices* saxServices);
	virtual void EndDocument();

	virtual void StartElement(const WideString &uri, const WideString &localname, const WideString &qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString &uri, const WideString &localname, const WideString &qname);
	
	virtual void Characters(const WideString &chars);
	virtual void ProcessingInstruction(const WideString &target, const WideString &data);

	virtual void StartPrefixMapping(const WideString &prefix, const WideString &uri);
	virtual void EndPrefixMapping(const WideString &prefix);

	virtual void IgnorableWhitespace(const WideString &chars);
	virtual void SkippedEntity(const WideString &name);
	virtual void ExtComment(const WideString &comment);
	virtual void ExtXMLDecl(const WideString &version, const WideString &encoding, const WideString &standalone, const WideString &actualEncoding);
	
private:
	K2Vector<WideString> fStringList;
	LanguageID fLanguageID;
};

CREATE_PMINTERFACE(CHLUserDictContentHandler, kCHLUserDictContentHandlerImpl)

/* CHLUserDictContentHandler::CHLUserDictContentHandler
 */
CHLUserDictContentHandler::CHLUserDictContentHandler(IPMUnknown* boss) : 
	CSAXContentHandler(boss),
		fLanguageID(-1)
{
}

/* CHLUserDictContentHandler::~CHLUserDictContentHandler
 */
CHLUserDictContentHandler::~CHLUserDictContentHandler()
{
}

/* CHLUserDictContentHandler::StartDocument
 */
void CHLUserDictContentHandler::StartDocument(ISAXServices* saxServices)
{
	TRACEFLOW("CHLUserDict", "\nStart Document\n");

	fStringList.clear();
	fLanguageID = -1;
}

/* CHLUserDictContentHandler::EndDocument
 */
void CHLUserDictContentHandler::EndDocument(void)
{
	TRACEFLOW("CHLUserDict", "End Document\n\n");
}

/* CHLUserDictContentHandler::StartElement
 */
void CHLUserDictContentHandler::StartElement
(
	const WideString &	uri,
	const WideString &	localname,
	const WideString &	qname,
	ISAXAttributes *	attrs
)
{
	TRACEFLOW("CHLUserDict", "Start Element: %s\n", PMString(localname).GetUTF8String().c_str());

	if (localname == WideString("language"))
	{
		PMString languageName;
		PMString icuName;
		WideString languageNameW;
		WideString icuLocaleNameW;

        attrs->GetValue(WideString("name"), languageNameW);
		languageNameW.GetSystemString(&languageName);
		
        attrs->GetValue(WideString("icuLocale"), icuLocaleNameW);
		languageNameW.GetSystemString(&icuName);
		
		InterfacePtr<ILanguageList> languageList((ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST));
		InterfacePtr<ILanguage> language(languageList->QueryLanguage(languageName));
		ASSERT(language);
		if (language)
		{
			fLanguageID = language->GetLanguageID();
		}

		InterfacePtr<ILanguage> bossLanguage(this, UseDefaultIID());
		if (bossLanguage)
		{
			bossLanguage->CopyFrom(language);
		}
	}
	else if (localname == WideString("udcEntry"))
	{
		WideString word;
        attrs->GetValue(WideString("word"), word);

		fStringList.push_back(word);
	}
}

/* CHLUserDictContentHandler::EndElement
 */
void CHLUserDictContentHandler::EndElement
(
	const WideString&		uri,
	const WideString&		localname,
	const WideString&		qname
)
{
	TRACEFLOW("CHLUserDict", "End Element: %s\n", PMString(localname).GetUTF8String().c_str());
	
	if (localname == WideString("wordlist"))
	{
		InterfacePtr<IUserDict> userDict(this, UseDefaultIID());
		if (userDict)
		{
			CHLUserDict* chlUserDict = static_cast<CHLUserDict*>((IUserDict*)userDict);
			if (chlUserDict)
			{
				UserDictWordList udWordList;
				
                for (const auto &theString : fStringList)
				{
					udWordList.InsertUnique(theString);
				}

				chlUserDict->SetUserDictWordList(udWordList);
			}
		}
	}
}

/* CHLUserDictContentHandler::Characters
 */
void CHLUserDictContentHandler::Characters
(
	const WideString&		chars
)
{
	TRACEFLOW("CHLUserDict", "Characters\n");
}

/* CHLUserDictContentHandler::ProcessingInstruction
 */
void CHLUserDictContentHandler::ProcessingInstruction
(
	const WideString&		target,
	const WideString&		data
)
{
	TRACEFLOW("CHLUserDict", "Processing Instruction\n");
}

/* CHLUserDictContentHandler::StartPrefixMapping
 */
void CHLUserDictContentHandler::StartPrefixMapping
(
	const WideString&		prefix,
	const WideString&		uri
)
{
	TRACEFLOW("CHLUserDict", "Start Prefix Mapping: %s = %s\n", PMString(prefix).GetUTF8String().c_str(), PMString(uri).GetUTF8String().c_str());
}

/* CHLUserDictContentHandler::EndPrefixMapping
 */
void CHLUserDictContentHandler::EndPrefixMapping
(
	const WideString&		prefix
)
{
	TRACEFLOW("CHLUserDict", "End Prefix Mapping: %s\n", PMString(prefix).GetUTF8String().c_str());
}

/* CHLUserDictContentHandler::IgnorableWhitespace
 */
void CHLUserDictContentHandler::IgnorableWhitespace
(
	const WideString&		/* chars */
)
{
	TRACEFLOW("CHLUserDict", "Ignorable Whitespace\n");
}

/* CHLUserDictContentHandler::SkippedEntity
 */
void CHLUserDictContentHandler::SkippedEntity
(
	const WideString&		/* name */
)
{
	TRACEFLOW("CHLUserDict", "Skipped Entity\n");
}

/* CHLUserDictContentHandler::ExtComment
 */
void CHLUserDictContentHandler::ExtComment
(
	const WideString&		/* comment */
)
{
	TRACEFLOW("CHLUserDict", "ExtComment\n");
}

/* CHLUserDictContentHandler::ExtXMLDecl
 */
void CHLUserDictContentHandler::ExtXMLDecl
(
	const WideString&		/* version */,
	const WideString&		/* encoding */,
	const WideString&		/* standalone */,
	const WideString&		/* actualEncoding */
)
{
	TRACEFLOW("CHLUserDict", "ExtXMLDecl\n");
}

