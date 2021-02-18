//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/DebuggingLayers.cpp $
//  
//  Owner: ?
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

#ifdef DEBUG

// Interfaces:
#include "ILayerList.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IHierarchy.h"
#include "INewLayerCmdData.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "ILayoutControlData.h"
#include "IControlView.h"
#include "IGeometry.h"
#include "IActiveContext.h"

// Includes
#include "DebuggingLayers.h"
#include "Trace.h"
#include "PMString.h"
#include "InterfacePtr.h"
#include "CmdUtils.h"
#include "UIDList.h"
#include "PersistUtils.h"

#include "ICallback.h"
#include "IDrawMgr.h"
#include "ISpread.h"
#include "SplineID.h"
#include "IPathGeometry.h"
//#include "TextID.h"
#include "DebugClassUtils.h"

void DumpSpline(IPMUnknown *spline);

//---------------------------------------------------------------
// class ItemIterator
// Used for iterating items in a hierarchy in IterateDrawOrder.
//---------------------------------------------------------------
class ItemIterator : public ICallback
{
public:
	ItemIterator (IDrawMgr *drawMgr)
		: fDrawMgr (drawMgr) {}
	virtual void	ExecuteCallback(const PMMatrix *, IPMUnknown *thing, int32 flags);
	virtual IDrawMgr *GetCallbackDrawManager()
		{
			return fDrawMgr;
		}
private:
	IDrawMgr	*fDrawMgr;
};

//---------------------------------------------------------------
// ItemIterator::Callback
// Callback function called once for every node in the hierarchy.
//---------------------------------------------------------------
void ItemIterator::ExecuteCallback(const PMMatrix *, IPMUnknown *thing, int32 )
{
	InterfacePtr<IHierarchy> itemHier(thing, IID_IHIERARCHY);
	if (!itemHier)
		return;

	ClassID clsID = ::GetClass(thing);

	DebugClassUtilsBuffer buf;
	TRACEFLOW("Old:Layers", "Got page item uid %ld, class %s\n", ::GetUID(thing).Get(), DebugClassUtils::GetIDName(&buf,clsID));

	// Does this node have children?
	int32 numChildren = itemHier->GetChildCount();
	TRACEFLOW("Old:Layers", "\tHas %d children%c\n", numChildren, numChildren > 0 ? ':' : ' ');
	for (int32 i = 0; i < numChildren; ++i)
	{
		InterfacePtr<IHierarchy> iChildHier(::GetDataBase(thing), itemHier->GetChildUID(i), UseDefaultIID());
		TRACEFLOW("Old:Layers", "\t\t%ld, class%s\n", itemHier->GetChildUID(i).Get(), DebugClassUtils::GetIDName(&buf,::GetClass(iChildHier)));
	}

	// Information about the parent
	UID parent = itemHier->GetParentUID();
	TRACEFLOW("Old:Layers", "\tRoot is %ld, ", itemHier->GetRootUID().Get());
	if (parent != kInvalidUID)	{
		TRACEFLOW("Old:Layers", "parent is UID %ld, class %s. ", parent.Get(), DebugClassUtils::GetIDName(&buf,::GetDataBase(itemHier)->GetClass(parent)));
		InterfacePtr<IHierarchy> parentHier(itemHier->QueryParent());
		if (parent != kInvalidUID)	{
			int32 myIndex = parentHier->GetChildIndex(itemHier);
			TRACEFLOW("Old:Layers", "Child (%ld) is %d in its hierarchy.\n", ::GetUID(thing).Get(), myIndex);
			}
		}
	else if (itemHier->GetRootUID() == ::GetUID(itemHier))
		TRACEFLOW("Old:Layers", "\titem is root of hierarchy\n");
	else
		TRACEFLOW("Old:Layers", "\tError! Parent is missing\n");

#if 0
	// Specific information about the type
	switch(clsID.Get())	{
		case kSplineItemBoss:
			DumpSpline(thing);
			break;
		default:
			break;
		}
#endif
	TRACEFLOW("Old:Layers", "\n\n");
}

