//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDataExchangeHandlerFor.h $
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
#ifndef __CDataExchangeHandlerFor__
#define __CDataExchangeHandlerFor__

#include "CPMUnknown.h"

#include "IDataExchangeHandler.h"

//========================================================================================
// class CDataExchangeHandlerFor
//		Usage is something like this:
//		
//		#include "CDataExchangeHandlerFor.h"
//
//		class MyDataExchangeHandler : public CDataExchangeHandlerFor {
//			MyDataExchangeHandler(IPMUnknown* boss) : CDataExchangeHandlerFor(boss) {fPMFlavor = kMyPMFlavor;}
//			virtual ~MyDataExchangeHandler() {}
//		};
//
//		CREATE_PMINTERFACE(MyDataExchangeHandler, kMyDataExchangeHandlerImpl)
//========================================================================================
#pragma export on

/** Helper class to make it easier for clients to create simple DataExchangeHandlers. And for me to update them.

		@see IDataExchangeHandler
*/
class PUBLIC_DECL CDataExchangeHandlerFor : public CPMUnknown<IDataExchangeHandler>
{
public:
		typedef CPMUnknown<IDataExchangeHandler> Inherited;
		
		CDataExchangeHandlerFor(IPMUnknown *boss);
		virtual						~CDataExchangeHandlerFor();

		/** Do scrap database initialization for this handler. Default implementation does nothing.*/
		virtual void				CreateScrapStorage();
		/** Override this method to specify the internal PMFlavor this handler represents.*/
		virtual	PMFlavor 		GetFlavor() const = 0;
		
		/** Override this method to examine external flavors in data object to see if this handler can convert them.
				Default implementation only knows about the flavor returned by GetFlavor().
		*/
		virtual DataExchangeResponse	CanInternalizeData(IPMDataObject* whichItem) const;
		
		/** Override this method to return whether this handler can convert the specified external flavor.
				Default implementation only knows about the flavor returned by GetFlavor().
		*/
		virtual	bool16 			CanConvertExternalFlavor(ExternalPMFlavor fromWhichFlavor) const;

		/** Override this method to add to the list, the set of flavors thus handler can convert from.
				Default implementation does nothing.
		*/
		virtual void				AddInternalizeableFlavorsToList(OrderedFlavorList& flavorList) const;
		
		/** Override this method to add to the list, the set of flavors thus handler can convert to.
				Default implementaton does nothing.
		*/
		virtual void				AddExternalizeableFlavorsToList(OrderedFlavorList& flavorList) const;

		/** Override this method to clear all data retained by the handler.
				Default implementation does nothing.
		*/
		virtual void				Clear();
		
		/** Override this method to return whether or not the handler is empty, or if it contains internalized flavor data.
				Default implementation returns kTrue.
		*/
		virtual bool16			IsEmpty() const;
		
	// ----- Conversion to platform drag manager
	public:
		/** Override this method to externalize the promises made for the data object.
				Default implementation does nothing.
		*/
		virtual ErrorCode		ExternalizePromises(IPMDataObject* whichItem);

		/** Override this method to externalize the data object to the specified external flavor, writing to the given stream.
				Default implementation asserts, but otherwise does nothing.
		*/
		virtual ErrorCode		Externalize(IPMDataObject* whichItem, ExternalPMFlavor toWhichFlavor, IPMStream* s);

		/** Override this method to internalize the data from a data object.
				Default implementation asserts, but otherwise does nothing.
		*/
		virtual ErrorCode		Internalize(IPMDataObject* whichItem);

		/** Override this method to internalize the data from a data object using a specified external flavor, reading from the given stream.
				Default implementation asserts, but otherwise does nothing.
		*/
		virtual ErrorCode		Internalize(IPMDataObject* whichItem, ExternalPMFlavor fromWhichFlavor, IPMStream* s);
};

#pragma export off
#endif //__CDataExchangeHandlerFor__
