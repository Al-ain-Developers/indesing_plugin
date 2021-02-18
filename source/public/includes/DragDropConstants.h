//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DragDropConstants.h $
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
//  Constants and Simple Classes used in the Drag and Drop framework
//  
//========================================================================================

#pragma once
#ifndef __DragDropConstants__
#define __DragDropConstants__

#include "PMFlavorTypes.h"

#pragma export on

/**
		Class/Container used to scope constants and enums specific to generic DataExchange operations.
		(should be a namespace)
		
		@see DragDrop
 */
class DataExchange
{
	public:
		/** Types of DataExchangeHandler flavor helpers:
				used to resolve situations where more than one helper is capable of handling an internalize/externalize operation.
				
				@see IDataExchHandlerFlavorHelper::GetHelperType
		*/
		enum eHelperType {
			/** behavior that ships with InDesign (lowest priority) */
			kDefaultHelper = 0,
			/** behavior added to what ships in InDesign (takes precedence over default behavior) */
			kAddonHelper = 1,
			/** behavior that overrides all other helpers (highest priority - please use sparingly) */
			kOverrideHelper = 2,
			/** special override helper that is also called to examine/modify flavors in an item to be internalized
					To Do: this functionality should be available to Default and Addon helpers, not just override helpers. 
			*/
			kOverrideFlavorPriorityHelper = 3 
		};
};

/**
		Class/Container used to scope constants and enums specific to Drag Drop operations.
		(should be a namespace)
 */
class DragDrop
{
	public:
		/** constant to indicate that the platform default drag feedback cursors should be used
		
				@see IDragDropSource::GetDragCursor
		*/
		enum eCursorType { kDefaultDragCursors = -99 };

		/** constants for indicating drag outline behavior 
		
				@see IDragDropSource::DoMakeDragOutlineRegion
		*/
		enum eOutlineType { 
			/** no drag outline */
			kNoDragOutline = 0, 
			/** grey drag outline (default) */
			kDefaultDragOutline = -1 
		};

		/** constants to indicate the type of drop target highlighting to be used.
		
				@see IDragDropTarget::DoMakeDropHiliteRegion
		*/
		enum eTargetHiliteType { 
			/** no target highlighting will be provided */
			kNoDropHilite = 0, 
			/** use platform default target highlighting - in the modern world of color this is often difficult to see */
			kDefaultDropHilite = -1,
			/** target will draw it's own highlighting in DoDragEnter and DoDragLeave */
			kTargetWillDrawDropHilite =  kNoDropHilite 
		};
		
		/** constants to indicate whether a drop target will draw its own feedback for the data being dragged
		
				@see DragDrop::TargetResponse
		*/
		enum eTargetWillDrawTrackingFeedback { 
			/** default drag feedback should be used */
			kUseDefaultTrackingFeedback = 0, 
			/** target will draw drag feedback while drag is within it's bounds */
			kTargetWillDrawTrackingFeedback = 1 
		};

		/** constants to indicate whether a drop target will provide its own cursors for the data being dragged
		
				@see DragDrop::TargetResponse 
				@see IDragDropTarget::DoDragWithin, IDragDropController::SetTrackingCursorFeedback, IDragDropController::GetDefaultTrackingCursorFeedback
		*/
		enum eTargetWillProvideCursorFeedback { 
			/** default drag cursors should be used */
			kUseDefaultCursorFeedback = 0, 
			/** target will provide its own cursors, and set them appropriately */
			kTargetWillProvideCursorFeedback = 1 
		};

		/** constants to indicate whether the drag drop framework should treat a drop target as being a "sticky target".
				Once the framework has set a sticky target as the active target, this target will remain the active target even if mouse 
				moves outside the sticky target until such time as the mouse enters a new valid target. Default target behavior is non-sticky.
				Stick targets are used to achieve behavior similar to I-beam
		
				@see DragDrop::TargetResponse
		*/
		enum eTargetTrackingBehavior { 
			/** default drop target selection behavior */
			kUseDefaultTargetTracking = 0,
			/** drop target will have sticky behavior */
			kTargetTrackingBehaviorIsSticky = 1 
		};

		/** constants to indicate what the drop target intends to do with the drag data
		
				@see DragDrop::TargetResponse
		*/
		enum eTargetResponse {
			/** target cannot accept the data in the drop */
			kWontAcceptDrop = 0, 
			/** target will copy the data in the drop */
			kDropWillCopy = 1, 
			/** target will move the data in the drop from one location to another */
			kDropWillMove = 2, 
			/** target will create a link to orifinal location of the data in the drop */
			kDropWillLink = 4,
			/** INTERNAL USE ONLY: a constant reserved for use within the drag drop framework */
			kNoDropEffectCursor = -1 
		};

		/** constants to represent drag drop command types
		
				@see IDragDropTarget::ProcessDragDropCommand, IDragDropSource::ProcessDragDropCommand
		*/
		enum eCommandType {
			/** source should remove the data (moved to different target, or trash) */
			kDragCommand = 0,
			/** move the data within the source/target */
			kDragMoveCommand,
			/** target should copy the data */
			kDropCommand,				
			kDrag = kDragCommand,  kDragMove = kDragMoveCommand, kDrop = kDropCommand
		};

