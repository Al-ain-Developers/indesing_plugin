//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IClipSettings.h $
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
//  Purpose:
//  Data interface for IID_ICLIPSETTINGS used to store and obtain the Clipping Path dialog
//  settings used to create a Clipping Path frame using edge detection algorithms.
//  
//========================================================================================

#pragma once
#ifndef __IClipSettings__
#define __IClipSettings__

#include "IPMUnknown.h"
#include "ClippingDlgID.h"

/** 
	This class describes the clipping path settings for an image.  These settings
	can be applied via the kSetClipValuesCmdBoss command.
	@see ISetClipValuesCmdData
*/
class IClipSettings : public IPMUnknown
{
public:
	/**
		Default IID enumeration for this class.
	*/
	enum { kDefaultIID = IID_ICLIPSETTINGS };

	/**
		ClipType enumeration
	*/
	typedef enum {
		kClipNone = 0,
		kClipEdgeDetection = 1,
		kClipAlpha = 2,
		kClipEmbeddedPath = 3,
		kClipUserPath = 4		// User-edited path
	} ClipType;

	enum {
		kDefaultClipIndex = -1
	};

	/**
		Returns the current clipping type set via SetClipType.
	*/
	virtual ClipType GetClipType() const = 0;

	/**
		Returns the current tolerance set via SetTolerance.
	*/
	virtual PMReal GetTolerance() const  = 0;

	/**
		Returns the current inset to apply to the clipping set via SetInset.
	*/
	virtual PMReal GetInset() const  = 0;

	/**
		Returns the current threshold value set via SetThreshold.
	*/
	virtual uint8 GetThreshold() const = 0;

	/**
		Returns the invert setting set by SetInvert.
	*/
	virtual uint8 GetInvert() const = 0;

	/**
		Returns the current High Res setting, set via SetUseHighRes.
	*/
	virtual uint8 GetUseHighRes() const = 0;

	/**
		Returns whether or not to allow holes, set via SetAllowHoles.
	*/
	virtual uint8 GetAllowHoles() const = 0;

	/**
		Sets ClipType
		@param clipType - IN: One of kClipNone, kClipEdgeDetection, kClipAlpha, and	kClipEmbeddedPath.
	*/
	virtual void SetClipType(ClipType clipType) = 0;

	/**
		After an edge detection or alpha edge detection operation to compute
			a clipping path, the resulting path is a polygon.  This path then goes through a smoothing
			process to convert the polygonal path to a bezier path and reduce the total number of points.
			The Tolerance specifies how closely the smoothed path must match the polygonal path.  The smaller
			the tolerance, the more points the resulting path will have.
		@param Tolerance - IN: How closely the smoothed path must follow the original polygonal path.
	*/
	virtual void SetTolerance( PMReal Tolerance) = 0;

	/**
		Sets how far to inset the resulting clipping path
		@param Inset - IN: Inset, in points.
	*/
	virtual void SetInset( PMReal Inset) = 0;

	/**
		Sets threshold. The larger the threshold, the darker the pixels included in an edge detection operation.
		@param Threshold - IN: A value between 0 and 255.
	*/
	virtual void SetThreshold(uint8 Threshold) = 0;

	/**
		Sets whether to invert the resulting clipping path.
		@param Invert - IN: kTrue to invert the resulting clipping path.
	*/
	virtual void SetInvert(bool8 Invert) = 0;

	/**
		Sets whether to force the high res image to be used to obtain pixel or alpha data.
		@param UseHighRes - IN: kTrue to force the high res image to be used to obtain pixel 
		or alpha data.  This option is slower but will produce the most accurate results.
	*/
	virtual void SetUseHighRes(bool8 UseHighRes) = 0;

	/**
		Sets whether to filter out any holes in the resulting clipping path.
		@param AllowHoles - IN: kFalse to filter out any holes in the resulting clipping path.
	*/
	virtual void SetAllowHoles(bool8 AllowHoles) = 0;
	
	/**
		Sets whether to restrict edge detection and alpha edge detection to the currently visible 
		portions of the image not clipped/cropped by the containing frame.
		@param yesno - IN: kTrue to restrict edge detection and alpha edge detection
			to the currently visible portions of the image not clipped/cropped by the containing frame.
	*/
	virtual void SetRestrictToFrame( bool8 yesno ) = 0;
	
	/**
		Returns whether or not to restrict edge detection and alpha edge detection to the currently 
		visible portions of the image not clipped/cropped by the containing frame. Set via SetRestrictToFrame.
	*/
	virtual bool8 GetRestrictToFrame( void ) const = 0;
	
	
	/**
		Sets index to determine which alpha channel to use.
		@param index - IN: If the clip type is kClipAlpha and there are multiple
			alpha channels, then use this zero-based index to determine which alpha channel to use.
	*/
	virtual void SetAlphaIndex( int16 index ) = 0;
	
	/**
		Returns which zero based alpha channel index to use when there is more than
		one alpha.  Set via SetAlphaIndex.
	*/
	virtual int16 GetAlphaIndex( void ) const = 0;

	/**
		Sets path to use when the clip type is kClipEmbeddedPath and there are multiple embedded paths.
		@param index - IN: If the clip type is kClipEmbeddedPath and there are multiple
			embedded paths, then use this zero-based index to determine which path to use.
			If kDefaultClipIndex is passed, then the default clipping path will be used.  
			In Photoshop, any given path can be designated as the clipping path.  The 
			clipping path is stored in the '8BIM' resource with ID 2999.  If such a path 
			does not exist, then the first path will be used.
	*/
	virtual void SetEmbeddedPathIndex( int16 index ) = 0;
	
	/**
		Returns which zero based embedded path to use when there is more than
		one embedded path.  Set via SetAlphaIndex.  If kDefaultClipIndex is returned,
		then the default clipping path will be used.  In Photoshop, any given path can
		be designated as the clipping path.  The clipping path is stored in the '8BIM'
		resource with ID 2999.  If such a path does not exist, then the first path will be used.
	*/
	virtual int16 GetEmbeddedPathIndex( void ) const = 0;
};

#endif
