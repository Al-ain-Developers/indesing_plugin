//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPagesPanelPrefs.h $
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
//========================================================================================

#pragma once
#ifndef __IPagesPanelPrefs__
#define __IPagesPanelPrefs__

#include "IPMUnknown.h"
#include "PagesPanelID.h"

class IGeometry;
class ISpread;
class IControlView;
/**
	Preferences that define the appearance of the pages panel
*/
class IPagesPanelPrefs : public IPMUnknown
{
public:
	
	/** Enumerated sizes for the Pages Panel page and master page icons */
	enum
	{
		/** Invalid setting, used internally for command as an "ignore" value */
		kInvalidPageIconSize = -1,
		/** Allows 1 master page prefix character to be visible */
		kExtraSmallPageIconSize = 0,
			kExtraSmall = kExtraSmallPageIconSize,
		/** Allows 2 master page prefix characters to be visible  */
		kSmallPageIconSize = 1,
			kSmall = kSmallPageIconSize,
		/** Allows 3 master page prefix characters to be visible */
		kMediumPageIconSize = 2,
			kMedium = kMediumPageIconSize,
		/** Allows 4 master page prefix characters to be visible */
		kLargePageIconSize = 3,
			kLarge = kLargePageIconSize,
		/** Allows 5 master page prefix characters to be visible  */
		kExtraLargePageIconSize = 4,
			kGradeAJumbo = kExtraLargePageIconSize,
		kExtraExtraLargePageIconSize = 5
	};
	typedef int32 IconSize;

	/** View setting enum.
	*/
	typedef enum
	{
		kInvalidView = -1,			/** Value that means don't change the view setting */
		kHorizontally = 0,			/** Standard setting for rows of pages arranged from left to right, multiple pages per row. */
		kVertically = 1,			/** View setting for one page per row, arranged and stacked vertically. */
		kByAlternateLayout = 2			/** View setting for each alternate layout arranged in a vertical stack. */
	} ViewSetting;

		/** Set page tab icon size
			@param set pages subpanel icon size (value is one of the enums in IPagesPanelPrefs)
		*/
	virtual void SetIconSize(IconSize iconSize) = 0;

		/** Get page tab icon size 
			@return Pages subpanel icon size (value is one of the enums in IPagesPanelPrefs)
		*/
	virtual IconSize GetLayoutIconSize() = 0;
	
		/** Set method for how to arrange pages.
			@param setting, a ViewSetting enum
			@see ViewSetting for valid values.
		*/
	virtual void SetViewSetting(ViewSetting setting) = 0;

		/** Get method for the view setting of the layout pages subpanel.
			@return a value from ViewSetting enum
		*/
	virtual ViewSetting GetViewSetting() = 0;

		/** Set master page icon size	
			@param set master pages subpanel icon size (value is one of the enums in IPagesPanelPrefs)
		*/
	virtual void SetMasterIconSize(IconSize iconSize) = 0;

		/** Get master page icon size	
			@return master pages subpanel icon size (value is one of the enums in IPagesPanelPrefs)
		*/
	virtual IconSize GetMasterIconSize() = 0;
	
		/** Set vertical view (kTrue), or wrapping view (kFalse)
			@param on set masters to vertical view if kTrue, or wrapping view if kFalse
		*/
	virtual void SetMasterVerticalView(bool16 on) = 0;

		/** Get vertical view (kTrue), or wrapping view (kFalse)
			@return kTrue if masters is in vertical view, or kFalse if wrapping view
		*/
	virtual bool16 GetMasterVerticalView() = 0;

		/** Set fixed size pages pane
			@param on set pages subpanel to fixed size on resize if kTrue, variable size if kFalse
		*/
	virtual void SetPagesFixedSize(bool16 on) = 0;

		/** Get pages fixed size
			@return kTrue if pages subpanel is fixed size on resize, kFalse if variable size
		*/
	virtual bool16 GetPagesFixedSize() = 0;

