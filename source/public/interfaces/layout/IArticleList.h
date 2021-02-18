//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IArticleList.h $
// 
//  Owner: Paresh Goel
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IARTICLELIST__
#define __IARTICLELIST__

#include "IPMUnknown.h"
#include "ArticleID.h"


/** Provides access to the Articles inside a document
*/

class IArticleList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IARTICLELIST };
	
	/** Add an Article at the specified position in the document's Article List.
		@param articleUID IN the UID of the Article that needs to be added.
		@param pos IN 0 based position at which to add the Article. Specify -1 to add to the end.
	*/
	virtual void AddArticle(UID articleUID, int32 pos = -1) = 0 ;

	/** Remove an Article from the document's Article List.
		@param articleUID IN the UID of the Article that needs to be removed.
	*/
	virtual void RemoveArticle(UID articleUID) = 0 ;
	
	/** Remove an Article from the document's Article List.
		@param pos IN the position of the Article in the document's Article List.
	*/
	virtual void RemoveNthArticle(int32 pos) = 0 ;
	
	/** Remove all Articles from the document's Article List.
	*/
	virtual void RemoveAllArticles() = 0 ;

	/** Get the number of Articles in the document's Article List.
		@return the number of Articles.
	*/	
	virtual int32 CountArticles() const = 0 ;
	
	/** Get the Nth Article UID from the document's Article List.
		@param pos IN the 0 based index of the Article in the document's Article List.
		@return the UID of the Article.
	*/
	virtual UID GetNthArticleUID(int32 pos) const = 0 ;
	
	/** Get the position of the Article in the document's Article List.
		@param articleUID IN the UID of the Article in the document's Article List.
		@return the position of the Article.
	*/
	virtual int32 GetArticlePosition(UID articleUID) const = 0 ;
};

#endif // __IARTICLELIST__
