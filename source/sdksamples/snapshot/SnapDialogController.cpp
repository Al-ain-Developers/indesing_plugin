//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapDialogController.cpp $
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
//  
//  The SnapDialogController's methods allow for the initialization, 
//  validation, and application of dialog field values. The dialog is 
//  used to maintain preferences for the Snapshot Tool.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ISession.h"
#include "IControlView.h"
#include "IDialog.h"
#include "ISubject.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IDropDownListController.h"
#include "IStringListControlData.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IImageWriteFormat.h"
#include "IImageWriteFormatInfo.h"
#include "IK2ServiceProvider.h"
#include "IWorkspace.h"
#include "ISnapPrefsData.h"
#include "ICommand.h"
#include "IShape.h"

// Implementation includes:
#include "SystemUtils.h"
#include "CreateObject.h"
#include "PersistUtils.h"
#include "ImageID.h"
#include "CmdUtils.h"
#include "CAlert.h"
#include "ImageTypes.h"
#include "Trace.h"
#include "CDialogController.h"
#include "K2Vector.h"
#include "JPEGFilterID.h"

// Project includes:
#include "SnapID.h"

/** SnapDialogController
	Methods allow for the initialization and validation of dialog widget values.
  
	
	@ingroup snapshot
*/
class SnapDialogController : public CDialogController
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SnapDialogController(IPMUnknown* boss)
			: CDialogController(boss) {}

		/** 
			Destructor.
		*/
		virtual ~SnapDialogController() {}

		/**
			Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
		*/
		virtual void InitializeDialogFields(IActiveContext* context);

		/**
			Validate the values in the widgets. 
			By default, the widget with ID kOKButtonWidgetID causes 
			ValidateFields to be called. When all widgets are valid, 
			ApplyFields will be called.			
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
		virtual WidgetID ValidateDialogFields(IActiveContext* myContext);

		/**
			Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
	
	private:
		/**
			Populate the format drop down widget with the list of
			format names registered in the service registry by 
			image write format services. 
			
			If the selectedFormatClassID is set to kInvalidClass select
			the default image format as defined in the registry. Otherwise
			select the format name that corresponds to the given selectedFormatClassID.
		*/
		void InitialiseWriteFormats(ClassID selectedFormatClassID);

		/**
			Find the selected format from its drop down widget and
			lookup its corresponding boss ClassID.
		*/
		ClassID GetFormatClassID();

		/** 
			Set the dropdown list value.
		*/
		void SetDropDownValue(const long widgetID, int32 newValue);

		/** 
			Get the dropdown list selected value.
		*/
		int32 GetDropDownValue(const long widgetID);

		/** Replaces substrings found in a string with something else.
		 * 	@param original IN/OUT Original string to search in.
		 * 	@param target IN Text to search for.
		 * 	@param replace IN Text to replace with.
		 */
		void Replace(PMString& original,
					 const PMString& target,
					 const PMString& replace);
		
		/**
			This list parallels the kFileFormatDropDownWidgetId and
			stores the boss ClassID that corresponds to the displayed
			image format.	
		*/
		K2Vector<ClassID> fFormatClassIDList;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SnapDialogController, kSnapDialogControllerImpl)


/*	InitializeFields
	Set the initial widget values based on the persistent preferences.
*/
void SnapDialogController::InitializeDialogFields(IActiveContext* context) 
{
	this->SetInitialized(kFalse);

	do
	{
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (workspace == nil)
		{
			ASSERT_FAIL("workspace invalid");
			break;
		}
		InterfacePtr<ISnapPrefsData> prefs(workspace, UseDefaultIID());
		if (prefs == nil)
		{
			ASSERT_FAIL("snap shot prefs data invalid");
			break;
		}
		SetTextControlData(kFilenameTextEditBoxWidgetID, prefs->GetName());
		InitialiseWriteFormats(prefs->GetFormatClassID());
		SetTextValue(kScalePercentageComboBoxWidgetID, prefs->GetScale()*100.0);
		SetTextValue(kResolutionRealComboBoxWidgetID, prefs->GetResolution());
		SetTextValue(kMinimumResolutionRealComboBoxWidgetID, prefs->GetMinimumResolution());
		SetTextValue(kBleedXMeasureEditBoxWidgetID, prefs->GetBleed());
		SetDropDownValue(kJPEGEncodingDropDownWidgetID, prefs->GetJPEGEncoding());
		SetDropDownValue(kJPEGQualityDropDownWidgetID, prefs->GetJPEGQuality());
		SetDropDownValue(kTIFFPaletteTypeDropDownWidgetID, prefs->GetTIFFPaletteType());

		// For GIF format, it needs a colour palette so NoPalette is not an option for GIF format. 
		// Since NoPalette is not in the drop down list for this widget, we need to match the 
		// value we defined in PaletteType, hence, we minus 1 here.
		SetDropDownValue(kGIFPaletteTypeDropDownWidgetID, prefs->GetGIFPaletteType() - 1);

		SetTriStateControlData(kTIFFTransparentWidgetID, prefs->GetTIFFTransparent());
		SetTriStateControlData(kGIFTransparentWidgetID, prefs->GetGIFTransparent());

		if (prefs->GetDrawArea())
		{
			SetTriStateControlData(kDrawAreaRadioWidgetID, ITriStateControlData::kSelected);
			SetTriStateControlData(kDrawItemRadioWidgetID, ITriStateControlData::kUnselected);
		}
		else
		{
			SetTriStateControlData(kDrawAreaRadioWidgetID, ITriStateControlData::kUnselected);
			SetTriStateControlData(kDrawItemRadioWidgetID, ITriStateControlData::kSelected);
		}

		SetTriStateControlData(kFullResolutionWidgetID, prefs->GetFullResolutionGraphics());
		SetTriStateControlData(kGrayscaleWidgetID, prefs->GetDrawGray());
		SetTriStateControlData(kGIFInterlacedWidgetID, prefs->GetGIFTransparent());

		if (prefs->GetDrawingFlags() == IShape::kPrinting)
			SetTriStateControlData(kPrintingWidgetID, kTrue);
		else
			SetTriStateControlData(kPrintingWidgetID, kFalse);

		SetInitialized(kTrue);

	} while (false);
		
}


