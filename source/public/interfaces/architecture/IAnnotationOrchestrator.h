//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAnnotationOrchestrator.h $
//  
//  Owner: Mudit Rastogi
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
//  IAnnotation is the abstract interface to a annotation
//  
//========================================================================================

#pragma once
#ifndef __IAnnotationOrchestrator__
#define __IAnnotationOrchestrator__

#include "IPMUnknown.h"
#include "PDFID.h"
#include <list>

class IDocument;
class PMString;
class AnnotationCollection;
class AnnotationItem;

class IAnnotationOrchestrator : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IANNOTATIONORCHESTRATOR };


	/*	Import the annotations from a filepath. Importing involves steps such as fetching of comments, mapping them into ID space and saving into target document object model.
		@param targetDoc IN - the target document where comments will be imported and persisted
		@param sourceExtension IN - the extension of source file
		@param filePath IN - the path of file from where annotations need to be imported
	*/
	virtual ErrorCode ImportAnnotations(IDocument* targetDoc, const char * sourceExtension, const char * filePath) = 0;


	/*	Import the annotations from filepathList, thus enabling batch import of annotations. Importing involves steps such as fetching of comments, mapping them into ID space and saving into target document object model.
	@param targetDoc IN - the target document where comments will be imported and persisted
	@param sourceExtension IN - the extension of source file
	@param filePathList IN - the list of file paths from where annotations need to be imported
	*/
	virtual ErrorCode ImportAnnotations(IDocument* targetDoc, const char * sourceExtension, const std::vector<const char*> & filePathList) = 0;

	/*	Import the annotations directly from list of annotations. Importing involves mapping all the given annotations into ID space and saving into target document object model.
	@param targetDoc IN - the target document where comments will be imported and persisted
	@param annotCollection IN - collection of all annotations
	*/
	virtual void ImportAnnotations(IDocument* targetDoc, AnnotationCollection& annotCollection) = 0;

	/*	Map the annotation directly to given page and save into target document object model.
	@param pageRef IN - the UIDRef of target page
	@param annotItem IN - annotation which will be mapped to page
	*/
	virtual ErrorCode AddAnnotationToPage(const UIDRef &pageRef, const AnnotationItem &annotItem) = 0;

	/*	Map the annotation directly to given page item and save into target document object model.
	@param pageItemRef IN - the UIDRef of target page item
	@param annotItem IN - annotation which will be mapped to page item
	*/
	virtual ErrorCode AddAnnotationToPageItem(const UIDRef &pageItemRef, const AnnotationItem &annotItem) = 0;

	/*	Map the annotation directly to given text range and save into target document object model.
	@param textUIDRef IN - the UIDRef of target text frame model
	@param startIndex IN - start index of text range
	@param endIndex IN - end index of text range
	@param annotItem IN - annotation which will be mapped to text range
	*/
	virtual ErrorCode AddAnnotationToTextRange(const UIDRef &textUIDRef, const TextIndex &startIndex, const TextIndex &endIndex, const AnnotationItem &annotItem) = 0;

	/*	Map the annotation list directly to given page and save into target document object model.
	@param pageRef IN - the UIDRef of target page
	@param annotItemList IN - annotation list which will be mapped to page
	*/
	virtual void AddAnnotationListToPage(const UIDRef &pageRef, const std::list<AnnotationItem*> &annotItemList) = 0;

	/*	Map the annotation list directly to given page item and save into target document object model.
	@param pageItemRef IN - the UIDRef of target page item
	@param annotItemList IN - annotation list which will be mapped to page item
	*/
	virtual void AddAnnotationListToPageItem(const UIDRef &pageItemRef, const std::list<AnnotationItem*> &annotItemList) = 0;

	/*	Map the annotation list directly to given text range and save into target document object model.
	@param textUIDRef IN - the UIDRef of target text frame model
	@param startIndex IN - start index of text range
	@param endIndex IN - end index of text range
	@param annotItemList IN - annotation list which will be mapped to text range
	*/
	virtual void AddAnnotationListToTextRange(const UIDRef &textUIDRef, TextIndex startIndex, TextIndex endIndex, const std::list<AnnotationItem*> &annotItemList) = 0;
    
    /*    Import the annotations from the review collaboration json data. Importing involves mapping all the given annotations into ID space and saving into target document object model.
     @param targetDoc IN - the target document where comments will be imported and persisted
     @param commentData IN - Json data from commenting component
     */
    virtual ErrorCode ImportRCAnnotations(IDocument* targetDoc, const std::string& commentData) = 0;

	/*    Refresh annotation from cache.
	 @param targetDoc IN - the target document where comments will be imported and persisted
	 */
	virtual ErrorCode RefreshRCAnnotationsFromCache(IDocument* targetDoc) = 0;
};

#endif //__IAnnotationOrchestrator__