		/** Types of DragDrop/ScrapSuite flavor helpers:
				used to resolve situations where more than one helper is capable of handling a DragDrop or Clipboard operation.
				
				@see IDragDropTargetFlavorHelper::GetHelperType, IDragDropSourceContentHelper::GetHelperType, IScrapSuitePasteHelper::GetHelperType
		*/
		enum eHelperType {
			/** behavior that ships with InDesign (lowest priority) */
			kDefaultHelper = 0,
			/** behavior added to what ships in InDesign (takes precedence over default behavior) */
			kAddonHelper = 1,
			/** behavior that overrides all other helpers (highest priority - please use sparingly) */
			kOverrideHelper = 2
		};


/**
   Represents the response from a Drag Drop Target when it is asked whether or not it could accept a drag.

   @see IDragDropTarget::CouldAcceptTypes
 */
 		class PUBLIC_DECL TargetResponse : public DataExchangeResponse
		{
			public: 
				/**	Default/empty constructor. Creates a response that indicates the target will not accept the drag.
				 */
				TargetResponse() 
					: DataExchangeResponse(), 
					  fResponse(kWontAcceptDrop), 
					  fTargetWillDrawTrackingFeedback(kUseDefaultTrackingFeedback),
					  fTargetWillProvideCursorFeedback(kUseDefaultCursorFeedback),
					  fTargetTrackingBehavior(kUseDefaultTargetTracking) {}
					
				/**	Constructor

					@param response could the target accept the drop
					@param willTargetDrawTrackingFeedback will the target provide tracking feedback (by default, target will not)
					@param willTargetProvideCursorFeedback will the target provide cursor feedback (by default, target will not)
					@param targetTrackingBehavior should the target be treated as a sticky target, (by default, target will not)
					@param priority the flavor priority of the flavor the target as decided to accept (ordinarily contained in a DataExchangeResponse )
				 */
				TargetResponse(eTargetResponse response, 
										 eTargetWillDrawTrackingFeedback willTargetDrawTrackingFeedback = kUseDefaultTrackingFeedback, 
										 eTargetWillProvideCursorFeedback willTargetProvideCursorFeedback = kUseDefaultCursorFeedback, 
										 eTargetTrackingBehavior targetTrackingBehavior = kUseDefaultTargetTracking, 
										 PMFlavorPriority priority = kUnknownFlavorPriority
										)
					: DataExchangeResponse((response  != kWontAcceptDrop && response  != kNoDropEffectCursor), priority),
					  fResponse(response), 
					  fTargetWillDrawTrackingFeedback(willTargetDrawTrackingFeedback),
					  fTargetWillProvideCursorFeedback(willTargetProvideCursorFeedback),
					  fTargetTrackingBehavior(targetTrackingBehavior) {}
					  
				/**	Constructor

					@param deResponse could a handler accept the data (usually obtained from the IDataExchangeHandler involved in accepting the drop)
					@param response could the target accept the drop
					@param willTargetDrawTrackingFeedback will the target provide tracking feedback (by default, target will not)
					@param willTargetProvideCursorFeedback will the target provide cursor feedback (by default, target will not)
					@param targetTrackingBehavior should the target be treated as a sticky target, (by default, target will not)
				 */
				TargetResponse(const DataExchangeResponse& deResponse, 
										 eTargetResponse targResponse, 
										 eTargetWillDrawTrackingFeedback willTargetDrawTrackingFeedback = kUseDefaultTrackingFeedback, 
										 eTargetWillProvideCursorFeedback willTargetProvideCursorFeedback = kUseDefaultCursorFeedback, 
										 eTargetTrackingBehavior targetTrackingBehavior = kUseDefaultTargetTracking 
										) 
					: DataExchangeResponse(deResponse),
					  fResponse(targResponse), 
					  fTargetWillDrawTrackingFeedback(willTargetDrawTrackingFeedback),
					  fTargetWillProvideCursorFeedback(willTargetProvideCursorFeedback),
					  fTargetTrackingBehavior(targetTrackingBehavior) {}
					  
				/**	Copy Constructor
				 */
				TargetResponse(const TargetResponse& other) 
					: DataExchangeResponse(other), fResponse(other.fResponse), 
					  fTargetWillDrawTrackingFeedback(other.fTargetWillDrawTrackingFeedback),
					  fTargetWillProvideCursorFeedback(other.fTargetWillProvideCursorFeedback),
					  fTargetTrackingBehavior(other.fTargetTrackingBehavior) {}
				
				bool16 CanTargetAccept() const {return CanDo();}
				eTargetResponse GetResponse() const {return fResponse;}
				bool16 WillTargetDrawTrackingFeedback() const {return fTargetWillDrawTrackingFeedback == DragDrop::kTargetWillDrawTrackingFeedback;}
				bool16 WillTargetProvideCursorFeedback() const {return fTargetWillProvideCursorFeedback == DragDrop::kTargetWillProvideCursorFeedback;}
				bool16 TargetTrackingBehaviorIsSticky() const {return fTargetTrackingBehavior == DragDrop::kTargetTrackingBehaviorIsSticky;}

			protected:
				eTargetResponse							fResponse;
				eTargetWillDrawTrackingFeedback			fTargetWillDrawTrackingFeedback;
				eTargetWillProvideCursorFeedback		fTargetWillProvideCursorFeedback;
				eTargetTrackingBehavior					fTargetTrackingBehavior;
		};

		/**	TargetResponse constant to indicate target could not accept the drop */
		static const WIDGET_DECL TargetResponse		kWontAcceptTargetResponse;
		/**	TargetResponse constant to indicate an invalid response - something went wrong in the target */
		static const WIDGET_DECL TargetResponse		kInvalidTargetResponse;					
};

#pragma export off

#endif
