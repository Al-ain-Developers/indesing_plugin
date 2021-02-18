//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAsset.h $
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
//  This interface is the main interface to the LibraryAsset Boss.  This interface
//  will get basic information about the asset and also controls write access.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAsset__
#define __ILibraryAsset__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "LibraryAssetID.h"

class ILibraryAssetCollection;
class IPMStream;

/** The main interface to the LibraryAsset boss.  Gets basic information about the asset and also
	controls write access.
*/
class ILibraryAsset : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIBRARYASSET };
	
	/** Get the ID number of this asset.
		@return the LibraryAssetID for the asset
	*/
	virtual LibraryAssetID	GetID()		const = 0;

	/** Get the asset UID.
		@return the UID for the asset
	*/
	virtual	UID				GetUID()	const = 0;
	
	/** Gets the asset collection this asset belongs to.
		@return a pointer to the asset's owning ILibraryAssetCollection
	*/
	virtual ILibraryAssetCollection* GetCollection() = 0;
	
	/** Test for exclusive write access to the asset.
		NOTE: Write access must be acquired before doing any operation that changes the asset.
		@return whether write access to the asset has been acquired
	*/
	virtual bool16 HasWriteAccess() const = 0;
	
	/** Get exclusive write access to the asset.
		NOTE: Write access must be acquired before doing any operation that changes the asset.
		@return whether write access to the asset has been acquired
	*/
	virtual bool16 AcquireWriteAccess() = 0;
	
	/** Release exclusive write access to the asset.
	*/
	virtual void ReleaseWriteAccess() = 0;
	
	
	//-------------- For Internal Use Only -------------------------
		
	// Sets the asset ID to the input argument. (Called once at asset creation.)
	/** * For Internal Use Only *
	*/
	virtual void SetID(const LibraryAssetID& id) = 0;
	
	// Sets the asset collection this asset belongs to. (Called once at asset creation.)
	/** * For Internal Use Only *
	*/
	virtual void SetCollection(ILibraryAssetCollection* assetCollection) = 0;
		
};


#endif