// A test function to iterate over all the items on the current spread using
// the DragMgr and print out (trace window) info about the items.
void IteratePageItems()
{
	InterfacePtr<ILayoutControlData> layoutData;
	IControlView* contextView = GetExecutionContextSession()->GetActiveContext()->GetContextView();
	if (contextView)
		layoutData = InterfacePtr<ILayoutControlData>(contextView, IID_ILAYOUTCONTROLDATA);

	if (layoutData == nil)
		return;

	IDocument* document = layoutData->GetDocument();
	InterfacePtr<IGeometry> spreadItem (layoutData->GetSpreadRef(), UseDefaultIID());
	InterfacePtr<ISpread> spread(spreadItem, IID_ISPREAD);

	if (document)
	{
		InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST);
		int32 numLayers = layerList->GetCount();

		const int32	flags = 0;
		InterfacePtr<IDrawMgr> drawMgr ((IDrawMgr *)::CreateObject (kDrawMgrBoss, IID_IDRAWMGR));
		ItemIterator callback (drawMgr);

		// Iterate over all the regular spread layers that are visible.
		for (int32 j = 0; j < numLayers; j++)
		{
			InterfacePtr<IDocumentLayer> docLayer(layerList->QueryLayer(j));
			InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(docLayer /* , nil, kFalse */));

			PMString layerName;
			spreadLayer->GetName(&layerName);

			if (spreadLayer->IsVisible())
			{
				TRACEFLOW("Old:Layers", "Iterating visible layer: \"%s\"\n", layerName.GetUTF8String().c_str());
				drawMgr->IterateDrawOrder( ::GetUIDRef(spreadLayer), &callback, flags);
				TRACEFLOW("Old:Layers", "\n");
			}
			else
			{
				TRACEFLOW("Old:Layers", "Skipping hidden layer: \"%s\"\n\n", layerName.GetUTF8String().c_str());
			}
		}
	}
}


// A test function to iterate over all the items on the current spread using
// the DragMgr and print out (trace window) info about the items.
void IterateSpread()
{
	InterfacePtr<ILayoutControlData> layoutData;
	IControlView* contextView = GetExecutionContextSession()->GetActiveContext()->GetContextView();
	if (contextView)
		layoutData = InterfacePtr<ILayoutControlData>(contextView, IID_ILAYOUTCONTROLDATA);

	if (layoutData)	{
		IDocument* document = layoutData->GetDocument();
		if (document)	{
			InterfacePtr<IGeometry> spreadItem (layoutData->GetSpreadRef(), UseDefaultIID());
			InterfacePtr<ISpread> spread(spreadItem, IID_ISPREAD);
			if (spread != nil)	{
				InterfacePtr<IDrawMgr> drawMgr ((IDrawMgr *)::CreateObject (kDrawMgrBoss, IID_IDRAWMGR));
				ItemIterator callback (drawMgr);
				const int32	flags = 0;
				drawMgr->IterateDrawOrder( ::GetUIDRef(spreadItem), &callback, flags);
				}
			}
		}
}


void DumpSpline(IPMUnknown *spline)
{
	InterfacePtr<IPathGeometry> path(spline, IID_IPATHGEOMETRY);
	int32 pathCount = path->GetNumPaths();
	TRACEFLOW("Old:Layers", "\tNumber of paths: %d\n", pathCount);
	for (int32 i = 0; i < pathCount; ++i)	{
		int32 pointCount = path->GetNumPoints(i);
		TRACEFLOW("Old:Layers", "\t\tPath (%s) %d: ", path->IsPathOpen(i) ? "open" : "closed", i);
		for (int32 k = 0; k < pointCount; ++k)	{
			PMPoint pt = path->GetNthPoint(i, k).GetPoint(kAnchorPt);
			TRACEFLOW("Old:Layers", "[%f, %f] ", ::ToFloat(pt.X()), ::ToFloat(pt.Y()));
			}
		TRACEFLOW("Old:Layers", "\n");
		}
}

