//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttrGradient.h $
//  
//  Owner: Jesse Jones
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
#ifndef __ITableAttrGradient__
#define __ITableAttrGradient__

#include "IPMUnknown.h"
#include "PMPoint.h"
#include "TablesID.h"
#include "PMRect.h"

const PMRect kUnitArea(0.0, 0.0, 1.0, 1.0);
/**
	Abstract interface representing table attribute that stores gradient parameters.
	Both the fill and the stroke of a cell in a table can have gradient attributes associated.
*/
class ITableAttrGradient : public IPMUnknown {

public:
	enum {kDefaultIID = IID_ITABLEATTRGRADIENT};
	
	/** Accessor for the gradient "start-point". 

		For linear gradients this is the start point. For radial
		gradients this is the inner center point. 

		@param 		area -- usually the bounds of the Table Frame, point is returned relative to the area,
					if no area is passed in then the normalized point is returned
		@return		StartPt relative to the area, Normalized if no area is passed in

	*/
	virtual PMPoint		GetStartPt(const PMRect& area = kUnitArea) const = 0;

	/** Mutator for the gradient "start-point".

		For linear gradients this is the start point. For radial
		gradients this is the inner center point. 

		@param value: New StartPt
 		@param 		area -- usually the bounds of the Table Frame to normalize the point,
					if no value is passed in we assume it is normalized
	
	*/
	virtual void		SetStartPt(const PMPoint& value, const PMRect& area = kUnitArea) = 0;
						
	/** Accessor for the gradient angle.

		Angle and length specify a vector that is anchored at start
		point and points to the end point. For a linear gradient this 
		specifies the rectangle in the table frame that encompasses the 
		gradient. For a radial gradient this defines the inner disk.
		Note that angles are in degrees...
		
		@param 		area -- usually the bounds of the Table Frame, point is returned relative to the area,
					if no area is passed in then the normalized point is returned
		@return
	*/
	virtual PMReal		GetAngle(const PMRect& area = kUnitArea) const = 0;

	/** Accessor for the gradient length. See GetAngle().

		@param 		area -- usually the bounds of the Table Frame, length is returned relative to the area,
					if no area is passed in then the normalized length is returned
		@return length relative to the area, Normalized if no area is passed in
	*/
	virtual PMReal		GetLength(const PMRect& area = kUnitArea) const = 0;

	/** Mutator for the gradient end-point.

		@param length
		@param angle
		@param 		area -- usually the bounds of the Table Frame to normalize the point,
					if no value is passed in we assume it is normalized
	*/
	virtual void 		SetEndPt(const PMReal& length, const PMReal& angle, const PMRect& area = kUnitArea) = 0;
	
	/** Accessor for the hilite angle, only relevant to radial gradients.

		Hilite length and hilite angle are only used for radial gradients
		when you click (not drag) with the gradient tool. They are used to
		define the outer circle.
		@param 		area -- usually the bounds of the Table Frame, point is returned relative to the area,
					if no area is passed in then the normalized point is returned
		@return
	*/
	virtual PMReal		GetHiliteAngle(const PMRect& area = kUnitArea) const = 0;
					
	/** Accessor for the hilite length, only relevant to radial gradients.

		@param 		area -- usually the bounds of the Table Frame, length is returned relative to the area,
					if no area is passed in then the normalized length is returned
		@return
	*/
	virtual PMReal		GetHiliteLength(const PMRect& area = kUnitArea) const = 0;

	/** Mutator for the hilite length, only relevant to radial gradients.

		@param length
		@param angle
		@param 		area -- usually the bounds of the Table Frame to normalize the point,
					if no value is passed in we assume it is normalized
	*/
	virtual void 		SetHilite(const PMReal& length, const PMReal& angle, const PMRect& area = kUnitArea) = 0;

	/** Method to allow a comparison of this gradient attribute and a comparand.

		@param rhs specifies the gradient to compare this gradient against

		@return kTrue if the gradients are equal, kFalse otherwise
	*/
	virtual bool16		IsEqual(const ITableAttrGradient* rhs) const = 0;

	
	/** Mutator for the angle

		Use SetAngle & SetLength only if you call SetStartPt with kUnitArea.
		See GetAngle for dicussion of angle
		
		@param 		angle of normalized vector
		@return
	*/
	virtual void		SetAngle(const PMReal& angle)  = 0;

	/** Mutator for the gradient length.

		Use SetAngle & SetLength only if you call SetStartPt with kUnitArea.
		See GetAngle for discussion of length.

		@param		length length of normalized vector
	*/
	virtual void		SetLength(const PMReal& length) = 0;
	
};

#endif
