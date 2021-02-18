//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAnnotationUtils.h $
//  
//  Owner: Sumit Pandey 
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2020 Adobe
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe .
//  
//========================================================================================


#pragma once
#ifndef __IAnnotationUtils__
#define __IAnnotationUtils__

#include "PDFID.h"

#include "UIDList.h"

#include "AnnotationItem.h"
#include "itextRangeNode.h"
#include "ITextRangeList.h"

#include "IDocument.h"
#include <list>
class ITextModel;

class IAnnotationUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANNOTATIONUTILS };

	/** Given a uidList of page/pageitems return UID list of all import PDF annotation linked to these page/pageitems.

	@param uidList - list of page/pageitems
	@return UIDList  - uidList of all annotations linked to page/pageitems list
    @param bIsSortByTimeStamp - true means sort the annotation list by time stamp
    @return includeTextRanges - false means do not get all the text ranges on the pageitem if it is a text frame
	*/
    virtual UIDList GetListOfImportPDFAnnotUIDOnPageOrPageItems(const UIDList &uidList, bool bIsSortByTimeStamp = false, bool includeTextRanges = true) = 0;

	/** Given a uidList of page/pageitems return UID list of all share for review annotation linked to these page/pageitems.

	@param uidList - list of page/pageitems
	@return UIDList  - uidList of all annotations linked to page/pageitems list
	@param bIsSortByTimeStamp - true means sort the annotation list by time stamp
	@return includeTextRanges - false means do not get all the text ranges on the pageitem if it is a text frame
	*/
	virtual UIDList GetListOfShare4ReviewAnnotUIDOnPageOrPageItems(const UIDList &uidList, bool bIsSortByTimeStamp = false, bool includeTextRanges = true) = 0;

	/** Given a text range return UID list of all annotation linked to this text range
	@param *model - The text model to look at
	@param start - The start of the range
	@param end - The end of the range 
	@param bIsSortByTimeStamp - true means sort the annotation list by time stamp
	@return UIDList  - uidList of all annotations linked to given text range
	*/
	virtual UIDList GetListOfAnnotUIDOnTextRange(ITextModel *model, TextIndex start, TextIndex end, bool bIsSortByTimeStamp = false) = 0;
    
    /** Given a document return UID list of all annotations that are orphan and hence have been mapped to this document
     @param doc - The UIDRef of the document
     */
    virtual UIDList GetListOfAnnotUIDMappedToDoc(const UIDRef &doc) = 0;

	/**	Deletes annotation. This method deletes the specified annotation object and disassociate the annotation with corresponding annotation destination.
	We delete the associated destination as well because there can only be one annotation referencing a destination.
	@param annotUIDRef - UIDRef of annotation to be deleted.
	@return ErrorCode - result of the operation.
	*/
	virtual ErrorCode DeleteAnnotation(const UIDRef &annotUIDRef) = 0;

	/**	Deletes annotation list. 
	@param annotList - annotation list to be deleted.
	*/
	virtual ErrorCode DeleteAnnotationList(const UIDList &annotList) = 0;

	/**	Change the  annotation status.

	@param annotation - annotation to be changed.
	@param newStatus - new Status for the annotation.

	@return ErrorCode - result of the operation.
	*/
	virtual ErrorCode ChangeAnnotationStatus(const UIDRef &annotation, const AnnotationStatus &newStatus) = 0;

	/** Given the annotation UID it fills the structure AnnotationItem with complete data of annotation.

	@param annotation - annotation to be read.
	@param annotData - structure AnnotationItem which will be filled by annotation Data
	*/
	virtual void ReadAnnotationData(const UIDRef &annotUIDRef, AnnotationItem &annotData) = 0;
};

#endif // __IAnnotationUtils__
