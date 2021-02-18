//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/DynamicSpellCheckAdornment.cpp $
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

#include "IColorData.h"
#include "IGalleyTextAdornment.h"
#include "IGlobalTextAdornment.h"
#include "IGraphicsPort.h"
#include "IRangeData.h"
#include "ISpellingPrefs.h"
#include "ISpellingDataStrand.h"
#include "ISpellingService.h"
#include "ITextFocus.h"
#include "ITextModel.h"
#include "ITextOptions.h"
#include "IWaxGlyphs.h"
#include "IWaxGlyphsTOPTransform.h"
#include "IWaxLineSubLog.h"
#include "IWaxRenderData.h"
#include "IWaxRun.h"
#include "IWorkspace.h"
#include "IWaxGlyphsME.h"
#include "ITextLines.h"

#include "EffectiveTextMap.h"
#include "LineDescriptionME.h"
#include "textiterator.h"
#include "TEInputOutputMapping.h"

// Implementation headers
#include "AutoGSave.h"
#include "bossrecycler.h"
#include "CDynamicSpellCheckCache.h"
#include "CPMUnknown.h"
#include "K2Vector.h"
#include "LineDescription.h"
#include "PreferenceUtils.h"
#include "iuicolorutils.h"
#include "Utils.h"


#ifdef DEBUG
bool16 gDrawPurpleCache = kFalse;
bool16 gDrawRunOriginPt = kFalse;
bool16 gPaintInvalRect = kFalse;
#endif


class DynamicSpellCheckAdornment : public CPMUnknown<IGlobalTextAdornment>
{
public:
	DynamicSpellCheckAdornment(IPMUnknown *boss) :
		CPMUnknown<IGlobalTextAdornment>(boss)
		{ }

	virtual Text::DrawPriority GetDrawPriority() { return kTAPriDynamicSpellCheck; }
	virtual bool16 	GetHasInkBounds() { return kTrue; }
	virtual void 	GetInkBounds(PMRect *inkBounds, const IWaxRun *waxRun, const IWaxRenderData *renderData, const IWaxGlyphs *waxGlyphs);
	virtual void 	Draw(GraphicsData* gd, int32 iShapeFlags, const IWaxRun *waxRun, const IWaxRenderData *renderData, const IWaxGlyphs *waxGlyphs);

	virtual bool16 	GetCheckIsActive() { return kTrue; }
	virtual bool16 	GetIsActive(const IParcelShape* parcelShape,
								const ITextOptions *textOptions,
   								int32 iShapeFlags);

	virtual bool16 	GetCheckCouldDraw() { return kFalse; } // dwaterfa: CouldDraw != IsActive
	virtual bool16 	GetCouldDraw(const IWaxRun *, const IWaxRenderData *, const IWaxGlyphs *) { return kTrue; }

	virtual void 	StartOfParcelDraw(GraphicsData* gd, int32 iShapeFlags, const IParcelShape* parcelShape) {return;}
	virtual void 	EndOfParcelDraw(GraphicsData* gd, int32 iShapeFlags, const IParcelShape* parcelShape) {return;}

private:
	bool16			WaxIsPathType(const IWaxRun *waxRun);
};

CREATE_PMINTERFACE(DynamicSpellCheckAdornment, kDynamicSpellCheckAdornmentImpl);
RECYCLE_BOSS(kDynamicSpellCheckAdornmentBoss, 1, 1, 1, "DynamicSpellCheck", nil)

class WidthAccessor
{
public:
	virtual float operator[](int32 i) const = 0;
};

class WaxWidthAccessor : public WidthAccessor
{
public:
	WaxWidthAccessor(const IWaxGlyphs* waxGlyphs)
	{
		fWaxGlyphs = waxGlyphs;
	}

	float operator[](int32 i) const { return ::ToFloat(fWaxGlyphs->GetCharWidthAt(i)); }

private:
	const IWaxGlyphs* fWaxGlyphs;
};

class GalleyWidthAccessor : public WidthAccessor
{
public:
	GalleyWidthAccessor(const float* xWidths)
	{
		fXWidths = xWidths;
	}

	float operator[](int32 i) const { return fXWidths[i];}

private:
	const float* fXWidths;
};

