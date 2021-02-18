//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateListBoxObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// Interfaces:
#include "IAppearanceSuite.h"
#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "IListBoxAttributes.h"
#include "IListBoxController.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "IStateData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IViewListBoxControlData.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"

// Includes:
#include "CoreResTypes.h"
#include "CreateObject.h"
#include "FormFieldUIDefs.h"
#include "LocaleSetting.h"
#include "PMString.h"
#include "RsrcSpec.h"
#include "SelectionObserver.h"

// Utility files:
#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "ILayoutUIUtils.h"
#include "IPalettePanelUtils.h"

// ID.h files:
#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "FormFieldID.h"
#include "GraphicStylesID.h"

using namespace FormFieldUIUtils;

//----------------------------------------------------------------------------------------
// Class StateListBoxObserver
//----------------------------------------------------------------------------------------

class StateListBoxObserver : public ActiveSelectionObserver
{
public:
	StateListBoxObserver(IPMUnknown *boss);
	virtual ~StateListBoxObserver();



protected:
	virtual void HandleSelectionChanged (const ISelectionMessage*);
	virtual void HandleSelectionAttributeChanged (const ISelectionMessage*);
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	
private:
	bool DoSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy); //adapted from LayerPanelObserver::Update

	void InitElementView( Form::AppearanceState inState, IControlView* elementView );

	// Methods for updating the panel, called in response to various changes	
	void UpdateWidgets( bool inListWidgets );

	void UpdateStateListWidgets();
	void UpdateButtons();
	void FillInListBoxData();
	void HandleListSelectionChanged();

	bool16 HandleControlChanged( const ClassID& inChange, ISubject* inSubject);
							
	// Methods for dealing with list element widgets.
	void			UpdateState(Form::AppearanceState inState, int32 inListIndex, bool16 bFillingList);
	bool16			ReuseItemWidget(Form::AppearanceState inState, 
									IViewListBoxControlData* listData,
									const int32& listIndex, 
									IControlView* view);
	IControlView*	CreateItemWidget(Form::AppearanceState inState);

	bool SelectionHasStates();
	bool SelectionIsForm();

	bool	 fListWidgetsAttached;
	bool	 fFormWidgetsAttached;
};


CREATE_PMINTERFACE(StateListBoxObserver, kStateListBoxObserverImpl)

//----------------------------------------------------------------------------------------
// StateListBoxObserver constructor 
//----------------------------------------------------------------------------------------

StateListBoxObserver::StateListBoxObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_IOBSERVER),
	fListWidgetsAttached(false),
	fFormWidgetsAttached(false)
{
	
}


//----------------------------------------------------------------------------------------
// StateListBoxObserver::~StateListBoxObserver: 
//----------------------------------------------------------------------------------------

StateListBoxObserver::~StateListBoxObserver()
{
}

//________________________________________________________________________________________

IPanelControlData *QueryRootPanelData(IWidgetParent* parentHolder)
{
	InterfacePtr<IWidgetParent> gpParentHolder((IWidgetParent*) parentHolder->QueryParentFor(IID_IWIDGETPARENT));
	if ( gpParentHolder )
	{
		//InterfacePtr<IWidgetParent> rootParentHolder((IWidgetParent*) gpParentHolder->QueryParentFor(IID_IWIDGETPARENT));
		//if ( rootParentHolder )
		//	return (IPanelControlData*) rootParentHolder->QueryParentFor(IID_IPANELCONTROLDATA);
		//else
			return (IPanelControlData*) gpParentHolder->QueryParentFor(IID_IPANELCONTROLDATA);
	}
	else
		return (IPanelControlData*) parentHolder->QueryParentFor(IID_IPANELCONTROLDATA);
}


//________________________________________________________________________________________

bool StateListBoxObserver::SelectionHasStates()
{
	if (!fCurrentSelection || ! fCurrentSelection->IsInterfaceEnabled (IID_IFORMFIELDSUITE) )
		return false;

	return (FormFieldUIUtils::SelectionHasStates(kPushButtonItemBoss) || 
			FormFieldUIUtils::SelectionHasStates(kCheckBoxItemBoss) ||
			FormFieldUIUtils::SelectionHasStates(kRadioButtonItemBoss) );
}

