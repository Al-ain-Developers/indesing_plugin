//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryScrapController.h $
//  
//  Owner: Mark VerMurlen
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
//  Reviewed: 9/25/98
//  
//  Purpose:
//  This interface is responsible for managing the Library Panel's Scrap.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryScrapController__
#define __ILibraryScrapController__

#include "CDataExchangeController.h"
#include "ShuksanID.h"


class IDataExchangeHandler;
class IDataBase;
class ILibraryAsset;

/** Responsible for managing the Library Panel's scrap.  However, InDesign CS2 largely
	avoids the use of this scrap, owing to its use of INX snippets as an internal
	data store for asset data.  The ISnippetImport and ISnippetExport interfaces manage
	the direct translation of document data to and from INX snippet asset store without
	the use of the library scrap.  This code is DEPRECATED, though left in to support
	pre-CS2 library conversion.
*/
class ILibraryScrapController : public CDataExchangeController
{
	// ----- Constructor/Destructor
	public:
		ILibraryScrapController(IPMUnknown *boss) : CDataExchangeController(boss) {};
		virtual ~ILibraryScrapController() {};

	// ----- Active handler
	public:
        /** Determine which data exchange handler could best handle the data in a drag.
            @param response OUT response from the data exchange handler
            @param internalizedFlavor IN the preferred internal flavor (native format) if data needs to be converted.
            @precondition a drag must be in progress
            @return the handler (if any) that can provide the requested conversion.
		*/
		virtual IDataExchangeHandler*	QueryHandlerForInternalize(DataExchangeResponse& response, const PMFlavor& internalizedFlavor = kNoFlavor) const = 0;

	// ----- Scrap Conversion
	public:
		/** Tell whether external data waiting to be internalized.  This method is useful for clients that would like
			to peek at the actual data to be pasted/dropped/whatever if it has already been internalized, or is internal data. 
			Internalizing can be expensive and should not be called to give user feedback (i.e. menu enabling, drag feedbacck).
			@return kTrue for data needing to be internalized; kFalse if not
		*/
		virtual bool16			NeedsToInternalize() const = 0;

		/** Render the contents of the scrap out to an external library asset.
			@return error code
		*/
		virtual ErrorCode		ExternalizeToLibrary() const = 0;

		/** Render the contents of an InDesign 2.0 or CS library asset into the scrap.
			@return error code
		*/
		virtual ErrorCode		InternalizeFromLibrary() = 0;

		/** Render the contents of an asset from a pre-InDesign 2.0 library into the scrap.
			@return error code
		*/
		virtual ErrorCode		InternalizeFromOldLibrary() = 0;

		/**	Fulfill a data promise.  Stub inherited from CDataExchangeController.
			@param whichItem IN the data item
			@param whichFlavor IN the flavor to fulfill
			@return error code
		*/
		virtual ErrorCode		FulfillPromise(IPMDataObject* whichItem, const ExternalPMFlavor& whichFlavor) const = 0;

		/** Emptying the internal Scrap.
			@return error code
		*/
		virtual ErrorCode		Clear() = 0;
		
		/** Set the asset being accessed currently.
			@param libraryAsset IN interface pointer to ILibraryAsset for the asset being accessed.
		*/
		virtual void			SetWorkingLibraryAsset( ILibraryAsset *libraryAsset ) = 0;

		/** Clean Up.
		*/
		virtual void			Cleanup() = 0;
};

#endif