void GalleyCoreDrawME(IGraphicsPort* gPort, const IWaxRun* waxRun, ITextModel* textModel, CDynamicSpellCheckCache* dynamicSpellCheckCache, const PMPoint &drawPt, const PMReal& scale, const TextIndex tIndex, const int32 span, ITextLines* textLines);
void GalleyCoreDrawME(IGraphicsPort* gPort, const IWaxRun* waxRun, ITextModel* textModel, CDynamicSpellCheckCache* dynamicSpellCheckCache, const PMPoint &drawPt, const PMReal& scale, const TextIndex tIndex, const int32 span, ITextLines* textLines)
{
	ASSERT (textModel);
	InterfacePtr<ISpellingDataStrand> spellingStrand((ISpellingDataStrand*)textModel->QueryStrand(kSpellingStrandBoss, IID_ISPELLINGDATASTRAND));
	if (!spellingStrand)
		return;
	
	bool16 bInWord = kFalse;
	PMReal y = drawPt.Y() + (scale * 0.5);
	TextIndex wordWidth = 0;


	TextIndex displayIndex = textLines->ModelIndexToDisplayIndex(textLines->GetCurrentStoryIndex(), (TextIndex)tIndex);
	
	if (displayIndex == -1)
		return;

	int32 offsetIntoLine;
	int32 lineIndex = textLines->FindIndexOfLineAtDisplayOffset((TextIndex)displayIndex, offsetIntoLine, RangeData::kLeanForward);

	if (lineIndex == -1) 
		return;
		
	LineDescription line = textLines->GetLine(lineIndex, kTrue);
	
	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	ASSERT(spellingPrefs != nil);
	TextIterator iterator(textModel, tIndex);
	TextIndex wordStartIndex = tIndex;

	K2Vector<DSCCache>* dscCache = nil;

	/* save off the port info */
	AutoGSave autoGSave(gPort);
	gPort->newpath();
	gPort->setlinewidth(0.5 * scale);

	SpellingState spellingState = kSpellingCorrect;
	
	/* do not cache drawing while using typing cache (portions wont draw) */
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IDYNAMICSPELLINGRANGEDATA);
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	if (typingStart == -1 && typingEnd == -1 && dynamicSpellCheckCache)
	{
		dscCache = dynamicSpellCheckCache->GetCache();
		ASSERT_MSG(dscCache == nil, "dscCache == nil");

		TRACEFLOW_OBSOLETE("DSC", "new K2Vector<DSCCache>\n");
		dscCache = new K2Vector<DSCCache>;
	}
	
	for (int32 charIndex = 0; charIndex < span; charIndex++)
	{
		UTF32TextChar c = *iterator++;

		/* only check words, or at end of line */
		if (! PMCharFilters::SpellingIsWordChar(0, c) /* UnicodeClass::IsWhiteSpace(c) */ || charIndex == span - 1 || c == 0xfeff)
		{
			/* last character in this span of text */
			if (charIndex == span - 1)
			{
				if (! bInWord)
				{
					/* do not start on punctuation, actually I would like to say start on letter only but... */
					if (PMCharFilters::SpellingIsWordCharNoPunctuation(0, c) && c != 0xfeff /*UnicodeClass::IsLetter(c)*/)			// ##: DANGER hard-coded char value
					{
						wordStartIndex = tIndex + charIndex;
						bInWord = kTrue;
					}
				}
					
				if (bInWord && PMCharFilters::SpellingIsWordChar(0 ,c) /* UnicodeClass::IsLetter(c) */ && c != 0xfeff)
					wordWidth++;
			}

			if (bInWord)
			{
				int32 runCount;
				TextIndex runBegin;
				spellingState = spellingStrand->GetSpellingDataRun(wordStartIndex, &runCount, &runBegin);
				
				if (spellingState == kSpellingUnchecked)
				{
					if (dscCache)
					{
						delete dscCache;
						dscCache = nil;
					}
				}
				
				/* general check to see if range exclusion is on */
				if (typingStart > kInvalidTextIndex && typingEnd > kInvalidTextIndex)
				{
					/* strip off the period */
					int32 stripPeriod = 0;
					/* specific check to see if the wordStartIndex is in this range */
					
					if (runBegin + wordStartIndex - runBegin + runCount > typingStart && runBegin <= typingEnd)
					{
						wordWidth = 0;
						bInWord = kFalse;
						continue;
					}
				}
				

				/* if there is an error draw underline */
				ISpellingService::SpellResult spellResult = (ISpellingService::SpellResult)spellingState;
				if (spellResult != ISpellingService::kCorrect && spellingState != kSpellingUnchecked && wordWidth > 0)
				{
					RangeData modelRange(wordStartIndex, wordStartIndex + wordWidth);
					
					RangeData displayRange = textLines->ModelToDisplayRange(textLines->GetCurrentStoryIndex(), modelRange,0,0);
					
					TERangeList ioRanges;
					ioRanges.Append(TERange(TEPosition(displayRange.Start(nil) - line.displayStartOffset, 0), TEPosition(displayRange.End() - line.displayStartOffset - 1, kHundredPerCent)));
					line.fMEData->fIOMapping->InputToOutputRangesClientEncoding(ioRanges);

					int32 colorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();

					switch (spellResult)
					{
						case ISpellingService::kUncapitalizedWord:
							colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
							break;
						case ISpellingService::kUncapitalizedStartOfSentence:
							colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
							break;
						case ISpellingService::kRepeatedWord:
							colorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
							break;
						case ISpellingService::kIncorrectWord:
							colorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
							break;
						default:
							{
							colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
							ASSERT_MSG(kFalse, "Bogus spelling error");
							break;
							}
					}
					UIDRef underlineColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(colorIndex, nil);
					ColorArray rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(underlineColorUIDRef.GetDataBase(), underlineColorUIDRef.GetUID());

					/* Draw squiggle line */
					gPort->setrgbcolor(rgbColor[0], rgbColor[1], rgbColor[2]);
					
					for (int32 i=0;i < ioRanges.Size();i++)//be be changed later
					{
						PMRect r;
						r.Top(y);
						r.Bottom(y + (1.0 * scale));
						
						r.Left(line.xPosition + line.fMEData->fStrikes[ioRanges[i].a.index].xPosition + ioRanges[i].a.inner * (line.fMEData->fGlyphWidths[ioRanges[i].a.index]) / 100.0 + 1.0);
						r.Right(line.xPosition + line.fMEData->fStrikes[ioRanges[i].b.index].xPosition + ioRanges[i].b.inner * (line.fMEData->fGlyphWidths[ioRanges[i].b.index]) / 100.0);

						PMReal rWidth = r.Right() - r.Left();
						gPort->moveto(r.Left(), r.Top());

						if (dscCache)
						{
							DSCCache cache;

							cache.fColor = rgbColor;
							cache.fRect = r;
							cache.fWidth = rWidth;
							cache.fSpellResult = spellResult;

						#ifdef DEBUG
							if (gDrawPurpleCache)
							{
								UIDRef rgbUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockUIPurple, nil);	/* purple so we can see when the cache draws */
								ColorArray rgb = Utils<IUIColorUtils>()->GetRGBColorValue(rgbUIDRef.GetDataBase(), rgbUIDRef.GetUID());
								cache.fColor = rgb;
							}
						#endif /* DEBUG */

							dscCache->push_back(cache);
						}

						PMReal scaleValue = 1.0 * scale;
						int32 increment = ::ToInt32(scaleValue);
						if (increment < 1)
							increment = 1;
						bool16 top = kTrue;

						for (int32 j = 0; j < rWidth - 1; j += increment)
						{
							gPort->lineto(r.Left() + j + increment, top ? r.Bottom() : r.Top());
							top = !top;
						}

						gPort->stroke();
					}
				}
			} 	/* if (bInWord) */

			bInWord = kFalse;
			wordWidth = 0;
			continue;
		}

		if (! bInWord)
		{
			/* do not start on punctuation, actually I would like to say start on letter only but... */
			if (PMCharFilters::SpellingIsWordCharNoPunctuation(0,c) && c != 0xfeff /*UnicodeClass::IsLetter(c)*/)			// ##: DANGER hard-coded char value
			{
				wordStartIndex = tIndex + charIndex;
				bInWord = kTrue;
			}
		}
		
		if (bInWord && PMCharFilters::SpellingIsWordChar(0,c) /* UnicodeClass::IsLetter(c) */ && c != 0xfeff)
			wordWidth++;
	}

	if (dscCache)
	{
		dynamicSpellCheckCache->SetCacheFlag(kTrue);
		dynamicSpellCheckCache->SetCache(dscCache);
	}

	gPort->closepath();
}

