//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippetsME/SnpApplyMEAttributes.cpp $
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

// Interface includes:
#include "ICompositionStyle.h"
#include "IDrawingStyle.h"


#include "ITextAttrUtils.h"
#include "ITextAttrClassID.h"
#include "ISelectionUtils.h"
#include "ITextAttributeSuite.h"
#include "IComposeScanner.h" // use SnpTextAttrHelper
#include "ITextTarget.h"
#include "ITextFocus.h"
#include "IAttrReport.h"

// ME Attributes
#include "IJustifMethodAttr.h"
#include "IHindiDigitsAttr.h"
#include "IDiacVPosAttr.h"
#include "IKashidaAttr.h"
#include "IDirOverrideAttr.h"

// General includes:
#include "TextRange.h"
#include "TCID.h" // for composer boss class IDs


// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpTextAttrHelper.h"

class SnpApplyMEAttributes : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		SnpApplyMEAttributes();

		/** Destructor.
		 */
		virtual			~SnpApplyMEAttributes();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			Change the value of text attributes in all the given items.
			Other methods are called to carry out the item chosen by the menu.
			All methods called by this method take in an ITextAttributeSuite.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
		
	private:
		ClassID composerClass;
};


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor.
*/
SnpApplyMEAttributes::SnpApplyMEAttributes() : SnpRunnable("ApplyMEAttributes") 
{
	// Describe what your snippet does.
	this->SetDescription("Apply ME text attributes");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("some text must be selected");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_cjk, sdk_text");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
SnpApplyMEAttributes::~SnpApplyMEAttributes()
{
}

/* Check if your preconditions are met.
*/
bool16	SnpApplyMEAttributes::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) {
			break;
		}
		 // Get the text range 
        InDesign::TextRange textRange(textFocus); 
        if (textRange.IsValid() == kFalse) 
        { 
            break; 
        } 

        // make sure the composer is a ME composer 
        ClassID theComposerClass(kInvalidClass); 
        ErrorCode status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, theComposerClass);

        if (theComposerClass != kOptycaParagraphComposerBoss &&
			theComposerClass != kOptycaSingleComposerBoss)
        { 
            break; 
        } 
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode SnpApplyMEAttributes::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kCancel;

	do {		
		// Require a text selection to be able to run.
		
		InterfacePtr<ITextAttributeSuite> textAttributeSuite(runnableContext, UseDefaultIID());
		if (textAttributeSuite == nil)
		{
			SNIPLOG("You do not have a text attribute suite. Exiting...");
			break;
		}		
		
		if (!textAttributeSuite->CanApplyAttributes())
		{
			SNIPLOG("Can't apply attributes.");
			break;
		}
		
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

		// make sure the composer is a ME composer 
        ClassID theComposerClass(kInvalidClass);
        ErrorCode status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, theComposerClass);

        if (theComposerClass != kOptycaParagraphComposerBoss &&
			theComposerClass != kOptycaSingleComposerBoss)
        { 
			SNIPLOG("The selected text is not using a ME text composer, " 
                    "so ME attributes will not compose properly.\n" 
                    "Please use Optyca paragraph or single-line composer."); 
            break; 
        } 
		
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		if (textModel == nil) 
		{
			break;
		}
		
		InterfacePtr<IComposeScanner> compScanner(textModel, UseDefaultIID());
		if (compScanner == nil) 
		{
			break;
		}

		RangeData rangeData = textRange.GetRange();
		IDrawingStyle* drawStyle = compScanner->GetParagraphStyleAt(rangeData.Start(nil), nil);
		if (drawStyle == nil) 
		{
			break;
		}

		InterfacePtr<ICompositionStyle> compStyle(drawStyle, UseDefaultIID());
		if (compStyle == nil) 
		{
			break;
		}
		
		// Ask for the type of attribute to be applied.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Change Paragraphe Direction"));
		choices.push_back(PMString("Change Character Direction"));
		choices.push_back(PMString("Apply ME Justification"));
		choices.push_back(PMString("Change Digits "));
		choices.push_back(PMString("Positionning Diacritic"));
		choices.push_back(PMString("Apply Kashida"));
		enum { kChangeParaDir, kChangeCharDir, kApplyJustif, kChangeDigits, kPositionDiac, kSetKashida };
		int32 choice  = parameterUtils->GetChoice("Choose which ME text attribute you want to apply.", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		
		// Ask for the attribute's value.
		switch (choice) 
		{
			default:
			case kChangeParaDir:
				{
					int32 dirPara = compStyle->GetParagraphDirection();
					if (dirPara == ICompositionStyle::kParagraphDirLTR)
						result = textAttributeSuite->ChangeParagraphDirection(ICompositionStyle::kParagraphDirRTL);
					else
						result = textAttributeSuite->ChangeParagraphDirection(ICompositionStyle::kParagraphDirLTR);
					if(result != kSuccess){
						SNIPLOG("Set Paragraphe Dir failed!");
					}
					break;
				}

			case kChangeCharDir:
				{
					result = kSuccess;
					K2Vector<PMString> names;
					names.push_back("Default");
					names.push_back("Left To Right");
					names.push_back("Right To Left");
					enum { kDefault, kL2R, kR2L };
					int32 dir  = parameterUtils->GetChoice("Choose direction attribute you want to apply on character(s).", names);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}
					
					InterfacePtr<IDirOverrideAttr> dirOverride(static_cast<IDirOverrideAttr*>(::CreateObject(kDirOverrideAttrBoss, IID_IDIROVERRIDEATTR)) );
					if (dirOverride)
						{
						switch (dir)
						{
						case 0:
							dirOverride->Set(IDirOverrideAttr::kDirOverrideDefault); break;
						case 1:
							dirOverride->Set(IDirOverrideAttr::kDirOverrideLTR); break;
						case 2:
							dirOverride->Set(IDirOverrideAttr::kDirOverrideRTL); break;
						default:
							dirOverride->Set(IDirOverrideAttr::kDirOverrideDefault); break;						
						}
						InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, textFocus->GetCurrentRange(), dirOverride, kCharAttrStrandBoss));
						result = CmdUtils::ProcessCommand(cmd);
						}

					if(result != kSuccess) {
						SNIPLOG("Set dir override failed!");
					}

					break;
				}

			case kApplyJustif:
				{
					result = kSuccess;
					K2Vector<PMString> names;
					names.push_back("kJustifMethodDefault");
					names.push_back("kJustifMethodArabic");
					names.push_back("kJustifMethodNaskh");
					names.push_back("kJustifMethodTraditionalNaskhTatweel");
					names.push_back("kJustifMethodTraditionalNaskhKashida");
					names.push_back("kJustifMethodTraditionalNaskhTatweelFrac");
					names.push_back("kJustifMethodTraditionalNaskhKashidaFrac");
					int32 justif  = parameterUtils->GetChoice("Choose text justif attribute you want to apply.", names);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}

					InterfacePtr<IJustifMethodAttr> justifAttr(static_cast<IJustifMethodAttr*>(::CreateObject(kJustifMethodAttrBoss, IID_IJUSTIFMETHODATTR)) );
					if (justifAttr)
						{
						switch (justif)
						{
						case 0:
							justifAttr->Set(IJustificationStyle::kJustifMethodDefault); break;
						case 1:
							justifAttr->Set(IJustificationStyle::kJustifMethodArabic); break;
						case 2:
							justifAttr->Set(IJustificationStyle::kJustifMethodNaskh); break;
						case 3:
							justifAttr->Set(IJustificationStyle::kJustifMethodTraditionalNaskhTatweel); break;
						case 4:
							justifAttr->Set(IJustificationStyle::kJustifMethodTraditionalNaskhKashida); break;
						case 5:
							justifAttr->Set(IJustificationStyle::kJustifMethodTraditionalNaskhTatweelFrac); break;
						case 6:
							justifAttr->Set(IJustificationStyle::kJustifMethodTraditionalNaskhKashidaFrac); break;
						default:
							justifAttr->Set(IJustificationStyle::kJustifMethodTraditionalNaskhKashidaFrac); break;						
						}
						InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, textFocus->GetCurrentRange(), justifAttr, kParaAttrStrandBoss));
						result = CmdUtils::ProcessCommand(cmd);
						}
					
					if(result != kSuccess) {
						SNIPLOG("Set Justif Attribute failed!");
					}
					break;
				}

			case kChangeDigits:
				{
					result = kSuccess;
					K2Vector<PMString> names;
					names.push_back("Standard");
					names.push_back("Arabic");
					names.push_back("Hindi");
					names.push_back("Farsi");
					enum { kDefault, kArabic, kHindi, kFarsi };
					int32 digits  = parameterUtils->GetChoice("Choose digits attribute you want to apply.", names);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}

					InterfacePtr<IDigitsAttr> digitsAttr(static_cast<IDigitsAttr*>(::CreateObject(kDigitsAttrBoss, IID_IDIGITSATTR)) );
					if (digitsAttr)
						{
						switch (digits)
						{
						case 0:
							digitsAttr->Set(IDigitsAttr::kDefaultDigits); break;
						case 1:
							digitsAttr->Set(IDigitsAttr::kArabicDigits); break;
						case 2:
							digitsAttr->Set(IDigitsAttr::kHindiDigits); break;
						case 3:
							digitsAttr->Set(IDigitsAttr::kFarsiDigits); break;						
						default:
							digitsAttr->Set(IDigitsAttr::kDefaultDigits); break;						
						}
						InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, textFocus->GetCurrentRange(), digitsAttr, kCharAttrStrandBoss));
						result = CmdUtils::ProcessCommand(cmd);
						}
					
					if(result != kSuccess) {
						SNIPLOG("Set Justif Attribute failed!");
					}

					break;
				}

			case kPositionDiac:
				{
					result = kSuccess;
					K2Vector<PMString> names;
					names.push_back("kDiacVPosOTFromBaseline");
					names.push_back("None");
					names.push_back("Loose");
					names.push_back("Normal");
					names.push_back("Tight");
					names.push_back("kDiacVPosOpenType");
					
					int32 diacVPos  = parameterUtils->GetChoice("Choose diac. position attribute you want to apply.", names);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}

					InterfacePtr<IDiacVPosAttr> diacAttr(static_cast<IDiacVPosAttr*>(::CreateObject(kDiacVPosAttrBoss, IID_IDIACVPOSATTR)) );
					if (diacAttr)
						{
						switch (diacVPos)
						{
						case 0:
							diacAttr->Set(IDiacVPosAttr::kDiacVPosOTFromBaseline); break;
						case 1:
							diacAttr->Set(IDiacVPosAttr::kDiacVPosOff); break;
						case 2:
							diacAttr->Set(IDiacVPosAttr::kDiacVPosLoose); break;
						case 3:
							diacAttr->Set(IDiacVPosAttr::kDiacVPosMedium); break;						
						case 4:
							diacAttr->Set(IDiacVPosAttr::kDiacVPosOpenType); break;						
						default:
							diacAttr->Set(IDiacVPosAttr::kDiacVPosOTFromBaseline); break;
						}
						InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, textFocus->GetCurrentRange(), diacAttr, kCharAttrStrandBoss));
						result = CmdUtils::ProcessCommand(cmd);
						}
					
					if(result != kSuccess) {
						SNIPLOG("Set Justif Attribute failed!");
					}
					
					break;
				}

			case kSetKashida:
				{					
					result = kSuccess;
					K2Vector<PMString> names;
					names.push_back("Enable Kashida");
					names.push_back("Disable Kashida");
					
					enum { kEnableKashida, kDisableKashida };
					int32 Kashida  = parameterUtils->GetChoice("Choose kashida attribute ON/OFF you want to apply.", names);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}
					
					InterfacePtr<IKashidaAttr> kashidaAttr(static_cast<IKashidaAttr*>(::CreateObject(kKashidaAttrBoss, IID_IKASHIDAATTR)) );
					if (kashidaAttr)
						{
						switch (Kashida)
						{
						case 0:
							kashidaAttr->Set(IKashidaAttr::kKashidaDefault); break;
						case 1:
							kashidaAttr->Set(IKashidaAttr::kKashidaOff); break;
						default:
							kashidaAttr->Set(IKashidaAttr::kKashidaDefault); break;
						}
						InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, textFocus->GetCurrentRange(), kashidaAttr, kCharAttrStrandBoss));
						result = CmdUtils::ProcessCommand(cmd);
						}
					break;
				}
		}
	} while(false);
	return (result);
}

/*	Declare an instance to register the snippet with the framework.
*/
SnpApplyMEAttributes instanceSnpApplyMEAttributes;

// End, SnpApplyMEAttributes.cpp

