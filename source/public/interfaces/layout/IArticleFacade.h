//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IArticleFacade.h $
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
#ifndef _IARTICLEFACADE_
#define _IARTICLEFACADE_

#include "ArticleID.h"
#include "UIDList.h"

namespace Facade
{
	class IArticleFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IARTICLEFACADE };

	public:

		/** Create an Article with the specified name. Does not add it to the document.
			@param database IN the database in which the Article is created.
			@param name IN The name of the Article.
			@return UID of the created Article.
		*/
		virtual UID CreateArticle(IDataBase* database , const PMString& name) = 0;	

		/** Add Article(s) to a document at the specified position.
			@param articleList IN the UIDList of Articles to be added.
			@param pos IN 0 based position at which to add the Articles. Specify -1 to add to the end.
			@return kSuccess if the Article was successfully added, else an error code.
		*/
		virtual ErrorCode AddArticle(const UIDList& articleList , int32 pos = -1) = 0;
		
		/** Create and Add an Article to the document.
			@param database IN the database in which the Article is created and added.
			@param name IN The name of the Article.
			@param pos IN 0 based position at which to add the Articles. Specify -1 to add to the end.
			@return UID of the added Article.
		*/
		virtual UID CreateAndAddArticle(IDataBase* database, const PMString& name, int32 pos = -1) = 0;
		
		/** Remove Articles from a Document. Does not delete the Articles.
			@param articleList IN The UIDList of Articles to be removed.
			@return kSuccess if the Articles were successfully removed, else an error code.
		*/
		virtual ErrorCode RemoveArticles(const UIDList& articleList) = 0;
		
		/** Delete Articles from a Document.
			@param articleList IN The UIDList of Articles to be deleted.
			@return kSuccess if the Articles were successfully deleted, else an error code.
		*/
		virtual ErrorCode DeleteArticle(const UIDList& articleList) = 0;
		
		/** Move Articles to new position within the same document.
			@param articleList IN The UIDList of Articles to be moved.
			@param toPos IN 0 based starting position at which the Articles will be moved.
			@return kSuccess if the Articles were successfully moved, else an error code.
		*/
		virtual ErrorCode MoveArticles(const UIDList& articleList, int32 toPos) = 0;
		
		/** Set the name of an Article.
			@param articleList IN The UIDList of Articles to be moved.
			@param name IN The name of the Article.
			@return kSuccess if the Article was successfully named, else an error code.
		*/
		virtual ErrorCode SetArticleName(const UIDRef& article, const PMString& name) = 0;

		/** Set the export status of an Article.
		@param articleList IN The UIDList of Articles whose export status needs to be changed.
		@param useForExport IN ktrue if the articles should be used for export, kFalse otherwise.
		@return kSuccess if the Articles export status were successfully changed, else an error code.
		*/
		virtual ErrorCode SetArticleExportStatus(const UIDList& articleList, bool16 useForExport) = 0;

		/** Add members to an Article at the specified position.
			@param article IN The article to which members need to be added.
			@param memberList IN The ordered list of members that need to be added.
			@param pos IN 0 based starting position at which the members will be added. Specify -1 to add to the end.
			@return kSuccess if the members were successfully added, else an error code.
		*/
		virtual ErrorCode AddMembers(const UIDRef& article, const UIDList& memberList, int32 pos = -1) = 0 ;
		
		/** Utility method to Auto Populate Articles with page items of the entire document.
			@param articleList IN the articles which need to be auto-populated.
			@return kSuccess if the members were successfully added, else an error code.
		*/
		virtual ErrorCode AutoPopulateArticle(const UIDList& articleList) = 0;

		/** Remove members from an Article.
			@param article IN The article from which the members need to be removed.
			@param memberList IN The list of members that need to be removed.
			@return kSuccess if the members were successfully removed, else an error code.
		*/
		virtual ErrorCode RemoveMembers(const UIDRef& article, const UIDList& memberList) = 0 ;
		
		/** Move members to new position within the same Article.
			@param memberList IN The members that need to be moved.
			@param toPos IN 0 based starting position at which the members will be moved. Specify -1 to move to the end.
			@return kSuccess if the members were successfully moved, else an error code.
		*/
		virtual ErrorCode MoveMembers(const UIDRef& article, const UIDList& memberList, int32 toPos = -1) = 0 ;

		/** Add children at the specified position in a Group.
			@param group IN the group to which the children need to be added.
			@param childList IN the children that need to be added.
			@param pos IN 0 based position at which to add the children. Specify -1 to add to the end.
			@return kSuccess if the children were successfully added, else an error code.
		*/	
		virtual ErrorCode AddChildren(const UIDRef& group, const UIDList& childList, int32 pos = -1) = 0 ;
		
		/** Remove children from a Group.
			@param group IN the group from which the children need to be removed.
			@param childList IN the children that need to be removed.
			@return kSuccess if the children were successfully removed, else an error code.
		*/
		virtual ErrorCode RemoveChildren(const UIDRef& group, const UIDList& childList) = 0 ;
		
		/** Move children within a Group.
			@param group IN the group in which the children need to be moved.
			@param childList IN the ordered list of children that need to be moved.
			@param pos IN 0 based position at which to move the children. Specify -1 to move to the end.
			@return kSuccess if the children were successfully moved, else an error code.
		*/
		virtual ErrorCode MoveChildren(const UIDRef& group, const UIDList& childList, int32 toPos = -1) = 0 ;

	};
}
#endif // _IARTICLEFACADE_