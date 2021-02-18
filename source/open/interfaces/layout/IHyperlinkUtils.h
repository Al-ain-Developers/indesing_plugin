//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/layout/IHyperlinkUtils.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IHyperlinkUtils__
#define __IHyperlinkUtils__

#include "Utils.h"
#include "HyperlinkID.h"

#include "itextRangeNode.h"
#include "IHyperlinkAppearanceData.h"
#include "IPDFHyperlinks.h"
#include "IXRefFormat.h"
#include "IHyperlinkTextDestinationData.h"
#include "IWorkspace.h"

#include "XRefBuildingBlock.h"
#include "UIDList.h"

class	IDataBase;
class	IHyperlink;
class	IHyperlinkSource;
class	IHyperlinkTextDestinationData;
class	ITextModel;
class	WideString;
class	RangeData;

/**
	Types of changes for changesFlag in QueryChangeHyperlinkCommand method
*/
enum
{
	kHLChangeOutlineStyle = 0x01,
	kHLChangeHilight  = 0x02,
	kHLChangeBorderColor = 0x04,
	kHLChangeBorderWidth = 0x08,
	kHLChangeVisibility = 0x10,
	kHLChangeName = 0x20,
	kHLChangeSource = 0x40,
	kHLChangeDestination = 0x80
};

class IHyperlinkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKUTILS };


	/** Enum of the hyperlink range which we are interested in */
	enum ContainedHyperlinkType
	{
		ContainedHyperlink_All = 0,
		ContainedHyperlink_FullRangeOnly,
		ContainedHyperlink_PartialRangeOnly,
	};
	
	/**	Given a range of text determine which hyperlink sources are partially or fully contained
		in that range. 
		The hyperlink source is considered as fully or partially contains iff meeting both conditions:
		(1) hyperlink source intersects the range
		(2) hyperlink source is not fully containing the range like:
		<xRRRx>, <xRRR>, <RRRx>
		where R represents the specified range,  <> represents the hyperlink range and x represents other characters. 
		Ranges like <RRR> is considered 	as fully contained and so included in the returned collection.
		
		@param *model - The text model to look at
		@param start - The start of the range
		@param end - The end of the range
		@param rangeType - The type of range which we care about. Default is to get both partially and fully contained ranges.
		@return RangeRefList - A list of the hyperlink sources that are contained by this range
	 */
	virtual RangeRefList		GetRangeContainedHyperlinks(ITextModel *model, TextIndex start, TextIndex end, ContainedHyperlinkType rangeType = ContainedHyperlink_All) = 0;

	/**	Given a range of text determine which hyperlink source wholly contains the range. 
		Following hyperlink is considered wholly containing the range:
		<xRRRx>, <xRRR>, <RRRx>, <RRR>
		where R represents the specified range, <> represents the hyperlink range and x represents other characters.
		
		@param *model - The text model to look at
		@param start - The start of the range
		@param end - The end of the range
		@return TextRangeReference - The source that contains the range (kInvalidTextRange if no hyperlink contains the range)
	 */
	virtual TextRangeReference		IsRangeContainedByAHyperlink(ITextModel *model, TextIndex start, TextIndex end) = 0;

	/**	Given a range of text compute a new range that wholly contains any hyperlink sources touched by start and end
		If no hyperlink source are between start and end, returns same range defined by start and end.
		@param *model - The text model to look at
		@param start - The start of the range
		@param end - The end of the range
		@return RangeData - The text range that wholly contains any hyperlink sources touched by start and end
	 */
	virtual RangeData	ExpandRangeToContainHyperlinks(ITextModel *model, TextIndex start, TextIndex end) = 0;

	/** Check if a range of text contains partial XML tag. If resolve flag is kTrue, try to move the start/end index to resolve the partial intersection.
		@param model - The text model of interest
		@param start - [IN/OUT] Pass in the start of the range to be checked. If resolve flag is kTrue, this is the start index of the new range on return.
		@param end - [IN/OUT] Pass in the end of the range to be checked. If resolve flag is kTrue, this is the end index of the new range on return.
		@param resolve - kTrue to fix the range, kFlase to just check.
		@return bool16 - kTrue if there is partial XML tag in the range. kFalse otherwise.
	*/
	virtual bool16	PartialXMLTagInRange(ITextModel *model, TextIndex& start, TextIndex& end, bool16 resolve) = 0;

	/**	Given a range of text delete all the hyprelink sources and text destination markers in the range.
		@param *model - The text model to check
		@param start - The start of the range
		@param end - The end of the range
	 */
	virtual void		DeleteHyperlinkSrcsAndDestsInStory(ITextModel* model, TextIndex start, TextIndex end) = 0;

	/** Clean up unused hidden destinations in the specified database.
		@param db - database for hidden destinations to be cleaned
		@param suppressWarnings - do not show any warnings, default true
	*/
	virtual void 		CleanupHiddenDestinations(IDataBase* db, bool16 suppressWarnings = kTrue) = 0;
	
	/**	Apply the character style to the a given text range
		@param *textModel - The text model to work on
		@param startIndex - Where to begin applying
		@param lastIndex - Length of the range to apply
		@param charStyle - The associated UID of the character style to apply
		@return  
	 */
	virtual void 		ApplyCharacterStyleToTextSource(ITextModel *textModel, 
													TextIndex startIndex, 
													int32 length, 
													UID charStyle) = 0;

	/** Replace the specified range with new cross reference source content.
		@param *textModel - The text model to work on
		@param startIndex - Where to begin replacing
		@param lastIndex - Length of the range to be replaced
		@param data - new content to be inserted
	*/
	virtual ErrorCode 	ReplaceXRefSourceContent(ITextModel *textModel, 
													TextIndex startIndex, 
													int32 length, 
													const boost::shared_ptr<WideString>& data) = 0;
	
	/**	Checks the text range if the character styles applied in the range match specified character style list
		@param *textModel - The text model of the range
		@param startIndex - Where to begin check
		@param lastIndex - Length of the range to check
		@param charStyles - character style range list to check against
		@return  bool16 - kTrue if the character styles in the range match specified list
	 */
	virtual bool16 		CharStylesInRangeMatch(const ITextModel *textModel, TextIndex startIndex, int32 length, 
												const K2Vector<CharStyleRange>& charStyles) = 0;
	
	/**	This method will take a string that contains unicode characters and strip
		things out that don't make sense for dialogs. (This includes things like
		tabs, page number markers, etc.)
		@param iTextModel - The text model to get the text from
		@param textStart - The starting point to get the text from
		@param paraLen - The length of the text that you want
		@param hyperlinkString - The finalized string (without extra characters)
		@return  
	 */
	virtual void		FormatStringForUI(ITextModel *iTextModel, 
						   TextIndex	textStart, 
						   int32		paraLen, 
						   WideString& hyperlinkString) = 0;

	/** Enum presentation options if a document is opened */
	enum OpenWindowType
	{
		OpenWindow_NoWindow = 0,
		OpenWindow_FrontWindow,
		OpenWindow_BehindFrontWindow,
	};
	
	/** Gets the database of the specified file.
		@param targetSysFile The system file to get the database for.
		@param openIfClosed - [IN/OUT] Passing in kTrue will open the file if it is not already open. 
						kFalse will be returned if we don't need to open it, otherwise return kTrue.
						If null is passed in, then we do not open if the file is closed.
		@param openWindow - Specifies whether to open a window in the UI.
		@returns IDataBase* the database of the specified file.
	*/
	virtual IDataBase* FindDataBaseOfSysFile(const IDFile& targetSysFile, bool16 *openIfClosed = nil, OpenWindowType openWindow = OpenWindow_NoWindow) const = 0;
	
	/**	Given an interface on a boss with an IDataLink interface this method will find 
		the database that the datalink points to. (This method uses exact paths)
		@param *link - This is any interface on the appropriate boss
		@param openIfClosed - [IN/OUT] Passing in kTrue will open the file if it is not already open. 
						kFalse will be returned if we don't need to open it, otherwise return kTrue.
						If null is passed in, then we do not open if the file is closed.
		@param openWindow - Specifies whether to open a window in the UI.
		@param examineDest - kTrue to check destination for link resource as well if the passed in link is on a hyperlink 
							object and it does not have link resource,  kFalse otherwise. You should most likely pass
							kFalse unless you are passing in IHyperlink* as link and the destination maybe external
							page destination.
		@return *IDataBase - The database that this method found
	 */
	virtual IDataBase	*FindDataBaseOfHyperlinkDest(const IPMUnknown *link, bool16* openIfClosed = nil, 
					OpenWindowType openWindow = OpenWindow_NoWindow, bool16 examineDest = kFalse) = 0;

	/** Retrieves the document change count property in the XMP data for the closed file.
		@param file - the file whose XMP data we are interested in.
	*/
	virtual uint32 		GetClosedDocChangeCount(const IDFile& file) = 0;

	/** Retrieves the document change count property in the XMP data for the opened document.
		@param db - the database whose XMP data we are interested in.
	*/
	virtual uint32 		GetOpenDocChangeCount(IDataBase* db) = 0;
	
	/** Save the document change count to XMP.
		@param db - The database to save change count.
		@param ErrorCode
	*/
	virtual ErrorCode SaveDocChangeCount(IDataBase* db) = 0;

	/** Increment the document change count of the specified database.
		@param db - The database to increment change count.
		@param ErrorCode
	*/
	virtual ErrorCode IncrementDocChangeCount(IDataBase* db) = 0;
	
	virtual void		SetupOwnedItemInfo(UIDRef textModelRef, TextIndex textIndex, UIDRef textMarker, UID ownedItemUID) = 0;

	/** Loads default cross reference formats in database.
	*/
	virtual void		LoadDefaultXRefFormats(IDataBase* db) = 0;

	/** Given a text range, filters out special characters which a cross reference source should not include and return the rest of the string
		@param iTextModel - Text model of the text range to generate cross reference source string from
		@param startIndex - Start index of the range
		@param length - Length of the range
		@param sourceString - [OUT]Returned string excluding special characters
		@param variableLoation - [OUT]List of text variables and their offset index in the source content
		@param inlineLoations - [OUT]List of inline objects with their offset index in the source content and their index in the destination story.
		@param externDest - kTrue if the destination is in external document, kFalse otherwise
		@param delim - specify the delimiter character if there is one
		@param includeDelim - specify if the result should include the delimiter character
		@param generateName - kTrue if the range passed in is cross reference source and we are generating the string for corss reference
								display name. kFalse for generating source content from destination range.
	*/
	virtual void 		FilterXRefSource(const ITextModel* iTextModel, TextIndex startIndex, int32 length, 
					PMString& sourceString, std::map<TextIndex, WideString>* variableLocations, 
					std::map<TextIndex, TextIndex>* inlineLocations,
					bool16 externDest, const UTF32TextChar* delim = nil, bool16 includeDelim = kFalse, 
					bool16 generateName = kFalse) = 0;

	/** Compare the source content in the specified range to the given new content.
		@param iTextModel - Text model of the text range to get cross reference source string from
		@param startIndex - Start index of the range
		@param length - Length of the range
		@param newContent - new source content to compare to
		@param variableLocations - variables and their offset in the new source content
		@return bool16 - kTrue if the sources match, kFlase if not.
	*/
	virtual bool16 		XRefSourceContentsMatch(const ITextModel* iTextModel, TextIndex startIndex, int32 length, 
					const boost::shared_ptr<WideString>& newContent, const std::map<TextIndex, WideString>& variableLocations) = 0;
		
	/**	Checks to see if the given hyperlink is a Cross-Reference or not.
		@param hyperlink - UID of hyperlink to check
		@return bool16 - kTrue if the hyperlink is a cross-reference.
	 */
	virtual bool16 IsXRef(UIDRef hyperlink) = 0;

	/**	Checks the status of cross-references in the specified database.
		@param db - database to check
		@param checkStatus - kTrue to check the status of all the cross references after the status is updated, 
							kFalse only update the status without checking
		@return bool16 - When checkStatus is kTrue, return kFalse if any cross reference has invalid destination 
						or is out of date. kTrue otherwise. If checkStatus is kFalse, we always return kTrue.
	 */
	virtual bool16 AllXRefsOk(IDataBase* db, bool16 checkStatus = kTrue) = 0;

	/**	Obtains a list of all the xref sources in a given range of text.
		@param textModel - story of the range to check
		@param startIndex - start index of the range to check
		@param length - length of range to check
		@param xrefs - [OUT] contains cross-references in the range
		@return bool16 - Return kTrue if cross reference found in the range. Otherwise return kFalse.
	 */
	virtual bool16 GetXRefsInTextRange(const ITextModel* textModel, TextIndex startIndex, int32 length, UIDList& xrefs) = 0;

