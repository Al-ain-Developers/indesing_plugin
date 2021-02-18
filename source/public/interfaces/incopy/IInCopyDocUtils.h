//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyDocUtils.h $
//  
//  Owner: chris parrish
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
//  Functions to aid in InCopy Document file actions
//  
//========================================================================================

#pragma once
#ifndef __IInCopyDocUtils__
#define __IInCopyDocUtils__

#include "InCopyWorkflowID.h"
#include "IDocFileHandler.h"
#include "IOpenFileCmdData.h"

class IDataLink;
class IDocument;
class SysFileList;
class UIDList;
class ITextModel;
class INewDocCmdData;
class IInCopyImportOptions;

/**
	The InCopy Document Utilities are designed to provide third parties the hooks necessary to replace InCopy
	files with whatever storage mechanisms they want to use, most often some form of database.  Third parties
	are expected to implement and replace the default which ships with the InCopyFileActions plug-in.
*/
class IInCopyDocUtils : public IPMUnknown
{
public:
		enum	{kDefaultIID = IID_IINCOPYDOCUTILS};

		//----- File Actions
		/**
			DoSave write the InCopy story to whatever storage is desired, normally a file. If story is not 
			saved yet, it will invoke DoSaveAs behavior. Starting in CS5, it will carried out save as 
			background task if story is already saved.
			@param textModel - The story to write.
			@param uiFlags - Whether to provide UI or not.
		*/
		virtual		void		DoSave(const UIDRef& textModel, UIFlags uiFlags = kFullUI) = 0;

