//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LineDescription.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __LineDescription__
#define __LineDescription__

#include "IInterfaceColors.h"
#include "ITextUtils.h"


#ifdef PUBLIC_BUILD
#pragma export on
#endif
class CDynamicSpellCheckCache;
class RealAGMColor;
class StoryDescription;
class PMRealGlyphPoint;


/**
	GlyphDrawAddIn - used to track special icon drawing locations.
*/
class PUBLIC_DECL GlyphDrawAddIn
{
public:
	typedef object_type data_type;

	/** AddInType - Enum defines general type of icon to draw if any.
	*/
	enum AddInType
	{
		/** Indicates regular text although it's generally not recorded */
		kNone,

		/** Indicates an owned item icon like a xml tag or inline text frame. */
		kOwnedItemIcon,

		/** Indicates an attribute icon, mostly J features like ruby or CJK text */
		kAttributeIcon
	};

	/** See enum definition above */
	AddInType fType;

	/** Index within run where item draws */
	int32 glyphIndex;
};

class LineDescriptionME;

/**
	Cache of drawing style so it doesn't need to be calculated at draw time
*/
class PUBLIC_DECL DrawingChunkRange
{
public:
	typedef object_type data_type;

	/** Describes the variant of the font to draw in, meant to be or'd together
	*/
	enum FontDrawStyle
	{
		/** Use normal font */
		kNormal = 0x00,

		/** Use bold variant */
		kBold = 0x02,

		/** Use italic variant */
		kItalic = 0x04,

		/** Display using all caps */
		kAllCaps = 0x08,

		/** Dispaly using small caps */
		kSmallCaps = 0x10
	};

	/** Describes the variant of the font */
	FontDrawStyle fFontStyle;

	/** fUseModelFont - if true override normal story display font with the current model font, used for codes that can't be represented in normal display font */
	bool16 fUseModelFont;

	/** Length of this chunk of glyphs */
	uint16 fLength;
};


/**
	Class which caches glyph data and other draw related attributes for story galley view.
*/
class PUBLIC_DECL StoryRunGlyphs
{
public:
	/** object_type - internal use K2Vector detail. */
	typedef object_type data_type;

	/**
		Constructor for StoryRunGlyphs.
		@return none.
	**/
	StoryRunGlyphs();

	/**
		Destructor for a StoryRunGlyphs.
		@return none.
	**/
	virtual ~StoryRunGlyphs();

	/** internal use only undo/redo support. */
	void ReadWrite(IPMStream* s, StoryDescription *storyDesc);

	/** fGlyphPoints - Cached glyphs to display in story or galley view */
	K2Vector<PMRealGlyphPoint> *fGlyphPoints;

	/** fGlyphPoints - special types of text like icons are tracked in this array */
	K2Vector<GlyphDrawAddIn> *fAddIns;

	/** Describes what text style to draw glyphs in */
	K2Vector<DrawingChunkRange> *fDrawRanges;
};

/**
	Each LineDescription may have 0 or more RunDescriptions. A RunDescription defines a specific type of item display in story/galley
	(See RunType enum) and range of text in a line. The RunDescriptions are created along with the line description during
	composition. These should not in general be modified by third parties but can be looked at to find out information about line text.
*/
class PUBLIC_DECL RunDescription
{
	public:
		/** object_type - internal use K2Vector detail. */
		typedef object_type data_type;


		/**
			Constructor for RunDescription.
			@return none.
		**/
		RunDescription();

		/**
			Constructor for RunDescription.
			@param src - source run to base new rundescription on
			@return none.
		**/
		RunDescription(const RunDescription& src);

		/**
			Destructor for a RunDescription.
			@return none.
		**/
		virtual ~RunDescription();

		/**
			Operator overload for '=' necessary for the fDynamicSpellCheckCache copying
			@param src - source run to base new rundescription on
			@return a RunDescription created from the src description.
		**/
		RunDescription& operator= (const RunDescription& src);

		/** internal use only undo/redo support. */
		void ReadWrite(IPMStream* s, StoryDescription *storyDesc);


		/** RunType - Enum defines different possible run types for a RunDescription.
		*/
		enum RunType
		{
			/** regularText - Standard vanilla text */
			regularText = 0,

