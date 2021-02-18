//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDragDropTarget_Extensible.h $
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
#ifndef __CDragDropTarget_Extensible__
#define __CDragDropTarget_Extensible__

#include "ShuksanID.h"
#include "DragDropID.h"

#include "IEvent.h"
#include "CDragDropTarget.h"
#include "IDropTargetCallback.h"
#include "IDragDropController.h"
#include "IDragDropTargetFlavorHelper.h"

#include "HelperInterface.h"
#include "PMFlavorTypes.h"
#include "CmdUtils.h"

class DataObjectIterator;

#pragma export on

/** Extensible implementation of the CDragDropSource interface, representing the target object that receives a drop operation.
		Implementors of IDragDropTarget should derive from either this or CDragDropTarget.
		Note that CDragDropTarget_Extensible derives from CDragDropTarget.

		@see IDragDropTarget, CDragDropTarget
 */
class WIDGET_DECL CDragDropTarget_Extensible : public CDragDropTarget
{
	typedef CDragDropTarget inherited;
	
	public:
										CDragDropTarget_Extensible(IPMUnknown *boss);
		virtual						~CDragDropTarget_Extensible();
		
		/** @name Support for Extensibility
				Framework use only - subclasses should not call or override these methods.
				HandleCouldAcceptTypes call Delegate_CouldAcceptTypes to attempt to find a flavor helper willing to accept the flavors in the drag, based on helper type and the inherent priority of the flavors in the drag.
				If no such helper can be found HandleCouldAcceptTypes reverts to the behavior inherited from CDragDropTarget, thus allowing the target to define some default behavior.
				The remaining methods here delegate to the active flavor helper if one has been set.
				Similarly, if no active helper has been set, they revert to their inherited behavior.
		*/
		//@{
		/**  */
		virtual DragDrop::TargetResponse
										HandleCouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*);

		/**  */
		virtual void				HandleDoDragEnter();
		/**  */
		virtual bool16			HandleDoDragEnter_PreflightDragData(IDragDropController*); 
		/**  */
		virtual void				HandleDoDragWithin(const PMPoint& localPt);
		/**  */
		virtual void				HandleDoDragLeave();
		/**  */
		virtual ErrorCode		HandleProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
		//@}

		/** Override if the target needs a chance to initialize itself prior to a drag operation entering the target. 
				Called from HandleCouldAcceptTypes.
				Default implementation clears the cached active target helper. 
		*/		
		virtual void				PrepareTargetForDrag();

		/** Default implementation checks CanHandleDragData, and then forwards the ProcessDragDropCommand method 
				to the active flavor helper. 
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

		// Extensibility
		/** Override this to return the service ID that flavor helpers for this target will respond to. 
		*/
		virtual ServiceID GetFlavorHelperServiceID() const = 0;
		
		/** Query for the active flavor handler, nil if one has not been set. */
		IDragDropTargetFlavorHelper*	QueryActiveFlavorHelper() const;
		/** Get the active flavor handler, nil if one has not been set. */
		IDragDropTargetFlavorHelper*	GetActiveFlavorHelper() const;
		/** Set the active flavor handler. Called by Delegate_CouldAcceptTypes when/if it finds a helper accept the data in a drag. */
		void	SetActiveFlavorHelper(IDragDropTargetFlavorHelper*);

		/** Get the cached flag for whether the target can handle the dragged data. */
		bool16						CanHandleDragData() const {return fCanHandleDragData;}
		/** Set the cached flag for whether the target can handle the dragged data.  Can be called by flavor helpers*/
		void							SetCanHandleDragData(bool16 can) {fCanHandleDragData = can;}

		/** Attempt to find a flavor helper willing to accept the flavors in the drag, based on helper type and the inherent priority of the flavors in the drag.
		*/
		DragDrop::TargetResponse						
										Delegate_CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*);
		/** Unused. This method is not called and should probably be removed. ProcessDragDropCommand currently handles delegation to the active helper */
		ErrorCode 				Delegate_ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

		/** Overridden to provide delegation to flavor helpers. If no helper is active, calls GetDragDataBounds on target itself. */
		virtual PMRect			HandleGetDragDataBounds() const;	
		
	protected:
		/** Override to give the target a chance to "preflight" the data contained in a drag.
				The default implementation returns kTrue to indicate that the drag should proceed.
		*/
		virtual bool16			DoDragEnter_PreflightDragData(IDragDropController*);

	private:
		IDragDropTargetFlavorHelper*	fActiveFlavorHelper;
		
		bool16						fCanHandleDragData;		// Once we see what the data is, can we still deal with a drop.
		
		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
