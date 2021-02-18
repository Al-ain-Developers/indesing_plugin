//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/EventUtilities.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __EVENTUTILITIES__
#define __EVENTUTILITIES__

#ifdef ID_DEPRECATED

#include "VirtualKey.h"
#include "KeyStates.h"
#include "PMTypes.h"
#include "Utils.h"

#pragma export on

// forward declares for pointers
class IEvent;
class IControlView;
class CursorSpec;

#ifdef MACINTOSH
/**	Use IEventUtils instead of this set of utility functions.
	This file will be removed in a future version.
	@see IEventUtils
*/
class DV_WIDGET_DECL EventUtilities
{
public:
	static void MovePaletteWindowsOffScreen(bool16 off);
};
#endif

DV_WIDGET_DECL GSysPoint GetGlobalMouseLocation();

DV_WIDGET_DECL bool16 IsMouseButtonDown();
DV_WIDGET_DECL bool16 IsMouseButtonReleased();

DV_WIDGET_DECL bool16 IsUserStartingDrag(IEvent *e, bool16 &isPatientUser, const CursorSpec* patientCursor = nil);

DV_WIDGET_DECL bool16 IsUserStartingDrag(IEvent *e, bool16 &isPatientUser, const SysRect& startOnExitGRect, const CursorSpec* patientCursor = nil);

DV_WIDGET_DECL void RemoveNextKeyCmd(IEvent* e);

DV_WIDGET_DECL bool16 IsDragOrTrackInProgress();

DV_WIDGET_DECL bool16 IsTrackInProgress();

#pragma export off

#endif
#endif
