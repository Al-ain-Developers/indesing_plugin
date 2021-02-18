//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/watermarkui/WatermarkUIDialogObserver.cpp $
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

// Interface includes:
#include "IActiveContext.h"
#include "IAssociatedWidgetAttributes.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IDialogController.h"
#include "IFontGroup.h"
#include "IFontMgr.h"
#include "IPMFont.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IStringListControlData.h"
#include "IColorListControlData.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"
#include "IWatermarkData.h"
#include "IWidgetUtils.h"
#include "IWorkspace.h"

// General includes:
#include "CDialogObserver.h"
#include "Utils.h"

// Project includes:
#include "WatermarkUIID.h"
#include "IWatermarkDataFacade.h"


/** Implements IObserver based on the partial implementation CDialogObserver.

	
	@ingroup watermarkui
*/
class WatermarkUIDialogObserver : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		WatermarkUIDialogObserver(IPMUnknown* boss) : CDialogObserver(boss) {}

		/** Destructor. */
		virtual ~WatermarkUIDialogObserver() {}

		/**
			Called by the application to allow the observer to attach to the subjects
			to be observed, in this case the dialog's widgets.
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach();

		/**
			Called by the host when the observed widgets change.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void Update( const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy );


	private:
		virtual int32 GetDDListSelection( const WidgetID& widgetID, PMString* indexString = nil );
		virtual UID GetDDColorListSelection( const WidgetID& widgetID );
		virtual void UpdateFontFamilyWidget(IActiveContext* myContext, const WideString& fontFamily);
		virtual void UpdateFontStyleWidget(IActiveContext* myContext, const WideString& fontFamily, const WideString& fontStyle);
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(WatermarkUIDialogObserver, kWatermarkUIDialogObserverImpl)


/* AutoAttach
*/
void WatermarkUIDialogObserver::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();

	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	ASSERT(panelControlData);
	if(!panelControlData) {
		return;
	}

	// Attach to other widgets you want to handle dynamically here.
	AttachToWidget(kWatermarkUIShowWatermarkCheckBoxWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUIDoPrintCheckBoxWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUIDrawInBackCheckBoxWidgetID, ITriStateControlData::kDefaultIID, panelControlData);

	AttachToWidget(kWatermarkUIEditBoxWidgetID, ITextControlData::kDefaultIID, panelControlData);

	AttachToWidget(kWatermarkUIColorDropDownWidgetID, IID_ICOLORLISTCONTROLDATA, panelControlData);
	AttachToWidget(kWatermarkUIOpacityWidgetID, ITextControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUIRotationWidgetID, ITextControlData::kDefaultIID, panelControlData);

	AttachToWidget(kWatermarkUICharFontFamilyDropDownWidgetId, IStringListControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUICharFontStyleDropDownWidgetId, IStringListControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUIFontSizeWidgetID, ITextControlData::kDefaultIID, panelControlData);

	AttachToWidget(kWatermarkUIHPosDropDownWidgetID, IStringListControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUIHOffsetWidgetID, ITextControlData::kDefaultIID, panelControlData);

	AttachToWidget(kWatermarkUIVPosDropDownWidgetID, IStringListControlData::kDefaultIID, panelControlData);
	AttachToWidget(kWatermarkUIVOffsetWidgetID, ITextControlData::kDefaultIID, panelControlData);
}



