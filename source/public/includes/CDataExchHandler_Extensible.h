//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDataExchHandler_Extensible.h $
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
//  base class implementation for extensible DataExchangeHandlers
//  
//========================================================================================

#pragma once
#ifndef __CDataExchangeHandler_Extensible__
#define __CDataExchangeHandler_Extensible__

#include "IDataExchangeHandler.h"
#include "PMFlavorTypes.h"
#include "HelperInterface.h"

#include "IDataExchHandlerFlavorHelper.h"

#pragma export on

/** Extensible implementation of the IDataExchangeHandler interface used in data exchange operations.
		Implementors of non-trivial IDataExchangeHandlers should derive from CDataExchangeHandler_Extensible, 
		unless they have a good reason to avoid extensibility.

		@see IDataExchangeHandler, IDataExchHandlerFlavorHelper
 */
class PUBLIC_DECL CDataExchangeHandler_Extensible : public IDataExchangeHandler
{
	public:
										CDataExchangeHandler_Extensible(IPMUnknown *boss);
		virtual						~CDataExchangeHandler_Extensible();
		
	public:
		// ----- Initialization
		virtual void 				CreateScrapStorage() = 0;
		// Call this to create storage for the scrap in a new database.

		// ----- Extensibility
		virtual ServiceID 		GetDEHandlerHelperServiceID() const = 0;

		// ----- Abilities
		/** @name eActionType
				enumeration of the different actions an IDataExchHandlerFlavorHelper can be called upon to perform
		*/
		enum eActionType		{kInternalizeFlavorAction, kExternalizeFlavorAction};
		
	public:
		virtual void				Clear() = 0;
		virtual bool16			IsEmpty() const = 0;
		
		// Return the Internal flavor (data type) this handler deals with.
		virtual PMFlavor 		GetFlavor() const = 0;
		
		/** @name Support for Extensibility
				The following methods have been overridden to delegate to the flavor helpers associated with this handler.
				Framework use only - subclasses should not override these methods.
		*/
		//@{
		/** Can this handler convert the data to it's internal flavor? */
		virtual DataExchangeResponse CanInternalizeData(IPMDataObject* whichItem) const;
		/** Can this handler convert from an external flavor to it's internal flavor? */
		virtual bool16	 		CanConvertExternalFlavor(ExternalPMFlavor fromWhichFlavor) const;
		/** Get the external flavors that can be converted during Internalize. */
		virtual void				AddInternalizeableFlavorsToList(OrderedFlavorList& flavorList) const;
		/** Get the external flavors that can be produced in Externalize. */
		virtual void				AddExternalizeableFlavorsToList(OrderedFlavorList& flavorList) const;

	// ----- Conversion to platform data exchange
	public:
		/** Make Externalization promises. */
		virtual ErrorCode		ExternalizePromises(IPMDataObject* whichItem);
		/** Externalize the contents into the given flavor on a stream. */
		virtual ErrorCode		Externalize(IPMDataObject* whichItem, ExternalPMFlavor toWhichFlavor, IPMStream* s);
		/** Internalize the data item. */
		virtual ErrorCode		Internalize(IPMDataObject* whichItem);
		/** Internalize the contents of a stream as the given flavor. */
		virtual ErrorCode		Internalize(IPMDataObject* whichItem, ExternalPMFlavor fromWhichFlavor, IPMStream* s);
		//@}

	protected:
		/** Gather the promises to be externalized from the helpers */
		ErrorCode					Delegate_ExternalizePromises(IPMDataObject* whichItem, OrderedPromiseList& orderedPromiseList);

		/** Find the best helper for internalization */
		IDataExchangeHandlerFlavorHelper* QueryBestHelperForInternalize(IPMDataObject* whichItem, DataExchangeResponse& bestHelperResponse) const;
		/** Find the best helper for a specific flavor conversion */
		IDataExchangeHandlerFlavorHelper*	QueryHelper_ForAction(eActionType action, ExternalPMFlavor whichFlavor, DataExchangeResponse& bestHelperResponse) const;

	private:
		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
