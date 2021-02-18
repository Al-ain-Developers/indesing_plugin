//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextTips.cpp $
//  
//  Owner: Wai Cheuk
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

// ---- plugin headers
#include "ConditionalTextUIID.h"
#include "TextEditorID.h"

// ---- implementation headers
#include "K2SmartPtr.h"
#include "PMString.h"
                   
// ---- interface headers
#include "IAttrReport.h"
#include "IComposeScanner.h"
#include "IConditionTag.h"
#include "IPanelControlData.h"
#include "IStoryRefData.h"	// for galley writing mode, not the note writing mode
#include "ITextAttrUIDList.h"
#include "ITextLines.h"
#include "ITextModel.h"
#include "ITextRuns.h"
#include "ITextStoryThread.h"
#include "AbstractTip.h"

// ---- utilities headers
#include "IDocumentPresentation.h"
#include "IDocumentUIUtils.h"
#include "IGalleyUtils.h"
#include "ILayoutUIUtils.h"
#include "INoteUtils.h"
#include "StringUtils.h"
#include "IWindowUtils.h"

#define kMaxTipsChars		1000	// maximum number of characters allowed in the tips
#define kMaxTipsLines		40		// maximum number of lines (carriage return or force line feed) allowed

//----------------------------------------------------------------------------------------
// SuperClass CConditionalTextTip
//----------------------------------------------------------------------------------------

class CConditionalTextTip : public AbstractTip
{			
	public:
		CConditionalTextTip(IPMUnknown *boss): AbstractTip(boss) {}
		virtual ~CConditionalTextTip() {}
		
	protected:
		virtual bool16 GetShowTipsState();
		virtual PMString GetTipContent(ITextStoryThread* storyThread);

private:
		PMString GetHiddenTextContent(ITextStoryThread* storyThread);
};

//----------------------------------------------------------------------------------------
//
// CConditionalTextTip::GetShowTipsState
//
//----------------------------------------------------------------------------------------
bool16 CConditionalTextTip::GetShowTipsState()
{
 	return kTrue;		
}

PMString CConditionalTextTip::GetHiddenTextContent(ITextStoryThread* storyThread)
{
	PMString tempStr;

	WideString copyText;
	InterfacePtr<ITextModel> textModel(storyThread->QueryTextModel());
	InterfacePtr<IComposeScanner> scanner(textModel, IID_ICOMPOSESCANNER);

	// first, pass the character count requirement, change the threadSpan
	bool16 overflow = storyThread->GetTextSpan() > kMaxTipsChars;
	int32 threadSpan = overflow ? kMaxTipsChars : storyThread->GetTextSpan();

	// second, pass the carriage return requirement, change the threadSpan
	int32 returnCount = 0; 
	TextIndex pos = storyThread->GetTextStart();
	TextIterator iter(textModel, storyThread->GetTextStart());
	TextIndex end = storyThread->GetTextEnd();
	for ( ; iter.Position() < end; ++iter )
	{
		if (*iter == kTextChar_CR || *iter == kTextChar_LF)
		{
			++returnCount;
			if (returnCount > kMaxTipsLines) {
				threadSpan = iter.Position() - storyThread->GetTextStart();
				overflow = kTrue;
				break;
			}
		}
	}

	scanner->CopyText(storyThread->GetTextStart(), threadSpan-1, &copyText);

	int32 rawTipsLength;
	const uchar16* rawTipText = copyText.GrabUTF16Buffer(&rawTipsLength);

	PMString hiddenText;
	Utils<INoteUtils>()->ConvertNoteTipText(rawTipText, rawTipsLength, hiddenText);

	if (overflow)
		hiddenText.AppendW(kTextChar_Ellipse);

	PMString hiddenContent;
	hiddenContent.SetString(hiddenText);

	tempStr.Append("\n");

	// add open quote
	tempStr.Append("\"");

	// add note content
	tempStr.Append(hiddenContent, hiddenContent.CharCount());

	// add close quote
	tempStr.Append("\"");

	return tempStr;
}

PMString CConditionalTextTip::GetTipContent(ITextStoryThread* storyThread)
{
	InterfacePtr<ITextModel> textModel(storyThread->QueryTextModel());
	InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
	InterfacePtr<IAttrReport> attr((IAttrReport*)composeScanner->QueryAttributeAt(storyThread->GetTextStart(), storyThread->GetTextEnd(), kConditionalTextAttributeBoss));
	InterfacePtr<ITextAttrUIDList> attrData(attr, UseDefaultIID());
	if (attrData)
	{
		K2Vector<UID> tagsApplied = attrData->Get();
		int32 howmany = tagsApplied.size();
		PMString tempStr("#ConditionalTextTip", PMString::kTranslateDuringCall);
		PMString tagStr (howmany > 1? "#ConditionalTextTipManyTags" : "#ConditionalTextTipOneTag", PMString::kTranslateDuringCall);
		::ReplaceStringParameters (&tempStr,tagStr);

		for (K2Vector<UID>::const_iterator ta = tagsApplied.begin(); ta != tagsApplied.end(); ta++)
		{
			InterfacePtr<IConditionTag> tag(::GetDataBase(textModel), *ta, UseDefaultIID());
			WideString tagName = tag->GetName();
			tempStr.Append("\r   \"");
			tempStr.Append(tagName);
			tempStr.Append("\"");
		}

		PMString hiddenContent = this->GetHiddenTextContent(storyThread);
		tempStr.Append(hiddenContent);

		return tempStr;
	}
	return PMString();
}


//----------------------------------------------------------------------------------------
// Class ConditionalTextLayoutTip
//----------------------------------------------------------------------------------------

