//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIButtonTriggerToolImpls.cpp $
//  
//  Owner: SusanCL
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Installs trackers used by the zoom plug-in.
//  
//========================================================================================

#include "VCPlugInHeaders.h"


#include "IApplication.h"
#include "IPanelMgr.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ITrackerRegister.h"
#include "ITrackerFactory.h"
#include "IEvent.h"
#include "ILayoutTrackerAccess.h"
#include "ILayoutSelectionSuite.h"
#include "IAnimationFacade.h"
#include "ISelectionUtils.h"
#include "ILayoutUtils.h"
#include "IPageItemTypeUtils.h"
#include "ICursorUtils.h"

//	For hit testing
#include "ISplineState.h"
#include "ILayoutControlData.h"
#include "ILayoutControlViewHelper.h"
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "IMasterSpread.h"
#include "ITOPSplineData.h"
#include "IMainItemTOPData.h"
#include "ITableFrame.h"
#include "ITextFrameColumn.h"
#include "IGeometry.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "ILayoutUIUtils.h"
#include "IDynamicEventTimingFacade.h"
#include "IAnimationUtils.h"
#include "IPalettePanelUtils.h"

#include "ICreateFormFieldCmdData.h"
#include "IUIDData.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IBehaviorList.h"
#include "IBehaviorData.h"
#include "IAnimationBehaviorData.h"
#include "IBehaviorEventData.h"
#include "ICommandFactory.h"
#include "IFormFieldUtils.h"

#include "CPMUnknown.h"
#include "CTracker.h"
#include "CTrackerEventHandler.h"
#include "CToolCursorProvider.h"

#include "LayoutUIID.h"
#include "BehaviorID.h"
#include "FormFieldID.h"
#include "FormFieldUIID.h"
#include "DynamicDocumentsID.h"
#include "DynamicDocumentsUIID.h"

#include "UIDList.h"
#include "CAlert.h"
#include "ErrorUtils.h"
#include "KeyStates.h"
#include "PaletteRefUtils.h"

#include "Trace.h"
//____________________________________________________________________________________
//	This file contains all the implementations for animation button trigger tool/tracker.
//		Tracker register (kAnimationUIButtonTriggerTrackerRegisterImpl)
//		Tracker implementation (kAnimationUIButtonTriggerTrackerImpl)
//		Tracker eventhandler (kAnimationUIButtonTriggerTrackerEHImpl)
//____________________________________________________________________________________
static ILayoutTarget* QueryLayoutTargetHitTest (IControlView* currentView, const PMPoint& where);

//____________________________________________________________________________________
//	ButtonTrigger Tool Trakcer Regsiter
//____________________________________________________________________________________
class AnimationUIButtonTriggerTrackerRegister : public CPMUnknown<ITrackerRegister>
{
public:
	AnimationUIButtonTriggerTrackerRegister(IPMUnknown *boss) : CPMUnknown<ITrackerRegister> (boss) {}

	void Register(ITrackerFactory *factory)
	{
		factory->InstallTracker (kAnimationUIButtonTriggerWidgetBoss, kAnimationUIButtonTriggerWidgetBoss, kAnimationUIButtonTriggerTrackerBoss);
	}
	
};

CREATE_PMINTERFACE (AnimationUIButtonTriggerTrackerRegister, kAnimationUIButtonTriggerTrackerRegisterImpl)

//____________________________________________________________________________________
//	ButtonTrigger Tool Trakcer EventHandler Implementation
//____________________________________________________________________________________
class AnimationUIButtonTriggerTrackerEH : public CTrackerEventHandler 
{
	bool fButtonDnClicked;
public: 
    // ----- Initialization ----- 
     
	AnimationUIButtonTriggerTrackerEH(IPMUnknown *boss) : CTrackerEventHandler(boss), fButtonDnClicked (false) {}
	virtual ~AnimationUIButtonTriggerTrackerEH() {}

	virtual bool16 LButtonDn(IEvent* e)
	{
		fButtonDnClicked = true;
		return CTrackerEventHandler::LButtonDn (e);
	}

