//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryService.h $
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
//  
//  Reviewed: 9/28/98
//  
//  Purpose:
//  This interface is used to create and manage Library Bosses.  It also is used
//  to obtain interfaces to Library utilities.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryService__
#define __ILibraryService__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"

class ILibrary;
class ILibraryCmdUtils;
class ILibraryDragDropUtils;

/**  This interface is used to create and manage Library Bosses.  It also is used
	to obtain interfaces to Library utilities.
*/
class  ILibraryService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIBRARYSERVICE };

	/** Create a new library object and return a pointer to it.
		The library service keeps a reference to the library, so the caller must call
		ReleaseLibrary when finished with it to cause the Library Service to release it.
		@return interface pointer to library created
	*/
	virtual ILibrary* CreateLibrary() = 0;
	
	/** Call when finished with using a library object.
		The library will most likely be destructed during this call.
		@param library IN the library to release
	*/
	virtual void ReleaseLibrary( ILibrary* library ) = 0;

	/** Get the number of library objects currently in use.
		@return the number of libraries
	*/
	virtual int32 NumLibraries() const = 0;	
	
	/** Get the Nth library.
		@param n IN library index
		@return interface pointer to nth library
	*/
	virtual ILibrary* QueryNthLibrary(int32 n) const = 0;
	
	/** Get the Library Command Utilities interface.
		@return interface pointer to ILibraryCmdUtils
	*/
	virtual ILibraryCmdUtils* QueryLibraryCmdUtils() const = 0;
	
	/** Get the Library Drag&Drop Utilities interface.
		@return interface pointer to ILibraryDragDropUtils
	*/
	virtual ILibraryDragDropUtils* QueryLibraryDDUtils() const = 0;
};

#endif