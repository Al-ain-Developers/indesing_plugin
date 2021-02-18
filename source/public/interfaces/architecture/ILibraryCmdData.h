//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryCmdData.h $
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
//  This interface is used to pass library reference data with various library command
//  bosses.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryCmdData__
#define __ILibraryCmdData__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "LibraryAssetID.h"


class ILibrary;

/** Used to pass library reference data with various library command bosses.
*/
class ILibraryCmdData : public IPMUnknown
{
public:
	
	/** Sets the file specification.
		@param libraryFile IN the specification for the library file
	*/
	virtual void SetLibraryFile(const IDFile &libraryFile) = 0;

	/** Gets the file specification.
		@return the IDFile file specification
	*/
	virtual IDFile GetLibraryFile() = 0;
	
	/** Sets the source library for the command.
		@param library IN the ILibrary interface for the source library
	*/
	virtual void SetSourceLibrary(ILibrary *library) = 0;

	/** Gets the source library for the command.
		@return the ILibrary interface for the source library
	*/
	virtual ILibrary * GetSourceLibrary() = 0;
	
	/** Sets the destination library for the command.
		@param library IN the ILibrary interface for the destination library
	*/
	virtual void SetDestLibrary(ILibrary *library) = 0;

	/** Gets the destination library for the command.
		@return the ILibrary interface for the destination library
	*/
	virtual ILibrary * GetDestLibrary() = 0;
	
	/** Set the asset list for the command.
		@param assetList list of AssetID's for the assets
	*/
	virtual void SetAssetList(const AssetIDList& assetList) = 0;

	/** Get the asset list for the command.
		@return the list of AssetID's for the command
	*/
	virtual AssetIDList&  GetAssetList() = 0;
	
	/** Set whether to use the original filename if old-asset-format conversion occurs.
		FOR INTERNAL USE ONLY 
		@param bUseOldName kTrue to use the original name (kFalse is the default)
	*/
	virtual void SetUseOldName(const bool16 bUseOldName) = 0;

	/** Get whether to use the original filename if old-asset-format conversion occurs.
		FOR INTERNAL USE ONLY 
		@return whether to use the original name (kFalse is the default)
	*/
	virtual bool16 GetUseOldName() = 0;
};


#endif // __ILibraryCmdData__
