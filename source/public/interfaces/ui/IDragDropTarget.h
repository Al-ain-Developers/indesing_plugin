//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDragDropTarget.h $
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
//  Interface definition for Drag and Drop targets
//  
//========================================================================================

#pragma once
#ifndef __IDragDropTarget__
#define __IDragDropTarget__

#include "DragDropID.h"
#include "DragDropConstants.h"

#include "IPMUnknown.h"

class IDragDropSource;
class IDragDropController;
class ICommand;
class PMMatrix;
class DataObjectIterator;
class PMPoint;
class IDocument;
class IDropTargetCallback;
class ICommandSequence;
class IDataBase;

/** IDragDropTarget interface, represents the target or destination object in a drag drop operation.
		Implementors should derive from either CDragDropTarget or CDragDropTarget_Extensible.

		@see IDragDropSource
 */
class IDragDropTarget : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAGDROPTARGET };
		
	public:
		/** Create a region to be highlighted to show that this target can accept the a drop.
				Can return constants kNoDropHilite, kDefaultDropHilite, or kTargetWillDrawDropHilite -
				caller is responsible for releasing the returned region, if any.
				
			@return SysWireframe region to be highlighted
		*/
		virtual SysWireframe			DoMakeDropHiliteRegion() const = 0;

		/** @cond INTERNAL_USE_ONLY */
		/** For Framework use only, subclasses should not call or override this method - see protected variants below. 
		*/
		virtual DragDrop::TargetResponse 
										HandleCouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) = 0;
		/** For Framework use only, subclasses should not call or override this method - see protected variants below. 
		*/
		virtual void				HandleDoDragEnter() = 0;
		/** For Framework use only, subclasses should not call or override this method - see protected variants below. 
		*/
		virtual void				HandleDoDragWithin(const PMPoint& localPt) = 0;
		/** For Framework use only, subclasses should not call or override this method - see protected variants below. 
		*/
		virtual void				HandleDoDragLeave() = 0;
		/** For Framework use only, subclasses should not call or override this method - see protected variants below. 
		*/
		virtual ErrorCode		HandleProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType) = 0;
		/** @endcond INTERNAL_USE_ONLY */
		
		/** Return the database that would accept the drag data received by this target.
				Used to determine if a source and target belonging to different bosses actually view the same data.
				Can be used to determine if a drag operation should be a move vs. a copy, but not required.
		
			@return the affected database (usually returns the database of an IDocument, or nil)
		*/
		virtual IDataBase*	GetTargetDataBase() const = 0;

		/** Convenience method for determining if the specified drag source is equivalent to this drag target?
		
			@param dragSource IN the drag source
			@return are they the same? Default implementation in CDragDropTarget checks that the source and target are on the same boss object.
		*/
		virtual bool16 			SameAsDragSource(const IDragDropSource* dragSource) const = 0;

		/** Convenience method for determining if the specified drag source and this drag target affect the same data?
			If true, then data can be "moved" between such a source and target.

			@param dragSource IN the drag source
			@return do they affect the same data? Default implementation in CDragDropTarget compares source->GetSourceDataBase() and this->GetTargetDataBase().
		*/
		virtual bool16 			AffectsSameDataAsDragSource(const IDragDropSource* dragSource) const = 0;

		/** Target implementors can override this to allow drop targets to respond to drops outside their actual bounds.
			Default implementation returns kFalse. Used for autoscrolling a target when cursor over its scroll bars, among other things.
			
		@param pt IN current mouse location
		@return should this target respond for the given point outside it's bounds
		*/
		virtual bool16			HitTest_OutsideBounds(const SysPoint&) const = 0;

		/** Look for non-widget targets inside this target.
				Used to traverse non-widget hierarchies (like page items, etc.)
				Transform to internal target must be supplied by this item
			
			@param windowPoint IN current mouse location in window coordinates.
			@param localPoint OUT transform to that of target coordinates.
			@param iter IN iterator based access to drag items in the drag (usually just one)
			@param source IN the drag drop source where the drag originated
			@param controller IN drag drop controller for this operation
			@return should this target respond for the given point outside it's bounds
		*/
		virtual IDragDropTarget* QueryInternalDropTarget(const SysPoint& windowPoint, 
															PMPoint& localPoint, 
															DataObjectIterator*, 
															const IDragDropSource*, 
															const IDragDropController*) = 0;
															
		/** Get the transform to convert from window to targets internal coordinates. 
				Not needed unless the target has internal targets.
			@return should this target respond for the given point outside it's bounds
		*/
		virtual PMMatrix 	GetInternalTransform() const = 0;
		/** Set the transform to convert from window to targets internal coordinates
			@param controller IN drag drop controller for this operation
		*/
		virtual void 				SetInternalTransform( PMMatrix) = 0;
		
		/** Register a target callback object.
				IDropTargetCallback is an external object that wants to follow the tracking state of a particular drop target (i.e. RulerCarets).
			@param callback IN callback to register
		*/
		virtual void				RegisterTargetCallback(IDropTargetCallback*) = 0;

		/** Release a target callback object.
				IDropTargetCallback is an external object that wants to follow the tracking state of a particular drop target.
			@param callback IN callback to unregister and release
		*/
		virtual void				ReleaseTargetCallback(IDropTargetCallback*) = 0;
		
		/** @cond OBSOLETE */
		/** This method is no longer called by the Framework. */
		virtual void				SetActiveContext() = 0;
		/** This method is no longer called by the Framework. */
		virtual void				ResetActiveContext() = 0;
		/** @endcond OBSOLETE */
		
		/** Set the document on an internal target.
				This method allows the parent target to set the document on an internal target that might not otherwise be able to find it's document.
				Is there a better way than passing this from target to target?		

		@param doc IN the document to remember
		*/
		virtual void 				SetDocument(IDocument*) = 0;
		
		/** Draw the target's outline feedback.
				A convenience method for targets that draw their own Highlight/Outlined feedback, so that their flavor helpers can trigger the drawing.
				This will not be called by the framework.
		*/
		virtual void				DrawTargetOutline() = 0;

		/**  Is the target viewing "read-only" data.
				 A convenience method to determine if a target is viewing "read-only" or modifiable data. Default is kTrue (modifiable).
		*/
		virtual bool16			IsTargetModifiable() const = 0; 

