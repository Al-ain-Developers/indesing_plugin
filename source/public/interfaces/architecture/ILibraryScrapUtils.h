//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryScrapUtils.h $
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
//  This interface is responsible for assisting the Library Panel's Scrap Controller.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryScrapUtils__
#define __ILibraryScrapUtils__

#include "IPMUnknown.h"
#include "LibraryAssetID.h"
#include "LibraryProviderID.h"
#include "PMFlavorTypes.h"

class ILibrary;
class ILibraryAsset;
class UIDList;
class IDataBase;
class IDataExchangeHandler;
class XMLReference;

/** This interface is responsible for assisting the Library Panel's Scrap Controller.  It also
	contains methods for CS2-based asset handling (which doesn't directly use the scrap).
*/
class ILibraryScrapUtils : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ILIBRARYSCRAPUTILS};

	/** DEPRECATED -- Convert the Library Scrap into a Library Asset.
		@param originalPageItems IN the original pageitems to convert
		@param libraryScrapPageItems IN items as stored in the library scrap
		@param library IN interface pointer to the library
		@param fromCompletePage IN if kTrue, we are adding all items from the page
		@return the LibraryAssetID of created asset
	*/
	virtual LibraryAssetID	ConvertToLibraryAsset(const UIDList *originalPageItems,
							const UIDList *libraryScrapPageItems, ILibrary* library,
							bool16 fromCompletePage = false) = 0;

	/** Convert pageitems into a Library Asset using Snippets 
		@param library IN interface pointer to the library
		@param itemList IN pointer to list of pageitems to convert, or nil if using handler
		@param handler IN data exchange handler for data, if itemList is nil
		@param gotFlavor IN flavor if using handler
		@return the LibraryAssetID of created asset
	*/
	virtual LibraryAssetID	ConvertToAssetUsingSnippets(ILibrary *library, UIDList *itemList,
							IDataExchangeHandler *handler, ExternalPMFlavor gotFlavor) = 0;

	/** Update an asset using pageitems 
		@param library IN interface pointer to the library
		@param asset IN the asset to update
		@param itemList IN pointer to list of pageitems to use, or nil if using handler
		@param handler IN data exchange handler for data, if itemList is nil
		@param gotFlavor IN flavor if using handler
		@return error code
	*/
	virtual ErrorCode		UpdateItemAsset(ILibrary *library, ILibraryAsset* asset, UIDList *itemList,
							IDataExchangeHandler *handler, ExternalPMFlavor gotFlavor) = 0;

	/** Update a structure asset using XMLReference 
		@param library IN interface pointer to the library
		@param asset IN the asset to update
		@param fromThis IN the structure item, or nil if using handler
		@param handler IN data exchange handler for data, if not using fromThis
		@param gotFlavor IN flavor if using handler
		@return error code
	*/
	virtual ErrorCode		UpdateStructureAsset(ILibrary *library, ILibraryAsset* asset, XMLReference& fromThis,
							IDataExchangeHandler *handler, ExternalPMFlavor gotFlavor) = 0;

	/** Convert structure into a Library Asset using Snippets 
		@param library IN interface pointer to the library
		@param addThis IN the structure item, or nil if using handler
		@param handler IN data exchange handler for data, if not using fromThis
		@param gotFlavor IN flavor if using handler
		@return the LibraryAssetID of created asset
	*/
	virtual LibraryAssetID	ConvertStructureToAssetUsingSnippets(ILibrary *library, XMLReference& addThis,
							IDataExchangeHandler *handler, ExternalPMFlavor gotFlavor) = 0;

    /** Check to see if a given database is the library scrap database.
        @param db IN IDatabase to test.
        @return kTrue if db is the library scrap database
    */
	virtual bool16			IsScrapDB(IDataBase* db) = 0;
};

#endif
