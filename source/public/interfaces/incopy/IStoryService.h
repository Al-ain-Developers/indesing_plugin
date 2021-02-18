//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryService.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __ISTORYSERVICE__
#define __ISTORYSERVICE__

#include "IPMUnknown.h"
#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "IFontMgr.h"
#include "IDrawingStyle.h"


class ITextLines;
class IDrawingStyle;
class WideString;
class LineDescription;
class RunDescription;

class IStoryService : public IPMUnknown
{
	public:

		enum { kDefaultIID = IID_ISTORYSERVICE };

			// Used for galley drawing gets a single chunk of glyphs
			// that can be drawn in one burst for galley view. Fills out
			// drawglyphs, widths and invisible characters. Buffers
			// for these glyphs must be passed to this routine.
			// It also returns information on what type of glyphs
			// are being returned with regards to what font style
			// the glyphs should be drawn in.


		/** 	Given a range of indexes provide an array of glyphs to display in the story and galley views.
				This version will also return unicode text values for the range and is less efficient than the version that does not.
				Return number of glyphs
				@param storyThreadDict dict of story thread for range
				@param storyThreadKey thread key to get range for
				@param textLines a pointer to the ITextLines of the view to get the glyphs for. Used to get display font etc.
				@param rangeStart start text index to get glyphs for.
				@param textLength number of characters to get glyphs for.
				@param glyphArray preallocated array to return glyphs in.
				@param widths preallocated array to return glyph width values in.
				@param text a WideString where the unicode values for the range are returned.
				@param rangeWidth draw width of all glyphs (can pass nil if don't care it will be more efficient).
				@param fontStyle if not "returnFullText" this returns the display font style for this range of text (see IFontMgr)
				@param capMode if not "returnFullText" this returns the cap mode for this range of text (see IDrawingStyle)
				@param showInvisibles Pass kTrue to get the routine to calculate hidden character array. Call GetCurrentInvisibles() and GetCurrentInvisiblesWidths() to get array values back after calling this routine
				@param maxSizeSAllowed maximum number of enteries there is space allocated for in the glyphArray param
				@param returnFullText kTrue to ignore run information and return a the full range requested regardless.
		*/
		virtual int32 GetRangeOfDrawGlyphs(UID storyThreadDict,
								   	int32 storyThreadKey,
								   	ITextLines *textLines,
								   	TextIndex rangeStart,
								  	int32 textLength,
								  	int32 *glyphArray, // space allocated by caller filled out by this method
									float *widths, // space allocated by caller filled out by this method
									WideString &text, // returned text
									PMReal *rangeWidth,
									IFontMgr::FontStyleBits &fontStyle,
									IDrawingStyle::CapitalizeMode &capMode,
									bool16 showInvisibles,
								  	int32 maxSizeSAllowed,
								  	bool16 returnFullText) = 0;

			// After calling GetRangeOfDrawGlyphs you may call this routine to get the
			// font to draw in or to measure text with. Galley normally will display in
			// a single display font family but allows for the possibility that the user
			// may have used a font having glyphs that are not displayable correctly in
			// a single display font (such as Symbol font). Galley allows a list of font
			// overrides to be specified. This routine is aware of those and will always
			// return the correct font to display text in.

		virtual IFontInstance *QueryDisplayFontInstanceForCurrentChunk() = 0;
		virtual IPMFont *QueryDisplayFontForCurrentChunk() = 0;

			// Return the glyphs for invisible characters. Must have called GetRangeOfDrawGlyphs
			// for the range of invisibles you are interested in prior to calling these methods.
		virtual int32 *GetCurrentInvisibles() = 0;
		virtual float *GetCurrentInvisiblesWidths() = 0;
		virtual float *GetCurrentInvisiblesYAjustments() = 0;
		virtual int32 GetCurrentInvisiblesLength() = 0;

			// Given a widths array from GetRangeOfDrawGlyphs this routine can be used
			// to find the xPosition from the left of a position.
		virtual PMReal SumCharWidths(float *widths, int32 numOfCharactersIn) = 0;


			// Get the text out of a story useful if you don't care
			// about any style information or glyphs just the straight
			// text.

		virtual void GetStoryContent(UID storyThreadDict,
								   int32 storyThreadKey,
								   TextIndex lineStart,
								   int32 textLength,
								   WideString &lineText) = 0;		// output

