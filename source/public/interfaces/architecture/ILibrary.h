//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibrary.h $
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
//  Reviewed: 9/25/98
//  
//  Purpose:
//  This interface is the main interface to the Library Boss.  This interface
//  controls openning and closing of the Library file and has various utility
//  methods to determine the status of the Library file.
//  
//========================================================================================

#pragma once
#ifndef __ILibrary__
#define __ILibrary__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"


class ILibraryScrapController;

/** The main interface to the library boss.  This interface controls opening and closing
	of a library file and has various utility methods to determine its status.
*/
class  ILibrary : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIBRARY };

	/** Initializes the Library Data.
		@return an error code
	*/
	virtual	ErrorCode Initialize() = 0;

	/** Opens the library with the given pathname.
		@param libraryFile IN the library file specification
		@param actualFileName IN the filename for the library
		@return kTrue if successful, kFalse otherwise
	*/
	virtual bool16 Open( const IDFile &libraryFile,  const PMString & actualFileName ) = 0;
	
	/** Creates a library with the given pathname.
		@param libraryFile IN the library file specification
		@param actualFileName IN the filename for the library
		@return kTrue if successful, kFalse otherwise
	*/
	virtual bool16 Create( const IDFile &libraryFile,  const PMString & actualFileName ) = 0;
	
	/** Closes the library.
	*/
	virtual void Close() = 0;
	
	/** Tell if the library is open.
		@return kTrue if open, kFalse if closed
	*/
	virtual bool16 IsOpen() const = 0;
	
	/** Tell if the library is locked (no changes can be made).
		@return kTrue for locked, kFalse for unlocked
	*/
	virtual bool16 IsLocked() const = 0;

	/** Get the total number of assets in library
		@return the number of assets
	*/
	virtual int32 Length() const = 0;
				
	/** Gets the name and path of the library file
		@return the file specification for the library
	*/
	virtual IDFile GetLibraryFileSpec() const = 0;
	
	/** Gets the file name of the library
		@return the library filename
	*/
	virtual PMString GetFileName() const = 0;
	
	
	//-------------- For Internal Use Only -------------------------

	// Tell whether the library is old and needs to be converted to snippet data store
	// Note: This will return kFalse if snippets are turned off in the QA menu. 
	// Plus: Do not call this on an already-open library -- use LibraryIsPreSnippets()
	/** * For Internal Use Only *
	*/
	virtual bool16 NeedsSnippetConversion( const IDFile &libraryFile ) = 0;

	// Converts the input library file to snippet data storage format
	/** * For Internal Use Only *
	*/
	virtual bool16 ConvertToSnippets( const IDFile &oldLibraryFile,  IDFile &newLibraryFile, bool16 bUseOldName = kFalse ) = 0;

	// Tell whether the file is pre-snippets.  Assumes the file is open already
	/** * For Internal Use Only *
	*/
	virtual bool16 LibraryIsPreSnippets() = 0;
		
	// Gets the interface to the library scrap controller
	/** * For Internal Use Only *
	*/
	virtual ILibraryScrapController* GetScrapController() const = 0;
	
	// Disable and Enable Notification of Library Open and Close events
	/** * For Internal Use Only *
	*/
	virtual void DisableLibraryLevelNotification() = 0;
	/** * For Internal Use Only *
	*/
	virtual void EnableLibraryLevelNotification() = 0;
};

#endif