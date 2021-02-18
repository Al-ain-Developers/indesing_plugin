//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorConverter.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IColorConverter__
#define __IColorConverter__

#include "IPMUnknown.h"
#include "ICMSSettings.h"
#include "ICMSProfile.h"
#include "IGraphicsPort.h"

#include "ColorMgmtID.h"
#include "BravoForwardDecl.h"

class IColorData;
class IDocument;


/*
 Structure used in Convert call below
 */
struct ColorConverterData
{
	uint16			bitsPerPixel;
	uint16			bitsPerComponent;
	void*			data;
	uint16			numComps;
};

class IColorConverter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORCONVERTER };
	
	virtual bool8 Begin(ICMSProfile *srcProfile, ICMSProfile *destProfile, ICMSSettings::renderingIntent intent) = 0;
	//This sets up the color converter for conversion. In this way, you can call "Convert" multiple times using the same
	//transform and render intent. You MUST bracket this with a call to "End".

	virtual bool8 Begin(AGMColorSpace* srcColorSpace, ICMSProfile *destProfile, ICMSSettings::renderingIntent intent) = 0;
	//This sets up the color converter for conversion. In this way, you can call "Convert" multiple times using the same
	//transform and render intent. You MUST bracket this with a call to "End".

	virtual bool8 Begin(AGMColorSpace* srcColorSpace, AGMColorSpace *destColorSpace, ICMSSettings::renderingIntent intent) = 0;
	//This sets up the color converter for conversion. In this way, you can call "Convert" multiple times using the same
	//transform and render intent. You MUST bracket this with a call to "End".
	
	virtual bool8 Begin(IDocument *doc, ICMSProfile::profileCategory categorySrc, ICMSProfile::profileCategory categoryDest, ICMSSettings::renderingIntent intent) = 0;
	//This sets up the color converter for conversion using categories (e.g., RGB source, CMYK separations).
	//As with the other Begins, you MUST bracket this with a call to "End".
	
	virtual bool8 Begin(int32 cstypeSrc, int32 cstypeDst) = 0;
	//This sets up the color converter for conversion using UNCALIBRATED METHODS.  Do NOT use this unless you know
	//that you want an uncalibrated conversion.  As with the other Begins, you MUST bracket this with a call to "End".
	
	virtual bool8 End() = 0;
	//This lets the converter know you are done converting. This will release any transforms and/or memory it allocated.
	//You MUST bracket this with a call to "Begin".

	virtual bool8 Convert(ColorConverterData *dataIn, ColorConverterData *dataOut, int32 numPixels) = 0;
	//Converts the dataIn structure using the preestablished profiles and render intent setup with a call to "Begin". Puts the
	//result in dataOut. Converts only "numPixels" worth of data, and assumes that dataIn holds at least that amount of info.
	
	virtual bool8 Convert(float *compsIn, float *compsOut) = 0;
	//Converts the colorIn using the preestablished profiles and render intent setup with a call to "Begin". Puts the
	//result in compsOut. 

	virtual bool8 Convert(IColorData *colorIn, IColorData *colorOut) = 0;
	//Converts the colorIn using the preestablished profiles and render intent setup with a call to "Begin". Puts the
	//result in colorOut.  NOTE: This interface is DISAPPEARING soon (sept 98).  Don't use this in new code. -MJP

	// Get the number of components in the source or destination color space according
	// to the current Begin() context.
	virtual int32 GetNumSourceComponents() const = 0;
	virtual int32 GetNumDestinationComponents() const = 0;

	/**
	 Provides color conversion options.
	
	 @param defRGBProfile	The default rgb profile to use for uncalibrated rgb.
	 @param defCMYKProfile	The default cmyk profile to use for uncalibrated rgb.
	 @param idealizedBlack	If true, uses idealized black conversions from CMYK to RGB/Gray.
							If false, uses accurate black conversions.
	 @param oppBlending		If true, uses XYZ-based blending for NChannel->process conversion.
							If false, blends in destination space.
	 @param fastXforms		If true, uses faster but less accurate xforms.
							If false, uses slower but more accurate xforms.
	 */
	virtual void SetColorConvertOptions
		(
			AGMColorProfile* defRGBProfile, 
			AGMColorProfile* defCMYKProfile, 
			bool32 idealizedBlack,
			bool32 oppBlending,
			bool32 fastXforms,
			IGraphicsPort::RenderingIntent defaultRI = IGraphicsPort::kRelative
		) = 0;

	/**
	 Provides color conversion options (version 2).  In this case the options will be copied
	 directly from the current port's settings.  This allows you to convert comparably to how
	 the port would -- although bear in mind that the color families identified in the Begin
	 call will always take precedent over the port's configuration.

	 @param iPort: The port from which to pull color conversion options.
	
	 */
	virtual void SetColorConvertOptions(IGraphicsPort* iPort) = 0;

	/**
	 Internal-only direct setting of all color convert options.
	
	 @param opts		A pointer to the options dictionary container.
	 @param defaultRI	Default rendering intent (default OPM is always kTrue).
	 */
	virtual void SetColorConvertOptions
		(
			void* opts, 
			IGraphicsPort::RenderingIntent defaultRI
		) = 0;
};

#endif

