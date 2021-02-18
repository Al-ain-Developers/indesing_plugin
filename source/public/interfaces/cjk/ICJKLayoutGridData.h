//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKLayoutGridData.h $
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
//  Purpose: Drawing data like color, fill, etc.
//  
//========================================================================================

#pragma once
#ifndef __ICJKLayoutGridData__
#define __ICJKLayoutGridData__

#include "IPMUnknown.h"
#include "IColumns.h"

#include "K2Vector.h"
#include "CJKGridID.h"

class PMRect;

typedef K2Vector<int16> Int16List;

/** ICJKLayoutGridData is the interface for grid related data that is specific to the layout grid.
*/
class ICJKLayoutGridData : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_ICJKLAYOUTGRIDDATA };

	//---------------------------------------
	//	enumerations
	//---------------------------------------

	enum GridStartingPoint 
	{	
		kTopOutside, 
		kTopInside, 
		kBottomOutside, 
		kBottomInside,
		kCenterVertical, 
		kCenterHorizontal, 
		kCenter 
	};

	//---------------------------------------
	//	Get and Set Methods
	//---------------------------------------

	// Grid starting point - which corner the grid will flow from 
	
	/**  SetGridStartingPoint
		@param choice IN The new grid starting point.
	*/
	virtual void SetGridStartingPoint(GridStartingPoint choice) = 0;
	
	/**  GetGridStartingPoint
		@return the grid starting point
	*/
	virtual GridStartingPoint GetGridStartingPoint() = 0;

	/**  SetUseMaster
		@param useMaster IN The new value for whether or not to use the master.
	*/
	virtual void SetUseMaster(const bool16 useMaster) = 0;
	
	/**  GetUseMaster
		@return Whether or not this grid uses the master pages grid
	*/
	virtual bool16 GetUseMaster() = 0;

	/**  CopyFrom copies from the source to this ICJKLayoutGridData.
		@param source IN The ICJKLayoutGridData to copy.
		@param doDirty IN Whether or not to dirty this ICJKLayoutGridData on copying.
	*/
	virtual void CopyFrom(ICJKLayoutGridData * source, bool16 doDirty = kTrue) = 0;

};


#endif