//________________________________________________________________________________________

bool StateListBoxObserver::SelectionIsForm()
{
	if (!fCurrentSelection || !fCurrentSelection->IsInterfaceEnabled (IID_IFORMFIELDSUITE) )
		return false;

	return ( FormFieldUIUtils::SelectionIsForm(kPushButtonItemBoss) ||
			 FormFieldUIUtils::SelectionIsForm(kCheckBoxItemBoss) ||
			 FormFieldUIUtils::SelectionIsForm(kRadioButtonItemBoss));
}

//________________________________________________________________________________________
//tw  Reponds to  IID_SELECTION_MESSAGE, ISelectionMessage::kSelectionChanged

void StateListBoxObserver::HandleSelectionChanged(const ISelectionMessage* inSelMsg)
{
	ActiveSelectionObserver::HandleSelectionChanged(inSelMsg);

	//Attach/detach widgets appropriate for the new selection.

	bool isForm = SelectionIsForm();
	bool hasStates = isForm && SelectionHasStates();

	UpdateWidgets( true );
}

//________________________________________________________________________________________
//tw  Reponds to  IID_SELECTION_MESSAGE, ISelectionMessage::kSelectionAttributeChanged

void StateListBoxObserver::HandleSelectionAttributeChanged( const ISelectionMessage*	iSelectionMsg )
{
	//Update widgets that correspond to the change...

	bool wasStateChange = iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE);
	bool wasFormAttrChanged = iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IGRAPHICATTRIBUTESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IFORMFIELDSUITE);

	if (wasStateChange || wasFormAttrChanged)
	{
		bool isForm = SelectionIsForm();
		bool hasStates = isForm && SelectionHasStates();

		bool oldListWidgetsAttached = fListWidgetsAttached;
	}

	UpdateWidgets( true );
}

//________________________________________________________________________________________
//tw

void StateListBoxObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	if ( !DoSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage) )
	
		ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::DoSelectionUpdate: (was Update - tw)
//----------------------------------------------------------------------------------------

bool StateListBoxObserver::DoSelectionUpdate(const ClassID& inChange, ISubject* inSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

//	Trace("got message %x\n",inChange);
	
	// Check if the view is active before handling this update
	// The reason we are checking this is because multiple StateListBoxObservers are being created
	// for each thumbnail size.  This could result in multiple calls to this routine for just one
	// single event.  See Vantive # 616089.
	InterfacePtr<IControlView> view( this, IID_ICONTROLVIEW );
	if ( ! view->IsVisible() )
		return true;

	//if (FormWidgetBlocker::Blocked())
	//	return false;

	//FormWidgetBlocker blocker;

	bool handled = true;

	ICommand* cmd = (ICommand*)changedBy;

	// The active layer can change when multiple items are selected and the user
	// clicks on of them. Technically, the kListSelectionChangedByUserMessage does not happen,
	// but kMasterItemChangedMessage does. Watch for it and treat it just like the
	// user selected a new active layer.
	
	if (inChange == kListSelectionChangedByUserMessage || 
		inChange == kListSelectionChangedMessage ||
		inChange == kMasterItemChangedMessage)
	{
		HandleListSelectionChanged();
	}

	// When a drag starts we get this message, just update the buttons, don't change the active layer.
	else if (inChange == kListSelectionChangedByUserDragMessage)
	{
		//this->UpdateButtons();
	}
	else {
		return HandleControlChanged(inChange, inSubject); //Handle any other control changed (name, visible, etc.)
	}
	
	return handled;
}

//----------------------------------------------------------------------------------------
//Handle any other control changed (name, visible, etc.)

