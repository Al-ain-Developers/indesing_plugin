//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformTextAttrTateChuYoko.cpp $
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
#include "IAttrReport.h" // Use SnpTextAttrHelper.
#include "IComposeScanner.h"
#include "ITextTarget.h"
#include "ITextFocus.h"
#include "ITextAttrClassID.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttrInt16.h"
#include "ITextModelCmds.h"
#include "IVerticalRelatedStyle.h" // TateChuYoko interface.

// General includes:
#include "Utils.h"
#include "TextRange.h" // namespace InDesign
#include "TCID.h" // for composer boss class IDs
#include "TextID.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// Depends on turn to read.
#include "SnpTextAttrHelper.h" // namespace SnpTextAttrHelper

// TODO align with coding conventions
/**
 * 	Stores all TateChuYoko related attributes in a single structure.
 * 	Note that this sample only sets a few of the members, however
 * 	all members are inspected.
 * 	All member variables correspond to a YateChuYoko attribute.
*/
struct SnpTateChuYokoSttings
{
	
	// Character attributes
		
	/** Specifies whether TateChuYoko is on or off.
	 * 	kTrue = on;
	 * 	kFalse = off
	 * 	@see kTATatechuyokoAttrBoss */
	bool16 fAttrOn;	 	

	/**	Specifies the X-distance of tateChuYoko from the base text in points.
		(-1000 - 1000)
	 * 	@see kTATatechuyokoXOffsetBoss */
	PMReal fXOffset;
	
	/**	Specifies the Y-distance of tateChuYoko from the base text in points.
		(-1000 - 1000)
	 * 	@see kTATatechuyokoXOffsetBoss */
	PMReal fYOffset;
	
	// Paragraph attributes
		
	/** Specifies the effective number of characters to display horizontally within vertical text.
		(0-10)
	 * 	@see kTAKumiNumberReportBoss */
	int16 fKumiNumber;

	/** Specifies whether to rotate Roman alphabet characters as well as single-byte numerics (kTrue)
		or only single-byte numerics (kFalse).
	 * 	kTrue = on;
	 * 	kFalse = off
	 * 	@see kTAKumiNumberWithRomanReportBoss */
	bool16 fKumiNumberWithRoman;
	
};


/** 
	\li How to apply, remove, and inspect Japanese TateChuYoko text attributes.

  	@ingroup sdk_snippet
	@ingroup sdk_text
	@ingroup sdk_cjk
	@see IAttrReport
	@see IComposeScanner
	@see ITextAttrBoolean
	@see ITextAttrClassID
	@see ITextAttrInt16
	@see ITextAttrRealNumber
	@see ITextFocus
	@see ITextModel
	@see ITextTarget
	@see ITextModelCmds
	@see IVerticalRelatedStyle
 */
class SnpPerformTextAttrTateChuYoko 
{
	public:

		/** Constructor.
		 */
		SnpPerformTextAttrTateChuYoko() {}

		/** Destructor.
		 */
		virtual			~SnpPerformTextAttrTateChuYoko() {}

		/**	Applies TateChuYoko attributes onto the specified text model range.
		 * 	@param[in] textRange The text range to which you want to apply TateChuYoko.
		 * 	@param[in] TCYData The TateChuYoko settings.  Use SetTateChuYokoData() to fill in the members. 
		 * 	@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode ApplyTateChuYoko(const InDesign::TextRange& textRange, const SnpTateChuYokoSttings& TCYData);

		/**	Applies automatic TateChuYoko attributes onto the specified paragraph.
		 * 	@param[in] textRange The text range to which you want to apply TateChuYoko.
		 * 	@param[in] TCYData The TateChuYoko settings.  Use SetTateChuYokoData() to fill in the members. 
		 * 	@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode ApplyAutomaticTateChuYoko(const InDesign::TextRange& textRange, const SnpTateChuYokoSttings& TCYData);

		/**	Removes (or simply turns off) TateChuYoko attributes from the specified text model range.
		 * 	@param[in] textRange The text range from which you want to remove TateChuYoko.
		 * 	@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode RemoveTateChuYoko(const InDesign::TextRange& textRange);
		
		/**	Removes (or simply turns off) automatic TateChuYoko attributes from the specified paragraph.
		 * 	@param[in] textRange The text range from which you want to remove TateChuYoko.
		 * 	@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode RemoveAutomaticTateChuYoko(const InDesign::TextRange& textRange);

		/**	Inspects TateChuYoko attributes over the specified text model range.
		 * 	The details are printed onto the SNIPLOG.
		 * 	@param[in] textRange The text range from which you want to inspect TateChuYoko.
		 * 	@param[out] TCYData The TateChuYoko settings. 
		 * 	@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode InspectTateChuYoko(const InDesign::TextRange& textRange, SnpTateChuYokoSttings& TCYData);

		/** Sets the SnpTateChuYokoSttings structure.
		 * 	@param[out] TCYData The TateChuYoko settings that can be passed on to ApplyTateChuYoko().
		 */
		void SetTateChuYokoData(SnpTateChuYokoSttings& TCYData);
		
