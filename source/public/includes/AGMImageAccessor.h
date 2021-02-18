//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AGMImageAccessor.h $
//  
//  Owner: dstephens
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
//  Description:
//  This class is simply a wrapper around an AGMImageRecord which provides convenient
//  accessor methods such that 3rd parties can at least know what the properties
//  of the AGMImageRecord.
//  
//========================================================================================

#pragma once
#ifndef __AGMImageAccessor__
#define __AGMImageAccessor__


#include "BravoForwardDecl.h"

/**
	The purpose of an AGMImageAccessor is simply to wrap an AGM Image such that 3rd parties
	can at least know the properties of the image without knowing specifics of the internals.
*/
class PUBLIC_DECL AGMImageAccessor
{
public:	
	/** Destructor
	*/
	virtual ~AGMImageAccessor();
	
	/** Get the InDesign color space family.  Possible values include kPMRGBColorSpace,
		kPMCMYKColorSpace, kPMGrayColorSpace, and kPMICCLabColorSpace.
	*/
	virtual uint32 GetPMColorFamily(void) const = 0;
	
	/** Get the AGM color space family.  Possible values include kAGMCsCMYK,
		kAGMCsRGB, kAGMCsGray, and kAGMCsLab.
	*/
	virtual uint16 GetAGMColorFamily(void) const = 0;
	
	/** Get a pointer to the pixel buffer.  If the image is a virtual image, then nil
		will be returned.
	*/
	virtual const uint8* GetBaseAddr(void) const = 0;
	
	/** Get the number of bytes per row.
	*/
	virtual uint16 GetRowBytes(void) const = 0;
	
	/** Get the number of bits per pixel
	*/
	virtual uint16 GetBitsPerPixel(void) const = 0;
	
	/** Get the bounds of the image
	*/
	virtual Int32Rect GetBounds(void) const = 0;
	
	/** If the image is colormapped, fill in the provided buffer with the colors in the map.
		@param colors - IN/OUT - out return, will be filled with the colors in the map.
		@return the number of colors in the table
	*/
	virtual uint32 GetColorMap(uint8** colors) const = 0;
	
	/** Fills in the provided decodeArray paramater with the values of the decode array if one exists.
		@param decodeArray - IN/OUT
	*/
	virtual void GetDecodeArray(const float** decodeArray) const = 0;
	
	/** GetAGMImageRecord() really should not be called any more as of InDesign 3.0.  Calling this
		routine will cause the construction of an AGMImageRecord based on a CAGMImage.
	*/
	virtual const _t_AGMImageRecord* GetAGMImageRecord(void) const = 0;

	/** GetCAGMImage will return the underlying CAGMImage.
	*/
	virtual const CAGMImage& GetCAGMImage(void) const = 0;
};

/** Construct an AGMImageAccessor using an AGMImageRecord.
	@param image - IN - the ptrs within 'image' will be owned by AGMImageAccessor so
	do not delete them
	@param imageCS - IN - the colorspace to use; if nil it'll be uncalibrated.
*/
PUBLIC_DECL AGMImageAccessor *CreateAGMImageAccessor(_t_AGMImageRecord& image, AGMColorSpace* imageCS = nil);

/** Construct an AGMImageAccessor using a CAGMImage.
	@param image - IN - the ptrs within 'image' will be owned by AGMImageAccessor so
	do not delete them
*/
PUBLIC_DECL AGMImageAccessor *CreateAGMImageAccessor(const CAGMImage& image);
	
#endif