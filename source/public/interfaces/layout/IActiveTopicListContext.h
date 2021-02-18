//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IActiveTopicListContext.h $
//  
//  Owner: Michel Hutinel
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
//  Comments: This interface saves the informations about the Active TopicList context.
//  
//========================================================================================

#pragma once
#ifndef __IActiveTopicListContext__
#define __IActiveTopicListContext__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "IIndexOptions.h"
#include "K2Vector.h"
#include "UIDRef.h"

class ISubject;
class ICommand;

/** Data utility class that wraps information about the update notification.
	Used between the active topic list context and the index panel. 
*/
class IndexTopicListUpdateInfos
{
	public:
		IndexTopicListUpdateInfos():
			fCommand(NULL),
			fTopicListUIDRef(NULL, kInvalidUID),
			fSelectionNeedsUpdate(kFalse),
			fSectionId(-1),
			fNodeId(-1),
			fPageRefId(-1),
			fXRefId(-1)
		{};

	ICommand*	fCommand;
	UIDRef		fTopicListUIDRef;
	bool16		fSelectionNeedsUpdate;
	int32		fSectionId;
	int32		fNodeId;
	int32		fPageRefId;
	int32		fXRefId;
};

/** Interface implemented by the active topic list context.
	The active topic list context is a singleton that sits on the session boss and keeps track of the current topic list.
	In case of books, there are multiple topic lists (one in each document) and the active context builds\
	a composed topic list from all the docs in the book when the scope is "book" (@see GetScope/SetScope below).
*/
class IActiveTopicListContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IACTIVETOPICLISTCONTEXT };
		
		typedef enum {
			kActiveDocumentChange = 0,
			kDocumentClosed = 1,
			kActiveBookChange = 2,
			kBookContentChange = 3,
			kTopicListCreation = 4,
			kTopicListDeletion = 5,
			kAppShutDown = 6,
			kDocumentWorkspaceLanguageChanged = 7
		} UpdateReason;

		/** Gets the current scope for the context.
			@see IIndexOptions::Scope enum.
			@return the current scope for the active context.
		*/
		virtual const IIndexOptions::Scope	GetScope() const = 0;

		/** Sets the current scope for the context.
			@see IIndexOptions::Scope enum.
			@param scope [IN] - the current scope for the active context.
		*/
		virtual void				SetScope(const IIndexOptions::Scope scope) = 0;

		/** Retrieves the UIRef of the current topic list for the active context.
			If the context is 'document' than the current topic list will be the topic list of the current active document.
			@param buildIfNeeded [IN, OPTIONAL] - usually used when the context is book, specifies if the active context should built the topic list if needed.
			@param pIsBuiltByActiveContext [IN, OPTIONAL] - if not nill, it will be set on return if the active context had to build the active topic list.
			@return the UIDRef of the current topic list.
		*/
		virtual const UIDRef&	GetActiveTopicList(bool16 buildIfNeeded = kTrue, bool16* pIsBuiltByActiveContext = NULL) = 0;

		/** Gets the default topic list for the specified document.
			NOTE: this function will be moved out as a separate utility function in a future version.
			@param docRef [IN] - UIDRef of the document for which we want to retrieve the topic list.
			@return UIDRef of the default topic list of the specified document.
		*/
		virtual UIDRef			GetDefaultTopicList(const UIDRef& docRef) const = 0;

		/** Retrieves the name of the current active book.
			@param bookName [OUT] - name of the currently active book.
		*/
		virtual void			GetActiveBookName(PMString& bookName) = 0;

		/** Retrieves the currently active document.
			@return UIDRef of the active document.
		*/
		virtual UIDRef			GetActiveDocument() const = 0;

		/** Retrieves the currently active book.
			@return UIDRef of the active book.
		*/
		virtual UIDRef			GetActiveBook() const = 0;

		/** Retrieves the list of the open documents from the currently active book.
			@param docList [IN] - array of UIDRefs of the open documents that belong to the active book.
		*/
		virtual void			GetOpenedDocListFromActiveBook(K2Vector<UIDRef>& docList) const = 0;

		/** Gets the default topic list of the active document.
			Similar to calling GetDefaultTopicList(GetActiveDocument()).
			@return UIDRef of the default topic list of the active document.
		*/
		virtual UIDRef			GetActiveTopicListFromActiveDocument() const = 0;

		/** Checks if the active document belongs to the active book.
			@return true if the active document belongs to the active book.
		*/
		virtual	const bool16	IsBookAble() = 0;

		/** Returns the number of components (topic lists) from the current active topic list.
			@see GetActiveTopicList.
			When the context is book, the composed topic list will contain all the topic lists from the documents that belong to the book.
			@return number of components for the active topic list.
		*/
		virtual int32			GetNumActiveComponents() const = 0;

		/** Returns the UIDRef of the component (topic list) at the specified index.
			@see GetNumActiveComponents.
			@return UIDRef of the specified component.
		*/
		virtual UIDRef			GetNthActiveComponent(int32 nth) const = 0;

		/** Updates the state of the active context.
			Called by the document and book observers to update the state of the active context.
			@param reason [IN] - reason for update.
			@param updaterRef [IN] - the subject who notifies the context (usually the document).
			@param doNotify [IN, OPTIONAL] - if the context should broadcast the changes for the other observers.
		*/
		virtual void			UpdateContext(IActiveTopicListContext::UpdateReason reason, const UIDRef& updaterRef, bool16 doNotify = kTrue) = 0;

		/** Notifies the active context that a topic list has changed.
			Called by the document observers to update the active context.
			@param theChange [IN] - ClassID of the notification.
			@param theSubject [IN] - the subject.
			@param protocol [IN] - PMIID of the protocol.
			@param changedBy [IN] - generic pointer to the object that caused the change, usually a pointer to a command object.
			@param topicListRef [IN, OPTIONAL] - UIDRef of the affected topic list.
			@param doNotify [IN, OPTIONAL] - if the context should broadcast the changes for the other observers.
		*/
		virtual void			OnTopicListModification(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy, UIDRef* topicListRef = NULL, bool16 doNotify = kTrue) = 0;

		/** Invalidates the active topic list.
			Used by the inval handler to refresh the active topic list when undo/redo happens.
		*/
		virtual void			InvalidateActiveTopicList() = 0;
};

#endif // __IActiveTopicListContext__