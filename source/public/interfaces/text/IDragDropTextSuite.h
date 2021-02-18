//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDragDropTextSuite.h $
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

#ifndef __IDRAGDROPTEXTSUITE__
#define __IDRAGDROPTEXTSUITE__

#include "IPMUnknown.h"
#include "ICursorMgr.h"
#include "IDragDropSource.h"
#include "TextEditorID.h"
#include "RangeData.h"

class IDataExchangeHandler;
class IControlView;
class UIDRef;
class RangeData;

/**
	This interface abstract interaction between DnD text and selection architecture
*/
class IDragDropTextSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDRAGDROPTEXTSUITE };

	/**	Description: Can start text drag based on current selection?
		@param view pointer to the control view under the mouse
		@param mousePt location of current mouse position
		@param hitObj an IPMUnknown pointer from a frame from hittesting at the mousePt. May be nil.
		@return bool16 kTrue / kFalse if drag can be started.
	 */
	virtual bool16 CanDrag(IControlView* view, const SysPoint mousePt, const IPMUnknown* hitObj) = 0;

	/**	Description: Does the indicated text range overlap the text selection (in the destination)?
		@param sourceStoryUIDRef Reference to the source story (may be kInvalidUIDRef)
		@param destStoryUIDRef Reference to the story to drop into
		@param destRange text range at hit location (length of 1)
		@param type an enum of type DragDrop::eCommandType. kDragMove for moving text, otherwise use kDrop to copy.
		@return bool16 kTrue if selection contains text range, kFalse otherwise.
	 */
	virtual bool16 TextRangeOverlapsSelection(UIDRef& sourceStoryUIDRef, UIDRef& destStoryUIDRef, RangeData& destRange, DragDrop::eCommandType type) = 0;

	/**	Description: Prepare text data source for drag and drop operation
		@param handler pointer to IDataExchangeHandler
		@return ErrorCode the result of adding source data to the exchange handler. An alert will be displayed if kSuccess is not returned.
	 */
	virtual ErrorCode PrepareDragDataSource(IDataExchangeHandler* handler, IDragDropSource* source) = 0;
};

#endif // __IDRAGDROPSOURCESUITE__