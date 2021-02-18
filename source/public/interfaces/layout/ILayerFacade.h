//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayerFacade.h $
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
#ifndef __ILayerFacade__
#define __ILayerFacade__


#include "IPMUnknown.h"

#include "LayerID.h"
class IDocumentLayer;

/**	Suite interface to manipulate document-wide layers
	@ingroup layout_layer
	@ingroup layout_util
	@ingroup layout_suite
	@see kDocumentLayerBoss

*/
namespace Facade
{
	class ILayerFacade : public IPMUnknown
	{
		public:
			enum { kDefaultIID = IID_ILAYERFACADE };

			/**	 Moves selected items(or duplicates) to new layer. 
				@param inOutItemsToMove, items in list initially will be moved or duplicated to targetLayer IDocumentLayer. On return, will be populated with the moved items(which might be duplicates)
				@param targetLayer passed in item UIDs will be moved to targetLayer IDocumentLayer. 
				@param bDuplicate, kTrue to duplicate the items before moving to the destination layer. 
				@return ErrorCode
			 */
			virtual ErrorCode MoveToLayer(UIDList& inOutItemsToMove, IDocumentLayer* targetLayer, bool16 bDuplicate) = 0;

			/**	 Moves selected layers(or duplicates) to new spot in layer list. 
				@param layersToMove, items in list initially will be moved or duplicated relative to relativeToLayerRef. On return, will be populated with the moved items(which might be duplicates).
				@param relativeToLayerRef layers will be moved so that it is directly under this layer. 
				@param bDuplicate, kTrue to duplicate the items before moving to the destination layer. 
				@return ErrorCode
			 */
			virtual ErrorCode MoveLayers(UIDList& inOutlayersToMove, const UIDRef& relativeToLayerRef, bool16 bDuplicate) = 0;
	};
}

#endif // __IShortcutContext__
		
		