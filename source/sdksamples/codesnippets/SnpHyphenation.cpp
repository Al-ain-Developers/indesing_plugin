//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpHyphenation.cpp $
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
#include "ITextAttrInt16.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttributeSuite.h"
#include "ITextAttributes.h"
#include "IAttrReport.h"
#include "IHyphenationStyle.h"
#include "ITextAttrHyphenMode.h"
#include "ITextAttrProviderHyphStyle.h"

// General includes:
#include "TextRange.h"


// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	Sample code snippet that shows how access the hyphenation policy that applies to text, and how to set the
	hyphenation policy for particular text.

	@ingroup sdk_snippet
	@ingroup sdk_text

*/
class SnpHyphenation 
{
public:
	/** Constructor.
	 */
	SnpHyphenation() {}

	/** Destructor.
	 */
	virtual ~SnpHyphenation() {}

	/** Adapts from the UI to model. 
		@param iTextAttributeSuite IN the suite used to get the value of the attributes. If there is a text selection, we wil get the
			value of the attributes that apply to the text, otherwise we will retrieve the document or session defaults.
		@return kFailure on error or if the user cancels
	*/
	ErrorCode ReportHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite);

	/** Adapts from the UI to model. 
		@param iTextAttributeSuite IN the attribute suite used to manipulate the attributes. This means any updates
			are based on the context of the call. If we call with a text selection, it is the attributes that apply that are modified.
			If there is no text selection, it will be the document of session preferences that are modified. 
		@return kFailure on error or if the user cancels
	*/
	ErrorCode ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite);