void CoreDrawME(IGraphicsPort* gPort, const IWaxRun* waxRun, ITextModel* textModel, CDynamicSpellCheckCache* dynamicSpellCheckCache, const PMPoint &drawPt, const PMReal& scale, const TextIndex tIndex, const int32 span, bool16 isTOP, const IWaxGlyphs *waxGlyphs);
void CoreDrawME(IGraphicsPort* gPort, const IWaxRun* waxRun, ITextModel* textModel, CDynamicSpellCheckCache* dynamicSpellCheckCache, const PMPoint &drawPt, const PMReal& scale, const TextIndex tIndex, const int32 span, bool16 isTOP, const IWaxGlyphs *waxGlyphs)
{
	ASSERT (textModel);
	//ASSERT (spellingStrand);
	InterfacePtr<ISpellingDataStrand> spellingStrand((ISpellingDataStrand*)textModel->QueryStrand(kSpellingStrandBoss, IID_ISPELLINGDATASTRAND));
	if (!spellingStrand)
		return;

	InterfacePtr<const IWaxGlyphsME> waxGlyphsME(waxRun, UseDefaultIID());
	if (!waxGlyphsME) //if we don't have ME data, we cannot do anything here.
		return;

	TextIndex		wordWidth = 0;
	const float		*xWidths = waxGlyphs->PeekWidthsArray();
	const float		*xOffsets = waxGlyphsME->PeekLeftOffsetArray();
	TEInputOutputMapping* subLog = waxGlyphsME ? const_cast<TEInputOutputMapping *>(waxGlyphsME->GetLog()) : nil;

	bool16 bInWord = kFalse;
	Fixed xWidthOffset = 0;
	Fixed xWordStart = 0;
	PMReal y = drawPt.Y() + (scale * 0.5);

	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	ASSERT(spellingPrefs != nil);
	TextIterator iterator(textModel, tIndex);
	TextIndex wordStartIndex = tIndex;

	K2Vector<DSCCache>* dscCache = nil;

	/* save off the port info */
	AutoGSave autoGSave(gPort);

	gPort->newpath();
	gPort->setlinewidth(0.5 * scale);

	SpellingState spellingState = kSpellingCorrect;
	
	/* do not cache drawing while using typing cache (portions wont draw) */
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IDYNAMICSPELLINGRANGEDATA);
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	if (typingStart == -1 && typingEnd == -1 && dynamicSpellCheckCache && !isTOP)
	{
		dscCache = dynamicSpellCheckCache->GetCache();
		ASSERT_MSG(dscCache == nil, "dscCache == nil");

		TRACEFLOW_OBSOLETE("DSC", "new K2Vector<DSCCache>\n");
		dscCache = new K2Vector<DSCCache>;
	}

	for (int32 charIndex = 0; charIndex < span; charIndex++)
	{
		PMReal realWidth = ::ToPMReal(xWidths[charIndex]);
		
		xWidthOffset += ::ToFixed(realWidth);

		UTF32TextChar c = *iterator++;

		/* only check words, or at end of line */
		if (! PMCharFilters::SpellingIsWordChar(0, c) || charIndex == span - 1)
		{
			/* last character in this span of text */
			if (charIndex == span - 1)
			{
				if (! bInWord)
				{
					/* do not start on punctuation, actually I would like to say start on letter only but... */
					if (PMCharFilters::SpellingIsWordCharNoPunctuation(0, c) && c != kTextChar_ZeroSpaceNoBreak)
					{
						wordStartIndex = tIndex + charIndex;
						bInWord = kTrue;
						if (charIndex > 0)
							xWordStart = xWidthOffset - ::ToFixed(realWidth);
					}
				}

				if (bInWord && PMCharFilters::SpellingIsWordChar(0 ,c) /* UnicodeClass::IsLetter(c) */)
					wordWidth++;
			}

			if (bInWord)
			{
				int32 runCount;
				TextIndex runBegin;
				spellingState = spellingStrand->GetSpellingDataRun(wordStartIndex, &runCount, &runBegin);

				if (spellingState == kSpellingUnchecked)
				{
					if (dscCache)
					{
						delete dscCache;
						dscCache = nil;
					}
				}

				/* general check to see if range exclusion is on */
				if (typingStart > kInvalidTextIndex && typingEnd > kInvalidTextIndex)
				{
					/* strip off the period */
					int32 stripPeriod = 0;
					/* specific check to see if the wordStartIndex is in this range */
					
					if (runBegin + wordStartIndex - runBegin + runCount > typingStart && runBegin <= typingEnd)
					{
						wordWidth = 0;
						bInWord = kFalse;
						continue;
					}
				}
		
				/* if there is an error draw underline */
				ISpellingService::SpellResult spellResult = (ISpellingService::SpellResult)spellingState;
				if (spellResult != ISpellingService::kCorrect && spellingState != kSpellingUnchecked)
				{
					const IWaxLine *waxLine =  waxRun->GetWaxLine();
					TERangeList tmpRanges;

					tmpRanges.Append(TERange(TEPosition(tIndex - waxLine->TextOrigin(), 0), TEPosition(tIndex + span - waxLine->TextOrigin() - 1, kHundredPerCent)));

					subLog->InputToOutputRangesClientEncoding(tmpRanges);

					int32 runGlyphStart = tmpRanges[0].a.index;

					TERangeList ioRanges;

					ioRanges.Append(TERange(TEPosition(wordStartIndex - waxLine->TextOrigin(), 0), TEPosition(wordStartIndex + wordWidth - waxLine->TextOrigin() - 1, kHundredPerCent)));

					subLog->InputToOutputRangesClientEncoding(ioRanges);
					int32 colorIndex;

					switch (spellResult)
					{
						case ISpellingService::kUncapitalizedWord:
							colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
							break;
						case ISpellingService::kUncapitalizedStartOfSentence:
							colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
							break;
						case ISpellingService::kRepeatedWord:
							colorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
							break;
						case ISpellingService::kIncorrectWord:
							colorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
							break;
						default:
							colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
							ASSERT_MSG(kFalse, "Bogus spelling error");
							break;
					}

					UIDRef underlineColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(colorIndex, nil);
					ColorArray rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(underlineColorUIDRef.GetDataBase(), underlineColorUIDRef.GetUID());

					/* Draw squiggle line */
					gPort->setrgbcolor(rgbColor[0], rgbColor[1], rgbColor[2]);
					for (int32 i=0;i<ioRanges.Size();i++)
					{ 
						int32 startIdx = ioRanges[i].a.index - runGlyphStart;
						int32 endIdx = ioRanges[i].b.index - runGlyphStart;
						
						if (isTOP)
						{
							if (ioRanges[i].a.inner > 50)
								startIdx++;
							if (ioRanges[i].b.inner > 50)
								endIdx++;

							PMReal	xPosition = waxRun->GetXPosition();
							PMReal	yPosition = waxRun->GetYPosition();

							for (int32 glyphIndex = startIdx; glyphIndex < endIdx; glyphIndex++)
							{
								PMMatrix drawPosition = waxGlyphs->GetGlyphDrawPosition(glyphIndex);

								PMPoint glyphOrigin(drawPosition.GetXTranslation(), drawPosition.GetYTranslation());

								glyphOrigin.X() += xPosition;
								glyphOrigin.Y() += yPosition;

								PMMatrix	glyphEndMatrix;
								
								glyphEndMatrix.Translate(xWidths[glyphIndex], 0.);
								drawPosition.PreConcat(glyphEndMatrix);

								PMPoint glyphEnd(drawPosition.GetXTranslation(), drawPosition.GetYTranslation());
								
								glyphEnd.X() += xPosition;
								glyphEnd.Y() += yPosition;

								gPort->moveto(glyphOrigin.X(), glyphOrigin.Y());
								gPort->lineto(glyphEnd.X(), glyphEnd.Y());

								gPort->stroke();
							}
						}
						else
						{
							PMRect r;
							r.Top(y);
							r.Bottom(y + (1.0 * scale));
						
							PMReal xStartPos = waxRun->GetXPosition();
							for (int32 j=0;j<startIdx;j++)
								xStartPos += xWidths[j];
									
							PMReal xEndPos = waxRun->GetXPosition();
							for (int32 j=0;j<endIdx;j++)
								xEndPos += xWidths[j];

							r.Left(xStartPos + ioRanges[i].a.inner * xWidths[startIdx] / 100.0 + 1.0);
							r.Right(xEndPos + ioRanges[i].b.inner * xWidths[endIdx] / 100.0);

							PMReal rWidth = r.Right() - r.Left();
							gPort->moveto(r.Left(), r.Top());

							if (dscCache)
							{
								DSCCache cache;

								cache.fColor = rgbColor;
								cache.fRect = r;
								cache.fWidth = rWidth;
								cache.fSpellResult = spellResult;

						#ifdef DEBUG
								if (gDrawPurpleCache)
								{
									UIDRef rgbUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockUIPurple, nil);	/* purple so we can see when the cache draws */
									ColorArray rgb = Utils<IUIColorUtils>()->GetRGBColorValue(rgbUIDRef.GetDataBase(), rgbUIDRef.GetUID());
									cache.fColor = rgb;
								}
						#endif /* DEBUG */

								dscCache->push_back(cache);
							}

							PMReal scaleValue = 1.0 * scale;
							int32 increment = ::ToInt32(scaleValue);
							if (increment < 1)
								increment = 1;
							bool16 top = kTrue;

							for (int32 j = 0; j < rWidth - 1; j += increment)
							{
								gPort->lineto(r.Left() + j + increment, top ? r.Bottom() : r.Top());
								top = !top;
							}

							gPort->stroke();
						}

					}
				}
				
			} 	/* if (bInWord) */

			wordWidth = 0;
			bInWord = kFalse;
			continue;
		}

		if (! bInWord)
		{
			/* do not start on punctuation, actually I would like to say start on letter only but... */
			if (PMCharFilters::SpellingIsWordCharNoPunctuation(0,c) && c != kTextChar_ZeroSpaceNoBreak /*UnicodeClass::IsLetter(c)*/)			// ##: DANGER hard-coded char value
			{
				wordStartIndex = tIndex + charIndex;
				bInWord = kTrue;
			}
		}

		if (bInWord && PMCharFilters::SpellingIsWordChar(0,c) /* UnicodeClass::IsLetter(c) */)
			wordWidth++;

	}

	if (dscCache && ! isTOP)
	{
		if (dynamicSpellCheckCache)
		{
			dynamicSpellCheckCache->SetCacheFlag(kTrue);
			dynamicSpellCheckCache->SetCache(dscCache);
		}
	}

	gPort->closepath();
}

