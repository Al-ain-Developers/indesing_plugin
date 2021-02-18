//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayerList.h $
//  
//  Owner: Zak WIlliamson
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
#ifndef __ILAYERLIST__
#define __ILAYERLIST__

#include "IPMUnknown.h"
#include "LayerID.h"


class IDocumentLayer;
class PMString;

/**
	An interface off the document (kDocBoss), manages the list of document-wide layers (kDocumentLayerBoss).
	@ingroup layout_layer
	@see kDocBoss
	@see kDocumentLayerBoss
 */
class ILayerList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYERLIST };

	enum {
		kAtTheEnd = -1
	};
		

	/**	Return the number of layers in this document.
		@param none
		@return int32 The number of layers in this document.
	 */
	virtual int32 GetCount() const = 0;

	/**	Return the UID of the document layer with the specified name.
		@param name [IN] The name of the layer you are finding.
		@return UID The UID of the layer found, kInvalidUID if not found.
	 */
	virtual UID FindByName(const PMString& name) const = 0;
		
	/**	Return the n'th layer in this document. Caller is responsible for calling Release().
		@param n [IN] index of layer to return.
		@return IDocumentLayer* The returned document layer, nil if index out of range.
	 */
	virtual IDocumentLayer * QueryLayer(int32 n) const = 0;

	/**	Return the n'th layer in this document by UIDRef.
		@param n [IN] index of layer to return.
		@return UIDRef The returned document layer, invalid if index out of range.
	 */
	virtual UIDRef GetLayerUIDRef(int32 n) const = 0;

	/**	Return the index of the specified layer in this document.
		@param docLayer [IN] The document layer you are requesting the index for.
		@return int32 index (0-based) of the layer, -1 if not found.
	 */
	virtual int32 GetLayerIndex(const IDocumentLayer * docLayer) const = 0;

	/**	 return the index of the specified layer in this document
		@param layerUID [IN] The UID of the layer you are want the index for.
		@return int32 The index of the layer (0-based), or -1 if not found.
	 */
	virtual int32 GetLayerIndex(UID layerUID) const = 0;

	/**	Add a new layer to the document at the (optionally) specified location. Generally this
		will only be used by the kNewLayerCmdBoss.
		@param docLayer [IN] The layer to add to the document layer list. The list holds the reference.
		@param kAtTheEnd [IN] Position of the layer. 
	 */
	virtual void Add(IDocumentLayer * docLayer, int32 pos = kAtTheEnd) = 0;

	/**	Remove the specified layer from the document. Generally only used by the kDeleteLayerCmdBoss.
		@param docLayer [IN] The layer to remove from the list. 
	 */
	virtual void Remove(IDocumentLayer * docLayer) = 0;

	/**	Move the layer at location 'from' to a new location 'to' (i.e. 
		change the stacking order of the layers. Generally only used by the kMoveLayerCmdBoss.
		@param from [IN] The index of the layer to move.
		@param to [IN] The index to insert the layer in the list. May be kAtTheEnd.
	 */
	virtual void Move(int32 from, int32 to) = 0;
	
	/**	Returns the next candidate for an active layer. It looks for the
		first visible, unlocked layer in front of the given one, then in back,
		then the next visible, but perhaps locked, then the next layer period.
		Returns nil, if there are no other layers.
		@param docLayer [IN] The layer for where to start looking for next candidate.
		@return IDocumentLayer The "future" active layer, may be nil.
	 */
	virtual UIDRef GetNextActiveLayer(const IDocumentLayer * docLayer) const = 0;

	/**	Returns the next candidate for an active layer.  It looks for the
		first visible, unlocked layer in front of the given one, then in back,
		then the next visible, but perhaps locked, then the next layer period.
		Returns nil, if there are no other layers.  This version is useful
		if the old layer has already been removed and you have its index.

		@param layerIndex [IN] The layer index for where to start looking for next candidate.
		@return IDocumentLayer* The "future" active layer, may be nil.
	 */
	virtual UIDRef GetNextActiveLayer(int32 layerIndex) const = 0;

	/**	Generates a unique layer name, of the form "Layer 1", "Layer 2", ....
		If the duplicate flag is set, and the suggested name is used, a 'copy n' will be appended
		@param pName [IN] The base name of the layer.
		@param duplicate [IN] Return 'copy n' appended to the name if kTrue, otherwise don't.
	 */
	virtual void GenerateNewLayerName(PMString* pName, bool16 duplicate = kFalse) = 0;

	/**	Returns the least used layer color. Generally the next UI color in the list.
		@param none
		@return UID UID of the least used layer color.
	 */
	virtual UID GetLeastUsedLayerColor() = 0;
};

#endif
