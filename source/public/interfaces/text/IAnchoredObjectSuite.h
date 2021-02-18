//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAnchoredObjectSuite.h $
//  
//  Owner:
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
#ifndef _IAnchoredObjectSuite_
#define _IAnchoredObjectSuite_

#include "IPMUnknown.h"

#include "IAnchoredObjectData.h"		// for enums
#include "IAnchoredObjectInsertData.h"		// for enums

/** IAnchoredObjectSuite
	The suite methods of changing the anchored object data & preferences.
	@see IAnchoredObjectData
	@see IAnchoredObjectInsertData
*/
class IAnchoredObjectSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANCHOREDOBJECT_ISUITE };

	/** Does this suite target support setting the anchored object data fields?
		@return kTrue for anchored objects & default targets
	*/
	virtual bool16 CanSetAnchoredObjectParams() const = 0;
	/** Does this suite target support setting the anchored object insert data fields?
		@return kTrue for default targets
	*/
	virtual bool16 CanSetAnchoredObjectInsertParams() const = 0;

	/** Does this suite target support inserting an anchored object?
		@return kTrue for text targets
	*/
	virtual bool16 CanInsertAnchoredObject() const = 0;
	/** Insert an anchored object using the specification provided by the interface passed it.
		@param objectSpec is an interface with the proper insert settings. It should also be able to provide
				the IAnchoredObjectData interface through a QueryInterface.
		@param toggleSelection specifies whether the insert should select the new object.
		@return kFailure if not legal to insert an anchored object
	*/
	virtual ErrorCode InsertAnchoredObject(IAnchoredObjectInsertData *objectSpec, bool16 toggleSelection = kFalse) = 0;

	/** CanToggleBetweenAnchoredFrame is the toggling between text selections & anchored text frame allowed?
		@return true if the selection supports toggling back and forth between anchored frames and main text frames.
	*/
	virtual bool16 CanToggleBetweenAnchoredFrame() const = 0;

	/** ToggleBetweenAnchoredFrame toggle between text selections & anchored text frame
		@param toggledFrame and @param location will be filled out according to these rules:
			if the selection spans or is adjacent to an existing anchored frame, then toggledFrame will contain the
				UIDRef of the existing frame and location will be set to the end of that frame's text.
			if the selection is within an already existing anchored frame, then the toggledFrame will be the story that
				contains the anchor, and location will be the anchor's location.
			if the selection is a caret that is not adjacent to an already existing anchored frame, it will create one and
				return that new spline item's UIDRef and a location of 0 (could create an Unassigned, Graphic or Text frame).
			if the selection doesn't support the operation, the toggledFrame may be <nil, kInvalidUID>.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode ToggleBetweenAnchoredFrame(UIDRef& toggledFrame, TextIndex& location) const = 0;

	/** CanReleaseAnchoredObject
		Can the suite target be released onto the text frame's layer?
	*/
	virtual bool16 CanReleaseAnchoredObject() const = 0;
	/** ReleaseAnchoredObject
		Make the object be on the text frame's layer instead of anchored.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode ReleaseAnchoredObject() = 0;

	/** Does the selection support the "anchored" position? E.g., inlines in text on a path can't be anchored.
		@return kFalse if the selection doesn't support the anchored position.
	*/
	virtual bool16 CanSetAnchoredPosition() const = 0;
	/** Set the positioning type of the anchored object.
		@param position is the positioning type to apply.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetPosition(IAnchoredObjectData::AnchoredPosition position) = 0;
	/** Get the positioning type of the anchored object.
		@mixed will be set to kTrue if the target contains multiple values.
		@return the positioning type of the object style.
	*/
	virtual IAnchoredObjectData::AnchoredPosition GetPosition(bool16 *mixed = nil) const = 0;

	/** Whether or not you can set the spline relative value (false when facing pages is off)
		@return bool16 	Whether or not you can set the spline relative value
	*/
	virtual bool16 CanGetSpineRelative() const  = 0;
	/** Set whether the anchored object's positioning is relative to the spine.
		@param spineRelative true or false.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetSpineRelative(bool16 splineRelative) = 0;
	/** Get spine relative positioning.
		@mixed will be set to kTrue if the target contains multiple values.
		@return true if spine relative.
	*/
	virtual bool16 GetSpineRelative(bool16 *mixed = nil) const = 0;

	/** Set which location the horizontal position is based upon.
		@param location specifies which point the object's horizontal position is relative to.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetAnchorTypeHorizontal(IAnchoredObjectData::HorizontalAnchorPointObject location) = 0;
	/** Get which location the horizontal position is based upon.
		@mixed will be set to kTrue if the target contains multiple values.
		@return which point the object's horizontal position is relative to.
	*/
	virtual IAnchoredObjectData::HorizontalAnchorPointObject GetAnchorTypeHorizontal(bool16 *mixed = nil) const = 0;

	/** Set which horizontal point OF THE OBJECT to align to.
		@param align specifies which horizontal point to use.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetObjectHorizontal(IAnchoredObjectData::AnchoredHorizontal align) = 0;
	/** Get which horizontal point OF THE OBJECT to align to.
		@mixed will be set to kTrue if the target contains multiple values.
		@return which horizontal point to use.
	*/
	virtual IAnchoredObjectData::AnchoredHorizontal GetObjectHorizontal(bool16 *mixed = nil) const = 0;

	/** Set which horizontal point OF THE REFERENCE to align to (AnchorTypeHorizontal).
		@param align specifies which horizontal point to use.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetAnchorPtHorizontal(IAnchoredObjectData::AnchoredHorizontal align) = 0;
	/** Get which horizontal point OF THE REFERENCE to align to (AnchorTypeHorizontal).
		@mixed will be set to kTrue if the target contains multiple values.
		@return specifies which horizontal point to use.
	*/
	virtual IAnchoredObjectData::AnchoredHorizontal GetAnchorPtHorizontal(bool16 *mixed = nil) const = 0;

	/** Set which location the vertical position is based upon.
		@param location which point the object's vertical position is relative to.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetAnchorTypeVertical(IAnchoredObjectData::VerticalAnchorPointObject location) = 0;
	/** Get which location the vertical position is based upon.
		@mixed will be set to kTrue if the target contains multiple values.
		@return specifies which point the object's vertical position is relative to.
	*/
	virtual IAnchoredObjectData::VerticalAnchorPointObject GetAnchorTypeVertical(bool16 *mixed = nil) const = 0;

	/** Set which vertical point OF THE OBJECT to align to.
		@param align specifies which vertical point to use.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetObjectVertical(IAnchoredObjectData::AnchoredVertical align) = 0;
	/** Get which vertical point OF THE OBJECT to align to.
		@mixed will be set to kTrue if the target contains multiple values.
		@return specifies which vertical point to use.
	*/
	virtual IAnchoredObjectData::AnchoredVertical GetObjectVertical(bool16 *mixed = nil) const = 0;

	/** Set which vertical point OF THE REFERENCE to align to (AnchorTypeVertical).
		@param align specifies which vertical point to use.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetAnchorPtVertical(IAnchoredObjectData::AnchoredVertical align) = 0;
	/** Get which vertical point OF THE REFERENCE to align to (AnchorTypeVertical).
		@mixed will be set to kTrue if the target contains multiple values.
		@return specifies which vertical point to use.
	*/
	virtual IAnchoredObjectData::AnchoredVertical GetAnchorPtVertical(bool16 *mixed = nil) const = 0;

	/** Set the x-offset of the anchored object from the point specified
		Due to the way spine-relative positioning can dynamically change the anchored
		object's position, positive x-offsets move the graphic AWAY from the anchor
		location, negative closer.
		@param xoffset is the offset value in points.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetXOffset(PMReal xoffset) = 0;
	/** Set the y-offset of the anchored object from the point specified
		@param yoffset is the offset value in points.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetYOffset(PMReal yoffset) = 0;
	/** Get the y-offset and x-offset of the anchored object from the point specified
		@mixed will be set to kTrue if the target contains multiple values.
		@return the displacement vector of the first object.
	*/
	virtual PMPoint GetOffset(bool16 *mixed = nil) const = 0;

	/** Set the amount of space to add above the anchored item.
		Y Offset Above is only used by "above line" positioning
		@param yoffset specifies extra space in points.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetYOffsetAbove(PMReal yoffset) = 0;
	/** Get the amount of space to add above the anchored item.
		Y Offset Above is only used by "above line" positioning
		@mixed will be set to kTrue if the target contains multiple values.
		@return specifies extra space in points of the first object.
	*/
	virtual PMReal GetYOffsetAbove(bool16 *mixed = nil) const = 0;

	/** Set whether the anchored object's position should be pinned within the text column boundaries.
		@param pinPos specifies whether to pin the anchored object.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetPinPosition(bool16 pinPos) = 0;
	/** Get whether the anchored object's position should be pinned within the text column boundaries.
		@mixed will be set to kTrue if the target contains multiple values.
		@return whether to pin the first anchored object.
	*/
	virtual bool16 GetPinPosition(bool16 *mixed = nil) const = 0;

	/** Set whether the anchored object's position should be locked.
		This is a shortcut to applying the "Lock Object" functionality and is identical.
		@param lock specifies whether to set locking for the anchored object.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetLockPosition(bool16 lock) = 0;
	/** Get whether the anchored object's position should be locked.
		This is a shortcut to applying the "Lock Object" functionality and is identical.
		@mixed will be set to kTrue if the target contains multiple values.
		@return whether to set locking for the first targetted anchored object.
	*/
	virtual bool16 GetLockPosition(bool16 *mixed = nil) const = 0;

	/** When inserting an anchored object automatically, which type of object should be inserted?
		@param content is the type of object to insert: text frame, graphic frame, unassigned frame.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetInitialContent(IAnchoredObjectInsertData::AnchoredContent content) = 0;
	/** Get the type of content that will be inserted.
		@return the content type.
	*/
	virtual IAnchoredObjectInsertData::AnchoredContent GetInitialContent() const = 0;

	/** Set the object style to be applied to the inserted object.
		@param styleID is the object style to apply.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetInitialObjectStyle(UID styleID) = 0;
	/** Get the object style that would be applied to the inserted object.
		@return the UID of the object style.
	*/
	virtual UID GetInitialObjectStyle() const = 0;

	/** Set the paragraph style to be applied to the inserted object, IFF the object is a text frame.
		@param styleID is the paragraph style to apply
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetInitialParagraphStyle(UID styleID) = 0;
	/** Get the paragraph style that would be applied to an inserted text frame.
		@return the UID of the paragraph style.
	*/
	virtual UID GetInitialParagraphStyle() const = 0;

	/** Set the width of the object to be inserted.
		@param w is the width in points.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetInitialWidth(PMReal w) = 0;
	/** Get the initial width of the object that would be inserted.
		@return the initial width.
	*/
	virtual PMReal GetInitialWidth() const = 0;

	/** Set the height of the object to be inserted.
		@param h is the height in points.
		@return kFailure if not applied to anchored object or defaults.
	*/
	virtual ErrorCode SetInitialHeight(PMReal h) = 0;
	/** Get the height of the object to be inserted.
		@return the initial height in points.
	*/
	virtual PMReal GetInitialHeight() const = 0;

		/** GetSmallestObjectHeight -- used by some contraints.
			@return the smallest height of all selected anchored objects
		*/
	virtual PMReal GetSmallestObjectHeight() const = 0;

		/** GetSmallestLineHeight -- used by some contraints.
			@return the smallest height of the lines which contain all selected anchored objects
		*/
	virtual PMReal GetSmallestLineHeight() const = 0;

	/** Returns true if the anchored object is inside of vertical text
		@return true if the anchored object is inside of vertical text
	*/
	virtual bool16 ObjectInVerticalText() const = 0;

};

#endif // _IAnchoredObjectSuite_
