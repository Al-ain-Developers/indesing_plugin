//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocumentSignalData.h $
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
#ifndef __IDOCUMENTSIGNALDATA__
#define __IDOCUMENTSIGNALDATA__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "DocumentID.h"


class ICommand;

/**
	Purpose: Data sent with the New document signals (and also Open, Close, Save, Save As, Revert signals). 
	Use by responders to retrieve information during their Respond method in response to various document signals.
	Typical signals are found in DocumentID.h (kBeforeNewDocSignalResponderService, kDuringNewDocSignalResponderService, etc.)
	To receive one of these signals you must implement a service provider that returns the signal(s) that you are
	interested in, then implement a responder that implements the Respond method that will be called at the
	designated time.
 */
class IDocumentSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDOCUMENTSIGNALDATA };
	
	/**	Set up the signal data for the current document signal action.
		@param *documentCmd the command sending the signal, may be nil.
		@param &file the IDFile for the document in question. 
		@param &doc the UIDRef for the document in question. May be IDRef::gNull.
		@param uiflags 
	 */
	virtual void Set(ICommand *documentCmd, const IDFile &file, const UIDRef &doc, K2::UIFlags uiflags) = 0;
	
	/**	Return the command being executed. 
		@param none
		@return ICommand 
	 */
	virtual ICommand *GetCommand() const = 0;

	/**	Return the associated file. May be an empty IDFile.
		@param none
		@return const IDFile& a reference to the file.
	 */
	virtual const IDFile &GetFile() const = 0;		

	/**	Return the associated document.
		@param none
		@return const UIDRef& UIDRef of the document. May be UIDRef::gNull.
	 */
	virtual const UIDRef &GetDocument() const = 0;		

	/**	Return the specified UI behavior. Responder may choose to use this it if posts any alerts or warnings.
		@param none
		@return const K2::UIFlags the UI flags in effect.
	 */
	virtual const K2::UIFlags GetUIFlags() const = 0;

	/** Set the UI flags */
	virtual void SetUIFlags(UIFlags uiFlags) = 0;

	/**	Return if document being operated on is a cloned document.
		@param none
		@return kTrue if document being operated on is a cloned document. kFalse for normal document
	 */
	virtual bool16 GetDocumentClone() const = 0;

	/** Set the docuemnt clone flags
		@param clonedDocument kTrue if document being operated on is a cloned document
	*/
	virtual void SetDocumentClone(bool16 clonedDocument) = 0;
};

#endif // __IDOCUMENTSIGNALDATA__

