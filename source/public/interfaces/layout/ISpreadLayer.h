//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISpreadLayer.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __ISPREADLAYER__
#define __ISPREADLAYER__

#include "IPMUnknown.h"
#include "LayerID.h"

#include "IDocumentLayer.h"	// for TextWrapLayerOptionsEnum
class GraphicsData;
class PMString;

/** Interface that represents a spread layer.
  
	InDesign and its derivatives supports document-wide layers.  This means each layer exists on all spreads and the z-order and attributes
	of the layers are the same on every spread.
 
	The ISpreadLayer interface is aggregated into a Spread Layer boss (kSpreadLayerBoss).  The is a spread layer boss for each individual
	document layer (kDocumentLayerBoss) on each spread; for instance, a document with 2 spreads and 3 layers has 6 spread layer boss objects.
 
	The spread layer boss (kSpreadLayerBoss) serves two purposes.  First as a page item in the display hierarchy, its IHierarchy interface
	holds the UIDs of all the items on the layer.  Second, the ISpreadLayer interface maintains a relationship back to
	the corresponding document layer boss.
 
	The ISpreadLayer interface primarily just provides "getter" methods that forward the request for information
	to the corresponding IDocumentLayer interface (i.e. GetName, GetColorUID, IsLocked, etc.).

	@see kSpreadLayerBoss
	@ingroup layout_layer

*/
class ISpreadLayer : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREADLAYER };

	/** The document layer should only be set once, when the spread
		layer is created.  It's expected to never change. Really for private
		use by the kNewLayerCmdBoss.
	  
		NOTE: Read class description for background info.
		@param docLayer The document layer this spread layer is associated with.
	*/
	virtual void SetDocLayer(IDocumentLayer * docLayer) = 0;

	/** Returns a pointer to the associated document layer in the document
		@return "Query" prefix means the caller must Release!
	*/
	virtual IDocumentLayer * QueryDocLayer() const = 0;

	/** Returns the UID of the associated layer in the document. 
		@return UID of associated document layer.
	*/
	virtual UID GetDocLayerUID() const = 0;
		
	/** Return the name of the document-wide layer.
		@param pName fills in the name of the document layer. Must be non-nil.
	*/
	virtual void GetName(PMString * pName) const= 0;
		
	/** Return the layer color (used for as selection hilite color
		for items on this layer).
		@return UID of a color to use for handle drawing. See IUIColorUtils.
	*/
	virtual UID GetColorUID() const = 0;

	/** Set that a layer is a guide-only layer.
		This method should only be called by code that
		is creating new layers, not on an existing layer (e.g. only by kNewLayerCmdBoss)
		@param isGuideLayer kFalse for non-guide spread layers, kTrue for spread guide layers.
	*/
	virtual void SetIsGuideLayer(bool16 isGuideLayer) = 0;	
		
	/** Return whether the layer is a guide-only layer, which will be
		suppressed from display in the Layer palette.
		@return kTrue if a guide spread layer (guides can be on this layer) or
				kFalse if not a guide layer (where regular page items live)
	*/
	virtual bool16 GetIsGuideLayer() const = 0;	

	/** Return whether the layer is locked or not. This is indicated by a lock
		symbol to the left of the layer name in the Layers palette. Function actually
		forwards question to the associated document layer. A spread layer is locked
		when its document layer is locked.
		@return kTrue if a layer is locked (won't be hittested), kFalse if not locked.
	*/
	virtual bool16 IsLocked() const = 0;	
		
	/** Return whether the layer is visible or not. This is indicated by an eyeball
		symbol to the left of the layer name in the Layers palette. Function actually
		forwards question to the associated document layer. A spread layer is visible
		when its document layer is visible.
		@return kTrue if a layer is visible, kFalse if hidden (won't be hittested or be drawn).
	*/
	virtual bool16 IsVisible() const = 0;
		
	/** Return whether the layer is printable or not. Function actually
		forwards question to the associated document layer. A spread layer is printable
		when its document layer is printable.
		@return kTrue if a layer is printable, kFalse if not.
	*/
	virtual bool16 IsPrintable() const = 0;
		
	/** Invalidates all the child items on this spread. Should be used carefully, generally the
		right way to do this inval is with IShape->Inval on kLayerShapeImpl.
		@param gd GraphicsData to provide a context for drawing
		@param reasonForInval Generally the ClassID of the command that called this method (theChange).
		@param flags Flags from IShape.
	*/
	virtual void Inval( GraphicsData *gd, ClassID reasonForInval = 0, int32 flags = 0 ) = 0 ;

	/**	Get whether or not text wrap items on this layer will be ignored when the layer is
		invisible. Corresponds to the Suppress Text Wrap When Layer is Hidden checkbox from Layer Options dialog.
		@return kTrue if items will be ignored, kFalse if they are included.
	 */
	virtual bool16 GetIgnoreTextWrapWhenNotVisible(void) const = 0;
};

#endif
