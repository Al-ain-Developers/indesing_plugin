//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAssetIterator.h $
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
//  This interface is to a standard C class which is used to iterate over the assets
//  in a library.
//  
//  THIS IS NOT A STANDARD BOSS INTERFACE
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAssetIterator__
#define __ILibraryAssetIterator__




class ILibraryAsset;
class ILibraryComplexFilterData;

/** This is a standard C class used to iterate over the assets in a library.  Not a standard
	boss interface.
	@see ILibraryAsset
	@see ILibraryComplexFilterData
*/
class ILibraryAssetIterator INHERITFROM
{
public:
	
	virtual ~ILibraryAssetIterator() {};
	
	/** Initialize internal state & return the first asset of the collection.
		@return an ILibraryAsset interface pointer; must be released by calling
		ILibraryAssetCollection::ReleaseAsset when the client is done with it.
	*/
	virtual ILibraryAsset* First() = 0;
	
	/** Move to the next asset of the collection. 
		@return an ILibraryAsset interface pointer; must be released by calling
		ILibraryAssetCollection::ReleaseAsset when the client is done with it.
	*/
	virtual ILibraryAsset* Next() = 0;
	
	/** Find an asset by its LibraryAssetID
		@param assetID IN the LibraryAssetID for the asset to find
		@return an ILibraryAsset interface pointer; must be released by calling
		ILibraryAssetCollection::ReleaseAsset when the client is done with it.
	*/
	virtual ILibraryAsset* Find(LibraryAssetID assetID) = 0;

	/** Tell whether an asset is found using a filter.
		@param assetID IN the asset to search for
		@param inFilter IN the filter to use
		@return kTrue if the asset is found, kFalse otherwise
	*/
	virtual bool16 PassesThrough(LibraryAssetID assetID, ILibraryComplexFilterData* inFilter) = 0;
};


#endif