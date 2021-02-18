//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelObserver.cpp $
//  
//  Owner: Michele Stutzman
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
//  Comments: Updates list in appearance panel based on changes to the current
//  selection's IAppearanceList.  Also hooks up buttons to listen to
//  changes in the list, and watches for user interaction with the list
//  (handling selection, eyeball clicking etc.)
//  This is currently attached to the list, but it observes things outside the
//  list.  It probably should be moved to the palette boss (SPAM TODO)
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IApplication.h"
#include "IAppearanceSuite.h"
#include "IActionManager.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "IGraphicAttributeSuite.h"
#include "IHierarchy.h"
#include "IInLineEditController.h"
#include "IPanelControlData.h"
#include "ISelectionDataSuite.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeViewMgr.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "FormFieldUIDefs.h"
#include "SelectionObserver.h"
#include "UIDList.h"
#include "KeyStates.h"
#include "DynamicDocumentsUIID.h"
#include "CAlert.h"

// ----- Utility files -----

#include "AttributesUtils.h"
#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "MSOPanelUtils.h"
#include "SelectionUtils.h"
#include "StringUtils.h"
#include "UserInterfaceUtils.h"
#include "ErrorUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"
#include "FormFieldID.h"
#include "GroupID.h"

using namespace UserInterfaceUtils;
using namespace FormFieldUIUtils;

class MSOPanelObserver : public ActiveSelectionObserver
{
public:
	MSOPanelObserver(IPMUnknown *boss);
	virtual ~MSOPanelObserver();

protected:
	virtual void AutoAttach();
	virtual void AutoDetach();

	virtual void HandleSelectionChanged(const ISelectionMessage*);
	virtual void HandleSelectionAttributeChanged(const ISelectionMessage*);
	virtual void HandleSelectionUpdate(const ClassID& inBossClassID, ISubject* inSubject, const PMIID& inProtocol, void* inMessage);
	
private:
	bool DoSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy); //adapted from LayerPanelObserver::Update

	// Methods for updating the panel, called in response to various changes	
	void UpdateWidgets( bool inFormWidgets); //adapted from LayerPanelObserver::UpdatePanel
	void UpdateTreeViewList();

	bool16 HandleControlChanged( const ClassID& inChange, ISubject* inSubject);

	void UpdateMSONameWidget(IPanelControlData* panelData);
	void UpdateMSOStatusWidget(IPanelControlData* panelData, bool enable);
	void UpdateMSOSelectionWidget(IPanelControlData* panelData, bool16 hasStates);
	void UpdateAddToPasteIntoButtonWidget(IPanelControlData* panelData, bool enable);
					
	void AttachDetachControl(WidgetID inWID, PMIID inIID, bool32 inAttach);

	bool SelectionHasStates();
	bool SelectionIsForm();
	bool SelectionIsMSO();

	Form::AppearanceState fSelectedState;
};

// =============================================================================
// *** MSOPanelObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelObserver, kMSOPanelObserverImpl)

MSOPanelObserver::MSOPanelObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_IOBSERVER),
	fSelectedState(Form::kStateInvalid)
{
} // end constructor


MSOPanelObserver::~MSOPanelObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void MSOPanelObserver::AutoAttach()
{
	ActiveSelectionObserver::AutoAttach();
	AttachDetachControl(kMSONameEditWidgetID, IID_ITEXTCONTROLDATA, true);				
	AttachDetachControl(kShowPreviewButtonWidgetID, IID_ITRISTATECONTROLDATA, true);

	UpdateTreeViewList();
	UpdateWidgets(true);
} // end AutoAttach()

// -----------------------------------------------------------------------------

void MSOPanelObserver::AutoDetach()
{
	ActiveSelectionObserver::AutoDetach();
	AttachDetachControl(kMSONameEditWidgetID, IID_ITEXTCONTROLDATA, false);	
	AttachDetachControl(kShowPreviewButtonWidgetID, IID_ITRISTATECONTROLDATA, false);
} // end AutoDetach()

//----------------------------------------------------------------------------------------

void MSOPanelObserver::AttachDetachControl(WidgetID inWID, PMIID inIID, bool32 inAttach)
{
	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
	IControlView* iView = panelData->FindWidget(inWID);
	ASSERT_MSG(iView != nil, "FormFieldUIWidgetsObserver::AttachDetachControl: Can't find widget ID!");
	if (iView == nil)
		return;
		
	InterfacePtr<ISubject> iSubject(iView, IID_ISUBJECT);
	if (inAttach) 
	{
		ASSERT_MSG(!iSubject->IsAttached(this, inIID), "AppearancePanelObserver::AttachDetachControl - Control already attached");
		iSubject->AttachObserver(this, inIID);
	}
	else
		iSubject->DetachObserver(this, inIID);
}