		/** Set master pane to be fixed size
			@param on set master pages subpanel to fixed size on resize if kTrue, variable size if kFalse
		*/
	virtual void SetMasterFixedSize(bool16 on) = 0;

		/** Get master pane fixed size
			@return kTrue if master pages subpanel is fixed size on resize, kFalse if variable size
		*/
	virtual bool16 GetMasterFixedSize() = 0;

		/** Set pages on top
			@param on pages subpanel on top if kTrue, on bottom if kFalse
		*/
	virtual void SetPagesOnTop(bool16 on) = 0;

		/** Get pages on top
			@return kTrue if pages subpanel is on top, kFalse if it is on bottom
		*/
	virtual bool16 GetPagesOnTop() = 0;

		/** Set thumbnails on or off for pages section
			@param on pages thumbnails on if kTrue, off if kFalse
		*/
	virtual void SetPagesThumbnails(bool16 on) = 0;

		/** Get thumbnails setting for pages section
			@return kTrue if pages thumbnails are on, kFalse if off
		*/
	virtual bool16 GetPagesThumbnails() = 0;

		/** Set thumbnails on or off for masters section
			@param on masters thumbnails on if kTrue, off if kFalse
		*/
	virtual void SetMastersThumbnails(bool16 on) = 0;

		/** Get thumbnails setting for masters section
			@return kTrue if masters thumbnails are on, kFalse if off
		*/
	virtual bool16 GetMastersThumbnails() = 0;
	
		/** Set transparency icon on or off
			@param on transparency icon is on if kTrue, off if kFalse
		*/
	virtual void SetShowTransparencyIcon(bool16 on) = 0;

		/** Get the bool indicating if the transparency indicator should be drawn on spreads with transparency applied.
			This is the checkerboard icon.
			@return kTrue if the transparency icon is on; kFalse otherwise
		*/
	virtual bool16 GetShowTransparencyIcon() = 0;	

		/** Set transitions icon on or off
			@param on transitions icon is on if kTrue, off if kFalse
		*/
	virtual void SetShowTransitionsIcon(bool16 on) = 0;

		/** Get the bool indicating if the transition icon should be drawn on spreads with page transitions applied.
			@return kTrue if the spread has a transition applied; kFalse otherwise
		*/
	virtual bool16 GetShowTransitionsIcon() = 0;	

		/** Set rotation icon on or off
			@param on rotation icon is on if kTrue, off if kFalse
		*/
	virtual void SetShowRotationIcon(bool16 on) = 0;

		/** Get the bool indicating if the rotation icon should be drawn on spreads with non-zero rotation applied.
			@return kTrue if the rotation icon is on; kFalse otherwise
		*/
	virtual bool16 GetShowRotationIcon() = 0;	






//////////////////////////////////////////////////////////
//The following member functions are for internal use only
//////////////////////////////////////////////////////////


	// The following methods define the look of the pages panel - they are not backed by saved 
	// data, they return values that are a function of the above get/set methods.
	
		/** Get the number of pixels between spreads (vertically) in the pages panel 
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return the empty space between rows in the pages panel (this same value is used in vertical and wrapping modes, in both the masters and pages section).
		 */
	virtual int32 GetLayoutVerticalInterSpreadSpace() = 0;
	virtual int32 GetMasterVerticalInterSpreadSpace() = 0;

		/** Get the number of pixels between spreads (horizontally) in the pages panel - used in wrapping view
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return the empty space between columns in the pages panel (this same value is used in both the masters and pages section).
		*/
	virtual int32 GetHorizontalInterSpreadSpace( IconSize iconSize) = 0;

