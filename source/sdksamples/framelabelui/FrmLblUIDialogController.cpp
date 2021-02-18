//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabelui/FrmLblUIDialogController.cpp $
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
#include "ISelectionManager.h"
#include "IDropDownListController.h"
#include "IStringListControlData.h"
#include "ITriStateControlData.h"
#include "iuicolorutils.h"
#include "IPanelControlData.h"
#include "IColorListControlData.h"
#include "IWorkspace.h"
#include "ISwatchList.h"
// General includes:
#include "CDialogController.h"
// Project includes:
#include "FrmLblUIID.h"
#include "FrmLblID.h"
#include "FrmLblType.h"
#include "IFrmLblDataSuite.h"

/** FrmLblUIDialogController
	Methods allow for the initialization, validation, and application of dialog widget
	values.
	Implements IDialogController based on the partial implementation CDialogController.

	
	@ingroup framelabelui
*/
class FrmLblUIDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		FrmLblUIDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~FrmLblUIDialogController() {}

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

		/**Set the default preference setting for current document.
		   Called by InitializeDialogFields.		  
		   @param labelInfo the item label value.
		*/
		void SetDefaultSetting(IActiveContext* myContext, const FrmLblInfo &labelInfo);

		/**Initialize the adornment label position.
		   Called by InitializeDialogFields.	
		*/
		void InitializeLabelPosition(IActiveContext* myContext, int32 index, bool16 isSelect = kTrue);
};

/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its
ImplementationID making the C++ code callable by the
application.
*/
CREATE_PMINTERFACE(FrmLblUIDialogController, kFrmLblUIDialogControllerImpl)

/* InitialFields
*/
void FrmLblUIDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	do
	{
		if (dlgContext == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}
		CDialogController::InitializeDialogFields(dlgContext);	

		FrmLblInfo labelInfo;
		InterfacePtr<IFrmLblDataSuite> frmLblDataSuite(dlgContext->GetContextSelection(),UseDefaultIID());
		if (frmLblDataSuite == nil)
		{
			ASSERT_FAIL("IFrmLblDataSuite is invalid");
			break;
		}
		frmLblDataSuite->GetFrameLabelProperties(labelInfo);
		
		//Set the default setting
		SetDefaultSetting(dlgContext, labelInfo);		

	} while(false);	
}

/* ValidateFields
*/
WidgetID FrmLblUIDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID result = CDialogController::ValidateDialogFields(myContext);	
	return result;
}

/* ApplyFields
*/
void FrmLblUIDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	do 
	{
		InterfacePtr<IFrmLblDataSuite> frmLblDataSuite(myContext->GetContextSelection(),UseDefaultIID());		
		if (frmLblDataSuite == nil)
		{
			ASSERT_FAIL("IFrmLblDataSuite is invalid");
			break;
		}

		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		if (dialogController == nil)
		{
			ASSERT_FAIL("IDialogController is invalid");
			break;
		}

		FrmLblInfo labelInfo;
		//set label text value,and get static text data from GetTextControlData
		labelInfo.label = WideString(dialogController->GetTextControlData(kFrmLblUIAdornmentTextEditBoxWidgetID));
		
		InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}

		IControlView* showLabelControlView = panelData->FindWidget(kFrmLblUIShowLabelCheckBoxWidgetID) ;
		if (showLabelControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}
		InterfacePtr<ITriStateControlData> dtriStateControlData(showLabelControlView, IID_ITRISTATECONTROLDATA);
		if (dtriStateControlData == nil)
		{
			ASSERT_FAIL("ITriStateControlData is invalid");
			break;
		}
		//set label visible/invisible state,and get the state  from ITriStateControlData::GetState()
		labelInfo.visibility = (dtriStateControlData->GetState() == ITriStateControlData::kSelected) ? kTrue :  kFalse;

		IControlView* fontColorControlView = panelData->FindWidget(kFrmLblUIColorDropDownWidgetID) ;
		if (fontColorControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}
		
		InterfacePtr<IColorListControlData> colorListControlData(fontColorControlView, UseDefaultIID());
		if (colorListControlData == nil)
		{
			ASSERT_FAIL("IColorListControlData is invalid");
			break;
		}

		//set font color
		labelInfo.fontColor = colorListControlData->GetSelection();

		IControlView* labelPosControlView = panelData->FindWidget(kFrmLblUILabelPosDropDownWidgetID) ;
		if (labelPosControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}		
		
		InterfacePtr<IDropDownListController> labelPosDropDownListController(labelPosControlView, UseDefaultIID());
		if (labelPosDropDownListController == nil)
		{
			ASSERT_FAIL("IDropDownListController is invalid");
			break;
		}
		//set label position,and position info the IDropDownListController::GetSelected()
		labelInfo.position = (FrmLblPosition)labelPosDropDownListController->GetSelected();
		//UpdateFrameLabelProperties
		frmLblDataSuite->UpdateFrameLabelProperties(labelInfo);
		
	} while(false);

}

