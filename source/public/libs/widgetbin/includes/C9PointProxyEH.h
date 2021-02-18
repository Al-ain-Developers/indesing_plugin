//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/C9PointProxyEH.h $
//  
//  Owner:
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
#ifndef __ProxyViewEventHandler__
#define __ProxyViewEventHandler__

#include "IReferencePointData.h"

class IPMUnknown;
class IEvent;
class VirtualKey;
class PMLine;

/** Helper class providing partial implementation of IEventHandler for a proxy widget (e.g. control strip or transform panel).
	@see IEventHandler.h
	@see IProxyWidgetAttributes.h
*/

#include "DVControlEventHandler.h"


class WIDGET_DECL C9PointProxyEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;

public:
	/** Constants for the appearance of the proxy. */
	enum
	{
		kMainDiamondHeight = 24,
		kCornerDiamondHeight = 8,
		kMainSquareHeight = 19,
		kCornerSquareHeight = 7,
		kLineSquareHeight = 7
	};

	C9PointProxyEH(IPMUnknown* boss);
	~C9PointProxyEH();

	/**	Client must override this function.
		@param none
		@return kTrue if you want the proxy to be a tab stop (and keyboard drivable), kFalse otherwise.
	 */
	virtual bool16		CanHaveKeyFocus() const = 0;

	/**	Override if you want non-standard keyboard handling when proxy widget has focus. Default implementation
		responds to number pad numbers, regular numbers, arrows (all to move proxy point around),
		and return/enter/escape (to lose focus).
		@param e the event
		@return kTrue if event was handled, kFalse otherwise. 
	 */
	virtual bool16		KeyDown(IEvent* e);

	/**	Override if you want to provide special event handling. Default implementation changes the
		current layout window's reference point in response to clicked on point.
		@param e the event
		@return bool16 kTrue if event was handled, kFalse otherwise.
	 */
	virtual bool16 LButtonDn(IEvent* e);

	/**	Transform the current reference position by the given scale and angle
		@param position the position to transform
		@param xScale the x scale to use in the transform
		@param yScale the y scale to use in the transform
		@param cwAngle the angle to use in the transform
		@param invert whether to invert (kTrue) or not (kFalse) the reference position
		@return static IReferencePointData::ReferencePointPosition the original position transformed by the given values
	 */
	static IReferencePointData::ReferencePointPosition TransformPosition(
									const IReferencePointData::ReferencePointPosition& position,
									const PMReal& xScale,
									const PMReal& yScale,
									const PMReal& cwAngle,
									bool16 invert);

	/**	Transform the given point into a reference position
		@param position IN/OUT the position to transform
		@param xScale IN the x scale to use in the transform
		@param yScale IN the y scale to use in the transform
		@param cwAngle IN the angle to use in the transform
		@param referencePoint IN the reference point to use during the transform of the point
		@param invert IN whether to invert the scale/rotate matrix
	 */
	static void TransformPoint(PMPoint& point,
				 const PMReal& xScale, const PMReal& yScale, const PMReal& cwAngle,
				 const PMPoint& referencePoint,  bool16 invert);

	/**	Return the first position of the proxy to draw. Used when drawing the line appearance.
		@param line the line to draw the proxy with
		@return static IReferencePointData::ReferencePointPosition 
	 */
	static IReferencePointData::ReferencePointPosition GetFirstPosition(const PMLine& line);

	/**	Return the last position of the proxy to draw. Used when drawing the line appearance.
		@param line the line to draw the proxy with
		@return static IReferencePointData::ReferencePointPosition 
	 */
	static IReferencePointData::ReferencePointPosition GetLastPosition(const PMLine& line);

	/**	Given the size of the main proxy widget and a reference position, return a point location
		of one of the points of the proxy.
		@param position the reference position to draw
		@param mainSquare the size of the main proxy
		@return static PMPoint the returned point corresponding to the given position
	 */
	static PMPoint GetCornerPoint(const IReferencePointData::ReferencePointPosition& position,
						   const PMRect& mainSquare);

	/**	Given the size of the main proxy widget and a reference position and a size, return a
		rect that is the size of one of the points of the proxy.
		@param position the reference position to draw
		@param mainSquare the size of the main proxy
		@param cornerHeight the size of each proxy point
		@return static PMRect the rect size of the proxy (centered on GetCornerPoint)
	 */
	static PMRect GetCornerRect(const IReferencePointData::ReferencePointPosition& position,
						   const PMRect& mainSquare,
						   const PMReal& cornerHeight);

	/**	Given the size of the main proxy widget and a reference position and a size, return a
		rect that is the size of one of the points of the proxy. Used when proxy is rotated.
		@param position the reference position to draw
		@param mainDiamond the size of the main proxy in rotated mode
		@param cornerHeight the size of each proxy point
		@return static PMPolygon4 a polygon the size of the proxy
	 */
	static PMPolygon4 GetCornerDiamond(const IReferencePointData::ReferencePointPosition& position,
						   const PMPolygon4& mainDiamond,
						   const PMReal& cornerHeight);

	/**	Test if the given polygon contains a point
		@param poly4 the polygon to use
		@param point the point to test
		@return static bool16 return kTrue if point is in the polygon
	 */
	static bool16 Contains(const PMPolygon4& poly4, const PMPoint& point);

	/**	Given a height and a center, return a polygon describing the size of the diamond appearance of the proxy.
		@param poly4 OUT the returned polygon
		@param center the center of the widget
		@param height the height to make the polygon
	 */
	static void MakeDiamond(PMPolygon4& poly4, const PMPoint& center, const PMReal& height);

	/**	Inset the given polygon by an amount
		@param poly4 IN/OUT the polygon to alter
		@param inset the amount to inset
	 */
	static void Poly4Inset(PMPolygon4& poly4, const PMReal& inset);

	/**	Given an angle, return the octant of the proxy. Used for diamond appearance. 1 means 45 degrees, 2 90, etc.
		So octant value is the number of 45 degree rotations of the proxy.
		@param angle the angle to test
		@return static short the octant value. 0 if regular rect appearance, non-zero odd value for diamond appearance
	 */
	static short Octant(const PMReal& angle);

	/**	Map a reference position into a point on the proxy
		@param position the given ref position
		@return static PMPoint the returned point
	 */
	static PMPoint PositionToPoint(const IReferencePointData::ReferencePointPosition& position);

	/**	Map a point into a reference position on the proxy
		@param point the given point
		@return static IReferencePointData::ReferencePointPosition the returned reference position
	 */
	static IReferencePointData::ReferencePointPosition PointToPosition(const PMPoint& point);

