//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDuplicateLayerCmdData.h $
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
//  Data interface for duplicate layers.
//  
//========================================================================================

#pragma once
#ifndef __IDuplicateLayerCmdData__
#define __IDuplicateLayerCmdData__

#include "IPMUnknown.h"
#include "UIDRef.h"

/**  Data interface for duplicate layer command to duplicate all the page items from one document layer to another.
	@ingroup layout_layer
	@see kDuplicateLayerCmdBoss
	@see kNewLayerCmdBoss
*/
class IDuplicateLayerCmdData : public IPMUnknown
{
public:
	/**
	   Sets the values for the command's data for source and destination document layer. All the items on the source layer
	   are duplicated onto the destination layer (which must already exist). Any text threaded is preserved.
	   @param sourceLayer the layer to duplicate.
	   @param destinationLayer the destination layer to put all the page items from the sourceLayer on.
	 */
	virtual void Set(const UIDRef& sourceLayer, const UIDRef& destinationLayer) = 0;

	/**
	   Gets the data value for the source document layer.
	   @return the source layer.
	 */
	virtual const UIDRef& GetSourceLayer() const = 0;

	/**
	   Gets the data value for the destination document layer.
	   @return the destination layer.
	 */
	virtual const UIDRef& GetDestinationLayer() const = 0;
};

#endif // __IDuplicateLayerCmdData__
