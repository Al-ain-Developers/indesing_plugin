//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunSuiteCSB.cpp $
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
#include "ILayoutControlData.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IControlView.h"
#include "ITableModel.h"
#include "ICellContent.h"
#include "IDocument.h"
#include "ITextStoryThread.h"
#include "ITableUtils.h"
#include "ISelectUtils.h"
#include "ILayoutTarget.h"
#include "ITextTarget.h"
#include "ITableTarget.h"

// General includes:
#include "CPMUnknown.h"
#include "TextChar.h"
#include "Utils.h"

// Project includes:
#include "SnipRunID.h"
#include "ISnipRunSuite.h"
#include "ISnpRunnableContext.h"
#include "ISnipRunParameterUtils.h"
#include "SnpRunnable.h"
#include "SnipRunManager.h"
#include "SnipRunLog.h"
#include "SDKLayoutHelper.h"
#include "SnpTextModelHelper.h"

#include "SnpCreateDocument.h"
#include "SnpCreateFrame.h"

/** ISnipRunSuite concrete selection boss(CSB) suite implementation,
	aggregated onto each CSB supported by the appication. Uses
	SnipRunManager to find and call the requested snippet.

	@ingroup snippetrunner
	
	@see ISnipRunSuite
 */
class SnipRunSuiteCSB : public CPMUnknown<ISnipRunSuite>
{
	public:
		/**	Constructor.
		*/
		SnipRunSuiteCSB(IPMUnknown* boss);

		/**	Destructor.
		*/
		virtual ~SnipRunSuiteCSB();	

		/** See ISnipRunSuite::GetSnippetNames.
		*/
		virtual void GetSnippetNames(SnippetNames& snippetNames) const;

		/** See ISnipRunSuite::IsRegistered.
		*/
		virtual bool16 IsRegistered(const SnippetName& snippetName) const;

		/** See ISnipRunSuite::GetCategories.
		*/
		virtual void GetCategories(const SnippetName& snippetName, K2Vector<PMString>& categories) const;

		/** See ISnipRunSuite::GetDescription.
		*/
		virtual void GetDescription(const SnippetName& snippetName, PMString& description) const;

		/** See ISnipRunSuite::GetPreconditions.
		*/
		virtual void GetPreconditions(const SnippetName& snippetName, PMString& preconditions) const;

		/** Uses SnipRunManager to get hold of the requested snippet,
			sets up the context and calls the snippet. 
			See ISnipRunSuite::CanRun for more documentation.
		*/
		virtual bool16 CanRun(const SnippetName& snippetName) const;		

		/** Uses SnipRunManager to get hold of the requested snippet,
			sets up the context and calls the snippet. 
			See ISnipRunSuite::Run for more documentation.
		*/
		ErrorCode Run(const SnippetName& snippetName, PMString& parameters, bool16 enableParameterDialog) const;

		/** 
			Set up the proper InDesign context for the snippert so that it
			can be run.
			@param runnableContext
			@return kSuccess on success, other ErrorCode otherwise
		*/
		virtual ErrorCode SetupContext(const SnippetName& snippetName);

	
	private:

		/**	Record the success or failure of a snipet to the log.
			@param snippetName IN
			@param status IN
		 */
		void	LogRunStatus(const SnippetName& snippetName, const ErrorCode& status) const;

		/**	Tokenise a string buffer.
			@param buf IN
			@param tokens OUT
			@param separator IN
		 */
		void	GetTokens(const PMString& buf, K2Vector<PMString>& tokens, const textchar separator) const;
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunSuiteCSB, kSnipRunSuiteCSBImpl)

/*
*/
SnipRunSuiteCSB::SnipRunSuiteCSB(IPMUnknown* boss) : CPMUnknown<ISnipRunSuite>(boss)
{
}

/*
*/
SnipRunSuiteCSB::~SnipRunSuiteCSB()
{
}

/*
*/
void SnipRunSuiteCSB::GetSnippetNames(SnippetNames& snippetNames) const 
{
	// Make sure the dictionary of registered snippets is sorted.
	SnipRunManager::Instance()->SortSnippets();
		
	// Get the dictionary of registered snippets.
	const SnipRunManager::SnippetDict& snippets = SnipRunManager::Instance()->GetSnippets();

	// Return their names to the caller.
	for (int32 i = 0; i < snippets.size(); i++) {
		SnpRunnable* runnable = snippets [i].Value();
		// 1036945: Only return snippets that want to make themselves 
		// available to be run by the framework. A snippet can be registered 
		// with SnipRunManager but not be presented in the UI because its 
		// CanLoad method returns kFalse.
		if (runnable && runnable->CanLoad()) {
			snippetNames.push_back(snippets [i].Key());
		}
	}

}

/*
*/
bool16 SnipRunSuiteCSB::IsRegistered(const SnippetName& snippetName) const
{
	bool16 result = kTrue;
	SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
	if (runnable == nil) {
		result = kFalse;
	}
	else {
		// 1036945: Since GetSnippetNames was changed only to return snippets
		// that want to be available to be run by the framework add the same
		// check here just to be consistent. 
		result = runnable->CanLoad();
	}
	return result;
}

