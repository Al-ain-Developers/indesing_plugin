//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStandOffContourWrapSettings.h $
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
//========================================================================================

#pragma once
#ifndef __IStandOffContourWrapSettings__
#define __IStandOffContourWrapSettings__

#include "IPMUnknown.h"

#include "StandOffID.h"

/** INTERNAL USE ONLY */
class IStandOffContourWrapSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTOURWRAPSETTINGS };

	typedef enum {
		kInvalid = -1,
		kGraphicBounds = 0,		// use the bounds of the graphic
		kEdgeDetection = 1,		// look at the pixel values to find darker areas of the image
		kAlpha = 2,				// Use edge detection algorithm on the alpha channel
		kEmbeddedPath = 3,		// Use the embedded path
		kGraphicFrame,			// Use the graphic's frame
		kSameAsClip,			// Use the graphic's clipping
		kSelectSubject				// Do Smart subject Detection using Adobe Sensei
	} ContourWrapType;

	enum {
		kDefaultPathIndex = -1	// This value indicates that the path used is the one named by '8BIM' resource ID 2999.
	};

	virtual ContourWrapType GetType() const = 0;

	virtual PMReal GetTolerance() const  = 0;

	virtual uint8 GetThreshold() const = 0;

	virtual uint8 GetAllowHoles() const = 0;

	virtual void SetType(ContourWrapType type) = 0;

	virtual void SetTolerance( PMReal Tolerance) = 0;

	virtual void SetThreshold(uint8 Threshold) = 0;

	virtual void SetAllowHoles(bool8 AllowHoles) = 0;

	// If the type is kAlpha and there are multiple
	// alpha channels, then use this zero-based index to determine
	// which alpha channel to use.
	virtual void SetAlphaIndex( int16 index ) = 0;

	virtual int16 GetAlphaIndex( void ) const = 0;

	// If the type is kEmbeddedPath and there are multiple
	// embedded paths, then use this zero-based index to determine
	// which path to use.
	virtual void SetEmbeddedPathIndex( int16 index ) = 0;

	// Warning: the following Get method may return a value
	// of kDefaultPathIndex.  This value indicates that the path
	// used is the one named by '8BIM' resource ID 2999.
	virtual int16 GetEmbeddedPathIndex( void ) const = 0;

	virtual void CopyTo( IStandOffContourWrapSettings *pCopyTo ) const = 0;
};

#endif
