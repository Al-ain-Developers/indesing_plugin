//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/utils/FormFieldUIUtils.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionManager.h"
#include "IApplication.h"
#include "IAnimationBehaviorData.h"
#include "IAppearanceItemFacade.h"
#include "IAppearanceSuite.h"
#include "IApplication.h"
#include "IBehaviorData.h"
#include "IDialog.h"
#include "IDialogController.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IDynamicTargetsFacade.h"
#include "IFormFieldFactory.h"
#include "IFormFieldSuite.h"
#include "IFormFieldUIFactory.h"
#include "IHierarchy.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILibrary.h"
#include "ILibraryAsset.h"
#include "ILibraryAssetMetaData.h"
#include "IListControlDataOf.h"
#include "IMovieActionData.h"
#include "IMultiStateObjectBehaviorData.h"
#include "IPanelControlData.h"
#include "IPanelMgr.h"
#include "ISelectionManager.h"
#include "ISoundActionData.h"
#include "IStateData.h"
#include "IStringListControlData.h"
#include "ITool.h"
#include "IUIDData.h"

// ----- Includes -----

#include "K2Pair.h"
#include "PlugIn.h"
#include "PMString.h"

// ----- Utility files -----

#include "AssetLibUtils.h"
#include "FileUtility.h"
#include "FileUtils.h"
#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "IToolBoxUtils.h"
#include "SelectionUtils.h"
#include "StringUtils.h"
#include "UserInterfaceUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"	// kSWFPreviewSpreadActionID
#include "FormFieldID.h"
#include "FormFieldUIID.h"


using namespace Form;
using namespace AssetLibUtils;

//------------------------------------------------------------------------

void FormFieldUIUtils::AdjustStylePresetMenu( const PMString& inStyleLibName, IPanelControlData* inPanelData,
		WidgetID inPopupWidget, bool16 supportsNone )
{
	PMString styleLibFileName = inStyleLibName;

	IControlView* iListView = inPanelData->FindWidget(inPopupWidget);
	ASSERT_MSG(iListView, "Widget Not Found");
	if (iListView == 0)
		return;

	InterfacePtr<IStringListControlData> iStringList(iListView, IID_ISTRINGLISTCONTROLDATA);

	iStringList->Clear();

	bool hasStyleLib = !styleLibFileName.IsEmpty();
	
	PMString noneStyleName("$$$/AppearanceStyle/None");
	noneStyleName.Translate();
	noneStyleName.SetTranslatable(kFalse);
	PMString customStyleName("$$$/AppearanceStyle/Custom");
	customStyleName.Translate();
	customStyleName.SetTranslatable(kFalse);

	if (hasStyleLib)
	{
		class AddNamesToMenu : public AssetEnumerator
		{
		public:
			IStringListControlData* mStringList;
			bool mAddedAny;
			virtual bool operator()(ILibraryAsset *inAsset)
			{
				if (!mAddedAny)
				{
				  	mAddedAny = true;
				}
				
				InterfacePtr<ILibraryAssetMetaData> assetMetaData(inAsset,IID_ILIBRARYASSETMETADATA);
				PMString appearanceName( assetMetaData->GetName() );
				PMString predefinedAppearanceNamePreamble( kPredefinedAppearanceNamePreamble );
				if ( appearanceName.IndexOfString(predefinedAppearanceNamePreamble) == 0 ) {
					// Normally, names in the library are already translated.  However, we have
					// a special case here where our predefined appearance style names are not
					// translated.  So we need to go through some hoops here to do the translation.
					int32 size;
					const UTF16TextChar *buf = appearanceName.GrabUTF16Buffer(&size);
					PMString untranslatedString("");
					untranslatedString.SetXString( buf, size );
					appearanceName = untranslatedString;
					appearanceName.Translate();
					appearanceName.SetTranslatable(kFalse);
				}
	  			mStringList->AddString(appearanceName);
	  			return true; //continue iteration
			}
		};
		
		iStringList->Clear();

		InterfacePtr<ILibrary> assetLib( QueryStyleLibByName(styleLibFileName) ); 

		AddNamesToMenu addNamesToMenu;
		addNamesToMenu.mStringList = iStringList;
		addNamesToMenu.mAddedAny = false;
	
		if (assetLib)
			AssetLibUtils::EnumerateAssets(assetLib, &addNamesToMenu);

		if (addNamesToMenu.mAddedAny) {
			PMString separatorString("-");
			separatorString.SetTranslatable(kFalse);
	  		iStringList->AddString(separatorString); 
	  	}
	  	
	  	//NOTE: Update SelectStylePresetMenu if these are reordered/changed...
	  	
	  	iStringList->AddString(customStyleName);
	  	if ( supportsNone )
	  		iStringList->AddString(noneStyleName);
		//Menu Selection handled in another call...
	}
	else
	{
	  	iStringList->AddString(customStyleName);
	  	if ( supportsNone )
	  		iStringList->AddString(noneStyleName);

		InterfacePtr<IDropDownListController> iListData(iListView, IID_IDROPDOWNLISTCONTROLLER);
		iListData->Deselect();
	}
	
	iListView->Enable(hasStyleLib);
}

