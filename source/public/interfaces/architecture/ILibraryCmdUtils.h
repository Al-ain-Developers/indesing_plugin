//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryCmdUtils.h $
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
//  This interface is used to create and process the various commands of the Library.
//  
//========================================================================================

#pragma once
#ifndef __LibraryCmdUtils__
#define __LibraryCmdUtils__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "LibraryAssetID.h"
#include "PMFlavorTypes.h"
#include "Utils.h"

class UIDList;
class ICommand;
class ILibrary;
class IDocument;
class IDataExchangeHandler;
class XMLReference;
class UIDRef;

/** Used to create and process the various commands of the Library.
*/
class ILibraryCmdUtils : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ILIBRARYCMDUTILS};

	/** Get an instance of the Library Cmd Utility Boss
		@return an Interface pointer for ILibraryCmdUtils
	*/
	static ILibraryCmdUtils* QueryLibraryCmdUtils() { return Utils<ILibraryCmdUtils>().QueryUtilInterface() ; }

	// Create the various Library Commands

	/**	Create a command to add a library asset from pageitems.
		@param selection IN the items to add
		@param library IN the library to contain the items
		@param fromCompletePage IN if kTrue, we are adding all items from the page
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryAddItemCmd(UIDList *selection, ILibrary *library, bool16 fromCompletePage = false ) = 0;

	/**	Create a command to update a library asset from pageitems.
		@param selection IN the items to add
		@param library IN the library containing the asset being updated
		@param assetList IN AssetIDList containing one and only one assetID for asset to update
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryUpdateItemCmd(UIDList *selection, ILibrary *library, const AssetIDList &assetList ) = 0;

	/** Create a command to copy assets from one library to another.
		@param sourceAssetList IN assetID's of assets being copied
		@param sourceLibrary IN ILibrary pointer to source library
		@param destLibrary IN ILibrary pointer to destination library
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryCopyItemsCmd(const AssetIDList &sourceAssetList,
						ILibrary *sourceLibrary, ILibrary *destLibrary ) = 0;

	/** Create a command to delete library assets.
		@param assetList IN assetIDs of assets to delete
		@param library IN ILibrary pointer to library
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryDeleteItemsCmd(const AssetIDList &assetList, ILibrary *library ) = 0;

	/** Create a command to create a new library.
		@param libraryFile IN file specification for the library file
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryNewLibCmd( const IDFile &libraryFile ) = 0;

	/** Create a command to open a library.
		@param libraryFile IN file specification for the library file
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryOpenLibCmd( const IDFile &libraryFile ) = 0;

	/** Create a command to close a library.
		@param library IN file specification for the library file
		@return interface pointer to ICommand
	*/
	virtual ICommand* CreateLibraryCloseLibCmd( ILibrary *library ) = 0;	
	
	/**	Create and immediately process a command to add a library asset from pageitems.
		@param selection IN a pointer to the items to add, if IDataExchangeHandler is nil; 
				this interface takes ownership of the pointer
		@param library IN the library to contain the items
		@param fromCompletePage IN if kTrue, we are adding all items from the page
		@param newAssetList OUT if supplied, contains the created assetIDs
		@param handler IN data exchange handler containing data, if selection UIDList pointer is nil
		@param gotFlavor IN flavor used by data exchange handler, if used
		@return error code
	*/
	virtual ErrorCode ProcessLibraryAddItemCmd(UIDList *selection, ILibrary *library, 
				bool16 fromCompletePage = false, AssetIDList* newAssetList = nil,
				IDataExchangeHandler *handler = nil, ExternalPMFlavor gotFlavor = kNoFlavor) = 0;

	/**	Create and immediately process a command to add a library asset from structure.
		@param addThis IN a pointer to the XMLReference to add, if IDataExchangeHandler is nil
		@param library IN the library to contain the items
		@param newAssetList OUT if supplied, contains the created assetIDs
		@param handler IN data exchange handler containing data, if XMLReference is nil
		@param gotFlavor IN flavor used by data exchange handler, if used
		@return error code
	*/
	virtual ErrorCode ProcessLibraryAddStructureCmd(XMLReference& addThis, ILibrary *library, 
				AssetIDList* newAssetList = nil, IDataExchangeHandler *handler = nil, ExternalPMFlavor gotFlavor = kNoFlavor) = 0;

	/**	Create and immediately process a command to update a library asset from pageitems.
		@param selection IN a pointer to the one and only one to add, if IDataExchangeHandler is nil
		@param library IN the library to contain the items
		@param newAssetList OUT if supplied, contains the created assetIDs
		@param handler IN data exchange handler containing data, if selection UIDList pointer is nil
		@param gotFlavor IN flavor used by data exchange handler, if used
		@return error code
	*/
	virtual ErrorCode ProcessLibraryUpdateItemCmd(UIDList *selection, ILibrary *library, 
				AssetIDList* newAssetList = nil,
				IDataExchangeHandler *handler = nil, ExternalPMFlavor gotFlavor = kNoFlavor) = 0;

	/**	Create and immediately process a command to update a library asset from structure.
		@param addThis IN a pointer to the XMLReference to add, if IDataExchangeHandler is nil
		@param library IN the library to contain the items
		@param assetList OUT if supplied, contains the created assetIDs
		@param handler IN data exchange handler containing data, if XMLReference is nil
		@param gotFlavor IN flavor used by data exchange handler, if used
		@return error code
	*/
	virtual ErrorCode ProcessLibraryUpdateStructureCmd(XMLReference& addThis, ILibrary *library, 
				AssetIDList* assetList = nil, IDataExchangeHandler *handler = nil, ExternalPMFlavor gotFlavor = kNoFlavor) = 0;

	/** Create and immediately process a command to copy an asset from one library to another.
		@param sourceAssetList IN assetID's of assets being copied
		@param sourceLibrary IN ILibrary pointer to source library
		@param destLibrary IN ILibrary pointer to destination library
		@return error code
	*/
	virtual ErrorCode ProcessLibraryCopyItemsCmd(const AssetIDList &sourceAssetList,
						ILibrary *sourceLibrary, ILibrary *destLibrary ) = 0;

	/** Create and immediately process a command to delete library assets.
		@param assetList IN assetIDs of assets to delete
		@param library IN ILibrary pointer to library
		@return error code
	*/
	virtual ErrorCode ProcessLibraryDeleteItemsCmd(const AssetIDList &assetList, ILibrary *library ) = 0;

	// See ILibrarySuite for these functions:
