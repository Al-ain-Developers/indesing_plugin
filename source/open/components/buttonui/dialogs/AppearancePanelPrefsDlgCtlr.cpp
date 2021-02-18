//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/AppearancePanelPrefsDlgCtlr.cpp $
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
//  This source file contains all the dialog routines to initialize,
//  process, and close the dialog which set the Appearance Panel (Forms Panel)
//  Prefs. In particular, it sets the thumbnail size of the appearance cells.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "AppUIID.h"
#include "IIntData.h"
#include "ITriStateControlData.h"
#include "IPanelControlData.h"
#include "IBoolData.h"

#include "CDialogController.h"

#include "FormFieldUIID.h"
#include "FormFieldUIDefs.h"

//------------------------------------------------------------------------

class AppearancePanelPrefsDialogController : public CDialogController
{
	public:
		AppearancePanelPrefsDialogController(IPMUnknown* boss);
		void InitializeDialogFields( IActiveContext* dlgContext);
		void ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);
		void UserCancelled();

	private:
};

//------------------------------------------------------------------------

CREATE_PMINTERFACE(AppearancePanelPrefsDialogController, kAppearancePanelPrefsDialogControllerImpl)

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
AppearancePanelPrefsDialogController::AppearancePanelPrefsDialogController(IPMUnknown* boss)
: CDialogController(boss)
{
}

//------------------------------------------------------------------------

static void SetRadioButton(	IPanelControlData* inPanelData, WidgetID inWidget, bool inSelect )
{
	InterfacePtr<ITriStateControlData> iTriStateData(inPanelData->FindWidget(inWidget), IID_ITRISTATECONTROLDATA);
	
	if (inSelect)
		iTriStateData->Select();
	else
		iTriStateData->Deselect();
}
//------------------------------------------------------------------------

static bool GetRadioButton(	IPanelControlData* inPanelData, WidgetID inWidget )
{
	InterfacePtr<ITriStateControlData> iTriStateData(inPanelData->FindWidget(inWidget), IID_ITRISTATECONTROLDATA);
	
	return iTriStateData->IsSelected();
}

//------------------------------------------------------------------------

void AppearancePanelPrefsDialogController::InitializeDialogFields( IActiveContext* dlgContext)
{
	//Handles text-related fields...
	InterfacePtr<IPanelControlData>	panelData(this, IID_IPANELCONTROLDATA);
	InterfacePtr<IIntData> iThumbSizeIndex( this, IID_IINTDATA );

	int32 index = iThumbSizeIndex->Get();
	
	SetRadioButton( panelData, kSmallSizeRadioButtonWID, index == kSmallSize);
	SetRadioButton( panelData, kMediumSizeRadioButtonWID, index == kMediumSize);
	SetRadioButton( panelData, kLargeSizeRadioButtonWID, index == kLargeSize);
	SetRadioButton( panelData, kExtraLargeSizeRadioButtonWID, index == kExtraLargeSize);
}

//----------------------------------------------------------------------------------------
// This is so caller knows whether to apply properties or not...

void AppearancePanelPrefsDialogController::UserCancelled()
{
	InterfacePtr<IBoolData> iDialogCancelled( this, IID_IDIALOGWASCANCELLED );
	iDialogCancelled->Set(kTrue);
}

//------------------------------------------------------------------------

void AppearancePanelPrefsDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId)
{
	//If requested, just get the attributes and return, and let the caller deal with it...

	InterfacePtr<IBoolData> iDialogCancelled( this, IID_IDIALOGWASCANCELLED );
	iDialogCancelled->Set(kFalse);

	InterfacePtr<IPanelControlData>	panelData(this, IID_IPANELCONTROLDATA);
	InterfacePtr<IIntData> iThumbSizeIndex( this, IID_IINTDATA );

	int32 index = 0;
	
	if (GetRadioButton( panelData, kSmallSizeRadioButtonWID ))
		index = kSmallSize;

	else if (GetRadioButton( panelData, kMediumSizeRadioButtonWID ))
		index = kMediumSize;

	else if (GetRadioButton( panelData, kLargeSizeRadioButtonWID ))
		index = kLargeSize;

	else if (GetRadioButton( panelData, kExtraLargeSizeRadioButtonWID ))
		index = kExtraLargeSize;
		
	iThumbSizeIndex->Set(index);
}

// End, AppearancePanelPrefsDialogController.cpp.
