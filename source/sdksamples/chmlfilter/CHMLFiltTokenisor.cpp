//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltTokenisor.cpp $
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

// C++ includes
//#include <cctype>

// General includes
#include "CAlert.h"
#include "Trace.h"

// Interface includes
#include "IPMStream.h"

// Project includes
#include "CHMLFiltTokenisor.h"



/* 	Constructor
*/
CHMLFiltTokenisor::CHMLFiltTokenisor(IPMStream* s)
{
	// make sure the stream is set for reading etc...
	token_spare = kFalse;
	theStream = s;
	fCurrentTokenType = kTokenInvalid;
	ResetStream();
}

/* Destructor
*/
CHMLFiltTokenisor::~CHMLFiltTokenisor(void)
{}


/* PushTokenBack
*/
void CHMLFiltTokenisor::PushTokenBack(void)
{
	token_spare = kTrue;
}

/* GetNextToken
*/
Token_t CHMLFiltTokenisor::GetNextToken(TokenValue& theToken)
{
	// the user of this module has pushed a token back on, return this token
	if (token_spare) 
	{
		theToken = fCurrentToken;
		token_spare = kFalse;
		return fCurrentTokenType;
	}

	// at this point we need to get another token...
	fCurrentToken.Clear();
	uchar tmp(0);
	theStream->XferByte(tmp);

	// get rid of any whitespace
	while ((isspace(tmp)) && 
		   (theStream->GetStreamState() != kStreamStateEOF))	
	{
		theStream->XferByte(tmp);
	}
	if (theStream->GetStreamState() == kStreamStateEOF)
	{
		// the user can make no assumptions about the state of the variables when eof is encountered...
		fCurrentTokenType = kTokenEOF;
		theToken = fCurrentToken;	// this will be cleared
		return fCurrentTokenType;
	}

	// we have a valid character in the stream, read the rest in
	// until we get whitespace
	while ((!isspace(tmp)) &&
		   (theStream->GetStreamState() != kStreamStateEOF))
	{	
		TRACEFLOW("SDKTraceFlow", "Current token: '%s'\n", fCurrentToken.GetUTF8String().c_str());
		fCurrentToken.Append((char)tmp);
		theStream->XferByte(tmp);
	}
	// we now have a valid token, if it isn't a special token, just return
	TRACEFLOW("SDKTraceFlow", "Current token: '%s'\n", fCurrentToken.GetUTF8String().c_str());
	if (fCurrentToken[0] != '<')
	{
		theToken = fCurrentToken;
		fCurrentTokenType = kTokenText;
		return fCurrentTokenType;
	}

	// At this point we know we have a tag value. We might need to continue reading the stream
	// until we get to the '>' character. The tag might not have a value, check this first!
	// set up the end of string to be the space char
	PMString tagend(">");
	if (!fCurrentToken.Contains(tagend))
	{
		// we need to delimit the tag with the value so insert a space
		fCurrentToken.Append(' ');
		theStream->XferByte(tmp);

		// get the rest of the tag
		while ((tmp != '>') && 
			   (theStream->GetStreamState() != kStreamStateEOF))	
			
		{
			fCurrentToken.Append((char)tmp);
			theStream->XferByte(tmp);
		}
		fCurrentToken.Append((char)tmp);
	}

	// now we need to work out what token it was, strip of the token itself and return the value if one...
	// first deal with tokens with no value...
	if (fCurrentToken == TOKENHEAD)
	{	
		// I do nothing about the value, caller should ignore it
		fCurrentTokenType = kTokenHead;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENSTARTBOLD)
	{
		fCurrentTokenType = kTokenBold;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENENDBOLD)
	{
		fCurrentTokenType = kTokenNoBold;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENSTARTUNDERLINE)
	{
		fCurrentTokenType = kTokenUnderline;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENENDUNDERLINE)
	{
		fCurrentTokenType = kTokenNoUnderline;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENPARA)
	{
		fCurrentTokenType = kTokenPara;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENSTARTCOMMENT)
	{
		fCurrentTokenType = kTokenCommentStart;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENENDCOMMENT)
	{
		fCurrentTokenType = kTokenCommentEnd;
		return fCurrentTokenType; 
	}
	
	// Additional tokens based on Japanese features
	if (fCurrentToken == TOKENKENTEN)
	{
		fCurrentTokenType = kTokenKenten;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENENDKENTEN)
	{
		fCurrentTokenType = kTokenNoKenten;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENSYATAI)
	{
		fCurrentTokenType = kTokenSyatai;
		return fCurrentTokenType; 
	}
	if (fCurrentToken == TOKENENDSYATAI)
	{
		fCurrentTokenType = kTokenNoSyatai;
		return fCurrentTokenType; 
	}
	
	// Now deal with the tags that have associated values
	// The last char should be '>'
	if (fCurrentToken[fCurrentToken.WCharLength()-1] == '>')
	{
		fCurrentToken.Truncate(1);
	}
	else
	{
		return kTokenInvalid;
	}
	
	if (fCurrentToken.Contains(TOKENSIZE, 0))
	{	
		fCurrentTokenType = kTokenSize;
		// remove the "<s " part of the tag...
		fCurrentToken.Remove(0, TOKENSIZE.WCharLength());
		theToken = fCurrentToken;
		return fCurrentTokenType;
	}
	if (fCurrentToken.Contains(TOKENFONT, 0))
	{
		fCurrentTokenType = kTokenFont;
		fCurrentToken.Remove(0, TOKENFONT.WCharLength());
		theToken = fCurrentToken;
		return fCurrentTokenType;
	}
	if (fCurrentToken.Contains(TOKENIFILE, 0))
	{
		fCurrentTokenType = kTokenIFile;
		fCurrentToken.Remove(0, TOKENIFILE.WCharLength());
		theToken = fCurrentToken;
		return fCurrentTokenType;
	}
	if (fCurrentToken.Contains(TOKENTBOX, 0))
	{
		fCurrentTokenType = kTokenTbox;
		fCurrentToken.Remove(0, TOKENTBOX.WCharLength());
		theToken = fCurrentToken;
		return fCurrentTokenType;
	}
	if (fCurrentToken.Contains(TOKENALIGN, 0))
	{
		fCurrentTokenType = kTokenAlign;
		fCurrentToken.Remove(0, TOKENALIGN.WCharLength());
		theToken = fCurrentToken;
		return fCurrentTokenType;
	}
	
	// Additional token values based on Japanese features
	if (fCurrentToken.Contains(TOKENRUBY, 0))
	{
		fCurrentTokenType = kTokenRuby;
		fCurrentToken.Remove(0, TOKENRUBY.WCharLength());
		theToken = fCurrentToken;
		return fCurrentTokenType;
	}

	// we don't know the token
	return kTokenInvalid;
}

/*  GetCurrentToken
*/
Token_t CHMLFiltTokenisor::GetCurrentToken(TokenValue& theToken)
{
	theToken = fCurrentToken;
	return fCurrentTokenType;
}

/*  ResetStream
*/
void CHMLFiltTokenisor::ResetStream(void)
{
	if (theStream) 
	{
		// make sure we're at the beginning
		theStream->Seek(0, kSeekFromStart);
	}
	else
	{
		ASSERT_FAIL("CHMLFiltTokenisor::ResetStream : member 'theStream' is nil!");
	}
}

// End, CHMLFiltTokenisor.cpp.

