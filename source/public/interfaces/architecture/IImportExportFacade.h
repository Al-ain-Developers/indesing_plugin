//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportExportFacade.h $
//  
//  Owner: Jonathan W. Brown
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
//  Description:
//  A high level API for dealing with import and export.
//  
//========================================================================================

#pragma once
#ifndef __IImportExportFacade__
#define __IImportExportFacade__

// ----- Includes -----
#include "IPMUnknown.h"

#include "IPlaceGun.h"
#include "OpenPlaceID.h"
#include "UIDList.h"
#include "URI.h"
#include "Utils.h"

class ICmdCollection ;
class IDataBase ;
class IImportResourceCmdData ;
class ISpread;

/**
 Interface used to manage import and export.
 @see IPlaceBehavior
 @see IPlaceGun
*/
namespace Facade
{
	class IImportExportFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IIMPORTEXPORTFACADE };

		/**@name Place Gun command methods */
		//@{

		enum PlaceGunContent {
			kFirstItem,
			kAllItems
		} ;

		/** Load the place gun with one or more items.
			@param itemList	[IN]	The items to load. The items will be loaded into the place gun associated with the items' database.
			@param location	[IN]	Where to load the items.
			@return kSuccess if the place gun is loaded, else an error code.
		*/
		virtual ErrorCode LoadPlaceGun( const UIDList& itemList, IPlaceGun::PlaceGunLocation location ) const = 0 ;

		/** Load the place gun with items from a pipeline command. Executes the pipeline command.
			@param itemList	[IN]	The pipeline command that will supply the items to load. The items will be loaded into the place gun associated with the items' database.
			@param location	[IN]	Where to load the items.
			@return kSuccess if the place gun is loaded, else an error code.
		*/
		virtual ErrorCode LoadPlaceGun( ICmdCollection* cmdCollection, IPlaceGun::PlaceGunLocation location ) const = 0 ;

		/** Clear one or all items from the place gun. The cleared items are not deleted.
			@param placeGun	[IN]	The place gun to clear.
			@param what		[IN]	Whether to clear just the first or all items in the place gun.
			@return kSuccess if the place gun is cleared, else an error code.
		*/
		virtual ErrorCode ClearPlaceGun( IPlaceGun* placeGun, PlaceGunContent what ) const = 0 ;

		/** Abort the place gun by clearing one or all items and deleting them.
			@param placeGun	[IN]	The place gun to abort.
			@param what		[IN]	Whether to abort just the first or all items in the place gun.
			@return kSuccess if the place gun is aborted, else an error code.
		*/
		virtual ErrorCode AbortPlaceGun( IPlaceGun* placeGun, PlaceGunContent what ) const = 0 ;

		/** Load the place gun with one or more items.
			@param db			[IN]	database to be imported into (required)
			@param uri			[IN]	identifying the resource to import.
			@param flags		[IN]	specifies how much UI to show during import
			@param retainFormat	[IN]	retain text format, applies to text import
			@param convertQuotes[IN]	convert quotation mark types, applies to text import
			@param applyCJKGrid	[IN]	apply CJK grid if present, applies to text import
			@param uidPreview	[IN]	UID of preview object
			@param location		[IN]	Where to load the items.
			@return kSuccess if the place gun is loaded, else an error code.
		*/
		virtual ErrorCode ImportAndLoadPlaceGun( IDataBase* db, const URI& uri, UIFlags flags, 
													bool16 retainFormat, bool16 convertQuotes, bool16 applyCJKGrid, 
													UID uidPreview, IPlaceGun::PlaceGunLocation location ) const = 0 ;
		/** Load the place gun with one or more items.
			@param cmdData		[IN]	Existing command data to reuse (required)
			@param location		[IN]	Where to load the items.
			@return kSuccess if the place gun is loaded, else an error code.
		*/
		virtual ErrorCode ImportAndLoadPlaceGun( IImportResourceCmdData* cmdData, IPlaceGun::PlaceGunLocation location ) const = 0 ;
		/** Load the place gun with one or more items.
			@param db			[IN]	database to be imported into (required)
			@param uri			[IN]	identifying the resource to import.
			@param flags		[IN]	specifies how much UI to show during import
			@param retainFormat	[IN]	retain text format, applies to text import
			@param convertQuotes[IN]	convert quotation mark types, applies to text import
			@param applyCJKGrid	[IN]	apply CJK grid if present, applies to text import
			@param useClippingFrame	[OUT]	Whether the command indicated to use the clipping frame
			@param skipPlace		[OUT]	Whether the command indicated to skip place
			@return kSuccess if the place gun is loaded, else an error code.
		*/
		virtual ErrorCode ImportAndLoadPlaceGun( IDataBase* db, const URI& uri, UIFlags flags, 
													bool16 retainFormat, bool16 convertQuotes, bool16 applyCJKGrid, 
													bool16& useClippingFrame, bool16& skipPlace ) const = 0 ;
		/** Load the place gun with one or more items.
			@param db			[IN]	database to be imported into (required)
			@param linkResourceUID [IN]	identifying the resource to import.
			@param flags		[IN]	specifies how much UI to show during import
			@param retainFormat	[IN]	retain text format, applies to text import
			@param convertQuotes[IN]	convert quotation mark types, applies to text import
			@param applyCJKGrid	[IN]	apply CJK grid if present, applies to text import
			@param useClippingFrame	[OUT]	Whether the command indicated to use the clipping frame
			@param skipPlace		[OUT]	Whether the command indicated to skip place
			@return kSuccess if the place gun is loaded, else an error code.
		*/
		virtual ErrorCode ImportAndLoadPlaceGun( IDataBase* db, UID linkResourceUID, UIFlags flags, 
													bool16 retainFormat, bool16 convertQuotes, bool16 applyCJKGrid, 
													bool16& useClippingFrame, bool16& skipPlace ) const = 0 ;

		/** Rotate the items in theplace gun.
			@param placeGun	[IN]	The place gun to rotate.
			@param forward	[IN]	Rotate the list forward (i.e. move the front item to end) or backward (move backmost item to front)
			@return kSuccess if the place gun is rotated, else an error code.
		*/
		virtual ErrorCode RotatePlaceGun( IPlaceGun* placeGun, bool16 forward ) const = 0 ;
		//@}

		/** Replace one page item with another. @see IPlaceBehavior::ProcessReplace
			@param db				[IN] database where the replace will occur.
			@param oldPageItem		[IN] UID of the page item to be replaced.
			@param newPageItem		[IN] UID of the new page item.
			@param useClippingFrame	[IN] retain the clipping frame.
			@param replaceList		[OUT] the placed item(s)
			@return kSuccess if replace is successful, else an error code.
		*/
		virtual ErrorCode ReplacePageItem( IDataBase* db, UID oldPageItem, UID newPageItem, bool16 useClippingFrame, UIDList& replaceList ) const = 0 ;

		/** Place an external file on the specified point on pasteboard
		 	@param spread           [IN] spread of the document where file has to be placed
		 	@param filePath			[IN] file path of the file to be placed
		 	@param pbPoint			[IN] position to be placed with respect to the pasteboard coordinates
		 */
		virtual ErrorCode PlaceExternalFile(ISpread* spread, const IDFile& filePath, const PBPMPoint& pbPoint) const = 0;

		/** Place an external file on the specified point on pasteboard
			@param spread           [IN] spread of the document where file has to be placed
			@param filePath			[IN] file path of the file to be placed
			@param pbPoint			[IN] position to be placed with respect to the pasteboard coordinates
			@param uiFlags			[IN] specifies how much UI to show during import
		*/
		virtual ErrorCode PlaceExternalFileWithUIFlags(ISpread* spread, const IDFile& filePath, const PBPMPoint& pbPoint, const UIFlags uiFlags ) const = 0;
	};
} // namespace Facade

#endif // __IImportExportFacade__
