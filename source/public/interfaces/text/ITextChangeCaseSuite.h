//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextChangeCaseSuite.h $
//  
//  Owner: dwaterfa
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
//  
//  Notes:
//  
//========================================================================================

#pragma once
#ifndef __ITextChangeCaseSuite__
#define __ITextChangeCaseSuite__

#include "IPMUnknown.h"
#include "TextID.h"


/**	ITextChangeCaseSuite is a very light-weight suite that
	is just used for the "change case" functionality. The functions
	here should have probably been folded into the TextAttributeSuite.
	@see ITextAttributeSuite
	@ingroup text_suite
*/
class ITextChangeCaseSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTCHANGECASE_ISUITE };

		/** These are the types of case-changing supported
		*/
		typedef enum {
			kCCLower	= 0,
			kCCUpper,
			kCCTitle,
			kCCSentence,
		} ChangeCaseType;

		/** Does the current selection support the change case functionality?
			@return kTrue if the selection can change case.
		*/
		virtual bool16	CanChangeCase() = 0;

		/** Perform the specified change case operation.
			@param ccType is the type of case-change to perform: capitalize, make lowercase, etc.
		*/
		virtual void	ChangeCase(ChangeCaseType ccType) = 0;

};

#endif
	// __ITextChangeCaseSuite__
