//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDragDropController.h $
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
//  Interface definition for the Drag and Drop controller
//  
//========================================================================================

#pragma once
#ifndef __IDragDropController__
#define __IDragDropController__

#include "CDataExchangeController.h"

#include "DragDropConstants.h"

#include "IPMDataObject.h"
#include "IDataExchangeHandler.h"
#include "PMPoint.h"
#include "DragDropID.h"
#include "CursorSpec.h"

class IPMDataObject;
class IDragDropSource;
class IDragDropTarget;
class IEvent;
class DataObjectIterator;
class IAbortableCmdSeq;

/** IDragDropController interface, represents the controlling entity in a drag drop operation.
		
		IDragDropController is derived should derive from IDataExchangeController by way of the partial implementation
		class CDataExchangeController. Implementations of IDragDropController provide the glue between the platform dependent
		drag managers (OLE and Mac OS X) and the platform independent Drag Drop framework presented bu InDesign.

		@see IDataExchangeController
 */
class IDragDropController : public CDataExchangeController
{
	public:
		enum { kDefaultIID = IID_IDRAGDROPCONTROLLER };
		
	public:
		// ----- Constructor/Destructor
		IDragDropController(IPMUnknown *boss) : CDataExchangeController(boss) {};
		virtual ~IDragDropController() {};

		// ----- Managing the drag UI
		/** Ask the controller to begin a drag operation.

			@param source IN the drag source that will provide data for the drag
			@param e IN event that should initiate the drag (used for mouse location and modifier keys)
			@param patientUser IN whether or not the drag should happen in "patient user" mode. Typically this means the user is
			willing to wait a bit for better drag feedback (i.e. drag the real item vs drag an outline)
			@precondition a drag must not already be in progress
			@return whether or not the drag succeeded
			@postcondition upon return, the drag will have completed for better or worse
		*/
		virtual bool16				StartDrag(IDragDropSource*, IEvent* e, bool16 patientUser = kFalse) = 0;
		
		/** Clear the controller of any knowledge of the previous drag operation.
				Called by the framework in preparation to begin a new drag and also at the end of all drags started within the application.
		*/
		virtual ErrorCode 			ClearDrag() = 0;
		
		/** Ask the controller if a drag operation is in progress.
				For drags started within this application, IsDragInProgress will remain true until the platform drag manager
				completes the entire drag operation. However, for drags that begin in another application, IsDragInProgress will only be
				true while the drag is actually over one of this applications target windows. 

			@return kTrue if a drag is in progress
		*/
		virtual bool16				IsDragInProgress() const = 0; 
		
		/** Get the location of the drag.
				GetDragMouseLocation actually the location of the drag cursor as maintained by the platform drag manager. As such this is the location
				of the mouse at the start of the last callback from the platform drag manager into the Drag Drop framework. When doing drag tracking
				this location should be used rather than the actual current mouse location since some lag may be involved.

			@return location of the drag cursor in global (screen) coordinates
		*/
		virtual GSysPoint 			GetDragMouseLocation() const = 0;
		
		/** Was the drag started in patient user more?

			@precondition a drag must be in progress
			@return kTrue for patient user mode
		*/
		virtual bool16				IsPatientUser() const = 0; 
		
		/** Is the user currently using the copy gesture (option/alt key pressed)?

			@return kTrue for patient user mode
		*/
		virtual bool16				IsUserUsingCopyGesture() const = 0;
		
		/** Was the user using the copy gesture (option/alt key pressed) at the time the drag was started?

			@precondition a drag must be in progress
			@return kTrue or kFalse
		*/
		virtual bool16				DidUserUseCopyGesture() const = 0;
		
		/** Was the user using the drag children gesture (cmd key pressed) at the time the drag was started?

			@precondition a drag must be in progress
			@return kTrue or kFalse
		*/
		virtual bool16				DidUserUseDragChildrenGesture() const = 0;
		
		/** Description

			@precondition a drag must be in progress
			@return kTrue of the drag source and drop target exist and are on the same boss.
		*/
		virtual bool16				IsTargetSameAsSource() const = 0;

		/** Is data from an external drag, or data in a non-native format, waiting to be converted to an internally supported format?
				This method can be useful for clients that would like to peek at the drag data if it has already been internalized, 
				or is already in a native (internal) format. Internalizing can be expensive (think import or place gun) and should not be 
				called to generate user feedback (i.e. menu enabling, drag feedback)

			@precondition a drag must be in progress
			@return kTrue if the data in the drag needs to be converted.
		*/
		virtual bool16				NeedsToInternalize() const = 0;

