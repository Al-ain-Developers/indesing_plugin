//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkMarkInfo.h $
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
#include "IPreflightArtworkImage.h"

class IPreflightArtworkPaintInfo;
class IPreflightArtworkTextInfo;

/**	This interface provides information about a particular marking operation. This is used
	by rule implementations (ie in IPreflightRuleVisitor::Visit()) that ask to look at
	objects of class kPreflightOM_ArtworkMark. When you're given an object of that class,
	use this interface to inspect it further.

	Typical usage (this example from the registration color rule):

		InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());
		InterfacePtr<IPreflightArtworkMarkInfo> iMark(iObj, UseDefaultIID());
		InterfacePtr<IPreflightArtworkPaintInfo> iColor(iMark->QueryColorPaintInfo());
		if (!iColor) return;

		InterfacePtr<IPreflightArtworkCSInfo> iCS(iColor->QueryColorSpace());
		if (!iCS) return;

		if (iCS->GetType() == IPreflightArtworkCSInfo::kCS_Indexed)
		{
			iCS = InterfacePtr<IPreflightArtworkCSInfo>(iCS->QueryBase());
		}

		if ((iCS->GetType() == IPreflightArtworkCSInfo::kCS_NChannel 
				|| iCS->GetType() == IPreflightArtworkCSInfo::kCS_DeviceN)
			&& iCS->GetRegistrationChannelsMap().size() > 0)
		{
			InterfacePtr<IPreflightResultRecord> iRecord(iVisit->CreateResultRecord());
			iRecord->SetCriteria(kPreflightRC_Default);
		}
*/

class IPreflightArtworkMarkInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKMARKINFO };

	/** Which kind of marking operation this is. */
	typedef enum 
	{ 
		kMarkOp_Invalid,
		kMarkOp_Stroke,
		kMarkOp_Fill
	} MarkOperation;

	/** The type of path; determines which APIs can be used below. */
	typedef enum 
	{ 
		kMarkType_Invalid,

		/** A text marking operation; use GetText* below. */
		kMarkType_Text,

		/** A path (collection of points) marking operation; use GetPath* below. */
		kMarkType_Path 
	} MarkType;

	typedef enum
	{
		kMarkPt_Invalid,
		kMarkPt_MoveTo,
		kMarkPt_LineTo,
		kMarkPt_CurveTo,
		kMarkPt_Close
	} MarkPointType;

public:
	/** Get the color paint information.

		@return A refcounted paint interface associated with the color data. This is a lightweight
			object with proper IPMUnknown semantics, but not a real boss. Could conceivably be nil.
	*/
	virtual IPreflightArtworkPaintInfo* QueryColorPaintInfo() const = 0;

	/** Get the alpha paint information.

		@return A refcounted paint interface associated with the alpha data. This is a lightweight
			object with proper IPMUnknown semantics, but not a real boss. Will be nil if there is
			no alpha specification (ie the object is opaque).
	*/
	virtual IPreflightArtworkPaintInfo* QueryAlphaPaintInfo() const = 0;

	/** Get the interface that describes the text/font information. This returns non-nil only
		for marking operations of type kMarkType_Text.

		@return A refcounted interface pointer, or nil if not applicable.
	*/
	virtual IPreflightArtworkTextInfo* QueryTextInfo() const = 0;

	/** Get the bounds of the marking operation. The bounds are in path coordinates, or you
		can pass a particular matrix that you want to use if you want the bounds computed in
		that space (the points are xformed so this is more accurate than xforming the rect).

		@param r OUT Receives the bounding box.
		@param m IN Optionally a matrix to xform the points through before calculating bbox.
	*/
	virtual void GetBounds(PMRect& r, const PMMatrix& m = PMMatrix()) const = 0;

	/** Returns whether overprint is currently enabled.
		@return kTrue if overprint is on, kFalse otherwise.
	*/
	virtual bool GetOverprint() const = 0;
	
	/** Returns the shape of the mark -- path vs text.
		@return The marking type.
	*/
	virtual MarkType GetMarkType() const = 0;

	/** Returns whether the marking operation is stroke or fill.
		@return The marking operation type.
	*/
	virtual MarkOperation GetMarkOperation() const = 0;

	/**	Get the stroke width (applicable to stroke operations).
		@note This is only valid if GetMarkOperation() == kMarkOp_Stroke.
		@return The stroke width in CTM coordinates.
	*/
	virtual PMReal GetStrokeWidth() const = 0;

	/** Get the point data for the path for the marking operation.
		@note Applies iff GetMarkType() == kMarkType_Path. 
		@param locs OUT If non-nil, receives the locations (in CTM coords).
		@param ptTypes OUT If non-nil, receives the point types.
		@return The number of points in the path.
	*/
	virtual uint32 GetPathPoints(PMPoint* locs = nil, MarkPointType* ptTypes = nil) const = 0;

	/** Get the absolute matrix, ie the cumulative matrix from here to 72dpi page space.
		Useful for determining the absolute size/resolution of things taking into account any 
		group or page item scaling.

		@param m OUT Receives the matrix.
	*/
	virtual void GetAbsoluteMatrix(PMMatrix& m) const = 0;

	/** Get the path matrix, ie the matrix that applies to the points in the path.

		@param m OUT Receives the path matrix.
	*/
	virtual void GetPathMatrix(PMMatrix& m) const = 0;

	/** Determines whether this marking operation is part of an expanded pattern.
		@return kTrue if it's part of a pattern, kFalse otherwise.
	*/
	virtual bool IsFromPattern() const = 0;

	/** Build an image of the mark.
	
		Be careful with this one, in particular with images; in many cases, large images are 
		virtual and do not incur much inspection cost UNLESS you want the pixels, which of 
		course this method does. Therefore for images this can be a very expensive call.

		This method returns a refcounted image object which you need to release. Note that since
		it's IPMUnknown based you can use InterfacePtr. The image is completely independent from
		this marking operation; you can keep it as long as you like.

		The image is (for now) always built in the colorspace of the marking operation. For example
		if this is an RGB marking operation it will be an RGB image; if it is CMYK plus some spots 
		the image will be CMYK plus spot plates. @see IPreflightArtworkImage.

		@param matrix The matrix to use to get from path matrix space to image space. If you pass
			a unity matrix then there will be a 1:1 mapping from GetBounds() to pixels. If you 
			pass a 2x scale matrix then each Bounds() unit maps to two image pixels. And so on.
			Use this matrix to establish the effective resolution and origin of the image. The image 
			will have minimum padding outside of the path bounds (generally only enough to accommodate
			antialiasing bleed).
		@param alpha True if you want the image to have alpha; false if not. Alpha is useful for
			determining what is marked, as opposed to what's white.
	*/

	virtual IPreflightArtworkImage* Rasterize
		(
			const PMMatrix& path2image = PMMatrix(), 
			uint32 rf_flags = IPreflightArtworkImage::kRF_Default
		) const = 0;
};

