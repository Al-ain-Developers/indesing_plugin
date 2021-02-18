//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVTreeScrollerWidgetView.h $
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
#ifndef __DVTreeScrollerWidgetView__
#define __DVTreeScrollerWidgetView__
	
#include "DVBasePanelView.h"


#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/*
	Drover world's version of TreeScrollerWidgetView
	
	Note: DVTreeScrollerWidgetView subclasses that draw (rare) and that want to draw with AGM (rarer still)
	must call SetWantsToDrawWithAGM() so that their Draw() methods will be called.
*/

class DV_WIDGET_DECL DVTreeScrollerWidgetView : public DVBasePanelView
{
	typedef DVBasePanelView inherited;
public:
			 DVTreeScrollerWidgetView(IPMUnknown *boss); 
	virtual	~DVTreeScrollerWidgetView();

	virtual PMMatrix*	GetUpdatedContentToWindowTransform();
	virtual	SysRect		GetBBox() const;
	// For internal use. This extracts the area to which the scroller child nodes drawing should
	// be restricted to. Used in the UI_Draw of ID_UI_TreeScrollerView.
	virtual PMRect		GetClippedArea() const;

private:
	// These data are mutable due to them being changed inside of GetBBox()
	// which must be const because of the interface.
	mutable int32 fScrollBarInsetX;
	mutable int32 fScrollBarInsetY;
};

#pragma export off

#endif
