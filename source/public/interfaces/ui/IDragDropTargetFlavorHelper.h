//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDragDropTargetFlavorHelper.h $
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
//  Interface definition for Drag and Drop target extensibility
//  
//========================================================================================

#pragma once
#ifndef __IDragDropTargetFlavorHelper__
#define __IDragDropTargetFlavorHelper__

#include "DragDropConstants.h"

#include "IDragDropSource.h"
#include "IDragDropTarget.h"
#include "PMRect.h"

/** The IDragDropTargetFlavorHelper interface provides extensibility for drag drop targets.
	Implementors of IDragDropTargetFlavorHelper should derive from CDragDropTargetFlavorHelper which provides 
	default implementations for many of the methods described here.

	Drag target extensibility requires the source be derived from CDragDropSourceTarget_Extensible.  
	Create a new boss with an IDragDropTargetFlavorHelper implementation combined with a IK2ServiceProvider 
	implementation that corresponds to the service ID defined by the extensible drag target.
	
	When the framework asks an extensible drag target if could accept the drag being dragged onto it, 
	the target then asks each of it's flavor helpers if they could accept any of the flavors in the dragged data. 
	One helper is chosen based on it's willingness to accept the drag, and in the case of multiple helpers, 
	prioritized by helper type and the priority of the flavor they propose to accept. The extensible target then 
	forwards the subsequent method calls that occur during the drag to the chosen helper.
	
	@see IDragDropTarget, CDragDropTargetFlavorHelper, CDragDropSourceTarget_Extensible, IK2ServiceProvider
 */
class IDragDropTargetFlavorHelper : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAGDROPTARGETFLAVORHELPER };

		/** Return the type or priority of the helper.
			This is used to resolve conflicts that can arise when more than one target flavor helper is 
			capable of accepting the drag data. The presence of multiple helpers is not a conflict,
			a conflict would arise when one helper wants to replace or augment what another helper already does.
		
			@return helper type appropriate for this helper. Use DragDrop::kDefaultHelper by default.
		*/
		virtual DragDrop::eHelperType	
									GetHelperType() const = 0;

		/** Does the helper want to do its own drag dracking?
			Id kTrue is returned, the helper will receive DoDragEnter, DoDragWithin, and DoDragLeave calls.

			@return kTrue if the helper wants to do its own tracking
		*/
		virtual bool16		HelperWillDoDragTracking() const = 0;

		/** INTERNAL_USE_ONLY. An implementation of this method is provided in CDragDropTargetFlavorHelper. 
			Subclasses should not override this method; see the protected variant below. 
		*/
		virtual DragDrop::TargetResponse	
										HandleCouldAcceptTypes(const IDragDropTarget*, DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const = 0;
		
		/** Give helper a chance to "preflight" the data contained in a drag.
			This method is called during CDragDropTarget_Extensible::HandleDoDragEnter. 
			Preflighting is not recommended, but can be necessary if type acceptance is insufficient.
			Since the data in external drags will have to be internalized, the data should not 
			be re-internalized in ProcessDragDropCommand, below.
			
			@param target IN the drag drop target this helper is assisting
			@param controller IN drag drop controller for this operation
			@return kTrue to indicate that the drag should proceed, kFalse otherwise.
		*/
		virtual bool16		DoDragEnter_PreflightDragData(IDragDropTarget*, IDragDropController*) = 0;

		/** Respond to a drag entering the target.
			Implementors often override DoDragEnter when implementing non standard drag tracking 
			behavior - especially custom drag hilighting and feedback. If information about the 
			data is needed while tracking it can be obtained from the IDragDropController interface on the session. 

			@param target IN the drag drop target this helper is assisting
			@precondition only called if HelperWillDoDragTracking returns kTrue
		*/
		virtual void			DoDragEnter(IDragDropTarget*) = 0;
		
		/** Respond to a drag moving over and within the target.
			Implementors often override DoDragWithin when implementing non standard drag behavior - 
			especially custom drag feedback.

			@param target IN the drag drop target this helper is assisting
			@param localPt IN coordinates of the cursor in local target coordinates.
			@precondition only called if HelperWillDoDragTracking returns kTrue
		*/
		virtual void			DoDragWithin(IDragDropTarget*, const PMPoint& localPt) = 0;
		
		/** Respond to a drag leaving the target.
			Implementors often override DoDragLeave when implementing non standard drag behavior - 
			especially custom drag hilighting and feedback.

			@param target IN the drag drop target this helper is assisting
			@precondition only called if HelperWillDoDragTracking returns kTrue
		*/
		virtual void			DoDragLeave(IDragDropTarget*) = 0;

		/** Create and process (or schedule) the commands needed to complete the drop operation. 
			Normally called on the drop target, this method is also called on sources when the 
			original data needs to be deleted, as in a drag to the trash.
		
			@param target IN the drag drop target this helper is assisting
			@param controller IN drag drop controller for this operation
			@param commandType IN which operation to perform (targets will only receive kDragMove or kDrop)
			@return success or failure of the drop
		*/
		virtual ErrorCode	ProcessDragDropCommand(IDragDropTarget*, IDragDropController*, DragDrop::eCommandType) = 0;

		/** Return the bounds of the item(s) being dragged.
			The bounds are provided to all IDropTargetCallbacks registered on the target of the drag.

			@precondition only called if HelperWillDoDragTracking returns kTrue
			@return dragged item bounds
		*/
		virtual PMRect		GetDragDataBounds() const = 0;	

	protected:

		/** Could this target helper accept the current drag.
			Override CouldAcceptTypes to report whether the helper could accept any of the promised 
			flavors in the dragged data. CouldAcceptTypes should not attempt to examine the actual 
			drag data, but should base it's return value only on the flavors of data available. 
			Add kDropTargetDrawsFeedback to result if target will draw its own feedback representing 
			the data as it moves through the target, as does the layout widget.  Not to be confused 
			with target hilighting.
		
			@param target IN the drag drop target this helper is assisting
			@param iter IN iterator based access to drag items in the drag (usually just one)
			@param source IN the drag drop source where the drag originated, used to help determine 
			if operation would result in a move, copy or link. (drags from external apps will have source == nil)
			@param controller IN drag drop controller for this operation
			@return the action the target intends to perform (nothing, copy, move, link) plus target options for handling the drag
		*/
		virtual DragDrop::TargetResponse		
									CouldAcceptTypes(const IDragDropTarget*, DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const = 0;

};

#endif
