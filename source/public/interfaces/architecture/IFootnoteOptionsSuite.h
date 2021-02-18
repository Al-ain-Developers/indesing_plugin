//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFootnoteOptionsSuite.h $
//  
//  Owner: rkamicar
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _IFootnoteOptionsSuite_
#define _IFootnoteOptionsSuite_

#include "IPMUnknown.h"
#include "IFootnoteSettings.h"
#include "IFootnoteSettingsCmdData.h"

/** IFootnoteOptionsSuite

	@note See IFootnoteSettings for descriptions of most of these methods as this is a mirror interface to that.
*/
class IFootnoteOptionsSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFOOTNOTEOPTIONS_ISUITE };

	/** Can the options be set?  (i.e. does the current selection make sense for footnote options)
	*/
	virtual bool16 CanApplyFootnoteOptions(void) const = 0;


	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::MarkerPositionOptions GetMarkerPositioning() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMarkerPositioning(IFootnoteSettings::MarkerPositionOptions positioning) = 0;

	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::RestartNumberingOptions GetRestartOption() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetRestartOption(IFootnoteSettings::RestartNumberingOptions option) = 0;

	/** See IFootnoteSettings
	*/
	virtual int32 GetStartingNumber() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetStartingNumber(int32 n) = 0;

	/** See IFootnoteSettings
	*/
	virtual ClassID GetNumberingMethod() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetNumberingMethod(ClassID whichMethod) = 0;

	/** See IFootnoteSettings
	*/
	virtual const WideString& GetMarkerPrefix() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMarkerPrefix(const WideString& pre) = 0;

	/** See IFootnoteSettings
	*/
	virtual const WideString& GetMarkerSuffix() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMarkerSuffix(const WideString& suf) = 0;

	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::SuffixPrefixUsageOptions GetPrefixSuffixUsage() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetPrefixSuffixUsage(IFootnoteSettings::SuffixPrefixUsageOptions options) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetFootnoteMarkerStyle() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetFootnoteMarkerStyle(UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetFootnoteParagraphStyle() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetFootnoteParagraphStyle(UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual const WideString& GetFootnoteSeparator() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void  SetFootnoteSeparator(const WideString& sep) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetSpaceBetween() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetSpaceBetween(PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetSpacerHeight() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetSpacerHeight(PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual Text::FirstLineOffsetMetric GetFirstLineOffset() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetFirstLineOffset(Text::FirstLineOffsetMetric flo) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetMinFirstLineOffset() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMinFirstLineOffset(PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetEndOfStoryPlacement() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetEndOfStoryPlacement(bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetNoSplitting() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetNoSplitting(bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetStraddlingInfo() const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetStraddlingInfo(bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetSeparatorLineOn(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetSeparatorLineOn(IFootnoteSettings::FootnoteRuleKind k, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetWeightStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetWeightStroke(IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual ICompositionStyle::StrokeType GetStrokeType(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetStrokeType(IFootnoteSettings::FootnoteRuleKind k, ICompositionStyle::StrokeType s) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetIndentLeft(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetIndentLeft(IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetWidth(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetWidth(IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetOffset(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetOffset(IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetColorStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetColorStroke(IFootnoteSettings::FootnoteRuleKind k, UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetTintStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetTintStroke(IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetOverprintStroke(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetOverprintStroke(IFootnoteSettings::FootnoteRuleKind k, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetColorGap(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetColorGap(IFootnoteSettings::FootnoteRuleKind k, UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetTintGap(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetTintGap(IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetOverprintGap(IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetOverprintGap(IFootnoteSettings::FootnoteRuleKind k, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual void SetAllSettings(const IFootnoteSettingsCmdData::FootnotePrefs* settings,
									const IFootnoteSettingsCmdData::FootnoteLinePrefs* separator,
									const IFootnoteSettingsCmdData::FootnoteLinePrefs* continuing) = 0;
};

#endif // _IFootnoteOptionsSuite_
