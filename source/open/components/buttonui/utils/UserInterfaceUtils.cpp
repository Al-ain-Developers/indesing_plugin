//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/utils/UserInterfaceUtils.cpp $
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
//  
//  This file contains common defines and macros for often-used functions.
//  
//  Adapted From SDKUtilities.cpp in the SDK
//  
//========================================================================================

#include "VCPlugInHeaders.h"


// InDesign interfaces:
#include "IPanelControlData.h"
#include "ITriStateControlData.h"
#include "ITextControlData.h"
#include "IDropDownListController.h"
#include "ITextValue.h"
#include "IGraphicAttributeSuite.h"
#include "IStringListControlData.h"
#include "IDialogController.h"
#include "ISpread.h"
#include "IPanorama.h"
#include "IGeometry.h"
#include "ILayoutControlData.h"
#include "IMasterSpreadList.h"
#include "IDocument.h"
#include "ISpreadList.h"

#include "IApplication.h"
#include "IDialogMgr.h"
#include "ISession.h"

#include "CAlert.h"			// ModalAlert
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "ErrorUtils.h"
#include "TransformUtils.h"
#include "ILayoutUIUtils.h"
#include "RsrcSpec.h"

//Blackduck
#include "UserInterfaceUtils.h"
#include "AttributesUtils.h"
#include "IStringAttr.h"
#include "FormFieldID.h"

using namespace AttributesUtils;

//----------------InvokePluginAboutBox------------------------
// Brings up CAlert with kAboutBoxString and OK button.
//------------------------------------------------------------
void UserInterfaceUtils::InvokePlugInAboutBox(const PMString alertStringID)
{
	CAlert::ModalAlert
	(
	   alertStringID,							// Alert string
	   kOKString, /*CAlert::kDefaultAction,*/	// OK button
	   kNullString, /*CAlert::kDefaultAction,*/	// No second button
	   kNullString, /*CAlert::kDefaultAction,*/	// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

//------------------------------------------------------------

void UserInterfaceUtils::PresentModalDialog( PluginID inPluginID, RsrcID inDialogResourceID )
{
	IDialog* dialog = GetModalDialog(inPluginID, inDialogResourceID);
	if (dialog != nil)
	{
		// Open causes the dialog to be displayed and then returns immediately
		//	so WaitForDialog() is used.
		dialog->Open();
		dialog->WaitForDialog();
	}
}

//------------------------------------------------------------

IDialog* UserInterfaceUtils::GetModalDialog( PluginID inPluginID, RsrcID inDialogResourceID, bool inVisible )
{
	// Get the applicaton interface and the DialogMgr:	
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, ::UseDefaultIID());
	
	// We need to load the plug-ins resource:
	RsrcSpec dialogSpec
	(
		LocaleSetting::GetLocale(),					// Locale index from PMLocaleIDs.h. 
		inPluginID,		// Our Plug-in ID from SimpleDialog.h. 
		kViewRsrcType,				// This is the kViewRsrcType.
		inDialogResourceID,			// Resource ID for our dialog.
		inVisible ? kTrue : kFalse	// Initially visible.
	);

	// CreateNewDialog takes the dialogSpec created above, and also
	// the type of dialog being created (kMovableModal).
	IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
	
	if (dialog == nil)
		ASSERT_FAIL("UserInterfaceUtils::DoAction: Could not create new dialog");

	return dialog;
}

//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdateStaticWidget(	IPanelControlData* inPanelData,
											bool inEnable,
											WidgetID inStaticWidget )
{
	IControlView* iStaticView = inPanelData->FindWidget(inStaticWidget);
	ASSERT_MSG(iStaticView, "Widget Not Found");
	if ( iStaticView == 0 )
		return;
	iStaticView->Enable(inEnable);
}


