//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IColumnPrefsCmdData.h $
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
#ifndef __IColumnPrefsCmdData__
#define __IColumnPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMReal.h"
#include "IColumns.h"

class IDataBase;

/** Data interface for Column prefs commands.
	Includes : 	Number of columns and gutter
	@see kSetColumnPrefsCmdBoss 
	@see IColumn
	@ingroup layout_column
*/
class IColumnPrefsCmdData : public IPMUnknown
{
public:
	/**
		Sets column preference data.
		@param doc which document to affect
		@param numColumns margin rect value
		@param gutter gutter value
		@param direction column direction
		@param colorIndex column color
		@param locked whether locked or not for user drag, -1 to leave unchanged
	*/
	virtual void SetColumnPrefsCmdData(	const	UIDRef&	doc, 			/* which document to affect */
						int32 numColumns,	 	/* margin rect value */
						PMReal gutter,			/* gutter value */
						IColumns::ColumnOrientation direction, 		/* column direction */
						int32 colorIndex = -1,	/* column color */
						bool16 locked = -1) = 0;/* locked or not for user drag, -1 to leave unchanged. */
	virtual UIDRef GetDocument_() const = 0;
	virtual int32 GetNumColumns_() const = 0;
	virtual PMReal GetGutter_() const = 0;
	virtual IColumns::ColumnOrientation GetColumnOrientation_1() const = 0;
	virtual int32 GetColorIndex_() const = 0;
	virtual bool16 GetLocked_() const = 0;
};


#endif // __IColumnPrefsCmdData__
