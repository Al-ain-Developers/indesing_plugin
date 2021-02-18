//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/PrivateSpellingUtils.cpp $
//  
//  Owner: hhorton
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
//  Proj:	SpellPanel
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IComposeScanner.h"
#include "IConcreteSelection.h"
#include "IControlView.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "IDocumentPresentation.h"
#include "IDrawingStyle.h"
#include "IDynamicSpellCheckCache.h"
#include "IFrameList.h"
#include "IGlobalRecompose.h"
#include "IGraphicsPort.h"
#include "IHyphExceptionsPrefs.h"
#include "IHyphExceptionByLangCmd.h"
#include "IHyphenationExceptions.h"
#include "IHyphenationStyle.h"
#include "IIntData.h"
#include "IItemStrand.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILayoutControlData.h"
#include "ILayoutController.h"
#include "ILinguisticMgr.h"
#include "IOwnedItem.h"
#include "IPanelControlData.h"
#include "IParcelList.h"
#include "IPendingInvals.h"
#include "IRangeData.h"
#include "ISession.h"
#include "ISpellPanelOptions.h"
#include "ISpellingDataStrand.h"
#include "ISpellingService.h"
#include "IStoryList.h"
#include "IStoryRefData.h"
#include "ITextEditor.h"
#include "ITextFocus.h"
#include "ITextFrameColumn.h"
#include "ITextLines.h"
#include "ITextMiscellanySuite.h"
#include "ITextModel.h"
#include "ITextParcelList.h"
#include "ITextRuns.h"
#include "ITextStoryThread.h"
#include "ITextTiler.h"
#include "ITextTrackerAccess.h"
#include "IUserDictService.h"
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IWaxLineShape.h"
#include "IWaxRun.h"
#include "IWaxRunIterator.h"
#include "IWaxStrand.h"
#include "IWindow.h"
#include "IPresentationList.h"
#include "IWorkspace.h"
#include "IWidgetUtils.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "CAlert.h"
#include "CIdleTask.h"
#include "CPMUnknown.h"
#include "CharacterClass.h"
#include "GraphicsData.h"
#include "HelperInterface.h"
#include "HyphenExceptions.h"
#include "K2SmartPtr.h"
#include "keyboarddefs.h"
#include "TextChar.h"
#include "Trace.h"
#include "UserDictWordList.h"
#include "UnicodeClass.h"
#include "WideString.h"
#include "WritingModeUIID2.h"

// ----- Utility files -----

#include "IDictionaryUtils.h"
#include "IGalleyUtils.h"
#include "ILayoutUIUtils.h"
#include "IPrivateSpellingUtils.h"
#include "ISelectionUtils.h"
#include "IDocumentUIUtils.h"
#include "PMTextUtils.h"
#include "IPageItemUtils.h"
#include "PreferenceUtils.h"
#include "ISelectionUtils.h"
#include "SystemUtils.h"
#include "TransformUtils.h"
#include "ICompositionUtils.h"

// ----- ID.h files -----

#include "DictEditorID.h"
#include "InCopySharedID.h"
#include "LinguisticID.h"
#include "NoteID.h"
#include "SpellPanelID.h"
#include "TextEditorImplID.h"
#include "TextID.h"


#if DEBUG
extern bool16 gPaintInvalRect;
#endif

const int kUIWordLimit = 60;

class PrivateSpellingUtils : public CPMUnknown<IPrivateSpellingUtils>
{
public:
	PrivateSpellingUtils( IPMUnknown *boss );

	virtual void InvalTextRange(IControlView* view, ITextModel* textModel, TextIndex startIndex, TextIndex endIndex);

	virtual void DeleteCacheAndInvalDocWindows(IDocument* doc, bool16 recheckAll);	/* all windows for a single document */
	virtual void DeleteCacheAndInvalAllDocWindows(bool16 recheckAll);	/* all windows for all documents */

	virtual bool16 ModifyDictionary(const PMString& originalWord,
									DictAction action,
									bool16 bCaseSensitive,
									IPMUnknown* target,
									ILanguage* pLanguage,
									const UserDictWordList& udStrList);
									
private:
	std::vector<RangeData> GetThreadRanges(ITextModel *model, RangeData fullRange);
};

CREATE_PMINTERFACE(PrivateSpellingUtils, kPrivateSpellingUtilsImpl)

PrivateSpellingUtils::PrivateSpellingUtils( IPMUnknown *boss ) :
		CPMUnknown<IPrivateSpellingUtils>(boss)
{
}

