//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVListTreeScrollerWidgetView.h $
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
#ifndef __DVListTreeScrollerWidgetView__
#define __DVListTreeScrollerWidgetView__
	
#include "DVTreeScrollerWidgetView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/*
	Drover world's version of ListTreeScrollerWidgetView
*/

class DV_WIDGET_DECL DVListTreeScrollerWidgetView : public DVTreeScrollerWidgetView
{
	typedef DVTreeScrollerWidgetView inherited;
public:
			 DVListTreeScrollerWidgetView(IPMUnknown *boss); 
	virtual	~DVListTreeScrollerWidgetView();

	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
	// For internal use. This extracts the area to which the scroller child nodes drawing should
	// be restricted to. Used in the UI_Draw of ID_UI_TreeScrollerView.
	virtual PMRect		GetClippedArea() const;
	
protected:
	// deprecated:      The default is set to not draw endline.
	virtual void   SetDrawListWidgetEndLine(bool16 drawEndLine);

private:
	bool16 fDrawListEndLine;
};

#pragma export off

#endif
