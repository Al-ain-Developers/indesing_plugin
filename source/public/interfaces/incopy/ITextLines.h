//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextLines.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __ITextLines__
#define __ITextLines__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "PMRect.h"
#include "IInterfaceColors.h"
#include "IFontMgr.h"
#include "UIDList.h"
#include "LineDescription.h"
#include "IDrawingStyle.h"
#include "IInCopyGalleySettingData.h"
#include "RangeData.h"
#include "K2Vector.h"


class VOS_Object;
class IGraphicsPort;
class IPMFont;
class IWaxLine;
class IFontInstance;
class WideString;
class SelectionExtension;
namespace InDesign { class TextRange;}

class ComposeInformation
{
	public:
		typedef base_type data_type;
		
		UIDRef storyUIDRef;
		TextIndex startIndex;
		int32 length;
		PMReal composeWidth;
};


/** 
	The textlines are what defines what characters are in each line of the display on the screen. These are roughly equivalent to
	the WaxLines in the layout view. This interface owns all line information for the galley and story views. There are methods 
	present in this interface for getting and setting of line information. Normally, non-internal callers will be interested in 
	getting information only. The setting is generally left up the an interaction between this interface an the
	IQuickComposer interface.
	The methods are divided up into several sections...
		Global Attributes - like display font
		LineDescription Access - methods to get information about a specific line
		Line Maintenance - Methods used to modify lines (delete or add or recompose all). Also, there are methods
							to inform callers how many lines there are.
		Searching - Methods to search through lines and find one of interest based on textIndexes mostly.
		Text Display - Methods to display lines on screen.
		View Invaliing - Methods to cause parts of view corresponding to lines to redraw.
		Printing - mostly internal use for changes to drawing that occur when printing.
		Text Offset Type Conversion - story/galley uses two different types of text indices (Display and Model). The model indices
							match the indices in the ITextModel while the display indices match the order that text is actually displayed
							on the screen in galley/story. The methods in this section aid in the conversion between the two types.
		Story Management - methods that deal with the management of multiple stories in a single view. All the stories text lines that
							are displayed in a single view are owned by a single instance of the ITextLines interface. That is to say there
							is one instance of this interface for each story/galley view no matter how many stories are displayed in the view.
							The methods in the story management section help get access to each individual stories text lines.
		
		
	Notes: For routines that do not take a storyIndex it is assumed that the operation will apply to the currently active
		story. See the methods GetCurrentStoryIndex() and SetCurrentStoryIndex(). InCopy can have more than one story active
		in a view. InDesign has a one per view approach.
		
*/
class ITextLines : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTLINES };
		
		// ---------------- TEXTLINES GLOBAL ATTRIBUTES ------------------ //
		enum LinesType { kLayoutLineEnds = 0, kWindowLineEnds }; // kLayoutLine ends is ALE, kWindowLineEnds is ILE
		enum ExtendType { kDontExtend = 0, kExtendLeft, kExtendRight }; // used in some selection routines to control the highlight extension over nonprimary text runs
		
		/**
			Will describe the type of line endings in terms of the LinesType enum. 
			@return It will return either that the lines have kWindowLineEnds meaning that the lines are a story view. Or that the lines
					are kLayoutLineEnds meaning the lines are a galley view (galley view is InCopy only).
		**/
		virtual LinesType GetLinesType() = 0;
		
		/**
			Allows the caller to change the type of line endings. Should normally go through the IGalleyUtils::SetDocWindowView() to do this.
			This call should only be used in InCopy since InDesign doesn't support galley view only story.
			@param lType can pass in either kWindowLineEnds or kLayoutLineEnds (see GetLinesType())
			@return none.
		**/
		virtual void SetLinesType(LinesType lType) = 0;
		
		/**
			Allows the caller to change the display font for the view. This is really for internal use external callers should
			go through kSetGalleyDisplayFontCmdBoss which will end up calling this. 
			@param fontName name of the font to use as a display font.
			@param initializeLines pass true to cause the lines to be recomposed with the new display font information.
			@return none.
		**/
		virtual void UpdateFontInfo(const PMString *fontName, bool16 initializeLines) = 0;
		
		/**
			Allows the caller to change the line spacing amount for the view. This is really for internal use external callers should
			go through kSetLeadingCmdBoss which will end up calling this. 
			@param fontName name of the font to use as a display font.
			@param initializeLines pass true to cause the lines to be recomposed with the new display font information.
			@return none.
		**/
		virtual void UpdateLeading() = 0;
		
		/**
			Can be used to find out the name of the display font. 
			@param styleBits the font variant type (see IFontMgr).
			@return The display font name.
		**/
		virtual PMString &GetDisplayFontName(IFontMgr::FontStyleBits styleBits = IFontMgr::kNormal) = 0;
		
		/**
			Get the point size of the display font. 
			@param styleBits the font variant type (see IFontMgr).
			@return The point size.
		**/
		virtual PMReal GetDisplayFontSize(IDrawingStyle::CapitalizeMode capMode = IDrawingStyle::kCapNormal) = 0;
		
		/**
			Get the height of a line. 
			@param textOnly if you only want to get the text portion not the extra for line spacing pass true.
			@return the height of a line.
		**/
		virtual PMReal GetLineHeight(bool16 textOnly = kFalse) = 0;
		
		/**
			Query an instance of the display font. 
			@param styleBits the font variant type (see IFontMgr).
			@param capMode interested instance of display font for which type kCapSmallLowercase, kCapNormal, kCapAll, kCapSmallEverything.
			@return instance of the display font.
		**/
		virtual IFontInstance *QueryDisplayFontInstance(IFontMgr::FontStyleBits styleBits, IDrawingStyle::CapitalizeMode capMode) = 0;
		
		/**
			Deprecated (don't use won't do anything)
		**/
		virtual bool16 ComposeLayout() = 0;
		
		/**
			Deprecated (don't use won't do anything)
		**/
		virtual void SetComposeLayout(bool16 shouldCompose) = 0;


		// ---------------- LINEDESCRIPTION ACCESS ------------------ //
		
		/**
			Get the text model index of a line start. 
			@param at index of line.
			@return a text model index of the first character in a line.
		**/
		virtual TextIndex GetLineStartOffsetAtLine(int32 at) = 0;
		
		/**
			Get the text model index of a line end. 
			@param at index of line.
			@return a text model index of the last position in the line (index of character at the start of the next line).
		**/
		virtual TextIndex GetLineEndOffsetAtLine(int32 at) = 0;

		/**
			Get the Y offset of the line. 
			@param at index of line.
			@return The y position of the top of the line. The y position of the first line in the view is 0. 
				This is an absolute position, windows and scrolling do not come into play.
		**/
		virtual PMReal GetYPosition(int32 at) = 0;
		
		/**
			Get the left start X offset of a line. 
			@param storyIndex index of story to get line from.
			@return a PMReal which is the X position of the line measured from the left edge of the view. 
		**/
		virtual PMReal GetYPosition(int32 storyIndex, int32 at) = 0;
		
		/**
			Get the left start X offset of a line of the current story. 
			@param at index of line.
			@return a PMReal which is the X position of the line measured from the left edge of the view.  
		**/
		virtual PMReal GetXPosition(int32 at) = 0;
		
		/**
			Get a rectangle describing a line bounds. The rectangle is described in local coordinates of the view.
			@param at index of line.
			@return a PMRect which describes the line. The rectangles right side will actually be a very large number
				not the width of the line.  If the true line width is desired get the LineDescription and check the 
				width field.
		**/
		virtual PMRect CalculateLineRect(int32 at) = 0;
		
		/**
			Get a rectangle describing a line bounds. The rectangle is described in local coordinates of the writingview
			@param storyIndex index of story to get line from
			@param at index of line.
			@return a PMRect which describes the line. The rectangles right side will actually be a very large number
				not the width of the line.  If the true line width is desired get the LineDescription and check the 
				width field.
		**/
		virtual PMRect CalculateLineRect(int32 storyIndex, int32 at) = 0;
		
		/**
			Get a rectangle describing a line bounds. The rectangle is described in local coordinates of the writingview
			@param storyIndex index of story to get line from
			@param at index of line.
			@return a PMRect which describes the line. The rectangles right side will actually be a very large number
				not the width of the line.  If the true line width is desired get the LineDescription and check the 
				width field.
		**/
		virtual const LineDescription GetLine(int32 at, bool16 returnRuns = kFalse) = 0;
		
		/**
			Get a full line description for a specific line. Some data in this structure may not be up to date until
			UpdateLine() is called. Specifically, the text indexes associated with the line are updated with the UpdateLine()
			method (in this same interface see comments by the UpdateLine method).
			@param storyIndex index of story to get line from
			@param at index of line.
			@param returnRuns fill in kTrue to get the RunDescription pointer filled in kFalse (default) otherwise.
			@return a LineDescription class that has information on what is contained in the line.
		**/
		virtual const LineDescription GetLine(int32 storyIndex, int32 at, bool16 returnRuns) = 0;
		
		
		// ---------------- LINE MAINTENANCE ------------------ //
		
		/**
			Recompose all lines. 
			@param composeInformation list of stories to recompose
			@param forceInitialization recompose even if already initialized if TRUE.
			@param scrollARangeIntoView if a range is selected scroll it into view if this is TRUe
			@return none
		**/
		virtual void InitializeLines(const K2Vector<ComposeInformation> &composeInformation, bool16 forceInitialization = kFalse, bool16 scrollARangeIntoView = kFalse) = 0;
		
		/**
			Warning: This should typically only be used internally. The composer will call this to append new lines of text to the view.
			@param line description of the line to append
			@param autoScroll should the view scroll to the current text cursor location after appending the line.
			@return none.
		**/
		virtual void AppendLine(const LineDescription &line, bool16 autoScroll = kTrue) = 0;
		
		/**
			This should typically only be used internally. The composer will call this to insert a new lines of text to the view.
			@param beforeIndex text line index to insert before.
			@param line description of the line to insert.
			@param autoScroll should the view scroll to the current text cursor location after appending the line.
			@return kTrue if the line was inserted successfully kFalse otherwise.
		**/
		virtual bool16 InsertLine(int32 beforeIndex, const LineDescription &line, bool16 autoScroll = kTrue) = 0;
		
		/**
			This should typically only be used internally. The composer will call this to remove unneeded lines from the view.
			@param at index of the line to remove.
			@return kTrue if the line was removed successfully kFalse otherwise.
		**/
		virtual bool16 DeleteLine(int32 at) = 0;
		
		/**
			This should typically only be used internally. The composer will call this to remove all lines from the view.
			@return none.
		**/
		virtual void DeleteAllLines() = 0;
		
		/**
			This should typically only be used internally. The composer will call this to replace a line with a different line description.
			@param at the index of the line to replace.
			@param line description of the new line that will replace the old line information.
			@return kTrue if the line was replaced successfully kFalse otherwise.
		**/
		virtual bool16 ReplaceLine(int32 at, const LineDescription &line) = 0;
		
		/**
			This should typically only be used internally. This is used in galley view only (not story) to add the frame and column dividers.
			This items are actually lines of a specific type. This routine actually decides whether it's should add a divider or not base on the parameters
			passed in.
			@param waxLine layout wax line information for the line that is after the potential frame divider.
			@param at index where the divider might be added before.
			@param atPosition the x position relative to the left side of the view to add the frame divider.
			@param previousLineFrameUID uid of the frame of the wax line before this line.
			@param isFrontMost if view is front most then draw will occur right away otherwise it will simply invalidate and draw later.
			@return kTrue if divider was added kFalse otherwise.
		**/
		virtual bool16 AddFrameDivider(IWaxLine *waxLine, int32 at, const PMPoint &atPosition, UID previousLineFrameUID, bool16 isFrontMost) = 0;
		
		/**
			This should typically only be used internally. Used to create a matching galley line from a layout wax line. Not used in story view.
			@param waxLine layout wax line information to create a matching galley line for.
			@param at index of galley line.
			@param atPosition the x position relative to the left side of the view to add the frame divider.
			@param lineNumber used to display in the info column multiple galley lines may map to one waxline because galley lines also wrap at view edge.
			@param lineID a matching id is stored with the waxline.
			@param isFrontMost if view is front most then draw will occur right away otherwise it will simply invalidate and draw later.
			@return none.
		**/
		virtual void AddLineFromLayoutLine(IWaxLine *waxLine, int32 at, const PMPoint &atPosition, int32 lineNumber, uint32 lineID, bool16 isFrontMost) = 0;
		
		/**
			This should typically only be used internally. Used to remove excess lines that may be present after compostion finishes.
			@param startIndex .
			@param atPosition the x position relative to the left side of the view to add the frame divider.
			@param lineNumber used to display in the info column multiple galley lines may map to one waxline because galley lines also wrap at view edge.
			@param lineID a matching id is stored with the waxline.
			@param isFrontMost if view is front most then draw will occur right away otherwise it will simply invalidate and draw later.
			@return none.
		**/
		virtual void RemoveExcessLines(int32 startIndex, bool16 isFrontMost, bool16 autoScroll = kTrue) = 0;

		/**
			Causes the LineDescription (text index values) to be updated to match the model. This must be called prior to fetching any LineDescription
			and looking at any of the model or display text index fields. Also, it is not a good idea to simply update through the last line index
			this will cause a performance hit as then every line (that is not already updated) prior to the index of the line requested will need
			to be updated. It is highly recommended that the routine GetLineStartOffsetAtLine() or GetLineEndOffsetAtLine() be used when possible instead
			of this call for external users.
			@param at index of line to update through.
			@return none.
		**/
		virtual void UpdateLine(int32 at) = 0;
		
		/**
			Causes the LineDescription (text index values) to be updated to match the model. This must be called prior to fetching any LineDescription
			and looking at any of the model or display text index fields. Also, it is not a good idea to simply update through the last line index
			this will cause a performance hit as then every line (that is not already updated) prior to the index of the line requested will need
			to be updated. It is highly recommended that the routine GetLineStartOffsetAtLine() or GetLineEndOffsetAtLine() be used when possible instead
			of this call for external users.
			@param storyIndex index of story to get line from
			@param at index of line to update through.
			@return none.
		**/
		virtual void UpdateLine(int32 storyIndex, int32 at) = 0;
		
		/**
			It's not expected 3rd parties would use this. This is only set from the composer. Improper use can cause crashes and screen draw problems.
			@param index index of the last valid line
			@return none.
		**/
		virtual void SetLastValidIndex(int32 index) = 0;
		
		/**
			Return the last updated line (see the UpdateLine() method).
			@return index of the last valid line.
		**/
		virtual int32 GetLastValidIndex() = 0;
		
		/**
			Return the last updated line (see the UpdateLine() method).
			@param storyIndex index of story to get last valid line from
			@return index of the last valid line.
		**/
		virtual int32 GetLastValidIndex(int32 storyIndex) = 0;
		
		/**
			Return the index of the last line in the current story
			@return index of the last line.
		**/
		virtual int32 GetLastLineIndex() = 0;
		
		/**
			Return the index of the last line in the specified story
			@param storyIndex index of story to get the last line index of.
			@return index of the last line.
		**/
		virtual int32 GetLastLineIndex(int32 storyIndex) = 0;
		
		/**
			Index of first line that actually might hold text as opposed to a storyBar or other decoration
			@return index of the first line with text in it.
		**/
		virtual int32 GetFirstTrueTextLineIndex() = 0;
		
		/**
			Index of first line that actually might hold text as opposed to a storyBar or other decoration
			@param storyIndex index of story to get first valid index of.
			@return index of the first line with text in it.
		**/
		virtual int32 GetFirstTrueTextLineIndex(int32 storyIndex) = 0;
		
		/**
			Internal use only
			@return none.
		**/
		virtual void DeleteCacheForAllLines() = 0;

		/**
			Update the scroll bar values and scroll the view to the current selection location. 
			@param lockRelativePosition don't scroll just update the scroll bars used during background composition if TRUE
			@param scrollToASelectionRange scroll to a range not just an insertion point if TRUE
			@return none
		**/
		virtual void SyncScrolling(bool16 lockRelativePosition = kFalse, bool16 scrollToASelectionRange = kFalse) = 0;
		
		
		// ---------------- SEARCHING ------------------ //
		/**
			Set an ID is used to connect TextLines to WaxLines. Shouldn't be called externally. Specific to galley view story doesn't care about this
			@param at index of line to assign an id to
			@param newID id to store with a text line this id will match an id stored with a equivalent IWaxLine.
			@return none
		**/
		virtual bool16 SetUniqueIDOfLine(int32 at, uint32 newID) = 0;		
		
		/**
			Return an index of a line with a specific id.
			@param id search the text lines for an id that matches this
			@return returns index of line with matching id or -1 if none is found.
		**/
		virtual int32 FindIndexOfLineWithID(uint32 id) = 0;
		
		/**
			Return an index of a line with a specific id.
			@param storyIndex index of the story to search in.
			@param id search the text lines for an id that matches this
			@return returns index of line with matching id or -1 if none is found.
		**/
		virtual int32 FindIndexOfLineWithID(int32 storyIndex, uint32 id) = 0;
		
		/**
			Finds the line and the offset into the line of the text index requested.
			@param offset text index to search for in the text lines
			@param offsetIntoLine will contain the number of characters into the line the text index falls at.
			@param lean for cases where the text index falls between two lines this param will facilitate the choice the method will make. LeanBack use first line while LeanForward will use the second
			@param checkRunBoundary if true then for deleted text if the offset is at the start of deleted text make sure we get the first line not the line at the end of the deleted text run.
			@return returns index of line that the given text index (offset param) falls in or if none found then -1
		**/
		virtual int32 FindIndexOfLineAtTextOffset(TextIndex offset, int32 &offsetIntoLine, RangeData::Lean lean, bool16 checkRunBoundary = kFalse) = 0;
		
		/**
			Finds the line and the offset into the line of the display index requested.
			@param offset text index to search for in the text lines
			@param offsetIntoLine will contain the number of characters into the line the display index falls at.
			@param lean for cases where the text index falls between two lines this param will facilitate the choice the method will make. LeanBack use first line while LeanForward will use the second
			@return returns index of line that the given display index (offset param) falls in or if none found then -1
		**/
		virtual int32 FindIndexOfLineAtDisplayOffset(                  TextIndex offset, int32 &offsetIntoLine, RangeData::Lean lean) = 0;
		
		/**
			Finds the line and the offset into the line of the display index requested.
			@param storyIndex search in this story for the display index
			@param offset text index to search for in the text lines
			@param offsetIntoLine will contain the number of characters into the line the display index falls at.
			@param lean for cases where the text index falls between two lines this param will facilitate the choice the method will make. LeanBack use first line while LeanForward will use the second
			@return returns index of line that the given display index (offset param) falls in or if none found then -1
		**/
		virtual int32 FindIndexOfLineAtDisplayOffset(int32 storyIndex, TextIndex offset, int32 &offsetIntoLine, RangeData::Lean lean) = 0;
		
		/**
			Finds the corresponding line indeces for a given text index range.
			@param storyIndex to use to get the lines from the range
			@param range find lines corresponding to this text range
			@param low first line with a value in the given range (returned to caller)
			@param high last line with a value in the given range (returned to caller)
			@return none
		**/
		virtual void  DisplayRangeToLineIndices( int32 storyIndex, const RangeData& range, int32* low, int32* high) = 0;
		
		/**
			Given a coordinate in the view give the index of a line at this coordinate
			@param point coordinate to find line at
			@return index of line at the given coordinate if none can be found then -1
		**/
		virtual int32 FindIndexOfLineAtPoint(                  const PMPoint &point) = 0;
		
		/**
			Given a coordinate in the view give the index of a line at this coordinate
			@param point coordinate to find line at
			@return index of line at the given coordinate if none can be found then -1
		**/
		virtual int32 FindIndexOfLineAtPoint(int32 storyIndex, const PMPoint &point) = 0;
		
		/**
			Given a display offset into a line return the horizontal distance this character is drawn at on the screen from the left side of the view.
			@param atLineIndex index of line we want the x-position of a character for
			@param displayOffsetIntoLine display index into a line
			@return draw horizontal distance (pixels) that the character lives at from view left.
		**/
		virtual PMReal GetXPositionOfDisplayOffsetCharacter(                  int32 atLineIndex, int32 displayOffsetIntoLine) = 0;
		
		/**
			Given a display offset into a line return the horizontal distance this character is drawn at on the screen from the left side of the view.
			@param storyIndex story that the line lives in
			@param atLineIndex index of line we want the x-position of a character for
			@param displayOffsetIntoLine display index into a line
			@return draw horizontal distance (pixels) that the character lives at from view left.
		**/
		virtual PMReal GetXPositionOfDisplayOffsetCharacter(int32 storyIndex, int32 atLineIndex, int32 displayOffsetIntoLine) = 0;
		
		/**
			Given a text index offset into a line return the horizontal distance this character is drawn at on the screen from the left side of the view.
			@param atLineIndex index of line we want the x-position of a character for
			@param characterOffsetIntoLine text model index of character (offset into line not from model start)
			@param absoluteTextOffset text model index of character (model start)
			@param isEndPosition is this position at the end of a line.
			@param extend used for track change deleted text (internally) if true extend distance to include the deleted text run adjacent (if present).
			@param absoluteTextEndOffset used internally for track change deleted text leave -1 
			@return draw horizontal distance (pixels) that the character lives at from view left.
		**/
		virtual PMReal GetXPositionOfCharacter(int32 atLineIndex, int32 characterOffsetIntoLine, TextIndex absoluteTextOffset = -1, 
						bool16 isEndPosition = kFalse, ExtendType extend = kDontExtend, TextIndex absoluteTextEndOffset = -1) = 0;
		
		/**
			Given an index of a run within a line and a line index within the current story and a character offset within the run find the
			display distance of that character offset
			@param atLineIndex line index within the current story
			@param index of a run within a line
			@param character offset within the run
			@return return the display index of the requested character offset from run left.
		**/
		virtual PMReal GetXPositionOfCharacterInRun(int32 atLineIndex, int32 runIndex, int32 characterOffsetIntoRun) = 0;


		/**
			Find a character at a given x (horizontal from view left) draw position
			@param atLineIndex line index within the current story
			@param xPosition horizontal postion (from view left)
			@param offsetIntoLine gives the offset (index) within of the line of the hit character.
			@return see note description below.
			The return value means the following:
			kFalse - everything went normally.  All the values are accurate
			kTrue - The xPosition was past the end of line
						offsetIntoLine will contain the first character on the next line
						xPosition will contain the very end of the current line
		**/
		virtual bool16 FindCharacterAtXPosition(int32 atLineIndex, PMReal &xPosition, int32 &offsetIntoLine) = 0;
		
		/**
			Find line at point and return a text index hit in galley display indexes
			@param storyIndex story being hit tested
			@param lineIndex index of line hit
			@param x point to find line at
			@param nextLine text index of the first character in the next line after the line hit (useful for the selection code)
			@return text index of last character in the hit line (text index is in display indexes must convert to model if you wish to use with the text model see DisplayToModelRange())
		**/
		virtual PMReal HitTestText( int32 storyIndex, int32* lineIndex,  const PMPoint &x, TextIndex *nextLine) = 0;
		
		
		/**
			Get first line that intersects the rectangle. This is a quick routine it uses a estimation to
			get close first then zeros in on the first line from there.
			@param rectToFit rectangle to check for a intersecting line
			@param partialFitOK ok to return a line that doesn't totally fall within a rectagle
			@return index of line that first intersects a rectangle (first means starting at text index 0 and incrementing up).
		**/
		virtual int32 GetIndexOfFirstLineInRect(PMRect rectToFit, bool16 partialFitOK = kTrue) = 0;		

		// ---------------- TEXT DISPLAY ------------------ //
		// The following are for drawing hilite. Most likely will be moved to a separate interface.
		/**
			This no longer has meaning in Dragontail (depricated) Set a selection instead
		*/	
		virtual void SetHilite(TextIndex start, TextIndex end, bool16 drawHilite = kTrue, UID extendToDeletedUID = kInvalidUID) = 0;
		
		/**
			This no longer has meaning in Dragontail (depricated) Set a selection instead
		*/			
		virtual void SetHilite(const RangeData& range, bool16 drawHilite = kTrue, UID extendToDeletedUID = kInvalidUID) = 0;
		
		/**
			Method to get the current text highlight information. It really just returns the current selection information
			@param start the beginning of the current text selection
			@param end the end of the current text selection
			@param extendToUIDPair current uids for track change deleted text selection.
			@return kTrue if selection was set.
		*/	
		virtual void GetHilite(TextIndex &start, TextIndex &end, SelectionExtension *extendToDeletedUIDs = nil) = 0;
				
		/**
			Method to draw a text highlight in the story/galley views. Should be called from the selection hiliter (BaseTextSelectionHiliter)
			shouldn't call from other places doing so can cause highlight draws to occur.
			@param newSelection New selection range to draw
			@param oldSelection Old selection range to erase
			@param newExtension New selection extension uids to draw
			@param oldExtension Old selection extension uids to erase
			@return void
		*/	
		virtual void DrawTextHighlight( const InDesign::TextRange& newSelection, const InDesign::TextRange& oldSelection,
				 SelectionExtension *newExtension = nil, SelectionExtension *oldExtension = nil) = 0;

		/**
			Draws a line to the view
			@param at index of line to draw
			@param gPort graphics port to draw in
			@param clipRect rectangle to clip drawing to
			@param scrollCompensationValue value we are to within the view.
			@param displayFont font to display main text of line in may be overridden for special run types or missing glyphs
			@param displaySize size to display text of line at.
			@param topLineInDraw is this the first line draw for this round of drawing. Pass kFalse if not sure
			@return bool16 return kTrue if the line was draw otherwise kFalse (won't draw if does fall within clipRect)
		*/	
		virtual bool16 DrawLine(int32 at, IGraphicsPort *gPort, const PMRect &clipRect, const PMPoint &scrollCompensationValue, 
									IPMFont *displayFont, PMReal displaySize, bool16 topLineInDraw) = 0;
		
		
		// ---------------- VIEW INVALING ------------------ //
		// Methods to store up drawing invals independent of the system invals. Similar to layout view text drawing.
		//
		
		/**
			Invalidate line for later refresh
			@param at index of line to draw
			@param isFrontMost is the view frontMost (can pass false if unsure it will still work)
			@return none
		*/	
		virtual void InvalidateLine(int32 at, bool16 isFrontMost = kFalse) = 0;
		
		/**
			Invalidate run within a line for later refresh. Normally, InvalidateLine is fine instead of this routine and much simpler to use
			@param at index of line to draw
			@param whichRun index of run within line to draw
			@param startOffsetInRun textIndex into run to start inval at
			@param endOffsetInRun text index into run to end inval at
			@param isFrontMost is the view frontMost (can pass false if unsure it will still work)
			@return none
		*/	
		virtual void InvalidateRun(int32 at, int32 whichRun, TextIndex startOffsetInRun, TextIndex endOffsetInRun, bool16 isFrontMost = kFalse) = 0;
		
		/**
			Internal use only
			@return none
		*/	
		virtual void ClearPendingInvalRect() = 0;
		
		/**
			Internal use only. Stores rectanglar area to redraw when window is frontmost which draws sooner than a system inval would.
			@param rectToAdd
			@return none
		*/	
		virtual void AddToPendingInvalRect(const PMRect &rectToAdd) = 0;
		
		/**
			Internal use only doesn't include an area to be redrawn do to a system inval
			@return rectangular area to redraw
		*/	
		virtual PMRect GetPendingInvalRect() = 0;
		
		/**
			Internal use only. Draw all pending invals now don't wait for a system inval to come through
			@param instantDraw request immediate drawing instead of inval. May not happen if drawing is suspended. Usually fine to let inval handle it.
			@return none
		*/	
		virtual void PlayPendingInvals(bool16 instantDraw = kFalse) = 0;
		
		
		// !!! SuspendPlayInvals and ResumePlayInvals must be used in pairs !!!
		/**
			Suspend drawing temporarily while we do some multiple step operations and we don't want to see the screen refreshing during these.
			@return none
		*/	
		virtual void SuspendPlayPendingInvals() = 0;
		
		/**
			Resume drawing (causes a full screen redraw)
			@return none
		*/	
		virtual void ResumePlayPendingInvals() = 0;
		
		/**
			Is drawing currently suspended
			@return kTrue if drawing is NOT suspended.
		*/	
		virtual bool16 GetPlayPendingInvals() const = 0;
				
		/**
			Internal use only. 
		*/	
		
		virtual void RecordUndoRedoPendingInvals(const PMRect& invals) = 0;

		/**
			Internal use only.
		*/	
		virtual PMRect* GetPendingInvalsForUndoRedo() = 0;


		// ---------------- PRINTING ------------------ //
		
		/**
			Get number of pages to print text
			@param rectToFit specifies page height
			@param columns number of columns to print on a page
			@return index of page.
		*/	
		virtual int32 GetPages(PMRect rectToFit, int32 columns) = 0;
		
		/**
			Set ranges of text to print
			@param ranges ranges of text to print
			@return none.
		*/	
		virtual void SetRanges(PMString ranges) = 0;
		
		/**
			Get the line number (galley) of the last line and first line in a story
			@param start first line number in a story (returned)
			@param end last line number in a story (returned)
			@return none.
		*/	
		virtual void GetLineNumberStartEnd(int32& start, int32& end)=0;
		
		/**
			Set stories intial collapse or expanded state when printing
			@param storyList stories and their corresponding collapse state
			@return none.
		*/	
		virtual void InitializeStoryCollapsedState(K2Vector<StoryState> & storyList)=0;
		
		// ---------------- TEXT OFFSET TYPE CONVERSION ------------------ //
		
		/**
			Convert a model text index to a display text index. Mostly for internal use see ModelIndexToDisplayIndex instead.
			@param modelOffset model text index to convert
			@param lineIndex line that the model text index lives in
			@param ignoreRunTypes normally routine will only normally look through run types < RunDescription::endPrimaryStoryTypes if 
									true this routine will look through other types as well. kFalse is normally what is wanted
			@return none.
		*/	
		virtual TextIndex ModelOffsetToDisplayOffset( TextIndex modelOffset, int32 lineIndex, bool16 ignoreRunTypes = kFalse) = 0;

		/**
			Convert a model text index to a display text index
			@param modelIndex to convert
			@return best guess display index see ModelToDisplayRange() for a more accurate conversion (more that one display index may map to a single model index).
		*/	
		virtual TextIndex ModelIndexToDisplayIndex( TextIndex modelIndex) = 0;
		
		/**
			Convert a model text index to a display text index
			@param storyIndex story to use for the conversion
			@param modelIndex to convert
			@return best guess display index (more that one display index may map to a single model index).
		*/	
		virtual TextIndex ModelIndexToDisplayIndex( int32 storyIndex, TextIndex modelIndex) = 0;
		
		/**
			Convert a display text index to a model text index
			@param displayIndex index to convert
			@return model index corresponding to given display index.
		*/	
		virtual TextIndex DisplayIndexToModelIndex( TextIndex displayIndex) = 0;
		
		/**
			Convert a display text index to a model text index
			@param storyIndex index of story to use for conversion
			@param displayIndex index to convert
			@return model index corresponding to given display index.
		*/	
		virtual TextIndex DisplayIndexToModelIndex( int32 storyIndex, TextIndex displayIndex) = 0;
		
		
		// ---------------- STORY MANAGEMENT ------------------- //
		
		/**
			Set the current model display index (used for all routines in ITextLines that don't take a storyIndex).
			Note that these indexes are specific to the story/galley view not the IStoryList interface. See the GetStoryRefList() routine
			in this file. They are indexes into the ref list returned by GetStoryRefList().
			@param i index of story to use
			@return none
		*/	
		virtual void SetCurrentStoryIndex(int32 i) = 0;
		
		/**
			Index of currently active story
			@return index of active story
		*/	
		virtual int32 GetCurrentStoryIndex() = 0;
		
		/**
			Returns the number of stories in displayed in the story/galley view
			@return number of stories.
		*/	
		virtual int32 GetStoryCount() = 0;
		
		/**
			Get a list (in display order) of the uidref's of all stories displayed in the story/galley view.
			@return list of story ref's (kTextStoryBoss)
		*/	
		virtual UIDList *GetStoryRefList() = 0;
		
		/**
			Find the index of a story at a given y view position
			@param yPosition the y view position
			@param ExtendLastLineOfStoryDown count area below the last line of the story as belonging to the last story
			@return index of story at the given yPosition (may be -1 if none found)
		*/	
		virtual int32 FindIndexOfStoryAtYPosition(PMReal yPosition, bool16 ExtendLastLineOfLastStoryDown = kFalse) = 0;
		
		/**
			Get a story ref for a given story index
			@param storyIndex index of story to get a ref for
			@return a UIDRef of the story
		*/	
		virtual const UIDRef &GetStoryRef(int32 storyIndex) = 0;
		
		/**
			Used to rearrange draw order of stories set a ref at a given story index. Should use the higher level kReorderStoriesCmdBoss to do this correctly
			@param ref story to insert
			@param storyIndex index to place story at 
			@return none
		*/	
		virtual void SetStoryRef(const UIDRef &ref, int32 storyIndex) = 0;
		
		/**
			Get the yDraw position of a story
			@param storyIndex story index to get vertical position of
			@return Vertical position from the top of the view where the story will start to draw at
		*/	
		virtual PMReal GetStoryYDrawStart(int32 storyIndex) const = 0;
		
		/**
			Internal use, set the yDraw position of a story
			@param yStartPosition where to start drawing the given story at horizontally.
			@param storyIndex story index to set vertical position of
			@return none
		*/	
		virtual void SetStoryYDrawStart(PMReal yStartPosition, int32 storyIndex) = 0;
		
		/**
			InCopy only stories may be collapsed (hidden except for story divider) see if this is true for a given story
			@param storyIndex index to check if collapsed
			@return kTrue if collapsed
		*/	
		virtual bool16 IsStoryCollapsed(int32 storyIndex)  = 0;
		
		/**
			For a list of story indeces in a view set the collapse state
			@param stories indices to collapse or expand
			@param collapse kTrue to collapse or false to expand
			@return none
		*/	
		virtual void SetStoryCollapseState(const K2Vector<int32> &storyIndexes, bool16 collapse) = 0;
		
		/**
			A story divider bar may be selected (InCopy only) see if it is selected
			@param storyIndex index of story (and associated story bar to check)
			@return is the bar selected if so returns kTrue
		*/	
		virtual bool16 IsStoryBarSelected(int32 storyIndex) = 0;
		
		/**
			Mark a story bar as selected (internal use)
			@param storyIndex index of story (and associated story bar to check)
			@param selected value to set selected state to. kTrue if want to select.
			@return none
		*/	
		virtual void SetStoryBarSelected(int32 storyIndex, bool16 selected) = 0;
		
		/**
			Clear a view of all stories must put stories back in quickly. Should only be used internally normally
			@return none
		*/	
		virtual void RemoveAllStories() = 0;
		
		/**
			Is view displaying track changes and notes.
			@return none
		*/	
		virtual bool8 GetUseTextRuns() = 0;
		
		// Other methods for story management live in the IStoryManager interface
		friend class StoryManager;
