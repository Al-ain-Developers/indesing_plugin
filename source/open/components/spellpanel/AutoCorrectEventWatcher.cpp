//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectEventWatcher.cpp $
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
#include "IDialogMgr.h"
#include "IEvent.h"
#include "IEventHandler.h"
#include "IEventWatcher.h"
#include "IIdleTask.h"
#include "IIntData.h"
#include "IKeyBoard.h"
#include "IRangeData.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "ITextEditor.h"
#include "ITextMiscellanySuite.h"
#include "IWorkspace.h"
#include "ITextLines.h"

#include "keyboarddefs.h"
#include "SpellPanelID.h"


//----------------------------------------------------------------------------------------
// CLASS AutoCorrectKeyWatcher 
//----------------------------------------------------------------------------------------
class  AutoCorrectKeyWatcher : public CPMUnknown<IEventWatcher> //CIdleKeyWatcher
{
public:
	AutoCorrectKeyWatcher(IPMUnknown *boss);
	virtual ~AutoCorrectKeyWatcher();

	IEventDispatcher::EventTypeList WatchEvent(IEvent* e);		
	void StartWatching();
	void StopWatching();

private:
	bool16 fWatching;
};

CREATE_PMINTERFACE(AutoCorrectKeyWatcher, kAutoCorrectKeyEventWatcherImpl)

AutoCorrectKeyWatcher::AutoCorrectKeyWatcher(IPMUnknown *boss) : 
	CPMUnknown<IEventWatcher>(boss), 
		fWatching(kFalse)
{}

AutoCorrectKeyWatcher::~AutoCorrectKeyWatcher() 
{}

IEventDispatcher::EventTypeList AutoCorrectKeyWatcher::WatchEvent(IEvent* e)
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
	
    InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(theApp, UseDefaultIID());
	if (dialogMgr && dialogMgr->IsModalDialogOpen())
		return myInterest;

	InterfacePtr<IKeyBoard> theKeyBoard(theApp, UseDefaultIID());
    if (!theKeyBoard)
		return myInterest;
    IEventHandler* currentFocus = theKeyBoard->GetKeyFocus();
	InterfacePtr<ITextEditor> editor(currentFocus, UseDefaultIID());
	InterfacePtr<ITextLines> galleyTypeView(currentFocus, UseDefaultIID());

	if (!editor && !galleyTypeView)
		return myInterest;

	if (!e->OptionAltKeyDown() && !e->CmdKeyDown())
	{
		VirtualKey virtualKey = e->GetVirtualKey();
		if (virtualKey == kVirtualPageUpKey || virtualKey == kVirtualPageDownKey
			|| virtualKey == kVirtualHomeKey || virtualKey == kVirtualEndKey
			|| virtualKey == kVirtualUpArrowKey || virtualKey == kVirtualDownArrowKey
			|| virtualKey == kVirtualRightArrowKey || virtualKey == kVirtualLeftArrowKey)
			return myInterest;
		
		InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
		InterfacePtr<ITextMiscellanySuite> textMiscellanySuite(static_cast<ITextMiscellanySuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ITEXTMISCELLANYSUITE, selectionManager)));
		if (textMiscellanySuite)
		{
			textMiscellanySuite->SetWorkSpaceTypingRangeData(e->GetChar(), IID_IAUTOCORRECTRANGEDATA);
		}

		InterfacePtr<IIdleTask> idletask(this, UseDefaultIID());
		ASSERT_MSG(idletask, "missing my idle task" );

		InterfacePtr<IIntData> intData(this, UseDefaultIID());
		if (intData)
			intData->Set(e->GetChar());

		int32 idleTime = 3000;
		//idletask->UninstallTask();
	
		if (virtualKey == kVirtualReturnKey || virtualKey == kVirtualTabKey || virtualKey == kVirtualSpaceKey
			|| virtualKey.GetChar() == ',' || virtualKey.GetChar() == '.'
			|| virtualKey.GetChar() == 0x002f || virtualKey.GetChar() == '?'
			)
		{
			idleTime = 0;	/* if the user typed a space, go ahead and fire */
			idletask->UninstallTask();
			idletask->InstallTask(idleTime);
		}

		//idletask->InstallTask(idleTime);
	}
	
	return myInterest;
}

void AutoCorrectKeyWatcher::StartWatching()
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
		InterfacePtr<IRangeData> rangeData(ws, IID_IAUTOCORRECTRANGEDATA);
		rangeData->Set(kInvalidTextIndex, kInvalidTextIndex);
	}
}


void AutoCorrectKeyWatcher::StopWatching()
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


