//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformTextAttrWarichu.cpp $
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
#include "IAttrReport.h"
#include "IComposeScanner.h"
#include "ITextAttrClassID.h"
#include "ITextAttrInt16.h"
#include "ITextAttrRealNumber.h"
#include "ITextModelCmds.h"
#include "ITextTarget.h"
#include "ITextAttrAlign.h"

// General includes:
#include "CJKID.h"
#include "TCID.h" // for composer boss class IDs
#include "TextRange.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpTextAttrHelper.h"

/** Number of Warichu kinds
 */	
static const int16 kSnpNumWarichuAlignments = 12;

/** Warichu  Alignment name table
 */
static const char* kSnpWarichuAlignmentTable[kSnpNumWarichuAlignments] = { 
	"Warichu:AlignLeft",
	"Warichu:AlignCenter",
	"Warichu:AlignRight",
	"Warichu:AlignJustifyFull",
	"Warichu:AlignJustifyLeft",		// only warichu in 2.0
	"Warichu:AlignJustifyCenter",	// only warichu in 2.0
	"Warichu:AlignJustifyRight",	// only warichu in 2.0
	"Warichu:AlignAuto"             // only warichu in 2.0
};

// TODO align with coding conventions
/**
 * 	Stores all Warichu related attributes in a single structure.
 * 	Note that this sample only sets a few of the members, however
 * 	all members are inspected.
 * 	All member variables correspond to a Warichu attribute.
 */
struct SnpWarichuDataSettings
{
	// general Warichu settings

	/** Specifies whether Warichu is on or off.
	 * 	kTrue = on;
	 * 	kFalse = off
	 * 	@see kTAWarichuAttrBoss */
	bool16 fAttrOn;	 	

	/** Specifies the effective number of Warichu lines.
	 *	(2 ~ 5)
	 * 	@see kTAWarichuNumOfLineBoss */
	int16 fWarichuNumOfLine;

	/** Specifies the Warichu character size as a percentage of base character size.
	 *	(0.01 ~ 1)
	 * 	@see kTAWarichuRelativeSizeBoss */
	PMReal fWarichuRelativeSize;
	
	/** Specifies an interval in the space between the lines of Warichu. (Point)
	 *	(-10 ~ 1296)
	 * 	@see kTAWarichuLineSpacingBoss */
	PMReal fWarichuLineSpacing;
	
	/** Specifies the alignment of Warichu.
	 * 	@see kTAWarichuAlignmentBoss */
	ICompositionStyle::TextAlignment fWarichuAlignment;

	/** Specifies the minimum character number for line break at first line.
	 *	(1 - 10)
	 * 	@see kTAWarichuMinCharsBeforeBreakBoss */
	int16 fWarichuMinCharsBeforeBreak;
	
	/** Specifies the minimum character number for line break at last line.
	 *	(1 - 10)
	 * 	@see kTAWarichuMinCharsAfterBreakBoss */
	int16 fWarichuMinCharsAfterBreak;

};

/** 
	\li How to apply, remove, and inspect Japanese Warichu text attributes.
	
	"Warichu" refers to an in-line text annotation that is commonly used in Japanese text layout. It is
	used in ways similar to footnotes or endnotes in. In InDesign, Warichu is implemented as a group of
	text attributes along with appropriate support from the Japanese text composers. When you apply
	Warichu to your text, you must be using a Japanese text composer.
	
	<p><img src="../sdk/warichu.gif"></p>
	
	@ingroup sdk_snippet
	@ingroup sdk_text
	@ingroup sdk_cjk
	
	@see IAttrReport
	@see IComposeScanner
	@see ITextAttrClassID
	@see ITextAttrInt16
	@see ITextAttrRealNumber
	@see ITextFocus
	@see ITextModel
	@see ITextTarget
*/

class SnpPerformTextAttrWarichu 
{
public:
	/** Constructor.  
	*/
	SnpPerformTextAttrWarichu() {}

	/** Destructor.
	*/
	virtual ~SnpPerformTextAttrWarichu() {}	

	/**	Applies Warichu attributes onto the specified text model range.
	 * 	@param[in] textRange The text range to which you want to apply Warichu.
	 * 	@param[in] warichuData The Warichu settings.  Use SetWarichuData() to fill in the members. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode ApplyWarichu(const InDesign::TextRange& textRange, const SnpWarichuDataSettings& warichuData);

	/**	Removes (or simply turns off) Warichu attributes from the specified text model range.
	 * 	@param[in] textRange The text range from which you want to remove Warichu.
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode RemoveWarichu(const InDesign::TextRange& textRange);

	/**	Inspects Warichu attributes over the specified text model range.
	 * 	The details are printed onto the SNIPLOG.
	 * 	@param[in] textRange The text range from which you want to inspect Warichu.
	 * 	@param[out] warichuData The Warichu settings. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode InspectWarichu(const InDesign::TextRange& textRange, SnpWarichuDataSettings& warichuData);
	
	/** Sets the SnpWarichuDataSettings structure.
	 * 	@param[in] textRange The text range to use as a basis for some Warichu settings.
	 * 	@param[out] warichuData The Warichu settings that can be passed on to ApplyWarichu().
	 */
	void SetWarichuData(const InDesign::TextRange& textRange, SnpWarichuDataSettings& warichuData);
	
