//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradientFill.h $
//  
//  Owner: Thanh Nguyen
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
//  Defines the gradient fill interface for objects that support being filled.
//  
//========================================================================================

#pragma once
#ifndef __IGradientFill__
#define __IGradientFill__

#include "IPMUnknown.h"					  
#include "IColorData.h"
#include "K2Vector.h"
#include "GradientFillID.h"
#include "GraphicTypes.h"

/**	A gradient data interface. This is a required data interface for
	all gradient rednering objects of class kGradientFillRenderObjectBoss.
	@see GradientFillID.h
	@see GraphicTypes.h
	@see also IRenderingObject
	@see also IGradientFillInstall
*/
class IGradientFill : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRADIENTFILL };

public:

	/**	Set gradient type. Gradient type is either kAxial or kRadial.
		@param gradType the new gradient type to set.
		@see GraphicTypes.h
	*/
	virtual void SetGradientFillType (const GradientType& gradType) = 0;
	/**	Initialize the nubmer color stops this gradient will have.
		@param gradColorNum the number of color stops to set..
	*/
	virtual void SetNumberOfStop(int16 gradColorNum) = 0;
	/**	Set the nth color stop color UID. 
		@param index the nth color stop to set starting from 0.
		@param colorUID the new color UID to set.
		This colorUID is any color rendering objects, kPMColorBoss.
		@see ColorSystemsID.h
		@see IColorData
	*/
	virtual void SetNthGradientColorUID(int16 index, UID colorUID) = 0;
	/**	Set the nth color stop position. This value should be a number between 0 and 1.
		@param index the nth stop position to set starting from 0.
		@param boundValue the new color position.
	*/
	virtual void SetNthStopPosition(int16 index, PMReal boundValue) = 0;
	/**	Set the nth midpoint position. The minimum mid point position is 0.13, the
		maximum is 0.87, and the default value is 0.5.
		@param index the nth midpoint to set starting from 0.
		@param boundValue the new midpoint position.
	*/
	virtual void SetNthGradientMidPoint(int16 index, PMReal midPoint) = 0;

	/**	Set the nth relative midpoint position.
		@param index the nth color stop to set starting from 0.
		@param value the new relative mid point position.
	*/
	virtual void SetNthMidPointRelativeLocation(int16 index, PMReal value) = 0;

	/**	Insert the specified color UID at the nth position.
		@param index the nth color stop to insert starting from 0.
		@param colorUID the new color UID to insert.
		This colorUID is any color rendering objects, kPMColorBoss.
		@see ColorSystemsID.h
		@see IColorData
	*/
	virtual void InsertGradientColorUID (int16 index, UID colorUID) = 0;

	/**	Remove the specified color UID from the nth position.
		@param index the nth color stop to remove starting from 0.
	*/
	virtual void RemoveNthGradientColorUID (int16 index) = 0;

	/**	Remove all gradient data and set it back to the default gradient.
	*/
	virtual void ClearAll() = 0;

	/**	Return the list of IColorData corresponding to the list of gradient color stops.
		@param colorDataList the list of IColorData.
		@see IColorData
	*/
	virtual void QueryColorData(K2Vector<IColorData*>* colorDataList) = 0;
	/**	Return the IColorData corresponding the nth gradient color stop.
		@param at the nth color stop starting from 0.
		@return the requested IColorData*. This could be nil if nth color UID is no longer valid.
	*/
	virtual IColorData* CreateNthColorData(int16 at) const = 0;
	/**	Return the color swatch UID corresponding the nth gradient color stop.
		@param at the nth color stop starting from 0.
		@return the requested color UID.
	*/
	virtual UID GetNthGradientColorUID(int16 index) const = 0;
	/**	Return the gradient type. This is either kAxial or kRadial.
		@return the gradient type.
		@see GraphicTypes.h
	*/
	virtual GradientType GetGradientFillType() const = 0;
	/**	Return the number of gradient stops.
		@return the number of gradient stops.
	*/
	virtual int16 GetNumberOfStop() const = 0;
	/**	Return the nth color stop position.
		@param index the nth color stop position starting from 0.
		@return the color stop position.
	*/
	virtual PMReal GetNthStopPosition(int16  index) const = 0;
	/**	Return the nth midpoint position.
		@param index the nth color stop position starting from 0.
		@return the midpoint position.
	*/
	virtual PMReal GetNthGradientMidPoint(int16 index) const = 0;
	/**	Return the nth relative midpoint position.
		@param index the nth color stop position starting from 0.
		@return the relative midpoint position.
	*/
	virtual PMReal GetNthMidPointRelativeLocation(int16 index) const = 0;

	/**	Return kTrue if both sets of gradient data are equal.
		@param pMatch the gradient data to compare with.
		@return kTrue if equal otherwise kFalse.
	*/
	virtual bool16 Equals( IGradientFill* pMatch ) const = 0;

	/**	Return the data base associated with this gradient data.
		@return the data base associated with this gradient data.
		IDataBase* can be nil if gradient object does not have a assoicated
		database or if a data base cannot be identified.
	*/
	virtual IDataBase* GetDataBase (void) = 0;
};

#endif // __IGradientFill__