#pragma mark hyperlinkCmds

	/**	Creates a new hyperlink command.
	
		@param hyperlinkSource - Hyperlink source object associated with the new hyperlink.
		@param hyperlinkDestination - Hyperlink destination object associated with the new hyperlink.
		@param hyperlinkName - name of the hyperlink. Default to be empty string in which case a unique name will be generated.
		@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. Default is kTrue.
		@param defaultAppearance - kTrue to use default appearance for the hyperlink. kFalse otherwise. Default is kTrue. 
								In case of kTrue, we ignore the following appearance parameters.  
		@param visibleRectangle - kTrue if the new hyprelink has visible rectangle border. kFalse otherwise. Default is kFalse.
		@param borderLineWidth - hyperlink border line width. Default is 1.
		@param hilight - hyperlink hilight setting. Default is no hilight.
		@param outlineStyle - hyperlink outline style. Default is solid outline.
		@param altText - hyperlink alt text. Default is empty.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewHyperlinkCommand
		(
			UIDRef hyperlinkSource,
			UIDRef hyperlinkDestination,
			const PMString& hyperlinkName = "",
			bool16 visible = kTrue,
			bool16 defaultAppearance = kTrue,
			bool16 visibleRectangle = kFalse,
			int32 borderLineWidth = 1,
			UID borderColor = kInvalidUID,
			IHyperlinkAppearanceData::HyperlinkHilight hilight = IHyperlinkAppearanceData::kNoHyperlinkHilight,
			IHyperlinkAppearanceData::HyperlinkOutlineLineStyle outlineStyle = IHyperlinkAppearanceData::kHyperlinkSolidOutline,
			const PMString& altText=""
		) = 0;

	/**	Creates a delete hyperlink command.
	
		@param hyperlinks - hyperlinks to be deleted. 

		@return ICommand - new command.
	 */
	virtual ICommand* QueryDeleteHyperlinkCommand
		(
			UIDList hyperlinks
		) = 0;

	/**	Creates a change hyperlink command to rename the hyperlink.
	
		@param hyperlink - hyperlink to be changed. 
		@param newName - new hyperlink name.
		
		@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeHyperlinkCommand
		(
			UIDRef hyperlink,
			const PMString& newName
		) = 0;

	/**	Creates a change hyperlink command to change the source or destination of the hyperlink.
	
		@param hyperlink - hyperlink to be changed. 
		@param changeSource - kTrue if to change the source, kFalse if to change the destination.
		@param sourceOrDestRef - UIDRef of the new source or destination depending on the above flag.
		
		@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeHyperlinkCommand
		(
			UIDRef hyperlink,
			bool16 changeSource,
			UIDRef sourceOrDestRef
		) = 0;

	/**	Creates a change hyperlink command to change hyperlink appearance.
	
		@param hyperlink - hyperlink to be changed. 
		@param changesFlag - Lower 5 bits (0x1F) indicate which appearance(s) to be changed. Default is 0x1F which is to change all appearances.
							For detailed settings, see changesFlag on IHyperlinkFacade::ChangeHyperlink method.
		@param defaultAppearance - kTrue to use default appearance for the hyperlink. kFalse otherwise. Default is kTrue. 
								In case of kTrue, we ignore the following appearance parameters.  
		@param visible - kTrue if the new hyprelink has visible rectangle border. kFalse otherwise. Default is kFalse.
		@param borderLineWidth - hyperlink border line width. Default is 1.
		@param hilight - hyperlink hilight setting. Default is no hilight.
		@param outlineStyle - hyperlink outline style. Default is solid outline.
		
		@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeHyperlinkCommand
		(
			UIDRef hyperlink,
			int16 changesFlag = 0x1F,
			bool16 defaultAppearance = kTrue,
			bool16 visible = kFalse,
			int32 borderLineWidth = 1,
			UID borderColor = kInvalidUID,
			IHyperlinkAppearanceData::HyperlinkHilight hilight = IHyperlinkAppearanceData::kNoHyperlinkHilight,
			IHyperlinkAppearanceData::HyperlinkOutlineLineStyle outlineStyle = IHyperlinkAppearanceData::kHyperlinkSolidOutline
		) = 0;

	/**	Creates a delete hyperlink source command.
	
		@param sources - Hyperlink sources to be deleted. 

		@return ICommand - new command.
	 */
	virtual ICommand* QueryDeleteHyperlinkSourceCommand
		(
			UIDList sources
		) = 0;
	
	/**	Creates a new hyperlink text source command.
	
		@param story - story UIDRef to create the new source in.
		@param startIndex - Text index of the start of the new source.
		@param length - length of the selection to create the text source. Default is 0 which is an insertion point.
		@param hyperlinkName - Name of the new source. Default is empty string in which case a unique name will be generated.  
		@param isXRef - kTrue if the new source is a cross reference source. kFalse otherwise. Default is kFalse.
		@param xrefFormat - UID of the format for cross reference source.
		@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. Default is kTrue.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewHyperlinkTextSourceCmd
		(
			UIDRef story,
			TextIndex startIndex,
			int32 length = 0,
			const PMString& hyperlinkName = "",
			UID charStyle = kInvalidUID,
			bool16 isXRef = kFalse,
			UID xrefFormat = kInvalidUID,
			bool16 visible = kTrue
		) = 0;

	/**	Creates a new hyperlink page item source command.
	
		@param pageItem - page item to create source from.
		@param name - Name of the new source. Default is empty string in which case a unique name will be generated.  
		@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. Default is kTrue.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewHyperlinkPageItemSourceCmd
		(
			UIDRef pageItem,
			const PMString& name = "",
			bool16 visible = kTrue
		) = 0;


	/**	Creates a delete hyperlink destination command.
	
		@param destinations - Destinations to be deleted. 

		@return ICommand - new command.
	 */
	virtual ICommand* QueryDeleteHyperlinkDestinationCmd
		(
			UIDList destinations
		) = 0;

	/**	Creates a update hyperlink destination info command.
	
		@param hyperlinks - Hyperlinks to be updated. If the list is empty, all the hyperlinks in the document will be updated.
		@param openClosedDoc - kTrue to open closed documents to get destination info. kFlase otherwise.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryUpdateHyperlinkDestInfoCmd
		(
			UIDList hyperlinks,
			bool16 openClosedDoc = kTrue
		) = 0;
	
	/**	Creates a new hyperlink text destination command.
	
		@param story - Story to create destination in.
		@param position - Insertion point of the text destination marker.
		@param name - name of the destination. Default to be empty string which will generate a unique name.  
		@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
		@param useExistingAnchor - kTrue to use existing text anchor if one already exists at the insertion point. 
								kFalse to always insert a new one. Default to kFalse.
		@param isParagraph - kTrue if the new destination is a paragraph destination. kFlase otherwise. Default is kFalse.
		@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
							be generated.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewHyperlinkTextDestCmd
		(
			UIDRef story,
			TextIndex position,
			const PMString& name = "",
			bool16 visible = kTrue,
			bool16 useExistingAnchor = kFalse,
			bool16 isParagraph = kFalse,
			int32 uniqueKey = 0
		) = 0;
	
	/** Creates a change hyperlink text destination command.
	
		@param destination - Hyperlink text destination to be changed. 
		@param story - New story to insert destination in. Default to kInvalidUIDRef which story is not changed.
		@param position - Insertion point of the text destination marker. Default to -1 which anchor position is not changed.
		@param name - name of the destination. Default to be empty string which name is not changed.  
								
		@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeHyperlinkTextDestCmd
		(
			UIDRef destination,
			UIDRef story = kInvalidUIDRef,
			TextIndex position = -1,
			const PMString& name = ""
		) = 0;
	
	/**	Creates a new hyperlink page destination command.
	
		@param page - Page to create destination for.
		@param name - name of the destination. Default to be empty string which will generate a unique name.  
		@param allowUserSpecifiedName - kTrue if the allow user specified name. kFalse to generate name based on page number. Default is kTrue.
		@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
		@param zoomFact - Zoom fact for exporting to PDF. Default to 1.0.
	 	@param pdfFitType - Fit type for exporting to PDF. Default to type DestXYZ which destination specified as upper-left corner point and a zoom factor.
		@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle which has no area.
		@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
							be generated.
							
		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewHyperlinkPageDestCmd
		(
			UIDRef page,
			bool16 allowUserSpecifiedName = kTrue,
			const PMString& name = "",
			bool16 visible = kTrue,
			PMReal zoomFact = 1.0,
			IPDFHyperlinks::DestinationType pdfFitType = IPDFHyperlinks::DestXYZ,
			PMRect zoomRectangle = kEmptyRect,
			int32 uniqueKey = 0
		) = 0;
	
	/**	Creates a change hyperlink page destination command.
	
		@param page - New page to create destination for.
		@param allowUserSpecifiedName - kTrue if the allow user specified name. kFalse to generate name based on page number. Default is kTrue.
		@param name - name of the destination. Default to be empty string in which case not changing the name.  
		@param zoomFact - Zoom factor for exporting to PDF. Default to -1 in which case not changing the zoom factor.
	 	@param pdfFitType - Fit type for exporting to PDF. Default to -1 which is not changing the fit type. 
	 					Otherwise the value will be one of the type in IPDFHyperlinks::DestinationType. 
		@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle in which case not changing the zoom rectangle.
							
		@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeHyperlinkPageDestCmd
		(
			UIDRef destination,
			UIDRef page = kInvalidUIDRef,
			const PMString& name = "",
			PMReal zoomFact = -1,
			int32 pdfFitType = -1,
			PMRect zoomRectangle = kEmptyRect,
			bool16 allowUserSpecifiedName = kTrue
		) = 0;

	/**	Creates a new hyperlink URL destination command.
	
		@param db - database of the document where the new destination will be added.
		@param urlString - URL string for the destination.
		@param name - name of the destination. Default is empty string in which case a unique name will be generated.
		@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
		@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
							be generated.
							
	@return ICommand - new command.
	 */
	virtual ICommand* QueryNewHyperlinkURLDestinationCmd
		(
			IDataBase* db,
			const PMString& urlString,
			const PMString& name = "",
			bool16 visible = kTrue,
			int32 uniqueKey = 0
		) = 0;

	/**	Creates a change hyperlink URL destination command.
	
		@param destination - Hyperlink URL destination to be changed. 
		@param urlString - New URL string for the destination. Empty string if not changing the url.
		@param name - name of the destination. Default is empty string in which case not changing the name.
							
	@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeHyperlinkURLDestinationCmd
		(
			UIDRef destination,
			const PMString& urlString,
			const PMString& name = ""
		) = 0;

	/**	Creates a new xref format command.
	
		@param db - database of the document where the new format will be added.
		@param buildingBlocks - List of building blocks for the format.
		@param name - name of the format. Default to empty string in which case a unqiue name will be generated.
		@param charStyle - character style of the format.
		
		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewXRefFormatCommand
		(
			IDataBase* db,
			const K2Vector<XRefBuildingBlock>* buildingBlocks = nil,
			const PMString& name = "",
			UID charStyle = kInvalidUID
		) = 0;
	
	/**	Creates a new bookmark command.
	
		@param destination - destination associated with the new bookmark.
		@param parentBookmark - Parent of the bookmark. Deafult to be kInvalidUID which is no parent.
		@param bookmarkName - name of the bookmark. Default to be empty string in which case a unique name will be generated.
		@param indentLevel - Indent level of the bookmark. Default to be 0 which is the topmost level.  

		@return ICommand - new command.
	 */
	virtual ICommand* QueryNewBookmarkCommand
		(
			UIDRef destination,
			UID parentBookmark,
			const PMString& bookmarkName = "",
			int32 indentLevel = 0
		) = 0;

	/**	Creates a delete bookmark command.
	
		@param bookmarks - Bookmarks to be deleted. 
		@param deleteDest - kTrue if delete the bookmark destination as well. Default is kTrue.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryDeleteBookmarkCommand
		(
			UIDList bookmarks,
			bool16 deleteDest = kTrue
		) = 0;

	/**	Creates a move bookmark command.
	
		@param bookmark - Bookmark to be moved. 
		@param newParent - New parent to move the bookmark to.
		@param newIndex - New index inside the parent to insert the bookmark.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryMoveBookmarkCommand
		(
			UIDRef bookmark,
			UIDRef newParent,
			int32 newIndex
		) = 0;

	/**	Creates a change bookmark command.
	
		@param bookmark - Bookmark to be changed. 
		@param newName - New name for the bookmark.

		@return ICommand - new command.
	 */
	virtual ICommand* QueryChangeBookmarkCommand
		(
			UIDRef bookmark,
			const PMString& newName
		) = 0;

	/**
	XRefPageNumber or XRefChapterNumber variables are a special non-user
	visible calculated text variable which, when inserted within a XRef source,
	will calculate its value based on the location of the matching destination.
	This method will return kTrue if an XRefPageNumber or XRefChapterNumber
	variable is a the specified TextIndex.
	@param textModel Pointer to TextModel
	@param at TextIndex of a location within the TextModel to check
	@return kTrue if there is a valid XRefPageNumber or XRefChapterNumber variable at the specified TextIndex
	*/
	virtual bool16	HasXRefPageOrChapterNumberVariableAt(const ITextModel* textModel, TextIndex at) = 0;

	/**
	*/
	enum XRefDestStatus {
		/**
		Page number will be valid.
		*/
		kXRDS_OK 			= 0,

		/**
		Page number will be invalid.
		*/
		kXRDS_HiddenLayer,

		/**
		Page number will be invalid.
		*/
		kXRDS_MasterPage,

		/**
		Page number will be invalid.
		*/
		kXRDS_Pasteboard,

		/**
		Page number will be invalid.
		*/
		kXRDS_Overset,

		/**
		Page number will be invalid.
		*/
		kXRDS_HiddenCondition,

		/**
		Page number will be invalid.
		*/
		kXRDS_Deleted,

		/**
		Page number will be invalid.
		*/
		kXRDS_Note,

		/**
		Any other StoryThread that we don't explicity specify - TextMacro, etc.
		Page number will be invalid.
		*/
		kXRDS_OtherLocation,

		/**
		Page number will be invalid.
		*/
		kXRDS_Missing,

		/**
		Page number will be invalid.
		*/
		kXRDS_HiddenItem,

	};

	/** Returns the page number string for the source or destination of specified hyperlink.
		@param hl - hyperlink to get page number string from.
		@param pageString - [OUT] if not nil, it will contain the page number string.
		@param wantDestination - kFalse to get the page number string for the cross-reference source, kTrue for the destination.
		@return XRefDestStatus - the status of the source or destination.
	*/
	virtual XRefDestStatus GetXRefPageString(const IHyperlink*hl,
											WideString* pageString = nil,
											bool16 wantDestination = kTrue) = 0;

	/** Returns the page number string for the hyperlink text destination.
		@param hlDest - hyperlink destination to get page number string from.
		@param pageString - [OUT] if not nil, it will contain the page number string.
		@return XRefDestStatus - the status of the destination.
	*/
	virtual XRefDestStatus GetXRefPageString(const IHyperlinkTextDestinationData* hlTextDest, WideString* pageString = nil) = 0;

	/** Returns the page number string for the first TextIndex of the hyperlink text source.
		@param hlSrc - hyperlink source to get page number string from
		@param pageString - [OUT] if not nil, it will contain the page number string.
		@return XRefDestStatus - the status of the source.
	*/
	virtual XRefDestStatus GetXRefPageString(const IHyperlinkSource* hlSrc, WideString* pageString = nil) = 0;

	/** Returns the page number string for the specified TextIndex.
		@param textModel - Pointer to ITextModel
		@param at - TextIndex within the ITextModel
		@param pageString - [OUT] if not nil, it will contain the page number string.
		@return XRefDestStatus - the status of the source or destination.
	*/
	virtual XRefDestStatus GetXRefPageString(const ITextModel* textModel, TextIndex at, WideString* pageString = nil) = 0;

	/** Returns the chapter number string for the destination of specified hyperlink.
		@param hl - hyperlink to get chapter number string from.
		@param chapterString - [OUT] if not nil, it will contain the chapter number string.
		@return kTrue if the hyperlink destination DataBase is valid, kFalse otherwise. Note that this method does require a valid TextDestination, only the DataBase to be valid.
	*/
	virtual bool16 GetXRefChapterString(const IHyperlink*hl,
										WideString* chapterString = nil) = 0;

	virtual RsrcID GetIconFromDestStatus(XRefDestStatus status) const = 0;
	
	/** Parse the string to generate a list of cross reference building blocks.
	*/
	virtual ErrorCode ParseXRefBuildingBlocksString(IDataBase* db, const PMString& s, K2Vector<XRefBuildingBlock>& blocks,
		PMString* warningString = nil) = 0;

	virtual IWorkspace* QueryWorkspaceForDB(IDataBase *db) = 0;

	/** Checks if specified cross-reference format is used by any cross-reference source. 
	*/
	virtual bool16 IsXRefFormatInUse(UIDRef format) = 0;

	/**
	Given a TextModel and TextIndex, returns a reference to any HyperlinkSource
	that overlaps that TextIndex.
	@param model Pointer to ITextModel
	@param at TextIndex within the model where to look for the HyperlinkSource
	@param pOptStart Optional pointer which will be filled in with the first TextIndex of the found HyperlinkSource, unchanged otherwise.
	@param pOptEnd Optional pointer which will be filled in with the end TextIndex of the found HyperlinkSource, unchanged otherwise.
	@return Pointer to HyperlinkSource, or nil.
	*/
	virtual IHyperlinkSource* QueryHyperlinkSourceAt(const ITextModel* model,
												TextIndex at,
												TextIndex* pOptStart = nil,
												TextIndex* pOptEnd = nil) = 0;



	/**
	Given a scanner and TextIndex, returns the full text of the paragraph including any numbers. All non-visible 
	characters are stripped out. Inline placeholders are not removed.
	@param scanner text scanner
	@param textIndex beginning of the paragraph. 
	@param paragraphSpan span of the paragraph.
	@return cleaned paragraph string.
	*/
    virtual WideString	GetFullVisibleParagraphString(IComposeScanner * scanner, TextIndex textIndex, int32 &paragraphSpan) = 0; 

	/** Clean up unused destinations in the specified database.
		@param db - database for destinations to be cleaned
		@param hiddenOnly - only cleanup hidden (not shared) destinations
		@param suppressWarnings - do not show any warnings, default true
	*/
	virtual void 		CleanupUnusedDestinations(IDataBase* db, bool16 hiddenOnly, bool16 suppressWarnings = kTrue) = 0;
	
	/**	Given a range of text determine whether any hyperlink source wholly contains the range or not.

		@param *model - The text model to look at
		@param start - The start of the range
		@param end - The end of the range
		@return bool16 - kTrue if any hyperlink source wholly contains the range or kFalse.
	*/
	virtual bool16		IsRangeWhollyContainHyperlink(ITextModel* model, TextIndex start, TextIndex end) = 0;
};

#endif // __HyperlinkUtils__
