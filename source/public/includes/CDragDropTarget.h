//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDragDropTarget.h $
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
//========================================================================================

#pragma once
#ifndef __CDragDropTarget__
#define __CDragDropTarget__

#include "ShuksanID.h"
#include "DragDropID.h"

#include "IEvent.h"
#include "IDragDropTarget.h"
#include "IDropTargetCallback.h"
#include "IDragDropController.h"
#include "HelperInterface.h"
#include "PMFlavorTypes.h"
#include "CmdUtils.h"

class DataObjectIterator;

#pragma export on


/** Basic implementation of the IDragDropTarget interface, representing the target object that receives a drop operation.
		Implementors of IDragDropTarget should derive from either this or CDragDropTarget_Extensible.

		@see IDragDropTarget, CDragDropTarget_Extensible
 */
class WIDGET_DECL CDragDropTarget : public IDragDropTarget
{
	typedef IDragDropTarget inherited;
	typedef K2Vector<IDropTargetCallback*> DropTargetCallbackList;

	public:
										CDragDropTarget(IPMUnknown *boss);
		virtual						~CDragDropTarget();
		
		/** Framework use only.
				Subclasses should not call or override these methods - see protected variants.
		*/
		//@{
		/**  */
		virtual DragDrop::TargetResponse 
										HandleCouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*);
		/**  */
		virtual void				HandleDoDragEnter();
		/**  */
		virtual void				HandleDoDragWithin(const PMPoint& localPt);
		/**  */
		virtual void				HandleDoDragLeave();
		/**  */
		virtual ErrorCode		HandleProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
		//@}
		
		/** Override to specify a region to be hilighted to show that this target can accept the a drop.
				Default implementation returns DragDrop::kDefaultDropHilite, which highlights based on the bounds of the target.
		*/
		virtual SysWireframe			DoMakeDropHiliteRegion() const;

		/** Override to process the commands needed to complete a drop.
				Default implementation does nothing and returns kFailure.

			@param IDragDropController* IN controller for the drag
			@param DragDrop::eCommandType IN targets will only receive kDragMove or kDrop
			@return kSuccess or error code on failure
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

		/** Override to specify the database that would accept the drag data received by this target.
				Default behavior is to return nil - which means that no drag source, other than on on the same boss as this target,
				is able to move data to this target so the drop represents a copy.
		*/
		virtual IDataBase*	GetTargetDataBase() const;

		/** Is the specified drag source equivalent to this drag target?
				Default implementation checks to see if the source is on the same boss as this target.
		*/
		bool16 SameAsDragSource(const IDragDropSource* dragSource) const;

		/** Does the specified drag source operate on the same data (pub/database/whatever) as this drag target?
				If AffectsSameDataAsDragSource is true, then data can be "moved" between such a source and target.
				(Default implementation checks to see if they return the same IDatabase from GetSource/TargetDataBase())
		*/
		bool16 AffectsSameDataAsDragSource(const IDragDropSource* dragSource) const;

		/** Override to allow drop targets to respond outside their actual bounds. 
				Typically used for autoscrolling a target when over its scroll bars.
				Default implementation does not support this and returns kFalse.
		*/
		virtual bool16				HitTest_OutsideBounds(const SysPoint&) const;

		/** Override to look for non-widget targets inside this target.
				Default implementation does not support this and returns nil.
		*/
		virtual IDragDropTarget*	QueryInternalDropTarget(const SysPoint& windowPoint, 
																PMPoint& localPoint, 
																DataObjectIterator* dataIter, 
																const IDragDropSource* iSource, 
																const IDragDropController* iController);
		/** Basic implementation to retrieve the transformation. */
		virtual PMMatrix 	GetInternalTransform() const;
		/** Basic implementation to remember the transformation. */
		virtual void 				SetInternalTransform(PMMatrix);
	
		/** Basic implementation to register a target callback. */
		virtual void				RegisterTargetCallback(IDropTargetCallback*);
		/** Basic implementation to release a target callback. */
		virtual void				ReleaseTargetCallback(IDropTargetCallback*);
		
		/** Override to allow a target specific context (like IID_IDRAGDROPTARGETDOCUMENT) to be set.
				Default implementation does not support this.
		*/
		virtual void				SetActiveContext();
		/** Override to clear target specific context.
				Default implementation does not support this.
		*/
		virtual void				ResetActiveContext();

		/** Override to support setting of the target's document.
				Default implementation does not support this 
		*/		
		virtual void 				SetDocument(IDocument*);

		/** Override if the targets wants to draw it's own highlight/outline feedback, it can make it available here.
				This method will not be called by the framework, but can be called by flavor helpers.
				Default implementation does nothing. 
		*/		
		virtual void				DrawTargetOutline();

		/** Override if a target could be viewing "read-only" data. 
				Default is kTrue (target is modifiable).
		*/
		virtual bool16			IsTargetModifiable() const; 

	protected:
		/** Override if the target needs a chance to initialize itself prior to a drag operation entering the target. 
				Called from HandleCouldAcceptTypes.
				Default implementation does nothing. 
		*/		
		virtual void				PrepareTargetForDrag();

		/** Override to check the available external flavors to see if this target can handle any of them.
				Default implementation returns DragDrop::TargetResponse(DragDrop::kWontAcceptDrop). 
		*/		
		virtual DragDrop::TargetResponse	
										CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;

		// Tracking the drag as it enters, drags, and leaves this target
		/** Override to handle a drag entering the target. Default implementation does nothing. */		
		virtual void				DoDragEnter();
		/** Override to handle a drag moving within the target. Default implementation does nothing. */		
		virtual void				DoDragWithin(const PMPoint& localPt);
		/** Override to handle a drag leaving the target. Default implementation does nothing. */		
		virtual void				DoDragLeave();
		
		/** Default implementation to call any target callbacks registered for this target. Called
				from HandleDoDragEnter/Within/Leave just after calling DoDragEnter/Within/Leave.
		*/
		virtual void 				NotifyTargetCallbacks(IDropTargetCallback::eCallbackState state, 
																			const PMPoint& localPt);
																			
		/** Added so delegation of GetDragDataBounds to FlavorHelpers is possible. 
				Default implementation simply calls GetDragDataBounds() on this target
		*/
		virtual PMRect			HandleGetDragDataBounds() const;	// 
		/** Override to return the dragged item bounds that will be sent to the target callbacks. 
				Default implementation returns an empty PMRect 
		*/
		virtual PMRect			GetDragDataBounds() const;
		
	protected:
		/** Retrieve the target response computed in CouldAcceptTypes for later use.
				Response is cached by HandleCouldAcceptTypes 
		*/
		const DragDrop::TargetResponse& GetCachedResponse() const {return fCachedResponse;}
		mutable DragDrop::TargetResponse		fCachedResponse;
		
		DropTargetCallbackList* GetTargetCallbackList() {return &fTargetCallbackList;}

	private:
		PMMatrix						fInternalTransform;
		DropTargetCallbackList 	fTargetCallbackList;
		
		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