/* AutoDetach
*/
void WatermarkUIDialogObserver::AutoDetach()
{
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	ASSERT(panelControlData);
	if(!panelControlData) {
		return;
	}
	// Detach from other widgets you handle dynamically here.
	DetachFromWidget(kWatermarkUIShowWatermarkCheckBoxWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUIDoPrintCheckBoxWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUIDrawInBackCheckBoxWidgetID, ITriStateControlData::kDefaultIID, panelControlData);

	DetachFromWidget(kWatermarkUIEditBoxWidgetID, ITextControlData::kDefaultIID, panelControlData);

	DetachFromWidget(kWatermarkUIColorDropDownWidgetID, IID_ICOLORLISTCONTROLDATA, panelControlData);
	DetachFromWidget(kWatermarkUIOpacityWidgetID, ITextControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUIRotationWidgetID, ITextControlData::kDefaultIID, panelControlData);

	DetachFromWidget(kWatermarkUICharFontFamilyDropDownWidgetId, IStringListControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUICharFontStyleDropDownWidgetId, IStringListControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUIFontSizeWidgetID, ITextControlData::kDefaultIID, panelControlData);

	DetachFromWidget(kWatermarkUIHPosDropDownWidgetID, IStringListControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUIHOffsetWidgetID, ITextControlData::kDefaultIID, panelControlData);

	DetachFromWidget(kWatermarkUIVPosDropDownWidgetID, IStringListControlData::kDefaultIID, panelControlData);
	DetachFromWidget(kWatermarkUIVOffsetWidgetID, ITextControlData::kDefaultIID, panelControlData);

	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();
}

/* Update
*/
void WatermarkUIDialogObserver::Update( const ClassID& theChange, ISubject* theSubject,
										const PMIID& protocol, void* changedBy )
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	do
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView == nil) {
			ASSERT_FAIL("IControlView is invalid");
			break;
		}

		WidgetID widgetID = controlView->GetWidgetID();

		// Check for Cancel button.
		if (widgetID == kCancelButton_WidgetID && theChange == kTrueStateMessage) {
			break;
		}
		// Check for OK button.
		if (widgetID == kOKButtonWidgetID && theChange == kTrueStateMessage) {
			break;
		}
		// Check for Preview button.
		if (widgetID == kPreviewButtonWidgetID) {
			break;
		}

		InterfacePtr<IDialogController> dlgController(this, UseDefaultIID());
		if (dlgController == nil) {
			ASSERT_FAIL("IDialogController is invalid");
			break;
		}
		InterfacePtr<IActiveContext> myContext(dlgController->QueryDialogContext());
		if (myContext == nil) {
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}
		const IWorkspace* activeWorkspace = myContext->GetContextWorkspace();
		if (activeWorkspace == nil) 
		{
			ASSERT_FAIL("Active workspace is invalid");
			break;
		}
		

		// get the current watermark pref
		IWatermarkData::WatermarkInfo wmkInfo;
		if (kFailure == Utils<IWatermarkDataFacade>()->GetWatermarkPref(::GetUIDRef(activeWorkspace), wmkInfo))
		{
			ASSERT_FAIL("Cannot obtain watermark preference from context workspace.");
			break;
		}


		// If first opening the dialog, make sure the font list is updated...
	    if(theChange == kFinishedSettingupEventFilteringMsg)
	    {
			// this message goes out when the dialog has opened.  Since there isn't a specific
			// message saying "Dialog Opened" I'm hijacking this one.

			UpdateFontFamilyWidget(myContext, wmkInfo.fFontFamily);
			UpdateFontStyleWidget(myContext, wmkInfo.fFontFamily, wmkInfo.fFontStyle);
			break;
		}


		ITriStateControlData::TriState state;

		// VISIBILITY
		state = dlgController->GetTriStateControlData(kWatermarkUIShowWatermarkCheckBoxWidgetID);
		wmkInfo.fVisibility = ((state == ITriStateControlData::kSelected) ? kTrue : kFalse);

		// DO PRINT
		state = dlgController->GetTriStateControlData(kWatermarkUIDoPrintCheckBoxWidgetID);
		wmkInfo.fDoPrint = ((state == ITriStateControlData::kSelected) ? kTrue : kFalse);

		// DRAW IN BACK
		state = dlgController->GetTriStateControlData(kWatermarkUIDrawInBackCheckBoxWidgetID);
		wmkInfo.fDrawInBack = ((state == ITriStateControlData::kSelected) ? kTrue : kFalse);

		// TEXT
		wmkInfo.fText = WideString(dlgController->GetTextControlData(kWatermarkUIEditBoxWidgetID));

		// FONT COLOR
		wmkInfo.fFontColor = GetDDColorListSelection(kWatermarkUIColorDropDownWidgetID);

		// OPACITY
		wmkInfo.fOpacity = ToInt32(dlgController->GetTextValue(kWatermarkUIOpacityWidgetID));

		// ROTATION
		wmkInfo.fRotation = ToInt32(dlgController->GetTextValue(kWatermarkUIRotationWidgetID));

		// FONT FAMILY
		PMString familyString;
		GetDDListSelection(kWatermarkUICharFontFamilyDropDownWidgetId, &familyString);
