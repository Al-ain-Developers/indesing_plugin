//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFPlacePrefs.h $
//  
//  Owner: Ed Bomke
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
#ifndef __IPDFPLACEPREFS__
#define __IPDFPLACEPREFS__

#include "PMTypes.h"
#include "PDFID.h"

/** Public interface used to remember the PDF place options.

This interface is used by the PDF place code to hold the settings the user selects in the PDF
options dialog.  The workspace has this interface to hold the default values.
*/

class IPDFPlacePrefs : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPDFPLACEPREFS };
//		enum { kDontChange = -1 };

		// Note: the order of this enumeration must exactly match the item ordering in the
		//		Place PDF dialog's "Crop To" dropdown list, including the existence of
		//		an unused entry for the list separator.
		//		Also, the ordering of the items following the separator is generally smallest
		//		to largest - EB 10/30/98
		enum
		{
			kCropToContentVisibleOnly = 0,
			kCropToUnused,			// appears as a separator line
			kCropToArt,
			kCropToPage,
			kCropToTrim,
			kCropToBleed,
			kCropToMedia,
			kCropToContentAllLayers
		};

		/** Method to copy all the stored information from one interface to another.
	        @param dataToCopy is where the information is copied from.
		*/
		virtual void CopyData(IPDFPlacePrefs* dataToCopy) = 0;

		/** Method to store the PDF page number of the placed page.
	        @param nPage is the page number (1 is the first page).
		*/
		virtual void SetPage(int32 nPage) = 0;

		/** Method to get the stored PDF page number.
	        @return the page number.
		*/
		virtual int32 GetPage() = 0;

		/** Method to store the CropTo information.
	        @param newCropTo 
		*/
		virtual void SetCropTo(int32 newCropTo) = 0;

		/** Method to get the CropTo information.
	        @return the CropTo number.
		*/
		virtual int32 GetCropTo() = 0;

		/** Method to store the preserve screens information.
	        @param bPreserve is true to preserve screens. 
		*/
		virtual void SetPreserveScreens(bool16 bPreserve) = 0;

		/** Method
		*/
		virtual bool16 GetPreserveScreens() = 0;

		/** Method
		*/
		virtual void SetTransparentBackground(bool16 bTransparent) = 0;

		/** Method
		*/
		virtual bool16 GetTransparentBackground() = 0;

		/** Method
		*/
		virtual void SetStream(IPMStream* pStream) = 0;

		/** Method
		*/
		virtual IPMStream* GetStream() = 0;

		/** Method
		*/
		virtual void SetUserPassword( PMString strPassword ) = 0;

		/** Method
		*/
		virtual PMString GetUserPassword() = 0;

		/** Method
		*/
		virtual void SetProxyResolution( int32 nDPI ) = 0;

		/** Method
		*/
		virtual int32 GetProxyResolution() = 0;

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
		virtual void GetPageRange(K2Vector<uint32> &list) = 0;

		/** Method to store the total pages when all pages are placed.
	        @param totalPages is the total number of pages in the PDF file.
			A value of 0xffffffff for totalPages, means the interal total page value is not changed.
			You can use this when you only want to set the allPages value.
	        @param allPages is true to place all the pages. When it is false the page range is used.
			We place the current page (GetPage value).  The subsequent pages placed are
			sequential until the total is reached.  To place all pages, set the current page to 1
			using SetPage(1).
		*/
		virtual void SetAllPages(uint32 totalPages, bool16 allPages) = 0;

		/** Method to get the total pages of the PDF and whether all pages are being placed.
	        @param totalPages is returned.  totalPages is optional, pass nil if you don't want it.
	        @return the allPages setting.
		*/
		virtual bool16 GetAllPages(uint32 *totalPages = nil) = 0;

		/**
		 *  Determine wether we show a preview in the import options dialog.
		 */
		virtual bool16 GetShowPreview() = 0;
		virtual void SetShowPreview(bool16 b) = 0;
};

#endif
