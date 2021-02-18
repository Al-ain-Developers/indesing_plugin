//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IGlyphFacade.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  A high level API for dealing with glyph-related functions
//  
//========================================================================================

#pragma once
#ifndef __IGlyphFacade__
#define __IGlyphFacade__


#include "IGlyphUtils.h"
#include "IPMUnknown.h"
#include "TextID.h"


/**
 High-level facade interface for glyph-related queries.
 @see IGlyphUtils
*/
namespace Facade
{
	class IGlyphFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IGLYPHFACADE };

		/**	Return a string for the name of the unicode character. 
			@param c			the UTF32TextChar character to look up the name for
			@return				the Unicode name of the character. Maybe be missing for some characters, will return empty string in this case.
		 */
		virtual PMString	GetUnicodeName(const UTF32TextChar& c) = 0;

	};
}
#endif // __IGlyphFacade__