bool16 StateListBoxObserver::HandleControlChanged( const ClassID& inChange, ISubject* inSubject)
{
	//Blocking handled by caller (DoSelectionUpdate)
	
	//if (FormWidgetBlocker::Blocked())
	//	return;

	bool16 handled = kFalse;

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );
	
	if ( iFormSuite && iFormSuite->IsFieldSelectionOfType(kPushButtonItemBoss) &&
		 (	inChange == kPopupChangeStateMessage ||
			inChange == kTextChangeStateMessage || 
			inChange == kFalseStateMessage ||
//			inChange == kEditBoxGiveUpKeyFocusMessage ||
			inChange == kTrueStateMessage ||
			inChange == kListSelectionChangedMessage )
		)
	{

		InterfacePtr<IControlView> iView(inSubject, IID_ICONTROLVIEW);
		if (iView == 0)
			return kFalse;
			
		WidgetID wid = iView->GetWidgetID();
		handled = kTrue;
	
		//SPAM twright 03/07/2001 Using same Observer for multiple panels for now.  Check for existence of
		//widget to see which panel we have...

		switch( wid.Get() )
		{			
			case kStateListElementEyeballWidgetID:
				break;

			case kButtonEventChoicesWidgetID:
				break;

			case kBehaviorChoicesWidgetID:
			{
				break;
			}
			
			default:
				handled = kFalse;
				break;
		}
	}

	return handled;
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::FillInListBoxData: 
//----------------------------------------------------------------------------------------

void StateListBoxObserver::FillInListBoxData()
{
	InterfacePtr<IViewListBoxControlData> listData(this, IID_ILISTCONTROLDATA);
	InterfacePtr<IListBoxAttributes> listAttributes(listData, IID_ILISTBOXATTRIBUTES);
	InterfacePtr<IListBoxController> listCntl(listData, IID_ILISTBOXCONTROLLER);

	listAttributes->MuteDrawing(kTrue);
	bool selHasStates = SelectionHasStates();
	bool showStates(selHasStates);
	
	InterfacePtr<IFormFieldSuite> iFormSuite(FormFieldUIUtils::QueryFormSuite());
	if ( !selHasStates )
	{		
		showStates = iFormSuite && ( iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss) ||
			iFormSuite->CanCreateFieldFromSelection(kCheckBoxItemBoss) || iFormSuite->CanCreateFieldFromSelection(kRadioButtonItemBoss));
	}
	
	int32 selectedStateIndex = -1;
	if ( showStates )
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite( (IAppearanceSuite*)QueryAbstractSelection(IID_IAPPEARANCESUITE) );

		Form::AppearanceState activeState = Form::kStateInvalid;

		if ( selHasStates )
			activeState = iAppearanceSuite->GetActiveState();

		// update the states according to the selection everytime.
		listData->Clear(kFalse, kFalse);
		InterfacePtr<IControlView> view(listData, IID_ICONTROLVIEW);
		view->Invalidate();

		int32 nStates = 3;	// Normal, Rollover, Down. 
		int32 stateIndex = 0;

		int32 maxListEntryIndex = listData->Length() - 1;	// 0 based index of last entry in the layer panel

		// if this is not a check box or radio button, proceed as normal..
		if(!(iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) || iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss)))
		{
			// iterate over the states and add a list entry for each one
			for (; stateIndex < nStates; stateIndex++)
			{			
				Form::AppearanceState state = Form::kStateNormal;

				switch (stateIndex) {
				case 1:
					state = Form::kStateOver;
					break;
				case 2:
					state = Form::kStateDown;
					break;
				default:
					break;
				}

				UpdateState(state, stateIndex, kTrue);

				if ( state != Form::kStateInvalid )
				{
					// Tag the active layer as selected (and the rest as deselected)
					// Make sure the master item is up to date.
					if (activeState == state)
					{
						listCntl->Select(stateIndex, kTrue, kFalse);
						selectedStateIndex = stateIndex;
					}
					else if (listCntl->IsSelected(stateIndex))
					{
						listCntl->Deselect(stateIndex, kTrue, kFalse);
					}
				}
				else if (listCntl->IsSelected(stateIndex))
				{
					listCntl->Deselect(stateIndex, kTrue, kFalse);
				}
			}			
		}
		else 
		{
			nStates = 6;
			int32 initialState = 3;			

			// iterate over the states and add a list entry for each one
			for (; stateIndex < nStates; stateIndex++, initialState++)
			{			
				Form::AppearanceState state = Form::kStateNormalOn;

				switch (initialState) {
				case 3:
					state = Form::kStateNormalOn;
					break;
				case 4:
					state = Form::kStateNormalOff;
					break;
				case 5:
					state = Form::kStateOverOn;
					break;
				case 6:
					state = Form::kStateOverOff;
					break;
				case 7:
					state = Form::kStateDownOn;
					break;
				case 8:
					state = Form::kStateDownOff;
					break;
				default:
					break;
				}

				UpdateState(state, stateIndex, kTrue);

				if ( state != Form::kStateInvalid )
				{
					// Tag the active layer as selected (and the rest as deselected)
					// Make sure the master item is up to date.
					if (activeState == state)
					{
						listCntl->Select(stateIndex, kTrue, kFalse);
						selectedStateIndex = stateIndex;
					}
					else if (listCntl->IsSelected(stateIndex))
					{
						listCntl->Deselect(stateIndex, kTrue, kFalse);
					}
				}
				else if (listCntl->IsSelected(stateIndex))
				{
					listCntl->Deselect(stateIndex, kTrue, kFalse);
				}
			}
		}
	}
	else
	{
		listData->Clear(kFalse, kFalse);
		InterfacePtr<IControlView> view(listData, IID_ICONTROLVIEW);
		view->Invalidate();
	}

	listAttributes->MuteDrawing(kFalse);

	if(selectedStateIndex != -1)
	{
		int32 firstVisibleItem = listCntl->GetFirstVisibleItem();
		int32 maxVisibleItems = listCntl->GetMaximumVisibleItems();
		bool16 doScroll = !(selectedStateIndex >= firstVisibleItem && selectedStateIndex < firstVisibleItem + maxVisibleItems) ;
		if(doScroll)
			listCntl->ScrollItemIntoView(selectedStateIndex);
	}
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::UpdateWidgets: 
//----------------------------------------------------------------------------------------

