//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrwEvtDispatcher.h $
//  
//  Owner: David Berggren
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
//  This interface registers, unregisters and calls draw event handlers who wish
//  to process draw events.
//  
//========================================================================================

#pragma once
#ifndef __IDrwEvtDispatcher__
#define __IDrwEvtDispatcher__

#include "IPMUnknown.h"

class IDrwEvtHandler;
class GraphicsData;
class PMRect;
class UIDRef;
class PMMatrix;
class ICallback;
class IVisitorHelper;
class IBaseVisitor;

/** DrwEvtHandler priorities
*/
enum 
{
	/** Post process - HandleEvent return code ignored (called after all other priorities)
	*/
	kDEHPostProcess,

	/** Lowest priority - called last
	*/
	kDEHLowestPriority,
	/** Low priority
	*/
	kDEHLowPriority,
	/** Medium priority
	*/
	kDEHMediumPriority,
	/** High priority - called first, after initialization
	*/
	kDEHHighPriority,

	/** Initialization - HandleEvent return code ignored (called before all other priorities)
	*/
	kDEHInitialization
};
typedef int32 DrwEvtHandlerPriority;

/** The IDrwEvtDispatcher can be instaniated off the session in order to register a draw event
	handler (see IDrwEvtHandler). 
	A draw event handler has to register using a particular priority. The handlers are
	called from high to lowest priority for each event. If any handler returns true
	from the HandleEvent call, it is assumed the event has been handled, and the
	remaining lower priority handlers are not called. The initialization priority is 
	called before all other priorities, however the return code from HandleEvent is ignored.
	@see IDrwEvtHandler
*/
class IDrwEvtDispatcher : public IPMUnknown
{
	public:
		/** Register an event handler using the supplied priority.
			NOTE: an AddRef will be called on the handler!
			@param eventID IN the event ID you are registering for - see DocumentContextID.h in kMessageIDSpace
			@param handler IN the handler that will handle the dispatch
			@param priority IN which priority to be used - see DrwEvtHandlerPriority
		*/
		virtual void RegisterHandler(ClassID eventID, IDrwEvtHandler *handler, DrwEvtHandlerPriority priority) = 0;
		
		/** Unregister an event handler - the opposite of RegisterHandler.
			NOTE: a Release will be called on the handler!
			@param eventID IN the event ID you are unregistering for
			@param handler IN the handler that you are unregistering
		*/
		virtual void UnRegisterHandler(ClassID eventID, IDrwEvtHandler *handler) = 0;

		/** Propigate event throughout the registered handlers - this version usually called from the DrawShape methods 
			on the different shapes. Data is packaged into DrawEventData class to be sent to ProcessEvent in IDrwEvtHandler.
			@param eventID IN the event ID being executed - see DocumentContextID.h in kMessageIDSpace
			@param changedBy IN who is dispatching this event
			@param gd IN current graphic data in place
			@param flags IN - See IShape.h for the drawing flags.
			@return bool16 - kTrue if the handler handled the event and the calling code should not continue, kFalse otherwise
		*/
		virtual bool16 ProcessFilterEvent( IPMUnknown *changedBy, GraphicsData* gd, int32 flags) = 0;
		bool16 ProcessHitTestFilterEvent( IPMUnknown *changedBy, GraphicsData* gd, int32 flags)
		{
			return ProcessFilterEvent( changedBy, gd, flags);
		}
		bool16 ProcessInvalFilterEvent( IPMUnknown *changedBy, GraphicsData* gd, int32 flags)
		{
			return ProcessFilterEvent( changedBy, gd, flags);
		}
		bool16 ProcessDrawFilterEvent( IPMUnknown *changedBy, GraphicsData* gd, int32 flags)
		{
			return ProcessFilterEvent( changedBy, gd, flags);
		}
		virtual bool16 ProcessDrawEvent(ClassID eventID, IPMUnknown *changedBy, GraphicsData* gd, int32 flags) = 0;
		
