//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IClippingPathSuite.h $
//  
//  Owner: Dave Stephens
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __IClippingPathSuite__
#define __IClippingPathSuite__

#include "IPMUnknown.h"

#include "ImageID.h"

class IClipSettings;
class IPathGeometry;

/** The IClippingPathSuite is used to obtain clipping path information about the current selection
	and to apply clipping paths to the current selection.  As an alternative to clipping paths,
	you might consider creating a soft mask in Photoshop because InDesign supports native transparency
	within Photoshop images.
*/
class IClippingPathSuite : public IPMUnknown
{
public:
	/** Default IID
	*/
	enum { kDefaultIID = IID_ICLIPPINGPATHSUITE };

	/** Flags
	*/
	enum 
	{
		kInvertFlag				= 1 << 0,	// Invert the resulting path by combining with a path equal to the bounds of the image
		kUseHighResFlag			= 1 << 1,	// Force edge detection to use the high resolution source image (potentially much slower
											// but higher quality.  Although the 72 dpi proxy does a pretty good job).
		kAllowHolesFlag			= 1 << 2,	// For edge detection, do we remove the holes or leave them in.
		kRestrictToFrameFlag	= 1 << 3	// For edge detection, do we only detect edges within the visible portions of the image?
											// That is, do we crop the image to its frame before performing edge detection?
	};
	

/** ----- Abilities
*/	
	/**	Does the selection support clipping paths? Return kTrue or kFalse.
		@param void 
		@return CanHaveClippingPath 
	 */
	virtual bool16		CanHaveClippingPath (void) const = 0;

	/**	Does the selection have any alpha channels?
		@param void 
		@return HasAlphaChannels 
	 */
	virtual bool16		HasAlphaChannels (void) const = 0;

	/**	Does the selection have any embedded Photoshop paths?
		@param void 
		@return HasPhotoshopPaths 
	 */
	virtual bool16		HasPhotoshopPaths (void) const = 0;

	/**	Vector graphics, such as EPS and PDF, do not have a high res raster from which
		to perform edge detection.  Hence, if performing edge detection, the proxy must
		be used.
		@param void 
		@return HasHighResRaster 
	 */
	virtual bool16		HasHighResRaster (void) const = 0;

	/**	Does the selection have a clipping path and a containing frame such that
		the points on the frame can be made to match the clipping path?
		@param void 
		@return CanConvertClippingToFrame 
	 */
	virtual bool16		CanConvertClippingToFrame (void) const = 0;

/** ----- Accessors
*/
	/**	Return a pointer to the active IClipSettings.  If a clippable page item is selected, return its
		IClipSettings.  Else if a document is open, return its IClipSettings.  Else return the
		Session's IClipSettings.
		@param void 
		@return IClipSettings* 
	 */
	virtual IClipSettings* QueryActiveClipSettings(void) const = 0;

	/**	Return an AddRefed pointer to the IPathGeometry representing the current clipping path.
		If no clipping currently exists, then nil is returned.
		@param void 
		@return IPathGeometry* 
	 */
	virtual IPathGeometry* QueryActiveClippingPath(void) const = 0;

/** ----- Manipulators
*/
	/** Process commands to clip the selection.
	*/

	/**	Apply an embedded photoshop clipping path
		@param index 
		@param *pathName IN - the name of the clipping path
		@param tolerance  - a tolerance value specifying how close to the original path we must be if we smooth
			the path.  0.0 indicates a perfect match.  Smoothing may simplify the path, reducing the number of
			points.
		@param minPathSize - subpaths smaller than the minPathSize will be deleted.
		@param inset  - how far to inset the path.  Negative values cause an outset.
		@param flags - see the enum at the top of this class.
		@return  ErrorCode - kSuccess if successful.
	 */
	virtual ErrorCode	ApplyEmbeddedPath(uint16 index, const PMString *pathName, const PMReal& tolerance, const PMReal& minPathSize, 
											const PMReal& inset, uint32 flags) const = 0;


	/**	Perform edge detection on a given alpha channel.
		@param index 
		@param tolerance  - a tolerance value specifying how close to the original path we must be if we smooth
			the path.  0.0 indicates a perfect match.  Smoothing may simplify the path, reducing the number of
			points.
		@param minPathSize - subpaths smaller than the minPathSize will be deleted.
		@param inset  - how far to inset the path.  Negative values cause an outset.
		@param flags - see the enum at the top of this class.
		@param threshhold - The threshhold is a value between 0 and 255.  Any gray value 
		greater than or equal to the threshold will be mapped to white.  All other pixels will be mapped to black.
		@return  ErrorCode - kSuccess if successful.
	 */
	virtual ErrorCode	ApplyAlphaChannel(uint16 index, const PMReal& tolerance, const PMReal& minPathSize, const PMReal& inset,
											uint32 flags, uint8 threshhold) const = 0;


	/**	Convert the image to grayscale and then to 1-bit using the threshhold to determine which gray
		values will be black and which gray values will be white.  Then perform edge detection on the
		resulting 1-bit image to create a clipping path.
		@param tolerance  - a tolerance value specifying how close to the original path we must be if we smooth
			the path.  0.0 indicates a perfect match.  Smoothing may simplify the path, reducing the number of
			points.
		@param minPathSize - subpaths smaller than the minPathSize will be deleted.
		@param inset  - how far to inset the path.  Negative values cause an outset.
		@param flags - see the enum at the top of this class.
		@param threshhold 
		@return  ErrorCode - kSuccess if successful.
	 */
	virtual ErrorCode	DoDetectEdges(const PMReal& tolerance, const PMReal& minPathSize, const PMReal& inset,
											uint32 flags, uint8 threshhold) const = 0;


	/**	Remove any existing clipping path such that the image's graphic frame is the only thing
		which could be clipping the image.
		@param void 
		@return  ErrorCode - kSuccess if successful.
	 */
	virtual ErrorCode	RemoveClipping(void) const = 0;

	/** Process commands to convert the clipping path to the frame -- and delete the original clipping path.
		The result matches the behavior of InDesign 1.5, which did not have separate clipping paths.
		@param void 
		@return  ErrorCode - kSuccess if successful.
	*/
	virtual ErrorCode	DoConvertClippingToFrame (void) const = 0;

	/** Invert or un-invert the current clipping.  Change the inset amount.
		@param bInvert  - If true, then invert the current clipping.  Otherwise, remove any inversion if it exists.
		@param inset  - how far to inset the path.  Negative values cause an outset.
		@return  ErrorCode - kSuccess if successful.
	*/
	virtual ErrorCode	ApplyUserPathOptions (bool8 bInvert, const PMReal& inset) const = 0;

};

#endif // __IClippingPathSuite__
