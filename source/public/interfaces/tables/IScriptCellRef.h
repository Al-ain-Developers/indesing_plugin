//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IScriptCellRef.h $
//  
//  Owner: Peter Boctor
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
//  This interface describes a Table area. It describes the range
//  and the table selected. The interface is used in scripting of
//  cells, rows and columns.
//  
//========================================================================================

#pragma once
#ifndef __IScriptCellRef__
#define __IScriptCellRef__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

class ITableModel;
class UIDRef;

class IScriptCellRef : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ISCRIPTCELLREF };

		/**	Set the table within which this cell object exists */
		virtual void				SetTableModel(const ITableModel* model, bool16 registerFocus = kTrue) = 0;

		/** Query the table within which this cell object exists */
		virtual ITableModel*		QueryModel() const = 0;
		/** Get the table within which this cell object exists */
		virtual UIDRef				GetModel() const = 0;

		/** Set the range of cells which this cell object represents */
		virtual ErrorCode			SetRange(const GridArea &area) = 0;
		/** Get the range of cells which this cell object represents */
		virtual ErrorCode			GetRange(GridArea &area) const = 0;		
};

#endif //__IScriptCellRef__
