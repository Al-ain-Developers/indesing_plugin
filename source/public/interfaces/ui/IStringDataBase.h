//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStringDataBase.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IStringDataBase_h__
#define __IStringDataBase_h__

#include "IPMUnknown.h"
#include "PMLocaleId.h"
#include "WorkspaceID.h"

class PMString;
class IStringDataBaseTable;

//========================================================================================
// CLASS IStringDataBase
//========================================================================================
/** Interface which holds table of key strings and localized strings and provides translation
*/

class IStringDataBase : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTRINGDATABASE };
	
	/** Add a new string to the string database
		@param localeId specifies which language this string is for. Typically there's only a string database for 1 language per run.
		@param key untranslated keystring.
		@param string translated string for the language specified by localeId
		@param providingPlugin the id of the plugin providing this string. Just used to debug string collisions at the moment.
	*/
	virtual void			Add(const PMLocaleId& localeId,
								const PMString& key, const PMString& string, const PluginID &providingPlugin) = 0;
	
	/** Look up a translation in the string database
		@param localeId specifies which language you want the translation in. Only works if a string database for the language has been populated.
		@param key untranslated keystring.
		@return translated string for the language specified by localeId
	*/
	virtual bool16			Retrieve(const PMLocaleId& localeId,
									 const PMString& key, PMString& string) const = 0;

	/** Internal use only. Disables purging of the string database
	*/
	virtual void			TurnOffMemoryPurge() = 0;

	/** Direct access to the string table for a specified locale.
		Returns a pointer to the string table for the specified locale. May return nil if a string table was not initialized for that locale.
		INTERNAL USE ONLY!
	*/
	virtual const IStringDataBaseTable* GetStringTable(const PMLocaleId& locale) const = 0;
	
	/** Notification when all strings for this locale have been added. Must be called before Retrieve.
	*/
	virtual void			InitializationComplete(const PMLocaleId& locale) = 0;
	
	/** Internal use only. Destroys string database.
	*/
	virtual void			Cleanup() = 0;
	
	/** Look up a translation in the string database
		@param localeId specifies which language you want the translation in. Only works if a string database for the language has been populated.
		@param key untranslated keystring.
		@return translated string for the language specified by localeId
	*/
	virtual bool16			Retrieve(const PMLocaleId& localeId,
									 ConstCString key, PMString& string) const = 0;
};

#endif // __IStringDataBase_h__
