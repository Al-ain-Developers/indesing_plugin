//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPMDataObject.h $
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
//  Common implementation interface for data exchange objects
//  
//========================================================================================

#pragma once
#ifndef __CPMDataObject__
#define __CPMDataObject__

#include "IPMDataObject.h"
#include "IFlavorData.h"
#include "ISession.h"
#include "HelperInterface.h"


//========================================================================================
// CLASS CPMDataObject
//========================================================================================
#pragma export on

/** This enum is used to signal to streams used in DataExchange operations.
		These states are used to avoid the confusion a stream can encounter when
		they are opened and closed multiple times by some of the exporters, like PDF.
		Streams used for DataExchange are guaranteed to see kOpenAndInitialize and kCloseAndFinalize 
		exactly once per externalization of a flavor. 
		The eFlavorStreamState data is stored in the IIntData interface attached to the IPMDataObject's boss.
*/
enum eFlavorStreamState
{
	kUnknownState = 0x0000,
	kOpenAndInitialize = 0x0001,
	kOpenedState = 0x0002,
	kCloseAndFinalize = 0x0003
};
	
/** A data object is the representation for the external data in a data exchange operation.
		CPMDataObject is the shared base implementation for Clipboard, DragDrop, Mac OSX Services and LibraryScrap data objects. 
		CPMDataObject should also serve as the base class for all custom data exchange controller implementations
 		
 		@see IPMDataObject
*/
class PUBLIC_DECL CPMDataObject : public IPMDataObject
{
	public:
												CPMDataObject(IPMUnknown *boss);
		virtual								~CPMDataObject();
	
		virtual uint32 					GetItemID() const;
		virtual void	 					SetItemID(uint32 id);
#ifdef MACINTOSH
		virtual PasteboardRef				GetPasteboardRef() const;
		virtual void	 					SetPasteboardRef(PasteboardRef);
#endif
#ifdef WINDOWS
		virtual IDataObject*			GetOLEItem() const;
		virtual void	 					SetOLEItem(IDataObject* obj);
#endif

		/** Get the priority/flags of the requested flavor. (Must be overridden) */
		virtual DataExchangeResponse	FlavorExistsWithPriority(ExternalPMFlavor flavor) const;

		/** Get a stream that can be used to read flavor data from the object */
		virtual IPMStream* 			GetStreamForReading(ExternalPMFlavor flavor);
		/** Get a stream that can be used to write flavor data to the object */
		virtual IPMStream* 			GetStreamForWriting(ExternalPMFlavor flavor);
		/** Let the object know that we are finished with the stream */
		virtual void						FinishedWithStream(IPMStream*);

		// Intended use for this item
		virtual int16 					GetUsage() const;
		virtual void	 					SetUsage(int16);

	protected:
		/** Standard implementation for stream creation.
				Subclassers should only override this methods if they don't use the standard interface ID 
				for their read stream (IID_IPMSTREAM_FLAVOR_READ), or if the streams are obtained from a different object/boss.
		*/
		virtual IPMStream*			QueryForReadingStream();
		/** Standard implementation for stream creation.
				Subclassers should only override this methods if they don't use the standard interface ID 
				for their read stream (IID_IPMSTREAM_FLAVOR_WRITE), or if the streams are obtained from a different object/boss.
		*/
		virtual IPMStream*			QueryForWritingStream();

		/** A helper method to make sure non-zero length data exists before opening a read stream. 
				Default implementation calls GetSizeOfFlavorData.
		*/
		virtual bool16					CanReadPromisedFlavor(ExternalPMFlavor flavor);

	protected:
		uint32								fItemReference;
		IPMStream*						fReadStream;
		ExternalPMFlavor				fReadStreamFlavor;
		IPMStream*						fWriteStream;
		ExternalPMFlavor				fWriteStreamFlavor;
		int16								fUsage;
		
#ifdef MACINTOSH
		PasteboardRef						fPasteboardRef;
#endif
#ifdef WINDOWS
		IDataObject*						fCOMDataObject;
#endif
		
		DECLARE_HELPER_METHODS()
};


#pragma export off
#endif
