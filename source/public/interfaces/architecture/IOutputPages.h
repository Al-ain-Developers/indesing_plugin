//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOutputPages.h $
//  
//  Owner: DBerggren
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
//  an interface to be used off of export commands
//  to output multiple pages from multiple open pubs -
//  basically a UIDRef list for outputing pages
//  from multiple open pubs (possibly from a book)
//  
//========================================================================================

#pragma once
#ifndef __IOutputPages__
#define __IOutputPages__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"
#include "UIDRef.h"
#include "PMRect.h"
#include "PMString.h"
#include "UIDList.h"

class IDataBase;
class IPMStream;

/** IOutputPages is used to enable the export and print of multiple
	pages that come from potentially different publications. Such is
	the case when printing/exporting multiple pubs from a Book. This
	interface will handle the open/close of pubs that require it. 
	If not printing/exporting a Book, things are simple. The database 
	has to be open and valid, and the pages or spreads can be added via
	the insert or append methods that add a UIDRef. If printing/exporting
	a Book, the pubs may be open or closed. If the pub is closed, this
	requires a IDFile to the pub, a page or spread UID, and the page
	bounds of the page or spread. When the print or export code asks for
	a UIDRef for the page, this interface will open the pub headless, and
	return a valid database in the UIDRef. When finished, it will close
	the pub. IOutputPages is used in Printing, EPS, PDF and SVG export.
*/
class IOutputPages : public IPMUnknown
{
    public:
		enum { kDefaultIID = IID_IOUTPUTPAGES };

	// -----------------------------
	// Start/End
	// -----------------------------
		/** Start - MUST be paired with End()!
			- should be called at the start of the outermost
			context of the IOutputPages. Start does not have to be
			called again for nested IOutputPages uses, only the 
			outmost context. Start/End are used for cleaning up
			pubs that IOutputPages had to open, when printing books.
			If not printing/exporting books, Start/End are unnecessary.
		*/
		virtual void			Start() = 0;

		/** End - MUST be paired with Start()!
			- should be called at the end of the outermost
			context of the IOutputPages. End does not have to be
			called again for nested IOutputPages uses, only the 
			outmost context. It is used to close any pubs that IOutputPages
			had to open when printing books.
		*/
		virtual void			End() = 0;

	// -----------------------------
	// Master Database
	// -----------------------------
		/** If outputting a book, this is the database of the master pub, 
			otherwise, if this has not been initialized, it is the database
			of the first pub in the list, zero if no pubs in the list.
			This is used for document settings that need to be used for
			all documents being output.
			@return IDataBase pointer to the master database
			@see IDataBase
		*/
		virtual IDataBase*		GetMasterDataBase(void) = 0;
		
		/** Set the master data base pointer.
			@param iDataBase	IN IDataBase pointer of the master database to use
		*/
		virtual void			SetMasterDataBase(IDataBase* iDataBase) = 0;


	// -----------------------------
	// IsSpreads
	// -----------------------------
		/** Tell whether we are dealing with pages or spreads.
			Are the output UIDRefs used below page UIDRefs or spread UIDRefs? 
			Defaults to kFalse (page UIDRefs) 
			NOTE: this should be set up prior to calling AppendUIDRef!
			@return kTrue if UIDRefs refer to spreads instead of pages, kFalse otherwise
		*/
		virtual bool16			GetIsSpreads(void) const = 0;
		
		/** Set the boolean for outputting spreads.
			@param bIsSpreads	IN kTrue if outputting spreads, kFalse otherwise
		*/
		virtual void			SetIsSpreads(const bool16 bIsSpreads) = 0;

	// -----------------------------
	// Which pages/spreads to output methods
	// -----------------------------
		/** Initialize from a UIDList of pages (or spreads if bSpreads is kTrue)
			to output
			@param listPages	IN UIDList reference to initialize from
			@param bSpreads		IN kTrue if UIDList contains spread references, kFalse otherwise
		*/
		virtual void            InitializeFrom( const UIDList& listPages, bool16 bSpreads ) = 0;

		/** Insert a UIDRef, containing the DataBase of the open pub, and the 
			UID of either the page to be output, or the spread to be output, onto 
			the front of the list. The page/spread bounds are calculated automatically.
			@param uidRef	IN UIDRef of the page or spread to insert
		*/
        virtual void			InsertOutputPageUIDRef(const UIDRef& uidRef) = 0;

		/** Append a UIDRef, containing the DataBase of the open pub, and the 
			UID of the page to be output, or the spread to be output, onto the 
			end of the list. The page/spread bounds are calculated automatically.
			@param uidRef	IN UIDRef of the page or spread to append
		*/
        virtual void			AppendOutputPageUIDRef(const UIDRef& uidRef) = 0;

		/** Append a UIDRef, containing the UID of the page to be output, or the 
			spread to be output, onto the end of the list. For this method only, 
			the DataBase portion of the UIDRef does not have to be valid (i.e. 
			the pub does not have to be open) since the IDFile of the pub is provided, 
			as well as the bounds of the page/spread.
			@param uidRef		IN UIDRef containing the UID of the page/spread to append (the DB doesn't matter)
			@param sysFile		IN IDFile pointer of the pub that contains the UID of the page/spread
			@param pageBounds	IN PMRect of the page/spread bounds
		*/
        virtual void			AppendOutputPageUIDRef2(const UIDRef& uidRef, const IDFile* sysFile, const PMRect& pageBounds) = 0;

		/** Removes the selected index from the list
			@param index	IN index of the UIDRef to remove
		*/
        virtual void			RemoveUIDRef(const int32 index) = 0;

