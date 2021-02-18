//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/utils/AssetLibUtils.h $
//  
//  Owner: Tim Wright
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
//  Comments: Miscellaneous useful functions that deal with Asset Libraries.
//  
//========================================================================================

#pragma once
#ifndef __AssetLibUtils_h__
#define __AssetLibUtils_h__

#include "LibraryAssetID.h"
#include "ISpread.h"

class ILibrary;
class ILibraryAsset;
class ILibraryAssetMetaData;
class ILibraryScrapController;
class IPageItemScrapData;
class UIDList;

#pragma export on

namespace AssetLibUtils
{

// -------------------------------------------------------------------------------------				
/* Usage:

	Use StAssetLib to open/close the library, given a IDFile, or a file path (PMString)
	
	This gives you the ILibrary you need for iteration.
	
	You can iterate by
	
	1) asset, using IterateAssets/AssetEnumerator.
		This gets each ILibraryAsset in the ILibrary.
	
	2) asset metadata, using IterateAssetMetaData/AssetMetaDataEnumerator.
		This returns ILibraryAssetMetaData off of each ILibraryAsset in the library.
	
	3) asset page items, using IterateAssetPageItems/AssetPageItemEnumerator.
		Converts each ILibraryAsset to a page item on the library scrap, or ILibraryScrapController
		Getting asset page items can be expensive, so  AssetPageItemEnumerator includes a method,
		WantPageItems, that asks when the page items are actually needed for each ILibraryAsset
	
	4) A combination of all 3 using IterateAssets
	
*/

// -------------------------------------------------------------------------------------				

class PUBLIC_DECL AssetEnumerator
{
public:
	virtual ~AssetEnumerator();
	virtual bool operator()(ILibraryAsset *) = 0;
};

// -------------------------------------------------------------------------------------				
class PUBLIC_DECL AssetPageItemEnumerator
{
public:
	virtual ~AssetPageItemEnumerator();
	virtual bool WantPageItems(ILibraryAsset *) = 0; //return whether you want to go ahead w/getting the page items (which is expensive)
	virtual bool operator()(const UIDList&, ILibraryAsset *, ILibraryScrapController*, IPageItemScrapData* ) = 0;
};

// -------------------------------------------------------------------------------------				

PUBLIC_DECL ILibrary* QueryStyleLibByName(const PMString& inAssetLibFileName);

// -------------------------------------------------------------------------------------				
//Iterate over assets in Lib:

// Iterate over every asset
PUBLIC_DECL void EnumerateAssets(ILibrary* inLib, AssetEnumerator* inAssetEnum);

// Iterate over each asset as a page item (UIDList)
PUBLIC_DECL void EnumerateAssetPageItems(ISpread* inSpread, ILibrary* inLib, AssetPageItemEnumerator* inPageItemEnumerator, bool16 bClear = kFalse);

// Iterate over asset ids in list, instead of all the assets...

PUBLIC_DECL void ProcessAssetPageItems(ISpread* inSpread, ILibrary* inLib, const AssetIDList& inIDList, AssetPageItemEnumerator* inPageItemEnumerator);

PUBLIC_DECL void ProcessAssets(ILibrary* inLib, const AssetIDList& inIDList, AssetEnumerator* inAssetEnum);

// -------------------------------------------------------------------------------------				
// Copy nth asset into inCopyToItem

PUBLIC_DECL void CopyAssetToItem( ILibrary* inLib, int32 inAssetIndex, const UIDRef& inCopyToItem );

// -------------------------------------------------------------------------------------				
// convert assets to page items, should do inLibraryScrapController->Clear() when done w/ returned items.

PUBLIC_DECL UIDList* GetAssetPageItems( ISpread* inSpread, ILibraryAsset* inAsset,
							ILibraryScrapController* inLibraryScrapController,
							IPageItemScrapData* inLibraryScrapData );

// -------------------------------------------------------------------------------------				

}

#pragma export off

#endif // __AssetLibUtils_h__

// End, AssetLibUtils.h.

