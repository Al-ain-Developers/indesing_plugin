//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVBasePanelView.h $
//  
//  Owner: Dave Burnard
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
//  Copyright 1997-2009 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __DVBasePanelView__
#define __DVBasePanelView__
	
#include "DVAbstractControlView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	Drover widget base class for panel views. It's expected this will be used as a base for specific panel view implementations (see DVPanelView.h and DVGroupPanelView.h for examples).
*/
/* If you want  to restrict the  drawing of the child to a specified bounds  . Do something similar to that is done in DVTreeScrollerWidgetView*/

class DV_WIDGET_DECL DVBasePanelView : public DVAbstractControlView
{
	typedef DVAbstractControlView inherited;
public:
	DVBasePanelView(IPMUnknown *boss); 
	virtual	~DVBasePanelView();

	virtual void Show(bool16 doShow = kTrue);
	virtual void Hide();
	virtual void ParentsVisibleStateChanged(bool16 visible);
	virtual void WindowActivated();
	virtual void WindowDeactivated();
	virtual void Hilite(bool16 doHilite = kTrue);
	virtual void Unhilite();
	virtual void WindowShown();
	virtual void WindowHidden();
	virtual void WindowChanged();
	virtual void WindowClosed();
	virtual void DoPostCreate();
	virtual void ParentPurged();
	virtual void InvalidateTransform();
	
	/* The parent is send the mouse event before the primary recipient is determined.
	   When UI_DoMouseEvent is called, the primary_recipient is NULL in this case.
	   The parent will be called again once the primary recipient has been found,
	   if no child has handled the event.
	   Such events are sent to the event handler on the  IID_IPRECHILDEVENTHANDLER interface
	*/
	virtual void SetWantsMouseEventBeforeChildren();
	
	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;

protected:
	/*
	 DVBasePanelView supports drawing in DV_Draw() via drawbot, but can optionally support drawing in Draw() via AGM. If you want to use AGM based drawing, you must call this method during the initialization of your widget.
	 */
			 void SetWantsToDrawWithAGM(bool drawWithAGM = true);
	
private:
	 bool fDrawPanelWithAGM;
};

#pragma export off

#endif

