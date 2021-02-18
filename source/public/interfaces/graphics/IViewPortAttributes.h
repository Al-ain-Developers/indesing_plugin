//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IViewPortAttributes.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IViewPortAttributes__
#define __IViewPortAttributes__

#include "PMRect.h"
#include "GraphicsID.h"
class IControlView;

typedef ClassID VPAttrID;

/**
 Provides the interface for determining the set of attributes supported by a port
 */
class IViewPortAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IVIEWPORTATTRIBUTES };
	
	/**
	 Bitmap output options
	 */
	enum 
	{
		kViewPortBMSampleOmit_Inval = 0,
		kViewPortBMSampleHiRes,
		kViewPortBMSampleLowRes,
		kViewPortBMSampleOptimized
	};

	/**
	 Initializes the attributes available by the Get methods below.
	 A ViewPortBoss should call Initialize() before each time it begins
	 to draw in order to be sure that the attributes are up to date.
	 The optional IDataBase argument can be used by initialize to get preference
	 settings from the given database, when it is known that the ViewPort
	 is drawing one document.  The optional IControlView argument can be
	 used by initialize to get preference settings from the given IControlView.
	 
	 Note: Initialization of the ViewPortBounds must be done explicitly with 
	 SetViewPortBounds().
	 
	 @param db				IN Optional database from which to take preference settings
	 @param controlView		IN Optional view from which to take preference settings
	 @see IControlView
	 */
	virtual void Initialize(IDataBase* db = nil, IControlView *controlView = nil) = 0;

	/**
	 Gets the resolution of the view port. Currently this is used
	 when importing an EPS because MPS requires the output device's
	 resolution when creating the display list.
	 
	 @return the view port's resolution
	 */
	virtual PMReal GetViewPortResolution(void) const = 0;
	
	/**
	 Sets the resolution of the view port. Currently this is used
	 when importing an EPS because MPS requires the output device's
	 resolution when creating the display list.
	 
	 @param resolution		IN the view port's resolution
	 */
	virtual void SetViewPortResolution(PMReal resolution) = 0;

	/**
	 Gets whether the port wants to output OPI comments
	 
	 @return kTrue if the port wants to output OPI, else kFalse
	 */
	virtual bool16 GetViewPortOutputOPIComments(void) const = 0;
	
	/**
	 Sets whether the port wants to output OPI comments
	 
	 @param b				IN If kTrue, the port should output OPI
	 */
	virtual void SetViewPortOutputOPIComments( bool16 b ) = 0;

	/**
	 Gets whether the ViewPort wants to optimize re-display by cacheing things
	 like images. Cacheing is most useful when diplaying on-screen;
	 for printing and exporting, it is typically not recommended.
	 
	 @return kTrue if the port wants to cache things, else kFalse
	 */
	virtual bool16 GetViewPortCacheing(void) const = 0;
	
	/**
	 Sets whether the ViewPort wants to optimize re-display by cacheing things
	 like images. Cacheing is most useful when diplaying on-screen;
	 for printing and exporting, it is typically not recommended.
	 
	 @param cacheing		IN If kTrue, the port should cache
	 */
	virtual void SetViewPortCacheing(bool16 cacheing) = 0;

	/**
	 Gets the type of bitmap data the ViewPort wants to display, export,
	 or print
	 
	 @return one of kViewPortBMSampleOmit_Inval, kViewPortBMSampleHiRes, kViewPortBMSampleLowRes, or kViewPortBMSampleOptimized
	 */
	virtual int32 GetViewPortBitmapSampling(void) const = 0;
	
	/**
	 Sets the type of bitmap data the ViewPort wants to display, export,
	 or print
	 
	 @param sampling	IN The sampling type
	 @see IViewPortAttributes::GetViewPortBitmapSampling
	 */
	virtual void SetViewPortBitmapSampling(int32 sampling) = 0;

	/**
	 Gets the type of vector data the ViewPort wants to display, export,
	 or print
	 
	 @return one of kViewPortBMSampleOmit_Inval, kViewPortBMSampleHiRes, kViewPortBMSampleLowRes, or kViewPortBMSampleOptimized
	 */
	virtual int32 GetViewPortVectorSampling(void) const = 0;

	/**
	 Sets the type of bitmap data the ViewPort wants to display, export,
	 or print
	 
	 @param sampling	IN The sampling type
	 @see IViewPortAttributes::GetViewPortVectorSampling
	 */
	virtual void SetViewPortVectorSampling(int32 sampling) = 0;

	/** 
	 Gets whether this port wants to filter content
	 
	 @return kTrue if the port should filter content
	 */
	virtual bool16 GetViewPortFilterContent(void) const = 0;
	
	/** 
	 Sets whether this port wants to filter content
	 
	 @param filter	IN kTrue if the port should filter content
	 */
	virtual void SetViewPortFilterContent(bool16 filter) = 0;

	/**
	 Gets the port's line screen. Currently this is used in the calculation 
	 of the desired resolution when BitmapSampling is set to Optimize. 
	 Currently this is only set up for PS view ports.
	 
	 @return the port's line screen
	 */
	virtual PMReal GetViewPortLineScreen(void) const = 0;
	
	/**
	 Sets the port's line screen. Currently this is used in the calculation 
	 of the desired resolution when BitmapSampling is set to Optimize. 
	 Currently this is only set up for PS view ports.
	 
	 @param n		IN The line screen to use
	 */
	virtual void SetViewPortLineScreen( const PMReal& n ) = 0;
	
	/** 
	 Gets whether the port supports tiling
	 
	 @return whether the port supports tiling
	 */ 
	virtual bool16 GetViewPortTiling(void) const = 0;
	
	/** 
	 Sets whether the port supports tiling
	 
	 @param b		IN kTrue if the port supports tiling
	 */ 
	virtual void SetViewPortTiling( bool16 b ) = 0;

	/**
	 Gets whether the port is doing a proof print
	 
	 @return whether the port is doing a proof print
	 */
	virtual bool16 GetViewPortProofPrint(void) const = 0;
	
	/**
	 Sets whether the port is doing a proof print
	 
	 @param b		IN kTrue if the port is doing a proof print
	 */
	virtual void SetViewPortProofPrint(bool16 b) = 0;

	/**
	 Gets whether we want to make sure that we get all the image data--even
	 what has been cropped by the frame
	 
	 @return whether to disallow image cropping
	 */
	virtual bool16 GetViewPortDisallowImageCrop(void) const = 0;
	
	/** 
	 Gets whether we want to make sure that we get all the image data--even
	 what has been cropped by the frame
	 
	 @param b		IN kTrue to disallow image cropping
	 */
	virtual void SetViewPortDisallowImageCrop(bool16 b) = 0;
	
	/**
	 Gets whether placed EPS's should be omitted
	 
	 @return whether placed EPS's should be omitted
	 */
	virtual bool16 GetViewPortOmitEPS(void) const = 0;
	
	/**
	 Sets whether placed EPS's should be omitted
	 
	 @param b		IN kTrue if placed EPS's should be omitted, else kFalse
	 */
	virtual void SetViewPortOmitEPS(bool16 b) = 0;

	/**
	 Gets whether placed PDF's should be omitted
	 
	 @return whether placed PDF's should be omitted
	 */
	virtual bool16 GetViewPortOmitPDF(void) const = 0;

	/**
	 Sets whether placed PDF's should be omitted
	 
	 @param b		IN kTrue if placed PDF's should be omitted, else kFalse
	 */
	virtual void SetViewPortOmitPDF(bool16 b) = 0;

	/**
	 Gets whether placed bitmap images should be omitted
	 
	 @return whether placed bitmap images should be omitted
	 */
	virtual bool16 GetViewPortOmitBitmapImages(void) const = 0;

	/**
	 Sets whether placed bitmap images should be omitted
	 
	 @param b		IN kTrue if placed bitmap images should be omitted, else kFalse
	 */
	virtual void SetViewPortOmitBitmapImages(bool16 b) = 0;		
	
	/**
	 Sets whether to draw pasteboard shadow. Initial value is implementation 
	 dependent
	 
	 @param drawShadow	IN whether to draw pasteboard shadow
	 */
	virtual void SetViewPortDrawPasteboardShadow (bool16 drawShadow) = 0;
	
	/**
	 Gets whether to draw pasteboard shadow. Initial value is implementation 
	 dependent
	 
	 @return whether to draw pasteboard shadow
	 */
	virtual bool16 GetViewPortDrawPasteboardShadow (void) const = 0;
	
	/**
	 Sets whether to draw page shadow. Initial value is implementation dependent
	 
	 @param drawShadow	IN whether to draw pasteboard shadow
	 */
	virtual void SetViewPortDrawPageShadow (bool16 drawShadow) = 0;
	
	/**
	 Gets whether to draw page shadow. Initial value is implementation dependent
	 
	 @return whether to draw pasteboard shadow
	 */
	virtual bool16 GetViewPortDrawPageShadow (void) const = 0;
	
	/**
	 Gets whether port is a printing port. Indicates if screen drawing things 
	 should happen or not. This is the same concept as IShape::kPrinting
	 which is passed to drawing methods, though at port level.
	 
	 @return whether port is a printing port
	 */
	virtual bool16 GetViewPortIsPrintingPort (void) const = 0;

	/**
	 Sets whether port is a printing port. Indicates if screen drawing things 
	 should happen or not. This is the same concept as IShape::kPrinting
	 which is passed to drawing methods, though at port level.
	 
	 @param b	IN whether port is a printing port
	 */
	virtual void SetViewPortIsPrintingPort( bool16 b ) = 0;

	/**
	 Tests whether an attribute is defined

	 These are an extensible system for new attributes.  It's simply a map
	 from the VPAttrID to a PMReal (commonly just using the integer portion).
	 If you have a simple attribute you want to add, this is a good way to
	 do it without having to modify the ViewPortAttributes interface.

	 Currently the following attributes use this method:
		kXPIsMaskPortVPAttr - See XPID.h
		kSpotOVPModeVPAttr - See PrintID.h
		
	 @param attr		IN The attribute to check
	 @return kTrue if attribute is defined, else kFalse
	 */
	virtual bool32 IsAttrDefined(VPAttrID attr) const = 0;
	
	/**
	 Sets the value for an attribute as an integer
	 
	 @param attr		IN The attribute to set
	 @param value		IN The attribute's value
	 @see IViewPortAttributes::IsAttrDefined
	 */
	virtual void SetAttr(VPAttrID attr, int32 value) = 0;

	/**
	 Sets the value for an attribute as a real
	 
	 @param attr		IN The attribute to set
	 @param value		IN The attribute's value
	 @see IViewPortAttributes::IsAttrDefined
	 */
	virtual void SetAttr(VPAttrID attr, PMReal value) = 0;
	
	/**
	 Gets the value for an attribute as an integer
	 
	 @param attr		IN The attribute to set
	 @param defVal		IN The attribute's default value
	 @return the attribute's value if defined, else defVal
	 @see IViewPortAttributes::IsAttrDefined
	 */
	virtual int32 GetAttr(VPAttrID attr, int32 defVal = 0) const = 0;
	
	/**
	 Gets the value for an attribute as a real
	 
	 @param attr		IN The attribute to set
	 @param defVal		IN The attribute's default value
	 @return the attribute's value if defined, else defVal
	 @see IViewPortAttributes::IsAttrDefined
	 */
	virtual PMReal GetAttrReal(VPAttrID attr, PMReal defVal = 0.) const = 0;
};
#endif
