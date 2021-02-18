//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStripCharService.h $
//  
//  Owner: Ryan Gano (based on ITOCStripCharService by Yeming Liu)
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
#ifndef __ISTRIPCHARSERVICE__
#define __ISTRIPCHARSERVICE__

#include "BaseType.h"		// for textchar
#include "K2Vector.h"

/** This is a pair of textchar/textchar.
	It is used in the FillListWithHyperlinkDestinations method
	@ingroup text_service
*/
struct TextCharPair {
	typedef  object_type data_type;

/** Constructor for a TextCharPair
	@param first - The character to mark as removable
	@param second - The character to replace the removed character with
*/
	TextCharPair(UTF32TextChar first, UTF32TextChar second)
	{
		fRemove = first;
		fReplace = second;
	}

	/** The only comparison for whether two items are equal is on fRemove
		@param rhs - The item to compare with this one.
	*/
	inline bool16 operator==(const TextCharPair &rhs) const
	{return fRemove == rhs.fRemove;}

	/** character to remove from a string */
	UTF32TextChar	fRemove;
	/** character to replace it with */
	UTF32TextChar	fReplace;
};

/** This service is used for stripping invalid characters out of text so that it will not
	be displayed in the UI or saved as the name for something. 
	@ingroup text_service
*/
class IStripCharService : public IPMUnknown
{
	public:
		/** Checks the serviceID passed in and fills the registeredCharList with pairs which contain 
			characters that should be removed and the character they should be replaced with
			@param replaceCharList - Filled with a list of characters to not allow which maps to a list of characters to replace them with
			@param stripServices - The service IDs to use when determining which characters to strip.
			@param replaceWith - Can be used to specify which character to replace an invalid character with (nil will result in default)
		*/
		virtual void GetReplacedChars(K2Vector<TextCharPair>& replaceCharList, const K2Vector<ServiceID>& stripServices, 
											   textchar *replaceWith = nil) = 0;
};

#endif //__ITOCSTRIPCHARSERVICE__
