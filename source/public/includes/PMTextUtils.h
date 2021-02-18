//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMTextUtils.h $
//  
//  Owner: Eric_Menninga
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
//  There already is a TextUtils.h in the MacOS interfaces
//  
//========================================================================================

#pragma once
#ifndef __PMTextUtils__
#define __PMTextUtils__

#include "ITextUtils.h"
#include "Utils.h"
#include "ICharFilters.h"		// for PMCharFilters
#include "RangeData.h"			// for StoryRange


// BP 4/17/97: The TextOffscreen is a TextEditor service. It will be cached in PMTextUtils.cpp.
//	Please do not use SetTextOffscreen(). This function shall only be called by ITextOffscreen itself.
//	Since text redraw is very time critical we have to do some ugly optimization tricks...
class ITextOffscreen;
PUBLIC_DECL ITextOffscreen 	*QueryTextOffscreen();
PUBLIC_DECL void			SetTextOffscreen( ITextOffscreen *pOffscreen );

// This is the new direction
namespace Text {
		// use these functions instead of PMString("RomanRegularBookPlainMedium").Cointain();
	inline	bool16 IsPlainStyleName( const PMString &styleName )
			{ return Utils<ITextUtils>()->IsPlainStyleName( styleName ); }

	inline	bool16 IsItalicStyleName( const PMString &styleName )
			{ return Utils<ITextUtils>()->IsItalicStyleName( styleName ); }

	inline	bool16 IsBoldStyleName( const PMString &styleName )
			{ return Utils<ITextUtils>()->IsBoldStyleName( styleName ); }

	inline	bool16 IsBoldItalicStyleName( const PMString &styleName )
			{ return Utils<ITextUtils>()->IsBoldItalicStyleName( styleName ); }
}

namespace PMCharFilters
{
	inline bool16 SpellingIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->SpellingIsWordChar( aStart, aEnd ); }

	inline bool16 SpellingIsWordCharNoPeriod( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->SpellingIsWordCharNoPeriod( aStart, aEnd ); }

	inline bool16 DefaultIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->DefaultIsWordChar( aStart, aEnd ); }

	inline bool16 TestIsSpace( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->TestIsSpace( aStart, aEnd ); }

	inline bool16 TestIsPunctuation( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->TestIsPunctuation( aStart, aEnd ); }

	inline bool16 LanguageIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->LanguageIsWordChar( aStart, aEnd ); }

	inline bool16 SpellingIsWordCharNoPunctuation( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->SpellingIsWordCharNoPunctuation( aStart, aEnd ); }

	inline bool16 SpellingIsUserDictChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->SpellingIsUserDictChar( aStart, aEnd ); }

	inline bool16 TextMacroCodeIsWordChar( const UTF32TextChar& aStart, const UTF32TextChar& aEnd )
			{ return Utils<ICharFilters>()->TextMacroCodeIsWordChar( aStart, aEnd ); }
}

#endif
		// __PMTextUtils__