		/** Get the number of vertical pixels used by each row of the pages panel
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@param widthToHeightRatio - IN: Typically, we draw a rectangle with a folder
				corner for each page and the ratio of the width to height is 3:4.  However,
				it may be desirable to draw a rectangle that maintains the proportions of
				the actual page size if, for example, we want to draw a thumbnail of the page.
			@return how many pixels tall is a row (horizontal or vertical layout; masters or pages) when the icon size specified is used?
		*/
	virtual int32	GetMasterPageRowHeight() = 0;
	virtual int32	GetLayoutPageRowHeight() = 0;
	
		/** Get the number of pixels wide a page tab will be
			@param iconSize size of the page tab icons 
			@param widthToHeightRatio - IN: Typically, we draw a rectangle with a folder
				corner for each page and the ratio of the width to height is 3:4.  However,
				it may be desirable to draw a rectangle that maintains the proportions of
				the actual page size if, for example, we want to draw a thumbnail of the page.
			@return how wide the page icons should be, given the specified icon size, 
		*/
	virtual int32	GetMasterPageTabWidth( IGeometry* thePage) = 0;
	virtual int32	GetLayoutPageTabWidth( IGeometry* thePage) = 0;

		/** Get the number of pixels high each page tab will be
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@param widthToHeightRatio - IN: Typically, we draw a rectangle with a folder
				corner for each page and the ratio of the width to height is 3:4.  However,
				it may be desirable to draw a rectangle that maintains the proportions of
				the actual page size if, for example, we want to draw a thumbnail of the page.
			@return how tall should the page icons be, given the specified icon size
		*/
	virtual int32	GetMasterPageTabHeight() = 0;
	virtual int32	GetLayoutPageTabHeight() = 0;


		/** Get the number of pixels used to draw the fold in the corner of a page tab
			@param iconSize size of the page tab icons 
			@return How many pixels the corner fold should be for the specified icon size
		*/
	virtual int32	GetCornerFoldSize(IconSize iconSize) = 0;

		/** Get the number of pixels around each spread widget horizontally
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return how wide, beyond the page tab, should the spread widget be for the specified icon size? this width is added to both sides of the spread widget
		*/
	virtual int32	GetSpreadBorderWidth(IconSize iconSize, bool16 bVerticalMode) = 0;
	
		/** Get the number of pixels around each spread widget vertically
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@param spaceAbove space above
			@param spaceBelow space below
			@return how tall should the border be for the specified icon size? Optionally, break that down into space below and space above
		*/
	virtual int32	GetSpreadBorderHeight(IconSize iconSize, int32 *spaceAbove /*= 0*/, int32 *spaceBelow /*= 0*/) = 0;
	
		/** Get the number of pixels between the bottom of the spread widget and the top of the text widget
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return how many pixels there should be between the spread widget and the text underneath it
		*/
	virtual int32	GetSpreadTextOffset(IconSize iconSize) = 0;
	
		/** Get the number of pixels tall the text under the spread is
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return how tall the text is underneath this spread
		*/
	virtual int32	GetSpreadTextSize( IconSize iconSize) = 0;
	
		/** Get the height of the section marker (above the spread widget)
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return for the given page tab icon size, how tall the section marker should be
		*/
	virtual int32	GetSectionMarkerSize(IconSize iconSize, bool16 bVerticalMode /*= kFalse*/) = 0;

	
		/** Get the number of pixels above the first and below the last spread widget.
			@param iconSize size of the page tab icons 
			@param spaceAtTop white space above all rows
			@param spaceAtBottom white space below all rows
			@return for the given page tab icon size, how much white space should be left above the first row & after the last row? (returns spaceAtTop)
		*/
	virtual int32	GetPanelBorder(IconSize iconSize, int32 *spaceAtTop /*= 0*/, int32 *spaceAtBottom /*= 0*/) = 0;


	/** Get the height of the color flag (below the page tab widget)
			@param iconSize size of the page tab icons 
			@param bVerticalMode kTrue if panel is in vertical mode, kFalse otherwise
			@return for the given page tab icon size, how tall the color label should be
		*/
	virtual PMPoint	GetColorLabelSize(IconSize iconSize) = 0;



};

#endif
