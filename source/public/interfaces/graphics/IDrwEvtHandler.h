//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrwEvtHandler.h $
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
//  If someone wants to process draw events, they must provide an implemenation
//  of this interface. The Register()/UnRegister will allow them to install/uninstall
//  themselves into the draw event dispatcher. The HandleEvent() method gets called
//  when the event they've register for happens. This header file also defines the
//  event data which is passed to HandleEvent().
//  
//========================================================================================

#pragma once
#ifndef __IDrwEvtHandler__
#define __IDrwEvtHandler__

class IPMUnknown;
class IDrwEvtDispatcher;
class GraphicsData;
class PMRect;
class UIDRef;
class PMMatrix;
class ICallback;
class IVisitorHelper;
class IBaseVisitor;

/**
 Any draw event handler must supply the following three routines. Register is
 called so the handler can register for particular draw events using the 
 RegisterHandler() method in IDrwEvtDispatcher.h. UnRegister is the reverse
 of Register. HandleEvent is called when the event happens. If the handler
 returns true from HandleEvent, it is assumed the event has been handled, and
 lower priority handlers will not be called. 
 @see IDrwEvtDispatcher
*/
class IDrwEvtHandler : public IPMUnknown
{
	public:
		/** Install self to handle events.
			@param eventDispatcher IN the IDrwEvtDispatcher to handle the event
		*/
		virtual void Register(IDrwEvtDispatcher * eventDispatcher) = 0;

		/** Uninstall self to handle events - reverse of Register
			@param eventDispatcher IN the IDrwEvtDispatcher to unregister
		*/
		virtual void UnRegister(IDrwEvtDispatcher * eventDispatcher) = 0;

		/** Take care of event that has been registered for.
			@param eventID IN the event ID you are registering for - see DocumentContextID.h in kMessageIDSpace
			@param eventData IN event data in the form of a subclass of CDrawEventData depending on what the event is.
			For example, Draw events will be passed DrawEventData, Hit test events will be passed HitTestEventData,
			Inval events will be passed InvalEventData, Iterate events will be passed IterateEventData and 
			Get BBox events will be passed GetBBoxEventData.
		*/
		virtual bool16 HandleDrawEvent(ClassID eventID, void *eventData) = 0;
};

/** Common parent data class for draw/hittest/inval/iterate events:
	(provided so a common handler can get access to the common members).
*/
class CDrawEventData {
public:
	/** Who is dispatching this event.
	*/
	IPMUnknown *changedBy;
	/**	See IShape.h for the drawing flags.
	*/
	int32 flags;
	
	/** constructor
		@param c IN who is dispatching this event
		@param f IN see IShape.h for the drawing flags
	*/
	CDrawEventData(IPMUnknown *c, int32 f) : 
		changedBy(c),
		flags(f)
	{}
};

/** Data class for Draw Events.
*/
class DrawEventData : public CDrawEventData {
public:
	/** Current graphic data in place.
	*/
	GraphicsData *gd;

	/** constructor
		@param c IN who is dispatching this event
		@param g IN current graphic data in place
		@param f IN see IShape.h for the drawing flags
	*/
	DrawEventData(IPMUnknown *c, GraphicsData* g, int32 f) :
		CDrawEventData(c, f),
		gd(g)
	{}
};

/** Data class for Hit Test Events.
*/
class HitTestEventData : public CDrawEventData {
public:
	/** Current graphic data in place.
	*/
	GraphicsData* hitTestEventGraphicsData;

	/**	The hit rectangle.
	*/
	const PMRect &hitTestEventTestRect;

	/**	The UIDRef of the thing that is hit
	*/
	UIDRef* hitTestEventItemHit;

	/**	Boolean kTrue if the thing is hit, kFalse otherwise.
	*/
	bool16 *hitTestEventIsHit;

	/**	Pointer to IVisitorHelper.
	*/
	IVisitorHelper* pVisitable; 

	/**	Pointer to IBaseVisitor.
	*/
	IBaseVisitor* theVisitor;

	/** constructor
		@param c IN who is dispatching this event
		@param g IN current graphic data in place
		@param x IN the hit rectangle
		@param t INOUT the UIDRef of the thing that is hit
		@param f IN see IShape.h for the drawing flags
		@param b INOUT bool16 kTrue if the thing is hit, kFalse otherwise
		@param h IN pointer to IVisitorHelper
		@param v IN pointer to IBaseVisitor
	*/
	HitTestEventData(IPMUnknown *c, GraphicsData* g, const PMRect &x, UIDRef* t, int32 f, bool16 *b,
					IVisitorHelper* h, IBaseVisitor* v) :
		CDrawEventData(c, f),
		hitTestEventGraphicsData(g),
		hitTestEventTestRect(x),
		hitTestEventItemHit(t),
		hitTestEventIsHit(b),
		pVisitable(h),
		theVisitor(v)
	{}
};

/** Data class for Inval Events
*/
class InvalEventData : public CDrawEventData {
public:
	/** Current graphic data in place.
	*/
	GraphicsData* gd;
	/**	ClassID of the reason for invalidation.
	*/
	ClassID reasonForInval;

	/** constructor
		@param c IN who is dispatching this event
		@param g IN current graphic data in place
		@param r IN ClassID of the reason for invalidation
		@param f IN see IShape.h for the drawing flags
	*/
	InvalEventData(IPMUnknown *c, GraphicsData *g, ClassID r, int32 f) :
		CDrawEventData(c, f),
		gd(g),
		reasonForInval(r)
	{}
};

/** Data class for Iterate Events
*/
class IterateEventData : public CDrawEventData {
public:
	/** Current transformation.
	*/
//	const PMMatrix* xform_ied;


	/**	Pointer to ICallback interface.
	*/
	ICallback* callbackInfo;



	/** constructor
		@param c IN who is dispatching this event
		@param m IN current transformation
		@param cbInfo IN pointer to ICallback interface
		@param flags IN see IShape.h for the drawing flags
	*/
	IterateEventData( IPMUnknown *c, /*const PMMatrix *m,*/ ICallback *cbInfo, int32 f) :
		CDrawEventData(c, f),
//		xform_ied(m),
		callbackInfo(cbInfo)
	{}
};

/** Data class for Get BBox events
*/
class GetBBoxEventData : public CDrawEventData {
public:
	/** Current graphic data in place.
	*/
	GraphicsData* gd;
	/**	The bounding box for the event.
	*/
	PMRect *bBox;

	/** constructor
		@param c IN who is dispatching this event
		@param g IN current graphic data in place
		@param b INOUT the bounding box for the event
	*/
	GetBBoxEventData(IPMUnknown *c, GraphicsData* g, PMRect *b) :
		CDrawEventData(c, 0),
		gd(g),
		bBox(b)
	{}
};

#endif