// Inval the text range in the writingView
// if the view is nil, then we want to inval the range, for this story, in all views that it is in
// so we walk every document and check to see
//
void PrivateSpellingUtils::InvalTextRange(IControlView* writingView, ITextModel* textModel, TextIndex startIndex, TextIndex endIndex)
{
	if (!textModel)
		return;

	IDataBase* db = ::GetDataBase(textModel);
	
	//Get the list of presentations for this document, abort if none
	InterfacePtr<IPresentationList> presList(db, db->GetRootUID(), UseDefaultIID());
	if (!presList || presList->empty())
		return;

	InterfacePtr<IWaxStrand> waxStrand((IWaxStrand *)textModel->QueryStrand(kFrameListBoss, IID_IWAXSTRAND));
	if (waxStrand)
	{
		// index to point, thats wax business; see FocusShell::GetDeltaFromLines().
		PMPoint		offsetPointWax, offsetPointWax2;
		PMMatrix	waxToFrameMatrix, waxToFrameMatrix2;
		PMMatrix	waxToGlyphMatrix, waxToGlyphMatrix2;
		PMReal		waxLineHeight, waxLineHeight2;
		UID			frameUID, frameUID2;

		int32 storyLength = textModel->TotalLength();

		/* It may be possible the model is now shorter than the range set by the idle task */
		if (startIndex >= storyLength)
			startIndex = storyLength - 1;
		if (startIndex < 0)
			startIndex = 0;
		if (endIndex >= storyLength)
			endIndex = storyLength - 1;
		if (endIndex < 0)
			endIndex = 0;

		/* invalidate entire words -- so grab the indexes of the begining of the first word and the end of the last word */
		InterfacePtr<IComposeScanner> scanner(textModel, IID_ICOMPOSESCANNER);
		if (scanner)
		{
			int32 firstWordLength, lastWordLength;

			startIndex = scanner->FindSurroundingWord(startIndex, &firstWordLength, nil, PMCharFilters::SpellingIsWordChar);
			endIndex = scanner->FindSurroundingWord(endIndex, &lastWordLength, nil, PMCharFilters::SpellingIsWordChar);

			ASSERT_MSG(lastWordLength >= 0, "lastWordLength >= 0");
 			endIndex += lastWordLength;
		}

		if (startIndex != endIndex)
		{
			// Loop over all presentations on the document -- do something different depending on whether it's Galley/Story vs Layout
			// Begin with an active presentation if possible, after that don't worry about relative order.
			IDocumentPresentation* activePres = Utils<IDocumentUIUtils>()->GetFrontmostPresentationForDocument(db);
			
			//Create a local list of the presentations, with "activePres" presentation as the first entry.
			PresentationSequence presentationList;
			presentationList.push_back(activePres);
			for (IPresentationList::iterator iter = presList->begin(); iter != presList->end(); ++iter)
			{
				if (*iter != activePres) presentationList.push_back(*iter);
			}
			
			PresentationSequence::iterator presentationIter = presentationList.begin();
			while (presentationIter != presentationList.end())
			{
				if (*presentationIter && Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(*presentationIter))	/* Galley/Story view */		//SEIssue
				{
					IControlView* localView = writingView;
					if (! localView)
					{
						//if (presentation && Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(presentation)) redundant check
						{
							InterfacePtr<IPanelControlData> panelData(*presentationIter, IID_IPANELCONTROLDATA);
							localView = panelData->FindWidget(kWritingId);
							if (! localView)
							{
								//presentation = Utils<IDocumentUIUtils>()->GetNextDocumentPresentationForDocument(presentation, db);
								//Try another presentation
								++presentationIter;  
								continue;
							}
						}
					}
					ASSERT_MSG(localView != nil, "localView != nil");

					InterfacePtr<ITextLines> textLines(localView, IID_ITEXTLINES);
					if (textLines)
					{
						int32 startLineOffsetIntoLine = -1;
						int32 endLineOffsetIntoLine = -1;
						int32 startRunIndex = -1;
						int32 endRunIndex = -1;

						int32 storyIndex = Utils<IGalleyUtils>()->GetStoryIndex(textLines, textModel);
						if (storyIndex < 0)
						{
							//presentation = Utils<IDocumentUIUtils>()->GetNextDocumentPresentationForDocument(presentation, db);
							++presentationIter;
							continue;
						}

					// NOTE: FindIndexOfLineAtTextOffset doesn't work inside notes and deleted text.  Convert to display
					// offsets and use that to find the appropriate line

	#ifdef DEBUG
						int32 primaryStorySpan = textModel->GetPrimaryStoryThreadSpan();
						if (startIndex < 0)
							TRACEFLOW_OBSOLETE("Spelling", "startIndex < 0");
						if (endIndex < 0)
							TRACEFLOW_OBSOLETE("Spelling", "endIndex < 0");
	#endif

						TextIndex safeStart = startIndex; // Not sure if this will ever occur but the above debug code suggests it does so handle it
						TextIndex safeEnd = endIndex;
						if (safeStart < 0) safeStart = 0;
						if (safeEnd < 0) safeEnd = safeStart;
						RangeData fullRange = (safeStart == safeEnd) ? RangeData(safeStart, RangeData::kLeanForward) : RangeData(safeStart, safeEnd);
						std::vector<RangeData> threadRanges = PrivateSpellingUtils::GetThreadRanges(textModel, fullRange);
						
						for (std::vector<RangeData>::iterator iter = threadRanges.begin(); iter != threadRanges.end(); iter++)
						{
							TextIndex displayStartIndex = textLines->ModelIndexToDisplayIndex (storyIndex, iter->Start(nil));
							TextIndex displayEndIndex = textLines->ModelIndexToDisplayIndex (storyIndex, iter->End());
							
							if (displayStartIndex == -1 || displayEndIndex == -1 || displayEndIndex == displayStartIndex) 
							{
								continue;
							}
	
							int32 startLineIndex = textLines->FindIndexOfLineAtDisplayOffset(storyIndex, displayStartIndex, startLineOffsetIntoLine, RangeData::kLeanForward);
							int32 endLineIndex = textLines->FindIndexOfLineAtDisplayOffset(storyIndex, displayEndIndex, endLineOffsetIntoLine, RangeData::kLeanForward);
	
							InterfacePtr<ITextRuns> textRuns(textLines, IID_ITEXTRUNS);
	
							const RunDescription* startRun = nil;
							if (startLineIndex > -1)
								startRun = textRuns->FindRunAtDisplayOffset(storyIndex, displayStartIndex, startLineIndex, &startRunIndex);
							const RunDescription* endRun = nil;
							if (endLineIndex > -1)
								endRun = textRuns->FindRunAtDisplayOffset(storyIndex, displayEndIndex, endLineIndex, &endRunIndex);
	
							if (startLineIndex >= 0 && endLineIndex >= 0)
							{
								for (int32 i = startLineIndex; i <= endLineIndex; i++)
								{
									PMRect lineRect = textLines->CalculateLineRect(storyIndex, i);
	
									if (i == startLineIndex)
									{
										lineRect.Left(textLines->GetXPositionOfDisplayOffsetCharacter(storyIndex, startLineIndex, startLineOffsetIntoLine));
									}
									if (i == endLineIndex)
									{
										lineRect.Right(textLines->GetXPositionOfDisplayOffsetCharacter(storyIndex, endLineIndex, endLineOffsetIntoLine));
									}
	
									/* inval each lines rect */
									localView->Invalidate(&lineRect);
	
								#ifdef DEBUG
									if (gPaintInvalRect)
									{
										PMRect sPaintRectBounds(lineRect);
										sPaintRectBounds.Inset(1.0, 1.0);
										Utils<IWidgetUtils>()->DrawHiliteRect(localView, sPaintRectBounds, kTrue, 1.0);
									}
								#endif
								}
							}
						}
					}
				}
				else	/* layout view */
				{
					if (*presentationIter)
					{
						
						InterfacePtr<IPanelControlData> panelData(*presentationIter, ::UseDefaultIID());
						if (panelData)
						{
							K2Vector<IControlView*> layoutViews;
							IControlView* layoutWidget = panelData->FindWidget(kLayoutWidgetBoss);
							layoutViews.push_back(layoutWidget);
							
							// Find the split layout widget in the secondary layout panel, add it if not hidden 
							IControlView* splitLayoutPanel = panelData->FindWidget(kLayoutSecondaryPanelWidgetID);
							InterfacePtr<IPanelControlData> splitPanelData(splitLayoutPanel, UseDefaultIID());
							IControlView* splitLayoutWidget = (splitPanelData ? splitPanelData->FindWidget(kLayoutWidgetID) : nil);
							if (splitLayoutWidget && splitLayoutWidget->IsVisible())
								layoutViews.push_back(splitLayoutWidget);

							for (K2Vector< IControlView* >::iterator iDocView = layoutViews.begin(); iDocView != layoutViews.end(); ++iDocView)
							{	
								if (*iDocView)
								{
									// Iterate the WaxLines in this text range
									K2::scoped_ptr<const IWaxIterator>	waxIterator(waxStrand->NewReadOnlyWaxIterator());
									bool16				drawAborted = kFalse;
									const IWaxLine *		waxLine;
									PMRect				waxLineInkBounds;
									int32				span = 0;

									Utils<ICompositionUtils>()->PregenerateWaxRuns(waxIterator.get(), startIndex, endIndex);

									waxLine = waxIterator->GetFirstWaxLine(startIndex);
									if (waxLine)
										span = waxLine->TextOrigin();

									while (waxLine != nil)
								{
									span += waxLine->GetTextSpan();

									// If waxLine is not destroyed (bug fix 538392),
									// Check to see if we need to redraw this line
									if (!waxLine->IsDestroyed() && !waxLine->IsDamaged())
									{
										// clear the dsc drawing cache
										K2::scoped_ptr<IWaxRunIterator> waxRunIter(waxLine->QueryWaxRunIterator());
										IWaxRun * waxRun = waxRunIter->GetFirstRun();
										while (waxRun)
										{
											InterfacePtr<IDynamicSpellCheckCache> dynamicSpellCheckCache(waxRun, UseDefaultIID());
											if (dynamicSpellCheckCache && dynamicSpellCheckCache->GetCacheFlag())
											{
												dynamicSpellCheckCache->SetCacheFlag(kFalse);
												dynamicSpellCheckCache->SetCache(nil);	//deletes the cache
											}
											waxRun = waxRunIter->GetNextRun();
										}

										InterfacePtr<IWaxLineShape>	waxShape(waxLine, UseDefaultIID());
										{
											CmdUtils::AutoUndoSequencePtr seq(db);

											waxShape->GetInkBounds(&waxLineInkBounds);
										}
										InterfacePtr<ITextStoryThread> thread(waxLine->QueryStoryThread());

										ParcelKey parcelKey = waxLine->GetParcelKey();
										if (parcelKey.IsValid())
										{
											InterfacePtr<IParcelList> pl(thread->QueryParcelList());
											InterfacePtr<const ITextParcelList> tpl(pl, UseDefaultIID());


											//	InterfacePtr<IParcelList> pl(thread->QueryParcelList());
											//	PMMatrix toFrameMatrix = pl->GetNthToContentMatrix(waxLine->GetParcelIndex());		// toContent
											//	toFrameMatrix.Invert();																// now contentToParcel
											//	toFrameMatrix.PostConcat(pl->GetNthToFrameMatrix(waxLine->GetParcelIndex()));		// now contentToFrame

											InterfacePtr<ITextFrameColumn> textFrameColumn(pl->QueryParcelFrame(parcelKey));
											//InterfacePtr<ITextFrameColumn> textFrameColumn(pl->QueryNthFrame(waxLine->GetParcelIndex()));

											PMRect copyWaxLineInkBounds(waxLineInkBounds);
											if (1)
											{
												PMMatrix toFrameMatrix = tpl->GetParcelToContentMatrix(parcelKey).Inverse();	// now contentToParcel
												toFrameMatrix.PostConcat(pl->GetParcelToFrameMatrix(parcelKey));

												if (textFrameColumn)
													toFrameMatrix.PostConcat(::InnerToPasteboardMatrix(textFrameColumn));

												toFrameMatrix.Transform(&copyWaxLineInkBounds);

#if DEBUG
												if (gPaintInvalRect)
												{
													PMRect paintRectBounds(copyWaxLineInkBounds);
													paintRectBounds.Inset(1.0, 1.0);
													Utils<IWidgetUtils>()->DrawHiliteRect(*iDocView, paintRectBounds, kTrue, 1.0);
												}
#endif
											}
											InterfacePtr<IShape> textFrameShape(textFrameColumn, UseDefaultIID());
											if (textFrameShape)
												Utils<ILayoutUIUtils>()->InvalidateShapeGraphixCache(textFrameShape);
											//InterfacePtr<IPendingInvals> pendingInvals(textFrameColumn, UseDefaultIID());
											if (0 /*pendingInvals*/)
											{
												//
												// Convert the inkBounds from Wax (content) coordinates to Frame
												// coordinates before adding it to the pending invals interface.
												//
												InterfacePtr<IParcel> parcel(pl->QueryParcel(parcelKey));
												InterfacePtr<const ITextTiler> textTiler(parcel, UseDefaultIID());

												PMMatrix waxToParcel = textTiler->GetToContentMatrix().Inverse();	// waxToParcel
												waxToParcel.Transform(&waxLineInkBounds);
												parcel->AddPendingInval(waxLineInkBounds);

												//pendingInvals->RecordPendingInval(waxLineInkBounds);
											}
											else
											{
												InterfacePtr<ILayoutController> controller(*iDocView, ::UseDefaultIID());
												if (controller)
												{
													PMRect localRect(copyWaxLineInkBounds);
													(*iDocView)->ContentToWindowTransform(&localRect);
													controller->InvalidateContent(&localRect, kTrue);
												}
											}
										}
									}

									if (span >= endIndex)
										break;

									waxLine = waxIterator->GetNextWaxLine();
								}
								}
							}
						}
					}
				}

				//presentation = Utils<IDocumentUIUtils>()->GetNextDocumentPresentationForDocument(presentation, db);
				++presentationIter;
			}
		}
	}
}



