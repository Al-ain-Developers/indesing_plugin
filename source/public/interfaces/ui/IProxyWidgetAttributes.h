//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IProxyWidgetAttributes.h $
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
//  
//  Purpose:	Stores attributes of the proxy widget, such as whether it is a line proxy
//  
//========================================================================================

#pragma once
#ifndef __IProxyWidgetAttributes__
#define __IProxyWidgetAttributes__

class PMLine;
class ISelectionManager;
class PathInfo;
class IControlView;

#include "IReferencePointData.h"
#include "widgetid.h"

/** Interface responsible for getting and setting various attributes of proxy widgets.
	This is the widget that appears in the Transform panel that typically has a 9-point appearance,
	though it can also be rotated, or have a line or point appearance. The proxy widget generally 
	reflects the current selection state of the document.
*/

class IProxyWidgetAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPROXYWIDGETATTRIBUTES };

	/**	Return if the appearance is a line state (just 3 points drawn) or not.
		@param none
		@return bool16 kTrue for line appearance, kFalse otherwise.
	 */
	virtual bool16 GetProxyIsLine() = 0;

	/**	Set the appearance of the proxy to a line
		@param isLine kTrue for line appearance, kFalse for 9-point appearance.
		@see SetAppearance
	 */
	virtual void SetProxyIsLine(bool16 isLine) = 0;

	/**	Set the anglee of the proxy. Reflects the rotation of the selection. Proxy will
		itself will rotate based on the rotation value of selection to make the proxy visually
		match the selection. e.g. Upper left of proxy is upper left of selection.
		@param angle 
	 */
	virtual void SetProxyReferenceAngle(const PMReal& angle) = 0;

	/**	Set the x scale of the proxy. Reflects the x scale percentage of the selection.
		Proxy may "flip" if the selection is flipped to make the proxy visually
		match the selection. e.g. Upper left of proxy is upper left of selection.
		@param xScale 
	 */
	virtual void SetProxyReferenceXScale(const PMReal& xScale) = 0;

	/**	Set the y scale of the proxy. Reflects the y scale percentage of the selection.
		Proxy may "flip" if the selection is flipped to make the proxy visually
		match the selection. e.g. Upper left of proxy is upper left of selection.
		@param yScale 
	 */
	virtual void SetProxyReferenceYScale(const PMReal& yScale) = 0;

	/**	Set the skew of the proxy. Reflect the skew of the selection.
		@param xSkew 
	 */
	virtual void SetProxyReferenceXSkew(const PMReal& xSkew) = 0;

	/**	Set the line of the proxy. Used for the line appearance when the selection is a line.
		@param line 
		@see SetAppearance
	 */
	virtual void SetProxyReferenceLine(const PMLine& line) = 0;

	/**	Return the angle of the proxy for the current selection.
		@return PMReal 
	 */
	virtual PMReal GetProxyReferenceAngle() = 0;

	/**	Return the x scale of the proxy for the current selection.
		@return PMReal 
	 */
	virtual PMReal GetProxyReferenceXScale() = 0;

	/**	Return the y scale of the proxy for the current selection.
		@return PMReal 
	 */
	virtual PMReal GetProxyReferenceYScale() = 0;

	/**	Return the skew value of the proxy for the current selection.
		@param none
		@return PMReal 
	 */
	virtual PMReal GetProxyReferenceXSkew() = 0;

	/**	Return a line representing the line when proxy is using line appearance.
		@param none
		@return PMLine 
	 */
	virtual PMLine GetProxyReferenceLine() = 0;

	/**	Set the appearance of the proxy. There are several ways proxy can be drawn.
		@param appearance the new appearance
		@see IReferencePointData
	 */
	virtual void SetProxyAppearance(const IReferencePointData::ReferenceAppearance& appearance) = 0;

	/**	Return the appearance of the proxy
		@param none
		@return IReferencePointData::ReferenceAppearance 
	 */
	virtual IReferencePointData::ReferenceAppearance GetProxyAppearance() = 0;

	/**	Set the position of the proxy (where the black dot draws). Usually one of 9 positions.
		@param position the new position
		@see IReferencePointData.h
	 */
	virtual void SetProxyPosition(const IReferencePointData::ReferencePointPosition& position) = 0;

	/**	Return the current position of the proxy. Usually one of 9 positions.
		@param none
		@return IReferencePointData::ReferencePointPosition 
	 */
	virtual IReferencePointData::ReferencePointPosition GetProxyPosition() = 0;

	/**	Recompute the position and appearance of the proxy using the IReferencePointSuite
		@param selectionManager 
		@param pathInfo Obsolete, unused argument
		@see IReferencePointSuite.h
	 */
	virtual void UpdateProxyState(ISelectionManager* selectionManager, IControlView* view, PathInfo* pathInfo) = 0;

	/**	Update rotation, scale and skew from the selection manager
		@param selectionManager 
	 */
	virtual void UpdateProxyValues(ISelectionManager* selectionManager) = 0;

	/**	Update the rotation from the current selection.
		@param selectionManager 
	 */
	virtual void UpdateProxyRotation(ISelectionManager* selectionManager) = 0;

	/**	Update the scale from the current selection.
		@param selectionManager 
	 */
	virtual void UpdateProxyScale(ISelectionManager* selectionManager) = 0;

	/**	Update the skew from the current selection.
		@param selectionManager 
	 */
	virtual void UpdateProxySkew(ISelectionManager* selectionManager) = 0;

	/**	Return if the appearance is row only (just 3 points drawn horizontally) or not.
	@return bool16 kTrue for row appearance, kFalse otherwise.
	*/
	virtual bool16 GetProxyIsRow() = 0;

	/**	Set the appearance to row only (just 3 points drawn horizontally).
	@param isRow kTrue for row appearance, kFalse will set nine points appearance.
	*/
	virtual void SetProxyIsRow(bool16 isRow) = 0;

	/**	Return if the appearance is column only (just 3 points drawn vertically) or not.
	@return bool16 kTrue for column appearance, kFalse otherwise.
	*/
	virtual bool16 GetProxyIsColumn() = 0;

	/**	Set the appearance to row only (just 3 points drawn vertically).
	@param isColumn kTrue for row appearance, kFalse will set nine points appearance.
	*/
	virtual void SetProxyIsColumn(bool16 isColumn) = 0;

};

#endif