		/**
			DoSaveAll saves all InCopy stories in a document.
			@param doc - The document.
			@param uiFlags - Whether to provide UI or not.
		*/
		virtual		void		DoSaveAll(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;

		/**
			DoSaveAs saves an InCopy story to a new file.
			@param doc - The document containing the story.
			@param copy - Whether to save a copy or not.  Default is false.
			@param destFile - A pointer to an IDFile to store into (default is unspecifed).
			@param uiFlags - Whether or not to show UI (default is full UI).
			@param asStationary - Whether or not to save stationery (default is false).
			@param fileTypeID - What file type to use (default is kInvalidFileTypeInfoID).
		*/
		virtual		void		DoSaveAs(const UIDRef& doc,  bool16 copy = kFalse, const IDFile *destFile = nil, UIFlags uiFlags = kFullUI, bool8 asStationary = kFalse, FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID) = 0;

		/**
			DoOpen opens one or more story files in InCopy.  If a story is already open, bring its window to the front and
			place a text insertion point in the story.
			@param filesToOpen - A list of files to open.
			@param flags - Flags indicating the desired open options.
			@param showWindow - Whether or not to show a window (default is true).
			@param undoSupport - Indicates whether commands that change the document (if this is an InDesign/InCopy document) will appear on the undo menu (default=IDocument::kFullUndoSupport).
			@param uiFlags - Whether to show UI (default is full UI).
			@return - A UIDRef for the opened document.
		*/
		virtual		UIDRef		DoOpen(const IDFile& filesToOpen, IOpenFileCmdData::OpenFlags flags, bool16 showWindow = kTrue, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport, UIFlags = kFullUI) = 0;

		/**
			DoNew creates a new document with a single story frame in it.
			@param openWin - Whether to open a window or not (default is true).
			@param undoSupport - Indicates whether commands that change the document (if this is an InDesign/InCopy document) will appear on the undo menu (default=IDocument::kFullUndoSupport).
			@return - A UIDRef for the new document.
		*/
		virtual		UIDRef		DoNew(bool16 openWin = kTrue, IDocument::UndoSupport undoSupport = IDocument::kFullUndoSupport) = 0;

		/**
			DoRevert closes a document without saving and reopens its original (typically from a file).
			@param doc - The document to revert.
			@param uiFlags - Whether to show UI (default is full UI).
		*/
		virtual		void		DoRevert(const UIDRef& doc, UIFlags uiFlags = kFullUI) = 0;

		/**
			DoUpdateDesign closes and reopens a document, typically when a newer version becomes available.
			@param docRef - The document to update.
			@param uiFlags - Whether to show UI (default is full UI).
		*/
		virtual		void		DoUpdateDesign(const UIDRef& docRef, UIFlags uiFlags = kFullUI) = 0;

		/**
			DoNewWindow creates a new window for an existing document.
			@param doc - The document to open a new view from.
		*/
		virtual		void		DoNewWindow(const UIDRef& doc) = 0;

		/**
			DoClose closes a document, offering the user a chance to save.
			@param doc - The document to close.
			@param uiFlags - Whether to show UI (default is full UI).
			@param allowCancel - Whether to allow the user the opportunity to cancel the close.
			@param cmdMode - Whether to process or schedule the close command.  Processing it causes the close to occur
			immediately while scheduling it causes it to close after current commands are done processing.
		*/
		virtual		void		DoClose(const UIDRef& doc, UIFlags uiFlags, bool16 allowCancel, IDocFileHandler::CloseCmdMode cmdMode) = 0;

		/**
			QueryDocFileHandler returns a refcounted InCopy IDocFileHandler.
			@return - The reference counted IDocFileHandler pointer.  Typically this should immediately land in an InterfacePtr.
		*/
		virtual		IDocFileHandler*	QueryDocFileHandler() = 0;
		
		/**
			ShouldDoSaveAs determines if the document already has a place to save or if it needs a SaveAs operation.
			@param doc - The document to save.
			@return - Whether or not SaveAs should be done.
		*/
		virtual 	bool16		ShouldDoSaveAs(IDocument* doc) = 0;
	
		/**
			CanDoSave determines whether to enable to Save menu item.
			@param doc - The document to save.
			@return - Whether or not the menu item should be enabled.
		*/
		virtual		bool16		CanDoSave(const UIDRef& doc) = 0;

		/**
			CanDoSaveAll determines whether to enable to the Save All menu item.
			@param doc - The document to save.
			@return - Whether or not the menu item should be enabled.
		*/
		virtual		bool16		CanDoSaveAll(const UIDRef& doc) = 0;

		/**
			CanDoRevert determines whether to enable the Revert menu item.
			@param doc - The document to save.
			@return - Whether or not the menu item should be enabled.
		*/
		virtual		bool16		CanDoRevert(const UIDRef& doc) = 0;

		/**
			CanDoUpdateDesign determines whether to enable the Update Design menu item.
			@param doc - The document to save.
			@return - Whether or not the menu item should be enabled.
		*/
		virtual		bool16		CanDoUpdateDesign(const UIDRef& doc) = 0;

		/**
			IsReadOnly determines if a document can be modified.
			@param iDoc - The document.
			@return - Whether or not it can be modified.
		*/
		virtual		bool16		IsReadOnly(IDocument* iDoc) = 0;

		/**
			ExportAllLinkedStories iterates through all the InCopy stories in a document and exports them.
			Stories are stored in the file specified by their datalink and the datalink is marked as up to date.
			This must be called from within a command or other database transaction.
			@param doc - The document
			@param fileTypeID - unused
			@param uiFlags - Whether to present UI while exporting.
		*/
		virtual		void		ExportAllLinkedStories(IDocument* doc, const FileTypeInfoID& fileTypeID, UIFlags uiFlags = kFullUI) = 0;

		/**
			ExportStoryAndCreateLink exports a story and creates a datalink for it.
			This must be called from within a command or other database transaction.
			@param story - The UIDRef of the ITextModel to export.
			@param file - The IDFile to write the story into.
			@param fileTypeID - kInCopyXMLInterchangeFileTypeInfoID or kInCopyXMLMarkupFileTypeInfoID or kInCopyTemplateFileTypeInfoID
		*/
		virtual		void		ExportStoryAndCreateLink(const UIDRef& story, const IDFile& file, const FileTypeInfoID& fileTypeID) = 0;

		/**
			ExportLinkedStory exports a story which already has a datalink on it.  This method does not update the
			datalink or modify the database.
			@param story - The UIDRef of the ITextModel to export.
			@param fileTypeID - kInCopyXMLInterchangeFileTypeInfoID or kInCopyXMLMarkupFileTypeInfoID or kInCopyTemplateFileTypeInfoID
			@return - An error code or kSuccess.
		*/
		virtual		ErrorCode	ExportLinkedStory(const UIDRef& story, const FileTypeInfoID& fileTypeID) = 0;
		
		/**
			ImportAllLinkedStories updates all InCopy stories in a document from their datalinked files.
			@param doc - The document.
			@param fileTypeID - The file type of the containing document.
			@param options - The import options to use for old incd file links.
		*/
		virtual		void		ImportAllLinkedStories(IDocument* doc, const FileTypeInfoID& fileTypeID, IInCopyImportOptions* options) = 0;

		/**
			ImportStoryAndCreateLink reads in a story and optionally creates a link.
			@param story - The ITextModel UIDRef.
			@param stream - The stream to read the new story from.
			@param options - The import options to use (primarily for old incd files).
			@param fileTypeID - The type of the imported file.
			@param createLink - Whether to create a datalink or not.
			@param importedItem - A UIDRef to the page item that was created.
			@return - An error code or kSuccess.
		*/
		virtual		ErrorCode	ImportStoryAndCreateLink(const UIDRef& story, IPMStream* stream, IInCopyImportOptions* options, const FileTypeInfoID& fileTypeID, bool16 createLink = kTrue, UIDRef *importedItem = nil) = 0;

		/**
			ImportLinkedStory reads in a single linked InCopy story.
			@param story - The ITextModel UIDRef.
			@param fileTypeID - The type of the imported file.
			@param options - The import options to use (primarily for old incd files).
			@return - An error code or kSuccess.
		*/
		virtual		ErrorCode	ImportLinkedStory(const UIDRef& story, const FileTypeInfoID& fileTypeID, IInCopyImportOptions* options = nil) = 0;
		
		/**
			GetFirstUserStory finds the first user accessible story in a document.
			@param doc - The document to search.
			@return - The UIDRef of the first story.
		*/
		virtual		UIDRef		GetFirstUserStory(IDocument* doc) = 0;

		/**
			GetLinkedStories finds all stories with an InCopy format datalink.
			@param doc - The document to search.
			@param stories - A returned list of found stories.
			@param links - A returned list of links.
			@param db - The document's database, which can be safely omitted since it defaults properly.
		*/
		virtual		void		GetLinkedStories(IDocument* doc, UIDList* stories, UIDList* links, IDataBase* db = nil) = 0;

		/**
			CreateDefaultTextFrame makes a full page text frame for a standalone document.
			@param doc - The document.
			@return - The UIDRef of the new text frame.
		*/
		virtual		UIDRef		CreateDefaultTextFrame(IDocument* doc) = 0;

		/**
			CreateDefaultGraphicFrame makes a full page graphic frame for a standalone document.
			@param doc - The document.
			@return - The UIDRef of the graphic frame.
		*/
		virtual		UIDRef		CreateDefaultGraphicFrame(IDocument* doc) = 0;

		/**
			CheckOnClose puts up the "Do you want to save?" dialog if the document has been modified.
			@param doc - The document.
			@param uiFlags - Whether to present UI to the user or not.
			@param allowCancel - Determines if the user is allowed to cancel the close operation.
			@return - description
		*/
		virtual IDocFileHandler::CloseOptions 			
								CheckOnClose(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel) = 0;

		/**
			CheckOnRevertStory asks the user if they want to revert a story.
			@param storyRef - The story to revert.
			@return - Whether or not they want to revert it.
		*/
		virtual bool16			CheckOnRevertStory(const UIDRef& storyRef) = 0;
			
		/**
			IsFileAlreadyOpen determines if a story is already open, in either an InDesign document, an assignment
			or a standalone InCopy document.
			@param file - The story file.
			@param doc - The UIDRef of the open document that contains the story.
			@param foundStory - The UIDRef of the open story.
			@return - Whether the story was found or not.  If true, then doc and foundStory are valid.
		*/
		virtual		bool16		IsFileAlreadyOpen(const IDFile& file, UIDRef* doc, UIDRef* foundStory = nil) = 0;
				 
		/**
			GetCopyDefaultName generates a "save a copy" name and path using the first story in the document.
			@param doc - The document.
			@param name - The returned document name and location.
			@param useSystemDefaultDir - If false on return, then the name is a full specification. If true, then
			only the name is specified and the caller will need  to determine the directory.
		*/
		virtual		void		GetCopyDefaultName(const UIDRef& doc, IDFile *name, bool16& useSystemDefaultDir) = 0;		
				
		/**
			GetOpenFileType returns the Macintosh file type of an open file.
			@param sysFile - The IDFile of the file in question.
			@param type - The Macintosh file type of the open file.
			@return - Whether or not the file type was recognized.
		*/
		virtual		bool16		GetOpenFileType(const IDFile& sysFile, SysOSType &type) = 0;

		/**
			GetStreamFileType checks the stream for "magic bytes" that indicate its type.
			@param stream - The stream.
			@param type - The type of the stream.
			@return - Whether or not this is a known stream type.
		*/
		virtual		bool16		GetStreamFileType(IPMStream* stream, SysOSType &type) = 0;

		/**
			SetInCopyUserFile informs the document that it is actually an InCopy file instead of an InDesign database
			(even though it really is an InDesign database).  This affects recovery in InCopy primarily.
			@param doc - The document.
			@param newFile - The InCopy file associated with this document.
		*/
		virtual		void		SetInCopyUserFile(IDocument *doc, const IDFile &newFile) = 0;
		
		/**
			LockNonInCopyStories runs through all the stories in a document and locks the ones which are not
			InCopy stories (graphics or text).  InCopy stories are locked or unlocked elsewhere based on their
			"checked out" state.
			@param doc - The document.
		*/
		virtual		void		LockNonInCopyStories(const UIDRef& doc) = 0;

};

#endif //__IInCopyDocUtils__
