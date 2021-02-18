//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IShortcutManager.h $
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
#ifndef __IShortcutManager__
#define __IShortcutManager__

#include "IPMUnknown.h"
#include "VirtualKey.h"
#include "PMString.h"
#include "ActionID.h"
#include "IKBSCSetsManager.h"

class IShortcutContext;
/**	This is the interface that manages the keyboard shortcuts for the application. It maintains a mapping of key combo(which is a key + 0 or more modifier keys) + shortcut context to ActionID.
	Whenever we get a key event that isn't handled by whatever eventhandler currently has the key focus, we check to see if it's a shortcut(by calling IsEnabledShortcut), and if it is, we execute the action
	by calling PerformShortcut. This interface also supports the functionality in the keyboard shortcut editor dialog, including adding & removing shortcuts, and reading and writing shortcut sets. 
	In a Debug build, you can see some information about the shortcut matching that happens if you enable TRACE for the category "Shortcuts" from the test menu.
*/
class IShortcutManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISHORTCUTMANAGER };

		/**	Add a shortcut 
			@param actionToAddTo The action that this new shortcut should invoke.
			@param contextStr The string for the context this shortcut should be assigned in. @see IShortcutContext.
			@param key The key for the new shortcut
			@param mods The modifier keys for the new shortcut. @see KBSCModifierDefs.h
		*/
		virtual void				AddShortcut(ActionID actionToAddTo, const PMString & contextStr, const VirtualKey& key, int16 mods) = 0;

		/**	Remove all shortcuts associated with a particular action 
			@param id The action to remove shortcuts for
		*/
		virtual void				RemoveAllShortcutsForAction(ActionID id) = 0;
		
		/**	Remove a shortcut 
			@param contextStr The string for the context this existing shortcut. @see IShortcutContext.
			@param key The key for the existing shortcut
			@param mods The modifier keys for the existing shortcut. @see KBSCModifierDefs.h
		*/
		virtual void				RemoveShortcut(const PMString& context,	const VirtualKey& key, int16 mods) = 0;

		/**	Invoke the action associated with a shortcut. Should only be called if you know there is an enabled shortcut for this set of parameters.
			@param context The starting context. This method will also look in the rest of the context chain if the current context does not have an entry for this shortcut. 
				@see IShortcutContext. Often retrieved from a call to IShortcutUtils::QueryCurrentContext()
			@param key The key for the shortcut
			@param mods The modifier keys for the shortcut. @see KBSCModifierDefs.h
		*/
		virtual void				PerformShortcut(const IShortcutContext* context, const VirtualKey& key, int16 mods) = 0;
		
		/**	Check whether a shortcut is enabled 
			@param context The starting context. This method will also look in the rest of the context chain if the current context does not have an entry for this shortcut.
			 	@see IShortcutContext. Often retrieved from a call to IShortcutUtils::QueryCurrentContext()
			@param key The key for the shortcut
			@param mods The modifier keys for the shortcut. @see KBSCModifierDefs.h
			@return kTrue if there is an enabled shortcut matching the passed in parameters.
		*/
		virtual bool16				IsEnabledShortcut(const IShortcutContext* context, const VirtualKey& key, int16 mods) = 0;

		/**
			Retrieve the action associated with a shortcut in a single context
			@param contextStr The string for the context to look for this shortcut. @see IShortcutContext. Often retrieved from a call to IShortcutUtils::QueryCurrentContext()
			@param key The key for the shortcut
			@param mods The modifier keys for the shortcut. @see KBSCModifierDefs.h
			@return kInvalidActionID if no shortcut found in this context, else the ActionID of the assigned action.
		*/
		virtual ActionID			GetActionIDOfShortcut(const PMString& contextString, const VirtualKey& key, int16 mods) const = 0;
		
		/**
			Retrieve the action associated with a shortcut. This one looks in the context passed in, as well as all the 'next' contexts.
			@param context The starting context. This method will also look in the rest of the context chain if the current context does not have an entry for this shortcut. 
				Often retrieved from a call to IShortcutUtils::QueryCurrentContext() @see IShortcutContext.
			@param key The key for the shortcut
			@param mods The modifier keys for the shortcut. @see KBSCModifierDefs.h
			@return kInvalidActionID if no shortcut found in the context chain, else the ActionID of the assigned action.
		*/
		virtual ActionID			GetActionIDInContextChain(const IShortcutContext* context, const VirtualKey& key, int16 mods) const = 0;

		/**	Clear all shortcuts */
		virtual void				ClearShortcuts() = 0;

		/**	Retrieve the number of shortcuts associated with a particular action 
			@param actionID the action to investigate
			@return count of how many shortcuts are assigned to this action.
		*/
		virtual int32				GetNumShortcutsForAction(ActionID actionID) const = 0;
		
		/**
			Retrieve information about the nth shortcut associated with a particular action.
			Pass nil for things you don't care about.
			@param actionID The action to get the shortcuts for.
			@param index Index of which shortcut for this action to return.
			@param contextStrOut filled out with the context string for the nth action. Pass nil if you don't need this info.
			@param keyOut filled out with the key for the nth action. Pass nil if you don't need this info.
			@param modsOut filled out with the modifier keys for the nth action. Pass nil if you don't need this info.
		*/
		virtual void				GetNthShortcutForAction(ActionID actionID, int32 index, PMString* contextStrOut, VirtualKey* keyOut, int16* modsOut) const = 0;

		/**	Retrieve the number of shortcut contexts 
			@return count of known shortcut contexts
		*/
		virtual int32				GetNumShortcutContexts() const = 0;
		
		/**	Query the nth shortcut context 
			@return the nth shortcut context known to the shortcut manager
		*/
		virtual IShortcutContext*	QueryNthShortcutContext(int32 index) const = 0;
		
		/**	Query a shortcut context by name 
			@param contextName the name of the shortcut context
			@return the IShortcutContext which matches that name, or nil if no match was found.
		*/
		virtual IShortcutContext*	QueryShortcutContextByName(const PMString& contextName) const = 0;

		/** Retrieve the filename of the current shortcut set 
			@return filename of current shortcut set.
		*/
		virtual PMString			GetShortcutSetFilename() const = 0;

		/** Retrieve the area of the current shortcut set 
			@return area of current shortcut set.
		*/
		virtual IKBSCSetsManager::KBSCArea	GetShortcutKBSCArea() const = 0;

		typedef enum {
			/** kKBSCFileNoError success*/
			kKBSCFileNoError = 0, 
			/** kKBSCFileNotFound File was not found*/
			kKBSCFileNotFound, 
			/** kKBSCFileWrongPlatform File appears to be from wrong platform(i.e. trying to open windows shortcut set on mac)*/
			kKBSCFileWrongPlatform, 
			/** kKBSCFileFormatWrongOrCorrupt File isn't a known type of shortcut set*/
			kKBSCFileFormatWrongOrCorrupt, 
			/** kKBSCFileFormatIncompatible File isn't a version that can be understood*/
			kKBSCFileFormatIncompatible,
			/** kKBSCFileWriteError failed to write file*/
			kKBSCFileWriteError
		} ShortcutFileError; 
		
		/** Update the current shortcuts to those in a file 
			@param filename The name of the new shortcut file to use
			@return kKBSCFileNoError if successful, else one of the errors.
		*/
		virtual ShortcutFileError	ChangeShortcutSetFile(const PMString& filename, IKBSCSetsManager::KBSCArea area) = 0;
		
		/** Save the current shortcut set to the current shortcut file 
			@return kKBSCFileNoError if successful, else one of the errors, most likely kKBSCFileWriteError.
		*/
		virtual ShortcutFileError	SaveCurrentShortcutSetFile() = 0;

		/** Load the default shortcut set file. For English, this is Default.indk, but in general is the file
			corresponding to the translation of the "#defaultKBSCSetName" string.
			@return kKBSCFileNoError if successful, else one of the errors, most likely kKBSCFileWriteError.
		*/
		virtual ShortcutFileError	LoadDefaultShortcutSetFile(const PMLocaleId& locale) = 0;

		/**
			Retrieve information about the shortcut that has been invoked. Only valid during a call to PerformShortcut.
			Pass nil for things you don't care about. It's quite rare for client code to need this information.
			@param contextStrOut filled out with the context string for the current shortcut. Pass nil if you don't need this info.
			@param keyOut filled out with the key for the current shortcut. Pass nil if you don't need this info.
			@param modsOut filled out with the modifier keys for the current shortcut. Pass nil if you don't need this info.
		*/
		virtual void				GetCurrentShortcut(PMString* contextOut, VirtualKey* keyOut, int16* modsOut) const = 0;

		/**
			Retrieve the action name that was persisted with shortcuts for a particular action id. Can be used to determine 
			whether the shortcuts assigned to this action id are assigned to the wrong action by comparing with the name 
			currently associated with the action (see IActionManager::GetActionName). This could happen if the id/name 
			mapping for an action is dynamic and had been persisted in the preferences folder but then discarded.
			It's quite rare for client code to need this information.
			@param actionID the action to get the name of
			@return string for the name of this action at the time of the last save.
		*/
		virtual const PMString&		GetPersistedActionName( const ActionID& actionID ) const = 0 ;

		/** Start up the shortcut manager. Internal use only. */
		virtual bool16				Startup(const PMLocaleId& locale) = 0;
		
		/** Shut down the shortcut manager. Internal use only. */
		virtual void				Shutdown(const PMLocaleId& locale) = 0;

#ifdef DEBUG
		typedef enum { contextInfo, allShortcutInfo, shortcutsMissingActions} ShortcutInfoType;
		/** Dump the contents of the shortcut manager */
		virtual void				DumpShortcutInfo(ShortcutInfoType infoType) = 0;
		/** Remove all shortcuts associated with unregistered actions */
		virtual void				RemoveAllShortcutsForUnregisteredActionIDs() = 0;
#endif
};

#endif // __IShortcutManager__
