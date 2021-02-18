//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDataExchHandlerFlavorHelper.h $
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
//  Interface definition for Data Exchange handler extensibility
//  
//========================================================================================

#pragma once
#ifndef __IDataExchHandlerFlavorHelper__
#define __IDataExchHandlerFlavorHelper__

#include "DragDropID.h"
#include "DragDropConstants.h"
#include "PMFlavorTypes.h"

class IDataExchangeHandler;
class IPMDataObject;

/** The IDataExchangeHandlerFlavorHelper interface provides extensibility for data exchange handlers.

		Data exchange handler extensibility requires the handler be derived from CDataExchangeHandler_Extensible.  
		Create a new boss with an IDataExchangeHandlerFlavorHelper implementation combined with a IK2ServiceProvider 
		implementation that corresponds to the service ID defined by the extensible handler.
		
		When the framework asks an extensible data exchange handler if it can internalize (or externalize) data, 
		the extensible handler then asks each of it's flavor helpers if they could perform the conversion. 
		One helper is chosen based on it's willingness to perform the conversion, and in the case of multiple helpers, 
		prioritized by helper type and the priority of the flavor they propose to conversion. The extensible handler then 
		forwards the subsequent method calls that occur during the conversion to the chosen helper.
		
		@see CDataExchangeHandlerFor, CDataExchangeHandler_Extensible, IDataExchangeHandlerFlavorHelper, IK2ServiceProvider
 */
class IDataExchangeHandlerFlavorHelper : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDATAEXCHANGEHANDLERFLAVORHELPER };

		/** Return the type or priority of the helper.
				This is used to resolve conflicts that can arise when more than one handler flavor helper is 
				capable of responding to a request. The presence of multiple helpers is not a conflict,
				a conflict would arise when one helper wants to replace or augment what another helper already does.
		
			@return helper type appropriate for this helper. Use DataExchange::kDefaultHelper by default.
		*/
		virtual DataExchange::eHelperType	
									GetHelperType() const = 0;

		/** Can this helper convert the given external flavor to the handlers native type?

			@param handler IN handler this helper is associated with
			@param fromWhichFlavor IN the external flavor to be converted
			@return response containing kTrue/False, plus and additional conversion information (flags, priority)
		*/
		virtual DataExchangeResponse CanConvertExternalFlavor(const IDataExchangeHandler*, ExternalPMFlavor fromWhichFlavor) const = 0;

		/** Can this helper produce the given external flavor from the handlers native type?

			@param handler IN handler this helper is associated with
			@param toWhichFlavor IN the external flavor to be produced
			@return response containing kTrue/False, plus and additional conversion information (flags, priority)
		*/
		virtual DataExchangeResponse CanProduceExternalFlavor(const IDataExchangeHandler*, ExternalPMFlavor toWhichFlavor) const = 0;

		/** Add promises for flavors that can be produced externalization promises (for clipboard , drag/drop, services, etc).
				Promised should be added to the end of the list, in order by quality of the conversion. 
				Override handlers may also reorder exiting items and/or remove previously added promises at this time.
				The helper function AppendPromiseIfUnique should be used.

			@param handler IN handler this helper is associated with
			@param whichItem IN item the flavors will be added to (not not here)
			@param orderedPromiseList IN/OUT add promises to the end of list
		*/
		virtual void				AddPromisesForExternalize(IDataExchangeHandler*, const IPMDataObject* whichItem, OrderedPromiseList& orderedPromiseList) = 0;
		
		/** Get the external flavors that can be converted during Internalize
				Flavors should be added to the end of the list, in order by quality of the conversion (highest quality first).
				The helper function AppendFlavorIfUnique should be used.

			@param handler IN handler this helper is associated with
			@param flavorList IN/OUT add flavors to the end of list 
		*/
		virtual void				AddInternalizeableFlavorsToList(const IDataExchangeHandler*, OrderedFlavorList& flavorList) const = 0;
		
		/** Get the external flavors that can be produced in Externalize
				Flavors should be added to the end of the list, in order by quality of the conversion (highest quality first). 
				The helper function AppendFlavorIfUnique should be used.

			@param handler IN handler this helper is associated with
			@param flavorList IN/OUT add flavors to the end of list 
		*/
		virtual void				AddExternalizeableFlavorsToList(const IDataExchangeHandler*, OrderedFlavorList& flavorList) const = 0;

		/** Externalize the contents into the given flavor on a stream (for clipboard and drag/drop).

			@param handler IN handler this helper is associated with
			@param whichItem IN item the data is associated with
			@param toWhichFlavor IN the type of flavor data to write on the stream
			@param s IN stream on which to write the data
			@return kSuccess or error code in case of failure
		*/
		virtual ErrorCode		Externalize(IDataExchangeHandler*, IPMDataObject* whichItem, ExternalPMFlavor toWhichFlavor, IPMStream* s) = 0;
		
		/** Internalize the contents of a stream as the given flavor (for clipboard or drag/drop).

			@param handler IN handler this helper is associated with
			@param whichItem IN item the data is associated with
			@param fromWhichFlavor IN the type of flavor data in on the stream
			@param s IN stream from which to read the data
			@return kSuccess or error code in case of failure
		*/
		virtual ErrorCode		Internalize(IDataExchangeHandler*, IPMDataObject* whichItem, ExternalPMFlavor fromWhichFlavor, IPMStream* s) = 0;

		/** kOverrideFlavorPriorityHelpers Only: Prior to Internalizing, these helpers are given an opportunity to reorder the available flavors
				advertised by the data exchange handler this helper is associated with.
				Reordering should be limited to reordering similar flavors (ie. to put PDF before PICT, or RFT before TEXT).

			@param handler IN handler this helper is associated with
			@param flavorList IN/OUT flavorlist to manipulate 
		*/
		virtual void 				ReorderFlavors(const IDataExchangeHandler*, OrderedFlavorList&) {}

};

#endif
