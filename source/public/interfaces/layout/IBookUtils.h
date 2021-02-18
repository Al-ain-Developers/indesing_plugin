//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookUtils.h $
//  
//  Owner: Yeming Liu, (Bernd Paradies: generalized from BookUtils.h).
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
#ifndef __IBOOKUTILS__
#define __IBOOKUTILS__

#include "BookID.h"
#include "IPMUnknown.h"
#include "IDataBase.h"
#include "ISetRepaginationCmdOptions.h"
#include "PMString.h"
#include "K2Vector.h"
#include "Utils.h"

class IDocument;
class ISection;
class ICommand;
class IBook;
class IPanelControlData;
class UIDRef;
class IBookContent;


namespace BookContentStatus
{
	typedef enum  {
		kDocNormal = 0,
		kDocMising,
		kDocOutofDate,
		kDocInUse,
		kDocOpen
	} State;
}

/** Helper class to cache originally closed documents during operations (e.g., TOC/Indexing) across book.
*/
class OriginallyCloseDocInfo
{
	public:
		typedef object_type data_type;

		/** Default constructor.
		*/
		OriginallyCloseDocInfo() :
		  fCurrentOpenedDocumentList()
		  {}

		/** Copy constructor with given values.
			@param documentList IN the list of documents opened that were originally closed
			@param documentUndoList IN the corresponding list of undo state for the originally closed document
		*/
		OriginallyCloseDocInfo(const K2Vector<UIDRef>& documentList):	
			fCurrentOpenedDocumentList(documentList)
			{}
	
		/** Equal operator for comparison.
		    @param other IN the object to compare with.
			@return bool16 kTrue means equal, otherwise kFalse.
		*/
		bool16 operator==(const OriginallyCloseDocInfo& other) const
		{ 
			return  fCurrentOpenedDocumentList == other.fCurrentOpenedDocumentList; 
		}

		void Clear()
		{
			fCurrentOpenedDocumentList.clear();
		}

		K2Vector<UIDRef> fCurrentOpenedDocumentList;
};

// The extra slop for the databases that can be opened at one session.
const int32 kOpenDatabasesBuffer = 5;

