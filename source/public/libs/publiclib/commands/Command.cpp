//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/commands/Command.cpp $
//  
//  Owner: Robin_Briggs
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
//  To be done:
//  Command names fixed to be localizable.
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "Command.h"
#include "ErrorUtils.h"
#include "IApplication.h"
#include "ICommandMgr.h"
#include "IWorkspace.h"

#ifdef ID_ENABLE_DEBUGGING
#include "TestID.h"
#include "Trace.h"
#include "DebugClassUtils.h"
#include "LogObject.h"
#include "PMLocaleId.h"
#include "PMLocaleIds.h"
#include "ICmdCollection.h"
#include "ICommandCoverage.h"
#include "PreferenceUtils.h"
#include "IBoolData.h"
#include "IDThreading.h"
#include "IClassInfo.h"
PUBLIC_DECL IDThreading::ThreadLocal<LogObject*> tl_CommandLog(nil);
#endif

DEFINE_HELPER_METHODS(Command)

Command :: Command(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fItemList(),
	fCommandState(kNotDone),
	fName(nil),
	fCreatorID(0),
	fUndoability(kRegularUndo),
	fTarget(),
	fIsActive(kTrue),
	fIsLWProcessed(kFalse)
{}

Command :: ~Command()
{ 
    fItemList.Release();
	if (fName)
		delete fName;
}

void Command :: DoImmediate(bool16 isDynamic)
{
	if (fIsActive)
	{
		if (isDynamic)
		{
			DoDynamic();
			SetCommandState(ICommand::kDoneDynamic);
			// DoNotify(); // [RCR] We should do this here, and remove it from all the commands
		}
		else
		{
#ifdef ID_ENABLE_DEBUGGING
			LogCommand( kDo ) ;
			if (tl_CommandLog.Get()) tl_CommandLog.Get()->Indent();
			Undoability beforeDoUndoability = GetUndoability();
#endif

			Do();
#ifdef ID_ENABLE_DEBUGGING
			ASSERT_MSG(beforeDoUndoability == GetUndoability(),
						"Must set command undoability before starting command processing");
#endif
			if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
			{
				SetCommandState(ICommand::kDone);
				#ifdef ID_ENABLE_DEBUGGING
					if (tl_CommandLog.Get()) tl_CommandLog.Get()->Prepend("> ");
				#endif
				DoNotify();

				#ifdef ID_ENABLE_DEBUGGING
					if (tl_CommandLog.Get()) tl_CommandLog.Get()->RemovePrepend();
				#endif
			}
#ifdef ID_ENABLE_DEBUGGING
			if (tl_CommandLog.Get()) tl_CommandLog.Get()->UnIndent();
#endif
		}
	}
	else
	{
		#ifdef ID_ENABLE_DEBUGGING
			if (tl_CommandLog.Get()) tl_CommandLog.Get()->Prepend("> ");
		#endif

		DoNotify();

		#ifdef ID_ENABLE_DEBUGGING
			if (tl_CommandLog.Get()) tl_CommandLog.Get()->RemovePrepend();
		#endif
	}
}
	
// DEPRICATED
// Avoid using this function if possible - this is legacy and is deprecated.
void Command :: DoDynamic()
{
	ASSERT_FAIL("This is not a dynamic command!");
}

ICommand::CommandState Command::GetCommandState() const
{
	return fCommandState;
}

void Command::SetCommandState(CommandState state)
{
#ifdef DEBUG
	// -- Currently we're not handling the kDoneDynamic case.  Should that be added? [LDM]
	if (state == ICommand::kNotDone)
		PreVerify(state);
	else if (state == ICommand::kDone)
		PostVerify(state);
#endif
	fCommandState = state;
}

void Command::DoNotify()
{}

bool16 Command::IsDone() const
{
	return (fCommandState == kDone || fCommandState == kDoneDynamic);
}

void Command :: SetName(const PMString& name)		
{ 
	if (!fName)
		fName = new PMString();
	*fName = name;
}

void Command :: GetName(PMString *name)	const
{ 
	if (!fName)
		fName = const_cast <Command*> (this)->CreateName();
	ASSERT_MSG(name != nil, "Command :: GetName - name != nil");
	if (name)	{
		if (fName != nil)
			*name = *fName;
		else
			*name = PMString();
		}
}
	
bool16 Command :: IsNameRequired() const
{ 
	return GetUndoability() == kRegularUndo;
}

const UIDList *Command :: GetItemList() const
{ 
//	InterfacePtr<IItemListData> listData((Command*)this, IID_IITEMLISTDATA);
//	if (listData != nil)
//		return listData->GetItemList();
	return fItemList.GetDataBase() ? &fItemList : NULL;
}

const UIDList &Command :: GetItemListReference() const
{
	return fItemList;
}

 


void Command :: SetItemList(const UIDList &newItemList)
{
	//if(newItemList != fItemList)
	//{
		fItemList.Release();
		fItemList = newItemList;
	//}
}


PMString *Command :: CreateName()
{
#ifdef ID_ENABLE_DEBUGGING
	// BP 06/09/03: Assert "CmdHistory::GetNthUndoStepName(): Missing command name..."
	DebugClassUtilsBuffer classIDName;
	DebugClassUtils::GetIDName( &classIDName, ::GetClass(this), kTrue );
#endif

	return nil;
}


// -------------------------------------------------------------
// Command::CanJoin
// -------------------------------------------------------------
bool16 Command::CanJoin(  const ICommand *pNewCmd ) const
{
	return kFalse;
}

void  Command::SetCreatorID(int32 creatorID)
{
	fCreatorID = creatorID;
}

int32  Command::GetCreatorID() const
{
	return fCreatorID;
}

bool16 Command::LowMemIsOK() const
{
	return kTrue;
}

const ICommand::Target &Command :: GetTarget() const
{
	if(fTarget == UIDRef::gNull)
	{
		const_cast <Command*> (this)->SetUpTarget();
	
#ifdef ID_ENABLE_DEBUGGING
		if(fTarget.GetDataBase() == nil)
		{
			char cmdString[256];	
			ClassID theClass = ::GetClass(this);
			InterfacePtr<IObjectModel> om(GetExecutionContextSession(), IID_IOBJECTMODEL);	
			const char* cmdName= (const char*)om->GetIDName(theClass);	
			if(cmdName)
				sprintf(cmdString, "Command::SetUpTarget(): Command '%s' failed to set up its target", cmdName);
			else
				sprintf(cmdString, "Command::SetUpTarget(): Command 0x%x failed to set up its target", theClass.Get());

			ASSERT_FAIL(cmdString);
		}
#endif // ID_ENABLE_DEBUGGING
	}
	
	return fTarget;
}

void Command :: SetTarget(IDataBase *db)
{
	ASSERT_MSG(db != nil, "Command::SetTarget(): nil db pointer");
	
	SetTarget(UIDRef(db, db->GetRootUID()));
}

void Command :: SetTarget(const ICommand::Target &newTarget)
{
	ASSERT_MSG(fCommandState < kDone, "Command :: SetTarget(): target can't be changed after the command already has been done");
	
	if(fCommandState < kDone)
		fTarget = newTarget;
		
#ifdef DEBUG
	ClassID clsID = newTarget.GetDataBase()->GetClass(newTarget.GetUID());
	InterfacePtr<IObjectModel> om(GetExecutionContextSession(), IID_IOBJECTMODEL);
	InterfacePtr<IClassInfo> classInfo (om->QueryClassInfo(clsID));
	if (classInfo)
	{
		ImplementationID cmdMgrImplID = classInfo->GetImplementation(IID_ICOMMANDMGR);
		ASSERT_MSG(cmdMgrImplID != kInvalidImpl, "Command:SetTarget(): target has no commandmgr interface");
	}
#endif
}

void Command :: SetTarget(Command::PredefinedTarget newTarget) 
{
	switch(newTarget)
	{		
		case kSessionWorkspaceTarget:
		{
			InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
			if(ws != nil)
			{
				InterfacePtr<ICommandMgr> cmdMgr(ws, IID_ICOMMANDMGR);
				SetTarget(::GetUIDRef(cmdMgr));
				break;
			}
		}
		
		// fall thru (Hack Roey 3/18/99):
		// If we are called during workspace creation GetExecutionContextSession()->QueryWorkspace() will
		// not work. Since undo is turned off anyway during workspace creation we simply
		// use the session target instead.
		
		case kSessionTarget:
		{
			InterfacePtr<ICommandMgr> cmdMgr(GetExecutionContextSession(), IID_ICOMMANDMGR);
			if (cmdMgr)
				SetTarget(::GetUIDRef(cmdMgr));
			else
			{
				ASSERT_MSG(!IDThreading::IsMainThreadDomain(),"Main thread session expected to have a command mgr");
				InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
				if(ws != nil)
				{
					InterfacePtr<ICommandMgr> wsCmdMgr(ws, IID_ICOMMANDMGR);
					SetTarget(::GetUIDRef(wsCmdMgr));
				}
			}
		}
		break;
	}
}

void Command :: SetUpTarget()
{
	IDataBase *db = GetItemListReference().GetDataBase();

	if(db != nil)
		SetTarget(db);
}

ICommand::Undoability Command :: GetUndoability() const
{
	return fUndoability;
}

void Command :: SetUndoability(ICommand::Undoability newUndoability)
{
	ASSERT_MSG(fCommandState == kNotDone, 
				"Must set command undoability before starting command processing");
	bool16 validChange = fCommandState == kNotDone;
	
	if(validChange)
		fUndoability = newUndoability;
}

void Command::SetActive(bool16 isActive)
{
	fIsActive = isActive;
}
	
bool16 Command::IsActive() const
{
	return fIsActive;
}
	
void Command::PreVerify(CommandState state)
{
	// -- does nothing in the default case.
}

void Command::PostVerify(CommandState state)
{
	// -- does nothing in the default case.
}

void Command::LWDoImmediate()
{
	ASSERT (fIsActive);
	fIsLWProcessed = kTrue;
#ifdef ID_ENABLE_DEBUGGING
	LogCommand( kDo ) ;
	if (tl_CommandLog.Get()) tl_CommandLog.Get()->Indent();
#endif
	Do();
	if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
	{
		SetCommandState(ICommand::kDone);
	}
#ifdef ID_ENABLE_DEBUGGING
	if (tl_CommandLog.Get()) tl_CommandLog.Get()->UnIndent();
#endif
}

bool8 Command::IsLWProcessed() const
{
	return fIsLWProcessed;
}

#ifdef ID_ENABLE_DEBUGGING
static IDThreading::ThreadLocal<bool16> tl_newLog(kTrue);

void Command::LogCommand( Action act )
{
	//This method will log the command to one or more of
	//	the command coverage tracker
	//	a log file ShuksanCommandLog.txt
	//	trace target(s)

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	ICommandCoverage* cover = nil;
	//cannot access the session workspace until the session has initialized
	if (GetExecutionContextSession()->GetState() == ISession::kRunning)
		cover = (ICommandCoverage*)::QuerySessionPreferences(IID_ICOMMANDCOVERAGE);
		
	ClassID cmdClass = ::GetClass( this ) ;
	ConstCString action = "" ;

	switch ( act )
	{
	case kDo :
		action = "Doing" ;
		if ( cover ) cover->Done( cmdClass ) ;
		break ;
	case kDoAbsolutelyNothing :
	default :
		break ;
	}

	if (cover)
		cover->Release();
	
	ConstCString undoability = "" ;
	switch ( GetUndoability() )
	{
	case kAutoUndo :
		undoability = "AutoUndoWithPrevious" ;
		break ;
	case kRegularUndo :
		undoability = "RegularUndo" ;
	default :
		break ;
	}

	PMString name ;
	GetName(&name);

	//if ILOGPREFS == kTrue, then we don't do logging
	InterfacePtr<IBoolData> prefs(app, IID_ILOGBOOLPREFS);
	if ( tl_CommandLog.Get() == nil && prefs && prefs->GetBool() == kFalse)
	{
		char fileNameBuf[1024];
		const IDThreading::ExecutionContextID ecId = IDThreading::CurrentExecutionContextId();

		sprintf (fileNameBuf,"ShuksanCommandLog%d.txt", ecId);
		tl_CommandLog.Set(new LogObject( fileNameBuf, tl_newLog.Get())) ; 
	}

	if ( tl_CommandLog.Get() && prefs && prefs->GetBool() == kTrue)
	{
		tl_CommandLog.Get()->SetWriteTrailer(kFalse);
		delete tl_CommandLog.Get();
		tl_CommandLog.Set(nil);
		tl_newLog.Set(kFalse);
	}

	UID itemUid = 0;
	if (GetItemListReference().Length() > 0)
		itemUid = (GetItemListReference())[0].Get();

	DebugClassUtilsBuffer buf;
	if ( tl_CommandLog.Get() && prefs && prefs->GetBool() == kFalse)
	{
		tl_CommandLog.Get()->WriteLog( kTrue, "%s command %s (%s) this=0x%.8x uid[0]=%.4d %s", action, name.GetUTF8String().c_str(),
							   DebugClassUtils::GetIDName( &buf,cmdClass ), this, itemUid.Get(), undoability ) ;
	}

	TRACEFLOW(kInterfaceSnapshotTrace, "%s command %s (%s) this=0x%.8x uid[0]=%.4d %s\n", action, name.GetUTF8String().c_str(),
							   DebugClassUtils::GetIDName( &buf,cmdClass ), this, itemUid.Get(), undoability );

	TRACEFLOW("Command Log", "%s command %s (%s) this=0x%.8x uid[0]=%.4d %s\n", action, name.GetUTF8String().c_str(),
							   DebugClassUtils::GetIDName( &buf,cmdClass ), this, itemUid.Get(), undoability ) ;
}

#endif
