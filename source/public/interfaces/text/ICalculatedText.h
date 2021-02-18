//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICalculatedText.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __ICalculatedText__
#define __ICalculatedText__

#include "IPMUnknown.h"
#include "TextID.h"

class PMString;
class IDrawingStyle;
class ICalculatedTextResult;

/**
	@ingroup text_layout
*/
class ICalculatedText : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICALCULATEDTEXT };

	/** Fill out the string with the calculated text result.  Called by anyone that wants the true result of the calculation.
		@param baseStyle - the style applied to the character marking this as calculated text.
		@param data - private data, if any, for the specific type of calculated text
		@return An object representing the value of the calculated text.
		@see QueryApproxCalculatedText.
	*/
	virtual ICalculatedTextResult* NewCalculatedText(const IDrawingStyle *baseStyle, void* data = nil) const = 0;					// ##rk: CALCTEXT: void* is ugly!

	/** Fill out the string with the approximate calculated text.
		This is called by the composer (or anyone else) that is only interested in an approximation of the calculated text.
		It is a way to improve efficiency at the expense of accuracy.
		@param baseStyle - the style applied to the character marking this as calculated text.
		@param data - private data, if any, for the specific type of calculated text
		@return An object representing the value of the calculated text.
		@note This method can be used to approximate the calculated text. If not, it's equivalent to QueryCalculatedText().
		@note The composer calls this, for instance, at line breaking time. It will use the width of this text to determine line breaks.
				Later during glyph generation, if the true text is not the same width the line is expanded or compressed to fit.
		@note For example, footnotes that restart every page do this.
	*/
	virtual ICalculatedTextResult* NewApproxCalculatedText(const IDrawingStyle *baseStyle, void* data = nil) const = 0;	// ##rk: CALCTEXT: void* is ugly!

	/** Get a string representing the calculated text as it should appear in the story editor.
		@note Should only be called by the manager of this object (e.g. the table that translates (this) UID into a number or string)
		@param data - private data, if any, for the specific type of calculated text
		@param ws - will be filled out with the string.
		@see NewCalculatedText.
	*/
	virtual void GetCalculatedTextStringForStoryEditor(WideString& ws, void* data = nil) const = 0;					// ##rk: CALCTEXT: void* is ugly!

	/** ResetCalculatedText tells the object to invalidate its data.
		@param any data associated with the reset (well-known between this object and its manager).
		@param damageIfChanged tells the object to whether to damage its Wax or not when the data changes.
		@return kFalse if the object was already damaged.
		@note Should only be called by the manager of this object (e.g. the table that translates (this) UID into a number or string)
	*/
	virtual bool16 ResetCalculatedText(void* data, bool16 damageIfChanged = kTrue) const = 0;					// ##rk: CALCTEXT: void* is ugly!

	/** Tells the object to recalculate.
		@return kTrue if the object's data changed.
		@note Should only be called by the manager of this object (e.g. the table that translates (this) UID into a number or string)
	*/
	virtual bool16 Recalculate() const = 0;
};

#endif // __ICalculatedText__
