//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDragDropTextSignalData.h $
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
//  
//  Purpose:	Data sent with the DragDropText signal
//  
//========================================================================================

#pragma once
#ifndef __IDRAGDROPTEXTSIGNALDATA__
#define __IDRAGDROPTEXTSIGNALDATA__

#include "IPMUnknown.h"
#include "TextEditorID.h"
#include "DragDropConstants.h"

class IControlView;
class IDataExchangeHandler;
class RangeData;
class UIDRef;


/** Signal data used during kBeforeDragTextSignalResponderService, kBeforeDropTextSignalResponderService, and kAfterDropTextSignalResponderService.
 */
class IDragDropTextSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDRAGDROPTEXTSIGNALDATA };
	
	/**	Description: Set method that must be called before one of these signals: 
		kBeforeDragTextSignalResponderService - Just before we add text drag content to drag controller. Responder
		may want to adjust source range (e.g. a partially selected hyperlink). Responder may set global error code to
		display an alert.
		kBeforeDropTextSignalResponderService - Just before we create a command to do the drag/drop operation. 
		Responder may set global error code (e.g. some kind of illegal drop that will display an error alert). 
		kAfterDropTextSignalResponderService - Just after the drag/drop command has executed. 
		Responder may want to do extra adjustment (e.g. smart cut/paste to insert/delete extra spaces)
		@param sourceView IN pointer to the control view for the source for drag/drop operation.
		@param destinationView IN pointer to the control view for the destination for drag/drop operation. 
		May be same as source. May be nil for kBeforeDropTextSignalResponderService signal.
		@param sourceStoryRef IN the source story that is being dragged.
		@param sourceRange IN/OUT the source text range that is being dragged. May be modified by responder.
		@param destinationStoryRef IN the destination story that is being dropped. Will be kInvalidUIDRef for kBeforeDragTextSignalResponderService signal.
		@param destinationRange IN/OUT the destination range for the caret drop location (length of zero) that is 
				being dropped. Will be RangeData(0,0,RangeData::kLeanForward)) for kBeforeDragTextSignalResponderService signal.
				May be modified by responder.
		@param droppedRange IN/OUT the dropped range for the drag and drop operation.
				Will be the length of the sourceRange. This range is used to select the text after the drop.
				May be modified by responder.
		@param type IN what kind of drag we are doing. kDragMove for moving text, otherwise use kDrop to copy.
		@param handler IN the data exchange handler used for the text drag drop operation. Gives responders a place to access stored data.
	 */
	virtual void Set(IControlView* sourceView,
					 IControlView* destinationView,
					 const UIDRef& sourceStoryRef, 
					 RangeData& sourceRange,
					 const UIDRef& destinationStoryRef, 
					 RangeData& destinationRange,
					 RangeData& droppedRange,
					 DragDrop::eCommandType type,
					 IDataExchangeHandler* handler) = 0;

	/**	Description: Return the source control view for the drop/drop operation.
		@return IControlView the source control view.
	 */
	virtual IControlView* GetSourceView() = 0;

	/**	Description: Return the destination control view for the drop/drop operation.
		@return IControlView the destination control view. May be nil.
	 */
	virtual IControlView* GetDestinationView() = 0;
	
	/**	Description: Return the source story reference for the drop/drop operation.
		@return the source story uid ref.
	 */
	virtual const UIDRef& GetSourceStoryRef() = 0;

	/**	Description: Return the source range within the source story ref for the drop/drop operation.
		@return the source range data.
	 */
	virtual RangeData& GetSourceRange() = 0;
	
	/**	Description: Sets the source range for the drop/drop operation.
		@param the new source range data.
	 */
	virtual void SetSourceRange(RangeData& range) = 0;

	/**	Description: Return the detination story reference for the drop/drop operation.
		@return the destination story uid ref (may be kInvalidUIDRef).
	 */
	virtual const UIDRef& GetDestinationStoryRef() = 0;

	/**	Description: Return the destination range within the destination story ref for the drop/drop operation.
		@return the destination range data (will have length of zero)
	 */
	virtual RangeData& GetDestinationRange() = 0;

	/**	Description: Sets the destination range for the drop/drop operation.
		@param the new destination range data.
	 */
	virtual void SetDestinationRange(RangeData& range) = 0;

	/**	Description: Return the dropped range within the destination story ref for the drop/drop operation.
		@return the dropped range data (will have length of source range)
	 */
	virtual RangeData& GetDroppedRange() = 0;

	/**	Description: Sets the dropped range for the drop/drop operation.
		@param the new dropped range data.
	 */
	virtual void SetDroppedRange(RangeData& range) = 0;

	/**	Description: Return what kind of drag we are doing.
		@return an enum of type DragDrop::eCommandType. kDragMove for moving text, otherwise use kDrop to copy.
	 */
	virtual DragDrop::eCommandType GetDragType() = 0;

	/**	Description: Get data exchange handler used for the text drag drop operation.
		@return the data exchange handler.
	 */
	virtual IDataExchangeHandler* GetDataExchangeHandler() = 0;
};

#endif // __IDRAGDROPTEXTSIGNALDATA__

