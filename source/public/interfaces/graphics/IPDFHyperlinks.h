//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFHyperlinks.h $
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
#ifndef __IPDFHyperlinks__
#define __IPDFHyperlinks__

#include "PMRect.h"
#include "KeyValuePair.h"
#include "PDFID.h"
class PMMatrix;

typedef struct _t_PDDoc *PDDoc;
typedef struct _t_PDPage *PDPage;
typedef struct OPAQUE_64_BITS CosObj;
typedef OPAQUE_64_BITS PDAnnot;

// Used to store a list of page indeces that documents start page
typedef KeyValuePair<PMString, int32> DocPathIndexPair;
typedef K2Vector<DocPathIndexPair> DocPageIndexList;

/** Hyperlink attributes.
*/
class HotSpotAttributes
{
public:
	HotSpotAttributes() : borderWidth(0), hCornerRadius(0), vCornerRadius(0), selectionBehavior(1),
		useBorderColor(0), borderDashArrayLen(0) {};
	~HotSpotAttributes() {};

	/** The width of the border rectangle. 0 to hide it. Default 1.
	*/
	int32 borderWidth;

	/** Border rectangle horizontal corner radius. Default 0.
	*/
	int32 hCornerRadius;

	/** Border rectangle vertical corner radius. Default 0.
	*/
	int32 vCornerRadius;

	/** Selection behavior.
		0 No highlighting.
		1 Invert the contents of the annotations's bounding box.
		2 Display the annotations' down appearance, if any.
		3 Invert the annotations's border.
	*/
	int32 selectionBehavior;

	/** Whether to use the border color or black.
	*/
	bool32 useBorderColor;

	/** Number of entries in the borderDashArray.  0 for a solid line, the default.
	*/
	int32 borderDashArrayLen;

	/** RGB color to draw the border when useBorderColor is true.
	*/
	PMReal borderColor[3];

	/** On Off On Off ... length values.
	*/
	PMReal borderDashArray[10];
};

