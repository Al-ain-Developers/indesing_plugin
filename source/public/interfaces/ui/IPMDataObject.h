//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPMDataObject.h $
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
//  Interface definition for data objects used in clipboard and drag and drop operations
//  
//========================================================================================

#pragma once
#ifndef __IPMDataObject__
#define __IPMDataObject__

#include "IPMUnknown.h"
#include "PMFlavorTypes.h"
#include "K2Vector.h"
#include "DragDropID.h"

#ifdef WINDOWS
	#include <objbase.h>
#endif

/** Interface used to represent the data in a data exchange operation.

		Subclassed to handle communication with platform data exchange frameworks.
		Subclasses should derive from the shared implementation class CPMDataObject.
		On Win WPMDataObject represents all OLE based data exchange,
		while for the Mac there are separate MDragDropObject and MClipboardDataObject implementations.
*/
class IPMDataObject : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPMDATAOBJECT };

	public:
		/** Add a flavor to the item as a promise.

			@param newFlavor IN flavor to add
			@param flavorFlags IN flavor flags, if any
			@precondition DESCRIPTION
			@postcondition DESCRIPTION
		*/
		virtual void 						PromiseFlavor(ExternalPMFlavor newFlavor, PMFlavorFlags flavorFlags = kNormalFlavorFlag) = 0;
		
		/** Get the unique item id (unique within a single data exchange operation).
			@return the item id
		*/
		virtual uint32 					GetItemID() const= 0;

		/** Framework call to set the unique item id (unique within a single data exchange operation).
			@param id IN the id of the item
		*/
		virtual void	 					SetItemID(uint32 id) = 0;
#ifdef MACINTOSH
		/** Mac only APIs to get and set the pasteboard ref associated with the data object.
		    Used generally by the clipboard and drag drop operations
		 **/
		/** Mac Only: Get the PasteboardRef associated with the data object.
			@return the PasteboardRef
		*/
		virtual PasteboardRef				GetPasteboardRef() const = 0;

		/** Mac only: Framework call to set the PasteboardRef for the data object.
			@param PasteboardRef IN 
		*/
		virtual void	 					SetPasteboardRef(PasteboardRef) = 0;
#endif
#ifdef WINDOWS
		/** Win only: Get the OLE IDataObject associated with the data object.
			@return the IDataObject
		*/
		virtual IDataObject*			GetOLEItem() const = 0;
		
		/** Win only: Framework call to set the OLE IDataObject for the data object.
			@param obj IN
		*/
		virtual void	 					SetOLEItem(IDataObject* obj) = 0;
#endif
		
		/** Get the count of promised flavors.

			@return the count
		*/
		virtual uint16 		CountFlavors() const = 0;
		
		/** Get the list of promised flavors

			@return pointer to an internally cached list of promised flavors
		*/
		virtual K2Vector<ExternalPMFlavor>* GetPromisedFlavors() const = 0;
		
		/** Does this item support the requested flavor

			@param requestedFlavor IN the flavor of interest
			@return whether the specified flavor was promised
		*/
		virtual bool16					FlavorExists(ExternalPMFlavor requestedFlavor) const = 0;

		/** Does this item support the requested flavor - if true, also returns the priority and flavor flags.
			 Priority is determined by the order in which flavors are added to an item: highest are first, lowest are last.

			@param flavor IN the flavor of interest
			@return data exchange response
		*/
		virtual DataExchangeResponse	FlavorExistsWithPriority(ExternalPMFlavor flavor) const = 0;

		/** Get the size, in bytes, of the data associated with a flavor
			NOTE: if called for a promised flavor, it will trigger the promise to be fulfilled. This can be time consuming.

			@param flavor IN the flavor of interest
			@precondition the presence of the flavor should be verified first
			@return length in bytes of the flavor data
		*/
		virtual uint32 					GetSizeOfFlavorData(ExternalPMFlavor flavor) const = 0;

		// 
		/** Get a stream that can be used to read flavor data from the object.
			Called by the framework, clients are usually passed a stream when necessary.
			
			@param flavor IN the flavor of interest
			@precondition the presence of the flavor should be verified first
			@return readable stream
		*/
		virtual IPMStream* 			GetStreamForReading(ExternalPMFlavor flavor) = 0;
		
		/** Get a stream that can be used to write flavor data to the object
			Called by the framework, clients are usually passed a stream when necessary.

			@param flavor IN the flavor of interest
			@precondition the presence of the flavor should be verified first
			@return DESCRIPTION
		*/
		virtual IPMStream* 			GetStreamForWriting(ExternalPMFlavor flavor) = 0;
		
		/** Framework call signifying that the stream is no longer needed

			@param IPMStream* INOUT DESCRIPTION
			@precondition DESCRIPTION
			@postcondition DESCRIPTION
		*/
		virtual void						FinishedWithStream(IPMStream*) = 0;

		/** Intended use for this item. */
		enum {
		/** default */
		kUnspecifiedUsage = -1, 
		/** use to Internalize external data */
		kInternalizeUsage = 0, 
		/** use to Externalize internal data */
		kExternalizeUsage = 1};
		
		/** Framework call to get the intended use for this item

			@return one of kUnspecifiedUsage, kInternalizeUsage, or kExternalizeUsage
		*/
		virtual int16 					GetUsage() const= 0;

		/** Framework call to set the intended use for this item

			@param int16 IN one of kUnspecifiedUsage, kInternalizeUsage, or kExternalizeUsage
		*/
		virtual void	 					SetUsage(int16) = 0;
};

#endif