	virtual bool16 LButtonUp(IEvent* e)
	{
		if (fButtonDnClicked)
		{
			fButtonDnClicked = false;
			CTrackerEventHandler::LButtonUp (e);

			return kTrue;
		}
		return kFalse;
	}

private:

}; 
CREATE_PMINTERFACE(AnimationUIButtonTriggerTrackerEH, kAnimationUIButtonTriggerTrackerEHImpl) 


//____________________________________________________________________________________
//	ButtonTrigger Tool Trakcer Implementation
//____________________________________________________________________________________
class AnimationUIButtonTriggerTracker : public CTracker
{
	PMPoint fCurrentPoint;
	ILayoutTarget* fTarget;
	UIDList fAnimationTargetList;

public:
	AnimationUIButtonTriggerTracker(IPMUnknown *boss) : CTracker (boss), fTarget (nil) 
	{
		//	Turn off autoscroll
		fWantsToAutoScroll = kFalse;
	}

	virtual ~AnimationUIButtonTriggerTracker () {}

	virtual bool16 BeginTracking(IEvent* theEvent) 
	{ 
		// Button trigger tracker does not want snapping at all.
		if (fSnapTo) 
		{ 
			fSnapTo->SetSnappingEnabled(kFalse); 
		} 

		// Save initial point 
		this->GlobalToPasteboard (theEvent->GlobalWhere(), fCurrentPoint); 
	     
		bool16 result = CTracker::BeginTracking(theEvent); 
		if (result)
		{
			this->ChangeModalCursor (CursorSpec (kCrsrButtonTrigger));
		}

		//	Note that if we ask for IID, the item list returned is a flatten list. 
		//	That means if, for example, it's a group, button, mso, placed graphics, it get flattened so that
		//	the item list contains the children - not what we want.
		InterfacePtr<ISelectionManager> iSelMgr (Utils<ISelectionUtils>()->QueryViewSelectionManager ((IPMUnknown*)fControlView));
		InterfacePtr<ILayoutTrackerAccess> iLayoutTrackerAccess (static_cast<ILayoutTrackerAccess*>(Utils<ISelectionUtils>()->QuerySuite(ILayoutTrackerAccess::kDefaultIID, iSelMgr)));
		UIDList selectedItems = iLayoutTrackerAccess->GetUIDList (this, kStripStandoffs);
		ASSERT (selectedItems.size () >= 1);

		fAnimationTargetList = UIDList (selectedItems.GetDataBase ());
		if (selectedItems.size () == 1)
		{
			UIDRef itemRef;
			IDataBase* iDB = selectedItems.GetDataBase ();
			InterfacePtr<ISplineState> iSplineState (iDB, iDB->GetRootUID (), UseDefaultIID ());

			if (iSplineState == nil || iSplineState->GetMotionPageItem () == UIDRef::gNull ||
				!iDB->IsValidUID (iSplineState->GetMotionPageItem ().GetUID ()))
			{
				itemRef = selectedItems.GetRef (0);
			}
			else
			{
				itemRef = iSplineState->GetMotionOwnerPageItem ();
			}
			ASSERT (Utils<Facade::IAnimationFacade> ()->PageItemHasAnimation (itemRef));
			fAnimationTargetList.push_back (itemRef.GetUID ());
		}
		else
		{
			for (int32 n = 0; n < selectedItems.size (); n++)
			{
				UIDRef itemRef = selectedItems.GetRef (n);
				if (Utils<Facade::IAnimationFacade> ()->PageItemHasAnimation (itemRef))
				{
					fAnimationTargetList.push_back (itemRef.GetUID ());
				}
			}
		}
     
		return result; 
	} 

