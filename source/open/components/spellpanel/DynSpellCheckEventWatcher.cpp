//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/DynSpellCheckEventWatcher.cpp $
//  
//  Owner: Heath Horton
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

#include "IApplication.h"
#include "ICursorMgr.h"
#include "IEvent.h"
#include "IEventWatcher.h"
#include "IIdleTask.h"
#include "IIdleTaskMgr.h"
#include "IIntData.h"
#include "IRangeData.h"
#include "ISession.h"
#include "IWorkspace.h"

//#include "CIdleKeyWatcher.h"
//#include "CIdleTask.h"
#include "EventUtilities.h"
#include "keyboarddefs.h"
#include "PMTextUtils.h"
#include "SpellPanelID.h"
#include "SystemUtils.h"

//----------------------------------------------------------------------------------------
// CLASS DynamicSpellCheckKeyWatcher 
//----------------------------------------------------------------------------------------
class  DynamicSpellCheckKeyWatcher : public CPMUnknown<IEventWatcher> //CIdleKeyWatcher
{
public:
	DynamicSpellCheckKeyWatcher(IPMUnknown *boss);
	virtual ~DynamicSpellCheckKeyWatcher();

	IEventDispatcher::EventTypeList WatchEvent(IEvent* e);		
	void StartWatching();
	void StopWatching();

	//virtual uint32 KeyPressed();

private:
//	bool16 fInView;
	bool16 fWatching;
};

CREATE_PMINTERFACE(DynamicSpellCheckKeyWatcher, kDynamicSpellCheckKeyEventWatcherImpl)

DynamicSpellCheckKeyWatcher::DynamicSpellCheckKeyWatcher(IPMUnknown *boss) : 
	//CIdleKeyWatcher(boss)
	CPMUnknown<IEventWatcher>(boss), 
		fWatching(kFalse)//, 	
		//fOldHilite(kInvalidIndex)
{}

DynamicSpellCheckKeyWatcher::~DynamicSpellCheckKeyWatcher() 
{}

#if 0
uint32 DynamicSpellCheckKeyWatcher::KeyPressed()
{
	InterfacePtr<IApplication> app (GetExecutionContextSession()->QueryApplication());
	InterfacePtr<ICursorMgr> cursorMgr(app, IID_ICURSORMGR);
	if (!cursorMgr->IsSuspended() && !::IsMouseButtonDown())
	{
		if (!::SysPointInSysRgn(position, cursorMgr->GetCurrentRgn()))
		{
			cursorMgr->ComputeNewProvider(position);
			cursorMgr->SetNewCursor(position);				
		}
		else
		{
			if (cursorMgr->LocationAffectsProvider())
			{
				cursorMgr->ComputeNewProvider(position);
				cursorMgr->SetNewCursor(position);
			}
		}
	}
	
	return 1000/2; //call me 2 times/second
}
#endif

IEventDispatcher::EventTypeList DynamicSpellCheckKeyWatcher::WatchEvent(IEvent* e)
{
	IEventDispatcher::EventTypeList myInterest(IEvent::kKeyDown/* , IEvent::kKey, IEvent::kKeyUp */);
	
	IEvent::EventType etype = e->GetType();

	switch (e->GetType())
	{
		case IEvent::kKeyDown:
			break;
		/* case IEvent::kKey:
			break;
		case IEvent::kKeyUp:
			break; */
		default:
			return myInterest;
	}

	if (!e->OptionAltKeyDown() && !e->CmdKeyDown() /*&& (PMCharFilters::SpellingIsWordChar(c,c) || c == kBackspaceKey || c == kDeleteKey)*/)
	{
		VirtualKey virtualKey = e->GetVirtualKey();
		if (virtualKey == kVirtualPageUpKey || virtualKey == kVirtualPageDownKey
			|| virtualKey == kVirtualHomeKey || virtualKey == kVirtualEndKey
			|| virtualKey == kVirtualUpArrowKey || virtualKey == kVirtualDownArrowKey
			|| virtualKey == kVirtualRightArrowKey || virtualKey == kVirtualLeftArrowKey)
				return myInterest;

		InterfacePtr<IIdleTask> idletask(this, UseDefaultIID());
		ASSERT_MSG(idletask, "missing my idle task" );

		InterfacePtr<IIntData> intData(this, UseDefaultIID());
		if (intData)
			intData->Set(e->GetChar());

		int32 idleTime = 1250; //750;
		idletask->UninstallTask();
	
		if (virtualKey == kVirtualTabKey || virtualKey == kVirtualSpaceKey)
		{
			idleTime = 0;	/* if the user typed a space, go ahead and fire */
		}

		idletask->InstallTask(idleTime);
	}
	
	return myInterest;
}

void DynamicSpellCheckKeyWatcher::StartWatching()
{
	if (fWatching) 
		return;
	
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IEventDispatcher> dispatcher(app, UseDefaultIID());
	if (dispatcher)
	{
		IEventDispatcher::EventTypeList myInterest(IEvent::kKeyDown/* , IEvent::kKey, IEvent::kKeyUp */);
		dispatcher->AddEventWatcher(this, myInterest);
		fWatching = kTrue;

		InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
		InterfacePtr<IRangeData> rangeData(ws, IID_IDYNAMICSPELLINGRANGEDATA);
		rangeData->Set(kInvalidTextIndex, kInvalidTextIndex);
	}
}


void DynamicSpellCheckKeyWatcher::StopWatching()
{
	if (!fWatching) 
		return;

	/* Remove the idle task */
	InterfacePtr<IIdleTask> idletask(this, UseDefaultIID());
	idletask->UninstallTask();

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IEventDispatcher> dispatcher(app, UseDefaultIID());
	if (dispatcher)
	{
		fWatching = kFalse;
		dispatcher->RemoveEventWatcher(this, IEventDispatcher::EventTypeList());
	}
}


