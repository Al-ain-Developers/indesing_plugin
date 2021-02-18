//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IReferencePointSuite.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IREFERENCEPOINTSUITE__
#define __IREFERENCEPOINTSUITE__

#include "IReferencePointData.h"
#include "LayoutUIID.h"
#include "PMLine.h"
class IControlView;

/**
	A selection suite to operate on the reference point. InDesign has just one global reference
	point and position, but it may be accessed via several suites, and the reference point in
	different suites has some different behaviors. e.g. In the text selection suite we never draw
	the reference point, though it still exists.
	@ingroup layout_suite
	@see IRefPointUIUtils.h
*/
class IReferencePointSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IREFERENCEPOINTSUITE };

// ----- Abilities

	/**	Does the current selection have a visible reference point? Currently the LayoutCSB
		is the only selection the has a visible reference point, and it applies whenever there
		is a non-guide selection. In practice, we only actually draw the reference point when one of
		the transform tools is also selected (e.g. Rotate, Scale, Shear tools).
		@return bool16 Return kTrue if a reference point should be shown, kFalse otherwise.
	 */
	virtual bool16 ViewHasReferencePoint( IControlView* view) const = 0;

	/**	Return the default reference position for the specified selection. For a guide selection, it
		is kCenter, otherwise it is the current position.
		@return IReferencePointData::ReferencePointPosition the current position of the reference point.
	 */
	virtual IReferencePointData::ReferencePointPosition GetViewDefaultReferencePosition( IControlView* view) const = 0;

	/**	Return the reference position for the current selection.
		@return IReferencePointData::ReferencePointPosition one of nine positions, or other.
	 */
	virtual IReferencePointData::ReferencePointPosition GetViewReferencePointPosition( IControlView* view) const = 0;
	
	/**	Return what the proxy representation should be (line, 9 point, single point, etc.)
		@return ReferenceAppearance the appearance of the proxy.
	 */
	virtual IReferencePointData::ReferenceAppearance GetViewReferenceAppearance( IControlView* view) const = 0;

	/**	Return the PMLine for the selection, undefined if GetReferenceAppearance != kLine.
		We use the line appearance whenever a line is selected. Can be a vertical, horizontal,
		or diagonal line that best matches the angle of the line selection. Also used for
		@return a PMLine that represents the selection.
		@see IPathInfoUtils.h
		@see GetLine
	 */
	virtual PMLine GetViewReferenceLine( IControlView* view) const = 0;

	/**	Can the reference point be changed for the current selection? A single guide cannot have
		its reference point changed, since it is always kCenter.
		@return bool16 Return kTrue if the reference point can be changed, kFalse otherwise.
	 */
	virtual bool16 CanChangeViewReferencePoint( IControlView* view) const = 0;

	/**	Calculate the current reference point for the given position for the current selection.
		@param position [IN] the new reference position
		@param nil OUT Optionally return parent rectangle in pasteboard coordinates if it exists (e.g. graphic item direct selected)
		@return PBPMPoint 
	 */
	virtual PBPMPoint CalculateViewReferencePoint( IControlView* view, IReferencePointData::ReferencePointPosition position,
												 PBPMRect* referenceFrame = nil) = 0;	

// ----- Manipulators

	/**	Change the reference point for the selection suite to the new values.
		@param newPosition [IN] the new reference point position
		@param newPoint [IN] the new reference point value in pasteboard coordinates
		@param referenceFrame [IN] the new parent reference frame, use kZeroRect if it doesn't apply
		@return ErrorCode the result of the command to change the reference point
		@see kMoveReferencePointCmdBoss
	 */
	virtual ErrorCode ChangeViewReferencePoint( IControlView* view, IReferencePointData::ReferencePointPosition newPosition,
									 const PMPoint& newPoint,
									 const PBPMRect& referenceFrame = kZeroRect) = 0;

	/**	Change just the reference position for the selection suite based on its selection.
		@param newPosition [IN] the new reference position
		@return ErrorCode the result of processing the command to move the position
	 */
	virtual ErrorCode ChangeViewReferencePosition( IControlView* view, IReferencePointData::ReferencePointPosition newPosition) = 0;

};


#endif	// __IREFERENCEPOINTSUITE__


