//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/strings/PlatformChar.cpp $
//  
//  Owner: Margie Vogel
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

#include "VCPublicHeaders.h"

#include "IEncodingUtils.h"
#include "ShuksanCoolType.h"

#if USE_PLATFORMCHAR_CLASS
uchar PlatformChar::GetAsOneByteChar() const
{	if (IsTwoByte())
	{
		ASSERT_FAIL("PlatformChar::GetAsOneByteChar() - has twobyte value");
		return 0;
	}
	else
		return (uchar)(fPlatformChar & 0x00FF);
}


PMString *PlatformChar::GetAsHexString( ) const
{
	PMString *hexString = new PMString;
	char buff[10];
	
	if(IsTwoByte())
		::sprintf(buff, "%04x", fPlatformChar);
	else
		::sprintf(buff, "%02x", fPlatformChar);
	hexString->SetCString(buff, static_cast<PMString::StringEncoding>(fScript));
	
	return hexString;
}

int16 PlatformChar::GetAsNumber( ConversionError *pError ) const
{
	if( pError)
		*pError = kNoError;

	switch(fPlatformChar)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	
		return int16(fPlatformChar) - '0';
		
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	
		return int16(fPlatformChar) - 'a' + 10;

	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	
		return int16(fPlatformChar) - 'A' + 10;
	}
	
	if( pError )
		*pError = kNotNumber;
	return 0;
	
}
void PlatformChar::SetFromNumber(int16 number)
{
	ASSERT_FAIL("PlatformChar::SetFromNumber - not implemented");
}

bool16 PlatformChar::IsValidCharForScript(int32 script) const
{
	bool16 retValue = kTrue;
	
	if (script == kCTDontKnowScript)
		script = fScript;
		
	if (script != kCTDontKnowScript && IsTwoByte())
	{
		if (!EncodingUtils::IsPossibleLeadByte(HighByte(), fScript))
		{
			ASSERT_FAIL("PlatformChar::IsValidCharForScript - invalid lead byte");
			retValue = kFalse;
		}
		if (!EncodingUtils::IsPossibleSecondByte(LowByte(), fScript))
		{
			ASSERT_FAIL("PlatformChar::IsValidCharForScript - invalid trail byte");
			retValue = kFalse;
		}
	}
	
	return retValue;
}

bool16 PlatformChar::IsValidInUnicode(int32 script) const
{
	bool16 retValue = kTrue;
	
	if (script == kCTDontKnowScript)
		script = fScript;
		
	if (script != kCTDontKnowScript)
	{
		return Utils<IEncodingUtils>()->DoubleByteIsValidUnicode(fPlatformChar, script);
	}
	
	return retValue;
}

void PlatformChar::SetFromUnicode(textchar uniChar)
{
	fPlatformChar = uniChar;
	
#if 1 // do this because switching scripts is REALLY SLOW
	fScript = kCTJapaneseScript;
	fPlatformChar = Utils<IEncodingUtils>()->unicode2DoubleByteEncoding( fPlatformChar, fScript );
	if (!IsValid())
#endif
	{
		fPlatformChar = uniChar;

		// find the script of the unicode character and convert it
		for (fScript = kCTRomanScript; fScript <= kCTExtendedArabicScript; fScript++)
		{
			Utils<IEncodingUtils>()->unicode2DoubleByteEncoding( fPlatformChar, fScript );
			if (IsValid()) break;
		}
	}
	
	if (IsLowASCII())
		fScript = kCTRomanScript;
}

bool16 PlatformChar::IsUpper() const
{ 
	if (IsTwoByte())
		return kFalse;
	else
		return (std::isupper(LowByte()));
}

bool16 PlatformChar::IsLower() const
{ 
	if (IsTwoByte())
		return kFalse;
	else
		return (std::islower(LowByte()));
}

PlatformChar PlatformChar::ToUpper() const
{ 
	if (IsTwoByte())
		return *this;
	else
		return (PlatformChar(0, std::toupper(LowByte()),fScript));
}

PlatformChar PlatformChar::ToLower() const
{ 
	if (IsTwoByte())
		return *this;
	else
		return (PlatformChar(0, std::tolower(LowByte()),fScript));
}

#endif
