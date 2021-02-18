//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDragDropSource.h $
//  
//  Owner: Dave Burnard
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
//  Interface definition for Drag and Drop sources
//  
//========================================================================================

#pragma once
#ifndef __IDragDropSource__
#define __IDragDropSource__

#include "DragDropConstants.h"
#include "DragDropID.h"

#include "IPMUnknown.h"
#include "CursorSpec.h"

class IDragDropController;
class IDragDropTarget;
class IEvent;
class ICommand;
class IDragItemIterator;
class ICommandSequence;
class IDataBase;

/** IDragDropSource interface, represents the source object that initiates a drag drop operation.
		Implementors should derive from either CDragDropSource or CDragDropSource_Extensible.

		@see IDragDropTarget
 */
class IDragDropSource : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAGDROPSOURCE };
		
	public:
		/** Called by Drag Drop framework prior to initiating a drag operation. 
		
			@param e IN event to be used to obtain the current mouse position
			@return whether or not a drag could be initiated from the mouse position in the event
		*/
		virtual bool16			WillDrag(IEvent* e) const = 0;
		
		/** Provide the cursor to be displayed during the drag based on the response from a target.
				Return DragDrop::kDefaultDragCursors to use the default platform cursors.
		
			@param targetResponse IN what action the target intends to perform (nothing, copy, move, link)
			@param isDragLocal IN is the drag taking place within the source object (source and target are equivalent)
			@return CursorSpec to display corresponding to target's intended action
		*/
		virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal ) const = 0;
		
		/** Provide the outline region to be dragged with the cursor as feedback during the drag operation.
				Can return constants DragDrop::kNoDragOutline or DragDrop::kDefaultDragOutline when appropriate -
				caller is responsible for releasing the returned region, if any.
				
			@return SysWireframe to be used as drag feedback (caller is responsible for deleting this object)
		*/
		virtual SysWireframe 			DoMakeDragOutlineRegion() const = 0;

		/** Add drag content for the current drag operation
		
			@param controller IN used to call IDragDropController::AddDragItem as necessary.
			@return whether or not the operation succeeded
		*/
		virtual bool16			DoAddDragContent(IDragDropController*) = 0;
		
		/** Create and process (or schedule) the commands needed to complete the drop operation. 
				Normally called on the drop target, this method is also called on sources when the original data needs to be deleted, as in a drag to the trash.
		
			@param controller IN drag drop controller for this operation
			@param commandType IN which operation to perform (sources will only receive kDrag to delete data)
			@return success or failure of the drop
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType) = 0;
			
		/** Return the database that contains the drag data offered by this source.
				Used to determine if a source and target belonging to different bosses actually view the same data.
				Can be used to determine if a drag operation should be a move vs. a copy, but not required.
		
			@return the affected database (usually returns the database of an IDocument, or nil)
		*/
		virtual IDataBase*	GetSourceDataBase() const = 0;
};

#endif