#ifdef MACINTOSH
		// macintosh adds space to end of font menu names, so remove the space before using it in prefs.
		familyString.StripWhiteSpace(PMString::kTrailingWhiteSpace);	
#endif
		wmkInfo.fFontFamily = WideString(familyString);


		// FONT STYLE
		if (widgetID == kWatermarkUICharFontFamilyDropDownWidgetId) {
			UpdateFontStyleWidget(myContext, wmkInfo.fFontFamily, WideString());
		}
		PMString styleString;
		GetDDListSelection(kWatermarkUICharFontStyleDropDownWidgetId, &styleString);
		wmkInfo.fFontStyle = WideString(styleString);

		// FONT SIZE
		wmkInfo.fFontPointSize = ToInt32(dlgController->GetTextValue(kWatermarkUIFontSizeWidgetID));

		// HORIZONTAL POSITION
		wmkInfo.fHorzPosition = (IWatermarkData::WatermarkInfo::WatermarkHPos)GetDDListSelection(kWatermarkUIHPosDropDownWidgetID);

		// HORIZONTAL OFFSET
		wmkInfo.fHorzOffset = dlgController->GetTextValue(kWatermarkUIHOffsetWidgetID);

		// VERTICAL POSITION
		wmkInfo.fVertPosition = (IWatermarkData::WatermarkInfo::WatermarkVPos)GetDDListSelection(kWatermarkUIVPosDropDownWidgetID);

		// VERTICAL OFFSET
		wmkInfo.fVertOffset = dlgController->GetTextValue(kWatermarkUIVOffsetWidgetID);


		// use the facade to send a command to the active workspace to update its info
		if (kFailure == Utils<IWatermarkDataFacade>()->SetWatermarkPref(::GetUIDRef(activeWorkspace), wmkInfo))
		{
			ASSERT_FAIL("Cannot set watermark preference for active workspace.");
			break;
		}

	} while (kFalse);
}



/* UpdateFontFamilyWidget
*/
void WatermarkUIDialogObserver::UpdateFontFamilyWidget(IActiveContext* myContext, const WideString& fontFamily) 
{
	do
	{
	    InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}
		IControlView* panelControlView = panelData->FindWidget(kWatermarkUICharFontFamilyDropDownWidgetId);
		if (panelControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}
		InterfacePtr<IDropDownListController> ddListController(panelControlView, UseDefaultIID());
		if (ddListController == nil)
		{
			ASSERT_FAIL("IDropDownListController is invalid");
			break;
		}
		InterfacePtr<IStringListControlData> listData(panelControlView, UseDefaultIID());
		if (listData != nil)
		{
#ifdef MACINTOSH
			// add space to end of family name to match menu format (mac only)
			int32 theIndex = listData->GetIndex(fontFamily + " ");
#else
			int32 theIndex = listData->GetIndex(fontFamily);
#endif

			if (theIndex < 0) {
				ASSERT_FAIL("Specified font family does not exist.");
				break;
			}

			theIndex = (theIndex < 0) ? 0 : theIndex;
			ddListController->Select(theIndex, kTrue, kFalse);

			InterfacePtr<ITextControlData> textData(panelControlView, UseDefaultIID());
			if (textData) {
				textData->SetString(listData->GetString(theIndex));
			}
		}
		

	} while(false);
}

