//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/TreeNodeEventHandler.h $
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
#ifndef __TreeNodeEventHandler__
#define __TreeNodeEventHandler__

#include "DVHostedWidgetEH.h"

#pragma export on

#include "IEvent.h"
#include "DVControlEventHandler.h"

class WIDGET_DECL TreeNodeEventHandler : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
public:
	TreeNodeEventHandler(IPMUnknown *boss);
	virtual ~TreeNodeEventHandler();

	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);

protected:
	virtual bool16 HandleLButtonDnBeforeSelectionProcessing(IEvent * e);
	virtual bool16 HandleLButtonDnAfterSelectionProcessing(IEvent * e);
	virtual bool16 HandleTreeNodeDragDrop(IEvent * e);

private:
	bool16 fPreChildEventHandling;
};

class WIDGET_DECL TreeNodePreChildEventHandler : public DVHostedWidgetEH
{
public:
	typedef DVHostedWidgetEH inherited;
	TreeNodePreChildEventHandler(IPMUnknown *boss);
	virtual ~TreeNodePreChildEventHandler();

	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);

protected:
	virtual bool16 HandleLButtonDnBeforeSelectionProcessing(IEvent * e);
	virtual bool16 HandleLButtonDnAfterSelectionProcessing(IEvent * e);
	virtual bool16 HandleTreeNodeDragDrop(IEvent * e);
};

#pragma export off

#endif
