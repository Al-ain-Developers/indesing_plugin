//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/strings/MPMString.cpp $
//  
//  Owner: EricM
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
//  This file implements the edge routines defined in PMString.h
//  
//========================================================================================

#include "PMString.h"

CFStringRef PMString::CreateCFString() const
{
	// The Apple documentation for this function specifies that the second parameter is the number of CHARACTERS in the string.
	// I am skeptical that it handles surrogates (one characters is 32 bits rather than 16).  This may be moot since this utility
	// is used primarily for handling filenames, which are based on platform encodings*, and therefore won't ever map to surrogates.
	// * not anymore. Now OS X is all Unicode and supports surrogate pairs in filenames.
	return ::CFStringCreateWithCharacters(NULL, GrabUTF16Buffer(nil), NumUTF16TextChars());
}

void PMString::SetCFString(CFStringRef cfstring)
{
	UniCharCount cfstringLen = ::CFStringGetLength(cfstring);
	K2::scoped_ptr<UniChar> cfstringBuf(new UniChar[cfstringLen]);
	::CFStringGetCharacters(cfstring, ::CFRangeMake(0, cfstringLen), cfstringBuf.get());
	SetXString(cfstringBuf.get(), cfstringLen);
}