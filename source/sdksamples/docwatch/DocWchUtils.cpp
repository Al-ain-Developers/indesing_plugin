//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/docwatch/DocWchUtils.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes

// Implementation includes
#include "CAlert.h"	
#include "StringUtils.h"
#include "DocWchUtils.h"
#include "DocWchID.h"

/** Initialize the static properties for the class */
bool16 DocWchUtils::fDocResponder = kFalse;



/* DwAlert
	Brings up CAlert with information message.
*/
void DocWchUtils::DwAlert(UIDRef docUIDRef, char* txtMsg)
{
	// Create and translate the message string.
	PMString msg(txtMsg, PMString::kTranslateDuringCall);

	// If a document name exists, put it in the message string.
	if (docUIDRef.GetDataBase() != nil)
	{
		// Get the document's name
		PMString docName;
		InterfacePtr<IDocument> docPtr(docUIDRef, UseDefaultIID());
		docPtr->GetName(docName);

		// Put the document's name in the alert message
		docName.Insert(" - ");
		msg.Append(docName);
		
		// Appending to msg cleared the translate bit.  We appended some
		// not-translatable text, so reset the translate flag.
		msg.SetTranslated();
	}

	// Put up the alert
	CAlert::InformationAlert(msg);
}


/* InitDocWchModes
	Initializes the properties for this class.
*/
void DocWchUtils::InitDocWchModes() 
{
	// Disable use of the document Responder.
	fDocResponder = kFalse;
}

// End, DocWchUtils.cpp.


