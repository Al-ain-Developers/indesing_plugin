//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVRollOverIconButtonView.h $
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
//  
//========================================================================================

#pragma once
#ifndef __DVRollOverIconButtonView__
#define __DVRollOverIconButtonView__

#include "DVIconSuiteButtonView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif


class DV_WIDGET_DECL DVRollOverIconButtonView : public DVIconSuiteButtonView
{
	typedef DVIconSuiteButtonView inherited;
public:
	DVRollOverIconButtonView(IPMUnknown *boss);
	virtual ~DVRollOverIconButtonView();

protected: 
	virtual void 	DrawUnselected(dvaui::drawbot::Drawbot* drawbotP);
	virtual void 	DrawHilited(dvaui::drawbot::Drawbot* drawbotP); 
	virtual bool	ShouldDisplayContainer() const;

	virtual void	CommonInit();
};

#pragma export off

#endif // __DVRollOverIconButtonView__