/* UpdateFontStyleWidget
*/
void WatermarkUIDialogObserver::UpdateFontStyleWidget(IActiveContext* myContext, const WideString& fontFamily, const WideString& fontStyle)
{
	do
	{
	    InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}
		IControlView* panelControlView = panelData->FindWidget(kWatermarkUICharFontStyleDropDownWidgetId);
		if (panelControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}
		InterfacePtr<IDropDownListController> ddListController(panelControlView, UseDefaultIID());
		if (ddListController == nil)
		{
			ASSERT_FAIL("IDropDownListController is invalid");
			break;
		}

		// clear any existing name in the text edit box
		InterfacePtr<ITextControlData> textData(panelControlView, UseDefaultIID());
		if (textData) {
			textData->SetString("");
		}

		InterfacePtr<IStringListControlData> listData(panelControlView, UseDefaultIID());
		if (listData)
		{
			listData->Clear();

			InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
			if (fontMgr == nil) {
				ASSERT_FAIL("IControlView is invalid");
				break;
			}

			// get the font group based on the family name
			IFontGroup* fontGroup = fontMgr->QueryFontGroup(fontFamily);			
			if (!fontGroup) {
				// if group was not found, try using the display name
				PMString noStyle;
				InterfacePtr<IPMFont> font(fontMgr->QueryFontFromDisplayName(fontFamily, noStyle));
				if (font) {
					PMString groupName;
					font->AppendFamilyName(groupName);
					fontGroup = fontMgr->QueryFontGroup(groupName);
				}
			}
			if (fontGroup) {
				// for each font in the group, add its style name to our list of styles
				for (int32 faceIndex = 0; faceIndex < fontGroup->GetNumFonts(); faceIndex++) {
					InterfacePtr<IPMFont> font(fontMgr->QueryFont(fontGroup, faceIndex));
					if (font) {
						PMString styleName;
						font->AppendStyleName(styleName);
						styleName.SetTranslatable(kFalse);
						listData->AddString(styleName);
					}
				}
			}

			if (listData->Length() <= 0) {
				ASSERT_FAIL("Style IStringListControlData is empty.  No styles available for specified font family.");
				break;
			}

			int32 theIndex = 0;
			if (!fontStyle.empty()) {
				theIndex = listData->GetIndex(fontStyle);
				theIndex = (theIndex < 0) ? 0 : theIndex;
			}

			ddListController->Select(theIndex, kTrue, kFalse);

			if (textData) {
				textData->SetString(listData->GetString(theIndex));
			}

			fontGroup->Release();
		}

	} while(false);
}


/* GetDDListSelection
*/
int32 WatermarkUIDialogObserver::GetDDListSelection( const WidgetID& widgetID, PMString* itemString )
{
	int32 theIndex = -1;
	do 
	{
		InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}
		IControlView* ctrlView = panelData->FindWidget(widgetID);
		if (ctrlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}		
		InterfacePtr<IDropDownListController> ddListController(ctrlView, UseDefaultIID());
		if (ddListController == nil)
		{
			ASSERT_FAIL("IDropDownListController is invalid");
			break;
		}

		theIndex = ddListController->GetSelected();

		if (itemString != nil)
		{
			InterfacePtr<IStringListControlData> listData(ctrlView, UseDefaultIID());
			if (listData != nil)
			{
				itemString->SetString(listData->GetString(theIndex));
			}
		}

	} while (kFalse);

	return theIndex;
}


/* GetDDColorListSelection
*/
UID WatermarkUIDialogObserver::GetDDColorListSelection( const WidgetID& widgetID )
{
	UID theColorUID = kInvalidUID;
	do 
	{
		InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}
		IControlView* ctrlView = panelData->FindWidget(widgetID);
		if (ctrlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}		
		InterfacePtr<IColorListControlData> colorListControlData(ctrlView, UseDefaultIID());
		if (colorListControlData == nil)
		{
			ASSERT_FAIL("IColorListControlData is invalid");
			break;
		}

		theColorUID = colorListControlData->GetSelection();

	} while (kFalse);

	return theColorUID;
}

