//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IBooleanControlData.h $
//  
//  Owner: Frits Habermann
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
#ifndef __IBOOLEANCONTROLDATA__
#define __IBOOLEANCONTROLDATA__

#include "widgetid.h"

/**
	Interface on bi-state controls that can be in two states; selected or deselected. 
*/
class IBooleanControlData : public IPMUnknown
{
	public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IBOOLEANCONTROLDATA };

	/** Method to set the control state to be selected.
		@param updateView specifies whether the control should be redrawn
		@param notifyOfChange specifies whether observers on the control data should be notified of the change. 
	*/
	virtual void				Select(bool16 updateView = kTrue, bool16 notifyOfChange = kTrue) = 0;
	/** Method to set the state to deselected.
		@param updateView specifies whether the control should be redrawn
		@param notifyOfChange specifies whether observers on the control data should be notified of the change. 
	*/
	virtual void 				Deselect(bool16 updateView = kTrue, bool16 notifyOfChange = kTrue) = 0;
	/** Method to change the state to the logical opposite. 
		@param updateView specifies whether the control should be redrawn
		@param notifyOfChange specifies whether observers on the control data should be notified of the change

	*/
	virtual void 				Toggle(bool16 updateView = kTrue, bool16 notifyOfChange = kTrue) = 0;
	/** Accessor to determine whether the control is in selected state
		@return kTrue if the control is in the selected state, kFalse if deselected
	*/
	virtual bool16			IsSelected() const = 0;
};

#endif