		// ----- Methods to access data contained in a drag.
		/** How many drag items are in the current drag?
				Multiple drag items is strictly a Mac only concept. On Windows there is only one drag item
				which might contain multiple pieces of data (i.e. files or pageitems). On the Mac, multiple drag items are
				supported because some external applications present their data this way (i.e. in a multi-file drag the Finder
				uses a drag item to represent each file dragged). The DragDrop framework attempts to hide this fact as much as possible
				but it does appear in various places.

			@precondition a drag must be in progress
			@return how many items are in the drag (might be zero for an internal drag with no data added yet)
		*/
		virtual uint16 	GetItemCount() = 0;
		
		/** Add a drag item to the current drag operation.
				This method is called by IDragDropSource::DoAddDragContent and should normally only be called once per drag.
				Exceptions would be Mac only, and only when trying to emulate the behavior of another applications drag behavior (i.e the Finder).

			@param itemID IN the id of the item to add (almost always 1).
			@precondition a drag must be in progress
			@return a new drag item
			@postcondition caller must release the returned data object.
		*/
		virtual IPMDataObject*	AddDragItem(uint32 itemID) = 0;	// Returns an addref'd interface, caller must release

		/** Retrieve a particular drag item from the current drag

			@param itemID IN the id of the item to retriver (almost always 1).
			@precondition a drag must be in progress
			@return a pointer the drag item
		*/
		virtual IPMDataObject*	GetDragItem(uint32 itemID) = 0;
	
		/** Get the command sequence encompassing the current drag.
			This command sequence is necessary for two-part move operations where the drag results in
			data being removed from the source and added to the target.

			@return command sequence, or nil if a drag is not in progress.
		*/
		virtual IAbortableCmdSeq* GetCommandSequence() const = 0;
		
		// ----- Active handlers
		/** Retrieve the data exchange handler used to add data to the drag.
				There will always be a source handler for drags started within the application,
				but there will not be a source handler for drag started externally.

			@precondition a drag must be in progress
			@return data exchange handler used when data was added to the drag, or nil for externally initiated drags.
		*/
		virtual IDataExchangeHandler*	QuerySourceHandler() const = 0;
		
		/** Set the data exchange handler used by source for the current drag.
				Should be called from in IDragDropSource::DoAddDragContent or IDragDropSourceContentHelper::DoAddDragContent.

			@param handler IN the handler
			@postcondition should be called only once per drag
		*/
		virtual void					SetSourceHandler(IDataExchangeHandler* handler) = 0;
		
		/** Retrieve the data exchange handler requested by the drop target in the current drag.
				There may not be a target handler, it is not a requirement that the drop target sets a target handler.

			@precondition a drag must be in progress
			@return data exchange handler requested by the drop target (possibly nil), or nil for externally completed drags.
		*/
		virtual IDataExchangeHandler*	QueryTargetHandler() const = 0;

		/** Set the data exchange handler used by target for the current drop.
				Called from IDragDropTarget::ProcessDragDropCommand or IDragDropTargetFlavorHelper::DoAddDragContent.
				It is a good think to set SetTargetHandler prior to checking NeedsToInternalize() and Internalize() as
				the presence of this information can help in the internalization process.

			@precondition a drag must be in progress
			@param handler IN the handler
		*/
		virtual void					SetTargetHandler(IDataExchangeHandler* handler) = 0;
		
		/** Determine which data exchange handler could best handle the data in a drag.
				By passing a specific internal flavor, you are asking if the data in the drag can be converted into that flavor.
				By passing kNoFlavor, the controller will instead find the first handler which recognizes the data in the drag,
				regardless of the flavor of object it creates.

			@param response OUT response from the data exchange handler
			@param internalizedFlavor IN the preferred internal flavor (native format) if data needs to be converted.
			@precondition a drag must be in progress
			@return the handler (if any) that can provide the requested conversion.
		*/
		virtual IDataExchangeHandler*	QueryHandlerForInternalize(DataExchangeResponse& response, const PMFlavor& internalizedFlavor = kNoFlavor) const = 0;

		// ----- Externalize/Internalize Methods
		/** Render the contents of the drag out to the platform drag manager.
				FulfillPromise is called by the drag drop framework in response a flavor data request from an external drop target.
				Internally it sets up a PMFlavorStream and calls the source handler to externalize the flavor to the stream. 

			@param whichItem IN the IPMDataObject representing the drag item.
			@param whichFlavor IN which flavor to provide data for
			@precondition a drag must be in progress
			@return kSuccess or an error code
		*/
		virtual ErrorCode			FulfillPromise(IPMDataObject* whichItem, const ExternalPMFlavor& whichFlavor) const = 0;
		
