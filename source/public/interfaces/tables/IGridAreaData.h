//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IGridAreaData.h $
//  
//  Owner: Joe Shankar
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
//  Purpose: Data interface for a GridArea.
//  
//========================================================================================

#pragma once
#ifndef __IGridAreaData__
#define __IGridAreaData__

#include "IPMUnknown.h"
#include "TablesID.h"

//----- Forward declarations.
class GridArea;

/**
	Carries a grid area.
*/
class IGridAreaData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRIDAREADATA };

	/**
		Set the data being carried.
		@param area grid area data to be carried.
	*/
	virtual void	 Set(const GridArea& area) = 0;

	/**
		Get the data being carried.
		@return grid area data being carried.
	*/
	virtual GridArea Get() const = 0;
};




#endif //__IGridAreaData__