protected:
		/** Could the target accept the current drag.
				Implementors should override CouldAcceptTypes to report whether the target could accept any of the promised flavors in the dragged data.
				CouldAcceptTypes should not attempt to examine the actual drag data, but should base it's return value only on the flavors of data available. 
				Add kDropTargetDrawsFeedback to result if target will draw its own feedback representing the data as it moves through the target, 
				as does the layout widget.  Not to be confused with target hilighting.
		
			@param iter IN iterator based access to drag items in the drag (usually just one)
			@param source IN the drag drop source where the drag originated, used to help determine if operation would result in a move, copy or link.
				 (drags from external apps will have source == nil)
			@param controller IN drag drop controller for this operation
			@return the action the target intends to perform (nothing, copy, move, link) plus target options for handling the drag
		*/
		virtual DragDrop::TargetResponse 
										CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const = 0;
		
		friend class 				CDragDropTargetFlavorHelper; // Used so it can inherit targets drag handling behavior
		
		/** Respond to a drag entering the target.
				Implementors often override DoDragEnter when implementing non standard drag tracking behavior - especially custom drag hilighting and feedback.
				If information about the data is needed while tracking it can be obtained from the IDragDropController
				interface on the session. 
		*/
		virtual void				DoDragEnter() = 0;

		/** Respond to a drag moving over and within the target.
				Implementors often override DoDragWithin when implementing non standard drag behavior - especially custom drag feedback.
			@param localPt IN coordinates of the cursor in local target coordinates.
		*/
		virtual void				DoDragWithin(const PMPoint& localPt) = 0;

		/** Respond to a drag leaving the target.
				Implementors often override DoDragLeave when implementing non standard drag behavior - especially custom drag hilighting and feedback.
		*/
		virtual void				DoDragLeave() = 0;

		/** Create and process (or schedule) the commands needed to complete the drop operation. 
				Normally called on the drop target, this method is also called on sources when the original data needs to be deleted, as in a drag to the trash.
		
			@param controller IN drag drop controller for this operation
			@param commandType IN which operation to perform (targets will only receive kDragMove or kDrop)
			@return success or failure of the drop
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType) = 0;
			
};

#endif
