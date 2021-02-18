//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IGlobalTextAdornment.h $
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
#ifndef __IGlobalTextAdornment__
#define __IGlobalTextAdornment__

#include "IPMUnknown.h"
#include "TextID.h"
#include "TextDrawPriority.h"

class GraphicsData;
class PMRect;
class IWaxRun;
class IWaxRenderData;
class IWaxGlyphs;
class IParcelShape;
class ITextOptions;



/**	GlobalTextAdornments are a special kind of TextAdornments in that they are
	treated as if they were attached to every WaxRun, with the exception that
	they never have run specific data adornment data.

	The best example of the application of a GlobalTextAdornment is the
	ShowInvisibles function. This Adornment will draw special symbols to
	represent the hidden text characters (paragraph markers, spaces, etc) in a
	composed line. The drawing of these symbols is triggered by a menu pick
	and we of course cannot require recomposition in order to attach adornments
	to individual runs. Implemented as a global adornment, the adornment can
	have the behavior as if was attached to all the runs but only get called
	when it says so by having its GetIsActive() method query the state of the
	menu pick. 
	@ingroup text_adorn
*/
class IGlobalTextAdornment : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGLOBALTEXTADORNMENT };

	/** Returns the Draw priority of the adornment which is used for z-ordering */
	virtual Text::DrawPriority GetDrawPriority() = 0;

	/**	@see GetIsActive */
	virtual bool16 GetCheckIsActive() = 0;
	
	/**	The purpose of this method is to give the Parcel a chance to avoid
		passes and calling adornments that aren't needed. If, for example, a
		particular adornment was the only one needing to be called on a
		particular pass and the adornment wouldn't be drawing because of some
		global state, by returning kFalse the pass could be avoided.

		Global adornments which indicate they are not active will NOT be called to Draw. 

		@param parcelShape : the parcel this text is in. It MAY NOT be a UID based object.
		@param textOptions : pointer to the document's text options
		@param iShapeFlags : Two important IShape flags must be observed:
								IShape::kPrinting		If set, indicates that we are printing.
								IShape::kPreviewMode	If set, indicates that we are previewing
														printing to the screen, global adornments
														that do not draw when printing should not
														draw for this either
	*/
	virtual bool16 GetIsActive(const IParcelShape *parcelShape,
								const ITextOptions *textOptions,
								int32 iShapeFlags) = 0;

	/** see GetCouldDraw */
	virtual bool16 GetCheckCouldDraw() = 0;

	/** The Adornment is asked if it could like to draw on the particular run.
		This is NOT a question about whether the adornment is active or not,
		rather if an adornment didn't want to draw on any of the runs in a 
		particular parcel then that adornment would never be called.

		All non-global adornments by definition would like to draw because they
		are attached to the runs so they never need to be asked this question.

		This method helps us optimize the calling of global adorments which are
		implemented as "triggers" to things in the Wax. Take, for example, the
		HnJViolations global adornment. It only wants to draw if the WaxLine has
		HnJViolations AND the appropriate menu pick has occured. So it wants to
		be able to avoid being called to draw when none of the WaxLines in the
		frame have any violations even through the menu pick may be active.

		@param waxRun : the run in question
		@param waxRenderData : drawing data for the run (font, color, etc.) can be nil (e.g. inline graphic)
		@param waxGlyphs : glyph interface for the run. can be nil (e.g. inline graphic)
	*/
	virtual bool16 GetCouldDraw(const IWaxRun *waxRun,
								const IWaxRenderData *waxRenderData,
								const IWaxGlyphs *waxGlyphs) = 0;

	/** @see GetInkBounds */
	virtual bool16 GetHasInkBounds() = 0;

	/** The Adornment is asked if it has ink bounds.
		Again, this is NOT a question about whether the adornment is active or
		not, rather if an adornment didn't want to draw on any of the runs in a 
		particular parcel then that adornment would never be called.

		If the Adornment never creates ink that exceeds the standard ink bounds
		of the run (ie the selection bounds) then it does not have to provide
		ink bounds.

		@param inkBounds: rectange to set with ink bounds. NOTE: The inkBounds are passed in empty. 
						If your adornment is guaranteed to draw within the Text bounds of the run
						and the vertical selection bounds of the line then you DO NOT have to return
						 anything for the inkBounds, just leave them unchanged (empty).
		@param waxRun : the run in question
		@param waxRenderData : drawing data for the run (font, color, etc.) can be nil (e.g. inline graphic)
		@param waxGlyphs : glyph interface for the run. can be nil (e.g. inline graphic)
	*/
	virtual void GetInkBounds(PMRect *inkBounds,
								const IWaxRun *waxRun,
								const IWaxRenderData *waxRenderData,
								const IWaxGlyphs *waxGlyphs) = 0;

	/** The adornment is allowed to draw.
		@param gd Pointer to the GraphicsData.
		@param iShapeFlags The value of the flags parameter passed into IShape::Draw.
		@param waxRun : the run in question
		@param waxRenderData : drawing data for the run (font, color, etc.) can be nil (e.g. inline graphic)
		@param waxGlyphs : glyph interface for the run. can be nil (e.g. inline graphic)
	*/
	virtual void Draw(GraphicsData *gd, int32 iShapeFlags,
						const IWaxRun *waxRun,
						const IWaxRenderData *waxRenderData,
						const IWaxGlyphs *waxGlyphs) = 0;

	/** Notification that the Parcel has started the pass.
		@param gd Pointer to the GraphicsData.
		@param iShapeFlags The value of the flags parameter passed into IShape::Draw.
		@param parcelShape : Note that parcelShape MAY NOT be a UID based object. */
	virtual void StartOfParcelDraw(GraphicsData* gd, int32 iShapeFlags,
									const IParcelShape *parcelShape) = 0;

	/** Notification that the Parcel has finished the pass.
		@param gd Pointer to the GraphicsData.
		@param iShapeFlags The value of the flags parameter passed into IShape::Draw.
		@param parcelShape : Note that parcelShape MAY NOT be a UID based object. */
	virtual void EndOfParcelDraw(GraphicsData* gd, int32 iShapeFlags,
									const IParcelShape *parcelShape) = 0;

};


//
// Draw priorities of some well known Adobe Global adornments.
//
#define	kTAPriHnJKeepsViolations 	Text::DrawPriority(Text::kTAPassPriBackground + -0.54)
#define	kTAPriMissingFont			Text::DrawPriority(Text::kTAPassPriBackground + -0.52)
#define kTAPriMissingGlyphs			Text::DrawPriority(Text::kTAPassPriBackground + -0.50)
#define kTAPriKinsoku				Text::DrawPriority(Text::kTAPassPriBackground + -0.49)
#define kTAPriCustomCharWidths		Text::DrawPriority(Text::kTAPassPriBackground + -0.49)
#define kTAPriNotes					Text::DrawPriority(Text::kTAPassPriText + 0.30)
#define kTAPriPositionMarker		Text::DrawPriority(Text::kTAPassPriText + 0.35)
#define kTAPriXMLMarkers			Text::DrawPriority(Text::kTAPassPriText + 0.48)
#define kTAPriShowInvisibles		Text::DrawPriority(Text::kTAPassPriForeground +  0.50)
#define kTAPriDynamicSpellCheck		Text::DrawPriority(Text::kTAPassPriForeground +  0.52)

#endif
