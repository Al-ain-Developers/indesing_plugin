//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IShortcutUtils.h $
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
#ifndef __IShortcutUtils__
#define __IShortcutUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "VirtualKey.h"

class IWorkspace;
class IShortcutContext;
class IEvent;

/** This interface provides utility functions for working with shortcuts, and lives on the Utils boss.
	see Utils.h and use like so: Utils<IShortcutUtils>()->GetShortcutString( ... ) ;</pre>
	@ingroup text_util
*/
class IShortcutUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISHORTCUTUTILS };


	/** Returns a string including all the shortcuts assigned to this ActionID.
		@param id is the action you want the shortcuts for.
		@param bAddContextStr is a boolean indicating whether or not you want the string for the shortcut context in which this shortcut is valid appended to the string or not.
		@param bGetOnlyOne is a boolean indicating whether or not you want to get only one shortcut string.
		@return string describing all the shortcuts for this action.
	*/
	virtual PMString GetShortcutString(ActionID id, bool16 bAddContextStr = kFalse, const bool bGetOnlyOne = false) = 0;
	/** Returns a string describing the key & modifiers passed in.
		@param key is the virtual key you want a shortcut description for.
		@param mods is a set of modifier keys(from KBSCModifierDefs.h)
		@param shouldTranslate controls whether the individual modifier strings are translated.
		@return string describing this shortcut key + modifiers
	*/
	virtual PMString GetShortcutString(const VirtualKey& key, int16 mods, const bool& shouldTranslate = true) = 0;

	/** Parse a shortcut string into key & modifiers
		@param shortcutStr is shortcut string you want to parse
		@param keyOut is set to the key part of the shortcut from the string.
		@param modsOut is set to the modifiers from this shortcut string(defined in KBSCModifierDefs.h)
		@param shouldTranslate should be set true if you want the parser to traslate the individual components
				as it parses. Useful for reading untranslate strings from the XML keyboard shortcut file format.
	*/
	virtual void ParseShortcutString(const PMString& shortcutStr, VirtualKey *keyOut, int16 *modsOut, const bool& shouldTranslate = false) = 0;	
	
	/** Find the shortcut style.
		@param ws the workspace.
		@param key the virtual key you want a shortcut style for.
		@param mods a set of modifier keys(from KBSCModifierDefs.h)
		@param whichStrand specified ID
		@return shortcut style
	*/
	virtual UID FindShortcutStyle(IWorkspace *ws, const VirtualKey& key, int16 mods, ClassID *whichStrand) = 0;

	/** Returns approriate modifiers for using this event as a KBSC. 
		It may change the VirtualKey passed in(for numpad keys on windows)
		@param pEvent is the event you want the key & modifiers for
		@param vkey is the virtual key, which you pass in and may be changed by this function
		@return modifers for this event + vkey - see KBSCModifierDefs.h
	*/
	virtual int16 GetEventModifiersForKBSC(const IEvent* pEvent, VirtualKey& vkey) = 0;

	/** Returns the appropriate shortcut context for the current user state
		@return current user shortcut context
	*/
	virtual IShortcutContext* QueryCurrentContext() = 0;
	
	/** Is this event(virtual key + mods) an enabled shortcut in the currently active shortcut context.
		@param e is the event you want to know about
		@return true if this event refers to an enabled shortcut, taking into account what the current shortcut context is.
	*/
	virtual bool16 IsEnabledShortcut(const IEvent* e) = 0; 
	
	/** Get the status of the numlock key on the keyboard
		@return true if numlock key is on.
	*/
	virtual bool16 GetNumLockStatus() const= 0;

	/** Set the status of the numlock key on the keyboard. Client code should not call this.
		@param bStatus is the new status. 
	*/
	virtual void SetNumLockStatus(bool16 bStatus) = 0;
};


#endif	// __IShortcutUtils__
