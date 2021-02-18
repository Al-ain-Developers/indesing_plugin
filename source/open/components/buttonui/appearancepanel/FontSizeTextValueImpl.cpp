//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/FontSizeTextValueImpl.cpp $
//  
//  Owner: Reena Agrawal
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================
#include "VCPlugInHeaders.h"

// ----- Interface Includes -----
#include "IEditBoxAttributes.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----
#include "widgetid.h"
#include "PMString.h"
#include "FormFieldUIID.h"
#include "HelperInterface.h"

class FontSizeTextValue : public ITextValue 
{
public:
	FontSizeTextValue(IPMUnknown *boss);
	~FontSizeTextValue();

	virtual PMReal GetTextAsValue(bool16 *errorOut = nil,bool16 *blankEntry = nil) ;
	virtual void   SetTextFromValue(const PMReal& valueIn, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);

	virtual PMReal ParseString(const PMString& textIn, bool16 *errorOut) const;
	virtual void ReformatText(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual PMString GetFormattedString(const PMReal& valueIn) const;

	// dummy implementations..
	virtual void SetControlState(TextControlState newState, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) {}
	virtual TextControlState GetControlState() const {return ITextValue::kNormal;}
	virtual TextControlChange GetLastControlChange(PMReal* value) const {return ITextValue::kAbsolute ;}

	DECLARE_HELPER_METHODS();
};

CREATE_PMINTERFACE(FontSizeTextValue, kFontSizeTextValueImpl)

//========================================================================================
// METHODS FontSizeTextValue
//========================================================================================

DEFINE_HELPER_METHODS(FontSizeTextValue)

FontSizeTextValue::FontSizeTextValue(IPMUnknown *boss) :
HELPER_METHODS_INIT(boss)
{
}

FontSizeTextValue::~FontSizeTextValue()
{
}

PMReal FontSizeTextValue::ParseString(const PMString& textIn, bool16 *errorOut) const
{
	PMString AutoStr("$$$/Panel/AutoSize", PMString::kTranslateDuringCall);

	if(textIn == AutoStr)
		return 0;

	PMString::ConversionError convertError = PMString::kNoError;
	PMReal realNum(textIn.GetAsDouble(&convertError));
	if(convertError != PMString::kNoError && errorOut)
		*errorOut = kTrue;                                
	return realNum;
}

PMString FontSizeTextValue::GetFormattedString(const PMReal& valueToFormat) const
{
	PMString numString;
	if(valueToFormat != 0.0)
		numString.AsNumber(valueToFormat,3,kTrue,kTrue);
	else
		numString = PMString("$$$/Panel/AutoSize", PMString::kTranslateDuringCall);

	return numString;
}

PMReal FontSizeTextValue::GetTextAsValue(bool16 *errorOut,bool16 *blankEntry)
{
	// BP 05/02/98: errorOut must be initialized.
	if( errorOut )
		*errorOut = kFalse;

	InterfacePtr<ITextControlData> textData(this,IID_ITEXTCONTROLDATA);
	PMString currentText = textData->GetString();
	currentText.SetTranslatable(kFalse);

	bool16 localParseError = kFalse;
	PMReal newValue = ParseString(currentText,&localParseError);

	if(errorOut)
		*errorOut = localParseError;

	if(blankEntry)
	{
		if(currentText.empty())
			*blankEntry = kTrue;
		else
			*blankEntry = kFalse;
	}

	if(localParseError == kFalse)
		return newValue;
	else
		return 0.0; //return 0 for error, in which case it will map to Auto...
}

void FontSizeTextValue::SetTextFromValue(const PMReal& valueToFormat, bool16 invalidate, bool16 notifyOfChange)
{
	PMString newString = GetFormattedString(valueToFormat);
	newString.SetTranslatable(kFalse);

	InterfacePtr<IEditBoxAttributes> ebAttr(this,IID_IEDITBOXATTRIBUTES);
	if (ebAttr)
	{
		CharCounter maxLimit = ebAttr->GetMaxNumChars();
		CharCounter len = newString.CharCount();
		ASSERT(maxLimit >= 0);
		if(maxLimit > 0 && len > maxLimit)
		{
			newString.Truncate(len - maxLimit);
			len = newString.CharCount();
			if (newString.GetWChar(len - 1) == kTextChar_Period)
			{
				newString.Remove(len - 1);
			}
		}
	}

	Utils<IWidgetUtils>()->FormatUserDecimal(&newString);

	InterfacePtr<ITextControlData> textData(this,IID_ITEXTCONTROLDATA);

	textData->SetString(newString, invalidate, notifyOfChange);
}

void  FontSizeTextValue::ReformatText(bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<ITextControlData> textData(this,IID_ITEXTCONTROLDATA);
	PMString currentText = textData->GetString();
	currentText.SetTranslatable(kFalse);

	bool16 errorOut = kFalse;
	bool16 isBlank = kFalse;
	PMReal value = GetTextAsValue(&errorOut,&isBlank);
	ASSERT_MSG(!errorOut || isBlank,"FontSizeTextValue::ReformatText got unexpected conversion error");
	SetControlState(kNormal,kFalse,kFalse);
	SetTextFromValue(value,invalidate,notifyOfChange);
}
