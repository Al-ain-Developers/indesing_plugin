//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKGridData.h $
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
//  
//  Purpose: Basic grid definition
//  
//========================================================================================

#pragma once
#ifndef __ICJKGridData__
#define __ICJKGridData__

#include "IPMUnknown.h"
//#include "IFilteredCJKGridCmdData.h"
#include "ICompositionStyle.h"
#include "CTextEnum.h"
#include "IDrawingStyle.h"

#include "CJKGridID.h"

class IFilteredCJKGridCmdData;

/** ICJKGridData is the interface used to describe a CJK grid.  Among other places it is
      aggregated on the kTextStoryBoss to describe a story's frame grids, and on the 
      kPageBoss to describe a page's layout grid.
*/
class ICJKGridData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICJKGRIDDATA };
	
	//---------------------------------------
	//	Get and Set Methods
	//---------------------------------------

	/**  Sets the font UID.
		@param font IN The new font UID.
		@precondition font should be a valid font UID.
	*/
	virtual void SetFontUID(UID font) = 0;

	/**  Returns the font UID.
		@return the current font UID.
	*/
	virtual UID GetFontUID() const = 0;
		
	/**  Sets the font style name
		@param name IN The new font style name.
	*/
	virtual void SetFontStyleName(const PMString& name) = 0;

	/**  Returns the font style name
		@return The font style name
	*/
	virtual const PMString& GetFontStyleName() const = 0;

	/**
	Set axes for variable fonts. If you want
	to set this you can use the value from either IPMFont::GetNumDesignAxes() and
	IPMFont AccessDesignVector or FontGroupIteratorCallBack::OnMMAxes

	@param    num        number of axes
	@param    buffer    buffer with axes
	*/
	virtual void SetMMAxes(int32 num, const Fixed* buffer) = 0;
	/**
		Get number multiple master axes

		@return    number of axes
	*/
	virtual int32 GetNumMMAxes() const = 0;
	/**
		Get multiple master axes

		@return    Fixed*
	*/
	virtual const Fixed* GetMMAxes() const = 0;

	/**  Sets the pre-scale size of the grid cells.
		@param size IN New size of grid.
	*/
	virtual void SetTextSize(PMReal size) = 0;

	/**  Returns the pre-scale size of the grid box in points.
		@return grid size in points.
	*/
	virtual PMReal GetTextSize() const = 0;

	/**  Sets char aki.
		@param space IN The new space between grid cells in the char wise direction.
	*/
	virtual void SetCharAki(PMReal amount) = 0;

	/**  Returns char aki.
		@return the distance in points between grid cells in the char wise direction
	*/
	virtual PMReal GetCharAki() const = 0;

	/**  Sets line aki.
		@param space IN The new space between grid cells in the line wise direction.
	*/
	virtual void SetLineAki(PMReal space) = 0;
	
	/**  Returns line aki.
		@return the distance in points between grid cells in the line wise direction
	*/
	virtual PMReal GetLineAki() const = 0;

	/**  Returns Char Okuri in points.  When vertical, okuri equals
		the grid size * vertical glyph scale + char aki.  When horizontal
		okuri equals grid size * horizontal glyph scale + char aki.
		@param isVertical IN Whether or not the frame is vertical..
		@return Grid size * appropriate glyph scale + char aki
	*/
	virtual PMReal GetCharOkuri(bool16 isVertical) const = 0;

	/**  Returns Line Okuri in points.  When vertical, okuri equals
		the grid size * horizontal glyph scale + line aki.  When horizontal
		okuri equals grid size * vertical glyph scale + line aki.
		@param isVertical IN Whether or not the frame is vertical..
		@return Grid size * appropriate glyph scale + line aki
	*/
	virtual PMReal GetLineOkuri(bool16 isVertical) const = 0;

	/**  Sets horizontal glyph scale.
		@param value IN New horizontal glyph scale.
	*/
	virtual void SetHScale(PMReal value) = 0;
	/**  Returns horizontal glyph scale
		@return Horizontal glyph scale percentage (1.0 = 100%)
	*/
	virtual PMReal GetHScale() const = 0;

	/**  Sets vertical glyph scale.
		@param value IN New vertical glyph scale.
	*/
	virtual void SetVScale(PMReal value) = 0;

	/**  Returns vertical glyph scale
		@return Vertical glyph scale percentage (1.0 = 100%)
	*/
	virtual PMReal GetVScale() const = 0;

	/**  Sets text alignment setting
		@param alignment IN  New text alignment setting
	*/
	virtual void SetTextAlignment(ICompositionStyle::TextAlignment alignment) = 0;

	/**  Returns text alignment setting
		@return ICompositionStyle::TextAlignment 
	*/
	virtual ICompositionStyle::TextAlignment GetTextAlignment() const = 0;
				
	/**  Sets grid alignment setting
		@param gridAlignment IN  New grid alignment setting
	*/
	virtual void SetGridAlignment(Text::GridAlignmentMetric gridAlignment) = 0;

	/**  Returns grid alignment setting
		@return Text::GridAlignmentMetric.
	*/
	virtual Text::GridAlignmentMetric GetGridAlignment() const = 0;

	/**  Sets character hang setting
		@param characterHang IN  New character hang setting
	*/
	virtual void SetCharacterHang(IDrawingStyle::CharacterHang characterHang) = 0;

	/**  Returns character hang setting
		@return IDrawingStyle::CharacterHang.
	*/
	virtual IDrawingStyle::CharacterHang GetCharacterHang() const = 0;

	/**  Copies all data from the passed in ICJKGridData to this ICJKGridData.
		@param source IN ICJKGridData to copy from.
		@param doDirty IN Should dirty be called when changing data in this ICJKGridData.
	*/
	virtual void CopyFrom(const ICJKGridData * source, bool16 doDirty = kTrue) = 0;

	/**  Copies all valid data from the passed in IFilteredCJKGridCmdData to this ICJKGridData.
		@param source IN IFilteredCJKGridCmdData to copy from.
		@param doDirty IN Should dirty be called when changing data in this ICJKGridData.
	*/
	virtual void CopyFrom(const IFilteredCJKGridCmdData * source, bool16 doDirty = kTrue) = 0;

	/**  Compares this grid data with passed in grid data.
		@param g2 IN Pointer to ICJKGridData to compare to this ICJKGridData .
		@return kTrue on match, kFalse on difference
	*/
	virtual bool16 GridDataMatches(const ICJKGridData *g2) const = 0;

	/**  Compares this grid data (excluding alignment data) with passed in grid data.
		@param g2 IN Pointer to ICJKGridData to compare to this ICJKGridData .
		@return kTrue on match, kFalse on difference
	*/
	virtual bool16 NonAlignmentGridDataMatches(const ICJKGridData *g2) const = 0;

};

#endif
