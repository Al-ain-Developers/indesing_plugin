//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKGridPrefs.h $
//  
//  Owner: Heath Lynn
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
#ifndef __ICJKGridPrefs__
#define __ICJKGridPrefs__

#include "IPMUnknown.h"
#include "ICJKCharCountOptions.h"

/** ICJKGridPrefs is an interface that allows for the access and modification of CJK Grid Preferences. 
You may find these preferences on the application and/or document workspaces.
*/
class ICJKGridPrefs : public IPMUnknown
{

public:
	
	enum { kDefaultIID = IID_ICJKGRIDPREFS };
	
	/** Do drags currently snap to the layout grid
	@return kTrue if drag should snap to layout grid
	*/
	virtual bool16 GetSnapToLayoutGrid() = 0;
	
	/** Sets if drags should snap to the layout grid
	@param status IN kTrue to set snap, kFalse to turn snapping off
	*/
	virtual void SetSnapToLayoutGrid(bool16 status) = 0;

	/** Sets the color of the layout grid.
	@param uiColorUIDRef IN The new color.
	@param bTranslateDBToDB IN kTrue if you want this UIDRef to be translated to the current database
	*/
	virtual void SetLayoutGridColor(const UIDRef uiColorUIDRef, bool16 bTranslateDBToDB = kTrue) = 0;
	/** Gets the current layout grid color.
	@return A UIDRef for the layout grids color.
	*/
	virtual const UIDRef GetLayoutGridColor() = 0;

	/** Sets which nth cell to color.
	@param n IN Which nth cell to color.
	*/
	virtual void SetColorEveryNthCell(int16 n) = 0;
	
	/** Which (Nth) cell is being colored?
	@return Index
	*/
	virtual int16 GetColorEveryNthCell() = 0;

	/** Sets whether or not we start counting from the start of each new line.
	@param isSingleLine IN pass kTrue to start at each line, kFalse to continue counting
	without regard to line boundaries.
	*/
	virtual void SetSingleLineColorMode(bool16 isSingleLine) = 0;
	
	/** When coloring every nth grid cell, do we start counting from the start of the line?
	@return kTrue if we are in single line mode, meaning we start counting from the start of each line.
	*/
	virtual bool16 GetSingleLineColorMode() = 0;

	/** Sets whether or not CJK Grids are using ICF Mode (HLTODO)
	@param useICF IN pass kTrue to use ICF mode.
	*/
	virtual void SetICFMode(bool16 useICF) = 0;
	
	/** Are grids using ICF (HLTODO). 
	@return kTrue if grids are using ICF mode.
	*/
	virtual bool16 GetICFMode() = 0;

	/** Sets whether or not CJK grid drawing is to use circular cells.
	@param useCircles IN pass kTrue for circular cells.
	*/
	virtual void SetUseCircularCells(bool16 useCircles) = 0;
	
	/** Is grid drawing currently using circular cells.
	@return kTrue for circular cells.
	*/
	virtual bool16 GetUseCircularCells() = 0;

	/** Sets the minimum scale factor for grid drawing.  The grid will
	not draw when scaled out beyond the minimum.
	@param minScale IN The new minimum
	*/
	virtual void SetMinimumScale(const PMReal& minScale) = 0;
	
	/** Gets the minimum viewing scale for grid drawing.  The grid will
	not draw when scaled out beyond the minimum.
	@return The current minimum scale
	*/
	virtual PMReal GetMinimumScale() = 0;

	/** Gets view preference for show/hide all layout grids.
 	@return kTrue if all frame grids are visible, kFalse if hidden.
	*/
	virtual bool16 GetShowAllLayoutGrids() = 0;

	/** Sets view preference for show/hide layout grids.
	@param show IN kFalse to hide, kTrue to show
	*/
	virtual void SetShowAllLayoutGrids(bool16 show) = 0;

	/** Gets view preference for show/hide all frame grids.
 	@return kTrue if all frame grids are visible, kFalse if hidden.
	*/
	virtual bool16 GetShowAllFrameGrids() = 0;

	/** Sets view preference for show/hide frame grids.
	@param show IN kFalse to hide, kTrue to show
	*/
	virtual void SetShowAllFrameGrids(bool16 show) = 0;

	/** Gets view preference for show/hide character count.
 	@return kTrue if the character count is visible, kFalse if hidden.
	*/
	virtual bool16 GetShowCharacterCount() = 0;

	/** Sets view preference for show/hide character count.
	@param show IN kFalse to hide, kTrue to show
	*/
	virtual void SetShowCharacterCount(bool16 show) = 0;
	
	/** Utility method used to copy ICJKGridPrefs from another instance.
	@param source IN The source instance.
	@precondition *source must point to a valid ICJKGridPrefs instance.
	@postcondition The preferences are copied.
	*/
	virtual void CopyFrom(ICJKGridPrefs *source) = 0;

	/** Internal  method used to convert snap to layout grid setting. Please do not call!
	*/
	virtual bool16 GetSnapToLayoutGrid_DURING_CONVERSION_ONLY() = 0;

	/** Internal  method used to convert show layout grid setting. Please do not call!
	*/
	virtual bool16 GetShowAllLayoutGrids_DURING_CONVERSION_ONLY() = 0;

	/** Internal  method used to convert show frame grid setting. Please do not call!
	*/
	virtual bool16 GetShowAllFrameGrids_DURING_CONVERSION_ONLY() = 0;

	/** Internal  method used to convert show character count setting. Please do not call!
	*/
	virtual bool16 GetShowCharacterCount_DURING_CONVERSION_ONLY() = 0;

	/** Internal  method used to convert a color index during conversion. Please do not call!
	*/
	virtual int32 GetLayoutGridColorIndex_DURING_CONVERSION_ONLY() = 0;

};

#endif
