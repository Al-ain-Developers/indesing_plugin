//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunParameterUtils.cpp $
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
#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IWindow.h"

// Dialog-specific resource includes:
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "ErrorUtils.h"

// General includes:
#include "K2Vector.h"
#include "K2Assert.h"
#include "CPMUnknown.h"
#include "TextChar.h"

// Project includes:
#include "SnipRunID.h"
#include "ISnipRunParameterUtils.h"
#include "ISnipRunDialogData.h"
#include "SnipRunLog.h"

/** Implements ISnipRunParameterUtils. Parameter gathering has three modes:
	<ol>
	<li> Interactive; the user is prompted for parameter values via dialog as the code snippet runs.
		The values entered by the user are recorded and made available
		to the SnippetRunner user interface in its parameter edit box widget.
	<li> Non-interactive; the user is not prompted for parameter values, instead parameter values are 
		parsed from a CSV string supplied by client code.
		(the parameters in the parameter edit box widget in the SnippetRunner user interface
		are passed in). 
	<li> Default; the default parameter values specified by code snippets are used.
	</ol>

	@ingroup snippetrunner
	
	@see ISnipRunParameterUtils
*/
class SnipRunParameterUtils : public CPMUnknown<ISnipRunParameterUtils>
{
	public:
		/** Constructor.
		*/
		SnipRunParameterUtils(IPMUnknown* boss);

		/**	Destructor.
		*/
		virtual ~SnipRunParameterUtils();

		/** See ISnipRunParameterUtils::GetPMString
		 */
		virtual PMString	GetPMString(const PMString& prompt, const PMString& defaultValue = "") const;

		/** See ISnipRunParameterUtils::GetInt32
		 */
		virtual int32		GetInt32(const PMString& prompt, const int32 defaultValue = 0, const int32 lowerLimit = 0, const int32 upperLimit = 0) const;

		/** See ISnipRunParameterUtils::GetPMReal
		 */
		virtual PMReal		GetPMReal(const PMString& prompt, const PMReal& defaultValue = 0, const PMReal& lowerLimit = 0, const PMReal& upperLimit = 0) const;

		/** See ISnipRunParameterUtils::GetChoice
		 */
		virtual int32		GetChoice(const PMString& prompt, const K2Vector<PMString>& choices, const int32 defaultChoiceIndex = 0) const;

		/** See ISnipRunParameterUtils::WasDialogCancelled
		 */
		virtual bool16		WasDialogCancelled() const;

		/** See ISnipRunParameterUtils::EnableDialog
		 */
		virtual void		EnableDialog(const bool16 enable);

		/** See ISnipRunParameterUtils::IsDialogEnabled
		 */
		virtual bool16		IsDialogEnabled() const;

		/** See ISnipRunParameterUtils::EnableTranslation
		 */
		virtual void		EnableTranslation(const bool16 enable);

		/** See ISnipRunParameterUtils::IsTranslationEnabled
		 */
		virtual bool16		IsTranslationEnabled() const;

		/** See ISnipRunParameterUtils::SetParameters
		 */
		virtual void		SetParameters(const PMString& params);

		/** See ISnipRunParameterUtils::GetParameters
		 */
		virtual PMString		GetParameters();

	private:

		/**	@return an instance of SnippetRuner's parameter dialog.
		 */
		virtual IDialog*	CreateSnipRunDialog() const;

		/**	Wraps mutation of fWasDialogCancelled inside a const method
			to hide mutation from client code.
			@param cancel kTrue if dialog was cancelled, kFalse otherwise.
			@return  
		 */
		virtual void		SetWasDialogCancelled(const bool16 cancel) const;

	private:
		bool16 fIsDialogEnabled;
		bool16 fIsTranslationEnabled;
		bool16 fWasDialogCancelled;

	private:
		/** Helper class that tokenises a string of parameters and has helper methods that can convert
			parameters into various data types (int32, PMReal, etc.). The class also has the ability to
			record parameters.
		*/
		class SnipRunTokeniser
		{
			public:
				/** Constructor
				*/
				SnipRunTokeniser(const UTF16TextChar separator = kTextChar_Comma, const UTF16TextChar quote = kTextChar_QuotationMark);

