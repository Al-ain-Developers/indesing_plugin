//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ILanguageLetterCode.h $
//  
//  Owner: Steve Flenniken
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

#pragma once
#ifndef __ILanguageLetterCode__
#define __ILanguageLetterCode__

#include "PDFID.h"

/** ILanguageLetterCode converts a LanguageID to a short abbreviation of the language.

	For the country codes used for the sub languages see
	http://www.iso.org/iso/en/prods-services/iso3166ma/02iso-3166-code-lists/list-en1.html

	A IID_ILANGUAGELETTERCODE interface is off the session.
*/
class ILanguageLetterCode : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ILANGUAGELETTERCODE};

	/** Get the language abbreviation for the given LanguageID.
		@return the language abbreviation. ie "en-US"
	*/ 
	virtual PMString GetLanguageString(LanguageID languageID) = 0;

	/** Get the 2 character ISO language abbreviation for the given LanguageID.
		@return the 2 character language abbreviation. ie "en"
	*/ 
	virtual PMString GetLanguageCodeString(LanguageID languageID) = 0;

	/** Get the 2 character ISO country abbreviation for the given LanguageID.
		@return the 2 character country abbreviation. ie "US"
	*/ 
	virtual PMString GetCountryCodeString(LanguageID languageID) = 0;
};

#endif
