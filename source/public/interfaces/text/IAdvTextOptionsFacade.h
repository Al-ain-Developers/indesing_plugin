//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAdvTextOptionsFacade.h $
//  
//  Owner: nmccully
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
#ifndef __IAdvTextOptionsFacade__
#define __IAdvTextOptionsFacade__

// ----- Interfaces -----

#include "IPMUnknown.h"
#include "TextID.h"

// ----- Includes -----


namespace Facade
{
	/**   A high level API for dealing with advanced text options prefs.  Please use the IAdvTextOptionsFacade 
		directly via the UtilsBoss if possible, see Utils.h:
		i.e. Utils<Facade::IAdvTextOptionsFacade>()->GetMissingGlyphProtectionForInput( ... ) ;
		  @author Nat McCully
	   */
	class IAdvTextOptionsFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IADVTEXTOPTIONSFACADE };
		
		//------------------------------------------------------
		//	Text Sizes Prefs
		//------------------------------------------------------

		//------------------------------------------------------
		//	IME Prefs
		//------------------------------------------------------

		//------------------------------------------------------
		//	Missing Glyph Protection Prefs
		//------------------------------------------------------

		/** Set the flag to use missing glyph protection
			@param useFontInputLocking		protects against missing glyphs when typing
			@param useFontChangeLocking		protects against missing glyphs when changing fonts
		*/
		virtual void SetMissingGlyphProtectionPrefs(const bool16 useFontInputLocking, const bool16 useFontChangeLocking) = 0; 

		/** Get the flag to use font input locking
			@return		useFontInputLocking		
		*/
		virtual bool16 GetMissingGlyphProtectionForInput() const = 0;

		/** Get the flag to use font change locking
			@return		useFontChangeLocking		
		*/
		virtual bool16 GetMissingGlyphProtectionForFontChange() const = 0;
	};
}

#endif	// __IAdvTextOptionsFacade__
