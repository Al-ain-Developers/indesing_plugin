//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDataExchangeHandler.h $
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
//  Interface definition for handlers used to manage data for data exchange operations
//  
//========================================================================================

#pragma once
#ifndef __IDataExchangeHandler__
#define __IDataExchangeHandler__

#include "IPMUnknown.h"
#include "PMFlavorTypes.h"

#include "DragDropID.h"

class IPMDataObject;
class IPMStream;

/**
	This interface is used when exchanging data through the clipboard, drag drop, OSX services, libraries, external databases, etc.
	
	Each implementation of IDataExchangeHandler supports a unique native (internal) PMFlavor type. IDataExchangeHandler bosses live
	in the scrap databases associated with each IDataExchangeController, one copy of each handler boss will be found in each scrap database.
	The implementation of a given IDataExchangeHandler is extensible via the IDataExchangeHandlerFlavorHelper interface.

	@see CDataExchangeHandlerFor, CDataExchangeHandler_Extensible, IDataExchangeHandlerFlavorHelper
*/
class IDataExchangeHandler : public IPMUnknown
{
	public:
		/**
			Define the default IID for IDataExchangeHandler.
		*/
		enum { kDefaultIID = IID_IDATAEXCHANGEHANDLER };

	// ----- Initialization
	public:
		/**
			Create handler specific initial data (colors, styles, etc.) required for a new scrap database.

			@return void.
		*/
		virtual void 				CreateScrapStorage() = 0;

	// ----- Accessors
	public:
		/**
			Clear the data held by this handler.

			@return void.
		*/
		virtual void				Clear() = 0;

		/**
			Does the handler contain data, or is it empty.

			@return bool16 kTrue if it is empty, otherwise kFalse.
		*/
		virtual bool16			IsEmpty() const = 0;
		
		/**
			Get the Internal flavor (data type) this handler deals with.

			@return PMFlavor internal flavor this handler deals with.
		*/
		virtual PMFlavor 		GetFlavor() const = 0;
		
		/** 
			Check if this handler can convert external data to its internal flavor.

			@param whichItem the item to be internalized.
			@return DataExchangeResponse @see PMFlavorTypes.h for the definition of DataExchangeResponse. 
		*/
		virtual DataExchangeResponse CanInternalizeData(IPMDataObject* whichItem) const = 0;

		/** 
			Check if this handler can convert this type of external flavor to its internal flavor.

			@param fromWhichFlavor the kind of external flavor. @see PMFlavorTypes.h for the definition of ExternalPMFlavor.
			@return bool16 kTrue if it can convert, otherwise kFalse.
		*/
		virtual bool16	 		CanConvertExternalFlavor(ExternalPMFlavor fromWhichFlavor) const = 0;

		/**
			Get the external flavors that can be produced in Externalize, or converted during internalize.

			@param flavorList a list that are internalizeable.
			@return void.
		*/
		virtual void				AddInternalizeableFlavorsToList(OrderedFlavorList& flavorList) const = 0;

		/**
			Get the internal flavors that can be produced in Externalize, or converted during externalize.

			@param flavorList a list that are externalizeable.
			@return void.
		*/
		virtual void				AddExternalizeableFlavorsToList(OrderedFlavorList& flavorList) const = 0;

	// ----- Conversion to platform data exchange (clipboard and drag/drop)
	public:
		/**
			Make promises for data flavors this handler can produce during externalization (for clipboard and drag/drop, etc.).

			@param whichItem the item to be externalized.
			@return ErrorCode the result of the operation.
		*/
		virtual ErrorCode		ExternalizePromises(IPMDataObject* whichItem) = 0;

		/**
			Externalize handlers contents into the given flavor on a stream (for clipboard and drag/drop, etc.).

			@param whichItem the item to be externalized.
			@param toWhichFlavor the data in the item should be converted into this external flavor.
			@param s the stream that will hold externalized contents.
			@return ErrorCode the result of the operaiton. 
		*/
		virtual ErrorCode		Externalize(IPMDataObject* whichItem, ExternalPMFlavor toWhichFlavor, IPMStream* s) = 0;

		/**
			Internalize the data item (for clipboard or drag/drop).

			@param whichItem the item to be internalized.
			@return ErrorCode the result of the operation. 
		*/
		virtual ErrorCode		Internalize(IPMDataObject* whichItem) = 0;

		/**
			Internalize the contents of a stream as the given flavor (for clipboard or drag/drop, etc.).

			@param whichItem the item to be internalized.
			@param toWhichFlavor the data for the item will be converted from this external flavor.
			@param s the stream that will hold the internalized contents.
			@return ErrorCode the result of the operation.
		*/
		virtual ErrorCode		Internalize(IPMDataObject* whichItem, ExternalPMFlavor fromWhichFlavor, IPMStream* s) = 0;
};

#endif
