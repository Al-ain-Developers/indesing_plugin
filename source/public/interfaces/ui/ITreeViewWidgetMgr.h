//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeViewWidgetMgr.h $
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
#ifndef __ITreeViewWidgetMgr__
#define __ITreeViewWidgetMgr__

#include "IPMUnknown.h"
#include "widgetid.h"
#include "NodeID.h"
#include "PMPoint.h"
#include "TreeViewDefs.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IControlView;

//----------------------------------------------------------------------------------------
// ITreeViewWidgetMgr
//----------------------------------------------------------------------------------------
/** Interface responsible for creating the tree-view control widgets and applying
	node data to the widget.

	Should be implemented by client code wishing to use a tree-view widget.
*/
class ITreeViewWidgetMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREEVIEWWIDGETMGR };
	
	/**@name Widget Factory and reuse */
	//@{

	/** Create the widget, but don't change the widget-data to match the node.  That should be handled in ApplyNodeIDToWidget
		@param node
		@return reference to IControlView interface on newly created widget boss object
	*/
	virtual	IControlView*	CreateWidgetForNode(const NodeID& node) const = 0;

	/**  Determine a widget id that corresponds to the type of widget that should be
		used to render data from the given node
		@param node specifies the node of interest
		@return a widget ID for a widget type that can be used to render this node's data
	*/
	virtual	WidgetID		GetWidgetTypeForNode(const NodeID& node) const = 0;

	/** Change data in your nodeWidget(widget) to reflect the node passed in.
		@param node specifies node to be rendered
		@param widget this is where the data from the node should be rendered
		@param message if you call an ITreeViewMgr method with a message, that message will be passes back to you in this parameter.  For instance, if it is
					expensive to update the text, but not the icon.  You could pass yourself a kMyIconChanged message in ITreeViewMgr::NodeChanged() and 
					then only update the icon in ApplyDataToWidget() if message=kMyIconChanged
		@return kTrue if you were successful in applying data, kFalse if unsuccessful.  If kFalse is returned, the TreeViewMgr will ask
				you to create a new widget for this node with CreateWidgetForNode() and then ask to apply data again
	*/
	virtual	bool16			ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message = 0 ) const = 0;
	
	/**
		Only TreeViews that need to do something prior to the tree deleting a widget will
		need to override this method.  
		This method is called from the tree view manaager before it deletes a widget. 
		For example, this provides the widget manager client to disconnect
		any child widgets it wants to continue to manage.
		@param widget this is the widget that is being deleted
	*/
	virtual void				PreDeleteWidget( IControlView* widget ) = 0;
	//@}


	/**@name  Widget placement */
	//@{

	/**
		@param node
		@param return desired height in pixels of widget rendering given node
	*/
	virtual PMReal			GetNodeWidgetHeight(const NodeID& node) const = 0;

	/**
		@param node
		@return desired width in pixels of widget rendering given node
	*/
	virtual PMReal			GetNodeWidgetWidth(const NodeID& node) const = 0;

	/**
		@param node
		@return indent in pixels for widget rendering given node
	*/
	virtual	PMReal			GetIndentForNode(const NodeID& node) const = 0;
	//@}

	/**@name  Widget Style - The tree view may have different looks, i.e. Large vs. Small palette rows */
	//@{
	/**  Set a style for the TreeView.  These are essentially client defined and can be used however you like.  This
		method is not called by the Tree Architecture, but can be called by a given tree implementaion to change the look of the tree.
		@param styleIdentifier this is a client defined number that arbitrarily identifies a style.  For you convenience, 2 standard
		styles identifiers have been provided, kSmallPaletteRowsTreeStyle and kLargePaletteRowsTreeStyle
	*/
	virtual void			SetStyle(int32 styleIdentifier) = 0;

	/**
		@return arbitrary style identifer used by the interface.  See SetStyle
	*/
	virtual int32			GetStyle() const = 0;
	//@}



};	

#endif // __ITreeViewMgr__