protected:
	/**	Called after the proxy widget acquires keyboard focus.
		@param e event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	 */
	virtual void		PostGetKeyFocus();

	/**	Called after the proxy widget loses keyboard focus.
		@param e event of interest
		@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
	 */
	virtual void		PostGiveUpKeyFocus();

	/**	Given a point, hit test the 9 squares of the proxy (when in IReferencePointData::kNinePoint appearance) and return the nearest reference position.
		@param point the point to use for hittesting
		@return IReferencePointData::ReferencePointPosition the nearest position
	 */
	IReferencePointData::ReferencePointPosition HitTestSquares(const PMPoint& point);

	/**	Given a point, hit test the 9 squares of the proxy (when in rotated IReferencePointData::kNinePoint appearance) and return the nearest reference position.
		@param point the point to use for hittesting
		@return IReferencePointData::ReferencePointPosition the nearest position
	 */
	IReferencePointData::ReferencePointPosition HitTestDiamonds(const PMPoint& point);

	/**	Given a point, hit test the 3 squares of the proxy (when in IReferencePointData::kLine appearance) and return the nearest reference position.
		@param point the point to use for hittesting
		@return IReferencePointData::ReferencePointPosition the nearest position
	 */
	IReferencePointData::ReferencePointPosition HitTestLine(const PMPoint& point);


	/**	High level routine: Given a point, hit test the proxy points and return the hit position. Calls either HitTestSquares, HitTestDiamonds,
		or HitTestLine to do its work.
		@param localPoint the point to use for hittesting.
		@return IReferencePointData::ReferencePointPosition the new reference position after doing the hittest.
	 */
	IReferencePointData::ReferencePointPosition ComputeNewReferencePosition(const PMPoint& localPoint);

	/**	Change the reference position
		@param newPosition the new reference point position
	 */
	virtual void ChangeReferencePosition(IReferencePointData::ReferencePointPosition newPosition) = 0;

	/**	Handle a key event when the proxy widget has focus. Currently handles numbers and arrow keys
		@param key the virtual key to handle and move the proxy point
	 */
	void HandleKeyEvent(VirtualKey& key);

private:
	/**	Invalidate the keyboard focus are of the proxy widget.
	 */
	virtual void		InvalidateFocus();

	/**	Release keyboard focus from the proxy widget.
	 */
	virtual void		ReleaseKeyBoardFocus();
};

#endif

