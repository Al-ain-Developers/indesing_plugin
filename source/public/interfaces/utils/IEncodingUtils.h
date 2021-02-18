//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/utils/IEncodingUtils.h $
//  
//  Owner: hhorton, (Bernd Paradies: generalized from EncodingUtils.h).
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

#pragma once
#ifndef _H_IEncodingUtils
#define _H_IEncodingUtils

#include "CJKID.h"			// For IID_IENCODINGUTILS
#include "IPMUnknown.h"
#include "Utils.h"
class PMString;
class IPMFont;

/** Utilities for converting encodings.
		i.e. Utils<IEncodingUtils>()->Unicode2ShiftJIS( ch );
*/
class IEncodingUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IENCODINGUTILS };

	/**	Convert Unicode value to shift JIS value.
		@param ch	IN/OUT on exit ch contains shift JIS value.
	 */
	virtual void			Unicode2ShiftJIS(textchar &ch) = 0;

	/**	Convert shift JIS value to Unicode value.
		@param ch	IN/OUT on exit ch contains unicode value.
	 */
	virtual void			ShiftJIS2Unicode(textchar &ch) = 0;

	/**	Convert shift JIS to JIS value.
		@param ch	IN/OUT on exit ch contains JIS value.
	 */
	virtual void			ShiftJIS2JIS(textchar &ch) = 0;

	/**	Convert JIS value to shift JIS value.
		@param ch	IN/OUT on exit ch contains shift JIS value.
	 */
	virtual void			JIS2ShiftJIS(textchar &ch) = 0;

	/**	Convert JIS value to kuten value.
		@param ch	IN/OUT on exit ch contains kuten value.
	 */
	virtual void			JIS2Kuten(textchar &ch) = 0;

	/**	Convert kuten value to JIS value.
		@param ch	IN/OUT on exit ch contains JIS value.
	 */
	virtual void			Kuten2JIS(textchar &ch) = 0;


	/**	Convert shift JIS to unicode
		@param ch			shift JIS value
		@return textchar	Unicode value
	 */
	virtual textchar		ShiftJIS2Unicode(PlatformChar ch) = 0;

	/**	Convert shift JIS to JIS
		@param ch			shift JIS value
		@return textchar	JIS value
	 */
	virtual textchar		ShiftJIS2JIS(PlatformChar ch) = 0;

	/**
		Encoding Type
		
		@see StringToCharacterCode
	*/
	typedef enum {
		/** Value is already character */
		kCharInput = 0,
		/** Value is string representation of shift JIS code for character */
		kShiftJIS,
		/** Value is string representation of JIS code for character */
		kJIS,
		/** Value is string representation of Kuten code for character */
		kKuten,
		/** Value is string representation of Chinese Big5 code for character */
		kBig5,
		/** Value is string representation of Chinese GB code for character */
		kGB,
		/** Value is string representation of Korean code for character */
		kKorean,
		/** Value is string representation of Unicode value for character */
		kUnicode
	} encodingType;
	/**	Use this if you have a popup with the following Entries - Character Input, Separator,
		Shift JIS, JIS, Kuten, Unicode
		@param popupIndex		index in popup
		@return encodingType	encodingType
	 */
	virtual encodingType	PopupIndexToEncodingType(int32 popupIndex) = 0;

	/**	Converts a string representation of a character code to a Unicode value.
		So "0041" with encoding kUnicode becomes the unicode value for 'A'
		@param str				string representation of character code
		@param encoding			encoding
		@return UTF32TextChar	new value. 0 or 1 if value could not be converted.
	 */
	virtual UTF32TextChar	StringToCharacterCode(PMString& str, encodingType encoding) = 0;

	/**	Converts a Unicode value to a string representation of a character code.
		@param code				Unicode to convert
		@param encoding			encoding
		@return PMString		string representation of character code
	 */
	virtual PMString		CharacterCodeToString(UTF32TextChar code, encodingType encoding) = 0;

	/**	Converts a string representation of a Unicode value to a Unicode value.
		So "0041" becomes the unicode value for 'A'
		@param s			string representation of unicode value
		@return uint32		new value. 0 or 1 if value could not be converted.
	 */
	virtual uint32			GetHexCode(PMString& s) = 0;

	/**	Converts a Kuten Code to a Unicode value.
		@param s			Kuten Code
		@return textchar	new value. 0 if value could not be converted.
	 */
	virtual textchar		GetKutenCode(PMString& s) = 0;

	/**	Character is '0' - '9' or 'A'-'F' or 'a'-'F'
		@param c			character to check
		@return bool16		kTrue if hex
	 */
	virtual bool16			IsHex(uchar c) = 0;

	/**	Character is '0' - '9'
		@param c			character to check
		@return bool16		kTrue if decimal
	 */
	virtual bool16			IsDecimal(uchar c) = 0;

	/**	Get integer value of character
		@param c			character to check. should be '0' - '9' or 'A'-'F' or 'a'-'F'.
		@return int32		value of character as integer. Value will be 0-15.
							value is 0 if is not an integer
	 */
	virtual int32			IntValue(uchar c) = 0;

	// if script is -1 functions use script of PMString constructor for conversion
	/**	Convert character to unicode.
		@param ch				character to convert.
		@param script			script of character. If -1 default script of PMString is used.
		@return UTF32TextChar	new value.
	 */
	virtual UTF32TextChar	DoubleByteEncoding2unicode( uchar16 ch, uint8 script = -1  ) = 0;

	/**	Character has Unicode value.
		@param ch			character to check.
		@param script		script of character. If -1 default script of PMString is used.
		@return bool16		kTrue if character has value in Unicode.
	 */
	virtual bool16			DoubleByteIsValidUnicode(const textchar &inChar, uint8 script = -1 ) = 0;

	/**	Convert Unicode value to platform encoding.
		@param ch			unicode value to convert
		@param script		script of character. If -1 default script of PMString is used.
		@return uchar16		platform encoding value
	 */
	virtual uchar16			unicode2DoubleByteEncoding( const UTF32TextChar &ch, uint8 script = -1 ) = 0;


	/**	Convert character to unicode using font to convert.
		@param platformChar	platform character to convert
		@param transFont	font to use to convert
		@return textchar	unicode value
	 */
	virtual textchar		FontBasedPlatformEncoding2Unicode( PlatformChar platformChar, IPMFont *transFont ) = 0;

	/**	DESCRIPTION
		@param unicodeChar	unicode character to convert
		@param transFont	font to use to convert. If nil script is used to convert.
		@param script		script for conversion if transFont is nil. If -1 default script of PMString is used.
		@return PlatformChar	converted character
	 */
	virtual PlatformChar	FontBasedUnicode2PlatformEncoding( UTF32TextChar unicodeChar, IPMFont *transFont, uint8 script = -1 ) = 0;

	// routines for parsing 2-byte text.
	/**	Character is in lead byte range for script.
		@param charByte		byte to check	
		@param script		script to check with. using -1 will always return kFalse.
		@return bool16		kTrue if byte is lead byte for script
	 */
	virtual bool16			IsPossibleLeadByte(uchar charByte, int8 script) = 0;

	/**	Character is in possible second byte range for script.
		@param charByte		byte to check	
		@param script		script to check with. using -1 will always return kFalse.
		@return bool16		kTrue if byte is possible second byte for script
	 */
	virtual bool16			IsPossibleSecondByte(uchar charByte, int8 script) = 0;

	/**	Checks if script is double byte.
		@param script		script to check
		@return bool16		kTrue if Japanese, TraditionalChinese, Korean or SimplifiedChinese
	 */
	virtual bool16			IsDoubleByteScript(int8 script) = 0;


	/**	Determine if we can break string after the character index
		@param s			string to check 
		@param index		index to check
		@return bool16		kTrue if break is possible
	 */
	virtual bool16			ValidLineBreakAfterIndex(const PMString &, CharCounter index) = 0;
};


/** PMString uses EncodingUtils before the ObjectModel is launched. I am adding IsPossibleLeadByte() and IsPossibleSecondByte() 	as functions.
*/
namespace EncodingUtils
{
	// routines for parsing 2-byte text.
	PUBLIC_DECL bool16		IsPossibleLeadByte(uchar charByte, int8 script);
	PUBLIC_DECL bool16		IsPossibleSecondByte(uchar charByte, int8 script);
}



#endif /* _H_EncodingUtils */