//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdatePopupWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inPopupWidget,
							IGraphicStyleAttributeBossList* inDefaults )
{
	IControlView* iListView = inPanelData->FindWidget(inPopupWidget);
	ASSERT_MSG(iListView, "Widget Not Found");
	if (iListView == 0)
		return;

	InterfacePtr<IDropDownListController> iListData(iListView, ::UseDefaultIID());

	if (inEnable)
	{
		if (iGfxAttrSuite->GetAttributeCount(inAttrBoss) >= 1)
		{
			int32	commonValue;
			
			if (HasUniqueValue(iGfxAttrSuite, inAttrBoss, &commonValue))
			{
				iListData->Select(commonValue);
			}
			else
				iListData->Deselect();
		}
		else
		{
			iListData->Select( inDefaults ? GetInt32Value(inDefaults, inAttrBoss) : 0 );
		}
	}
	else
		iListData->Deselect();

	iListView->Enable(inEnable);
}

//----------------------------------------------------------------------------------------
//Used when popup entries are variable and therefore we can't use enum to
//store the attribute.  inAttrBoss should be a string attribute, and the popup
//menu should have a "custom" entry.

void UserInterfaceUtils::UpdateStringListWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inPopupWidget,
							const PMString& inDefault )
{
	IControlView* iListView = inPanelData->FindWidget(inPopupWidget);
	ASSERT_MSG(iListView, "Widget Not Found");
	if (iListView == 0)
		return;

	InterfacePtr<IDropDownListController> iListData(iListView, ::UseDefaultIID());
	InterfacePtr<IStringListControlData> iStringList(iListView, ::UseDefaultIID());

	if (inEnable)
	{
		PMString customStyleName("$$$/AppearanceStyle/Custom");
		customStyleName.Translate();
		customStyleName.SetTranslatable(kFalse);
		
		if (iGfxAttrSuite->GetAttributeCount(inAttrBoss) >= 1)
		{
			PMString	commonValue;
			
			if (HasUniqueValue(iGfxAttrSuite, inAttrBoss, &commonValue))
			{
				int32 popupIndex =	iStringList->GetIndex(commonValue);
				
				if (popupIndex < 0)
					popupIndex = iStringList->GetIndex(customStyleName);
				if (popupIndex >= 0)
					iListData->Select(popupIndex);
				else
					iListData->Deselect();
			}
			else
				iListData->Deselect();
		}
		else
		{
			PMString defaultStyleName(inDefault);
			defaultStyleName.Translate();
			
			int32 popupIndex =	iStringList->GetIndex(defaultStyleName);
			if (popupIndex < 0)
				popupIndex = iStringList->GetIndex(customStyleName);
			if (popupIndex >= 0)
				iListData->Select(popupIndex);
			else
				iListData->Deselect();
		}
	}
	else
		iListData->Deselect();

	iListView->Enable(inEnable);
}

//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdateCheckWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inWidget,
							IGraphicStyleAttributeBossList* inDefaults )
{
	IControlView* iTriStateView = inPanelData->FindWidget(inWidget);
	ASSERT_MSG(iTriStateView, "Widget Not Found");
	if (iTriStateView == 0)
		return;

	InterfacePtr<ITriStateControlData> iTriStateData(iTriStateView, ::UseDefaultIID());

	if (inEnable)
	{
		if (iGfxAttrSuite->GetAttributeCount(inAttrBoss) >= 1)
		{
			bool16	commonValue;
			
			if (HasUniqueValue(iGfxAttrSuite, inAttrBoss, &commonValue))
			{
				if (commonValue)
					iTriStateData->Select();
				else
					iTriStateData->Deselect();
			}
			else
				iTriStateData->SetUnknown();
		}
		else
		{
			if ( inDefaults && GetBoolValue(inDefaults, inAttrBoss) )
				iTriStateData->Select();
			else
				iTriStateData->Deselect();
		}
	}
	else
		iTriStateData->Deselect();

	iTriStateView->Enable(inEnable);
}