// -----------------------------------------------------------------------------

void MSOPanelObserver::UpdateMSONameWidget(IPanelControlData* panelData)
{
	IControlView* view = panelData->FindWidget(kMSONameEditWidgetID);
	InterfacePtr<IAppearanceSuite> iAppearanceSuite(QueryAppearanceSuite());

	PMString strValue = "";
	bool enable = false;

	InterfacePtr<ITextControlData> data(view, UseDefaultIID());
	
	InterfacePtr<IFormFieldSuite> iFormSuite(FormFieldUIUtils::QueryFormSuite());
	if (iAppearanceSuite && iFormSuite && iFormSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
	{
		InterfacePtr<ITextControlData> iEdit(view, UseDefaultIID());
		iAppearanceSuite->GetName(strValue);
		enable = true;
	}
	else if (iAppearanceSuite && iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))
	{
		InterfacePtr<ITextControlData> iEdit(view, UseDefaultIID());
		iAppearanceSuite->GetNameOfOnlyItemOfClass(strValue, kMultiStateObjectItemBoss);
		enable = false;
	}
		
	view->Enable(enable);
	data->SetString(strValue);
} // end UpdateMSONameWidget()

static void ShowHideMixedSelectionWidget(IControlView* mixedSelectionView, IControlView* treeView, bool16 bShowMixedSelectionView)
{
	if (!mixedSelectionView || !treeView)
		return;
	if (bShowMixedSelectionView)
	{
		mixedSelectionView->ShowView();
		treeView->HideView();
	}
	else
	{
		mixedSelectionView->HideView();
		treeView->ShowView();
	}
}

// -----------------------------------------------------------------------------

void MSOPanelObserver::UpdateMSOStatusWidget(IPanelControlData* panelData, bool enable)
{
	IControlView* view = panelData->FindWidget(kMSOPanelStatusAreaWidgetID);
	InterfacePtr<ITextControlData> data(view, UseDefaultIID());
	if (!data) return;

	IControlView* mixedSelectionView = panelData->FindWidget(kMSOMixedStaticWidgetID);
	IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
	InterfacePtr<ITextControlData> mixedSelectionData(mixedSelectionView, UseDefaultIID());
	if (!mixedSelectionData) return;

	if (enable)
	{
		// It's a MSO - hide the mixed selection static text.
		ShowHideMixedSelectionWidget(mixedSelectionView, treeView, kFalse);

		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite(static_cast<ISelectionDataSuite*>(QueryAbstractSelection(IID_ISELECTIONDATASUITE)));
		if (iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() > 0)
		{
			// Set a MSO is selected for the panel
			InterfacePtr<IBoolData> msoSelectedData(this, UseDefaultIID());
			msoSelectedData->Set(kTrue);

			InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			if (appearanceSuite)
			{
				if (appearanceSuite->IsAppearanceItemOfTypeSelected(kMultiStateObjectItemBoss))
				{
					data->SetString("$$$/Panel/MSOPanel/StatusMSOSelected");
				}
				else if (appearanceSuite->IsActiveStateOfAppearanceItemOfTypeSelected(kMultiStateObjectItemBoss))
				{
					data->SetString("$$$/Panel/MSOPanel/StatusStateSelected");
				}
				else
					data->SetString("$$$/Panel/MSOPanel/StatusStateContentSelected");
			}
		}
		else
			data->SetString("");
	}
	else
	{
		// It's not a MSO, if more than one selected show the mixed selection static text.
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite(static_cast<ISelectionDataSuite*>(QueryAbstractSelection(IID_ISELECTIONDATASUITE)));
		if (iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() > 1)
		{
			if (!mixedSelectionView->IsVisible())
			{
				bool16 bShowMixedSelectionView = kFalse;
				InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
				if (iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kMultiStateObjectItemBoss))
				{
					mixedSelectionData->SetString("$$$/Panel/MSOPanel/MixedSelection");
					bShowMixedSelectionView = kTrue;
				}
				else
				{
					InterfacePtr<IAppearanceSuite> iAppearanceSuite(QueryAppearanceSuite());
					if (iAppearanceSuite && iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))
					{
						PMString strValue("$$$/Panel/MSOPanel/MSOAndMixedSelection", PMString::kTranslateDuringCall);

						PMString nameStr = "";
						iAppearanceSuite->GetNameOfOnlyItemOfClass(nameStr, kMultiStateObjectItemBoss);

						::ReplaceStringParameters(&strValue, nameStr, nameStr);

						mixedSelectionData->SetString(strValue);
						bShowMixedSelectionView = kTrue;
					}
				}
				ShowHideMixedSelectionWidget(mixedSelectionView, treeView, bShowMixedSelectionView);

			}
		}
		else
			ShowHideMixedSelectionWidget(mixedSelectionView, treeView, kFalse);

		data->SetString("");
	}
}

