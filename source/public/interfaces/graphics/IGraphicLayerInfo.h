//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicLayerInfo.h $
//  
//  Owner: David Berggren
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
//  Stores info about layers read in from a placed graphic (i.e. PSD or AI file)
//  Assumes layer names are unique
//  
//========================================================================================

#pragma once
#ifndef __IGraphicLayerInfo__
#define __IGraphicLayerInfo__

#include "IPMUnknown.h"
#include "ImageID.h"
#include "PMString.h"

/** 
	An interface for holding the graphic layer information for
	placed graphics such as Photoshop (PSD) files. This assumes 
	that all layer names are unique.
*/
class IGraphicLayerInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICLAYERINFO };

	/** 
		This enum is a bitfield for the update link options.
	*/
	typedef enum 
	{
		/** Unknown option
		*/
		kUnknownLinkOption		= 0,

		/** if this option is set, the layer visibility is taken
			from the file being imported, no overrides are applied.
		*/
		kUseApplicationSettings,

		/** if this option is set, the layer visibility current
			overrides are applied to the file being imported.
		*/
		kKeepOverrides

	} UpdateLinkOption;

	/** 
		This enum is a bitfield for flags controlling the layer information.
	*/
	typedef enum 
	{
		/** the default attribute is no flags, or 0
		*/
		kNoFlags				= 0,

		/** requires validation
		*/
		kNeedsValidation		= (1L << 1),

		/** failed validation
		*/
		kValidationFailed		= (1L << 2),

		/** new layers added with source file's layer visibility
		*/
		kValidationNewLayersAdded = (1L << 3),

		/** for internal use only
		*/
		kInternalUseOnly		= (1L << 28)

	} GraphicLayerFlags;

	/** 
		This enum represents the visibility state of the layer. Used
		for both original visibility state and current visibility state.
	*/
	typedef enum 
	{
		/** the layer is not showing, or hidden
		*/
		kVisibilityHidden,
		/** the layer is visible, or showing
		*/
		kVisibilityShowing,
		/** the state of the layer is unknown
		*/
		kVisibilityUnknown

	} GraphicVisibilityState;

	/** 
		This enum is a bitfield for the attributes of the layer.
	*/
	typedef enum 
	{
		/** the default attribute is no attribute, or 0
		*/
		kNoAttributes			= 0,

		/** if this bit is on, the layer is a separator layer. It 
			might only be a placeholder, and may not be visible. Layers
			of this type will not show the eyeball icon in the list, and
			the visibility does not affect its children.
		*/
		kLayerSeparator			= (1L << 0),

		/** if this bit is on, the layer is an adjustment layer.
		*/
		kLayerAdjustment		= (1L << 1),

		/** if this bit is on, the layer has an effect.
		*/
		kLayerHasFX				= (1L << 2),

		/** if this bit is on, the layer visibility is locked.
		*/
		kLayerIsLocked			= (1L << 3),

		/** if this bit is on, the layer has a Usage descriptor 
			with ViewState. Use kLayerViewStateON to determine if on or off.
		*/
		kLayerHasViewState		= (1L << 4),

		/** if this bit is on, the layer has a Usage descriptor 
			with ViewState turned ON.
		*/
		kLayerViewStateON		= (1L << 5),

		/** if this bit is on, the layer has a Usage descriptor 
			with ExportState. Use kLayerExportStateON to determine if on or off.
		*/
		kLayerHasExportState	= (1L << 6),

		/** if this bit is on, the layer has a Usage descriptor 
			with ExportState turned ON.
		*/
		kLayerExportStateON		= (1L << 7),

		/** if this bit is on, the layer has a Usage descriptor 
			with PrintState. Use kLayerPrintStateON to determine if on or off.
		*/
		kLayerHasPrintState		= (1L << 8),

		/** if this bit is on, the layer has a Usage descriptor 
			with PrintState turned ON.
		*/
		kLayerPrintStateON		= (1L << 9),

		/** if this bit is on, the layer is a section divider layer. It 
			is a layer set placeholder in PSD files. Turning the visibility
			off for a layer section divider will affect any children.
		*/
		kLayerSectionDivider	= (1L << 10),

		/** if this bit is on, the layer is a text layer. Currently we are 
			only detecting this in PSD files. 
		*/
		kLayerIsTextLayer		= (1L << 11)

	} LayerAttributes;

	// ***********************
	// Set methods for interface
	// ***********************

	/**	Set if the interface has been initialized.
		@param bIsInitialized IN kTrue if the layer information has been initialized.
	*/
	virtual void SetIsInitialized (bool16 bIsInitialized) = 0;
	/**	Set the update link option. See the UpdateLinkOption enum for options.
		@param newOption IN see the enum UpdateLinkOption for values.
	*/
	virtual void SetUpdateLinkOption (const UpdateLinkOption newOption) = 0;
	/**	Set new graphic layer flags. It is the callers responsibility to OR in their
		new flag with the existing flags, retrieved through GetGraphicLayerFlags().
		@param newFlags IN see the enum GraphicLayerFlags for values.
	*/
	virtual void SetGraphicLayerFlags (const GraphicLayerFlags newFlags) = 0;

	// ***********************
	// Get methods for interface
	// ***********************

	/**	Get if the interface has been initialized.
		@return bool16 - kTrue if the layer information has been initialized.
	*/
	virtual bool16 GetIsInitialized () const = 0;
	/**	Get the current update link option.
		@return UpdateLinkOption - see the enum UpdateLinkOption for values.
	*/
	virtual UpdateLinkOption GetUpdateLinkOption () const = 0;
	/**	Get the current graphic layer flags.
		@return GraphicLayerFlags - see the enum GraphicLayerFlags for values.
	*/
	virtual GraphicLayerFlags GetGraphicLayerFlags () const = 0;

	// ***********************
	// Add/Remove/Copy/Utilities methods for layers
	// ***********************

	/**	Insert a layer into the interface. The layer will be inserted into
		the front of the list. It is assumed that all layers are uniquely IDed. 
		@param layerName IN a PMString containing a layer name.
		@param layerUniqueID IN a unique ID that can represent the layer
		@param origVisState IN the original visibility state at the time
		the layer is added. The current visibility state is set to the original 
		visibility state when the layer is added.
		@param parentID IN the unique ID of the parent layer, if this layer 
		is nested. Default of -1.
		@param layerAttributes IN a enum bitfield of the layer attributes.
		Default of kNoAttributes, or 0.
	*/
	virtual void InsertLayer (	const	PMString&				layerName, 
										int32					layerUniqueID,
								const	GraphicVisibilityState	origVisState,
										int32					parentID = -1,
								const	LayerAttributes			layerAttributes = kNoAttributes
							) = 0;

	/**	Append a layer to the interface. The layer will be appended onto
		the end of the list. It is assumed that all layers are uniquely IDed. 
		@param layerName IN a PMString containing a layer name.
		@param layerUniqueID IN a unique ID that can represent the layer
		@param origVisState IN the original visibility state at the time
		the layer is added. The current visibility state is set to the original 
		visibility state when the layer is added.
		@param parentID IN the unique ID of the parent layer, if this layer 
		is nested. Default of -1.
		@param layerAttributes IN a enum bitfield of the layer attributes.
		Default of kNoAttributes, or 0.
	*/
	virtual void AppendLayer (	const	PMString&				layerName, 
										int32					layerUniqueID,
								const	GraphicVisibilityState	origVisState,
										int32					parentID = -1,
								const	LayerAttributes			layerAttributes = kNoAttributes
							) = 0;

	/**	Remove a layer from the interface.
		@param layerIndex IN the index of the layer to remove.
	*/
	virtual void RemoveNthLayer (int32 layerIndex) = 0;
	/**	Remove a layer from the interface.
		@param layerUniqueID IN the ID of the layer to remove. Layer IDs are
		assumed to be unique.
	*/
	virtual void RemoveLayer (int32 layerUniqueID) = 0;

	/**	Clear all layers out of the interface.
	*/
	virtual void Clear() = 0;
	/**	Copy all information from the given interface into this interface. This
		will perform a Clear() on the existing information prior to the copy.
		@param srcLayerInfo IN the source IGraphicLayerInfo to copy from.
	*/
	virtual void Copy(const IGraphicLayerInfo* srcLayerInfo) = 0;
	/**	Compare all information from the given interface to this interface.
		@param otherLayerInfo IN the other IGraphicLayerInfo to compare to.
		@return bool16 - kTrue if they are equal, kFalse otherwise. 
	*/
	virtual bool16 CompareAll(const IGraphicLayerInfo* otherLayerInfo) const = 0;
	/**	Uses the unique ids from the given interface to compare the current
		visibility in this interface to the current visibility of the other
		interface. 
		@param otherLayerInfo IN the other IGraphicLayerInfo to compare to.
		@return bool16 - kTrue if the current visibilities are equal, kFalse otherwise. 
	*/
	virtual bool16 CompareVisibility(const IGraphicLayerInfo* otherLayerInfo) const = 0;
	/**	Validate the graphic layers with another interface. Will compare the layer IDs 
		and layer names based on the IDs, and if they all match it will return kTrue.
		NOTE: it compares based on the srcLayerInfo number of layers - this interface
		may have more layers, but it will only compare based on srcLayerInfo.
		@param srcLayerInfo IN the source IGraphicLayerInfo to use.
		@return bool16 - kTrue if the IDs and names exist, kFalse otherwise. 
	*/
	virtual bool16 ValidateGraphicLayers(const IGraphicLayerInfo* srcLayerInfo) = 0;
	/**	Compare the original visibility to the current visibility in this interface.
		@return bool16 - kTrue if they are not equal, kFalse the visibility has not changed. 
	*/
	virtual bool16 VisibilityChanged() const = 0;
	/**	Resets the current visibility state to the original visibility state for all layers.
	*/
	virtual void ResetLayerVisiblity() = 0;
	/** Preallocate the layer list to this size. If it is known before hand how
		many layers will be added to the interface, use this to preallocate the
		number of entries.
		@param preallocSize IN the number of entries that will be added to the list.
	*/
	virtual void Preallocate(int32 preallocSize) = 0;

	// ***********************
	// Set methods for each layer
	// ***********************

	/**	Set the layer name of a given layer index.
		@param layerIndex IN the index of the layer to rename.
		@param newName IN the new name to be given to the layer
	*/
	virtual void SetNthLayerName (int32 layerIndex, const PMString& newName) = 0;
	/**	Set the layer name of a layer with the given unique ID.
		@param layerUniqueID IN the unique ID of the layer to change. 
		@param newName IN the new name of the layer. 
	*/
	virtual void SetLayerName (int32 layerUniqueID, const PMString& newName) = 0;

	/**	Set the layer unique ID of a given layer index.
		@param layerIndex IN the index of the layer to change.
		@param newID IN the new ID to be given to the layer. Does not change
		the index of the layer, only the internal unique ID stored with the layer.
	*/
	virtual void SetNthLayerUniqueID (int32 layerIndex, int32 newID) = 0;

	/**	Set the layer original visibility state of a given layer index.
		@param layerIndex IN the index of the layer to change.
		@param newState IN the new original visibility state to be given to the layer.
	*/
	virtual void SetNthLayerOriginalVisibility (int32 layerIndex, const GraphicVisibilityState newState) = 0;
	/**	Set the layer original visibility state of a given layer name.
		@param layerUniqueID IN the unique ID of the layer to change. 
		@param newState IN the new original visibility state to be given to the layer.
	*/
	virtual void SetLayerOriginalVisibility (int32 layerUniqueID, const GraphicVisibilityState newState) = 0;

	/**	Set the layer current visibility state of a given layer index.
		@param layerIndex IN the index of the layer to change.
		@param newState IN the new current visibility state to be given to the layer.
	*/
	virtual void SetNthLayerCurrentVisibility (int32 layerIndex, const GraphicVisibilityState newState) = 0;
	/**	Set the layer current visibility state of a given layer name.
		@param layerUniqueID IN the unique ID of the layer to change. 
		@param newState IN the new current visibility state to be given to the layer.
	*/
	virtual void SetLayerCurrentVisibility (int32 layerUniqueID, const GraphicVisibilityState newState) = 0;

	/**	Set the parent index of a given layer index.
		@param layerIndex IN the index of the layer to change.
		@param newParentID IN the new parent's unique ID to be given to the layer.
	*/
	virtual void SetNthLayerParentID (int32 layerIndex, int32 newParentID) = 0;
	/**	Set the parent index of a given layer name.
		@param layerUniqueID IN the unique ID of the layer to change. 
		@param newParentID IN the new parent's unique ID to be given to the layer.
	*/
	virtual void SetLayerParentID (int32 layerUniqueID, int32 newParentID) = 0;

	/**	Set the layer attributes of a given layer index. The attributes are overwritten, so
		use GetLayerAttributes(), and turn on/off bits as desired prior to calling this method.
		@param layerIndex IN the index of the layer to change.
		@param newAttributes IN the new attributes to be given to the layer.
	*/
	virtual void SetNthLayerAttributes (int32 layerIndex, const LayerAttributes newAttributes) = 0;
	/**	Set the layer attributes of a given layer name. The attributes are overwritten, so
		use GetLayerAttributes(), and turn on/off bits as desired prior to calling this method.
		@param layerUniqueID IN the unique ID of the layer to change. 
		@param newAttributes IN the new attributes to be given to the layer.
	*/
	virtual void SetLayerAttributes (int32 layerUniqueID, const LayerAttributes newAttributes) = 0;

	// ***********************
	// Get methods
	// ***********************

	/**	Get the number of layers currently stored in the interface. For use when iterating
		through the layers, setting or getting specific information.
		@return int32 of the number of layers. 
	*/
	virtual int32 GetNumberLayers () const = 0;

	/**	Get the name of the layer of the given layer index.
		@param layerIndex IN the index of the layer name to retrieve.
		@return PMString of the layer name. 
	*/
	virtual PMString				GetNthLayerName (int32 layerIndex) const = 0;
	/**	Get the name of the layer with the given unique ID.
		@param layerUniqueID IN the unique ID of the layer to retrieve. 
		@return PMString of the layer's name. 
	*/
	virtual PMString				GetLayerName (int32 layerUniqueID) const = 0;

	/**	Get the unique ID of the layer of the given layer index.
		@param layerIndex IN the index of the layer ID to retrieve.
		@return int32 of the layer's internal unique ID (see AddLayer() above). 
	*/
	virtual int32					GetNthLayerUniqueID (int32 layerIndex) const = 0;
	/**	Get the index of the layer with the given unique ID.
		@param layerUniqueID IN the unique ID of the layer to retrieve. 
		@return int32 of the layer's index. 
	*/
	virtual int32					GetLayerIndex (int32 layerUniqueID) const = 0;
	
	/**	Get the original visibility state of the layer of the given layer index.
		@param layerIndex IN the index of the layer state to retrieve.
		@return GraphicVisibilityState of the layer's original visibility state. See
		the GraphicVisibilityState enum definition above.
	*/
	virtual GraphicVisibilityState	GetNthLayerOriginalVisibility (int32 layerIndex) const = 0;
	/**	Get the original visibility state of the layer with the given name.
		@param layerUniqueID IN the unique ID of the layer to retrieve. 
		@return GraphicVisibilityState of the layer's original visibility state. See
		the GraphicVisibilityState enum definition above.
	*/
	virtual GraphicVisibilityState	GetLayerOriginalVisibility (int32 layerUniqueID) const = 0;

	/**	Get the current visibility state of the layer of the given layer index.
		@param layerIndex IN the index of the layer state to retrieve.
		@return GraphicVisibilityState of the layer's current visibility state. See
		the GraphicVisibilityState enum definition above.
	*/
	virtual GraphicVisibilityState	GetNthLayerCurrentVisibility (int32 layerIndex) const = 0;
	/**	Get the current visibility state of the layer with the given name.
		@param layerUniqueID IN the unique ID of the layer to retrieve. 
		@return GraphicVisibilityState of the layer's current visibility state. See
		the GraphicVisibilityState enum definition above.
	*/
	virtual GraphicVisibilityState	GetLayerCurrentVisibility (int32 layerUniqueID) const = 0;

	/**	Get the parent index of the layer of the given layer index.
		@param layerIndex IN the index of the layer parent index to retrieve.
		@return int32 of the layer's parent unique ID.  Defaults to -1.
	*/
	virtual int32					GetNthLayerParentID (int32 layerIndex) const = 0;
	/**	Get the parent index of the layer with the given name.
		@param layerUniqueID IN the unique ID of the layer to retrieve. 
		@return int32 of the layer's parent unique ID. Defaults to -1.
	*/
	virtual int32					GetLayerParentID (int32 layerUniqueID) const = 0;

	/**	Get the attributes bitfield of the layer of the given layer index.
		@param layerIndex IN the index of the layer attributes to retrieve.
		@return LayerAttributes of the layer's attributes (see LayerAttributes definition above). 
	*/
	virtual LayerAttributes			GetNthLayerAttributes (int32 layerIndex) const = 0;
	/**	Get the attributes of the layer with the given name.
		@param layerUniqueID IN the unique ID of the layer to retrieve. 
		@return LayerAttributes of the layer's attributes (see LayerAttributes definition above).
	*/
	virtual LayerAttributes			GetLayerAttributes (int32 layerUniqueID) const = 0;

	/**	Validate the graphic layers with another interface. Will compare the layer IDs
		and layer names based on the IDs, and if they all match it will return kTrue.
		NOTE: it compares based on the srcLayerInfo number of layers - this interface
		may have more layers, but it will only compare based on srcLayerInfo. Used for
		PDF and placed InDesign document graphics items.
		@param srcLayerInfo IN the source IGraphicLayerInfo to use.
		@return bool16 - kTrue if the IDs and names exist, kFalse otherwise.
	*/
	virtual bool16					ValidateGraphicLayersByName(const IGraphicLayerInfo* srcLayerInfo) = 0;

	/**	Set the current visibility of the layers from the source layers. This method matches layers based
		on layer name and not index.
		@param srcLayerInfo IN the layer info to copy visibility state from
		@param newLayerState IN the visibility state to use for layers not present in source (new layers).
							 Pass in kVisibilityUnknown if you want to retain the new layers original visibility.
		@parama hasNewLayers OUT kTrue, if the target layers contain additional new layers
		@return None
	*/
	virtual void					SetLayerVisibilityFromSource(const IGraphicLayerInfo* srcLayerInfo, GraphicVisibilityState newLayersState, bool16& hasNewLayers) = 0;
};

#endif