/*  ValidateFields
*/
WidgetID SnapDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID badWidgetID = kDefaultWidgetId;

	do
	{
		{
			// Validate image filename
			PMString name = GetTextControlData(kFilenameTextEditBoxWidgetID);
			name.StripWhiteSpace();
			if (name.CharCount() == 0)
			{
				badWidgetID = kFilenameTextEditBoxWidgetID;
				PMString message(kAlertBadFilenameKey, PMString::kTranslateDuringCall);
				message.SetTranslatable(kFalse);
				name.SetTranslatable(kFalse);
				this->Replace(message, "^0", name);
				CAlert::ErrorAlert(message);
				break;
			}
		} // Validate image filename

		{
			// Validate image write format

			// First get some info about the selected image write format
			ClassID formatClass = GetFormatClassID();
			InterfacePtr<IImageWriteFormatInfo> imageWriteFormatInfo((IImageWriteFormatInfo *)::CreateObject(formatClass, IID_IIMAGEWRITEFORMATINFO));
			if (imageWriteFormatInfo == nil)
			{
				ASSERT_FAIL("SnapDialogController::ValidateFields() imageWriteFormatInfo invalid");
				break;
			}
			ImageColorSpaceSupportInfo colourSpaceSupportInfo;

			// Validate the format supports RGB or grayscale colour spaces
			uint32 colourSpace = kPMRGBColorSpace;
			if (GetTriStateControlData(kGrayscaleWidgetID) == ITriStateControlData::kSelected)
				colourSpace = kPMGrayColorSpace;
			bool16 colourSpaceSupported = imageWriteFormatInfo->GetImageColorSpaceSupportInfo (colourSpace, &colourSpaceSupportInfo);
			if (colourSpaceSupported == kFalse)
			{
				// The selected format does not support RGB or Grayscale colour spaces
				badWidgetID = kFileFormatDropDownWidgetId;
				PMString message(kAlertFormatDoesNotSupportRgbOrGrayscaleKey);
				CAlert::ErrorAlert(message);
				break;
			}
		} // Validate image write format 

		{
			// Validate resolution is greater than minimum
			PMReal minimumResolution = GetTextValue(kMinimumResolutionRealComboBoxWidgetID);
			PMReal resolution = GetTextValue(kResolutionRealComboBoxWidgetID);
			if (resolution < minimumResolution)
			{
				// The selected format does not support pixel data
				badWidgetID = kMinimumResolutionRealComboBoxWidgetID;
				PMString message(kAlertMinimumResolutionKey);
				CAlert::ErrorAlert(message);
				break;
			}
		} // Validate resolution is greater than minimum

		{

			// Warn user if there is a possibility that we might generate large image files

			// Grab our preferences so we can see if the user's made a change...
			InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
			if (workspace == nil)
			{
				ASSERT_FAIL("workspace invalid");
				break;
			}
			InterfacePtr<ISnapPrefsData> prefs(workspace, UseDefaultIID());
			if (prefs == nil)
			{
				ASSERT_FAIL("prefs invalid");
				break;
			}

			// Now pop an alert if we're doing large or high res stuff.
			// Really this check should be in the tracker which should
			// evaluate the size of the area to be imaged, the scale & 
			// the resolution. Instead we're just putting in a quick and dirty
			// check here. This is _not_ ideal.
			PMReal resolution = GetTextValue(kResolutionRealComboBoxWidgetID);
			PMReal scale = GetTextValue(kScalePercentageComboBoxWidgetID)/100.0;
			if ( (scale != prefs->GetScale() && scale > 1.0) || (resolution != prefs->GetResolution() && resolution > 72.0) )
			{
			
				PMString message(kAlertDoYouReallyWantToDoThis);
			
				int32 userChoice = CAlert::ModalAlert
				(
					message,		// Alert string
					kYesString, 	// Yes - display alerts
					kNoString, 		// No - exit showing alerts
					kNullString, 	// No third button
					1,										// Set Yes button to default
					CAlert::eQuestionIcon					// Warning icon.
				);

				if (userChoice == 2) 
				{
					if (scale > 1.0)
						badWidgetID = kScalePercentageComboBoxWidgetID;
					else
						badWidgetID = kResolutionRealComboBoxWidgetID;
					break;
				}
			}

		} // Warn user if there is a possibility that we might generate large image files

	} while (false);

	return badWidgetID;

}


