//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateDocument.cpp $
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

// General includes:
#include "Utils.h"

// SDK includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"

#include "SnpCreateDocument.h"

/*
*/
ErrorCode SnpCreateDocument::Create(UIFlags	uiFlags,
	const	PMReal& width,
	const	PMReal& height,
	const	int32 numPages,
	const	int32 numPagesPerSpread
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
				numPagesPerSpread);
		if (documentUIDRef == UIDRef::gNull) {
			break;
		}
		// Open a view onto the document.
		result = helper.OpenLayoutWindow(documentUIDRef);
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpRunCreateDocument available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerCreateDocument : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerCreateDocument();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCreateDocument();

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
			
		/** Run my unit test
		*/
		ErrorCode RunUnitTest(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};
/* Constructor.
*/
_SnpRunnerCreateDocument::_SnpRunnerCreateDocument() : SnpRunnable("CreateDocument")
{
	this->SetDescription("creates a document and displays it in a window");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor.
*/
_SnpRunnerCreateDocument::~_SnpRunnerCreateDocument()
{
}

/*
*/
bool16	_SnpRunnerCreateDocument::CanRun(ISnpRunnableContext* runnableContext)
{
	// Can always create a new document.
	return kTrue;
}

/*
*/
ErrorCode _SnpRunnerCreateDocument::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// Get parameters.
		Utils<ISnipRunParameterUtils> parameterUtils;

		// Get UIFlags.
		// These UI flags will be passed to document signal data so that
		// new doc signal responders can check the UI Flags.
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

		// Create document.
		SnpCreateDocument	instance;
		status = instance.Create(uiFlags, width, height, pages, pagesPerSpread);
		
	} while(false);
	return (status);
}

/*
*/
ErrorCode	_SnpRunnerCreateDocument::RunUnitTest(ISnpRunnableContext* runnableContext)
{
	SnpCreateDocument	instance;
	return instance.Create(K2::kSuppressUI, 612.0, 792.0, 1, 1);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerCreateDocument instance_SnpRunnerCreateDocument;
DEFINE_SNIPPET(_SnpRunnerCreateDocument) 	
// End, SnpCreateDocument.cpp

