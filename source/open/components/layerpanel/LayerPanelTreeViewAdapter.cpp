//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelTreeViewAdapter.cpp $
//  
//  Owner: lance bushore
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

#include "ITreeViewHierarchyAdapter.h"
#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "ILayerList.h"
#include "IDocumentLayer.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "IHierarchy.h"
#include "IPageItemTypeUtils.h"
#include "IGraphicFrameData.h"
#include "ITextUtils.h"
#include "ITextModel.h"
#include "IPageItemAdapter.h"
#include "IMultiColumnTextFrame.h"
#include "ITextFrameColumn.h"

#include "CPMUnknown.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelID.h"
#include "ILayerUtils.h"
#include "ILayerUIUtils.h"
#include "LayerPanelUtils.h"
#include "IFrameUtils.h"

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter constructor
//----------------------------------------------------------------------------------------
class LayerPanelTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	LayerPanelTreeViewAdapter(IPMUnknown *boss);
	~LayerPanelTreeViewAdapter();
	
	virtual NodeID_rv	GetRootNode() const;
	virtual NodeID_rv	GetParentNode(const NodeID& node) const;
	virtual int32		GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv	GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32		GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv	GetGenericNodeID() const;
	virtual bool16		ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }
};

CREATE_PMINTERFACE(LayerPanelTreeViewAdapter, kLayerPanelTreeViewAdapterImpl)
//DEFINE_HELPER_METHODS(LayerPanelTreeViewAdapter)

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter constructor
//----------------------------------------------------------------------------------------


LayerPanelTreeViewAdapter::LayerPanelTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}


//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter::~LayerPanelTreeViewAdapter 
//----------------------------------------------------------------------------------------

LayerPanelTreeViewAdapter::~LayerPanelTreeViewAdapter()
{
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------
NodeID_rv LayerPanelTreeViewAdapter::GetRootNode() const
{
	IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	if(frontDocDB)
	{
		return LayerTreeUIDNodeID::Create(frontDocDB->GetRootUID(),kFalse);
	}
	return LayerTreeUIDNodeID::Create(kInvalidUID,kFalse);
}
	
//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------
NodeID_rv LayerPanelTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(node);
	//TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetParentNode called for node with UID %d\n",layerNode->GetUID().Get());
	IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	if(frontDocDB)
	{
		if(layerNode->GetUID() == frontDocDB->GetRootUID())
			return kInvalidNodeID;
		else
		{
			//if the node is not valid, we bail out.
			if (!frontDocDB->IsValidUID(layerNode->GetUID()))
				return kInvalidNodeID;

			InterfacePtr<const IDocumentLayer> docLayer(frontDocDB,layerNode->GetUID(),UseDefaultIID());
			if(docLayer)
				return LayerTreeUIDNodeID::Create(frontDocDB->GetRootUID(),kFalse);
			else
			{
				InterfacePtr<const IHierarchy> piHier(frontDocDB,layerNode->GetUID(),UseDefaultIID());
				if(piHier)
				{
					InterfacePtr<const IHierarchy> parentHier(piHier->QueryParent());
					ASSERT_MSG(parentHier != nil,"No parent hierarchy");
					InterfacePtr<const IPageItemAdapter> iPageItemAdapter(parentHier,UseDefaultIID());
					if(iPageItemAdapter)
					{
						// for inlines, we show the spline containing the MCTF to be their parent.
						InterfacePtr<const ITextFrameColumn> textCol(iPageItemAdapter->QueryTextFrame());		
						if(textCol)
						{
							InterfacePtr<const IMultiColumnTextFrame> mctf(textCol->QueryMultiColumnTextFrame	());
							InterfacePtr<const IHierarchy> mctfHier(mctf,UseDefaultIID());
							InterfacePtr<const IHierarchy> tfSplineHier(mctfHier->QueryParent());
							return LayerTreeUIDNodeID::Create(::GetUID(tfSplineHier),kFalse);
						}
					}
					else
					{
						InterfacePtr<const ISpreadLayer> spreadLayer(parentHier,UseDefaultIID());
						if(spreadLayer)
						{
							InterfacePtr<const IDocumentLayer> piDocLayer(spreadLayer->QueryDocLayer());
							return LayerTreeUIDNodeID::Create(::GetUID(piDocLayer),kTrue);
						}
						else
							return LayerTreeUIDNodeID::Create(::GetUID(parentHier),kFalse);
					}
				}
			}
		}
	}
	return kInvalidNodeID;
}


