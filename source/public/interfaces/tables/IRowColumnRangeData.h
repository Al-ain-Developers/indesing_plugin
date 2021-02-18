//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IRowColumnRangeData.h $
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
//  Data interface to specify a row or column range.
//  
//========================================================================================

#pragma once
#ifndef __IRowColumnRangeData__
#define __IRowColumnRangeData__

#include "IPMUnknown.h"
#include "TablesID.h"

/** 
	The row/column range selected at the time the command was fired
	@ingroup tables_cmd
*/
class IRowColumnRangeData : public IPMUnknown
{
public:
	
	enum { kDefaultIID = IID_IROWCOLUMNRANGEDATA };
	
	/**
		Sets the start and count	Range(start, start + count)
		@param	rowOrColumnPosition	(start)
		@param	count
	*/
	virtual void	Set(int32 rowOrColumnPosition, int32 count) = 0;
	/**
		Returns the start position	Range(start, start + count)
		@return	int32
	*/
	virtual int32	GetPosition(void) const = 0;
	/**
		Returns the count			Range(start, start + count)
		@return	int32
	*/
	virtual int32	GetCount(void) const = 0;
};

#endif // __IRowColumnRangeData__