	virtual void ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove) 
	{
		if (mouseDidMove) 
		{ 
			// Make sure we don't overlap columns 
			PBPMPoint constrainedWhere (where);     	             
			fCurrentPoint = constrainedWhere; 

			// Identify the page item hit
			if (fTarget) fTarget->Release ();

			fTarget = ::QueryLayoutTargetHitTest (fControlView, fCurrentPoint);
			if (fTarget)
			{
				//	Check if target is valid.
				if ((IsValidButtonTrigger (fTarget)) != UIDRef::gNull ||
					(IsValidSelfTrigger (fTarget)) != UIDRef::gNull)
				{
					//TRACEFLOW ("Motion", "Mouse over a possible button trigger...");
				}
			}
			else
			{
				CTracker::ContinueTracking (where, mouseDidMove);
			}
		} 
	}


	virtual bool16 EndTracking(IEvent* theEvent) 
	{ 
		bool16 result = CTracker::EndTracking(theEvent);
		Utils<ICursorUtils>()->ReleaseCursor();     
		
		//	Don't select trigger and bing up button panel if option/alt key pressed.
		bool optAltKeyPressed = ::IsOptionAltKeyPressed ();

		// Where did user move to?
		if (fTarget) fTarget->Release ();
		fTarget = ::QueryLayoutTargetHitTest(fControlView, fCurrentPoint);
		if (fTarget)
		{
			//	Create button trigger
			UIDRef possibleButtonTriggerRef;
			UIDRef possibleSelfTriggerRef;
			if ((possibleSelfTriggerRef = IsValidSelfTrigger (fTarget)) != UIDRef::gNull)
			{
				CreateSelfTriggerForTarget (possibleSelfTriggerRef);
			}
			else if ((possibleButtonTriggerRef = IsValidButtonTrigger (fTarget)) != UIDRef::gNull)
			{
				if (CreateButtonTriggerForTargets (possibleButtonTriggerRef, fAnimationTargetList, !optAltKeyPressed) && !optAltKeyPressed)
				{
					//	Show button panel if not already shown
					InterfacePtr<IApplication> iApp (GetExecutionContextSession()->QueryApplication ());
					InterfacePtr<IPanelMgr> iPanelManager(iApp->QueryPanelManager());
					
					if (!optAltKeyPressed && iPanelManager->IsPanelWithWidgetIDShown (kAppearanceParentWidgetId) == kFalse)
					{
						iPanelManager->ShowPanelByWidgetID (kAppearanceParentWidgetId);	
					}

					if (iPanelManager->IsPanelWithWidgetIDShown (kAppearanceParentWidgetId))
					{
						InterfacePtr<IPanelControlData> iButtonPanelData (Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId)); 
						InterfacePtr<IControlView> iButtonPanelView (iButtonPanelData, UseDefaultIID());
						if (iButtonPanelView)
						{
							PaletteRef buttonPaletteRef = iPanelManager->GetPaletteRefContainingPanel (iButtonPanelView);
							PaletteRefUtils::BringPaletteToFront (buttonPaletteRef);
						}
					}
				}
			}
			fTarget->Release ();
			fTarget = nil;
		}
		
		return kTrue;
	}

