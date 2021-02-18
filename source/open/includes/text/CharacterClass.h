//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/CharacterClass.h $
//  
//  Owner: ekenning
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
#ifndef __CharacterClass__
#define __CharacterClass__

#include "BaseType.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif


class PUBLIC_DECL CharacterClass
{
	public:
		static bool16 IsClickWordSelect(const UTF32TextChar& c, const UTF32TextChar& contextChar);
		static bool16 IsClickWordSelect(const UTF32TextChar& c);
		static bool16 IsContextSensitiveWordChar(const UTF32TextChar& c);
		
			// for ui double click action
		static bool16 IsClickJapaneseWordSelect(const UTF32TextChar& c1, const UTF32TextChar& c2);

		static bool16 Kinsoku_NoHardBreakBefore(const UTF32TextChar& c);
		static bool16 Kinsoku_NoSoftBreakBefore(const UTF32TextChar& c);		
		static bool16 Kinsoku_NoBreakAfter(const UTF32TextChar& c);
		static bool16 Kinsoku_NoBreakBetween(const UTF32TextChar& c1, const UTF32TextChar& c2);
			// kinsokushori rules

	protected:	// maybe not needed for public access...
		static bool16 Kinsoku_AfterDigitNoBreak(const UTF32TextChar& c);
		static bool16 Kinsoku_BeforeDigitNoBreak(const UTF32TextChar& c);
};


#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif
		// __CharacterClass__
		
