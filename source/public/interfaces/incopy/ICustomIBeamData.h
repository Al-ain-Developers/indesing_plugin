//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICustomIBeamData.h $
//  
//  Owner: dwaterfa
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
#ifndef __ICustomIBeamData__
#define __ICustomIBeamData__

#include "IPMUnknown.h"
#include "WritingModeUIID2.h"
#include "PMPoint.h"
#include "CursorSpec.h"
#include "ICursorMgr.h"


class IControlView;
class IEvent;
class ITracker;
class ICursorMgr;

/**
	The IBeam Tool looks for this interface on OwnedItems to help it set
	the appropriate cursor and spawn the appropriate trackers for the
	OwnedItem.
*/
class ICustomIBeamData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICUSTOMIBEAMDATA };

/**	Returns a cursor for the Text IBeam Tool which has wandered over the ICustomIBeamData.
	If the item fails to return a cursor then the appropriate default IBeam is used.
	@param globalPoint In Pasteboard coordinates
	@param ICursorMgr::eCursorModifierState Cursor Modifier State
	@param controlView The relevant ControlView
	@param spec Return the cursor resource spec
	@return bool16 kTrue if a cursor was returned via spec
				   kFalse if no cursor
 */
    virtual bool16		GetCursor(const SysPoint globalPoint,
								  ICursorMgr::eCursorModifierState, 
								  IControlView* controlView,
								  CursorSpec &spec) const = 0;

/**	Returns a tracker for the Text IBeam Tool which has wandered over the ICustomIBeamData.
	@param event The event
	@param controlView The relevant ControlView
	@return ITracker* A pointer to the new tracker object or nil if no tracker is returned.
 */
	virtual ITracker*	CreateTracker(const IEvent* event,
									IControlView* controlView) const = 0;

};

#endif
