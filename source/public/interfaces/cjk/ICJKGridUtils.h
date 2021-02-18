//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKGridUtils.h $
//  
//  Owner: Heath Lynn, (Bernd Paradies: generalized from BookUtils.h).
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
#ifndef __ICJKGRIDUTILS__
#define __ICJKGRIDUTILS__

#include "CJKGridID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "PMPoint.h"
#include "AttributeBossList.h"

class ICJKGridData;
class ICJKLayoutGridData;
class ICJKGridManager;
class IGraphicsPort;
class IPMFont;
class IStoryOptions;
class PMRect;
class UIDList;
class IDocument;


/** ICJKGridUtils is the interface for utilities related to the CJK grid.
*/
class ICJKGridUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICJKGRIDUTILS };

	enum WhichAttributes
		{
			kParaAttributes = 1,
			kCharAttributes = 2,
			kAllAttributes = 3
		};

	/**  
		Queries the proper interface for thePage. The master page's 
		instance is returned if a master is used.
		
		@param thePage IN An interface on the kPageBoss you want to query on.
		@param iid IN The desired PMIID or IID_ICJKLAYOUTGRIDDATA by default.
		@return A pointer to interface instance.
		@postcondition Caller must release returned interface.
	*/
	virtual IPMUnknown* QueryLayoutGrid(const IPMUnknown* thePage, PMIID iid = IID_ICJKLAYOUTGRIDDATA) = 0;

	/**  
		Queries the proper ICJKGridManager for thePage.
		The master page's instance is returned if
		a master is used and no column, margin, or grid 
		overrides have taken place.
	
		@param thePage IN An interface on the kPageBoss you want to query on.
		@return Pointer to ICJKGridManager or nil on failure.
		@postcondition Caller must release returned interface.
	*/
	virtual ICJKGridManager* QueryLayoutGridManager(const IPMUnknown *thePage) = 0;


	/**  
		Puts the path of a circle into the gPort
		
		@param gPort IN The IGraphicsPort you want to draw the circle into.
		@param bounds IN The rectangular bounds of the circle.
	*/
	virtual void DrawCirclePath(IGraphicsPort* gPort, const PMRect& bounds) = 0;


	/**  
		Moves newCord to the next closest grid boundary.
		
		@param newCord IN/OUT Coordinate you would like to move to the next closest grid boundary.
		@param colStart IN Coordinate of column start.
		@param colEnd IN Coordinate of column end.
		@param spacing IN Space between each grid boundary.
		@param onlyAdvance IN kTrue if newCord only advances and never moves back.
		@param extra IN Any extra space that will be added after newCord is aligned to the next grid boundary.
		@return  kTrue when newCord is moved.
	*/
	virtual bool16 MoveAcrossSingleColumn(PMReal& newCord, 
											  PMReal colStart, 
											  const PMReal& colEnd,
											  const PMReal& spacing, 
											  bool16 onlyAdvance,
											  const PMReal& extra) = 0;


	/**  
		Converts sourceUID from srcDB to destDB, creating it if it doesn't exist.
	
		@param sourceUID IN Source font UID.
		@param srcDB IN Source database.
		@param destDB IN Destination database.
		@return UID for font in destDB.
	*/
	virtual UID ConvertFontUID(UID sourceUID, IDataBase * srcDB, IDataBase * destDB) = 0;

	/**  
		@param str IN The string you want to measure.
		@param fontSize IN The font size.
		@param scaleX IN The x scale factor.
		@param scaleY IN The y scale factor.
		@return Height in width in PMPoint x/y.
	*/
	virtual PMPoint MeasureString(const PMString& str, const PMReal& fontSize, const PMReal& scaleX, const PMReal& scaleY) = 0;

	/**  
		@return default 13Q in points.
	*/
	virtual PMReal CJKGridGetQTextSize() = 0;
	

	/**  Returns whether or not a text frame contains a characer count
		@param obj IN Interface on text frame boss (kFrameItemBoss or kMultiColumnFrameBoss).
		@return kTrue if it is an active frame grid with a visible character count
	*/
	virtual bool16 TextFrameDrawsCJKCharCount(const IPMUnknown * obj) = 0;

	/**  Applies to cjkGridData based on the attributes passed in.
		@param attributeBossList IN Attributes that will be used to determine ICJKGridData.
		@param cjkGridData OUT The ICJKGridData you want filled out.
		@precondition attributeBossList should be complete.
	*/
	virtual void ApplyAttributesToGridData(const AttributeBossList &attributeBossList, ICJKGridData *cjkGridData, bool16 isVertical) = 0;

	/**  Applies auto leading at some percent that matches the line okuri of the grid.
		@param gridData IN The ICJKGridData to pull line okuri from.
		@param *attrBossList OUT The attributes we are applying to.
	*/
	virtual void ApplyGridLeadingToAttributes(const ICJKGridData* gridData, AttributeBossList *attrBossList, bool16 isVertical ) = 0;

	/**  Applies to attributeBossList based on ICJKGridData
		@param cjkGridData IN The ICJKGridData you want attributes for.
		@param attributeBossList OUT The list to apply to.
		@param isVertical IN Whether or not object containing attributes is of the vertical writing direction.
	*/
	virtual void ApplyGridDataToAttributes(const ICJKGridData* cjkGridData, AttributeBossList* attributeBossList , ICJKGridUtils::WhichAttributes whichAttributes = ICJKGridUtils::kAllAttributes) = 0;

	/**  Applies an objects grid data to its attribute list by callling kApplytoAttributeListCmdBoss 1 or more times.
		@param  itemList IN DESCRIPTION.
		@precondition itemList should contain UIDs for objects that support ITextAttributes and ICJKGridData
		@return ErrorCode of first command to fail or kSuccess.
	*/
	virtual ErrorCode ApplyGridDataToAttributeLists(const UIDList & itemList ) = 0;

	/**  Returns an IPMFont * for the character count adornment's font.  This will be KozGoStd-Regular if available,
		or the default system font.
		@return An IPMFont of the character count adornment's font.
		@postcondition Returned IPMFont must be released by the caller.
	*/
	virtual IPMFont * QueryCharacterCountFont() = 0;

	/**  Set up the command data for SetCJKGridDataCmd.
		@param namedGridUID IN The UID of named grid may be used in the command data.
		@param gridData IN The gridData for the selected page.
		@param itemList IN The items the command applies to.
		@param cmd IN The command which the command data attached to.
	*/
	virtual	void SetupSetCJKGridDataCmd(UID namedGridUID, ICJKGridData* gridData, UIDList & itemList, ICommand * cmd) = 0;

	/**
		Adjust the right bottom point of the newly created frame grid which holds the passed in story.
		@param parent IN the parent object where the frame is in.
		@param bVertical IN the direction of the frame.
		@param location IN the left top point of the frame.
		@param defaultEndPoint OUT the right bottom point of the frame.
		@param xUnits OUT x units for adjusting defaultEndPoint.X().
		@param yUnits OUT y units for adjusting defaultEndPoint.Y(). 
	*/
	virtual void AdjustFrameEndPoint(const UIDRef& parent, const bool16& bVertical, const PMPoint& location, PMPoint& defaultEndPoint, int32& xUnits, int32& yUnits) = 0;

	/**
		Calculate the CJK grid metric.
		@param parent IN the parent object where the frame is.
		@param pt IN the click point on the layout in PasteBoard coordinates
		@param bVertical IN the direction of the frame.
		@param lineOkuri OUT Okuri for line.
		@param charOkuri OUT Okuri for char.
		@param lineAki OUT x Aki for line.
		@param charAki OUT y Aki for char. 
	*/
	virtual void CalcCJKGridMetrics(const UIDRef& parent, const PBPMPoint& pt, const bool16& bVertical, PMReal& lineOkuri, PMReal& charOkuri, PMReal& lineAki, PMReal& charAki) = 0;

	/**
		Calculate the CJK grid metric.
		@param parent IN the parent object where the frame is.
		@param pt IN the click point on the layout in PasteBoard coordinates
		@param textSize OUT textSize for grid.
		@param charAki OUT x Aki for char. 
		@param lineAki OUT y Aki for line.
		@param hScale OUT x scale.
		@param vScale OUT y scale
	*/
	virtual void GetCJKGridMetrics(const UIDRef& parent,
									const PBPMPoint& pt,
									PMReal& textSize,
									PMReal& charAki,
									PMReal& lineAki,
									PMReal& hScale,
									PMReal& vScale) = 0;

};


#endif	// __ICJKGridUtils__
