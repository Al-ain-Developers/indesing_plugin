//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkPaintInfo.h $
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "GraphicTypes.h"
#include "BravoForwardDecl.h"

class IPreflightArtworkCSInfo;

/**	This interface provides information about a particular marking operation. See 
	IPreflightArtworkMarkInfo for more context, in particular QueryColorPaintInfo() and/or
	QueryAlphaPaintInfo().
*/

class IPreflightArtworkPaintInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKPAINTINFO };

	/** The spatial representation of the marking operation. */
	typedef enum
	{
		kPaintSpatial_Invalid,
		kPaintSpatial_Other,
		kPaintSpatial_Constant,
		kPaintSpatial_Image,
		kPaintSpatial_Shading,
		kPaintSpatial_Composite,
		kPaintSpatial_Encapsulated,
		kPaintSpatial_Pattern
	} PaintSpatialType;

public:
	/** This is used to initialize the interface. This takes an opaque type, so only 
		InDesign internal code can call or implement this method.

		@param paint IN The opaque object that this interface gives you information about.
		@param paintMatrix IN The paint matrix.
		@param overprint IN The overprint state from the marking operation.
	*/
	virtual void Initialize(CAGMPaint& paint, const PMMatrix& paintMatrix, bool overprint) = 0;

	/** Returns whether overprint is enabled. This is the same value as on the parent mark.
		@return True if overprinted, False if knocked out.
	*/
	virtual bool GetOverprint() const = 0;

	/** Return the matrix associated with the paint.
		@return The matrix for the paint.
	*/
	virtual PMMatrix GetPaintMatrix() const = 0;

	/** Return the color space information for the paint. This provides all the information
		about the color channels, alpha, and so on.

		@return A refcounted CSInfo interface.
	*/
	virtual IPreflightArtworkCSInfo* QueryColorSpace() const = 0;

	/** Return the spatial type, ie how the color varies spatially.
		@return The spatial paint type.
	*/
	virtual PaintSpatialType GetSpatialType() const = 0;

	/** Analyzes the paint to figure out whether the paint marks a single plate at some minimum
		threshold everywhere on that plate and zero on all the other channels. This may seem like
		a very strange criteria; but it's needed to determine whether this is a trap-safe paint.
		
		Actually, you also need to check the mark for its overprint state; if it's overprinted
		and marking a single plate then it doesn't really need to be trapped. This in turn is
		important if you're concerned about misregistration of very small elements.

		Note that if this returns true that only means that this particular paint, in isolation,
		is expected to trap properly based on its color. It may not be after compositing with
		transparency.

		@param threshold The coverage value above which all marks on the sole marked plate must 
			be to qualify. Typically this is on the order of 0.9 (90%).
		@return The total number of plates marked.
	*/
	virtual uint32 IsTrapSafeColor(const PMReal& threshold) const = 0;

	/** This is simply a logical AND combination of IsTrapSafeColor() and GetOverprint(). 

		@param threshold The coverage value above which all marks on the sole marked plate must 
			be to qualify. Typically this is on the order of 0.9 (90%).
		@return The total number of plates marked.
	*/
	virtual uint32 IsTrapSafe(const PMReal& threshold) const = 0;

	/** Returns true if the paint is a constant color white (ie, marks no plates). If it's anything
		other than constant color, returns false (assuming all-white gradients, patterns, 
		images, etc., are uninteresting cases).

		@param tolerance The value above which a channel is assumed to be marked.
		@return kTrue if it's white; kFalse otherwise.
	*/
	virtual bool IsWhite(const PMReal& tolerance = 0.001) const = 0;

	/** Get the constant paint components (applicable only for constant spatial paint operations).

		@note Valid only when GetSpatialType() == kPaintSpatial_Constant.
		@param comps OUT Receives the array of component values, if not nil.
		@return The number of components in the array (returned whether or not nil pointer is passed).
	*/
	virtual int32 GetConstantColorValues(K2Vector<PMReal>* comps) const = 0;

	/** For image paints, get the pixel bounds of the image. 
		@note Applies iff GetSpatialType() == kPaintSpatial_Image.
		@return The bounds of the image.
	*/
	virtual Int32Rect GetImagePixelBounds() const = 0;

	/** For image paints, get the XY resolution of the image in CTM.
		@note Applies iff GetSpatialType() == kPaintSpatial_Image.
		@return The resolution of the image in CTM. @see GetAbsoluteMatrix.
	*/
	virtual PMPoint GetImageResolution() const = 0;

	/** For image paints, get the bit depth per pixel.
		@note Applies iff GetSpatialType() == kPaintSpatial_Image.
		@return The bit depth per pixel.
	*/
	virtual uint32 GetImageBitsPerPixel() const = 0;

	/** For image and encapsulated paint types, determines whether the mark is an OPI proxy.
		@note This merely inspects the paint's OPI tag, if present. If there is no OPI tag it
			could still be part of some OPI artwork that is declared at the artwork context level.
		@return kTrue if it's known to be an OPI proxy; kFalse if not.
	*/
	virtual bool IsOPIProxy() const = 0;

};