/* SetDefaultSettings
*/
void FrmLblUIDialogController::SetDefaultSetting(IActiveContext* myContext, const FrmLblInfo& labelInfo) 
{

	do 
	{
		InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}	
		
		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		if (dialogController == nil)
		{
			ASSERT_FAIL("IDialogController is invalid");
			break;
		}
		//set static text value
		PMString display(labelInfo.label);
		display.SetTranslatable(kFalse);
		dialogController->SetTextControlData(kFrmLblUIAdornmentTextEditBoxWidgetID, display);

		IControlView* showLabelControlView = panelData->FindWidget(kFrmLblUIShowLabelCheckBoxWidgetID) ;
		if (showLabelControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}
		InterfacePtr<ITriStateControlData> dtriStateControlData(showLabelControlView, IID_ITRISTATECONTROLDATA);
		if (dtriStateControlData == nil)
		{
			ASSERT_FAIL("ITriStateControlData is invalid");
			break;
		}
		//set check box value for visibility
		if (labelInfo.visibility == kTrue)
		{
			dtriStateControlData->Select(kTrue, kTrue);
		}
		else
		{
			dtriStateControlData->Deselect(kTrue, kTrue);
		}
	
		IControlView* fontColorControlView = panelData->FindWidget(kFrmLblUIColorDropDownWidgetID) ;
		if (fontColorControlView == nil)
		{
			ASSERT_FAIL("IControlView invalid");
			break;
		}
		
		//initial font color widget
		InitializeFontColorWidget(myContext,labelInfo.fontColor);

		//initial label position
		InitializeLabelPosition(myContext, labelInfo.position);  

	} while(false);
}

/* InitialFontColor
*/
void FrmLblUIDialogController::InitializeFontColorWidget(IActiveContext* myContext, UID defaultColorUID) 
{
	do
	{
	    InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
		if (panelData == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break;
		}

		IControlView* panelControlView = panelData->FindWidget(kFrmLblUIColorDropDownWidgetID);
		if (panelControlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}

		InterfacePtr<IColorListControlData> colorListControlData(panelControlView, IID_ICOLORLISTCONTROLDATA);
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

/* InitializeLabelPosition
*/
void FrmLblUIDialogController::InitializeLabelPosition(IActiveContext* myContext, int32 index, bool16 isSelect)
{

    do {

        InterfacePtr<IStringListControlData> stingListControlData(QueryListControlDataInterface(kFrmLblUILabelPosDropDownWidgetID));
        if (stingListControlData == nil)
        {
            ASSERT_FAIL("IStringListControlData is invalid");
            break;
        }

        // Clear the drop list
        stingListControlData->Clear();

        // initialize widget values
        stingListControlData->AddString(PMString(kFrmLblUILabelPosTopDropDownItemKey));
        stingListControlData->AddString(PMString(kFrmLblUILabelPosBottomDropDownItemKey));
		stingListControlData->AddString(PMString(kFrmLblUILabelPosLeftDropDownItemKey));
        stingListControlData->AddString(PMString(kFrmLblUILabelPosRightDropDownItemKey));

       
        // Get a pointer to the controller for the drop list
        InterfacePtr<IDropDownListController> dropListController (stingListControlData, UseDefaultIID());
        if (dropListController == nil)
        {
            ASSERT_FAIL("IDropDownListController is invalid");
            break;
        }

		//select the dorp list 
		if(isSelect == kTrue && index != kFrmLblPosNone)
		{
			dropListController->Select(index);
		}
		else
		{
			dropListController->Deselect();
		}

    } while (kFalse);

}