		/** Remove all of the UIDRefs from the list
		*/
        virtual void			Clear(void) = 0;

		/** Return the index of the given UIDRef
			@param uidRef	IN UIDRef to find 
		*/
        virtual int32			Location(const UIDRef& uidRef) const = 0;

		/** Get the number of pages/spreads in the list
			@return the number of pages/spreads in the list
		*/
        virtual int32			Number(void) const = 0;
		
		/** Get the UIDRef of the selected index into the list
			@param index				IN index of the UIDRef to retrieve
			@param bValidateDataBase	IN if kTrue, the IDataBase portion of the 
										UIDRef is guaranteed to be good, at least until 
										then next call to GetNthUIDRef. If kFalse, the 
										IDataBase portion of the UIDRef may or may not be 
										valid - so only count on the UID portion.
			@return UIDRef of the given index into the list
		*/
        virtual UIDRef			GetNthUIDRef(const int32 index, bool16 bValidateDataBase = kTrue) const = 0;
		
		/** Get a pointer to a IDFile of the selected index into the list,
			the pointer will be nil if the pub has never been saved!
			@param index	IN index of the IDFile to retrieve
			@return IDFile pointer of the given index into the list, may be nil
		*/
        virtual IDFile*		GetNthSysFile(const int32 index) = 0;
		
		/** Overwrite the setting for the page/spread bounds (in InD coordinates)
			@param index		IN index of the bounds to change
			@param pageBounds	IN PMRect containing the new page bounds
		*/
        virtual void			SetNthOutputPageBounds(const int32 index, const PMRect& pageBounds) = 0;
		
		/** Get a PMRect of the page/spread bounds (in InD coordinates) for the given 
			index. The rect is calculated in the AppendUIDRef methods, as the pages/spreads
			are added to the list. SetNthBounds can be used to overwrite the bounds.
			@param index	IN index of the bounds to retrieve
			@return PMRect containing the bounds of the given index
		*/
        virtual PMRect			GetNthOutputPageBounds(const int32 index) const = 0;
		
	// -----------------------------
	// Page information methods
	// -----------------------------
		/** Determine if the output pages/spreads contiguous. Defaults to kFalse
			@return kTrue if the pages/spreads in the list are contiguous, kFalse otherwise
		*/
		virtual bool16			GetContiguousPages(void) const = 0;
		
		/** Set the boolean for contiguous pages/spreads.
			@param bContiguousPages	IN kTrue if the pages/spreads are contiguous, kFalse otherwise
		*/
		virtual void			SetContiguousPages(const bool16 bContiguousPages) = 0;

		/** Determine if the output pages/spreads are the same size.
			NOTE: if the SetUniformSizePages method has not been used, it will figure this out from 
			the bounds. If the SetUniformSizePages method has been used, it will return that value.
			@return kTrue if all of the output pages/spreads are the same size, kFalse otherwise 
		*/
		virtual bool16			GetUniformSizePages(void) = 0;
		
		/** Set if the output pages/spreads are the same size. It is not necessary to use this 
			method, because the GetUniformSizePages method will figure out if the pages are the 
			same size. If this method is used, the GetUniformSizePages will return whatever this 
			has been set to.
			@param bUniformSizePages	IN kTrue if all the pages are the same size, kFalse otherwise
		*/
		virtual void			SetUniformSizePages(const bool16 bUniformSizePages) = 0;

	// -----------------------------
	// Document/Book name methods
	// -----------------------------
		/** Get the name associated with the book or document. This is used
			in export information, such as DSC comments for EPSs.
			@param name	OUT PMString reference containing the name to use
		*/
		virtual void			GetName(PMString& name) const = 0;
		
		/** Set the document name. See GetName above for more info.
			@param name	IN PMString reference containing the name to use
		*/
		virtual void			SetName(const PMString& name) = 0;

	// -----------------------------
	// Output stream methods
	// -----------------------------
		/** Get a stream to output to - if this is nil, code should ask the user for file
			@return an IPMStream to output to, or may be nil
			@see IPMStream
		*/
		virtual IPMStream*		GetOutputStream(void) const = 0;

		/** Set a stream to output to
			@param outputStream	IN the stream to write the output to
		*/
		virtual void			SetOutputStream(IPMStream *outputStream) = 0;

	// -----------------------------
	// Utility methods
	// -----------------------------
		/** Copy the given IOutputPages to this one
			@param other	IN the IOutputPages to copy from
		*/
		virtual void			Copy(IOutputPages* other) = 0;

		/** Convert from a IOutputPages without spreads to one with or without spreads.  
			Will not convert from one that has spreads to one that does not however.
			@param pSrc					IN the IOutputPages to initialize
			@param bConvertToSpreads	IN kTrue if converting to spreads, kFalse otherwise
		*/
		virtual void            InitializeFrom( IOutputPages* pSrc, bool16 bConvertToSpreads ) = 0;

		/** Set the export destination file
			@param sysFile		IN IDFile reference that is the destination file
			@param validFile	IN kTrue if the file is valid, kFalse otherwise
		*/
		virtual void SetOutputFile(IDFile& sysFile, bool16 validFile = kFalse) = 0;

		/** Get the export destination file. If the file is not valid, the export manager
			will put up a save file dialog.
			@param isValidOutputFile	OUT kTrue if the file is valid, kFalse otherwise
			@return IDFile of the output file
		*/
		virtual IDFile GetOutputFile(bool16& isValidOutputFile) = 0;

		/** Reverse the output page UID list.
			@param none
		*/
		virtual void ReverseOrder() = 0;
};

#endif // __IOutputPages__
