//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectTypingIdleTask.cpp $
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

#include "IAutoCorrectPrefs.h"
#include "IComposeScanner.h"
#include "IControlView.h"
#include "IDataBase.h"
#include "IDrawingStyle.h"
#include "IGalleyUtils.h"
#include "IHyphenationStyle.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILayoutController.h"
#include "ILinguisticMgr.h"
#include "IPanelControlData.h"
#include "IRangeData.h"
#include "ISelectionUtils.h"
#include "ISession.h"
#include "ISpellingUtils.h"
#include "IPrivateSpellingUtils.h"
#include "IStoryRefData.h"
#include "ITextChangeCaseSuite.h"
#include "ITextFocus.h"
#include "ITextMiscellanySuite.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "ITextTrackerAccess.h"
#include "IDocumentPresentation.h"
#include "IDocumentUIUtils.h"
#include "IWorkspace.h"

#include "K2SmartPtr.h"
#include "CIdleTask.h"
#include "GraphicsData.h"
#include "keyboarddefs.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "PMTextUtils.h"
#include "PreferenceUtils.h"
#include "ISelectionUtils.h"
#include "SpellPanelID.h"
#include "SystemUtils.h"
#include "TextID.h"
#include "TransformUtils.h"
#include "UnicodeClass.h"
#include "WritingModeUIID2.h"
	
#include "Trace.h"

#if DEBUG
extern bool16 gPaintInvalRect;
#endif


//----------------------------------------------------------------------------------------
// CLASS AutoCorrectTypingIdleTask 
//----------------------------------------------------------------------------------------
class AutoCorrectTypingIdleTask : public CIdleTask
{
public:
	AutoCorrectTypingIdleTask(IPMUnknown *boss);
	~AutoCorrectTypingIdleTask();
	
	virtual uint32 		RunTask(uint32 appFlags, IdleTimer* timeCheck);
	virtual const char* TaskName();

	virtual void InstallTask(uint32 millisecsBeforeFirstRun);
	virtual void UninstallTask();

private:
	void 		DoTask();

	IDocumentPresentation* 	fWindow;
};


CREATE_PMINTERFACE(AutoCorrectTypingIdleTask, kAutoCorrectTypingIdleTaskImpl)

WideString fAutoSentence;
int32 fAutoGrammarStart = -1;
int32 fAutoGrammarLength = -1;

//----------------------------------------------------------------------------------------
// AutoCorrectTypingIdleTask constructor 
//----------------------------------------------------------------------------------------
AutoCorrectTypingIdleTask::AutoCorrectTypingIdleTask(IPMUnknown *boss) :
	CIdleTask(boss),
		fWindow(nil)
{
}

AutoCorrectTypingIdleTask::~AutoCorrectTypingIdleTask()
{
}

void AutoCorrectTypingIdleTask::InstallTask(uint32 millisecsBeforeFirstRun)
{
#ifdef DEBUG
	TRACEFLOW_OBSOLETE("AutoCorrect", "AutoCorrectTypingIdleTask::InstallTask -- Disabling the adornment(s)\n");
#endif

	fWindow = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();
	if (! fWindow)
		return;

	//InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
	//InterfacePtr<ITextMiscellanySuite> textMiscellanySuite(static_cast<ITextMiscellanySuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ITEXTMISCELLANYSUITE, selectionManager)));
	//if (textMiscellanySuite)
	//{
	//	InterfacePtr<IIntData> intData(this, UseDefaultIID());
	//	SysChar c = 0;
	//	if (intData)
	//	{
	//		c = intData->Get();
	//	}
	//	textMiscellanySuite->SetWorkSpaceTypingRangeData(c, IID_IAUTOCORRECTRANGEDATA);
	//}

	CIdleTask::InstallTask(millisecsBeforeFirstRun);
}

void AutoCorrectTypingIdleTask::UninstallTask()
{
#ifdef DEBUG
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IAUTOCORRECTRANGEDATA);
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	TRACEFLOW_OBSOLETE("AutoCorrect", "AutoCorrectTypingIdleTask::UninstallTask\n");
#endif

	CIdleTask::UninstallTask();
}

//FW:Denali:source:components:ToolBox:PopOutMouseTrackThread.cpp

