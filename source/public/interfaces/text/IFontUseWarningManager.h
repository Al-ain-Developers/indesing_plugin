//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontUseWarningManager.h $
//  
//  Owner: Joe Shankar
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
#ifndef __IFontUseWarningManager__
#define __IFontUseWarningManager__

#include "FontMgrID.h"
class IPMFont;

/** IFontUseWarningManager can be called before applying a font 
	selected by the user to check it and possibly warn the user about restrictions.
	@ingroup text_font
*/
class IFontUseWarningManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFONTUSEWARNINGMANAGER };

		// Warning flags can be or'd together.
		typedef enum {
					kDefaultWarning = -1,		// Default application warning behavior, may depend on user preference.
					kWarnIfBitmap	= 0x01		// Warn about bitmap fonts
		} WarningFlags;
				
		
		// returns true if the user ought to be warned, and would be warned by WarnUser
		virtual bool16 ShouldWarn(IPMFont* checkThisFont, WarningFlags flags, bool16 fDontWarnTwice ) = 0;

		// Return kTrue if the user was warned.
		virtual bool16 WarnUser(IPMFont* checkThisFont, WarningFlags flags) = 0;
};

#endif // __IFontUseWarningManager__