//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemActionComponent.cpp $
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
#include "IApplication.h"
#include "IActiveContext.h"
#include "IDocument.h"
#include "IPrintCmdData.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "LocaleSetting.h"
#include "PrintID.h"
// Project includes:
#include "PrtMemID.h"

/** Global flag to make sample quicker to write.
 * 	This flag is accessed by other components in this plug-in. 
 * 
 * 	\li If kFalse, printing to memory is disabled. 
 * 	\li If kTrue, printing to memory is enabled.
 * 
 * 	NOTE: Using a global flag like this is NOT recommended 
 * 	as general pattern for storing Print settings. 
 * 
 * 	For a recommendation on how to manage and present Printing
 * 	options, see the PrintHook and PrintHook sample plug-in set. 
 * 
 * 	@ingroup printmemorystream
*/

bool16 gPrtMemPrintingToMemory(kFalse);

/** Performs the actions that are executed when the plug-in's
 * 	menu items are selected.
 * 	@ingroup printmemorystream
*/
class PrtMemActionComponent : public CActionComponent
{
public:
	/** Constructor.
	 * 	@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	PrtMemActionComponent(IPMUnknown* boss);

	/** The action component should perform the requested action.
	 * 	This is where the menu item's action is taken.
	 * 	@see IActionComponent::DoAction
	 */
	virtual void DoAction(IActiveContext* ac, 
						  ActionID actionID, 
						  GSysPoint mousePoint = kInvalidMousePoint, 
						  IPMUnknown* widget = nil);

private:
	/** Encapsulates functionality for the about menu item. */
	void DoAbout(void);

	/** Encapsulates functionality for the PrintFront menu item. 
	 * 	This simply mimics the user selecting the File >> Print menu, 
	 * 	or pressing Ctrl/Cmd-P. 
	 */
	void DoPrintFrontDocument(IActiveContext* ac);

	/** Encapsulates functionality for the PrintToMemory menu item. 
	 * 	Enables our global flag, executes the print command, and then
	 * 	disables our global flag once again.
	 */
	void DoPrintToMemory(IActiveContext* ac);
};

// CREATE_PMINTERFACE
//	Binds the C++ implementation class onto its ImplementationID 
// 	making the C++ code callable by the application.
CREATE_PMINTERFACE(PrtMemActionComponent, kPrtMemActionComponentImpl)

/*  Constructor
*/
PrtMemActionComponent::PrtMemActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void PrtMemActionComponent::DoAction(IActiveContext* ac, 
									 ActionID actionID, 
									 GSysPoint mousePoint, 
									 IPMUnknown* widget)
{
	switch (actionID.Get())
	{
	case kPrtMemAboutActionID:
		{
			this->DoAbout();
			break;
		}
	case kPrtMemPrintToMemoryActionID:
		{
			this->DoPrintToMemory(ac);
			break;
		}
	default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void PrtMemActionComponent::DoAbout(void)
{
	CAlert::ModalAlert
		(
		kPrtMemAboutBoxStringKey,	// Alert string
		kOKString,					// OK button
		kNullString,				// No second button
		kNullString,				// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon	// Information icon.
		);
}

/* DoPrintToMemory
*/
void PrtMemActionComponent::DoPrintToMemory(IActiveContext* ac)
{
	// enable our flag - NOTE: see comment at the top of this source file.
	gPrtMemPrintingToMemory= kTrue;
	do
	{
		IDocument* document = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
		if (document == nil)
		{
			ASSERT_FAIL("There is no document to print!");
			break;
		}

		ClassID printCmdBoss = kPrintActionCmdBoss;

		if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		{
			// for InCopy, we need to use a different command. 
			printCmdBoss = kInCopyPrintActionCmdBoss;
		}

		// Process the Print command. 
		InterfacePtr<ICommand> printActionCmd(CmdUtils::CreateCommand(printCmdBoss));
		if (printActionCmd == nil)
		{
			ASSERT_FAIL("printActionCmd is nil");
			break;
		}
        InterfacePtr<IPrintCmdData> printActionCmdData(printActionCmd,  UseDefaultIID());
		if (printActionCmdData == nil)
		{
			ASSERT_FAIL("printActionCmdData is nil");
			break;
		}
		// set the document to print
		printActionCmdData->SetIDoc(document);
		// set UI options
		printActionCmdData->SetPrintUIOptions(IPrintCmdData::kSuppressFileSaveDialog);

		// execute the command (no undo info is kept)
		ErrorCode status = CmdUtils::ProcessCommand(printActionCmd);
		ASSERT(status == kSuccess);
	} while (kFalse);

	// disable our flag - NOTE: see comment at the top of this source file. 
	gPrtMemPrintingToMemory = kFalse;
}

// End, PrtMemActionComponent.cpp.
