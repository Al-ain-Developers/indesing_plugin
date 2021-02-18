//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/QuoteEntry.h $
//  
//  Owner: Adnan_Sulejmanpasic
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
#ifndef __QuoteEntry__
#define __QuoteEntry__

#include "IPMUnknown.h"
#include "BaseType.h"
#include "K2Vector.h"
#include "ILanguage.h"

typedef K2Vector<textchar> QuoteList;

class PUBLIC_DECL QuoteEntry
{
public:	
	
	QuoteEntry() : fQuotes()
    {
        fQuotes.reserve(kNumQuotes);
    }

	QuoteEntry(InterfacePtr<ILanguage>& pLanguage);

	QuoteEntry(InterfacePtr<ILanguage>& pLanguage, const UTF32TextChar leftSingle, const UTF32TextChar rightSingle, const UTF32TextChar leftDouble, const UTF32TextChar rightDouble);

	QuoteEntry(const QuoteEntry& otherQuoteEntry);

	void ConstructorHelp(InterfacePtr<ILanguage>& pLanguage, bool16 defaultQuotes, const UTF32TextChar leftSingle = 0, const UTF32TextChar rightSingle = 0, UTF32TextChar leftDouble = 0, const UTF32TextChar rightDouble = 0);
	
	bool16 operator!=(const QuoteEntry& otherQuoteEntry) const;

	textchar GetTypographersQuotes(const ILanguage::QuotationType nType, const ILanguage::QuotationPosition nPosition) const;

	void ReadWrite(IPMStream *s);

private:
	PMString fName;
	QuoteList fQuotes;
	enum { kNumQuotes = 4 };

	friend class QuoteTable;
	friend class QuoteData;
	friend class Quotes;
};

DECLARE_OBJECT_TYPE(QuoteEntry);

#endif
