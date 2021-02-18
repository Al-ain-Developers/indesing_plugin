//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/treeview/CTreeViewWidgetMgr.cpp $
//  
//  Owner: Matt Joss
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

#include "DV_VCWidgetHeaders.h"

#include "CTreeViewWidgetMgr.h"

#include "IPanelControlData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"
#include "ITreeAttributes.h"
#include "IWidgetParent.h"
#include "IWindow.h"
#include "ITreeViewMgr.h"
#include "DVTreeNodeControlView.h" 


#include "ILayoutUIUtils.h"
#include "widgetid.h"
#include "ListIndexNodeID.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "RsrcSpec.h"
#include "TreeViewDefs.h"
#include "IconRsrcDefs.h"
#include "DVUtilities.h" 
#include "IBoolData.h"

#include "IDVUINodeRef.h"

WIDGET_DECL NodeID kInvalidNodeID;

const PMPoint kInvalidSize(-kMaxInt16,-kMaxInt16);

DEFINE_HELPER_METHODS(CTreeViewWidgetMgr)

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr constructor
// THIS CONSTRUCTOR IS DEPRECATED.  For InDesign 4.0 and later, use the contructor with optionFlags!
//----------------------------------------------------------------------------------------
CTreeViewWidgetMgr::CTreeViewWidgetMgr(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss), fStyle(kNoTreeStyle), fCurrentStyleWidgetID(kInvalidWidgetID), fDefaultWidgetSize(kInvalidSize), fCurrentStyleRsrcSpec(0, 0), fOptionFlags(0)
{
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
CTreeViewWidgetMgr::CTreeViewWidgetMgr(IPMUnknown *boss, int32 optionFlags) :
	HELPER_METHODS_INIT(boss), fStyle(kInvalidTreeStyle), fCurrentStyleWidgetID(kInvalidWidgetID), fDefaultWidgetSize(kInvalidSize), fCurrentStyleRsrcSpec(0, 0), fOptionFlags(optionFlags | kCTreeViewWidgetMgrV2)
{
}


//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::~CTreeViewWidgetMgr 
//----------------------------------------------------------------------------------------
CTreeViewWidgetMgr::~CTreeViewWidgetMgr()
{
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::ApplyDataToWidget
// Most TreeViews will override this method.  This method is called from ApplyNodeIDToWidget() to apply the Node specific data
// to the widgets within the main node widget.  Typically, the name of the node and icon for the node are applied
// to a Text widget and an cion widget.  When overriding this method, the base class version is not typically called.
// - node - the node whose data you want applied to the given widget
// - widgetList - This is the IPanelControlData of the Tree node widget.  The Tree node widget typically contains subwidgets
//	which are changed based on the specific data for the given node.
//----------------------------------------------------------------------------------------
bool16 CTreeViewWidgetMgr::ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const
{	
	// As a default, we give a folder icon to anything that has children and a dot icon to those that have no children
	InterfacePtr<ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());
	if (adapter->GetNumChildren(node) == 0)
		SetNodeIcon( widgetList, kStandardTreeNodeChildWidgetIconRsrcID );
	else
		SetNodeIcon( widgetList, kGenericFolderIconID );

	
	TreeNodePtr<ListIndexNodeID>	listIndexNode(node);
	ASSERT_MSG(listIndexNode != nil, "CTreeViewWidgetMgr::ApplyDataToWidget() - Your Tree uses a nodeID other than ListIndexNodeID, so you must override CTreeViewWidgetMgr::ApplyDataToWidget()");
	if (listIndexNode)
	{
		PMString indexName;
		indexName.AppendNumber( listIndexNode->GetIndex() );
		SetNodeName( widgetList, indexName );
	}

	return kTrue;
}

	/**
		Only TreeViews that insert external views into the tree widget will override this method.  
		This method is called from the tree view manaager before it deletes a widget. 
		This provides the widget manager clien to override this method and disconnect
		any child widgets it wants to continue to manage 
	*/
void CTreeViewWidgetMgr::PreDeleteWidget( IControlView* widget )
{
// we do nothing by default
}




//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::RegisterStyles
//	This method is where you specify the widget that should be used for each of the Tree Styles you support.  If you only
//	support 1 Tree Style, then you need only Register one style in from this method.  This method is automatically called
//	when it is time to register your styles.  Inside you should call RegisterStyleWidget() to asssociate a widget with a style.
//
//	If your tree can contain different widgets depending on the NodeID, then you should use override CreateWidgetForNode
//	instead of this RegisterStyles() method
//
//	This default implementation registers the standard Tree widgets for large and small palette rows.  If you aren't using the
//	standard widgets, then override this and don't call the base class method.
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::RegisterStyles()
{
	RegisterStyleWidget( kLargePaletteRowsTreeStyle, kStandardLargeTreeNodeRsrcID, kWidgetsPluginID);
	RegisterStyleWidget( kSmallPaletteRowsTreeStyle, kStandardSmallTreeNodeRsrcID, kWidgetsPluginID);
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetNodeWidgetWidth
//	For the given node, what is the width of the widget.  This is only relevant for TreeViews with a horizontal
//	scroll bar.  If you have a horizontal scroll bar, this refers to the entire width of the widget including indent
//	and is used to determine the width of the tree view for scrolling.
//	The default implementation returns the width of template widget used when calling RegisterStyle()
//	if you override this method, there is no reason to call the base class method
//----------------------------------------------------------------------------------------
PMReal CTreeViewWidgetMgr::GetNodeWidgetWidth(const NodeID& node) const
{
	//NOTE:  If your widgets are not all the same size, you'll need to override this method
	
	if (fStyle == kInvalidTreeStyle)
		LazyRegisterStyles();

	//The first time, we create a widget and get it's size.  After that, we just use it's size
	if (fDefaultWidgetSize == kInvalidSize)
	{
		InterfacePtr<IControlView>	widget(this->CreateWidgetForNode(node));
		if (widget)
		{
			fDefaultWidgetSize = widget->GetFrame().Dimensions();
			Utils<IWidgetUtils>()->DeleteWidgetAndChildren(widget); //cleanup UIDs
		}
	}
	
	return fDefaultWidgetSize.X();
	
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetNodeWidgetHeight
//----------------------------------------------------------------------------------------
PMReal CTreeViewWidgetMgr::GetNodeWidgetHeight(const NodeID& node) const
{
	//NOTE:  If your widgets are not all the same size, you'll need to override this method

	if (fStyle == kInvalidTreeStyle)
		LazyRegisterStyles();
	
	//The first time, we create a widget and get it's size.  After that, we just use it's size
	if (fDefaultWidgetSize == kInvalidSize)
	{
		InterfacePtr<IControlView>	widget(this->CreateWidgetForNode(node));
		if (widget)
		{
			fDefaultWidgetSize = widget->GetFrame().Dimensions();
			Utils<IWidgetUtils>()->DeleteWidgetAndChildren(widget); //cleanup UIDs
		}
	}
	
	return fDefaultWidgetSize.Y();
	
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::ApplyNodeIDToWidget
//	This is the main entry point for Applying node data to a widget.  For the most control, override this method
//	and handle applying all node data on your own.  
//----------------------------------------------------------------------------------------
bool16 CTreeViewWidgetMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const
{	
	ApplyHighlightToWidget( node, widget, message );

	// Only go into here if using the new version of CTreeViewWidgetMgr that sets option flags
	if ( fOptionFlags & kCTreeViewWidgetMgrV2 )
	{
		InterfacePtr<IPanelControlData>	widgetList(widget, UseDefaultIID());
		HideExpanderIfNotExpandable( node, widgetList, message );
		ApplyIndentToWidget( node, widgetList, message );
		
		return ApplyDataToWidget( node, widgetList, message );
	}
	return kTrue;
}


//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::ApplyIndentToWidget
//	You may want to override this method handle indent in your own way if the default way of handling indent doesn't work for you.
//	By default, we get the indent for a node by recursively calling GetIndent to get the indent value.  We use binding to determine
//	which subwidgets to move for indentation.  Only direct subwidgets of the node widget are moved.
//	Subwidgets that are bound Left AND NOT bound Right, are NOT moved
//	Subwidgets that are bound Right AND NOT bound Left, are NOT moved
//	Subwidgets that are bound Left AND bound Right are resized
//	Subwidgets that are NOT bound on Left OR Right, are moved
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::ApplyIndentToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message ) const
{	
	PMReal indent = this->GetIndent(node);
		
	PMReal previousOffset = kMaxInt32;
	for (int32 i = 0; i < widgetList->Length(); i++)
	{
		IControlView* childWidget = widgetList->GetWidget(i);
		FrameBinding binding = childWidget->GetFrameBinding();
		PMRect frame = childWidget->GetFrame();
		if  (binding & kBindLeft && binding & kBindRight)
		{
			if (previousOffset == kMaxInt32)
				previousOffset = frame.Left () - fBaseIndentOffset;
			PMReal left = frame.Left() + indent - previousOffset;
			frame.Left( left );
			childWidget->SetFrame(frame);
		} else if ( !(binding & kBindLeft || binding & kBindRight) )
		{
			if (previousOffset == kMaxInt32)
				previousOffset = frame.Left () - fBaseIndentOffset;
			if (LocaleSetting::GetLocale().IsRightToLeftUI())
			{
				InterfacePtr<IWidgetParent>    iParentHolder (childWidget, IID_IWIDGETPARENT);     
				InterfacePtr<IControlView>    parentWidget ((IControlView*)iParentHolder->QueryParentFor(IID_ICONTROLVIEW)); 
				previousOffset = ( parentWidget->GetFrame().Width() - frame.Right () ) - fBaseIndentOffset;
				frame.MoveRel(- (indent - previousOffset), 0);
			}
			else
				frame.MoveRel(indent - previousOffset, 0);
			childWidget->SetFrame(frame);
		}
		
	}
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::SetStyle
//	A tree view may have different looks depending on state.  The most commonly used example of this is the list palettes
//	that can be viewed with small palette rows as opposdd to the normal sized palette rows.  SetStyle is called by the client
//	code at it's discretion.  The style identifier is just a unique way for the client to refer to it's different styles and 
//	is fully defined by the client, although 2 standard styleIdentifiers have been defined(kLargePaletteRowsTreeStyle & kSmallPaletteRowsTreeStyle)
//	for convenience.
//
//	The most common use of tree styles is palettes with Small Palette Rows.  These Tree Views will show one node widget when in the
//	small rows state and a different in the large rows state.  They use the style identifiers kLargePaletteRowsTreeStyle & 
//	kSmallPaletteRowsTreeStyle to set the current style.
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::SetStyle(int32 styleIdentifier)
{
	InternalSetStyle(styleIdentifier);

	// When we explicitly call SetStyle() from client code, we want to ChangeRoot to clear
	// all existing widgets.  We don't want to call ChangeRoot when called
	// via RegisterStyles(), because that is called during ArrangeWidgets in the TreeViewMgr.
	InterfacePtr<ITreeViewMgr>	treeMgr(this, UseDefaultIID());
	treeMgr->ChangeRoot(); 
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::InternalSetStyle
// This is where the guts of setting the style is done.  This is separated out from the interface SetStyle call to avoid calling ChangeRoot
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::InternalSetStyle(int32 styleIdentifier)
{
	// We need to set fStyle here, so that any subsequent checks to see if we need to RegisterStyles() will fail
	fStyle = styleIdentifier;


	std::map<int32, RsrcSpec>::iterator cur = fStyleWidgetTable.find( styleIdentifier );
	ASSERT_MSG(cur != fStyleWidgetTable.end(), "styleIdentifier CTreeViewWidgetMgr::InternalSetStyle() was not registered with RegisterStyleWidget(...).  Either register the style or don't call CTreeViewWidgetMgr::SetStyle(...)");
	if (cur != fStyleWidgetTable.end())
	{
		fCurrentStyleRsrcSpec = cur->second;
		
		InterfacePtr<IControlView>	widget(this->CreateWidgetForNode(kInvalidNodeID));
		ASSERT_MSG(widget != nil, "CTreeViewWidgetMgr::InternalSetStyle() - Call to CreateWidgetForNode(kInvalidNodeID) returned nil.  It should return a generic node, or you should override SetStyle()");
		if (widget)
		{
			fCurrentStyleWidgetID = widget->GetWidgetID();

			fBaseIndentOffset = GetBaseIndentOffset(widget);
			
			int16 existingWidgetHeight = ::ToInt16( fDefaultWidgetSize.Y() );
			fDefaultWidgetSize = widget->GetFrame().Dimensions();

			// If the scroll bar button increment is the same as the current widget size, update the scroll bar button increment
			// to match the new size
			InterfacePtr<ITreeAttributes> 	treeattributes(this, UseDefaultIID());	
			if (existingWidgetHeight == treeattributes->GetScrollButtonIncrement( ITreeAttributes::kVerticalScrollBar ))
			{
				int16 thumbScrollIncrement = treeattributes->GetThumbScrollIncrement( ITreeAttributes::kVerticalScrollBar );
				if ( thumbScrollIncrement == treeattributes->GetScrollButtonIncrement( ITreeAttributes::kVerticalScrollBar ) )	
					thumbScrollIncrement = ::ToInt16( fDefaultWidgetSize.Y() );
					
				treeattributes->SetScrollAmount( ITreeAttributes::kVerticalScrollBar, ::ToInt16(fDefaultWidgetSize.Y()), thumbScrollIncrement );
			}
			
			// Save off the RootNodeDisplayed setting
			if (treeattributes->IsRootNodeDisplayed())
				fOptionFlags |= kRootNodeDisplayed;
			else
				fOptionFlags &= ~kRootNodeDisplayed;
				
			Utils<IWidgetUtils>()->DeleteWidgetAndChildren(widget); //cleanup UIDs

			dv_utils::TriggerConstrainDimensionForTreeWidget(this);
		}
	}

}


//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetStyle
// This returns the current TreeView style.  See SetStyle for more info on TreeView Styles
//----------------------------------------------------------------------------------------
int32 CTreeViewWidgetMgr::GetStyle() const
{	
	if (fStyle == kInvalidTreeStyle)
		LazyRegisterStyles();
		
	return fStyle; 
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetBaseIndentOffset
//----------------------------------------------------------------------------------------
PMReal CTreeViewWidgetMgr::GetBaseIndentOffset(IControlView* styleWidget) const
{	
	InterfacePtr<IPanelControlData>	panelData(styleWidget, UseDefaultIID());
	if (panelData)
	{		
		for (int32 i = 0; i < panelData->Length(); i++)
		{
			IControlView* childWidget = panelData->GetWidget(i);
			FrameBinding binding = childWidget->GetFrameBinding();
			if ( (binding & kBindLeft && binding & kBindRight) || !(binding & kBindLeft || binding & kBindRight) )
			{
				return childWidget->GetFrame().Left();
			}
		}
	}
	return 0; 
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::RegisterStyleWidget
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::RegisterStyleWidget( int32 treeStyle,  RsrcID widgetRsrcID, PluginID pluginID)
{
	fStyleWidgetTable.insert( std::make_pair(treeStyle, RsrcSpec(LocaleSetting::GetLocale(),pluginID, kViewRsrcType, widgetRsrcID)) );

	// By default, we set the initial Style to the first style that is registered.
	if (fStyleWidgetTable.size() == 1)
		this->InternalSetStyle(treeStyle);
}


//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::HideExpanderIfNotExpandable
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::HideExpanderIfNotExpandable( const NodeID& node, IPanelControlData* widgetList, int32 message ) const
{	
	IControlView* expander = widgetList->FindWidget(kTreeNodeExpanderWidgetID);
	if (expander)
	{	
		InterfacePtr<ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());
		int32 numChildren = adapter->GetNumChildren(node);

		if (numChildren == 0)
			expander->HideView();
		else
			expander->ShowView();
	}
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::ApplyHighlightToWidget
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::ApplyHighlightToWidget( const NodeID& node, IControlView* widget, int32 message ) const
{	
	//The default is to Hilite selected items and unhilite non-selected items
	InterfacePtr<const ITreeViewController>	forSelection(this, UseDefaultIID());
	if ( forSelection->IsSelected( node ) )
		widget->Hilite();
	else
		widget->Unhilite();
}


//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::SetNodeName
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::SetNodeName( IPanelControlData* widgetList, const PMString& name, WidgetID nameWidget ) const
{	
	IControlView* textWidget = widgetList->FindWidget( nameWidget );
	ASSERT_MSG( textWidget != nil, "Calling CTreeViewWidgetMgr::SetNodeName() will only work if your name widget has WidgetID of kTreeNodeNameWidgetID");
	InterfacePtr<ITextControlData>	textData(textWidget, UseDefaultIID());
	if (textData)
	{
		PMString nonConst(name);
		nonConst.SetTranslatable(kFalse);
		textData->SetString( nonConst );
	}
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::SetNodeIcon
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::SetNodeIcon( IPanelControlData* widgetList, RsrcID iconRsrc, PluginID pluginID, WidgetID iconWidget ) const
{	
	IControlView* icon = widgetList->FindWidget(iconWidget);
	//The following assert won't be valid since user can pass the iconWidget as kInvalidWidgetID and 
	//don't want to show the icon in their tree node.
	//ASSERT_MSG( icon != nil, "Calling CTreeViewWidgetMgr::SetNodeIcon() will only work if your name widget has WidgetID of kTreeNodeIconWidgetID");
	if (icon)
	{
		if (pluginID != 0)
			icon->SetRsrcPluginID( pluginID );
		icon->SetRsrcID( iconRsrc );
	}
}


//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetIndentForNode() const
//----------------------------------------------------------------------------------------
PMReal CTreeViewWidgetMgr::GetIndentForNode(const NodeID& node) const
{
	if ( IsOptionSet(kHierarchical) )
		return kDefaultIndent;
		
	return 0;
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetIndent
//----------------------------------------------------------------------------------------
PMReal CTreeViewWidgetMgr::GetIndent(const NodeID& node) const
{
	PMReal indent = 0;
	InterfacePtr<const ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());
	NodeID currentNode = node;
	InterfacePtr<const ITreeViewWidgetMgr>	widgetMgr(this, UseDefaultIID());
	
	//We automatically skip the root node so that derived classes don't have to special case
	//the root node and since there is no reason for the root node to have an indent
	NodeID rootNode = adapter->GetRootNode();
	bool16 isRootNode = currentNode == rootNode;
	while ( currentNode.IsValid() && !isRootNode )
	{
		PMReal nodeIndent = widgetMgr->GetIndentForNode(currentNode);	
		currentNode = adapter->GetParentNode(currentNode);
		
		// If the root node is not displayed, we don't want it's children to have an indent
		isRootNode = currentNode == rootNode;
		if ( isRootNode && !(fOptionFlags & kRootNodeDisplayed))
			return indent;
		
		indent += nodeIndent;	
	}

	return indent;
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetTreeViewWidth
//----------------------------------------------------------------------------------------
PMReal CTreeViewWidgetMgr::GetTreeViewWidth() const
{
	InterfacePtr<const IPanelControlData>	myWidgets(this, UseDefaultIID());
	IControlView* treeScrollerView = myWidgets->FindWidget( kTreeScrollerWidgetID );
	return treeScrollerView->GetFrame().Width();
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------
IControlView* CTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
	if (fStyle == kInvalidTreeStyle)
		LazyRegisterStyles();

	ASSERT_MSG( fCurrentStyleRsrcSpec.GetPluginID() != 0, "CTreeViewWidgetMgr::CreateWidgetForNode() - Style PluginID is invalid, please use CTreeViewWidgetMgr constructor with 'optionFlags' parameter");
	IControlView*	view = ::CreateObject2<IControlView>(::GetDataBase(this), fCurrentStyleRsrcSpec);
			
	ASSERT_MSG(view != nil, FORMAT_ARGS("CTreeViewWidgetMgr::CreateWidgetForNode() - Could not create widget with PluginID=%ld, RsrcID=%ld.  Did you forget to add the resource?"));
	return view;
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------
WidgetID CTreeViewWidgetMgr::GetWidgetTypeForNode(const NodeID& node) const
{	
	if (fStyle == kInvalidTreeStyle)
		LazyRegisterStyles();
	
	return fCurrentStyleWidgetID;
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::IsOptionSet
//----------------------------------------------------------------------------------------
bool16 CTreeViewWidgetMgr::IsOptionSet( CTreeViewWidgetMgr::Options option ) const
{	
	return option & fOptionFlags;
}

//----------------------------------------------------------------------------------------
// CTreeViewWidgetMgr::LazyRegisterStyles
//----------------------------------------------------------------------------------------
void CTreeViewWidgetMgr::LazyRegisterStyles() const
{
	// RegisterStyles isn't really const, but because we want to use lazy initialization(Regsister when we need them) to Register our styles, we may end up
	// calling it from a const method, so we cast out the const here
	CTreeViewWidgetMgr* nonConst = const_cast<CTreeViewWidgetMgr*>(this);
	
	nonConst->RegisterStyles();
}

void CTreeViewWidgetMgr::SetSelectableDlgDrawNodeSeparatorOff(IControlView* widget)const
{
	InterfacePtr<IBoolData> drawNodeSeparator(this, IID_IDRAWNODESEPARATOR);
	if(drawNodeSeparator && drawNodeSeparator->GetBool() == kFalse)
		static_cast<DVTreeNodeControlView*>(widget)->SetDrawNodeSeparatorOnOff(kFalse);
}
