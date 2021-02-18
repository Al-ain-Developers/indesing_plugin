//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextUtils.h $
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
#ifndef __ITextUtils__
#define __ITextUtils__

#include "IPMUnknown.h"		// super class

#include "TextID.h"			// default IID
#include "CTextEnum.h"		// for Text::GridAlignmentMetric, etc
#include "IScaleObject.h"
#include "LanguageID.h"		// return from ScriptToLanguageID()
#include "TextAttrID.h"		// for default params to RemapFontStyles()
#include "OwnedItemDataList.h"	// for OwnedItemDataList template
#include "K2SmartPtr.h"			// for struct TextAttrs
#include "AttributeBossList.h"	// for K2::scoped_ptr<AttributeBossList>
#include "RangeData.h"			// for StoryRange
#include "ITextOptions.h"
#include "ITextStoryThreadDictHier.h"
#include "IMultiColumnTextFrame.h"
#include "BravoForwardDecl.h"	// for kDontKnowScript
#include "IDrawingStyle.h"
#include "ICreateMCFrameData.h"

class AttributeBossList;
class CursorSpec;
class IBaselineGridPrefs;
class ICommand;
class IComposeScanner;
class IControlView;
class IDocument;
class IFontFamily;
class IFontGroup;
class IFrameList;
class IGeometry;
class IGraphicFrameData;
class IHierarchy;
class IInkResourceData;
class IItemStrand;
class ILayoutTarget;
class IPMFont;
class IParcel;
class IShape;
class ITextAttrFont;
class ITextAttrUID;
class ITextFocus;
class ITextFrameColumn;
class ITextModel;
class ITextParcelList;
class ITextStoryThread;
class ITextTarget;
class IVisitorHelper;
class ParcelKey;
class UIDList;
class WideString;
class IBaselineFrameGridData;
class IGraphicFrameData;
class IWaxLine;

//#include "IWordCountInfoData.h"
//#include "TextStoryThreadHelper.h"
class TextStoryThreadHelper;

#include <utility>

/** Function for making character - character determinations.
	E.g. do these characters separate words? Paragraphs?
*/
typedef bool16 (*FuncIsWordChar)( const UTF32TextChar& aStart, const UTF32TextChar& aEnd );

/** Invalid chapter number
*/
#define kInvalidChapterNumber -1

