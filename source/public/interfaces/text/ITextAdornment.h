//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAdornment.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextAdornment__
#define __ITextAdornment__

#include "IPMUnknown.h"
#include "TextID.h"
#include "IPMStream.h"
#include "IShape.h"
#include "TextDrawPriority.h"

class IGraphicsContext;
class PMRect;
class IWaxRun;
class IWaxLineShape;
class IWaxRenderData;
class IWaxGlyphs;
class ITextAdornmentData;
class GraphicsData;


/** 
	Text Adornments are bosses that are "attached" by ClassID to individual
	wax runs and, when the run is drawn, they are given control via this
	interface.

	Adornments affect when they are called by the priority value they return
	via their GetPriority() method. Higher priorities (smaller numbers) are
	called before lower priorities (larger numbers).

	In addition, drawing priorities are further broken down into two pieces -
	Pass (whole part) and Run (fractional part). For each unique Pass value
	across all the active adornments in a frame, a full iteration of the wax
	runs will be made calling all the adornments which share that pass value.
	Then, within each wax run, the adornments will be called based on their Run 
	priority.

	For performance reasons it is important to minimize the number of passes
	that are made over the wax.  Try to piggyback your drawing on an existing
	pass, such as when text is drawn. The critical indicator is to decide if
	drawing your adornment on a particular run will be negatively effected by
	some other adornment drawn on another run within the same pass. This is
	usually the case with fill type operations. These types of adornments
	probably require their own pass.

	To assist in selecting appropriate priorities, we have defined some
	values below for adornments that are part of the base implementation.

	And now a word about Page Item Adornments... These aren't strictly related
	to text but it may be important for them to know when the text will be
	drawn related to their priorities. So in that vein:

	Page Item Adornment		Relative To Text
	"Priority"				Adornment Draw Priority
	-------------------		-----------------------
	kBeforeTextBackground	BEFORE kMaxPriority
	kBeforeText				kPassPriText		(before any text adornment
												 	 with same priority)
	kBeforeTextForeground	kPassPriForeground	(before any text adornment
												 	 with same priority)
	kAfterTextForeground	AFTER kMinPriority

	@ingroup text_adorn

*/
class ITextAdornment : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTADORNMENT };

	/**  Returns the Draw priority of the adornment.
		@return the Text::DrawPriority of the adornment.
	*/
	virtual Text::DrawPriority GetDrawPriority() = 0;

	/**  Returns information about the adornment including whether it would
		draw on this run and what the ink bounds are.
		
		The ink bounds are in waxLine coordinate space (i.e. "within the line" space).
		(The same space as the baseTextWaxRun itself - no xForm need be done at the waxLine level).
		 
		@param inkBounds OUT The inkBounds are passed in empty. If your adornment is guaranteed
			 to draw within the Text bounds of the run and the vertical
			 selection bounds of the line then you DO NOT have to return
			 anything for the inkBounds, just leave them unchanged (empty).
		@param runInkBounds IN Value returned by CWaxRunShape::GetTextInkBounds() for this wax run boss.
		@param waxRun IN An interface on this wax run boss. 
		@param renderData An interface on this wax run boss.  It can be nil, meaning the WaxRunis NOT a typical text run.
		@param waxGlyphs IN An interface on this wax run boss.  It can be nil, meaning the WaxRunis NOT a typical text run.
		@param data IN pointer to optional ITextAdornmentData.  It may be nil if no data is specified when the adornment was attached.
	*/
	virtual void GetInkBounds(PMRect* inkBounds, const PMRect& runInkBounds,
								IWaxRun* waxRun,
								IWaxRenderData* renderData,
								IWaxGlyphs* waxGlyphs,
								const ITextAdornmentData *data) = 0;


	/**  Draw the text adornment.
	
		Two important IShape flags must be observed:
		
		IShape::kPrinting       If set, indicates that we are printing.

		IShape::kPreviewMode    If set, indicates that we are previewing
							printing to the screen, text adornments
							that do not draw when printing should not
							draw for this either
							
		@param gd IN Pointer to the GraphicsData.
		@param iShapeFlags IN The value of the flags parameter passed into IShape::Draw.
		@param waxRun IN An interface on this wax run boss. 
		@param renderData An interface on this wax run boss.  It can be nil, meaning the WaxRunis NOT a typical text run.
		@param waxGlyphs IN An interface on this wax run boss.  It can be nil, meaning the WaxRunis NOT a typical text run.
		@param data IN pointer to optional ITextAdornmentData.  It may be nil if no data is specified when the adornment was attached.
	*/
	virtual void Draw(GraphicsData *gd, int32 iShapeFlags,
							IWaxRun* waxRun,
								IWaxRenderData* renderData,
								IWaxGlyphs* waxGlyphs,
								const ITextAdornmentData *data) = 0;
	
/**  The adorned run is splitting: split the given data at the given offset and return the new data
		@param offsetInRun IN Offset in original run.
		@param waxRun IN An interface on the original wax run boss. 
		@param newWaxRun IN An interface on the new wax run boss the .
		@param data IN pointer to optional ITextAdornmentData.  It may be nil if no data is specified when the adornment was attached.
		@return Pointer to new instance of ITextAdornmentData which will be attached to the new wax run.
	*/
	virtual ITextAdornmentData* SplitAt( int32 offsetInRun, IWaxRun* waxRun, IWaxRun* newWaxRun, ITextAdornmentData* data ) = 0 ;
};


//	Some well known Adobe non-Global adornment priorities
//	Paragraph Rules:
//		Give Rule above priority over Rule below - this way Rule below overprints
//		(which is what version 152 did before we split into 2 bosses).
#define kTAPriParagraphShade		Text::DrawPriority(Text::kTAPassPriBackground + -0.62)			// BEFORE Para border
#define kTAPriParagraphBorder		Text::DrawPriority(Text::kTAPassPriBackground + -0.61)			// Before Para Rules
#define kTAPriParagraphRuleAbove	Text::DrawPriority(Text::kTAPassPriBackground + -0.60)			// BEFORE kTAPriMissingFont
#define kTAPriParagraphRuleBelow	Text::DrawPriority(Text::kTAPassPriBackground + -0.59)	// Above is drawn above below

// Underline draws below the text, strike through above
#define kTAPriUnderline				Text::DrawPriority(Text::kTAPassPriBackground + -0.58)		// right after paragraph rules
#define kTAPriStrikethru	Text::DrawPriority(Text::kTAPassPriText	+ 0.55)

#define kTAPriIMEHints		Text::DrawPriority(Text::kTAPassPriText	+ 0.45)

#define kTAPriBN			Text::DrawPriority(Text::kTAPassPriText	+ 0.48)	// Make bullets and numbering draw before text so that when export to PDF they will be tagged before paragraph, see bug #1695730.

#define kTAPriDrawText		Text::DrawPriority(Text::kTAPassPriText	+ 0.50)

#define kTAPriKenten		Text::DrawPriority(Text::kTAPassPriText	+ 0.60)
#define kTAPriRuby			Text::DrawPriority(Text::kTAPassPriText	+ 0.65)			// Ruby after Kenten

#define	kTAPriFakeTabViolations Text::DrawPriority(Text::kTAPassPriBackground + -0.60)	// before kTAPriHnJKeepsViolations. See IGlobalTextAdornment.h

#endif
