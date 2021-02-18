//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCGlyphNodeList.cpp $
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
#include "IComposeScanner.h"

// General includes:
#include "K2Vector.h"
#include "PMRect.h"
#include "TextChar.h"

// Project includes:
#include "SLC.h"
#include "SLCGlyphNode.h"
#include "SLCTextGlyphNode.h"
#include "SLCInlineGraphicGlyphNode.h"
#include "SLCGlyphNodeList.h"

/* CreateGlyphNode
*/
SLCGlyphNode* SLCGlyphNodeList::CreateGlyphNode(IComposeScanner* composeScanner,
												IDrawingStyle* drawingStyle,
												TextIndex startingIndex,
												const PMReal& xOffset)
{
	TRACEFLOW("SLCGlyphNode", "SLCGlyphNodeList::CreateGlyphNode()-->In\n");
	SLCGlyphNode* result = nil;

	do
	{
		SLCGlyphNode* glyphNode = nil;

		// The type of glyph node to be created depends on the nature
		// of the character to be composed.
		TextIterator iter = composeScanner->QueryDataAt(startingIndex,
														nil, // Not interested in drawing style.
														nil); // Not interested in length of run.
		ASSERT(iter.IsNull() != kTrue);
		if (iter.IsNull())
		{
			break;
		}
		if ((*iter).GetValue() == kTextChar_ObjectReplacementCharacter)
		{
			// Create a GlyphNode for an inline graphic.
			glyphNode = new SLCInlineGraphicGlyphNode(composeScanner, drawingStyle, startingIndex, xOffset);
		}
		else
		{
			// Create a GlyphNode for text.
			glyphNode = new SLCTextGlyphNode(composeScanner, drawingStyle, startingIndex, xOffset);
		}
		ASSERT(glyphNode != nil);
		if (glyphNode == nil)
		{
			break;
		}
		ASSERT(glyphNode->GetStatus() == kCompSuccess);
		if (glyphNode->GetStatus() != kCompSuccess)
		{
			delete glyphNode;
			break;
		}

		// Add the new GlyphNode to the list.
		fGlyphNodeList.push_back(glyphNode);
		result = glyphNode;

	} while (false);

	TRACEFLOW("SLCGlyphNode", "SLCGlyphNodeList::CreateGlyphNode()-->Out result = 0x%x\n", result);

	return result;

}

/* Clear
*/
void SLCGlyphNodeList::Clear()
{
	if (fGlyphNodeList.size() > 0)
	{
		for (int32 i = static_cast<int32>(fGlyphNodeList.size()) - 1; i >= 0; --i)
		{
			delete fGlyphNodeList [i];
		}
		fGlyphNodeList.clear();
	}
}

/* GetTextSpan
*/
int32 SLCGlyphNodeList::GetTextSpan(int32 fromIndex) const
{
	int32 count = 0;
	for (int32 i = fromIndex; i < fGlyphNodeList.size(); i++)
	{
		count += fGlyphNodeList [i]->GetTextSpan();
	}
	return count;
}

/* GetTrailingWhiteSpaceWidth
*/
PMReal SLCGlyphNodeList::GetTrailingWhiteSpaceWidth(int32 fromIndex) const
{
	PMReal width = 0.0;
	for (int32 i = static_cast<int32>(fGlyphNodeList.size())-1; i >= fromIndex; i--)
	{
		if (fGlyphNodeList [i]->GetTrailingWhiteSpaceWidth(width) == kFalse)
		{
			break;
		}
	}
	return width;
}

/* FitTrailingWhiteSpace
*/
void SLCGlyphNodeList::FitTrailingWhiteSpace(int32 fromIndex, const PMReal& widthScaleFactor)
{
	for (int32 i = static_cast<int32>(fGlyphNodeList.size())-1 ; i >= fromIndex; i--)
	{
		if (fGlyphNodeList [i]->FitTrailingWhiteSpace(widthScaleFactor) == kFalse)
		{
			// No more trailing white space so stop.
			break;
		}
	}
}

/* GetWidth
*/
PMReal SLCGlyphNodeList::GetWidth(int32 fromIndex) const
{
	PMReal width = 0.0;
	for (int32 i = fromIndex; i < fGlyphNodeList.size(); i++)
	{
		width += fGlyphNodeList [i]->GetWidth();
	}
	return width;
}

/* Dump
*/
void SLCGlyphNodeList::Dump(int32 fromIndex, const char* msg) const
{
	TRACEFLOW("SLCGlyphNode", "SLCGlyphNodeList::Dump()-->In fromIndex=%d %s\n", fromIndex, msg);
	for (int32 i = fromIndex; i < fGlyphNodeList.size(); i++)
	{
		fGlyphNodeList [i]->Dump("");
	}
	TRACEFLOW("SLCGlyphNode", "SLCGlyphNodeList::Dump()-->Out\n");
}

// End, SLCGlyphNodeList.cpp.
