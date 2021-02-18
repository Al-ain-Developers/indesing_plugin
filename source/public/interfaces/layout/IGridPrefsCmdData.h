//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGridPrefsCmdData.h $
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
//  
//  Data interface for Grid prefs commands.
//  includes : 	Grids drawn in front or back, shown or hidden and 
//  intervals between gridlines.
//  
//========================================================================================

#pragma once
#ifndef __IGridPrefsCmdData__
#define __IGridPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMRect.h"

class IDataBase;

class IGridPrefsCmdData : public IPMUnknown
{
public:
	virtual void Set(	const	UIDRef&	doc, 			/* which document to affect */
						const	bool16	shown,		 	/* Grids shown or hidden */
						const	PMReal&	division,		/* Interval between main gridlines, -1 to leave unchanged */
						const	int32&	subdivisions,   /* Number of subdivisions, -1 to leave unchanged */
						const   int32&  colorIndex = -1) = 0;
	virtual const UIDRef& GetDocument() const = 0;
	virtual const bool16 GetGridShown() const = 0;
	virtual const PMReal& GetGridDivision() const = 0;
	virtual const int32& GetGridSubdivisions() const = 0;
	virtual const int32& GetGridColorIndex() const = 0;
	
	virtual const void SetGridsInBack(bool16 bInBack) = 0;
	virtual const bool16 GetGridsInBack() const = 0;

	// Value of -1 will leave unchanged.
	virtual void SetGridHorizontalDivision(const PMReal& horizontalDivision) = 0;
	virtual void SetGridVerticalDivision(const PMReal& verticalDivision) = 0;
	virtual const PMReal& GetGridHorizontalDivision() = 0;
	virtual const PMReal& GetGridVerticalDivision() = 0;

	// Value of -1 will leave unchanged.
	virtual void SetGridHorizontalSubdivisions(const int32& horizontalSubdivisions) = 0;
	virtual void SetGridVerticalSubdivisions(const int32& verticalSubdivisions) = 0;
	virtual const int32& GetGridHorizontalSubdivisions() = 0;
	virtual const int32& GetGridVerticalSubdivisions() = 0;
};

#endif // __IGridPrefsCmdData__
