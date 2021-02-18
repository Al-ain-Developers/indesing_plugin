//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/uifactories/GenericFieldUIFactory.cpp $
//  
//  Owner: Tim Wright
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

#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IGraphicAttributeSuite.h"
#include "IGraphicStyleAttrBossList.h"

// Project:
#include "FormFieldUIFactory.h"
#include "AttributesUtils.h"
#include "UserInterfaceUtils.h"

using namespace AttributesUtils;
using namespace UserInterfaceUtils;

//------------------------------------------------------------------------

class GenericFieldUIFactory : public FormFieldUIFactory
{
public:
	GenericFieldUIFactory(IPMUnknown * boss) : FormFieldUIFactory(boss){}

	ActionID GetToolActionID() const { return  kPushButtonToolActionID;}

	void InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGraphicAttrSuite );
};

CREATE_PMINTERFACE(GenericFieldUIFactory, kGenericFieldUIFactoryImpl)

//------------------------------------------------------------------------

void GenericFieldUIFactory::InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGfxAttrSuite )
{
	//SPAM twright 01/24/2002 This needs to go in the base class, and the subtypes should call into the base class.
	//GenericFieldUIFactory is always used to set up the common controls, but it is meant to be used only for mixed selections
	//(Need to fix that up in FormFieldPropertiesDialogController::InitializeFields() )
	//The idea is that  QuerySelectionUIFactory will eventually return GenericFieldUIFactory for mixed selections.  It returns
	//nil now.  I didn't want to make too many changes at once, though

	const bool kEnable = true;

	InterfacePtr<IGraphicStyleAttributeBossList> defaultAttrs( QueryDefaultAttributes() );

	UpdateTextWidget( inPanelData, inGfxAttrSuite, kEnable, kFormNameAttrBoss, 			kNameEditWID, defaultAttrs );
	UpdateTextWidget( inPanelData, inGfxAttrSuite, kEnable, kFormDescriptionAttrBoss, 	kDescriptionEditWID, defaultAttrs );
	
	// Get the Screen and Print Visibility attributes and translate them to the PDF Visibility popup
	bool16 visibleOnScreen = kTrue;
	bool16 visibleInPrint = kTrue;
	bool mixedState = false;
	
	if ( inGfxAttrSuite->GetAttributeCount(kFormScreenVisibleAttrBoss) >= 1) {
		if (! HasUniqueValue(inGfxAttrSuite, kFormScreenVisibleAttrBoss, &visibleOnScreen))
			mixedState = true;
	}
	else {
		if ( defaultAttrs )
			visibleOnScreen = GetBoolValue(defaultAttrs, kFormScreenVisibleAttrBoss);
	}
	
	if ( inGfxAttrSuite->GetAttributeCount(kFormPrintVisibleAttrBoss) >= 1) {
		if (! HasUniqueValue(inGfxAttrSuite, kFormPrintVisibleAttrBoss, &visibleInPrint))
			mixedState = true;
	}
	else {
		if ( defaultAttrs )
			visibleInPrint = GetBoolValue(defaultAttrs, kFormPrintVisibleAttrBoss);
	}
	
	int16 pdfVisibilitySelection = 0;
	if ( visibleOnScreen && visibleInPrint )
		pdfVisibilitySelection = 0;
	else if ( !visibleOnScreen && !visibleInPrint )
		pdfVisibilitySelection = 1;
	else if ( visibleOnScreen && !visibleInPrint )
		pdfVisibilitySelection = 2;
	else if ( !visibleOnScreen && visibleInPrint )
		pdfVisibilitySelection = 3;
	
	IControlView* pdfVisibilityView = inPanelData->FindWidget(kPDFVisiblityPopupWID);
	InterfacePtr<IDropDownListController> pdfVisbilityList(pdfVisibilityView, IID_IDROPDOWNLISTCONTROLLER);
	
	if ( mixedState )
		pdfVisbilityList->Deselect();
	else
		pdfVisbilityList->Select(pdfVisibilitySelection);
}

