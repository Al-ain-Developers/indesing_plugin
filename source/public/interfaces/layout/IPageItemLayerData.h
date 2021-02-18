//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemLayerData.h $
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
//========================================================================================

#pragma once
#ifndef __IPageItemLayerData__
#define __IPageItemLayerData__

#include "IPMUnknown.h"
#include "PageItemScrapID.h"
#include "K2Vector.h"
#include "K2Vector.h"

//========================================================================================
// Forward declarations
//========================================================================================

class UIDList;

//========================================================================================
// CLASS IPageItemLayerData
//========================================================================================

/**
	@ingroup layout_layer
	@ingroup arch_scrap
	@see kPageItemScrapHandlerBoss 
*/
class IPageItemLayerData : public IPMUnknown
{
// ----- Constructors/desctructors
public:

// ----- Manipulators
public:
	virtual void		Clear() = 0;

	virtual void		SetPageItemList(const UIDList& pageItemNameList) = 0;
		// Set the page item UIDs for the items in the scrap
	virtual void		SetLayerNameList(K2Vector<PMString>& layerNameList) = 0;
		// Set the names of the layers for the items in the scrap
	virtual void		SetLayerIndexList(K2Vector<int32>& layerIndexList) = 0;
		// Set the indices into the layer name list of the items in the scrap
	virtual void		SetIsGuideLayer(bool16 isGuideLayer) = 0;
		// Are the layer names for guide layers? False by default.
	
// ----- Accessors
public:
	virtual bool16		IsEmpty() const = 0;

	virtual UIDList* CreatePageItemList() const = 0;
		// Get the page item UIDs for the items in the scrap
	virtual K2Vector<PMString>* CreateLayerNameList() const = 0;
		// Get the names of the layers for the items in the scrap
	virtual K2Vector<int32>* CreateLayerIndexList() const = 0;
		// Get the indices into the layer name list of the items in the scrap
	virtual void GetLayerForItem(UID itemUID, PMString* layerName) const = 0;
		// Return the layer for the indicated item.
	virtual bool16 GetIsGuideLayer() const = 0;
		// Are the layer names for guide layers? False by default.
		
	virtual void GetLayerNameAtIndex(int32 index, PMString* layerName) const = 0;
		// Return the layer name at the index into the layer name list
	virtual int32 GetIndexOfLayerName(PMString& layerName) const = 0;
		// Return the index of the layer name in the layer name list
	virtual int32 GetNumLayers() const = 0;
		// Return the number of layer names in the layer name list

	virtual int32 GetLayerIndexAtIndex(int32 index) const = 0;
		// Return the layer index at the index into the layer index list
	virtual int32 GetNumIndices() const = 0;
		// Return the number of layer indices in the layer index list
};

#endif