class ConditionalTextLayoutTip : public CConditionalTextTip
{			
public:
	typedef CConditionalTextTip Inherited;

	ConditionalTextLayoutTip(IPMUnknown *boss);
	virtual ~ConditionalTextLayoutTip() {}

	virtual PMString GetTipText(const PMPoint& mouseLocation);
	

	DECLARE_HELPER_METHODS()
};



CREATE_PMINTERFACE(ConditionalTextLayoutTip, kConditionalTextLayoutTipImpl)
DEFINE_HELPER_METHODS( ConditionalTextLayoutTip )


//----------------------------------------------------------------------------------------
//
// ConditionalTextLayoutTip::Constructor
//
//----------------------------------------------------------------------------------------
ConditionalTextLayoutTip::ConditionalTextLayoutTip(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss), Inherited(boss)
{
} 

//----------------------------------------------------------------------------------------
//
// ConditionalTextLayoutTip::GetTipText
//
//----------------------------------------------------------------------------------------
PMString ConditionalTextLayoutTip::GetTipText(const PMPoint& mouseLocation)
{
	if (this->GetShowTipsState() == kFalse)
		return PMString();

	IDocumentPresentation* frontDocPres = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();
	InterfacePtr<ILayoutControlData> lcd(Utils<ILayoutUIUtils>()->QueryLayoutData(frontDocPres));
	InterfacePtr<IControlView> frontView(lcd, UseDefaultIID());

	if (!frontView)
		return PMString("");
	
	if (Utils<IGalleyUtils>()->InGalleyOrStory())
		return PMString("");

	IPMUnknown* hitObj = nil;
	if (::GetClass(this) == kHiddenTextBoss)
		hitObj = QueryInterface(IID_IUNKNOWN);
	ASSERT_MSG(hitObj, "Didn't find tip for conditional text!");

	InterfacePtr<const IPMUnknown> autoreleaseHitObj(hitObj);

	if (hitObj && ::GetClass(hitObj) == kHiddenTextBoss)
	{
		InterfacePtr<ITextStoryThread> storyThread(hitObj, UseDefaultIID());
		if (storyThread)
		{
			return GetTipContent(storyThread);
		}
	}
	return PMString("");
} 




//----------------------------------------------------------------------------------------
// Class ConditionalTextGalleyTip
//----------------------------------------------------------------------------------------

class ConditionalTextGalleyTip : public CConditionalTextTip
{			
public:
	typedef CConditionalTextTip Inherited;

	ConditionalTextGalleyTip(IPMUnknown *boss);
	virtual ~ConditionalTextGalleyTip() {}

	virtual PMString GetTipText(const PMPoint& mouseLocation);
	
	DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE( ConditionalTextGalleyTip, kConditionalTextGalleyTipImpl )
DEFINE_HELPER_METHODS( ConditionalTextGalleyTip )



//----------------------------------------------------------------------------------------
//
// ConditionalTextGalleyTip::Constructor
//
//----------------------------------------------------------------------------------------
ConditionalTextGalleyTip::ConditionalTextGalleyTip(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss), Inherited(boss)
{
}

//----------------------------------------------------------------------------------------
//
// ConditionalTextGalleyTip::GetTipText
//
// Show note tips for collapsed inline note.
//
//----------------------------------------------------------------------------------------
PMString ConditionalTextGalleyTip::GetTipText(const PMPoint& mouseLocation)
{ 
	if (this->GetShowTipsState() == kFalse)
		return PMString();

	InterfacePtr<IControlView> thisView(this, IID_ICONTROLVIEW);

	if (thisView == nil)
		return PMString();

	PMPoint where(mouseLocation);
	thisView->WindowToContentTransform(&where);

	InterfacePtr<ITextLines> textLines(thisView, IID_ITEXTLINES);
	InterfacePtr<ITextRuns> textRuns(thisView, IID_ITEXTRUNS);

	int32 lineIndex;
	int32 runIndex = textRuns->FindIndexOfRunAtPoint(where, &lineIndex);
	
	if (lineIndex < 0 || lineIndex > textLines->GetLastLineIndex() ||
		runIndex < 0 || runIndex > textRuns->GetLastRunIndex(lineIndex))
		{
		return PMString();
		}

	
	// Try to see if it's Conditional Text we need a tip for
	int32 offsetIntoLine;
	bool16 bPastEndOfLine = textLines->FindCharacterAtXPosition(lineIndex, where.X(), offsetIntoLine);
	
	if (!bPastEndOfLine)
	{
		TextIndex currentTextPos = kInvalidTextIndex;
		if (offsetIntoLine < 0) 
			return PMString();
			
		currentTextPos = textLines->GetLineStartOffsetAtLine(lineIndex) + offsetIntoLine;

		OwnedItemDataList ownedItems;
		InterfacePtr<IStoryRefData> storyRefData(textLines, IID_ISTORYREFDATA);
		UIDRef storyRef(storyRefData ? storyRefData->GetStoryRef() : UIDRef());
		InterfacePtr<ITextModel> textModel(storyRef, IID_ITEXTMODEL);
		Utils<ITextUtils>()->CollectOwnedItems(textModel, currentTextPos , 1, &ownedItems);

        for (const auto &theOwnedItem : ownedItems)
		{
			if (theOwnedItem.fClassID == kHiddenTextBoss)
			{
				// It is a hidden text boss.
				InterfacePtr<ITextStoryThread> storyThread(::GetDataBase(textModel), theOwnedItem.fUID, UseDefaultIID());
				return GetTipContent(storyThread);
			}
		}
	}

	return PMString();
} 

