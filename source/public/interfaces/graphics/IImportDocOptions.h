//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImportDocOptions.h $
//  
//  Owner: Dave Stephens
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IImportDocOptions__
#define __IImportDocOptions__

#include "IPMUnknown.h"

#include "PMTypes.h"

#include "EPSID.h"

class IDocument;

/** Interface used to set various import/draw options for Placed InDesign document page items.
*/
class IImportDocOptions : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IIMPORTDOCOPTIONS };

	/** enum of cropping options
	*/
	typedef enum {
		kCropToPage = 0,
		kCropToBleed = 1,
		kCropToSlug = 2
	} CropOptions;

	/** Initialize this object manually.

		@param pageItemUIDRef [IN]: UIDRef of the page item. That is, the client is responsible for
			creating the page item before calling the kImportDocCmdBoss.
		@param crop [IN]: How should the page be cropped.
		@param pageIndex [IN]: zero-based page index
		@param doc [IN]: a pointer to the opened document. Passing a non-nil pointer will cause
			an AddRef, which will be released in the destructor.
	*/
	virtual void Set(const UIDRef& pageItemUIDRef, CropOptions crop = IImportDocOptions::kCropToPage, int32 pageIndex = 0, IDocument *doc = nil) = 0;

	/** Copy the settings from one IImportDocOptions instance to this instance.
		@param fromOptions [IN]: The options to copy
	*/
	virtual void Copy(const IImportDocOptions *fromOptions) = 0;

	/** Set the crop option
		@param crop [IN]: How should the page be cropped.
	*/
	virtual void SetCrop(CropOptions crop) = 0;

	/** Set the index of the page to import/draw
		@param pageIndex [IN]: zero-based page index
	*/
	virtual void SetPage(int32 pageIndex) = 0;

	/** Set the UIDRef of the page item that represents the imported page of the INDD document.
		@param pageItemUIDRef [IN]: UIDRef of the page item. That is, the client is responsible for
			creating the page item before calling the kImportDocCmdBoss.
	*/
	virtual void SetPageItem(const UIDRef& pageItemUIDRef) = 0;

	/** AddRef and store a pointer to the document to avoid having to re-open multiple times.
		@param doc [IN]: a pointer to the opened document. Passing a non-nil pointer will cause
			an AddRef, which will be released in the destructor.
	*/
	virtual void SetDocument(IDocument *doc) = 0;

	/** Get the UIDRef of the page item. 
	*/
	virtual const UIDRef& GetPageItem() const = 0;

	/**
		@return Gets a pointer to the IDocument passed into the Set method.
	*/
	virtual IDocument* GetDocument() const = 0;

	/** @return Gets the page index */
	virtual int32 GetPageIndex() const = 0;

	/** @return Get the crop setting for the page.
	*/
	virtual CropOptions GetCrop() const = 0;

	/** Method to store the page range to place.
        @param list contains the page numbers to place (page numbers start at 0).
		We place the current page (GetPage value).  The subsequent pages placed come
		from this list.  We linear search the list for the first instance of the current page 
		then place all the remaining items in the list. If the list does not contain the current page,
		no items from the list are placed.
	*/
	virtual void SetPageRange(const K2Vector<uint32> &list) = 0;

	/** Method to get the stored page range.
        @param list is filled with the page numbers to place.
	*/
	virtual void GetPageRange(K2Vector<uint32> &list) const = 0;

	/** Method to store the total pages when all pages are placed.
        @param totalPages is the total number of pages in the INDD file.
		A value of 0xffffffff for totalPages, means the internal total page value is not changed.
		You can use this when you only want to set the allPages value.
        @param allPages is true to place all the pages. When it is false the page range is used.
		We place the current page (GetPage value).  The subsequent pages placed are
		sequential until the total is reached.  To place all pages, set the current page to 1
		using SetPage(1).
	*/
	virtual void SetAllPages(uint32 totalPages, bool16 allPages) = 0;

	/** Method to get the total pages of the INDD and whether all pages are being placed.
        @param totalPages is returned.  totalPages is optional, pass nil if you don't want it.
        @return the allPages setting.
	*/
	virtual bool16 GetAllPages(uint32 *totalPages = nil) const = 0;

	/**
	 *  Determine wether we show a preview in the import options dialog.
	 */
	virtual bool16 GetShowPreview() const = 0;
	virtual void SetShowPreview(bool16 b) = 0;
};

#endif