			/** movedText - Tracked change added text */
			addedText,

			/** movedText - Tracked change moved text */
			movedText,

			baselessBeginTag,
			baselessEndTag,

			/** endPrimaryStoryTypes - Enum value to separate main story text from anchored text types like inline notes and deleted text.
				Enums values greater than this value are anchored in the main text. Enum values less than this value are main story text */
			endPrimaryStoryTypes,

			/** deletedText - Tracked change deleted text */
			deletedText,

			/** inlineNoteText - The text portion of an inline note */
			inlineNoteText,

			/** inlineNoteBeginTag - The begin tag portion of an inline note */
			inlineNoteBeginTag,

			/** inlineNoteBeginTag - The end tag portion of an inline note */
			inlineNoteEndTag,

			/** xmlBeginTag - obsolete handled by IOwnedItemIcons instead */
			xmlBeginTag,

			/** xmlEndTag - obsolete handled by IOwnedItemIcons instead */
			xmlEndTag,

			/** xmlStoryTag - obsolete handled by IOwnedItemIcons instead */
			xmlStoryTag,

			/** footnoteText - The text portion of a footnote */
			footnoteText,

			/** footnoteBeginTag - The begin tag portion of a footnote */
			footnoteBeginTag,

			/** footnoteBeginTag - The end tag portion of a footnote */
			footnoteEndTag,

 			xmlRTLBeginTag,
			xmlRTLEndTag,
			footnoteRTLBeginTag,

			/** tableText - text in a table */
			tableText
		};
		
		// 2008/01/28 MH: WARNING!!! DON'T FORGET TO UPDATE THIS MACRO IN CASE OF ADDING OR REMOVING a RunType
#define STORYEDITOR_CONTEXTUALIZED_RUN(runType)\
		((runType == RunDescription::regularText)\
		|| (runType == RunDescription::addedText)\
		|| (runType == RunDescription::movedText)\
		|| (runType == RunDescription::deletedText)\
		|| (runType == RunDescription::inlineNoteText)\
		|| (runType == RunDescription::footnoteText)\
		|| (runType == RunDescription::tableText))

		/** startModelOffset - Start offset of the text run.  These are text model offsets. See ITextLines for discussion of display vs model offsets */
		TextIndex startModelOffset;

		/** startDisplayOffset - Start offset of the text run.  These are galley display offsets. */
		TextIndex startDisplayOffset;

		/** length - length of the run, same for display and model offsets */
		int32 length;

		/** anchorPoint - Some non-primary runs need to know the index they start drawing at in the primary story (their anchor position) this stores this */
		TextIndex anchorPoint;

		/** type - Describes how this run draws and behaves. See RunType comments for description of different possible types */
		RunType type;

		/** color - highlight color, used for tracked change text types */
		RealAGMColor color;

		/** textcolor - text color, used for tracked change text types */
		RealAGMColor textcolor;

		/** width - width of run in pixels */
		PMReal	width;

		/** xPosition - pixel position from line start where the run starts drawing */
		PMReal xPosition;

		/** storyThreadRef - reference to find the non-primary story thread for runs not in the primary story */
		UIDRef	storyThreadRef;

		/** onlyContainsEndCharacter - Is kTrue to indicate that this is a special type of inlineNoteText or footnote run with only the end story thread character present.  */
		bool16 onlyContainsEndCharacter;

		/** onlyContainsEndCharacter - used to cache dynamic spell check information.  */
		CDynamicSpellCheckCache* fDynamicSpellCheckCache;

		/** Glyphs that are shown in this run.  */
		StoryRunGlyphs* fGlyphCache;

		/** fThreadDictKey - Used to find thread associated with this run. */
		uint32 fThreadDictKey;

		/** fSecondaryType - More information describing run for example table text may be also track change added text. So it would have a type of tableText and a secondary type of addedText */
		RunType fSecondaryType;

		int32	level;					// direction level of the run
		int32	glyphIndex;				// index of the first glyph in LineDescriptionME::fStrikes
		int32	glyphLength;			// number of glyphs for this run in LineDescriptionME::fStrikes
		int32	complementaryFontIndex;
};

