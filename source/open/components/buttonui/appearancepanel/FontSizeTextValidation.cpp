//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/FontSizeTextValidation.cpp $
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
//  
//  Similar to TextEBTextValidation, with IsEntryLegal() redefined
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "CTextDataValidation.h"

#include "FormFieldUIID.h"
#include "IDropDownListController.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "IStringListControlData.h"

//========================================================================================
// CLASS FontSizeTextValidation
//========================================================================================

class FontSizeTextValidation : public CTextDataValidation
{
public:
	FontSizeTextValidation(IPMUnknown *boss);
	~FontSizeTextValidation();

	virtual bool16 IsEntryLegal();
	virtual PMString GetErrorString();
};

CREATE_PERSIST_PMINTERFACE(FontSizeTextValidation, kFontSizeTextValidationImpl) 

//======================================================================================== 
// METHODS FontSizeTextValidation 
//======================================================================================== 

FontSizeTextValidation::FontSizeTextValidation(IPMUnknown *boss) :
CTextDataValidation(boss)
{
}

FontSizeTextValidation::~FontSizeTextValidation()
{
}

bool16 FontSizeTextValidation::IsEntryLegal()
{
	InterfacePtr<ITextValue> textValue(this, UseDefaultIID());

	bool16 err = kFalse;
	PMReal TextSize(textValue->GetTextAsValue(&err));

	if(err || (TextSize > 300 || TextSize < 0))
		return kFalse;
	
	return kTrue;
}

PMString FontSizeTextValidation::GetErrorString()
{
	PMString errorString;
	errorString.SetCString("$$$/Error/YouNeedToSpecifyAValidFontSize");
	errorString.Translate();
	return errorString;
}

