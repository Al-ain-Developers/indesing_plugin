//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableUtils.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Purpose: Table related utility functions.
//  
//========================================================================================

#pragma once
#ifndef __ITABLEUTILS__
#define __ITABLEUTILS__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "UIDRef.h"
#include "ScriptData.h"
#include "TableTypes.h"
#include "PMTextUtils.h"
#include "K2Vector.h"
#include "PMPoint.h"
#include "TextChar.h"

//-----------------------------------
//	Forward References
//
class ITableFrame;
class ITableModel;
class ITextModel;
class ITableTarget;
class PMReal;
class ITextStoryThreadDict;
class ICellContent;
class IPlaceBehavior;


// ===================================================================================
//	class ITableUtils
// ===================================================================================
/** Table related utility functions. Some of these are not
	new selection-architecture compliant and should be approached with caution.
*/
class ITableUtils : public IPMUnknown {

//-----------------------------------
//	API
//
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_ITABLEUTILS};

	/** Data structure that identifies the cells chunkArea in the table frame represented by tableFrameContainingChunck
		A cell chunk is made up of a GridArea and the table frame where the chunk falls, a chunk will fall in only one table frame
	 */
	class CellChunk
	{
	public:
		typedef base_type data_type;

		/** Constructor
			@param chunk	GridArea
			@param tableFrame	TableFrame containing GridArea
		*/
		CellChunk(GridArea chunk, UIDRef tableFrame) : chunkArea(chunk), tableFrameContainingChunck(tableFrame) {}
		GridArea		chunkArea;
		UIDRef			tableFrameContainingChunck;
	};

	// ----- Table Creation -----
	/** Method to convert tab-delimited text into a table.
		Wrapper around execution of the kTextToTableCmdBoss command which simplifies process
		of converting delimited text into a table.
		@param textModel specifies the text model containing text to convert to table
		@param textRange delimits the range of text characters to transform into table
		@param colSeparator specifies delimiter for columns
		@param rowSeparator specifies delimiter for rows
		@param userNumCols specifies number of columns in table if colSeparator equals rowSeparator, otherwise ignored
		@param tableStyleUID [IN] optional, the table style to use for the new
		table, if this is <code>kInvalidUID</code>, the root table style is used
		@return reference to the table created as UIDRef
	*/
	virtual UIDRef 		ConvertTextToTable(ITextModel* textModel, const Text::StoryRange& textRange, const PMString colSeparator="\t", const PMString rowSeparator="\r", const int32 userNumCols=1, const UID& tableStyleUID = kInvalidUID) const = 0;
	/** Same as above method except params 3 and 4 are vectors of seperators instead of individual strings
		@param colSeparators	vector of strings that can be used interchangably as seperators for the columns
		@param rowSeparators	vector of strings that can be used interchangably as seperators for the rows
	*/
	virtual UIDRef 		ConvertTextToTable(ITextModel* textModel, const Text::StoryRange& textRange, const K2Vector<PMString>& colSeparators, 
										const K2Vector<PMString>& rowSeparators, const int32 userNumCols=1,
										const UID& tableStyleUID = kInvalidUID) const = 0;
						// $$$ Use a specifier here: should not require a selection.
						// $$$ This is probably true for most of these functions.

	/** Used to specify whether text caret should be placed in first
		cell when a new table is created.
	*/
	enum ESetTextSelection { eNoSelection, eSetSelectionInFirstCell };

	/** Method to insert a table into a text flow.
		Height is measured in points. If rowHeight = 0.0 then the row height is
		determined by the size of the content because auto-grow is on for
		all rows. A non zero value of height will  result in all rows having
		that minimum height.

		@param textModel refers to the text model into which this table might later be placed.
		@param index index within the text model for the start of the span to be replaced
		@param len span of characters in the model to be replaced by the table
		@param numRows specifies number of rows in the new table
		@param numCols specifies number of columns in the new tables
		@param rowHeight specifies the desired row height in points
		@param colWidth specifies the desired row height in points
		@param cellType	specifies type of cell, e.g. kTextCellContentType
		@param setSelection specifies whether caret is going to be in first cell or not
		@param tableStyle [IN], optional the table style to use for the new
		table, if this is <code>kInvalidUID</code> the root table style will
		be used
		@precondition  textModel <> nil
		@precondition len >= 0
		@precondition index >= 0 and index+len < threadStart + threadspan
		@precondition numRows >= 0 and numCols >= 0
		@precondition rowHeight >= 0.0 and colWidth > 0.0
		@postcondition self.GetTableModel(textModel, index) <> UIDRef::gNull
	*/
	virtual void 		InsertTable(ITextModel* textModel,
									TextIndex index, int32 len,
									int32 numRows, int32 numCols,
									const PMReal& rowHeight,
									const PMReal& colWidth,
									CellType cellType,
									const ESetTextSelection setSelection,
									const UID& tableStyle = kInvalidUID) const = 0;

	/**
		Same as above, only this takes three addition parameters. Two after the number of rows and columns --
		the number of headers and footers
		One after tableStyle-
		@param direction	specifies direction of table

	*/
	virtual void 		InsertTable(ITextModel* textModel,
									TextIndex index, int32 len,
									int32 numRows, int32 numCols,
									int32 numHeaderRows, int32 numFooterRows,
									const PMReal& rowHeight,
									const PMReal& colWidth,
									CellType cellType,
									const ESetTextSelection setSelection,
									const UID& tableStyle = kInvalidUID,
									Tables::EDirection direction = Tables::eLTR) const = 0;

	// ----- Misc -----
	/** Acquire a table model ref given a text model and a starting point in the text model.

		Attempts to return a persistent reference (UIDRef) for a table model, given a text
		model and an index within the model that is located within a story thread for a cell in the table.
		Will find a table model if the index is inside of a cell.
		Will find a table model if index points to a frame anchor or points to an anchor character
		embedded inside a frame anchor.

		@param text reference to text model that contains a table
		@param index should be an index in the text model that is text within a cell
		@precondition text <> nil
		@precondition index >= 0 && index < text.TotalLength()
		@postcondition <pre> ownedItemStrand = text.QueryInterface(IID_IITEMSTRAND)
						result <> UIDRef::gNull implies
						indices->exists(i | ownedItemStrand.GetOwnedUID(i, kFrameAnchorBoss) <> kInvalidUID
						result = UIDRef::gNull implies
						ownedItemStrand.GetOwnedUID(index, kFrameAnchorBoss) = kInvalidUID</pre>

	*/
	virtual UIDRef 		GetTableModel(ITextModel* text, TextIndex index) const = 0;

	/** Query for root table style by UID.
		@precondition db <> nil
		@return UID of root style, kInvalidUID otherwise.
	*/
	virtual	UID			GetRootTableStyle(IDataBase* db) const = 0;

	/** Takes the given GridArea and turns it into chunks of complete cells.
		@param	selection specifies the area of the table that is to be turned into cell-chunks.
		@param	tableModel refers to the table model from which the cells are going to be chunked.
		@return collection of areas, each of which is a complete cell
	*/
	virtual K2Vector<CellChunk> * GetCellChunks(const GridArea selection, const ITableModel* tableModel) const = 0;

	// ----- Misc shared by UI and scripting -----
	/** Calculate default sizes for cells in a table to be created.
		Attempts to calculate a reasonable sized bounding box for a table that might be
		placed in a textflow.

		@param	textModel refers to the text model into which this table might later be placed.
		@param	insertLocation specifies the index within the text model where a table might be placed.
		@param	numRows count of rows in prospective table
		@param	numCols	count of columns in prospective table
		@param rowHeight, out-parameter, holds the calculated row-height given the input
		@param colWidth, out-parameter, holds the calculated column-width given the input
	 */
	virtual void		CalculateDefaultCellBounds(const ITextModel* textModel,
													TextIndex insertLocation,
	 												int32 numRows, int32 numCols,
	 												PMReal& rowHeight, PMReal& colWidth) const = 0;

	// ----- Misc shared by UI and Model -----
	/** Determine how many sides in the selection are selected.
		This method attempts to calculate  how many sides are selected, e.g. when applying strokes to the selection.
		Returns the sides which can be active in the selection
		Returns a Tables::ESelectionSides which represents the sides the selection contains

		@param tableTarget refers to the table selection
		@return the sides selected, as an ESelectionSides value
	*/
	virtual Tables::ESelectionSides	CalculateSides(const ITableTarget* tableTarget) const = 0;

	// ----- Scripting -----
	/** Creates an instance of an object (e.g. of class kScriptCellRefBoss)
		that can be used to manipulate a region of a table.
		@param context is the request context
		@param area delimits the area of interest within the table
		@param tableModel table of interest that this object will manipulate
		@param objectList effectively holds the [out] parameter, an interface ptr (of type IScript) is appended to this list
		@param parent the parent of the script DIFFERENCE IN TWO VERSIONS OF FUNCTION, one has this one doesn't
		@return kSuccess if object could be created and appended to list, kFailure otherwise
	*/
	virtual ErrorCode	CreateCellScriptObject( const RequestContext& context, const GridArea& area, const ITableModel* tableModel, ScriptList* objectList ) = 0 ;
	/** @see CreateCellScriptObject */
	virtual ErrorCode	CreateCellScriptObject( const RequestContext& context, const GridArea& area, const ITableModel* tableModel, ScriptList* objectList, IScript* parent ) = 0 ;
	/** @see CreateCellScriptObject */
	virtual ErrorCode	CreateRowScriptObject( const RequestContext& context, GridCoord row, const ITableModel* tableModel, ScriptList* objectList, IScript* parent ) = 0 ;
	/** @see CreateCellScriptObject */
	virtual ErrorCode	CreateColumnScriptObject( const RequestContext& context, GridCoord col, const ITableModel* tableModel, ScriptList* objectList, IScript* parent ) = 0 ;
	/** @see CreateCellScriptObject */
	virtual ErrorCode 	CreateTableScriptObject( const RequestContext& context, const ITableModel* tableModel, ScriptList* objectList ) = 0;
	/** @see CreateCellScriptObject */
	virtual IScript* 	CreateTableScriptObject( const RequestContext& context, const ITableModel* tableModel) = 0;

	/** Creates a new table style and adds it to the table style name table.
		@param styleName			Name of the style. Should be non empty. Style name strings are not tranlsated. Pre: self.IsStyleNamePresent(styleName) == kFalse
		@param styleAttributes 	Attributes of the table style. All attributes in the list should an ITableAttrReport implementaion.
		@param dbOfStyleNameTable	The style is owned by the style name table that's on the workspace boss of this database.
		@param outNewStyleUID		Out argument. If return is kSuccess this is the tUID of the table style created.
	*/
	virtual ErrorCode	ProcessCreateTableStyle(const PMString& styleName, const AttributeBossList* styleAttributes, IDataBase* dbOfStyleNameTable, UID& outNewStyleUID) const = 0;

	/**
		Returns kTrue if a table style with styleName exists in ITableStyleNameTable on the workspace associated with the
		database dbOfStyleNameTable.
		@param styleName			Name of style to check for
		@param dbOfStyleNameTable	Database whose associated workspace should be checked
	 */
	virtual bool16		IsStyleNamePresent(const PMString& styleName, IDataBase* dbOfStyleNameTable) const = 0;