/** IPDFHyperlinks contains methods for creating PDF hyperlinks when exporting PDFs.

	As a document is being exported to a PDF file, this interface is called to signal
	special events and these methods come in pairs, see BeginBook, EndBook, BeginDocument,
	EndDocument etc.  The export process draws to a PDF port, similar to drawing to the
	screen or to a printer port. When it is on a page, between calls BeginPage, EndPage, you
	can call methods to create hyperlinks on the current page. See Hyperlink... methods.

	You can get this interface from a IGraphicsPort (gPort) using this:
	InterfacePtr<IPDFHyperlinks> structureMarks(gPort, IID_IPDFHYPERLINKS);
*/
class IPDFHyperlinks : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFHYPERLINKS };

		/** Destination type.
		*/
		enum DestinationType
		{
			/** Destination specified as upper-left corner point and a zoom factor.
			*/
			DestXYZ = 0, 

			/** Fits the page into the window, corresponding to the Acrobat viewer’s FitPage menu item.
			*/
			DestFit, 

			/** Fits the widths of the page into the window, corresponding to the Acrobat viewer’s 
			Fit Width menu item.
			*/
			DestFitH,	

			/** Fits the height of the page into a window.
			*/
			DestFitV, 

			/** Fits the rectangle specified by its upper-left and lower-right corner points into the window.
			*/
			DestFitR, 

			/** Fits the rectangle containing all visible elements on the page (known as the bounding box) 
			into the window, corresponds to the Acrobat viewer’s Fit Visible menu item.
			*/
			DestFitB, 

			/** Fits the width of the bounding box into the window.
			*/
			DestFitBH, 

			/** Fits the height of the bounding box into the window.
			*/
			DestFitBV
		};

		/** Contains the page index along with destination parameters and specifies where
		the hyperlink goes in the other document.
		*/
		class PageDestination
		{
		public:
			/** Construct a default PageDestination object.
			*/
			PageDestination() : fPageIndex(0), fDestinationType(DestXYZ), fInheritRect(true), fInheritZoom(true) {};

			/** Construct a PageDestination object.
			@param pageIndex is the destination page index.
			@param destinationType is the destination type.
			@param destinationRect is the destination rectangle.
			@param zoomFactor is the destination zoom factor.
			@param inheritRect is the destination inherit rectangle.
			@param inheritZoom is the destination inherit zoom factor.
			*/
			PageDestination(const uint32 pageIndex, const DestinationType destinationType, const PMRect &destinationRect,	const PMReal &zoomFactor) :
				fPageIndex(pageIndex), fDestinationType(destinationType), fDestinationRect(destinationRect), fZoomFactor(zoomFactor),
				fInheritRect(pageIndex), fInheritZoom(destinationType) {};
			~PageDestination() {};

			/** Get the destination page index.
			@return the destination page. 
			*/
			uint32 GetPageIndex() const {return fPageIndex;} ;

			/** Get the destination page type.
			@return the destination type. 
			*/
			DestinationType GetDestinationType() const {return fDestinationType;};

			/** Get the destination rectangle.
			@return the destination rectangle. 
			*/
			const PMRect &GetDestinationRect() const {return fDestinationRect;};

			/** Get the destination zoom factor.
			@return the destination zoom factor. 
			*/
			PMReal GetZoomFactor() const {return fZoomFactor;};

			/** Get the destination inherit rectangle.
			@return the destination inherit rectangle. 
			*/
			bool32 GetInheritRect() const {return fInheritRect;};

			/** Get the destination inherit zoom factor.
			@return the destination inherit zoom factor. 
			*/
			bool32 GetInheritZoom() const {return fInheritZoom;};

		private:
			uint32 fPageIndex;
			DestinationType fDestinationType;
			PMRect fDestinationRect;
			PMReal fZoomFactor;
			bool32 fInheritRect;
			bool32 fInheritZoom;
		};

		/** This is called by the default implementation when starting a PDF export whether it is a book export
		or a normal export.
		@param thePDDoc is the PDDoc being created. 
		@param addHyperlinks is true when the PDF export preference specifies hyperlinks.
		@param db is the database of the document being exported.
		@param addBookmarks is true when the PDF export preference specifies bookmarks. 
		@param bookExport is true when exporting a book. 
		@param docIndexList is the document page index list. 
		@param readerSpreads is true when reader spreads are on. 
		@param layers is true when exporting layers. 
		@return kSuccess when successful.
		*/
		virtual ErrorCode BeginBook(PDDoc thePDDoc, bool32 addHyperlinks, IDataBase *db, bool32 addBookmarks, bool32 bookExport, DocPageIndexList docIndexList, bool16 readerSpreads, bool16 layers = false) = 0;

		/** This is called by the default implementation when ending a PDF export whether it is a book export
		or a normal export.
		*/
		virtual ErrorCode EndBook() = 0;

		/** This is called by the default implementation when starting to export a document. A book has one or
		more documents.
		@param db is the database of the document being exported.
		*/
		virtual ErrorCode BeginDocument(IDataBase *db) = 0;

		/** This is called by the default implementation when ending a document.
		*/
		virtual ErrorCode EndDocument() = 0;

		/** This is called by the default implementation when starting to export a page of a document. 
		@param thePDPage is the PDPage being created.
		@param pageBounds is the page bounds.
		@param pageUID is the InDesign page UID being exported.
		*/
		virtual ErrorCode BeginPage(PDPage thePDPage, PMRect &pageBounds, PMMatrix &pageBoundsToSpreadMatrix, UID pageUID) = 0;

		/** This is called by the default implementation when ending a page of a document.
		*/
		virtual ErrorCode EndPage() = 0;

		/** Create a hyperlink on the current page that goes to a named destination.
			@param hotSpot is the location of the hotspot rectangle on the page.
			@param name is the destination name.  This is matched by name with the destination created with HyperlinkDestination.
			@param pAttributes points to the optional hotspot attributes. When nil, the default attributes are used.
			@param pAnnotation points to an optional return parameter.  The int32 returned is a token used with
			GetLinkAnnotation to get the associated PDF link annotation.
			@return kSuccess when successful.
		*/
		virtual ErrorCode HyperlinkHotSpot(const PMRect &hotSpot, const PMString &name, const HotSpotAttributes *pAttributes = nil, int32 *pAnnotation = nil) = 0;

		/** Create a hyperlink on the current page which goes to the given page.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param pageIndex is the destination page of the hyperlink.
		@param pAttributes points to the optional hotspot attributes. When nil, the default attributes are used.
		@param pAnnotation points to an optional return parameter.  The int32 returned is a token used with
		GetLinkAnnotation to get the associated PDF link annotation.
		@return kSuccess when successful.
		*/
		virtual ErrorCode HyperlinkHotSpotPage(const PMRect &hotSpot, int32 pageIndex, const HotSpotAttributes *pAttributes = nil, int32 *pAnnotation = nil) = 0;

		/** Create a hyperlink on the current page which goes to the given URL.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param theURL is the destination URL of the hyperlink.
		@param isMap is true to track the mouse position when the URI is resolved.
		@param pAttributes points to the optional hotspot attributes. When nil, the default attributes are used.
		@param pAnnotation points to an optional return parameter.  The int32 returned is a token used with
		GetLinkAnnotation to get the associated PDF link annotation.
		@return kSuccess when successful.
		*/
		virtual ErrorCode HyperlinkHotSpotURL(const PMRect &hotSpot, const PMString &theURL, const bool32 isMap, const HotSpotAttributes *pAttributes = nil, int32 *pAnnotation = nil) = 0;

		/** Special named destinations.
		*/
		enum NamedType { 
			/** Go to the next page.
			*/
			NextPage = 0,
			/** Go to the previous page.
			*/
			PrevPage, 
			/** Go to the first page of the document.
			*/
			FirstPage, 
			/** Go to the last page of the document.
			*/
			LastPage};

		/** Create a hyperlink on the current page which goes to the NamedType.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param namedType is the destination, either first, last, next or prev page, see NamedType.
		@param pAttributes points to the optional hotspot attributes. When nil, the default attributes are used.
		@param pAnnotation points to an optional return parameter.  The int32 returned is a token used with
		GetLinkAnnotation to get the associated PDF link annotation.
		@return kSuccess when successful.
		*/
		virtual ErrorCode HyperlinkHotSpotNamed(const PMRect &hotSpot, NamedType namedType, const HotSpotAttributes *pAttributes = nil, int32 *pAnnotation = nil) = 0;

		/** Create a hyperlink on the current page which goes to another PDF document.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param name is the named destination in another PDF document.
		@param fullpath is the full path name to the PDF document.
		@param bNewWindow is optional. Pass true to open the new document in a new window.
		@param pAttributes points to the optional hotspot attributes. When nil, the default attributes are used.
		@param pAnnotation points to an optional return parameter.  The int32 returned is a token used with
		GetLinkAnnotation to get the associated PDF link annotation.
		@return kSuccess when successful.
		*/
		virtual ErrorCode HyperlinkHotSpotExternal(const PMRect &hotSpot, const PMString &name, const PMString &fullpath, bool32 bNewWindow = false, const HotSpotAttributes *pAttributes = nil, int32 *pAnnotation = nil) = 0;

		/** Create a hyperlink named destination on the current page at the given location with the given name.
		@param name is the destination name to create. This name is matched up with the name specified by 
		HyperlinkHotSpot.
		@param destType is the type of destination to create.
		@param destRect is an optional pointer to a reference rectangle. See DestinationType.
		@param zoomFactor is an optional pointer to a zoom factor. See DestinationType.
		*/
		virtual ErrorCode HyperlinkDestination(const PMString &name, DestinationType destType, const PMRect *destRect = nil, const PMReal *zoomFactor = nil) = 0;

		/** Get the CosObj page and PDAnnot for the given annotation. The annotation is valid between 
		BeginDocument and EndDocument.
		@param annotation specifies the PDF annotation to get. It comes from a previous call to one of the creation
		methods above.
		@param page is the page the hyperlink is on.
		@param annot is the PDF annotation.
		*/
		virtual ErrorCode GetLinkAnnotation(int32 annotation, CosObj *page, PDAnnot *annot) = 0;

		/** Create a hyperlink on the current page with the given hot spot. The attributes and destination are
		determined by the db, hyperlinkUID.
		@param db of hyperlinkUID.
		@param hyperlinkUID is the hyperlinkUID.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param linkAnnotation points to an optional return parameter.  The int32 returned is a token used with
		GetLinkAnnotation to get the associated PDF link annotation.
		*/
		virtual ErrorCode CreateHyperlink(IDataBase *db, UID hyperlinkUID, PMRect &hotSpot, int32 *linkAnnotation) = 0;

		/** Create a hyperlink on the current page which goes to another PDF document. 
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param pageDestination contains the page index along with destination parameters and specifies where
		it goes in the other document.
		@param fullpath is the full path name to the PDF document.
		@param bNewWindow is optional. Pass true to open the new document in a new window.
		@param pAttributes points to the optional hotspot attributes. When nil, the default attributes are used.
		@param pAnnotation points to an optional return parameter.  The int32 returned is a token used with
		GetLinkAnnotation to get the associated PDF link annotation.
		@return kSuccess when successful.
		*/
		virtual ErrorCode HyperlinkHotSpotExternalPage(const PMRect &hotSpot, const PageDestination &pageDestination, const PMString &fullpath, bool32 bNewWindow = false, const HotSpotAttributes *pAttributes = nil, int32 *pAnnotation = nil) = 0;

		/** This is called by the default implementation when starting to export a layer of a document. 
		@param layerInfo is the layer information.
		*/
		virtual ErrorCode BeginLayer(CosObj layerInfo) = 0;

		/** This is called by the default implementation when ending a layer of a document.
		*/
		virtual ErrorCode EndLayer() = 0;

		/** Create a link at endnote reference on the current page with the given hot spot. The attributes and destination are
		determined by the db, endnoteUID.
		@param db of endnoteUID.
		@param endnoteUID is the UID of the endnote reference.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param linkAnnotation points to an optional return parameter.  The int32 returned is a token used with
		*/
		virtual ErrorCode CreateEndnoteRefLink(IDataBase *db, UID endnoteUID, PMRect &hotSpot, int32 *linkAnnotation) = 0;

		/** Create a endnote link at endnote range on the current page with the given hot spot. The attributes and destination are
		determined by the db, endnoteRangeUID.
		@param db of endnoteRangeUID.
		@param endnoteRangeUID is the UID of the endnote range.
		@param hotSpot is the location of the hotspot rectangle on the page.
		@param linkAnnotation points to an optional return parameter.  The int32 returned is a token used with
		*/
		virtual ErrorCode CreateEndnoteRangeLink(IDataBase *db, UID endnoteRangeUID, PMRect &hotSpot, int32 *linkAnnotation) = 0;
		
		/** Get the CosObj page and PDAnnot for the given endnote annotation. The annotation is valid between
		BeginDocument and EndDocument.
		@param annotation specifies the PDF endnote annotation to get. It comes from a previous call to one of the creation
		methods above.
		@param page is the page the hyperlink is on.
		@param annot is the PDF annotation.
		*/
		virtual ErrorCode GetEndnotelinkAnnotation(int32 annotation, CosObj *page, PDAnnot *annot) = 0;

		/** Get alternate text of hyperlink.
		@param annotation specifies hyperlink annotation. 
		@param altText stores alt text of hyperlink.
		@return kSuccess when successful.
		*/
		virtual ErrorCode GetHyperlinkAltText(int32 annotation, PMString& altText) = 0;
};

#endif
