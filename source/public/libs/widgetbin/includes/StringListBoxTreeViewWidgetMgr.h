//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/StringListBoxTreeViewWidgetMgr.h $
//  
//  Owner: Bob Freeman
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
#ifndef __StringListBoxWidgetMgr__
#define __StringListBoxWidgetMgr__

#include "CTreeViewWidgetMgr.h"
#include "StringNodeID.h"


class WIDGET_DECL StringListBoxWidgetMgr : public CTreeViewWidgetMgr
{
	typedef CTreeViewWidgetMgr inherited;
public:
	StringListBoxWidgetMgr(IPMUnknown *boss);
	virtual ~StringListBoxWidgetMgr();

protected:
	virtual bool16				ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message = 0 ) const;
	virtual bool16				ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message = 0 ) const;
	virtual PMReal				GetNodeWidgetHeight(const NodeID& node) const;
	virtual void				RegisterStyles();
	virtual PMString			GetStringFromControlData(int32 nodeIndex) const;
	virtual   IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual PMReal              GetNodeWidgetWidth(const NodeID& node) const;
};

class WIDGET_DECL StringListBoxSmallWidgetMgr : public StringListBoxWidgetMgr
{
public:
	StringListBoxSmallWidgetMgr(IPMUnknown *boss);
	virtual ~StringListBoxSmallWidgetMgr();

protected:
	virtual void				RegisterStyles();

};

class WIDGET_DECL StringListBoxLargeSmallWidgetMgr : public StringListBoxWidgetMgr
{
public:
	StringListBoxLargeSmallWidgetMgr(IPMUnknown *boss);
	virtual ~StringListBoxLargeSmallWidgetMgr();

protected:
	virtual void				RegisterStyles();

};


#pragma export off

#endif
