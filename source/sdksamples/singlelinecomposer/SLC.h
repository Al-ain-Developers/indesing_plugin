//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLC.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __SLC_h__
#define __SLC_h__

#include "CTextEnum.h"

/** Status codes used internally by the composer. Status codes
 * 	greater or equal to kCompSuccess are good, less than kCompSuccess
 * 	are bad. So tests for status like if (status < kCompSuccess) error
 * 	are used.
 * 	@ingroup singlelinecomposer
*/
enum SLComposerStatusCode 
{
	/** The character cannot be added into a GlyphNode. */
	kCompIncompatibleCharacter = -5,
	/** The maximum height we have tiles for has been exceeded. */
	kCompChangeOfHeight = -4,	
	/** Cannot fit characters in the current set of tiles. */
	kCompWillNotFit = -3,	
	/** Memory allocation failure. */
	kCompOutOfMemory = -2,	
	/** Unexpected error, nil interface pointer */
	kCompFailure = -1,	
	/** Success */
	kCompSuccess = 0,	
	/** End of line detected. */
	kCompEndOfLine,
	/** Composition stopped before end of line. A table character,
		kTextChar_Table, or similar has been detected. All
		we have to do is stop, leave the character alone and the
		application will compose the table.
	*/
	kCompStop
};

typedef SLComposerStatusCode SLComposerStatusCode;

/** This composer implements a roman leading model (the distance between
 * 	the baselines of consecutive lines of text is set to the maximum leading
 * 	value on the line being composed).
 * 	@ingroup singlelinecomposer
*/
const Text::LeadingModel kSLCLeadingModel = Text::kRomanLeadingModel;

/** Maximum leading value on the line is used to set the line height.
 * @ingroup singlelinecomposer
*/
const Text::FirstLineOffsetMetric kSLCLineHeightMetric = Text::kFLOLeading;

/** Offset is always zero for baseline grid or no alignment. Note alignment to the
 * 	baseline grid is done by the tiler. If we ask for tiles aligned to
 * 	the baseline grid then we'll get them. The tiler figures out where they should be.
 * 	@ingroup singlelinecomposer
*/
const PMReal kSLCGridAlignmentMetricOffset(0.0);

#endif // __SLC_h__

// End, SLC.h

