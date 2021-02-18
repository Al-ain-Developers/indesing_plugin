//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ISelectCellRangeCmdData.h $
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
//========================================================================================

#pragma once
#ifndef __ISelectCellRangeCmdData__
#define __ISelectCellRangeCmdData__

#include "IPMUnknown.h"
#include "HelperInterface.h"
#include "TablesUIID.h"
#include "TableTypes.h"
#include "ITableSelectionSuite.h"

/** 
	The cell range selected at the time the command was fired
	@ingroup tables_cmd
*/
class ISelectCellRangeCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISELECTCELLRANGECMDDATA };
	
	/**
		Sets the model we are acting on
		@param	ref	
	*/
	virtual void SetModel(UIDRef ref) = 0;
	/**
		Gets the model we are acting on
		@return	UIDRef	
	*/
	virtual const UIDRef GetModel(void) const = 0;

	/**
		Sets the cell area we are acting on
		@param	range	
	*/
	virtual void SetRange(GridArea range) = 0;
	/**
		Gets the cell area we are acting on
		@return	GridArea	
	*/
	virtual const GridArea GetRange(void) const = 0;

	/**
		Sets the whether to redraw the selection
		@param	bool16	
	*/
	virtual void SetRedraw(bool16 redraw) = 0;
	/**
		Gets whether to redraw the selection
		@return	bool16	
	*/
	virtual const bool16 GetRedraw(void) const = 0;

	/**
		Sets whether to auto scroll the selection
		@param	bool16	
	*/
	virtual void SetAutoScroll(bool16 redraw) = 0;
	/**
		Gets whether to auto scroll the selection
		@return	bool16	
	*/
	virtual const bool16 GetAutoScroll(void) const = 0;

	/**
		Sets the action we are doing to make the second @see ITableSelectionSuite::SelectAction
		@param	selectAction	
	*/
	virtual void SetSelectAction(ITableSelectionSuite::SelectAction selectAction) = 0;
	/**
		Gets the action we are doing to make the second @see ITableSelectionSuite::SelectAction
		@return	ITableSelectionSuite::SelectAction	
	*/
	virtual const ITableSelectionSuite::SelectAction GetSelectAction(void) const = 0;
};

#endif
