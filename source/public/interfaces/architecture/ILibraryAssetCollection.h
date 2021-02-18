//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAssetCollection.h $
//  
//  Owner: 
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
//  Purpose:
//  This interface is a secondary interface to the Library Boss.  This interface
//  controls the "collection" of assets that make up the Library.  Use this
//  interface to add and remove assets from the Library.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAssetCollection__
#define __ILibraryAssetCollection__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"


class ILibraryAsset;
class ILibraryAssetIterator;
class ILibraryComplexFilterData;
class LibraryAssetID;

/** A secondary interface to the Library boss, this controls the "collection" of assets
	that make up the library.  Use this to add and remove assets from the library.
*/
class ILibraryAssetCollection : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIBRARYASSETCOLLECTION };

	/** Adds a new empty asset to the collection and returns a pointer to it.
		You must later release the asset.
		@return the ILibraryAsset pointer
	*/
	virtual ILibraryAsset* AcquireNewAsset() = 0;
	
	/** Adds a new asset to the collection by copying an existing asset and
		returns a pointer to the new copy.  You must later release the copied
		asset.
		@param sourceAsset IN the asset to copy
		@return an interface pointer to the new ILibraryAsset
	*/
	virtual ILibraryAsset* AcquireAssetCopy(ILibraryAsset* sourceAsset) = 0;
	
	/** Gets the asset with the given id and returns a pointer to it.  You must
		later release the asset.
		@param id IN the LibraryAssetID for the asset to get
		@return the ILibraryAsset pointer for the asset
	*/
	virtual ILibraryAsset* AcquireAsset(const LibraryAssetID& id) = 0;
	
	/** Releases the asset.  If the assetWasChanged flag is true, observers will
		be notified that the asset has changed.
		@param asset IN an interface pointer to the asset to release
		@param assetWasChanged IN kTrue to notify observers, kFalse otherwise
		@param bForce IN * For Internal Use Only *
	*/
	virtual void ReleaseAsset( ILibraryAsset* asset, bool16 assetWasChanged = kTrue, bool16 bForce = kFalse ) = 0;
	
	/** Removes the asset with the given id from the collection.
		@param id IN the asset's LibraryAssetID
	*/
	virtual void RemoveAsset(const LibraryAssetID& id) = 0;
	
	/** Get whether the collection is open.
		@return kTrue if the collection is open, kFalse otherwise
	*/
	virtual bool16 IsOpen() const = 0;
	
	/** Get whether the collection is locked (no changes can be made).
		@return kTrue if locked, kFalse otherwise
	*/
	virtual bool16 IsLocked() const = 0;
	
	/** Returns an iterator to traverse the assets in the collection.
		@param IN inFilter information about how to filter; pass nil to see all assets
		@return an interface pointer to ILibraryAssetIterator
	*/
	virtual ILibraryAssetIterator* CreateIteratorWithFilter(ILibraryComplexFilterData* inFilter) = 0;
	
	/** Get the total number of assets in collection.
		@return the collection length
	*/
	virtual int32 Length() const = 0;	
			
	//-------------- For Internal Use Only -------------------------
	
	// Opens the collection with the given pathname
	/** * For Internal Use Only *
	*/
	virtual bool16 Open( const IDFile &libraryFile ) = 0;
	
	// Creates a new collection with the given pathname
	/** * For Internal Use Only *
	*/
	virtual bool16 Create( const IDFile &libraryFile ) = 0;
	
	// Closes the collection.
	/** * For Internal Use Only *
	*/
	virtual void Close() = 0;
	
	// Disable and Enable Notification of Library Open and Close events
	/** * For Internal Use Only *
	*/
	virtual void DisableLibraryLevelNotification() = 0;
	/** * For Internal Use Only *
	*/
	virtual void EnableLibraryLevelNotification() = 0;
	
	// Disable and Enable Notification of Asset Addition, Change, and Deletion events
	/** * For Internal Use Only *
	*/
	virtual void DisableAssetLevelNotification() = 0;

	/** * For Internal Use Only *
	*/
	virtual void EnableAssetLevelNotification() = 0;
	
	// Get, Set, and Test the status of the "Has Changed" flag
	/** * For Internal Use Only *
	*/
	virtual void ClearHasChangedStatus() = 0;

	/** * For Internal Use Only *
	*/
	virtual void SetHasChangedStatus() = 0;

	/** * For Internal Use Only *
	*/
	virtual bool16 HasChanged() = 0;

	// Tell whether the library is old and needs to be converted to snippet data store
	/** * For Internal Use Only *
	*/
	virtual bool16 NeedsSnippetConversion( const IDFile &libraryFile ) = 0;

	// Converts the input library file to snippet data storage format
	/** * For Internal Use Only *
	*/
	virtual bool16 ConvertToSnippets( const IDFile &oldLibraryFile,  IDFile &tmpLibraryFile, IDFile &newLibraryFile, bool16 bUseOldName = kFalse ) = 0;
	
};


#endif