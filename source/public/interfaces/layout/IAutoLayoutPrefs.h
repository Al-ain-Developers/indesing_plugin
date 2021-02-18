//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAutoLayoutPrefs.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IAutoLayoutPrefs__
#define __IAutoLayoutPrefs__

#include "IPMUnknown.h"

/**	Interface for setting and getting preferences for Layout Adjustment feature.
*/
class IAutoLayoutPrefs : public IPMUnknown
{
public:	
	
	/**	Enable the Layout Adjustment feature.
		@param val IN kTrue to turn on, kFalse to turn off.
	*/
	virtual void SetAutoLayoutOn(bool16 val) = 0;

	/**	Allow graphics and groups to be stretched (as opposed to moved only) by layout adjustment.
		@param val IN kTrue to allow stretching, kFalse to disallow
	*/
	virtual void SetStretchGraphics(bool16 val) = 0;

	/**	Allow guides to be moved by layout adjustment.
		@param val IN kTrue to allow moving, kFalse to disallow
	*/
	virtual void SetMoveGuides(bool16 val) = 0;

	/**	Allow locked items to be adjusted by layout adjustment.
		@param val IN kTrue to allow adjusting locked items, kFalse to disallow
	*/
	virtual void SetLoosenLocks(bool16 val) = 0;

	/**	Set whether ruler guides move with column edges if aligned.
		@param val IGNORED guide stickiness is always on; this setting is ignored
	*/
	virtual void SetStickyGuides(bool16 val) = 0;

	/**	Ignore alignment to ruler guides when performing layout adjustment.
		@param val IN kTrue to ignore guides, kFalse to obey guides
	*/
	virtual void SetIgnoreGuides(bool16 val) = 0;

	/**	Set the tolerance zone for layout adjustment's determination of pageitem edge alignment to guides, columns, etc.
		@param val IN distance in points from either side of an edge to consider aligned with guides, columns, etc. (range is 0 to 12 pts).
	*/
	virtual void SetAutoSnapZone(PMReal val) = 0;

	/**	Get the on/off state of layout adjustment.
		@return kTrue for on, kFalse for off
	*/
	virtual bool16 GetAutoLayoutOn() = 0;

	/**	Get whether graphics and groups may be stretched by layout adjustment.
		@return kTrue for allow stretching,  kFalse for disallow
	*/
	virtual bool16 GetStretchGraphics() = 0;

	/**	Get whether guides may be moved by layout adjustment.
		@return kTrue for allow moving,  kFalse for disallow
	*/
	virtual bool16 GetMoveGuides() = 0;

	/**	Get whether locked items can be adjusted by layout adjustment.
		@return kTrue for allow adjusting locked items,  kFalse for disallow
	*/
	virtual bool16 GetLoosenLocks() = 0;

	/**	Get whether ruler guides move with column guides when aligned. UNUSED; INTERNAL STATE IS ALWAYS kTrue.
		@return kTrue for allow stretching,  kFalse for disallow
	*/
	virtual bool16 GetStickyGuides() = 0;

	/**	Get whether guide alignments are ignored by layout adjustment.
		@return kTrue for ignore guides,  kFalse for don't ignore guides
	*/
	virtual bool16 GetIgnoreGuides() = 0;

	/**	Get the auto-snap zone.
		@return PMReal alignment tolerance zone in points (range 0-12 pts)
	*/
	virtual PMReal GetAutoSnapZone() = 0;
	
};

#endif