/*
*/
void SnipRunSuiteCSB::GetCategories(const SnippetName& snippetName, Categories& categories) const
{
	SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
	ASSERT(runnable != nil);
	if (runnable != nil) {
		PMString categoriesAsCSV(runnable->GetCategories());
		this->GetTokens(categoriesAsCSV, categories, kTextChar_Comma);
	}
}

/*
*/
void SnipRunSuiteCSB::GetDescription(const SnippetName& snippetName, PMString& description) const
{
	SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
	ASSERT(runnable != nil);
	if (runnable != nil) {
		description = runnable->GetDescription();
	}
}

/*
*/
void SnipRunSuiteCSB::GetPreconditions(const SnippetName& snippetName, PMString& preconditions) const
{
	SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
	ASSERT(runnable != nil);
	if (runnable != nil) {
		preconditions = runnable->GetPreconditions();
	}
}

/*
*/
bool16 SnipRunSuiteCSB::CanRun(const SnippetName& snippetName) const
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ISnpRunnableContext> runnableContextSuite(this, UseDefaultIID());
		ASSERT(runnableContextSuite);
		if (!runnableContextSuite) {
			break;
		}
		SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
		if (runnable == nil) {
			break;
		}
		result = runnable->CanRun(runnableContextSuite);
	} while(false);
	return result;
}

/*
*/
ErrorCode SnipRunSuiteCSB::Run(const SnippetName& snippetName, PMString& parameters, bool16 enableParameterDialog) const
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ISnpRunnableContext> runnableContextSuite(this, UseDefaultIID());
		ASSERT(runnableContextSuite);
		if (!runnableContextSuite) {
			SNIPLOG("Can't run %s ISnpRunnableContext is not available", snippetName.GetPlatformString().c_str());
			break;
		}

		Utils<ISnipRunParameterUtils> parameterUtils;
		const bool16 wasDialogEnabled = parameterUtils->IsDialogEnabled();
		if (wasDialogEnabled != enableParameterDialog) {
			parameterUtils->EnableDialog(enableParameterDialog);
		}
		const bool16 wasTranslationEnabled = parameterUtils->IsTranslationEnabled();
		if (wasTranslationEnabled) {
			// Disable string translation in the parameter
			// prompt dialog. Code snippets don't have translatable
			// strings.
			parameterUtils->EnableTranslation(kFalse);
		}

		// Set the parameters to be used.
		parameterUtils->SetParameters(parameters);

		// Log the command being processed, lookup the snippet and run it of found.
		SNIPLOG("%s-->In(%s)", snippetName.GetPlatformString().c_str(), parameters.GetPlatformString().c_str());
		SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
		if (runnable != nil)
			status = runnable->Run(runnableContextSuite);
		else
			status = kSnipRunSnippetNotFoundErrorCode;

		// Return the parameters that were used.
		parameters = parameterUtils->GetParameters();
		SNIPLOG("%s-->Out(%s)", snippetName.GetPlatformString().c_str(), parameters.GetPlatformString().c_str());

		// Record the result in the log.
		this->LogRunStatus(snippetName, status);

		if (wasTranslationEnabled) {
			// Re-enable string stranslation.
			parameterUtils->EnableTranslation(kTrue);
		}
		if (wasDialogEnabled != enableParameterDialog) {
			// Restore dialog state that existed when we were called.
			parameterUtils->EnableDialog(wasDialogEnabled);
		}

	} while (false);
	return status;
}


/* 
*/
ErrorCode SnipRunSuiteCSB::SetupContext(const SnippetName& snippetName)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnpRunnableContext> runnableContextSuite(this, UseDefaultIID());
		ASSERT(runnableContextSuite);
		if (!runnableContextSuite) {
			break;
		}
		SnpRunnable* runnable = SnipRunManager::Instance()->FindSnippet(snippetName);
		if (runnable == nil) {
			break;
		}
		result = runnable->SetupContext(runnableContextSuite);
	} while(false);
	return result;
}
				

/*
*/
void SnipRunSuiteCSB::GetTokens(const PMString& buf, K2Vector<PMString>& tokens, const textchar separator) const
{
	PMString token;
	for (int32 i = 0; i < buf.CharCount(); i++) {
		if (buf [i] == separator) {
			tokens.push_back(token);
			token.Clear();
		}
		else {
			token.Append(buf [i]);
		}
	}
	if (!token.empty()) {
		tokens.push_back(token);
	}
}

/*
*/
void SnipRunSuiteCSB::LogRunStatus(const SnippetName& snippetName, const ErrorCode& status) const
{
	do {
		PMString message;
		if (status == kSuccess) {
			message.Append(" ok");
		}
		else if (status == kCancel) {
			message.Append(" cancelled");
		}
		else if (status == kSnipRunSnippetNotFoundErrorCode) {
			message.Append( " failed: can't find this snippet");
		}
		else  {
			message.Append(" failed: status=");
			message.AppendNumber(status);
		}
		SnipRunLog::Instance()->Log(message);
		SnipRunLog::Instance()->UpdateTextControl();
	} while(false);
}

// End, SnipRunSuiteCSB.cpp.





