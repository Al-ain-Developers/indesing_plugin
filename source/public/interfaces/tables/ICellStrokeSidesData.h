//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellStrokeSidesData.h $
//  
//  Owner: Danielle Bessette
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
//  Purpsse: Stores the sides of the cell selection that are selected
//  Set by the stroke panel ui for tables
//  
//========================================================================================

#pragma once
#ifndef __ICellStrokeSidesData__
#define __ICellStrokeSidesData__

#include "IPMUnknown.h"
#include "TablesUIID.h"
#include "TableTypes.h"
#include "IControlView.h"
#include "ICellFocus.h"
#include "ITableModel.h"

class ICellFocus;
class ITableModel;

/** 
 * 	UI information about the selected sides of a cell (or group of cells)
 *  	@ingroup table_ui
 */
 class ICellStrokeSidesData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICELLSTROKESIDESDATA };

	/**
		Returns the current selected sides in the stroke panel
		@return	Tables::ESelectionSides
	*/
	virtual Tables::ESelectionSides Get() const = 0;

	/**
		Takes a boolean when to notify of the change because for initialization we don't want
		to notify that this has changed
		@param	sides		The sides that are currently selected in the stroke panel
		@param	notifyOfChange	notify that this changed
	*/
	virtual void Set(Tables::ESelectionSides sides, bool16 notifyOfChange = kTrue) = 0;

	/**
		Updates this value according to what sides are selected by the widget in the stroke panel
	*/
	virtual void Update() = 0;

};


#endif
