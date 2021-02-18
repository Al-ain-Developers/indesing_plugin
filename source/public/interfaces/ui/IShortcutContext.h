//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IShortcutContext.h $
//  
//  Owner: lance bushore
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
#ifndef __IShortcutContext__
#define __IShortcutContext__


#include "IPMUnknown.h"

#include "PMString.h"
#include "ActionID.h"
#include "VirtualKey.h"

#define kDefaultContext "DefaultContext"

/** This interface is part of our support for 'shortcut contexts' whereby the same key combo can do different things in different contexts.
	For example, the arrow keys move around the text when in text context, but nudge the selected item around on the page when in default context.
	Typically, 3rd parties would not need to use/implement this interface, unless they're adding a new shorcut context, in which case they'll have
	to create a new implementation of this interface, and put it on a boss supporting kShortcutContextService
*/
class IShortcutContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISHORTCUTCONTEXT };

		/** returns the string for this context. If empty, context will be ignored.
			@return string describing this context
		*/
		virtual PMString		GetShortcutContextString() const= 0;
		
		/** returns the string for the context to try if no shortcut was found in this context. Most common is "" to stop looking,
			or kDefaultContext to look at the shortcuts in the default context
			@param key The virtual key we're checking shortcuts for
			@param currentModifiers The modifiers we're checking shortcuts for. @see KBSCModifierDefs.h
			@return the string for the next context to look in
		*/
		virtual PMString		GetNextContextString(const VirtualKey& key, int16 currentModifiers) const= 0;
		
		/** Gives the shortcut context an opportunity to modify the key and modifiers before they're used to look up the associated action.
			This is used by the text context to treat the arrow keys differently in horizontal vs. vertical text.
			@param key The virtual key we're checking shortcuts for
			@param pModifiers The modifiers we're checking shortcuts for. @see KBSCModifierDefs.h
			@return the remapped virtual key
		*/
		virtual VirtualKey	RemapShortcutKey(const VirtualKey& key, int16 * pModifiers) const = 0;
		
};

#endif // __IShortcutContext__
		
		