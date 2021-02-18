//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSuiteIntegrator.cpp $
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
//  Purpose: Implements the integrator for ILayerSuite on the abstract selection boss.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IIntegratorTarget.h"

// ----- Includes -----

#include "ILayerSuite.h"
#include "HelperInterface.h"
#include "UIDList.h"
#include "IControlView.h"
#include "ILayoutControlData.h"
#include "IDocumentLayer.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


class LayerSuiteIntegrator : public ILayerSuite
{
public:
	LayerSuiteIntegrator(IPMUnknown *boss);
	~LayerSuiteIntegrator();

		virtual void		GetSelectedLayers(UIDList& docLayerUIDList);
		virtual bool16		AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
		virtual void		DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
		virtual void		DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr);
		virtual void		SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd);
		virtual ErrorCode	MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate);
		virtual UIDList GetSelectedItemsForLayersPanel() const;
	
DECLARE_HELPER_METHODS()
};

DEFINE_HELPER_METHODS(LayerSuiteIntegrator)

CREATE_PMINTERFACE(LayerSuiteIntegrator, kLayerSuiteIntegratorImpl )

LayerSuiteIntegrator::LayerSuiteIntegrator(IPMUnknown *boss) : 
	HELPER_METHODS_INIT(boss)
{
}


LayerSuiteIntegrator::~LayerSuiteIntegrator()
{
}

UIDList LayerSuiteIntegrator::GetSelectedItemsForLayersPanel() const
{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));
	
	int32 numSuites = layerSuites->size();
	for (int32 i = 0; i < numSuites; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		UIDList selectedPageItems = ithSuite->GetSelectedItemsForLayersPanel();
		if(selectedPageItems.size())
			return selectedPageItems;
	}
	return UIDList();
}


void LayerSuiteIntegrator::GetSelectedLayers(UIDList& docLayerUIDList)
{

	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));

	ASSERT_MSG(docLayerUIDList.Length() == 0, "Document Layer list not empty!");
	
	int32 numSuites = layerSuites->size();
	for (int32 i = 0; i < numSuites; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		ithSuite->GetSelectedLayers(docLayerUIDList);
	}
}

bool16 LayerSuiteIntegrator::AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly)
{
	ASSERT(view);

	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));
	
	int32 numSuites = layerSuites->size();
	bool16 allSelected = kFalse;
	for (int32 i = 0; i < numSuites; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		allSelected = allSelected || ithSuite->AreAllItemsOnLayerSelected(documentLayer, view, guideLayerOnly);
	}
	return allSelected;
}

void LayerSuiteIntegrator::DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly)
{
	ASSERT(view);

	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));
	
	int32 numSuites = layerSuites->size();
	for (int32 i = 0; i < numSuites; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		ithSuite->DeselectAllItemsOnLayer(documentLayer, view, guideLayerOnly);
	}
}

void LayerSuiteIntegrator::DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr)
{
	ASSERT(selectionMgr);

	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));
	
	int32 numSuites = layerSuites->size();
	for (int32 i = 0; i < numSuites; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		ithSuite->DeselectAllItemsInList(list, selectionMgr);
	}
}

void LayerSuiteIntegrator::SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd)
{
	ASSERT(view);

	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));
	
	int32 numSuites = layerSuites->size();
	for (int32 i = 0; i < numSuites; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		ithSuite->SelectAllItemsOnLayer(documentLayer, view, guideLayerOnly, replaceOrAdd);
	}
}

ErrorCode LayerSuiteIntegrator::MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate)
{
	ASSERT(view);
	ErrorCode rc = kSuccess;

	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> layerSuites (iIntegratorTarget->GetTarget (IID_ILAYERSUITE));
	
	int32 numSuites = layerSuites->size();
	for (int32 i = 0; i < numSuites && rc == kSuccess; i++)
	{
		ILayerSuite* ithSuite = static_cast<ILayerSuite*>((*layerSuites)[i].get());
		rc = ithSuite->MoveToLayer(sourceLayer, targetLayer, view, replaceOrAdd, bDuplicate);
	}

	return rc;
}
