//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IClusterController.h $
//  
//  Owner: Dave Burnard (was Tom Taylor)
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
#ifndef __IClusterController__
#define __IClusterController__

#include "IPMUnknown.h"
#include "widgetid.h"

class IEventHandler;

/** Interface used to control a "cluster" of related widgets, for example, a radio button group.
		This interface is found ong the kClusterPanelWidgetBoss object.
*/
class IClusterController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICLUSTERCONTROLLER };

	/** Query for the event handler of the currently selected widget in the cluster. */
	virtual IEventHandler*		QuerySelectedClusterWidgetEH() const = 0;

	/** Query for the event handler of the "next" widget in the cluster and "select" it.
			In other words, the currently turned on widget is turned off and the next one in the list is turned on.
			The event handler of the new widget is returned. 		
		@param next IN if true then select the next widget in the cluster, if false then select the previous one.
	*/
	virtual IEventHandler*		SelectAndQueryNextClusterWidget(bool16 next = kTrue) = 0;
};

#endif