void StateListBoxObserver::UpdateWidgets(bool inListWidgets)
{
	if (inListWidgets)
		UpdateStateListWidgets();
}

//----------------------------------------------------------------------------------------

void StateListBoxObserver::UpdateStateListWidgets()
{
	FillInListBoxData();
	UpdateButtons();
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::UpdateButtons:
//		After filling in the listbox due to a document switch, z-order change, layer
//		deletion, etc, trigger the DeleteLayerButtonObserver
//		to react by sending a list selection changed message.
//----------------------------------------------------------------------------------------

void StateListBoxObserver::UpdateButtons()
{
	WidgetID listBoxID = Utils<IPalettePanelUtils>()->GetCurrentListBoxID(kAppearanceParentWidgetId);

	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	// IDType ISSUE: For this call to Change(), we need to move the WidgetID from
	// the first parameter (which is a ClassID) to the third parameter.
	// Something like this:
	//		panelSubject->Change( 1, IID_ILISTCONTROLDATA, listBoxID.Get() );
	// This will require changes to attached observers so they correctly 
	// use the parameters. Too risky at the moment.
	//
	

	//New/delete buttons observe this change and enable/disable based on changes to the list.
	
	if (subject)
		subject->Change( listBoxID.Get(), IID_ILISTCONTROLDATA, this );
		
		
}

//----------------------------------------------------------------------------------------

void StateListBoxObserver::HandleListSelectionChanged() //was SelectionChanged
{
	InterfacePtr<IControlView> frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
	IDocument * frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	
	if (frontView == nil || frontDoc == nil)
		return;
	
	InterfacePtr<IViewListBoxControlData> listData(this, IID_ILISTCONTROLDATA);
	InterfacePtr<IListBoxController> listCntl(this, IID_ILISTBOXCONTROLLER);

	int32 selectedIndex = listCntl->GetSelected();
	
	if (selectedIndex >= 0 && (selectedIndex < listData->Length()))
	{
		InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
		if(iFormSuite && !(iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) ||
		  iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss)))
		{
			InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );

			IControlView* view = (*listData)[selectedIndex];
			InterfacePtr<IStateData>	listElementData(view, IID_ISTATEDATA);
			Form::AppearanceState	state = listElementData->GetState();

			if ( !iAppearanceSuite->HasAppearance(state) )
			{
				if (iAppearanceSuite->HasAppearance(state))
				{
					//iAppearanceSuite->DeleteState( state );
					// toggle the state
					Form::Appearance appearance;
					if ( iAppearanceSuite->GetAppearance(state, &appearance) )
					{
						appearance.fEnabled = !appearance.fEnabled;
						iAppearanceSuite->SetAppearance(state, state, appearance);
					}
				}
				else if ( iAppearanceSuite->CanAddState(state) )
				{
					// Add the state
					ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
					if (iAppearanceSuite->NewState(state) == kSuccess)
					{
						if (iAppearanceSuite->SetActiveState(state) == kSuccess)
							iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kPushButtonItemBoss);
					}
					CmdUtils::EndCommandSequence(cmdSeq);
				}
			}
			else
			{
				iAppearanceSuite->SetActiveState(state);
				iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kPushButtonItemBoss);
				UpdateButtons();
			}
		}
		else if(iFormSuite && (iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) ||
		  iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss)))
		{
			InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );

			ClassID selectedItemClass = iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) ? kCheckBoxItemBoss : kRadioButtonItemBoss;
			IControlView* view = (*listData)[selectedIndex];
			InterfacePtr<IStateData>	listElementData(view, IID_ISTATEDATA);
			Form::AppearanceState	state = listElementData->GetState();
			if ( !iAppearanceSuite->HasAppearance(state) )
			{
				if ( iAppearanceSuite->CanAddState(state) )
				{
					// Add the state
					ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

					if ( state == Form::kStateOverOn || state == Form::kStateOverOff )
					{
						// Create both the over off and on states
						iAppearanceSuite->SetActiveState(Form::kStateNormalOff);
						if (iAppearanceSuite->NewState(Form::kStateOverOff) == kSuccess)
						{
							iAppearanceSuite->SetActiveState(Form::kStateNormalOn);
							if (iAppearanceSuite->NewState(Form::kStateOverOn) == kSuccess)
							{
								if (iAppearanceSuite->SetActiveState(state) == kSuccess)
									iAppearanceSuite->SelectAssociatedAppearanceItemOfType(selectedItemClass);
							}
						}
					}
					else if ( state == Form::kStateDownOn || state == Form::kStateDownOff )
					{
						// Create both the down off and on states
						iAppearanceSuite->SetActiveState(Form::kStateNormalOff);
						if (iAppearanceSuite->NewState(Form::kStateDownOff) == kSuccess)
						{
							iAppearanceSuite->SetActiveState(Form::kStateNormalOn);
							if (iAppearanceSuite->NewState(Form::kStateDownOn) == kSuccess)
							{
								if (iAppearanceSuite->SetActiveState(state) == kSuccess)
									iAppearanceSuite->SelectAssociatedAppearanceItemOfType(selectedItemClass);
							}
						}
					}

					CmdUtils::EndCommandSequence(cmdSeq);
				}
			}
			else
			{
				iAppearanceSuite->SetActiveState(state);
				iAppearanceSuite->SelectAssociatedAppearanceItemOfType(selectedItemClass);
				UpdateButtons();
			}
		}
	}
}


