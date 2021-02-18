//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageColumnsCmdData.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPageColumnsCmdData__
#define __IPageColumnsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "PMReal.h"
#include "IColumns.h"

class IDataBase;

/** Command data interface for set columns command (kSetPageColumnsCmdBoss).

	@ingroup layout_column
	@see kSetPageColumnsCmdBoss 
	@see IColumns
	@see kPageBoss

*/
class IPageColumnsCmdData : public IPMUnknown
{
public:
	/** Set page columns data.
		@param columns dimensions of the new Columns
		@param direction column direction
		@param valid new column valid setting
		@param custom new column custom setting
	*/
	virtual void SetPageColumnsCmdData_(	const	PMRealList&	columns,		/* dimensions of the new Columns */
						const	IColumns::ColumnOrientation direction,				/* column direction */
						const	bool16 valid /* = kTrue */,			/* the new column valid setting */
						const	bool16 custom /* = kFalse*/) = 0;	/* the new column custom setting */
	virtual const PMRealList& GetColumns() const = 0;
	virtual IColumns::ColumnOrientation GetColumnOrientation_3() const = 0;
	virtual bool16 GetValid() const = 0;
	virtual bool16 GetCustom() const = 0;
};




#endif // __IPageColumnsCmdData__