//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdateTextWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inEditWidget,
							IGraphicStyleAttributeBossList* inDefaults)
{
	IControlView* iEditView = inPanelData->FindWidget(inEditWidget);

	ASSERT_MSG(iEditView, "Widget Not Found");
	if ( iEditView ==0 )
		return;


	InterfacePtr<ITextControlData> iEdit(iEditView, ::UseDefaultIID());
	InterfacePtr<ITextValue> iTextValue(iEditView, ::UseDefaultIID());
	
	PMString strValue = "";
	ITextValue::TextControlState controlState = ITextValue::kNormal;
	
	if (inEnable)
	{
		if (iGfxAttrSuite->GetAttributeCount(inAttrBoss) >= 1)
		{
			PMString	commonValue;
			if (HasUniqueValue(iGfxAttrSuite, inAttrBoss, &commonValue))
			{
				strValue = commonValue;
			}
			else
			{
				controlState = ITextValue::kUnknown;
			}
		}
		else
		{
			strValue =  inDefaults ? GetStringValue(inDefaults, inAttrBoss) : "";
		}
	}

	//Need to set iLastGood, otherwise we don't always get change notifications...
	
	iEdit->SetString(strValue);
	iTextValue->SetControlState(controlState);
	iEditView->Enable(inEnable);
}

//----------------------------------------------------------------------------------------

//twright 04/18/2001
//???? The MSVC optimizer screws up this routine
//for some unknown reason...  Turn off optimization around
//it to avoid a program-terminating exception.

#if MSVC
#pragma optimize("",off)
#endif

void UserInterfaceUtils::UpdateRealWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inEditWidget,
							IGraphicStyleAttributeBossList* inDefaults)
{
	IControlView* iEditView = inPanelData->FindWidget(inEditWidget);

	ASSERT_MSG(iEditView, "Widget Not Found");
	if (iEditView ==0)
		return;

	InterfacePtr<ITextValue> iTextValue(iEditView, ::UseDefaultIID());
	InterfacePtr<ITextControlData> iTextControlData(iEditView, ::UseDefaultIID());
	
	bool enable = inEnable;
	ITextValue::TextControlState textControlState = ITextValue::kUnknown;
	PMReal value =  inDefaults ? GetRealValue(inDefaults, inAttrBoss) : 0.0;
	
	if (enable)
	{
		if (iGfxAttrSuite->GetAttributeCount(inAttrBoss) >= 1)
		{
			PMReal	commonValue;
			if (HasUniqueValue(iGfxAttrSuite, inAttrBoss, &commonValue))
			{
				value = commonValue;
				textControlState = ITextValue::kNormal;
			}
		}
	}
	
	iTextValue->SetControlState(textControlState);
	if (textControlState == ITextValue::kNormal)
		iTextValue->SetTextFromValue(value);
	
	iEditView->Enable(enable);
}

//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdateIntegerWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inEditWidget,
							IGraphicStyleAttributeBossList* inDefaults)
{
	IControlView* iEditView = inPanelData->FindWidget(inEditWidget);

	ASSERT_MSG(iEditView, "Widget Not Found");
	if (iEditView ==0)
		return;

	InterfacePtr<ITextValue> iTextValue(iEditView, ::UseDefaultIID());
	InterfacePtr<ITextControlData> iTextControlData(iEditView, ::UseDefaultIID());
	
	bool enable = inEnable;
	ITextValue::TextControlState textControlState = ITextValue::kUnknown;
	int32 value = inDefaults ? GetInt32Value(inDefaults, inAttrBoss) : 0;
	
	if (enable)
	{
		if (iGfxAttrSuite->GetAttributeCount(inAttrBoss) >= 1)
		{
			int32	commonValue;
			if (HasUniqueValue(iGfxAttrSuite, inAttrBoss, &commonValue))
			{
				value = commonValue;
				textControlState = ITextValue::kNormal;
			}
		}
	}
	
	iTextValue->SetControlState(textControlState);
	if (textControlState == ITextValue::kNormal)
		iTextValue->SetTextFromValue(value);

	iEditView->Enable(enable);
}

#if MSVC
#pragma optimize("",on)
#endif

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdatePopupAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl )
{
	InterfacePtr<IDropDownListController> iList(inControl, ::UseDefaultIID());

	if (iList->GetSelected() >= 0)
		SetInt32Value(inCommandString, inGfxAttrSuite, inAttrBoss, iList->GetSelected() );
}

//----------------------------------------------------------------------------------------

