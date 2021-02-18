//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorData.h $
//  
//  Owner: Jack Kirstein
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
//  Purpose of Interface:
//  This persistant interface is the storage interface for colors. Colors are stored
//  as components and a space tag.
//  
//========================================================================================

#pragma once
#ifndef __IColorData__
#define __IColorData__

#include "IPMUnknown.h"
#include "ColorSystemID.h"
#include "GraphicTypes.h"

#include "K2Vector.h"
typedef K2Vector<PMReal> ColorArray;

/**	An interface for InDesign document color data or UI color data.
*/
class IColorData : public IPMUnknown
{
	public:
	
		enum { kDefaultIID = IID_ICOLORDATA };
		
		/**	Return the color space. Color space can be one of kPMCsCalRGB, kPMCsCalCMYK, kPMCsLab, or
			kPMCsDeviceN.
			@return the color space.
			@see GraphicTypes.h
		*/
		virtual int32 GetColorSpace() const = 0;

		/**	Return the color array corresponding to the color space.
			@return the ColorArray.
		*/
		virtual const ColorArray& GetColorData() const = 0;

		/**	Return number of color components corresponding to the color space.
			For kPMCsCalRGB and kPMCsLab, number of components should be 3.
			For kPMCsCalCMYK, number of components should be 4.
			For kPMCsDeviceN, number of components should match the number of inks.
			@return the number of color components.
		*/
		virtual int32 GetNumComponents() const = 0;
		
		/**	Return nth component of the color array corresponding to the color space.
			@param index the nth component starting with 0.
			@return the nth component of color array.
		*/
		virtual PMReal GetNthComponent( int32 index ) const = 0;

		/**	Sets the color space. Color space can be one of kPMCsCalRGB, kPMCsCalCMYK, kPMCsLab, or
			kPMCsDeviceN.
			@see GraphicTypes.h
			@param space the color space to set.
		*/
		virtual void SetColorSpace(int32 space) = 0;

		/**	Sets the color array corresponding to the color space. Typically color space is set first
			before setting the color array.
			@param componentArray the color array to set.
			@see GraphicTypes.h
		*/
		virtual void SetColorData(const ColorArray& componentArray) = 0;
		
		
		/**	Sets the color space and the corresponding color array. 
			@param space the color space to set.
			@param componentArray the color array to set.
			@see GraphicTypes.h
		*/
		virtual void SetColorData(int32 space, const ColorArray& componentArray) = 0;

		/**	Compares two color data. Returns kTrue if they are equal.
			@param iColorData the color data to compare to.
			@return kTrue if they are equal, otherwise returns kFalse.
		*/
		virtual bool16 IsEqual (const IColorData* iColorData) const = 0;
    
        /** Sets the value of convertToHSB flag as True if the colorspace set is HSB
            @param convertToHSB bool value to set
        */
        virtual void SetConvertToHSB(bool16 convertToHSB) = 0;
    
        /** Return the value of flag convertToHSB
         */
        virtual bool16 GetConvertToHSB() const = 0;
    
        
};

#endif