				/** Destructor
				*/
				~SnipRunTokeniser();

			public:
				/** Vector of strings built by tokenising a string.
				*/
				typedef K2Vector<PMString> Tokens;

				// Parameter tokenisation.
			public:
				/** @return kTrue if parameters are available, kFalse otherwise.
				*/
				bool16 HasParameters() const;

				/** Set the parameters.
					Tokenises params into a list of tokens using the separator specified on construction.
					Supports quotes to delimit tokens where white space is significant.

					@param params IN
				*/
				void SetParameters(const PMString& params);

				/** Return the parameters.
					@return the parameters.
				*/
				PMString GetParameters();

				/** Get next token as an int32.
					@param value OUT The value.
					@param lowerLimit IN (default 0, if both lowerLimit and upperlimit are 0 range checking is switched off)
					@param upperLimit IN (default 0)
					@param token OUT The next token.
					@return kSuccess on success, kFailure otherwise.
				*/
				ErrorCode GetInt32(int32& value, const int32& lowerLimit, const int32& upperLimit, PMString& token) const;

				/** Get next token as a PMReal.
					@param value OUT
					@param lowerLimit IN (default 0, if both lowerLimit and upperlimit are 0 range checking is switched off)
					@param upperLimit IN (default 0)
					@param token OUT The next token.
					@return kSuccess on success, kFailure otherwise.
				*/
				ErrorCode GetPMReal(PMReal& value, const PMReal& lowerLimit, const PMReal& upperLimit, PMString& token) const;

				/** Get next token as a PMString.
					@param value OUT
					@return kSuccess on success, kFailure otherwise.
				*/
				ErrorCode GetPMString(PMString& value) const;

				/** Get next token as the index of a selected choice in a list of valid choices. 
					by a vector of PMString's.
					@param value OUT the index of the selected choice
					@param choices IN vector of strings representing the choices available
					@param token OUT The next token from the selected choice.
				*/
				ErrorCode GetChoice(int32& value, const K2Vector<PMString>& choices, PMString& token) const;

			// Parameter recording.
		public:
				/** Store the given token as a recorded parameter.
					@param token
				*/
				void	RecordToken(const PMString& token);

				/** Return all the recorded tokens as a parameter string separated by the 
					separator character identified at construction.
				*/
				PMString	GetRecordedParameters();

				/** @return kTrue is recorded parameters are available, kFalse otherwise.
				*/
				bool16 HasRecordedParameters() const;

			private:
				/** Tokenise the given parameters into vector fParameterTokens.
					@param params
				 */
				void	GetTokens(const PMString& params);

				/** 
				*/
				void	AppendToken(PMString& token, bool stripWhiteSpace = true);

			private:
				/** Parameter string passed by client.
				 */
				PMString fParameters;
				/** Vector of tokens parsed out of fParameters.
				 */
				Tokens fParameterTokens;
				/** Index of last token read by client from fParameterTokens.
				 */
				int32 fParameterTokenIndex;
				/** Character to be used to delimit tokens in parameter strings.
				 */
				UTF16TextChar fSeparator;
				/** Character to be used to quote tokens where white space is significant.
				 */
				UTF16TextChar fQuote;
				/** Records tokens passed by client code.
				 */
				Tokens fRecordedTokens;
		};
		/** Tokenisor used to source parameter values when parameters are
			passed as a CSV from client code.
		 */
		SnipRunTokeniser fTokenisor;
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunParameterUtils, kSnipRunParameterUtilsImpl)

/*
*/
SnipRunParameterUtils::SnipRunParameterUtils(IPMUnknown* boss) : CPMUnknown<ISnipRunParameterUtils>(boss),
	fIsDialogEnabled(kTrue),
	fIsTranslationEnabled(kTrue),
	fWasDialogCancelled(kFalse)
{

}

/*
*/
SnipRunParameterUtils::~SnipRunParameterUtils()
{
}


/*
*/
void SnipRunParameterUtils::SetParameters(const PMString& params)
{
	fTokenisor.SetParameters(params);
}

