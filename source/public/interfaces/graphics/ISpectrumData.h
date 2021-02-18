//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISpectrumData.h $
//  
//  Owner: SusanCL
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
#ifndef __ISpectrumData__
#define __ISpectrumData__

#include "IColorData.h"

class PMPoint;

/**	A data interface for the color bar widget in the color picker panel.
*/
class ISpectrumData : public IPMUnknown
{
public:

	/**	LocationType specfies where the click occurred in the color bar.
	*/
	enum LocationType
	{
		/**	kNotInSpectrumBar indicate that the click is not in the color bar.
		*/
		kNotInSpectrumBar,
		/**	kInColorBar indicate that the click is in the color bar.
		*/
		kInColorBar,
		/**	kInMinSwatch indicate that the click is in the minimum swatch proxy
			at the end of the color bar.
		*/
		kInMinSwatch,
		/**	kInMaxSwatch indicate that the click is in the maximum swatch proxy
			at the end of the color bar.
		*/
		kInMaxSwatch
	};

	
	/**	Initialize two tables internally required to setup the default color bar bitmap. Four
		color spaces are suppported: CMYK, RGB, LAB, and Grayscale.
		Table1 contains the ramps column-wise.
		Table2 contains the ramps row-wise.
		@param colorspace specifies the color space to set up the tables for.
		@param width specifies the pixel width of the table.
		@param height specifies the pixel height of the table.
		@param doHiRes whether or not we are operating in hi-res mode (affects position-to-color calculations).
		@param doBWSwatch is true if color bar setup includes the minimum and maximum swatch proxy.
	*/
	virtual void InitializeTables( const int32 colorspace, const int16 width, const int16 height, bool16 doHiRes, bool16 doBWSwatch) = 0;
	
	/**	Initialize the transition table internally required to setup the tint transition.
		@param colorspace specifies the color space to set up the transition table for.
		@param components specifies the color values for the transition table.
		@param width specifies the pixel width of the transition table.
		@param height specifies the pixel height of the transition table.
		@param doHiRes whether or not we are operating in hi-res mode (affects position-to-color calculations).
		@param doBWSwatch is true if color bar setup includes the minimum and maximum swatch proxy.
	*/
	virtual void InitializeTransition( const int32 colorspace, const ColorArray& components, const int16 width, const int16 height, bool16 doHiRes, bool16 doBWSwatch) = 0;
	
	/**	Returns the pointer to Table1
	*/
	virtual uint8* GetTable1() const = 0;
	
	/**	Returns the pointer to Table2
	*/
	virtual uint8* GetTable2() const = 0;

	/**	Map a position in the color bar to a color value represented by the point.
		@param where specifies the point in the color bar.
		@param wantTransitionFract is true if mapping for transition table.
		@return a color value in the color space of the color bar.
	*/
	virtual ColorArray		MapPositionToColor(const PMPoint& where, bool16 wantTransitionFract = kTrue) = 0;
	
	/**	Map a position in the color bar to location type represented by the point.
		@param where specifies the point in the color bar.
		@return a location type in the color color.
	*/
	virtual LocationType	MapPositionToLocation(const PMPoint& where ) = 0;
};

#endif
