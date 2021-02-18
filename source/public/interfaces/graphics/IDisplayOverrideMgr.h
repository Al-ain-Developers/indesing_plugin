//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDisplayOverrideMgr.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  This is the handle shape interface for page item adornments.  This interface can
//  return trackers just like a normal handle shape.  Keep in mind, however, that
//  it is the page item which is in the selection, not the adornment.  
//  
//========================================================================================

#pragma once
#ifndef __IDisplayOverrideMgr__
#define __IDisplayOverrideMgr__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"

class IDisplayOverrideMgr: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDISPLAYOVERRIDESMGR };

public:
    /**
	 * Returns the current draw options for the specified shape.
	 * Depending on the interrupt state.  In Dragontail, draw
	 * options are non-persistent.
	 *
	 * bForUIWidget should be true when you are deciding what option
	 *  should be checked, and false when you are deciding how to draw
	 *  the actual page item.  Sometimes, when ignore local overrides
	 *  is checked, the UI appears different than how the page item is
	 *  actually drawn.
	 */
	 
    virtual uint32 GetDrawOptionsGroup(UID uidShape, bool16 bForUIWidget) = 0;

	/**
	 * Update the draw options.  This call:will set the status to the specified group, 
	 * regardless of the interrupt state.
	 */

    virtual void SetDrawOptionsGroup(UID uidShape, uint32 nGroup)        = 0;

	/**
	 * This method changes all overrides to 'optimized'.  They stay that way
	 * until:
	 * A. ResumeAfterInterrupt is called, in which case all overrides that
	 *    haven't been updated since the interrupt return to their original
	 *    state.
	 * B. A new value is set on a particular page item.
	 */

    virtual void SetInterruptDraw( bool16 bInterrupt ) = 0;

	/**
	 * Returns true if draw is currently interrupted.
	 */

    virtual bool16 IsDrawInterrupted() = 0;
	
	/**
	 * Set and retrieve the most recently used active set ID for the view.
	 * We do this so that when the user hits escape, the view setting is
	 * restored.
	 */
	virtual void SetMostRecentDrawOptionsID(uint32 n) = 0;
	virtual uint32 GetMostRecentDrawOptionsID() = 0;

	/**
	 * Retrieves the set of uids that have the specified in-memory override.
	 */

	virtual void GetInMemoryOverrides(uint32 nDrawGroup, UIDList& uidOverrides ) = 0;
};

#endif
