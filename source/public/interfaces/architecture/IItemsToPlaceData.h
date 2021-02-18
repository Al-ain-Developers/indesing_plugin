//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IItemsToPlaceData.h $ 
//   
//  Owner: vaggarwa 
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
//======================================================================================== 

#pragma once 
#ifndef __IItemsToPlaceData__ 
#define __IItemsToPlaceData__ 

// ----- Includes -----

// ----- ID.h files -----
#include "LayoutUIID.h"


//======================================================================================== 
// class IItemsToPlaceData 
//======================================================================================== 

class IItemsToPlaceData : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IITEMSTOPLACEDATA }; 

	/** Content to be placed may reside in these places */
	enum ePlaceFrom {
		/**  */
		kPlaceGun, 
		/**  */
		kPlaceHead, 
	};
	
	//Gets the first Item uid to be placed.
	virtual UID GetFirstItemUID(IDocument* document) const = 0;

	//Finds if there are still items to be placed
	virtual bool16 IsLoaded(IDocument* document) const = 0;

	//Returns number of items to be placed
	virtual int32 CountItemsToPlace(IDocument* document) const = 0;

	//Clears the queue of items to be placed
	virtual ErrorCode ClearFirstItem(IDocument* document) = 0;
	
	virtual ErrorCode ClearQueue(IDocument* document) = 0;

	//Aborts the place action
	virtual ErrorCode AbortFirstItem(IDocument* document) = 0;

	virtual ErrorCode AbortPlace(IDocument* document) = 0;

	//returns the place whether the items to be placed are to be taken from PlaceGun or PlaceHead
	virtual IItemsToPlaceData::ePlaceFrom GetPlaceSource() = 0;

};




#endif