#ifndef qME
void CoreDraw(IGraphicsPort* gPort, const IWaxRun* waxRun, ITextModel* textModel, CDynamicSpellCheckCache* dynamicSpellCheckCache,
			  const PMPoint &drawPt, const PMReal& scale, const TextIndex tIndex, const int32 span, WidthAccessor& xWidths, bool16 isTOP,
			  IWaxGlyphs* waxGlyphs);
void CoreDraw(IGraphicsPort* gPort, const IWaxRun* waxRun, ITextModel* textModel, CDynamicSpellCheckCache* dynamicSpellCheckCache,
			  const PMPoint &drawPt, const PMReal& scale, const TextIndex tIndex, const int32 span, WidthAccessor& xWidths, bool16 isTOP,
			  IWaxGlyphs* waxGlyphs)
{
	ASSERT (textModel);
	InterfacePtr<ISpellingDataStrand> spellingStrand((ISpellingDataStrand*)textModel->QueryStrand(kSpellingStrandBoss, IID_ISPELLINGDATASTRAND));
	if (!spellingStrand)
		return;

	PMReal y = drawPt.Y() + (scale * 0.5);

	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	ASSERT(spellingPrefs != nil);

	K2Vector<DSCCache>* dscCache = nil;

	/* save off the port info */
	AutoGSave autoGSave(gPort);

	gPort->newpath();
	gPort->setlinewidth(0.5 * scale);

	SpellingState spellingState = kSpellingCorrect;

	/* do not cache drawing while using typing cache (portions wont draw) */
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IDYNAMICSPELLINGRANGEDATA);
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	if (typingStart == -1 && typingEnd == -1 && dynamicSpellCheckCache && !isTOP)
	{
		dscCache = dynamicSpellCheckCache->GetCache();
		ASSERT_MSG(dscCache == nil, "dscCache == nil");

		TRACEFLOW_OBSOLETE("DSC", "new K2Vector<DSCCache>\n");
		dscCache = new K2Vector<DSCCache>;
	}

	int32 runCount = 0;

	for (int32 spanIndex = 0; spanIndex < span; spanIndex+=runCount)
	{
		TextIndex runBegin;
		spellingState = spellingStrand->GetSpellingDataRun(spanIndex+tIndex, &runCount, &runBegin);
		if (runCount == 0)
		{
			runCount = 1;
			continue;
		}

		if (spellingState == kSpellingUnchecked)
		{
			if (dscCache)
			{
				delete dscCache;
				dscCache = nil;
			}
		}

		/* general check to see if range exclusion is on */
		if (typingStart > kInvalidTextIndex && typingEnd > kInvalidTextIndex)
		{
			/* specific check to see if the index is in this range */
			if (spanIndex+tIndex > typingStart && spanIndex+tIndex <= typingEnd)
			{
				spanIndex = typingEnd+1-tIndex;
				continue;
			}
		}

		/* if there is an error draw underline */
		ISpellingService::SpellResult spellResult = (ISpellingService::SpellResult)spellingState;
		if (spellResult != ISpellingService::kCorrect && spellingState != kSpellingUnchecked)
		{
			int32 colorIndex;

			switch (spellResult)
			{
				case ISpellingService::kUncapitalizedWord:
					colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
					break;
				case ISpellingService::kUncapitalizedStartOfSentence:
					colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
					break;
				case ISpellingService::kRepeatedWord:
					colorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
					break;
				case ISpellingService::kIncorrectWord:
					colorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
					break;
				default:
					colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
					//colorIndex = spellingPrefs->GetDynamicSpellColorIndex(spellResult);
//					ASSERT_MSG(kFalse, "Bogus spelling error");
					break;
			}

			UIDRef underlineColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(colorIndex, nil);
			ColorArray rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(underlineColorUIDRef.GetDataBase(), underlineColorUIDRef.GetUID());

			gPort->setrgbcolor(rgbColor[0], rgbColor[1], rgbColor[2]);

			if (isTOP)	// need to draw the underline under each character
			{
				ASSERT(waxRun);
				ASSERT(waxGlyphs);
				PMReal				xPosition = waxRun->GetXPosition();
				PMReal				yPosition = waxRun->GetYPosition();
				const PMPoint		waxRunOrigin(xPosition, yPosition);
#ifdef DEBUG
				if (gDrawRunOriginPt)
				{
					gPort->moveto(waxRunOrigin.X() - 2, waxRunOrigin.Y());
					gPort->lineto(waxRunOrigin.X() + 2, waxRunOrigin.Y());
					gPort->moveto(waxRunOrigin.X(), waxRunOrigin.Y() - 2);
					gPort->lineto(waxRunOrigin.X(), waxRunOrigin.Y() + 2);
				}
#endif
				int32 runTextOrigin = waxRun->TextOrigin();
				int32 charStart = spanIndex+tIndex - runTextOrigin;
				int32 numChars = waxRun->GetCharCount() - charStart;
				numChars = std::min(runCount, numChars);

				// Map then process the entire range of chars.
				int32 glyphIndex = -1;
				int32 glyphRangeEnd;
				{
					int32 glyphLength = 0;
					waxGlyphs->MapCharsToGlyphs(charStart, numChars, &glyphIndex, &glyphLength);
					ASSERT(glyphIndex != -1);					// bad mapping??

					glyphRangeEnd = glyphIndex + glyphLength;
				}

				PMReal yAdjust = 0.0;

				/* Draw squiggle line */
				for(; glyphIndex<glyphRangeEnd; glyphIndex++)
				{
					PMMatrix glyphMatrix;
					PMPoint penCorrection;

					bool16 ok = waxGlyphs->GetGlyphMatrix(glyphIndex, &glyphMatrix, &penCorrection);
					PMReal charWidth = waxGlyphs->GetWidthAt(glyphIndex);

					PMPoint glyphOrigin(waxRunOrigin);
					glyphOrigin.Y() = glyphOrigin.Y() + yAdjust;

					PMPoint glyphEnd(glyphOrigin);
					glyphEnd.X() = glyphEnd.X() + charWidth;

					glyphMatrix.Transform(&glyphOrigin);
					glyphMatrix.Transform(&glyphEnd);

					gPort->moveto(glyphOrigin.X(), glyphOrigin.Y());
					gPort->lineto(glyphEnd.X(), glyphEnd.Y());

					gPort->stroke();
				}
			}
			else
			{
				float floatStart = 0;
				int32 startIndex = 0;
				for (; startIndex < spanIndex; startIndex++)
				{
					floatStart += xWidths[startIndex];
				}
				float floatWidth = 0;
				int32 endIndex = std::min(spanIndex + runCount, span);
				for (int32 widthIndex = startIndex; widthIndex < endIndex; widthIndex++)
				{
					floatWidth += xWidths[widthIndex];
				}
				PMReal rStart(floatStart);
				PMReal rWidth(floatWidth);

				PMReal x = drawPt.X() + rStart;
				PMRect r;
				r.Top(y);
				r.Left(x);
				r.Bottom(y + (1.0 * scale));
				r.Right(r.Left() + rWidth);

				/* Draw squiggle line */
				gPort->moveto(r.Left(), r.Top());

				if (dscCache)
				{
					DSCCache cache;

					cache.fColor = rgbColor;
					cache.fRect = r;
					cache.fWidth = rWidth;
					cache.fSpellResult = spellResult;

				#ifdef DEBUG
					if (gDrawPurpleCache)
					{
						UIDRef rgbUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockUIPurple, nil);	/* purple so we can see when the cache draws */
						ColorArray rgb = Utils<IUIColorUtils>()->GetRGBColorValue(rgbUIDRef.GetDataBase(), rgbUIDRef.GetUID());
						cache.fColor = rgb;
					}
				#endif /* DEBUG */

					dscCache->push_back(cache);
				}

				PMReal scaleValue = 1.0 * scale;
				int32 increment = ::ToInt32(scaleValue);
				if (increment < 1)
					increment = 1;
				bool16 top = kTrue;

				for (int32 j = 0; j < rWidth - 1; j += increment)
				{
					gPort->lineto(r.Left() + j + increment, top ? r.Bottom() : r.Top());
					top = !top;
				}

				gPort->stroke();
			}
		}
	}

	if (dscCache && ! isTOP)
	{
		if (dynamicSpellCheckCache)
		{
			dynamicSpellCheckCache->SetCacheFlag(kTrue);
			dynamicSpellCheckCache->SetCache(dscCache);
		}
	}

	gPort->closepath();
}
#endif