private:
	UIDRef IsValidButtonTrigger (ILayoutTarget* iLayoutTarget)
	{
		UIDRef triggerRef;
		UIDList itemList = iLayoutTarget->GetUIDList (kStripStandoffs, kStripIfParentLocked);
		if (itemList.size () == 1 && !Utils<Facade::IAnimationFacade> ()->IsPageItemMotionPathPageItem (itemList.GetRef (0)))
		{
			if (fAnimationTargetList.size () == 1 && itemList.GetRef (0) != fAnimationTargetList.GetRef (0))
			{
				//	Clicked on another object
				triggerRef = itemList.GetRef (0);
			}
			else if (fAnimationTargetList.size () > 1)
			{
				//	Remove the object in the selection that was to be the button trigger.
				UIDList::iterator t = std::find (fAnimationTargetList.begin (), fAnimationTargetList.end (), itemList [0]);
				if (t != fAnimationTargetList.end ())
				{
					fAnimationTargetList.erase (t);
				}
				triggerRef = itemList.GetRef (0);
			}
			if (triggerRef != UIDRef::gNull)
			{
				//	Need to check to see if same timing parent (or rather button should not have target outside its state!)
				//	If clicked on an MSO, do nothing since we can't convert MSO to a button.
				Utils<IPageItemTypeUtils> iPGTypeUtils;
				if (iPGTypeUtils->IsMultiStateObject (triggerRef) || iPGTypeUtils->IsMedia (triggerRef) ||
					(!iPGTypeUtils->IsButton (triggerRef) && !Utils<IFormFieldUtils>()->CanCreateFromItems (UIDList (triggerRef), kPushButtonItemBoss)))
				{
					//	Not supported.
					triggerRef = UIDRef::gNull;
				}
				else
				{
					//	Make sure all targets are on the same state or same spread timing or
					//	If button is not part of an MSO, then targets can be anywhere on the same spread.
					Utils<IAnimationUtils>	iAnimaUtils;
					bool sameTimingParent = true;
					IDataBase* iDB = triggerRef.GetDataBase ();
					UID spreadUID = iAnimaUtils->GetParentSpreadUID (triggerRef);
					UID triggerTimingUID = iAnimaUtils->GetTimingParentUID (triggerRef);
					UIDList::iterator t = fAnimationTargetList.begin ();
					for (; t != fAnimationTargetList.end () && sameTimingParent; ++t)
					{
						sameTimingParent = ((triggerTimingUID == spreadUID && spreadUID == iAnimaUtils->GetParentSpreadUID (UIDRef (iDB, *t))) ||
										(triggerTimingUID == iAnimaUtils->GetTimingParentUID (UIDRef (iDB, *t))));
					}
					if (!sameTimingParent) triggerRef = UIDRef::gNull;
				}
			}
		}

		return triggerRef;
	}

	UIDRef IsValidSelfTrigger (ILayoutTarget* iLayoutTarget)
	{
		UIDRef triggerRef;
		UIDList itemList = iLayoutTarget->GetUIDList (kStripStandoffs, kStripIfParentLocked);
		if (itemList.size () == 1)
		{
			if (fAnimationTargetList.size () == 1 && itemList.GetRef (0) == fAnimationTargetList.GetRef (0))
			{
				triggerRef = itemList.GetRef (0);
			}
			else if (fAnimationTargetList.size () == 1)
			{
				IDataBase* iDB = itemList.GetDataBase ();
				InterfacePtr<ISplineState> iSplineState (iDB, iDB->GetRootUID (), UseDefaultIID ());

				UIDRef possibleSelfTrigger;
				if (iSplineState != nil && iSplineState->GetMotionPageItem () != UIDRef::gNull &&
					iDB->IsValidUID (iSplineState->GetMotionPageItem ().GetUID ()))
				{
					possibleSelfTrigger = iSplineState->GetMotionOwnerPageItem ();
					if (possibleSelfTrigger == fAnimationTargetList.GetRef (0)) triggerRef = fAnimationTargetList.GetRef (0);
				}
			}
		}
		return triggerRef;
	}

	bool CreateButtonTriggerForTargets (const UIDRef& triggerRef, const UIDList& targetList, bool doSelectButton)
	{
		ErrorCode errCode = kSuccess;
		UIDRef buttonRef = triggerRef;
		ICommandSequence *iCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		if (!Utils<IPageItemTypeUtils> ()->IsButton (triggerRef))
		{
			//	Create a butotn.
			InterfacePtr<ICommand> iCreateButtonCmd( CmdUtils::CreateCommand(kCreateFormFieldCmdBoss) );
			InterfacePtr<ICreateFormFieldCmdData> iCreateButtonCmdData (iCreateButtonCmd, UseDefaultIID());
			
			PMString createName ("kAnimationUICreateButtonTriggerCmd");
			iCmdSequence->SetName(createName);

			iCreateButtonCmdData->SetFormPageItemType(kPushButtonItemBoss);
			iCreateButtonCmdData->SetIconList(UIDList (triggerRef));

			errCode = CmdUtils::ProcessCommand(iCreateButtonCmd);
			if (errCode == kSuccess)
			{
				//TRACEFLOW ("Motion", "Creating a button trigger...");
				buttonRef = iCreateButtonCmd->GetItemListReference().GetRef (0);

				//	We used to have to call M2MValidateAll to make sure that the button was added to the spread's dynamic content list.
				//	This was necessary because DynamicEventTimingListnerData was checking to see if button is in the dynamic content list
				//	before allowing update to button's timing list.
				//	This was unnecessary since button is already added to the hierarchy.
			}
		}
		if (kSuccess == errCode && doSelectButton)
		{
			//	Select the button
			InterfacePtr<ILayoutSelectionSuite> iLayoutSelectionSuite(Utils<ISelectionUtils>()->QueryActiveLayoutSelectionSuite()); 
			if (iLayoutSelectionSuite)
			{
				//TRACEFLOW ("Motion", "Selecting the button trigger...");

				iLayoutSelectionSuite->SelectPageItems (UIDList(buttonRef), Selection::kReplace, Selection::kDontScrollLayoutSelection); 
			}
		}

		//	Create animation target for button "On Release" event
		for (int32 n = 0; n < targetList.size (); n++)
		{
			UIDRef targetRef = targetList.GetRef (n);
			UID behaviorUID = this->CreateAnimationBehaviorUIDFromTargetUID (buttonRef, targetRef);
			ASSERT (behaviorUID != kInvalidUID);
		}
		
		CmdUtils::EndCommandSequence(iCmdSequence);
		ASSERT (ErrorUtils::PMGetGlobalErrorCode () == kSuccess);
		
		return (ErrorUtils::PMGetGlobalErrorCode () == kSuccess);
	}


	//	This should be called within a command sequence.
	UID CreateAnimationBehaviorUIDFromTargetUID (const UIDRef& ownerRef, const UIDRef& targetRef)
	{
		//TRACEFLOW ("Motion", "Creating a target for button trigger...");
		
		ASSERT (Utils<Facade::IAnimationFacade> ()->PageItemHasAnimation (targetRef));

		IDataBase* iDB = targetRef.GetDataBase ();

		UID behaviorUID = kInvalidUID;
		InterfacePtr<IK2ServiceRegistry> servReg (GetExecutionContextSession(), UseDefaultIID());
		InterfacePtr<IK2ServiceProvider> provider(servReg->QueryServiceProviderByClassID (kBehaviorService, kAnimationActionFactoryBoss));
		InterfacePtr<IBehaviorData> iBehaviorData (provider, UseDefaultIID());
		ASSERT (iBehaviorData->GetAction() == kAnimationBehavior);

		InterfacePtr<IAnimationBehaviorData> iAnimaActionData (iBehaviorData, UseDefaultIID ());
		iAnimaActionData->SetTarget (targetRef.GetUID ());
		iAnimaActionData->SetOperation (IAnimationBehaviorData::kPlay);
	
		//	This creates the behavior object and add ref (of the behavior UID & acion page item UID) to IPageItemBehaviorXRef
		//	ownerRef is passed to create behavior UID from the same database.
		InterfacePtr<ICommandFactory> factory (iBehaviorData, UseDefaultIID());
		InterfacePtr<ICommand> createBehaviorCmd (factory->CreateCreateCommand());
		createBehaviorCmd->SetCreatorID(ICommand::kUniqueCreatorID);
		createBehaviorCmd->SetItemList (UIDList (ownerRef));
		
		InterfacePtr<IBehaviorData> cmdActionData (createBehaviorCmd, UseDefaultIID());
		cmdActionData->Copy(iBehaviorData);
		ErrorCode errCode = CmdUtils::ProcessCommand (createBehaviorCmd);
		const UIDList* itemList = createBehaviorCmd->GetItemList ();
		if (itemList != nil && itemList->size () == 1)
		{
			ASSERT (errCode == kSuccess);
			behaviorUID = itemList->First ();

			InterfacePtr<ICommand> adoptCmd (CmdUtils::CreateCommand(kAdoptBehaviorCmdBoss));
			adoptCmd->SetCreatorID(ICommand::kUniqueCreatorID);

			InterfacePtr<IBehaviorEventData> cmdEventData(adoptCmd, UseDefaultIID());
			cmdEventData->SetEvent(kMouseUpEvt);
			
			InterfacePtr<IUIDData> cmdUIDData(adoptCmd, UseDefaultIID());
			cmdUIDData->Set(ownerRef);
			
			adoptCmd->SetItemList (UIDList (itemList->GetRef (0)));
			errCode = CmdUtils::ProcessCommand (adoptCmd);
			if (errCode != kSuccess)
			{
				behaviorUID = kInvalidUID;
			}
		}

		return behaviorUID;
	}
	void CreateSelfTriggerForTarget (const UIDRef& selfTriggerRef)
	{
		ASSERT (selfTriggerRef == fAnimationTargetList.GetRef (0));
		Utils<Facade::IDynamicEventTimingFacade> iTimingFacade;
		if (!iTimingFacade->DynamicTargetIsSelfTriggered (selfTriggerRef))
		{
			iTimingFacade->AddSelfClickRolloverDynamicEventToItem (selfTriggerRef, kOnSelfClick);
			ASSERT (ErrorUtils::PMGetGlobalErrorCode () == kSuccess);
		}
	}
};

