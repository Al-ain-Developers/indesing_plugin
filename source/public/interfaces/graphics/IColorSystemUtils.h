//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorSystemUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IColorSystemUtils__
#define __IColorSystemUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "BravoForwardDecl.h"

#include "IColorData.h"

#include "ColorSystemID.h"
#include "ShuksanID.h"

#include "GraphicTypes.h"
#include "PMString.h"
#include "K2Vector.h"

class	IGraphicsPort;
class	IDocument;
class	IInkData;
class	IColorOverrides;
class	IColorSpaceMgr;
class	IDataBase;
class	IInkList;
class	IViewPortAttributes;


/**	Utility for InDesign color rendering object.
*/
class IColorSystemUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORSYSTEMUTILS };


	/**	Construct a string based on the color space and color value array. e.g. R=xx B=yy G=zz. 
		@param colorSpace specifies the color space to use.
		@param colorValueArray specifies the color values.
		@param doUseComma is kTrue then a comma is added after each component.
		@return a string.
		@precondition the colorValueArray's component values must be already in the desired range.
		For RGB color space, the range is [0,255], for CMYK [0,100].
	*/
	virtual PMString GetColorInfoString( const int32& colorSpace, 
											const ColorArray& colorValueArray, 
											bool16 doUseComma ) = 0;



	/**	Query for the base rendering object's interface
		@param iDataBase the database of the object to use.
		@param renderObjectUID specifies the object's UID.
		@param iidToQuery is the PMIID to query.
		@return the interface pointer for the requested interface.
	*/
	virtual IPMUnknown* QueryBaseRenderObject(IDataBase* iDataBase, UID renderObjectUID, PMIID iidToQuery = IID_IUNKNOWN) = 0;

	/**	Query for the base rendering object's interface
		@param object specifies the object to query.
		@param iidToQuery is the PMIID to query.
		@return the interface pointer for the requested interface.
	*/
	virtual IPMUnknown* QueryBaseRenderObject(IPMUnknown* object, PMIID iidToQuery = IID_IUNKNOWN) = 0;

	/**	Return the specified swatch's tint value. tint is kInvalidTintPercent if swatch does not have
		a tint value or if swatch is not a color swatch.
		@param swatchRef specifies the UIDRef of the swatch.
		@return the tint percent.
	*/
	virtual PMReal GetTintValueFromSwatch(const UIDRef& swatchRef) = 0;

	/**	Return the specified color object's tint value. tint is kInvalidTintPercent if swatch does not have
		a tint value or if swatch is not a color swatch.
		@param colorObject specifies the color object.
		@return the tint percent.
	*/
	virtual PMReal GetTintValueFromColorObject(IPMUnknown* colorObject) = 0;

	/**	Return tint percentage of the given database's active fill or stroke attribute
		depending on whether fill or stroke proxy is active.
		@param iDataBase specifies the data base.
	*/
	virtual PMReal GetCurrentActiveTintValue( IDataBase* iDataBase ) = 0;

	//___________________________________________________________________________________

	/**	Creates and returns the AGM color space from the specified color and ink data. 
		This version does not take any view port attribute into consideration.
		It uses the default CMS off settings. It assumed the target graphic port is screen.
		@param colorFamily specifies the color space.
		@param colorArray specifies color value.
		@param inkUIDList specifies the ink components for this color.
		@return an AGMColorSpace for this color space.
	*/
	virtual AGMColorSpace* NewAGMColorSpace (int32 colorFamily, const ColorArray& colorArray, const UIDList* pInkUIDList, IInkList* iInkList = nil) = 0;

	/**	Creates and returns the AGM color space from the specified color swatch UIDRef.
		This version ignores the view port settings. It uses the default CMS off settings. 
		It assumed the target graphic port is screen.
		To accurately reflect the current port settings, use GetColorSpaceAndColorValue()
		@param swatchRef specifies the UIDRef of the color swatch.
		@return the AGMColorSpace created from the specified color swatch.
		@precondition The color swatch UIDRef must be an InDesign persistent color object (kPMColorBoss).
	*/
	virtual AGMColorSpace* NewAGMColorSpaceFromColorSwatch (const UIDRef& swatchRef) = 0;

	/**	Creates the color space and gets color value from the given color swatch UIDRef.
		@param doPrint is kTrue if graphic port is a printer port.
		@param swatchRef specifies the UIDRef of the color swatch.
		@param tint specifies the tint percentage of the color swatch.
		@param colorSpace returns the AGMColorSpace for this swatch.
		@param colorValue returns the AGM color values for this swatch.
		@param gPort specifies the graphic port for this AGMColorSpace.
		@precondition The color swatch UIDRef must be an InDesign persistent color object (kPMColorBoss).
	*/
	virtual void GetColorSpaceAndColorValue(bool16 doPrint, const UIDRef& swatchRef, const PMReal& tint,
												AGMColorSpace **colorSpace, float *colorValue, IGraphicsPort* gPort = nil) = 0;


	/**	Release the AGMColorSpace. This is the AGMColorSpace created from
		GetAGMColorSpace, GetAGMColorSpaceFromColorSwatch, and GetColorSpaceAndColorValue().
		@param colorSpace specifies the AGMColorSpace to be released.
	*/
	virtual void ReleaseColorSpace(AGMColorSpace *colorSpace) = 0;

	/**	Set the color value and color space specified by colorFamily and colorArray in the given port.
		This version ignores the view port settings. It uses the default CMS off settings. 
		It assumed the target graphic port is screen. To accurately reflect the color in the
		graphics port, use the version which specifies the complete color data.
		@param gPort specifies the graphic port for this AGMColorSpace.
		@param IColorData specifies the color data.
		@param tint specifies the tint percentage of the color swatch.
		@param inkUIDList specifies the ink components for this color.
	*/
	virtual void SetColorSpaceAndColorValue (IGraphicsPort *gPort, int32 colorFamily, const ColorArray& colorArray, const PMReal& tint, const UIDList* pInkUIDList = nil) = 0;

	/**	Set the color value and color space in the given port. This version is only called from
		within the implementation of ColorRenderingObject.
		@param gPort specifies the graphic port for this AGMColorSpace.
		@param IColorData specifies the color data.
		@param iAltColorData specifies the alternate color data.
		@param iInkData specifies the ink data.
		@param iCORides specifies the color overrides data.
		@param iCSMgr specifies the color managment manager to use.
		@param tint specifies the tint percentage of the color object.
	*/
	virtual void SetColorSpaceAndColorValue( IGraphicsPort *gPort, IColorData* iColorData, IColorData* iAltColorData, 
												IInkData* iInkData, IColorOverrides* iCORides, 
												IColorSpaceMgr* iCSMgr, const PMReal& tint ) = 0;

	/**	Transform source color array to destination color array based on current document CMS setting.
		If iDoc is nil, the current front document is used.
		@param iDoc specifies which the CMS setting should be used.
		@param srcArray is the source color array to be converted.
		@param srcColorSpace is the color space of the source color array.
		@param dstColorSpace is the color space to transform the source color to.
		@param pInkUIDList specifies the ink components for the source color array.
		@param iInkList specifies the IInkLIst for the ink components. Specify an IInkList if inks in pInkUIDList
		are not in the same database as the document or application database.
	*/
	virtual ColorArray ColorTransform( IDocument* iDoc, ColorArray srcArray, int32 srcColorSpace, int32 dstColorSpace, const UIDList* pInkUIDList = nil, IInkList* iInkList = nil) = 0;

	/**	Compute the tinted color components given a base color array and a tint percent between 0 and 100 percent.
		@param colorSpace is the color space of the color value.
		@param colorArray is the color values
		@param tint is the tint percentage in the range [0, 100].
		@return tint color array.
	*/
	virtual ColorArray GetTintedColorComponents(int32 colorSpace, ColorArray colorArray, PMReal tint) = 0;
	
	/**	Get the specified color swatch's color space and color array.
		If color swatch is a tint swatch, the tint percent is returned otherwise returns kDefaultTintPercent.
		@param colorRef specifies the color swatch UIDRef to get the color information from.
		@param colorspace returns the swatch's color space.
		@param colorArray returns the swatch's color component array.
		@param tint returns the swatch's tint value. If not a tint swatch, kDefaultTintPercent is returned..
	*/
	virtual void GetColorSwatchColorSpaceAndValue (const UIDRef& colorRef, int32& colorspace, ColorArray& colorArray, PMReal& tint) = 0;

	/**	Returns true iff the color is white -- that is, that the color will not mark any plate
		with a nonzero value.
		@param swatchRef is the swatch you're curious about.
		@param tint is the tint to apply. If the swatch is a tint swatch then the two tints multiply.
		@param useAltspaceOnly If true, non-process colors (spots and deviceN) are effectively
		converted to process; that is, their altspace value is used rather than considering contribution 
		on plates.  Note that this only makes a difference if a spot is defined as white.
	*/
	virtual bool32 IsWhite(const UIDRef& swatchRef, PMReal tint = kDefaultTintPercent, bool32 useAltspaceOnly = kFalse) = 0;
	
	/** Returns true iff, given the viewport attributes, the paper swatch should be represented by CMYK white
		(or whatever other paper strategy is appropriate for the port) as opposed to its native color as defined
		in the swatch list.  At present this returns true when printing, when previewing overprint, or when 
		proofing with paper white; but it may be more sophisticated in the future.
		@param iAttr The view port attributes to inspect.
		@return True if the Paper swatch should be drawn with CMYK white.
	*/
	virtual bool32 ShouldIgnorePaperColor(IViewPortAttributes* iAttr) = 0;
    
	/** RGBToHSB() a utility function to convert the RGBColor Values to their corresponding HSBColor Values. 
    	HSB is also known as HSV, argument name uses v instead of b to not to conflict with b of rgb.
	*/
    virtual void RGBToHSB( PMReal r, PMReal g, PMReal b, PMReal &h, PMReal &s, PMReal &v ) = 0;
    
	/** HSBToRGB() a utility function to convert the HSBColor Values to their corresponding RGBColor Values. 
    	HSB is also known as HSV, argument name uses v instead of b to not to conflict with b of rgb.
	*/
    virtual void HSBToRGB( PMReal h, PMReal s, PMReal v, PMReal &r, PMReal &g, PMReal &b ) = 0;
};


#endif	// __IColorSystemUtils__

