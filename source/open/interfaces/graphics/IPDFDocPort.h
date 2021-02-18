//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/graphics/IPDFDocPort.h $
//  
//  Owner: Tommy Donovan
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
//  Purpose of interface
//  IPDFDocPort is API for creating PDF documents.
//  
//========================================================================================

#pragma once
#ifndef __IPDFDOCPORT__
#define __IPDFDOCPORT__

#include "BravoForwardDecl.h"

class IDocument;
class IPDFFlattenerParams;
class PMRect;
class PMMatrix;
class IShape;
class IMetaData;
class RCAnnotationMappingData;

#include "LanguageID.h"
#include "PDFID.h"
#include "KeyValuePair.h"
#include "UIDList.h"
#include "PMRect.h"

#include <map>

typedef struct _t_PDDoc *PDDoc;
typedef struct _t_PDPage *PDPage;
typedef struct _t_PDEElement *PDEElement;
typedef struct _t_PDEContent *PDEContent;
typedef struct _t_PDEForm	*PDEForm;

typedef struct _t_PDEXGroup *PDEXGroup;
typedef struct OPAQUE_64_BITS* CosObjPtr;
typedef struct OPAQUE_64_BITS* PDAnnotPtr;

// Used to store a list of page indeces that documents start page
typedef KeyValuePair<PMString, int32> DocPathIndexPair;
typedef K2Vector<DocPathIndexPair> DocPageIndexList;

const PMReal kMinPDFPageWidth = 3.0;
const PMReal kMaxPDFPageWidth = 14400.0;
const PMReal kMinPDFPageHeight = 3.0;
const PMReal kMaxPDFPageHeight = 14400.0;

/**
 IPDFDocPort is one of the primary interfaces used in InDesign's PDF export
 code. It is intended primarily for internal use only, as it is very complex
 and makes extensive use of internal types not made available to third-party
 developers.
 
 Third-party developers wishing to incorporate PDF export functionality in 
 their plug-ins should consider using the services provided by the PDF export 
 command (kPDFExportCmd) rather than attempting to use this interface directly.
 Using this InDesign interface in conjunction with the PDFLib SDK is discouraged: It
 is likely that the version of the PDFLib used by InDesign and the version supported
 by PDFLib SDK will be different and thus potentially incompatible.
 
 IPDFDocPort is an integral part of kPDFViewPortBoss and is responsible for
 much of the basic manipulation of the document's structure. In many ways, the
 doc port is also responsible for maintaining the document's lifetime: the 
 document is created in a call to startdoc, and saved to disk in a call to 
 enddoc.
 
 IPDFDocPort (or just 'the doc port' for short) maintains an internal stack of
 PDEContent objects. Calls to the IGraphicsPort interface aggregated on 
 kPDFViewPortBoss will target the current content object. A number of the 
 methods on the interface create and push new PDEContent objects on the stack, 
 with a corresponding method to finalize the content and pop it from the stack.
 Care must be taken that these calls are nested properly, or undefined results 
 will be produced. You have been warned.
 
 @see IGraphicsPort
 */