bool16 DynamicSpellCheckAdornment::WaxIsPathType(const IWaxRun *waxRun)
{
    // first check if TextOnPath plugin is loaded
    InterfacePtr<const IWaxGlyphsTOPTransform> iTOPTransform(waxRun, UseDefaultIID());
    if (iTOPTransform == nil || !iTOPTransform->IsTopRun())
        return  kFalse;

    // If both arrays are nil, not a text on path run
    const PMMatrix*  pTransformArray = iTOPTransform->PeekGlyphTransformArray();
    const PMPoint*  pOffsetArray = iTOPTransform->PeekSelectionOffsetArray();

    return (pTransformArray && pOffsetArray);
}
//---------------------------------------------------------------
// DynamicSpellCheckAdornment::Draw
//---------------------------------------------------------------
void DynamicSpellCheckAdornment::Draw(GraphicsData* gd, int32 iShapeFlags, const IWaxRun *waxRun, const IWaxRenderData *renderData, const IWaxGlyphs *waxGlyphs)
{
	ASSERT_MSG(gd != nil, "gd != nil");
	ASSERT_MSG(waxRun != nil, "waxRun != nil");

	if ((iShapeFlags & (IShape::kPrinting | IShape::kPreviewMode)) || (renderData == nil) || (waxGlyphs == nil))
		return;

	bool16 isTOP = WaxIsPathType(waxRun);

	int32 glyphCount = waxGlyphs->GetGlyphCount();
	if (glyphCount == 0)
		return;

	const IWaxLine* waxLine = waxRun->GetWaxLine();
	InterfacePtr<ITextModel> textModel(waxLine->QueryTextModel());

	PMReal scale = 1.0;
	TextIndex tIndex = waxRun->TextOrigin();


	/* get port and save off state */
	IGraphicsPort* gPort = gd->GetGraphicsPort();
	ASSERT_MSG(gPort != nil, "gPort != nil");

	//
	// first check if TextOnPath plugin is here
	//
	PMMatrix* pTransformArray = nil;
	PMPoint* pOffsetArray = nil;
	if (waxRun->IsTOPRun())
	{
		InterfacePtr<IWaxGlyphsTOPTransform> iTOPTransform(waxRun, IWaxGlyphsTOPTransform::kDefaultIID);
		pTransformArray = const_cast<PMMatrix*>(iTOPTransform->PeekGlyphTransformArray());
		pOffsetArray = const_cast<PMPoint*>(iTOPTransform->PeekSelectionOffsetArray());
	}

	const PMPoint drawPt(waxRun->GetXPosition(), waxRun->GetYPosition());

	InterfacePtr<IDynamicSpellCheckCache> dynamicSpellCheckCache(waxRun, UseDefaultIID());
	if (dynamicSpellCheckCache && dynamicSpellCheckCache->GetCacheFlag())
	{
		//TRACEFLOW_OBSOLETE("DSC", "Cache drawing!\n");

		AutoGSave autoGSave(gPort);
		gPort->newpath();
		gPort->setlinewidth(0.5 * scale);

		K2Vector<DSCCache>* dscCache = nil;
		dscCache = dynamicSpellCheckCache->GetCache();

		InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));

		if (dscCache)
		{
			for (int32 i = 0; i < dscCache->size(); i++)
			{
				const DSCCache& cache = dscCache->at(i);

				int32 colorIndex;

				switch (cache.fSpellResult)
				{
					case ISpellingService::kUncapitalizedWord:
						colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
						break;
					case ISpellingService::kUncapitalizedStartOfSentence:
						colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
						break;
					case ISpellingService::kRepeatedWord:
						colorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
						break;
					case ISpellingService::kIncorrectWord:
						colorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
						break;
					default:
						colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
						//colorIndex = spellingPrefs->GetDynamicSpellColorIndex(cache.fSpellResult);
//						ASSERT_MSG(kFalse, "Bogus spelling error");
						break;
				}

				UIDRef underlineColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(colorIndex, nil);
				ColorArray rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(underlineColorUIDRef.GetDataBase(), underlineColorUIDRef.GetUID());

#ifdef DEBUG
				if (gDrawPurpleCache)
				{
					UIDRef rgbUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockUIPurple, nil);	/* purple so we can see when the cache draws */
					rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(rgbUIDRef.GetDataBase(), rgbUIDRef.GetUID());
				}
#endif /* DEBUG */

				//gPort->setrgbcolor(cache.fColor[0], cache.fColor[1], cache.fColor[2]); do not cache color, in case preferences change
				gPort->setrgbcolor(rgbColor[0], rgbColor[1], rgbColor[2]);
				gPort->moveto(cache.fRect.Left(), cache.fRect.Top());

				PMReal scaleValue = 1.0 * scale;
				int32 increment = ::ToInt32(scaleValue);
				if (increment < 1)
					increment = 1;
				bool16 top = kTrue;

				for (int32 j = 0; j < cache.fWidth - 1; j += increment)
				{
					gPort->lineto(cache.fRect.Left() + j + increment, top ? cache.fRect.Bottom() : cache.fRect.Top());
					top = !top;
				}

				gPort->stroke();
			}
		}

		gPort->closepath();
		//TRACEFLOW_OBSOLETE("DSC", "End Cache drawing!\n");
	}
	else
	{
		InterfacePtr</*const*/ IWaxGlyphs> waxRunGlyphs(waxRun, UseDefaultIID());
		WaxWidthAccessor wa(waxRunGlyphs);

#ifndef qME
		InterfacePtr<IWaxLineSubLog> waxLineSubLog(waxLine, UseDefaultIID()) ;
		TEInputOutputMapping& subLog =  const_cast<TEInputOutputMapping&>(waxLineSubLog->GetLog());
		if (subLog.GetInputCount())
		{
#endif
			int32 rangeStart, runSpan;
			waxGlyphs->MapGlyphsToChars(0, waxGlyphs->GetGlyphCount(), &rangeStart, &runSpan);
			CoreDrawME(gPort, waxRun, static_cast<ITextModel*>(textModel), static_cast<CDynamicSpellCheckCache*>((static_cast<IDynamicSpellCheckCache*>(dynamicSpellCheckCache))), drawPt, scale, tIndex, runSpan, isTOP, waxGlyphs);
#ifndef qME
		}
		else
		{
			int32 runSpan = waxRun->GetCharCount();
			CoreDraw(gPort, waxRun, static_cast<ITextModel*>(textModel), static_cast<CDynamicSpellCheckCache*>((static_cast<IDynamicSpellCheckCache*>(dynamicSpellCheckCache))), drawPt, scale, tIndex, runSpan, wa, isTOP, waxRunGlyphs);
		}
#endif
	}
}


