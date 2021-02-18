//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapSetPrefsCmd.cpp $
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
//  
//  Command to set Snanpshot Tool's preferences. Snapshot tool uses one set of global
//  preferences stored in the session workspace in interface ISnapPrefsData.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes
#include "ISubject.h"
#include "ISession.h"
#include "IWorkspace.h"

// General includes
#include "ErrorUtils.h"
#include "PreferenceUtils.h"
#include "Command.h"

// SnapSetPrefsCmd includes
#include "ISnapPrefsData.h"
#include "SnapID.h"

/**	SnapSetPrefsCmd
	
	  Custom command to set the preference for various image write format. This command does not use the itemlist,
	  and the target is always the session's workspace.
	  
	  @ingroup snapshot
*/
class SnapSetPrefsCmd : public Command
{
	public:
		/**
			Constructor.
		*/
		SnapSetPrefsCmd(IPMUnknown* boss);

	protected:
		void Do();
		void DoNotify();
		PMString* CreateName();
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SnapSetPrefsCmd, kSnapSetPrefsCmdImpl)


/* Constructor.
*/
SnapSetPrefsCmd::SnapSetPrefsCmd(IPMUnknown* boss) :
	Command(boss)
{
	SetTarget(kSessionWorkspaceTarget);
}

/* Do
*/
void SnapSetPrefsCmd::Do()
{
	ErrorCode status = kFailure;

	do
	{
		// Acquire the new preference data
		InterfacePtr<ISnapPrefsData> newData(this, UseDefaultIID());
		if (newData == nil)
		{
			ASSERT_FAIL("newData invalid");
			break;
		}
		
		// Acquire the current preference data and save its state	
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (workspace == nil)
		{
			ASSERT_FAIL("workspace invalid");
			break;
		}
		InterfacePtr<ISnapPrefsData> snapPrefsData(workspace, UseDefaultIID());
		if (snapPrefsData == nil)
		{
			ASSERT_FAIL("snapPrefsData invalid");
			break;
		}

   		// Update state
   		snapPrefsData->SetName(newData->GetName());
   		snapPrefsData->SetFormatClassID(newData->GetFormatClassID());
   		snapPrefsData->SetScale(newData->GetScale());
   		snapPrefsData->SetResolution(newData->GetResolution());
    	snapPrefsData->SetMinimumResolution(newData->GetMinimumResolution());  
   		snapPrefsData->SetBleed(newData->GetBleed());
   		snapPrefsData->SetDrawArea(newData->GetDrawArea());
    	snapPrefsData->SetFullResolutionGraphics(newData->GetFullResolutionGraphics());  
    	snapPrefsData->SetDrawGray(newData->GetDrawGray());  
    	snapPrefsData->SetDrawingFlags(newData->GetDrawingFlags());  
		snapPrefsData->SetJPEGEncoding(newData->GetJPEGEncoding());
		snapPrefsData->SetJPEGQuality(newData->GetJPEGQuality());
		snapPrefsData->SetTIFFPaletteType(newData->GetTIFFPaletteType());
		snapPrefsData->SetGIFPaletteType(newData->GetGIFPaletteType());
		snapPrefsData->SetTIFFTransparent(newData->GetTIFFTransparent());
		snapPrefsData->SetGIFTransparent(newData->GetGIFTransparent());
		snapPrefsData->SetGIFInterlaced(newData->GetGIFInterlaced());

   		status = kSuccess;
   	
	}	while (false);

	// Handle any errors
	if ( status != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(status);
	}
}

/* DoNotify
*/
void SnapSetPrefsCmd::DoNotify()
{
	do
	{
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (workspace == nil)
		{
			ASSERT_FAIL("workspace invalid");
			break;
		}
		InterfacePtr<ISnapPrefsData> snapPrefsData(workspace, UseDefaultIID());
		if (snapPrefsData == nil)
		{
			ASSERT_FAIL("snapPrefsData invalid");
			break;
		}

		InterfacePtr<ISubject> subject( workspace, UseDefaultIID());
		if (subject == nil)
		{
			ASSERT_FAIL("subject invalid");
			break;
		}
		subject->ModelChange(kSnapSetPrefsCmdBoss, IID_ISNAPPREFSDATA, this);
	} while (false);
}


/* CreateName
*/
PMString* SnapSetPrefsCmd::CreateName()
{
	PMString* str = new PMString(kCommandSnapSetPrefsCmdKey);
	return str;
}