private:
	/** Report a specific hyphenation policy.
		@param iTextAttributeSuite IN the current attribute selection context. 
		@param attribute IN the attribute of interest.
		@param description IN a description of the attribute.
		@return kSuccess if the operation completes normally.
	*/
	ErrorCode ReportHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, PMString description);

	
	/**
		Reports the value of a particular attribute.
		@param iAttrReport IN the iAttrReport of interest.
		@param description IN some descriptive text to accompany the attribute value when reported.
		@return kSuccess if the operation is successful.
	*/
	ErrorCode reportAttribute(const IAttrReport* iAttrReport, PMString description);

	/** 
		Modify an attribute (type boolean) that controls hyphenation.
		@param iTextAttributeSuite IN the current attribute selection context.
		@param attribute IN the type of attribute to be applied.
		@param value IN the value for the attribute.
		@return kSuccess if the attribute is successfully applied.
	*/
	ErrorCode ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const bool8 value);

	/** 
		Modify an attribute (type PMReal) that controls hyphenation.
		@param iTextAttributeSuite IN the current attribute selection context.
		@param attribute IN the type of attribute to be applied.
		@param value IN the value for the attribute.
		@return kSuccess if the attribute is successfully applied.
	*/
	ErrorCode ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const PMReal value);

	/** 
		Modify an attribute (type int16) that controls hyphenation.
		@param iTextAttributeSuite IN the current attribute selection context.
		@param attribute IN the type of attribute to be applied.
		@param value IN the value for the attribute.
		@return kSuccess if the attribute is successfully applied.
	*/
	ErrorCode ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const int16 value);

	/** 
		Modify the hyphenation method that is in effct for a (set of) paragraph. 
		@param iTextAttributeSuite IN the current attribute selection context.
		@param attribute IN the type of attribute to be applied (should only ever be kTextAttrHyphenModeBoss).
		@param value IN the value for the attribute.
		@return kSuccess if the attribute is successfully applied.
	*/
	ErrorCode ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const IHyphenationStyle::HyphenationMethod value);

	/**
	Modify the provider hyphenation style that is in effect for a (set of) paragraph.
	@param iTextAttributeSuite IN the current attribute selection context.
	@param attribute IN the type of attribute to be applied (should only ever be kTextAttrProviderHyphStyleBoss).
	@param value IN the value for the attribute.
	@return kSuccess if the attribute is successfully applied.
	*/
	ErrorCode ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const IHyphenationStyle::ProviderHyphenationStyle value);

	/**
		Obtain a boolean value from the user.
		@param b OUT the boolean value.
		@param message IN descriptice text to display to the user.
		@return kSuccess if a boolean value is obtained, kFailure if the user cancels, or on error.
	*/
	ErrorCode getBoolValue(bool8& b, const PMString& message);

	/**
		Obtain an int16 value from the user.
		@param i OUT the integer value.
		@param message IN descriptice text to display to the user.
		@param upperLimit IN the upper limit for the request.
		@return kSuccess if an int16 value is obtained, kFailure if the user cancels, or on error.
	*/
	ErrorCode getInt16Value(int16& i, const PMString& message, const int16 upperLimit);

	/**
		Obtain a PMReal value from the user.
		@param v OUT the PMReal value.
		@param message IN descriptice text to display to the user.
		@param upperLimit IN the upper limit for the request.
		@return kSuccess if a PMReal value is obtained, kFailure if the user cancels, or on error.
	*/
	ErrorCode getRealValue(PMReal& v, const PMString& message, const PMReal upperLimit);

	/**
		Allow the user to select the hyphenation mode that should be in effect.
		@param h OUT the hyphenation mode.
		@param message IN descriptice text to display to the user.
		@return kSuccess if the user selects the hyphenation mode, kFailure if the user cancels, or on error.
	*/
	ErrorCode getHyphenMode(IHyphenationStyle::HyphenationMethod& h, const PMString& message);

	/**
	Allow the user to select the provider hyphenation style that should be in effect.
	@param s OUT the hyphenation style.
	@param message IN descriptice text to display to the user.
	@return kSuccess if the user selects the provider hyphenation style, kFailure if the user cancels, or on error.
	*/
	ErrorCode getProviderHyphenStyle(IHyphenationStyle::ProviderHyphenationStyle& s, const PMString& message);
};

 
/*
*/
ErrorCode 
SnpHyphenation::getHyphenMode(IHyphenationStyle::HyphenationMethod& h, const PMString& message)
{
	ErrorCode status = kFailure;
	do{
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Hyphens Off (hard hyphens only)"));
		choices.push_back(PMString("+Manual hyphens (as well as hard)"));
		choices.push_back(PMString("+Dictionary (as well as manual and hard)"));
		choices.push_back(PMString("+Algorithm (all hyphen options)"));
		h = static_cast<IHyphenationStyle::HyphenationMethod>(parameterUtils->GetChoice(message, choices));
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode SnpHyphenation::getProviderHyphenStyle(IHyphenationStyle::ProviderHyphenationStyle & s, const PMString & message)
{
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("+All (Include all hyphenation points)"));
		choices.push_back(PMString("+All but unaesthetic (Include all but unaesthetic hyphenation points)"));
		choices.push_back(PMString("+Aesthetic (Include aesthetic hyphenation points)"));
		choices.push_back(PMString("+Preferred Aesthetic (Include preferred aesthetic hyphenation points)"));
		s = static_cast<IHyphenationStyle::ProviderHyphenationStyle>(parameterUtils->GetChoice(message, choices));
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpHyphenation::getBoolValue(bool8& b, const PMString& message)
{
	ErrorCode status = kFailure;
	do{
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("false"));
		choices.push_back(PMString("true"));
		b = parameterUtils->GetChoice(message,  choices) == 0 ? kFalse:kTrue;
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpHyphenation::getInt16Value(int16& i, const PMString& message,const int16 upperLimit)
{
	ErrorCode status = kFailure;
	do{
		Utils<ISnipRunParameterUtils> parameterUtils;
		i = parameterUtils->GetInt32(message,  0, 0, upperLimit);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpHyphenation::getRealValue(PMReal& r, const PMString& message, const PMReal upperLimit)
{
	ErrorCode status = kFailure;
	do{
		Utils<ISnipRunParameterUtils> parameterUtils;
		r = parameterUtils->GetPMReal(message,  0, 0, upperLimit);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpHyphenation::ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite)
{
	ErrorCode status = kFailure;
	do{
		// get the attribute type we wish to modify
		Utils<ISnipRunParameterUtils> parameterUtils;

		// Get which choice the user wants to run.
		K2Vector<PMString> choices;
		choices.push_back(PMString("HyphenateCapitalizedWords"));
		choices.push_back(PMString("HyphenationWeight"));
		choices.push_back(PMString("HyphenateLastWord"));
		choices.push_back(PMString("MinimumCharactersBefore"));
		choices.push_back(PMString("MinimumCharactersAfter"));
		choices.push_back(PMString("ShortestWordLength"));
		choices.push_back(PMString("HyphenationMode"));
		choices.push_back(PMString("HyphenationZone"));
		choices.push_back(PMString("HyphenationLadder"));
		choices.push_back(PMString("NoBreak"));
		choices.push_back(PMString("HyphenateAcrossColumns"));
		choices.push_back(PMString("ProviderHyphenationStyle"));
		
		enum {	kHyphenateCapitalizedWords, 
				kHyphenationWeight, 
				kHyphenateLastWord,
				kMinimumCharactersBefore, 
				kMinimumCharactersAfter, 
				kShortestWordLength,
				kHyphenationMode, 
				kHyphenationZone, 
				kHyphenationLadder, 
				kNoBreak, 
				kHyphenateAcrossColumns,
				kProviderHyphenationStyle};
		
		int32 choice  = parameterUtils->GetChoice("What attribute do you wish to change.", choices);
		if (parameterUtils->WasDialogCancelled() == kFalse) {
			switch (choice) 
			{
				case kHyphenateCapitalizedWords:
					{
						bool8 t = kFalse;
						if(this->getBoolValue(t,PMString("Hyphenate capital words?"))==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenCapBoss,t);
						break;
					}
				case kHyphenationWeight:
					{
						int16 t = 0;
						if(this->getInt16Value(t,PMString("Hyphenation weight?"),10)==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenWeightBoss,t);
						break;
					}
				case kHyphenateLastWord:
					{
						bool8 t = kFalse;
						if(this->getBoolValue(t,PMString("Hyphenate last word?"))==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenLastBoss,t);
						break;
					}
				case kNoBreak:
					{
						bool8 t = kFalse;
						if(this->getBoolValue(t,PMString("Apply no break?"))==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrNoBreakBoss,t);
						break;
					}
				case kMinimumCharactersBefore:
					{
						int16 t = 0;
						if(this->getInt16Value(t,PMString("Minimum chars before?"),15)==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrMinBeforeBoss,t);
						break;
					}
				case kMinimumCharactersAfter:
					{
						int16 t = 0;
						if(this->getInt16Value(t,PMString("Minimum characters after?"),15)==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrMinAfterBoss,t);
						break;
					}
				case kShortestWordLength:
					{
						int16 t = 0;
						if(this->getInt16Value(t,PMString("Minimum chars in word?"),25)==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrShortestWordBoss,t);
						break;
					}
				case kHyphenationMode:
					{
						IHyphenationStyle::HyphenationMethod hm = IHyphenationStyle::kHyphensOff;

						if(this->getHyphenMode(hm,PMString("Hyphenation mode?"))==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenModeBoss,hm);
						break;
					}
				case kHyphenationZone:
					{
						PMReal t = 0.0;
						if(this->getRealValue(t,PMString("Hyphenation zone?"),PMReal(200.0))==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenZoneBoss,t);
						break;
					}
				case kHyphenationLadder:
					{
						int16 t = 0;
						if(this->getInt16Value(t,PMString("Hyphenation ladder?"),50)==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenLadderBoss,t);
						break;
					}
				case kHyphenateAcrossColumns:	//CS3
					{
						bool8 t = kFalse;
						if(this->getBoolValue(t,PMString("Hyphenate across columns?"))==kFailure){
							break;
						}
						status = this->ModifyHyphenationPolicy(iTextAttributeSuite,kTextAttrCrossFrameHyphenBoss,t);
						break;
					}
				case kProviderHyphenationStyle:	//CC13
				{
					IHyphenationStyle::ProviderHyphenationStyle phs = IHyphenationStyle::kHyph_All;

					if (this->getProviderHyphenStyle(phs, PMString("Provider hyphenation style?")) == kFailure) {
						break;
					}
					status = this->ModifyHyphenationPolicy(iTextAttributeSuite, kTextAttrProviderHyphStyleBoss, phs);
					break;
				}
				default:
					{
						SNIPLOG("No such choice");
					}
			}
		}		

	}while (kFalse);
	return status;
}


/*
*/
ErrorCode 
SnpHyphenation::ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const IHyphenationStyle::HyphenationMethod value)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextAttrHyphenMode> iTextAttrHyphenMode(::CreateObject2<ITextAttrHyphenMode>(attribute));

		if (iTextAttrHyphenMode == nil){
			ASSERT(iTextAttrHyphenMode);
			break;
		}
		iTextAttrHyphenMode->SetMethod(value);		

		status = iTextAttributeSuite->ApplyAttribute(iTextAttrHyphenMode);
	}while (kFalse);
	return status;
}

/*
*/
ErrorCode
SnpHyphenation::ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const IHyphenationStyle::ProviderHyphenationStyle value)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ITextAttrProviderHyphStyle> iTextAttrProviderHyphStyle(::CreateObject2<ITextAttrProviderHyphStyle>(attribute));

		if (iTextAttrProviderHyphStyle == nil) {
			ASSERT(iTextAttrProviderHyphStyle);
			break;
		}
		iTextAttrProviderHyphStyle->SetProviderHyphStyle(value);

		status = iTextAttributeSuite->ApplyAttribute(iTextAttrProviderHyphStyle);
	} while (kFalse);
	return status;
}


