//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelDrawHandler.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IDrwEvtHandler.h"
#include "IDrwEvtDispatcher.h"
#include "IDocument.h"
#include "IHierarchy.h"
#include "IShape.h"
#include "ISpread.h"
#include "IDrawMgr.h"
#include "IPMPersist.h"
#include "IDataBase.h"
#include "IActiveContext.h"

// Implementation Includes
#include "CPMUnknown.h"
#include "DocumentContextID.h"
#include "ILayoutUtils.h"

// Project includes:
#include "PrnSelID.h"
#include "IPrnSelSuite.h"
#include "IPrnSelData.h"



/** Implements the code necessary to process draw events.
	Register()/UnRegister() allows install/uninstall into 
	the draw event dispatcher. HandleEvent() is called when 
	the event registered for happens.

	PrnSelDrawHandler implements IDrwEvtHandler.

	
	@ingroup printselection
*/
class PrnSelDrawHandler : public CPMUnknown<IDrwEvtHandler>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on 
			which this interface is aggregated.
		*/
		PrnSelDrawHandler(IPMUnknown* boss);

		/**
			Destructor.
		*/
		virtual ~PrnSelDrawHandler() {}
		
		/**
		Called so handler can register for particular draw events 
		using the RegisterHandler() method in IDrwEvtDispatcher.
		@param eventDispatcher (in) specifies active draw event dispatcher.
		*/
		virtual void Register(IDrwEvtDispatcher* eventDispatcher);
		
		/**
		Called so handler can unregister for particular draw events 
		using the UnRegisterHandler() method in IDrwEvtDispatcher.
		Not actually necessary since all handlers get unregistered 
		automatically at quit time, but it is good form.
		@param eventDispatcher (in) specifies active draw event dispatcher.
		*/
		virtual void UnRegister(IDrwEvtDispatcher* eventDispatcher);
		
		/**
		If event handled here, return kTrue and the item should 
		not be drawn.  Else event not handled here, return kFalse 
		and continue drawing item.
		@param eventID (in) specifies ID of the specific event.
		@param eventData (in) specifies pointer to the draw event data.
		In this case, we are being passed a UIDRef of the spread
		to be printed.
		*/
		virtual bool16 HandleDrawEvent(ClassID eventID, void* eventData);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelDrawHandler, kPrnSelDrawHandlerImpl)


/* Constructor
*/
PrnSelDrawHandler::PrnSelDrawHandler(IPMUnknown* boss) 
	: CPMUnknown<IDrwEvtHandler>(boss)
{
}


/* Register
*/
void PrnSelDrawHandler::Register(IDrwEvtDispatcher* eventDispatcher)
{
	eventDispatcher->RegisterHandler(
		kDrawShapeMessage, this, kDEHLowestPriority);
}


/* UnRegister
*/
void PrnSelDrawHandler::UnRegister(IDrwEvtDispatcher* eventDispatcher)
{
	eventDispatcher->UnRegisterHandler(
		kDrawShapeMessage, this);
}


/* HandleEvent
*/
bool16 PrnSelDrawHandler::HandleDrawEvent(
	ClassID eventID, void* eventData)
{
	bool16 bHandled = kFalse;

	do
	{
		// Make sure this is a kDrawShapeMessage.
		if (eventID.Get() != kDrawShapeMessage)
		{
			break;
		}

		DrawEventData* ed = static_cast<DrawEventData*>(eventData);
		ASSERT(ed);

		// Make sure we are printing.
		if ((ed->flags & IShape::kPrinting) == 0)
		{
			break;
		}

		// We are in the unfortunate position of having to get the
		// active context out of the blue here.
		InterfacePtr<IActiveContext> ac
			(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (ac == nil)
		{
			break;
		}

		// Get our document.
		InterfacePtr<IDocument> 
			doc(ac->GetContextDocument(), UseDefaultIID());
		if (doc == nil)
		{
			break;
		}

		// Get our data interface
		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		ASSERT(psData);
		if (psData == nil)
		{
			break;
		}

		// Unless the page item to be drawn here matches one of
		// our stored UIDs, we will say we handled this draw event.
		// The effect will be that unselected page items do not draw(print).
		bHandled = kTrue;
		UID uid2Test = ::GetUID(ed->changedBy) - 1;
		if (psData->GetPageItemUIDHadSelection(::GetUID(ed->changedBy)))
		{
			bHandled = kFalse;
		}

		if (psData->GetPageUIDHadSelection(::GetUID(ed->changedBy)))
		{
			bHandled = kFalse;
		}
	} while(0);

	return bHandled;
}

// End, PrnSelDrawHandler.cpp.

