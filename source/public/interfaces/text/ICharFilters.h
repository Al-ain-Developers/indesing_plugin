//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICharFilters.h $
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
#ifndef __ICharFilters__
#define __ICharFilters__

#include "TextID.h"
#include "IPMUnknown.h"
#include "Utils.h"


/** Please use the ICharFilters directly via the UtilsBoss if possible. See Utils.h.
<pre>	Utils&lt;ICharFilters&gt;()->SpellingIsWordChar( ... )</pre>
	@ingroup text_util 
*/
class ICharFilters : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICHARFILTERS };

	virtual bool16 SpellingIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 SpellingIsWordCharNoPeriod( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 DefaultIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 TestIsSpace( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 TestIsPunctuation( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 LanguageIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 SpellingIsWordCharNoPunctuation( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 SpellingIsUserDictChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
	virtual bool16 TextMacroCodeIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd ) = 0;
};


#endif	// __ICharFilters__