		virtual	TextIndex GetStoryThreadIndex(UID storyThreadDict,
								   int32 storyThreadKey,
								   TextIndex inTextIndex) = 0;

			// Given the inTextIndex, return the corresponding text
			// index in the story thread.

		virtual	TextIndex GetStoryThreadEnd(UID storyThreadDict,
								   int32 storyThreadKey,
								   TextIndex inTextIndex) = 0;
			// Given the inTextIndex, return the corresponding text
			// last index in the story thread.

		virtual	TextIndex GetTextLineIndex(UID storyThreadDict,
								       int32 storyThreadKey,
								       TextIndex inTextIndex) = 0;
			// Given the inTextIndex in the story thread, return the
			// corresponding text index in the main story thread.

		virtual IFontMgr::FontStyleBits GetFontStyle(IDrawingStyle *drawStyle) = 0;

		/** 	This is used so when all other attempts to convert a character code to a glyph fail to provide a valid glyph.
				Typically this is because we have a symbol font or some other font that is encoded in the text model with
				platform encoding.
				Return glyph id coorsponding to character code passed in (character)
				@param fontInstance to get glyph width from
				@param font Font to ask for a gyph from
				@param character The character code to convert to a glyph
				@param glyphWidth width of glyph is returned in this variable.
		*/
		virtual Text::GlyphID ConvertToGlyphUsingPlatformEncoding(IFontInstance *fontInstance, IPMFont *font, UTF32TextChar character, PMReal *glyphWidth) = 0;

		/** 	Call to clear the cached glyph data.
				Return void
		*/
		virtual void ClearGlyphCache() = 0;

		/** 	Given a range of indexes provide an array of glyphs to display in the story and galley views.
				This version is more efficient than the version which also will return the model unicode values.
				Return number of glyphs
				@param storyThreadDict dict of story thread for range
				@param storyThreadKey thread key to get range for
				@param textLines a pointer to the ITextLines of the view to get the glyphs for. Used to get display font etc.
				@param rangeStart start text index to get glyphs for.
				@param textLength number of characters to get glyphs for.
				@param glyphArray preallocated array to return glyphs in.
				@param widths preallocated array to return glyph width values in.
				@param rangeWidth draw width of all glyphs (can pass nil if don't care it will be more efficient).
				@param fontStyle if not "returnFullText" this returns the display font style for this range of text (see IFontMgr)
				@param capMode if not "returnFullText" this returns the cap mode for this range of text (see IDrawingStyle)
				@param showInvisibles Pass kTrue to get the routine to calculate hidden character array. Call GetCurrentInvisibles() and GetCurrentInvisiblesWidths() to get array values back after calling this routine
				@param maxSizeSAllowed maximum number of enteries there is space allocated for in the glyphArray param
				@param returnFullText kTrue to ignore run information and return a the full range requested regardless.
		*/
		virtual int32 GetRangeOfDrawGlyphs(UID storyThreadDict,
								   	int32 storyThreadKey,
								   	ITextLines *textLines,
								   	TextIndex rangeStart,
								  	int32 textLength,
								  	int32 *glyphArray, // space allocated by caller filled out by this method
									float *widths, // space allocated by caller filled out by this method
									PMReal *rangeWidth,
									IFontMgr::FontStyleBits &fontStyle,
									IDrawingStyle::CapitalizeMode &capMode,
									bool16 showInvisibles,
								  	int32 maxSizeSAllowed,
								  	bool16 returnFullText) = 0;


		// Set the current lineDescription
		virtual void				SetCurrentLineDescription(LineDescription* lineDescription) = 0;

		// Get the current lineDescription
		virtual LineDescription*	GetCurrentLineDescription() = 0;

		// Set the current runDescription
		virtual void				SetCurrentRunDescription(const RunDescription* runDescription) = 0;

		// Get the current runDescription
		virtual const RunDescription*	GetCurrentRunDescription() = 0;

		// Set the offset of the invisibles glyphs (for a run)
		virtual void				SetInvisiblesOffset(float offset) = 0;

		// Get the offset of the invisibles glyphs (for a run)
		virtual float				GetInvisiblesOffset() = 0;

};

#endif 		// __ISTORYSERVICE__

