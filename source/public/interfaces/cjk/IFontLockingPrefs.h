//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IFontLockingPrefs.h $
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
#ifndef __IFontLockingPrefs__
#define __IFontLockingPrefs__

#include "IPMUnknown.h"
#include "CJKID.h"

/** 
	Interface for getting and setting preferences of Japanese 
	Font Locking (Missing Glyph Protection) support
*/
class IFontLockingPrefs : public IPMUnknown
{
public:	

	/** interface ID enum */
 	enum { kDefaultIID = IID_IFONTLOCKINGPREFS };
 
	/** 
		Set the flag for using font input locking
		@param useInputLocking		Whether to protect against missing glyphs on text input
	*/
	virtual void SetFontInputLocking(const bool16 useInputLocking) = 0;
	
	/** 
		Get the flag to use font input locking 
		@return Whether to protect against missing glyphs on text input 
	*/
	virtual bool16 GetFontInputLocking() const = 0;

	/** 
		@param useFontChangeLocking		Whether to protect against missing glyphs on font change
	*/
	virtual void SetFontChangeLocking(const bool16 useFontChangeLocking) = 0;
	
	/** 
		@return Whether to protect against missing glyphs on font change 
	*/
	virtual bool16 GetFontChangeLocking() const = 0;
};

#endif //__IFontLockingPrefs__