class IPDFDocPort : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPDFDOCPORT };
		
		/**
		 Initializes the doc port at the beginning of an export session. Must be 
		 called before any of the other methods on the interface are called.
		 
		 @param db				IN The database for the document being exported
		 @param pathName		IN The path to the PDF file to generate
		 @param docName			IN The name of the document being exported
		 @param bookExport		IN Flag: kTrue if export is for a book, else kFalse
		 @param docIndexList	IN Used to map a document's path to its page number in the generated PDF
		 @param readerSpreads	IN Flag: kTrue if should export as spreads, else kFalse
		 @return ErrorCode indicating success or failure of the initialization
		 */
		virtual ErrorCode startdoc(IDataBase *db, IDFile& pathName, PMString& docName, bool32 bookExport, DocPageIndexList docIndexList, bool16 readerSpreads) = 0;

		/**
		 Initializes the doc port at the beginning of an export session. Must be 
		 called before any of the other methods on the interface are called.
		 
		 @param db				IN The database for the document being exported
		 @param pStream			IN The stream to which the generated PDF is written
		 @param docName			IN The name of the document being exported
		 @param bookExport		IN Flag: kTrue if export is for a book, else kFalse
		 @param docIndexList	IN Used to map a document's path to its page number in the generated PDF
		 @param readerSpreads	IN Flag: kTrue if should export as spreads, else kFalse
		 @return ErrorCode indicating success or failure of the initialization
		 */
		virtual ErrorCode startdoc(IDataBase *db, IPMStream* pStream, PMString& docName, bool32 bookExport, DocPageIndexList docIndexList, bool16 readerSpreads) = 0;
		
		/**
		 Finalizes the document being exported at the end of an export session.
		 Should be called after all operations for the export have been 
		 completed. Optionally saves the generated PDF.
		 
		 @param bSaveIt			IN Flag: kTrue if the generated PDF should be saved to the file or stream
		 @return ErrorCode indicating success or failure of the finalization
		 */
		virtual ErrorCode enddoc(bool16 bSaveIt = kTrue) = 0;
		
		/**
		 Starts a new page with the specified bounds. The various 'box'
		 parameters are used to populate the corresponding entries in the PDF
		 document page's dictionary. Implicitly creates a new PDEContent for 
		 the page and adds it to the doc port's internal content stack.
		 
		 Note: This opens a new page context that must be closed by a matching 
		 call to endpage.
		 
		 @param mediaBox	IN The media box for the page, as per the PDF spec
		 @param bleedBox	IN The bleed box for the page, as per the PDF spec
		 @param trimBox		IN The trim box for the page, as per the PDF spec
		 @param artBox		IN The art box for the page, as per the PDF spec
		 @param pageBounds	IN The page's bounds
		 @param pageBoundsToSpreadMatrix	IN The transformation matrix from the page's bounds to spread bounds
		 @param pageUID		IN The UID for the page being added
		 @param params		IN Flattener parameters for the page, if any. Used to construct TransparencyInfo for the page.
		 @param pageClipBounds	IN The bounds that the page is clipped - if nil, the rect will be empty
		 @param reverseorder IN If true, the PDF page is added to the start, rather than at the end.
		 @param pageUIDList	IN The List of UIDs of ID Pages from which this PDF page was made.
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode startpage(PMRect& mediaBox, PMRect& bleedBox,
			PMRect& trimBox, PMRect& artBox, const PMRect &pageBounds, const PMMatrix &pageBoundsToSpreadMatrix, UID pageUID, IPDFFlattenerParams *params = nil, PMRect *pageClipBounds = nil,
			bool reverseorder = false, UIDList pageUIDList = NULL, RCAnnotationMappingData *UIDToPageItemDataMapping = NULL) = 0;
		/**
		 Closes a page context opened by a prior call to startpage.
		 
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode endpage() = 0;

		/**
		 Starts a new PDEContent context that must be closed by a matching call
		 to EndPDEContent. The newly created content is added to the doc port's
		 internal content stack.
		 
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode StartPDEContent() = 0;
		
		/**
		 Ends a PDEContent context begun with a prior call to StartPDEContent,
		 and returns the content object.
		 
		 Note: The content object has been acquired and *must* be released by
		 the caller.
		 
		 @param bPDEContent	OUT Pointer to storage for the PDEContent. Must be non-nil, and returned PDEContent must be released.
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode EndPDEContent(PDEContent* bPDEContent) = 0;
		
		/**
		 Begins a new PDEForm context that must be closed by a matching call to
		 EndPDEForm or EndPDEFormCapture. Since this method does not take a bounding box
		 when the form is started, you must use a version of EndPDEForm or EndPDEFormCapture that
		 does take a bounding box. Implicitly calls StartPDEContent internally.  
		 
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode BeginPDEForm() = 0;
		/**
		 Begins a new PDEForm context that must be closed by a matching call to
		 EndPDEForm or EndPDEFormCapture. The form bounding box is saved off, so you should call
		 the EndPDEForm or EndPDEFormCapture method that does not take a bounding box parameter.
		 Implicitly calls StartPDEContent internally.
		 
		 @param formBBox					IN The bounding box for the form
		 @param annotationAppearanceStream	IN Flag: kTrue if the form being created for an annotation appearance stream, else kFalse
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode BeginPDEForm(const PMRect& formBBox, const bool& annotationAppearanceStream = false) = 0;
		
		/**
		 Ends a form context begun by a prior call to BeginPDEForm, that passed the formBBox parameter.
		 Implicitly calls EndPDEContent internally. The form is implicitly added to the
		 current content.
		 
		 Note: The annotationAppearanceStream *must* be the same value passed 
		 to BeginPDEForm. Failure to do this will result in incorrect handling 
		 of the form's bounds.
		 
		 @param annotationAppearanceStream	IN Flag: kTrue if the form being created for an annotation appearance stream, else kFalse
		 @return ErrorCode indicating success or failure of the call
		 @see EndPDEFormCapture
		 */
		virtual ErrorCode EndPDEForm(const bool& annotationAppearanceStream = false) = 0;
		/**
		 Ends a form context begun by a prior call to BeginPDEForm, that did not pass a formBBox parameter.
		 Implicitly calls EndPDEContent internally. The form is implicitly added to the
		 current content.
		 		 
		 @param formBBox	IN The bounding box for the form
		 @return ErrorCode	indicating success or failure of the call
		 @see EndPDEFormCapture
		 */
		virtual ErrorCode EndPDEForm(PMRect& formBBox) = 0;
		
		/**
		 Retrieves the PDDoc owned by this object. The returned document has 
		 not been acquired and must *not* be released by the caller.
		 
		 @return The PDDoc owned by the doc port
		 */
		virtual const PDDoc &GetPDDoc() = 0;
		
		/**
		 Retrieves the current PDPage owned by this object. The returned page 
		 has not been acquired and must *not* be released by the caller.
		 
		 @return The current PDPage owned by the doc port
		 */		 
		virtual const PDPage &GetPDPage() = 0;
		
		/**
		 Retrieves the bounds for the current page.
		 
		 @return The bounds for the current page in spread coordinate space
		 */
		virtual PMRect GetPageBounds() const = 0;
		
		/**
		 Retrieves the matrix that transforms the page bound to spread coordinates.
		 
		 @return The matrix to transform the current page bounds to spread coordinate space
		 */
		virtual PMMatrix GetPageboundsToSpreadMatrix() const = 0;

		/**
		 Retrieves the bounds that the current page is being clipped. If nil
		 is passed into startpage for this variable, the rect will be empty. 
		 
		 @return The clip bounds for the current page in PDF coordinate space
		 */
		virtual PMRect GetPageClipBounds() const = 0;
		
		/**
		 Adds the specified PDEElement to the current PDEContent item (ie. the
		 one most recently added to the internal content stack).
		 
		 @param element		IN The PDEElement to add
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode AddElementToContent(PDEElement element) = 0;
		
		/**
		 Adds the specified PDPage to the current PDEContent as an XObject 
		 form.
		 
		 @param shape		IN The shape to extract metadata from
		 @param pdfPage		IN The page to add
		 @param m			IN Additional matrix to apply to page
		 @param cropRect	IN The destination bounding box for the page
		 @param srcFilePath	IN Used to fill in file spec constructed for page's Ref dictionary
		 @return ErrorCode indicating success or failure of the call
		 @see AddPageToContentRes
		 */
		virtual ErrorCode AddPageToContent(IShape* shape, PDPage pdfPage, PMMatrix& m, PMRect& cropRect,
			PMString& srcFilePath) = 0;
		
		/**
		 Creates thumbnails for the PDF file being generated. Should be called
		 at the end of the export session, just before enddoc is called.
		 
		 Note: Will be called implicitly from within enddoc if the export prefs
		 used indicate that thumbnails should be generated.

		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode CreateThumbs() = 0;

		/**
		 Creates OPI dictionary for the specified image.
		 
		 @param	omitBBox		IN The bounding box for the image, if required (may be nil)
		 @param	imageElement	IN The PDEElement to which the OPI dictionary is attached
		 @param image			IN The AGM image for which OPI is being added
		 @param imageCs			IN The image's colorspace, for colorized grayscale cases (may be nil)
		 @param imageFlags		IN The flags specified when the image was drawn
		 @param newElement		OUT Pointer to storage for the newly created PDEElement for the OPI
		 @param imageMatrix		IN Matrix required to position unit square in default coord space
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode CreateOPIContent(
			PMRect* omitBBox, 
			PDEElement imageElement, 
			AGMImage* image, 
			AGMColorSpace* imageCs, 
			int32 imageFlags, 
			PDEElement *newElement,
			PMMatrix const &imageMatrix
		) = 0;

		/**
		 Adds OPI using OPI information from an AGM OPI object.
		 
		 Note: For internal use only
		 
		 @param objRect			IN The bounds of the object
		 @param pdfPage			IN The page to which the Ref dictionary is attached (may be nil)
		 @param opiServer		IN The OPI object to use
		 @param matrix			IN Matrix required to position objRect in default coord space
		 @return ErrorCode indicating success or failure of the call
		 @see AddOPIToContentRes
		 */		 
		virtual ErrorCode AddOPIToContent(
			PMRect objRect, 
			PDPage pdfPage,
			CAGMOPI& opiServer,
			PMMatrix const &matrix
		) = 0;

		/**
		 Creates a new CosDict containing the OPI information for the specified
		 image.
		 
		 @param srcElement		IN Currently unused
		 @param image			IN The image for which OPI is generated
		 @param imageCs			IN The colorspace to use, for colorized grayscale
		 @param imageFlags		IN The flags with which the image was drawn
		 @param opiObject		OUT The newly created CosDict for the OPI
		 @param imageMatrix		IN Matrix required to position unit square in default coord space
		 */
		virtual ErrorCode CreateOPIObject(
			PDEElement srcElement,
			AGMImage* image, 
			AGMColorSpace* imageCs, 
			int32 imageFlags, 
			CosObjPtr opiObject,
			PMMatrix const &imageMatrix
		) = 0;
		
		/**
		 Sets the current export document. For book export, this is used to set
		 the document for each page in the book.
		 
		 @param pExportDoc		IN The current export document
		 */
		virtual void SetExportDocument(IDocument* pExportDoc) = 0;
		
		/**
		 Retrieves the current export document
		 
		 @return The current export document
		 */
		virtual IDocument* GetExportDocument() = 0;
		
		/**
		 Sets the current document's metadata.
		 
		 @param metaData		IN The current document's metadata
		 @see IMetaData
		 */
		virtual void SetExportDocumentMetaData(IMetaData* metaData) = 0;
		
		/**
		 Retrieves the current document's metadata
		 
		 @return The current document's metadata
		 @see IMetaData
		 */
		virtual IMetaData* GetExportDocumentMetaData() const = 0;

		/**
		 Adds the specified PDPage to the current PDEContent as an XObject 
		 form.
		 
		 @param shape		IN The shape to extract metadata from
		 @param pdfPage		IN The page to add
		 @param m			IN Additional matrix to apply to page
		 @param cropRect	IN The destination bounding box for the page
		 @param srcFilePath	IN Used to fill in file spec constructed for page's Ref dictionary
		 @param db			IN Database used to access font information (currently unused)
		 @param pageItemUID	IN Pageitem used to access font information (currently unused)
		 @return ErrorCode indicating success or failure of the call
		 @see AddPageToContent
		 */
		virtual ErrorCode AddPageToContentRes(IShape* shape, PDPage pdfPage, PMMatrix& m, PMRect& cropRect,
			PMString& srcFilePath, IDataBase *db, UID pageItemUID) = 0;
			
		/**
		 Adds OPI using OPI information from an AGM OPI object.
		 
		 Note: For internal use only
		 
		 @param objRect			IN The bounds of the object
		 @param pdfPage			IN The page to which the Ref dictionary is attached (may be nil)
		 @param opiServer		IN The OPI object to use
		 @param matrix			IN Matrix required to position objRect in default coord space
		 @param db				IN Database used to access font information (currently unused)
		 @param pageItemUID		IN Pageitem used to access font information (currently unused)
		 @return ErrorCode indicating success or failure of the call
		 @see AddOPIToContent
		 */		 
		virtual ErrorCode AddOPIToContentRes(
			PMRect objRect, 
			PDPage pdfPage,
			CAGMOPI& opiServer, 
			IDataBase *db, 
			UID pageItemUID,
			PMMatrix const &matrix
		) = 0;
		
		/** 
		 Sets the binding for the document.
		 
		 @param binding		IN The page binding to use (see ILayoutUtils.h DocPageBinding for values)
		 @return ErrorCode indicating success or failure of the call
		 @see ILayoutUtils
		 */
		virtual ErrorCode SetDocumentBinding(int32 binding) = 0;

		/** 
		 Begins a new PDEGroup context. The context must be closed with a 
		 matching call to EndPDEGroup.
		 
		 Note: Implicitly creates a new PDEContent and pushes it on internal 
		 content stack.
		 
		 @param formBBox		IN The bounds for the implicitly created form
		 @param group			IN The group to begin
		 @param isMask			IN Flag: kTrue if group represents a mask
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode BeginPDEGroup(const PMRect& formBBox, PDEXGroup group, bool16 isMask) = 0;

		/**
		 Ends a PDEGroup context begun by a prior call to BeginPDEGroup
		 
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode EndPDEGroup() = 0;
		
		/**
		 Ends a form context begun by a prior call to BeginPDEForm, that passed a formBBox parameter.
		 Implicitly calls EndPDEContent internally.
		 
		 Note: The annotationAppearanceStream *must* be the same value passed 
		 to BeginPDEForm. Failure to do this will result in incorrect handling 
		 of the form's bounds.
		 
		 This does essentially the same thing as EndPDEForm, but does not 
		 implicitly add the form to the current content. It also returns the 
		 captured form.
		 
		 @param annotationAppearanceStream	IN Flag: kTrue if the form being created for an annotation appearance stream, else kFalse
		 @return The captured PDEForm, or nil if fails
		 @see EndPDEForm
		 */
		virtual PDEForm	  EndPDEFormCapture(const bool& annotationAppearanceStream = false) = 0;
		/**
		 Ends a form context begun by a prior call to BeginPDEForm, that did not pass a formBBox parameter.
		 Implicitly calls EndPDEContent internally.
		 
		 This does essentially the same thing as EndPDEForm, but does not 
		 implicitly add the form to the current content. It also returns the 
		 captured form.
		 
		 @param formBBox	IN The bounding box for the form
		 @return The captured PDEForm, or nil if fails
		 @see EndPDEForm
		 */
		virtual PDEForm	  EndPDEFormCapture(PMRect& formBBox) = 0;

		/**
		 Releases a form that was created by EndPDEContent to prevent a leak. The form
		 is zeroed out after being released.
		 		 
		 @param pdeForm	IN a reference to the form to be released
		 @see EndPDEFormCapture
		 */
		virtual void	  ReleasePDEForm(PDEForm& pdeForm) = 0;

		/**
		 Begins an annotation context. The context must be closed by a matching
		 call to EndAnnotation.
		 
		 @param pageItem		IN The page item for which annotation is being created
		 @param annotBBox		IN The bounding box for the annotation
		 @param lineWidth		IN Used to calculate the bounding box for the annotation and form created internally
		 @param subtype			IN The subtype for the annotation
		 @param pageBounds		IN The bounds of the page. Used to calculate the bounding box for the annotation
		 @param beginForm		IN Indicates if appearance stream (PDEForm) should be started alongwith
		 @param annotP			OUT The created PDF annotation object
		 */
		virtual ErrorCode BeginAnnotation(const IPMUnknown* pageItem, const PMRect& annotBBox, PMReal lineWidth,
			const PMString& subtype, const PMRect& pageBounds, bool16 beginForm, PDAnnotPtr annotP) = 0;
		
		/**
		 Ends an annotation context begun by a prior call to BeginAnnotation.
		 
		 @param flags			IN The flags written to the annotation dictionary
		 @param addPageObjRef	IN Whether to add a reference to the page object the annotation is associated with
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode EndAnnotation(int32 flags = -1, bool16 addPageObjRef = kFalse) = 0;

		/**
		 Begins an annotation context, tuned for InCopy. The context must be 
		 closed by a matching call to EndAnnotation.
		 
		 Note: This implicitly calls BeginPDEForm.
		 
		 @param annotBBox		IN The bounding box for the annotation
		 @param lineWidth		IN Used to calculate the bounding box for the form created internally
		 @param subtype			IN The subtype for the annotation
		 @param pageBounds		IN The bounds of the page. Used to calculate the bounding box for the annotation
		 */
		virtual ErrorCode BeginNoteAnnotation(const PMRect& annotBBox, PMReal lineWidth, PMString& subtype, 
			const PMRect& pageBounds) = 0;
			
		/**
		 Ends an annotation context begun by a prior call to BeginNoteAnnotation.
		 
		 @param flags			IN The flags written to the annotation dictionary
		 @param title			IN The title to write to the annotation dictionary, if non-nil
		 @param content			IN The content string to write to the annotation dictionary, if non-nil
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode EndNoteAnnotation(int32 flags, PMString *title, PMString *content) = 0;

		/**
		 Begins a new marked content context. The context must be closed by a
		 matching call to EndMarkedContent.
		 
		 Note: Implicitly calls StartPDEContent.
		 
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode BeginMarkedContent() = 0;
		
		/**
		 Ends a marked content context begun by a prior call to 
		 BeginMarkedContent.
		 
		 @param shape			IN Used to access metadata for the marked content
		 @param contentName		IN The name of the content
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode EndMarkedContent(IShape *shape, PMString& contentName) = 0;
		
		/**
		 Sets flag indicating whether to mute generation of page item structure.

		 @param mute		IN Flag indicating whether to mute page item structure
		 @return The prior value of the mute page item structure flag
		 */
		virtual bool16 MutePageItemStructure(const bool16& mute = kTrue) = 0;
		
		/**
		 Retrieves the value of the flag indicating whether to mute generation of 
		 page item structure.
		 
		 @return The value of the mute page item structure flag
		 */
		virtual bool16 IsPageItemStructureMuted() const = 0;

		/**
		 @return the topmost PDEContent from the doc port's internal content stack
		 */
		virtual PDEContent GetPDEContent() const = 0;
		
		/*
		 Adds the specified shape to the document metadata's link table
		 */
		virtual void AddLinkedResourceToDocMetadata(IShape const *shape) = 0;

		/*
		 Adds the page transition that is defined for the specified spread
		 */
		virtual ErrorCode AddPageTransition(const UIDRef& spreadUIDRef) = 0;

		/**
		 Get the annotation (created using BeginAnnotation) for a page item.
		 This is useful when the annotation is required in a context different from the one in
		 which BeginAnnotation was called.

		 @param pageItem		IN The page item for which annotation is required.
		 @param pdfPageNum		IN The pdf page number on which the annotation is required.
		                           Page items can create annotations on multiple pages of the PDF.
		 @param annotID			OUT An integer identifier for the annotation.
		 @return ErrorCode indicating success or failure of the call.
		 */
		virtual ErrorCode GetAnnotationID(const IPMUnknown* pageItem, int32 pdfPageNum, int32* annotID) = 0;

		/**
		 Returns the PDF annotation object from its integer identifier.
		 
		 @param annotID		IN The identifier for the annotation (returned in the GetAnnotationID api)
		 @param page		OUT The PDF page for the annotation.
		 @param annot		OUT The PDF annotation object.
		 @return ErrorCode indicating success or failure of the call.
		 */
		virtual ErrorCode GetAnnotation(int32 annotID, CosObjPtr page, PDAnnotPtr annot) = 0;

		/**
		 Closes a page context opened by a prior call to startpage.
		 
		 @param pageHasXP		IN Boolean indicating if the page has transparency which hasn't been flattened.
		 @return ErrorCode indicating success or failure of the call
		 */
		virtual ErrorCode endpage2(bool16 pageHasXP) = 0;

		/**
		 Set the page clip bounds.
		 
		 @param pageBounds		IN PMRect page bounds used to set the bbox of form objects.
		 @return none
		 */
		virtual void SetPageClipBounds(const PMRect& pgClipBounds) = 0;

		/**
		 Set whether to suppress creation of PDF form xobjects for master page items.
	 
		 @param suppress		IN Pass true to suppress creation of PDF form xobjects.
		 @return none.
		 */
		virtual void SetSuppressFormXObjects(bool suppress) = 0;

		/**
		 Return whether PDF form xobjects creation is suppressed.
		 
		 @param none.
		 @return bool indicating if PDF form xobjects creation is suppressed or not.
		 */
		virtual bool GetSuppressFormXObjects() const = 0;
	
		/**
		return the clip rect to be applied on master form xobjects 
		 
		 @param none.
		 @return PMRect - clip rect to be applied on master form xobjects.
		 */
		virtual PMRect GetMasterClipRect() const = 0;

		/**
		set the clip rect to be applied on master form xobjects 
		 
		 @param PMRect -clip rect to be applied on master form xobjects
		 @return none
		 */
		virtual void SetMasterClipRect(const PMRect& clipRect) = 0;

};
#endif
