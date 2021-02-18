//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpTemplate.cpp $
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

// Interface includes:

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Provides a template code snippet.

	To use the template take the following steps.

	Make a copy of SnpTemplate.cpp and rename it according to the
	function of your snippet, for example SnpCreateFrame.cpp. 
	Verb-noun naming is recommended, CreateDocument, ModifyText,
	PerformDocumentAction and please use Snp prefix. The steps below
	use are based on the creation of snippet SnpCreateFrame.cpp.

	Add your snippet (SnpCreateFrame.cpp) to the SnippetRunner projects.

	Replace string "Template" with "CreateFrame". Note don't
	do the seemingly similar replace of "SnpTemplate" with 
	"SnpCreateFrame" or the name of your snippet in the user
	interface won't get set properly.

    There are normally two classes in a code snippet:
	\li SnpTemplate in which you define your functional code, and,
	\li _SnpRunnerTemplate using which you integrate your code snippet with
		the SnippetRunner framework.

	Edit the _SnpRunnerTemplate constructor code to describe your snippet to the framework.

	Edit the _SnpRunnerTemplate::CanRun method to check the preconditions
	your snippet requires are met.

	Edit the _SnpRunnerTemplate::Run method to get any parameters you want
	then instantiate and call your snippet.

	Edit your functional methods(s) into your SnpTemplate class.


  	@ingroup sdk_snippet

 */
class SnpTemplate
{
	public:
		/** TODO: Replace with functional method(s).
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode MyMethod(void);
};

/*
*/
ErrorCode SnpTemplate::MyMethod(void)
{
	ErrorCode result = kFailure;
	do {
		// TODO: add functional code.
		SNIPLOG("Add functional code");
		result = kSuccess;
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpTemplate available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerTemplate : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerTemplate();

		/** Destructor.
		 */
		virtual			~_SnpRunnerTemplate();

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

/* Describe your snippet to the framework here.
*/
_SnpRunnerTemplate::_SnpRunnerTemplate() : SnpRunnable("Template")
{
	// TODO: describe what your snippet does.
	this->SetDescription("Provides a template");

	// TODO: describe the preconditions your snippet requires.
	this->SetPreconditions("none");
	// e.g. "document open" or "layout selection set".

	// TODO: provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerTemplate::~_SnpRunnerTemplate()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerTemplate::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// TODO: query runnableContext for the selection target 
		// e.g. ILayoutTarget or ITextTarget. Or call
		// runnableContext to get the IActiveContext.
		// See ISnpRunnableContext for documentation.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerTemplate::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// TODO:
		// Use runnableContext to discover the selection target or IActiveContext if you need a context.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;

		// Perform your operation.
		SnpTemplate instance;
		status = instance.MyMethod();
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerTemplate instance_SnpRunnerTemplate;
DEFINE_SNIPPET(_SnpRunnerTemplate) 	
// TODO Add this line to SnpRunNoStrip.cpp
//      REFERENCE_SNIPPET(_SnpRunnerTemplate) 

// End, SnpTemplate.cpp

