//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationPanelObserver.cpp $
//  
//  Owner: Yeming Liu
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IPanelMgr.h"
#include "IAnimationAttributeSuite.h"
#include "IBoolData.h"
#include "IBooleanControlData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IDynamicTargetsFacade.h"
#include "IIntData.h"
#include "IMenuManager.h"
#include "IMotionPresetData.h"
#include "IMotionPresetMgr.h"
#include "IMotionFacade.h"
#include "IPageItemTypeUtils.h"
#include "IPanelControlData.h"
#include "ISelectionDataSuite.h"
#include "ISelectionManager.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "ITriStateControlData.h"
#include "IPanelDetailController.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"
#include "IIntList.h"
#include "IProxyWidgetAttributes.h"
#include "IStringData.h"
#include "IPalettePanelUtils.h"
#include "IActionManager.h"
#include "IDialogMgr.h"
// ----- Include files -----

#include "DynamicDocumentsUIDefs.h"
#include "IconRsrcDefs.h"
#include "ListLazyNotificationData.h"
#include "SelectionObserver.h"
#include "KeyStates.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "IAnimationUtils.h"
#include "IGraphicStateUtils.h"
#include "ILayoutUIUtils.h"
#include "IMenuUtils.h"
#include "IMotionPresetUtils.h"
#include "ISelectionUtils.h"
#include "PaletteRefUtils.h"

// ----- ID files -----

#include "DynamicDocumentsID.h"
#include "DynamicDocumentsUIID.h"
#include "GenericID.h"

const int32 kNumProxyPoints = 9;
const PMPoint kProxyPoints [kNumProxyPoints] = {
	PMPoint (0,0), PMPoint (0.5, 0), PMPoint (1.0, 0),
	PMPoint (0,0.5), PMPoint (0.5, 0.5), PMPoint (1.0, 0.5),
	PMPoint (0,1), PMPoint (0.5, 1), PMPoint (1.0, 1),
};
static const char* kSeparatorString = "-";
class AnimationPanelObserver : public ActiveSelectionObserver
{
	bool fEnableState;
	PMString kTranslatedSeparatorString;

public:
	AnimationPanelObserver(IPMUnknown *boss) 
		: ActiveSelectionObserver (boss), fEnableState (false)
	{
		kTranslatedSeparatorString = PMString (kSeparatorString);
		kTranslatedSeparatorString.SetTranslatable (kFalse);
	}

	virtual void AutoAttach()
	{		
		// Attach the widgets in the basic panel
		_AttachDetachWidget (kAnimationUINameEditBoxWID, IID_ITEXTCONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIOnRollOffCheckboxWID, IID_ITRISTATECONTROLDATA, true);
		//_AttachDetachWidget (kAnimationUIDurationILEWID, IID_IINLINEEDITCONTROLLER, true);
		_AttachDetachWidget (kAnimationUIDurationILEWID, IID_ITEXTCONTROLDATA, true);
		//_AttachDetachWidget (kAnimationUIPlayILEWID, IID_IINLINEEDITCONTROLLER, true);
		_AttachDetachWidget (kAnimationUIPlayILEWID, IID_ITEXTCONTROLDATA, true);
		_AttachDetachWidget (kAnimationUILoopCheckboxWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUISpeedDropDownWID, IID_ISTRINGLISTCONTROLDATA, true);
		
		// Attach the widgets in the property sub panel
		_AttachDetachWidget (kAnimationUIPropertyExpanderWidgetIconWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIHideBeforeAnimateCheckboxWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIHideAfterAnimateCheckboxWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIPropertyOpacityDropDownWID, IID_ISTRINGLISTCONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIScaleHorzILEWID, IID_IINLINEEDITCONTROLLER, true);
		_AttachDetachWidget (kAnimationUIScaleHorzILEWID, IID_ITEXTCONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIScaleVertILEWID, IID_IINLINEEDITCONTROLLER, true);
		_AttachDetachWidget (kAnimationUIScaleVertILEWID, IID_ITEXTCONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIScaleLockButtonWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIRotateILEWID, IID_IINLINEEDITCONTROLLER, true);
		_AttachDetachWidget (kAnimationUIRotateILEWID, IID_ITEXTCONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIPropertyDesignDropDownWID, IID_ISTRINGLISTCONTROLDATA, true);

		_AttachDetachWidget (kAnimationUIXFPointProxyWID, IID_IPROXYWIDGETATTRIBUTES, true);
		
		// Attach the buttons at the bottom of the panel		
		_AttachDetachWidget (kAnimationUIPreviewButtonWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIShowProxyButtonWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIConvertToMotionPathButtonWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIShowTimingButtonWID, IID_ITRISTATECONTROLDATA, true);
		_AttachDetachWidget (kAnimationUIClearAnimationButtonWID, IID_ITRISTATECONTROLDATA, true);

		ActiveSelectionObserver::AutoAttach ();

		// For LazyUpdate()
		_AttachDetachModelChanges (true);

		_UpdatePanelSize(false);
	}

