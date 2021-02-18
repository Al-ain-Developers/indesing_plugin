//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AnnotationPage.h $
//
//  Owner: Souvik Sinha Deb
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __AnnotationPage__
#define __AnnotationPage__

// Annotation  Page Class -- implements a page of the InDesign Document with it's list of all associated annotations.
#include "AnnotationItem.h"

typedef UID AnnotationPageID;

class PUBLIC_DECL AnnotationPage
{
public:
	/** Sets the information of a particular page of the document.
	*/
	AnnotationPage();

	/** Sets the PageID of a particular page of the document.
		@param annotPageid IN is the page's unique ID 
	*/
	virtual void SetAnnotationPageID(const AnnotationPageID& annotPageID);

	/** Gets the PageID of a particular page of the document.
		@param annotPageid OUT is the page's unique ID 
	*/
	virtual void GetAnnotationPageID(AnnotationPageID& annotPageID) const;

	/** Sets the List of Associated Annotations of a particular page of the document.
		@param annotations IN is the page's collection of all annotation. 
	*/
	virtual void SetListOfAnnotationsInPage(const std::vector<std::shared_ptr<AnnotationItem>>& annotations);

	/** Gets the List of Associated Annotations of a particular page of the document.
		@param annotations OUT is the page's collection of all annotation. 
	*/
	virtual void GetListOfAnnotationsInPage(std::vector<std::shared_ptr<AnnotationItem>>& annotations) const;

	/** Appends a List of Annotations to a particular page of the document.
	@param annotations IN is the page's collection of all annotation.
	*/
	virtual void AppendListOfAnnotationsToPage(const std::vector<std::shared_ptr<AnnotationItem>>& annotations);

private:
    /** The AnnotationPage ID is its UID in the document
     */
	AnnotationPageID fAnnotPageID;
    /** The list of Annotation Items on a Page of ID document
    */
	std::vector<std::shared_ptr<AnnotationItem>> fAnnotations;
};

#endif //__AnnotationPage__
