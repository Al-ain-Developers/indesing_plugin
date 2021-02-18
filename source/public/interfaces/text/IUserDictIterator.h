//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IUserDictIterator.h $
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
#ifndef __IUserDictIterator__
#define __IUserDictIterator__

#include "IPMUnknown.h"
#include "IUserDictService.h"

class WideString;

//----------------------------------------------------------------------------------------
// Interface IUserDictIterator
//----------------------------------------------------------------------------------------

/** 
	@ingroup text_dict
*/
class IUserDictIterator : public IPMUnknown
{
public:

	/** 
		Queries first word in the user dictionary.

		@param pService		user dict service for the user dictionary.
		@param userDict		user dictionary to query.
		@param nType		Type of the word to query for.
		@param pWord		[OUT] first word found in the user dictionary.
		
		@return bool16		kTrue if query succeeded. 
	*/
	virtual bool16	First( IUserDictService *pService, IUserDict * userDict, IUserDictService::WordType nType, WideString *pWord ) = 0;

	/** 
		Queries next word in the user dictionary.

		@param pWord		[OUT] next word found in the user dictionary.
		
		@return bool16		kTrue if query succeeded. 
	*/
	virtual bool16	Next( WideString *pWord ) = 0;
};

#endif
