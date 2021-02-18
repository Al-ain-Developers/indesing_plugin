//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightTableCellInfo.h $
//  
//  Owner: Matt Phillips
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
#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "TableTypes.h"

/**	This interface provides information about a particular table cell, table frame cell,
	or table cell area found in the document. 
*/

class IPreflightTableCellInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTTABLECELLINFO };

	/** Get the UIDRef of the table model that "owns" the cell.

		@return UIDRef of the table model that "owns" the cell.
	*/
	virtual UIDRef GetTableModelRef() const = 0;

	/** Get the area in the table model this cell or cell range is. 
		
		To determine whether this is a single cell, as opposed to a range, use 
		GetGridArea().GetSpan().IsUnitSpan(). Note that if you know this is a TableCell 
		or TableFrameCell, you're guaranteed that it is a single cell, so this advice 
		only applies if you're handed one of these interfaces without context.

		If you know it's a single cell then you can get the address from 
		GetGridArea().GetTopLeft().

		@return The area of the cell.
	*/
	virtual GridArea GetGridArea() const = 0;

	/**	Get the UIDRef of the table frame, ie the owned item in a parcel that contains the
		cell. This will only return a valid UIDRef if this is a table frame cell (a table cell
		is a true UID based data structure; a table frame cell is the composed, non-UID-based
		cell-on-page).

		@return The UIDRef of the table frame; or an invalid UIDRef if this is a table cell.
	*/
	virtual UIDRef GetTableFrameRef() const = 0;

	/** Initialize. Internal use only.
	*/
	virtual void Initialize() = 0;
};