//----------------------------------------------------------------------------------------
// Attach observers we need when an item with appearance states is selected...

void StateListBoxObserver::AutoAttach()
{
	ActiveSelectionObserver::AutoAttach();

	if (!fFormWidgetsAttached)
	{
		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject != nil)
		{
			InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
			InterfacePtr<IPanelControlData> panelData(QueryRootPanelData(parentHolder));
			InterfacePtr<IObserver> deleteObserver(panelData->FindWidget(kStateDeleteButtonWidgetID), IID_IOBSERVER);
			if (deleteObserver)
				subject->AttachObserver(deleteObserver, IID_ILISTCONTROLDATA);
		}

		fFormWidgetsAttached = true;
	}

	// attach to the list of states
	if ( !fListWidgetsAttached )
	{
		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject != nil)
			subject->AttachObserver(this, IID_ILISTCONTROLDATA); //start watching the state list

		fListWidgetsAttached = kTrue;
	}
	
	UpdateWidgets( true );
}

//----------------------------------------------------------------------------------------
// Detach observers we need when an item with appearance states is selected...

void StateListBoxObserver::AutoDetach()
{
	ActiveSelectionObserver::AutoDetach();

	if (fListWidgetsAttached )
	{
		// ----- Detach from the view.

		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject != nil)
		{
			subject->DetachObserver(this, IID_ILISTCONTROLDATA); //stop watching the state list
		}
				
		fListWidgetsAttached = kFalse;
	}


	if (fFormWidgetsAttached)
	{
		// ----- Detach from the view.

		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject != nil)
		{
			InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
			InterfacePtr<IPanelControlData> panelData(QueryRootPanelData(parentHolder));

			InterfacePtr<IObserver> deleteObserver(panelData->FindWidget(kStateDeleteButtonWidgetID), IID_IOBSERVER);
			if (deleteObserver)
				subject->DetachObserver(deleteObserver, IID_ILISTCONTROLDATA);
		}

		fFormWidgetsAttached = false;
	}

	// force everything to be released
	InterfacePtr<IViewListBoxControlData> listData(this, IID_ILISTCONTROLDATA);
	listData->Clear(kFalse, kFalse);
}