		/** Reports TateChuYoko data to SNIPLOG.
		 * 	@param[in] TCYData The TateChuYoko settings.  
		 */
		void ReportTateChuYokoData(const SnpTateChuYokoSttings& TCYData);

};



/* ApplyTateChuYoko
*/
ErrorCode SnpPerformTextAttrTateChuYoko::ApplyTateChuYoko(const InDesign::TextRange& textRange, const SnpTateChuYokoSttings& TCYData)
{
	ErrorCode status = kFailure;
	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();
		
		// Check for valid length. 
		if (rangeData.Length() <= 0)
		{
			SNIPLOG("You must have a positive number of text characters selected. Please try again.");
			break;
		}
        
		// create an AttributeBossList so we can apply all attributes in one operation.
		boost::shared_ptr<AttributeBossList> attrList (new AttributeBossList);
		if (attrList.get() == nil) 
		{
			ASSERT(attrList);
			break;
		}

		InterfacePtr<IAttrReport> attr01(SnpTextAttrHelper::CreateTextBool16Attribute(kTATatechuyokoAttrBoss, TCYData.fAttrOn));
		attrList->ApplyAttribute(attr01);
		InterfacePtr<IAttrReport> attr02(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTATatechuyokoXOffsetBoss, TCYData.fXOffset));
		attrList->ApplyAttribute(attr02);
		InterfacePtr<IAttrReport> attr03(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTATatechuyokoXOffsetBoss, TCYData.fYOffset));
		attrList->ApplyAttribute(attr03);
		
		// generate the command
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds);
		InterfacePtr<ICommand> applyCmd(textModelCmds->ApplyCmd(rangeData, attrList, kCharAttrStrandBoss));  // for Caracter attriibute strand boss.
		if (applyCmd == nil) 
		{
			ASSERT(applyCmd); break;
		}

		// process the command
		status = CmdUtils::ProcessCommand(applyCmd);

	} while(false);
	return status;
}

/* ApplyAutomaticTateChuYoko
*/
ErrorCode SnpPerformTextAttrTateChuYoko::ApplyAutomaticTateChuYoko(const InDesign::TextRange& textRange, const SnpTateChuYokoSttings& TCYData)
{
	ErrorCode status = kFailure;
	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();
		
		// Check for valid length. 
		if (rangeData.Length() <= 0)
		{
			SNIPLOG("You must have a positive number of text characters selected. Please try again.");
			break;
		}
        
		// create an AttributeBossList so we can apply all attributes in one operation.
		boost::shared_ptr<AttributeBossList> attrList (new AttributeBossList);
		if (attrList.get() == nil) 
		{
			ASSERT(attrList);
			break;
		}

		InterfacePtr<IAttrReport> attr01(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKumiNumberReportBoss, TCYData.fKumiNumber));
		attrList->ApplyAttribute(attr01);
		InterfacePtr<IAttrReport> attr02(SnpTextAttrHelper::CreateTextBool16Attribute(kTAKumiNumberWithRomanReportBoss, TCYData.fKumiNumberWithRoman));
		attrList->ApplyAttribute(attr02);
		
		// generate the command
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds);
		InterfacePtr<ICommand> applyCmd(textModelCmds->ApplyCmd(rangeData, attrList, kParaAttrStrandBoss));
		if (applyCmd == nil) 
		{
			ASSERT(applyCmd); break;
		}

		// process the command
		status = CmdUtils::ProcessCommand(applyCmd);

	} while(false);
	return status;
}

