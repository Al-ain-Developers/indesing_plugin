//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayerSuite.h $
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
#ifndef __ILayerSuite__
#define __ILayerSuite__


#include "IPMUnknown.h"

#include "LayerPanelID.h"
#include "ISelectionMessages.h"

class IControlView;
class IDocumentLayer;
class ISelectionManager;

/**	Suite interface to manipulate document-wide layers
	@ingroup layout_layer
	@ingroup layout_util
	@ingroup layout_suite
	@see kDocumentLayerBoss

*/
class ILayerSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILAYERSUITE };


		/**	Populates the UIDList the document layer uids for selection.
			@param docLayerUIDList, UIDs of document layers the selection is on. 
		 */
		virtual void GetSelectedLayers(UIDList& docLayerUIDList) = 0;

		/**	Checks if everything on a particular layer (on current spread) is selected
			@param documentLayer, the IDocumentLayer that will be checked. 
			@param view, the IControlView to use. 
			@param guideLayerOnly, kTrue for guide layers only, kFalse for all layers. 
			@return true if all the items on this layer are selected
		 */
		virtual bool16 AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly) = 0;

		/**	Deselects items on the current layer (on current spread)
			@param documentLayer, the IDocumentLayer that will be deselected.
			@param view, the IControlView to use. 
			@param guideLayerOnly, kTrue for guide layers only, kFalse for all layers. 
		 */
		virtual void DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly) = 0;
		
		/**	Deselects items in the pass in list 
			@param documentLayer, the IDocumentLayer that will be deselected.
			@param view, the IControlView to use. 
		 */
		virtual void DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr) = 0;
		
		/**	Selects items on the current layer (on current spread)
			@param list, the list items to deselect. 
			@param view, the IControlView to use. 
			@param guideLayerOnly, kTrue for guide layers only, kFalse for all layers. 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
		 */
		virtual void SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd) = 0;

		/**	 Moves items selected in layout on current spread & current layer to new layer.
			@param sourceLayer, selection on source IDocumentLayer will be moved to targetLayer IDocumentLayer. 
			@param targetLayer, selection on source IDocumentLayer will be moved to targetLayer IDocumentLayer. 
			@param view, the IControlView to use. 
			@param guideLayerOnly, kTrue if moving guide layers, kFalse otherwise. 
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param bDuplicate, kTrue to duplicate the selection before moving to the destination layer. 
			@return ErrorCode
		 */
		virtual ErrorCode MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate) = 0;

		/**	Returns a UIDList of pageitems known to the layers panel, an part of the current selection
		 @return list of page items shown in the layers panel that are currently selected 
		 */
		virtual UIDList GetSelectedItemsForLayersPanel() const = 0;
};

#endif // __IShortcutContext__
		
		