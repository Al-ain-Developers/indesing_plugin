//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUITVWidgetMgr.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IControlView.h"
#include "IImportProvider.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "ITreeViewHierarchyAdapter.h"

// General includes:
#include "CTreeViewWidgetMgr.h"
#include "CreateObject.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SysControlIds.h"

// Project includes:
#include "DataUpdaterUIID.h"
#include "DataUpdaterUINodeID.h"

/**
	Implements ITreeViewWidgetMgr, providing methods to create and describe the widgets for 
	nodes in the tree. This interface is similar to a widget factory in that this is where 
	you will create widgets for the nodes in the tree.
	
	For further reading on ITreeViewWidgetMgr interface, see the Widgets chapter
	of the User Interface technote.

	
	@ingroup xmldataupdaterui

*/

class DataUpdaterUITVWidgetMgr: public CTreeViewWidgetMgr
{
public:
	/**
		Constructor
		@param boss object on which this interface is being aggregated
	*/	
	DataUpdaterUITVWidgetMgr(IPMUnknown* boss);

	/**
		Destructor
	*/	
	virtual ~DataUpdaterUITVWidgetMgr() {}

	/** Create instance of the widget that represents given node in the tree.
		@param node [IN] specifies node of interest
		@return return reference to a newly instantiated object that is suitable for this node
	*/	
	virtual	IControlView* CreateWidgetForNode(
		const NodeID& node) const;
	/**
		Retrieve ID of a widget that has the right appearance for the node
		that you're trying to display. Here we use the same widget types for all the nodes,
		but vary the appearance by showing or hiding the expander widget depending on the number
		of children associated with a node.
		@param node [IN] specifies node of interest
		@return the ID of a widget that has the correct appearance for the given node type
	*/	
	virtual	WidgetID GetWidgetTypeForNode(const NodeID& node) const;

	/** Determine how to render the given node to the specified control.
		Figure out how you're going to render it based on properties of the node
		such as whether is has children or not (don't show expander if no children, for instance).
		@param node [IN] refers to the node that we're trying to render
		@param widget [IN] the control into which this node's appearance is going to be rendered
		@param message [IN] specifies ???
		@return kTrue if the node has been rendered successfully, kFalse otherwise
	*/	
	virtual	bool16 ApplyNodeIDToWidget(
		const NodeID& node, 
		IControlView* widget, 
		int32 message = 0) const;

	/** Given a particular node, how far should it be indented? This method
		returns a value in pixels that is used to indent the displayed node 
		from the left edge of the tree-view control.
		@param node [IN] specifies node of interest
		@return an indent for this particular node from the left edge of tree-view
	*/
	virtual PMReal GetIndentForNode(const NodeID& node) const;

private:
	void indent(
		const NodeID& node, IControlView* widget, IControlView* staticTextWidget) const;
};	

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DataUpdaterUITVWidgetMgr, kDataUpdaterUITVWidgetMgrImpl)

/* Constructor
*/
DataUpdaterUITVWidgetMgr::DataUpdaterUITVWidgetMgr(IPMUnknown* boss) :
	CTreeViewWidgetMgr(boss)
{
}


/* CreateWidgetForNode
*/
IControlView* DataUpdaterUITVWidgetMgr::CreateWidgetForNode(
	const NodeID& node) const
{
	IControlView* retval= (IControlView*) ::CreateObject(
		::GetDataBase(this),
		RsrcSpec(LocaleSetting::GetLocale(), 
		kDataUpdaterUIPluginID, 
		kViewRsrcType, 
		kDataUpdaterUINodeWidgetRsrcID),
		IID_ICONTROLVIEW);

	ASSERT(retval);
	return retval;
}



/* GetWidgetTypeForNode
*/
WidgetID DataUpdaterUITVWidgetMgr::GetWidgetTypeForNode(
	const NodeID& node) const
{
	return kDataUpdaterUINodeWidgetId;
}


/* ApplyNodeIDToWidget
*/
bool16 DataUpdaterUITVWidgetMgr::ApplyNodeIDToWidget(
	const NodeID& node, IControlView* widget, int32 message) const
{
	CTreeViewWidgetMgr::ApplyNodeIDToWidget(node, widget);
	do
	{
		// If this node doesn't have any children, don't show expander Widget
		InterfacePtr<IPanelControlData> 
			panelControlData(widget, UseDefaultIID());
		ASSERT(panelControlData);
		if(panelControlData==nil) {
			break;
		}
		// Set expander widget to hidden state if this node has no kids
		IControlView* expanderWidget = panelControlData->FindWidget(kTreeNodeExpanderWidgetID);
		ASSERT(expanderWidget);
		if(expanderWidget == nil) {
			break;
		}
		InterfacePtr<const ITreeViewHierarchyAdapter>
			adapter(this, UseDefaultIID());
		ASSERT(adapter);
		if(adapter == nil) {
			break;
		}
		if (expanderWidget) {
			if (adapter->GetNumChildren(node) <= 0) {
				expanderWidget->HideView();
			}
			else {
				expanderWidget->ShowView();
			}
		}


		TreeNodePtr<DataUpdaterUINodeID> nodeID(node);
		ASSERT(nodeID);
		if(nodeID == nil) {
			break;
		}	
		PMString nodeValue =  nodeID->GetValue();

		IControlView* displayStringView = 
			panelControlData->FindWidget( kDataUpdaterUINodeNameWidgetID );
		ASSERT(displayStringView);
		if(displayStringView == nil) {
			break;
		}
		InterfacePtr<ITextControlData>
			textControlData( displayStringView, UseDefaultIID() );
		ASSERT(textControlData);
		if(textControlData== nil) {
			break;
		}
		
		PMString stringToDisplay(nodeValue);
		if(stringToDisplay.empty()) {
			stringToDisplay="Empty?";	
		}
		stringToDisplay.SetTranslatable( kFalse );
		textControlData->SetString(stringToDisplay);
		// Adjust indenting- this may be temporary
		this->indent( node, widget, displayStringView );
		
	} while(kFalse);

	return kTrue;
}


/* GetIndentForNode
*/
PMReal DataUpdaterUITVWidgetMgr::GetIndentForNode(const NodeID& node) const
{
	return 10.0;
}


/* indent
*/
void DataUpdaterUITVWidgetMgr::indent(
	const NodeID& node, 
	IControlView* widget, 
	IControlView* staticTextWidget) const
{	
	do
	{
		ASSERT(widget);
		ASSERT(staticTextWidget);
		if(widget == nil || staticTextWidget == nil) {
			break;
		}
		const PMReal myIndent = this->GetIndent(node);	
		// adjust the size to fit the text 
		PMRect widgetFrame = widget->GetFrame();
		widgetFrame.Left() = myIndent;
		widget->SetFrame( widgetFrame );
		// Call window changed to force FittedStaticText to resize
		staticTextWidget->WindowChanged();
		PMRect staticTextFrame = staticTextWidget->GetFrame();
		staticTextFrame.Right( widgetFrame.Right() );
		// Don't at present take account of scroll bar dimension?
		staticTextWidget->SetFrame( staticTextFrame );
	} while(kFalse);
}



//	end, File: DataUpdaterUITVWidgetMgr.cpp
