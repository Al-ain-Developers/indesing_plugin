//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformNoteFunction.cpp $
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

// General includes:
#include "Utils.h"
#include "IWorkspace.h"
#include "INoteSuite.h"
#include "INoteData.h"
#include "INoteSettings.h"
#include "IWindow.h"
#include "IIntData.h"
#include "INoteSuiteUtils.h"
#include "IConvertNoteToTextCmdData.h"
#include "INotePaletteUtils.h"
#include "INoteUtils.h"
#include "INoteUIUtils.h"
#include "IGalleyUtils.h"
#include "IDocumentUIUtils.h"
#include "IControlView.h"
#include "ITextFocus.h"
#include "ITextModelCmds.h"
#include "ITextTarget.h"
#include "IBoolData.h"
#include "RangeData.h"
#include "WritingModeID.h"
#include "LayoutUIID.h"
#include "NoteID.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	How to manipulate note through INoteSuite.
	\li	How to check note's visibility state.
	\li	How to insert text into note.

  	@ingroup sdk_snippet
  	@ingroup sdk_incopy
  	@see INoteSuite
  	@see INoteSuiteUtils
  	@see INoteSettings

 */
class SnpPerformNoteFunction
{
	public:
		/** Add a note at the current text cursor position.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode AddANote(ISnpRunnableContext* runnableContext);
		/** Insert text into the current position, if the cursor is inside the note, the text will go into the note.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode InsertText(ISnpRunnableContext* runnableContext, UIDRef targetStory, TextIndex indexStart, TextIndex indexEnd);
		/** Open a note if the selected note is collapsed, close a note if the selected note is expanded.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode OpenCloseNote(ISnpRunnableContext* runnableContext);
		/** Toggle all notes' visibility state.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ShowHideNote();
		/** Given the current text cursor, go to the next/previous note and open the note if it is collpased.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode NavigateNote(ISnpRunnableContext* runnableContext, INoteSuite::NavigateType navType);
		/** Convert the selected text into note.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ConvertTextToNote(ISnpRunnableContext* runnableContext);
		/** Convert the selected note into text.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ConvertNoteToText(ISnpRunnableContext* runnableContext, UIDRef targetStory, TextIndex indexStart, TextIndex indexEnd);
		/** Delete the selected note.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode DeleteNote(ISnpRunnableContext* runnableContext);
		/** Remove all the notes from the document.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode RemoveAllNote(ISnpRunnableContext* runnableContext);
		/** if text cursor is inside a note, split the note into 2 notes at the cursor position.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SplitNote(ISnpRunnableContext* runnableContext);
};

/*
*/
ErrorCode SnpPerformNoteFunction::AddANote(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kFailure;
	do 
	{
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		noteSuite->DoAddNote(runnableContext->GetActiveContext()->GetContextView());
		
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::InsertText(ISnpRunnableContext* runnableContext, UIDRef targetStory, TextIndex indexStart, TextIndex indexEnd)
{
	ErrorCode result = kFailure;
	do 
	{
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		ASSERT(textTarget);
		if (textTarget == nil) {
			break;
		}
		// there is situation when the CanRun return true for inserting text, but after the snip dialog dismissed, 
		// the text focus will be gone when it comes to here, in that case, we will just use the saved data for insertion.
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) {
			InterfacePtr<ITextModel> textModel(targetStory, UseDefaultIID());
			InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());

			// kFalse means take ownership of the string
			boost::shared_ptr<WideString>	tempText (new WideString("Newly Inserted Note Text!"));
			InterfacePtr<ICommand> cmd(textModelCmds->InsertCmd(indexStart, tempText));

			result =  CmdUtils::ProcessCommand(cmd);			

			break;
		}
		else
		{
			InterfacePtr<ITextModel> textModel(textFocus->QueryModel());
			InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());

			// kFalse means take ownership of the string
			boost::shared_ptr<WideString>	tempText (new WideString("Newly Inserted Note Text!"));
			RangeData r = textFocus->GetCurrentRange();
			InterfacePtr<ICommand> cmd(textModelCmds->InsertCmd(r.Start(nil), tempText));

			result =  CmdUtils::ProcessCommand(cmd);			
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::OpenCloseNote(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kFailure;
	do 
	{
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;		
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		// DoOpenNote will actually close a note if it is currently open, and vice versa
		noteSuite->DoOpenNote( runnableContext->GetActiveContext()->GetContextView(), docView);
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::ShowHideNote()
{
	ErrorCode result = kFailure;
	do 
	{
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		InterfacePtr<INoteSettings> noteSettings(sessionWorkspace, UseDefaultIID());
		if (!noteSettings)
		{
			ASSERT( noteSettings );
			break;
		}
		InterfacePtr<ICommand> command(CmdUtils::CreateCommand(kSetHideNoteStateCmdBoss));
	    if (command && noteSettings)
	    {
			InterfacePtr<IBoolData> cmdData(command, UseDefaultIID());
	        if (noteSettings->NotesAreHidden())
	            cmdData->Set(kFalse); //Show notes
			else
				cmdData->Set(kTrue); //Hide notes
			result = CmdUtils::ProcessCommand(command);
	    }
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::NavigateNote(ISnpRunnableContext* runnableContext, INoteSuite::NavigateType navType)
{
	ErrorCode result = kFailure;
	do 
	{
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;		
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		noteSuite->DoNavigateNote( runnableContext->GetActiveContext()->GetContextView(), docView, runnableContext->GetActiveContext()->GetContextSelection(), navType);
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::ConvertTextToNote(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kFailure;
	do 
	{
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		noteSuite->DoConvertToNote( runnableContext->GetActiveContext()->GetContextView(), kConvertToNoteCmdBoss);
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::ConvertNoteToText(ISnpRunnableContext* runnableContext, UIDRef targetStory, TextIndex indexStart, TextIndex indexEnd)
{
	ErrorCode result = kFailure;
	do 
	{
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;		
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;	
		// when a dialog (e.g. snippet runner's para dialog) comes up and goes away, the active context somehow will change. for example, if a note
		// is created in layout mode, the active context used to check INoteSuite::CanConvertToText will return true, but then if a dialog is up and gone
		// the active context will change and INoteSuite::CanConvertToText will now return false.  The following is really a hack to remody this case.
		// When _SnpRunnerPerformNoteFunction::CanRun is called after a note is created, the active context used to check INoteSuite::CanConvertToText
		// will return true, but after the snip dialog is dismissed, and this method got called thru Run(), the active context change, so INoteSuite::CanConvertToText
		// now return false. in that case, I use the saved data from the previous context and execute the command directly. Since the suite method 
		// won't work
		if (noteSuite->CanConvertToText(runnableContext->GetActiveContext()->GetContextView(), docView))
			noteSuite->DoConvertToText(runnableContext->GetActiveContext()->GetContextView(), docView);
		else
		{
			TextIndex noteAnchorPos;
			if (Utils<INoteUIUtils>()->TextFocusInNote(targetStory, indexStart, &noteAnchorPos))
			{
				InterfacePtr<ITextModel> textModel(targetStory, UseDefaultIID());
				ASSERT(textModel != nil);
				
				//find out the start,end range
				//note is selected
				InterfacePtr<INoteData> noteDataOnLeft(Utils<INoteUtils>()->QueryNoteData(textModel, noteAnchorPos));
				if (!noteDataOnLeft)
					break;

				TextIndex threadStart = kInvalidTextIndex;
				int32 threadLength = 0;

				UIDRef noteDataRef = ::GetUIDRef(noteDataOnLeft);
				if( textModel->FindStoryThread(noteDataRef.GetUID(), 0, &threadStart, &threadLength))
				{
					indexStart = threadStart;
					indexEnd = threadStart+threadLength-1; //no carriage return
				
				}
				
				InterfacePtr<ICommand> convertToTextCmd(CmdUtils::CreateCommand(kConvertNoteToTextCmdBoss));

				if (convertToTextCmd != nil)
				{
					UIDList cmdUIDList(targetStory);					// first item is story
					cmdUIDList.Append(noteDataRef.GetUID());	// second item is note
					convertToTextCmd->SetItemList(cmdUIDList);
							
					InterfacePtr<IIntData> focusStartData(convertToTextCmd, IID_ISTARTFOCUSINTDATA);
					focusStartData->Set(indexStart);
					InterfacePtr<IIntData> focusEndData(convertToTextCmd, IID_IENDFOCUSINTDATA);
					focusEndData->Set(indexEnd);
						
					InterfacePtr<IConvertNoteToTextCmdData> viewData(convertToTextCmd, IID_ICONVERTNOTETOTEXTCMDDATA);
					viewData->SetDocControlViewRef(UIDRef::gNull);

					InterfacePtr<IBoolData> focusInTextData(convertToTextCmd, IID_IFOCUSINTEXTBOOLDATA);
					focusInTextData->Set(kTrue);
					result = CmdUtils::ProcessCommand(convertToTextCmd);
				}			
				
			}
		}
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::DeleteNote(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kFailure;
	do 
	{
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;		
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		noteSuite->DoDeleteNote(runnableContext->GetActiveContext()->GetContextView(), docView);
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::RemoveAllNote(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kFailure;
	do 
	{
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;
		IDocumentPresentation* frontPres = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();
		InterfacePtr<IActiveContext> docAC(frontPres, UseDefaultIID());
		if (!docAC)
			break;
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		noteSuite->DoRemoveAllNotes(runnableContext->GetActiveContext()->GetContextView(), docView, docAC->GetContextDocument());
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpPerformNoteFunction::SplitNote(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kFailure;
	do 
	{
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;		
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		if (!noteSuite)
			break;		
		noteSuite->DoSplitNote(runnableContext->GetActiveContext()->GetContextView(), docView);
		result = kSuccess;
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpPerformNoteFunction available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerPerformNoteFunction : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerPerformNoteFunction();

		/** Destructor.
		 */
		virtual			~_SnpRunnerPerformNoteFunction();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}

	private:
		/** each binary bit from right to left represents on/off of a function.
		*/
		int32		mFunctionLevel;
		UIDRef		mStoryRef;
		TextIndex	mRangeStart;
		TextIndex	mRangeEnd;
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerPerformNoteFunction::_SnpRunnerPerformNoteFunction() : SnpRunnable("PerformNoteFunction"),
	mFunctionLevel(0),
	mStoryRef(UIDRef::gNull),
	mRangeStart(-1),
	mRangeEnd(-1)
{
	this->SetDescription("Shows how to perform basic notes functions");

	this->SetPreconditions("document open");

	this->SetCategories("sdk_snippet, sdk_incopy");
	
}

/* Destructor.
*/
_SnpRunnerPerformNoteFunction::~_SnpRunnerPerformNoteFunction()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerPerformNoteFunction::CanRun(ISnpRunnableContext* runnableContext)
{
	mFunctionLevel = 0;
	bool16 result = kFalse;
	do
	{
		InterfacePtr<INoteSuite> noteSuite( (IPMUnknown *)((runnableContext->GetActiveContext())->GetContextSelection()), UseDefaultIID());
		IDocumentPresentation* frontPres = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();
		if (!frontPres)
			break;
		IControlView *docView = Utils<INoteSuiteUtils>()->GetDocControlView();
		if (!docView)
			break;
		InterfacePtr<IActiveContext> docAC(frontPres, UseDefaultIID());
		if (!docAC)
			break;
				
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());

		bool16 inGalleyStoryView = Utils<IGalleyUtils>()->InGalleyOrStory();
		if (noteSuite != nil)
		{
			PMString resetMenuString;
			if (noteSuite->CanAddNote(runnableContext->GetActiveContext()->GetContextView()))
				mFunctionLevel += 1;
			else	// if I can't add a note, it means the cursor is inside a note or some text is selected
			{
				// direct insertion into note only supported in galley view, in layout, you have to enter text thru the note palette.
	//			InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
				if (textTarget)
				{
					InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
					if (textFocus)
					{
						mStoryRef = textTarget->GetTextModel();
						RangeData selectedRange = textTarget->GetRange();
						mRangeStart = selectedRange.Start(nil);
						mRangeEnd = selectedRange.End();
						mFunctionLevel += 2;
					}
				}
			}
			if (noteSuite->CanOpenNote(runnableContext->GetActiveContext()->GetContextView(), docView, resetMenuString))
				mFunctionLevel += 4;
			if (noteSuite->CanShowHideNote(runnableContext->GetActiveContext()->GetContextView(), docView))
				mFunctionLevel += 8;
			if (noteSuite->CanNavigateNote(runnableContext->GetActiveContext()->GetContextView(), docView))
				mFunctionLevel += 16;
			if (noteSuite->CanConvertToNote(runnableContext->GetActiveContext()->GetContextView()))
				mFunctionLevel += 32;
			if (noteSuite->CanConvertToText(runnableContext->GetActiveContext()->GetContextView(), docView))
			{
				mFunctionLevel += 64;
				mStoryRef = textTarget->GetTextModel();
				RangeData selectedRange = textTarget->GetRange();
				mRangeStart = selectedRange.Start(nil);
				mRangeEnd = selectedRange.End();

				ASSERT( mStoryRef);
			}
			if (noteSuite->CanDeleteNote(runnableContext->GetActiveContext()->GetContextView(), docView))
				mFunctionLevel += 128;
			if (noteSuite->CanRemoveAllNotes(runnableContext->GetActiveContext()->GetContextView(), docView,docAC->GetContextDocument()))
				mFunctionLevel += 256;
			if (noteSuite->CanSplitNote(runnableContext->GetActiveContext()->GetContextView(), docView))
				mFunctionLevel += 512;
			if (mFunctionLevel)
				result = kTrue;
		}
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerPerformNoteFunction::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		if (mFunctionLevel & 1) 
			choices.push_back(PMString("Add a note"));
		if (mFunctionLevel & 2) 
			choices.push_back(PMString("Insert text"));
		if (mFunctionLevel & 4)
			choices.push_back(PMString("Open/Close note"));
		if (mFunctionLevel & 8)
		{
			InterfacePtr<IWorkspace> workSpace(GetExecutionContextSession()->QueryWorkspace());
			InterfacePtr<INoteSettings> noteSettings(workSpace, UseDefaultIID());
			bool16 noteHidden = (noteSettings && noteSettings->NotesAreHidden());
			
			if (noteHidden) 
				choices.push_back(PMString("Show all notes"));
			else 
				choices.push_back(PMString("Hide all notes"));
		}
		if (mFunctionLevel & 16)
		{
			choices.push_back(PMString("Go to next note"));
			choices.push_back(PMString("Go to previous note"));
		}
		if (mFunctionLevel & 32)
			choices.push_back(PMString("Convert text to note"));
		if (mFunctionLevel & 64)
			choices.push_back(PMString("Convert note to text"));
		if (mFunctionLevel & 128)
			choices.push_back(PMString("Delete note"));		
		if (mFunctionLevel & 256)
			choices.push_back(PMString("Remove all notes"));
		if (mFunctionLevel & 512)
			choices.push_back(PMString("Split note"));
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What notes function do you want to perform?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Echo back to the user the choice they made and the story
		// and range of text that is to be reported on.
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());

		// Perform your operation.
		SnpPerformNoteFunction instance;

		if (choices[choice] == PMString("Add a note"))
			status = instance.AddANote(runnableContext);
		else if (choices[choice] == PMString("Insert text"))
			status = instance.InsertText(runnableContext, mStoryRef, mRangeStart, mRangeEnd);
		else if (choices[choice] == PMString("Open/Close note"))
			status = instance.OpenCloseNote(runnableContext);
		else if (choices[choice] == PMString("Show all notes") || choices[choice] == PMString("Hide all notes"))
			status = instance.ShowHideNote();
		else if (choices[choice] == PMString("Go to next note"))
			status = instance.NavigateNote(runnableContext, INoteSuite::kNextNote);
		else if (choices[choice] == PMString("Go to previous note"))
			status = instance.NavigateNote(runnableContext, INoteSuite::kPreviousNote);
		else if (choices[choice] == PMString("Convert text to note"))
			status = instance.ConvertTextToNote(runnableContext);
		else if (choices[choice] == PMString("Convert note to text"))
			status = instance.ConvertNoteToText(runnableContext, mStoryRef, mRangeStart, mRangeEnd);
		else if (choices[choice] == PMString("Delete note"))
			status = instance.DeleteNote(runnableContext);
		else if (choices[choice] == PMString("Remove all notes"))
			status = instance.RemoveAllNote(runnableContext);
		else if (choices[choice] == PMString("Split note"))
			status = instance.SplitNote(runnableContext);
	} while(false);

	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerPerformNoteFunction instance_SnpRunnerPerformNoteFunction;
DEFINE_SNIPPET(_SnpRunnerPerformNoteFunction) 	

// End, SnpPerformNoteFunction.cpp

