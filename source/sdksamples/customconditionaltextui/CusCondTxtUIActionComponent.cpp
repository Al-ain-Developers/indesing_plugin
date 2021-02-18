//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTxtUIActionComponent.cpp $
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
#include "IWorkspace.h"
#include "IPanelControlData.h"
#include "IPalettePanelUtils.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"
#include "IConditionalTextFacade.h"
#include "IActionStateList.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Project includes:
#include "CusCondTxtUIID.h"
#include "ITextControlData.h"
#include "ICusCondTxtSuite.h"


/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.

	
	@ingroup customconditionaltext

*/
class CusCondTxtActionComponent : CActionComponent
{
public:
		/**
		 Constructor.
		 @param boss interface ptr from boss object on which this interface is aggregated.
		 */
		CusCondTxtActionComponent(IPMUnknown* boss);

		/** Called by the framework to allow actions to be enabled or disabled
			dependent on the capability of the selection.
			@param ac context in which the action is to be performed.
			@param listToUpdate list containing items to be enabled disabled.
			@param mousePoint ontains the global mouse location at time of event causing action (e.g. context menus), kInvalidMousePoint otherwise.
			@param widget the widget that invoked the action or nil otherwise
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
		
		/** The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param ac active context
			@param actionID identifies the menu item that was selected.
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();
		
		/** List the conditions applied on selected text. */
		void ListConditions(IActiveContext* ac);
	
		/** List the text which is hidden with conditions applied. */
		void ListHiddenText(IActiveContext* ac);
		
		/** 
			@param panelWidgetID represents the widget ID of the panel
			@param widgetID represents the widget ID of the widget on the panel
			@return the interface pointer of the widget.
		 */
		 IControlView* GetWidgetOnPanel(const WidgetID& panelWidgetID, const WidgetID& widgetID);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CusCondTxtActionComponent, kCusCondTxtUIActionComponentImpl)

/* CusCondTxtActionComponent Constructor
*/
CusCondTxtActionComponent::CusCondTxtActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/*
*/
void CusCondTxtActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do {			
		ASSERT(listToUpdate);
		if(listToUpdate == nil) {
			break;
		}
		InterfacePtr<ICusCondTxtSuite> cusCondTxtSuite(ac->GetContextSelection(), UseDefaultIID()); 
		ASSERT(cusCondTxtSuite);
		if (cusCondTxtSuite == nil) {
			break;
		}

		for(int32 i = 0; i < listToUpdate->Length(); i++) 
		{
			ActionID actionID = listToUpdate->GetNthAction(i);
			switch (actionID.Get())
			{
				case kCusCondTxtUIListConditionsActionID:
				case kCusCondTxtUIListHiddenTextActionID:
				{
					if(cusCondTxtSuite->CanGetConditionalData() == kTrue) {
						listToUpdate->SetNthActionState(i, kEnabledAction);
					}
					else {
						listToUpdate->SetNthActionState(i, kDisabled_Unselected);
					}
					break;
				}

				default: 
				{
					break;
				}
			} // end switch

		} // end for

	} while(false);
}

/* DoAction
*/
void CusCondTxtActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{

		case kCusCondTxtUIPopupAboutThisActionID:
		case kCusCondTxtUIAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kCusCondTxtUIListConditionsActionID:
		{
			ListConditions(ac);
			break;
		}
		
		case kCusCondTxtUIListHiddenTextActionID:
		{
			ListHiddenText(ac);
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void CusCondTxtActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kCusCondTxtUIAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}

void CusCondTxtActionComponent::ListConditions(IActiveContext* ac)
{
	do {
		IControlView* multiLineView = GetWidgetOnPanel(kCusCondTxtPanelWidgetID, kCusCondTxtMultiLineStaticTextWidgetID);
		if(!multiLineView)
			break;
				
		InterfacePtr<ITextControlData> textControlData(multiLineView, UseDefaultIID());
		if(!textControlData)
			break;
		
		//clear the text on this widget
		PMString text("");
		text.SetTranslatable(kFalse);
		textControlData->SetString(text);
		
		InterfacePtr<ICusCondTxtSuite> cusCondTxtSuite(ac->GetContextSelection(),UseDefaultIID());
		if(!cusCondTxtSuite)
			break;
	
		K2Vector<ConditionTagInfo> conTags;
		if(cusCondTxtSuite->GetConditionTags(conTags) != kSuccess)
			break;
			
		IDataBase* database = ::GetDataBase(ac->GetContextWorkspace());
		ASSERT(database);
		
		for(int32 i = 0; i < conTags.size(); i++)
		{
			ConditionTagInfo& conTag = conTags[i];
			text.AppendNumber(conTag.textStart);
			text.Append(',');
			text.AppendNumber(conTag.textEnd);
			text.Append('\n');
			for(int32 j = 0; j < conTag.tagUIDs.size(); j++)
			{
				WideString conditionName;
				if(Utils<Facade::IConditionalTextFacade>()->GetConditionName(UIDRef(database, conTag.tagUIDs[j]), conditionName) == kSuccess)
				{
					text.Append(conditionName);
					text.Append('\n');
				}
			}
		}
		
		text.SetTranslatable(kFalse);
		textControlData->SetString(text);
	} while(false);
}
	
void CusCondTxtActionComponent::ListHiddenText(IActiveContext* ac)
{
	do {
		IControlView* multiLineView = GetWidgetOnPanel(kCusCondTxtPanelWidgetID, kCusCondTxtMultiLineStaticTextWidgetID);
		if(!multiLineView)
			break;
				
		InterfacePtr<ITextControlData> textControlData(multiLineView, UseDefaultIID());
		if(!textControlData)
			break;

		PMString text("");
		text.SetTranslatable(kFalse);
		textControlData->SetString(text);
			
		InterfacePtr<ICusCondTxtSuite> cusCondTxtSuite(ac->GetContextSelection(),UseDefaultIID());
		if(!cusCondTxtSuite)
			break;
	
		WideString hiddenText;
		if(cusCondTxtSuite->GetHiddenConditionalText(hiddenText) != kSuccess)
			break;
			
		text = hiddenText;
		text.SetTranslatable(kFalse); 

		textControlData->SetString(text);
			
	} while(false);
}

/* 
*/
IControlView* CusCondTxtActionComponent::GetWidgetOnPanel(const WidgetID& panelWidgetID, const WidgetID& widgetID)
{
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(panelWidgetID));	
	// Don't assert, fail silently, the panel may be closed.
	if(panelData == nil) {
		return nil;
	}
	
	IControlView* controlView = panelData->FindWidget(widgetID);
	ASSERT(controlView);
	return controlView;
}


//  Code generated by DollyXs code generator