/*
*/
ErrorCode 
SnpHyphenation::ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const bool8 value)
{
	return iTextAttributeSuite->SetBooleanAttribute(attribute,value);
}

/**
*/
ErrorCode 
SnpHyphenation::ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const PMReal value)
{
	return iTextAttributeSuite->SetRealNumberAttribute(attribute,value);
}

/*
*/
ErrorCode 
SnpHyphenation::ModifyHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, const int16 value)
{
	return iTextAttributeSuite->SetInt16Attribute(attribute,value);
}

/*
*/
ErrorCode 
SnpHyphenation::reportAttribute(const IAttrReport* iAttrReport, PMString description)
{
	ErrorCode status = kFailure;
	do
	{
		if (iAttrReport == nil)
		{
			ASSERT(iAttrReport);
			break;
		}
		iAttrReport->AppendDescription(&description,::GetDataBase(iAttrReport),nil);
		ClassID attribute = ::GetClass(iAttrReport);
		// a more complete description for attributes that are a little opaque
		if (attribute == kTextAttrHyphenCapBoss || attribute == kTextAttrHyphenLastBoss || attribute == kTextAttrNoBreakBoss){
			InterfacePtr<ITextAttrBoolean> iTextAttrBoolean(iAttrReport,UseDefaultIID());
			if (iTextAttrBoolean == nil){
				ASSERT(iTextAttrBoolean);
				break;
			}
			iTextAttrBoolean->GetFlag() ? description.Append(" Boolean attr ON") : description.Append(" Boolean attr OFF");
		}
		else if (attribute == kTextAttrHyphenModeBoss) {
			InterfacePtr<ITextAttrHyphenMode> iTextAttrHyphenMode(iAttrReport,UseDefaultIID());
			if (iTextAttrHyphenMode == nil)	{
				ASSERT(iTextAttrHyphenMode);
				break;
			}
			IHyphenationStyle::HyphenationMethod hypMethod = iTextAttrHyphenMode->GetMethod();
			switch (hypMethod)
			{
				case IHyphenationStyle::kHyphensOff:
				{
					description.Append(" Hyphenation off");
					break;
				}
				case IHyphenationStyle::kHyphensManual:
				{
					description.Append(" Manual hyphenation");
					break;
				}
				case IHyphenationStyle::kHyphensDictionary:
				{
					description.Append(" Dictionary hyphenation");
					break;
				}
				case IHyphenationStyle::kHyphensAlgorithm:
				{
					description.Append(" Algorithmic hyphenation");
					break;
				}
			}
		}
		else if (attribute == kTextAttrProviderHyphStyleBoss) {
			InterfacePtr<ITextAttrProviderHyphStyle> iTextAttrProviderHyphStyle(iAttrReport, UseDefaultIID());
			if (iTextAttrProviderHyphStyle == nil) {
				ASSERT(iTextAttrProviderHyphStyle);
				break;
			}
			IHyphenationStyle::ProviderHyphenationStyle providerHyphenationStyle = iTextAttrProviderHyphStyle->GetProviderHyphStyle();
			switch (providerHyphenationStyle)
			{
			case IHyphenationStyle::kHyph_All:
			{
				description.Append(" Hyphenation All");
				break;
			}
			case IHyphenationStyle::kHyph_AllButUnaesthetic:
			{
				description.Append(" Hyphenation All But Unaesthetic");
				break;
			}
			case IHyphenationStyle::kHyph_Aesthetic:
			{
				description.Append(" Hyphenation Aesthetic");
				break;
			}
			case IHyphenationStyle::kHyph_PreferredAesthetic:
			{
				description.Append(" Hyphenation Preferred Aesthetic");
				break;
			}
			}
		}
	
		SNIPLOG(description.GetPlatformString().c_str());
		status = kSuccess;
	} while(kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpHyphenation::ReportHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite, const ClassID attribute, PMString description)
{
	ErrorCode status = kFailure;
	do 
	{
		InterfacePtr<const IAttrReport> iAttrReport(static_cast<const IAttrReport*>(iTextAttributeSuite->QueryAttributeN(0, attribute, IID_IATTRREPORT)));
		if (iAttrReport == nil)
		{
			ASSERT(iAttrReport);
			break;
		}
		status = this->reportAttribute(iAttrReport,description);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpHyphenation::ReportHyphenationPolicy(ITextAttributeSuite* iTextAttributeSuite)
{
	ErrorCode status = kFailure;
	do {
		if (iTextAttributeSuite == nil)
		{
			ASSERT(iTextAttributeSuite);
			break;
		}

		if (!iTextAttributeSuite->CanQueryAttributes())
		{
			SNIPLOG("Can not query text attribute. No text in selection?");
			break;
		}

		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenCapBoss,PMString("Capitalisation")) == kFailure){
			SNIPLOG("No hyphen capitalisation attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenWeightBoss,PMString("Weight")) == kFailure){
			SNIPLOG("No hyphen weight attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenLastBoss,PMString("Hyphenate last")) == kFailure){
			SNIPLOG("No hyphen last attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrMinBeforeBoss,PMString("Minimum chars before")) == kFailure){
			SNIPLOG("No hyphen min chars before attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrMinAfterBoss,PMString("Minimum chars after")) == kFailure){
			SNIPLOG("No hyphen min chars after attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrShortestWordBoss,PMString("Shortest word")) == kFailure){
			SNIPLOG("No hyphen shortest word attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenModeBoss,PMString("Mode")) == kFailure){
			SNIPLOG("No hyphen mode attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenZoneBoss,PMString("Zone")) == kFailure){
			SNIPLOG("No hyphen zone attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrHyphenLadderBoss,PMString("Ladder")) == kFailure){
			SNIPLOG("No hyphen ladder attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrNoBreakBoss,PMString("No Break")) == kFailure){
			SNIPLOG("No \"No break\" attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite,kTextAttrCrossFrameHyphenBoss,PMString("Hyphenate Across Columns")) == kFailure){
			SNIPLOG("No hyphenate across columns attribute?");
			break;
		}
		if (this->ReportHyphenationPolicy(iTextAttributeSuite, kTextAttrProviderHyphStyleBoss, PMString("Provider Hyphenation Style")) == kFailure) {
			SNIPLOG("No provider hyphenation style attribute?");
			break;
		}
		status = kSuccess;
	} while (kFalse);
	return status;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpHyphenation available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerHyphenation : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerHyphenation(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerHyphenation(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
		
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/* Constructor.
*/
_SnpRunnerHyphenation::_SnpRunnerHyphenation(void) : SnpRunnable("Hyphenation")
{
	this->SetDescription("Manipulate hyphenation aspects");
    this->SetPreconditions("none");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerHyphenation::~_SnpRunnerHyphenation(void)
{
	// do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerHyphenation::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerHyphenation::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		InterfacePtr<ITextAttributeSuite> iTextAttributeSuite(runnableContext, UseDefaultIID());
		if (iTextAttributeSuite == nil)
		{
			SNIPLOG("Snippet needs a text attribute suite");
			break;
		}		


		SnpHyphenation instance;
		// Get parameters.
		Utils<ISnipRunParameterUtils> parameterUtils;

		// Get which choice the user wants to run.
		K2Vector<PMString> choices;
		choices.push_back(PMString("ReportHyphenationPolicy"));
		choices.push_back(PMString("ModifyHyphenationPolicy"));
		enum {kReportHyphenationPolicy, kModifyHyphenationPolicy};
		int32 choice  = parameterUtils->GetChoice("What do you want to do.", choices);
		if (parameterUtils->WasDialogCancelled() == kFalse) {
			switch (choice) 
			{
				case kReportHyphenationPolicy:
					{
						status = instance.ReportHyphenationPolicy(iTextAttributeSuite);
						break;
					}
				case kModifyHyphenationPolicy:
					{
						status = instance.ModifyHyphenationPolicy(iTextAttributeSuite);
						break;
					}
				default:
					{
						SNIPLOG("No such choice");
					}
			}
		}		
	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerHyphenation instance_SnpRunnerHyphenation;
DEFINE_SNIPPET(_SnpRunnerHyphenation) 	
