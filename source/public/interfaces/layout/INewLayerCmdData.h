//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INewLayerCmdData.h $
//  
//  Owner: robin briggs
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
//  Data interface for the NewLayerCmd. 
//  
//========================================================================================

#pragma once
#ifndef __INewLayerCmdData__
#define __INewLayerCmdData__

#include "IPMUnknown.h"
#include "LayerID.h"

class PMString;

/**  Data interface for new layer command to create a new document layer.
	@ingroup layout_layer
	@see kNewLayerCmdBoss
	@see IDocumentLayer
	@see ILayerList
*/
class INewLayerCmdData : public IPMUnknown
{
public:
	/**
	   Set method to control all the data values for the new document layer to create.
	   Default values may be used for all but the first parameter to just create a 
	   new visible, unlocked document layer (Layer 2, Layer 3, etc).
	   @param layerList The layer list for the document to create the new layer in.
	   @param name A pointer to the layer name, nil to autogenerate a unique name.
	   @param isVisible The setting for the new layer's visibility. Default is kTrue for visible, kFalse for hidden.
	   @param isLocked The setting for the new layer's locked state. Default is kTrue for unlocked, kFalse for locked.
	   @param isGuideVisible The setting for the new layer's ruler guide visibility. Default is kTrue for visible guides on this layer, kFalse for hidden.
	   @param isGuideLocked The setting for the new layer's ruler guide locked state. Default is kTrue for unlocked guides, kFalse for locked.
	   @param layerColor A UID from the documents IID_IUICOLORLIST. Use kInvalidUID to generate the next available color.
	   @param isUILayer The setting for whether the new layer should appear in the UID (Layers palette). Defaults to kTrue.
	   @param isExpendable The setting for whether the new layer should be expendable/deletable. Defaults to kTrue.
	 */
	virtual void Set(const UIDRef& layerList, const PMString *name = nil, 
					bool16 isVisible = kTrue, bool16 isLocked = kFalse, 
					bool16 isGuideVisible = kTrue, bool16 isGuideLocked = kFalse, 
					UID layerColor = kInvalidUID, 
					bool16 isUILayer = kTrue, bool16 isExpendable = kTrue) = 0;

	/**
	   Returns the target of the command, the layer list to make the new document layer in.
	   @return a UIDRef to the layer list the command will modify.
	 */
	virtual const UIDRef& GetLayerList() = 0;

	/**
	   Gets the data value for the name of the new layer.
	   @return the new layer's name.
	 */
	virtual const PMString& GetName() = 0;

	/**
	   Gets the data value for visible flag for the new layer.
	   Hidden layers are skipped for hittesting. Items cannot be selected on a hidden layer.
	   @return kTrue if the layer is visible, kFalse if hidden.
	 */
	virtual bool16 IsVisible() = 0;

	/**
	   Gets the data value for lock flag for the new layer.
	   Locked layers are skipped for hittesting. Items cannot be selected on a locked layer.
	   @return kTrue if the layer is locked, kFalse if unlocked.
	 */
	virtual bool16 IsLocked() = 0;

	/**
	   Gets the data value for ruler guide visible flag for the new layer.
	   Guides can be invisible just on a particular layer,
	   independently of the overall document hide guides/show guides setting.
	   @return kTrue if guides are visible on the new layer, kFalse if hidden.
	 */
	virtual bool16 IsGuideVisible() = 0;

	/**
	   Gets the data value for ruler guide lock flag for the new layer.
	   Guides can be locked just on a particular layer,
	   independently of the overall document lock guides/unlock guides setting.
	   @return kTrue if guides are locked on the new layer, kFalse if unlocked.
	 */
	virtual bool16 IsGuideLocked() = 0;

	/**
	   Gets the data value for color to be used for the handles of selected items on this layer. Default is kInvalidUID, which means to just use the next available color in the list.
	   @return the UID of the kTrue if the new layer should appear in the Layers palette, kFalse if it should not. Non-UI layers are not visible to scripting either.
	   @see IUIColorUtils.h
	 */
	virtual UID GetColor() = 0;

	/**
	   Gets the data value for UI data member.
	   @return kTrue if the new layer should appear in the Layers palette, kFalse if it should not. Non-UI layers are not visible to scripting either.
	 */
	virtual bool16 IsUILayer() = 0;

	/**
	   Gets the data value for expendable/deletable data member.
	   @return kTrue if the new layer should be deletable, kFalse if it cannot be deleted.
	 */
	virtual bool16 IsLayerExpendable() = 0;	// can the layer be deleted?

	/**
	   Sets the data value for printable/nonprintable data member.
	   @param bPrintable The setting for the new layer's printable setting. If not specified, new layers default to printable.
	 */
	virtual void SetPrintable(bool16 bPrintable) = 0;

	/**
	   Gets the data value for printable/nonprintable data member.
	   @return kTrue if new layer should be printable, kFalse for nonprintable.
	 */
	virtual bool16 IsPrintable() = 0;

	/** For new layer, if kTrue, then ignore all text wrap items on this layer when the layer is invisible.
		@param bIgnoreWhenNotVisible. If not specified, new layers default to kFalse for this value.
	 */
	virtual void SetIgnoreTextWrapWhenNotVisible(bool16 bIgnoreWhenNotVisible) = 0;

	/** Description: Get whether or not text wrap items on this layer will be ignored when the layer is invisible.
		@param void
		@return bool16
	 */
	virtual bool16 GetIgnoreTextWrapWhenNotVisible() = 0;
};


#endif // __INewLayerCmdData__
