//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IInsertHyphExceptionsCmdData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IInsertHyphExceptionsCmdData__
#define __IInsertHyphExceptionsCmdData__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "LanguageID.h"
#include "LinguisticID.h"

class WideString;
class IDocument;

//----------------------------------------------------------------------------------------
// Interface IInsertHyphExceptionsCmdData
//----------------------------------------------------------------------------------------

/** 
	@ingroup text_hyphen
*/
class IInsertHyphExceptionsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINSERTHYPHEXCEPTIONSCMDDATA };

	/**	
		Sets document.
		If you only set the document, InsertHyphExceptionsCmd will use every language's user dictionaries.
		
		@param pDoc	Document for the command data to set to.
	 */
	virtual	void Set( IDocument *pDoc ) = 0; 

	/**	
		Sets command data.
		If you specify a stringlist and a language the stringlist will be used instead.
		
		@param pDoc	Document for the command data to set to.
		@param rExceptions	List of exception strings for the command data to set to.
		@param nLanguage	language ID for the command data to set to.
	 */
	// 
	virtual	void Set( IDocument *pDoc, const K2Vector<WideString*> &rExceptions, LanguageID nLanguage ) = 0; 
		
	/**	
		Gets document for the command data.

		@return IDocument*	Document in the command data.
	 */
	virtual IDocument *						QueryDocument() = 0;
	/**	
		Gets list of exceptions for the command data.

		@return const K2Vector<WideString*> &	exceptions list in the command data.
	 */
	virtual const K2Vector<WideString*> &GetExceptions() const = 0;
	/**	
		Gets the language for the command data.

		@return LanguageID	language for the command data.
	 */
	virtual LanguageID 						GetLanguage() const = 0;
};

#endif
