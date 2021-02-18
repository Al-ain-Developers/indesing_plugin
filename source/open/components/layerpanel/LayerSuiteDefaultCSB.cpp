//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSuiteDefaultCSB.cpp $
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

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IControlView.h"
#include "IDocumentLayer.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "ILayerSuite.h"
#include "ILayoutControlData.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ILayoutSelectionSuite.h"

// ----- Includes -----

#include "HelperInterface.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ILayerUtils.h"
#include "ISelectionUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


class LayerSuiteDefaultCSB : public ILayerSuite
{
public:
    LayerSuiteDefaultCSB(IPMUnknown *boss);
    ~LayerSuiteDefaultCSB();

	virtual void		GetSelectedLayers(UIDList& docLayerUIDList);
	virtual bool16		AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr);
	virtual void		SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd);
	virtual ErrorCode	MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate);
	virtual UIDList		GetSelectedItemsForLayersPanel() const;

DECLARE_HELPER_METHODS()
};

DEFINE_HELPER_METHODS(LayerSuiteDefaultCSB)

CREATE_PMINTERFACE(LayerSuiteDefaultCSB, kLayerSuiteDefaultCSBImpl )

LayerSuiteDefaultCSB::LayerSuiteDefaultCSB(IPMUnknown *boss) :
    HELPER_METHODS_INIT(boss)
{
}


LayerSuiteDefaultCSB::~LayerSuiteDefaultCSB()
{
}

void LayerSuiteDefaultCSB::GetSelectedLayers(UIDList& )
{
	// Does nothing for Default CSB, nothing is selected.
}

UIDList LayerSuiteDefaultCSB::GetSelectedItemsForLayersPanel() const
{
	// Does nothing for Default CSB, nothing is selected.
	return UIDList();
}

void LayerSuiteDefaultCSB::DeselectAllItemsOnLayer(IDocumentLayer* , IControlView* , bool16 )
{
	// Does nothing for Default CSB, nothing is selected.
}

void LayerSuiteDefaultCSB::DeselectAllItemsInList(UIDList&, ISelectionManager*)
{
	// Does nothing for Default CSB, nothing is selected.
}

bool16 LayerSuiteDefaultCSB::AreAllItemsOnLayerSelected(IDocumentLayer* , IControlView* , bool16 )
{
	// Does nothing for Default CSB, nothing is selected.
	return kFalse;
}

void LayerSuiteDefaultCSB::SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd)
{
	InterfacePtr<ILayoutControlData> layoutData(view, IID_ILAYOUTCONTROLDATA);
	ASSERT_MSG(layoutData != nil, "CLayoutLayerListObserver::DeselectItems - layoutData != nil");
	if (layoutData)
	{
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(documentLayer, nil, guideLayerOnly));	// Regular spread layer or guide layer
		InterfacePtr<IHierarchy> layerHierarchy(spreadLayer, IID_IHIERARCHY);

		UIDList selectedList(GetDataBase(spread));

		if (layerHierarchy)
		{
			// Put all the items on this layer into a list.
			if (spreadLayer->IsVisible() && !spreadLayer->IsLocked())
			{
				int32 numItems = layerHierarchy->GetChildCount();
				for (int32 j = 0; j < numItems; j++)
					selectedList.Append(layerHierarchy->GetChildUID(j));
			}

			if (selectedList.Length() > 0)
			{
				InterfacePtr<ISelectionManager> iSelectionManager ( Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
				InterfacePtr<ILayoutSelectionSuite>	iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (iSelectionManager));	
				
				iLayoutSelectionSuite->SelectPageItems (selectedList, replaceOrAdd, Selection::kDontScrollLayoutSelection);
			}
		}
		else
		{
			ASSERT_FAIL("LayerSuiteLayoutCSB::SelectAllItemsOnLayer, No hierarchy found!");
		}
	}
}

ErrorCode LayerSuiteDefaultCSB::MoveToLayer(IDocumentLayer* , IDocumentLayer* , IControlView* , Selection::Action , bool16 )
{
	// Does nothing for Default CSB, nothing is selected.
	return kSuccess;
}
