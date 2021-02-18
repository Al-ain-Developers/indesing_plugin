//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVListTreeWidgetControlView.h $
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
#ifndef __DVListTreeWidgetControlView__
#define __DVListTreeWidgetControlView__

#include "DVTreeWidgetControlView.h"

/**	Drover-based widget equivalent for ListTreeWidgetControlView
*/
class DV_WIDGET_DECL DVListTreeWidgetControlView : public DVTreeWidgetControlView
{
	typedef DVTreeWidgetControlView inherited;
public:
	DVListTreeWidgetControlView(IPMUnknown *boss);
	virtual ~DVListTreeWidgetControlView();

	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;

protected:	
	virtual	IControlView*	CreateTreeScrollerWidget();
	virtual void WindowHidden();
};

#endif