UIDList GetPlaceItemsForTextFrame(const IHierarchy* textFrameHier)
{
	IDataBase *db = ::GetDataBase(textFrameHier);
	InterfacePtr<const IGraphicFrameData> frameData(textFrameHier, UseDefaultIID());
	ASSERT_MSG(frameData->GetTextContentUID().IsValid(),"If this is a text frame, why doesn't it have a valid UID?");
	InterfacePtr<IMultiColumnTextFrame> mctf(db, frameData->GetTextContentUID(), UseDefaultIID());
	UIDList placeItemList(db);
	Utils<IFrameUtils>()->GetUIDListOfPlacedPageItem(mctf, kFalse, &placeItemList);
	return placeItemList;
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------
int32 LayerPanelTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(node);
//	TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetNumChildren called for node with UID %d\n",layerNode->GetUID().Get());

	IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	if(frontDocDB)
	{
		if(layerNode->GetUID() == frontDocDB->GetRootUID())
		{
			InterfacePtr<const ILayerList> layerList(frontDocDB,frontDocDB->GetRootUID(), UseDefaultIID());
			return  Utils<ILayerUtils>()->CountUILayers(layerList);
		}
		else
		{
			if(layerNode->IsLayerEntry())
			{
				InterfacePtr<const IDocumentLayer> docLayer(frontDocDB,layerNode->GetUID(),UseDefaultIID());
#ifdef DEBUG
				DebugClassUtilsBuffer classBuf;
				ASSERT_MSG(docLayer,FORMAT_ARGS("Failed to get IDocumentLayer for Layer UID %d, class %s",layerNode->GetUID().Get(),DebugClassUtils::GetIDName(&classBuf,frontDocDB->GetClass(layerNode->GetUID()))));
#endif
				InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
				if(layoutData)
				{
					UIDRef spreadRef = layoutData->GetSpreadRef();
					InterfacePtr<const ISpread> activeSpread(spreadRef,UseDefaultIID());
					InterfacePtr<const ISpreadLayer> spreadLayer(activeSpread->QueryLayer(docLayer));
					InterfacePtr<const IHierarchy> spreadLayerHier(spreadLayer,UseDefaultIID());
					//TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetNumChildren returning %d for layer node with UID %d\n",spreadLayerHier->GetChildCount(),layerNode->GetUID().Get());
					return spreadLayerHier->GetChildCount();
				}
			}
			else
			{
				InterfacePtr<const IHierarchy> piHier(frontDocDB,layerNode->GetUID(),UseDefaultIID());
//#ifdef DEBUG
//				DebugClassUtilsBuffer classBuf;
//				ASSERT_MSG(piHier,FORMAT_ARGS("Failed to get IHierarchy for UID %d, class %s",layerNode->GetUID().Get(),DebugClassUtils::GetIDName(&classBuf,frontDocDB->GetClass(layerNode->GetUID()))));
//#endif
				if(piHier)
				{
					//TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetNumChildren returning %d for page item node with UID %d\n",piHier->GetChildCount(),layerNode->GetUID().Get());
					if(Utils<IPageItemTypeUtils>()->IsTextFrame(piHier))
					{
						UIDList inlineList = GetPlaceItemsForTextFrame(piHier);
						return inlineList.Length();
					}
					else
					{
						 if(Utils<IPageItemTypeUtils>()->IsGraphicFrame(piHier) && piHier->GetChildCount() == 1)
						 {
							InterfacePtr<const IHierarchy> childHier(piHier->QueryChild(0));
							if(Utils<IPageItemTypeUtils>()->IsGraphic(childHier) || Utils<IPageItemTypeUtils>()->IsMedia(childHier) )
								return 0;
						 }
						return piHier->GetChildCount();
					}
				}
			}
		}
	}
	//TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetNumChildren returning 0 for node with UID %d\n",layerNode->GetUID().Get());
	return 0;
}

