//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICompositionUtils.h $
//  
//  Owner: Eric Menninga
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
#ifndef __ICompositionUtils__
#define __ICompositionUtils__

#include "IPMUnknown.h"
#include "ICalculatedTextResult.h"
#include "Utils.h"
#include "CTextEnum.h"
#include "OTFeature.h"
#include "TCID.h"


class ITextModel;
class IWaxIterator;


/** Utilities related to text composition.
	e.g.
	<pre>Utils&lt;ICompositionUtils&gt;()->NewCalculatedText( ... ) ;</pre>
	@ingroup text_util
*/
class ICompositionUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOMPOSITIONUTILS };

	/**	Calculates the string based on the character and position passed in.  Returns an object containing that string and other relevant stuff.
		@param model	IN the text model that contains the calculated text.
		@param position	IN the location of the calculated text in question within the text model.
		@param c	IN the text char of the calculated text in question within the text model and the given position.
		@param style		IN the text attributes applied to the calculated text, if nil it will be calculated
		@param setMe	OUT the object containing the calculated text and associated stuff.
		@param return kSuccess when the calculated text string is correctly set.
		@return	 an object containing that string and other relevant stuff.

		@note This method is typically used for OwnedItem based calculated text (e.g. footnotes)
	 */
	virtual ICalculatedTextResult* NewCalculatedText(const ITextModel *model, TextIndex position, UTF32TextChar c, const IDrawingStyle *style = nil) = 0;

	/**	Calculates the string based on the character and text frame passed in.
		@param forFrame	IN the text frame that contains the section name.
		@param c	IN the text char of the calculated text in question within the text model and the given position.
		@param style		IN the text attributes applied to the calculated text, should not be nil
		@param setMe	OUT the object containing the calculated text and associated stuff.
		@return	 an object containing that string and other relevant stuff.

		@note This method is typically used for non-OwnedItem based calculated text (e.g. page numbers)
	 */
	virtual ICalculatedTextResult* NewCalculatedText(const UIDRef& forFrame, UTF32TextChar c, const IDrawingStyle *style, TextIndex position) = 0;

	/**	Same as NewCalculatedText, except it returns just the string.
		@return kSuccess when the calculated text string is correctly set.
		@ see NewCalculatedText
	 */
	virtual ErrorCode GetCalculatedTextString(const ITextModel *model, TextIndex position, UTF32TextChar c, const IDrawingStyle *style, WideString *calcText) = 0;

	/**	Same as NewCalculatedText, except it returns just the string.
		@return kSuccess when the calculated text string is correctly set.
		@ see NewCalculatedText
	 */
	virtual ErrorCode GetCalculatedTextString(const UIDRef& forFrame, UTF32TextChar c, const IDrawingStyle *style, WideString *calcText, TextIndex position) = 0;

	/** Scan the incoming string and return the characteristics of the contained characters
	@see CalculatedStringContent
	*/
	virtual ICalculatedTextResult::CalculatedStringContent ScanStringContents(const PMString &s) const = 0;

	/** Some fonts use custom use area characters (not unicode - e.g. Bembo Expert numbers)  - this method remaps them to the right unicode (via platform encoding).
	@param style the drawing style associated with this string
	@param original the incoming string to be scanned/remapped
	@param calcString the resulting string with remappings in place, if any
	@return whether any remapping was done
	*/
	virtual bool16 RemapCharactersIfNecessary(const IDrawingStyle *style, const PMString &original, WideString &calcString) const = 0;

	/**	Helper function used to generate necessary data for calculated text. May remap characters, change styles, etc.
		@param str		IN the resulting string to use.
		@param baseDrawStyle		IN the style applied to the calculated text.
		@param overrideDrawStyle	IN the style locally applied to the calculated text. Can be nil.
		@return	 the completed object containing the wide string and other relevant stuff.
	 */
	virtual ICalculatedTextResult* InitializeCalcResult(const PMString& str, const IDrawingStyle* baseDrawStyle) = 0;

	/**
	Given the leading information for a previous WaxLine, calculates an
	adjustment which, when added to the previous WaxLine's YPosition,
	determines the initial starting YPosition for the following WaxLine.
	Although the values returned may be negative, it will never exceed the
	lineHeight. This prevents the YPosition of the next line from being
	above the previous line's YPosition.
	*/
	virtual PMReal CalcLeadingModelYPosAdjustment(PMReal lineHeight,
								Text::LeadingModel prevLeadingModel, PMReal prevLeading, PMReal prevLeadingModelOffset,
								Text::LeadingModel leadingModel, PMReal leading, PMReal leadingModelOffset) = 0;

	/**
	Experimental routine that will try to use multiple threads to generate the runs for multiple lines in parallel.
	*/
	virtual void PregenerateWaxRuns(const IWaxIterator *waxIter, TextIndex startPos, TextIndex endPos) = 0;


	/**
	This method will return a list of substitution opentype features that are applied to the style.
	There are some GPOS features that are included, and some that will be left out (mostly kern & some japanese width features).
	There are also some heuristics related to justification that aren't in play in this routine because justification data is not here.
	@param draw is the style in question.
	@param japanese denotes whether to use some japanese specific logic around discretionary ligatures.
	@vertical specifies if the text in question is vertical
	@isTCY specifies if the vertical text in question is actually "horizontal in vertical"
	@return the list of opentype features that may be applied by the composer for this style.
	*/
	virtual OpenTypeFeatureList GetCalculatedOTFeaturesList(const IDrawingStyle *draw, bool japanese = false, bool vertical = false, bool isTCY = false) = 0;


};


#endif	// __ICompositionUtils__