//----------------------------------------------------------------------------------------
// StateListBoxObserver::InitElementView: 
//----------------------------------------------------------------------------------------

void StateListBoxObserver::InitElementView( Form::AppearanceState inState, IControlView* inElementView )
{
	// Initialize the values for the eyeball and pencil icons
	InterfacePtr<IPanelControlData> panelData(inElementView, IID_IPANELCONTROLDATA);
	IControlView* eyeball = panelData->FindWidget(kStateListElementEyeballWidgetID);
	
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	if (!iAppearanceSuite || !iFormSuite)
		return;
		
	//Normal state can't be disabled, so hide the enabling control (this should be
	//changed to a checkbox...)
	
	if ( (iFormSuite->IsFieldSelectionOfType(kPushButtonItemBoss) || iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) 
		|| iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss) ) && iAppearanceSuite->HasStates() )
	{
		if ( Utils<IFormFieldUtils>()->IsNormalState(inState))
		{	
			eyeball->SetRsrcID( kStateEnabledIcon );
			eyeball->Disable();
		}
		else
		{
			eyeball->Enable();
			Form::Appearance appearance;
			if ( iAppearanceSuite->HasAppearance(inState) )
				iAppearanceSuite->GetAppearance(inState, &appearance);
			else
				appearance.fEnabled = false;
			eyeball->SetRsrcID( appearance.fEnabled ? kStateEnabledIcon : kStateDisabledIcon);
		}
	}
	else
	{
		if ( Utils<IFormFieldUtils>()->IsNormalState(inState))	
		{
			eyeball->Enable();
			eyeball->SetRsrcID(kStateDisabledIcon);
		}
		else
		{
			eyeball->Disable();
			eyeball->SetRsrcID(kStateDisabledIcon);
		}
	}
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::UpdateState: 
//----------------------------------------------------------------------------------------

