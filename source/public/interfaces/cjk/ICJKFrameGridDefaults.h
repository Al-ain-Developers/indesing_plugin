//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKFrameGridDefaults.h $
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
#ifndef __ICJKFrameGridDefaults__
#define __ICJKFrameGridDefaults__

#include "IPMUnknown.h"
#include "ICJKCharCountOptions.h"
#include "ICJKGridData.h"
#include "ICompositionStyle.h"
#include "CTextEnum.h"
#include "IDrawingStyle.h"

class ICJKFrameGridDefaults : public ICJKGridData
{
public:

	enum { kDefaultIID = IID_ICJKFRAMEGRIDDEFAULTS};
	
	enum View
	{
		kGridView,
		kZNView,
		kAlignView,
		kGridAndZNView
	};

	//---------------------------------------
	//	Get and Set Methods
	//---------------------------------------

	// Grid FontUID and Style(variant)
	virtual void SetFontUID(UID font) = 0;
	virtual UID GetFontUID() const = 0;
		
	virtual void SetFontStyleName(const PMString& name) = 0;
	virtual const PMString& GetFontStyleName() const = 0;
    virtual void SetMMAxes(int32 num, const Fixed* buffer) = 0;
    virtual int32 GetNumMMAxes() const = 0;
    virtual const Fixed* GetMMAxes() const = 0;

	// Grid cell size in points
	virtual void SetTextSize(PMReal size) = 0;
	virtual PMReal GetTextSize() const = 0;

	// Character and line aki (em box end to next em box start)
	virtual void SetCharAki(PMReal amount) = 0;
	virtual PMReal GetCharAki() const = 0;
	virtual void SetLineAki(PMReal space) = 0;
	virtual PMReal GetLineAki() const = 0;
	
	virtual PMReal GetCharOkuri(bool16 isVertical) const = 0;
	virtual PMReal GetLineOkuri(bool16 isVertical) const = 0;
	
	// Character scaling 
	virtual void SetHScale(PMReal value) = 0;
	virtual PMReal GetHScale() const = 0;

	virtual void SetVScale(PMReal value) = 0;
	virtual PMReal GetVScale() const = 0;

	// Text Alignment
	virtual void SetTextAlignment(ICompositionStyle::TextAlignment alignBody) = 0;
	virtual ICompositionStyle::TextAlignment GetTextAlignment() const = 0;
				
	// Grid Alignment

	virtual void SetGridAlignment(Text::GridAlignmentMetric gridAlignment) = 0;
	virtual Text::GridAlignmentMetric GetGridAlignment() const = 0;

	// Character Hang
	virtual void SetCharacterHang(IDrawingStyle::CharacterHang characterHang) = 0;
	virtual IDrawingStyle::CharacterHang GetCharacterHang() const = 0;

	// View
	virtual void SetView(ICJKFrameGridDefaults::View view) = 0;
	virtual ICJKFrameGridDefaults::View GetView() const = 0;

	// Character Count
	virtual PMReal GetCharacterCountTextSize() const = 0;
	virtual void SetCharacterCountTextSize(const PMReal & size) = 0;

	/**	Sets the default location of the character count.
		@param  IN
	*/
	virtual void SetCharacterCountLocation( ICJKCharCountOptions::Location location ) =0;
	
	/**	Returns the location of the character count.
		@return ICJKCharCountOptions::Location for the character count.
	*/
	virtual ICJKCharCountOptions::Location GetCharacterCountLocation() const = 0;

	//---------------------------------------
	//	Utility
	//---------------------------------------

	virtual void CopyFrom(const ICJKGridData * source, bool16 doDirty = kTrue) = 0;
	virtual void CopyFrom(const IFilteredCJKGridCmdData * source, bool16 doDirty = kTrue) = 0;
	virtual void CopyFrom(const ICJKFrameGridDefaults * source, bool16 doDirty = kTrue) = 0;
	
	virtual bool16 GridDataMatches(const ICJKGridData *g2) const = 0;
	virtual bool16 NonAlignmentGridDataMatches(const ICJKGridData *g2) const = 0;
};

DECLARE_BASE_TYPE(ICJKFrameGridDefaults::View);

#endif
