//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPasteboardPrefs.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IPasteboardPrefs__
#define __IPasteboardPrefs__

#include "IPMUnknown.h"
#include "SpreadID.h"

/**	
	@ingroup layout_paste
*/
class IPasteboardPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPASTEBOARDPREFERENCES };

	/**
		Define the vertical gap between pasteboards.
	*/
	enum { kPasteboardSeperatorAmount = 36 };	// 1/2 an inch

	////
	//// Pasteboard Preferences
	////
	
	/**	Set the minimum pasteboard border for around the spread.
		@param minXBorder - minimum value for left and right border.
		@param minYBorder - minimum value for top and bottom border.
	 */
	virtual void SetPasteboardBorder( PMReal minXBorder, PMReal minYBorder) = 0;

	/**	Get the minimum pasteboard border for around the spread.
		@param minXBorder - return the minimum value for left and right border.
		@param minYBorder - return the minimum value for top and bottom border.
	 */
	virtual void GetPasteboardBorder( PMReal* minXBorder, PMReal* minYBorder) const = 0;
	
	// Pasteboard color -- UNUSED in 3.0

	/**	Set the UI color UID for the pasteboard color. Used in normal (non-preview) mode.
		This is UNUSED in 3.0, but left in for future use.
		@param uiColorUID - UID of a UI color to set the pasteboard fill color to.
	 */
	virtual void SetPasteboardColor(UID uiColorUID) = 0;

	/** Get the UI color UID for the pasteboard color. Used in normal (non-preview) mode.
		This is UNUSED in 3.0, but left in for future use.
		@param none
		@return UIDRef - UIDRef of the UI color used for pasteboard fill. 
	 */
	virtual UIDRef GetPasteboardColor() const = 0;

	// Preview background color 

	/**	Set the UI color UID for the preview background color. Used in preview mode.
		@param uiColorUID - UID of a UI color to set the preview background fill color to.
	 */
	virtual void SetPreviewBackgroundColor(UID uiColorUID) = 0;

	/** Get the UI color UID for the pasteboard color. Used in preview mode.
		@param none
		@return UIDRef - UIDRef of the UI color used for preview background fill. 
	 */
	virtual UIDRef GetPreviewBackgroundColor() const = 0;

	/** Set the flag to match the Preview color with theme color. Used in preview mode.
		@param bool - true - match color to theme, false - do not match to theme color
		@return UIDRef - UIDRef of the UI color used for preview background fill. 
	 */
	virtual void SetMatchPreviewColorToThemeColor(bool16) = 0;

	/** Get the flag to match the Preview color with theme color. Used in preview mode.
		@param none 
		@return bool16 - match color to theme or not
	 */
	virtual bool16 GetMatchPreviewColorToThemeColor() = 0;

	// Bleed color

	/**	Set the UI color UID for the bleed color. Used in normal (non-preview) mode.
		@param uiColorUID - UID of a UI color to set the bleed line color to.
	 */
	virtual void SetBleedColor(UID uiColorUID) = 0;

	/** Set the UI color UID for the bleed color. Used in normal (non-preview) mode.
		@param none
		@return UIDRef - UIDRef of the UI color used for bleed line. 
	 */
	virtual UIDRef GetBleedColor() const = 0;

	// Slug color

	/**	Set the UI color UID for the slug color. Used in normal (non-preview) mode.
		@param uiColorUID - UID of a UI color to set the slug line color to.
	 */
	virtual void SetSlugColor(UID uiColorUID) = 0;

	/** Set the UI color UID for the slug color. Used in normal (non-preview) mode.
		@param none
		@return UIDRef - UIDRef of the UI color used for slug line. 
	 */
	virtual UIDRef GetSlugColor() const = 0;
};

#endif