NodeID_rv LayerPanelTreeViewAdapter::GetNthChild(const NodeID& parentTreeNode, const int32& nth) const
{
	TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(parentTreeNode);
	//TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetNthChild called for node with UID %d, nth %d\n",layerNode->GetUID().Get(), nth);
	IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	if(frontDocDB)
	{
		if(layerNode->GetUID() == frontDocDB->GetRootUID())
		{
			InterfacePtr<const ILayerList> layerList(frontDocDB,frontDocDB->GetRootUID(), UseDefaultIID());
			InterfacePtr<const IDocumentLayer> thisUILayer(Utils<ILayerUIUtils>()->QueryNthUILayer(layerList,nth));
			if(thisUILayer)
			{
				return LayerTreeUIDNodeID::Create(::GetUID(thisUILayer),kTrue);
			}
		}
		else
		{
			InterfacePtr<const IDocumentLayer> docLayer(frontDocDB,layerNode->GetUID(),UseDefaultIID());
			if(docLayer)
			{
				InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
				if(layoutData)
				{
					UIDRef spreadRef = layoutData->GetSpreadRef();
					InterfacePtr<const ISpread> activeSpread(spreadRef,UseDefaultIID());
					InterfacePtr<const ISpreadLayer> spreadLayer(activeSpread->QueryLayer(docLayer));
					InterfacePtr<const IHierarchy> spreadLayerHier(spreadLayer,UseDefaultIID());
					return LayerTreeUIDNodeID::Create(spreadLayerHier->GetChildUID(spreadLayerHier->GetChildCount() - nth - 1),kFalse);
				}
			}
			else
			{
				InterfacePtr<const IHierarchy> piHier(frontDocDB,layerNode->GetUID(),UseDefaultIID());
				if(Utils<IPageItemTypeUtils>()->IsTextFrame(piHier))
				{
					// deal with owned items.
					UIDList inlineList = GetPlaceItemsForTextFrame(piHier);
					return LayerTreeUIDNodeID::Create(inlineList[nth],kFalse);
				}				
				return LayerTreeUIDNodeID::Create(piHier->GetChildUID(piHier->GetChildCount() - nth - 1),kFalse);
			}
		}
		
	}
	return LayerTreeUIDNodeID::Create(kInvalidUID,kFalse);
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 LayerPanelTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<const LayerTreeUIDNodeID>	parentNode(parent);
	TreeNodePtr<const LayerTreeUIDNodeID>	childNode(child);
	//TRACEFLOW("LayerPanel","LayerPanelTreeViewAdapter::GetChildIndex called for parent UID %d, child UID %d\n",parentNode->GetUID().Get(),childNode->GetUID().Get());
	IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	if(frontDocDB)
	{
		if(parentNode->GetUID() == frontDocDB->GetRootUID())
		{
			InterfacePtr<const ILayerList> layerList(frontDocDB,frontDocDB->GetRootUID(), UseDefaultIID());
			return Utils<ILayerUIUtils>()->GetUILayerIndex(layerList,childNode->GetUID());
		}
		else
		{
			InterfacePtr<const IDocumentLayer> docLayer(frontDocDB,parentNode->GetUID(),UseDefaultIID());
			if(docLayer)
			{
				InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
				if(layoutData)
				{
					UIDRef spreadRef = layoutData->GetSpreadRef();
					InterfacePtr<const ISpread> activeSpread(spreadRef,UseDefaultIID());
					InterfacePtr<const ISpreadLayer> spreadLayer(activeSpread->QueryLayer(docLayer));
					InterfacePtr<const IHierarchy> spreadLayerHier(spreadLayer,UseDefaultIID());
					InterfacePtr<const IHierarchy> childHier(frontDocDB,childNode->GetUID(),UseDefaultIID());
					int32 childCount = spreadLayerHier->GetChildCount() ;
					int32 childIndex = spreadLayerHier->GetChildIndex(childHier) ;
					if ( childCount > 0 && childIndex >= 0 )	//#2307207
						return childCount - childIndex - 1 ;
				}
			}
			else
			{
				InterfacePtr<const IHierarchy> piHier(frontDocDB,parentNode->GetUID(),UseDefaultIID());
				if (piHier)
				{
					if(Utils<IPageItemTypeUtils>()->IsTextFrame(piHier))
					{
						// deal with owned items.
						UIDList inlineList = GetPlaceItemsForTextFrame(piHier);
						for(int childIndex = 0; childIndex < inlineList.Length(); ++childIndex)
						{
							if(inlineList[childIndex] == childNode->GetUID())
								return childIndex;
						}
					}
					
					InterfacePtr<const IHierarchy> childHier(frontDocDB,childNode->GetUID(),UseDefaultIID());
					return piHier->GetChildCount() - piHier->GetChildIndex(childHier) - 1;
				}
			}
		}
	}

	return -1;
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------
NodeID_rv LayerPanelTreeViewAdapter::GetGenericNodeID() const
{
	return LayerTreeUIDNodeID::Create( kInvalidUID,kFalse );	
}