		/** A framework call that is now a no-op

			@param whichFlavor IN flavor to externalize
			@return kSuccess or an error code
		*/
		virtual ErrorCode			ExternalizeDrag(PMFlavor whichFlavor) const = 0;
		
		/** Can the data in a drag be internalized during the tracking phase of a drag.
			This question turned out to be not so simple - in essense the answer is "Well, maybe."  So these days, if you have to ask
			the answer is no.  However if you have special knowledge of the source of the drag and of the flavor being promised
			and the data is simple for the source to externalize - then, maybe, you can ask for the data during tracking.

			@return always returns kFalse
		*/
		virtual bool16				CanInternalizeDuringTracking() const = 0;
		
		/** Render the contents of the platform drag manager into an internal data format.
			Usually called from IDragDropTarget::ProcessDragDropCommands or, occasionally for internal drags, from IDragDropTarget::DoDragEnter

			@param extFlavor IN specify which external flavor should be used for the conversion, or kNoExternalFlavor to let the data exchange handler decide which one to use.
			@param intFlavor IN specify which internal flavor you would like the data to end up in, or kNoFlavor to let the framework decide.
			@precondition a drag must be in progress
			@return kSuccess or an error code
		*/
		virtual ErrorCode			InternalizeDrag(ExternalPMFlavor extFlavor, PMFlavor intFlavor) = 0;
		
		// ----- Support for target supplied cursor feedback
		/** Allows a drop target to set the cursor while tracking.
			Targets should call SetTrackingCursorFeedback during the tracking phase DoDragEnter, DoDragWithin, DoDragLeave

			@param cursor IN the cursor to be shown
			@precondition a drag must be in progress
		*/
		virtual void					SetTrackingCursorFeedback(const CursorSpec& cursor) = 0;
		
		/** Allows a drop target to get the default cursor that would otherwise be used while tracking.

			@param targetResponse IN specify the target response for which the cursor is needed
			@precondition a drag must be in progress
			@return the default cursor matching the supplied target response
		*/
		virtual CursorSpec		GetDefaultTrackingCursorFeedback(DragDrop::eTargetResponse targetResponse) const = 0;

		/** Allows framework to see if the target will be providing cursor feedback while tracking - FRAMEWORK USE ONLY.

			@precondition a drag must be in progress
			@return kTrue if the target will provide cursor feedback.
		*/
		virtual bool16				WillTargetProvideCursorFeedback() const = 0;

		// ----- Support for platform specific drag drop features
#ifdef MACINTOSH
		/** Mac Only: Platform drag manager calls this to obtain targeting information for special targets.

			@param item IN the data object the location applies to
			@param dropLocation OUT description of the drop target location (used with kPasteboardTypeFileURLPromiseExternalFlavor). Caller must release.
			@return noErr for success or error code otherwise
		*/
		virtual OSErr				CopyDropLocation(CFURLRef* dropLocation) const = 0;
		
		/** Mac Only: Drag Drop framework calls this to set additional targeting information for special targets.

			@param item IN the data object the location applies to
			@param dropLocation IN description of the drop target location (used with kPasteboardTypeFileURLPromiseExternalFlavor)
			@return noErr for success or error code otherwise
		*/
		virtual OSErr				SetDropLocation(CFURLRef dropLocation) = 0;
#endif

		/** Suppress external drag handling.
				During certain critical sections (EventAvail, PreviewModalDialogs, ProgressBar, CommandProcessing)
				we have to refuse drag messages for drags initiated outside InDesign to avoid getting messages out of order 
				as well as avoiding re-entrancy in the command processor. 
				Don't call this method directly, use stack based class below to guarantee balance.

			@param doSuppress IN kTrue to suppress drag handling, kFalse to restore it
		*/
		virtual void				SuppressExternalDragHandling(bool16 doSuppress) = 0;
};

/** SuppressExternalDragsDuringCriticalSection used to suppress drag initiation during critical code sections.
		
		During certain critical sections (EventAvail, PreviewModalDialogs, ProgressBar, CommandProcessing)
		we have to refuse drag messages for drags initiated outside InDesign to avoid getting messages out of order 
		as well as avoiding re-entrancy in the command processor. 

		@see IDragDropController
 */
class SuppressExternalDragsDuringCriticalSection
{
	public:
		SuppressExternalDragsDuringCriticalSection()
		{
			InterfacePtr<IDragDropController> dragController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
			if (dragController)
				dragController->SuppressExternalDragHandling(kTrue);
		}
		
		~SuppressExternalDragsDuringCriticalSection()
		{
			InterfacePtr<IDragDropController> dragController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
			if (dragController)
				dragController->SuppressExternalDragHandling(kFalse);
		}
};

#endif
