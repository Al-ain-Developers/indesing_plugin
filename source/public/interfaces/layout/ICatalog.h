//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICatalog.h $
//  
//  Owner: Hardeep
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
#ifndef __ICatalog__
#define __ICatalog__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "ILibraryAsset.h"
#include "K2Vector.tpp"
#include "IProperty.h"
#include "IPropertyTable.h"
class LibraryAssetID;

/** Provides access to assets in an InDesign library.
*/
class ICatalog : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICATALOG };
		enum LibVersion { CURRENT = 0, ANNABETA = 1, ANNARELEASE = 2 };

		/** Initializes the catalog.  Call this after creating a new catalog.
		*/
		virtual void Init() = 0;

		/** Create a new asset in the catalog file.
			@return a UID value to be passed to CreateLibraryAssetID for construction of a LibraryAssetID
		*/
		virtual UID NewLibAsset() = 0;

		/** Acquire access to an asset.
			@param id IN LibraryAssetID of the asset desired
			@return interface pointer to the asset's ILibraryAsset interface
		*/
		virtual ILibraryAsset* Acquire(const LibraryAssetID& id) = 0;

		/** Remove an asset from the catalog.
			@param id IN the UID of the asset to remove
			@return kFalse for asset not found; kTrue otherwise
		*/
		virtual bool16 Remove(const UID id) = 0;

		/** Get the UID of an asset.
			@param pos IN the index of the asset
			@return UID value for found asset
		*/
		virtual UID GetNthAssetUID(int32 pos) = 0;

		/** Get the number of assets.
			@return the number of assets in the catalog
		*/
		virtual int32 GetAssetCount() = 0;

		/** Get whether the catalog is writable.
			@return whether the catalog is writable.
		*/
		virtual bool16 IsWritable() = 0;

		/** Set the read-only status of the catalog.
			@param flag IN kTrue for set to read-only, kFalse for writable
		*/
		virtual void SetReadOnly(bool16 flag) = 0;

		/** Close the catalog.
		*/
		virtual void Close() = 0;

		/** Save the catalog.
			@return result code from save operation
		*/
		virtual IDataBase::DBResultCode Save() = 0;

		/** Set a catalog preference key/value pair.
			@param propKey IN the key
			@param propValue IN the value
		*/
		virtual void SetPreferences(const PMString& propKey,const PMString& propValue) = 0;

		/** Get a catalog preference key/value pair.
			@param propKey IN the key
			@param propValue IN the value
		*/
		virtual void GetPreferences(const PMString& propKey,PMString& propValue) const = 0;

		/** Return the results from the most recent property search.
			@return K2Vector of UIDs for the assets found.
		*/
		virtual K2Vector<UID>& GetSearchResults() = 0;

		/** Set whether to use a subset property search.
			@param useSubsetSearch IN kTrue for subset search; kFalse otherwise
		*/
		virtual void	SetUseSubsetSearch(bool16 useSubsetSearch=kTrue) = 0;

		/** Get whether a subset property search is being used.
			@return kTrue for a subset search.
		*/
		virtual bool16	GetUseSubsetSearch() = 0;

		/** Initialize a property search.
			@param booleanOp IN the boolean operation to use in the search -- either ILibraryComplexFilterData::Conjunction_And or
			ILibraryComplexFilterData::Conjunction_Or
			@param fromList IN property list for search if other than all items; use nil for all items
		*/
		virtual void	InitializeSearchResults(int16 booleanOp,PropUIDList* fromList=nil) = 0;

		/** Perform a property search.
			@param property IN property a pointer to the property
			@param whichComparator IN the comparator index for the property
			@param value IN interface pointer to the value to compare
			@param booleanOp IN the boolean operation to use in the search -- either ILibraryComplexFilterData::Conjunction_And or
			ILibraryComplexFilterData::Conjunction_Or
			@param fromList IN property list for search; may be nil if searching all property items
			@return always returns zero
		*/
		virtual int16 Search(IProperty* property,int32 whichComparator,IPMUnknown* value,int16 booleanOp,PropUIDList* fromList=nil)
		{
			return 0;
		}

		/** For internal use only.  Used for identifying older-version libraries.
		*/
		virtual LibVersion	GetLibraryVersion() = 0;

		/** For internal use only.  Used for identifying older-version libraries.
		*/
		virtual void		SetLibraryVersion(LibVersion libV) = 0;

		/** Tell whether an asset with the given LibraryAssetID exists.
			@param id IN the LibraryAssetID of the asset
			@return kTrue for valid, kFalse otherwise
		*/
		virtual bool16 IsValid(const LibraryAssetID& id) const = 0;
};
#endif