private:
		/**
			Get internal list information for all stories in the view
			@return a vector with the stories in the view
		*/	
		virtual K2Vector<StoryDescription> &GetStories() = 0;
		
		/**
			Update the y draw positions of all stories called when typing adds or deletes a line.
			@param redraw kTrue to redraw story
			@return none
		*/	
		virtual void UpdateStoryStarts(bool16 redraw = kTrue) = 0;
public:

		/**
			Draw a highlight range while erasing previous range. Called internally to match selection state.
			@param storyIndex index of story to operate on
			@param newRange range to select (highlight)
			@param oldRange range to deselect (unhighlight)
			@return none
		*/	
		virtual void DrawTextDisplayHighlight(int32 storyIndex, const RangeData& newRange, const RangeData& oldRange) = 0;

		/**
			Convert a display index to a model index
			@param storyIndex index of story to operate on
			@param displayIndex display index to convert
			@return corresponding model index
		*/	
		virtual TextIndex DisplayIndexToModelIndex_( int32 storyIndex, TextIndex displayIndex) = 0;
		
		/**
			Convert a model range to a display index range
			@param storyIndex index of story to operate on
			@param modelRange model index range to convert
			@param leftExtra only used for track changes external users should most likely pass kInvalidUID
			@param rightExtra only used for track changes external users should most likely pass kInvalidUID
			@return corresponding display range
		*/	
		virtual RangeData ModelToDisplayRange( int32 storyIndex, const RangeData& modelRange, UID leftExtra, UID rightExtra) = 0;
		
		/**
			Convert a display range to a model index range
			@param storyIndex index of story to operate on
			@param displayRange display index range to convert
			@param leftExtra external callers may ignore.
			@param rightExtra external callers may ignore.
			@return corresponding model index range
		*/	
		virtual RangeData DisplayToModelRange( int32 storyIndex, const RangeData& displayRange, UID* leftExtra, UID* rightExtra) = 0;
		
		/**
			For a given caret position return an atomic range surrounding it (internal use)
			@param storyIndex index of story to operate on
			@param caret model index
			@param relativeTo extra data for internal use.
			@return the atomic range
		*/	
		virtual RangeData AtomicRange( int32 storyIndex, RangeData caret, const RangeData& relativeTo) = 0;
};

#endif 		// __ITextLines__
