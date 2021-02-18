//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDataExchangeController.h $
//  
//  Owner: Dave Burnard
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
#ifndef __CDataExchangeController__
#define __CDataExchangeController__

#include "IDataExchangeController.h"
#include "ShuksanID.h"
#include "HelperInterface.h"

#include "K2Vector.h"
#include "IDataExchangeHandler.h"
#include "DataExchangeHandlerEntry.h"

//========================================================================================
// Forward declarations
//========================================================================================
class IDataBase;
class ICommand;
class IDocument;

class DataExchangeTestProvider;

#pragma export on

/** CDataExchangeController
		Shared implementation for Clipboard, DragDrop, Mac OSX Services and LibraryScrap controllers.
		Should also serve as the base class for all custom data exchange controller implementations
 		
 		@see IDataExchangeController
*/
class PUBLIC_DECL CDataExchangeController : public IDataExchangeController
{
	// ----- Constructors/desctructors
	public:
		CDataExchangeController(IPMUnknown *boss);
		virtual ~CDataExchangeController();
		
		virtual void 								ReadWrite(IPMStream* s, ImplementationID prop);

	// ----- Scrap handlers
	public:
		// ----- Registration
		/** Iterate over all bosses implementing IDataExchangeHandler in the object model and register them. */
		virtual void 								RegisterAllHandlers();
		/** Register a specific IDataExchangeHandler boss. */
		virtual bool16							RegisterDataHandler(ClassID dataClass);
		/** Create an instance of a specific IDataExchangeHandler boss, in this controllers managed scrap database. */
		virtual IDataExchangeHandler*	NewDataHandler(ClassID dataClass) const;
		// ----- Queries
		/** Query for the handler representing a particular flavor. */
		virtual IDataExchangeHandler*	QueryHandler(const PMFlavor& scrapFlavor) const;
		/** Query for a handler capable of performing a specific conversion for internalizing external scrap data. */
		virtual IDataExchangeHandler* 	QueryHandler(const ExternalPMFlavor& fromFlavor, const PMFlavor& toFlavor) const;
		virtual IDataExchangeHandler*	QueryHandlerForInternalize(DataExchangeResponse& response, const PMFlavor& internalizeToThisFlavor = kNoFlavor) const = 0;

		/** Iterate over all IDataExchangeHandlers in the object model and return the collection of internalizeable flavors. */
		virtual void					GetInternalizeableFlavors(OrderedFlavorList &flavorList) const;

		// ----- Active handler
	public:
		/** Query for the current active handler. */
		virtual IDataExchangeHandler*	QueryActiveHandler() const;
		/** Set the active handler. */
		virtual void								SetActiveHandler(IDataExchangeHandler* activeHandler);

		virtual bool16							NeedsToInternalize() const = 0;

	// ----- Scrap database, Initialization and Cleanup
	public:
		/** Return the scrap database managed by this controller instance. */
		virtual IDataBase*					GetScrapDataBase() const;
		/** Initialize the controller (includes creation of the scrap database, and handler registration). */
		virtual ErrorCode 						Initialize();
		/** Is this controller instance in a valid state. */
		virtual bool16							IsValid() const;
		/** Release referenced objects and destroy database, or return it to a known empty state */
		virtual void								Cleanup();
		
	// ----- Memory purge
	public:
		/** Purge handler */
		virtual void 								Purge(int32 level);
		/** static purge handler */
		static void 								Purge(int32 level, void *refPtr);
			
		void AllowPurge()
			{ ++fAllowPurge; }
		void DisallowPurge()
			{ --fAllowPurge; }
		bool PurgeIsAllowed() const
			{ return fAllowPurge == 0; }

	// ----- Support for testing
	friend class DataExchangeTest;
	
	protected:
		// ----- Internal Queries
		/** Given a dataobject with external data and a desired internal flavor, query for a handler that can perform this operation

			@param whichItem IN data object representing the external data
			@param response OUT response from the returned handler
			@param toFlavor IN desired flavor for the data to be converted to
			@return the handler best suited to perform the internalization
		*/
		virtual IDataExchangeHandler* 	QueryHandlerToInternalizeData(IPMDataObject* whichItem, DataExchangeResponse& response, const PMFlavor& toFlavor) const;
		/** Given a dataobject with external data and a desired internal flavor, query for a handler that can perform this operation

			@param dataIter IN iterator over the data objects representing the external data
			@param response OUT response from the returned handler
			@param toFlavor IN desired flavor for the data to be converted to
			@return the handler best suited to perform the internalization
		*/
		virtual IDataExchangeHandler* 	QueryHandlerToInternalizeData(DataObjectIterator& dataIter, DataExchangeResponse& response, const PMFlavor& toFlavor) const;

		// ----- Initialization
		/** Return the bossID of the doc boss to use, default is kScrapDocBoss */
		virtual ClassID							GetScrapDocBossID() const;		

		/** Return name to use for this scrap db file	- must be unique to each controller implementation */
		virtual PMString					GetScrapDBFileName() const = 0;	
		/** Create the actual database. This solves a link circularity. Subclasses must set magic bytes to something appropriate! */
		virtual IDataBase*					CreateDataBase() const = 0;		
		/** Set the database's magic bytes. This solves a link circularity. Subclasses must set magic bytes to something appropriate! */
		virtual void						ResetMagicBytes() const = 0;		

		/** Initialize scrap to a standard state. Similar to document initialization, uses document signal responders and sends kDuringNewScrapDocSignalResponderService signal*/
		virtual ErrorCode						InitializeScrap();				
		/** Revert scrap database back to the standard state. */
		virtual ErrorCode						RevertScrap();					
		
		/**  Add standard colors, styles etc. to scrap. */
		virtual void								RunNewScrapResponders();		//
				
	protected:
		// ----- Scrap database
		bool16										fInitialized;
		ErrorCode									fInitializationErrorCode;
		IDataBase*								fScrapDB;
		UID											fScrapDocID;
		bool16										fScrapDBFailed;
		IPMUnknown*									fRoot;
		int32										fAllowPurge;
		
		// ----- Scrap handlers
		bool16										fDataHandlersRegistered;
		K2Vector<DataExchangeHandlerEntry>	fDataHandlers;
		
		// ----- Active handler
		IDataExchangeHandler*				fActiveHandler;
		IDataExchangeHandler*				GetActiveHandler() const {return fActiveHandler;}

		// ----- cached handler from last query
		virtual IDataExchangeHandler*	QueryCachedHandler() const;
		virtual void								SetCachedHandler(IDataExchangeHandler* handlerToCache);
		IDataExchangeHandler*				fCachedHandler;

	DECLARE_HELPER_METHODS()
};

#pragma export off


#endif
