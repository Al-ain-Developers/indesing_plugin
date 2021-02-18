//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVPanelWithBorderView.h $
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
#ifndef __DVPanelWithBorderView__
#define __DVPanelWithBorderView__
	
#include "DVPanelView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	Drover-based widget equivalent for PanelWithBorderView - 
		the base container widget with a gray one pixel border around it.
*/

class DV_WIDGET_DECL DVPanelWithBorderView : public DVPanelView
{
	typedef DVPanelView inherited;
public:
	DVPanelWithBorderView(IPMUnknown *boss); 
	virtual	~DVPanelWithBorderView();
	/** Resizes the widget. Invals appropriately. */
	virtual void Resize(const PMPoint& newDimensions, bool16 invalidate = kTrue);

	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
};

#pragma export off

#endif