	/** Reports Warichu data to SNIPLOG.
	 * 	@param[in] warichuData The Warichu settings.  
	 */
	void ReportWarichuData(const SnpWarichuDataSettings& warichuData);

};


/* ApplyWarichu
*/
ErrorCode SnpPerformTextAttrWarichu::ApplyWarichu(const InDesign::TextRange& textRange, 
										  const SnpWarichuDataSettings& warichuData)
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
		InterfacePtr<IAttrReport> attr01(SnpTextAttrHelper::CreateTextBool16Attribute(kTAWarichuAttrBoss, warichuData.fAttrOn));
		attrList->ApplyAttribute(attr01);
		InterfacePtr<IAttrReport> attr02(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAWarichuNumOfLineBoss, warichuData.fWarichuNumOfLine));
		attrList->ApplyAttribute(attr02);
		InterfacePtr<IAttrReport> attr03(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAWarichuRelativeSizeBoss, warichuData.fWarichuRelativeSize));
		attrList->ApplyAttribute(attr03);
		InterfacePtr<IAttrReport> attr04(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAWarichuLineSpacingBoss, warichuData.fWarichuLineSpacing));
		attrList->ApplyAttribute(attr04);
		InterfacePtr<IAttrReport> attr05(SnpTextAttrHelper::CreateTextAttribute<ITextAttrAlign, ICompositionStyle::TextAlignment>(kTAWarichuAlignmentBoss, warichuData.fWarichuAlignment));
		attrList->ApplyAttribute(attr05);
		InterfacePtr<IAttrReport> attr06(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAWarichuMinCharsBeforeBreakBoss, warichuData.fWarichuMinCharsAfterBreak));
		attrList->ApplyAttribute(attr06);
		InterfacePtr<IAttrReport> attr07(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAWarichuMinCharsAfterBreakBoss, warichuData.fWarichuMinCharsAfterBreak));
		attrList->ApplyAttribute(attr07);

		// generate the command
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds);
		InterfacePtr<ICommand> applyCmd(textModelCmds->ApplyCmd(rangeData, attrList, kCharAttrStrandBoss));
		if (applyCmd == nil) 
		{
			ASSERT(applyCmd); break;
		}

		// process the command
		status = CmdUtils::ProcessCommand(applyCmd);

	} while(false);
	return status;
}

/* RemoveWarichu
*/
ErrorCode SnpPerformTextAttrWarichu::RemoveWarichu(const InDesign::TextRange& textRange)
{
	ErrorCode status = kFailure;
	do {
	
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
	
		// check if Warichu is on
		bool16 attrOn = kFalse;
	
		// Get TateChuyoko
        status = SnpTextAttrHelper::GetTextBool16Attribute(textRange, kTAWarichuAttrBoss, attrOn);

		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		else if (attrOn == kFalse) 
		{
			SNIPLOG("Warichu is not turned at the text selection... Skipping.");
			// exit with status == kSuccess
			status = kSuccess;
			break;
		}

		// Turn off Warichu.
		status = SnpTextAttrHelper::SetTextBool16Attribute(textRange, kTAWarichuAttrBoss, kFalse);
	
	} while (false);
	return status;
}

/* InspectWarichu
*/
ErrorCode SnpPerformTextAttrWarichu::InspectWarichu(const InDesign::TextRange& textRange, 
											SnpWarichuDataSettings& warichuData)
{
	ErrorCode status = kFailure;
	do {
	
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
		
		// Get Warichu attribute of character.
		SnpTextAttrHelper::GetTextBool16Attribute(textRange, kTAWarichuAttrBoss, warichuData.fAttrOn);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAWarichuNumOfLineBoss, warichuData.fWarichuNumOfLine);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAWarichuRelativeSizeBoss, warichuData.fWarichuRelativeSize);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAWarichuLineSpacingBoss, warichuData.fWarichuLineSpacing);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrAlign, ICompositionStyle::TextAlignment>(textRange, kTAWarichuAlignmentBoss, warichuData.fWarichuAlignment);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAWarichuMinCharsBeforeBreakBoss, warichuData.fWarichuMinCharsBeforeBreak);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAWarichuMinCharsAfterBreakBoss, warichuData.fWarichuMinCharsAfterBreak);
				
		// report this to SnipLog
		this->ReportWarichuData(warichuData);

		status = kSuccess;
	} while (false);
	return status;
}

