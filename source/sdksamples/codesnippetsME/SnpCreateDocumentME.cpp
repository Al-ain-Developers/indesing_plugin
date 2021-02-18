//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippetsME/SnpCreateDocumentME.cpp $
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
//  
//  Usage rights licenced to Adobe Inc. 1997 - 2010.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// General includes:
#include "LocaleSetting.h"
#include "ILayoutUtils.h"

// SDK includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"



// End Temporary includes:

/** 
	\li	How to create a new document and put it on view in a window,
	\li	uses SDKLayoutHelper to perform the document action,
	\li	the page dimensions, total number of pages and number of pages 
		in each spread can be given.

  	@ingroup sdk_snippet
	@ingroup sdk_layout
	@author Seoras Ashby
	@see SDKLayoutHelper
 */
class SnpCreateDocumentME : public SnpRunnable
{
	public:
		/** Create a document and put it on view in a window.

			@param uiFlags IN
			@param width IN width of page in points
			@param height IN height of page in points
			@param numPages IN number of pages
			@param numPagesPerSpread IN number of pages per spread
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode Create(const UIFlags uiFlags,
			const	PMReal& width, 
			const	PMReal& height, 
			const	int32 numPages, 
			const	int32 numPagesPerSpread,
			const	DocPageBinding binding
			);


	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		SnpCreateDocumentME();

		/** Destructor.
		 */
		virtual				~SnpCreateDocumentME();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/*
*/
/*
*/
ErrorCode SnpCreateDocumentME::Create(UIFlags	uiFlags,
	const	PMReal& width,
	const	PMReal& height,
	const	int32 numPages,
	const	int32 numPagesPerSpread,
	const	DocPageBinding binding
)
{
	ErrorCode result = kFailure;
	do {
		// Create the document using SDKLayoutHelper.
		SDKLayoutHelper helper;
		UIDRef documentUIDRef = helper.CreateDocument(uiFlags,
				width,
				height,
				numPages,
				numPagesPerSpread,
				binding);
		if (documentUIDRef == UIDRef::gNull) {
			break;
		}
		// Open a view onto the document.
		result = helper.OpenLayoutWindow(documentUIDRef);
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor.
*/
SnpCreateDocumentME::SnpCreateDocumentME() : SnpRunnable("CreateDocumentME")
{
	this->SetDescription("creates a document and displays it in a window");
	this->SetPreconditions("Must be running the R2L feature set.");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor.
*/
SnpCreateDocumentME::~SnpCreateDocumentME()
{
}

/*
*/
bool16	SnpCreateDocumentME::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	// check if this is running on the R2L feature set
    if ((LocaleSetting::GetLocale().GetLanguageFS() != kRightToLeftLanguageFS))
		return result;
	
	result = kTrue;

	return result;
}

/*
*/
ErrorCode SnpCreateDocumentME::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// Get parameters.
		Utils<ISnipRunParameterUtils> parameterUtils;

		// Get UIFlags.
		K2Vector<PMString> choices;
		choices.push_back(PMString("kSuppressUI"));
		choices.push_back(PMString("kMinimalUI"));
		choices.push_back(PMString("kFullUI"));
		K2::UIFlags uiFlags = (K2::UIFlags)(parameterUtils->GetChoice(PMString("UIFlags"), choices, K2::kFullUI));
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get width.
		PMReal width = parameterUtils->GetPMReal(PMString("Page width in points"), 612, 12, 15552);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get height.
		PMReal height = parameterUtils->GetPMReal(PMString("Page height in points"), 792, 12, 15552);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get number of pages.
		int32 pages = parameterUtils->GetInt32(PMString("Total number of pages"), 1, 1, 9999);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get number of pages per spread.
		int32 pagesPerSpread = parameterUtils->GetInt32(PMString("Number of pages per spread"), 1, 1, 10);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get page binding.
		K2Vector<PMString> binding_choices;
		binding_choices.push_back(PMString("kLeftToRightBinding"));
		binding_choices.push_back(PMString("kRightToLeftBinding"));
		DocPageBinding binding = (DocPageBinding)(parameterUtils->GetChoice(PMString("Binding"), binding_choices, kRightToLeftBinding));
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Create document.
		status = this->Create(uiFlags, width, height, pages, pagesPerSpread, binding);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
SnpCreateDocumentME instanceSnpCreateDocumentME;

// End, SnpCreateMEDocument.cpp