void DynamicSpellCheckAdornment::GetInkBounds(PMRect* inkBounds,
											  const IWaxRun* waxRun,
											  const IWaxRenderData* renderData,
											  const IWaxGlyphs* waxGlyphs)
{
	ASSERT_MSG(inkBounds != nil, "inkBounds != nil");
	ASSERT_MSG(waxRun != nil, "waxRun != nil");

	if (renderData == nil || waxGlyphs == nil)			// We only deal with TextRuns (i.e. those that have Glyphs and RenderData)
		return;

	// Add our ink bounds.
	const PMReal yScale = renderData->GetFontMatrix().GetYScale();
	const PMReal xPosition = waxRun->GetXPosition();
	const PMReal yPosition = waxRun->GetYPosition();

	inkBounds->Left(xPosition);
	inkBounds->Right(xPosition + waxGlyphs->GetWidth());
	//inkBounds->Top(yPosition - (yScale * 0.85) - (1.51/2));	 //	vertical +  1/2 line width
	//inkBounds->Bottom(yPosition	+ (yScale *	0.10) + (1.51/2)); // horizonal + 1/2 line width
	inkBounds->Top(yPosition);
	inkBounds->Bottom(yPosition	+ 1.0);
}

bool16 DynamicSpellCheckAdornment::GetIsActive(const IParcelShape* parcelShape,
												const ITextOptions *textOptions,
   												int32 iShapeFlags)
{
	if (iShapeFlags & (IShape::kPrinting | IShape::kPreviewMode))
		return kFalse;

	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	return spellingPrefs ? spellingPrefs->GetDynamicSpellCheck() : kFalse;
}


