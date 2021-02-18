//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDragDropTextHelper.h $
//  
//  Owner: Paul Sorrick
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
//  Utilities for use for dealing with drag and drop of text.
//  
//========================================================================================

#pragma once
#ifndef __IDRAGDROPTEXTHELPER__
#define __IDRAGDROPTEXTHELPER__

#include "TextEditorID.h"
#include "DragDropConstants.h"
#include "IDragDropTextUtils.h"

class UIDRef;
class RangeData;
class IParcel;
class ITextStoryThread;

/** Helper interface used for text dragging and dropping. Installed on same boss as text drag drop source and target.
 */
class IDragDropTextHelper : public IPMUnknown 
{
	public:
		enum	{ kDefaultIID = IID_IDRAGDROPTEXTHELPER };

	/**	Description: Query for an IParcel interface from an object.
		@param view IN pointer to the control view under the mouse
		@param where IN the point in pasteboard coordinates to use
		@param hitObj IN an IPMUnknown* from the object to test.
		@param previousParcel IN an IParcel interface from a possible previous hit. May be nil, and will be nil initially.
		@return IParcel the parcel interface from the object. Return nil if not found. Caller must release reference.
	 */
	virtual IParcel* QueryParcelFromHitObject(IControlView* view, const PMPoint& where, const IPMUnknown* hitObj, const IParcel* previousParcel) = 0;

	/**	Description: Query for an ITextStoryThread interface from an object.
		@param view IN pointer to the control view under the mouse
		@param where IN the point in pasteboard coordinates to use
		@param hitObj IN an IPMUnknown* from the object to test.
		@param previousParcel IN an IParcel interface from a possible previous hit. May be nil, and will be nil initially.
		@return ITextStoryThread the text story thread interface from the object. Return nil if not found. Caller must release reference.
	 */
	virtual ITextStoryThread* QueryStoryThreadFromHitObject(IControlView* view, const PMPoint& where, const IPMUnknown* hitObj, const IParcel* previousParcel) = 0;

	/**	Description: Adjust a range data (with correct lean) as computed by AdjustHitTestTextIndex for the story and text indices. Should have length of zero. 
		Gives helper a chance to examine the display text index and range and alter if necessary (e.g. convert to model range, etc.).
		@param view IN pointer to the control view under the mouse
		@param storyUIDRef IN Reference to the story to drop into (the destination)
		@param hitIndex IN the display text index to construct the range with
		@param nextLine IN the nextLine text index of the first character in the next line after the line hit (useful for computing the lean)
		@param storyUIDRef IN Reference to the story to drop into (the destination)
		@param RangeData OUT the altered text range with correct lean representing the hit location.
	 */
	virtual void AdjustRangeFromHitTest(IControlView* view, const UIDRef& storyUIDRef, const PMReal& hitIndex, const PMReal& nextLine, RangeData& adjustedRange) = 0;
};
	
#endif // __IDRAGDROPTEXTHELPER__

