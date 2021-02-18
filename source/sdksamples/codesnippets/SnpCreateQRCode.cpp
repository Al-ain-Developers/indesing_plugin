//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateQRCode.cpp $
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
//  Copyright 2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Snippet runner includes
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

#include "ISelectionUtils.h"
#include "IControlView.h"
#include "ILayoutControlData.h"

// QR Code include
#include "IBarcodeSuite.h"

/**
  * \li Creates a QR Code
  *
  * @ingroup sdk_snippet
  */
class SnpCreateQRCode
{
	public:
		// Constructor.
		SnpCreateQRCode() {}

		// Destructor.
		virtual ~SnpCreateQRCode() {}

        ErrorCode CreatePlainTextQRCode(PMString theString);
		ErrorCode CreateHyperlinkQRCode(PMString url);
		ErrorCode CreateSMSQRCode(PMString to, PMString message);
};

// Creates a QR code for some plain text.
// This will load the place gun if there is no active selection.
ErrorCode SnpCreateQRCode::CreatePlainTextQRCode(PMString theString)
{
    ErrorCode status = kFailure;
    
    do {
        InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
        InterfacePtr<IBarcodeSuite> barcodeSuite(selectionManager, UseDefaultIID());
        
        if (!barcodeSuite)
        {
            break;
        }
        
        IQRCodeMetaData::ErrorLevel errorLevel = IQRCodeMetaData::kM;
        status = barcodeSuite->CreateQRCodePlainTextFromSelection(theString, errorLevel, kInvalidUID);

    } while (false);
    
    return status;
}

// Creates a QR for an SMS message.
// This will load the place gun if there is no active selection.
ErrorCode SnpCreateQRCode::CreateSMSQRCode(PMString to, PMString message)
{
    ErrorCode status = kFailure;
    
    do {
        InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
        InterfacePtr<IBarcodeSuite> barcodeSuite(selectionManager, UseDefaultIID());
        
        if (!barcodeSuite)
        {
            break;
        }
        
        IQRCodeMetaData::ErrorLevel errorLevel = IQRCodeMetaData::kM;
		status = barcodeSuite->CreateQRCodeSmsFromSelection(to, message, errorLevel, kInvalidUID);

    } while (false);
    
    return status;
}

// Creates a QR code for a URL.
// This will load the place gun if there is no active selection.
ErrorCode SnpCreateQRCode::CreateHyperlinkQRCode(PMString url)
{
    ErrorCode status = kFailure;
    
    do {
        InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
        InterfacePtr<IBarcodeSuite> barcodeSuite(selectionManager, UseDefaultIID());
        
        if (!barcodeSuite)
        {
            break;
        }
        
        IQRCodeMetaData::ErrorLevel errorLevel = IQRCodeMetaData::kM;
		status = barcodeSuite->CreateQRCodeHyperLinkFromSelection(url, errorLevel, kInvalidUID);

    } while (false);
    
    return status;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpCreateQRCode available to the SnippetRunner framework.
  *
  * @ingroup sdk_snippet_run
  */
class _SnpCreateQRCode : public SnpRunnable
{
	public:
		// Constructor.
		_SnpCreateQRCode();

		// Destructor.
		virtual			~_SnpCreateQRCode();

		/** Return kTrue if the snippet can run.
		  * @param runnableContext see ISnpRunnableContext for documentation.
		  * @return kTrue if snippet can run, kFalse otherwise
		  */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
		  *	@param runnableContext see ISnpRunnableContext for documentation.
		  * @return kSuccess on success, other ErrorCode otherwise.
		  */
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** 
		  * get the snippet context
		  * @return eSnpRunContextType for this snippet
		  */
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/* 
 * Describes this snippet to the snippet runner framework - 
 * common to all snippets.
 */
_SnpCreateQRCode::_SnpCreateQRCode() : SnpRunnable("CreateQRCode")
{	
	this->SetDescription("Creates a QR code");
	this->SetPreconditions("Open document");
	this->SetCategories("sdk_snippet");
}

_SnpCreateQRCode::~_SnpCreateQRCode()
{

}

/* 
 * Check if there is a document open.
 */
bool16 _SnpCreateQRCode::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	IDocument *doc = runnableContext->GetActiveContext()->GetContextDocument();
	if (doc)
	{
		result = kTrue;
	}
	return result;
}

/* 
 * The main functionality of the snippet. 
 * This is where we prompt the user for input parameters
 * and then call into code to create the QR code accordingly.
 */
ErrorCode _SnpCreateQRCode::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;

	do {
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.clear();
		choices.push_back(PMString("Plain text"));
		choices.push_back(PMString("A URL"));
		choices.push_back(PMString("An SMS message"));
		enum {plaintext, hyperlink, sms};

		int32 choice  = parameterUtils->GetChoice("What would you like to create a QR Code for?", choices);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		// create a new instance of the snippet
		SnpCreateQRCode instance;

		if (choice == plaintext)
		{
			PMString theString = parameterUtils->GetPMString("Enter text:");
			if (parameterUtils->WasDialogCancelled()) 
			{
				break;
			}
			status = instance.CreatePlainTextQRCode(theString);
		}
		else if (choice == hyperlink)
		{
			PMString url = parameterUtils->GetPMString("Enter URL:");
			if (parameterUtils->WasDialogCancelled()) 
			{
				break;
			}
			status = instance.CreateHyperlinkQRCode(url);
		}
		else if (choice == sms)
		{
			PMString to = parameterUtils->GetPMString("Enter destination number:");
			if (parameterUtils->WasDialogCancelled()) 
			{
				break;
			}
			PMString message = parameterUtils->GetPMString("Enter message body:");
			if (parameterUtils->WasDialogCancelled()) 
			{
				break;
			}
			status = instance.CreateSMSQRCode(to, message);
		}
        
	} while(false);

	return status;
}

/*	
 * This is boilerplate code used by all snippets to register an 
 * instance of the snippet with the snippet runner framework.
 */
static _SnpCreateQRCode instance_SnpCreateQRCode;
DEFINE_SNIPPET(_SnpCreateQRCode) 	