		/** Propigate event throughout the registered handlers - this version called from the hit test handlers.
			Data is packaged into HitTestEventData class to be sent to ProcessEvent in IDrwEvtHandler.
			@param eventID IN the event ID being executed - see DocumentContextID.h in kMessageIDSpace
			@param changedBy IN who is dispatching this event
			@param gd IN current graphic data in place
			@param r IN the hit rectangle
			@param thingHit INOUT the UIDRef of the thing that is hit
			@param flags IN see IShape.h for the drawing flags
			@param isHit INOUT bool16 kTrue if the thing is hit, kFalse otherwise
			@return bool16 - kTrue if the handler handled the event and the calling code should not continue, kFalse otherwise
		*/
		virtual bool16 ProcessHitTestEvent(ClassID eventID, IPMUnknown *changedBy, GraphicsData* gd, const PMRect &r, UIDRef* thingHit, int32 flags, bool16 *isHit) = 0;
		
		/** Propigate event throughout the registered handlers - this version called from the hit test handlers.
			Data is packaged into HitTestEventData class to be sent to ProcessEvent in IDrwEvtHandler.
			@param eventID IN the event ID being executed - see DocumentContextID.h in kMessageIDSpace
			@param changedBy IN who is dispatching this event
			@param gd IN current graphic data in place
			@param r IN the hit rectangle
			@param thingHit INOUT the UIDRef of the thing that is hit
			@param flags IN see IShape.h for the drawing flags
			@param isHit INOUT bool16 kTrue if the thing is hit, kFalse otherwise
			@param pVisitable IN pointer to IVisitorHelper
			@param theVisitor IN pointer to IBaseVisitor
			@return bool16 - kTrue if the handler handled the event and the calling code should not continue, kFalse otherwise
		*/
		virtual bool16 ProcessHitTestEvent(ClassID eventID, IPMUnknown *changedBy, GraphicsData* gd, const PMRect &r, UIDRef* thingHit, int32 flags, bool16 *isHit, 
									IVisitorHelper *pVisitable, IBaseVisitor *theVisitor) = 0;
		
		/** Propigate event throughout the registered handlers - this version called from Inval handlers.
			Data is packaged into InvalEventData class to be sent to ProcessEvent in IDrwEvtHandler.
			@param eventID IN the event ID being executed - see DocumentContextID.h in kMessageIDSpace
			@param changedBy IN who is dispatching this event
			@param gd IN current graphic data in place
			@param reasonForInval IN ClassID of the reason for invalidation
			@param flags IN see IShape.h for the drawing flags
			@return bool16 - kTrue if the handler handled the event and the calling code should not continue, kFalse otherwise
		*/
		virtual bool16 ProcessInvalEvent(ClassID eventID, IPMUnknown *changedBy, GraphicsData *gd, ClassID reasonForInval, int32 flags) = 0;
		
		/** Propigate event throughout the registered handlers - this version called from the iterate draw order handler.
			Data is packaged into IterateEventData class to be sent to ProcessEvent in IDrwEvtHandler.
			@param eventID IN the event ID being executed - see DocumentContextID.h in kMessageIDSpace
			@param changedBy IN who is dispatching this event
			@param xform IN current transformation
			@param callbackInfo IN pointer to ICallback interface
			@param flags IN see IShape.h for the drawing flags
			@return bool16 - kTrue if the handler handled the event and the calling code should not continue, kFalse otherwise
		*/
		virtual bool16 ProcessIterateEvent(ClassID eventID, IPMUnknown *changedBy, /*const PMMatrix *xform,*/ ICallback *callbackInfo, int32 flags) = 0;
		
		/** Get the bounding box for the event. Data is packaged into GetBBoxEventData class to be sent to ProcessEvent in IDrwEvtHandler.
			@param eventID IN the event ID being executed - see DocumentContextID.h in kMessageIDSpace
			@param changedBy IN who is dispatching this event
			@param gd IN current graphic data in place
			@param bBox INOUT the bounding box for the event
			@return bool16 - kTrue if the handler handled the event and the calling code should not continue, kFalse otherwise
		*/
		virtual bool16 ProcessGetBBoxEvent(ClassID eventID, IPMUnknown *changedBy, GraphicsData *gd, PMRect* bBox) = 0;
		
		/**	Loop through service registry registering sericeID handlers.
			@param serviceID IN service ID to register
		 */
		virtual void RegisterDrawEventServices(ServiceID serviceID) = 0;

		/**	Loop through service registry unregistering sericeID handlers.
			@param serviceID IN service ID to unregister
		 */
		virtual void UnRegisterDrawEventServices(ServiceID serviceID) = 0;

		/** Removes all handlers from the table.
		*/
		virtual void Shutdown() = 0;
};

#endif

