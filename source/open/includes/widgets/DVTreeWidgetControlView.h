//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVTreeWidgetControlView.h $
//  
//  Owner: Vadim Tkachev
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __DVTreeWidgetControlView__
#define __DVTreeWidgetControlView__
	
#include "DVErasablePanelView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	Drover-based widget equivalent for TreeWidgetControlView */

class DV_WIDGET_DECL DVTreeWidgetControlView : public DVErasablePanelView
{
	typedef DVErasablePanelView inherited;
public:
	DVTreeWidgetControlView(IPMUnknown *boss); 
	virtual	~DVTreeWidgetControlView();

	virtual	void	DoPostCreate();
	virtual	void 	DoAutoAttach();
	virtual	void 	DoAutoDetach();
	virtual	void	Resize(const PMPoint& dimensions, bool16 invalidate);
	virtual	void	WindowHidden();
	virtual	void	DeleteDrawRegion();
 	virtual	void	ParentsVisibleStateChanged(bool16 visible);

	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
	virtual PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;
	
protected:
	virtual	IControlView*	CreateTreeScrollerWidget();

	// If ContrainDimensions() is called on the tree, the tree will not contrain to showing
	// fMinItemsShowingInList list items at a minimum.  Default is 2
	int32	fMinItemsShowingInList;

};

#pragma export off

#endif
