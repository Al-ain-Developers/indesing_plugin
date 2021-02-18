//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/INamedGridInfo.h $
//  
//  Owner: EricK
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
#ifndef __INAMEDGRIDINFO__
#define __INAMEDGRIDINFO__

#include "IPMUnknown.h"
#include "CJKGridID.h"

/**
	Data interface for the non grid data parts of a named grid.
*/

class INamedGridInfo : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_INAMEDGRIDINFO };
	
		/** Returns the name of the named grid.
		*/
		virtual const PMString GetName() const = 0;

		/** Sets the name of the named grid.
		@param s IN The new name of the named grid.
		@param translatable IN Is this string translatable.
		*/
		virtual void SetName(const PMString& s, bool16 translatable = kFalse) = 0;

		/**
		Set the keyboard shortcut that triggers this named grid.
		@param virtualKey is the key code.
		@param modifiers are the modifier keys.
		@see KeyboardDefs.h
		*/
		virtual void SetKeyboardShortcut(uint16 virtualKey, int16 modifiers) = 0; 
		/**
		Get the keyboard shortcut that triggers this named grid.
		@param modifiers MAY NOT BE NIL.
		@return the key code.
		*/
		virtual uint16 GetKeyboardShortcut(int16 *modifiers) const = 0; 
		
};

#endif
