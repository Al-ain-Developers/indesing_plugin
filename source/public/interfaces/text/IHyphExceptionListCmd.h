//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphExceptionListCmd.h $
//  
//  Owner: hhorton
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef _H_IHyphExceptionListCmdData
#define _H_IHyphExceptionListCmdData


#include "IPMUnknown.h"

class HyphenExceptionsList;

class IHyphExceptionListCmdData : public IPMUnknown
{
	public:
		/**	
			Sets hyphenation exception list.
			
			@param list	Hyphenation exception list to set to.
		 */
		virtual void Set(const HyphenExceptionsList& list) = 0;
		/**	
			Gets hyphenation exception list in the command data.
			Simply just calls GetHyphenationExceptionsList.
			
			@return HyphenExceptionsList&	Hyphenation exception list retrieved.
		 */
		const HyphenExceptionsList& Get() const
			{ return GetHyphenationExceptionsList(); }

		/**	
			Gets hyphenation exception list in the command data.
			
			@return HyphenExceptionsList&	Hyphenation exception list retrieved.
		 */
		virtual const HyphenExceptionsList& GetHyphenationExceptionsList() const = 0;
};


#endif /* _H_IHyphExceptionListCmdData */
