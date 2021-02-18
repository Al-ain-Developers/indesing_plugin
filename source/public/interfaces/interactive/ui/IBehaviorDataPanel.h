//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/IBehaviorDataPanel.h $
//  
//  $Owner: Michael Burbidge $
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
#ifndef __IBehaviorDataPanel_h__
#define __IBehaviorDataPanel_h__

#include "IPMUnknown.h"
#include "BehaviorUIID.h"

//========================================================================================
// CLASS IBehaviorDataPanel
//========================================================================================

/** Add-in interface to Behavior Factory Boss, that provides a panel that can be used
	to edit the behavior.  The panel is is placed inside a dialog that is presented when
	a new behavior is being created, or an existing behavior of a certain type is edited.
*/
class IBehaviorDataPanel : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIORDATAPANEL };

	/** Create panel for a certain type of behavior UI (whatever is appropriate for the behavior
		boss that this interface is added to.
		@param localeId A localeid to be used to get the proper resource for the panel.
		@param iid Interface to be returned. Should be IID_ICONTROLVIEW.
		@return a iid ( IID_ICONTROLVIEW) interface on the panel
	*/
	virtual IPMUnknown* CreatePanel(const PMLocaleId& localeId, const PMIID& iid) const = 0;
};

#endif // __IBehaviorDataPanel_h__
