//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibrarySuite.h $
//  
//  Owner: Paul Sorrick
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __ILibrarySuite__
#define __ILibrarySuite__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "LibraryAssetID.h"

// Forward declaration
class ILibrary;
class IDocument;
class IControlView;

class ILibrarySuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIBRARYSUITE };

// ----- Abilities
	
	/**	Can the selection be added to the library? Return kTrue or kFalse.
		@param library 
		@param view - Control View to use 
		@return bool16 
	 */
	virtual bool16 CanAddToLibrary (ILibrary* library, IControlView* view) const = 0;

	/**	Can the selection be used to update the item in the library? Return kTrue or kFalse.
		@param library 
		@param view - Control View to use 
		@return bool16 
	 */
	virtual bool16 CanUpdateLibraryItem (ILibrary* library, const AssetIDList &assetList, IControlView* view) const = 0;

	/**	Can the contents of current page be added to the library? Return kTrue or kFalse.
		@param library 
		@param assetIDList single-element list containing the ID of the asset to update
		@param view - Control View to use 
		@return bool16 
	 */
	virtual bool16 CanAddPageToLibrary (ILibrary* library, IControlView* view) const = 0;

	/**	Can the library assets be placed? Return kTrue or kFalse.
		@param assetList [IN] the assets to place.
		@param library 
		@param view - Control View to use 
		@return bool16 
	 */
	virtual bool16 CanPlaceLibraryItems (const AssetIDList &assetList, ILibrary* library, IControlView* view) const = 0;

	// ----- Manipulators

	/**	Add the selection to the library.
		@param library 
		@param newAssetIDList [OUT] receives the assets created
		@param view - Control View to use 
		@return ErrorCode 
	 */
	virtual ErrorCode DoAddToLibrary (ILibrary* library, AssetIDList* newAssetIDList, IControlView* view) = 0;

	/**	Update an asset in the library, using the selection.
		@param library 
		@param assetIDList [IN] single-element list containing the ID of the asset to update
		@param view - Control View to use 
		@return ErrorCode 
	 */
	virtual ErrorCode DoUpdateLibraryItem (ILibrary* library, AssetIDList* assetIDList, IControlView* view) = 0;

	/**	Add the contents of current page to the library.
		@param library 
		@param newAssetIDList [OUT] receives the assets created
		@param view - Control View to use 
		@param bSeparateAssets - if kTrue, add each item as a separate asset; else add all as a single asset
		@return ErrorCode 
	 */
	virtual ErrorCode DoAddPageToLibrary (ILibrary* library, AssetIDList* newAssetIDList, IControlView* view, bool16 bSeparateAssets = kFalse) = 0;

	/**	Place items from library into a document.
		@param &assetList 
		@param *library 
		@param out_placedItemList [OUT] receives UIDs of items after placed in document. 
		@param view - Control View to use 
		@return ErrorCode 
	 */
	virtual ErrorCode DoPlaceLibraryItems(const AssetIDList &assetList, ILibrary *library, UIDList& out_placedItemList, IControlView* view) = 0;

};

#endif // __ILibrarySuite__
