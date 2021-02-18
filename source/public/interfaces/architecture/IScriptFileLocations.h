//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptFileLocations.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __IScriptFileLocations__
#define __IScriptFileLocations__

#include "KeyValuePair.h"
#include "ScriptingID.h"

/**
	A utility class to access locations for scripts.
*/
class IScriptFileLocations : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTFILELOCATIONS } ;

	/** Retrieve the number of scripts folder locations
		@return the number of locations
	*/
	virtual int32		GetNumberOfScriptLocations() const = 0 ;

	/** Retrieve the name of the nth scripts folder location
		@param n is the index of the desired location
		@return the name of the nth location
	*/
	virtual PMString	GetNthScriptLocationName( int32 n ) const = 0 ;

	/** Retrieve the nth scripts folder location
		@param n is the index of the desired location
		@param resolveAlias if true and the location is an alias, resolves the alias
		@return the nth location, which may or may not correspond to an actual folder on disk
	*/
	virtual IDFile		GetNthScriptLocation( int32 n, bool16 resolveAlias ) const = 0 ;

	/** Retrieve a scripts folder location by name
		@param name is the name of the desired location
		@param resolveAlias if true and the location is an alias, resolves the alias
		@return the location with the specified name, which may or may not correspond to an actual folder on disk,
			or an empty IDFile if no match is found
	*/
	virtual IDFile		GetScriptLocationByName( const PMString& name, bool16 resolveAlias ) const = 0 ;

	/** Add a scripts folder location. If one already exists with the same name, 
		it is updated to the new location.
		@param name is the name of the location
		@param location is the folder, which may or may not correspond to an actual folder on disk
	*/
	virtual void		AddOrReplaceScriptLocationByName( const PMString& name, const IDFile& location ) = 0 ;

	/** Remove a scripts folder location.
		@param name is the name of the location
	*/
	virtual void		RemoveScriptLocationByName( const PMString& name ) = 0 ;
};

#endif // __IScriptFileLocations__