ITextEditor* QueryTextEditor(IDocumentPresentation *pres);
ITextEditor* QueryTextEditor(IDocumentPresentation *pres)
{
	ASSERT(pres);
	InterfacePtr<ILayoutControlData> pLayoutData(Utils<ILayoutUIUtils>()->QueryLayoutData(pres));
	if (!pLayoutData)
        return nil;

    InterfacePtr<IPanelControlData> panelData(pLayoutData,UseDefaultIID());

    IControlView *pView = panelData->FindWidget(kTextEditorWidgetID);
    return pView ? (ITextEditor*)pView->QueryInterface(IID_ITEXTEDITOR) : nil;
}

/* all windows for a single document */
// will refactor this after ship
/* Doesn't have support for split window*/
void PrivateSpellingUtils::DeleteCacheAndInvalDocWindows(IDocument* doc, bool16 recheckAll)
{
	if (!doc)
		return;

	/* right now we just force all stories to re-check, maybe we should just search through all stories for this word and just damage it? */
	if (recheckAll)
	{
		InterfacePtr<IStoryList> storyList(::GetUIDRef(doc), UseDefaultIID());
		if (storyList)
		{
			for (int32 i = 0; i < storyList->GetUserAccessibleStoryCount(); i++)
			{
				InterfacePtr<ITextModel> textModel(storyList->GetNthUserAccessibleStoryUID(i), UseDefaultIID());
				if (textModel)
				{
					InterfacePtr<ISpellingDataStrand> spellingDataStrand((ISpellingDataStrand*)textModel->QueryStrand(kSpellingStrandBoss, IID_ISPELLINGDATASTRAND));
					if (spellingDataStrand)
					{
						spellingDataStrand->SetSpellingDataState(0, textModel->TotalLength(), kSpellingUnchecked, textModel);
					}
				}
			}
		}
	}

	InterfacePtr<IPresentationList> presList(doc, UseDefaultIID());
	if (! presList)
		return;
	
	for (IPresentationList::iterator iter = presList->begin(); iter != presList->end(); ++iter)
	{
		if (*iter)
		{
			InterfacePtr<IPanelControlData> panelData(*iter, ::UseDefaultIID());
			if (panelData)
			{
				IControlView* iDocView = nil;
				if (Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(*iter))
				{
					iDocView = panelData->FindWidget(kWritingId);
					if (iDocView)
					{
						InterfacePtr<ITextLines> textLines(iDocView, UseDefaultIID());
						if (textLines)
						{
							textLines->DeleteCacheForAllLines();
						}
					}
				}
				else
				{
					iDocView = panelData->FindWidget (kLayoutWidgetBoss);
					if (iDocView)
					{
						InterfacePtr<ITextEditor> textEditor(::QueryTextEditor(*iter));
						if (textEditor)
						{
							InterfacePtr<IFrameList> frameList(textEditor->QueryFrameList());
							if (frameList)
							{
								InterfacePtr<IWaxStrand> waxStrand(frameList, UseDefaultIID());
								K2::scoped_ptr<const IWaxIterator>	waxIterator(waxStrand->NewReadOnlyWaxIterator());
								const IWaxLine * waxLine = waxIterator->GetFirstWaxLine(0);

								while ((waxLine != nil) &&
									   (!waxLine->IsDestroyed()) &&
									   (waxLine->DoWaxRunsExist()))
								{
									K2::scoped_ptr<IWaxRunIterator> waxRunIterator(waxLine->QueryWaxRunIterator());
									const IWaxRun * waxRun = waxRunIterator->GetFirstRun();
									while (waxRun != nil)
									{
										InterfacePtr<IDynamicSpellCheckCache> dynamicSpellCheckCache(waxRun, IID_IDYNAMICSPELLCHECKCACHE);
										if (dynamicSpellCheckCache && dynamicSpellCheckCache->GetCache())
										{
											dynamicSpellCheckCache->SetCache(nil);	//deletes the cache
											dynamicSpellCheckCache->SetCacheFlag(kFalse);
										}

										waxRun = waxRunIterator->GetNextRun();
									}

									waxLine = waxIterator->GetNextWaxLine();
								}
							}
						}
					}
				}

				if (iDocView && !recheckAll)	//if we are not re checking then we just want to refresh view
				{
					InterfacePtr<ILayoutController> controller(iDocView, ::UseDefaultIID());
					if (controller)
					{
						controller->InvalidateContent();
						SysRgn region = controller->GetInvalidContentRgn();
						controller->InvalidateContent(region, kFalse);
						Utils<ILayoutUIUtils>()->InvalidateShapeGraphixCache(doc);

						// Redraw the screen
						iDocView->ForceRedraw(region, kFalse);

						if (region)
							::DeleteSysRgn(region);
					}
					else
					{
						iDocView->ForceRedraw(nil, kFalse);
					}
				}
			}
		}
	}
}

