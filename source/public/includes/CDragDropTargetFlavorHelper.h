//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDragDropTargetFlavorHelper.h $
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
#ifndef __CDragDropTargetFlavorHelper__
#define __CDragDropTargetFlavorHelper__

#include "IDragDropTargetFlavorHelper.h"

#include "IDragDropSource.h"
#include "IDragDropTarget.h"
#include "IDragDropController.h"
#include "IDataExchangeHandler.h"

#pragma export on

//========================================================================
// Class CDragDropTargetFlavorHelper
/** Common baseclass for Drag Drop Target Flavor Helpers. 
		Implementors of drop target flavor helpers should subclass CDragDropTargetFlavorHelper,
		
		@see IDragDropTargetFlavorHelper
*/
//========================================================================
class WIDGET_DECL CDragDropTargetFlavorHelper : public IDragDropTargetFlavorHelper
{
	public:
										CDragDropTargetFlavorHelper(IPMUnknown *boss);
		virtual						~CDragDropTargetFlavorHelper();
		
		/** Override to change the type or priority of the helper.
				Default implementation returns DragDrop::kDefaultHelper.
		*/
		virtual DragDrop::eHelperType	
										GetHelperType() const;

		/** Override if the helper wants to do its own drag dracking.
				Default implementation returns kFalse.
		*/
		virtual bool16			HelperWillDoDragTracking() const;

		/** Override to perform any necessary initialization of the target helper, called from HandleCouldAcceptTypes.
				Default implementation does nothing.
		*/
		virtual void 				PrepareHelperForDrag() const;

		/** Override to indicate if this target helper can accept the current drag.
		*/
		virtual DragDrop::TargetResponse	
										CouldAcceptTypes(const IDragDropTarget*, DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const = 0;

		/** Once we see the data inside a drag, can we still perform the drop. */
		bool16						CanHandleDragData() const {return fCanHandleDragData;}
		/** Set the "can handle drag data" flag. */
		void							SetCanHandleDragData(bool16 can) {fCanHandleDragData = can;}

		/** Override to give helper a chance to "preflight" the data contained in a drag.
				Default implementation returns kTrue (all is well).
		*/
		virtual bool16			DoDragEnter_PreflightDragData(IDragDropTarget*, IDragDropController*);

		/** Override to respond to a drag entering the target.
				Default implementation falls back to the target.
		*/
		virtual void				DoDragEnter(IDragDropTarget*);
		/** Override to respond to a drag moving within the target.
				Default implementation falls back to the target.
		*/
		virtual void				DoDragWithin(IDragDropTarget*, const PMPoint& localPt);
		/** Override to respond to a drag leaving the target.
				Default implementation falls back to the target.
		*/
		virtual void				DoDragLeave(IDragDropTarget*);

		/** Override to create and process (or schedule) the commands needed to complete the drop operation. 
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropTarget*, IDragDropController*, DragDrop::eCommandType) = 0;

		/** INTERNAL_USE_ONLY - Subclasses should override CouldAcceptTypes. 
		*/
		DragDrop::TargetResponse	
										HandleCouldAcceptTypes(const IDragDropTarget*, DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
		
		/** Override to return the bounds of the item(s) being dragged.
				Default implementation returns an empty rect.
		*/
		virtual PMRect			GetDragDataBounds() const;	

	protected:
		DragDrop::TargetResponse GetCachedResponse() const {return fCachedResponse;}
		
		mutable DragDrop::TargetResponse		fCachedResponse;
		mutable bool16			fCanHandleDragData;		
};

#pragma export off

#endif
