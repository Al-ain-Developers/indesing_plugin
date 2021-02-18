//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IFontLockingPrefsCmdData.h $
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
//  
//  Proj:	
//  
//========================================================================================

#pragma once
#ifndef _H_IFontLockingPrefsCmdData
#define _H_IFontLockingPrefsCmdData

#include "IPMUnknown.h"
#include "CJKID.h"

/** 
	Interface for command to set preferences of Japanese 
	FontLocking (Missing Glyph Protection) support
*/
class IFontLockingPrefsCmdData : public IPMUnknown
{
public:
	/** interface ID enum */
 	enum { kDefaultIID = IID_IFONTLOCKINGPREFSCMDDATA };

	/** Set the flag to use font locking
		@param useFontInputLocking		protects against missing glyphs when typing
		@param useFontChangeLocking		protects against missing glyphs when changing fonts
	*/
	virtual void Set(const bool16& useFontInputLocking, const bool16& useFontChangeLocking) = 0; 

	/** Get the flag to use font input locking
		@return		useFontInputLocking		
	*/
	virtual bool16 GetUseFontInputLocking() const = 0;

	/** Get the flag to use font change locking
		@return		useFontChangeLocking		
	*/
	virtual bool16 GetUseFontChangeLocking() const = 0;
};


#endif	/* _H_IFontLockingPrefsCmdData */
