//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICatalogList.h $
//  
//  Owner: Hardeep S Parmar
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ICatalogList__
#define __ICatalogList__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "ICatalog.h"

/** Access library catalogs.  Provides ways to create, open, close, and recover catalog files.
*/
class ICatalogList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICATALOGLIST };

		/** For Internal Use Only.  Recovery status flags.
		*/
		enum { kQuery=0, kInProgress, kDone };

		/** Create a new catalog.  (Not AddRef'ed, no need to Release.)
			@param catalogFile IN file specification for catalog
			@return interface pointer to ICatalog created
		*/
		virtual	ICatalog*		NewCatalog(const IDFile& catalogFile) = 0;
		
		/** Open an existing catalog.  (Not AddRef'ed, no need to Release.)
			@param catalogFile IN file specification for catalog
			@return interface pointer to ICatalog opened
		*/
		virtual	ICatalog*		OpenCatalog(const IDFile& catalogFile) = 0;

		/** For Internal Use Only.  Recover a catalog.
			@param pubFile IN the catalog file to recover
			@param miniSaveFile IN minisave file specification if it exists
			@param protection IN protection level
			@param fileInfo IN (Macintosh only) type and creator information (use nil on Windows)
			@return interface pointer to recovered catalog

			Type and creator information block is as follows:
			<pre>
	typedef struct MacintoshFileInfo {
		SysOSType fCreator;
		SysOSType fFileType;
	} MacintoshFileInfo;
			</pre>
		*/
		virtual ICatalog*		RecoverCatalog(const IDFile* pubFile, const IDFile* miniSaveFile, IDataBase::ProtectionLevel protection, void* fileInfo) = 0;

		/** Close a catalog.
			@param catalogFile IN file specification for catalog
		*/
		virtual	void			CloseCatalog( ICatalog* catalog ) = 0;
			
		/** Get the number of catalogs open.
			@return the number of open catalogs
		*/
		virtual	int32			GetCatalogCount( ) = 0;
		
		/** Iterate through open catalogs.
			@param n IN catalog index to get
			@return ICatalog interface pointer or nil
		*/
		virtual ICatalog* 		GetNthCatalog( int32 n ) = 0;
		
		/** Retrieve a catalog matching a file specification.
			@param cataloge IN file specification for catalog
			@return interface pointer to ICatalog found. (Not AddRef'ed, no need to Release.)
		*/
		virtual	ICatalog*		FindDoc(const IDFile& catalog) = 0;

		/** For Internal Use Only. Gets/sets recovery status flag for a library. Acts like a global flag. 
		*/
		virtual void			Recovery(int16& status) { };
};

#endif