void StateListBoxObserver::UpdateState( Form::AppearanceState inState, int32 inListIndex, bool16 inFillingList) //was AddState
{
	InterfacePtr<IViewListBoxControlData> listData(this,  UseDefaultIID());
	
	InterfacePtr<IPanelControlData> layerPanelData(this, IID_IPANELCONTROLDATA);
	int32 listDataLength = listData->Length();

	// If entirely filling the list, might be able to reuse some widgets.
	int32 maxListEntryIndex = listDataLength - 1;	// 0 based index of last entry in the layer panel

	if (inFillingList && inListIndex <= maxListEntryIndex)
	{
		IControlView * nthWidget = (*listData)[inListIndex];
		// If the item has changed, invalidate it, otherwise, don't bother
		if (ReuseItemWidget(inState, listData, inListIndex, nthWidget))
		{			
			nthWidget->Invalidate();
		
			// Set up initial values for eye, pencil, proxy
			InitElementView(inState, nthWidget);
		}
	}
	else 
	{
		InterfacePtr<IControlView> view(CreateItemWidget(inState));
		listData->Add(view, inListIndex == 0 ? IViewListBoxControlData::kBeginning : inListIndex, kFalse, kFalse);

		// Set up initial values for eye, pencil, proxy
		InitElementView(inState, view);
	}
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::ReuseItemWidget: 
//----------------------------------------------------------------------------------------

bool16 StateListBoxObserver::ReuseItemWidget(
	Form::AppearanceState inState, 
	IViewListBoxControlData* inListData,
	const int32& inListIndex,
	IControlView* inView)
{
	return kTrue;
	
	bool16	bChanged = kFalse;

	// ----- Init the layer element widget
	InterfacePtr<IStateData> data(inView, IID_ISTATEDATA);
	Form::AppearanceState	newState = inState;
	const	Form::AppearanceState	currentState = data->GetState();
	
	IControlView	*currentView = (*inListData)[inListIndex];

	InterfacePtr<IPanelControlData> panelData(inView, IID_IPANELCONTROLDATA);
	IControlView* eyeball = panelData->FindWidget(kStateListElementEyeballWidgetID);
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );
	if (!iAppearanceSuite)
		return kFalse;
	
	Form::Appearance appearance;
	bool bEnabled = iAppearanceSuite->HasAppearance(inState) && iAppearanceSuite->GetAppearance(inState, &appearance) && appearance.fEnabled;
	bool eyeballMatches = ((eyeball->GetRsrcID() == kStateEnabledIcon) == bEnabled);

	if ((newState != currentState) || (currentView != inView) || !eyeballMatches )
	{
		data->Set(newState);
		inListData->Replace(inView, inListIndex, kFalse, kFalse);
		bChanged = kTrue;
	}
	else if ( currentView && !currentView->GetVisibleState() )
		bChanged = kTrue;
	
	return(bChanged);
}

//----------------------------------------------------------------------------------------
// StateListBoxObserver::CreateItemWidget: 
//----------------------------------------------------------------------------------------

IControlView* StateListBoxObserver::CreateItemWidget( Form::AppearanceState inState )
{
	// ----- Create the layer list element widget and its children
	InterfacePtr<IListBoxAttributes> listAttr(this, IID_ILISTBOXATTRIBUTES);
	RsrcID rsrcID = listAttr->GetItemWidgetRsrcID();
	if (rsrcID == 0)
		rsrcID = kStateListMediumElementRsrcID;

	RsrcSpec	myResSpec(LocaleSetting::GetLocale(), kFormFieldUIPluginID, kViewRsrcType, rsrcID);
	IControlView* view = (IControlView*) ::CreateObject(::GetDataBase(this), myResSpec, IID_ICONTROLVIEW);
	
	// ----- Init the layer list element widget
	InterfacePtr<IStateData> data(view, IID_ISTATEDATA);
	data->Set(inState);

	// Set the state name here. 
	PMString stateName;
	switch (inState)
	{
		case Form::kStateNormal:
			stateName = "$$$/Panel/Normal";
			break;
		case Form::kStateOver:
			stateName = "$$$/Panel/Over";
			break;
		case Form::kStateDown:
			stateName = "$$$/Panel/Down";
			break;
		case Form::kStateNormalOff:
			stateName = "$$$/Panel/Off";
			break;
		case Form::kStateNormalOn:
			stateName = "$$$/Panel/On";
			break;
		case Form::kStateOverOff:
			stateName = "$$$/Panel/RolloverOff";
			break;
		case Form::kStateOverOn:
			stateName = "$$$/Panel/RolloverOn";
			break;
		case Form::kStateDownOff:
			stateName = "$$$/Panel/DowmOff";
			break;
		case Form::kStateDownOn:
			stateName = "$$$/Panel/DownOn";
			break;		
		default:
			{
				InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
				stateName = iAppearanceSuite->GetStateName(inState);
				break;
			}
	}
	stateName.Translate();

	InterfacePtr<IControlView> nameWidget((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(view, kStateListElementNameWidgetID, IID_ICONTROLVIEW));
	InterfacePtr<ITextControlData> stateNameData(nameWidget, UseDefaultIID());
	stateNameData->SetString(stateName);

	return view;
}


