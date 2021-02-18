//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDVPlatformOffscreen.h $
//  
//  Owner: Deepak Gupta
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
//  Core interface around Platform offscreen drawing environments
//  
//========================================================================================

#pragma once
#ifndef __IDVPlatformOffscreen__
#define __IDVPlatformOffscreen__

#include "GRRefCountedObj.h"
#include "InterfacePtr.h"

#include "DVAForwardDeclarations.h"

/** IDVPlatformOffscreen is a wrapper around a Drawbot based offscreen bitmap.
	
	@see IOffscreenViewPortCache, IDVOffscreenPortData
*/

typedef boost::intrusive_ptr<dvaui::drawbot::ImageInterface> ImageInterfaceP;

/** IDVPlatformOffscreen is a wrapper around a Drover based bitmap.
	This interface is implemented in DVPlatformOffscreen, which helps in
	creation of Drover based offscreen DRawbot object, so that all drawing happens
	offscreen. This infetrface provides functions to copy bitmap bits to/from 
	onscreen drawbot object.
 
	This inteface cannot be added to boss, instead its implementation DVPlatformOffscreen
	is used from DVOffscreenPortData.
 
 @see IDVOffscreenViewPortCache, IDVOffscreenPortData
*/
class IDVPlatformOffscreen : public grRefCountedObj 
{ 
public: 
	/**     
	Returns the underlying drawbot object
	*/ 
	virtual dvaui::drawbot::Drawbot* GetOffscreenDrawbot() const = 0; 

	/**    Get the current origin of the bitmap 
	@param x - OUT: Horizontal coordinate of the origin. 
	@param y - OUT: Vertical coordinate of the origin. 
	*/ 
	virtual void GetOrigin(int32* x, int32* y) const = 0; 

	/**    Set the origin to originPt 
	@param x - IN: New horizontal coordinate to use for the origin. 
	@param y - IN: New vertical coordinate to use for the origin. 
	*/ 
	virtual void SetOrigin(int32 x, int32 y) = 0; 


	/**    Copy pixels from srcPort into the offscreen represented by this class. 
	@param &srcDrawbot - IN: Pointer to the source drawbot. 
	@param &srcBounds - IN - the area of the port/window to copy 
	@param &dstBounds - IN - the area of the offscreen to copy into 
	@param clipRgn - IN - the area of the port/window to restrict the copy operation to. 
	*/ 
//	virtual void CopyBitsIntoOffscreen(const dvaui::drawbot::Drawbot* srcDrawbot, const Int32Rect &srcBounds, const Int32Rect &dstBounds, const SysRgn clipRgn = nil) = 0; 

	/**    Copy pixels from this offscreen into the provided port. 
	@param &dstPort - IN - Pointer to the destination drawbot  
	@param &srcBounds - IN - the area of the offscreen to copy 
	@param &dstBounds - IN - the area of the window to copy into 
	@param clipRgn - IN - the area of the offscreen to copy 
	*/ 
	virtual void CopyBitsFromOffscreen(dvaui::drawbot::Drawbot* dstDrawbot, const Int32Rect &srcBounds, const Int32Rect &dstBounds, const PMMatrix& clip2destMatrix = PMMatrix(), const SysRgn clipRgn = nil,
		int debug_cookie = 0, const char* debug_string = 0, void* debug_address = 0 //Ichabod temporary debugging code
		) = 0; 


	/**    Copy pixels from the provided offscreen into this offscreen. 
	@param srcPort - IN - the source offscreen 
	@param &srcBounds - IN - the area of the offscreen to copy 
	@param &dstBounds - IN - the area of this offscreen (the destination) to copy into 
	@param clipRgn - IN - the area of the offscreen to copy 
	*/ 
//	virtual void CopyBitsIntoOffscreen(IDVPlatformOffscreen* srcDVPlatformOffscreen, const Int32Rect &srcBounds, const Int32Rect &dstBounds, const SysRgn clipRgn = nil) = 0; 

	/**    Copy pixels from this offscreen into the provided offscreen. 
	@param dstPort - IN - the destination offscreen 
	@param &srcBounds - IN - the area of this offscreen (the source) to copy 
	@param &dstBounds - IN - the area of the provided offscreen (the destination) to copy into 
	@param clipRgn - IN - the area of the offscreen to copy 
	*/ 
	virtual void CopyBitsFromOffscreen(IDVPlatformOffscreen* dstDVPlatformOffscreen, const Int32Rect &srcBounds, const Int32Rect &dstBounds, const PMMatrix& clip2destMatrix = PMMatrix(),  const SysRgn clipRgn = nil,
		int debug_cookie = 0, const char* debug_string = 0, void* debug_address = 0 //Ichabod temporary debugging code
		) = 0; 


