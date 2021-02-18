//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/watermarkui/WatermarkUIDialogController.cpp $
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
#include "IColorListControlData.h"
#include "IDropDownListController.h"
#include "IObserver.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISwatchList.h"
#include "ITextControlData.h"
#include "IWatermarkData.h"
#include "IWorkspace.h"

// General includes:
#include "CDialogController.h"
#include "TextPanelID.h"
#include "Utils.h"

// Project includes:
#include "WatermarkUIID.h"
#include "IWatermarkDataFacade.h"



/** WatermarkUIDialogController
	Methods allow for the initialization, validation, and application of dialog widget values.
	
	Implements IDialogController based on the partial implementation CDialogController.
	
	@ingroup watermarkui
*/
class WatermarkUIDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		WatermarkUIDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~WatermarkUIDialogController() {}

		/** Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
		*/
	       virtual void InitializeDialogFields(IActiveContext* dlgContext);

		/** Validate the values in the widgets.
			By default, the widget with ID kOKButtonWidgetID causes
			ValidateFields to be called. When all widgets are valid,
			ApplyFields will be called.
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
	       virtual WidgetID ValidateDialogFields(IActiveContext* myContext);


		/** Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);

private:
		
		/**Initialize the font color widget  with UI color.
		   Called by InitializeDialogFields.	
		*/
		void InitializeFontColorWidget(IActiveContext* myContext, UID defaultColorUID); 

		/**Initialize the watermark Vertical position.
		   Called by InitializeDialogFields.	
		*/
		void InitializeVPosition(IActiveContext* myContext, int32 index, bool16 isSelect = kTrue);
		
		/**Initialize the watermark Horizontal position.
		   Called by InitializeDialogFields.	
		*/
		void InitializeHPosition(IActiveContext* myContext, int32 index, bool16 isSelect = kTrue);

};

CREATE_PMINTERFACE(WatermarkUIDialogController, kWatermarkUIDialogControllerImpl)


/* InitializeDialogFields
*/
void WatermarkUIDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	do
	{
		if (dlgContext == nil)
		{
			ASSERT_FAIL("Active context is invalid");
			break;
		}
		CDialogController::InitializeDialogFields(dlgContext);	

		// get the current values for the watermark info
		const IWorkspace* contextWorkspace = dlgContext->GetContextWorkspace();
		if (contextWorkspace == nil) 
		{
			ASSERT_FAIL("Context workspace is invalid");
			break;
		}
		IWatermarkData::WatermarkInfo wmkInfo;
		if (kFailure == Utils<IWatermarkDataFacade>()->GetWatermarkPref(::GetUIDRef(contextWorkspace), wmkInfo))
		{
			ASSERT_FAIL("Cannot obtain watermark preference from context workspace.");
			break;
		}
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil) {
			ASSERT_FAIL("Cannot obtain panelControlData.");
			break;
		}

		ITriStateControlData::TriState state;

		// VISIBILITY
		state = wmkInfo.fVisibility ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		SetTriStateControlData(kWatermarkUIShowWatermarkCheckBoxWidgetID, state);

		// DO PRINT
		state = wmkInfo.fDoPrint ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		SetTriStateControlData(kWatermarkUIDoPrintCheckBoxWidgetID, state);

		// DRAW IN BACK
		state = wmkInfo.fDrawInBack ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		SetTriStateControlData(kWatermarkUIDrawInBackCheckBoxWidgetID, state);

		// TEXT
		PMString currentText(wmkInfo.fText);
		currentText.SetTranslatable(kFalse);
		SetTextControlData(kWatermarkUIEditBoxWidgetID, currentText);

		// FONT COLOR
		InitializeFontColorWidget(dlgContext, wmkInfo.fFontColor);

		// OPACITY
		SetTextValue(kWatermarkUIOpacityWidgetID, wmkInfo.fOpacity);

		// ROTATION
		SetTextValue(kWatermarkUIRotationWidgetID, wmkInfo.fRotation);

		// FONT FAMILY & STYLE 
		// initialized in observer's Update method, after the font family list has been populated

		// FONT POINT SIZE
		SetTextValue(kWatermarkUIFontSizeWidgetID, wmkInfo.fFontPointSize);

		// HORIZONTAL POSITION/OFFSET
		InitializeHPosition(dlgContext, wmkInfo.fHorzPosition);
		SetTextValue(kWatermarkUIHOffsetWidgetID, wmkInfo.fHorzOffset);

		// VERTICAL POSITION/OFFSET
		InitializeVPosition(dlgContext, wmkInfo.fVertPosition);
		SetTextValue(kWatermarkUIVOffsetWidgetID, wmkInfo.fVertOffset);

	} while(false);	
}




