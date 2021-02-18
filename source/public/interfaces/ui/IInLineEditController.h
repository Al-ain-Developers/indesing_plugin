//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IInLineEditController.h $
//  
//  Owner: Matt joss
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IInLineEditController__
#define __IInLineEditController__

#include "IPMUnknown.h"
#include "widgetid.h"

class IEventHandler;
/**   
	InLineEdit widget normally displayed as static text. Under certain event 
	(e.g. double click), static text can be changed on the spot. This interface 
	controls start and stop editing mode of InLineEdit widget.
*/
class IInLineEditController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINLINEEDITCONTROLLER };

	/**
		Switch InLineEdit widget into editing mode.
		@return kTrue if entering editing mode successfully, kFalse otherwise
	*/
	virtual bool16 BeginEditing() = 0;

	/**
		Switch InLineEdit widget off editing mode.
		@return kTrue if quiting editing mode successfully, kFalse otherwise
	*/
	virtual bool16 StopEditing(bool16 syncData = kTrue, bool16 releaseKeyFocus = kTrue) = 0;

	/**
		Return kTrue if being edited currently, kFalse otherwise
		@return kTrue kTrue if being edited currently, kFalse otherwise
	*/
	virtual bool16 IsBeingEdited() const = 0;

	virtual		   void SyncFilteringNode() = 0;
};

#endif