/*
*/
PMString SnipRunParameterUtils::GetParameters()
{
	PMString parameters;
	if (fTokenisor.HasRecordedParameters()) {
		parameters = fTokenisor.GetRecordedParameters();
	}
	else {
		parameters = fTokenisor.GetParameters();
	}
	return parameters;
}

/*
*/
void SnipRunParameterUtils::EnableDialog(const bool16 enable)
{
	fIsDialogEnabled = enable;
}

/*
*/
bool16 SnipRunParameterUtils::IsTranslationEnabled() const
{
	return fIsTranslationEnabled;
}
/*
*/
void SnipRunParameterUtils::EnableTranslation(const bool16 enable)
{
	fIsTranslationEnabled = enable;
}

/*
*/
bool16 SnipRunParameterUtils::IsDialogEnabled() const
{
	return fIsDialogEnabled;
}


/*	Hides the mutation of this class from client code by wrapping
	the method that sets the fWasDialogCancelled in a const method
	that cases away the const'ness.
*/
void SnipRunParameterUtils::SetWasDialogCancelled(const bool16 cancel) const
{
	const_cast<SnipRunParameterUtils*>(this)->fWasDialogCancelled = cancel;
}

/*
*/
bool16 SnipRunParameterUtils::WasDialogCancelled() const
{
	return fWasDialogCancelled;
}