// A test function to create a non-UI layer.
void CreateNonUILayer()
{
	IDocument* document = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	if (document)
	{
		// Create the NewLayerCmd:
		InterfacePtr<ICommand> layerCmd(CmdUtils::CreateCommand(kNewLayerCmdBoss));

		// Set NewLayerCmd arguments:
		InterfacePtr<INewLayerCmdData> layerData(layerCmd, IID_INEWLAYERCMDDATA);

		layerData->Set
		(
			GetUIDRef(document),			// const UIDRef& layerList
			nil,							// const PMString *name = nil
			kTrue,                          // bool16 isVisible = kTrue,
			kFalse,                         // bool16 isLocked = kFalse,
			kFalse,                         // bool16 isGuideVisible = kTrue,
			kFalse,                         // bool16 isGuideLocked = kFalse,
			kInvalidUID,                    // UID layerColor = kInvalidUID,
			kFalse,                         // bool16 isUILayer = kTrue,
			kTrue                           // bool16 isExpendable = kTrue;
		);

		// Process the command:
		CmdUtils::ProcessCommand(layerCmd);
	}
}

// A test function to create a non-Expendable layer.
void CreateNonExpendableLayer()
{
	IDocument* document = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	if (document)
	{
		// Create the NewLayerCmd:
		InterfacePtr<ICommand> layerCmd(CmdUtils::CreateCommand(kNewLayerCmdBoss));

		// Set NewLayerCmd arguments:
		InterfacePtr<INewLayerCmdData> layerData(layerCmd, IID_INEWLAYERCMDDATA);

		layerData->Set
		(
			GetUIDRef(document),			// const UIDRef& layerList
			nil,							// const PMString *name = nil
			kTrue,                          // bool16 isVisible = kTrue,
			kFalse,                         // bool16 isLocked = kFalse,
			kFalse,                         // bool16 isGuideVisible = kTrue,
			kFalse,                         // bool16 isGuideLocked = kFalse,
			kInvalidUID,                    // UID layerColor = kInvalidUID,
			kTrue,                          // bool16 isUILayer = kTrue,
			kFalse                          // bool16 isExpendable = kTrue;
		);

		// Process the command:
		CmdUtils::ProcessCommand(layerCmd);
	}
}

// A test function to create a non-Expendable layer.
void CreateNonUINonExpendableLayer()
{
	IDocument* document = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	if (document)
	{
		// Create the NewLayerCmd:
		InterfacePtr<ICommand> layerCmd(CmdUtils::CreateCommand(kNewLayerCmdBoss));

		// Set NewLayerCmd arguments:
		InterfacePtr<INewLayerCmdData> layerData(layerCmd, IID_INEWLAYERCMDDATA);

		layerData->Set
		(
			GetUIDRef(document),			// const UIDRef& layerList
			nil,							// const PMString *name = nil
			kTrue,                          // bool16 isVisible = kTrue,
			kFalse,                         // bool16 isLocked = kFalse,
			kFalse,                         // bool16 isGuideVisible = kTrue,
			kFalse,                         // bool16 isGuideLocked = kFalse,
			kInvalidUID,                    // UID layerColor = kInvalidUID,
			kFalse,                         // bool16 isUILayer = kTrue,
			kFalse                          // bool16 isExpendable = kTrue;
		);

		// Process the command:
		CmdUtils::ProcessCommand(layerCmd);
	}
}

void TraceLayerList()
{
	IDocument* document = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	if (document)
	{
		InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST);
		int32 numLayers = layerList->GetCount();

		for (int32 i = 0; i < numLayers; i++)
		{
			InterfacePtr<IDocumentLayer> docLayer(layerList->QueryLayer(i));

			PMString name;
			docLayer->GetName(&name);

			TRACEFLOW("Old:Layers", "%d: Name = %s, Visible = %d, Locked %d, Guide Visible %d, Guide Locked %d, UI Layer %d, Expendable %d\n", 
				i + 1,
				name.GetUTF8String().c_str(),
				docLayer->IsVisible(),
				docLayer->IsLocked(),
				docLayer->IsGuideVisible(),
				docLayer->IsGuideLocked(),
				docLayer->IsUILayer(),
				docLayer->IsExpendableLayer());
		}
	}
}

#endif	// DEBUG
