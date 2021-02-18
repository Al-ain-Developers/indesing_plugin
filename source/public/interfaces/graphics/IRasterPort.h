//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRasterPort.h $
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
//========================================================================================

#pragma once
#ifndef __IRASTERPORT__
#define __IRASTERPORT__

#include "GraphicsID.h"
#include "PMMatrix.h"
#include "PMReal.h"
#include "PMRect.h"
#include "BravoForwardDecl.h"

class IOutlineInfo;

/**
 This is a viewport interface which is a shell over AGM's rasterport specific API
 Most of the methods work exactly or very similar to PostScript operators.
 See Postscript language reference manual for more info

 IMPORTANT: You CANNOT use IRasterPort methods in any drawing code you expect to print
 
 Note: Many of the methods exposed by IRasterPort use internal types and are intended 
 for internal usage only.
 */
class IRasterPort : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRASTERPORT };

		/**
		 Initializes the port. May be called multiple times to re-initialize 
		 the port if the backing port changes
		 
		 @see IAGMPortData
		 */
		virtual void Setup() = 0;

		/**
		 Returns the current gsave level in the backing port
		 
		 @return the port's gsave level
		 */
		virtual int32 currentgstatelevel() = 0;

		/**
		 Sets the backing port's device coord scale factor.
			Note: For HiDPI offscreens set the device scale before setting the user matrix
		 
		 What this does is make every currentmatrix, setmatrix call pass through this scale factor.
		 With setmatrix, first the scale factor is put into the port, then the passed
		 in matrix. With currentmatrix, the real CTM is post-unscaled before returning.
		 That essentially means that there is a scale-factor stuck on the device that you
		 can't see (except with currentclipbounds) or get rid of. So for example, if
		 you create a double-size pixelbuffer for AGM and call initdevicescale(2.) on
		 the raster port, all the existing AGM drawing code that uses setmatrix,
		 currentmatrix will be drawing double-resolution pictures without knowing it.
		 
		 @param scale	IN The device coord scale factor (implicitly 1:1 unless an HiDPI mode is in effect)
		 */
		virtual void initdevicescale(const PMReal scale = 1.0) = 0;

		/**
		 Gets the backing port's device coord scale factor
		 
		 @return The device coord scale factor
		 */
		virtual PMReal getdevicescale() = 0;

		/**
		 Sets the backing port's user coord CTM to m
			if there is a device scale factor in effect, the matrix m should not include it
		 
		 @param m		IN The new matrix
		 */
		virtual void setmatrix(const PMMatrix &m) = 0;
								
		/**
		 Gets the backing port's current user coord CTM
			if there is a device scale factor, the returned matrix will not include it
		 
		 @param m		OUT The current matrix
		 @return non-zero if the call succeeds, else zero
		 */
		virtual int8 currentmatrix(PMMatrix *m) = 0;
				
		/**
		 Gets the backing port's current line width
		 
		 @return the current line width
		 */
		virtual PMReal currentlinewidth() = 0;
		
		/**
		 Gets the backing port's current dash pattern
		 
		 @param numDash		OUT The number of dashes
		 @param dashArray	OUT The current dash array
		 @param offset		OUT The dash offset
		 */
		virtual void currentdash(int32 *numDash, Fixed **dashArray, Fixed *offset) = 0;
		
		/**
		 Gets the backing port's current line cap. See GraphicTypes.h for 
		 possible return values
		 
		 @return the current line cap
		 */
		virtual int32 currentlinecap() = 0;
		
		/**
		 Gets the backing port's current line join. See GraphicTypes.h for
		 possible return values
		 
		 @return the current line join
		 */
		virtual int32 currentlinejoin() = 0;
		
		/**
		 Gets the backing port's current miter limit
		 
		 @return the current miter limit
		 */
		virtual PMReal currentmiterlimit() = 0;
		
		/**
		 Gets the backing port's current fill bounds
		 
		 @param bounds		OUT The fill bounds
		 */
		virtual void currentfillbounds(PMRect *bounds) = 0;
		
		/**
		 Gets the backing port's current stroke bounds
		 
		 @param bounds		OUT The stroke bounds
		 */
		virtual void currentstrokebounds(PMRect *bounds) = 0;
		
		/**
		 Gets the backing port's current clip bounds in device coordinates (not user-coordinates).
		 Note that even the device scale set by initdevicescale can be seen through currentclipbounds.
		 So if you were to initdevicescale(2.0); then translate user space by (100, 100); then clip 
		 to L:0 T:0 R:10 B:10 and then asked for currentclipbounds, you would get L:200 T:200 R:220 B:220
		 -- an answer in the coordinate system of the deep down unscaled device.
		 
		 Also note that before a clip is ever set, AGM reports a wide open clip of +/- (2^30 - 2^7) of 
		 all the strange things. But the first clip will actually intersect the requested clip with the
		 extent of the pixel bounds. For example:
		 
			gport->rectclip( -double(1UL<<29),  -double(1UL<<29), double(1UL<<30), double(1UL<<30));
			rport->currentclipbounds( &rect); //...we're now down to the pixel buffer.
		
		 will reveal the actual size of the pixel buffer (sneaking past the device scale factor set
		 by initdevicescale.


		 @param bounds		OUT The clip bounds
		 */
		virtual void currentclipbounds(PMRect *bounds) = 0;

		/** 
		 Gets the backing port's current source color
		 
		 @return the current source color
		 */
		virtual AGMPaint *currentsrccolor() = 0;
		
		/**
		 This method intentionally uncommented
		 */
		virtual void currentdstcolor(AGMRasterPort *dstDevice, AGMPaint *agmPaint) = 0;

		/**
		 Tests whether the rectangle in device space would be painted by fill, 
		 taking current clip into account
		 
		 @param devRect		IN The rect to test, in device coordinates
		 @return 0 if doesn't intersect, 1 if fully intersects, or 2 if partially intersects
		 */
		virtual int8 infill(const PMRect &devRect) = 0;
		
		/**
		 Tests whether the rectangle in device space would be painted by eofill,
		 taking current clip into account
		 
		 @param devRect		IN The rect to test, in device coordinates
		 @return 0 if doesn't intersect, 1 if fully intersects, or 2 if partially intersects
		 */
		virtual int8 ineofill(const PMRect &devRect) = 0;
		
		/**
		 Tests whether the rectangle in device space would be painted by stroke,
		 taking current clip into account
		 
		 @param devRect		IN The rect to test, in device coordinates
		 @return 0 if doesn't intersect, 1 if fully intersects, or 2 if partially intersects
		 */
		virtual int8 instroke(const PMRect &devRect) = 0;
		
		/**
		 Initializes the backing port's clipping
		 */
		virtual void initclip() = 0;
		
		/**
		 Check to see if the provided rectangle is within the current clip path.

		 The rectangle provided is in user space and will be transformed to device space
		 using the current CTM before comparing with device space clip in the gstate.
		 
		 @param rect		IN The rect to test
		 @return 0 if the rect is partially clipped, 1 if it's unclipped, 2 if it's totally clipped
		 */
		virtual int8 clipclass(const PMRect &rect) = 0;
		
		/**
		 Transforms the given point by the backing port's CTM to a point in device space
		 
		 @param x			IN/OUT The x component of the point
		 @param y			IN/OUT The y component of the point
		 @return kTrue if succeeds, else kFalse
		 */
		virtual bool8 transform(PMReal *x, PMReal *y) = 0;
		
		/**
		 Transforms the given point by the inverse of the backing port's CTM (i.e. from device space to CTM space)
		 
		 @param x			IN/OUT The x component of the point
		 @param y			IN/OUT The y component of the point
		 @return kTrue if succeeds, else kFalse
		 */
		virtual bool8 itransform(PMReal *x, PMReal *y) = 0;
		
		/**
		 Gets the backing port's current path
		 
		 @param callBack	OUT The outline info to store the path
		 @see IOutlineInfo
		 */
		virtual void GetPathInfo(IOutlineInfo *callBack) = 0;
				
		/**
		 Gets backing port's error state
		 
		 @return kTrue if the backing port is in an error state, else kFalse
		 */
		virtual bool8 GetError() = 0;
		
		/**
		 Sets XOR mode on the backing port
		 
		 @param xorOn		IN The new xor mode
		 */
		virtual void SetXORMode(bool32 xorOn) = 0;
		
		/**
		 Sets the anti-aliasing policy for the backing port. 
		 
		 Returns previous policy. Allows use like this:
	 	
	 	 <pre>
	 	 int32 options = 1;
		 rasterport->setantialiaspolicy(&options);
	 	 // use the port...
	 	 rasterport->setantialiaspolicy(&options);	// Restore previous value
	 	 </pre>

		 inOutPolicy is a bit mask that can take one or more of the following:
		 1 to antialias text
		 2 to antialias graphics
		 4 prevents linearized blending for non-AGM alpha

		 @param inOutPolicy	IN/OUT The new policy on input, the old policy on output
		 */
		virtual void setantialiaspolicy(int32* inOutPolicy) = 0;
		
		/**
		 This method intentionally uncommented
		 */
		virtual void setportoptions(uint32 portOptions) = 0;
		
		/**
		 This method intentionally uncommented
		 */		
		virtual uint32 getportoptions() = 0;
		
		/**
		 Sets the device profile for the current raster port.
		 
		 @param profile		IN The profile to set
		 @see IColorSpaceMgr
		 */
		virtual bool8 SetDeviceProfile(AGMColorProfile *profile) = 0;
	
		/**
		 Determines if the backing port is in high DPI mode (device scale == 2.0)
		 
		 @return kTrue if the backing port's device scale is 2.0, else kFalse
		 */
		virtual bool8 IsHiDPI() = 0;
};

#endif