/*
*/
PMString SnipRunParameterUtils::GetPMString(const PMString& prompt, const PMString& defaultValue) const
{
	PMString result = defaultValue;
	this->SetWasDialogCancelled(kFalse);
	do {
		if (fTokenisor.HasParameters()) {
			// Source value from the parameters passed into the framework via ISnipRunSuite::Run.
			PMString token;
			if (fTokenisor.GetPMString(token) == kSuccess) {
				result = token;
			} 
			else {
				if (!this->IsDialogEnabled()) {
					// Stop on detecting the first bad parameter if the user is not allowed to edit.
					SNIPLOG("Invalid PMString parameter \"%s\"", token.GetPlatformString().c_str());
					this->SetWasDialogCancelled(kTrue);	
					result = token; // record the bad token
					break;
				}
			}
		}

		if (!this->IsDialogEnabled()) {
			// Don't let the user edit the parameter value.
			break;
		}

		// Pop dialogue to allow the user to edit the parameter value.
		IDialog* dialog = this->CreateSnipRunDialog();
		if (!dialog) {
			break;
		}
		IControlView* dialogPanel = dialog->GetDialogPanel();
		ASSERT(dialogPanel);
		if (!dialogPanel) {
			break;
		}
		InterfacePtr<ISnipRunDialogData> dialogData(dialogPanel, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		dialogData->EnableTranslation(this->IsTranslationEnabled());
		dialogData->SetMode(ISnipRunDialogData::kSnipRunStringMode);
		dialogData->SetPrompt(prompt);
		dialogData->SetPMString(result);
		PMString typeInfo("PMString");
		typeInfo.SetTranslatable(kFalse);
		dialogData->SetTypeInfo(typeInfo);
		dialog->Open();
		dialog->WaitForDialog();

		// Return data to the caller.
		this->SetWasDialogCancelled(dialogData->GetWasCancelled());
		if (this->WasDialogCancelled()) {
			break;
		}
		result = dialogData->GetPMString();

	} while(false);

	// Record the token for later recall.
	result.SetTranslatable(kFalse);
	const_cast<SnipRunParameterUtils*>(this)->fTokenisor.RecordToken(result);

	return result;
}

/*
*/
int32 SnipRunParameterUtils::GetChoice(const PMString& prompt, const K2Vector<PMString>& choices, const int32 defaultChoiceIndex) const
{
	int32 result = defaultChoiceIndex;
	PMString recordedToken("");
	this->SetWasDialogCancelled(kFalse);
	do {
		// Validate the choices and defaultChoiceIndex.
		ASSERT(choices.size() > 0);
		if (choices.size() <= 0) {
			break;
		}
		ASSERT(defaultChoiceIndex >= 0 && defaultChoiceIndex < choices.size());
		if (!(defaultChoiceIndex >= 0 && defaultChoiceIndex < choices.size())) {
			break;
		}

		recordedToken = choices[defaultChoiceIndex];

		if (fTokenisor.HasParameters()) {
			PMString token;
			// Source value from the parameters passed into the framework via ISnipRunSuite::Run.
			if (fTokenisor.GetChoice(result, choices, token) == kSuccess) {
				recordedToken = token;
			}
			else {
				if (!this->IsDialogEnabled()) {
					// Stop on detecting the first bad parameter if the user is not allowed to edit.
					SNIPLOG("Invalid Choice parameter \"%s\"", token.GetPlatformString().c_str());
					this->SetWasDialogCancelled(kTrue);	
					recordedToken = token; // record the bad token
					break;
				}
			}
		}

		if (!this->IsDialogEnabled()) {
			// Don't let the user edit the parameter value.
			break;
		}

		// Pop dialogue to allow the user to edit the parameter value.
		IDialog* dialog = this->CreateSnipRunDialog();
		if (!dialog) {
			break;
		}
		IControlView* dialogPanel = dialog->GetDialogPanel();
		ASSERT(dialogPanel);
		if (!dialogPanel) {
			break;
		}
		InterfacePtr<ISnipRunDialogData> dialogData(dialogPanel, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		dialogData->EnableTranslation(this->IsTranslationEnabled());
		dialogData->SetMode(ISnipRunDialogData::kSnipRunChoiceMode);
		dialogData->SetPrompt(prompt);
		dialogData->SetChoiceIndex(result);
		dialogData->SetChoices(choices);
		PMString typeInfo("Choice");
		typeInfo.SetTranslatable(kFalse);
		dialogData->SetTypeInfo(typeInfo);
		dialog->Open();
		dialog->WaitForDialog();

		// Return data to the caller.
		this->SetWasDialogCancelled(dialogData->GetWasCancelled());
		if (this->WasDialogCancelled()) {
			break;
		}
		result = dialogData->GetChoiceIndex();
		recordedToken = choices[result];

	} while(false);

	// Record the token for later recall.
	const_cast<SnipRunParameterUtils*>(this)->fTokenisor.RecordToken(recordedToken);

	return result;
}

/*
*/
int32 SnipRunParameterUtils::GetInt32(const PMString& prompt, const int32 defaultValue, const int32 lowerLimit, const int32 upperLimit) const
{
	int32 result = defaultValue;
	PMString recordedToken;
	recordedToken.AppendNumber(result);
	this->SetWasDialogCancelled(kFalse);
	do {
		if (fTokenisor.HasParameters()) {
			// Source value from the parameters passed into the framework via ISnipRunSuite::Run.
			PMString token;
			if (fTokenisor.GetInt32(result, lowerLimit, upperLimit, token) == kSuccess) {
				recordedToken = token;
			}
			else {
				if (!this->IsDialogEnabled()) {
					// Stop on detecting the first bad parameter if the user is not allowed to edit.
					SNIPLOG("Invalid Int32 parameter %s", token.GetPlatformString().c_str());
					this->SetWasDialogCancelled(kTrue);	
					recordedToken = token; // record the bad token
					break;
				}
			}
		}

		if (!this->IsDialogEnabled()) {
			// Don't let the user edit the parameter value.
			break;
		}

		// Pop dialogue to allow the user to edit the parameter value.
		IDialog* dialog = this->CreateSnipRunDialog();
		if (!dialog) {
			break;
		}
		IControlView* dialogPanel = dialog->GetDialogPanel();
		ASSERT(dialogPanel);
		if (!dialogPanel) {
			break;
		}
		InterfacePtr<ISnipRunDialogData> dialogData(dialogPanel, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		dialogData->EnableTranslation(this->IsTranslationEnabled());
		dialogData->SetMode(ISnipRunDialogData::kSnipRunIntMode);
		dialogData->SetPrompt(prompt);
		dialogData->SetInt32(result);
		dialogData->SetLowerLimit(lowerLimit);
		dialogData->SetUpperLimit(upperLimit);
		PMString typeInfo("int32");
		typeInfo.SetTranslatable(kFalse);
		if (lowerLimit != 0 || upperLimit != 0) {
			ASSERT(result >= lowerLimit && result <= upperLimit);
			char buf[128] = "";
			sprintf(buf, " %d:%d", lowerLimit, upperLimit);
			typeInfo = typeInfo + buf;
		}
		dialogData->SetTypeInfo(typeInfo);
		dialog->Open();
		dialog->WaitForDialog();

		// Return data to the caller.
		this->SetWasDialogCancelled(dialogData->GetWasCancelled());
		if (this->WasDialogCancelled()) {
			break;
		}
		result = dialogData->GetInt32();
		recordedToken.Clear();
		recordedToken.AppendNumber(result);

	} while(false);

	// Record the token for later recall.
	const_cast<SnipRunParameterUtils*>(this)->fTokenisor.RecordToken(recordedToken);

	return result;
}

/*
*/
PMReal SnipRunParameterUtils::GetPMReal(const PMString& prompt, const PMReal& defaultValue, const PMReal& lowerLimit, const PMReal& upperLimit) const
{
	PMReal result = defaultValue;
	PMString recordedToken;
	recordedToken.AppendNumber(result);
	this->SetWasDialogCancelled(kFalse);
	do {
		if (fTokenisor.HasParameters()) {
			// Source value from the parameters passed into the framework via ISnipRunSuite::Run.
			PMString token;
			if (fTokenisor.GetPMReal(result, lowerLimit, upperLimit, token) == kSuccess) {
				recordedToken = token;
			}
			else {
				if (!this->IsDialogEnabled()) {
					// Stop on detecting the first bad parameter if the user is not allowed to edit.
					SNIPLOG("Invalid PMReal parameter %s", token.GetPlatformString().c_str());
					this->SetWasDialogCancelled(kTrue);	
					recordedToken = token; // record the bad token
					break;
				}
			}
		}

		if (!this->IsDialogEnabled()) {
			// Don't let the user edit the parameter value.
			break;
		}

		// Pop dialogue to allow the user to edit the parameter value.
		IDialog* dialog = this->CreateSnipRunDialog();
		if (!dialog) {
			break;
		}
		IControlView* dialogPanel = dialog->GetDialogPanel();
		ASSERT(dialogPanel);
		if (!dialogPanel) {
			break;
		}
		InterfacePtr<ISnipRunDialogData> dialogData(dialogPanel, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		dialogData->EnableTranslation(this->IsTranslationEnabled());
		dialogData->SetMode(ISnipRunDialogData::kSnipRunRealMode);
		dialogData->SetPrompt(prompt);
		dialogData->SetPMReal(result);
		dialogData->SetLowerLimit(lowerLimit);
		dialogData->SetUpperLimit(upperLimit);
		PMString typeInfo("PMReal");
		typeInfo.SetTranslatable(kFalse);
		if (lowerLimit != 0 || upperLimit != 0) {
			ASSERT(result >= lowerLimit && result <= upperLimit);
			char buf[128] = "";
			sprintf(buf, " %5.2f:%5.2f", ::ToDouble(lowerLimit), ::ToDouble(upperLimit));
			typeInfo = typeInfo + buf;
		}
		dialogData->SetTypeInfo(typeInfo);
		dialog->Open();
		dialog->WaitForDialog();

		// Return data to the caller.
		this->SetWasDialogCancelled(dialogData->GetWasCancelled());
		if (this->WasDialogCancelled()) {
			break;
		}
		result = dialogData->GetPMReal();
		recordedToken.Clear();
		recordedToken.AppendNumber(result);
	} while(false);

	// Record the token entered by the user for later recall.
	const_cast<SnipRunParameterUtils*>(this)->fTokenisor.RecordToken(recordedToken);

	return result;
}

/*
*/
IDialog* SnipRunParameterUtils::CreateSnipRunDialog() const
{
	IDialog* result = nil;
	do {
		// Get the application interface and the DialogMgr.	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application);
		if (application == nil) {	
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		ASSERT(dialogMgr);
		if (dialogMgr == nil) {
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kSnipRunPluginID,			// Our Plug-in ID  
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog);
		if (dialog == nil) {
			break;
		}
		result = dialog;

	} while (false);

	return result;

}

// --------------------------------- SnipRunTokeniser helper ---------------------------------------------------

/*
*/
SnipRunParameterUtils::SnipRunTokeniser::SnipRunTokeniser(const UTF16TextChar separator, const UTF16TextChar quote) : fParameterTokenIndex(0), fSeparator(separator), fQuote(quote)
{
}

/*
*/
SnipRunParameterUtils::SnipRunTokeniser::~SnipRunTokeniser()
{
}



/*
*/
bool16 SnipRunParameterUtils::SnipRunTokeniser::HasParameters() const
{
	bool16 result = kFalse;
	if (fParameterTokens.size() > 0) {
		result = kTrue;
	}
	return result;
}

/*
*/
void SnipRunParameterUtils::SnipRunTokeniser::SetParameters(const PMString& params)
{
	// Buffer the parameter string passed by the client.
	fParameters = params;
	fParameters.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);

	// 1078062 Some snippets are setting their parameters programatically. However,
	// parameters are never translatable strings so mark them translated.
	fParameters.SetTranslated(); 


	// Parse it into tokens.
	this->GetTokens(fParameters);
	// Reset the token index so client code can get the token values
	// in succeeding calls.
	fParameterTokenIndex = -1;
	// Clear the recorded tokens.
	fRecordedTokens.clear();
}

/*
*/
PMString SnipRunParameterUtils::SnipRunTokeniser::GetParameters()
{
	return fParameters;
}

/*
*/
void SnipRunParameterUtils::SnipRunTokeniser::GetTokens(const PMString& params)
{
	// Parse the given string into a vector of tokens using
	// the separator identifed at construction time to trigger
	// when to delimit tokens.
	fParameterTokens.clear();
	PMString line = params;
	PMString token;
	bool16 inQuote = kFalse;
	for (int32 i = 0; i < line.CharCount(); i++) {
		if (inQuote == kFalse) {
			if (line [i] == fQuote) {
				// Start of quoted token.
				// Add quote to token - it'll be stripped out by AppendToken.
				token.Append(line [i]);
				inQuote = kTrue;
			}
			else if (line [i] == fSeparator) {
				// Buffer the token.
				this->AppendToken(token);
				token.Clear();
			}
			else {
				// Add character to token.
				token.Append(line [i]);
			}
		} 
		else {
			// Add character to token
			token.Append(line [i]);
			if (line [i] == fQuote) {
				// The quote character will be stripped out by AppendToken.
				inQuote = kFalse;
			}
		}
	}

	if (token.CharCount() > 0) {
		this->AppendToken(token);
	}
}

/*
*/
void SnipRunParameterUtils::SnipRunTokeniser::AppendToken(PMString& token, bool stripWhiteSpace)
{
	if (stripWhiteSpace) {
		token.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
	}
	// Strip quotes from the token.
	for (CharCounter i = token.CharCount() -1; i >=0; i--) {
		if (token[i] == fQuote) {
			token.Remove(i, 1);
		}
	}
	fParameterTokens.push_back(token);
}

/*
*/
ErrorCode SnipRunParameterUtils::SnipRunTokeniser::GetInt32(int32& value, const int32& lowerLimit, const int32& upperLimit, PMString& token) const
{
	ErrorCode status = kFailure;
	do {
		token.Clear();
		const_cast<SnipRunTokeniser*>(this)->fParameterTokenIndex++;
		if (fParameterTokenIndex >= fParameterTokens.size()) {
			break;
		}
		token = fParameterTokens[fParameterTokenIndex];
		PMString::ConversionError conversionStatus;
		int32 tmp = fParameterTokens[fParameterTokenIndex].GetAsNumber(&conversionStatus);
		if (conversionStatus != PMString::kNoError) {
			break;
		}
		bool16 rangeCheckingOn = kTrue;
		if (lowerLimit == 0.0 && upperLimit == 0.0) {
			rangeCheckingOn = kFalse;
		}
		if (rangeCheckingOn) {
			if (tmp < lowerLimit || tmp > upperLimit) {
				break;
			}
		}
		value = tmp;
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnipRunParameterUtils::SnipRunTokeniser::GetPMReal(PMReal& value, const PMReal& lowerLimit, const PMReal& upperLimit, PMString& token) const
{
	ErrorCode status = kFailure;
	do {
		token.Clear();
		const_cast<SnipRunTokeniser*>(this)->fParameterTokenIndex++;
		if (fParameterTokenIndex >= fParameterTokens.size()) {
			break;
		}
		token = fParameterTokens[fParameterTokenIndex];
		PMString::ConversionError conversionStatus;
		PMReal tmp = fParameterTokens[fParameterTokenIndex].GetAsDouble(&conversionStatus);
		if (conversionStatus != PMString::kNoError) {
			break;
		}
		bool16 rangeCheckingOn = kTrue;
		if (lowerLimit == 0.0 && upperLimit == 0.0) {
			rangeCheckingOn = kFalse;
		}
		if (rangeCheckingOn) {
			if (tmp < lowerLimit || tmp > upperLimit) {
				break;
			}
		}
		value = tmp;
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnipRunParameterUtils::SnipRunTokeniser::GetPMString(PMString& value) const
{
	ErrorCode status = kFailure;
	do {
		value.Clear();
		const_cast<SnipRunTokeniser*>(this)->fParameterTokenIndex++;
		if (fParameterTokenIndex >= fParameterTokens.size()) {
			break;
		}
		value = fParameterTokens[fParameterTokenIndex];
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
ErrorCode SnipRunParameterUtils::SnipRunTokeniser::GetChoice(int32& value, const K2Vector<PMString>& choices, PMString& token) const
{
	ErrorCode status = kFailure;
	do {
		token.Clear();
		const_cast<SnipRunTokeniser*>(this)->fParameterTokenIndex++;
		if (fParameterTokenIndex >= fParameterTokens.size()) {
			break;
		}
		PMString choice = fParameterTokens[fParameterTokenIndex];
		token = choice;
		// Lookup value in choices.
		K2Vector<PMString>::const_iterator theChoice = std::find(choices.begin(), choices.end(), choice);
		if (theChoice == choices.end()) {
			break;
		}
		value = theChoice - choices.begin();
		status = kSuccess;
	} while(false);
	return status;
}

/*
*/
bool16 SnipRunParameterUtils::SnipRunTokeniser::HasRecordedParameters() const
{
	bool16 result = kFalse;
	if (fRecordedTokens.size() > 0) {
		result = kTrue;
	}
	return result;
}

/*
*/
void SnipRunParameterUtils::SnipRunTokeniser::RecordToken(const PMString& token)
{
	bool quoteTheToken = false;
	PMString strippedToken = token;
	strippedToken.StripWhiteSpace();
	if (strippedToken.CharCount() != token.CharCount()) {
		// The token contains white space so quote it.
		quoteTheToken = true;
	}
	if (token.IndexOfWChar(fSeparator) >= 0) {
		// The token contains the separator so quote it.
		quoteTheToken = true;
	}
	if (quoteTheToken) {
		PMString quotedToken;
		quotedToken.AppendW(fQuote);
		quotedToken.Append(token);
		quotedToken.AppendW(fQuote);
		fRecordedTokens.push_back(quotedToken);
	}
	else {
		fRecordedTokens.push_back(token);
	}
}

/*
*/
PMString SnipRunParameterUtils::SnipRunTokeniser::GetRecordedParameters()
{
	PMString result;
	// Push the first token onto the parameter line.
	Tokens::const_iterator iter = fRecordedTokens.begin();
	if (iter < fRecordedTokens.end()) {
		result += *iter;
		iter++;
	}
	// Push the rest of the tokens led by a separator.
	while (iter < fRecordedTokens.end()) {
		result.AppendW(fSeparator);
		result += *iter;
		iter++;
	}
	// The user entered all these tokens so, de-facto, they are translated.
	result.SetTranslated();
	return result;
}

// End, SnipRunParameterUtils.cpp

