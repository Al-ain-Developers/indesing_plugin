//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpTextAttrHelper.cpp $
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

// Framework includes:
#include "SnipRunLog.h" 

// General includes
#include "AttributeBossList.h"
#include "CJKID.h"
#include "CmdUtils.h"
#include "PersistUtils.h"
#include "RangeData.h"
#include "TCID.h" // for composer boss class IDs
#include "TextAttrID.h"
#include "TextID.h"
#include "TextRange.h"
#include "Utils.h"

// Interface includes
#include "IAttrReport.h"
#include "ICommand.h"
#include "IComposeScanner.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrFont.h"
#include "ITextAttrInt16.h"
#include "ITextAttrUtils.h"
#include "ITextModel.h"


#include "SnpTextAttrHelper.h"
//using namespace SnpTextAttrHelper;

// General functions


/* GetTextBool16Attribute
*/
ErrorCode SnpTextAttrHelper::GetTextBool16Attribute(const InDesign::TextRange& textRange, 
								 const ClassID& attrClassID, 
								 bool16& value)
{
	// Assume failure.
	ErrorCode status = kFailure;
	do 
	{
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();
		
		// Query the compose scanner to access text attributes
		InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
		if (composeScanner == nil) 
		{
			ASSERT(composeScanner); break;
		}
		
		// Query attribute report interface
		int32 attrLen = 0;
		InterfacePtr<const IAttrReport> attrReport(composeScanner->QueryAttributeAt(rangeData, attrClassID, &attrLen));
		if (attrReport == nil) 
		{
			SNIPLOG("Could not find text attribute with Class ID 0x%X on the selected text!", attrClassID.Get());
			break;
		}
		
		// Query the ITextAttrBoolean interface
		InterfacePtr<ITextAttrBoolean> attr(attrReport, UseDefaultIID());
		if (attr == nil) 
		{
			ASSERT(attr); break;
		}
		
		// Get the attribute value.
		value = attr->Get();
		status = kSuccess;
	} while (false);
	return status;
}

/* GetTextFontStyleAttribute
*/
ErrorCode SnpTextAttrHelper::GetTextFontStyleAttribute(const InDesign::TextRange& textRange, 
									const ClassID& attrClassID, 
									PMString& fontName)
{
	// Assume failure.
	ErrorCode status = kFailure;
	do 
	{
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();
		
		// Query the compose scanner to access text attributes
		InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
		if (composeScanner == nil) 
		{
			ASSERT(composeScanner); break;
		}
		
		// Query attribute report interface
		int32 attrLen = 0;
		InterfacePtr<const IAttrReport> attrReport(composeScanner->QueryAttributeAt(rangeData, attrClassID, &attrLen));
		if (attrReport == nil) 
		{
			SNIPLOG("Could not find text attribute with Class ID 0x%X on the selected text!", attrClassID.Get());
			break;
		}
		
		// Query the ITextAttrFont interface
		InterfacePtr<ITextAttrFont> attr(attrReport, UseDefaultIID());
		if (attr == nil) 
		{
			ASSERT(attr); break;
		}
		
		// Get the attribute value.
		fontName = attr->GetFontName();
		status = kSuccess;
	} while (false);
	return status;
}


/* CreateTextBool16Attribute
*/
IAttrReport* SnpTextAttrHelper::CreateTextBool16Attribute(const ClassID& attrClassID, const bool16& value)
{
	IAttrReport* attrReport = nil;
	do {
		// create the text attribute boss
		InterfacePtr<ITextAttrBoolean> attr(::CreateObject2<ITextAttrBoolean>(attrClassID));
		if (attr == nil)
		{
			ASSERT_FAIL("attr is nil!");
			break;
		}
		// set the attribute value
		attr->Set(value);

		InterfacePtr<IAttrReport> localAttrReport(attr, UseDefaultIID());
        attrReport = localAttrReport.forget();
	} while (false);
	ASSERT(attrReport);

	return attrReport;
}

/* CreateTextFontStyleAttribute
*/
IAttrReport* SnpTextAttrHelper::CreateTextFontStyleAttribute(const ClassID& attrClassID, 
										  const PMString& fontName)
{
	IAttrReport* attrReport = nil;
	do {
		// create the text attribute boss
		InterfacePtr<ITextAttrFont> attr(::CreateObject2<ITextAttrFont>(attrClassID));
		if (attr == nil)
		{
			ASSERT_FAIL("attr is nil!");
			break;
		}
		// set the attribute value
		attr->SetFontName(fontName);

		InterfacePtr<IAttrReport> localAttrReport(attr, UseDefaultIID());
        attrReport = localAttrReport.forget();
	} while (false);
	ASSERT(attrReport);

	return attrReport;
}


/* SetTextBool16Attribute
*/
ErrorCode SnpTextAttrHelper::SetTextBool16Attribute(const InDesign::TextRange& textRange, 
								 const ClassID& attrClassID, 
								 const bool16 value,
								 const ClassID& whichStrand /*= kCharAttrStrandBoss*/)
{
	// Assume failure.
	ErrorCode status = kFailure;
	do 
	{
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		const RangeData rangeData = textRange.GetRange();
		
		// create the text attribute boss
		InterfacePtr<ITextAttrBoolean> attr(::CreateObject2<ITextAttrBoolean>(attrClassID));
		if (attr == nil)
		{
			ASSERT_FAIL("attr is nil!");
			break;
		}
		// set the attribute value
		attr->Set(value);

		// create the text attribute command
		InterfacePtr<ICommand> cmd(
			Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, rangeData, attr, whichStrand));
		if (cmd == nil)
		{
			ASSERT_FAIL("cmd is nil!");
			break;
		}

		// process the command
		status = CmdUtils::ProcessCommand(cmd);

		ASSERT_MSG(status == kSuccess, "SetTextBool16Attribute: cmd failed");

	} while (false);
	return status;
}

/* SetTextInt16Attribute
*/
ErrorCode SnpTextAttrHelper::SetTextInt16Attribute(const InDesign::TextRange& textRange, 
								const ClassID& attrClassID, 
								const int16 value,
								const ClassID& whichStrand /*= kCharAttrStrandBoss*/)
{
	// Assume failure.
	ErrorCode status = kFailure;
	do 
	{
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		const RangeData rangeData = textRange.GetRange();
		
		// create the text attribute boss
		InterfacePtr<ITextAttrInt16> attr(::CreateObject2<ITextAttrInt16>(attrClassID));
		if (attr == nil)
		{
			ASSERT_FAIL("attr is nil!");
			break;
		}
		// set the attribute value
		attr->Set(value);

		// create the text attribute command
		InterfacePtr<ICommand> cmd(
			Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, rangeData, attr, whichStrand));
		if (cmd == nil)
		{
			ASSERT_FAIL("cmd is nil!");
			break;
		}

		// process the command
		status = CmdUtils::ProcessCommand(cmd);

		ASSERT_MSG(status == kSuccess, "SetTextInt16Attribute: cmd failed");

	} while (false);
	return status;
}


// end file: SnpTextAttrHelper.cpp