// -----------------------------------------------------------------------------

void MSOPanelObserver::UpdateMSOSelectionWidget(IPanelControlData* panelData, bool16 hasStates)
{
	IControlView* msoSelectionIconView = panelData->FindWidget(kMSOSelectionIconWidgetID);
	if (!msoSelectionIconView) return;

	InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (appearanceSuite && appearanceSuite->IsAppearanceItemOfTypeSelected(kMultiStateObjectItemBoss))
	{
		// Swap the appropriate MSO is selected PNG icon
		if (msoSelectionIconView->GetRsrcID() != kMSOIsSelectedIconRsrcID)
		{
			msoSelectionIconView->SetRsrcID(kMSOIsSelectedIconRsrcID);
			msoSelectionIconView->Invalidate();
		}
		if (!msoSelectionIconView->IsVisible())
			msoSelectionIconView->ShowView();
	}
	else if (hasStates)
	{
		// Swap the appropriate MSO is not selected PNG icon
		if (msoSelectionIconView->GetRsrcID() != kMSOIsNotSelectedIconRsrcID)
		{
			msoSelectionIconView->SetRsrcID(kMSOIsNotSelectedIconRsrcID);
			msoSelectionIconView->Invalidate();
		}
		if (!msoSelectionIconView->IsVisible())
			msoSelectionIconView->ShowView();
	}
	else if (msoSelectionIconView->IsVisible())
		msoSelectionIconView->HideView();

} // end UpdateMSOSelectionWidget()

// -----------------------------------------------------------------------------

void MSOPanelObserver::UpdateAddToPasteIntoButtonWidget(IPanelControlData* panelData, bool enable)
{
	IControlView* pasteIntoButtonView = panelData->FindWidget(kPasteIntoMSOStateButtonWidgetID);
	IControlView* addToButtonView = panelData->FindWidget(kAddToMSOStateButtonWidgetID);

	InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (appearanceSuite && appearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))
	{
		// hide the "paste into" button, show the "add to" button
		pasteIntoButtonView->HideView();
		addToButtonView->ShowView();
	}
	else
	{
		// show the "paste into" button, hide the "add to" button
		pasteIntoButtonView->ShowView();
		addToButtonView->HideView();
	}
}

// -----------------------------------------------------------------------------

bool MSOPanelObserver::SelectionHasStates()
{
	if (!fCurrentSelection || ! fCurrentSelection->IsInterfaceEnabled(IID_IFORMFIELDSUITE))
		return false;

	return FormFieldUIUtils::SelectionHasStates(kMultiStateObjectItemBoss);
} // end SelectionHasStates()

// -----------------------------------------------------------------------------

bool MSOPanelObserver::SelectionIsForm()
{
	if (!fCurrentSelection || !fCurrentSelection->IsInterfaceEnabled (IID_IFORMFIELDSUITE) )
		return false;

	return FormFieldUIUtils::SelectionIsForm(kMultiStateObjectItemBoss);
} // end SelectionIsForm()

// -----------------------------------------------------------------------------

void MSOPanelObserver::HandleSelectionChanged(const ISelectionMessage* inSelMsg)
{
	ActiveSelectionObserver::HandleSelectionChanged(inSelMsg);
	
	UpdateTreeViewList();
	UpdateWidgets(true);
} // end HandleSelectionChanged()

// -----------------------------------------------------------------------------

void MSOPanelObserver::HandleSelectionAttributeChanged( const ISelectionMessage*	iSelectionMsg )
{
	//Update widgets that correspond to the change...

	bool wasStateChange = iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE);
	bool wasFormAttrChanged = iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IGRAPHICATTRIBUTESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IFORMFIELDSUITE);

	if (wasStateChange || wasFormAttrChanged)
	{
		bool isForm = SelectionIsForm();

		bool updateFormWidgets = (isForm && wasFormAttrChanged);
		
		UpdateTreeViewList();
		UpdateWidgets(updateFormWidgets);
	}
} // end HandleSelectionAttributeChanged()

// -----------------------------------------------------------------------------

void MSOPanelObserver::HandleSelectionUpdate(const ClassID&inBossClassID, ISubject* inSubject, const PMIID& inProtocol,	void* inMessage)
{
	if (!HandleControlChanged(inBossClassID, inSubject))
		ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
} // end HandleSelectionUpdate()

// -----------------------------------------------------------------------------

