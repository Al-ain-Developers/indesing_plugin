//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAssetProxy.h $
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAssetProxy__
#define __ILibraryAssetProxy__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "GlobalTime.h"

// ----- ID.h files -----

#include "ShuksanID.h"
#include "BravoForwardDecl.h"

class ILibraryAssetCollection;
class ILibraryAsset;
class LibraryAssetID;

/** Library Panel's cache of information about a library asset.
*/
class ILibraryAssetProxy
{
public:

	/** What type an asset is.  Determined by a heuristic algorithm, and ca
		be reassigned by the user.  Do not change the order of the items
		in this enum, or logic that handles the dropdown menu will break.
	*/
	typedef enum {
		/** Asset is an image
		*/
		kImageType,
		/** Asset is an EPS
		*/
		kEPSType,
		/** Asset is a PDF
		*/
		kPDFType,
		/** Asset is a non-placed graphic pageitem (line, box, oval...)
		*/
		kGeometryType,
		/** Asset is an entire page of items
		*/
		kPageType,
		/** Asset is a textframe
		*/
		kTextType,
		/** Asset is an item from the structure panel
		*/
		kStructureType,
		/** Asset is a placed InDesign file
		*/
		kInDesignFileType
	} UserType;
	
	/** Updates the state of the proxy to reflect any changes made to the actual asset.
	*/
	virtual void Update() = 0;
		
	/** Get the ID number of this asset.
		@return the LibraryAssetID for the asset
	*/
	virtual LibraryAssetID GetID() const = 0;
		
	/** Get the asset's name.
		@return the name given the asset
	*/
	virtual PMString GetName() const = 0;
		
	/** Get the creation time (and date) of the asset.
		@return the timestamp for the asset's creation
	*/
	virtual GlobalTime GetCreationTime() const = 0;
		
	/** Get the asset's User Type.
		NOTE: User Type is just for user classification.  It may or may not be accurate.
		@return the UserType given the asset
	*/
	virtual UserType GetUserType() const = 0;

	/** Get a pointer to the asset's thumbnail image.
		@return pointer to AGMImageRecord for the thumbnail
	*/
	virtual AGMImageRecord* GetThumbnailImage() = 0;
	
	/** Query the actual asset this proxy points to.
		@return ILibraryAsset pointer for the asset.  Caller must Release.
	*/
	virtual ILibraryAsset* QueryActualAsset() const = 0;
	
	/** Free any memory associated with cached values.
	*/
	virtual void PurgeMemory() const = 0;
		
};


#endif
