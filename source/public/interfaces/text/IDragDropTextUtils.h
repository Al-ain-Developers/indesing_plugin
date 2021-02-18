//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDragDropTextUtils.h $
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
//  Purpose:
//  Utilities for use for dealing with drag and drop of text.
//  
//========================================================================================

#pragma once
#ifndef __IDragDropTextUtils__
#define __IDragDropTextUtils__

#include "Utils.h"
#include "TextEditorID.h"
#include "DragDropConstants.h"

class IDataExchangeHandler;
class IDragDropController;
class IEvent;
class UIDRef;
class RangeData;
class IDragDropSource;
class IParcel;
class ILayoutControlData;

/** Utilities for use for dealing with drag and drop of text.
 */
class IDragDropTextUtils : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IDRAGDROPTEXTUTILS};

	/**	Description: Try to start up a text drag operation with the given view, drag drop source, and event.
		@param view IN pointer to the control view under the mouse
		@param dragSource IN the drag source to ask if it WillDrag
		@param theEvent IN the event that initiated this query.
		@return bool16 kTrue / kFalse. If returns kTrue, need to return true from tracker or event handler. Drag has been started. Returns kFalse if drag has not be started up.
	 */
	virtual bool16 StartTextDrag(IControlView* view, IDragDropSource* dragSource, IEvent* theEvent) = 0;

	/**	Description: Utility method that encapsulates using the target object (hitObj) and uses its
		IDragDropTextHelper interface to return a parcel, story ref, and text range at the hit moust point.
		@see QueryParcelFromHitObject
		@see QueryStoryThreadFromHitObject
		@see HitTestStoryThread
		@see AdjustRangeFromHitTest
		@param view IN pointer to the control view under the mouse
		@param mousePt IN location of current mouse position
		@param hitObj IN an IPMUnknown pointer from a frame from hittesting at the mousePt. May be nil.
		@param previousParcel IN an IParcel interface from a possible previous hit. May be nil, and will be nil initially.
		@param storyUIDRef OUT Reference to the story containing the returned RangeData. kInvalidUIDRef if no hit.
		@param range OUT The hit range (length of 0). This is a model range.
		@param hitIndex OUT the model text index that was hit, may be nil.
		@param adjustedHitIndex OUT the adjusted model text index (rounded). May be nil.
		@return IParcel Return a parcel at the passed in point. May return nil and still be considered a hit (so storyUIDRef and range would still be filled in for return). Defaults to kTrue.
	 */
	virtual IParcel* QueryTextParcelAtPoint(IControlView* view, const SysPoint mousePt, const IPMUnknown* hitObj, const IParcel* previousParcel, UIDRef& storyUIDRef, RangeData& range, PMReal* hitIndex = nil, PMReal* adjustedHitIndex = nil) = 0;

	/**	Description: Use the range data (length of 0) to draw a caret at the story position
		in order to give user feedback about drop location.
		@see QueryTextParcelAtPoint.
		@param view IN pointer to the control view under the mouse
		@param storyUIDRef IN Reference to the story containing the RangeData
		@param range IN text range at drop location (length of 0)
		@param flushDrawing IN whether to force flush the drawing
	 */
	virtual void DrawCaretAtDropLocation(IControlView* view, UIDRef& storyUIDRef, RangeData& range, bool16 flushDrawing = kTrue) = 0;

	/**	Description: Process commands to do text drag and drop.
		@param view IN the control view for the drop (may be nil, used to bring window to front)
		@param controller IN the drag and drop controller
		@param storyUIDRef IN Reference to the story to drop into (the destination)
		@param range IN text range at hit location (length of 0) (the destination)
		@param type IN an enum of type DragDrop::eCommandType. kDragMove for moving text, otherwise use kDrop to copy.
		@param ignoreAttributes IN Ignore the attributes on drop, default to kFalse
		@return ErrorCode the result of processing the drag and drop command operation.
	 */
	virtual ErrorCode ProcessDragDropTextCommand(IControlView* view, IDragDropController* controller, const UIDRef& storyUIDRef, RangeData& range, DragDrop::eCommandType type,bool16 ignoreAttributes = kFalse) = 0;

	/**	Description: Check to see if we can create a text frame at this location (checks for locked layers).
		@param view IN What view to drop in.
		@param controller IN The drag and drop controller
		@param dropPoint OUT The dropped point from the controller
		@param parent OUT Where in the hierarchy to put the text frame (typically a spread layer).
		@return kSuccess if you can create a text frame in this view, an error code otherwise
	 */
	virtual	ErrorCode PrepareForTextFrameDrop(IControlView* view, IDragDropController* controller, PMPoint& dropPoint, UIDRef& parent) = 0;

	/**	Description: Process command to create a new text frame or frame grid based on the passed in storyUIDRef parameter.
		@param location Where the text frame should be created, in pasteboard coordinates.
		@param parent Where in the hierarchy to put the text frame (typically a spread layer)
		@param storyUIDRef The source story uid ref (may be kInvalidUIDRef)
		@param createdFrame OUT parameter. The created text frame or frame grid based on the passed in storyUIDRef parameter) 
		                    and it could be UIDRef(nil, kInvalidUID) if we fail to create. 
		@return ICommand The command to create the text frame (kCreateMultiColumnItemCmdBoss).
	 */
	virtual ErrorCode MakeFrame(const PBPMPoint& location, const UIDRef& parent, const UIDRef& storyUIDRef, UIDRef& createdFrame) = 0;

	/**	Description: Signal all drag drop text responders that a drag text event has just occurred. 
		@param id, a service id for what signal is being sent. Must be one of:
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
		@param sourceRange IN/OUT the source text range that is being dragged. May be modified by responder, and may even have zero length after the drop.
		@param destinationStoryRef IN the destination story that is being dropped. Will be kInvalidUIDRef for kBeforeDragTextSignalResponderService signal.
		@param destinationRange IN/OUT the destination range for the caret drop location (length of zero) that is 
				being dropped. Will be RangeData(0,0,RangeData::kLeanForward)) for kBeforeDragTextSignalResponderService signal.
				May be modified by responder.
		@param droppedRange IN/OUT the dropped range for the drag and drop operation.
				Will be the length of the sourceRange. This range is used to select the text after the drop.
				May be modified by responder.
		@param handler IN the data exchange handler used for the text drag drop operation. Gives responders a place to access stored data.
		@return error code returned by the responders. First error will terminate the rest of the responders, abort the drag/drop operation. 
			Note: An alert will be displayed (if there is a string corresponding to the error code).
	 */
	virtual ErrorCode SendDragDropTextSignal(ServiceID id,
					IControlView* sourceView,
					IControlView* destinationView,
					const UIDRef& sourceStoryRef, 
					RangeData& sourceRange,
					const UIDRef& destinationStoryRef, 
					RangeData& destinationRange,
					RangeData& droppedRange,
					DragDrop::eCommandType type,
					IDataExchangeHandler* handler) = 0;

	/** Description: Create a new-text-frame command, to hold raw text dragged onto a layout.
		@param layoutData IN Pointer to ILayoutControlData for layout view.
		@param texthandler IN IDataExchangeHandler for the drop.
		@param ignoreAttributes IN Ignore the attributes of the source.
		@return ICommand pointer for the command.
	*/
	virtual ICommand* MakeNewTextFrameCmdForDrop(ILayoutControlData* layoutData, IDataExchangeHandler* texthandler, const bool16 ignoreAttributes ) = 0;

};
	
#endif // __IDragDropTextUtils__
