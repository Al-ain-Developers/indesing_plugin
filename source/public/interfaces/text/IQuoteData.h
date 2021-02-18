//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IQuoteData.h $
//  
//  Owner: Adnan Sulejmanpasic
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
#ifndef __IQuoteData__
#define __IQuoteData__

#include "IPMUnknown.h"
#include "QuoteEntry.h"
#include "LinguisticID.h"

/** 
	@ingroup text_quote
*/
class IQuoteData : public IPMUnknown
{
	public:
	
		enum { kDefaultIID = IID_IQUOTEDATA };

		/*******************************************************************************************************
		**
		**	Arguments: None
		**
		**	Description: Returns the Quote Entry object which contains four quotes, and the language IDs.
		**
		********************************************************************************************************/

		virtual const QuoteEntry& GetTypographersQuotes() const = 0;

		/*******************************************************************************************************
		**
		**	Arguments: const QuoteEntry&
		**
		**	Description: Sets the internal quote entry to equal the argument
		**
		********************************************************************************************************/

		virtual void SetTypographersQuotes(const QuoteEntry& newQuoteEntry) = 0;

		virtual void SetTypographersQuotes(InterfacePtr<ILanguage>& pLanguage, const UTF32TextChar leftSingle, const UTF32TextChar rightSingle,
										const UTF32TextChar leftDouble, const UTF32TextChar rightDouble) = 0;

		/*******************************************************************************************************
		**
		**	Arguments: None
		**
		**	Description: Returns the language name associated with the quotes stored in this class
		**
		********************************************************************************************************/

		virtual const PMString& GetLanguageName() const = 0;
};


#endif // __IQuoteData__