/**	Default value for a psuedoLineID variable in LineDescription. All other values indicate a type of psuedoline used for background composing
*/
#define NoPsuedoComposeID 0

/**
	The LineDescription interface is a storage cache for the drawing of galley and story view text. The line data is filled out
	during text composition. It is related closely to the IWaxLines in layout view in the case of galley view with
	line endings. For story view most of the same data will be maintained, lineNumbers and lineID's
	have no meaning in story view.
*/
class PUBLIC_DECL LineDescription
{
	public:
		/** object_type - internal use K2Vector detail. */
		typedef object_type data_type;

		virtual ~LineDescription();

		/** LineType - Enum defines different possible line types for a LineDescription.
		*/
		enum LineType
		{
			/** textWithLineNumber - text that has an associated line number in the info column.  Only for galley view ignored in story view. */
			textWithLineNumber = 0,

			/** textWithLineNumber - text that has no associated line number in the info column (paragraph style name column). */
			textWithoutLineNumber,

			/** pageDivider - a line that indicates a page transition (galley view only). */
			pageDivider,

			/** columnDivider - a line that indicates a column transition (galley view only). */
			columnDivider,

			/** frameDivider - a line that indicates a frame transition (galley view only). */
			frameDivider,

			/** frameDivider - a line that indicates a transition to overset text (galley view only). */
			oversetDivider,

			/** storyBar - InCopy only the first line of the story is a bar that shows the story name and a widget to collapse or expand the story. */
			storyBar,

			/** paraDivider - not used */
			paraDivider,

			/** tableRowDivider - a divider line that indicates a transition to a new row (story and galley views). */
			tableRowDivider,

			/** tableColumnDivider - a divider line that indicates a transition to a  new column (story and galley views). */
			tableColumnDivider,
		};
		static const int32 kMaxViewSpace;

		/** LineAttributes - Currently not used possible use for alternate implementation of overset divider.
		*/
		enum LineAttributes
		{
			none = 0x0,
			oversetSplitLineStart = 0x1,
			oversetSplitLineEnd = 0x2
		};

		/** Constructor for LineDescription
			@return none
		*/		LineDescription();
		LineDescription(const LineDescription& other);

		/** internal use only undo/redo support. */
		void ReadWrite(IPMStream *s, StoryDescription *storyDesc);

		/** lineStartOffset - Start position of the text line (text model offsets). These are not always up to date use ITextLines::GetLineStartOffsetAtLine()
			to get updated value for sure may be a time penality to calculate if not updated.
		*/
		TextIndex lineStartOffset;

		/** lineEndOffset
		*/
		TextIndex lineEndOffset;

		/** tableThreadStartOffset - Start position of the text line (text model offsets) in terms of the table cell. These are not always 
		filled up. Only to be populated in case the line corresponds to a table cell in the text model.
		*/
		TextIndex tableThreadStartOffset;

		/** tableThreadEndOffset
		*/
		TextIndex tableThreadEndOffset;

		/** displayStartOffset - Start position of the text line (display model offsets). Not alway up to date have to call ITextLine::UpdateLine()
			to update the value if not already correct. Can be a time penality calling UpdateLine() if it actually needs to update. See ITextLines.
		*/
		TextIndex displayStartOffset;

		/** displayEndOffset - End position of the text line (display model offsets). Not alway up to date have to call ITextLine::UpdateLine()
			to update the value if not already correct. Can be a time penality calling UpdateLine() if it actually needs to update. See ITextLines.
		*/
		TextIndex displayEndOffset;

		/** xPosition - Where to draw the line in local view coordinates from left side of the view.
			Note, there is no yPosition the yPosition is calculated dynamically. See ITextLines::GetYPosition() */
		PMReal xPosition;

		/** lineWidth - The width of the line in pixels. */
		PMReal lineWidth;

		/** lineID - matches unique id stored in ILayoutViewLineData for mapping between galley and layout line data (used in galley view only). */
		int32 lineID;

		/** lineNumber - the line number that corresponds to the layout view line number. Not necessarily the same as the lineindex+1 (galley view only) */
		int32 lineNumber;

