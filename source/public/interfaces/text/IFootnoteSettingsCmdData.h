//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFootnoteSettingsCmdData.h $
//  
//  Owner:
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

#pragma once
#ifndef __IFootnoteSettingsCmdData__
#define __IFootnoteSettingsCmdData__

#include "IPMUnknown.h"
#include "ITextAttrStrokeType.h"
#include "IWorkspace.h"
#include "ISwatchList.h"
#include "IStyleNameTable.h"
#include "IFootnoteSettings.h"
#include "IStyleGroupManager.h"
#include "UIDRef.h"
#include "PMReal.h"
#include "WideString.h"

#include "ILayoutUIUtils.h"
#include "LocaleSetting.h"

#include "TextID.h"
#include "InstStrokeFillID.h"

/**
	@ingroup text_layout

	@note See IFootnoteSettings for descriptions of some of these methods as this is a mirror interface to a lot of that.
*/
class IFootnoteSettingsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFOOTNOTESETTINGSCMDDATA };

	/** Return which sets of settings have been changed.
	*/
	virtual void GetWhichSettings(bool16* settings, bool16* separator, bool16* continuing) const = 0;

	// Settings
	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::MarkerPositionOptions GetMarkerPositioning() const = 0;
	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::SuffixPrefixUsageOptions GetPrefixSuffixUsage() const = 0;
	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::RestartNumberingOptions GetRestartOption() const = 0;
	/** See IFootnoteSettings
	*/
	virtual int32 GetStartingNumber() const = 0;
	/** See IFootnoteSettings
	*/
	virtual ClassID GetNumberingMethod() const = 0;
	/** See IFootnoteSettings
	*/
	virtual UID GetFootnoteMarkerStyle() const = 0;
	/** See IFootnoteSettings
	*/
	virtual UID GetFootnoteParagraphStyle() const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetSpaceBetween() const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetSpacerHeight() const = 0;
	/** See IFootnoteSettings
	*/
	virtual Text::FirstLineOffsetMetric GetFirstLineOffset() const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetMinFirstLineOffset() const = 0;
	/** See IFootnoteSettings
	*/
	virtual bool16 GetEndOfStoryPlacement() const = 0;
	/** See IFootnoteSettings
	*/
	virtual bool16 GetNoSplitting() const = 0;
	/** See IFootnoteSettings
	*/
	virtual const WideString& GetMarkerPrefix() const = 0;
	/** See IFootnoteSettings
	*/
	virtual const WideString& GetMarkerSuffix() const = 0;
	/** See IFootnoteSettings
	*/
	virtual const WideString& GetFootnoteSeparator() const = 0;

	// separator, continuing Rule
	/** See IFootnoteSettings
	*/
	virtual bool16 GetSeparatorLineOn(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetWeightStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual ICompositionStyle::StrokeType GetStrokeType(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetIndentLeft(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetWidth(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetOffset(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual UID GetColorStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetTintStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual bool16 GetOverprintStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual UID GetColorGap(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual PMReal GetTintGap(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual bool16 GetOverprintGap(IFootnoteSettings::FootnoteRuleKind k) const = 0;

	/** Get the document associated to these changes (i.e. the document of the selection). Returns nil, if no document.
	*/
	virtual const UIDRef& GetDocument() = 0;
	/** Get the straddling information associated with the document
	*/
	virtual bool16 GetStraddlingInfo() const = 0;

	/** Struct encapsulating the preferences for the footnotes
	*/
	struct FootnotePrefs
	{
		FootnotePrefs()
		{
			bool16 isCCJK = (LocaleSetting::GetLocale().GetLanguageFS() == kJapaneseLanguageFS);
			bool16 isCCKOnly = (isCCJK && (LocaleSetting::GetLocale().GetUserInterfaceId() == k_zhCN		// simplified
										|| LocaleSetting::GetLocale().GetUserInterfaceId() == k_zhTW	// traditional
										|| LocaleSetting::GetLocale().GetUserInterfaceId() == k_koKR ));	// Korean

			fPrefixSuffixUsage = IFootnoteSettings::kPrefixSuffixNone;
			fSeparator.Append(isCCJK ? kTextChar_IdeographicSpace : kTextChar_Tab);

			fMarkerStyle = kInvalidUID;
			fFootnoteStyle = kInvalidUID;

			fNumberingMethod = kArabicFootnoteNumberingBoss;

			fStartingNumber = 1;
			fRestartOption = IFootnoteSettings::kDontRestart;

			fMarkerPositioning = (!isCCJK || isCCKOnly) ? IFootnoteSettings::kPositionSuperscript
												: IFootnoteSettings::kPositionRuby;
			fGutterHeight = 0.0;
			fSpacerHeight = 0.0;
			fMinFirstLineOffset = 0.0;

			// ##: Last minute change - make J match R.  See bug #1101932
			fFirstLineOffset = Text::kFLOLeading;				// NOTE: All other cases (tables, columns) do Ascent

			fEndOfStoryPlacement = kFalse;
			fNoSplitting = kFalse;
			fEnableStraddling = kTrue;
		}

		FootnotePrefs(const IFootnoteSettings* target)
		{
			fPrefixSuffixUsage = target->GetPrefixSuffixUsage();
			fMarkerSuffix = target->GetMarkerSuffix();
			fMarkerPrefix = target->GetMarkerPrefix();
			fSeparator = target->GetFootnoteSeparator();

			fMarkerStyle = target->GetFootnoteMarkerStyle();
			fFootnoteStyle = target->GetFootnoteParagraphStyle();

			fNumberingMethod = target->GetNumberingMethod();

			fStartingNumber = target->GetStartingNumber();
			fRestartOption = target->GetRestartOption();

			fMarkerPositioning = target->GetMarkerPositioning();

			fGutterHeight = target->GetSpaceBetween();
			fSpacerHeight = target->GetSpacerHeight();

			fFirstLineOffset = target->GetFirstLineOffset();
			fMinFirstLineOffset = target->GetMinFirstLineOffset();

			fEndOfStoryPlacement = target->GetEndOfStoryPlacement();
			fNoSplitting = target->GetNoSplitting();
			fEnableStraddling = target->GetStraddlingInfo();
		}

		FootnotePrefs(const FootnotePrefs& other)
		{
			fPrefixSuffixUsage = other.fPrefixSuffixUsage;
			fMarkerSuffix = other.fMarkerSuffix;
			fMarkerPrefix = other.fMarkerPrefix;
			fSeparator = other.fSeparator;

			fMarkerStyle = other.fMarkerStyle;
			fFootnoteStyle = other.fFootnoteStyle;

			fNumberingMethod = other.fNumberingMethod;

			fStartingNumber = other.fStartingNumber;
			fRestartOption = other.fRestartOption;

			fMarkerPositioning = other.fMarkerPositioning;

			fGutterHeight = other.fGutterHeight;
			fSpacerHeight = other.fSpacerHeight;

			fFirstLineOffset = other.fFirstLineOffset;
			fMinFirstLineOffset = other.fMinFirstLineOffset;

			fEndOfStoryPlacement = other.fEndOfStoryPlacement;
			fNoSplitting = other.fNoSplitting;
			fEnableStraddling = other.fEnableStraddling;
		}

		void InitializeStyles(IWorkspace* workspace)
		{
			// Para style - go find the "NormalParagraphStyle"
			InterfacePtr<IStyleGroupManager> paraStyleNameTable(workspace, IID_IPARASTYLEGROUPMANAGER);
			UID defaultStyleUID = paraStyleNameTable->FindByName("NormalParagraphStyle");
			if (defaultStyleUID == kInvalidUID)
				defaultStyleUID = paraStyleNameTable->GetDefaultStyleUID();

			fFootnoteStyle = defaultStyleUID;

			// Char style - get the default (root) style.
			InterfacePtr<IStyleGroupManager> charStyleNameTable(workspace, IID_ICHARSTYLEGROUPMANAGER);
			defaultStyleUID = charStyleNameTable->GetRootStyleUID();

			fMarkerStyle = defaultStyleUID;
		}

		WideString	fMarkerSuffix, fMarkerPrefix;
		WideString	fSeparator;
		UID fMarkerStyle;
		UID fFootnoteStyle;

		ClassID fNumberingMethod;

		int32 fStartingNumber;
		PMReal fGutterHeight;
		PMReal fSpacerHeight;
		PMReal fMinFirstLineOffset;
		Text::FirstLineOffsetMetric fFirstLineOffset;
		IFootnoteSettings::RestartNumberingOptions fRestartOption;
		IFootnoteSettings::SuffixPrefixUsageOptions fPrefixSuffixUsage;
		IFootnoteSettings::MarkerPositionOptions fMarkerPositioning;

		bool16 fEndOfStoryPlacement;
		bool16 fNoSplitting;
		bool16 fEnableStraddling;
	};

	/** Struct encapsulating the preferences for line that separates the main text from the footnotes.
		This struct applies to both the line that separates a new footnote and that of a continuing footnote from the previous column/frame.
	*/
	struct FootnoteLinePrefs
	{
		FootnoteLinePrefs()
		{
			fStrokeType = ICompositionStyle::StrokeType(kSolidPathStrokerBoss, kInvalidUID);

			fColorStroke = kInvalidUID;
			fColorGap = kInvalidUID;
			fSeparatorLineOn = kTrue;
			fIndentLeft = 0.;
			fWidth = 0.;								// This is typically overridden by constructor, since each rule has different default.
			fOffset = 0.;
			fWeightStroke = 1.;
			fOverprintStroke = kFalse;
			fOverprintGap = kFalse;
			fTintStroke = 100;
			fTintGap = 100;
		}
		FootnoteLinePrefs(const IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k)
		{
			fStrokeType = target->GetStrokeType(k);
			fColorStroke = target->GetColorStroke(k);
			fColorGap = target->GetColorGap(k);
			fSeparatorLineOn = target->GetSeparatorLineOn(k);
			fIndentLeft = target->GetIndentLeft(k);
			fWidth = target->GetWidth(k);
			fOffset = target->GetOffset(k);
			fWeightStroke = target->GetWeightStroke(k);
			fTintStroke = target->GetTintStroke(k);
			fOverprintStroke = target->GetOverprintStroke(k);
			fTintGap = target->GetTintGap(k);
			fOverprintGap = target->GetOverprintGap(k);
		}
		FootnoteLinePrefs(const FootnoteLinePrefs& other)
		{
			fStrokeType = other.fStrokeType;
			fColorStroke = other.fColorStroke;
			fColorGap = other.fColorGap;
			fSeparatorLineOn = other.fSeparatorLineOn;
			fIndentLeft = other.fIndentLeft;
			fWidth = other.fWidth;
			fOffset = other.fOffset;
			fWeightStroke = other.fWeightStroke;
			fTintStroke = other.fTintStroke;
			fOverprintStroke = other.fOverprintStroke;
			fTintGap = other.fTintGap;
			fOverprintGap = other.fOverprintGap;
		}

		void InitializeColors(IWorkspace* workspace)
		{
			InterfacePtr<ISwatchList> swatchList(workspace, UseDefaultIID());
			UID blackSwatchUID(swatchList->GetBlackSwatchUID());
			UID noneSwatchUID(swatchList->GetNoneSwatchUID());

			fColorStroke = blackSwatchUID;
			fColorGap = noneSwatchUID;
		}

		bool16		fSeparatorLineOn;

		ICompositionStyle::StrokeType	fStrokeType;
		UID		fColorStroke;
		UID		fColorGap;

		PMReal		fIndentLeft;
		PMReal		fWidth;
		PMReal		fOffset;

		PMReal		fWeightStroke;
		PMReal		fTintStroke;
		bool16		fOverprintStroke;

		PMReal		fTintGap;
		bool16		fOverprintGap;
	};

	/** Initialize the data.
		@note Any of the settings parameters can be nil.  Non-nil settings will have all the individual settings changed.
	*/
	virtual void Set(const IFootnoteSettingsCmdData::FootnotePrefs* settings, const IFootnoteSettingsCmdData::FootnoteLinePrefs* separator,
					const IFootnoteSettingsCmdData::FootnoteLinePrefs* continuing, const UIDRef& doc) = 0;
};

#endif // __IFootnoteSettingsCmdData__