bool16 MSOPanelObserver::HandleControlChanged( const ClassID& inChange, ISubject* inSubject)
{
	if (FormWidgetBlocker::Blocked())
		return false;

	FormWidgetBlocker blocker;

	bool16 handled = kFalse;

	InterfacePtr<IFormFieldSuite> iFormSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<IAppearanceSuite> iAppearanceSuite(QueryAppearanceSuite());
	
	InterfacePtr<IControlView> iView(inSubject, IID_ICONTROLVIEW);
	if (iView == 0)
		return kFalse;
		
	WidgetID wid = iView->GetWidgetID();

	if (iFormSuite && iFormSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) &&	inChange == kTextChangeStateMessage)
	{
		handled = kTrue;
	
		//SPAM twright 03/07/2001 Using same Observer for multiple panels for now.  Check for existence of
		//widget to see which panel we have...

		switch( wid.Get() )
		{							
			case kMSONameEditWidgetID:
			{
				//Make sure we don't set a blank name... #525049
				
				InterfacePtr<ITextControlData> iEdit(inSubject, UseDefaultIID());
				if (!iEdit->GetString().IsEmpty())
				{
					if (iAppearanceSuite) {
						ErrorCode setNameResult = iAppearanceSuite->SetName(iEdit->GetString());
						if (setNameResult != kSuccess) {
							PMString string = ErrorUtils::PMGetErrorString(setNameResult);
							if (!string.IsNull()) {
								ErrorUtils::PMSetGlobalErrorCode(kSuccess);
								CAlert::ErrorAlert(string);
							}
						}
					}
				}
				else
				{
					InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
					UpdateMSONameWidget(panelData);
				}
				break;
			}
			
			case kShowPreviewButtonWidgetID:
				// Show preview even in no selection or non form-field selection cases.
				if (inChange == kTrueStateMessage)
				{
					handled = kTrue;											
					InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
					InterfacePtr<IActionManager> iActionMgr(theApp->QueryActionManager());
					if (iActionMgr)
					{
						// HTML Preview
                        iActionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), kHTMLFXLPreviewActionID);
					}
				}
				break;	

			default:
				handled = kFalse;
				break;
		}
	}	
	else if (wid.Get() == kShowPreviewButtonWidgetID && inChange == kTrueStateMessage)
	{
		handled = kTrue;											
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IActionManager> iActionMgr(theApp->QueryActionManager());
		if (iActionMgr)
		{
			// HTML Preview
			iActionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), kHTMLFXLPreviewActionID);
		}
	}
	return handled;
} // end HandleControlChanged()


// -----------------------------------------------------------------------------

void MSOPanelObserver::UpdateWidgets(bool inFormWidgets)
{
	if (FormWidgetBlocker::Blocked())
		return;

	FormWidgetBlocker blocker;

	// Reset the MSO's selected or not for the panel
	InterfacePtr<IBoolData> msoSelectedData(this, UseDefaultIID());
	msoSelectedData->Set(kFalse);

	InterfacePtr<IFormFieldSuite> iFormSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
	
	if (inFormWidgets)
	{
		// Note: SelectionHasStates will return false for multiple selections. SelectionIsForm will return true if every page item
		// in the selection is a form.
		bool hasStates = SelectionHasStates();
	
		UpdateMSONameWidget(panelData);
		UpdateMSOStatusWidget(panelData, hasStates);
		UpdateMSOSelectionWidget(panelData, hasStates);
		UpdateAddToPasteIntoButtonWidget(panelData, hasStates);
	}
	else
	{
		// This can happen when "Release State to Objects", need to clear out the status area.
		UpdateMSOStatusWidget(panelData, false);
	}
	
	FormFieldUIUtils::UpdateShowPreviewWidget( panelData, fCurrentSelection );

} // end UpdateWidgets()

// -----------------------------------------------------------------------------

void MSOPanelObserver::UpdateTreeViewList()
{
	if (FormWidgetBlocker::Blocked())
		return;

	FormWidgetBlocker blocker;

	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());

	IControlView* inlineEditingView = panelData->FindWidget(kInLineEditEditingWidgetID);
	if (inlineEditingView != nil)
	{
		// this is a new MSO, tree is updated already and have begun inline editing mode
		InterfacePtr<IWidgetParent> parent(inlineEditingView, UseDefaultIID());
		if (parent)
		{
			InterfacePtr<IInLineEditController> inlineEditingController((IInLineEditController *)parent->QueryParentFor (IID_IINLINEEDITCONTROLLER));
			if (inlineEditingController && inlineEditingController->IsBeingEdited())
				return;
		}
	}

	IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
	InterfacePtr<ITreeViewMgr> treeViewMgr(treeView, UseDefaultIID());
	if (treeViewMgr)
		MSOPanelUtils::RebuildTreeViewList(treeViewMgr);
} // end UpdateTreeViewList()
