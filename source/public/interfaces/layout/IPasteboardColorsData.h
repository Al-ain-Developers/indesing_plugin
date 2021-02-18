//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPasteboardColorsData.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IPasteboardColorsData__
#define __IPasteboardColorsData__

#include "IPMUnknown.h"
#include "SpreadID.h"

/**	Interface for setting and getting color data for the pasteboard.
	@ingroup layout_paste
*/
class IPasteboardColorsData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPASTEBOARDCOLORSDATA };	// for UseDefaultIID()

	/** Set the color data all at once.
		@param iPasteboardColorIndex IN color index for the pasteboard
		@param iPreviewBackgroundColorIndex IN color index for the preview background
		@param iBleedColorIndex IN color index for bleed lines
		@param iSlugColorIndex IN color index for slug lines
	*/
	virtual void Set(	int32 iPasteboardColorIndex,
						int32 iPreviewBackgroundColorIndex,
						int32 iBleedColorIndex,
						int32 iSlugColorIndex) = 0;	

	/** Set the pasteboard color
		@param val IN color index for the pasteboard
	*/
	virtual void SetPasteboardColorIndex(int32 val) = 0;

	/** Set the preview background color
		@param val IN color index for the preview background
	*/
	virtual void SetPreviewBackgroundColorIndex(int32 val) = 0;

	/** Set the bleed line color
		@param val IN color index for bleed lines
	*/
	virtual void SetBleedColorIndex(int32 val) = 0;

	/** Set the slug line color
		@param val IN color index for slug lines
	*/
	virtual void SetSlugColorIndex(int32 val) = 0;

	/** Get the pasteboard color
		@return the color index for the pasteboard
	*/
	virtual const int32 GetPasteboardColorIndex() const = 0;

	/** Get the preview background color
		@return the color index for the preview background
	*/
	virtual const int32 GetPreviewBackgroundColorIndex() const = 0;

	/** Get the bleed line color
		@return the color index for bleed lines
	*/
	virtual const int32 GetBleedColorIndex() const = 0;

	/** Get the slug line color
		@return the color index for slug lines
	*/
	virtual const int32 GetSlugColorIndex() const = 0;

	/** Set the flag to match the Preview color with theme color. Used in preview mode.
		@param bool - true - match color to theme, false - do not match to theme color
		@return UIDRef - UIDRef of the UI color used for preview background fill. 
	 */
	virtual void SetDataMatchPreviewColorToTheme(bool16) = 0;

	/** Get the flag to match the Preview color with theme color. Used in preview mode.
		@param none 
		@return bool16 - match color to theme or not
	 */
	virtual bool16 GetDataMatchPreviewColorToTheme() = 0;

};




#endif // __IPasteboardColorsData__