#ifdef DEBUG
	/** Returns true if all attributes are table attributes.
		@param attrs	List of attributes to be checked.
	*/
	virtual bool16		AreTableAttributes(const AttributeBossList* attrs) const = 0;
#endif

	/**
		Convert pasteboard points to table frames' local points. Used for
		hit testing so it has some small adjustments to the rect of table frame. Will constrain
		to table frame if within 3 units of table frame stroke bounding box.
		Currently used in TableFrameEventAction and TableFrameOwnedItemIBeamData
		@param tableFrame			pointer of the table frame
		@param pt	Pasteboard coordinates
	 */
	virtual	PMPoint ConvertToLocalPoint(const ITableFrame *tableFrame, const PBPMPoint& pt) const = 0;

	/**
		Return whether the given text index is within a table or not.
		@param textModel specifies the text model containing the table
		@param at	the TextIndex in question.
	 */
	virtual bool16 InsideTable(const ITextModel* textModel, TextIndex at) const = 0;

	/**
		Return the text index (in the primary story thread) of the anchor representing the table which contains the given text index.
		If the text index parameter is not in a table, the unchanged parameter is the return value.
		@param textModel specifies the text model containing the table
		@param withinTableTextIndex	the TextIndex in question - must be within a table.
	 */
	virtual TextIndex TableToPrimaryTextIndex(const ITextModel* textModel, TextIndex withinTableTextIndex) const = 0;

	/**
		Return the text range (in the primary story thread) of the anchor representing the table which contains the given text range.
		If the range parameter is not in a table, the unchanged parameter is the return value.
		@param textModel specifies the text model containing the table
		@param tableRange	the range in question - must be within a table.
	 */
	virtual RangeData TableToPrimaryTextRange(const ITextModel* textModel, RangeData tableRange) const = 0;

	/**
	Adobe internal use only. Do not use. Will be removed.
	*/
	virtual bool16		DictGetIsComposable(const ITextStoryThreadDict* dict,
											uint32 dictKey) const = 0;
	virtual ParcelKey	DictGetParcelKeyOfControllingAnchor(const ITextStoryThreadDict* dict, uint32 dictKey, ParcelKey keyInChildThread) const = 0;

	/**
		This is the code which cleans up a selection area into a selection which best represents the selection which is drawn
		It does 2 things, the first is to Shrink the selection to the first anchor and the last anchor selected, the second is to
		fix up the selection so it contains as many whole cells as possible (if you select 2 adjacent anchors of congruent anchors it will
		extend the selection to contain both whole cells)
	*/
	virtual GridArea		FixUpTableSelection(const GridArea selection, const ITableModel *model) const  = 0;

	/**
	Not all TextStoryThreads can properly host a Table. This method will
	tell the caller if the specified TextIndex and do so.
	@param textModel
	@param TextIndex
	@return kTrue if a Table may be inserted at the specified TextIndex.
	*/
	virtual bool16			CanInsertTableAt(const ITextModel* textModel,
											TextIndex at) const = 0;

	/**
	@param cell Pointer to TextCell boss.
	@param key Of the Parcel containing the text content
	@return ParcelKey of the actual Parcel context.
	*/
	virtual ParcelKey		GetHFProxyParcelKey(const ICellContent* cell,
												ParcelKey key) const = 0;

	/**
	This method provides context information for a TextIndex which is in a
	Header or Footer cell. If it returns kTrue, then pFrameBodyRange will be
	set to the Text Range of the drawing TableFrame.
	@param textModel
	@param at
	@param pFrameBodyRange Pointer to RangeData that will be filled in with drawing TableFrames body rows.
	@param pTableBodyRange Pointer to RangeData that will be filled in with Table's Text range.
	@return kTrue if the specified TextIndex is in a Header/Footer cell.
	*/
	virtual bool16			GetHFTextRangeContext(const ITextModel* textModel,
										TextIndex at,
										RangeData* pFrameBodyRange,
										RangeData* pTableBodyRange) const = 0;

	/**
	This method first triggers the conversion of cell to a graphic cell, if it 
	is not a graphic cell. Then, it finds out the object inside page item cell & returns it 
	place behavior. This API is use to directly place an object inside text cell
	@param tableModel
	@cellAddress whose place behavior we wish to know
	@return place behavior of object inside page item cell
	*/
	virtual IPlaceBehavior* QueryPageItemCellPlaceBehavior(const ITableModel* tableModel, 
										GridAddress cellAddress) = 0;

	/**
		This method first triggers the conversion of cell to a graphic cell, if it
		is not a graphic cell. Then, it finds out the object inside page item cell & returns it
		place behavior. This API is use to directly place an object inside text cell
		@param tableModel
		@cellAddress whose place behavior we wish to know
		@return place behavior of object inside page item cell
	*/
	virtual IPlaceBehavior* QueryPageItemCellPlaceBehavior(UIDRef tableModel, 
		GridAddress cellAddress) = 0;

	/**
	This method checks is item is inside any table cell.
	@param item which we want 
	@return kTrue if item is inside table cell
	@return UID of pageItemAdapterBoss. See IPageItemAdapter for more details
	*/
	virtual bool16 IsTableCellContent(const UIDRef& item, UID& pageItemAdapter) const = 0;
	
	/**
	This method checks is item is inside any table cell.
	@param item which we want 
	@return kTrue if item is inside table cell
	@return UID of pageItemAdapterBoss if valid pointer. See IPageItemAdapter for more details
	*/
	virtual bool16 IsTableCellContent(const UIDRef& item, UID* pageItemAdapter = nil) = 0;


	/**
	This method performs validation on content of page item cells. i.e
	if they have valid bounds or not. And if not, then it will ask cell to 
	have minimum size bounds.
	@param items list of items to validate
	*/
	virtual void ValidateContent(UIDList& items) const = 0;

	/** Get the cell type of any specific cell
		@param	tableModel	tbale to query from
		@param	cellAddress	cell to query for
		@return	CellType the cell type of specified cell.
	
	*/
	virtual CellType GetCellContentType(UIDRef tableModel, GridAddress cellAddress) const = 0;

	/**
	This method first checks if placed item is placed in a cell.
	If yes, then it will return pointer to it's ICellContent.
	@param Ref of item placed in cell. 
	*/
	virtual ICellContent* QueryCellContentfromPlacedItem(UIDRef placedItem) const = 0;

	/**	Check if any cell can be converted into graohic cell
		@param	tableModel	table to query from
		@param	cellAddress	cell to query for
		@return kTrue if cell can be converted to graphic cell, otherwise kFalse
	*/
	virtual bool16 CanConvertToGraphicCell(UIDRef tableModel, const GridAddress &cellAddress) const = 0;

	/**	Check if a text cell with inline, can be converted into a graphic cell with inline object placed inside it
		@param	tableModel	table to query from
		@param	cellAddress	cell to query for
		@return kTrue if text cell with inline, can be converted into a graphic cell with inline object placed inside it
	*/
	virtual bool16 CanConvertInlineCellToImageCell(const ITableModel* table, const GridAddress& cell) const = 0;

	/** Returns kTrue if there is any text cell in the grid area specified, kFalse otherwise
		@param tableModel	tableModel to query from
		@param	area	GridArea of cells to query for
		@return bool16	Returns kTrue if there is any text cell in that grid area
	*/
	virtual bool16  HasAnyTextCell(ITableModel* tableModel, const GridArea& area) const = 0;

	/** Returns kTrue if there is any graphic cell in the grid area specified, kFalse otherwise
		@param tableModel	tableModel to query from
		@param	area	GridArea of cells to query for
		@return bool16	Returns kTrue if there is any graphic cell in that grid area
	*/
	virtual bool16  HasAnyGraphicCell(ITableModel* tableModel, const GridArea& area) const = 0;

	virtual bool16	CanPlaceInGraphicCell(UIDRef item, ErrorCode* err = NULL) const = 0;

	virtual ErrorCode ResizeTableFrame(ITableFrame *tableFrame, const PMReal& horizonProp, const PMReal& verticalProp) = 0;

    virtual ErrorCode ResizeTableFrame(ITableFrame *tableFrame, PMRect tableArea, const int32 numRowsInFrame,
                                       const int32 numColumnsInFrame, ColRange columnsInFrame, const PMReal& horizonProp, const PMReal& verticalProp) = 0;
    
	virtual void SetMinRowHeight(ITableModel* table, int32 row, int32 howMany, const PMReal& height) = 0;
};


#endif // __ITABLEUTILS__
