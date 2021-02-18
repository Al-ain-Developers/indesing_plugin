//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFootnoteFacade.h $
//  
//  Owner: David Stephens
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
#ifndef __IFootnoteFacade__
#define __IFootnoteFacade__

#include "IPMUnknown.h"

#include "IFootnoteOptionsSuite.h"

/** A high level API for dealing with footnotes.  To use this Facade, include
	this header file and the use the following example syntax:
	Utils<IFootnoteFacade>()->SetMode( pageItem, mode );

	@note See IFootnoteSettings for descriptions of these methods as this is a mirror interface to that.
*/
class IFootnoteFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFOOTNOTEFACADE };

	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::MarkerPositionOptions GetMarkerPositioning(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMarkerPositioning(IFootnoteSettings* target, IFootnoteSettings::MarkerPositionOptions positioning) = 0;

	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::RestartNumberingOptions GetRestartOption(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetRestartOption(IFootnoteSettings* target, IFootnoteSettings::RestartNumberingOptions option) = 0;

	/** See IFootnoteSettings
	*/
	virtual int32 GetStartingNumber(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetStartingNumber(IFootnoteSettings* target, int32 n) = 0;

	/** See IFootnoteSettings
	*/
	virtual ClassID GetNumberingMethod(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetNumberingMethod(IFootnoteSettings* target, ClassID whichMethod) = 0;

	/** See IFootnoteSettings
	*/
	virtual const WideString& GetMarkerPrefix(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMarkerPrefix(IFootnoteSettings* target, const WideString& pre) = 0;

	/** See IFootnoteSettings
	*/
	virtual const WideString& GetMarkerSuffix(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMarkerSuffix(IFootnoteSettings* target, const WideString& suf) = 0;

	/** See IFootnoteSettings
	*/
	virtual IFootnoteSettings::SuffixPrefixUsageOptions GetPrefixSuffixUsage(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetPrefixSuffixUsage(IFootnoteSettings* target, IFootnoteSettings::SuffixPrefixUsageOptions options) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetFootnoteMarkerStyle(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetFootnoteMarkerStyle(IFootnoteSettings* target, UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetFootnoteParagraphStyle(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetFootnoteParagraphStyle(IFootnoteSettings* target, UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual const WideString& GetFootnoteSeparator(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void  SetFootnoteSeparator(IFootnoteSettings* target, const WideString& sep) = 0;

	// The space between footnote parcels
	/** See IFootnoteSettings
	*/
	virtual PMReal GetSpaceBetween(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetSpaceBetween(IFootnoteSettings* target, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetSpacerHeight(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetSpacerHeight(IFootnoteSettings* target, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual Text::FirstLineOffsetMetric GetFirstLineOffset(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetFirstLineOffset(IFootnoteSettings* target, Text::FirstLineOffsetMetric flo) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetMinFirstLineOffset(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetMinFirstLineOffset(IFootnoteSettings* target, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetEndOfStoryPlacement(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetEndOfStoryPlacement(IFootnoteSettings* target, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetNoSplitting(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetNoSplitting(IFootnoteSettings* target, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetStraddlingInfo(IFootnoteSettings* target) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetStraddlingInfo(IFootnoteSettings* target, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetSeparatorLineOn(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetSeparatorLineOn(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetWeightStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetWeightStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual ICompositionStyle::StrokeType GetStrokeType(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetStrokeType(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, ICompositionStyle::StrokeType s) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetIndentLeft(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetIndentLeft(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetWidth(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetWidth(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetOffset(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetOffset(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetColorStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetColorStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetTintStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetTintStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetOverprintStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetOverprintStroke(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual UID GetColorGap(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetColorGap(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, UID s) = 0;

	/** See IFootnoteSettings
	*/
	virtual PMReal GetTintGap(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetTintGap(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, PMReal g) = 0;

	/** See IFootnoteSettings
	*/
	virtual bool16 GetOverprintGap(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k) const = 0;
	/** See IFootnoteSettings
	*/
	virtual void SetOverprintGap(IFootnoteSettings* target, IFootnoteSettings::FootnoteRuleKind k, bool16 b) = 0;

	/** See IFootnoteSettings
	*/
	virtual void SetAllSettings(IFootnoteSettings* target, const IFootnoteSettingsCmdData::FootnotePrefs* settings,
									const IFootnoteSettingsCmdData::FootnoteLinePrefs* separator,
									const IFootnoteSettingsCmdData::FootnoteLinePrefs* continuing) = 0;
};

#endif	// __IFootnoteFacade__
