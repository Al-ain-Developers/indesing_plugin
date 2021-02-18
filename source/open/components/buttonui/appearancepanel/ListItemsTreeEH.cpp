//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ListItemsTreeEH.cpp $
//  
//  Owner: Reena Agrawal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#include "ITreeViewMgr.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "CTreeViewController.h"
#include "TreeNodeTraverser.h"
#include "TreeViewEventHandler.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "IPalettePanelUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "widgetid.h"
#include "FormFieldUIID.h"


class ListItemsTreeEH : public TreeViewEventHandler
{
public:
    ListItemsTreeEH(IPMUnknown *boss) : TreeViewEventHandler(boss) {}
	virtual ~ListItemsTreeEH() {}

	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);
};

// =============================================================================
// *** ListItemsTreeEH impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE (ListItemsTreeEH, kListItemsTreeEHImpl)

// -----------------------------------------------------------------------------
//	Note: This is basically the same as the TreeViewEventHandler, except that it ensure
//	at least one is selected at all time.

bool16 ListItemsTreeEH::LButtonDn(IEvent* e)
{
	//	We deviate from the base class by passing deselectAllIfNotHandled = kFalse
	//	so that the current selection is not deselected if, for example, the node
	//	clicked is disabled.
	return this->DoLButtonDn(e, kFalse);
} // end LButtonDn()

// -----------------------------------------------------------------------------

bool16 ListItemsTreeEH::RButtonDn(IEvent* e)
{
	//	We deviate from the base class by passing deselectAllIfNotHandled = kFalse
	//	so that the current selection is not deselected if, for example, right-click
	//  in empty area below nodes.
	return this->DoRButtonDn(e, kFalse);
} // end RButtonDn()