/* all windows for all documents */
void PrivateSpellingUtils::DeleteCacheAndInvalAllDocWindows(bool16 recheckAll)
{
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
 	InterfacePtr<IDocumentList> docList(app->QueryDocumentList());

	for (int32 j = 0; j < docList->GetDocCount(); j++)
	{
		IDocument* doc = docList->GetNthDoc(j);
		DeleteCacheAndInvalDocWindows(doc, recheckAll);
	}
}

bool16 isLegalWord(const PMString rWord);
bool16 isLegalWord(const PMString rWord)
{
	// If the word includes trailing punctuation, it won't be included as part of the word during spell checking,
	// and therefore it shouldn't be added to the dictionary.
	UTF32TextChar lastCharacter(rWord.GetWChar(rWord.CharCount() - 1));
	if ( (UnicodeClass::IsPunctuation(lastCharacter) && lastCharacter != kTextChar_Period)
		|| UnicodeClass::IsPunctuation(rWord.GetWChar(0)) )
	{
		return kFalse;
	}
	return kTrue;
}



// The entries in the dictionary all go through the user interface, which doesn't
// distinguish between right and left double or single quotations.  When comparing
// against those entries, we need to turn typographer's quotes into standard
// (ANSI) quotes
static void NormalizeWordForPunctuation(WideString &tempText);
static void NormalizeWordForPunctuation(WideString &tempText)
{
	int32 numberOfCharacters = tempText.CharCount();
	for (int32 i = 0 ; i < numberOfCharacters; i++)
	{
		UTF32TextChar thisCharacter = tempText[i];
		if (thisCharacter == kTextChar_RightSingleQuotationMark ||
			thisCharacter == kTextChar_LeftSingleQuotationMark)
		{
			tempText.SetChar(i, kTextChar_Apostrophe);
		}
		else if (thisCharacter == kTextChar_LeftDoubleQuotationMark ||
			thisCharacter == kTextChar_RightDoubleQuotationMark)
		{
			tempText.SetChar(i,  kTextChar_QuotationMark);
		}
	}
}


