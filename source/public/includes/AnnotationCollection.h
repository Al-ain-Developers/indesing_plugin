//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AnnotationCollection.h $
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
#ifndef __AnnotationCollection__
#define __AnnotationCollection__

// Annotation  Collection Class -- implements a collection of all annotations belonging to a particular document.

#include "AnnotationItem.h"
#include "AnnotationPage.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

typedef std::string AnnotationCollectionID;

class PUBLIC_DECL AnnotationCollection
{
public:
	/** Sets the information of a particular collection of annotations related to a single document.
	*/
	AnnotationCollection();

	/** Sets the DocumentUID of a particular collection of annotations related to a single document.
		@param docID IN is the collection's associated document ID.
     */
	//virtual void SetAnnotationCollectionDocumentUID(const UID& docID);
    
    /** Gets the DocumentUID of a particular collection of annotations related to a single document.
     @param docID OUT is the collection's associated document ID.
     */
    //virtual void GetAnnotationCollectionDocumentUID(UID& docID);

	/** Gets the Collection of a particular collection of annotations related to a single document.
		@param uid OUT is the collection's unique ID 
	*/
	virtual void GetAnnotationCollectionID(AnnotationCollectionID& annotCollectionid) const;

	/** Sets the Number of Annotations of a particular collection of annotations related to a single document.
		@param totalNumberOfAnnotationsPresent IN is the total number of annotations present in the collection.
     */
	//virtual void SetNumberOfAnnotationsInDocument(const int& totalNumberOfAnnotationsPresent);

	/** Gets the Number of Annotations of a particular collection of annotations related to a single document.
		@param totalNumberOfAnnotationsPresent OUT is the total number of annotations present in the collection.
	*/
	//virtual void GetNumberOfAnnotationsInDocument(int& totalNumberOfAnnotationsPresent);

	/** Sets the List of Pages of a particular collection of annotations related to a single document.
		@param pages IN is the collection's list of pages with relevant annotations.
	*/
	virtual void SetListOfPagesInCollection(const std::vector<std::shared_ptr<AnnotationPage>>& pages);

	/** Gets the List of Pages of a particular collection of annotations related to a single document.
		@param pages OUT is the collection's list of pages with relevant annotations.
	*/
	virtual void GetListOfPagesInCollection(std::vector<std::shared_ptr<AnnotationPage>>& pages) const;

	/** Appends a List of Pages to a particular collection of annotations related to a single document.
	@param pages IN is the collection's list of pages with relevant annotations.
	*/
	virtual void AppendListOfPagesToCollection(const std::vector<std::shared_ptr<AnnotationPage>>& pages);

private:
    /** The List of Annotation Pages for a collection
     */
	std::vector<std::shared_ptr<AnnotationPage>> fPages;
	//int fTotalNumberOfAnnotations;
	//UID fDocID;
    /** The AnnotationCollectionID is a randomly generated UUID
     */
	AnnotationCollectionID fAnnotCollectionID;//-Required
};

#endif //__AnnotationCollection__