class GalleyDynamicSpellCheckAdornment : public CPMUnknown<IGalleyTextAdornment>
{
public:
	GalleyDynamicSpellCheckAdornment(IPMUnknown *boss) :
		CPMUnknown<IGalleyTextAdornment>(boss)
		{ }

	virtual bool16 	GetHasInkBounds() { return kTrue; }
	virtual void 	GetInkBounds(PMRect *inkBounds/* , IWaxRun *waxRun, IWaxRenderData *renderData, IWaxGlyphs *waxGlyphs */);
	virtual void 	Draw(IGraphicsPort* gPort, ITextModel* model, RunDescription* rd, TextIndex runStart, int32 runLength,
							const PMPoint &drawPt, float * xWidths, const PMReal& displaySize,
							int32 lineIndex, int32 runIndex, ITextLines *textLines, const PMRect &runRect);

	virtual bool16 	GetCheckIsActive() { return kTrue; }
	virtual bool16 	GetIsActive(const IParcelShape* parcelShape, const ITextOptions *textOptions, int32 iShapeFlags, ITextLines *textLines);

	virtual bool16 	GetCheckCouldDraw() { return kFalse; }
};

CREATE_PMINTERFACE(GalleyDynamicSpellCheckAdornment, kGalleyDynamicSpellCheckAdornmentImpl)
//RECYCLE_BOSS(kGalleyDynamicSpellCheckAdornmentBoss, 1, 1, 1, "DynamicSpellCheck", nil)

