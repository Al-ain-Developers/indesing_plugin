//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayerUtils.h $
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
//  
//  Purpose:
//  Utilities for use for dealing with layers.
//  
//========================================================================================

#pragma once
#ifndef __ILayerUtils__
#define __ILayerUtils__

#include "Utils.h"
#include "LayerID.h"

class UIDList;
class ICommand;
class IControlView;
class IDocument;
class IDocumentLayer;
class IHierarchy;
class ILayerList;
class ILayoutControlData;
class IScriptRequestData;
class ISpread;
class ISpreadLayer;

typedef int32 LayerFlags;	// Used for return value for IsLayerUsed
	
/*	Simple #defines (looking for only one attribute) involving CountLayers
	Usage is Utils<ILayerUtils>()->CountUILayers(layerList);
 */
#define	CountLockedLayers(layerList)		CountLayers(layerList, ILayerUtils::kFlagOn)
#define	CountVisibleLayers(layerList)		CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)
#define	CountLockedGuideLayers(layerList)	CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)
#define	CountVisibleGuideLayers(layerList)	CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)
#define	CountUILayers(layerList)			CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)
#define	CountExpendableLayers(layerList)	CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)
#define	CountColoredLayers(layerList, uid)	CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, uid)

/*	More complex #defines, looking for a combination of attributes:
	Usage is Utils<ILayerUtils>()->CountUILayers(layerList);
 */
#define CountExpendableUILayers(layerList)	CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn, ILayerUtils::kFlagOn)
#define CountLockedUILayers(layerList)	CountLayers(layerList, ILayerUtils::kFlagOn, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)
#define CountVisibleUILayers(layerList)	CountLayers(layerList, ILayerUtils::kDontCare, ILayerUtils::kFlagOn, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn)

/** Utilities for use for dealing with layers on the model side.
	@ingroup layout_layer
	@ingroup layout_util
 */
class ILayerUtils : public IPMUnknown 
{
	public:
		enum	{ kDefaultIID = IID_ILAYERUTILS };

		/**	Flags to pass to CountLayers.
		 */
		enum CountLayersFlags { kFlagOff = ((int32)0), kFlagOn = ((int32)1), kDontCare = ((int32)0xFFFFFFFF) };
		
	
		/**	Enum flags for IsLayerUsed return value.
		 */
		enum 
		{
			kLayerNotUsed			= 0x0000,
			kLayerContainsArtwork	= 0x0001,
			kLayerContainsGuides	= 0x0002,
			kLayerHasPlaceGunOwnedItem = 0x0004,
			kLayerContainsBoth		= kLayerContainsArtwork | kLayerContainsGuides
		};

		/**	Does this layer have content on it? (Looks on all spreads and master spreads). Can be expensive, use with caution.
			@param docLayer IN the document layer to check for content. 
			@return what kind of content is on this layer? See enum above.
		 */
		virtual LayerFlags IsLayerUsed(IDocumentLayer* docLayer) = 0;

		/**	Count the document layers having the specified attributes (one or more attributes may be used).
			Most often this will be used via the #defines at top of file.
			@param layerList ILayerList* to examine. 
			@param isLocked kFlagOn if you want to count IDocumentLayer->IsLocked layers, kFlagOff if you want to count unlocked layers, kDontCare otherwise
			@param isVisible kFlagOn if you want to count IDocumentLayer->IsVisible layers, kFlagOff if you want to count hidden layers, kDontCare otherwise
			@param isGuideLocked kFlagOn if you want to count IDocumentLayer->IsGuideLocked layers, kFlagOff if you want to count unlocked guide layers, kDontCare otherwise
			@param isGuideVisible kFlagOn if you want to count IDocumentLayer->IsGuideVisible layers, kFlagOff if you want to count hidden guide layers, kDontCare otherwise
			@param isUILayer kFlagOn if you want to count IDocumentLayer->IsUILayer layers, kFlagOff if you want to count non-UI layers, kDontCare otherwise
			@param isExpendable kFlagOn if you want to count IDocumentLayer->IsExpendable layers, kFlagOff if you want to count non-expendable, kDontCare otherwise
			@param colorUID UID of layers with given IDocumentLayer->GetColorUID, kDontCare otherwise.
			@return the number of layers meeting the given parameter requirements.
		 */
		virtual	int32 CountLayers(const ILayerList	*layerList,
								  int32		isLocked = kDontCare,
								  int32		isVisible = kDontCare,
								  int32		isGuideLocked = kDontCare,
								  int32		isGuideVisible = kDontCare,
								  int32		isUILayer = kDontCare,
								  int32		isExpendable = kDontCare,
								  UID		colorUID = (UID)kDontCare) = 0;

		/**	Determine if any UI layers in this document are hidden.
			@param document the document to check. 
			@param numHidden OUT the number of hidden layers, may be nil. 
			@return returns kTrue if one or more UI layers are hidden, kFalse otherwise. 
		 */
		virtual bool16 AnyLayersHidden(IDocument* document, int32* numHidden = nil) = 0;

		/**	Determine if any UI layers in this document are locked.
			@param document the document to check. 
			@param numLocked OUT the number of locked layers, may be nil. 
			@return returns kTrue if one or more UI layers are locked, kFalse otherwise. 
		 */
		virtual bool16 AnyLayersLocked(IDocument* document, int32* numLocked = nil) = 0;

		/**	Determine if page items are on unlocked and visible layers (therefore are editable).
			Used to enable/disable clipboard or drag/drop operations.
			@param pageItems UIDList of page items to check. 
			@return return kTrue if all items in list are on unlocked, visible layers, kFalse otherwise.
		 */
		virtual bool16 AreLayersUnlockedAndVisible(const UIDList* pageItems) = 0;

		/**	Determine if active layer is unlocked and visible (and therefore editable). Useful to determine if
			active layer can be acted upon (e.g. by a tracker).
			@param layoutData ILayoutControlData for the layout view to check.  
			@return return kTrue active layer is unlocked and visible, kFalse otherwise. 
		 */
		virtual bool16 IsActiveLayerUnlockedAndVisible(const ILayoutControlData* layoutData) = 0;

		/**	Helper function to create a command to unlock and or show the active layer (by default) or any layer.
			@param controlView IN the control view for the layout view
			@param docLayer IN nil if you want to unlock/show the active layer, or a particular layer 
			@return Command to unlock and/or show the layer. Caller must release. 
		 */
		virtual ICommand* MakeUnlockShowLayerCmd(IControlView *controlView, IDocumentLayer* docLayer = nil) = 0;

		/**	Determine the UID of the spread layer containing the specified item by walking up the hierarchy.
			@param theItem an IHierarchy* interface for the item to check its layer.
			@return UID of spread layer containing the specified item.  
		 */
		virtual UID	GetLayerUID(const IHierarchy *theItem) = 0;

		/**	Get the active document layer for the specified document. Works even when a document window isn't open.
			@param document IN the document to return the active layer for. 
			@return the active document layer. 
		 */
		virtual IDocumentLayer* QueryDocumentActiveLayer(const IDocument* document) = 0;

		/**	Handle the optional p_DestinationLayer parameter for scripting events. Returns the current 
			active layer for the given spread if the parameter wasn't supplied for this request.
			@param data IN the IScriptRequestData associated with the script request
			@param spread IN the spread to return the layer for
			@param destinationLayerList OUT the destination layer(s)
			@return kSuccess or an error code 
		 */
		virtual ErrorCode GetDestinationLayers( IScriptRequestData* data, ISpread* spread, K2Vector< InterfacePtr<ISpreadLayer> >& destinationLayerList ) = 0;
};
	
#endif // __ILayerUtils__
