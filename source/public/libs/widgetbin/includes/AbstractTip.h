//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/AbstractTip.h $
//  
//  Owner: Sanyam Jain
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
#ifndef __AbstractTip__
#define __AbstractTip__
	
#include "ITip.h"


#ifdef WIDGET_BUILD
#pragma export on
#endif

/**	This class is a new base class used to implement ITip for essentially all widgets. It
	@see ITip
*/

class DV_WIDGET_DECL AbstractTip : public ITip
{
public:
	// ----- Initialization -----

	AbstractTip(IPMUnknown *boss); 
	virtual ~AbstractTip();
	
	virtual PMString  GetTipText(const PMPoint& mouseLocation) = 0;
	virtual bool16 UpdateToolTipOnMouseMove();
	virtual void SetTipText(const PMString tipText) {};

protected:
DECLARE_HELPER_METHODS()
};


#pragma export off

#endif