		/** typeLine - Describes how this line draws and behaves see comments for enum LineType */
		LineType typeLine;

		/** typeLine - Line ends in a hyphenated word (galley view only story view doesn't hyphenate) */
		bool16 hyphenAtEnd;

		/** paraEndCharacter - Line ends in a paragraph return or other character that starts a new paragraph. */
		bool16 paraEndCharacter;

		/** overlapsWithNext - Line contains a run which overlaps with the next line (inline notes for example) requires extra invaling. */
		bool16 overlapsWithNext;

		/** psuedoLineID - used to mark line as being psuedo composed and needing background composition. */
		int32 psuedoLineID;

		/** attributes - used as a compact storage mechanism for various line settings (internal use only). */
		uint32 attributes;

		/** fTextRuns - Pointer to a vector of runs. See comments for RunDescription. */
		K2Vector<RunDescription> *fTextRuns;
		LineDescriptionME* fMEData;
};

/**
	This class is used to track stories that have psuedo lines in them for background composition.
*/
class PUBLIC_DECL UncomposedIDNode
{
	public:
		/** object_type - internal use K2Vector detail. */
		typedef object_type data_type;

		/** Constructor.
			@return none
		*/		UncomposedIDNode();
		void ReadWrite(IPMStream* s);

		/** fID - internal use only. */
		int32 fID;

		/** fLineIndexHint - internal use only. */
		int32 fLineIndexHint;
};

/**
	Used to make a vector of stories for multiple stories in one panel galley view and story view. InDesign
	will only have one story per window (view) but InCopy may have many.
*/
class PUBLIC_DECL StoryDescription
{
	public:
		/** object_type - internal use K2Vector detail. */
		typedef object_type data_type;

		/** ViewComposeOptions - These are values correspond to session preferences that affect the way text is composed on a view level. They are duplicated
			here because on undo the StoryDescription data is restored from snapshot data but this might be in disagreement with the session settings that had
			changed but do not get undone on the document level. Therefore we do a compare between the compose settings that view story has verses the version
			in the session to determine if any fix up needs to occur. It's an imperfect world, sigh.
		*/
		enum ViewComposeOptions
		{
			/** kDisplayTextOnly - basic text. */
			kDisplayTextOnly = 0,

			/** kDisplayInlineNotes - basic text with inline notes. */
			kDisplayInlineNotes = 1,

			/** kDisplayFootnotes - basic text with footnotes. */
			kDisplayFootnotes = 2,
		};

		/** Constructor.
			@return none
		*/		StoryDescription();

		virtual ~StoryDescription();

		/** internal use only undo/redo support. */
		void ReadWrite(IPMStream *s);

		/** fStoryRef - UID reference of the text model display in the story. */
		UIDRef fStoryRef;

		/** fYFirstLineStartPosition - how far down from the top of the view in pixels to start drawing this story. */
		PMReal fYFirstLineStartPosition;

		/** fLastValidIndex - last update line index in the story (See ITextLines::UpdateLine()). */
		int32 fLastValidIndex;

		/** fStoryOversetDividerIndex - If there is an overset divider adornment drawn this will mark which line index to draw it at.
			If there is none then it will be -1. */
		int32 fStoryOversetDividerIndex;

		/** fCollapsed - InCopy allows stories to be collapsed if this story is collapse then this will be kTrue */
		bool16 fCollapsed;

		/** fStoryBarSelected - Story bars are not regular text so they must be marked as being selected specially. This
			will be true if the storybar is selected. */
		bool16 fStoryBarSelected;

		/** fViewComposeOptions - Values from ViewComposeOptions enum, may be or'd to gether. */
		uint32 fViewComposeOptions;

		bool operator < (const StoryDescription& other) const
			{return fStoryRef.GetUID() < other.fStoryRef.GetUID();}

		bool operator == (const StoryDescription& other) const
			{return &other == this;}

		/** fTextLines - pointer to a vector of LineDescriptions representing the lines in the story */
		K2Vector<LineDescription> *fTextLines;

		/** fUncomposedIDs - pointer to a vector of psuedo composed lines (for background composition) */
		K2Vector<UncomposedIDNode> *fUncomposedIDs;
};

#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif // __LineDescription__