void UserInterfaceUtils::UpdateCheckAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl )
{
	InterfacePtr<ITriStateControlData> iTriStateData(inControl, ::UseDefaultIID());
	ITriStateControlData::TriState state = iTriStateData->GetState();

	if (state != ITriStateControlData::kUnknown)
		SetBoolValue(inCommandString, inGfxAttrSuite, inAttrBoss, state == ITriStateControlData::kSelected );
}

//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::UpdateTextAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl )
{
	InterfacePtr<ITextControlData> iEdit(inControl, ::UseDefaultIID());
	InterfacePtr<ITextValue> iTextValue(inControl, ::UseDefaultIID());

	if (iTextValue->GetControlState() != ITextValue::kUnknown)
		SetStringValue(inCommandString, inGfxAttrSuite, inAttrBoss, iEdit->GetString() );
}

//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::UpdateStringListAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl )
{
	InterfacePtr<IDropDownListController> iDropDown(inControl, ::UseDefaultIID());
	InterfacePtr<IStringListControlData> iStringList(inControl, ::UseDefaultIID());

	if (iDropDown->GetSelected() >= 0)
		SetStringValue(inCommandString, inGfxAttrSuite, inAttrBoss, iStringList->GetString(iDropDown->GetSelected()) );
}

//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::UpdateRealAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl )
{
	InterfacePtr<ITextValue> iTextValue(inControl, ::UseDefaultIID());

	if (iTextValue->GetControlState() != ITextValue::kUnknown)
		SetRealValue(inCommandString, inGfxAttrSuite, inAttrBoss, iTextValue->GetTextAsValue());
}

//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::UpdateIntegerAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl )
{
	InterfacePtr<ITextValue> iTextValue(inControl, ::UseDefaultIID());

	if (iTextValue->GetControlState() != ITextValue::kUnknown)
		SetInt32Value(inCommandString, inGfxAttrSuite, inAttrBoss, ToInt32(iTextValue->GetTextAsValue()));
}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::AddString(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* inTextControlView )
{
	if (inTextControlView)
	{
		InterfacePtr<ITextValue> iTextValue(inTextControlView, ::UseDefaultIID());
		InterfacePtr<ITextControlData> iTextData(inTextControlView, ::UseDefaultIID());
		
		PMString theString(iTextData->GetString());
		theString.Translate();

		if (iTextValue->GetControlState() != ITextValue::kUnknown)
			AddStringValue( inAttrs,  inAttrBoss, theString );

	}
}

//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::AddBool(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* inTriStateView )
{
	if (inTriStateView)
	{
		InterfacePtr<ITriStateControlData> iTriStateData(inTriStateView, ::UseDefaultIID());

		ITriStateControlData::TriState state = iTriStateData->GetState();
		if (state != ITriStateControlData::kUnknown)
			AddBoolValue( inAttrs,  inAttrBoss, state == ITriStateControlData::kSelected  );
	}
}

//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::AddInt32(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* iEditView )
{
	if (iEditView)
	{
		InterfacePtr<ITextValue> iTextValue(iEditView, ::UseDefaultIID());
		
		if (iTextValue->GetControlState() != ITextValue::kUnknown)
			AddInt32Value( inAttrs,  inAttrBoss, ToInt32(iTextValue->GetTextAsValue())  );
	}
}
//----------------------------------------------------------------------------------------
								
void UserInterfaceUtils::AddEnum(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* iPopupView )
{
	if (iPopupView)
	{
		InterfacePtr<IDropDownListController> iList(iPopupView, ::UseDefaultIID());

		if (iList->GetSelected() >= 0)
			AddInt32Value(inAttrs, inAttrBoss, iList->GetSelected() );
	}
}

//----------------------------------------------------------------------------------------
								
IControlView* UserInterfaceUtils::GetControl(IDialogController * inDialogController, WidgetID inWidget )
{
	InterfacePtr<IPanelControlData>	panelData(inDialogController, ::UseDefaultIID());
	return panelData ? panelData->FindWidget(inWidget) : 0;
}


// ----------------------------------------------------------------------------------------