/* ApplyFields
*/
void SnapDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	do
	{
		InterfacePtr<ICommand> setPrefsCmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
		if (setPrefsCmd == nil)
		{
			ASSERT_FAIL("setPrefsCmd invalid");
			break;
		}
		InterfacePtr<ISnapPrefsData> prefsData(setPrefsCmd, UseDefaultIID());
		if (prefsData == nil)
		{
			ASSERT_FAIL("prefsData invalid");
			break;
		}
		prefsData->SetName(WideString(GetTextControlData(kFilenameTextEditBoxWidgetID)));
		prefsData->SetFormatClassID(GetFormatClassID());
		prefsData->SetScale(GetTextValue(kScalePercentageComboBoxWidgetID)/100.0);
		prefsData->SetResolution(GetTextValue(kResolutionRealComboBoxWidgetID));
		prefsData->SetMinimumResolution(GetTextValue(kMinimumResolutionRealComboBoxWidgetID));
		prefsData->SetBleed(GetTextValue(kBleedXMeasureEditBoxWidgetID));
		prefsData->SetJPEGEncoding(GetDropDownValue(kJPEGEncodingDropDownWidgetID));
		prefsData->SetJPEGQuality(GetDropDownValue(kJPEGQualityDropDownWidgetID));
		prefsData->SetTIFFPaletteType(GetDropDownValue(kTIFFPaletteTypeDropDownWidgetID));
		// For GIF format, it needs a colour palette so NoPalette is not an option for GIF format. 
		// NoPalette is not in the drop down list for this widget. However, we need to match the 
		// value we defined in PaletteType, hence, we add 1 here.
		prefsData->SetGIFPaletteType(GetDropDownValue(kGIFPaletteTypeDropDownWidgetID) + 1);
		prefsData->SetTIFFTransparent(GetTriStateControlData(kTIFFTransparentWidgetID) == ITriStateControlData::kSelected);
		prefsData->SetGIFTransparent(GetTriStateControlData(kGIFTransparentWidgetID) == ITriStateControlData::kSelected);
		prefsData->SetGIFInterlaced(GetTriStateControlData(kGIFInterlacedWidgetID) == ITriStateControlData::kSelected);
		prefsData->SetDrawArea(GetTriStateControlData(kDrawAreaRadioWidgetID) == ITriStateControlData::kSelected);
		prefsData->SetFullResolutionGraphics(GetTriStateControlData(kFullResolutionWidgetID) == ITriStateControlData::kSelected);
		prefsData->SetDrawGray(GetTriStateControlData(kGrayscaleWidgetID) == ITriStateControlData::kSelected);
		if (GetTriStateControlData(kPrintingWidgetID) == ITriStateControlData::kSelected)
			prefsData->SetDrawingFlags(IShape::kPrinting);
		else
			prefsData->SetDrawingFlags(IShape::kNoFlags);

		TRACE("scale %f, resolution %f, minimumResolution %f, bleed %f, drawingFlags %d, fullResolutionGraphics %d, drawGray, %d\n",
				::ToDouble(prefsData->GetScale()), 
				::ToDouble(prefsData->GetResolution()), 
				::ToDouble(prefsData->GetMinimumResolution()),
				::ToDouble(prefsData->GetBleed()),
				prefsData->GetDrawingFlags(),
				prefsData->GetFullResolutionGraphics(),
				prefsData->GetDrawGray()
		);


		if (CmdUtils::ProcessCommand(setPrefsCmd) != kSuccess)
		{
			ASSERT_FAIL("command kSnapshotSetPrefsCmdBoss  failed");
			break;
		}
	} while (false);	
}


