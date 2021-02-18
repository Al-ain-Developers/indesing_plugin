//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/tooltips/AbstractTip.cpp $
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

#include "DV_VCWidgetHeaders.h"
#include "AbstractTip.h"

DEFINE_HELPER_METHODS(AbstractTip)

AbstractTip::AbstractTip(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}

AbstractTip::~AbstractTip()
{
}

bool16 AbstractTip::UpdateToolTipOnMouseMove() 
{ 
	return kFalse; 
}