	virtual void AutoDetach()
	{

		// Detach the widgets in the basic panel
		_AttachDetachWidget (kAnimationUINameEditBoxWID, IID_ITEXTCONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIOnRollOffCheckboxWID, IID_ITRISTATECONTROLDATA, false);
		//_AttachDetachWidget (kAnimationUIDurationILEWID, IID_IINLINEEDITCONTROLLER, false);
		_AttachDetachWidget (kAnimationUIDurationILEWID, IID_ITEXTCONTROLDATA, false);
		//_AttachDetachWidget (kAnimationUIPlayILEWID, IID_IINLINEEDITCONTROLLER, false);
		_AttachDetachWidget (kAnimationUIPlayILEWID, IID_ITEXTCONTROLDATA, false);
		_AttachDetachWidget (kAnimationUILoopCheckboxWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUISpeedDropDownWID, IID_ISTRINGLISTCONTROLDATA, false);

		// Detach the widgets in the property sub panel
		_AttachDetachWidget (kAnimationUIPropertyExpanderWidgetIconWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIHideBeforeAnimateCheckboxWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIHideAfterAnimateCheckboxWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIPropertyOpacityDropDownWID, IID_ISTRINGLISTCONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIScaleHorzILEWID, IID_IINLINEEDITCONTROLLER, false);
		_AttachDetachWidget (kAnimationUIScaleHorzILEWID, IID_ITEXTCONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIScaleVertILEWID, IID_IINLINEEDITCONTROLLER, false);
		_AttachDetachWidget (kAnimationUIScaleVertILEWID, IID_ITEXTCONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIScaleLockButtonWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIRotateILEWID, IID_IINLINEEDITCONTROLLER, false);
		_AttachDetachWidget (kAnimationUIRotateILEWID, IID_ITEXTCONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIPropertyDesignDropDownWID, IID_ISTRINGLISTCONTROLDATA, false);

		_AttachDetachWidget (kAnimationUIXFPointProxyWID, IID_IPROXYWIDGETATTRIBUTES, false);

		// Detach the buttons at the bottom of the panel		
		_AttachDetachWidget (kAnimationUIPreviewButtonWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIShowProxyButtonWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIConvertToMotionPathButtonWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIShowTimingButtonWID, IID_ITRISTATECONTROLDATA, false);
		_AttachDetachWidget (kAnimationUIClearAnimationButtonWID, IID_ITRISTATECONTROLDATA, false);

		// For LazyUpdate()
		_AttachDetachModelChanges (false);		
		
		ActiveSelectionObserver::AutoDetach ();
	}

protected:
	
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
	{
		switch (protocol.Get())
		{
			case IID_IMOTIONPRESETDATA:
			case IID_IMOTIONPRESETMANAGER:
			{
				InterfacePtr<IAnimationAttributeSuite> iAttrSuite (fCurrentSelection, UseDefaultIID ());
				_UpdatePresetStaticText(iAttrSuite);
				break;
			}
			case IID_IPAGEITEMNAME:
			{				
				const ListLazyNotificationData<UID>*  listData = static_cast<const ListLazyNotificationData<UID>* > (data);
				if (listData)
				{
					K2Vector<UID> changedItems;
					listData->BreakoutChanges(nil, nil, &changedItems);
					if (changedItems.size() > 0)
					{
						//	Need to check if valid UID since we get notify even though item does not exist anymore.
						//	e.g. undoing convert to button.
						IDataBase* db = fCurrentSelection->GetDataBase();
						if (db->IsValidUID (changedItems[0]))
						{
							PMString itemName = Utils<Facade::IDynamicTargetsFacade>()->GetTargetName(UIDRef(db, changedItems[0]));

							InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());	
							IControlView* iNameView = iPanelControlData->FindWidget(kAnimationUINameEditBoxWID);
							InterfacePtr<ITextControlData> iNameTextControlData(iNameView, UseDefaultIID());
							iNameTextControlData->SetString(itemName, kTrue, kFalse);
						}
					}
				}
				break;
			}
			default:
				break;
		}
	}
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
	{
		ActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);

		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (fCurrentSelection, UseDefaultIID ());
		if (!iAttrSuite)
			return;

		InterfacePtr<IControlView> iWidgetView(theSubject, UseDefaultIID());
		WidgetID widgetID = iWidgetView ? iWidgetView->GetWidgetID() : kInvalidWidgetID;

		switch (protocol.Get())
		{	
			case IID_ITEXTCONTROLDATA:
			{
				if (theChange == kTextChangeStateMessage)
				{
					InterfacePtr<ITextControlData> iTextControlData(theSubject, UseDefaultIID());
					PMString value = iTextControlData->GetString();
					ASSERT(!value.empty() || widgetID == kAnimationUIPresetDropDownWID);

					if (widgetID == kAnimationUINameEditBoxWID)
					{
						_ApplyAnimationName (iAttrSuite, value);
					}
					else if (widgetID == kAnimationUIPlayILEWID)
					{
						_ApplyAnimationPlays (iAttrSuite, value);
					}
					else if (widgetID == kAnimationUIDurationILEWID)
					{
						InterfacePtr<ITextValue> iDurationTextValue(iWidgetView, UseDefaultIID());
						if (iDurationTextValue)
						{
							bool16 bError = kFalse;
							PMReal newValue = iDurationTextValue->GetTextAsValue(&bError);
							if (!bError)
								_ApplyAnimationDuration (iAttrSuite, newValue);
						}
					}
					else
					{
						if (widgetID == kAnimationUIScaleHorzILEWID)
							_ApplyAnimationProperty(iAttrSuite, IAnimationAttributeSuite::kAnimationScaleX, 100.0, value);
						else if (widgetID == kAnimationUIScaleVertILEWID)
							_ApplyAnimationProperty(iAttrSuite, IAnimationAttributeSuite::kAnimationScaleY, 100.0, value);
						else if (widgetID == kAnimationUIRotateILEWID)
							_ApplyAnimationProperty(iAttrSuite, IAnimationAttributeSuite::kAnimationRotation, 0.0, value);
						else if (widgetID == kAnimationUIPresetDropDownWID)
						{
							if (!value.empty())
							{
								if (Utils<IMenuUtils>()->GetNumMenuParts(value) > 1)
								{
									InterfacePtr<IMotionPresetMgr>	iPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
									int32 presetIndex = iPresetMgr->FindPreset(Utils<IMenuUtils>()->GetNthMenuPart(value, 1));
									if (presetIndex >= 0 && iPresetMgr->IsDefaultPreset(presetIndex))
										value = Utils<IMenuUtils>()->GetNthMenuPart(value, 1);
								}
								_ApplyMotionPreset (iAttrSuite, value);
							}
						} 
					}
				}
				break;
			}
			case IID_IINLINEEDITCONTROLLER:	
			{
				if (theChange == kInLineEditStartEditingMessageID) 
				{					
					InterfacePtr<IPanelControlData> iInlinePanelData(iWidgetView, UseDefaultIID());
					IControlView * iStaticTextView = iInlinePanelData->FindWidget(kInLineEditStaticTextWidgetID);
					
					InterfacePtr<ITextControlData> iTextControlData(iStaticTextView, UseDefaultIID());
					PMString value = iTextControlData->GetString();

					if (widgetID == kAnimationUIPlayILEWID)
					{
						_ApplyAnimationPlays (iAttrSuite, value);
					}
					else if (widgetID == kAnimationUIDurationILEWID)
					{
						InterfacePtr<ITextValue> iDurationTextValue(iWidgetView, UseDefaultIID());
						if (iDurationTextValue)
						{
							bool16 bError = kFalse;
							PMReal newValue = iDurationTextValue->GetTextAsValue(&bError);
							if (!bError)
								_ApplyAnimationDuration (iAttrSuite, newValue);
						}
					}
					else
					{
						if (widgetID == kAnimationUIScaleHorzILEWID)
							_ApplyAnimationProperty(iAttrSuite, IAnimationAttributeSuite::kAnimationScaleX, 100.0, value);
						else if (widgetID == kAnimationUIScaleVertILEWID)
							_ApplyAnimationProperty(iAttrSuite, IAnimationAttributeSuite::kAnimationScaleY, 100.0, value);
						else if (widgetID == kAnimationUIRotateILEWID)
							_ApplyAnimationProperty(iAttrSuite, IAnimationAttributeSuite::kAnimationRotation, 0.0, value);
					}
				}
				break;
			}
			case IID_ISTRINGLISTCONTROLDATA:	
			{					
				InterfacePtr<IStringListControlData> iStringListControlData(theSubject, UseDefaultIID());
				InterfacePtr<IDropDownListController> iDDListController(iStringListControlData, UseDefaultIID());

				int32 selectedIndex = iDDListController->GetSelected();
				PMString selectString = (selectedIndex >= 0 && iStringListControlData->Length() > 0) ? iStringListControlData->GetString(selectedIndex) : kNullString;
				ASSERT(!selectString.empty() || widgetID == kAnimationUIPresetDropDownWID);

				if (widgetID == kAnimationUIPropertyDesignDropDownWID)
				{
					_ApplyAnimateSetting (iAttrSuite, selectString);
				}
				else if (widgetID != kAnimationUIPresetDropDownWID) // preset drop-down handled by text editbox notify (see above) 
				{
					if (widgetID == kAnimationUISpeedDropDownWID)
						_ApplyAnimationSpeed (iAttrSuite, selectString);
					else if (widgetID == kAnimationUIPropertyOpacityDropDownWID)
						_ApplyAnimationOpacity (iAttrSuite, selectString);
				}

				break;
			}
			case IID_ITRISTATECONTROLDATA:	
			{					
				InterfacePtr<ITriStateControlData> iTriStateControlData(theSubject, UseDefaultIID());
				bool bOn = iTriStateControlData->IsSelected();

				if (widgetID == kAnimationUILoopCheckboxWID)
					_ApplyAnimationPlaysLoop (iAttrSuite, bOn);
				else if (widgetID == kAnimationUIOnRollOffCheckboxWID)
					_ApplyAnimationOnRollOff (iAttrSuite, bOn);
				else if (widgetID == kAnimationUIHideBeforeAnimateCheckboxWID)
					_ApplyVisibility(iAttrSuite, widgetID == kAnimationUIHideBeforeAnimateCheckboxWID, bOn);
				else if (widgetID == kAnimationUIHideAfterAnimateCheckboxWID)
					_ApplyVisibility(iAttrSuite, widgetID == kAnimationUIHideBeforeAnimateCheckboxWID, bOn);
				else if (widgetID == kAnimationUIScaleLockButtonWID)
					_UpdateScaleValue(bOn);
				else if (widgetID == kAnimationUIShowProxyButtonWID)
					_ApplyShowProxySetting (iAttrSuite, bOn);
				else if (theChange == kTrueStateMessage)
				{
					if (widgetID == kAnimationUIPropertyExpanderWidgetIconWID)
						_UpdatePanelSize(true);					
					else if (widgetID == kAnimationUIPreviewButtonWID)
					{											
						// HTML Preview
                        InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
                        InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
                        actionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), kHTMLFXLPreviewActionID);
					}
					else if (widgetID == kAnimationUIConvertToMotionPathButtonWID)
					{
						if ((iAttrSuite != nil) && iAttrSuite->CanSetAnimationMotionPathFromSelection())
							iAttrSuite->SetAnimationMotionPathFromSelection();
					}
					else if (widgetID == kAnimationUIShowTimingButtonWID)
					{
						_ShowTimingPanel ();
					}
					else if (widgetID == kAnimationUIClearAnimationButtonWID)
					{
						_ApplyMotionPreset (iAttrSuite, PMString("kAnimationUINone"));
					}

				}

				break;
			} 
			case IID_IPROXYWIDGETATTRIBUTES:
			{
				InterfacePtr<IProxyWidgetAttributes> iXFProxyAttr (theSubject, UseDefaultIID());
				if (iXFProxyAttr)
				{
					IReferencePointData::ReferencePointPosition newPosition = iXFProxyAttr->GetProxyPosition ();
					_ApplyXFormOffsetPoint (iAttrSuite, newPosition);
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}

	virtual void HandleSelectionChanged 
	(
		const ISelectionMessage*	iSelectionMsg
	)
	{
		bool32	suiteEnabled = fCurrentSelection->IsInterfaceEnabled (IID_IANIMATIONATTRIBUTESUITE);
		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (static_cast<IAnimationAttributeSuite*>
												(this->QueryAbstractSelection (IID_IANIMATIONATTRIBUTESUITE)));
		if (suiteEnabled && iAttrSuite->CanApplyAnimation ())
		{
			fEnableState = kTrue;

			__EnableWidgets (fEnableState, iAttrSuite->CanApplyMotionPreset(), iAttrSuite->CanSetAnimationMotionPathFromSelection());

			if (iSelectionMsg == nil || iSelectionMsg->WasSuiteAffected (IID_IANIMATIONATTRIBUTESUITE))
			{
				__UpdateWidgetsToDefinition (iAttrSuite);
			}
		}
		else
		{
			if (fEnableState == kTrue)
				fEnableState = kFalse;

			__EnableWidgets (fEnableState, (iAttrSuite && iAttrSuite->CanApplyMotionPreset()), (iAttrSuite && iAttrSuite->CanSetAnimationMotionPathFromSelection()));
			__UpdateWidgetsToDefinition (iAttrSuite);
		}
	}
	virtual void HandleSelectionAttributeChanged
	(
		const ISelectionMessage*	iSelectionMsg
	)
	{
		if (iSelectionMsg->WasSuiteAffected (IID_IANIMATIONATTRIBUTESUITE))
		{
#ifdef MACINTOSH
			//Workaround for bug: 3779634
			//When the modal dialog is dismissed and the panel is trying to refresh then we observe a crash.
			//The issue has not been completely narrowed down and the following is just a workaround to avoid the crash.
			InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IDialogMgr> dialogMgr(app,UseDefaultIID());
			if (dialogMgr != nil)
			{
				if (dialogMgr->IsModalDialogOpen())
					return;
			}
#endif
			InterfacePtr<IAnimationAttributeSuite> iAttrSuite (static_cast<IAnimationAttributeSuite*>
													(this->QueryAbstractSelection (IID_IANIMATIONATTRIBUTESUITE)));
			if (iAttrSuite != nil && iAttrSuite->CanApplyAnimation ())
			{
				if (!fEnableState)
				{
					fEnableState = kTrue;
					__EnableWidgets (fEnableState, iAttrSuite->CanApplyMotionPreset(), iAttrSuite->CanSetAnimationMotionPathFromSelection());
				}

				ASSERT_MSG (iAttrSuite != nil, "AnimationUIPresetWidgetObserver::HandleSelectionAttributeChanged, IAnimationAttributeSuite is nil.");
				__UpdateWidgetsToDefinition (iAttrSuite);
			}
			else
			{
				fEnableState = kFalse;
				__EnableWidgets (fEnableState, (iAttrSuite && iAttrSuite->CanApplyMotionPreset()), (iAttrSuite && iAttrSuite->CanSetAnimationMotionPathFromSelection()));
			}
		}
	}	

private:
	void _AttachDetachWidget (WidgetID const &widgetID, PMIID const &protocol, bool const bAttach) 
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());	
		IControlView* iWidgetView = iPanelControlData->FindWidget(widgetID);

		InterfacePtr<ISubject> iWidgetSubject(iWidgetView, UseDefaultIID());
		if (iWidgetSubject)
		{	
			if (bAttach && !iWidgetSubject->IsAttached( this, protocol, IID_IOBSERVER))
				iWidgetSubject->AttachObserver(this, protocol, IID_IOBSERVER);
			else if (!bAttach && iWidgetSubject->IsAttached( this, protocol, IID_IOBSERVER))
				iWidgetSubject->DetachObserver(this, protocol, IID_IOBSERVER);
		}
	}

	void _AttachDetachModelChanges (bool const bAttach) 
	{
		IDataBase* db = fCurrentSelection->GetDataBase();

		InterfacePtr<IDocument> iDocument(db, db->GetRootUID(), UseDefaultIID());
		if (iDocument)
		{
			InterfacePtr<ISubject> iDocumentSubject(iDocument, UseDefaultIID());	

			//
			// IID_IPAGEITEMNAME
			//
			if (bAttach && !iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER)) 
				iDocumentSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER); 
			else if (!bAttach && iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER)) 
				iDocumentSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER); 

			//
			// IID_IDYNAMICEVENTTIMING_DOCUMENT --- for timing items change (e.g., trigger)
			//
			if (bAttach && !iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER)) 
				iDocumentSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER); 
			else if (!bAttach && iDocumentSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER)) 
				iDocumentSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IDYNAMICEVENTTIMING_DOCUMENT, IID_IOBSERVER); 

		}

		InterfacePtr<IWorkspace> iSessionWS(GetExecutionContextSession()->QueryWorkspace()); 
		if (iSessionWS)
		{
			InterfacePtr<ISubject> iWSSubject(iSessionWS, UseDefaultIID());	
			if (iWSSubject)
			{
				//
				// IID_IMOTIONPRESETDATA
				//
				if (bAttach && !iWSSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETDATA, IID_IOBSERVER)) 
					iWSSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETDATA, IID_IOBSERVER); 
				else if (!bAttach && iWSSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETDATA, IID_IOBSERVER)) 
					iWSSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETDATA, IID_IOBSERVER); 

				//	IID_IMOTIONPRESETMANAGER
				if (bAttach && !iWSSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETMANAGER, IID_IOBSERVER)) 
					iWSSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETMANAGER, IID_IOBSERVER); 
				else if (!bAttach && iWSSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETMANAGER, IID_IOBSERVER)) 
					iWSSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IMOTIONPRESETMANAGER, IID_IOBSERVER); 
			}
		}
	}

	//___________________________________________________________________________________________
	//	The following methods apply animation settings
	//___________________________________________________________________________________________
	void _ApplyAnimationName(IAnimationAttributeSuite* iAttrSuite, PMString const &name)
	{
		iAttrSuite->SetName (name);
	}

	bool _ApplyMotionPreset(IAnimationAttributeSuite* iAttrSuite, PMString const &presetName)
	{		
		if (iAttrSuite->CanApplyMotionPreset ())
		{				
			UIDRef presetUIDRef = UIDRef::gNull;

			InterfacePtr<IMotionPresetMgr>	iPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
			int32 presetIndex = iPresetMgr->FindPreset(presetName);
			if (presetIndex >= 0)
			{
				UID presetUID = iPresetMgr->GetNthPresetUID(presetIndex);
				ASSERT_MSG (presetUID != kInvalidUID, FORMAT_ARGS ("AnimationPanelObserver::_ApplyMotionPreset, presetUID (%x) from AppPresetMgr is not valid!"));

				IDataBase* db = ::GetDataBase(iPresetMgr);
				if ((presetUID != kInvalidUID) && (db->GetClass (presetUID) != kInvalidClass))		
					presetUIDRef = UIDRef(db, presetUID);
			}
			else
			{
				PMString presetNameTranslated (presetName);
				presetNameTranslated.Translate();
				PMString noneStringTranslated ("kAnimationUINone");
				noneStringTranslated.Translate ();
				if (presetNameTranslated != noneStringTranslated)
					return kFalse;
			}

#ifdef DEBUG
			if (presetUIDRef == UIDRef::gNull)
			{
				UID currentPresetUID = kInvalidUID;
				bool unique = iAttrSuite->GetMotionPresetApplied (currentPresetUID);
				if (currentPresetUID != kInvalidUID || iAttrSuite->HasCustomAnimationSettings ())
				{
					PMString none("kAnimationUINone");
					if (presetName.HasTranslated())
						none.Translate();
					ASSERT (presetName == none);
				}
				else if (unique)
				{
					PMString choose("kAnimationUIChoose");
					if (presetName.HasTranslated())
						choose.Translate();
					ASSERT (presetName == choose);
				}

			}	
#endif			
			// Note: Apply UIDRef::gNullRef is to remove the motion preset from the selection.
			iAttrSuite->ApplyMotionPreset (presetUIDRef);

			//
			// Update speed drop down list as "From Preset".
			//
			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUISpeedDropDownWID, PMString("kAnimationUIFromPreset"), true);

			//
			// Update Opacity drop down List as "From Preset".
			//
			_UpdateAnimationOpacity (iAttrSuite);
			
		}
		return true;
	}

	bool _ApplyAnimationDuration (IAnimationAttributeSuite* iAttrSuite, PMReal const &newValue)
	{
		PMReal oldValue = 1.0;
		bool unique = iAttrSuite->GetAnimationDuration(oldValue);

		if (!unique || oldValue != newValue)
		{
			// Update singular to plural form and vice versa.
			PMString labelString = (newValue > 1) ? PMString("kAnimationUISecondsStaticTextLabel") : PMString("kAnimationUISecondStaticTextLabel");
			_UpdateLabelString(labelString, kAnimationUIDurationSecondLabelWID, true);

			iAttrSuite->SetAnimationDuration (newValue);

			return true;
		}

		return false;
	}

	void _ApplyAnimationPlays (IAnimationAttributeSuite* iAttrSuite, PMString const &valueString)
	{
		PMReal value = PMReal(valueString.GetAsDouble());
		uint32 newValue = ::ToUInt32(value);
		uint32 oldValue = 1;
		bool unique = iAttrSuite->GetAnimationPlays (oldValue);

		if (!unique || oldValue != newValue)
		{
			iAttrSuite->SetAnimationPlays(newValue);

			//
			// Update singular to plural form and vice versa.
			//
			PMString labelString = (value > 1) ? PMString("kAnimationUITimesStaticTextLabel") : PMString("kAnimationUITimeStaticTextLabel");
			_UpdateLabelString(labelString, kAnimationUITimeLabelWID, true);
		}
	}

	void _ApplyAnimationPlaysLoop (IAnimationAttributeSuite* iAttrSuite, bool const bOn)
	{
		iAttrSuite->SetAnimationPlaysLoop (bOn);

		//
		// Enable/Disable the play value
		//
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
  		IControlView* iAnimationUIPlayView = iPanelControlData->FindWidget(kAnimationUIPlayILEWID);
		iAnimationUIPlayView->Enable(!bOn);
	}

	void _ApplyAnimationOnRollOff (IAnimationAttributeSuite* iAttrSuite, bool const bOn)
	{
		//	This is to support reverse animation on rollOff.
		uint32 numEvents = 0;
		bool unique = iAttrSuite->GetNumAnimationTriggerEvents (numEvents);

		for (uint32 n = 0; n < numEvents; n++)
		{
			EventTriggerType trigger = kNoTriggerEvent;
			iAttrSuite->GetNthAnimationTriggerEvent (n, trigger);

			bool canbeReversed = iAttrSuite->CanReverseAnimationForEvent (trigger);
			if (canbeReversed)
			{
				iAttrSuite->SetReverseAnimationForEvent (trigger, bOn);
			}
		}
	}

	bool _ApplyAnimationSpeed (IAnimationAttributeSuite* iAttrSuite, PMString const &easeTypeString)
	{		
		bool applied = false;
		AnimationEaseType newEaseType = kNoEase;
		AnimationEaseType oldEaseType = kNoEase;
		iAttrSuite->GetSimpleEaseType (oldEaseType);

		if (easeTypeString == "kAnimationUIEaseIn")
			newEaseType = kEaseIn;
		else if (easeTypeString == "kAnimationUIEaseOut")
			newEaseType = kEaseOut;
		else if (easeTypeString == "kAnimationUIEaseInAndOut")
			newEaseType = kEaseInAndOut;
		else if (easeTypeString == "kAnimationUINone")
			newEaseType = kNoEase;
		else if (easeTypeString == "kAnimationUIFromPreset")
		{
			newEaseType = kEaseCustomReadOnly;
			ASSERT (oldEaseType == newEaseType);
		}

		if (oldEaseType != newEaseType)
		{
			applied = true;
			iAttrSuite->SetSimpleEaseType (newEaseType);
			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUISpeedDropDownWID, PMString("kAnimationUIFromPreset"), false);
		}
		return applied;
	}

	void _ApplyAnimateSetting (IAnimationAttributeSuite* iAttrSuite, PMString const &animateString)
	{
		bool applied = false;
		AnimationOptions newAnimateOption = kAnimateFrom;
		AnimationOptions oldAnimateOption = kAnimateFrom;
		bool unique = iAttrSuite->GetAnimateOption (oldAnimateOption);

		if (animateString == "kAnimationUIFrom")
			newAnimateOption = kAnimateFrom;
		else if (animateString == "kAnimationUITo")
			newAnimateOption = kAnimateTo;
		else if (animateString == "kAnimationUIOffset")
			newAnimateOption = kAnimateOffset;
		
		if (!unique || oldAnimateOption != newAnimateOption)
		{
			iAttrSuite->SetAnimateOption (newAnimateOption);
		}
	}

	void _ApplyVisibility (IAnimationAttributeSuite* iAttrSuite, bool doUpdateVisibilityBefore, bool const bOn)
	{
		if (doUpdateVisibilityBefore)
		{
			iAttrSuite->SetAnimationHideInitially (bOn);
		}
		else
		{
			iAttrSuite->SetAnimationHideAfter (bOn);
		}
	}
	void _ApplyShowProxySetting (IAnimationAttributeSuite* iAttrSuite, bool const bOn)
	{
		bool showProxy = iAttrSuite->GetShowAnimationProxy ();
		ASSERT (bOn == !showProxy);
		iAttrSuite->SetShowAnimationProxy (bOn);
	}

	bool _ApplyAnimationProperty (IAnimationAttributeSuite* iAttrSuite, IAnimationAttributeSuite::PropertyType const &type, const PMReal& srcValue, PMString const &valueString)
	{
		PMReal newValue = PMReal(valueString.GetAsDouble());

		CmdUtils::SequencePtr seq;
		seq->SetName("kUpdateAnimation");

#if 1
		iAttrSuite->RemoveAllKeyFrames (type);
		iAttrSuite->SetKeyFrame (type, IAnimationAttributeSuite::kFirstKeyFrame, srcValue);		
		iAttrSuite->SetKeyFrame (type, IAnimationAttributeSuite::kLastKeyFrame, newValue);
#else
		uint32 totalFrames = 0;
		bool unique = iAttrSuite->GetTotalNumFrames (totalFrames);
		if (unique)
		{
			uint32 numKeyFrames = 0;
			iAttrSuite->GetNumKeyFrames (type, numKeyFrames);
			uint32 firstKeyFrame = 0;
			uint32 lastKeyFrame = totalFrames-1;

			//	If we are setting a value in the property,
			//	just remove all first and reset first to srouce value and last to the new value.
			if (numKeyFrames > 0)
			{
				iAttrSuite->RemoveAllKeyFrames (type);
			}

			iAttrSuite->SetKeyFrame (type, firstKeyFrame, srcValue);		
			iAttrSuite->SetKeyFrame (type, lastKeyFrame, newValue);
		}
#endif

		//
		// Update the scale value if constrained.
		//
		//
		if (type == IAnimationAttributeSuite::kAnimationScaleX || type == IAnimationAttributeSuite::kAnimationScaleY)
		{
			_SynchronizeConstrainedScaleValues (type, newValue);
		}

		//
		// TODO::Shoule we compare with the old values to determine if we really change the values or not.
		// Harder to do now that we have to deal with multiple selection.
		//
		return true;
	}

	void _SynchronizeConstrainedScaleValues (IAnimationAttributeSuite::PropertyType const &type, const PMReal& newValue)
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView *lockIconView = iPanelControlData->FindWidget(kAnimationUIScaleLockButtonWID);
		if (lockIconView->GetRsrcID() == kAnimationUIScaleLockIcon )
		{
			WidgetID scaleWidgetID = kInvalidWidgetID;
			if (type == IAnimationAttributeSuite::kAnimationScaleX) 
				scaleWidgetID = kAnimationUIScaleVertILEWID;
			else if (type == IAnimationAttributeSuite::kAnimationScaleY) 
				scaleWidgetID = kAnimationUIScaleHorzILEWID;
			
			if (scaleWidgetID != kInvalidWidgetID)
			{
				IControlView *iScaleWidgetView = iPanelControlData->FindWidget(scaleWidgetID);
				InterfacePtr<IPanelControlData>	iILEPanelData(iScaleWidgetView, UseDefaultIID());
				InterfacePtr<ITextValue> iTextValue (iScaleWidgetView, UseDefaultIID ());
				if (!iTextValue && iILEPanelData)
				{
					IControlView * iStaticView = iILEPanelData->FindWidget(kInLineEditStaticTextWidgetID);
					iTextValue = InterfacePtr<ITextValue> (iStaticView, UseDefaultIID());
				}

				PMReal currentValue = iTextValue->GetTextAsValue();
				if (currentValue != newValue)
					iTextValue->SetTextFromValue(newValue, kTrue, kTrue);
			}				
		}
	}


	bool _ApplyAnimationOpacity (IAnimationAttributeSuite* iAttrSuite, const PMString& opacityString)
	{
		PMString oldOpacityString;
		bool unique = _GetAnimationOpacityString (iAttrSuite, oldOpacityString);

		bool applied = false;
		PMReal value1 = 100.0;
		PMReal value2 = 0.0;
		if (opacityString == "kAnimationUINone")
		{
			value2 = -1.0;
		}
		else if (opacityString == "kAnimationUIFadeIn")
		{
			value1 = 0.0;
			value2 = 100.0;
		}
		else if (opacityString == "kAnimationUIFadeOut")
		{
			value1 = 100.0;
			value2 = 0.0;
		}
		else if (opacityString == "kAnimationUIFadeOut")
		{
			ASSERT (oldOpacityString == opacityString);
		}

		if (opacityString != oldOpacityString)
		{
			applied = true;
			CmdUtils::SequencePtr seq;
			seq->SetName("kUpdateAnimation");
			
			if (value2 < 0.0)
			{
				//	Applying none
				iAttrSuite->RemoveAllKeyFrames (IAnimationAttributeSuite::kAnimationOpacity);
			}
			else
			{
				//	Remove all old keyframes first.
				iAttrSuite->RemoveAllKeyFrames (IAnimationAttributeSuite::kAnimationOpacity);
				iAttrSuite->SetKeyFrame (IAnimationAttributeSuite::kAnimationOpacity, IAnimationAttributeSuite::kFirstKeyFrame, value1);
				iAttrSuite->SetKeyFrame (IAnimationAttributeSuite::kAnimationOpacity, IAnimationAttributeSuite::kLastKeyFrame, value2);
			}

			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUIPropertyOpacityDropDownWID, PMString("kAnimationUIFromPreset"), false);
		}
		return applied;
	}


	void _ApplyXFormOffsetPoint(IAnimationAttributeSuite* iAttrSuite, const IReferencePointData::ReferencePointPosition& position)
	{
		ASSERT (position >= IReferencePointData::kFirstReferencePointPosition && position <= IReferencePointData::kLastReferencePointPosition);
		PMPoint xFormPoint = kProxyPoints [position];
		
		iAttrSuite->SetAnimationTranformOffsetPoint (xFormPoint);
	}

	//___________________________________________________________________________________________
	//	The following methods update widgets to animation settings
	//___________________________________________________________________________________________
	void _UpdateAnimationName(IAnimationAttributeSuite* iAnimationAttrSuite) const
	{
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
		IControlView* iNameView = iPanelControlData->FindWidget(kAnimationUINameEditBoxWID);
		InterfacePtr<ITextControlData> iNameTextControlData(iNameView, UseDefaultIID());
		
		PMString name;
		bool unique = true;
		if (iAnimationAttrSuite)
		{
			unique = iAnimationAttrSuite->GetName (name);
			if (!unique) name = PMString ("");
		}
		iNameTextControlData->SetString(name, kTrue, kFalse);
		iNameView->Enable (unique);

	}

	void _UpdatePreviewProxy(IAnimationAttributeSuite* iAnimationAttrSuite) const
	{
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
		ddui_utils::UpdateAnimationPreviewProxy (iPanelControlData, iAnimationAttrSuite);
	}

	void _UpdatePresetStaticText(IAnimationAttributeSuite* iAttrSuite)
	{		
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID ());
		IControlView* presetTextView = panelControlData->FindWidget(kAnimationUIPresetStaticTextWID);
		if (!presetTextView) 
			return;
		
		InterfacePtr<ITextControlData> presetTextData(presetTextView, UseDefaultIID());

		if (!iAttrSuite || !iAttrSuite->HasAnimationApplied())
		{
			PMString choose("kAnimationUIChoose", PMString::kTranslateDuringCall);
			presetTextData->SetString(choose, kTrue, kFalse);
		}
		else
		{
			PMString presetNameApplied(kNullString);
			bool nameUnique = iAttrSuite->GetBaseMotionPresetNameApplied(presetNameApplied);
			ASSERT(nameUnique || presetNameApplied.empty());
			if (!presetNameApplied.empty())
				presetNameApplied.Translate();

			bool customIsMixed = false;
			bool hasCustom = iAttrSuite->HasCustomAnimationSettings(&customIsMixed);
			if (hasCustom && !customIsMixed && nameUnique)
			{
				PMString custom("kAnimationUICustomPreset", PMString::kTranslateDuringCall);
				if (!presetNameApplied.empty())
				{
					custom.Append(" (");
					custom.Append(presetNameApplied);
					custom.Append(")");
				}
				presetTextData->SetString(custom, kTrue, kFalse);
			}
			else if (!nameUnique || customIsMixed)
			{
				PMString mixed("kAnimationUIMixed", PMString::kTranslateDuringCall);
				presetTextData->SetString(mixed, kTrue, kFalse);
			}
			else
				presetTextData->SetString(presetNameApplied, kTrue, kFalse);
		}
	}

	void _UpdateEventInfo(IAnimationAttributeSuite* iAttrSuite)
	{		
		PMString eventInfo(kNullString);
		EventTriggerType triggerType = kNoTriggerEvent;

		bool enableView = false;
		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID ());
		IControlView* iEventInfoView = iPanelControlData->FindWidget(kAnimationUIEventStaticTextWID);
		InterfacePtr<IIntList> iEventInfoList(iEventInfoView, IID_IINTLIST);
		if (iEventInfoList) iEventInfoList->Clear ();

		uint32 numTriggerEvents = 0;
		ISpreadDynamicContentMgr::DynamicContentType contentType = ISpreadDynamicContentMgr::kAnimationItemType;
		std::vector<EventTriggerType> applicableList;
		if (iAttrSuite)
		{
			if (iAttrSuite->HasMSOAsTimingParent ()) contentType = ISpreadDynamicContentMgr::kMultiStateItemType;
			if (iAttrSuite->HasAnimationApplied ()) enableView = true;
			iAttrSuite->GetApplicableTriggerEvents (applicableList);
			iAttrSuite->GetNumAnimationTriggerEvents(numTriggerEvents);	
		}

		//	If mixed, set to "Mixed".
		//	If no event, default to page load/state load instead of "Choose" ("kAnimationUIChoose")
		if (numTriggerEvents == 0 && !enableView)
		{
			if (std::find (applicableList.begin (), applicableList.end (), kOnPageLoad) != applicableList.end ())
				eventInfo = Utils<IAnimationUtils>()->GetStringFromEventTrigger (kOnPageLoad, contentType);
			else if (!applicableList.empty ())
				eventInfo = Utils<IAnimationUtils>()->GetStringFromEventTrigger (applicableList[0], contentType);
		}
		else if (numTriggerEvents == 0 && enableView)
		{
			eventInfo = PMString ("kAnimationUIChoose");
		}
		else
		{
			bool unique = true;
			PMString eventSeparator("kAnimationUIEventSeparator", PMString::kTranslateDuringCall);
			for (int32 i = 0; i < numTriggerEvents; ++i)
			{
				bool triggerIsNotMixed = iAttrSuite->GetNthAnimationTriggerEvent (i, triggerType);
				if (iEventInfoList) iEventInfoList->Append (triggerType);

				if (unique && triggerIsNotMixed)
				{
					PMString nthEventInfo = Utils<IAnimationUtils>()->GetStringFromEventTrigger (triggerType, contentType);
					nthEventInfo.Translate();

					if (i > 0)
						eventInfo.Append(eventSeparator);

					eventInfo.Append(nthEventInfo);
				}
				else if (unique)
				{
					unique = triggerIsNotMixed;
				}
			}
			if (!unique)
			{
				eventInfo = PMString ("kAnimationUIMixed", PMString::kTranslateDuringCall);
			}

			eventInfo.SetTranslatable(kFalse);
		}
		
		InterfacePtr<ITextControlData> iEventInfoData(iEventInfoView, UseDefaultIID());
		iEventInfoData->SetString(eventInfo, kTrue, kFalse);

		InterfacePtr<IIntData> iNumTriggers(iEventInfoView, IID_IANIMATIONTRIGGERTYPEDATA);
		iNumTriggers->Set(numTriggerEvents);

		//	Disable/enable group view
		IControlView* iEventGroupView = iPanelControlData->FindWidget(kAnimationUIEventGroupWID);
		iEventGroupView->Enable (enableView);

	}

	void _UpdateAnimationOnRollOff (IAnimationAttributeSuite* iAttrSuite, EventTriggerType const &triggerType) const
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* iOnRollOffCheckboxView = iPanelControlData->FindWidget(kAnimationUIOnRollOffCheckboxWID);

		if (triggerType == kOnSelfRollover)
			iOnRollOffCheckboxView->Enable();
		else
			iOnRollOffCheckboxView->Disable();

		// Update the widget
		InterfacePtr<ITriStateControlData> iWidgetData (iOnRollOffCheckboxView, UseDefaultIID());
		if (triggerType == kOnSelfRollover)
		{
			bool doReverse = false;
			bool unique = iAttrSuite->GetReverseAnimationForEvent (triggerType, doReverse);
			if (!unique)
				iWidgetData->SetState (ITriStateControlData::kUnknown, kTrue, kFalse);
			else
				iWidgetData->SetState (doReverse ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue, kFalse);
		}
		else
		{
			iWidgetData->SetState (ITriStateControlData::kUnselected, kTrue, kFalse);
		}
	}

	void _UpdateLabelString(PMString const &labelString, WidgetID const &widgetID, bool doEnable) const
	{
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
		IControlView* iLabelView = iPanelControlData->FindWidget(widgetID);
		iLabelView->Enable (doEnable);

		InterfacePtr<ITextControlData> iLabelData(iLabelView, UseDefaultIID());
		iLabelData->SetString(labelString, kTrue, kFalse);
	}

	void _UpdateAnimationDuration (IAnimationAttributeSuite* iAttrSuite) const
	{
		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();

		PMReal value = 1.0;	
		bool unique = iAttrSuite ? iAttrSuite->GetAnimationDuration (value) : false;
		_SetValueInILEWidget(kAnimationUIDurationILEWID, value, !unique, enableView, false);	

		//
		// Update singular to plural form and vice versa.
		//
		PMString labelString = (value > 1) ? PMString("kAnimationUISecondsStaticTextLabel") : PMString("kAnimationUISecondStaticTextLabel");
		_UpdateLabelString(labelString, kAnimationUIDurationSecondLabelWID, enableView);

		//	Update control label
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
		IControlView* iLabelView = iPanelControlData->FindWidget(kAnimationUIDurationLabelWID);
		iLabelView->Enable (enableView);
	}

	void _UpdateAnimationPlays (IAnimationAttributeSuite* iAttrSuite) const
	{		
		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();

		uint32 plays = 1;
		bool unique = iAttrSuite ? iAttrSuite->GetAnimationPlays (plays) : false;		
		_SetValueInILEWidget(kAnimationUIPlayILEWID, plays, !unique, enableView , false);	

		//
		// Update singular to plural form and vice versa.
		//
		PMString labelString = (plays > 1) ?	PMString("kAnimationUITimesStaticTextLabel") : PMString("kAnimationUITimeStaticTextLabel");
		_UpdateLabelString(labelString, kAnimationUITimeLabelWID, enableView );

		//	Update control label
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
		IControlView* iLabelView = iPanelControlData->FindWidget(kAnimationUIPlayLabelWID);
		iLabelView->Enable (enableView);
	}

	void _UpdateAnimationPlaysLoop (IAnimationAttributeSuite* iAttrSuite) const
	{
		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();

		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* iLoopView = iPanelControlData->FindWidget(kAnimationUILoopCheckboxWID);
		iLoopView->Enable (enableView);
		
		InterfacePtr<ITriStateControlData>	iLoopData(iLoopView, UseDefaultIID ()); 

		bool bLoop = false;
		bool unique = iAttrSuite ? iAttrSuite->GetAnimationPlaysLoop (bLoop) : false;
		
		if (unique)
			iLoopData->SetState (bLoop ? (ITriStateControlData::kSelected) : (ITriStateControlData::kUnselected), kTrue, kFalse);
		else
			iLoopData->SetState (ITriStateControlData::kUnknown, kTrue, kFalse);

		//
		// Enable/Disable the play value
		//
  		IControlView* iAnimationUIPlayView = iPanelControlData->FindWidget(kAnimationUIPlayILEWID);
		iAnimationUIPlayView->Enable((enableView && !bLoop));
	}

	bool _GetAnimationOpacityString (IAnimationAttributeSuite* iAttrSuite, PMString& opacityString) const
	{
		opacityString = PMString ("kAnimationUIFromPreset");
		PMString opacityFromPresetString = opacityString;
		uint32 nKeyFrames;
		bool unique = iAttrSuite->GetNumKeyFrames (IAnimationAttributeSuite::kAnimationOpacity, nKeyFrames);
		if (!unique)
		{
			opacityString = PMString ("");
		}
		else if (nKeyFrames == 0)
		{
			opacityString = PMString ("kAnimationUINone");
		}
		else if (nKeyFrames > 0 && nKeyFrames <= 2)
		{
			PMReal value1 = 100.0;
			PMReal value2 = 100.0;
			iAttrSuite->GetValueAtKeyFrame(IAnimationAttributeSuite::kAnimationOpacity, 0, value1);
			if (nKeyFrames > 1)
			{
				uint32 keyframe = 0;
				iAttrSuite->GetKeyFrame(IAnimationAttributeSuite::kAnimationOpacity, 1, keyframe, value2);
			}
			if (value1 == 100.0 && value1 == value2)
			{
				opacityString = PMString ("kAnimationUINone");
			}
			else if (value1 == 100.0 && value2 <= 1.0)
			{
				opacityString = PMString ("kAnimationUIFadeOut");
			}
			else if (value1 <= 1.0 && value2 == 100.0)
			{
				opacityString = PMString ("kAnimationUIFadeIn");
			}
		}

		//	show "Custom" if no preset has been applied.
		UID presetUID = kInvalidUID;
		if (opacityString == PMString ("kAnimationUIFromPreset") &&
			iAttrSuite->GetMotionPresetApplied (presetUID) && presetUID == kInvalidUID)
		{
			opacityString = PMString ("kAnimationUICustomPreset");
		}
		return unique;
	}

	void _UpdateAnimationOpacity (IAnimationAttributeSuite* iAttrSuite) const
	{		
		PMString opacityString;
		bool unique = _GetAnimationOpacityString (iAttrSuite, opacityString);
		PMString opacityFromPresetString = PMString ("kAnimationUIFromPreset");
		if (opacityString == opacityFromPresetString)
		{
			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUIPropertyOpacityDropDownWID, opacityFromPresetString, true);
		}
		else if (opacityString == PMString ("kAnimationUICustomPreset"))
		{
			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUIPropertyOpacityDropDownWID, opacityString, true);
		}
		else
		{
			//	Remove custom entries if exist.
			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUIPropertyOpacityDropDownWID, opacityFromPresetString, false);
			_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUIPropertyOpacityDropDownWID, PMString ("kAnimationUICustomPreset"), false);

			InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID ());
			IControlView* iOpDDListView = iPanelControlData->FindWidget(kAnimationUIPropertyOpacityDropDownWID);

   			InterfacePtr<IStringListControlData> iOpDDListData (iOpDDListView, UseDefaultIID());
			InterfacePtr<IDropDownListController> iOpDDListController (iOpDDListView, UseDefaultIID());
			
			if (!unique)
			{
				iOpDDListController->Select (IDropDownListController::kNoSelection, kTrue, kFalse);
			}
			else
			{
				PMString translatedOpacityString(opacityString);
				translatedOpacityString.Translate();
				int32 index = iOpDDListData->GetIndexOfPartialString (translatedOpacityString, kTrue);
				if (index >= 0)
					iOpDDListController->Select (index, kTrue, kFalse);
				else
					iOpDDListController->Select (IDropDownListController::kNoSelection, kTrue, kFalse);
			}
		}
	}

	void _UpdateAnimationSpeed (IAnimationAttributeSuite* iAttrSuite) const
	{
		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();

		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID ());
		IControlView* iSpeedDropDownView = iPanelControlData->FindWidget(kAnimationUISpeedDropDownWID);
		iSpeedDropDownView->Enable (enableView);
 
		IControlView* iLabelView = iPanelControlData->FindWidget(kAnimationUISpeedLabelWID);
		iLabelView->Enable (enableView);

		InterfacePtr<IStringListControlData> iDropDownStringData(iSpeedDropDownView, UseDefaultIID());
		InterfacePtr<IDropDownListController> iSpeedDDListController(iSpeedDropDownView, UseDefaultIID());

		PMString easeString ("kAnimationUIFromPreset");
		PMString easeFromPresetString = easeString;

		AnimationEaseType easeType = kNoEase;
		if (iAttrSuite)
		{
			int32 index = -1;
			bool unique = iAttrSuite->GetSimpleEaseType(easeType);
			if (!unique)
			{
				iSpeedDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
			}
			else if (easeType == kEaseCustomReadOnly)
			{
				_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUISpeedDropDownWID, easeFromPresetString, true);
				index = iDropDownStringData->GetIndexOfPartialString(PMString("kAnimationUIFromPreset", PMString::kTranslateDuringCall), kTrue);
			}
			else
			{
				_UpdateDropDownListCustomEntries(iAttrSuite, kAnimationUISpeedDropDownWID, easeFromPresetString, false);

				if (easeType == kEaseIn)
					index = iDropDownStringData->GetIndexOfPartialString(PMString("kAnimationUIEaseIn", PMString::kTranslateDuringCall), kTrue);
				else if (easeType == kEaseOut)
					index = iDropDownStringData->GetIndexOfPartialString(PMString("kAnimationUIEaseOut", PMString::kTranslateDuringCall), kTrue);
				else if (easeType == kEaseInAndOut)
					index = iDropDownStringData->GetIndexOfPartialString(PMString("kAnimationUIEaseInAndOut", PMString::kTranslateDuringCall), kTrue);
				else if (easeType == kNoEase)
					index = iDropDownStringData->GetIndexOfPartialString(PMString("kAnimationUINone", PMString::kTranslateDuringCall), kTrue);
			}

			if (index >= 0)
				iSpeedDDListController->Select(index, kTrue, kFalse);
			else
				iSpeedDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
		}
		else
		{
			iSpeedDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
		}
	}

	void _UpdateVisibility (IAnimationAttributeSuite* iAttrSuite, const WidgetID& visibilityWID) const
	{
		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID ());
		IControlView* iVisibleCBView = iPanelControlData->FindWidget(visibilityWID);

		bool unique = false;
		bool visibilityOn = false;
		if (visibilityWID == kAnimationUIHideBeforeAnimateCheckboxWID)
			unique = iAttrSuite->GetAnimationHideInitially (visibilityOn);
		else
			unique = iAttrSuite->GetAnimationHideAfter (visibilityOn);

		InterfacePtr<ITriStateControlData>	iVisibleData (iVisibleCBView, UseDefaultIID ()); 
		if (unique)
			iVisibleData->SetState(visibilityOn ? (ITriStateControlData::kSelected) : (ITriStateControlData::kUnselected), kTrue, kFalse);
		else
			iVisibleData->SetState(ITriStateControlData::kUnknown, kTrue, kFalse);
	
		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();
		IControlView* iVisibleGroupView = iPanelControlData->FindWidget(kAnimationUIVisibilityGroupWID);
		iVisibleGroupView->Enable (enableView);
		iVisibleCBView->Enable (enableView);	//	Overkill but on the mac, this is not getting updated correctly.
	}

	void _UpdateShowProxySetting (IAnimationAttributeSuite* iAttrSuite) const
	{
		bool showProxy = iAttrSuite->GetShowAnimationProxy ();
		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID ());
		IControlView* iShowProxyButton = iPanelControlData->FindWidget(kAnimationUIShowProxyButtonWID);
		InterfacePtr<ITriStateControlData> iShowProxyData (iShowProxyButton, UseDefaultIID());
		iShowProxyData->SetState(showProxy ? (ITriStateControlData::kSelected) : (ITriStateControlData::kUnselected), kTrue, kFalse);

		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();
		iShowProxyButton->Enable (enableView);
	}
	
	void _UpdateDesignSetting (IAnimationAttributeSuite* iAttrSuite) const
	{
		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID ());
		IControlView* iDesignDDView = iPanelControlData->FindWidget(kAnimationUIPropertyDesignDropDownWID);

   		InterfacePtr<IStringListControlData> iDDStringData(iDesignDDView, UseDefaultIID());
		InterfacePtr<IDropDownListController> iDesignDDListController(iDesignDDView, UseDefaultIID());

		AnimationOptions animateOption = kAnimateFrom;

		if (iAttrSuite)
		{
			int32 index = -1;
			bool unique = iAttrSuite->GetAnimateOption(animateOption);
			if (!unique)
				index = -1;
			else if (animateOption == kAnimateFrom)
				index = iDDStringData->GetIndexOfPartialString(PMString("kAnimationUIFrom", PMString::kTranslateDuringCall), kTrue);
			else if (animateOption == kAnimateTo)
				index = iDDStringData->GetIndexOfPartialString(PMString("kAnimationUITo", PMString::kTranslateDuringCall), kTrue);
			else if (animateOption == kAnimateOffset)
				index = iDDStringData->GetIndexOfPartialString(PMString("kAnimationUIOffset", PMString::kTranslateDuringCall), kTrue);

			if (index >= 0)
				iDesignDDListController->Select(index, kTrue, kFalse);
			else
				iDesignDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
		}
		else
		{
			iDesignDDListController->Select(IDropDownListController::kNoSelection, kTrue, kFalse);
		}

		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();
		IControlView* iDesignGroup = iPanelControlData->FindWidget(kAnimationUIDesignGroupWID);
		iDesignGroup->Enable (enableView);
		iDesignDDView->Enable (enableView);

		// Update design setting info label.
		_UpdateLabelString(animateOption == kAnimateTo ? PMString("kAnimationFromStaticTextLabel")  : PMString("kAnimationToStaticTextLabel"), kAnimationUIPropertyDesignInfoLabelWID, true);

	}

	//	Value is considered mixed for the following conditions:
	//		1. if multiple selection
	//		2. if there are more than two keyframes
	//		3. if two or less keyframes and the first firame is not source value.
	//			For scales, source value is 100.0 and rotation is 0.0.
	bool _GetPropertyValue (IAnimationAttributeSuite* iAttrSuite, IAnimationAttributeSuite::PropertyType type, const PMReal& srcValue, PMReal& valueToSet) const
	{
		bool valueIsMixed = true;
		uint32 keyframe = 0;

		uint32 nFrames = 0;
		bool unique = iAttrSuite->GetNumKeyFrames (type, nFrames);
		if (unique && nFrames == 0)
		{
			//	property does not exist, implies values not changed over time.
			valueIsMixed = false;
		}
		else if (nFrames <= 2)
		{
			//	Get value for keyframe = 0
			if (iAttrSuite->GetValueAtKeyFrame(type, keyframe, valueToSet))
			{
				if (valueToSet == srcValue)
				{
					valueIsMixed = false;
					if (nFrames > 1)
					{
						iAttrSuite->GetKeyFrame(type, nFrames-1, keyframe, valueToSet);
					}
				}
			}
		}
		return valueIsMixed;
	}

	void _UpdateProperties (IAnimationAttributeSuite* iAttrSuite) const
	{	
		//	Scale x
		PMReal valueX = 100.0;
		bool scalexIsMixed = _GetPropertyValue (iAttrSuite, IAnimationAttributeSuite::kAnimationScaleX, 100.0, valueX);
		_SetValueInILEWidget(kAnimationUIScaleHorzILEWID, valueX, scalexIsMixed, true, false);	

		//	Scale Y
		PMReal valueY = 100.0;
		bool scaleyIsMixed = _GetPropertyValue (iAttrSuite, IAnimationAttributeSuite::kAnimationScaleY, 100.0, valueY);
		_SetValueInILEWidget(kAnimationUIScaleVertILEWID, valueY, scaleyIsMixed, true, false);	

		//	Rotation
		PMReal value = 0.0;
		bool valueIsMixed = _GetPropertyValue (iAttrSuite, IAnimationAttributeSuite::kAnimationRotation, 0.0, value);
		_SetValueInILEWidget(kAnimationUIRotateILEWID, value, valueIsMixed, true, false);
	}

	void _GetValueFromILEWidget(WidgetID const &widgetID, PMReal &value) const
	{		
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView *iControlView = iPanelControlData->FindWidget(widgetID);

		InterfacePtr<ITextValue> iTextValue (iControlView, UseDefaultIID ());
		InterfacePtr<IPanelControlData> iInlinePanelData(iControlView, UseDefaultIID()); 
		if (!iTextValue && iInlinePanelData)
		{
			IControlView * iInlineStaticView = iInlinePanelData->FindWidget(kInLineEditStaticTextWidgetID); 
			iTextValue = InterfacePtr<ITextValue> (iInlineStaticView, UseDefaultIID());
		}

		ASSERT (iTextValue != nil);
		value = iTextValue->GetTextAsValue();
	}

	void _SetValueInILEWidget(WidgetID const &widgetID, PMReal const & newValue, bool valueIsBlank, bool enable, bool doNotify) const
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* iILEWidgetView = iPanelControlData->FindWidget(widgetID);
		iILEWidgetView->Enable (enable);

		InterfacePtr<ITextValue> iTextValue (iILEWidgetView, UseDefaultIID ());
		InterfacePtr<IPanelControlData> iInlinePanelData(iILEWidgetView, UseDefaultIID()); 
		if (!iTextValue && iInlinePanelData)
		{
			IControlView * iInlineStaticView = iInlinePanelData->FindWidget(kInLineEditStaticTextWidgetID); 
			iTextValue = InterfacePtr<ITextValue> (iInlineStaticView, UseDefaultIID()); 
		}

		ASSERT (iTextValue != nil);
		if (!valueIsBlank)
		{
			bool16 isBlankEntry = false;
			PMReal oldValue = iTextValue->GetTextAsValue(&isBlankEntry);
			if (isBlankEntry || !doNotify || oldValue != newValue)
			{
				iTextValue->SetTextFromValue(newValue, kTrue, doNotify);
			}
		}
		else
		{
			InterfacePtr<ITextControlData> iTextData (iTextValue, UseDefaultIID ());
			if (iTextData)
				iTextData->SetString (PMString (), kTrue, doNotify);
		}
	}

	void _UpdateDropDownListCustomEntries(IAnimationAttributeSuite* iAttrSuite, WidgetID const &widgetID, PMString const &customString, bool const &bAdd) const
	{
		ASSERT(widgetID != kAnimationUIPresetDropDownWID);
		
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
   		IControlView* iControlView = iPanelControlData->FindWidget(widgetID);
   
   		InterfacePtr<IStringListControlData> iDropDownStringData(iControlView, UseDefaultIID());

		PMString translatedCustomString(customString);
		if (!translatedCustomString.HasTranslated())
			translatedCustomString.Translate();	
		int32 index = iDropDownStringData->GetIndexOfPartialString(translatedCustomString, kTrue);

   		InterfacePtr<IDropDownListController> iDDListController(iDropDownStringData, UseDefaultIID());

		if (bAdd)
		{
			if (index < 0)
			{
				iDropDownStringData->AddString(customString, IStringListControlData::kBeginning, kTrue, kFalse);
				iDDListController->Select(0, kTrue, kFalse);
			}
			else
			{
				iDDListController->Select(index, kTrue, kFalse);
			}
		}
		else
		{
			if (index >= 0)
			{
				iDropDownStringData->RemoveString(index, kTrue, kFalse);
			}
		}
	}

	void _UpdateScaleValue(bool const bOn) const 
	{
		//
        // If chained, set horizontal and vertical scale values the same.
		//
		InterfacePtr<IControlView> iPanelView(this, UseDefaultIID());	
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* iIconView = iPanelControlData->FindWidget (kAnimationUIScaleLockButtonWID); 
		if (bOn)
		{
			if (iIconView->GetRsrcID() == kAnimationUIScaleUnlockIcon)
				iIconView->SetRsrcID(kAnimationUIScaleLockIcon);
			else
				iIconView->SetRsrcID(kAnimationUIScaleUnlockIcon);
		
			PMReal newValue(100);

			_GetValueFromILEWidget(kAnimationUIScaleHorzILEWID, newValue);
			_SetValueInILEWidget(kAnimationUIScaleVertILEWID, newValue, false, true, true);	// we pass true to apply newValue to vert scale
        } 
	}

	void _UpdateXFormOffsetProxy (IAnimationAttributeSuite* iAttrSuite) const
	{
		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID());
		IControlView* iXFProxyWidget = iPanelControlData->FindWidget (kAnimationUIXFPointProxyWID);

		InterfacePtr<IProxyWidgetAttributes> iXFProxyAttr (iXFProxyWidget, UseDefaultIID ());

		bool unique = false;
		bool enableView = true;
		PMPoint offsetPoint (0,0);
		if (iAttrSuite)
		{
			unique = iAttrSuite->GetAnimationTranformOffsetPoint (offsetPoint);
			enableView = iAttrSuite->HasAnimationApplied ();
		}
		
		if (unique)
		{
			IReferencePointData::ReferencePointPosition position = _GetReferencePositionFromXFormPoint (offsetPoint);
			iXFProxyAttr->SetProxyPosition (position);
		}
		else
		{
			iXFProxyAttr->SetProxyPosition (IReferencePointData::kUninitializedReferencePointPosition);
		}

		//	Disable/enable widget and its static label.
		IControlView* iProxyLabel = iPanelControlData->FindWidget (kAnimationUIXFPointProxyLabelWID);
		if (iProxyLabel) iProxyLabel->Enable (enableView);
		
		iXFProxyWidget->Enable (enableView);
	}

	IReferencePointData::ReferencePointPosition _GetReferencePositionFromXFormPoint (const PMPoint& offsetPoint) const
	{
		for (int32 n = 0; n < kNumProxyPoints; n++)
		{
			PMPoint result = kProxyPoints [n] - offsetPoint;
			if (std::fabs(::ToDouble(result.X ())) < 0.01 && std::fabs(::ToDouble(result.Y())) < 0.01) 
				return static_cast<IReferencePointData::ReferencePointPosition> (n);
		}
		return IReferencePointData::kOtherReferencePointPosition;
	}

	void _UpdateTrashIcon (IAnimationAttributeSuite* iAttrSuite) const
	{
		bool enableView = iAttrSuite && iAttrSuite->HasAnimationApplied ();
		
		InterfacePtr<IPanelControlData> iPanelControlData (this, UseDefaultIID());
		IControlView* iTrashIconView = iPanelControlData->FindWidget (kAnimationUIClearAnimationButtonWID);
		iTrashIconView->Enable (enableView);
	}

	void _UpdatePanelSize(bool const bToggle) const
	{
		bool showPreview = false;
		bool showPropertySubPanel = false;

		InterfacePtr<IControlView> iPanelView(this, UseDefaultIID());	
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* iPropertyMainPanelView = iPanelControlData->FindWidget (kAnimationUIPreviewGroupWID);
		if (iPropertyMainPanelView->IsVisible ()) showPreview = true;
	
		IControlView* iTreeExpanderIconView = iPanelControlData->FindWidget (kAnimationUIPropertyExpanderWidgetIconWID); 
		if (bToggle)
		{
			if (iTreeExpanderIconView->GetRsrcID() == kTreeBranchCollapsedRsrcID)
				iTreeExpanderIconView->SetRsrcID(kTreeBranchExpandedRsrcID);
			else
				iTreeExpanderIconView->SetRsrcID(kTreeBranchCollapsedRsrcID);
		}

		RsrcID currentRsrcID = iTreeExpanderIconView->GetRsrcID();
		if (currentRsrcID == kTreeBranchExpandedRsrcID) 
			showPropertySubPanel = true;

		int16 detailLevel = ddui_utils::MapAnimationPanelDetailLevel (showPreview, showPropertySubPanel);
		InterfacePtr<IPanelDetailController> iPanelDetail(this, UseDefaultIID());
		if (iPanelDetail)
			iPanelDetail->ShowDetailLevel (detailLevel);
		else
			ddui_utils::UpdateAnimationPanelSize (iPanelView, showPreview, showPropertySubPanel);
	}

	void _UpdatePreviewButton ( ) const
	{
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());
		InterfacePtr<IControlView> iPreviewButtonView(iPanelControlData->FindWidget(kAnimationUIPreviewButtonWID), UseDefaultIID());
		
		IActiveContext *ac = GetExecutionContextSession()->GetActiveContext();
		InterfacePtr<ILayoutControlData> iLayoutControlData(ac->GetContextView(), UseDefaultIID());
		
		if (!iLayoutControlData || !fCurrentSelection)
			iPreviewButtonView->Disable();
		else
			iPreviewButtonView->Enable();
	}

	void _ShowTimingPanel () const
	{
		InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication()); 
		InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager()); 
		if (!iPanelMgr->IsPanelWithWidgetIDShown(kTimingPanelWidgetID)) 
		{
			iPanelMgr->ShowPanelByWidgetID(kTimingPanelWidgetID);
		}

		if (iPanelMgr->IsPanelWithWidgetIDShown (kTimingPanelWidgetID))
		{
			InterfacePtr<IPanelControlData> iTimingPanelData (Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kTimingPanelWidgetID)); 
			InterfacePtr<IControlView> iTimingPanelView (iTimingPanelData, UseDefaultIID());
			if (iTimingPanelView)
			{
				PaletteRef timingPaletteRef = iPanelMgr->GetPaletteRefContainingPanel (iTimingPanelView);
				PaletteRefUtils::BringPaletteToFront (timingPaletteRef);
			}
		}
	}

	void __UpdateWidgetsToDefinition (IAnimationAttributeSuite* iAttrSuite) 
	{
		if (iAttrSuite == nil) return;

		_UpdateAnimationName (iAttrSuite);
		
		//	_UpdateEventInfo returns the last trigger type updated for the event info.
		//	So if the selection has any button event, then we will never be able to access
		//	rolloff checkbox.
		//	For initialization, this is probably OK since user can use the event popup to select the
		//	self event.
		_UpdateEventInfo(iAttrSuite);

		//	Determine how to update reverse animation checkbox.
		uint32 nTriggers = 0;
		EventTriggerType triggerType = kNoTriggerEvent;
		iAttrSuite->GetNumAnimationTriggerEvents (nTriggers);
		if (nTriggers > 0)
		{
			bool canEnableReverseRolloffCB = false;
			for (int32 n = 0; n < nTriggers; n++)
			{
				iAttrSuite->GetNthAnimationTriggerEvent (n, triggerType);
				if (triggerType == kOnSelfRollover) canEnableReverseRolloffCB = true;
			}
			triggerType = (canEnableReverseRolloffCB) ? kOnSelfRollover : kNoTriggerEvent;
		}
		_UpdateAnimationOnRollOff (iAttrSuite, triggerType);

		_UpdateAnimationDuration (iAttrSuite);

		_UpdateAnimationPlays (iAttrSuite);

		_UpdateAnimationPlaysLoop (iAttrSuite);

		_UpdateAnimationSpeed (iAttrSuite);
		
		//
		// The following is to update the properties.
		//
		_UpdateVisibility (iAttrSuite, kAnimationUIHideAfterAnimateCheckboxWID);		
		_UpdateVisibility (iAttrSuite, kAnimationUIHideBeforeAnimateCheckboxWID);		

		_UpdateDesignSetting (iAttrSuite);		

		_UpdateProperties(iAttrSuite);

		_UpdateAnimationOpacity (iAttrSuite);
		_UpdateXFormOffsetProxy (iAttrSuite);

		// Put the update of presets to the end since properties/during/speed change will trigger Preset to show Custom.
		_UpdatePresetStaticText(iAttrSuite);

		_UpdatePreviewProxy (iAttrSuite);

		_UpdatePreviewButton();

		_UpdateShowProxySetting (iAttrSuite);

		_UpdateTrashIcon (iAttrSuite);
	}

	void __EnableWidgets (bool doEnable, bool doEnablePreset, bool doEnableConvert) const
	{			
		InterfacePtr<IPanelControlData const> iPanelControlData(this, UseDefaultIID());

		//
		// Enable/Disable widgets related to CanApplyAnimation() --- name, settings and property group widgets.
		//
		InterfacePtr<IControlView> iNameGroupView(iPanelControlData->FindWidget(kAnimationUINameGroupWID), UseDefaultIID());
		InterfacePtr<IControlView> iPresetSettingsView(iPanelControlData->FindWidget(kAnimationUIPresetSettingsGroupWID), UseDefaultIID());		
		InterfacePtr<IControlView> iPropertySubPanelView(iPanelControlData->FindWidget(kAnimationUIPropertySubPanelGroupWID), UseDefaultIID());		

		iNameGroupView->Enable(doEnable);
		iPresetSettingsView->Enable(doEnable);
		iPropertySubPanelView->Enable(doEnable);

		//
		// Enable/Disable widgets related to CanApplyMotionPreset() --- preset dropdown.
		//
		InterfacePtr<IControlView> iPresetGroupView(iPanelControlData->FindWidget(kAnimationUIPresetGroupWID), UseDefaultIID());
		iPresetGroupView->Enable(doEnablePreset);

		//
		// Enable/Disable Convert to Motion Path button.
		//
		InterfacePtr<IControlView> iConvertToMotionPathButtonView(iPanelControlData->FindWidget(kAnimationUIConvertToMotionPathButtonWID), UseDefaultIID());
		if (iConvertToMotionPathButtonView)
			iConvertToMotionPathButtonView->Enable(doEnableConvert);
		InterfacePtr<IControlView> iPropertyTitleGroupView(iPanelControlData->FindWidget(kAnimationUIPropertyTitleGroupWID), UseDefaultIID());
		if (iPropertyTitleGroupView)
			iPropertyTitleGroupView->Enable(doEnable);

		InterfacePtr<IControlView> iShowTimingView(iPanelControlData->FindWidget(kAnimationUIShowTimingButtonWID), UseDefaultIID());
		if (iShowTimingView)
			iShowTimingView->Enable(doEnable);

		InterfacePtr<IControlView> iPreviewButtonView(iPanelControlData->FindWidget(kAnimationUIPreviewButtonWID), UseDefaultIID());
		if (iPreviewButtonView)
			iPreviewButtonView->Enable(doEnable);


	}
};



CREATE_PMINTERFACE(AnimationPanelObserver, kAnimationPanelObserverImpl)


