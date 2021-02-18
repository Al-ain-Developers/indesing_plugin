//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IStructureMarks.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __ISTRUCTUREMARKS__
#define __ISTRUCTUREMARKS__

#include "BravoForwardDecl.h"

class IDocument;
class ICompositionStyle;
class IStyleInfo;
class IDrawingStyle;
class IWaxLine;
class IPDFFlattenerParams;
class PMRect;
class PMMatrix;
class IWaxRun;
class IMultiColumnTextFrame;

#include "LanguageID.h"
#include "IPDFHyperlinks.h"
#include "PDFID.h"

typedef struct _t_PDDoc *PDDoc;
typedef struct _t_PDPage *PDPage;
typedef struct _t_PDEElement *PDEElement;
typedef struct OPAQUE_64_BITS CosObj;

/**
This interface contains methods to watch important events during PDF export. 
You can get this interface from a IGraphicsPort (gPort) using this:
InterfacePtr<IStructureMarks> structureMarks(gPort, IID_ISTRUCTUREMARKS);
*/
class IStructureMarks : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTRUCTUREMARKS };

		/**
			Enumerates the different types of table rows.
		*/
		enum TableRowType
		{
			/** Table body row */
			kBodyRow = 0,
			/** Table header row */
			kHeaderRow,
			/** Table footer row */
			kFooterRow
		};

		/**
			Enumerates the different types of lists.
		*/
		enum ListType
		{
			/** Regular paragraph */
			kNone = 0,
			/** Bulleted list */
			kBulleted,
			/** Numbered list */
			kNumbered
		};

		/**
			This method is called at the beginning of export.  It is called even for the one document case.
			@param int32 docInfoIndex: index to the document information.
			@param DocPageIndexList docIndexList: index to the document page list.
			@param bool16 readerSpreads: kTrue when exporting reader spreads.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginBook(int32 docInfoIndex, DocPageIndexList docIndexList, bool16 readerSpreads) = 0;
		/**
			This method is called at the end of export.  It is called even for the one document case.
			There are matching BeginBook and EndBook calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndBook() = 0;

		/**
			This method is called at the beginning of a exporting a document.
			@param IDataBase *db: the document being exported.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginDocument(IDataBase *db) = 0;
		/**
			This method is called at the end of exporting a document.
			There are matching BeginDocument and EndDocument calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndDocument() = 0;

		/**
			This method is called at the beginning of a exporting a page.
			@param int32 indexPageInfo:
			@param UID pageUID: the page UID or spread UID being exported.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginPage(int32 indexPageInfo, UID pageUID) = 0;
		/**
			This method is called at the end of exporting a page.
			There are matching BeginPage and EndPage calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndPage() = 0;

		/**
			This method is called when a new PDF content stream is started. 
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginNestedContent() = 0;
		/**
			This method is called when a new PDF content stream is finished. 
			There are matching BeginNestedContent and EndNestedContent calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndNestedContent() = 0;

		/**
			This method is called at the beginning of exporting a text frame.
			@param IMultiColumnTextFrame* mcFrame: the text frame being exported.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginTextFrame(const IMultiColumnTextFrame* mcFrame) = 0;
		/**
			This method is called at the end of exporting a text frame.
			There are matching BeginTextFrame and EndTextFrame calls.
			@param IMultiColumnTextFrame* mcFrame: the text frame being exported.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndTextFrame(const IMultiColumnTextFrame* mcFrame) = 0;

		/**
			This method is called at the beginning of exporting a paragraph.
			BeginParagraph will not be called when the export starts in the middle of a paragraph.
			There is no EndParagraph because it wouldn't necessarily match up with the BeginParagraph.
			@param ICompositionStyle *compositionStyle: composition style of the paragraph.
			@param IWaxLine *waxLine: wax for the paragraph.
			@param IStyleInfo *styleInfo: style info of the paragraph.
			@param IDrawingStyle *drawingStyle: drawing style of the paragraph.
			@param IStructureMarks::ListType listType: list type - none, bulleted or numbered.
			@param int32 listLevel: Paragraph nesting level inside a list structure. 0 stands for top level list paragraph. Can run upto any level.
			@param bool isStartWithEndnote: true if we want to start endnote before paragraph.
			@param UID endnoteUID: the UID of the endnote.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode BeginParagraph(ICompositionStyle *compositionStyle, IWaxLine *waxLine, const IWaxRun* waxRun, IStyleInfo *styleInfo, IDrawingStyle *drawingStyle,
											IStructureMarks::ListType listType = IStructureMarks::kNone, int32 listLevel = 0, bool isStartWithEndnote = false, UID endnoteUID = kInvalidUID) = 0;

		/**
			This method is called at the beginning of exporting a hyperlink.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginHyperlink() = 0;
		/**
			This method is called when a link annotation is added to the current hyperlink.
			@param int32 annotation: index of the annotation.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode AddLinkAnnotation(int32 annotation) = 0;
		/**
			This method is called at the end of exporting a hyperlink.
			There are matching BeginHyperlink and EndHyperlink calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndHyperlink() = 0;

		/**
			This method is called at the beginning of exporting a text run.
			@param IWaxRun *waxRun: waw run pointer.
			@param IDrawingStyle *drawingStyle: drawing style pointer.
			@param LanguageID languageID: Language ID of the run.
			@param bool32 oneCharSpan: true when the run is a special one character run.
			@param textchar oneChar: the special character when oneCharSpan is true.
			@param UID paragraphStyleUID: the paragraph style UID for the run.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginTextRun(IWaxRun *waxRun, IDrawingStyle *drawingStyle, LanguageID languageID, bool32 oneCharSpan, textchar oneChar, UID paragraphStyleUID) = 0;
		/**
			This method is called when a text element is added to the current text run.
			@param int32 element: index of the text element.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode AddTextElement(int32 element) = 0;
		/**
			This method is called at the end of exporting a text run.
			There are matching BeginTextRun and EndTextRun calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndTextRun() = 0;

		/**
			This method is called at the beginning of PDF Figure.
			A figure is an inline or pageitems with IFigureElement interface.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginFigure() = 0;
		/**
			This method is called at the end of exporting a PDF Figure.
			There are matching BeginFigure and EndFigure calls.
			@param IDataBase *db: the document being exported.
			@param UID pageItemUID: the page item UID of the figure.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndFigure(IDataBase *db, UID pageItemUID) = 0;

		/**
			This method is called at the beginning of a table frame.
			A figure is an inline or pageitems with IFigureElement or IFigureElementOptional interface.
			@param PMRect &bbox: the bounding box of the table frame.
			@param bool32 firstTableFrame: true when this table contains the first table frame.
			@param bool32 oneFrameTable: true when the table is in only one frame.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginTableFrame(PMRect &bbox, bool32 firstTableFrame, bool32 oneFrameTable) = 0;
		/**
			This method is called at the beginning of a table row.
			@param IStructureMarks::TableRowType rowType: type of the row - body, header or footer.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginTableRow(IStructureMarks::TableRowType rowType = IStructureMarks::kBodyRow) = 0;
		/**
			This method is called at the beginning of a table cell.
			@param int32 spanWidth: the number of columns that this cells spans.
			@param int32 spanHeight: the number of rows that this cells spans.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginTableCell(int32 spanWidth, int32 spanHeight) = 0;
		/**
			This method is called at the end of exporting a table frame.
			There are matching BeginTableFrame and EndTableFrame calls.
			@param bool32 lastTableFrame: true when this is the last frame of this table.
			@param IDataBase *db: document being exported.
			@param UID pageItemUID: the text frame page item UID.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndTableFrame(bool32 lastTableFrame, IDataBase *db, UID pageItemUID) = 0;

		/**
			This method is called at the beginning of exporting a page item.
			@param IPMUnknown *pageItem: the page item being exported.
			@param const PMMatrix &matrix: the matrix of the page item.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual void BeginPageItemDrawing(IPMUnknown *pageItem, const PMMatrix &matrix) = 0;
		/**
			This method is called at the end of exporting a page item.
			There are matching BeginPageItemDrawing and EndPageItemDrawing calls.
			@param IPMUnknown *pageItem: the page item being exported.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual void EndPageItemDrawing(IPMUnknown *pageItem) = 0;

		/**
			This method is called at the beginning of exporting artifacts.
			Artifacts are page items or text that is not tagged in the PDF file.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual void BeginArtifacts() = 0;
		/**
			This method is called at the end of exporting artifacts.
			There are matching BeginArtifacts and EndArtifacts calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual void EndArtifacts() = 0;

		/**
			This method is called at the beginning of exporting a layer.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginLayer(CosObj layerInfo) = 0;
		/**
			This method is called at the end of exporting a layer.
			There are matching BeginLayer and EndLayer calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndLayer() = 0;

		/**
			This method returns true when structure is being recorded.
			@return bool32: true when recording structure, false otherwise. 
		*/
		virtual bool32 RecordingStructure() = 0;

		/**
			This method returns true when hyperlinks are being recorded.
			@return bool32: true when recording hyperlinks, false otherwise. 
		*/
		virtual bool32 RecordingHyperlinks() = 0;

		/**
			This method is called at the beginning of exporting a footnote reference.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode BeginFootnoteReference() = 0;
		/**
			This method is called at the end of exporting a footnote reference.
			There are matching BeginFootnoteReference and EndFootnoteReference calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndFootnoteReference() = 0;
		
		/**
			This method is called at the beginning of exporting an endnote reference.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode BeginEndnoteReference() = 0;
		/**
			This method is called at the end of exporting an endnote reference.
			There are matching BeginEndnoteReference and EndEndnoteReference calls.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode EndEndnoteReference() = 0;

		/**
			This method is called at the beginning of exporting a footnote item.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode BeginFootnote() = 0;
		/**
			This method is called at the end of exporting a footnote item.
			There are matching BeginFootnote and EndFootnote calls.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode EndFootnote() = 0;

		/**
			This method is called at the beginning of exporting a hyperlink inside a table cell.
			@return ErrorCode: Return kSuccess when successful. 
		*/
		virtual ErrorCode BeginTableCellHyperlink() = 0;

		/**
		This method is called to specify that the first paragraph of the text frame needs to be tagged as an index.
		@param setValue: if kTrue, the first paragraph is tagged as an index and the flag is then reset, so that rest of the paragraphs are tagged as list items.
		@return ErrorCode: Return kSuccess when successful.
		*/
		virtual void SetTagIndexOnce(bool16 setValue) = 0;

		/**
			This method is called at the beginning of exporting an anchored object.
			@return none.
		*/
		virtual void BeginAnchoredObject(IDataBase* db, UID pageItemUID) = 0;

		/**
			This method is called at the end of exporting an anchored object.
			There are matching BeginAnchoredObject and EndAnchoredObject calls.
			@return none.
		*/
		virtual void EndAnchoredObject(IDataBase* db, UID pagetItemUID) = 0;


		/**
			This method is called at the beginning of exporting an endnote text.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode BeginEndnote() = 0;

		/**
			This method is called at the end of exporting an endnote text.
			There are matching BeginEndnote and EndEndnote calls.
			@return ErrorCode: Return kSuccess when successful.
		*/
		virtual ErrorCode EndEndnote() = 0;

		/**
			Is this an endnote text run?
			@return true if this is an endnote text run, false otherwise.
		*/
		virtual bool IsEndnoteRun() = 0;

		/**
			This method is called when an anchored object marker (anchor) is encountered.
			@param IPMUnknown *inlineData: The anchored object's IInlineData interface.
			@param TextIndex textIndex: The position in the parent story where the object is anchored.
		*/
		virtual void AddAnchoredObjectMarker(const IPMUnknown *inlineData, TextIndex textIndex) = 0;

		/**
		This method is called in order to add an endnote link annotation.
		@param int32 annotation: The endnote annotation. @see IPDFHyperlinks::CreateEndnoteRefLink, IPDFHyperlinks::CreateEndnoteRangeLink
		@return kSuccess if the annotation was added successfully. Currently only returns kSuccess.
		*/
		virtual ErrorCode AddEndnoteLinkAnnotation(int32 annotation) = 0;

};
#endif