/* InitializeFontColorWidget
*/
void WatermarkUIDialogController::InitializeFontColorWidget(IActiveContext* myContext, UID defaultColorUID) 
{
	do
	{
	    InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}
		IControlView* panelControlView = panelData->FindWidget(kWatermarkUIColorDropDownWidgetID);
		if (panelControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}
		InterfacePtr<IColorListControlData> colorListControlData(panelControlView, IColorListControlData::kDefaultIID);
		if (colorListControlData == nil)
		{
			ASSERT_FAIL("IColorListControlData is invalid");
			break;
		}
		IWorkspace* workSpace = myContext->GetContextWorkspace();
		if (workSpace == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}	
		InterfacePtr<ISwatchList> uiColorList(workSpace, IID_IUICOLORLIST);
		if (uiColorList == nil)
		{
			ASSERT_FAIL("ISwatchList is invalid");
			break;
		}

		//setup color drop-down list 
		colorListControlData->Setup(::GetUIDRef(uiColorList), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, defaultColorUID);    

	} while(false);
}


/* InitializeHPosition
*/
void WatermarkUIDialogController::InitializeHPosition(IActiveContext* myContext, int32 index, bool16 isSelect)
{
    do {
        InterfacePtr<IStringListControlData> stringListControlData(QueryListControlDataInterface(kWatermarkUIHPosDropDownWidgetID));
        if (stringListControlData == nil)
        {
            ASSERT_FAIL("IStringListControlData is invalid");
            break;
        }
        // Clear the drop list
        stringListControlData->Clear();

        // initialize widget values
        stringListControlData->AddString(PMString(kWatermarkUIHPosLeftDropDownItemKey));
        stringListControlData->AddString(PMString(kWatermarkUIHPosCenterDropDownItemKey));
		stringListControlData->AddString(PMString(kWatermarkUIHPosRightDropDownItemKey));
       
        // Get a pointer to the controller for the drop list
        InterfacePtr<IDropDownListController> dropListController (stringListControlData, UseDefaultIID());
        if (dropListController == nil)
        {
            ASSERT_FAIL("IDropDownListController is invalid");
            break;
        }

		//select the drop list 
		if (isSelect == kTrue)
		{
			dropListController->Select(index);
		}
		else
		{
			dropListController->Deselect();
		}

    } while (kFalse);

}


/* InitializeVPosition
*/
void WatermarkUIDialogController::InitializeVPosition(IActiveContext* myContext, int32 index, bool16 isSelect)
{
    do {
        InterfacePtr<IStringListControlData> stringListControlData(QueryListControlDataInterface(kWatermarkUIVPosDropDownWidgetID));
        if (stringListControlData == nil)
        {
            ASSERT_FAIL("IStringListControlData is invalid");
            break;
        }
        // Clear the drop list
        stringListControlData->Clear();

        // initialize widget values
        stringListControlData->AddString(PMString(kWatermarkUIVPosTopDropDownItemKey));
        stringListControlData->AddString(PMString(kWatermarkUIVPosCenterDropDownItemKey));
		stringListControlData->AddString(PMString(kWatermarkUIVPosBottomDropDownItemKey));
       
        // Get a pointer to the controller for the drop list
        InterfacePtr<IDropDownListController> dropListController (stringListControlData, UseDefaultIID());
        if (dropListController == nil)
        {
            ASSERT_FAIL("IDropDownListController is invalid");
            break;
        }

		//select the drop list 
		if (isSelect == kTrue)
		{
			dropListController->Select(index);
		}
		else
		{
			dropListController->Deselect();
		}

    } while (kFalse);

}


/* ValidateDialogFields
*/
WidgetID WatermarkUIDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID result = CDialogController::ValidateDialogFields(myContext);

	return result;
}


/* ApplyDialogFields
*/
void WatermarkUIDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	// intentionally empty - dialog fields are handled by the observer
}

//  Code generated by DollyXs code generator