/* SetWarichuData
*/
void SnpPerformTextAttrWarichu::SetWarichuData(const InDesign::TextRange& textRange, 
									   SnpWarichuDataSettings& warichuData)
{
	ErrorCode status = kFailure;
	do
	{
		//  general Warichu settings
		warichuData.fAttrOn = kTrue;
		warichuData.fWarichuNumOfLine = 2;
		warichuData.fWarichuRelativeSize = 0.5;
		warichuData.fWarichuLineSpacing = 0.0;
		warichuData.fWarichuAlignment = ICompositionStyle::kTextAlignLeft;
		warichuData.fWarichuMinCharsBeforeBreak = (int16)2.0;
		warichuData.fWarichuMinCharsAfterBreak = (int16)2.0;
		
		status = kSuccess;

	} while (false);
	ASSERT(status == kSuccess);
}

/* ReportWarichuData
*/
void SnpPerformTextAttrWarichu::ReportWarichuData(const SnpWarichuDataSettings& warichuData)
{
	SNIPLOG("=== SnpWarichuDataSettings (begin) ===");
	SNIPLOG("--- GENERAL SETTINGS ---");
	SNIPLOG("*Warichu: %s", warichuData.fAttrOn?"On":"OFF");
	SNIPLOG("*WarichuNumOfLine: %d", warichuData.fWarichuNumOfLine);
	SNIPLOG("*WarichuRelativeSize: %f %%", ::ToDouble(warichuData.fWarichuRelativeSize));
	SNIPLOG("*WarichuLineSpacing: %f pt", ::ToDouble(warichuData.fWarichuLineSpacing));
	SNIPLOG("*WarichuAlignment: %s", kSnpWarichuAlignmentTable[warichuData.fWarichuAlignment]);
	SNIPLOG("*WarichuMinCharsBeforeBreak: %d", warichuData.fWarichuMinCharsBeforeBreak);
	SNIPLOG("*WarichuMinCharsAfterBreak: %d", warichuData.fWarichuMinCharsAfterBreak);
	SNIPLOG("=== (end) ===");
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerPerformTextAttrWarichu : public SnpRunnable
{

	/** Indicates the type of operation, as specified by the SnippetRunner parameters. */
	typedef enum 
	{ 
		/** "inspect" operation */
		kInspect,
		/** "apply" operation */
		kApply,
		/** "remove" operation */
		kRemove, 
		/** Cancelled */
		kCancelled
	} eSnipWarichuOpcode;
	
	/** Get parameters and populates the SnpWarichuDataSettings. 
	 * 	@param textRange (in) The text range to use as a basis for some Warichu 
	 * 		settings, particularly those that depend on the base text.
	 * 	@param warichuData (out) The filled out SnpWarichuDataSettings structure. 
	 * 	@return The operation type indicated by the parameters. 
	 */
	eSnipWarichuOpcode GetParameters(const InDesign::TextRange& textRange, 
									SnpWarichuDataSettings& warichuData);

	

public:

	// SnippetRunner framework hooks.

	/** Constructor.  
	*/
	_SnpRunnerPerformTextAttrWarichu(void);

	/** Destructor..
	*/
	virtual ~_SnpRunnerPerformTextAttrWarichu(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@pre SnipRun::CanRun is kTrue
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);

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
};

/* Constructor.
*/
_SnpRunnerPerformTextAttrWarichu::_SnpRunnerPerformTextAttrWarichu(void) 
	: SnpRunnable("PerformTextAttrWarichu")
{
	this->SetDescription("Shows how to apply, remove, and inspect Warichu text attributes.");
	this->SetPreconditions("some text must be selected");
	this->SetCategories("sdk_snippet, sdk_cjk, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformTextAttrWarichu::~_SnpRunnerPerformTextAttrWarichu(void)
{
	// do nothing.
}


/* GetParameters
*/
_SnpRunnerPerformTextAttrWarichu::eSnipWarichuOpcode 
	_SnpRunnerPerformTextAttrWarichu::GetParameters(const InDesign::TextRange& textRange, 
							    			SnpWarichuDataSettings& warichuData)
{
	// set return opcode
	_SnpRunnerPerformTextAttrWarichu::eSnipWarichuOpcode opcode = _SnpRunnerPerformTextAttrWarichu::kCancelled;
	
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
		choices.push_back(PMString("inspect Warichu (default)"));	// 0 - shows Warichu attribute details on sniplog.
		choices.push_back(PMString("apply Warichu"));				// 1 - specify the Warichu. 
		choices.push_back(PMString("remove Warichu"));				// 2 - the Warichu under the current selected text is removed.

		int32 choice = parameterUtils->GetChoice(PMString("What operation do you want to perform?"), choices, 0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			opcode = _SnpRunnerPerformTextAttrWarichu::kCancelled;
			break;
		}
		
		// examine the choice
		switch (choice) 
		{
		
		case 0:
			// (option 0) inspect
			// (inspects Warichu attributes, prints message if there is no Warichu on current text)
			opcode = _SnpRunnerPerformTextAttrWarichu::kInspect;
			SNIPLOG("(Option 0): inspect");
			break;
		
		case 1:
			{
				// (option 1) apply kind [char] 
				SNIPLOG("(Option 1): apply");
				opcode = _SnpRunnerPerformTextAttrWarichu::kApply;
	
				// set the default Warichu data
				// sets kind as "none" by default
				SnpPerformTextAttrWarichu instance;
				instance.SetWarichuData(textRange, warichuData);
	
				// set the Warichu kind attribute according to the next choice
				choices.clear();
				choices.push_back(PMString("AlignLeft(default)")); // 1
				choices.push_back(PMString("AlignCenter")); // 2
				choices.push_back(PMString("AlignRight")); // 3
				choices.push_back(PMString("AlignJustifyFull")); // 4
				choices.push_back(PMString("AlignJustifyLeft")); // 5
				choices.push_back(PMString("AlignJustifyCenter")); // 6
				choices.push_back(PMString("AlignJustifyRight")); // 7
				choices.push_back(PMString("AlignAuto")); // 8
				
				choice = parameterUtils->GetChoice(PMString("Which kind of Warichu alignment do you want to apply?"), choices, 0);
				if (parameterUtils->WasDialogCancelled()) 
				{
					opcode = _SnpRunnerPerformTextAttrWarichu::kCancelled;
					break;
				}				
				
				warichuData.fWarichuAlignment = (ICompositionStyle::TextAlignment)choice; // ICompositionStyle::TextAlignment
				SNIPLOG("   %s", kSnpWarichuAlignmentTable[choice]);
			}
			break;
	
		case 2:
            // (option 2) remove 
			// (deletes current Warichu, prints message if there is no Warichu on current text)
			opcode = _SnpRunnerPerformTextAttrWarichu::kRemove;
			SNIPLOG("(Option 2): remove");
			break;

		default:
			opcode = _SnpRunnerPerformTextAttrWarichu::kInspect;
			SNIPLOG("Invalid option - using \"inspect\"");
			break;
		}
	} while (false);

	return opcode;
}

/* CanRun
*/
bool16 _SnpRunnerPerformTextAttrWarichu::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	// we need a text focus in order to run this snippet
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

		// check against known text composers that are known to compose Warichu attributes correctly
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

/* Run
*/
ErrorCode _SnpRunnerPerformTextAttrWarichu::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpPerformTextAttrWarichu instance;
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
		// this check was added so that when the Warichu attributes are applied, 
		// the adornments are properly displayed.
		ClassID composerClass(kInvalidClass);
		status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);

		// check against known text composers that are known to compose Warichu attributes correctly
		if (composerClass != kJParagraphComposerBoss &&
			composerClass != kJSingleComposerBoss) 
		{
			SNIPLOG("The selected text is not using a Japanese text composer, "
					"so Warichu attributes will not compose properly.\n"
					"Please use a Japanese paragraph or single-line composer.");
			break;
		}
		
		// create a local SnpWarichuDataSettings strcture to pass around.
		SnpWarichuDataSettings data;

		// get the parameters
		_SnpRunnerPerformTextAttrWarichu::eSnipWarichuOpcode opcode = this->GetParameters(textRange, data);
		
		switch (opcode) 
		{
		case _SnpRunnerPerformTextAttrWarichu::kApply:
			status = instance.ApplyWarichu(textRange, data);
			break;
		
		case _SnpRunnerPerformTextAttrWarichu::kRemove:
			status = instance.RemoveWarichu(textRange);
			break;
		
		case _SnpRunnerPerformTextAttrWarichu::kInspect:
			status = instance.InspectWarichu(textRange, data);
			break;
		
		case _SnpRunnerPerformTextAttrWarichu::kCancelled:
			status = kCancel;
			break;

		default:
			SNIPLOG("Invalid option. Skipping.");
			break;
		}
		
	} while (false);
	return status;
}

/* 
*/
bool16  _SnpRunnerPerformTextAttrWarichu::CanLoad() const
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
static _SnpRunnerPerformTextAttrWarichu instance_SnpRunnerPerformTextAttrWarichu;
DEFINE_SNIPPET(_SnpRunnerPerformTextAttrWarichu) 	

//End, SnpPerformTextAttrWarichu.cpp

