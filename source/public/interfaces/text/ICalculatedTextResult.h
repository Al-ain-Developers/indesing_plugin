//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICalculatedTextResult.h $
//  
//  Owner:
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
#ifndef __ICalculatedTextResult__
#define __ICalculatedTextResult__


#include "WideString.h"

class IDrawingStyle;


/** This class is the result of a call to ICalculatedText. It represents a resolved calculated text character (e.g. variable, footnote, etc).
	@ingroup text_layout
	@ see ICalculatedText
*/
class ICalculatedTextResult
{
public:
	ICalculatedTextResult() : fOverrideDrawStyle(nil), fCSC(kContainsUnknown), fMustRegen(kFalse)
		{ }
	ICalculatedTextResult(const ICalculatedTextResult& copy) : fResultString(copy.fResultString), fCSC(copy.fCSC),
					fMustRegen(copy.fMustRegen), fOverrideDrawStyle(copy.fOverrideDrawStyle)
		{ }

	const WideString& GetString() const
		{ return fResultString; }
	WideString& GetString()
		{ return fResultString; }


	enum CalculatedStringContent {
		kContainsUnknown = 0x00,
		kContainsHalfWidthNumbers = 0x01,
		kContainsRomanLetters = 0x02,
		kContainsNonRoman = 0x04
	};

	/** return CalculatedStringContent which indicates the contents of the string. e.g. whether or not the string is Roman
	 */
	CalculatedStringContent GetContentFlags() const
		{ return fCSC; }
	CalculatedStringContent& GetContentFlags()
		{ return fCSC; }

	/** return a bool which indicates whether the line must be regenerated on each draw or not.
	 */
	bool16 GetMustRegen() const
		{ return fMustRegen; }

	/** specify whether the line must be regenerated on each draw or not.
	 */
	void SetMustRegen(bool16 mustRegen)
		{ fMustRegen = mustRegen; }

private:
	WideString 		fResultString;
	IDrawingStyle		*fOverrideDrawStyle;
	CalculatedStringContent	fCSC;
	bool16 			fMustRegen;
};


#endif // __ICalculatedTextResult__
