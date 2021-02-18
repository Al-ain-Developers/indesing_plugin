//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StringNumeric.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  This namespace provides string to numeric and numeric to string conversion routines.
//  
//========================================================================================

#pragma once
#ifndef __StringNumeric__
#define __StringNumeric__

// ----- Includes -----

class PMReal;
class WideString;


/**
 Namespace providing string to numeric and numeric to string conversion routines.
*/
namespace stringnumeric
{
	/**
	 Converts WideString to a std::wstring. \\
	 Note: wstring uses wchar_t as character type and is 16 bit on Windows and 32 bit on Mac.
	 @param src  [IN] Source string.
	 @param dest [OUT] Destination string.
	*/
	PUBLIC_DECL void ToWstring(const WideString& src, std::wstring& dest);

	/**
	 Converts a WideString to a std::wstring. \\
	 Overloaded for convenience. Beware of the cost (return by value). \\
	 Note: wstring uses wchar_t as character type and is 16 bit on Windows and 32 bit on Mac.
	 @param src [IN] Source string.
	 @return Resulting std::wstring.
	*/
	inline std::wstring ToWstring(const WideString& src)
	{
		std::wstring result;
		ToWstring(src, result);
		return result;		
	}

	/**
	 Converts a WideString to a integral or floating point value. \\
	 Note: 8 bit integral types are currently unsupported.
	 @param str [IN] Source string. \\
					 Valid signed integral form: [whitespace][{-|+}]digit[digits] \\
					 Valid unsigned integral form: [whitespace][+]digit[digits]
	 @param num [OUT] Destination integral or floating point type.
	 @return kSuccess if the conversion succeeds, else an error code.
	 */
	template<typename T>
	PUBLIC_DECL ErrorCode FromString(const WideString& str, T& num);

	/**
	 Converts a WideString to a floating point value with a specified precision.
	 @param str		  [IN] Source string.
	 @param precision [IN] Number of digits after the decimal point. \\
						   -1 for maximum number of display digits.
	 @param num		  [OUT] Destination floating point type.
	 @return kSuccess if the conversion succeeds, else an error code.
	 */
	template<typename T>
	PUBLIC_DECL ErrorCode FromString(const WideString& str, int32 precision, T& num);

	/**
	 Converts a WideString to a PMReal.
	 @param str		  [IN] Source string.
	 @param precision [IN] Number of digits after the decimal point. \\
						   -1 for maximum number of display digits.
	 @param num		  [OUT] Destination PMReal.
	 @return kSuccess if the conversion succeeds, else an error code.
	 */
	template<>
	PUBLIC_DECL ErrorCode FromString<PMReal>(const WideString& str, int32 precision, PMReal& num);

	/**
	 Converts a integral value or floating point value to a WideString. \\
	 Floating point values are converted using a display precision of 3.
	 @param num [IN] Source integral or floating point value.
	 @param str [OUT] Destination string.
	 @return kSuccess if the conversion succeeds, else an error code.
	 */
	template<typename T>
	PUBLIC_DECL ErrorCode ToString(T num, WideString& str);

	/**
	 Converts a floating point value to a WideString with a specified precision.
	 @param num		  [IN] Source floating point value.
	 @param precision [IN] Number of digits after the decimal point. \\
						   -1 for maximum number of display digits.
	 @param str		  [OUT] Destination string.
	 @return kSuccess if the conversion succeeds, else an error code.
	 */
	template<typename T>
	PUBLIC_DECL ErrorCode ToString(T num, int32 precision, WideString& str);

	/**
	 Converts a PMReal to a WideString with a specified precision.
	 @param num		  [IN] Source PMReal.
	 @param precision [IN] Number of digits after the decimal point. \\
						   -1 for maximum number of display digits.
	 @param str		  [OUT] Destination string.
	 @return kSuccess if the conversion succeeds, else an error code.
	 */
	template<>
	PUBLIC_DECL ErrorCode ToString<PMReal>(PMReal num, int32 precision, WideString& str);

}	// namespace stringnumeric

#endif	// __StringNumeric__
