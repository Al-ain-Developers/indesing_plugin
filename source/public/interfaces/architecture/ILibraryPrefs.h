//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryPrefs.h $
//  
//  Owner: Mark VerMurlen
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
#ifndef __ILibraryPrefs__
#define __ILibraryPrefs__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"

class PMString;

/**	This interface is a secondary interface to the Library Boss.  This interface
	is used to set Library preference data in the library file.  The Library does
	not have any predefined preferences, so the Library client is free to store
	whatever key/value pairs that are wanted.
*/
class ILibraryPrefs : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ILIBRARYPREFS};

	/** Set the preference.
		@param key IN key for the preference
		@param value IN value for the preference
	*/
	virtual void SetLibraryPref( const PMString& key, const PMString& value ) = 0;
		
	/** Gets a preference value, or sets if not found.
		@param key IN preference to look up
		@param value OUT value associated with key, if found
		@param defaultValue IN if key not found, sets it with this value
		@return kTrue (always)
	*/
	virtual bool16 GetLibraryPref( const PMString& key, PMString& value, const PMString& defaultValue ) const = 0;
};


#endif