/* RemoveTateChuYoko
*/
ErrorCode SnpPerformTextAttrTateChuYoko::RemoveTateChuYoko(const InDesign::TextRange& textRange)
{
	ErrorCode status = kFailure;
	do {
	
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
	
		// check if TetechuYoko is on
		bool16 attrOn = kFalse;
	
		// Get TateChuyoko
        status = SnpTextAttrHelper::GetTextBool16Attribute(textRange, kTATatechuyokoAttrBoss, attrOn);

		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		else if (attrOn == kFalse) 
		{
			SNIPLOG("TateChuYoko is not turned at the text selection... Skipping.");
			// exit with status == kSuccess
			status = kSuccess;
			break;
		}

		// Turn off TateChuyoko.
		status = SnpTextAttrHelper::SetTextBool16Attribute(textRange, kTATatechuyokoAttrBoss, kFalse);
	
	} while (false);
	return status;
}

/* RemoveAutomaticTateChuYoko
*/
ErrorCode SnpPerformTextAttrTateChuYoko::RemoveAutomaticTateChuYoko(const InDesign::TextRange& textRange)
{
	ErrorCode status = kFailure;
	do {
	
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
	
		// check if TeteChuYoko is on
		int16 kumiNumber = 0;
	
		// Get TateChuyoko
        status = SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16>(textRange, kTAKumiNumberReportBoss, kumiNumber);


		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		else if (kumiNumber == 0) 
		{
			SNIPLOG("Automatic TateChuYoko is not turned at the text selection... Skipping.");
			// exit with status == kSuccess
			status = kSuccess;
			break;
		}

		// Turn off Automatic TateChuyoko.
		status = SnpTextAttrHelper::SetTextInt16Attribute(textRange, kTAKumiNumberReportBoss, 0, kParaAttrStrandBoss);
	
	} while (false);
	return status;
}

/* InspectTateChuYoko
*/
ErrorCode SnpPerformTextAttrTateChuYoko::InspectTateChuYoko(const InDesign::TextRange& textRange, SnpTateChuYokoSttings& TCYData)
{
	ErrorCode status = kFailure;
	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
		
		// Get TateChuYoko attribute of character.
		// Cheack if tateChuYoko is On.
		SnpTextAttrHelper::GetTextBool16Attribute(textRange, kTATatechuyokoAttrBoss, TCYData.fAttrOn);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTATatechuyokoXOffsetBoss, TCYData.fXOffset);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTATatechuyokoYOffsetBoss, TCYData.fYOffset);

		// Get automatic tateChuYoko attribute of Paragraph.
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAKumiNumberReportBoss, TCYData.fKumiNumber);
		SnpTextAttrHelper::GetTextBool16Attribute(textRange, kTAKumiNumberWithRomanReportBoss, TCYData.fKumiNumberWithRoman);
		
		// report this to SnipLog
		this->ReportTateChuYokoData(TCYData);
	
		status = kSuccess;

	}while(false);
	
	return status;
}

/* SetTateChuYokoData
*/
void SnpPerformTextAttrTateChuYoko::SetTateChuYokoData(SnpTateChuYokoSttings& TCYData)
{
	// For TateChuYoko attribute of character.
	TCYData.fAttrOn = kTrue;
	TCYData.fXOffset = 0;
	TCYData.fYOffset = 0;
	
	// For automatic TateChuYoko attribute of paragraph.
	TCYData.fKumiNumber = 2;
	TCYData.fKumiNumberWithRoman = kFalse;
}

