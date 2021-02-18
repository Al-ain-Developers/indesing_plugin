//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryDragDropUtils.h $
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
//  This interface is used to load the Drag&Drop Controller with asset data from
//  a given library.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryDragDropUtils__
#define __ILibraryDragDropUtils__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"
#include "LibraryAssetID.h"
#include "Utils.h"

class IDragDropController;
class ILibrary;

/** Used to load the drag and drop controller with asset data from a given library.
*/
class ILibraryDragDropUtils : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ILIBRARYDRAGDROPUTILS};

	/** Load the drag and drop controller with data from an asset.
		@param controller IN the controller
		@param library IN the library containing the asset whose data to load
		@param assetList IN list of AssetIDs to load from the library
		@return kTrue if successful, kFalse otherwise
	*/
	virtual bool16 ProvideDragContent(IDragDropController* controller,
				ILibrary* library, const AssetIDList &assetList) = 0;
};

#endif  // __ILibraryDragDropUtils__