//------------------------------------------------------------------------

void FormFieldUIUtils::SelectStylePresetMenu( const PMString& inStyleLibName,
			IDropDownListController* inPopup, bool16 supportsNone )
{
	PMString styleLibFileName = inStyleLibName;

	if (!styleLibFileName.IsEmpty())
	{
		int32 itemSelected = inPopup->GetSelected();

		InterfacePtr<IStringListControlData> iStringList(inPopup, IID_ISTRINGLISTCONTROLDATA);

		int32 numItems = iStringList->Length();

		InterfacePtr<IAppearanceSuite> appSuite( FormFieldUIUtils::QueryAppearanceSuite() );

		if (appSuite)
		{
			int32 noneItemNum = supportsNone ? numItems-1 : 99999;
			int32 customItemNum = supportsNone ? numItems-2 : numItems-1;
			if (itemSelected == noneItemNum)
			{
				appSuite->RemoveAppearances();
			}
			else if (itemSelected == customItemNum)
			{
			}
			else
			{
				InterfacePtr<ILibrary> assetLib( QueryStyleLibByName(styleLibFileName) ); 
						
				if (assetLib && itemSelected < assetLib->Length())
				{
					appSuite->SetAppearanceStyle(assetLib, itemSelected);
				}
			}
		}
		
	}
}

//------------------------------------------------------------------------

IAppearanceSuite* FormFieldUIUtils::QueryAppearanceSuite()
{
	return  SelectionUtils::QuerySuite<IAppearanceSuite>();
}

//------------------------------------------------------------------------

IFormFieldSuite* FormFieldUIUtils::QueryFormSuite()
{
	return  SelectionUtils::QuerySuite<IFormFieldSuite>();
}

//________________________________________________________________________________________

bool FormFieldUIUtils::SelectionHasContentInAnyState()
{
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );
	return iAppearanceSuite && iAppearanceSuite->SelectionHasContentInAnyState();
}

//________________________________________________________________________________________

bool FormFieldUIUtils::SelectionHasContentInActiveState()
{
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );
	return iAppearanceSuite && iAppearanceSuite->SelectionHasContentInActiveState();
}

//________________________________________________________________________________________

bool FormFieldUIUtils::SelectionHasStates(ClassID inFormFieldType)
{
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );
	return SelectionIsForm(inFormFieldType) && iAppearanceSuite && iAppearanceSuite->NumStates();
}

//________________________________________________________________________________________

bool FormFieldUIUtils::SelectionIsForm(ClassID inFormFieldType)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( QueryFormSuite() );
	return iFormSuite && iFormSuite->IsFieldSelectionOfType(inFormFieldType);
}

//------------------------------------------------------------------------

IFormFieldUIFactory* FormFieldUIUtils::QuerySelectionUIFactory(IFormFieldSuite* inFormSuite)
{
	IFormFieldUIFactory* uifactory = 0;

	if (inFormSuite && (inFormSuite->IsFieldSelection()))
	{
		InterfacePtr<IFormFieldFactory> factory( inFormSuite->QueryFormFieldFactory() );
		if (factory)
		{
			uifactory = InterfacePtr<IFormFieldUIFactory>(factory, ::UseDefaultIID()).forget();
		}

		if (uifactory == 0 && !inFormSuite->IsMixedSelection())
		{
			InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool() );
			if (activeTool)
			{
				ActionID actionID =			activeTool->GetActionID();
				InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());
				int32 numServices = servReg->GetServiceProviderCount(kFormFieldService);
				for (int32 ss = 0; !uifactory && ss < numServices; ss++)
				{
					InterfacePtr<IK2ServiceProvider> servProv( servReg->QueryNthServiceProvider(kFormFieldService, ss));
					InterfacePtr<IFormFieldUIFactory> fieldUI(servProv, ::UseDefaultIID());
					
					if (fieldUI && fieldUI->GetToolActionID() == actionID)
						uifactory = fieldUI.forget();
				}
			}
		}
	}

	return uifactory;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//twright 06/04/2001 This is to indicate when we are updating any controls
//internally, so that we ignore the change messages that come through...

static int32 sObserverBlockDepth = 0;

FormWidgetBlocker::FormWidgetBlocker()
{
	sObserverBlockDepth++;
}

//------------------------------------------------------------------------

FormWidgetBlocker::~FormWidgetBlocker()
{
	sObserverBlockDepth--;
}

//------------------------------------------------------------------------

bool FormWidgetBlocker::Blocked()
{
	return (sObserverBlockDepth > 0);
}


//------------------------------------------------------------------------