#if 0
	virtual ErrorCode ProcessLibraryPlaceItemsCmd(const AssetIDList &assetList, 
						ILibrary *library,
						UIDList& out_placedItemList,
						IDocument* inDocument = nil) = 0; 

	virtual ErrorCode ProcessLibraryPlaceItemsCmd(const AssetIDList &assetList, 
						ILibrary *library,
						IDocument* inDocument = nil) = 0;
#endif

	/** Create and immediately process a command to create a new library.
		@param libraryFile IN file specification for the library file
		@return error code
	*/
	virtual ErrorCode ProcessLibraryNewLibCmd( const IDFile &libraryFile ) = 0;

	/** Create and immediately process a command to open a library.
		@param libraryFile IN file specification for the library file
		@param openedLib OUT a UIDRef for the library opened
		@return error code
	*/
	virtual ErrorCode ProcessLibraryOpenLibCmd( const IDFile &libraryFile, UIDRef *openedLib = nil ) = 0;
	
	/** Create and schedule a command close a library.
		@param library IN file specification for the library file
		@return error code
	*/
	virtual ErrorCode ScheduleLibraryCloseLibCmd( ILibrary *library ) = 0;

	/** Open a library with the Library Panel UI brought up.
		@param sysFile IN the file specification of the library to open
		@param openedLib OUT a UIDRef for the library opened
		@return error code
	*/
	virtual ErrorCode OpenLibraryWithUI(const IDFile& sysFile, UIDRef *openedLib = nil) = 0;
};


#endif