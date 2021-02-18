//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBook.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IBOOK__
#define __IBOOK__

#include "BookID.h"

/**
   This interface is used to save and manage books (kBookBoss). 
   The syntax is similar to IDocument.

   @ingroup layout_book
*/
class IBook : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOK };

		/**
		   kOpenExclusive indicates opening book with a full read/write right; 
		   kOpenShared indicates opening book as a copy. 
		   Internally, we always choose kOpenShared to prevent from different 
		   users open the same book at the same time or at different platform.
		*/
		typedef enum { kOpenExclusive, kOpenShared} openOptions;

		/**
		   Save book to user file. 	
		*/
		virtual void   Save() = 0;		
		
		/**
		   Save book to the IDFile provided. If there is already a file with the same name, 
		   it is first deleted, leaves the book	open and targeted to the SAVED-TO file.												
		   @param const IDFile& destBook: The file to save to.
		*/
		virtual void   SaveAs(const IDFile& destBook) = 0;	
		
		/**
		   Save book to the IDFile provided. If there is already a file with the same name, 
		   it is first deleted. Leaves the book open and targeted to the CURRENT file.	
		   @param const IDFile& destBook: The file to save to.
		*/
		virtual void   SaveACopy(const IDFile& destBook) = 0;	
			
		/** 
		   Check if book has been modified since the last save or open.						
		   @return bool16. kTrue = modified; kFalse = not modified.
		*/
		virtual bool16 IsModified() = 0;	
			
		/**
		   Check if book is open or not.
		   @return bool16. kTrue = book is open; kFalse = book is not open
		*/
		virtual bool16 IsOpen() = 0;

		/**
		   Set the open parameter.
		   @param bool16. Pass kTrue if it is open or kFalse if it is no.
		*/
		virtual void   SetOpen(bool16 open) = 0;

		/**
		   Get UID of doc object for the current master document of the book.							
		   @return UID of the current master/source document of the book.
		*/
		virtual UID    GetMasterDoc() = 0;

		/**
		   Set the document as the current master document of the book.
		   @param UID: UID of the document.This is a UID of book content, not the UID of document itself.
		*/
		virtual void   SetMasterDoc(UID doc) = 0;

		/**
		   Get the actual book file name in the file system. This contains the full path name.			
		   @return IDFile of the book file.
		*/
		virtual IDFile	GetBookFileSpec() const = 0;
		
		/**
		   Set the actual book file name when we do SaveAs									
		   @param const IDFile&: name of the book file.
		*/
		virtual void   SetBookFileSpec(const IDFile& name) = 0;

		/**
		   Get the book title name. This name is used for the title of book panel.						
		   @return PMString: book title name(not include full path name).
		*/
		virtual PMString	GetBookTitleName() const = 0;
			
		/**
		   Set the book title name. 	
		   @param const PMString&: name of the book title(not include full path name).
		*/
		virtual void        SetBookTitleName(const PMString& name) = 0;

		/**
		   Check if book is recovered or not.
		   @return bool16: kTrue if it was; kFalse if it was not.
		*/
		virtual bool16 IsRecovered() = 0;		

		/**
		   Check if book is converted or not.
		   @return bool16: kTrue if it was; kFalse if it was not.
		*/
		virtual bool16 IsConverted() = 0;						
		
		/**
		   Set the convertion flag.
		   @param const bool16&: pass kTrue if it was converted; kFalse if it was not.
		*/
		virtual void   SetConverted(const bool16& isConverted) = 0;			

		/**
		   Check if the book is a read only file or not.
		   @return bool16: kTrue if it is a read only; kFalse if it is not.
		*/
		virtual bool16 IsReadOnly() = 0;

		/**
		   Get the book open options(kOpenExclusive or kOpenShared).
		   @return IBook::OpenOptions: see definition of openOptions.
		*/
		virtual IBook::openOptions GetOpenOption() = 0;

		/**
		   Set the open option of the book.
		   @param IBook::openOptions: see definition of openOptions.
		*/
		virtual void SetOpenOption(IBook::openOptions option) = 0;

		/**
		   Get originally saved time when open the book to keep track if other user 
		   have modified the book or not before this user want to save.
		   @return uint64: time saved before.
		*/
		virtual uint64 GetSavedTime() = 0;

		/**
		   Set the new time.
		   @param uint64: time that the book is saved.
		*/
		virtual void SetSavedTime(uint64 time) = 0;

		/**
		   Get the flag that determine if we want to do auto convert during 
		   during repagination and synchronziation. 
		   @return bool16: kTrue = do auto convert that override existing documents;
		                   kFalse = don't auto convert and bring up save as dialog.
		*/
		virtual bool16 GetContentAutoConvertFlag() const = 0;

		/**
		   Set the flag for doing auto convert or not during repagination and synchronization.
		   @param bool16: kTrue/kFalse for auto convert or not.
		*/
		virtual void SetContentAutoConvertFlag(const bool16& bAutoConvert) = 0;

		/**
		   Get the flag that determine if we want to merge identically named layers during 
		   PDF export. 
		   @return bool16: kTrue = do merge identically named layers during PDF export;
		                   kFalse = don't merge identically named layers during PDF export.
		*/
		virtual bool16 GetMergeLayersFlag() const = 0;

		/**
		   Set the flag for merging identically named layers during PDF export.
		   @param bool16: kTrue/kFalse for merging layers or not.
		*/
		virtual void SetMergeLayersFlag(const bool16& bMergeLayers) = 0;

		/**
		   Get major build number that book was created.
		   @return int32: major build number.
		*/
		virtual int32 GetCreateMajorBuildNumber() const = 0;

		/**
		   Get minor build number that book was created.
		   @return int32: minor build number
		*/
		virtual int32 GetCreateMinorBuildNumber() const = 0;

		/**
		   Set the major format number that this book is saved to.
		   @param majorNumber: major format number.
		*/
		virtual void SetCreateMajorBuildNumber(const int32& majorNumber) = 0;

		/**
		   Set the minor format number that this book is saved to.
		   @param minorNumber: minor format number.
		*/
		virtual void SetCreateMinorBuildNumber(const int32& minorNumber) = 0;

		/** Returns the current modification time of the book.
			@return the current modification time of the book.
		*/
		virtual IDTime GetCurrentModificationTime() const = 0;
};

#endif // __IBOOK__
