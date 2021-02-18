//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStringConverter.h $
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
//  The IStringConverter interface allows installable string manipulating styles.
//  
//  Given a string, this interface will convert that string into another string.
//  
//========================================================================================

#pragma once
#ifndef __ISTRINGCONVERTER__
#define __ISTRINGCONVERTER__

#include "IPMUnknown.h"
#include "SectionID.h"

class PMString;

/** IServiceConverter for converting/manipulating strings.
*/
class IStringConverter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTRINGCONVERTER };

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
		Manipulates the input string returning the output string.
		@param IN string specifies the string to be converted
		@param OUT string stores the string representation of the string.
	*/
	virtual void Convert(const PMString& Object, PMString &output) const = 0;
};


#endif // __ISTRINGCONVERTER__