/** Utility interface with methods relating to the model side of books (kBookBoss).
	@see kUtilsBoss
	@ingroup layout_book
*/
class IBookUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBOOKUTILS };

	enum GatherPagesError
	{
		kGatherPagesSuccess,
		kGatherPagesNoEvenPages,
		kGatherPagesNoOddPages
	};

	/**	Get the status (normal, missing, out of data, in use or open) of the document/chapter in the book.
		@param iBookContent IN the document/chapter in the book.
		@return BookContentStatus::State 
	*/
	virtual BookContentStatus::State GetBookContentStatus(IBookContent *iBookContent) = 0;

	/**	Find the corresponding document in the open document list with the given book content's UID and book's database.
		@param db IN the database of book
		@param content IN the UID of document/chapter in book database
		@param sysFile OUT the document
		@param isMissingPlugins OUT flag indicates if there is missing plugins in the document or not.
		@param bShowAlert IN flag indicates if we should show the alert related to missing plugins or not.
		@return IDocument* the corresponding document in the document list, if it returns nil means we can't find it. 
	*/
	virtual IDocument* FindDocFromContentUID(IDataBase* db, UID content, IDFile& sysFile, bool16& isMissingPlugins, bool16 bShowAlert = kFalse) = 0;

	/**	With the given document's SysFile, create an open document command without a layout window. 
		@param sysFile IN the file of the document to be open.
		@return ICommand* the command created.
	*/
	virtual ICommand* CreateOpenDocCmd(IDFile sysFile) = 0;

	/**	Modify the given section with the new section's attributes(start page number, name, marker and style).
		@param bDefaultSection IN flag indicates if this is a default section or not. 
		@param iSection IN the section that is going to be modified.
		@param newStartPageNum IN the new start page number for the section.
		@param existingName IN the new name for the section.
		@param existingMarker IN the new marker for the section.
		@param existingStyleID IN the new style for the section.
		@param bPageNumIncludeSectionPrefix IN the flag indicates if we should include section prefix when do page numbering.
		@param doNotify IN the flag indicates if we should do notification when command is done.
		@return ErrorCode the result of the command.
	*/
	virtual ErrorCode ProcessModifySectionCmd
	(
		bool16 bDefaultSection, 
		ISection* iSection, 
		int32 newStartPageNum, 
		const PMString* existingName, 
		const PMString* existingMarker, 
		ClassID existingStyleID, 
		bool16 bPageNumIncludeSectionPrefix,
		bool16 doNotify = kFalse
	) = 0;

	/**	A callback to check if user hits cancel or not in the progress bar during open book action. 
		We use stepsDone and stepCount to determine the progress of open action.
		This function is copied from DocumentUtils::DocDBCallback().
		@param stepsDone IN a variable to quantify how much we have done.
		@param stepCount IN a variable to quantify how much total we should complete. 
		@return IDataBase::DBResultCode kUserCanceled means user cancel the open action, otherwise return kNoError.
	*/
	virtual IDataBase::DBResultCode BookDBCallback(int32 stepsDone, int32 stepCount) = 0;

	/**	Check if the given document is a book chapter or not. If it is, we will pass out the 
		chapter's position in the book through param position; if it is not, we will set param position as -1.
		@param iDoc IN the given document to check.
		@param iBook IN the given book.
		@param position OUT the position of the chapter in the book.
		@return bool16 the flag indicates if the given document is book chapter or not, kTrue means it is; kFalse means it is not.
	*/
	virtual bool16 IsBookContent(IDocument* iDoc, IBook* iBook, int32& position) = 0;

	/**	Get the status of overset for each story in the given document.
		@param doc IN the given document.
		@param state a list of bool16 data corresponding to the overset status for individual stories in the document.
	*/
	virtual void GetOversetState(IDocument* doc, K2Vector<bool16>& state) = 0;

	/**	Bring up warning alert related to the the given document and alert message.
		@param sysFile IN the file that serves as a parameter in the alert message.
		@param alertMsg IN the alert message appears in the warning alert.
	*/
	virtual void AlertMessageAboutDocument(IDFile sysFile, PMString alertMsg) = 0;

	/**	Bring up warning alert related to the the given document and alert message.
		@param docFullName IN the document full name(with path) that serves as a parameter in the alert message.
		@param alertMsg IN the alert message appears in the warning alert.
	*/
	virtual void AlertMessageAboutDocument(PMString* docFullName, PMString alertMsg) = 0;

	/**	Do repagination starting from the given document/chapter position within the book. 
		By default, we do repagination from the first document/chapter in the book.
		@param bookName IN the book where we do the repagination.
		@param updateOptions IN operations to be done e.g. Repagination, Update Chapter and Paragrapgh Numbering, All @see ISetRepaginationCmdOptions
		@param position IN from which the repagination action start.
		@param bAutoConvertDocuments IN flag indicates if we should save the originally closed documents when close it.
		@return ErrorCode the result of repagination.
	*/
	virtual ErrorCode ProcessRepagination(const PMString& bookName, const ISetRepaginationCmdOptions::UpdateOptionsEnum updateOptions = ISetRepaginationCmdOptions::kUpdatePageNumbers, const int32& position = -1, const bool16& bAutoConvertDocuments = kFalse) = 0;


	/**	Get the group index of synchronization styles with the give group name.
		@param groupName IN the group name.
		@return int32 the index with the groups.
	*/
	virtual int32 GetStyleGroupNameIndex(const PMString& groupName) = 0;

	/**	Get the group name of the synchronization styles with the given index. Currently, we only support two groups: General Styles and CJK Styles.
		@param index IN the passed index.
		@return PMString the name of the group.
	*/
	virtual PMString GetStyleGroupName(int32 index) = 0;

	/**	Open a book file with a book panel as the UI representation.
		@param sysFile IN the book file to open.
		@param openedBook OUT the UIDRef of the opened book.
		@return ErrorCode kSuccess means successfully opened, otherwise return kFailure or kCancel.
	*/
	virtual ErrorCode OpenBookWithUI(const IDFile& sysFile, UIDRef *openedBook = nil) = 0;

	/**	Get the current active book in this session. If there is an active book, book name will be passed out. 
		@param bookName OUT the name of the active book.
		@return bool16 kTrue means there is active book in this session, otherwise, return kFalse.
	*/
	virtual bool16 GetActiveBookName(PMString& bookName) = 0;

	/**	Open the document without a layout window and bring up alert if document has data from missing plugins.
		@param sysFile IN the given document file.
		@param originalOpen OUT flag indicates if document is originally opened or not.
		@param isMissingPlugins OUT flag indicates if document has missing plugin data or not.
		@return IDocument* the interface pointer to the opened document.
	*/
	virtual IDocument* OpenDocAtBackground
						(
							const IDFile& sysFile, // in
							bool16& originalOpen, // out
							bool16& isMissingPlugins // out
						) = 0;


	/**	Get the position of document/chapter within the given book that from which we should start to do repagination.
		@param bookName IN the name of the given book.
		@return int32 the index of document/chapter within the given book. If it returns -1, it means the given book does not exist.
	*/
	virtual int32 GetBookRepaginateStartIndex(const PMString& bookName) = 0;

	/**	Get the first page number and page range of the given document.
		@param doc IN the given document we will get page information from.
		@param pageRange OUT the string representation of the page range like (3-10)
		@return int32 the first page number of the given document.
	*/
	virtual	int32 GetPageRange(IDocument* doc, PMString &pageRange) = 0;

	/**	Check if the give document/chapter can be added to a book or not.
		@param sysFile IN the given document/chapter that is going to be added in a book.
		@param firstPageNum OUT the integer value for the first page number of the document.
		@param pageRangeString OUT the string that represents the page range of the document.
		@return ErrorCode kSuccess means the document/chapter can be added to book, otherwise means it can not be added to book.
	*/
	virtual	ErrorCode CanDocBeAddedToBook(IDFile &sysFile, int32 *firstPageNum, PMString &pageRangeString) = 0;

	/**	Display the alert dialog with the given alert message and file name.
		@param alertString IN the given alert message.
		@param sysFile IN the file name that is used as a parameter in the alert message.
	*/
	virtual	void DisplayAlertString(PMString& alertString, IDFile& sysFile) = 0;

	/**	Replace the given book content(UIDRef in the book database) with a new document/chapter.
		@param bookContentRef IN the given book content to be replaced with.
		@param docFile IN the document/chapter to be replace by.
		@param bookFile IN the given book.
		@return ErrorCode the result for the replace action.
	*/
	virtual ErrorCode ReplaceBookContentWithNewDocument(const UIDRef& bookContentRef, const IDFile& docFile, const IDFile& bookFile) = 0;

	/**	Check if the document has any critical or default plugins missing.
		@param doc IN the given document to check.
		@return bool16 kTrue means there is one or more critical or default plugins missing; kFalse means there is not.
	*/
	virtual bool16 IsMissingCriticalOrDefaultPlugins(IDocument* doc) = 0;

	/**	Set auto conversion flag in the book.
		@param bookRef IN the book that we want to alter
		@param bAutoConvertFlag IN the new flag(either kTrue or kFalse) for auto conversion in book.
		@param bSpecialHandlingBookModifyFlag IN kTrue = we should do special handling of book modification flag when the auto convert setting is set;
		                               otherwise (kFalse) indicates don't any special handling.
		@return ErrorCode the result of this action.
	*/
	virtual ErrorCode SetAutoConvertDocument(const UIDRef& bookRef, const bool16& bAutoConvertFlag, const bool16& bSpecialHandlingBookModifyFlag = kFalse) = 0;

	/**	Set merge layers flag in the book.
		@param bookRef IN the book that we want to alter
		@param mergeLayersFlag IN the new flag(either kTrue or kFalse) for merging identical layers in book when exporting.
		@return ErrorCode the result of this action.
	*/
	virtual ErrorCode SetMergeLayersFlag(const UIDRef& bookRef, const bool16& mergeLayersFlag) = 0;

	/**	Check if the given book is created in previous version or not.
		@param iBook IN the book to check.
		@return bool16 kTrue means the book is created in previous version, kFalse means it is not.
	*/
	virtual bool16 IsBookCreatedInPreviousVersion(IBook* iBook) = 0;

	/** Check if the given source file is already open or not.
	    @param sourceFile IN the given file to check
		@param fileIndex OUT the index within the documentList. If file is not open, fileIndex will be -1.
		@return bool16 kTrue means the file is open already, kFalse means not open.
	*/
	virtual bool16 IsSourceDocumentAlreadyOpen(const IDFile& sourceFile, int32& fileIndex) = 0;

	/** Check if the given document is within current open book or not.
	    @param doc IN the given document.
	    @return IBook the current active book.
	*/
	virtual IBook* IsDocumentWithinCurrentBook(IDocument* doc) = 0; 

	/** Close the given documents (currentOpenedDocumentList) in the book. 
	    @param currentOpenedDocumentList IN the given document list.
		@param closeDocUndoStateList IN the corresponding undo state list for the given opened document list.
	*/
	virtual void CloseDocumentsInBook(OriginallyCloseDocInfo& docInfo) = 0;

	/** Open the document corresponding to the given book content. If there are 
	    no available database, we will have to close the given opened document and update the undo state list.
		@param bookDB IN the given book database.
		@param bookContentUID IN the given book content UID within book database.
		//@param currentOpenedDocumentList IN the given opened document list.
		//@param closeDocUndoStateList IN the corresponding undo state list for the given opened document lsit.
		@return ErrorCode return kSuccess if we succeed in opening the document; other return kFailuare.
	*/
	virtual ErrorCode OpenOneDocument(IDataBase* bookDB, const UID bookContentUID, UIDRef& docRef, OriginallyCloseDocInfo& docInfo) = 0;
};


/**	An object class represent a book content(chapter) within a book database. 
 */
class BookContentInfo
{
	public:
		typedef object_type data_type;

		/** Construct an emptry chapter.
		*/
		inline BookContentInfo() {}

		/** Construct a chapter with the position and UID information.
		*/
		inline BookContentInfo(
				const int32& position,	// position in the list
				const UID& content):	// content
			fPosition(position),
			fContent(content) {}
	
		/** Operator == to compare two chapters are same or not.
			@param other the chapter to compare with.
			@return bool16 kTrue means they are same, otherwise, return kFalse.
		*/
		inline bool16 operator==(const BookContentInfo& other) const
		{ 
			return ( (fPosition == other.fPosition) && 
				     (fContent == other.fContent) ); 
		}

		/** Compare two chapters.
			@param other the chapter to compare with.
			@return bool16 kTrue means this chapter is before the compared one, otherwise, return kFalse.
		*/
		inline bool16 operator<(const BookContentInfo& other) const {  return fPosition < other.fPosition; }

		/** The chapter's position within the book. Position starts from 0.
		*/
		int32 fPosition;	

		/** The chapter's UID in the book database.
		*/
		UID   fContent;
};

#endif	// __IBOOKUTILS__