/* ReportTateChuYokoData
*/
void SnpPerformTextAttrTateChuYoko::ReportTateChuYokoData(const SnpTateChuYokoSttings& TCYData)
{
	SNIPLOG("=== TateChuYokoDataSettings (begin) ===");
	SNIPLOG("--- Character attribute TateChuYoko SETTINGS ---");
	SNIPLOG("*TateChuYoko: %s", TCYData.fAttrOn?"On":"OFF");
	SNIPLOG("*XOffset: %f", ::ToDouble(TCYData.fXOffset));
	SNIPLOG("*YOffset: %f", ::ToDouble(TCYData.fYOffset));
	
	SNIPLOG("--- Paragraph attribute automatic TateChuYoko SETTINGS ---");
	SNIPLOG("*NumOfKumiNumber: %d", TCYData.fKumiNumber);
	SNIPLOG("*KumiNumberWithRoman: %s", TCYData.fKumiNumberWithRoman?"On":"OFF");
	SNIPLOG("=== (end) ===");
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerPerformTextAttrTateChuYoko : public SnpRunnable
{

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerPerformTextAttrTateChuYoko();

		/** Destructor.
		 */
		virtual			~_SnpRunnerPerformTextAttrTateChuYoko();

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

		/** Only present this snippet in the framework's UI if the
			language feature set is Japanese and the product is not
			InCopy.
			@return kTrue if the snippet can be loaded, kFalse otherwise.
		*/
		bool16 CanLoad() const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}

		/** Indicates the type of operation, as specified by the SnippetRunner parameters. */
		typedef enum 
		{ 
			/** "inspect" operation */
			kInspect,
			/** "apply" operation */
			kApplyTateChuYoko,
			/** "remove" operation */
			kRemoveTateChuYoko, 
			/** "apply" automatic tatechuyoko operation on paragraph */
			kApplyAutomaticTateChuYoko,
			/** "remove" automatic tatechuyoko operation on paragraph */
			kRemoveAutomaticTateChuYoko, 
			/** Cancelled */
			kCancelled
		} eSnipTateChuYokoOpcode;

		/** Get parameters and populates the SnpTateChuYokoSttings. 
		 * 	@param textRange (in) The text range to use as a basis for some TateChuYoko settings.
		 * 	@param TCYData (out) The filled out SnpTateChuYokoSttings structure. 
		 * 	@return The operation type indicated by the parameters. 
		 */
		eSnipTateChuYokoOpcode GetParameters(const InDesign::TextRange& textRange, SnpTateChuYokoSttings& TCYData);
};
/* Constructor.
*/
_SnpRunnerPerformTextAttrTateChuYoko::_SnpRunnerPerformTextAttrTateChuYoko()
	: SnpRunnable("PerformTextAttrTateChuYoko")
{
	this->SetDescription("Shows how to apply, remove, and inspect TateChuYoko text attributes.");
	this->SetPreconditions("some text must be selected");
	this->SetCategories("sdk_snippet, sdk_cjk, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformTextAttrTateChuYoko::~_SnpRunnerPerformTextAttrTateChuYoko()
{
}

/* GetParameters
*/
_SnpRunnerPerformTextAttrTateChuYoko::eSnipTateChuYokoOpcode 
	_SnpRunnerPerformTextAttrTateChuYoko::GetParameters(const InDesign::TextRange& textRange, SnpTateChuYokoSttings& TCYData)
{
	// set return opcode
	_SnpRunnerPerformTextAttrTateChuYoko::eSnipTateChuYokoOpcode opcode = _SnpRunnerPerformTextAttrTateChuYoko::kCancelled;

	// create a parameter utils to use in this method
	Utils<ISnipRunParameterUtils> parameterUtils;
	K2Vector<PMString> choices;

	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

        // first, get a choice of operations
		choices.clear();
		choices.push_back(PMString("inspect TateChuYoko (default)"));				// 0 
		choices.push_back(PMString("apply TateChuYoko to characters"));				// 1
		choices.push_back(PMString("remove TateChuYoko from characters"));			// 2
		choices.push_back(PMString("apply automatic TateChuYoko to paragraph"));	// 3 
		choices.push_back(PMString("remove automatic TateChuYoko from paragraph"));	// 4

		int32 choice = parameterUtils->GetChoice(PMString("What operation do you want to perform?"), choices, 0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			opcode = _SnpRunnerPerformTextAttrTateChuYoko::kCancelled;
			break;
		}
		
		// examine the choice
		switch (choice) 
		{
		
			case 0:
				// (option 0) inspect
				// (inspects TateChuYoko attributes, prints message if there is not TateChuYoko on current text)
				opcode = _SnpRunnerPerformTextAttrTateChuYoko::kInspect;
				SNIPLOG("(Option 0): inspect");
				break;
				
			case 1:
				// (option 1) apply TateChuYoko
				opcode = _SnpRunnerPerformTextAttrTateChuYoko::kApplyTateChuYoko;
				SNIPLOG("(Option 1): apply TateChuYoko");
				break;
			case 2:
				// (option 2) remove TateChuYoko
				opcode = _SnpRunnerPerformTextAttrTateChuYoko::kRemoveTateChuYoko;
				SNIPLOG("(Option 2): remove TateChuYoko");
				break;
			case 3:
				// (option 3) apply automatic TateChuYoko
				opcode = _SnpRunnerPerformTextAttrTateChuYoko::kApplyAutomaticTateChuYoko;
				SNIPLOG("(option 3) apply automatic TateChuYoko");
				break;
			case 4:
				// (option 4) remove automatic TateChuYoko
				opcode = _SnpRunnerPerformTextAttrTateChuYoko::kRemoveAutomaticTateChuYoko;
				SNIPLOG("(option 4) remove automatic TateChuYoko");
				break;
			default:
				opcode = _SnpRunnerPerformTextAttrTateChuYoko::kInspect;
				SNIPLOG("Invalid option - using \"inspect\"");
				break;
		}		
	}while(false);
	
	return opcode;
}
/* Check if your preconditions are met.
*/
bool16	_SnpRunnerPerformTextAttrTateChuYoko::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) 
		{
			break;
		}

		// Get the text range
		InDesign::TextRange textRange(textFocus);
		if (textRange.IsValid() == kFalse)
		{
			break;
		}

		// make sure the composer is a Japanese composer
		ClassID composerClass(kInvalidClass);
		ErrorCode status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);

		// check against known text composers that are known to compose TateChuYoko attributes correctly
		if (composerClass != kJParagraphComposerBoss &&
			composerClass != kJSingleComposerBoss) 
		{
			break;
		}

		// if we got to this point, we can run this snippet.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPerformTextAttrTateChuYoko::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpPerformTextAttrTateChuYoko instance;
		// we need a text focus in order to run this snippet
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			ASSERT(textTarget);
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) 
		{
			SNIPLOG("You do not have any text selection - please select some text first.");
			break;
		}

		// Get the text range
		InDesign::TextRange textRange(textFocus);
		if (textRange.IsValid() == kFalse)
		{
			SNIPLOG("The textRange is invalid!");
			break;
		}

		// make sure the composer is a Japanese composer
		// NOTE: Any body of text can carry any set of attributes, however, 
		// this check was added so that when the TateChuYoko attributes are applied, 
		// the adornments are properly displayed.
		ClassID composerClass(kInvalidClass);
		status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);

		// check against known text composers that are known to compose TateChuYoko attributes correctly
		if (composerClass != kJParagraphComposerBoss &&
			composerClass != kJSingleComposerBoss) 
		{
			SNIPLOG("The selected text is not using a Japanese text composer, "
					"so TateChuYoko attributes will not compose properly.\n"
					"Please use a Japanese paragraph or single-line composer.");
			break;
		}
		
		// create a local TateChuYokoSettings strcture to pass around.
		SnpTateChuYokoSttings data;
		instance.SetTateChuYokoData(data);
		
		// get the parameters
		_SnpRunnerPerformTextAttrTateChuYoko::eSnipTateChuYokoOpcode opcode = this->GetParameters(textRange, data);

		switch (opcode) 
		{

		case _SnpRunnerPerformTextAttrTateChuYoko::kApplyTateChuYoko:
			status = instance.ApplyTateChuYoko(textRange, data);
			break;
			
		case _SnpRunnerPerformTextAttrTateChuYoko::kRemoveTateChuYoko:
			status = instance.RemoveTateChuYoko(textRange);
			break;
			
		case _SnpRunnerPerformTextAttrTateChuYoko::kApplyAutomaticTateChuYoko:
			status = instance.ApplyAutomaticTateChuYoko(textRange,data);
			break;
			
		case _SnpRunnerPerformTextAttrTateChuYoko::kRemoveAutomaticTateChuYoko:
			status = instance.RemoveAutomaticTateChuYoko(textRange);
			break;
		
		case _SnpRunnerPerformTextAttrTateChuYoko::kInspect:
			status = instance.InspectTateChuYoko(textRange, data);
			break;
			
		case _SnpRunnerPerformTextAttrTateChuYoko::kCancelled:
			status = kCancel;
			break;

		default:
			SNIPLOG("Invalid option. Skipping.");
			break;
		}
		
	} while (false);
	return (status);
}

/* 
*/
bool16  _SnpRunnerPerformTextAttrTateChuYoko::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS) == kFalse) {
		// Only load under the Japanese language feature set.
		result = kFalse;
	}
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS) == kTrue) {
		// Don't load under InCopy product.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPerformTextAttrTateChuYoko instance_SnpRunnerPerformTextAttrTateChuYoko;
DEFINE_SNIPPET(_SnpRunnerPerformTextAttrTateChuYoko) 	

// End, SnpTemplate.cpp

