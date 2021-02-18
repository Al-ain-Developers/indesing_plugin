//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDateConverter.h $
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
//  The IDateConverter interface allows installable numbering styles. The styles may be
//  aggregated on different services such as the page numbering service, the paragraph
//  numbering service etc., which would allow each type of numbering to support different
//  subsets of numbering styles.
//  Given a number, this interface will convert that number into a string that will
//  be used to display the number in the document. The earlier IPageDateConverter interface
//  could implement multiple styles, but this interface implements only a single style.
//  
//========================================================================================

#pragma once
#ifndef __IDATECONVERTER__
#define __IDATECONVERTER__

#include "IPMUnknown.h"
#include "SectionID.h"

class PMString;
class GlobalTime;

/** IServiceConverter for type GlobalTime (dates & times)
*/
class IDateConverter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATECONVERTER };

	/**
		Returns the name of the style to be used in the UI
		@param OUT styleName stores the returned name of the style.
	*/
	virtual void GetStyleName(PMString &styleName) const = 0;

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
		Converts the input time into an output string.
		@param IN datetime specifies the datetime to be converted
		@param INOUT on input it's the specification for the date (e.g. m/d/y),
				on output stores the string representation of the date (e.g. 4/21/77).
	*/
	virtual void Convert(const GlobalTime& datetime, PMString &output) const = 0;
};


#endif // __IDATECONVERTER__
