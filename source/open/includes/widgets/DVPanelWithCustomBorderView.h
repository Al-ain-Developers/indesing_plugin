//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVPanelWithCustomBorderView.h $ 
//   
//  Owner: arijain
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
//  Copyright 1997-2017 Adobe Systems Incorporated. All rights reserved. 
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
#ifndef __DVPanelWithCustomBorderView__ 
#define __DVPanelWithCustomBorderView__ 

#include "DVPanelWithBorderView.h" 

#ifdef DV_WIDGET_BUILD 
#pragma export on 
#endif 

/**    Drover-based widget equivalent for PanelWithBorderView -
the base container widget with a gray one pixel border around it.
*/

class DV_WIDGET_DECL DVPanelWithCustomBorderView : public DVPanelWithBorderView
{
	typedef DVPanelWithBorderView inherited;
public:
	DVPanelWithCustomBorderView(IPMUnknown *boss);
	virtual    ~DVPanelWithCustomBorderView();

	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
	
	//Widget corresponding to the Dv_Draw is GenericpanelWithCustomBorderWidget/ EVEGenericpanelWithCustomBorderWidget.
	// This helps to draw the custom borders.{ Facility to draw only some/all side of the border widget}
	// Based on the parameter that are passed in the widget it draw left,right,bottom,top border around a widget.
	// for drawing the LEFTBORDER around the widget use kLeftBorder
	//for drawing the RIGHTBORDER of the the height specified in the frame use KRightBorder
	// for drawing the TOPBORDER around the widget use kTopBorder
	//for drawing the BOTTOMBORDER of the the height specified in the frame use KBottomBorder
	// for drawing the rounded rect border provide all the border(left,right,top,bottom) and assign the radius value to non zero.
	
	
};

#pragma export off 

#endif 
