//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IQuotes.h $
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
#ifndef __IQuotes__
#define __IQuotes__

#include "IPMUnknown.h"
#include "QuoteEntry.h"
#include "TextID.h"

/** 
	@ingroup text_quote
*/
class IQuotes : public IPMUnknown
{
	public:
	
		enum { kDefaultIID = IID_IQUOTES };

		/*******************************************************************************************************
		**
		**	Arguments: const QuoteEntry&
		**
		**	Description: Sets the internal quote entry to equal the argument
		**
		********************************************************************************************************/

		virtual void SetTypographersQuotes(const QuoteEntry& newQuoteEntry) = 0;

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
		**	Arguments: QuotationType (kDouble/kSingle), QuotationPosition (kLeft/kRight)
		**
		**	Description: Returns the unicode value corresponding to the quote given the type and position.
		**
		********************************************************************************************************/

		virtual const textchar GetTypographersQuotes(const ILanguage::QuotationType nType, const ILanguage::QuotationPosition nPosition) const = 0;
};


#endif // __IQuotes__
