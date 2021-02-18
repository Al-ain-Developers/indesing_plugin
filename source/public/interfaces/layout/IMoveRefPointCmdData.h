//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMoveRefPointCmdData.h $
//  
//  Owner: Richard Rodseth
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
#ifndef __IMoveReferencePointCmdData__
#define __IMoveReferencePointCmdData__

#include "PMPoint.h"
#include "IReferencePointData.h"

class ILayoutControlData;

// Use of ILayoutControlData* is temporary, until layout view is persistent, so we can store a UID

/**  Command data interface for controlling the reference point location for a layout view.
	 In general, these methods are probably only used internally since the management of the reference
	 point is handled via higher-level calls.

	 @see kMoveReferencePointCmdBoss
	 @see IRefPointUIUtils.h
*/
class IMoveReferencePointCmdData : public IPMUnknown
{
public:

	/**	Set the data for the move reference point command.
		@param layoutData [IN] the ILayoutControlData for the layout view to set the reference point in. 
		@param newPosition [IN] the ReferencePointPosition to change to
		@param newLocation [IN] the new location in global pasteboard coordinates for the reference point
		@param newReferenceFrame[IN] the reference frame for the reference point to be relative to (use kZeroRect if not relevant).
	 */
	virtual void SetMoveReferencePointCmdData( ILayoutControlData* layoutData,
						 IReferencePointData::ReferencePointPosition newPosition,
						 const PBPMPoint& newLocation,
						 const PBPMRect& newReferenceFrame = kZeroRect) = 0;
						 

	/**	Used internally by the kMoveReferencePointCmdBoss to save off the old location value.
		@param oldLocation [IN] the previous reference location value.
	 */
	virtual void  SetOldReferencePointLocation(const PBPMPoint& oldLocation) = 0;

	/**	Return the ILayoutControlData* for the target view.
		@return ILayoutControlData* for the target view.
	 */
	virtual ILayoutControlData* GetReferencePointLayoutData() const = 0;
	
	/**	Return the data value for newPosition that was set in the Set method.
		@return ReferencePointPosition the new reference position
	 */
	virtual const IReferencePointData::ReferencePointPosition GetNewReferencePointPosition() = 0;
	
	/**	Return the old reference point location, used for invalidating when observing command changes.
		@return PBPMPoint the old reference location before the command was executed. 
	 */
	virtual const PBPMPoint GetOldReferencePointLocation() = 0;

	/**	Return the data value for newLocation that was set in the Set method.
		@param PBPMPoint the reference point value
	 */
	virtual const PBPMPoint GetNewReferencePointLocation() = 0;

	/**	Return the data value for newReferenceFrame that was set in the Set method.
		@return PBPMRect the reference frame value
	 */
	virtual const PBPMRect GetNewContentOffsetFrame() = 0;

};

#endif // __IMoveReferencePointCmdData__
