//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/TreeViewEventHandler.h $
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
#ifndef __TreeViewEventHandler__
#define __TreeViewEventHandler__



#include "NodeID.h"
#include "IEvent.h"
#include "IEventHandler.h"
//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IEvent;

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------
#pragma export on

#include "DVHostedWidgetEH.h"

//========================================================================================
// CLASS TreeViewEventHandler
//========================================================================================
class WIDGET_DECL TreeViewEventHandler : public DVHostedWidgetEH
{
	typedef DVHostedWidgetEH inherited;
	
public:
	TreeViewEventHandler(IPMUnknown *boss);
	virtual ~TreeViewEventHandler();
	
	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);
	bool16	DeselectAll(IEvent* e);

	virtual bool16 MouseWheel(IEvent* e);
	virtual bool16 CanHaveKeyFocus() const;
	virtual void PostGetKeyFocus();
	virtual void PostGiveUpKeyFocus();

	virtual bool16 KeyDown(IEvent* e);
	virtual bool16 HandleLeftRightKey(IEvent* e, const VirtualKey& key);
	virtual bool16 HandleHomeKey(IEvent* e);
	virtual bool16 HandleEndKey(IEvent* e);


protected:
	void SelectNode( int32 direction, bool16 extendSelection );
	bool16 DoLButtonDn(IEvent* e, bool16 deselectAllIfNotHandled);
	bool16 DoRButtonDn(IEvent* e, bool16 deselectAllIfNotHandled);
	virtual bool16 IsNodeSelectable(const NodeID& toBeSelectedNode) const {return kTrue;}

	virtual bool16 HandleUpDownKey(IEvent* e, const VirtualKey& key);	
	virtual bool16 HandlePageUpDownKey(IEvent* e, const VirtualKey& key);
	
	virtual void    AdjustSelectedItems(NodeIDList& nodeList) { }
	void SelectFirstNode();
	void SelectLastNode();
	void InvalidateFocusTrim();
	int32 ScrollBarAdjustment( bool16 horizontalScrollBar );

	int32 fHScrollAdjustment;
	int32 fVScrollAdjustment;	

private:
	NodeID GetFirstVisibleAndSelectableNode();
};

#pragma export off

#endif
