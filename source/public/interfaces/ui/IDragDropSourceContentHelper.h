//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDragDropSourceContentHelper.h $
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
//  Interface definition for Drag and Drop source extensibility
//  
//========================================================================================

#pragma once
#ifndef __IDragDropSourceContentHelper__
#define __IDragDropSourceContentHelper__

#include "DragDropConstants.h"

#include "IDragDropSource.h"

/** The IDragDropSourceContentHelper interface provides extensibility for drag drop sources.
		Drag source extensibility requires the source be derived from CDragDropSource_Extensible.  
		Create a new boss with an IDragDropSourceContentHelper implementation combined with a IK2ServiceProvider 
		implementation that corresponds to the service ID defined by the extensible drag source.
		
		When the framework asks an extensible drag source if it is willing to start a drag, the source then asks 
		each of it's content helpers if they could start a drag from the current mouse location. 
		One helper is chosen based on willingness to begin a drag, and in the case of multiple helpers, 
		prioritized by helper type. The extensible source then forwards the subsequent method calls that occur 
		during the drag to the chosen helper.

		@see IDragDropSource, IK2ServiceProvider, CDragDropSource_Extensible
 */
class IDragDropSourceContentHelper : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAGDROPSOURCECONTENTHELPER };

		/** Return the type or priority of the helper.
				This is used to resolve conflicts that can arise when more than one source content helper is 
				capable of starting a drag drop operation. The presence of multiple helpers is not a conflict,
				a conflict would arise when one helper wants to replace or augment what another helper already does.
		
			@return helper type appropriate for this helper. Use DragDrop::kDefaultHelper by default.
		*/
		virtual DragDrop::eHelperType	GetHelperType() const = 0;

		/** Could this helper initiate a drag from the given mouse position?
		
			@param source IN the drag drop source this helper is assisting
			@param e IN event containing current mouse position and modifiers
			@return kTrue if a drag could be started.
		*/
		virtual bool16			CouldStartDrag(IDragDropSource*, IEvent* e) const = 0;
		
		/** Provide the cursor to be displayed during the drag based on the response from a target.
				Return DragDrop::kDefaultDragCursors to use the default platform cursors.
		
			@param source IN the drag drop source this helper is assisting
			@param targetResponse IN what action the target intends to perform (nothing, copy, move, link)
			@param isDragLocal IN is the drag taking place within the source object (source and target are equivalent)
			@return CursorSpec to display corresponding to target's intended action
		*/
		virtual CursorSpec 	GetDragCursor(IDragDropSource*, DragDrop::eTargetResponse, bool16 isDragLocal ) const = 0;
		
		/** Provide the outline region to be dragged with the cursor as feedback during the drag operation.
				Can return constants DragDrop::kNoDragOutline or DragDrop::kDefaultDragOutline when appropriate -
				caller is responsible for releasing the returned region, if any.
				
			@param source IN the drag drop source this helper is assisting
			@return SysWireframe to be used as drag feedback (caller is responsible for deleting this object)
		*/
		virtual SysWireframe 			CreateDragOutlineRegion(IDragDropSource*) const = 0;

		/** Add drag content for the current drag operation.
		
			@param source IN the drag drop source this helper is assisting
			@param controller IN used to call IDragDropController::AddDragItem as necessary.
			@return kTrue if the operation succeeded
		*/
		virtual bool16			DoAddDragContent(IDragDropSource*, IDragDropController*) = 0;
		
		/** Create and process (or schedule) the commands needed to complete the drop operation. 
				Normally called on the drop target, this method is also called on sources when the original data needs to be deleted, as in a drag to the trash.
		
			@param source IN the drag drop source this helper is assisting
			@param controller IN drag drop controller for this operation
			@param commandType IN which operation to perform (sources will only receive kDrag to delete data)
			@return success or failure of the drop
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropSource*, IDragDropController*, DragDrop::eCommandType) = 0;
};

#endif
