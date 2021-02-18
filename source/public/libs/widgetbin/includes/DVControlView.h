//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVControlView.h $
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
#ifndef __DVControlView__
#define __DVControlView__

#include "DVAbstractControlView.h"


#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	DVControlView is a concrete ControlView class that is a convenient starting place for custom leaf controls. 
 CControlView existed pre CC and DVControlView is it's replacement.

 Subclasses may choose to override Draw or DV_Draw to customize drawing. DV_Draw is preferred internally, but since drawbot is not exposed to external clients, they should override
	 the traditional Draw method, and draw eith AGM's IGraphicsPort.

 @see IControlView, DVAbstractControlView
 */
class DV_WIDGET_DECL DVControlView : public DVAbstractControlView
{
	typedef DVAbstractControlView inherited;
public:
	// ----- Initialization -----
	
	DVControlView(IPMUnknown *boss); 
	virtual ~DVControlView();
};

typedef DVControlView CIDControlView; 

#pragma export off

#endif
