//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDragDropSourceSuite.h $
//  
//  Owner: Michael Martz
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _IDragDropSourceSuite_
#define _IDragDropSourceSuite_

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IDataExchangeHandler;

/**
	This interface abstract interaction between DnD source and selection architecture
*/
class IDragDropSourceSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDRAGDROPSOURCESUITE };

	/**	Description: Can start drag based on current selection?
		@param none
		@return bool16 kTrue / kFalse
	 */
	virtual bool16 CanDrag() const = 0;

	/**	Description: Prepare data source for drag and drop operation
		@param handler pointer to IDataExchangeHandler
		@param dragOutline the outline shown on screen during drag 
		@return ErrorCode
	 */
	virtual ErrorCode PrepareDragDataSource(IDataExchangeHandler * handler, PMRect& dragOutline) = 0;
};

#endif // _IDragDropSourceSuite_