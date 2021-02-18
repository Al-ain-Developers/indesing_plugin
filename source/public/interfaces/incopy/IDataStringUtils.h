//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IDataStringUtils.h $
//  
//  Owner: cparrish
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
#ifndef __IDataStringUtils__
#define __IDataStringUtils__

#include "InCopyWorkflowID.h"
#include "WideString.h"

class PMPoint;
class PMRect;

/**
	A utility class for converting between WideStrings and a variety of values, 
	used primarily by the old InCopy incd file format methods.  Developers should not 
	use these methods unless they are implementing their own incd file format extensions.
	All implementations currently copy to/from std::string and stream the values in and out.
*/
class IDataStringUtils : public IPMUnknown
{
public:
		enum	{kDefaultIID = IID_IDATASTRINGUTILS};
		
		/**
			StringToInt32 converts a string to an integer.
			@param source - The string containing an integer value.
			@return - The int32 of the same value.
		*/
		virtual	int32				StringToInt32(const WideString& source) = 0;

		/**
			Int32ToString converts an integer into a string
			@param intValue - The value to convert to a string.
			@param target - The string containing the aforementioned integer value.
		*/
		virtual	void				Int32ToString(int32 intValue, WideString* target) = 0;		
	
		/**
			StringToInt16 converts a string to a short integer.
			@param source - The string containing an integer value.
			@return - The int16 of the same value.
		*/
		virtual	int16				StringToInt16(const WideString& source) = 0;

		/**
			Int16ToString converts a short integer into a string.
			@param intValue - The short integer to write to the string.
			@param target - The string to hold the converted integer.
		*/
		virtual	void				Int16ToString(int16 intValue, WideString* target) = 0;
		
#ifdef ID_DEPRECATED
		/**
			StringToBool converts a string into a bool.  This version is dangerous because the compiler 
			is allowed to choose the size of the bool.  It is recommended that you use the method StringToBool16 instead.
			@param source - The string containing the boolean value.
			@param useText - If true, the string is expected to be "true" or "false" while if it is false, the 
			strings are expected to be "1" and "0".
			@return - The bool
			@see StringToBool16
		*/
		virtual	bool				StringToBool(const WideString& source, bool16 useText = kFalse) = 0;

		/**
			BoolToString converts a bool into a string.  This version is dangerous because the compiler
			is allowed to choose the size of the bool.  It is recommended that you use the method Bool16ToString instead.
			@param boolValue - The bool to convert into a string.
			@param target - The string to write the bool's value into.
			@param useText - If true, the string is expected to be "true" or "false" while if it is false, the 
			strings are expected to be "1" and "0".
			@see Bool16ToString
		*/
		virtual	void				BoolToString(bool boolValue, WideString* target, bool16 useText = kFalse) = 0;
#endif

		/**
			StringToBool16 converts a string into a bool16.
			@param source - The string to convert.
			@return - The bool16 result.
		*/
		virtual	bool16				StringToBool16(const WideString& source) = 0;

		/**
			Bool16ToString converts a bool16 into a string
			@param boolValue - The boolean value
			@param target - The string to convert into.
		*/
		virtual	void				Bool16ToString(bool16 boolValue, WideString* target) = 0;

		/**
			StringToPMReal converts a hex string to a PMReal.
			@param source - The string as a WideString.
			@return - The PMReal from the string.
		*/
		virtual	PMReal				StringToPMReal(const WideString& source) = 0;

		/**
			StringToPMReal converts a hex UTF16 string pointer into a PMReal.
			@param source - The UTF16 string pointer
			@return - The PMReal from the string.
		*/
				PMReal				StringToPMReal(const UTF16TextChar* source)
										{ return this->StringToPMReal(source); }
										
		/**
			PMRealToString converts a PMReal into a alpha numeric hexadecimal string.
			@param realValue - The PMReal to convert.
			@param target - The string to copy the hex into.
		*/
		virtual void				PMRealToString(const PMReal& realValue, WideString* target) = 0;
		
		/**
			StringToPMReal converts a scientific notation string to a PMReal.
			@param source - The WideString to convert.
			@param precision - The number of digits of precision desired.
			@return - The PMReal from the string.
		*/
		virtual	PMReal				StringToPMReal(const WideString& source, int32 precision) = 0;

		/**
			StringToPMReal converts a scientific notation string pointer to a PMReal.
			@param source - The UTF16 string pointer contains a scientific notation real number string.
			@param precision - The number of digits of precision desired.
			@return - The PMReal from the string.
		*/
				PMReal				StringToPMReal(const UTF16TextChar* source, int32 precision)
										{ return this->StringToPMReal(WideString(source), precision); }

		/**
			PMRealToString converts a PMReal into a real number in scientific notation.
			@param realValue - The PMReal to convert to a string.
			@param target - The WideString to copy into.
			@param precision - The number of digits of precision desired.
		*/
		virtual void				PMRealToString(const PMReal& realValue, WideString* target, int32 precision) = 0;

		/**
			StringToPMPoint converts an alpha numeric hexadecimal value string to a PMPoint .
			@param source - The WideString to convert.
			@return - The PMPoint from the string.
		*/
		virtual PMPoint				StringToPMPoint(const WideString& source) = 0;

		/**
			PMPointToString converts a PMPoint into an alpha numeric hexadecimal value string.
			@param pointVal - The PMPoint to convert
			@param target - The string to convert into.
		*/
		virtual void				PMPointToString(const PMPoint& pointVal, WideString* target) = 0;
		
		/**
			StringToPMPoint converts a scientific notation format string into a PMPoint.
			@param source - The WideString to convert.
			@param precision - The number of digits of precision desired.
			@return - The PMPoint structure.
		*/
		virtual PMPoint				StringToPMPoint(const WideString& source, int32 precision) = 0;

		/**
			PMPointToString converts a PMPoint into a scientific notation based string.
			@param pointVal - The point to convert.
			@param target - The string to convert into.
			@param precision - The number of digits of precision desired.
		*/
		virtual void				PMPointToString(const PMPoint& pointVal, WideString* target, int32 precision) = 0;						
		
		/**
			StringToPMRect converts a hexidecimal based string into a PMRect.
			@param source - The string to convert.
			@return - The resulting PMRect structure.
		*/
		virtual PMRect				StringToPMRect(const WideString& source) = 0;

		/**
			PMRectToString converts a PMRect into a hexidecimal string.
			@param rectVal - The rectangle to convert.
			@param target - The string to convert into.
		*/
		virtual void				PMRectToString(const PMRect& rectVal, WideString* target) = 0;	
				
		/**
			StringToPMRect converts a scientific notation based string into a PMRect.
			@param source - The string to convert.
			@param precision - The number of digits of precision involved.
			@return - The resulting PMRect structure.
		*/
		virtual PMRect				StringToPMRect(const WideString& source, int32 precision) = 0;

		/**
			PMRectToString converts a PMRect into a hexidecimal based string.
			@param rectVal - The rectangle to convert.
			@param target - The string to convert into.
			@param precision - The number of digits of precision desired.
		*/
		virtual void				PMRectToString(const PMRect& rectVal, WideString* target, int32 precision) = 0;
    
        /**
         PMRealToString converts a PMReal into a real number in scientific notation.
         @param realValue - The PMReal to convert to a string.
         @param target - The WideString to copy into.
         @param precision - The number of digits of precision desired.
         */
        virtual void                PMRealToStringWithFixedPrecision(const PMReal& realValue, WideString* target, int32 precision) = 0;

};


#endif	// __IDataStringUtils__
