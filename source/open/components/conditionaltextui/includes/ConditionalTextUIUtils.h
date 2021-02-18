//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/includes/ConditionalTextUIUtils.h $
//  
//  Owner: Michele Stutzman
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __CONDITIONALTEXTUIUTILS__
#define __CONDITIONALTEXTUIUTILS__

#include "NodeID.h"

class ITreeViewWidgetMgr;
class IControlView;

class ConditionalTextUIUtils
{
	public:
		static void ApplyAppliedIconToWidget(const ITreeViewWidgetMgr *widgetMgr, const NodeID& node, IControlView* widget);
};

#endif	// __CONDITIONALTEXTUIUTILS__
