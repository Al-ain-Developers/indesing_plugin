//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSuiteTableCSB.cpp $
//  
//  Owner: Danielle Bessette
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

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "ICommand.h"
#include "IControlView.h"
#include "IDocumentLayer.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "ILayoutControlData.h"
#include "IMultiColumnTextFrame.h"
#include "ISelectionManager.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ITableSuite.h"
#include "ITextFrameColumn.h"

// ----- Includes -----

#include "ILayerSuite.h"
#include "HelperInterface.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ISelectionUtils.h"


// ----- ID.h files -----

#include "LayerPanelID.h"


class LayerSuiteTableCSB : public ILayerSuite
{
public:
    LayerSuiteTableCSB(IPMUnknown *boss);
    ~LayerSuiteTableCSB();

	virtual void		GetSelectedLayers(UIDList& docLayerUIDList);
	virtual bool16		AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr);
	virtual void		SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd);
	virtual ErrorCode	MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate);
	virtual UIDList GetSelectedItemsForLayersPanel() const;

DECLARE_HELPER_METHODS()
};

DEFINE_HELPER_METHODS(LayerSuiteTableCSB)

CREATE_PMINTERFACE(LayerSuiteTableCSB, kLayerSuiteTableCSBImpl )

LayerSuiteTableCSB::LayerSuiteTableCSB(IPMUnknown *boss) :
    HELPER_METHODS_INIT(boss)
{
}


LayerSuiteTableCSB::~LayerSuiteTableCSB()
{
}

void LayerSuiteTableCSB::GetSelectedLayers(UIDList& )
{
	// Does nothing for tables
}

UIDList LayerSuiteTableCSB::GetSelectedItemsForLayersPanel() const
{
	// Does nothing for tables
	return UIDList();
}

bool16 LayerSuiteTableCSB::AreAllItemsOnLayerSelected(IDocumentLayer* , IControlView* , bool16 /*guideLayerOnly*/)
{
	// Does nothing for tables
	return kFalse;
}

void LayerSuiteTableCSB::DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 /*guideLayerOnly*/)
{
	InterfacePtr<ILayoutControlData> layoutData(view, IID_ILAYOUTCONTROLDATA);
	ASSERT_MSG(layoutData != nil, "LayerSuiteTableCSB::DeselectAllItemsOnLayer - layoutData != nil");

	InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
	InterfacePtr<ISpreadLayer> layer(spread->QueryLayer(documentLayer, nil, kFalse));	// Regular spread layer
	InterfacePtr<IHierarchy> layerHierarchy(layer, IID_IHIERARCHY);

	InterfacePtr<ITableSuite> tableSuite(this, UseDefaultIID());
	K2Vector<ITextFrameColumn*> *textFrameColumns = tableSuite->GetTextFramesSpannedBySelection();
	if(textFrameColumns != nil && textFrameColumns->size() > 0)
		{
		bool16 deselectAllDone = kFalse;
		for (K2Vector<ITextFrameColumn*>::const_iterator iter = textFrameColumns->begin(); 
			iter != textFrameColumns->end() && !deselectAllDone; ++iter)
			{
			ITextFrameColumn* currentTFC = *iter;
			InterfacePtr<IHierarchy> pFrameHier(currentTFC, UseDefaultIID());
			if (pFrameHier && layerHierarchy && 
				pFrameHier->GetLayerUID() == layerHierarchy->GetLayerUID() && !deselectAllDone)
				{
				// this assumes that if there is a text selection, there isn't 
				// anything else selected. also assumes only contiguous text selection
				InterfacePtr<ISelectionManager> iSelectionManager ( Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
				
				iSelectionManager->DeselectAll (nil);
				deselectAllDone = kTrue;
				}
			currentTFC->Release();
			}	
		}

	if(textFrameColumns)
		delete textFrameColumns;
}

void LayerSuiteTableCSB::DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr)
{
	InterfacePtr<ITableSuite> tableSuite(this, UseDefaultIID());
	K2Vector<ITextFrameColumn*> *textFrameColumns = tableSuite->GetTextFramesSpannedBySelection();
	if(textFrameColumns != nil && textFrameColumns->size() > 0)
	{
		bool16 deselectAllDone = kFalse;
		for (K2Vector<ITextFrameColumn*>::const_iterator iter = textFrameColumns->begin(); 
			iter != textFrameColumns->end() && !deselectAllDone; ++iter)
		{
			ITextFrameColumn* currentTFC = *iter;
			InterfacePtr<IMultiColumnTextFrame> pMCTF(currentTFC->QueryMultiColumnTextFrame());
			if (pMCTF && selectionMgr && list.Location(::GetUID(pMCTF)) != -1)
			{
				selectionMgr->DeselectAll (nil);
				deselectAllDone = kTrue;
			}
			currentTFC->Release();
		}	
	}

	if(textFrameColumns)
		delete textFrameColumns;
}

void LayerSuiteTableCSB::SelectAllItemsOnLayer(IDocumentLayer* , IControlView* , bool16 , Selection::Action )
{
	// Does nothing for tables
}

ErrorCode LayerSuiteTableCSB::MoveToLayer(IDocumentLayer* , IDocumentLayer* , IControlView* , Selection::Action , bool16 )
{
	// Does nothing for tables
	return kSuccess;
}
