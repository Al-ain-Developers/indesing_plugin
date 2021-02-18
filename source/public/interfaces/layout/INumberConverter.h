//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INumberConverter.h $
//  
//  Owner: Anurag Wahi
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
//  The INumberConverter interface allows installable numbering styles. The styles may be
//  aggregated on different services such as the page numbering service, the paragraph
//  numbering service etc., which would allow each type of numbering to support different
//  subsets of numbering styles.
//  Given a number, this interface will convert that number into a string that will
//  be used to display the number in the document. The earlier IPageNumberConverter interface
//  could implement multiple styles, but this interface implements only a single style.
//  
//========================================================================================

#pragma once
#ifndef __INUMBERCONVERTER__
#define __INUMBERCONVERTER__

#include "IPMUnknown.h"
#include "SectionID.h"

class PMString;

/** IServiceConverter for type int32 (number converter)
*/
class INumberConverter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INUMBERCONVERTER };

	/**
		@see GetNumberingStyleName
	*/
	void GetStyleName(PMString &styleName) const
		{ return GetNumberingStyleName(styleName); }
	/**
		@see GetStyleName
	*/
	void GetStyleNameBase(PMString &styleName) const
	{ return GetStyleName(styleName); }

	/**
		Returns whether this style can be included in the UI or not. This can be used to exclude
		locale-specific string styles from the UI, but to still have the conversion service available
		to draw if the user opens a document that was created in a different locale.
		@return kTrue if the style can be included in the UI, kFalse otherwise.
	*/
	virtual bool16 IncludeStyleChoiceInUI() const = 0;

	/**
		@see NumberToString
	*/
	void Convert(const int32& number, PMString &numString) const
		{ return NumberToString(number, numString); }

	/**
		Returns the name of the style to be used in the UI (e.g. "1, 2, 3, 4...", "a, b, c, d..." etc.)
		@param OUT styleName stores the returned name of the style.
	*/
	virtual void GetNumberingStyleName(PMString &styleName) const = 0;

	/**
		Returns the string representation of the input number in the style implemented by this number converter.
		@param IN number specifies the number to be converted
		@param OUT pNumString stores the string representation of the number.
	*/
	virtual void NumberToString(int32 number, PMString &numString) const = 0;
};


#endif // __INUMBERCONVERTER__
