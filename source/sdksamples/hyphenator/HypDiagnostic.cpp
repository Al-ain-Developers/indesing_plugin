//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypDiagnostic.cpp $
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

// General includes:
#include "IHyphenatedWord.h"
#include "WideString.h"
#include "PMString.h"
#include "Trace.h"
#include "CTUnicodeTranslator.h"

// Project includes:
#include "HypDiagnostic.h"

/*
*/
void HypDiagnostic::TraceHyphenatedWord(const IHyphenatedWord& hyphenatedWord)
{
	WideString word = hyphenatedWord.GetWord();
	TRACEFLOW(fCategory, "HypDiagnostic:TraceHyphenatedWord(\"%s\")-->In\n", PMString(word).GetUTF8String().c_str());

	// Convert the word from Unicode to ASCII and trace.
	char* buf = new char [word.CharCount()+1];
	::CTUnicodeTranslator::Instance()->TextCharToChar(word.begin_raw(), word.CharCount(), buf, word.CharCount());
	buf [word.CharCount()] = '\0';
	TRACEFLOW(fCategory, " word(ascii)=\"%s\"\n", buf);
	delete [] buf;

	// Trace each of the hyphenation points in the word and trace
	// a PMString representation of the hyphenated word by adding
	// '-' characters at each hyphenation point.
	//	e.g. ver-it-able.
	PMString tracedWord;
	int32 startIndex = 0;
	TRACEFLOW(fCategory, " nNthPoint, hyphenIndex, hyphenQuality\n");
	for (int32 i = 0; i < hyphenatedWord.GetPointCount(); i++) {
		int32 hyphenIndex = hyphenatedWord.GetIndexOfPoint(i);
		int32 hyphenQuality = hyphenatedWord.GetQualityOfPoint(i);
		TRACEFLOW(fCategory, " %d, %d, %d\n", i, hyphenIndex, hyphenQuality);
		tracedWord.AppendW(word.begin_raw()+startIndex, hyphenIndex-startIndex);
		tracedWord.Append("-");
		startIndex = hyphenIndex;
	}
	tracedWord.AppendW(word.begin_raw()+startIndex, word.CharCount()-startIndex);
	TRACEFLOW(fCategory, " hyphenatedWord=\"%s\"\n", tracedWord.GetUTF8String().c_str());

	TRACEFLOW(fCategory, "HypDiagnostic:TraceHyphenatedWord()-->Out\n");
}

// End, HypDiagnostic.cpp