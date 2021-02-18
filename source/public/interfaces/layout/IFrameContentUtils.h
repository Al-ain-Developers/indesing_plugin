//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFrameContentUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IFrameContentUtils__
#define __IFrameContentUtils__

#include "GenericID.h"
#include "IFrameContentSuite.h"
#include "IPMUnknown.h"
#include "IReferencePointData.h"
#include "Utils.h"

class UIDList;
class IGraphicFrameData;
class IFrameContentSuite;
class IReferencePointData;
class ITransform;

/** Utility interface for determining various aspects of frame contents. 
	@ingroup layout_util
 */
class IFrameContentUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFRAMECONTENTUTILS };

#ifdef ID_DEPRECATED

	/**	Returns kTrue if any item in the list can be converted to a graphic frame
		Deprecated - Use FrameContentFacade.
		@param items IN UIDList of items to check for convertibility. 
		@return kTrue (can convert one or more items) or kFalse (can't convert any items).
	 */
	virtual bool16 CanEnableConvertToFrame( const UIDList* items ) const = 0;


	/**	Returns kTrue if any item in the list can be converted to a text frame
		Deprecated - Use FrameContentFacade.
		@param items IN UIDList of items to check for convertibility. 
		@return kTrue (can convert one or more items) or kFalse (can't convert any items).
	 */
	virtual bool16 CanEnableConvertToText( const UIDList* items ) const = 0;


	/**	Returns kTrue if any frame in the list can be converted to a page item
		Deprecated - Use FrameContentFacade.
		@param items IN UIDList of items to check for convertibility. 
		@return kTrue (can convert one or more items) or kFalse (can't convert any items).
	 */
	virtual bool16 CanEnableConvertToItem( const UIDList* items ) const = 0;

#endif // ID_DEPRECATED

	/**	Determine if any item in the list is a graphic frame.
		@param items IN UIDList of items to examine. 
		@param bWantEmpty IN pass kTrue there must be an empty Graphic Frame in the list
		@return kTrue if any item in the list is a graphic frame. 
	 */
	virtual bool16 DoesContainGraphicFrame( const UIDList* items, bool16 bWantEmpty ) const = 0;

	/**	Determine if item list contains one more more text frames.
		@param items IN UIDList of items to examine. 
		@param bWantEmpty IN pass kTrue if there must be an empty Text Frame in the list
		@return kTrue if any item in the list is a text frame, kFalse otherwise. 
	 */
	virtual bool16 DoesContainTextFrame( const UIDList* items, bool16 bWantEmpty ) const = 0;

	/**	Determine if any frame in the list is a page item.
		@param items IN UIDList of items to examine. 
		@return kTrue if any frame in the list is a page item, kFalse otherwise. 
	 */
	virtual bool16 DoesContainItem( const UIDList* items ) const = 0;

	/**	Determine if the frame for this item contains an empty story.
		@param frameData IN An IGraphicFrameData from the frame to check. 
		@return kTrue if the frame is a text frame which contains an empty story, kFalse otherwise. 
	 */
	virtual bool16 IsEmptyTextFrame( const IGraphicFrameData* frameData ) const = 0;

	/**	Determine if the item have its frame fit to the size of the content
		@param item IN UIDRef of item to check. 
		@return kInvalidUID if can't do operation, UID of item otherwise.
	 */
	virtual UID CanFitFrameToContent(const UIDRef& item) const = 0;

#ifdef ID_DEPRECATED
	/**	Determine if Fit Frame to Content menu item should be enabled for given list of items. Used
		by CanFitFrameToContent suite functions in IFrameContentSuite.
		Deprecated - Use FrameContentFacade.
		@param items IN UIDList of items to examine. 
		@return Enable state (kTrue for enabled, kFalse otherwise). 
	 */
	virtual bool16 CanEnableFitFrameToContent(const UIDList* items) const = 0;
#endif // ID_DEPRECATED

	/**	Return the list of items from the given list that can have their frame fit to their content (non-empty frames)
		@param items IN UIDList of items to examine. 
		@return UIDList of qualifying items from "items" UIDList
	 */
	virtual UIDList* CreateListOfFrames(const UIDList& items) const = 0;

	/**	Determine if the item can be stretched to fit its frame.
		@param item IN, UIDRef of item to examine. 
		@return UID of content, kInvalidUID if can't fit content to frame (or there is no content)
	 */
	virtual UID CanFitContentToFrame(const UIDRef& item) const = 0;

#ifdef ID_DEPRECATED
	/**	Determine if Fit Frame to Content menu item should be enabled for given list of items. Used
		by CanFitContentToFrame (and CanFitContentProp and CanCenterContentInFrame) suite functions in IFrameContentSuite.
		@param items IN UIDList of items to examine. 
		@return enable state (kTrue for enabled, kFalse otherwise). 
	 */
	virtual bool16 CanEnableFitContentToFrame(const UIDList* items) const = 0;
#endif // ID_DEPRECATED

	/**	Return the list of items from the given list that can have their content fit to their frame (non-empty frames)
		@param items IN UIDList of items to examine. 
		@return UIDList of qualifying items from "items" UIDList
	 */
	virtual UIDList* CreateListOfContent(const UIDList& items) const = 0;

	/** Calculate Frame Fitting cropping values that represent the current arrangement of content in the Frame given the
	    reference point and fitting option.
		@param frame [IN] the UIDRef of the frame with content
		@param cropAmounts [OUT] the calculated crop values
	 */
	virtual void CalculateCurrentCropValuesForFitting( UIDRef frame, PMRect& cropAmounts) = 0;

	/** Calculate the crop Rectangle in a coordinate space defined by contentToCropMatrix. This is the same as the
		content to Parent matrix with only the rotate, skew and "flip" (sign part of the scale matrix).
		@param content ITransform of the content
		@param cropAmounts 4-tuple of insets from the biggest rectangle inscribed in the content but aligned with the parent.
		@param contentToCropMatrix the part of the content to parent matrix that contains Rotation, Skew and Flip.
		@param cropToParentMatrix the part of the content to parent matrix that contains the scale magnatude and translation.
		  if you multiply the contentToCropMatrix with cropToParentMatrix you get the same thing as the content to parent matrix
	  */
	virtual void GetContentCropParameters(
		ITransform * contentTransform, 
		PMRect cropAmounts, 
		PMRect &cropRect, 
		PMMatrix &contentToCropMatrix, 
		PMMatrix &cropToParentMatrix
	) = 0;
};


#endif	// __IFrameContentUtils__
