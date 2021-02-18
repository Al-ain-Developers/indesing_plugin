//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemTypeUtils.h $
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
#ifndef __IPageItemTypeUtils__
#define __IPageItemTypeUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "IAnchoredObjectData.h"

#include "UIDList.h"

class IMainItemTOPData;
class IGraphicFrameData;
class IHierarchy;
class IScrapItem;



/**
	Utility class for classifying and determing what type of page item something is.
	@ingroup layout_util
	@ingroup layout_pgitem
 */
class IPageItemTypeUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMTYPEUTILS };

	/**	Categorize the page items in the UIDList. Replacement for 
		LayoutUtils::WhatIsSelected(). When using the selection UIDList, it should
		only be called from the Layout CSB in the new selection architecture.
		NOTE: Any of the int32* may be nil. In fact, for performance reasons, pass nil for any
		count you don't care about.
		@param UIDList, UIDList [IN] UIDList of page items to categorize.
		@param *totalItemCountPtr [OUT] Total number of items in the selection, may be nil.
		@param *graphicFrameCountPtr [OUT] Total number of graphic frames in the selection, may be nil. 
		@param *textFrameCountPtr [OUT] Total number of text frames in the selection, may be nil. 
		@param *imageCountPtr [OUT] Total number of images in the selection, may be nil. 
		@param *topCountPtr [OUT] Total number of Text on Path items in the selection, may be nil. 
		@param *guideCountPtr [OUT] Total number of guide items in the selection, may be nil. 
		@param *standoffCountPtr [OUT] Total number of standoff items in the selection, may be nil. 
		@param *standardItemCountPtr [OUT] Default case of not one of the above types, total number of all other kinds of items in the selection, may be nil. 
	 */
	virtual void CategorizePageItems (const UIDList, int32 *totalItemCountPtr, int32 *graphicFrameCountPtr, int32 *textFrameCountPtr, int32 *imageCountPtr, int32 *topCountPtr, int32 *guideCountPtr, int32 *standoffCountPtr, int32 *standardItemCountPtr) const = 0;

	/**	Is the Specified page item a "Text on a Path" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsTextOnAPath	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Text on a Path" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsTextOnAPath	(const IPMUnknown* iPageItem) const = 0;

	/** Returns true iff the item is an embedded HTML item (e.g., iframe)
	 @param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	  */
	virtual bool16 IsHTMLPageItem(const UIDRef& pageItemUIDRef) const = 0;

	/** Returns true iff the item is an embedded HTML item (e.g., iframe)
	 @param iPageItem [IN] An interface from the page item in question. 
	 @return kTrue or kFalse
	 */
	virtual bool16 IsHTMLPageItem(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a "Graphic frame" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGraphicFrame	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Graphic frame" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGraphicFrame	(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a "Text frame" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsTextFrame	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Text frame" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	 
	virtual bool16	IsTextFrame	(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a "Graphic" (raster or vector) item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGraphic	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Graphic" (raster or vector) item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGraphic	(const IPMUnknown* iPageItem) const = 0;
	
	/**	Is the Specified page item a "Guide" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGuide	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Guide" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGuide	(const IPMUnknown* iPageItem) const = 0;

	 
	/**	Are only guides in the list
		@param items A UIDList
		@return kTrue or kFalse
	 */
	virtual bool16	OnlyGuidesInList (const UIDList& items) const = 0;

	/**	Is the Specified page item a "Standoff" or "Text Inset" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsStandOff	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Standoff" or "Text Inset" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsStandOff	(const IPMUnknown* iPageItem) const = 0;

	/**	Does the Specified page item have a "Standoff" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return bool16 
	 */
	virtual bool16  HasStandOff	(const IPMUnknown*) const = 0;

	/**	Is the Specified page item a "Text Inset" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsTextInset	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Text Inset" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsTextInset	(const IPMUnknown* iPageItem) const = 0;

	/**	Does the Specified page item have a "Text Inset" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return bool16 
	 */
	virtual bool16  HasTextInset (const IPMUnknown*) const = 0;

	/**	Is the Specified page item's root an "inline" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsInline	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item's root an "inline" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsInline	(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item's direct parent an "inline" item? Useful for
		determining if you have the actual inline selected (kTrue), or an item
		farther down the inline's hierarchy (kFalse) (e.g. an image or pasted inside item).
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsDirectInlineItem	(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item's direct parent an "inline" item? Useful for
		determining if you have the actual inline selected (kTrue), or an item
		farther down the inline's hierarchy (kFalse) (e.g. an image or pasted inside item).
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsDirectInlineItem	(const IPMUnknown* iPageItem) const = 0;
	
	/**	Return the position of an inline anchored object. One of the values: kStandardInline, kAnchoredObject, kAboveLine.
		@param pageItemUIDRef [IN] UIDRef of the page item in question. Page item must be an inline. 
		@return AnchoredPosition enum value. See IAnchoredObjectData.h.
	 */
	virtual IAnchoredObjectData::AnchoredPosition GetInlinePosition(const UIDRef& pageItemUIDRef) const = 0;

	/**	Return the position of an inline anchored object. One of the values: kStandardInline, kAnchoredObject, kAboveLine.
		@param pageItemUIDRef [IN] UIDRef of the page item in question. Page item must be an inline.
		@return AnchoredPosition enum value. See IAnchoredObjectData.h.
	 */
	virtual IAnchoredObjectData::AnchoredPosition GetInlinePosition(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a "group" item?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGroup		(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "group" item?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsGroup		(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a "media" item (sound or movie)?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsMedia		(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "media" item (sound or movie)?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsMedia		(const IPMUnknown* iPageItem) const = 0;

	/**	Is the page item content of a frame? (For InCopy). e.g. Can item be modified/selected? Items within other frames and inlines are both considered content (though not anchored frames).
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsContent (const IPMUnknown* iPageItem) const = 0;

	/**	Is the page item content of a frame? (For InCopy). e.g. Can item be modified/selected? Items within other frames and inlines are both considered content (though not anchored frames).
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsContent (const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "child of the scrap" item?
		@param IScrapItem* [IN] The parent item to check
		@param IScrapItem* [IN] The child item to check
		@return kTrue or kFalse
	 */
	virtual bool16	IsChildOfScrapItem (const IScrapItem*, IScrapItem*) const = 0;

	/** Is the specified page item an inline in the primary story thread (meaning not in a table, or a note, or a footnote)?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsInlineInStory(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item an inline is in the story that is locked
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsInlineInLockedStory(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item an inline in a TextStoryThread that supports TextWrap?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsWrapSupportedInline(const IPMUnknown* iPageItem) const = 0;

	/** Is the specified page item a placed InDesign page?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16 IsPlacedInDesignPage(const IPMUnknown* iPageItem) const = 0;

	/** Is the specified page item a placed InDesign page?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsPlacedInDesignPage(const UIDRef& pageItemUIDRef) const = 0;

	/** Is the specified page item a Button?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16 IsButton(const IPMUnknown* iPageItem) const = 0;

	/** Is the specified page item a Button?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsButton(const UIDRef& pageItemUIDRef) const = 0;

	/** Is the specified page item a multi-state object?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16 IsMultiStateObject(const IPMUnknown* iPageItem) const = 0;

	/** Is the specified page item a multi-state object?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsMultiStateObject(const UIDRef& pageItemUIDRef) const = 0;

	/** Does the specified page item have a form field interface? (Button or Multi-state object)
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsFormItem( IPMUnknown *inBoss ) const = 0;

	/** Does the specified page item have a form field interface? (Button or Multi-state object)
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsFormItem( UIDRef inRef ) const = 0;

	/** Is the specified page item a check box?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsCheckBox(const IPMUnknown* iPageItem) const = 0;

	/** Is the specified page item a check box?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsCheckBox(const UIDRef& pageItemUIDRef) const = 0;

	/** Is the specified page item a radio button?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsRadioButton(const IPMUnknown* iPageItem) const = 0;

	/** Is the specified page item a radio button?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	IsRadioButton(const UIDRef& pageItemUIDRef) const = 0;

	/** Does the specified page item has appearance list?
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16 PageItemHasAppearanceList(const IPMUnknown* iPageItem) const = 0;

	/** Does the specified page item has appearance list?
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	 */
	virtual bool16	PageItemHasAppearanceList(const UIDRef& pageItemUIDRef) const = 0;

	/** Does the specified page item placed inside the table's graphic cell(not as inline)
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsPlacedInTable(const IPMUnknown* iPageItem) const = 0;

	/** Does the specified page item placed inside the table's graphic cell(not as inline)
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsPlacedInTable(const UIDRef& pageItemUIDRef) const = 0;

	/** Does the specified page item's direct parent is the root object placed inside the table's graphic cell(not as inline)
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsDirectlyPlacedInTable(const IPMUnknown* iPageItem) const = 0;

	/** Does the specified page item's direct parent is the root object placed inside the table's graphic cell(not as inline)
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsDirectlyPlacedInTable(const UIDRef& pageItemUIDRef) const = 0;

	/** Does the specified page item placed inside the text model, either as inline object or being placed inside the table's graphic cells
		@param iPageItem [IN] An interface from the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsPlacedInsideText(const IPMUnknown* iPageItem) const = 0;
	
	/** Does the specified page item placed inside the text model, either as inline object or being placed inside the table's graphic cells
		@param pageItemUIDRef [IN] UIDRef of the page item in question. 
		@return kTrue or kFalse
	*/
	virtual bool16	IsPlacedInsideText(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the specified page item a text frame for an endnote story?
	@param pageItemUIDRef [IN] UIDRef of the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsEndnoteTextFrame(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the specified page item a text frame for an endnote story?
	@param iPageItem [IN] An interface from the page item in question.
	@return kTrue or kFalse
	*/

	virtual bool16	IsEndnoteTextFrame(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a "Empty Graphic frame"(contains nothing) item?
	@param pageItemUIDRef [IN] UIDRef of the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsEmptyGraphicFrame(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a "Empty Graphic frame"(contains nothing) item?
	@param iPageItem [IN] An interface from the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsEmptyGraphicFrame(const IPMUnknown* iPageItem) const = 0;

	/**	Is the Specified page item a shape(indesign native) item?
	@param pageItemUIDRef [IN] UIDRef of the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsNotAFrame(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a shape(indesign native) item?
	@param iPageItem [IN] An interface from the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsNotAFrame(const IPMUnknown* iPageItem) const = 0;

	/**	Is the selected frame is threaded text frame?
	@param pageItemUIDRef [IN]  UIDRef of the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsThreadedTextFrame(const UIDRef& pageItemUIDRef) const = 0;

	/**	Is the Specified page item a shape(indesign native) item?
	@param iPageItem [IN] An interface from the page item in question.
	@return kTrue or kFalse
	*/
	virtual bool16	IsThreadedTextFrame(const IPMUnknown* iPageItem) const = 0;
    
    /** Is the Specified page item an "SVG" item?
     @param pageItemUIDRef [IN] UIDRef of the page item in question.
     @return kTrue or kFalse
     */
    virtual bool16 IsSVGPageItem(const UIDRef& pageItemUIDRef) const = 0;
    
    /** Is the Specified page item an "SVG" item?
     @param iPageItem [IN] An interface from the page item in question.
     @return kTrue or kFalse
     */
    virtual bool16 IsSVGPageItem(const IPMUnknown* iPageItem) const = 0;
    
    /** Is the Specified page item a Table Frame?
     @param pageItemUIDRef [IN] UIDRef of the page item in question.
     @return kTrue or kFalse
     */
    virtual bool16 IsTableFrame(const UIDRef& pageItemUIDRef) const = 0;
    
    /** Is the Specified page item a Table Frame?
     @param iPageItem [IN] An interface from the page item in question.
     @return kTrue or kFalse
     */
    virtual bool16 IsTableFrame(const IPMUnknown* iPageItem) const = 0;
};


#endif	// __IPageItemTypeUtils__