bool16 PrivateSpellingUtils::ModifyDictionary(const PMString& originalWord,
												   DictAction action,
												   bool16 bCaseSensitive,
												   IPMUnknown* target,
												   ILanguage* pLanguage,
												   const UserDictWordList& udStrList)
{
	PMString rWord(originalWord);
	rWord.ParseForEmbeddedCharacters();
	if( rWord.IsNull() )
		return kFalse;

	WideString wideRWord(rWord);			/* convert the PMString to a WideString */
	NormalizeWordForPunctuation(wideRWord);
	if (!isLegalWord(rWord))
	{
		CAlert::ErrorAlert("kUserDictionaryBadPunctuation");
		return kFalse;
	}

	bool16 			bAdded = kFalse;
	int32 			index;
	WideString 		aWord;
	HyphenPoints 	aPoints;

	Utils<IDictionaryUtils>()->GetProximityWord( rWord, &aWord, &aPoints );

	InterfacePtr<IK2ServiceRegistry> pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider> pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr> pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
	InterfacePtr<IUserDictService> pUserDictService(pLinguMgr->QueryUserDictService( pLanguage ) );

	/* updated to handle adding to a document or user dict */
	InterfacePtr<IDocument> document(target, UseDefaultIID());
	InterfacePtr<IUserDict> pUserDict(target, UseDefaultIID());

	if (document != nil)
	{
        /* now handle case insensitive words */
        if (!bCaseSensitive)
            wideRWord.ToLower();    /* lowercase implies "case in-sensitive" in the proximity lib, and now hyph exceptions */

		/* HH 1/6/00 */
		InterfacePtr<IHyphExceptionsPrefs> hePrefs((IHyphExceptionsPrefs*)::QueryPreferences(IID_IHYPHEXCEPTIONPREFS, document));
		if (hePrefs && hePrefs->GetHyphExceptionType() == IHyphExceptionsPrefs::kBoth)
		{
			/* is equivalent rWord (case & hyphenation does not matter) is in the user dictionary */
			if (udStrList.Location(wideRWord) > -1)
			{
				PMString conflictString("HE_DupHyphSettings");
				int32 retval = CAlert::ModalAlert( 	conflictString,
													kYesString,
													kNoString,
													kNullString, /* 0 */ 1, //forced to have a default button although this alert should not!!! HH 4/24/01 #427382
													CAlert::eQuestionIcon );

				if (retval != 1)
					return kFalse;
			}
		}

		InterfacePtr<IHyphenationExceptions> he(document, IID_IHYPHENATIONEXCEPTIONS);

		if (he)	/* plugin not required so verify it's available */
		{
			if (pLanguage)
			{
				HyphenExceptions hyphenExceptions(pLanguage);
				const HyphenExceptions	*pHyphenExceptions;

				if (he->GetHyphenExceptionsByLanguage(&pHyphenExceptions, pLanguage))
					hyphenExceptions = *pHyphenExceptions;

				UserDictWordList& exceptionStrings = (action == kAddToDict) ? hyphenExceptions.fStrings : hyphenExceptions.fNotStrings;

				index = exceptionStrings.Location(wideRWord);	/* check to see if the if it's in the list (stripped and case insensitive) */
				if (index > -1)
					exceptionStrings.Remove(index); 			/* remove so we can replace it below */

				exceptionStrings.InsertUnique(wideRWord);

				// A word cannot be in a pubs added list AND removed list at the same time.
				// When adding a word, we need to remove it from the other list if it is in that list.
				// #341354		Lin Xia  2/22/2000

				// If exceptionStrings is the added list, exceptionStrings2 is the removed list.
				// If execptinoStrings is the removed list, exceptionStrings2 is the addes list.
				UserDictWordList& exceptionStrings2 = (action == kAddToDict) ? hyphenExceptions.fNotStrings : hyphenExceptions.fStrings;

				index = exceptionStrings2.Location(wideRWord);	/* check to see if the if it's in the list (stripped and case insensitive) */
				if (index > -1)
					exceptionStrings2.Remove(index); 			/* remove so we can replace it below */

				InterfacePtr<ICommand>	cmd(CmdUtils::CreateCommand(kSetHyphExceptionByLanguageCmdBoss));
				InterfacePtr<IHyphExceptionByLanguageCmdData> data(cmd, IID_IHYPHEXCEPTIONBYLANGUAGECMDDATA);
				{
					IDataBase* db = ::GetDataBase(document);	/* Lin Xia 2/14/00 */
					CmdUtils::AutoUndoSequencePtr seq(db);

					data->Set(hyphenExceptions, pLanguage);
					cmd->SetItemList(UIDList(db));
					CmdUtils::ProcessCommand(cmd);
					bAdded = kTrue;
				}

				/* HH 11/18/99 */
				if (aPoints.size() > 0)
				{
					if (hePrefs && hePrefs->GetRecompose())
					{
						InterfacePtr<IGlobalRecompose> globalRecompose(document, IID_IGLOBALRECOMPOSE);
						if (globalRecompose)
						{
							IDataBase* db = ::GetDataBase(globalRecompose);
							CmdUtils::AutoUndoSequencePtr seq(db);

							globalRecompose->RecomposeAllStories();	/* very costly */
						}
					}
				}
			}
		}
	}
	else	/* modifying the user dictionary */
	{
		if (aWord.Length() > kUIWordLimit)
		{
			PMString string = "kUserDictionaryWordTooLong";
			string.Translate();
			CAlert::WarningAlert(string);
			return kFalse;
		}

		if (!pUserDictService)
			return kFalse;

		bool16 bIgnoredPanel = kFalse;

		if (action == kRemoveFromDict)
		{
			bAdded = pUserDictService->RemoveFromMainDict(aWord);
		}
		else if (action == kAddToDict)
		{
			//bool16 caseSensitive = kFalse;
			//InterfacePtr<ISpellPanelOptions> spellPanelOptions((ISpellPanelOptions*)::QuerySessionPreferences(IID_ISPELLPANELOPTIONS));
			//if (spellPanelOptions)
			//	caseSensitive = spellPanelOptions->GetCaseSensitive();

			bAdded = pUserDictService->AddToUserDict(pUserDict, aWord, &aPoints, bCaseSensitive);
		}
		else if (action == kIgnoreDict)	/* now supporting ignored words in this dialog */
		{
			InterfacePtr<ISpellPanelOptions> spellPanelOptions((ISpellPanelOptions*)::QuerySessionPreferences(IID_ISPELLPANELOPTIONS));

			if (!spellPanelOptions || aWord.Length() == 0)
				return kFalse;

			if (spellPanelOptions->IsIgnored(aWord))
				return kFalse;

			InterfacePtr<ICommand> applyOptionsCmd(CmdUtils::CreateCommand( kApplySpellPanelOptionsCmdBoss));
			InterfacePtr<ISpellPanelOptions> cmdData(applyOptionsCmd, IID_ISPELLPANELOPTIONS);

			if (!applyOptionsCmd || !cmdData)
				return kFalse;

			cmdData->CopyFrom(spellPanelOptions);	/* copy previous settings */
			cmdData->AddToIgnoreList(aWord);	/* add word to ignored list */
			CmdUtils::ExecuteCommand(applyOptionsCmd);

			bIgnoredPanel = kTrue;
			//bAdded = kTrue;
		}

		/* HH 11/8/99 Update the Hyph Exceptions on the fly */
		if (!bIgnoredPanel && bAdded)
		{
			InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IDocumentList>	documentList(theApp->QueryDocumentList());
			for (int32 i = 0; i < documentList->GetDocCount(); ++i)
			{
				IDocument* doc = documentList->GetNthDoc(i);
				InterfacePtr<IHyphExceptionsPrefs> hePrefs((IHyphExceptionsPrefs*)::QueryPreferences(IID_IHYPHEXCEPTIONPREFS, doc));
				if (hePrefs && hePrefs->GetStoreInDocument())
				{
					InterfacePtr<IHyphenationExceptions> he(::GetUIDRef(doc), IID_IHYPHENATIONEXCEPTIONS);
					if (he)
					{
						if (pLanguage)
						{
							HyphenExceptions hyphenExceptions(pLanguage);
							const HyphenExceptions	*pHyphenExceptions;

							if (he->GetHyphenExceptionsByLanguage(&pHyphenExceptions, pLanguage))
								hyphenExceptions = *pHyphenExceptions;

							bool16 doCommand = kFalse;

							if (action == kRemoveFromDict)
							{
								index = hyphenExceptions.fNotStrings.Location(wideRWord);
								if (index > -1)
									hyphenExceptions.fNotStrings.Remove(index);

								hyphenExceptions.fNotStrings.InsertUnique(wideRWord);
								doCommand = kTrue;
							}
							else if (action == kAddToDict)
							{
								index = hyphenExceptions.fStrings.Location(wideRWord);
								if (index > -1)
									hyphenExceptions.fStrings.Remove(index);

								hyphenExceptions.fStrings.InsertUnique(wideRWord);
								doCommand = kTrue;
							}

							if (doCommand)
							{
								InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetHyphExceptionByLanguageCmdBoss));
								InterfacePtr<IHyphExceptionByLanguageCmdData> data(cmd, IID_IHYPHEXCEPTIONBYLANGUAGECMDDATA);

								IDataBase* db = ::GetDataBase(doc);	/* HH 1/14/00 */
								CmdUtils::AutoUndoSequencePtr seq(db);
								data->Set(hyphenExceptions, pLanguage);
								cmd->SetItemList(UIDList(db));
								CmdUtils::ProcessCommand(cmd);
							}
						}
					}
				}

				/* HH 11/18/99 We may be able to move this to get some optimization */
				if (aPoints.size() > 0)
				{
					if (hePrefs && hePrefs->GetRecompose())
					{
						InterfacePtr<IGlobalRecompose> globalRecompose(doc, IID_IGLOBALRECOMPOSE);
						if (globalRecompose)
						{
							IDataBase* db = ::GetDataBase(globalRecompose);
							CmdUtils::AutoUndoSequencePtr seq(db);

							globalRecompose->RecomposeAllStories();	/* very costly */
						}
					}
				}
			}
		}
	}

	return bAdded;
}

