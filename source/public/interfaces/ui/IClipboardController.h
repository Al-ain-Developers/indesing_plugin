//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IClipboardController.h $
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
#ifndef __IClipboardController__
#define __IClipboardController__

#include "CDataExchangeController.h"
#include "ShuksanID.h"
#include "DragDropID.h"

#include "IDataExchangeHandler.h"

#ifdef MACINTOSH
//#define USE_CARBONSCRAPCALLS	1
#endif

//========================================================================================
// Forward declarations
//========================================================================================

class IDataExchangeHandler;
class IDataBase;

//========================================================================================
// CLASS IClipboardController
//========================================================================================

/** IClipboardController interface, represents the controlling entity in a drag drop operation.
		
		IClipboardController is derived from IDataExchangeController by way of the partial implementation
		class CDataExchangeController. Implementations of IClipboardController provide the glue between the platform dependent
		clipboard (OLE and Mac OS X) and the platform independent framework presented by InDesign.

		@see IDataExchangeController, CDataExchangeController
 */
class IClipboardController : public CDataExchangeController
{
	public:
		enum { kDefaultIID = IID_ICLIPBOARDCONTROLLER };

	// ----- Constructor/Destructor
		IClipboardController(IPMUnknown *boss) : CDataExchangeController(boss) {};
		virtual ~IClipboardController() {};

	// ----- Active handler (compatibility methods - use QueryActiveHandler/SetActiveHandler instead)
	public:
		/** Use QueryActiveHandler instead (should be deprecated). */
		virtual IDataExchangeHandler*	QueryActiveScrapHandler() const = 0;
		/** Use SetActiveHandler instead (should be deprecated). 
				Note: SetActiveHandler/SetActiveScrapHandler can be called from IScrapSuite::CanCopy/Copy but is
				not appropriate during IScrapSuite::CanPaste/Paste - since Internalize may have already occurred.
				Calling SetActiveHandler would then effectively lose the already internalized data.
		*/
		virtual void				SetActiveScrapHandler(IDataExchangeHandler* activeHandler) = 0;

	// ----- Scrap Conversion
	public:
		/** Render the contents of the internal clipboard out to the platform clipboard.
				FulfillPromise is called by the data exchange framework in response a flavor data request from an external application.
				Internally it sets up a PMFlavorStream and calls the active handler to externalize the flavor to the stream. 

			@param whichItem IN the IPMDataObject representing the clipboard data.
			@param whichFlavor IN which flavor to provide data for
			@return kSuccess or an error code
		*/
		virtual ErrorCode 		FulfillPromise(IPMDataObject* whichItem, const ExternalPMFlavor& whichFlavor) const = 0;

		/** Advise framework as to whether the internal clipboard needs to be externalized.
				This is called when a copy or cut operation changes the internal clipboard,
				and also when an internalize call makes externalization unnecessary.
		*/
		virtual void				SetShouldExternalize(bool16 should = kTrue) = 0;

		/** Make all necessary flavor promises available to the external clipboard. 
				This makes the promises visible to other applications, and should be done on application context switch.
		*/
		virtual ErrorCode		Externalize() const = 0;

		/** Advise framework as to whether the platform clipboard needs to be internalized.
				This is called when the platform clipboard has changed from when we last internalized it,
				and also when an internalize call makes externalization unnecessary. This is called when switching 
				into our app from another application, and when a local copy or cut operation overrides the need to internalize
		*/
		virtual void				SetShouldInternalize(bool16 should = kTrue) = 0;

		/** Do we need to internalize pending external (platform) clipboard data? This method is useful
				for IScrapSuite::CanPaste and similar methods that would like to peek at the actual data to be pasted
				if it has already been internalized, or is internal data. Internalizing can be expensive and should not
				be called during menu enabling methods.
		*/
		virtual bool16			NeedsToInternalize() const = 0;

		/** Render the contents of the external clipboard into the scrap database. 
				This makes it possible to paste something into our app that was copied from another
				application. This should only be called when paste is actually called.
		*/
		virtual ErrorCode		Internalize() = 0;
			
		/** Return the preferred flavor of the contents of the external clipboard.
				Based on the convention of promising the preferred flavor first.

			@param preferredFlavor OUT the first (preferred) flavor in the platform clipboard
			@return kTrue if a flavor was returned, kFalse otherwise (empty clipboard, etc.)
		*/
		virtual bool16			GetPreferredClipboardFlavor(ExternalPMFlavor& preferredFlavor) = 0;

		/** Determine which data exchange handler could best handle the data on the clipboard.
				By passing a specific internal flavor, you are asking if the data on the clipboard can be converted into that flavor.
				By passing kNoFlavor, the controller will instead find the first handler which recognizes the data on the clipboard,
				regardless of the flavor of object it creates.

			@param response OUT response from the data exchange handler
			@param internalizedFlavor IN the preferred internal flavor (native format) if data needs to be converted.
			@return the handler (if any) that can provide the requested conversion.
		*/
		virtual IDataExchangeHandler*	QueryHandlerForInternalize(DataExchangeResponse& response, const PMFlavor& internalizedFlavor = kNoFlavor) const = 0;

		// ----- Clipboard Copy operations: PrepareForCopy and CopyHasCompleted
		/**	Should be called in the preamble to Copy or Cut operations.
				This is used to empty out the internal clipboard (and the external clipboard under Carbon)
				Since this also has the effect of calling SetShouldInternalize(kFalse), it should not be called
				prior to calling Internalize().
		*/	
		virtual ErrorCode	PrepareForCopy() = 0;

		/**	Should be called at the conclusion of Copy or Cut operations.
				This is used to make data promises to the external clipboard under Carbon/OS X. 
				On Win this is done at kSuspend time, but Carbon/OS X disallows this.
		*/
		virtual ErrorCode	CopyHasCompleted() = 0;
			
		/**	Return whether externalization to the external clipboard is already in progress.
		*/
		virtual bool16	IsExternalizeInProgress() const = 0;

		/** Returns whether a Cut operation is underway or not. 
			Helps distinguish between a Cut and a Copy for some clients.
		*/
		virtual bool16	IsCutOperation() const = 0;
		
		/** Sets whether a Cut operation is underway or not. 
			Helps distinguish between a Cut and a Copy for some clients.
			Most clients will not need to call this.
		*/
		virtual void	SetCutOperation(bool16 isCut)  = 0;

};

#endif
