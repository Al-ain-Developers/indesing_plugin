//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/ISnapPrefsData.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ISnapPrefsData__
#define __ISnapPrefsData__

#include "IPMUnknown.h"
#include "SnapID.h"
#include "SnapshotUtils.h"

/**	From SDK sample;  interface for SnapShot preferences data.
 * 	
 * 	@ingroup snapshot
 */
class ISnapPrefsData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISNAPPREFSDATA };

    /**    Copy the given ISnapPrefsData to here. This is a shortcut if you only
        want to change one setting, use this to copy the settings then just change the one.
        @param prefsToCopy IN the ISnapPrefsData to copy
     */
    virtual void CopyPrefs(ISnapPrefsData* prefsToCopy) = 0;

	/** 
		Set the file name to which you want your snap shot saved.
	*/
	virtual void SetName(const WideString& name) = 0;

	/**	
		Get the file name.
	*/
	virtual const WideString& GetName() = 0;

	/** 
		Set the image write format class ID.
	*/
	virtual void SetFormatClassID(const ClassID& formatClassID) = 0;

	/**
		Get the image write format class ID.
	*/
	virtual const ClassID& GetFormatClassID() = 0;

	/**
		Set the x and y scale factor.
	*/	
	virtual void SetScale(const PMReal& scale) = 0;

	/**
		Get the x and y scale factor.
	*/
	virtual const PMReal& GetScale() = 0;

	/**
		Set the image resolution.
	*/
	virtual void SetResolution(const PMReal& resolution) = 0;

	/** 
		Get the image resolution.
	*/
	virtual const PMReal& GetResolution() = 0;

	/**
		Set the minimum image resolution.
	*/
	virtual void SetMinimumResolution(const PMReal& minimumResolution) = 0;

	/**
		Get the minimum image resolution.
	*/
	virtual const PMReal& GetMinimumResolution() = 0;

	/**
		Set the bounds of the area to be drawn by the given amount of bleed.
	*/
	virtual void SetBleed(const PMReal& bleed) = 0;
	
	/**
		Get the bleed. 
	*/
	virtual const PMReal& GetBleed() = 0;

	/**
		Set the draw area, the spread that is clicked or the selected items.
	*/
	virtual void SetDrawArea(bool16 drawArea) = 0;
	
	/**
		Returns kTrue if draw the clicked spread, returns kFalse if draw the selected items.
	*/
	virtual const bool16& GetDrawArea () = 0;

	/**
		Set to kTrue to force images and graphics to draw at full resolution, otherwise draw proxies.
	*/
	virtual void SetFullResolutionGraphics(bool16 fullResolutionGraphics) = 0;

	/**
		Returns kTrue if the image is drawn at full resolution, otherwise returns kFalse.
	*/
	virtual const bool16& GetFullResolutionGraphics() = 0;

	/**
		Set to kTrue to draw grayscale, otherwise draw RGB.
	*/
	virtual void SetDrawGray(bool16 drawGray) = 0;

	/**
		Returns kTrue if image is draw in grayscale, otherwise returns kFalse.
	*/
	virtual const bool16& GetDrawGray() = 0;

	/** 
		Set the drawing flag. 
		@param drawingFlags IN If this is set to kPrinting, then it 
	  		suppresses the drawing of margins and guides. 
	  		See IShape for the drawing flags.
		@see IShape
	*/
	virtual void SetDrawingFlags(int32 drawingFlags) = 0;

	/**
		Get the drawing flag.
	*/
	virtual const int32& GetDrawingFlags() = 0;

	/** 
		Set the JPEG encoding
		@param encoding IN Set to baseline (0) or progressive (1).
	*/
	virtual void SetJPEGEncoding(const int32 encoding) = 0;

	/**
		Get the JPEG encoding.
	*/
	virtual const int32& GetJPEGEncoding() = 0;

	/**
		Set the JPEG quality: low, good, excellent and great.
	*/
	virtual void SetJPEGQuality(const int32 quality) = 0;

	/**
		Get JPEG quality.
	*/
	virtual const int32& GetJPEGQuality() = 0;

	/**
		Set the palette type for TIFF image.
		@param paletteType IN Set to kNoPalette (0), 
	  			kTryExactThenAdaptivePalette (1), kMacPalette (2), 
				kWebPalette (3) or kWinPalette (4).
	*/
	virtual void SetTIFFPaletteType(const int32 paletteType) = 0;

	/**
		Get the palette type for TIFF image.
	*/
	virtual const int32& GetTIFFPaletteType() = 0;

	/**
		Set the palette type for GIF image: 
		@param paletteType Set to kTryExactThenAdaptivePalette (0),
			kMacPalette (1), kWebPalette (2) or kWinPalette (4). 
			NOTE: kNoPalette is not an option for  GIF images as they 
	  		need a color palette.
	*/
	virtual void SetGIFPaletteType(const int32 paletteType) = 0;

	/**
		Get the palette type for GIF image.
	*/
	virtual const int32& GetGIFPaletteType() = 0;

	/** 
		Set the TIFF transparency on or off.
	*/
	virtual void SetTIFFTransparent(const bool16 transparent) = 0;

	/** 
		Get the transparency flag for TIFF image.
	*/
	virtual const bool16& GetTIFFTransparent() = 0;

	/** 
		Set the transparency flag for GIF image.
	*/
	virtual void SetGIFTransparent(const bool16 transparent) = 0;

	/** 
		Get the transparency flag for GIF image.
	*/
	virtual const bool16& GetGIFTransparent() = 0;

	/**
		Set the interlace flag for GIF image. In general, it causes
		the reader to take longer to display the image if it is set.
	*/
	virtual void SetGIFInterlaced(const bool16 interlaced) = 0;

	
	/**
		Get the interlace flag for GIF image.
	*/
	virtual const bool16& GetGIFInterlaced() = 0;
};

#endif // __ISnapPrefsData__