//---------------------------------------------------------------
// GalleyDynamicSpellCheckAdornment::Draw
//---------------------------------------------------------------
void GalleyDynamicSpellCheckAdornment::Draw(IGraphicsPort* gPort, ITextModel* textModel, RunDescription* rd, TextIndex runStart, int32 runLength,
					const PMPoint &drawPt, float * xWidths, const PMReal& displaySize,
					int32 lineIndex, int32 runIndex, ITextLines *textLines, const PMRect &runRect)
{
	ASSERT_MSG(gPort != nil, "gPort != nil");
	ASSERT_MSG(textModel != nil, "textModel != nil");

	const int32 glyphCount = runLength;
	if (runLength == 0)
		return;

	const TextIndex tIndex = runStart;

	IDataBase* db = ::GetDataBase(textModel);
	PMReal scale = displaySize / 10.0;

	if (rd && rd->fDynamicSpellCheckCache && rd->fDynamicSpellCheckCache->GetCacheFlag())
	{
		//TRACEFLOW_OBSOLETE("DSC", "Cache (galley) drawing!\n");

		AutoGSave autoGSave(gPort);
		gPort->newpath();
		gPort->setlinewidth(0.5 * scale);

		const K2Vector<DSCCache>* dscCache = rd->fDynamicSpellCheckCache->GetCache();

		if (dscCache)
		{
			const PMReal& top = drawPt.Y() + (scale * 0.5);
			PMReal bottom = top + (1.0 * scale);

			InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));

			for (int32 i = 0; i < dscCache->size(); i++)
			{
				const DSCCache& cache = dscCache->at(i);

				int32 colorIndex;

				switch (cache.fSpellResult)
				{
					case ISpellingService::kUncapitalizedWord:
						colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
						break;
					case ISpellingService::kUncapitalizedStartOfSentence:
						colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
						break;
					case ISpellingService::kRepeatedWord:
						colorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
						break;
					case ISpellingService::kIncorrectWord:
						colorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
						break;
					default:
						colorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
						//colorIndex = spellingPrefs->GetDynamicSpellColorIndex(cache.fSpellResult);
//						ASSERT_MSG(kFalse, "Bogus spelling error");
						break;
				}

				UIDRef underlineColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(colorIndex, nil);
				ColorArray rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(underlineColorUIDRef.GetDataBase(), underlineColorUIDRef.GetUID());

#ifdef DEBUG
				if (gDrawPurpleCache)
				{
					UIDRef rgbUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockUIPurple, nil);	/* purple so we can see when the cache draws */
					rgbColor = Utils<IUIColorUtils>()->GetRGBColorValue(rgbUIDRef.GetDataBase(), rgbUIDRef.GetUID());
				}
#endif /* DEBUG */

				//gPort->setrgbcolor(cache.fColor[0], cache.fColor[1], cache.fColor[2]);
				gPort->setrgbcolor(rgbColor[0], rgbColor[1], rgbColor[2]);
				gPort->moveto(cache.fRect.Left(), /* cache.fRect.Top() */ top);

				PMReal scaleValue = 1.0 * scale;
				int32 increment = ::ToInt32(scaleValue);
				if (increment < 1)
					increment = 1;
				bool16 bTop = kTrue;

				for (int32 j = 0; j < cache.fWidth - 1; j += increment)
				{
					gPort->lineto(cache.fRect.Left() + j + increment, bTop ? bottom /* cache.fRect.Top() */ : top /* cache.fRect.Bottom() */);
					bTop= !bTop;
				}

				gPort->stroke();
			}
		}

		gPort->closepath();
		//TRACEFLOW_OBSOLETE("DSC", "End Cache (galley) drawing!\n");
	}
	else
	{
		if (rd && ! rd->fDynamicSpellCheckCache)
		{
			TRACEFLOW_OBSOLETE("DSC", "new CDynamicSpellCheckCache\n");
			rd->fDynamicSpellCheckCache = new CDynamicSpellCheckCache(nil);
		}

		GalleyWidthAccessor wa(xWidths);
        
        LineDescription line = textLines->GetLine(lineIndex, kTrue);
		if(line.fMEData && line.fMEData->fIsRTL)
        {
            InterfacePtr<ITextLines> textLinesME(this, IID_ITEXTLINES);
            GalleyCoreDrawME(gPort, nil, textModel, rd ? rd->fDynamicSpellCheckCache : nil, drawPt, scale, tIndex, glyphCount, textLinesME);
        }
        else
        {
            CoreDraw(gPort, nil, textModel, rd ? rd->fDynamicSpellCheckCache : nil, drawPt, scale, tIndex, glyphCount, wa, kFalse, nil);
        }
	}
}


#if 1
void GalleyDynamicSpellCheckAdornment::GetInkBounds(PMRect* inkBounds /*, IWaxRun* waxRun, IWaxRenderData* renderData, IWaxGlyphs* waxGlyphs*/)
{
	ASSERT_MSG(inkBounds != nil, "inkBounds != nil");
	//ASSERT_MSG(waxRun != nil, "waxRun != nil");

	//if (renderData == nil || waxGlyphs == nil)			// We only deal with TextRuns (i.e. those that have Glyphs and RenderData)
	//	return;

	// Add our ink bounds.
	//const PMReal yScale = renderData->GetFontMatrix().GetYScale();
	//const PMReal xPosition = waxRun->GetXPosition();
	//const PMReal yPosition = waxRun->GetYPosition();

	//inkBounds->Left(xPosition);
	//inkBounds->Right(xPosition + waxGlyphs->GetWidth());
	//inkBounds->Top(yPosition - (yScale * 0.85) - (1.51/2));	 //	vertical +  1/2 line width
	//inkBounds->Bottom(yPosition	+ (yScale *	0.10) + (1.51/2)); // horizonal + 1/2 line width
	//inkBounds->Top(yPosition);
	inkBounds->Bottom(inkBounds->Bottom() + 1.0);
}
#endif

bool16 GalleyDynamicSpellCheckAdornment::GetIsActive(const IParcelShape* parcelShape, const ITextOptions *textOptions, int32 iShapeFlags, ITextLines *textLines)
{
	//if (iShapeFlags & (IShape::kPrinting | IShape::kPreviewMode))
	//	return kFalse;

	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
	return spellingPrefs ? spellingPrefs->GetDynamicSpellCheck() : kFalse;
}
