//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSuiteTextCSB.cpp $
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

#include "IHierarchy.h"
#include "ISpreadLayer.h"
#include "ISpread.h"
#include "ITextSelectionSuite.h"
#include "IFrameList.h"
#include "ITextFocus.h"
#include "ITextFrameColumn.h"
#include "ITextModel.h"
#include "ILayoutControlData.h"
#include "ICommand.h"
#include "IDocumentLayer.h"
#include "IGeometry.h"
#include "ITextRanges.h"
#include "ITextParcelList.h"
#include "IParcelList.h"
#include "IControlView.h"
#include "ISelectionUtils.h"

// ----- Includes -----

#include "ILayerSuite.h"
#include "HelperInterface.h"

// ----- Utility files -----

#include "CmdUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


class LayerSuiteTextCSB : public ILayerSuite
{
public:
    LayerSuiteTextCSB(IPMUnknown *boss);
    ~LayerSuiteTextCSB();

	virtual void		GetSelectedLayers(UIDList& docLayerUIDList);
	virtual bool16		AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr);
	virtual void		SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd);
	virtual ErrorCode	MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate);
	virtual UIDList GetSelectedItemsForLayersPanel() const;

DECLARE_HELPER_METHODS()
};

DEFINE_HELPER_METHODS(LayerSuiteTextCSB)

CREATE_PMINTERFACE(LayerSuiteTextCSB, kLayerSuiteTextCSBImpl )

LayerSuiteTextCSB::LayerSuiteTextCSB(IPMUnknown *boss) :
    HELPER_METHODS_INIT(boss)
{
}


LayerSuiteTextCSB::~LayerSuiteTextCSB()
{
}

// Look through the page items in the layout selection and
// create a list of document layers that all the items are on.
void LayerSuiteTextCSB::GetSelectedLayers(UIDList& )
{
	// Does nothing for Text
}

UIDList LayerSuiteTextCSB::GetSelectedItemsForLayersPanel() const
{
	// Does nothing for Text
	return UIDList();
}


bool16 LayerSuiteTextCSB::AreAllItemsOnLayerSelected(IDocumentLayer* , IControlView* , bool16 /*guideLayerOnly*/)
{
	// Does nothing for Text
	return kFalse;
}

void LayerSuiteTextCSB::DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 /*guideLayerOnly*/)
{
	InterfacePtr<ILayoutControlData> layoutData(view, IID_ILAYOUTCONTROLDATA);
	ASSERT_MSG(layoutData != nil, "LayerSuiteTextCSB::DeselectAllItemsOnLayer - layoutData != nil");

	InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
	InterfacePtr<ISpreadLayer> layer(spread->QueryLayer(documentLayer, nil, kFalse));	// Regular spread layer
	InterfacePtr<IHierarchy> layerHierarchy(layer, IID_IHIERARCHY);

	InterfacePtr<ITextRanges> textRangesInterface(this, UseDefaultIID());
	K2Vector<InDesign::TextRange> *textRanges = textRangesInterface->CreateTextRanges();

	bool16 deselectAll = kFalse;
	for(K2Vector<InDesign::TextRange>::const_iterator rangeIter = textRanges->begin(); 
	    rangeIter != textRanges->end() && !deselectAll; ++rangeIter)
	{
		InDesign::TextRange textRange = *rangeIter; 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel()); 
		InterfacePtr<ITextParcelList> tpl(textModel->QueryTextParcelList(textRange.Start())); 
		InterfacePtr<IParcelList> pl(tpl, UseDefaultIID()); 
		TextIndex currentStart = textRange.Start();
		TextIndex end = textRange.End();

		// With insertion point, bump end so we enter while loop.
		if (textRange.Length() == 0)
			end++;

		ParcelKey startParcelKey = tpl->GetParcelContaining(currentStart); 
		if(startParcelKey.IsValid())
		{
			IParcelList::const_iterator iter = pl->begin(startParcelKey);
			ParcelKey endParcelKey = tpl->GetParcelContaining(end - 1);
			if (!endParcelKey.IsValid())
				endParcelKey = pl->GetLastParcelKey();
			IParcelList::const_iterator iterEnd = pl->end(endParcelKey);

			for ( ; iter != iterEnd; ++iter)
			{
				InterfacePtr<ITextFrameColumn> pTFC(pl->QueryParcelFrame(*iter)); 
				InterfacePtr<IHierarchy> pFrameHier(pTFC, IID_IHIERARCHY);
				if (pFrameHier && layerHierarchy && pFrameHier->GetLayerUID() == layerHierarchy->GetLayerUID())
				{
					deselectAll = kTrue;
					break;
				}
			}
		}
	}
	delete textRanges;

	if(deselectAll)
	{
		// If the selection is contained in the layer being hidden then clear the whole selection
		InterfacePtr<ISelectionManager> iSelectionManager ( Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
		
		iSelectionManager->DeselectAll (nil);
	}
}

void LayerSuiteTextCSB::DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr)
{
	InterfacePtr<ITextRanges> textRangesInterface(this, UseDefaultIID());
	K2Vector<InDesign::TextRange> *textRanges = textRangesInterface->CreateTextRanges();

	bool16 deselectAll = kFalse;
	for(K2Vector<InDesign::TextRange>::const_iterator rangeIter = textRanges->begin(); 
	    rangeIter != textRanges->end() && !deselectAll; ++rangeIter)
	{
		InDesign::TextRange textRange = *rangeIter; 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel()); 
		InterfacePtr<ITextParcelList> tpl(textModel->QueryTextParcelList(textRange.Start())); 
		InterfacePtr<IParcelList> pl(tpl, UseDefaultIID()); 
		TextIndex currentStart = textRange.Start();
		TextIndex end = textRange.End();

		// With insertion point, bump end so we enter while loop.
		if (textRange.Length() == 0)
			end++;

		ParcelKey startParcelKey = tpl->GetParcelContaining(currentStart); 
		if(startParcelKey.IsValid())
		{
			IParcelList::const_iterator iter = pl->begin(startParcelKey);
			ParcelKey endParcelKey = tpl->GetParcelContaining(end - 1);
			if (!endParcelKey.IsValid())
				endParcelKey = pl->GetLastParcelKey();
			IParcelList::const_iterator iterEnd = pl->end(endParcelKey);

			for ( ; iter != iterEnd; ++iter)
			{
				InterfacePtr<ITextFrameColumn> pTFC(pl->QueryParcelFrame(*iter));
				InterfacePtr<IMultiColumnTextFrame> pMCTF(pTFC->QueryMultiColumnTextFrame());
				if (pMCTF && list.Location(::GetUID(pMCTF)) != -1)
				{
					deselectAll = kTrue;
					break;
				}
			}
		}
	}
	delete textRanges;

	if(deselectAll && selectionMgr)
	{
		// If the selection is contained in the list then clear the whole selection
		selectionMgr->DeselectAll (nil);
	}
}

void LayerSuiteTextCSB::SelectAllItemsOnLayer(IDocumentLayer* , IControlView* , bool16 , Selection::Action )
{
	// Does nothing for Text
}

ErrorCode LayerSuiteTextCSB::MoveToLayer(IDocumentLayer* , IDocumentLayer* , IControlView* , Selection::Action , bool16 )
{
	// Does nothing for Text
	return kSuccess;
}
