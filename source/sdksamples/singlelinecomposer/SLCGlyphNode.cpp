//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCGlyphNode.cpp $
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

// Interfaces:
#include "IComposeScanner.h"
#include "IDrawingStyle.h"
#include "IFontInstance.h"
#include "IPMFont.h"
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxRenderData.h"
#include "IWaxGlyphs.h"

// General Includes:
#include "CreateObject.h"
#include "TextChar.h"
#include "Trace.h"

// Project:
#include "SLC.h"
#include "SLCGlyphNode.h"

// Chunk size used to allocate dynamic memory.
const int32 kBufSize = 32;

/* Constructor
*/
SLCGlyphNode::SLCGlyphNode( IComposeScanner* composeScanner,
							IDrawingStyle* drawingStyle,
							TextIndex startingIndex,
							const PMReal& xOffset,
							GlyphNodeType glyphNodeType): 
	fStatus(kCompFailure),
	fTextIndex(startingIndex),
	fXOffset(xOffset),
	fGlyphNodeType(glyphNodeType),
	fTextSpan(0),
	fLeading(0.0),                  
	fAscent(0.0),
	fCapHeight(0.0),
	fXHeight(0.0),
	fComposeScanner(nil),
	fDrawingStyle(nil)
{
	TRACEFLOW("SLCGlyphNode", "SLCGlyphNode\n");
	do
	{
		// Cache a reference to the compose scanner.
		ASSERT(composeScanner != nil);
		if (composeScanner == nil)
		{
			break;
		}
		fComposeScanner = composeScanner;
		fComposeScanner->AddRef();

		// Cache a reference to the drawing style.
		ASSERT(drawingStyle != nil);
		if (drawingStyle == nil)
		{
			break;
		}
		fDrawingStyle = drawingStyle;
		fDrawingStyle->AddRef();

		// If we get this far we've successfully constructed the object.
		fStatus = kCompSuccess;

	} while (false);                 
}

/* Destructor
*/
SLCGlyphNode::~SLCGlyphNode()	
{
	TRACEFLOW("SLCGlyphNode", "~SLCGlyphNode\n");
	if (fDrawingStyle != nil)
	{
		fDrawingStyle->Release();
	}
	if (fComposeScanner != nil)
	{
		fComposeScanner->Release();
	}
}

/* Dump
*/
	static char* k_glyphNodeTypeName[] = { "Text", "ILG"};   
void SLCGlyphNode::Dump(const char* msg) const
{
	TRACEFLOW("SLCGlyphNode", "%sSLCGlyphNode::Dump():  type %s, fTextIndex %d, fXOffset %f, fTextSpan %d\n",
			  msg, 
			  k_glyphNodeTypeName[fGlyphNodeType],
			  fTextIndex,
			  ::ToDouble(fXOffset),
			  fTextSpan);
}

/* IsTrailingWhiteSpace
*/
bool16 SLCGlyphNode::IsTrailingWhiteSpace(const UTF32TextChar& character) const
{
	bool16 result = kFalse;
	if (character.GetValue() == kTextChar_Space || 
		character.GetValue() == kTextChar_CR ||
		character.GetValue() == kTextChar_SoftCR)
	{
		result = kTrue;
	}
	return result;
}

// End SLCGlyphNode.cpp.
