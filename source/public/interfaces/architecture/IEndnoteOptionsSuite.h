//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IEndnoteOptionsSuite.h $
//  
//  Owner: Susmita Singh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef _IEndnoteOptionsSuite_
#define _IEndnoteOptionsSuite_

#include "IPMUnknown.h"
#include "IEndnoteSettings.h"

/** IEndnoteOptionsSuite

@note See IEndnoteSettings for descriptions of most of these methods as this is a mirror interface to that.
*/
class IEndnoteOptionsSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IENDNOTEOPTIONS_ISUITE };

	/** Can the options be set?  (i.e. does the current selection make sense for endnote options)
	*/
	virtual bool16 CanApplyEndnoteOptions(void) const = 0;

	/** See IEndnoteSettings
	*/
	virtual WideString GetTitle() const = 0;
	virtual void SetTitle(WideString title) = 0;

	/** See IEndnoteSettings
	*/
	virtual UID GetHeaderParaStyle() const = 0;
	virtual void SetHeaderParaStyle(UID styleID) = 0;

	/** See IEndnoteSettings
	*/
	virtual IEndnoteSettings::RestartNumberingOptions GetRestartOption() const = 0;
	virtual void SetRestartOption(IEndnoteSettings::RestartNumberingOptions option) = 0;

	/** See IEndnoteSettings
	*/
	virtual int32 GetStartingNumber() const = 0;
	virtual void SetStartingNumber(int32 n) = 0;

	/** See IEndnoteSettings
	*/
	virtual ClassID GetNumberingMethod() const = 0;
	virtual void SetNumberingMethod(ClassID whichMethod) = 0;

	/** See IEndnoteSettings
	*/
	virtual IEndnoteSettings::MarkerPositionOptions GetMarkerPositioning() const = 0;
	virtual void SetMarkerPositioning(IEndnoteSettings::MarkerPositionOptions option) = 0;

	/** See IEndnoteSettings
	*/
	virtual UID GetMarkerStyle() const = 0;
	virtual void SetMarkerStyle(UID styleID) = 0;

	/** See IEndnoteSettings
	*/
	virtual UID GetEndnoteParagraphStyle() const = 0;
	virtual void SetEndnoteParagraphStyle(UID s) = 0;

	/** See IEndnoteSettings
	*/
	virtual const WideString& GetEndnoteSeparator() const = 0;
	virtual void  SetEndnoteSeparator(const WideString& sep) = 0;

	/** See IEndnoteSettings
	*/
	virtual IEndnoteSettings::Scope GetScope() const = 0;
	virtual void SetScope(IEndnoteSettings::Scope scope) = 0;

	/** See IEndnoteSettings
	*/
	virtual IEndnoteSettings::Place GetPlace() const = 0;
	virtual void SetPlace(IEndnoteSettings::Place place) = 0;

	/** See IEndnoteSettings
	*/
	virtual const WideString& GetMarkerPrefix() const = 0;
	virtual void SetMarkerPrefix(const WideString& pre) = 0;

	/** See IEndnoteSettings
	*/
	virtual const WideString& GetMarkerSuffix() const = 0;
	virtual void SetMarkerSuffix(const WideString& suf) = 0;

	/** See IEndnoteSettings
	*/
	virtual IEndnoteSettings::SuffixPrefixUsageOptions GetPrefixSuffixUsage() const = 0;
	virtual void SetPrefixSuffixUsage(IEndnoteSettings::SuffixPrefixUsageOptions options) = 0;

	/** Set all settings related to endnotes
	*/
	virtual void SetAllSettings(const IEndnoteSettings::EndnotePrefs* settings) = 0;
};

#endif // _IEndnoteOptionsSuite_
