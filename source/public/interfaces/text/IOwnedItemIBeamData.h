//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IOwnedItemIBeamData.h $
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
#ifndef __IOwnedItemIBeamData__
#define __IOwnedItemIBeamData__

#include "IPMUnknown.h"
#include "TextID.h"
#include "PMPoint.h"
#include "CursorSpec.h"

class IControlView;
class IEvent;
class ITracker;
class IPlaceBehavior;
class ITextFrameColumn;

/** The IBeam Tool looks for this interface on OwnedItems to help it set
	the appropriate cursor and spawn the appropriate trackers for the
	OwnedItem.

	The core reason it exists is because the Visitor/Helper mechanism assumes
	that hit items must be UID based objects and Table Cells do not fall into
	this category. So, for example, the TableFrame, which is a UID based object,
	returns itself as being hit and the callee must be smart enough to recognize
	that what was hit was an OwnedItem and look for this interface on the boss
	to get further information.

	@ingroup text_owned
*/
class IOwnedItemIBeamData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOWNEDITEMIBEAMDATA };

	/**
	Returns a cursor for the Text IBeam Tool which has wandered over the
	IOwnedItemIBeamData. If the item fails to return a cursor then the
	appropriate default IBeam is used.
	@param pt Point Pasteboard coordinates
	@param controlView Pointer to the relevant ControlView
	@param spec How the cursor is returned
	@return kTrue if a cursor was returned via spec kFalse if no cursor
	*/
    virtual bool16		GetCursor(PBPMPoint &pt, IControlView* controlView,
									CursorSpec &spec) const = 0;

	/**
	Returns a tracker for the Text IBeam Tool which has wandered over the
	IOwnedItemIBeamData.
	@param event The event
	@param controlView The relevant ControlView
	@return A pointer to the new tracker object or nil.
	*/			
	virtual ITracker*	CreateTracker(const IEvent* event,
									IControlView* controlView) const = 0;

	/**
	Returns a pointer to place behavior object for the specified parameters.
	Tables use this, for example, to support placing into Table cells.
	@param pt Point Pasteboard coordinates
	@param controlView Pointer to the relevant ControlView
	@return A pointer to a queried IPlaceBevior, or nil.
	*/
	virtual IPlaceBehavior*	QueryPlaceBehavior(PBPMPoint& pt,
									IControlView* controlView) const = 0;

	/**
	Some callers want to hit the containing MuliColumnTextFrame instead of the
	sub-objects and this method provides a quick way to getting that context.
	@return Pointer to TextFrameColumn
	*/
	virtual ITextFrameColumn* QueryContainingFrame() const = 0;

};

#endif
