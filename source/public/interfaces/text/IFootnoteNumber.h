//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFootnoteNumber.h $
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
#ifndef __IFootnoteNumber__
#define __IFootnoteNumber__

#include "IPMUnknown.h"
#include "TextID.h"

class PMString;
class IFootnoteNumbering;


const int32 kInvalidFootnoteNumber = -1;

/**
	@ingroup text_layout
*/
class IFootnoteNumber : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFOOTNOTENUMBER };

	typedef enum { kFootnoteReferenceInText, kFootnoteNumberInFootnote } FootnoteLocation;

	/** GetNumber returns the number stored internally. It may be "kInvalidFootnoteNumber" if it hasn't been calculated yet.
	*/
	virtual int32 GetTheNumber(bool16 calculateWhenInvalid) const = 0;

	/** GetNumberString fills out the string with the text used to display the note's number.
		@param noteNum will be filled out with the number-related string.
	*/
	virtual void GetNumberString(FootnoteLocation location, PMString& noteNum) const = 0;

	/** GetNominalNumberString fills out the string with the text used to display the note's initial number.
		This is used when composing text that contains footnotes that restart every page/spread.
		@param noteNum will be filled out with the number-related string.
	*/
	virtual void GetNominalNumberString(FootnoteLocation location, PMString& noteNum) const = 0;

	/** ResetFootnoteNumber tells the footnote to invalidate its personal number.
		@param n is the footnote number to set to.
		@param damageIfChanged tells the footnote to damage its WaxLine(s) or not when the number changes.
		@return ResetFootnoteNumber returns kFalse if the footnote was already damaged.
	*/
	virtual bool16 ResetFootnoteNumber(int32 n = kInvalidFootnoteNumber, bool16 damageIfChanged = kTrue) = 0;

	/** RecalculateFootnoteNumber tells the footnote to recalculate personal number.
		@return RecalculateFootnoteNumber returns kTrue if the number changed.
	*/
	virtual bool16 RecalculateFootnoteNumber() = 0;
    
    /** Returns the IFootnoteNumbering interface managing this footnote.
     @return IFootnoteNumbering
     */
    virtual IFootnoteNumbering* QueryFootnoteNumbering() const = 0;

};

#endif
	// __IFootNoteNumber__
