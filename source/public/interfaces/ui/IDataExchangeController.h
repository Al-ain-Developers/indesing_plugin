//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDataExchangeController.h $
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
//  
//  Interface definition for our data exchange controllers
//  
//========================================================================================

#pragma once
#ifndef __IDataExchangeController__
#define __IDataExchangeController__

#include "IPMUnknown.h"
#include "IPMDataObject.h"
#include "IDataExchangeHandler.h"

#include "DragDropID.h"

class DataObjectIterator;

/** IDataExchangeController interface, represents the controlling entity in a data exchange operation, and the common behavior
		shared by all such controllers
		
		The partial implementation class CDataExchangeController should be used when deriving a new controller type.
		class CDataExchangeController. Implementations of IDataExchangeController provide the glue between various external
		data exchange mechanisms (Clipboard, drag drop, OSX services, external databases, etc) and the platform independent data exchange framework within InDesign.

		@see CDataExchangeController, IDragDropController, IClipboardController, IMacOSXServicesController
 */
class IDataExchangeController : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDATAEXCHANGECONTROLLER };

	public:
		/** Register all data exchange handlers, IDataExchangeHandler, for this controller
		*/
		virtual void					RegisterAllHandlers() = 0;

		// ----- Handler queries
		/** Query for the handler for a particular internal flavor (there can only be one handler per flavor)

			@param flavor IN which flavor
			@return the unique handler for this flavor (if present)
		*/
		virtual IDataExchangeHandler*	QueryHandler(const PMFlavor& flavor) const = 0;
		
		/** Query for a handler that can convert a specific external flavor into an internal one

			@param fromFlavor IN the source external flavor
			@param toFlavor IN the desired flavor
			@return the unique handler for toFlavor (if it can perform the desired conversion, nil otherwise)
		*/
		virtual IDataExchangeHandler* 	QueryHandler(const ExternalPMFlavor& fromFlavor, const PMFlavor& toFlavor) const = 0;

		/** Query for the handler best suited to internalize data.
				Since no context is specified to identify the data to be internalized - this method is overridden in the 
				controller subclasses to apply to the data in the current drag, or clipboard operation.

			@param response OUT the response from the handler best suited to internalize the data
			@param internalizeToThisFlavor IN the desired destination flavor for the data, or kNoFlavor to let the framework choose the best one.

			@return a handler (if any) capable of performing the internalization.
		*/
		virtual IDataExchangeHandler*	QueryHandlerForInternalize(DataExchangeResponse& response, const PMFlavor& internalizeToThisFlavor = kNoFlavor) const = 0;

		/** Query for the active handler.

			@return the active handler or nil if one has not been set.
		*/
		virtual IDataExchangeHandler*	QueryActiveHandler() const = 0;
		
		/** Set the active handler.
			The active handler is usually set for the duration of a data exchange operation

			@param activeHandler IN the handler to become active, or nil to clear the active handler.
		*/
		virtual void					SetActiveHandler(IDataExchangeHandler* activeHandler) = 0;

		/** Render the contents of a data item to the given external data format.
				FulfillPromise is called by the framework in response to an external request for a specific flavor.

			@param whichItem IN the IPMDataObject representing the data to be exchanged.
			@param whichFlavor IN which flavor to provide data for
			@return kSuccess or an error code
		*/
		virtual ErrorCode				FulfillPromise(IPMDataObject* whichItem, const ExternalPMFlavor& whichFlavor) const = 0;

		/**  Is external data waiting to be internalized? This method is useful for clients that would like
			to peek at the actual data to be pasted/dropped/whatever if it has already been internalized, or is internal data. 
			Internalizing can be expensive and should not be called to give user feedback (i.e. menu enabling, drag feedbacck)

			@return kTrue if external data is awaiting internalization
		*/
		virtual bool16					NeedsToInternalize() const = 0;

		/** Return the database . 
				This is the database where the data exchange handlers and thus where the scrap data (used to store the internalized 
				contents of the clipboard, drag/drop, etc.) resides.
				Note that this is NOT the same as calling GetDataBase on the IDataExchangeController, 
				which will likely return the application database.

			@return the database used to maintain the "scrap" for this controller
		*/
		virtual IDataBase*				GetScrapDataBase() const = 0;

		/** Initialize the controller and the scrap database

			@return kSuccess or an error code
		*/
		virtual ErrorCode				Initialize() = 0;
		
		/** Is the controller in a valid state.
				Typically IsValid makes sure the controller has been initialized and that the scrap database is OK.

			@return kTrue if in a valid state
		*/
		virtual bool16					IsValid() const = 0;
		
		/** Cleanup the controller.  Usually called at shutdown
				Release any referenced handlers and delete the scrap database (or revert it to a pristene state if it persists).
		*/
		virtual void					Cleanup() = 0;
		
		/**	Get a list of all internalizeable flavors (compute by iterating over the registered handlers)

			** FOR INTERNAL USE ONLY **
		*/
		virtual void					GetInternalizeableFlavors(OrderedFlavorList &flavorList) const = 0;
};

#endif
