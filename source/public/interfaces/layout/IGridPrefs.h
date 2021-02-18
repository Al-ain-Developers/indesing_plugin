//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGridPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __IGridPrefs__
#define __IGridPrefs__

#define kMinGridDivision		0.01
#define kMaxGridDivision		1000
#define kMinGridSubdivisions	1
#define kMaxGridSubdivisions	1000

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"

class IGridPrefs : public IPMUnknown
{
public:	
	////
	//// Grid Preferences
	////
	
	// Is Grid shown or hidden by default
	virtual void SetGridShown(const bool16 bShown) = 0;
	virtual bool16 GetGridShown() = 0;

	// Grid division
	virtual void SetGridDivision(const PMReal& division) = 0;
	virtual PMReal GetGridDivision() = 0;

	// Number of grid subdivisions
	virtual void SetGridSubdivisions(const int32& subdivisions) = 0;
	virtual int32 GetGridSubdivisions() = 0;

	// UI Color index for grid
	virtual void SetGridColor(const UID uiColorUID) = 0;
	virtual UIDRef GetGridColor() = 0;
	
	// Are Grids in front or back
	virtual void SetGridsInBack(const bool16 bShown) = 0;
	virtual bool16 GetGridsInBack() = 0;

	// Horizontal grid division
	virtual void SetGridHorizontalDivision(const PMReal& division) = 0;
	virtual PMReal GetGridHorizontalDivision() = 0;

	// Number of grid subdivisions
	virtual void SetGridHorizontalSubdivisions(const int32& subdivisions) = 0;
	virtual int32 GetGridHorizontalSubdivisions() = 0;

	// Vertical grid division
	virtual void SetGridVerticalDivision(const PMReal& division) = 0;
	virtual PMReal GetGridVerticalDivision() = 0;

	// Number of vertical grid subdivisions
	virtual void SetGridVerticalSubdivisions(const int32& subdivisions) = 0;
	virtual int32 GetGridVerticalSubdivisions() = 0;

	/** Internal  method used to convert grid show setting. Please do not call!
	*/
	virtual bool16 GetGridShown_DURING_CONVERSION_ONLY() = 0;

	/** Internal  method used to convert grids in back setting. Please do not call!
	*/
	virtual bool16 GetGridsInBack_DURING_CONVERSION_ONLY() = 0;
	
	/** Internal  method used to convert grid color setting. Please do not call!
	*/
	virtual int32 GetGridColorIndex_DURING_CONVERSION_ONLY() = 0;

};

#endif
#endif