//----------------------------------------------------------------------------------------
// AutoCorrectTypingIdleTask::DoTask
// This invalidates the region associated with the text range in this idle task
//----------------------------------------------------------------------------------------
void AutoCorrectTypingIdleTask::DoTask()
{
#ifdef DEBUG
	TRACEFLOW_OBSOLETE("AutoCorrect", "AutoCorrectTypingIdleTask::DoTask\n");
#endif
			
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IAUTOCORRECTRANGEDATA);
	
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	IDocumentPresentation* window = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();

	if (fWindow != window)
	{
#ifdef DEBUG
		TRACEFLOW_OBSOLETE("AutoCorrect", "IdleTask installed with different window than runTask\n");
#endif
		window = fWindow; // FIXME_OWL2: 3rd time's a charm? (3rd incidence of this error)
		return; //fWindow could be bogus (if it closed before the task ran) TODO: set up observer which will remove idle task when window is closed.
	}

	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
	if (! autoCorrectPrefs)
		return;
	
	/* reset the range */
	rangeData->Set(kInvalidTextIndex, kInvalidTextIndex);

	PMRect invalRect;
	InterfacePtr<ITextModel> textModel(nil);
	IControlView* writingView = nil;
	
	if (window && Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(window))
	{
		InterfacePtr<IPanelControlData> panelData(window, IID_IPANELCONTROLDATA);
		writingView = panelData->FindWidget(kWritingId);
		if (writingView != nil)
		{
			InterfacePtr<IStoryRefData> storyRefData(writingView, IID_ISTORYREFDATA);
			ASSERT(storyRefData != nil);

			textModel.reset(InterfacePtr<ITextModel>(storyRefData->GetStoryRef(), IID_ITEXTMODEL).forget());
			ASSERT(textModel != nil);
		}
		else
			return;
	}
	else
	{
		InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection());
		InterfacePtr<ITextTrackerAccess> tta( selMgr, UseDefaultIID());
		if (!tta)
			return;
		InterfacePtr<ITextFocus> focus (tta->QueryTextFocus());
		if (!focus)
			return;
		textModel.reset(focus->QueryModel());
		if (! textModel)
			return;
	}

	if (textModel)
	{
		int32 storyLength = textModel->TotalLength();

		//--typingEnd;	/* ignore the separator character */

		/* It may be possible the model is now shorter than the range set by the idle task */
		if (typingStart >= storyLength)
			typingStart = storyLength - 1;
		if (typingStart < 0)
			typingStart = 0;
		if (typingEnd >= storyLength)
			typingEnd = storyLength - 1;
		if (typingEnd < 0)
			typingEnd = 0;

		if (typingEnd > typingStart)
		{
			InterfacePtr<IComposeScanner> cs(textModel, UseDefaultIID());
			if (cs)
			{
				WideString copy;

				LanguageID langID = kLanguageNeutral;
				IDrawingStyle* style = cs->GetCompleteStyleAt(typingStart);
				InterfacePtr<ILanguage> lang(nil);
				if (style)
				{
					InterfacePtr<IHyphenationStyle> hyphStyle(style, IID_IHYPHENATIONSTYLE);
					lang.reset(hyphStyle->QueryLanguage());
					if (lang)
						langID = lang->GetLanguageID();
				}
				
				TextIndex wordStart = cs->CopySurroundingWord(typingEnd > 0 ? typingEnd-1:typingEnd, &copy, nil, PMCharFilters::SpellingIsWordChar);    /* copy the word at the cursor position (less the separator char) */
				if (copy.Length() > 0 && typingEnd > wordStart)
				{
					cs->CopyText(wordStart, typingEnd - wordStart, &copy);	/* copy the characters typed */

					/* get the correct language */
					const AutoCorrectList& autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();	/* do not copy */
					
					bool16 replaced = kFalse;
					
					if (autoCorrectList.Length() > 0)
					{	
						int32 langIndex = -1;
						for (int32 j = 0; j < autoCorrectList.Length(); j++)
						{
							if (langID == autoCorrectList[j].fLanguageID)
							{
								langIndex = j;
								break;
							}
						}
						
						//TODO: finish algorithm for character matching, at this point the space/punctuation/word boundary char isn't entered. so we need to create a pseudo word
						//		from the begginning of the "word" to the insertion point here (typing end?)
						if (langIndex >= 0 && langIndex < autoCorrectList.Length())
						{
							// try exact match first
							int32 location = autoCorrectList[langIndex].fAutoStringPair.Location(copy);
							
							bool16 isUpper = UnicodeClass::IsUpper(copy[0]);
							
							if (location < 0)
							{
								WideString lowerCaseCopy(copy);
								lowerCaseCopy.ToLower();

								// try lower case match
								location = autoCorrectList[langIndex].fAutoStringPair.Location(lowerCaseCopy);
							}

							if (location >= 0)
							{
								InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
								if (textModelCmds)
								{
									copy = autoCorrectList[langIndex].fAutoStringPair.Value(location);	/* we may want to capitalize this! */
									
									if (isUpper)
									{
										copy.SetChar(0, UnicodeClass::ToUpper(copy[0]));
									}

									const boost::shared_ptr<WideString> value(new WideString(copy));
									InterfacePtr<ICommand> replaceTextCmd(textModelCmds->ReplaceCmd(wordStart, autoCorrectList[langIndex].fAutoStringPair.Key(location).Length(), value));
									ErrorCode err = CmdUtils::ProcessCommand(replaceTextCmd);
									
									replaced = kTrue;
								}
							}
						}
					}
					
					if (autoCorrectPrefs->GetAutoCorrectCapitalizationErrors())
					{
						// maybe the replacement has multiple words?
						//while ()
						
						int32 spaceIndex = copy.IndexOf(kTextChar_Space);
						
						if (spaceIndex >= 0)
							copy.Truncate(copy.Length() - spaceIndex);

						if (UnicodeClass::IsLowercase(copy[0]))	/* lower case ? */
						{
							if (Utils<ISpellingUtils>())
							{
								bool16 bCapitalizeTheWord = kFalse;

								InterfacePtr<IK2ServiceRegistry> pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
								InterfacePtr<IK2ServiceProvider> pLinguMgrService(pServices->QueryDefaultServiceProvider(kLinguisticManagerService));
								InterfacePtr<ILinguisticMgr> pLinguMgr(pLinguMgrService, IID_ILINGUISTICMGR);
								WideStringList alternatives;

								ISpellingService::SpellResult result = Utils<ISpellingUtils>()->IsWordCorrect(copy, lang, &alternatives, pLinguMgr, nil, nil);
								if (result == ISpellingService::kUncapitalizedWord)
									bCapitalizeTheWord = kTrue;
								else
								{
									int32 nGrammarStart = fAutoGrammarStart, nGrammarLength = fAutoGrammarLength;

									const TextIndex nParaStart = nGrammarStart = cs->FindSurroundingParagraph(wordStart + copy.Length(), &nGrammarLength);

									if (nGrammarLength > 0)
									{
										/* have we already found this paragraph? dont copy if indexes are the same as last time. */
										if (nGrammarStart != fAutoGrammarStart || nGrammarLength != fAutoGrammarLength)
										{
											cs->CopyText(nGrammarStart, nGrammarLength, &fAutoSentence);
											fAutoGrammarStart = nGrammarStart;
											fAutoGrammarLength = nGrammarLength;
										}

										ASSERT(fAutoGrammarStart >= 0 && nGrammarStart >= 0);
										ASSERT(fAutoGrammarLength > 0 && nGrammarLength > 0);
										ASSERT(fAutoSentence.Length() > 0);

										int32 errorStart = -1, errorLength = 0;
										result = Utils<ISpellingUtils>()->IsGrammarCorrect(fAutoSentence, wordStart - nGrammarStart, lang, pLinguMgr, textModel, errorStart, errorLength);
									}
									if (result == ISpellingService::kUncapitalizedStartOfSentence)
										bCapitalizeTheWord = kTrue;
								}

								if (bCapitalizeTheWord)
								{
									bool16 bFoundReplacement(kFalse);
									PMString pmCopy(copy);
									for (int32 i = 0; i < alternatives.size() && !bFoundReplacement; i++)
									{
										PMString pmAlternative(alternatives[i]);
										if (pmAlternative.Compare(kFalse, pmCopy) == 0)	/* if a case insensitive compare matches the suggestion, use it */
										{
											copy = alternatives[i];
											bFoundReplacement = kTrue;
										}
									}
									
									ErrorCode err = kSuccess;

									// If we got found a replacement in the alternatives, use it.
									if (bFoundReplacement)
									{
										InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
										if (textModelCmds)
										{
											const boost::shared_ptr<WideString> capitalizedWord(new WideString(copy));
											
											InterfacePtr<ICommand> replaceTextCmd(textModelCmds->ReplaceCmd(wordStart, copy.Length(), capitalizedWord));
											err = CmdUtils::ProcessCommand(replaceTextCmd);
										}
									}
									else	// Otherwise just capitalize the word using title case. OK not to use kCCSentence since we already know sentence context. Simpler.
									{
										InterfacePtr<ICommand> caseCmd(CmdUtils::CreateCommand(kChangeCaseCmdBoss));
										caseCmd->SetItemList(UIDList(textModel));

										InterfacePtr<IIntData> data(caseCmd, IID_IINTDATA);
										data->Set(ITextChangeCaseSuite::kCCTitle);

										InterfacePtr<IRangeData> range(caseCmd, IID_IRANGEDATA);
										range->Set(wordStart, wordStart+1);

										err = CmdUtils::ProcessCommand(caseCmd);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

uint32 AutoCorrectTypingIdleTask::RunTask(uint32 appFlags, IdleTimer* timeCheck)
{
	DoTask();
	
	/* One and done */
	this->UninstallTask();
	
	return 0;
}

const char* AutoCorrectTypingIdleTask::TaskName()
{
	return "AutoCorrectTypingIdleTask";
}