/** Utility functions for creating text-related commands and for gather text information.
	e.g.
	<pre>Utils&lt;ITextUtils&gt;()->QueryCopyStoryCommand( ... ) ;</pre>
	@ingroup text_util
*/
class ITextUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTUTILS };


	typedef K2Vector<InterfacePtr<IVisitorHelper> >	VisitableItems;
	typedef K2Vector<TextIndex>	HIndexList;

	/** Function for copying text from one story to another.
	This replaces the range in the destination story with a copy of the specified text from the source story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on copy, default to kFalse
	*/
	virtual ICommand* QueryCopyStoryCommand(const UIDRef& source, const UIDRef& dest, const StoryRange& sourceRange, const StoryRange& destRange, const bool16 ignoreAttributes = kFalse ) = 0;

	/** Function for copying text from one story to another.
	This copies the specified text from the source story to the end of the destination story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on copy, default to kFalse
	*/
	virtual ICommand* QueryCopyStoryToEndCommand(const UIDRef& source, const UIDRef& dest, const StoryRange& sourceRange, const bool16 ignoreAttributes = kFalse ) = 0;

	/** Function for copying all of the text from one story to another.
	This replaces the destination story with a copy of the source story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on copy, default to kFalse
	*/
	virtual ICommand* QueryCopyStoryFromAllToAllCommand(const UIDRef& source, const UIDRef& dest, const bool16 ignoreAttributes = kFalse ) = 0;

	/** Function for copying text from one story to another.
	This copies the entire source story to the end of the destination story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on copy, default to kFalse
	*/
	virtual ICommand* QueryCopyStoryFromAllToEndCommand(const UIDRef& source, const UIDRef& dest, const bool16 ignoreAttributes = kFalse ) = 0;

	/** Function for moving text from one story to another.
	This replaces the range in the destination story with the specified text from the source story.
	The source range is removed from the source story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on move, default to kFalse
	*/
	virtual ICommand* QueryMoveStoryCommand(const UIDRef& source, const UIDRef& dest, const StoryRange& sourceRange, const StoryRange& destRange, const bool16 ignoreAttributes = kFalse ) = 0;

	/** Function for moving text from one story to another.
	The entire source story is moved to the destination range.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on move, default to kFalse
	*/
	virtual ICommand* QueryMoveStoryFromAllCommand(const UIDRef& source, const UIDRef& dest, const StoryRange& destRange, const bool16 ignoreAttributes = kFalse ) = 0;

	/** Function for moving text from one story to another.
	This replaces the destination story with the source story.
	The source range is removed from the source story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on move, default to kFalse
	*/
	virtual ICommand* QueryMoveStoryFromAllToAllCommand(const UIDRef& source, const UIDRef& dest, const bool16 ignoreAttributes = kFalse) = 0;

	/** Function for moving text from one story to another.
	This moves the entire source story to the end of the destination story.
	The source range is removed from the source story.
	@param source The UIDRef of the source ITextModel.
	@param dest The UIDRef of the destination ITextModel.
	@param ignoreAttributes Ignore the attributes on move, default to kFalse
	*/
	virtual ICommand* QueryMoveStoryFromAllToEndCommand(const UIDRef& source, const UIDRef& dest, const bool16 ignoreAttributes = kFalse) = 0;

	/**	Creates the command to create a new multi-column text frame with a new story and a new frame list.

		@param parent - Parent page item under which to create the new frame.
		@param noGraphicAttr - kTrue if not to set object styles for the new frame. kFalse otherwise. Usually set to kTrue.
		@param boundary - Boundary (in pasteboard coordinates) of the spline where multi-column frame will be created.
		@param isHorizontal - kTrue if the new story orientation is horizontal, kFalse if it is vertical. Default is kTrue.
		@param isFrameGrid - kTrue if the new story is a frame grid. kFalse if it is a text frame. Default is kFalse.
		@param isLeftToRight - kTrue if the new story direction is left to right. kFalse if it is right to left. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.
		@param isEndnoteStory - Is the new text frame going to be part of an endnote story? Default is kFalse.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateNewMCFrameCommand(UIDRef parent,
												bool16 noGraphicAttr,
												const PMRect& boundary,
												bool16 isHorizontal = kTrue,
												bool16 isFrameGrid = kFalse,
												bool16 isLeftToRight = kTrue,
												ClassID frameItem = kFrameItemBoss,
												bool16 isEndnoteStory = kFalse) = 0;

	/**	Creates the command to create a new multi-column text frame with a new story and a new frame list.

		@param parent - Parent page item under which to create the new frame.
		@param noGraphicAttr - kTrue if not to set object styles for the new frame. kFalse otherwise. Usually set to kTrue.
		@param opposingCorners - Opposing corners (in pasteboard coordinates) of the spline where multi-column frame will be created.
		@param isHorizontal - kTrue if the new story orientation is horizontal, kFalse if it is vertical. Default is kTrue.
		@param isFrameGrid - kTrue if the new story is a frame grid. kFalse if it is a text frame. Default is kFalse.
		@param isLeftToRight - kTrue if the new story direction is left to right. kFalse if it is right to left. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateNewMCFrameCommand(UIDRef parent,
												bool16 noGraphicAttr,
												const PMPointList& opposingCorners,
												bool16 isHorizontal = kTrue,
												bool16 isFrameGrid = kFalse,
												bool16 isLeftToRight = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to create a new multi-column text frame, attaches to an existing story and starts a new frame list.

		@param parent - Parent page item under which to create the new frame.
		@param noGraphicAttr - kTrue if not to set object styles for the new frame. kFalse otherwise. Usually set to kTrue.
		@param boundary - Boundary of the spline where multi-column frame will be created.
		@param story - The existing story to which the new frame will attach.
		@param isHorizontal - kTrue if the story orientation set to horizontal, kFalse if it is vertical. Default is kTrue.
		@param isFrameGrid - kTrue if the story set to a frame grid. kFalse if it is a text frame. Default is kFalse.
		@param isLeftToRight - kTrue if the story direction set left to right. kFalse if it is right to left. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateNewMCFrameForStoryCommand(UIDRef parent,
												bool16 noGraphicAttr,
												const PMRect& boundary,
												ITextModel* story,
												bool16 isHorizontal = kTrue,
												bool16 isFrameGrid = kFalse,
												bool16 isLeftToRight = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to create a new multi-column text frame and insert to the end or beginning of the specified frame list.

		@param parent - Parent page item under which to create the new frame.
		@param noGraphicAttr - kTrue if not to set object styles for the new frame. kFalse otherwise. Usually set to kTrue.
		@param boundary - Boundary of the spline where multi-column frame will be created.
		@param frameList - The existing frame list into which the new frame will be inserted.
		@param atEnd - kTrue if the new frame will be appended to the end of the frame list,
						kFalse if it will be inserted to the beginning of the frame list. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateNewMCFrameForFrameListCommand(UIDRef parent,
												bool16 noGraphicAttr,
												const PMRect& boundary,
												IFrameList * frameList,
												bool16 atEnd = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to create a new multi-column text frame and insert into an existing frame list. The new frame will be inserted before or after
		the specified IMultiColumnTextFrame.

		@param parent - Parent page item under which to create the new frame.
		@param noGraphicAttr - kTrue if not to set object styles for the new frame. kFalse otherwise. Usually set to kTrue.
		@param boundary - Boundary of the spline where multi-column frame will be created.
		@param mcFrame - The multi-column frame in the existing frame list before or after which the new frame will be inserted.
		@param insertAfter - kTrue if the new frame will be inserted after mcFrame,
						kFalse if it will be inserted before mcFrame. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateNewMCFrameForFrameListCommand(UIDRef parent,
												bool16 noGraphicAttr,
												const PMRect& boundary,
												IMultiColumnTextFrame * mcFrame,
												bool16 insertAfter = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to create a new multi-column text frame and insert into an existing frame list.

		The other 2 versions of QueryNewMCFrameForFrameListCmd are recommended. This version is just for use in case if you want to insert the new frame
		to the middle of the frame list and don't have the corresponding IMultiColumnTextFrame. But this case is rare.

		@param parent - Parent page item under which to create the new frame.
		@param noGraphicAttr - kTrue if not to set object styles for the new frame. kFalse otherwise. Default is kTrue.
		@param boundary - Boundary of the spline where multi-column frame will be created.
		@param frameList - The existing frame list into which the new frame will be inserted.
		@param insertIndex - index in the frame list where the new frame will be inserted.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateNewMCFrameForFrameListCommand(UIDRef parent,
												bool16 noGraphicAttr,
												const PMRect& boundary,
												IFrameList * frameList,
												int32 insertIndex,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to convert an existing frame to a multi-column text frame with a new story and a new frame list.

		@param parent - Existing frame which will be converted to multi-column frame.
		@param isHorizontal - kTrue if the new Story orientation is horizontal, kFalse if it is vertical. Default is kTrue.
		@param isFrameGrid - kTrue if the new Story frame is a frame grid. kFalse if it is a text frame. Default is kFalse.
		@param isLeftToRight - kTrue if the new Story direction is left to right. kFalse if it is right to left. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateConvertToMCFrameCommand(UIDRef parent,
												bool16 isHorizontal = kTrue,
												bool16 isFrameGrid = kFalse,
												bool16 isLeftToRight = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to convert an existing frame to a multi-column text frame, attaches to an existing story and starts a new frame list.

		@param parent - Existing frame which will be converted to multi-column frame.
		@param story - The existing story to which the multi-column frame will attach.
		@param isHorizontal - kTrue if Story orientation set to horizontal, kFalse if it is vertical. Default is kTrue.
		@param isFrameGrid - kTrue if the Story frame set to a frame grid. kFalse if it is a text frame. Default is kFalse.
		@param isLeftToRight - kTrue if the Story direction set to left to right. kFalse if it is right to left. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateConvertToMCFrameForStoryCommand(UIDRef parent,
												ITextModel* story,
												bool16 isHorizontal = kTrue,
												bool16 isFrameGrid = kFalse,
												bool16 isLeftToRight = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to convert an existing frame to a multi-column text frame and insert at the end or beginning of an existing frame list.

		@param parent - Existing frame which will be converted to multi-column frame.
		@param frameList - The existing frame list into which the multi-column frame will be inserted.
		@param atEnd - kTrue if the multi-column frame will be appened to the end of the frame list, kFalse if it will be inserted to the beginning of the frame list. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateConvertToMCFrameForFrameListCommand(UIDRef parent,
												IFrameList* frameList,
												bool16 atEnd = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to convert an existing frame to a multi-column text frame and insert into an existing frame list. The new frame will be inserted before or after
		the specified IMultiColumnTextFrame.

		@param parent - Existing frame which will be converted to multi-column frame.
		@param mcFrame - The multi-column frame in the existing frame list before or after which the converted frame will be inserted.
		@param insertAfter - kTrue if the converted frame will be inserted after mcFrame,
						kFalse if it will be inserted before mcFrame. Default is kTrue.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateConvertToMCFrameForFrameListCommand(UIDRef parent,
												IMultiColumnTextFrame * mcFrame,
												bool16 insertAfter = kTrue,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**	Creates the command to convert an existing frame to a multi-column text frame and insert into an existing frame list.

		The other 2 versions of ConvertToTextFrameForFrameList are recommended. This version is just for use in case if you want to insert the frame
		to the middle of the frame list and don't have the corresponding IMultiColumnTextFrame. But this case is rare.

		@param parent - Existing frame which will be converted to multi-column frame.
		@param frameList - The existing frame list into which the multi-column frame will be inserted.
		@param insertIndex - Index in the frame list where the multi-column frame will be inserted.
		@param frameItem - ID of the frame item. Default is kFrameItemBoss.

		@return ICommand - ICommand of kCreateMultiColumnItemCmdBoss created.
	 */
	virtual ICommand* CreateConvertToMCFrameForFrameListCommand(UIDRef parent,
												IFrameList* frameList,
												int32 insertIndex,
												ClassID frameItem = kFrameItemBoss) = 0;

	/**
	Strip various types of characters from some text.
	@param rText is the source text.
	@param pStripped will be the converted text. If nil, nothing occurs and we return rText.
	@return Returns the converted text (pStripped) unless nil, then return rText.
	*/
	virtual const WideString& ConvertTextModelText( const WideString &rText,
														WideString *pStripped,
														bool16 stripHardHyphens = kTrue,
														bool16 stripDiscretionaryHyphens = kTrue,
														bool16 convertApostrophes = kTrue,
														bool16 stripNobreakNonspace = kTrue,
														bool16 convertHyphens = kTrue,
														bool16 stripLeadingSpaces = kTrue,
														bool16 convertForGrammarCheck = kFalse) = 0;

	/**
	Collects UIDs of items with specified interface from the text focus. e.g. IID_IGRAPHICFRAMEDATA, IID_ITOPFRAMEDATA
	Can be a costly function with a text selection that spans many pages. See FocusSpansMultiplePageItems.
	*/
	virtual bool16 CollectPageItemsFromFocus(const ITextFocus *pFocus, const PMIID& iid, UIDList *pList ) = 0;

	/** Does the focus span more than one page item frames.
	*/
	virtual bool16 FocusSpansMultiplePageItems(const ITextFocus *pFocus) = 0;

	/** returns the index of a multicolumn frame in its thread by simply calling
	IMultiColumnTextFrame::GetMCFIndex();
	Note: This was broken in CS2 and was returning the index first
	TextFrameColumn within the FrameList. It was fixed in CS5.
	*/
	virtual int32 GetMultiColFrameIndex( const IMultiColumnTextFrame* mcf ) = 0;

	/**
	Find the word at a text location.
	@param pModel The text model in question.
	@param nPosition The text location in question.
	@param pLength OUT the length of the word.
	@param aFunction a function that determines what characters are considered word breaking.
	@return the beginning location of the surrounding word.
	@see IComposeScanner.
	@see ILanguage.
	*/
	virtual	TextIndex FindSurroundingWord( const ITextModel *pModel, TextIndex nPosition, int32 *pLength, FuncIsWordChar aFunction ) = 0;

	/**
	Find the word at a text location.
	@param pModel The text model in question.
	@param nPosition The text location in question.
	@param pLength OUT the length of the word.
	@param aFunction a function that determines what characters are considered word breaking.
	@return the beginning location of the surrounding word.
	@see IComposeScanner.
	@see ILanguage.
	*/
	virtual	TextIndex FindSurroundingWordUsingWordCharFuncOnly( const ITextModel *pModel, TextIndex nPosition, int32 *pLength, const FuncIsWordChar aFunction ) = 0;

	/** Is this style name considered plain? (For example, "Roman", "Regular", "")
	*/
	virtual	bool16 IsPlainStyleName( const PMString &styleName ) = 0;

	/** Is this style name considered italic?  (For example, "Italic", "Oblique")
	*/
	virtual	bool16 IsItalicStyleName( const PMString &styleName ) = 0;

	/** Is this style name considered bold?  (For example, "Bold", "Heavy", "Black")
	*/
	virtual	bool16 IsBoldStyleName( const PMString &styleName ) = 0;

	/** Is this style name considered bold and italic?
	*/
	virtual	bool16 IsBoldItalicStyleName( const PMString &styleName ) = 0;

	/**
	used by ApplyTextAttrToWorkspaceCmd, UserApplyAttrCmd, and TextState.
	*/
	virtual bool16 GetFontStyleName( ITextAttrFont *fromFont, ITextAttrFont *toFont, PMString *styleName ) = 0;

	/**
	Remap font styles tries to choose the expected family/style and allow roundtripping.
	@param AxesInfo - pass this returns back axes info for variable font filled if variable font
	@param numAxes - returns number of design axes in variable font

	***Client responsibility to clear the design axes after API use***

	example for reference
	if(numAxes && AxesInfo)
	{
		fontStyleAttr->SetMMAxes(numAxes,axesInfo);
		delete[] axesInfo;
	}

	*/
	virtual bool16 RemapFontStyles( IDataBase *dataBase, const AttributeBossList &stateOverrides, const AttributeBossList &newOverrides,
						PMString *styleName, Fixed* &axesInfo, int &numAxes, ClassID textAttrFontUIDBoss = kTextAttrFontUIDBoss, ClassID textAttrFontStyleBoss = kTextAttrFontStyleBoss,
						bool16 remapExactFontStylesOnly = kFalse) = 0;

	/**	Is this font an opentype font?
	*/
	virtual	bool16 IsOpenTypeFont( const IPMFont *font ) = 0;

	/**	Is this font family an opentype font family?
	*/
	virtual	bool16 IsOpenTypeFamily( IFontFamily *fontFamily ) = 0;

	/**	Does this font carry an Adobe copyright?
	*/
	virtual	bool16 IsAdobeFont (IPMFont const *font ) = 0;

	// Check the current char is a word break or not.
	virtual bool16 IsWordBreak(const UTF32TextChar& curChar) = 0;

	/** How should the names be displayed?
	*/
	enum DisplayNamesFlag
	{
		/**	If only one style for the font group familyName will have style name included.
			styleName will always be blank (Type->Font menu uses this)
		*/
		kCombineSingleStyleIntoFamilyName,

		/**	Used in style sheet description field
		*/
		kSeparateFamilyAndStyleName,

		/**	familyName is blank, only styleName filled out. Character palette Style Menu uses this.
		*/
		kStyleNameOnly,

		/**	styleName is blank, only Family filled out. Character palette Famiy Menu uses this.
		*/
		kFamilyNameOnly
	};

	/**	Gets the display font names for font
		@param *fontGroup	font group for font
		@param *font		font to get name from
		@param &familyName	OUT
		@param &styleName	OUT
		@param namesFlag	See enum DisplayNamesFlag.
	 */
	virtual void GetDisplayFontNames( IFontGroup *fontGroup, IPMFont *font, PMString &familyName, PMString &styleName, DisplayNamesFlag namesFlag ) = 0;


	/**	Gets the display font names for font
		@param *dataBase	database of family UID
		@param fontUID		family UID
		@param fontStyle	style of font
		@param &familyName	OUT
		@param &styleName	OUT
		@param namesFlag	See enum DisplayNamesFlag.
	 */
	virtual void GetDisplayFontNames( IDataBase *dataBase, const ITextAttrUID* fontUID, const ITextAttrFont* fontStyle,
								PMString &familyName, PMString &styleName, DisplayNamesFlag namesFlag ) = 0;

	/**
	Returns the list of owned items associated with a TextRange
	@param model	The TextModel
	@param start	The starting TextIndex of Text range to collect from.
	@param len		The length of the Text range to collect from.
	@param resultList
	@param nested 	If kFalse, only the OwnedItems in the specified Text range
					are returned. If kTrue, then all nested OwnedItems, that
					is OwnedItems that are contained in StoryRanges managed
					by found OwnedItems, are also returned.
					See CollectStoryRanges() for more information on nesting.
	*/
	virtual void CollectOwnedItems(const ITextModel* model,
									TextIndex start, int32 len,
									OwnedItemDataList* resultList,
									bool16 nested = kFalse) = 0;

	/**
	returns the list of owned items associated with a TextRange that have an IVisitorHelper interface.
	*/
	virtual void CollectVisitableItems(ITextModel* model,
							TextIndex start, int32 len,
							VisitableItems *resultList) = 0;

	/**
	returns the child for each Inline UID in the owned item strand
	*/
	virtual void GetUIDListOfInlines(IParcel* parcel, bool16 bWithDropCaps,
										UIDList* resultList) = 0;

	/**
	Returns the list of *logically* sequential story ranges that derive
	from the specified span of the text model. For a typical model span
	with no special content this will simply return a single StoryRange
	as (start, start + len).
	If a table, or other type of owned item which contains nested text is
	within the specified span then the specified span will be returned as
	two ranges with the appropriate nested text range(s) inserted between
	them.
	The hIndex and hIndexList are optional parameters which allows the
	caller to identify the starting TextIndex of the hierarchical element
	that "owns" the equivalent range in the resultList. Ranges from the main
	story thread (which starts at TextIndex 0) will have the hIndex of
	kInvalidTextIndex. Hierarchical elements that are found in the main
	story thread will have hIndex values within the main story thread and
	if those elements have sub elements then those will be in other story
	threads.
	@param bIncludeAnchorSpan is optional parameter which provides flexibility
		to client if they want to include anchor when calculating net span.
		For example, we don't want to include anchor span(such as table)
		when when do line count, e.g., for a 4x4 table, we want the line count
		as 16 instead of 17.
	*/
	virtual void CollectStoryRanges(const ITextModel* model,
										TextIndex start, int32 len,
										StoryRangeList* resultList,
										TextIndex hIndex = kInvalidTextIndex,
										ITextUtils::HIndexList *hIndexList = nil,
										bool16 bIncludeAnchorSpan = kTrue) = 0;

	/**
	Builds a list of text ranges for the specified story that are in
	logical order. The first range will begin at 'start' and the rest of
	the ranges will wrap around the end of the story to end at 'start - 1'.
	*/
	virtual void BuildLogicalStoryRangeList(ITextModel* model,
												TextIndex start,
												StoryRangeList* resultList) = 0;

	/**
	Return the PMMatrix to transform a point in WaxCoordinates in a
	Parcel to the owning Frame. Useful if you are an inline and you want
	to find out where you are relative to the Frame.
	*/
	virtual PMMatrix GetWaxToFrameMatrix(const IParcel* parcel) = 0;

	/**
	Get the Content Bounds of the Parcel at the specified TextIndex.
	If there is no Parcel at that TextIndex then it returns kFalse. Note
	that if the text at that location isn't fully composed then the Parcel
	you get may not be the same Parcel after composition.
	*/
	virtual bool16 GetParcelContentBounds(ITextParcelList* tpl,
											TextIndex at, PMRect *pCBounds) = 0;

	/** Is the text parcel list overset?
	@return returns kTrue if the specified ParcelList has any characters in addition
	to the final carriage return not mapped to a Parcel. If it's ONLY the
	final carriage return that is overset that it is NOT considered overset.
	*/
	virtual bool16 IsOverset(const IFrameList* fl) = 0;

	/** returns false if writingScript and text are contradicting.
	*/
	virtual	bool16 IsScriptOfText( const char *anyText, int32 writingScript ) = 0;

	/** returns the best guess for the text's writing script, preferredWritingScript is being used as a hint.
	*/
	virtual	int32 GuessScriptOfText( const char *anyText, int32 preferredWritingScript = kDontKnowScript ) = 0;

	/** returns whether the char needs to be skipped during remapping.
	Used by Text::RemapCharacterValue.
	*/
	virtual	bool16 SkipTextCharForRemapping( const UTF32TextChar& textChar ) = 0;

	/** returns whether the char needs to be skipped during remapping.
	Used by UserApplyAttrCmd, ScriptUserEditCmdResp, and CJKUserEditCmdResp.
	*/
	virtual	bool16 SkipTextCharForFontLocking( const UTF32TextChar& textChar ) = 0;

	/** returns the remapped textchar after converting to platform encoding using oldFont and back to newFont.
	*/
	virtual	UTF32TextChar RemapCharacterValue( IPMFont *oldFont, IPMFont *newFont, const UTF32TextChar& textChar ) = 0;

	/** Create a new story in the specified database.
	@param defaults specified whether the user's default attributes should be applied to the new story
	@param clsID specifies whether user specified story boss should be created
	*/
	virtual UID CreateNewStory(IDataBase *db, bool16 defaults = kTrue, ClassID clsID = kTextStoryBoss) = 0;

	/** Writing script to Language ID conversion.
	*/
	virtual LanguageID	ScriptToLanguageID( int32 writingScript ) = 0;

	/**
	Returns a command to force recomposition (use to avoid CmdBehaviorMonitor
	asserts if you need to force recomposition from within another command)
	*/
	virtual ICommand* CreateRecomposeThruNthParcelCmd( const ITextParcelList* tpl, int32 parcelIndex ) = 0 ;

	/**
	Returns a command to force recomposition (use to avoid CmdBehaviorMonitor
	asserts if you need to force recomposition from within another command)
	*/
	virtual ICommand* CreateRecomposeThruTextIndexCmd( const ITextParcelList* tpl, TextIndex textIndex ) = 0 ;

	/**
	Determines the pair kern at a particular text index.
	@param kernService refers to the ClassID of a boss that has the IPairKernDict interface to use.
	@return this method returns an ErrorCode (kSuccess, kFailure, kCancel)
	*/
	virtual int32 DeterminePairKern(const ITextModel* model, TextIndex index, ClassID kernService, PMReal& result) = 0;

	/**
	WhichTextAttrs do you want to look for?
	*/
	struct WhichTextAttrs
	{
		bool16	wantParaStyle;
		bool16	wantCharStyle;
		bool16	wantParaOverrides;
		bool16	wantCharOverrides;

		WhichTextAttrs()  :
			wantCharOverrides(kFalse), wantParaOverrides(kFalse),
			wantCharStyle(kFalse),	   wantParaStyle(kFalse)
		{}
	};

	/**
	A collection of text attributes?
	*/
	struct TextAttrs
	{
		UID									paraStyle;
		UID									charStyle;
		K2::scoped_ptr<AttributeBossList>	paraOverrides;
		K2::scoped_ptr<AttributeBossList>	charOverrides;

		TextAttrs() : charOverrides(nil), paraOverrides(nil),
					  charStyle(kInvalidUID), paraStyle(kInvalidUID) {}
	};

	/**
	Returns the requested attributes from the preferences of the document specified. prefsFromDocument should
	be non nil. For paragraph and character overrides only continuing attributes are returned.
	*/
	virtual void GetDefaultTextAttrPreferences(const WhichTextAttrs which, TextAttrs& out, IDocument* prefsFromDocument) = 0;

	/**
	2.0: Tables use one or more characters to "anchor" the table to the
	text flow. Inserting within these ranges is considered bad form and
	will lead to crashes. You may use this method to launder the ranges
	to encompass all of the table instead of just part.
	*/
	virtual void AdjustForTableRange(const UIDRef& story, TextIndex* pStart, TextIndex* pEnd, TextIndex* nextLine) = 0;

	/**
	Align text in the primary story thread in the specified text frame. This
	is NOT suitable for alignment in any other TextStoryThread.
	*/
	virtual bool16 AlignToBaselineGrid(IGeometry* pageItem, IParcel* parcel,
									const IBaselineGridPrefs *gridPrefs,
									PMReal *pYTop, PMReal *pYBottom,
									Text::GridAlignmentMetric alignment,
									PMReal alignmentMetricOffset) const = 0;

	/**
	Looks for findOldItemUI from "start" and replaces it with newItemUID in the item strand.
	This is typically used by commands that create owned items during import.
	In case the owned item is contained in a table and there is text after the end of the table (ie after
	the table in the tables containing text story thread) then the TextIndex stored in the command may not
	be valid. The returned TextIndex is the new location at which findOldItemUID was found in the item strand.
	*/
	virtual TextIndex FindResetOwnedItemUID(IItemStrand* itemStrand, const ClassID objectType, const UID findOldItemUID, const TextIndex start, const UID newItemUID) = 0;

	/**
	returns the position of first remapped textchar in buffer and copies the remapped textchars in  replacedChars after converting to platform encoding using oldFont and back to newFont.
	*/
	virtual	int32 RemapCharacterValues( IPMFont *oldFont, IPMFont *newFont, const textchar * buffer,  int32 bufferLength, WideString *replacedChars ) = 0;

	/** Counts number of Unicode characters in a UTF16TextChar buffer
	*/
	virtual int32 CountChars(const UTF16TextChar *buffer, int32 length) const = 0;

	/**
	Translates character (can be multiple UTF16s) offset into UTF16 offset in UTF16TextChar buffer
	*/
	virtual int32 CharOffsetToUTF16Offset(const UTF16TextChar *buffer, int32 length, int32 charOffset) const = 0;


	/**  GetSelectedTextItemsFromTextTarget gathers UIDs for the text frames that are currently selected.
		@param textTarget IN The current ITextTarget you want to gather selected text items from.
		@param textframes OUT The text frames that are currently selected.
		@param mcfs OUT The multi column frames that are currently selected.
		@param splineItems OUT The spline items that are currently selected.
	*/
	virtual void GetSelectedTextItemsFromTextTarget(const ITextTarget * textTarget, UIDList * textframes, UIDList * mcfs, UIDList * splineItems) = 0;

	/**  GetSelectedTextItemsFromLayoutTarget gathers UIDs for the text frames that are currently selected.
		@param layoutTarget IN The current ILayoutTarget you want to gather selected text items from.
		@param textframes OUT The text frames that are currently selected.
		@param mcfs OUT The multi column frames that are currently selected.
		@param splineItems OUT The spline items that are currently selected.
	*/
	virtual void GetSelectedTextItemsFromLayoutTarget(const ILayoutTarget * layoutTarget, UIDList * textframes, UIDList * mcfs, UIDList * splineItems) = 0;

	/**  GetSelectedTextItemsFromLayoutTarget gathers UIDs for the text frames that are currently selected.
		@param UIDList IN The pageitems to look through for text frames
		@param textframes OUT The text frames that are currently selected.
		@param mcfs OUT The multi column frames that are currently selected.
		@param splineItems OUT The spline items that are currently selected.
	*/
	virtual void GetSelectedTextItemsFromUIDList(const UIDList& pageITems, UIDList * textframes, UIDList * mcfs, UIDList * splineItems) = 0;

	/** GetTextFramesContaining returns the range of TextFrames that the
		Parcels containing the Text Range map to. The Range MUST be within
		a single StoryThread. pFirstFrameIndex will be -1 if the Text Range
		does not map to a Text Frame.
	*/
	virtual void	GetTextFramesContaining(const ITextModel *textModel,
											const RangeData& range,
											int32 *pFirstFrameIndex,
											int32 *pLastFrameIndex) = 0;

	virtual UIDList* CreateOppositeDirectionFrameList (UIDList *pStoryList,
					ITextOptions::WritingDirection dir) = 0;

	/** GetUIDListOfTextFrames returns a list of TextFrames that the Parcels
		containing the specified Text Range map to. The Range MAY cross
		StoryThread boundries.
	*/
	virtual void	GetUIDListOfTextFramesFromRange(const ITextModel* textModel, const RangeData& range, UIDList* resultList) = 0;

	/**
	Fills in inkResourceData with the known inks in the specified Range. It incorporates
	handling of the last CR in the Story Thread, so callers need not take care of removing
	it from the range.

	Notes:
		1. This routine only examines Text attributes from a canned list and is currently not extensible.
		2. The caller is responsible for making sure that the specified range is fully composed.
	*/
	virtual void	GetUsedInks(const ITextModel* textModel, TextIndex threadEnd,
								TextIndex start, int32 len, IInkResourceData* inkResourceData) = 0;

	/**
	Notifies the last Frame in the FrameList that its overset state may have
	changed. This call simply posts the appropriate inval rect for the location
	of the overset indicator and adds the Frame to the RecomposedFrames list.
	Note that the caller must ensure that at least one Frame in the FrameList
	is damaged or else the inval may never be played until the Frame becomes
	damaged and is recomposed.
	@param frameList
	*/
	virtual void	NotifyOversetChanged(const IFrameList* frameList) = 0;

	/** Return whether or not the given object is a MultiColumn TextFrame
	@param obj can be any object
	*/
	virtual bool16	IsMultiColumnFrame(const IPMUnknown* obj) const
		{
		InterfacePtr<const IMultiColumnTextFrame> mcf(obj, UseDefaultIID());
		return (mcf != nil);
		}

	/** Given an ITextFrameColumn, return the associated MultiColumn TextFrame.
	@param tfc Pointer to ITextFrameColumn
	*/
	virtual IMultiColumnTextFrame*	QueryMultiColumnFrame(ITextFrameColumn* tfc) const = 0;

	/** Const version of QueryMultiColumnFrame
	*/
	virtual const IMultiColumnTextFrame*	QueryMultiColumnFrame(const ITextFrameColumn* tfc) const = 0;

	/** UID version of QueryMultiColumnFrame
	*/
	virtual UID	QueryMultiColumnFrameUID(const ITextFrameColumn* tfc) const = 0;

	/** If the spline contains text, return the associated multi-column object.
	If spline doesn't contain text and if the spline has TOP, return the multi-column object associated with kTOPFrameItemBoss.
	return nil, for other conditions.
	*/
	virtual	IMultiColumnTextFrame*	QueryMCFOrTOPFromSpline(const IGraphicFrameData* gfd) const = 0;
	virtual	UID	GetMCFOrTOPFromSpline(const IGraphicFrameData* gfd) const = 0;
	virtual ITextModel* QueryTextModelFromSpline(const IGraphicFrameData* gfd) const = 0;

	/** Given an IMultiColumnTextFrames, return the spline associated with it
	@param mcf Pointer to IMultiColumnTextFrame
	@return Pointer to IHierarchy
	*/
	virtual IHierarchy* QuerySplineFromTextFrame(const IMultiColumnTextFrame* mcf) const = 0;

	/** Given an ITextFrameColumn, return the spline associated with the parent MultiColumnTextFrame.
	@param tfc Pointer to ITextFrameColumn
	@return Pointer to IHierarchy
	*/
	virtual IHierarchy* QuerySplineFromTextFrame(const ITextFrameColumn* tfc) const = 0;

	/**
	*/
	virtual ErrorCode ProcessScaleParcelContent(const ITextParcelList* tpl,
											ParcelKey key,
											const PMReal& xScale,
											const PMReal& yScale,
											IScaleObject::ScaleContext& context) const = 0;

	/**
		Returns the uid of the page which this text frame is one, can return kInvalidUID
		@param pageItem -- pageitem to find page UID of
		@return UID
	 */
	virtual UID GetTextFramesPageItemUID(IGeometry* pageItem) const = 0;

	/**
	   Do character, word, paragraph and line count

	   @param startIndex		--- start index for counting
	   @param lengthToCount		--- how far should count stop.
	   @param action			--- just update line or update all.
	   @param state				--- start or continue counting.
	   @param wordStarted		--- left over state(word is started or not) of last time.
	   @param characters		--- count of characters. (passed out parameter)
	   @param words				--- count of words. (passed out parameter)
	   @param paragraphs		--- count of paragraphs. (passed out parameter)
	   @param lines				--- count of lines. (passed out parameter)
	   @param oversetCharacters	--- count of characters in overset. (passed out parameter)
	   @param oversetWords		--- count of words in overset. (passed out parameter)
	   @param oversetParagraphs	--- count of paragraphs in overset. (passed out parameter)
	   @param oversetLines		--- (Deprecated, won`t return actual overset lines) count of lines in overset. (passed out parameter)
    */
	typedef enum { kUpdateAll = 0, kUpdateLine, kNoAction } WordCountUpdateAction;
	typedef enum { kStartCounting = 0, kCustomizeStartCounting, kContinueCounting, kContinueCountingForComposedFrame, kEndCounting } WordCountUpdateState;

	virtual void GetWordCountInfo
					(
						const ITextModel* iTextModel,
						const uint32& startIndex,
						const int32& lengthToCount,
						const ITextUtils::WordCountUpdateAction& action,
						const ITextUtils::WordCountUpdateState& state,
						bool16& wordStarted,
						uint32& characters,
						uint32& words,
						uint32& paragraphs,
						uint32& lines,
						uint32& oversetCharacters,
						uint32& oversetWords,
						uint32& oversetParagraphs,
						uint32& oversetLines,
						bool16& bWordAcrossOverset,
						TextStoryThreadHelper& helper
					) = 0;

	/**
	   Do roman character, all character, katakana, hiragana, kanji, paragraph and line count

	   @param startIndex			--- start index for counting
	   @param lengthToCount			--- how far should count stop.
	   @param action				--- just update line or update all.
	   @param state					--- start or continue counting.
	   @param wordStarted		    --- left over state(word is started or not) of last time.
	   @param fullWidthChars		--- count of full-width chars including full-width numbers, symbols and punctuations. (passed out parameter)
	   @param oversetFullWidthChars	--- count of full-width chars including full-width numbers, symbols and punctuations in overset. (passed out parameter)
	   @param halfWidthChars		--- count of half-width chars including half-width numbers, symbols and punctuations. (passed out parameter)
	   @param oversetHalfWidthChars	--- count of half-width chars including half-width numbers, symbols and punctuations in overset. (passed out parameter)
	   @param japaneseChars         --- count of japanese chars including full and half-width Hiragana and Katakana. (passed out parameter)
	   @param oversetJapaneseChars  --- count of japanese chars including full and half-width Hiragana and Katakana in overset. (passed out parameter)
	   @param kanjis				--- count of kanjis. (passed out parameter)
	   @param oversetKanjis			--- count of kanjis in overset. (passed out parameter)
	   @param words					--- count of words. (passed out parameter)
	   @param oversetWords		    --- count of words in overset. (passed out parameter)
	   @param lines					--- count of lines. (passed out parameter)
	   @param oversetLines			--- count of lines in overset. (passed out parameter)
	   @param paragraphs			--- count of paragraphs. (passed out parameter)
	   @param oversetParagraphs		--- count of paragraphs in overset. (passed out parameter)
	   @param allChars				--- count of all characters(passed out parameter)
	   @param oversetAllChars       --- count of all characters in overset. (passed out parameter)
    */
	virtual void GetWordCountInfo	// J version
					(
						const ITextModel* iTextModel,
						const uint32& startIndex,
						const int32& lengthToCount,
						const ITextUtils::WordCountUpdateAction& action,
						const ITextUtils::WordCountUpdateState& state,
						bool16&  wordStarted,
						uint32&  fullWidthChars, uint32& oversetFullWidthChars,
						uint32&  halfWidthChars, uint32& oversetHalfWidthChars,
						uint32&  japaneseChars,  uint32& oversetJapaneseChars,
						uint32&  kanjis,		 uint32& oversetKanjis,
						uint32&  words,          uint32& oversetWords,
						uint32&  lines,          uint32& oversetLines,
						uint32&  paragraphs,     uint32& oversetParagraphs,
						uint32&  allChars,       uint32& oversetAllChars,
						bool16&  bWordAcrossOverset	,
						TextStoryThreadHelper& helper
					) = 0;

	/**
		return the number of overset lines in a given text model
	 */
	virtual int32 CountOversetLines(const UIDRef &textModelUIDRef) = 0;

	/**
		returns whether the given ITextFocus is a footnote and optionally returns the UIDRef for that footnote
	   @param pFocus					--- The ITextFocus in question
	   @param pFootnoteUIDRef		---  If non-nil and there is a footnote at that model-position, the UIDRef of the footnote
		@return Whether the focus is a footnote.
	 */
	virtual bool16 IsFocusAFootnote(const ITextFocus *pFocus, UIDRef* pFootnoteUIDRef = nil) = 0;

	/**
		returns whether the position in the model is a footnote and optionally returns the UIDRef for that footnote
	   @param model					--- The model in question
	   @param position				--- The position in the given model
	   @param pFootnoteUIDRef		---  If non-nil and there is a footnote at that model-position, the UIDRef of the footnote
		@return Whether that model-position is a footnote.
	 */
	virtual bool16 IsFootnote(const ITextModel* model, TextIndex position, UIDRef* pFootnoteUIDRef = nil) = 0;

	/**
		returns whether the range in the model contains a footnote
	   @param model					--- The model in question
	   @param range					--- The range in the given model
		@return Whether that model-range contains a footnote.
	 */
	virtual bool16 AnyFootnotes(const ITextModel* model, const RangeData& range) = 0;

	/**
		Populates the two passed in attribute boss lists with all the character attributes and paragraph attributes,
		respectively, that can exist in a style and therefore the attributes that can be "cleared".
		@param workspace			--- Workspace to use as the basis for collecting all possible "style" attributes.
		@param characterAttributes	--- AttributeBossList to populate with the complete list of character attributes that can be cleared (in a style)
		@param paragraphAttributes	--- AttributeBossList to populate with the complete list of paragraph attributes that can be cleared (in a style)
	 */
	virtual void GenerateListsOfAttributesThatCanBeCleared(IWorkspace * workspace, AttributeBossList * characterAttributes, AttributeBossList * paragraphAttributes) = 0;

	/** Calculate the range in the main story thread that ultimately owns the given range.
		e.g. Works to backtrack from a footnote or note or inline to the owning text index.
		@param point1 [IN/OUT] storyRef, the story that ultimately "owns" the given range.
		@param point2 [IN/OUT] range, the "owning" range of the original given range.
	*/
	virtual void GetPrimaryStoryAnchor(UIDRef& storyRef, RangeData& range) const = 0;

	/** Filter illegal control characters from the string.
		@param data is the string to filter
		@param func is a function that returns kTrue if it is passed a character that should be stripped
		@return the filtered string or nil if no filtering was required
	*/
	typedef bool16 (*StripMatchingCharactersFunction)( const UTF32TextChar& n ) ;
	virtual	boost::shared_ptr<WideString> FilterInsertString( const WideString* data, StripMatchingCharactersFunction func ) const = 0 ;

	/** Calculate the range in the main story thread that owns the given range.
		within the same TextModel. Unlike GetPrimaryStoryAnchor() above, this
		method does NOT attempt to back out of inlines into a different story.
		@param model TextModel to work on
		@param range [IN/OUT] the "owning" range of the original given range.
	*/
	virtual void GetPrimaryThreadAnchor(const ITextModel* model, RangeData& range) const = 0;

	/** Link two text frames together as follows:
		If prepend is kFalse, then the textFrameA will be linked to textFrameB. Thus, existing text will flow from textFrameA to textFrameB.
		If prepend is kTrue, then the textFrameB will be linked to textFrameA. Thus, existing text will flow from textFrameB to textFrameA.
		In both cases,  textFrameB will inherit textFrameA's attributes (e.g. vertical or horizontal frame).
		@param textFrameA - see desc above.
		@param textFrameB - see desc above.
		@param prepend - see desc above.
	*/
	virtual ErrorCode LinkTextFrames(const IMultiColumnTextFrame* textFrameA, const IMultiColumnTextFrame *textFrameB,  bool16 prepend) = 0;

	/** Convert the textFrame to a member of IHierarchy (even if the textFrame is Text-on-a-Path)
	*/
	virtual IHierarchy* QueryForHierarchyMember(IDataBase *db, const ITextFrameColumn *textFrame) const = 0;

	/** Return the UIDRef for the page the given textFrame is on
	@param target  The textFrame or OwnedItem whose page number is desired.
	*/
	virtual UIDRef GetPageUIDRef(const UIDRef& textFrameRef) const = 0;

	/** Return the page number for the page the given textFrame is on
	*/
	virtual int32 GetPageNumber(const UIDRef& textFrameRef) const = 0;

	/** Return the number formatter for the page the given textFrame is on.  Formatter is also applicable for chapter numbers.
	*/
	virtual ClassID GetPageNumberFormatter(const UIDRef& textFrameRef) const = 0;

	/** Return the formatted string for the current, previous, or next page the given textFrame is on.
	*/
	virtual void GetFormattedPageNumberString(const UIDRef& textFrameRef, PMString* s, IDrawingStyle::PositionIndicator whichPage = IDrawingStyle::kDataPosition_ThisPage) const = 0;

	/** Return the formatted string for the section the given textFrame is on
	*/
	virtual void GetFormattedSectionNameString(const UIDRef& textFrameRef, PMString* s) const = 0;

	/** Return the chapter number
	@param target The relevant text frame or an owned item
	*/
	virtual int32 GetChapterNumber(IDataBase* db) const = 0;

	/** Return the chapter number as a string.
	@param target The relevant database
	@param s The returned formatted string
	@param v The optional value to format.  If v==kInvalidChapterNumber, the value is retrieved from GetChapterNumber.
	*/
	virtual void GetFormattedChapterNumberString(IDataBase* db, PMString* s, int32 v=kInvalidChapterNumber) const = 0;

	/** Enum defining the scope of the Page Count
	*/
	enum PageCountScopes { kSection = 0, kDocument };

	/** Return the page count based on the given scope
	@param target The relevant text frame or an owned item
	*/
	virtual int32 GetPageCount(const UIDRef& target, enum PageCountScopes scope) const = 0;

	/** Return the UIDRef for the page number previous to the one the given textFrame is on
	*/
	virtual UIDRef GetPreviousPageNumberFrameRef(const UIDRef& textFrameRef) const = 0;

	/** Return the UIDRef for the page number after to the one the given textFrame is on
	*/
	virtual UIDRef GetNextPageNumberFrameRef(const UIDRef& textFrameRef) const = 0;

	/** Return whether or not the container for the given target is continued from elsewhere (e.g. a table is continued from the previous frame)
	*/
	virtual bool16 GetTargetIsInContinuedContainer(const UIDRef& target) const = 0;

	/** Return whether or not the container for the given target continues elsewhere (e.g. a table continues to another frame)
	*/
	virtual bool16 GetTargetContainerContinues(const UIDRef& target) const = 0;

	/**
	*/
	virtual TextIndex GetTextIndexForTrackedParagraph(const UIDRef& paraStrandDiskPageRef,
												UID trackerUID,
												uint32 trackerData) const = 0;

	/** Return the ICU Locale for the given target and position.
		If the target is a TextModel, then if the position is valid, it will return the LanguageID applied to that location.
		Otherwise, if target refers to a valid document, the default languageID for the document is returned.
		Otherwise, kLanguageNeutral is returned.
	@param target Preferably a document or a TextModel, but can be an empty UIDRef or any reference to the desired document.
	@param position The position in the model.  Optional.
	@return The ID of the language applied to the given location.
	*/
	virtual void GetLocaleFromTextIndex(const UIDRef& modelRef, const TextIndex position, bool16 &noLang, void *locale) const = 0;

	/** Return the last document in the current active book and whether it was already opened or not.
	*/
	virtual IDocument* GetLastDocInBook(bool16& docWasAlreadyOpen, int32& startPageNum) const = 0;

	/** Description: Fills in list of ITextFrameColumns known to the spread by
	calling the ISpreadMultiColumnFrames interface on the specified Spread.
	@param spreadRef UIDRef to spread to return TFCs from
	@param pList UIDList to fill
	@return Length of pList
	*/
	virtual int32 GetSpreadTextFrameColumns(const UIDRef& spreadRef,
												UIDList* pList) const = 0;

	/** Description: Fills in list of IMultiColumnTextFrames known to the
	spread. by calling the ISpreadMultiColumnFrames interface on the specified
	Spread.
	@param spreadRef UIDRef to spread to return MCFs from
	@param pList UIDList to fill
	@return Length of pList
	*/
	virtual int32 GetSpreadMultiColumnTextFrames(const UIDRef& spreadRef,
												UIDList* pList) const = 0;

	/** Description: Edit the given target style with the given style attributes.
	@param targetDB [IN] target database
	@param targetStyle [IN] target style
	@param attributesToApply [IN] the attributes in the target database to apply
	@param uidList [IN] itemList to apply
	*/
	virtual void EditTargetStyle(IDataBase* targetDB, const UID& targetStyle, AttributeBossList* attributesToApply, const UIDList& uidList) const = 0;

	/** Description: Convert the attributes from the source database to target database first and
	then apply the converted attributes to target style.
	@param sourceDB [IN] source database
	@param sourceStyle [IN] source style
	@param targetDB [IN] target database
	@param targetStyle [IN] target style
	@param uidList [IN] itemList to apply
	*/
	virtual void ApplySourceStyleAttrsToTargetStyle(IDataBase* sourceDB, const UID& sourceStyle, IDataBase* targetDB, const UID& targetStyle,
												    const UIDList& uidList) const = 0;

	/** Checks if the specified text is valid for insertion in the text model.
		Some control characters are not accepted by the text model.
		@see TextChar::IsIllegalControlChar().
		@param text [IN] text to be checked for validity.
		@return kTrue if the text is valid.
	*/
	virtual bool16 IsTextValidForInsertion(WideString const& text) const = 0;

	/** Fix up TOC/Index/Third party links when placing a story.
		@param oldStoryRef [IN] The destination of the fixing operation. The story being fixed.
		@param newStoryRef [IN] The source of the fixing operation.
	*/
	virtual void RepairGenericDataLink(UIDRef oldStoryRef, UIDRef newStoryRef) = 0;

	/**
	Returns a pointer to a WideString with the name of the
	XRefPageNumberVariable.
	@return WideString
	*/
	virtual const WideString& GetXRefPageNumberVariableName() = 0;
	
	/**
	Returns a pointer to a WideString with the name of the
	XRefChapterNumberVariable.
	@return WideString
	*/
	virtual const WideString& GetXRefChapterNumberVariableName() = 0;
	
	/** Return the text of a paragraph including any paragraph numbers at the beginning. Any non-visible characters are also stripped out.
	@param scanner Compose Scanner for the story with the paragraph.
	@param textIndex position in the paragraph.
	@param paragraphSpan [OUT]. Length of the paragraph according to the scanner. This will NOT be the length of the returned string.
	@return the paragrah string with non-visible characters stripped out and any numbers prepended if there are any.
	*/
	virtual WideString GetFullVisibleParagraphString(IComposeScanner * scanner, TextIndex textIndex, int32 &paragraphSpan) = 0;

		
	/** Returns whether or not the run at the text index within the specified line is left to right direction.
	@param waxLine the line to examine.
	@param textIndex position in the line.
	@return kTrue if the run direction is left to right, otherwise kFalse.
	*/
	virtual bool16 IsLeftToRightRun(const IWaxLine* waxLine, TextIndex ti) const = 0;

	/** Returns the Ref of first frame of the story
	@param story whose first frame we need to find.
	@return ref of spline of first MCF, otherwise kInvalidUIDRef if not able to find one
	*/
	virtual UIDRef GetFirstFrameOfStory(const UIDRef & story) const = 0;

	/** Map quotes to smart quotes
	@param story to convert quotes
	@param position where to start converting quotes
	@param length to convert quotes
	*/
	virtual void ConvertSmartQuotes(ITextModel* model, TextIndex position, int32 length) const = 0;


	/** Creates Glyphs for a given text range in text model with attributes to be overriden. Does not modify composed text frame.
	    Appends overrides to current style and finds the glyphs.

	@param model on which the whole action isto be taken. Current styles will be picked from this.
	@param range of model on which the overrides need to be applied.
	@param overrides list of attributes,that need to be applied on range.
	@param newGlyphPoints(out) list of Pair (glyphs and corresponding text index) that would be used with override. Does not allocate memory. Please pass reference to valid object.
	@param clearOverrides  set to true if overrides need to be cleared and not applied.
	*/
	virtual void GetGlyphsForOverrides(ITextModel* model, const RangeData& range, const AttributeBossList *overrides, 
		std::vector<std::pair<Text::GlyphID, TextIndex>> *newGlyphPoints, bool16 clearOverrides=kFalse) const = 0;

	/** Return the page number for the page with given page uid
	*/
	virtual int32 GetPageNumberFromPageUID(const UIDRef& page) const = 0;

	/** Compare two items in the same text model by their text index to determine if an item appears visually before or after the other item. 
	@param txtModel The text model for both the items to be compared
	@param item1Position Text index of the first item 
	@param item2Position Text index of the second item
	@return kIsBefore if item1 appears before item2, kIsEqual if both indexes are equal, kIsAfter if item1 appears after item2 
	*/
	virtual ITextStoryThreadDictHier::CompareResult CompareItemPosition(const ITextModel* txtModel, const TextIndex item1Position, const TextIndex item2Position) const = 0;

	/** Return kTrue if vertical column rule is active on given shape
	@param shape The shape of mcf
	@return bool16 Is vertical column rule active on shape.
	*/
	virtual bool16 IsVerticalColumnRuleActive(const IPMUnknown* shape) = 0;
};

// This is the new direction
namespace Text {

	typedef ITextUtils::VisitableItems	VisitableItems;
	typedef ITextUtils::HIndexList		HIndexList;
}


#endif	// __ITextUtils__