CREATE_PMINTERFACE (AnimationUIButtonTriggerTracker, kAnimationUIButtonTriggerTrackerImpl)


//____________________________________________________________________________________
//	Local utils
//____________________________________________________________________________________
//	This code adapted from EyeDropperUtils::QueryHitTest
//	We don't want to "see" locked items or items on the master page.
//____________________________________________________________________________________
ILayoutTarget* QueryLayoutTargetHitTest (IControlView* currentView, const PMPoint& where)
{
	ILayoutTarget *result = nil; 

	if (!currentView) 
	{ 
		currentView = Utils<ILayoutUIUtils>()->QueryFrontView(); 
		if (!currentView) 
			return result; 
	} 
             
	PMPoint itemToFindAt (where); 	     
	InterfacePtr<ILayoutControlViewHelper> helper ((IPMUnknown*)currentView, IID_ILAYOUTCONTROLVIEWHELPER); 
	if (helper) 
	{ 
		IGeometry *pageItem = nil; 
         
		// Try hit testing for text-on-a-path 
		// We get back the TOPSpline if exists 
		ClassID topClass = kSolidTOPHitTestHandlerBoss; 
		InterfacePtr<ITOPSplineData> pTOPSplineData ((ITOPSplineData*)helper->QueryHitTestPageItemNew(itemToFindAt, topClass, IID_ITOPSPLINEDATA)); 
		if (pTOPSplineData)
		{ 
			UID aMainItemTOPDataUID = pTOPSplineData->GetMainSplineItemUID(); 
			InterfacePtr<IMainItemTOPData> mainItemTOPData (::GetDataBase(pTOPSplineData), aMainItemTOPDataUID, UseDefaultIID ()); 
			if (mainItemTOPData)
			{ 
				InterfacePtr<IGeometry> iTOPPageItem(mainItemTOPData, UseDefaultIID ()); 
				if (iTOPPageItem)
				{ 
					pageItem = iTOPPageItem; 
					pageItem->AddRef(); 
				} 
			} 
		} 

		Utils<IPageItemTypeUtils> iPGTypeUtils;
		if (!pageItem) 
		{ 
			// Try hit testing using direct selection to get the innermost object. 
			ClassID dirSelClass = kDirSelHitTestHandlerBoss; 
			InterfacePtr<IGeometry> directPageItem( (IGeometry*)helper->QueryHitTestPageItemNew( itemToFindAt, dirSelClass)); 
			if (directPageItem)
			{
				UIDRef itemRef = ::GetUIDRef (directPageItem);
				if (Utils<IAnimationUtils> ()->AnimationAllowedForPageItem (itemRef))
				{
					pageItem = directPageItem; 
					pageItem->AddRef(); 
				}
				else
				{
					//	We could hit the content of a container such as button/mso
					UIDRef possibleButtonRef;
					if (Utils<IFormFieldUtils> ()->GetFirstAncestorOfClass (directPageItem, kPushButtonItemBoss, possibleButtonRef))
					{
						InterfacePtr<IGeometry> buttonGeometry (possibleButtonRef, UseDefaultIID ());
						pageItem = buttonGeometry.forget ();
					}
				}
			} 
		} 
         
		if (!pageItem) 
		{ 
			// If nothing was direct selected (treats non-filled spline items as if filled), 
			// make sure its not because the innermost item had a none-fill.Useful for hit testing text frame.
			ClassID solidClass = kSolidHitTestHandlerBoss; 
			InterfacePtr<IGeometry> solidPageItem((IGeometry *)helper->QueryHitTestPageItemNew(itemToFindAt, solidClass)); 
			if (solidPageItem) 
			{ 
				UIDRef itemRef = ::GetUIDRef (solidPageItem);
				if (Utils<IAnimationUtils> ()->AnimationAllowedForPageItem (itemRef))
				{
					pageItem = solidPageItem; 
					pageItem->AddRef(); 
				}
			} 
		} 

		if (!pageItem) 
		{ 
			// If still nothing try group
			ClassID solidClass = kSolidGroupHitTestHandlerBoss; 
			InterfacePtr<IGeometry> groupPageItem((IGeometry *)helper->QueryHitTestPageItemNew(itemToFindAt, solidClass)); 
			if (groupPageItem) 
			{ 
				//	Is it group
				pageItem = groupPageItem; 
				pageItem->AddRef(); 
			} 
		} 

		// 
		// We may be in a table which is outside of the text frame 
		// 
		InterfacePtr<ITableFrame> tableFrame(pageItem, UseDefaultIID()); 
		if (tableFrame) 
		{ 
			InterfacePtr<ITextFrameColumn> pTFC(tableFrame->QueryFrame()); 
			if ( pTFC ) 
			{ 
				InterfacePtr<IHierarchy> iHierarchy(pTFC, UseDefaultIID()); 
				InterfacePtr<IGraphicFrameData> graphicFrameData; 
				while(iHierarchy && !graphicFrameData) 
				{ 
					iHierarchy = InterfacePtr<IHierarchy>(iHierarchy->QueryParent()); 
					graphicFrameData = InterfacePtr<IGraphicFrameData>(iHierarchy, UseDefaultIID ()); 
				} 
                         
				InterfacePtr<IGeometry> frameGeom(graphicFrameData, UseDefaultIID()); 
				if(graphicFrameData && frameGeom) 
				{ 
					pageItem->Release(); 
					pageItem = frameGeom.forget(); 
				} 
			} 
		} 

		if (pageItem) 
		{ 
			// Make sure we don't pick up the master page item on doc spread. 
			InterfacePtr<IHierarchy>    pageItemtHier (pageItem, IID_IHIERARCHY); 
             
			// Tables have a IGeometry, but not an IHierarchy 
			if (pageItemtHier) 
			{ 
				InterfacePtr<IHierarchy>    pageItemRoot (pageItemtHier->QueryRoot()); 
				InterfacePtr<IMasterSpread> pageItemFromMaster (pageItemRoot, IID_IMASTERSPREAD); 
				if (pageItemFromMaster) 
				{ 
					InterfacePtr<ILayoutControlData> iLayoutControlData(helper, IID_ILAYOUTCONTROLDATA); 
					if (iLayoutControlData) 
					{ 
						const UIDRef& iCurrentSpreadGeom = iLayoutControlData->GetSpreadRef(); 

						UID curSpreadUID = iCurrentSpreadGeom.GetUID(); 
						UID targetsSpreadUID = ::GetUID(pageItemRoot); 

						if (curSpreadUID != targetsSpreadUID) 
						{ 
							pageItem->Release(); 
							pageItem = nil; 
						} 
					} 
				} 
			} 
		} 

		// Now fill out our targeting boss 
		if (pageItem) 
		{ 
			//TRACEFLOW ("Motion", "We have click on a possible button trigger...");

			bool16 overInvalidCell = kFalse; 
			InterfacePtr<ILayoutTarget> iLayoutTarget (::CreateObject2<ILayoutTarget>(kTargetingBoss)); 
             
			result = iLayoutTarget; 
			if (result) 
				result->AddRef(); 

			iLayoutTarget->Initialize (::GetDataBase(pageItem)); 
			iLayoutTarget->SetUIDList (::GetUID(pageItem)); 

			pageItem->Release(); 
			pageItem = nil; 
		} 
	}
	return result;
}
