//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAnchoredObjectData.h $
//  
//  Owner: Eric Menninga
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
#ifndef __IANCHOREDOBJECTDATA__
#define __IANCHOREDOBJECTDATA__

#include "IPMUnknown.h"
#include "TextID.h"


class IParcel;
class PMMatrix;
class IWaxLine;

/**
	IAnchoredObjectData is the data interface on page items that are anchored at a text location.
	Originally, pageitems could only be "inline": graphics that flowed in the line of text.
	Now, the pageitems can be inline, or above the line, or anchored to a line, page or frame specific location.
	This interface specifies the layout rules to apply and has methods to calculate the position.
	@ingroup text_layout
*/
class IAnchoredObjectData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANCHOREDOBJECTDATA };

	/** positioning type */
	typedef enum { kStandardInline, kAnchoredObject, kAboveLine  /* kBelowLine not supported yet */ } AnchoredPosition;
	/** horizontal placement */
	typedef enum { kRightSide, kCenter, kLeftSide, kTextAlignment } AnchoredHorizontal;
	/** vertical placement */
	typedef enum { kObjectTop, kObjectCenter, kObjectBottom } AnchoredVertical;
	/** what is the object positioned relative to the vertical axis */
	typedef enum { kColumnRelativeV, kFrameRelativeV, kMarginRelativeV, kPageRelativeV,
						// line relative positions MUST be after then others. Doing "v >= kLineBaseline" in places
					kLineBaseline, kLineXHeight, kLineCapheight, kLineAscent, kLineLeading,
					kEmBoxTop, kEmBoxMiddle, kEmBoxBottom  } VerticalAnchorPointObject;
	/** what is the object positioned relative to the horizontal axis */
	typedef enum { kColumnRelativeH, kFrameRelativeH, kMarginRelativeH, kPageRelativeH, kAnchorRelativeH } HorizontalAnchorPointObject;

	/** used by the ChangeAnchoredObjectCmd's IIntData interface to control which fields to set */
	enum { kCmdSelector_Position = 0x0100,
			kCmdSelector_AnchorTypeH = 0x0200, kCmdSelector_ObjectH = 0x0400, kCmdSelector_RelativeH = 0x0800,
			kCmdSelector_AnchorTypeV = 0x01000, kCmdSelector_ObjectV = 0x02000, kCmdSelector_RelativeV = 0x04000,
			kCmdSelector_XOffset = 0x08000, kCmdSelector_YOffset = 0x010000, kCmdSelector_SpineRelative = 0x020000,
			kCmdSelector_YOffsetAbove = 0x040000, kCmdSelector_PinPosition = 0x080000, kCmdSelector_LockPosition = 0x0100000 };

	/** Set the positioning type of the anchored object.
		@param position is the positioning type to apply.
	*/
	virtual void SetPosition(IAnchoredObjectData::AnchoredPosition position) = 0;
	/** Get the positioning type of the anchored object.
		@return the positioning type of the object style.
	*/
	virtual IAnchoredObjectData::AnchoredPosition GetPosition() const = 0;

	/** Set whether the anchored object's positioning is relative to the spine.
		@param spineRelative true or false.
	*/
	virtual void SetSpineRelative(bool16 spineRelative) = 0;
	/** Get spine relative positioning.
		@return true if spine relative.
	*/
	virtual bool16 GetSpineRelative() const = 0;

	/** Set which location the horizontal position is based upon.
		@param location specifies which point the object's horizontal position is relative to.
	*/
	virtual void SetAnchorTypeHorizontal(IAnchoredObjectData::HorizontalAnchorPointObject location) = 0;
	/** Get which location the horizontal position is based upon.
		@return which point the object's horizontal position is relative to.
	*/
	virtual IAnchoredObjectData::HorizontalAnchorPointObject GetAnchorTypeHorizontal() const = 0;

	/** Set which horizontal point OF THE OBJECT to align to.
		@param align specifies which horizontal point to use.
	*/
	virtual void SetObjectHorizontal(IAnchoredObjectData::AnchoredHorizontal align) = 0;
	/** Get which horizontal point OF THE OBJECT to align to.
		@return which horizontal point to use.
	*/
	virtual IAnchoredObjectData::AnchoredHorizontal GetObjectHorizontal() const = 0;

	/** Set which horizontal point OF THE REFERENCE to align to (AnchorTypeHorizontal).
		@param align specifies which horizontal point to use.
	*/
	virtual void SetAnchorPtHorizontal(IAnchoredObjectData::AnchoredHorizontal align) = 0;
	/** Get which horizontal point OF THE REFERENCE to align to (AnchorTypeHorizontal).
		@return specifies which horizontal point to use.
	*/
	virtual IAnchoredObjectData::AnchoredHorizontal GetAnchorPtHorizontal() const = 0;

	/** Set which location the vertical position is based upon.
		@param location specifies which point the object's vertical position is relative to.
	*/
	virtual void SetAnchorTypeVertical(IAnchoredObjectData::VerticalAnchorPointObject location) = 0;
	/** Get which location the vertical position is based upon.
		@return specifies which point the object's vertical position is relative to.
	*/
	virtual IAnchoredObjectData::VerticalAnchorPointObject GetAnchorTypeVertical() const = 0;

	/** Set which vertical point OF THE OBJECT to align to.
		@param align specifies which vertical point to use.
	*/
	virtual void SetObjectVertical(IAnchoredObjectData::AnchoredVertical align) = 0;
	/** Get which vertical point OF THE OBJECT to align to.
		@return specifies which vertical point to use.
	*/
	virtual IAnchoredObjectData::AnchoredVertical GetObjectVertical() const = 0;

	/** Set which vertical point OF THE REFERENCE to align to (AnchorTypeVertical).
		@param align specifies which vertical point to use.
	*/
	virtual void SetAnchorPtVertical(IAnchoredObjectData::AnchoredVertical align) = 0;
	/** Get which vertical point OF THE REFERENCE to align to (AnchorTypeVertical).
		@return specifies which vertical point to use.
	*/
	virtual IAnchoredObjectData::AnchoredVertical GetAnchorPtVertical() const = 0;

	/** Set the x-offset of the anchored object from the point specified
		Due to the way spine-relative positioning can dynamically change the anchored
		object's position, positive x-offsets move the graphic AWAY from the anchor
		location, negative closer.
		@param xoffset is the offset value in points.
	*/
	virtual void SetXOffset(PMReal xoffset) = 0;
	/** Set the y-offset of the anchored object from the point specified
		@param yoffset is the offset value in points.
	*/
	virtual void SetYOffset(PMReal yoffset) = 0;

	/** Get the y-offset and x-offset of the anchored object from the point specified
		@return the displacement vector.
	*/
	virtual PMPoint GetOffset() const = 0;

	/** Set the amount of space to add above the anchored item.
		Y Offset Above is only used by "above line" positioning
		@param yoffset specifies extra space in points.
	*/
	virtual void SetYOffsetAbove(PMReal yoffset) = 0;
	/** Get the amount of space to add above the anchored item.
		Y Offset Above is only used by "above line" positioning
		@return specifies extra space in points.
	*/
	virtual PMReal GetYOffsetAbove() const = 0;

	/** Set whether the anchored object's position should be pinned within the text column boundaries.
		@param pinPos specifies whether to pin the anchored object.
	*/
	virtual void SetPinPosition(bool16 pinPos) = 0;
	/** Get whether the anchored object's position should be pinned within the text column boundaries.
		@return whether to pin the anchored object.
	*/
	virtual bool16 GetPinPosition() const = 0;

	/** Set whether the anchored object's position should be locked.
		This is a shortcut to applying the "Lock Object" functionality and is identical.
		@param lockPos specifies whether to set locking for the anchored object.
	*/
	virtual void SetLockPosition(bool16 lockPos) = 0;
	/** Get whether the anchored object's position should be locked.
		This is a shortcut to applying the "Lock Object" functionality and is identical.
		@return whether to set locking for the anchored object.
	*/
	virtual bool16 GetLockPosition() const = 0;

	/**	For composition -- returns data about the inline graphic for composition.
		@param lineHeight is the height of the line containing the inline.
		@param inlineWidth is used to report back the width of the inline for composition. This width will include the effect of text wrap.
		@param height is used to report the height of the inline above the baseline.
		@param leftStrokeOffset is used to report the offset measured from the left side of the of the inlineWidth to the left side of the inline. The inline always adjusts itself so that its left bottom stroke corner is at 0.0. This will be the pen position for drawing the inline and may be negative.
		@return kTrue is returned when the object has width or height. A true inline will have width and height, an above line anchored object will have only height and an true anchored object will have neither.
	*/
	virtual bool16 CalculateWaxLineImpact(PMReal lineHeight,
										PMReal& width,
										PMReal& height,
										PMReal& leftStrokeOffset) const = 0;

	/**	The register inline method will be called after composition to adjust the matrix from text parcel to inline graphic.
		@param waxLine is the line that this object is anchor within.
		@param pParcel is the IParcel that the inline is relative to.
		@param waxToILGMatrix is the mapping from parcel to inline graphic.
		@return kTrue if the matrix was changed.
	*/
	virtual bool16 RegisterInlineAt(const IWaxLine *waxLine, const IParcel *pParcel, PMMatrix &waxToILGMatrix) const = 0;

	/**	Adjust the ink bounds of the inline graphic if it was re-positioned
		@param bounds in the bounding box of the inline graphic.
		@return kTrue if the bounding box was changed.
	*/
	virtual bool16 AdjustInkBounds(PMRect& bounds) const = 0;

	/**	Adjust the line bounds (selection, caret bounds) of the inline graphic if it was re-positioned
		@param bounds in the bounding box of the inline graphic.
		@return kTrue if the bounding box was changed.
	*/
	virtual bool16 AdjustLineBounds(PMLineSeg& line) const = 0;

	/** This is a calculated value, based on the object's position & specified rules.
		@return whether this particular object is anchored, spine relative, and on the opposite page
		so that the position and offsets are flipped.
	*/
	virtual bool16 SpineRelativePositionFlipped() const = 0;

	/** Copy these values TO the passed in interface.
		@param pCopyTo is filled out with the current interface's values.
	*/
	virtual void CopyData(IAnchoredObjectData *pCopyTo ) const = 0;

	/** Have the positioning rules changed since the graphic was last positioned?
		@return whether the interface changed since the last call to "RegisterInlineAt" ?
	*/
	virtual bool16 NeedsRecalculation() const = 0;

	/** Force the position to be recalculated.
	*/
	virtual void ForceRecalculation() = 0;

	/**
	Adobe internal use only.
	*/
	virtual void CobaltFixupInlines() = 0;

};

#endif
		// __IANCHOREDOBJECTDATA__