/* InitialiseWriteFormats
*/
void SnapDialogController::InitialiseWriteFormats(ClassID selectedFormatClassID)
{
	do
	{	
		// Acquire our panel's control data
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("panelControlData invalid");
			break;
		}

		// Clear the format dropdown of data
		IControlView* controlView = panelControlData->FindWidget(kFileFormatDropDownWidgetId);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid");
			break;
		}
		InterfacePtr<IDropDownListController> dropDownListController(controlView, UseDefaultIID());
		if (dropDownListController == nil)
		{
			ASSERT_FAIL("dropDownListController invalid");
			break;
		}
		InterfacePtr<IStringListControlData> stringListControlData(dropDownListController, UseDefaultIID());
		if (stringListControlData == nil)
		{
			ASSERT_FAIL("stringListControlData invalid");
			break;
		}
		stringListControlData->Clear(kTrue, kFalse);

		// Populate the drop down with the image write formats registered in the service registry
		InterfacePtr<IK2ServiceRegistry>	registry(GetExecutionContextSession(), UseDefaultIID());
		if (registry == nil)
		{
			ASSERT_FAIL("registry invalid");
			break;
		}
				
		// Use the default image write format service if none is yet selected
		if (selectedFormatClassID == kInvalidClass)
			selectedFormatClassID = registry->GetDefaultServiceProviderID(kImageWriteFormatService);
		
		// In the format widget we display the format names. In list
		// fFormatClassIDList we maintain their corresponding ClassID.
		// We use this list to map the selected dropdown list entry
		// onto the image write format's boss ClassID.
		fFormatClassIDList.clear();
		
		// Loop round populating the drop down widget and fFormatClassIDList.
		int32 selectedFormatIndex = -1;
		int32 numHandlers = (registry->GetServiceProviderCount(kImageWriteFormatService));
		for (int32 i = 0; i < numHandlers; i++)
		{
			InterfacePtr<IK2ServiceProvider> provider(registry->QueryNthServiceProvider(kImageWriteFormatService, i));
			InterfacePtr<IImageWriteFormatInfo> info(provider, IID_IIMAGEWRITEFORMATINFO);
			PMString formatName;
			info->GetFormatName(&formatName);
			stringListControlData->AddString(formatName, IStringListControlData::kEnd, kFalse, kFalse);
			ClassID formatClassID = ::GetClass(provider);
			fFormatClassIDList.push_back(formatClassID);
			if (formatClassID == selectedFormatClassID)
				selectedFormatIndex = i;
		}

		// Set the selected format
		if (selectedFormatIndex >= 0)
			dropDownListController->Select(selectedFormatIndex, kTrue, kFalse);

	}
	while (false); // only do once
}


/* GetFormatClassID
*/
ClassID SnapDialogController::GetFormatClassID()
{
	ClassID result = kInvalidClass;
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("panelControlData invalid");
			break;
		}		
		IControlView* controlView = panelControlData->FindWidget(kFileFormatDropDownWidgetId);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid");
			break;
		}
		InterfacePtr<IDropDownListController> dropDown(controlView, UseDefaultIID());
		if (dropDown == nil)
		{
			ASSERT_FAIL("dropDown invalid");
			break;
		}
		int32 selectedIndex = dropDown->GetSelected();
		result = fFormatClassIDList [selectedIndex];
	} while (false);
	return result;
}

/* SetDropDownValue
*/
void SnapDialogController::SetDropDownValue(const long widgetID, int32 newValue)
{
	do
	{
	   InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	   if (panelControlData == nil)
		   ASSERT_FAIL("panelControlData invalid");

	   IControlView* view = panelControlData->FindWidget(widgetID);
	   if (view == nil)
		   ASSERT_FAIL("control view invalid");

	   InterfacePtr<IDropDownListController> dropDownVal (view, UseDefaultIID());
	   if (dropDownVal == nil)
			ASSERT_FAIL("control view invalid");

	   dropDownVal->Select(newValue);
	 }	while (false);
}

/* GetDropDownValue
*/
int32 SnapDialogController::GetDropDownValue(const long widgetID)
{
	int32 result = -1;
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("panelControlData invalid");
			break;
		}		
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid");
			break;
		}
		InterfacePtr<IDropDownListController> dropDown(controlView, UseDefaultIID());
		if (dropDown == nil)
		{
			ASSERT_FAIL("dropDown invalid");
			break;
		}
		result = dropDown->GetSelected();
	} while (false);

	return result;
}

/* Replace
*/
void SnapDialogController::Replace(PMString& original,
								   const PMString& target,
								   const PMString& replace)
{
	const int32 kTargetFoundPos = original.IndexOfString(target);
	if (kTargetFoundPos >= 0)
	{
		original.Remove(kTargetFoundPos, target.CharCount());
		original.Insert(replace, kTargetFoundPos);
	}
}

// End, SnapDialogController.cpp.