ActionEvent FormFieldUIUtils::GetSelectedEvent(const IPMUnknown *relatedWidget)
{
	ActionEvent selectedEvent = -1;
	
	InterfacePtr<IDropDownListController> eventList((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(relatedWidget, kButtonEventChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > eventData(eventList, IID_ILISTCONTROLDATA);
	int32 eventChoiceIndex = eventList->GetSelected();
	if ( eventChoiceIndex >= 0 && eventChoiceIndex < eventData->Length() )
		selectedEvent =  (*eventData)[eventChoiceIndex].second;
		
	return selectedEvent;
}

IUIDData *FormFieldUIUtils::QueryActiveBehavior(void)
{
	InterfacePtr<const IApplication> theApp (GetExecutionContextSession()->QueryApplication ());
	InterfacePtr<const IPanelMgr> panelMgr( theApp->QueryPanelManager() );
      
	if (panelMgr)
	{
		IControlView *panelView = panelMgr->GetVisiblePanel(kAppearanceParentWidgetId);
		
		InterfacePtr<IUIDData> behavior(panelView, UseDefaultIID());
		if ( behavior )
		{
			// If the behavior's database and the active database don't match then reset so they'll sync up.
			// Addresses bug 2509274.
			if ((behavior->GetRef() != UIDRef::gNull) && 
				(behavior->GetItemDataBase() != Utils<ISelectionUtils>()->GetActiveSelection()->GetDataBase()))
			{
				behavior->Set(UIDRef::gNull);
			}
			return behavior.forget();
		}
	}

	return nil;
}

//________________________________________________________________________________________

void FormFieldUIUtils::UpdateShowPreviewWidget( IPanelControlData* inPanelData, ISelectionManager* currentSelection )
{
	IControlView *iShowPreviewButtonView = inPanelData->FindWidget(kShowPreviewButtonWidgetID);
	if (!iShowPreviewButtonView) return;

	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> iActionMgr(theApp->QueryActionManager());

}

PMString FormFieldUIUtils::GetBehaviorName(const UIDRef& behaviorRef)
{
	InterfacePtr<IBehaviorData> data(behaviorRef, UseDefaultIID());

	// Fix bug #1829627 - "incorrect string appears in the Buttons panel Actions pane ("Show/Hide Field" should be "Show/Hide Button")."
	// Cannot change the name stored with the button without writing a converter because the name is stored in the button. So, let's change 
	// the string here before it is displayed in the UI.
	PMString keyStr("$$$/Forms Action/Show/Hide Fields");
	PMString name(data->GetName());
	if ( keyStr == name )
	{
		return PMString("$$$/Menu/Show/Hide Buttons");
	}
	else
	{
		UID targetUID(kInvalidUID);

		// If it is Animation, Sound, Video, or one of the MSO actions then append the target name.
		if (data->GetAction() == kAnimationBehavior)
		{
			InterfacePtr<IAnimationBehaviorData> animationData(data, UseDefaultIID());
			targetUID = animationData->GetTarget();
		}
		else if (data->GetAction() == kMovieBehavior)
		{
			InterfacePtr<IMovieActionData> movieData(data, UseDefaultIID());
			targetUID = movieData->GetMovie();
		}
		else if (data->GetAction() == kSoundBehavior)
		{
			InterfacePtr<ISoundActionData> soundData(data, UseDefaultIID());
			targetUID = soundData->GetSound();
		}
		else if (data->GetAction() == kSwitchToMSOStateBehavior)
		{
			InterfacePtr<IMultiStateObjectBehaviorData> switchToMSO(data, UseDefaultIID());
			targetUID = switchToMSO->GetTarget();
			if (targetUID != kInvalidUID)
			{
				// Append the state name as well. 
				// The state can be invalid if it is deleted from the Layers panel, for example.
				PMString namePlus(name);
				namePlus.Translate();
				namePlus.SetTranslatable(kFalse);

				namePlus.Append(" (");
				namePlus.Append(Utils<Facade::IDynamicTargetsFacade>()->GetTargetName(UIDRef(behaviorRef.GetDataBase(), targetUID)));
				namePlus.Append(": ");
				if (switchToMSO->GetState() != Form::kStateInvalid)
					namePlus.Append(Utils<Facade::IAppearanceItemFacade>()->GetStateName(UIDRef(behaviorRef.GetDataBase(), targetUID), switchToMSO->GetState()));
				namePlus.Append(")");
				return namePlus;
			}
		}
		else if (data->GetAction() == kSwitchToNextMSOStateBehavior)
		{
			InterfacePtr<IMultiStateObjectBehaviorData> switchToNextMSO(data, UseDefaultIID());
			targetUID = switchToNextMSO->GetTarget();
		}
		else if (data->GetAction() == kSwitchToPrevMSOStateBehavior)
		{
			InterfacePtr<IMultiStateObjectBehaviorData> switchToPrevMSO(data, UseDefaultIID());
			targetUID = switchToPrevMSO->GetTarget();
		}

		if (targetUID != kInvalidUID)
		{
			PMString namePlus(name);
			namePlus.Translate();
			namePlus.SetTranslatable(kFalse);

			namePlus.Append(" (");
			namePlus.Append(Utils<Facade::IDynamicTargetsFacade>()->GetTargetName(UIDRef(behaviorRef.GetDataBase(), targetUID)));
			namePlus.Append(")");
			return namePlus;
		}
	}
	
	return data->GetName();
}