	/**    Returns the bounds of this offscreen 
	@return Current bounds of the offscreen. 
	*/ 
	virtual const Int32Rect& GetBounds() = 0; 

	/**    Returns information about this offscreen 
	@param baseAddr - OUT - a pointer to the underlying offscreen pixel data 
	@param rowBytes - OUT - the number of bytes per scanline of data 
	@param portRect - OUT - the bounds of this offscreen 
	@param bitsPerPixel - OUT - the number of bits per pixel 
	*/ 
	virtual void GetPlatformBitmapInfo(void** baseAddr, uint32* rowBytes, Int32Rect* portRect, uint32* bitsPerPixel = nil) = 0;

	/**    Returns any error which might have occured during drawing. 
	@return The current platform specific error or 0 if no error. 
	*/ 
	virtual int32 OffscreenError() = 0; 

	/**   Makes sure that it has an underlying bitmap that is at least as big 
	as the provided bounds rect.  If there is already an underlying bitmap which is at 
	least as large as the bounds, and the origin has not changed, then nothing happens. 
	Otherwise, the old bitmap is disposed and a new one is allocated using the provided 
	bounds. 

	@param bounds - IN: The new bounds for the underlying bitmap. 
	@return If UpdateBitmap returns kTrue then the underlying bitmap has been changed. 
	*/ 
	virtual bool16 UpdateBitmap(const Int32Rect& bounds, PMReal uiScaleFactor = 1.0) = 0; 

	/**    Same as UpdateBitmap except that the old bitmap can be disposed of if it is much 
	larger than the new bounds. 

	@param bounds - IN: The new bounds for the underlying bitmap. 
	@return If UpdateBitmapIfDifferent returns kTrue then the underlying bitmap has been changed. 
	*/
	virtual bool16 UpdateBitmapIfDifferent(const Int32Rect& bounds, PMReal uiScaleFactor = 1.0) = 0; 

	/**    Returns the scaling factor (real) for the offscreen.
	@return The scaling factor, currently 1 or 2 for the Mac, or a real number 1.0 to 5.0 for Win.
	*/ 
	virtual PMReal GetCurrentUIScaleFactorReal() = 0; 

	/**    Copy pixels from this offscreen into the provided offscreen. 
	@param dstDrawbot - IN - the destination offscreen 
	@param &srcBounds - IN - the area of this offscreen (the source) to copy 
	@param &dstBounds - IN - the area of the provided offscreen (the destination) to copy into 
	@param clip2destMatrix -IN - clip to destination space matrix
	@param path - IN - the area of the offscreen to copy 
	*/ 
	virtual void CopyBitsFromOffscreen(dvaui::drawbot::Drawbot* dstDrawbot, const Int32Rect &srcBounds, const PMRect &dstBounds, 
		const PMMatrix& clip2destMatrix, const dvaui::drawbot::PathP path,
		int debug_cookie = 0, const char* debug_string = 0, void* debug_address = 0 //Ichabod temporary debugging code
		) = 0; 
};


/** Template class for the refcounted IDVPlatformOffscreen class for cleaning
up the syntax of IDVPlatformOffscreen implementations.  
Third parties need not worry about this class.
*/
template <>
class InterfacePtr<IDVPlatformOffscreen>
{
public:
		/** Note: Constructing an InterfacePtr from an existing,
			"real" interface pointer implies the InterfacePtr
			now owns the reference that was held by the real pointer.
		*/
		InterfacePtr(IDVPlatformOffscreen * pFace)
			: fFace(pFace) {}
		
		/** Destructor */
		~InterfacePtr()
			{
				if (fFace != nil){
					//const_cast<IDVPlatformOffscreen *>(unknown)->Release();
					fFace->Release();
				}
			}
		
		operator IDVPlatformOffscreen*() const
		{ return fFace; }
			// We allow the cast operator to return a nil pointer
			// since it is valid to test against nil and may be valid
			// to pass a nil pointer to some methods.

		
		IDVPlatformOffscreen * operator ->() const
			{
			#ifdef DEBUG
				ASSERT_MSG(fFace != nil,"About to use nil interface ptr!");
			#endif
			return fFace;
			}

private:
	IDVPlatformOffscreen * fFace;

	// If you feel you need one of these, let me know.  Thx. - Zak
	// For the sake of clarity and simplicity, they're currently not supported.

	InterfacePtr(void);
	InterfacePtr(const InterfacePtr<IDVPlatformOffscreen>& IDVPlatformOffscreenPtr);
	InterfacePtr<IDVPlatformOffscreen>& operator=(const InterfacePtr<IDVPlatformOffscreen>& IDVPlatformOffscreenPtr);
	InterfacePtr<IDVPlatformOffscreen>& operator=(IDVPlatformOffscreen * pFace);

};

#endif
