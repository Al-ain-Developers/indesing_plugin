//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CTreeViewWidgetMgr.h $
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

#pragma once
#ifndef __CTreeViewWidgetMgr__
#define __CTreeViewWidgetMgr__

#include <map>

#include "ITreeViewWidgetMgr.h"
#include "IPanelControlData.h"
#include "HelperInterface.h"
#include "NodeID.h"
#include "PMPoint.h"
#include "TreeViewDefs.h"
#include "RsrcSpec.h"

const int32 kDefaultIndent = 20;

#pragma export on


//----------------------------------------------------------------------------------------
// class CTreeViewWidgetMgr 
//----------------------------------------------------------------------------------------
/** Base class for clients implementing ITreeViewwidgetMgr interfaces.  This base class
	handles a lot of the work for you.  You can use this base class and override some of
	the protected methods instead of implementing the ITreeViewWidgetMgr calls.  Make sure to 
	use the constuctor with optionFlags.  Pay particular attention to ApplyIndentToWidget() documentation
	for info on how indenting is handled by this class.  Also make sure to read RegisterStyles()
*/
class DV_WIDGET_DECL CTreeViewWidgetMgr : public ITreeViewWidgetMgr
{
public:
	/** THIS CONSTRUCTOR IS DEPRECATED.  For InDesign 4.0 and later, use the contructor with optionFlags!
	*/
	CTreeViewWidgetMgr(IPMUnknown *boss);

	/** 
		@param boss
		@param optionFlags pass kList if this tree is a simple list with no hierarchy.  
		Pass kHierarchical for a tree with a hierarchy
	*/
	CTreeViewWidgetMgr(IPMUnknown *boss, int32 optionFlags);
	/** 
		destructor
	*/
	virtual ~CTreeViewWidgetMgr();
	
	/** Change data in your nodeWidget(widget) to reflect the node passed in.
		@param node specifies node to be rendered
		@param widget this is where the data from the node should be rendered
		@param message if you call an ITreeViewMgr method with a message, that message will be passes back 
		to you in this parameter.  For instance, if it is expensive to update the text, but not the icon.  
		You could pass yourself a kMyIconChanged message in ITreeViewMgr::NodeChanged() and 
		then only update the icon in ApplyDataToWidget() if message=kMyIconChanged
		@return kTrue if you were successful in applying data, kFalse if unsuccessful.  If kFalse is 
		returned, the TreeViewMgr will ask you to create a new widget for this node with CreateWidgetForNode() 
		and then ask to apply data again
	*/
	virtual	bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message = 0 ) const;

	/**
		Returns desired height in pixels of widget rendering given node.
		@param node
		@param return desired height in pixels of widget rendering given node
	*/
	virtual PMReal				GetNodeWidgetHeight(const NodeID& node) const;

	/**
		Returns desired width in pixels of widget rendering given node.
		@param node
		@return desired width in pixels of widget rendering given node
	*/
	virtual PMReal				GetNodeWidgetWidth(const NodeID& node) const;

	/**
		Returns indent in pixels for widget rendering given node.
		@param node
		@return indent in pixels for widget rendering given node
	*/
	virtual	PMReal				GetIndentForNode(const NodeID& node) const;

	/** Create the widget, but don't change the widget-data to match the node; that should be 
		done in ApplyNodeIDToWidget
		@param node
		@return reference to IControlView interface on newly created widget boss object
	*/
	virtual	IControlView* 		CreateWidgetForNode(const NodeID& node) const;
	
	/** A tree view may have different looks depending on state.  The most commonly used example of this 
	is the list palettes that can be viewed with small palette rows as opposdd to the normal sized palette 
	rows.  SetStyle is called by the client code at it's discretion.  The style identifier is just a 
	unique way for the client to refer to it's different styles and is fully defined by the client, 
	although 2 standard styleIdentifiers have been defined(kLargePaletteRowsTreeStyle & kSmallPaletteRowsTreeStyle)
	for convenience.
	The most common use of tree styles is palettes with Small Palette Rows.  These Tree Views will show one 
	node widget when in the small rows state and a different in the large rows state.  They use the style 
	identifiers kLargePaletteRowsTreeStyle & kSmallPaletteRowsTreeStyle to set the current style.
	This implementation does not work well with multiple widget types in a tree at one time.  To do that, override
	ITreeViewWidgetMgr interfaces directly.
	@param styleIdentifier client defined identifier for a particular style.  Or use predefined styleIDs 
	*/
	virtual void				SetStyle(int32 styleIdentifier);

	/**
		Returns current style identifer used by the interface.  See SetStyle.
	*/
	virtual int32				GetStyle() const;

	/**  Determine a widget id that corresponds to the type of widget that should be 
		used to render data from the given node.
		@param node specifies the node of interest
		@return a widget ID for a widget type that can be used to render this node's data
	*/
	virtual WidgetID 			GetWidgetTypeForNode(const NodeID& node) const;
	
	/**
		Only TreeViews that need to do something prior to the tree deleting a widget will
		need to override this method.  
		This method is called from the tree view manaager before it deletes a widget. 
		For example, this provides the widget manager client to disconnect
		any child widgets it wants to continue to manage.
	*/
	virtual void				PreDeleteWidget( IControlView* widget );