/******************************************************************************
 * PrivateSpellingUtils::ModifyDictionary - separate a text model range into it's individual thread ranges
 * with one special behavior, if the range is the entire text model or entire text model minus one it will
 * return only the primary story range. The special behavior is an optimization for how this method is
 * used which is to determine which lines to inval. If it the entire text model then all the lines should
 * be invaled which at least in the case of the story editor will be covered by returning the primary
 * model range
 ******************************************************************************/
std::vector<RangeData> PrivateSpellingUtils::GetThreadRanges(ITextModel *model, RangeData fullRange)
{
	std::vector<RangeData> threadRanges;
	
	if (fullRange.Start(nil) == 0 && fullRange.End() >= model->TotalLength()-1)
	{
		int32 primaryRange = model->GetPrimaryStoryThreadSpan()-1;
		RangeData primaryMinusOne = (0 == primaryRange) ? RangeData(0, RangeData::kLeanForward) : RangeData(0, primaryRange);
		threadRanges.push_back(primaryMinusOne);
	}
	else
	{
		TextIndex threadIndex = fullRange.Start(nil);
		do
		{
			RangeData threadRange = model->GetStoryThreadRange(threadIndex);
			RangeData clippedThreadMinusOne = (threadIndex == threadRange.End()-1) ? RangeData(threadIndex, RangeData::kLeanForward) : RangeData(threadIndex, threadRange.End()-1);
			if (clippedThreadMinusOne.End() > fullRange.End())
			{
				// clip the range to not exceed the end
				clippedThreadMinusOne = (clippedThreadMinusOne.Start(nil) == fullRange.End()) ? RangeData(fullRange.End(), RangeData::kLeanForward) : RangeData(clippedThreadMinusOne.Start(nil), fullRange.End());
			}
			
			threadRanges.push_back(clippedThreadMinusOne);
			threadIndex = threadRange.End();
		} while (threadIndex < fullRange.End());
	}
	
	return threadRanges;
}

