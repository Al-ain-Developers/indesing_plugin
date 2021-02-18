//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPSDLayerCompInfo.h $
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
//  Stores info about layers comp information from a placed PSD (native Photoshop) graphic
//  
//========================================================================================

#pragma once
#ifndef __IPSDLayerCompInfo__
#define __IPSDLayerCompInfo__

#include "IPMUnknown.h"
#include "KeyValuePair.h"
#include "K2Vector.h"
#include "PSFilterID.h"
#include "PMString.h"

/** 
	A key/value pair containing a layerID and its visibility on/off.
*/
typedef KeyValuePair<long, bool16> LayerVisibilityPair;
/** 
	A vector of LayerVisibilityPairs.
*/
typedef K2Vector<LayerVisibilityPair> LayerVisibilityList;

/** 
	An interface for holding a native Photoshop file's (PSD) layer comp information 
	which has been read out and parsed from the 0x0429 image resource. 
*/
class IPSDLayerCompInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPSDLAYERCOMPINFO };

	/** 
		This enum is a bitfield for first two Layer Comp options.
	*/
	enum {
		/** [Custom]
		*/
		kCustomLayerCompID	= -2,

		/** Last Document State
		*/
		kLastDocStateCompID	= -1
	};

	/**	Clear all layer comps out of the interface.
	*/
	virtual void Clear ( ) = 0;
	/**	Copy all information from the given interface into this interface. This
		will perform a Clear() on the existing information prior to the copy.
		@param srcCompInfo IN the source IPSDLayerCompInfo to copy from.
	*/
	virtual void Copy(const IPSDLayerCompInfo* srcCompInfo) = 0;
	/** Preallocate the layer comp list to this size. If it is known before hand how
		many layer comps will be added to the interface, use this to preallocate the
		number of entries.
		@param numberComps IN the number of entries that will be added to the list.
	*/
	virtual void Preallocate ( int32 numberComps ) = 0;
	/**	Insert a layer comp into the interface. The layer comp will be inserted into
		the front of the list. It is assumed that all layer comps are uniquely IDed. 
		@param layerCompName IN a PMString containing a layer comp name.
		@param layerCompComment IN a PMString containing a layer comp comment.
		@param layerCompID IN a unique ID that can represent the layer comp
		@param layerVisibilityList IN a LayerVisibilityList containing the 
		key/value pairs denoting the layer visibility for each layer, as defined
		by the layer comp.
	*/
	virtual void InsertLayerComp (	const PMString& layerCompName, 
									const PMString& layerCompComment, 
									int32 layerCompID,
									LayerVisibilityList& layerVisibilityList
									) = 0;
	/**	Append a layer comp onto the interface. The layer comp will be appended onto
		the end of the list. It is assumed that all layer comps are uniquely IDed. 
		@param layerCompName IN a PMString containing a layer comp name.
		@param layerCompComment IN a PMString containing a layer comp comment.
		@param layerCompID IN a unique ID that can represent the layer comp
		@param layerVisibilityList IN a LayerVisibilityList containing the 
		key/value pairs denoting the layer visibility for each layer, as defined
		by the layer comp.
	*/
	virtual void AppendLayerComp (	const PMString& layerCompName, 
									const PMString& layerCompComment, 
									int32 layerCompID,
									LayerVisibilityList& layerVisibilityList
									) = 0;
	/**	Remove a layer from the interface.
		@param layerCompID IN the ID of the layer comp to remove.
	*/
	virtual void RemoveLayerComp (	int32 layerCompID ) = 0; 
	/**	Check if the currently applied layer comp in the given IPSDLayerCompInfo
		exists in the given IPSDLayerCompInfo interface.
		@param srcCompInfo IN the source IPSDLayerCompInfo to use.
		@return bool16 - kTrue if the current applied layer comp exists, kFalse otherwise. 
	*/
	virtual bool16 ValidateLayerComp(const IPSDLayerCompInfo* srcCompInfo) = 0;
	/**	See if the layer comp has changed.
		@return bool16 - kTrue if there is a currently applied layer comp and it is
		different from the originally applied layer comp, kFalse if not. 
	*/
	virtual bool16 LayerCompChanged() const = 0;

	/**	Set the original applied layer comp ID.
		@param layerCompID IN the ID of the originally applied layer comp.
	*/
	virtual void SetOriginalLastAppliedCompID (	int32 layerCompID ) = 0;
	/**	Set the current applied layer comp ID.
		@param layerCompID IN the ID of the currently applied layer comp.
	*/
	virtual void SetCurrentLastAppliedCompID (	int32 layerCompID ) = 0;

	/**	Get the number of layers comps currently stored in the interface. For use when iterating
		through the layer comps, setting or getting specific information.
		@return int32 of the number of layer comps. 
	*/
	virtual int32 GetNumberLayerComps( ) const = 0;

	/**	Get the name of the layer comp with the given unique ID.
		@param layerCompID IN the unique ID of the layer comp to retrieve. 
		@return PMString of the layer comp name. 
	*/
	virtual PMString GetLayerCompName ( int32 layerCompID ) const = 0;
	/**	Get the name of the layer comp of the given layer comp index.
		@param index IN the index of the layer comp to retrieve.
		@return PMString of the layer comp name. 
	*/
	virtual PMString GetNthLayerCompName ( int32 index ) const = 0;
	/**	Get the comment for the layer comp with the given unique ID.
		@param layerCompID IN the unique ID of the layer comp to retrieve. 
		@return PMString of the layer comp comment. 
	*/
	virtual PMString GetLayerCompComment ( int32 layerCompID ) const = 0;
	/**	Get the comment for the layer comp of the given layer comp index.
		@param index IN the index of the layer comp to retrieve.
		@return PMString of the layer comp comment. 
	*/
	virtual PMString GetNthLayerCompComment ( int32 index ) const = 0;
	/**	Get the LayerVisibilityList for the layer comp with the given unique ID.
		@param layerCompID IN the unique ID of the layer comp to retrieve. 
		@return LayerVisibilityList of the layer comp comment. The LayerVisibilityList is a
		vector of key/value pairs containing layer IDs and visibilities on/off for each layer. 
	*/
	virtual LayerVisibilityList GetLayerCompVisibilityList ( int32 layerCompID ) const = 0;
	/**	Get the LayerVisibilityList for the layer comp of the given layer comp index.
		@param index IN the index of the layer comp to retrieve.
		@return LayerVisibilityList of the layer comp comment. The LayerVisibilityList is a
		vector of key/value pairs containing layer IDs and visibilities on/off for each layer. 
	*/
	virtual LayerVisibilityList GetNthLayerCompVisibilityList ( int32 index ) const = 0;
	/**	Get the index of the layer comp with the given unique ID.
		@param layerCompID IN the unique ID of the layer comp to retrieve. 
		@return int32 of the layer comp's index. 
	*/
	virtual int32 GetLayerCompIndex ( int32 layerCompID ) const = 0;
	/**	Get the unique ID of the layer comp of the given layer comp index.
		@param index IN the index of the layer comp ID to retrieve.
		@return int32 of the layer comp's unique ID (see InsertLayerComp() above). 
	*/
	virtual int32 GetNthLayerCompID ( int32 index ) const = 0;

	/**	Get the ID of the originally applied layer comp.
		@return int32 of the originally applied layer comp ID. May be -1 for Last Document
		State - means no layer comp originally applied.
	*/
	virtual int32 GetOriginalLastAppliedCompID ( ) const = 0;
	/**	Get the ID of the currently applied layer comp.
		@return int32 of the currently applied layer comp ID. May be -1 for Last Document
		State or -2 for [Custom] - means no layer comp currently applied.
	*/
	virtual int32 GetCurrentLastAppliedCompID ( ) const = 0;
};

#endif