protected:
	/**
		Most TreeViews will override this method.  This method is called from ApplyNodeIDToWidget() 
		to apply the Node specific data to the widgets within the main node widget.  Typically, the 
		name of the node and icon for the node are applied to a Text widget and an icon widget.  
		When overriding this method, the base class version is not typically called.
		@param	node the node whose data you want applied to the given widget
		@param	widgetList This is the IPanelControlData of the Tree node widget.  The Tree node widget 
		typically contains subwidgets which are changed based on the specific data for the given node.
		@param	message if you call an ITreeViewMgr method with a message, that message will be passed 
		back to you in this parameter.  For instance, if it is expensive to update the text, but not the 
		icon.  You could pass yourself a kMyIconChanged message in ITreeViewMgr::NodeChanged() and 
		then only update the icon in ApplyDataToWidget() if message=kMyIconChanged
		@return	bool16 kTrue if you were successful in applying data, kFalse if unsuccessful.  
		If kFalse is returned, the TreeViewMgr will ask you to create a new widget for this node 
		with CreateWidgetForNode() and then ask to apply data again
	*/
	virtual bool16				ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message = 0 ) const;


	/**
		This method is where you specify the widget that should be used for each of the Tree Styles 
		you support.  If you only support 1 Tree Style, then you need only Register one style in from 
		this method.  This method is automatically called when it is time to register your styles.  
		Inside you should call RegisterStyleWidget() to asssociate a widget with a style.

		If your tree can contain different widgets depending on the NodeID, then you should use 
		override CreateWidgetForNode instead of this RegisterStyles() method

		This default implementation registers the standard Tree widgets for large and small palette rows.  If you aren't using the
		standard widgets, then override this and DON'T CALL the base class method.
	*/
	virtual void				RegisterStyles();

	/**
		You may want to override this method to handle indent in your own way if the default way of handling indent doesn't work for you.
		By default, we get the indent for a node by recursively calling GetIndent to get the indent value.  We use binding to determine
		which subwidgets to move for indentation.  Only direct subwidgets of the node widget are moved.
		Subwidgets that are bound Left AND NOT bound Right, are NOT moved
		Subwidgets that are bound Right AND NOT bound Left, are NOT moved
		Subwidgets that are bound Left AND bound Right are resized
		Subwidgets that are NOT bound on Left OR Right, are moved
		@param	node node to indent
		@param	widgetList the IPanelControlData of the NodeWidget itself.
		@param	message if you call an ITreeViewMgr method with a message, that message will be passed 
		back to you in this parameter.  For instance, if it is expensive to update the text, but not the 
		icon.  You could pass yourself a kMyIconChanged message in ITreeViewMgr::NodeChanged() and 
		then only update the icon in ApplyDataToWidget() if message=kMyIconChanged
	*/
	virtual void				ApplyIndentToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message = 0 ) const;
	virtual PMReal				GetBaseIndentOffset(IControlView* styleWidget) const;

	/**
		Returns the current width of the TreeView.  Most often used when trying to determine how wide 
		to make a widget when the tree has no horizontal scrollbar.
		@return	PMReal current width in pixels of the TreeView
	*/
	virtual	PMReal				GetTreeViewWidth() const;

	// Level 6
	/**
		This will highlight the specified widget.  Called from ApplyNodeIDToWidget() when widget is hilited.
		@param	node nodeID of node to highlight
		@param	widget widget of the node that needs highlighting
		@param	message	if you call an ITreeViewMgr method with a message, that message will be 
		passed back to you in this parameter.  For instance, if it is expensive to update the text, 
		but not the icon.  You could pass yourself a kMyIconChanged message in ITreeViewMgr::NodeChanged() 
		and then only update the icon in ApplyDataToWidget() if message=kMyIconChanged
	*/
	virtual void				ApplyHighlightToWidget( const NodeID& node, IControlView* widget, int32 message = 0 ) const;

	/**
		Returns the indent for this node in pixels.  This is cumulative indent value, so if each 
		item in a tree is indented 20 pixels from its parent and this node has 2 levels of hierarchy 
		above it, this would return 60 pixels.  Typically not needed if you override ApplyDataToWidget,
		but is needed if you override ApplyNodeIDToWidget instead.
		@param	node nodeID to indent
		@return	PMReal total number of pixels that this node is indented
	*/
	virtual	PMReal				GetIndent(const NodeID& node) const;

	/**
		Registers a widgetRsrcID/PluginID with a particular style.  Common use is to override 
		RegisterStyles() and call this method for each style you wish to register.  Current style 
		will be used to create create widgets as needed in CreateWidgetForNode().  If you register styles, 
		you don't need to override CreatewidgetForNode().
		@param	style the styleID you are registering
		@param	widgetRsrcID Widget Resource ID to use when creating widgets for specified style
		@param	pluginID plugin ID to use when creating widgets for specified style
	*/
	virtual	void				RegisterStyleWidget(int32 style, RsrcID widgetRsrcID, PluginID pluginID);

	/**
		Helper method called from default implementation of ApplyNodeIDToWidget().  Given a Node Widget, 
		this will search for the expander widget and hide the widget if node specified has no children.  
		Requires expander widget to have WidgetID = kTreeNodeExpanderWidgetID.
		@param	node node representing this widget
		@param	widgetList IPanelControlData off the Node widget
		@param	message if you call an ITreeViewMgr method with a message, that message will be passed 
		back to you in this parameter.  For instance, if it is expensive to update the text, but not the icon.  
		You could pass yourself a kMyIconChanged message in ITreeViewMgr::NodeChanged() and 
		then only update the icon in ApplyDataToWidget() if message=kMyIconChanged
	*/
	virtual void				HideExpanderIfNotExpandable( const NodeID& node, IPanelControlData* widgetList, int32 message = 0 ) const;


	/**
		Helper method to search for the name widget and set its text value.
		@param	widgetList IPanelControlData off the Node widget
		@param	name new name for name widget
		@param	nameWidget widgetID of name widget.  Not necessary to specify if default ID of kTreeNodeNameWidgetID is used
	*/
	virtual void				SetNodeName( IPanelControlData* widgetList, const PMString& name, WidgetID nameWidget = kTreeNodeNameWidgetID ) const;

	/**
		Helper method to search for the icon widget and set its new icon value.
		@param	widgetList IPanelControlData off the Node widget
		@param	iconRsrc new icon resource id
		@param	pluginID of new icon resource
		@param	iconWidget widgetID of icon widget.  Not necessary to specify if default ID of kTreeNodeIconWidgetID is used
	*/
	virtual void				SetNodeIcon( IPanelControlData* widgetList, RsrcID iconRsrc, PluginID pluginID = 0, WidgetID iconWidget = kTreeNodeIconWidgetID ) const;

	typedef enum { kList = 0, kHierarchical = 1} Options; // second 16 bits reserved for PrivateOptions

	/**
		Returns whether the specified option flag has been set.
		@param	option which option 
		@return	bool16 kTrue if options is set, kFalse if not.
	*/
	virtual	bool16				IsOptionSet( Options option ) const;
	
private:
		
	virtual void				LazyRegisterStyles() const;
	virtual void 				InternalSetStyle(int32 styleIdentifier);

	typedef enum { kCTreeViewWidgetMgrV2 = 0x0100, kRootNodeDisplayed = 0x0200} PrivateOptions;
//	std::map<int32, std::pair<RsrcID, PluginID> >	fStyleWidgetTable;
	int32			fOptionFlags;
	std::map<int32, RsrcSpec >	fStyleWidgetTable;
	int32			fStyle;
	mutable PMPoint	fDefaultWidgetSize;
	WidgetID		fCurrentStyleWidgetID;
	RsrcSpec		fCurrentStyleRsrcSpec;
	PMReal			fBaseIndentOffset;
	
DECLARE_HELPER_METHODS()

protected:
	virtual void				SetSelectableDlgDrawNodeSeparatorOff(IControlView* widget) const;

};


#pragma export off

#endif
