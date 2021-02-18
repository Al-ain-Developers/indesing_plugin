//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customactionfilter/CstAFltActionComponent.cpp $
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
#include "IActionManager.h"
#include "IActiveContext.h"
#include "IApplication.h"
#include "IDocument.h"
#include "ActionMapper.h"
#include "DebugClassUtils.h"
#include "IGenStlEdtListMgr.h"
#include "PDFID.h"
#include "IWorkspace.h"
#include "IActionIDToUIDData.h"
#include "K2Pair.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "LocaleSetting.h"
#include "IActionStateList.h" // not an interface!
#include "AppUIID.h" // for actionIDs and boss classes

// Project includes:
#include "CstAFltID.h"
#include "CstAFltActionFilter.h"


/** implements the actions that are executed when the plug-in's menu items are selected.
 * 	@ingroup customactionfilter
 * 	@author Ken Sadahiro
*/
class CstAFltActionComponent : public CActionComponent
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CstAFltActionComponent(IPMUnknown* boss);

	/**	The action component should do the requested action.
		This is where the menu item's action is taken.
		When a menu item is selected, the Menu Manager determines
		which plug-in is responsible for it, and calls its DoAction
		with the ID for the menu item chosen.

		@param actionID identifies the menu item that was selected.
		@see CActionComponent::DoAction
	*/
	virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	/** Called when the action component is asked to update a list of actions to the proper state.
		This method is required to be overridden by subclasses only if there are action components with 
		kCustomEnabling specified.

		The list of actions is intially disabled and unselected, so it only has to be
		changed if this state is not correct. Note that action components are never asked to update
		actions that don't belong to them, or actions they have not specified kCustomEnabling for.
		
		@see CActionComponent::UpdateActionStates
	*/
	virtual void UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

private:

	/** Encapsulates functionality for the about menu item. */
	void DoAbout(void);

	/** Checks if action can/should be carried out.
	 * 	@param actionID (in) The ActionID to examine...
	 * 	@return kTrue if action can be carried out.
	 */
	bool16 CanDoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	/** Performs the actual action. The includes a "PreProcess()" step before
	 * 	calling the original action component
	 * 	@param actionID (in) The ActionID to perform.
	 */
	void DoPerformAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	/** Does a bit of preprocessing.
	 * 	Change this to suit your needs.
	 *	@param msg (in) A PMString to display.
	 */
	void PreProcess(const PMString& msg);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CstAFltActionComponent, kCstAFltActionComponentImpl)

/* CstAFltActionComponent Constructor
*/
CstAFltActionComponent::CstAFltActionComponent(IPMUnknown* boss)
	: CActionComponent(boss)
{
}

/* DoAction
*/
void CstAFltActionComponent::DoAction(IActiveContext* ac, 
									  ActionID actionID, 
									  GSysPoint mousePoint, 
									  IPMUnknown* widget)
{
	if (actionID.Get() == kCstAFltAboutActionID)
	{
		this->DoAbout();
	}
	else
	{
		if (this->CanDoAction(ac, actionID, mousePoint, widget))
		{
			this->DoPerformAction(ac, actionID, mousePoint, widget);
		}
	}
}

/* UpdateActionStates
*/
void CstAFltActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do
	{
		if (ac == nil || listToUpdate == nil)
		{
			break;
		}

		int32 len = listToUpdate->Length();

		TRACEFLOW(kCstAFltPluginName, "[CstAFltActionComponent::UpdateActionStates()]\n");

	} while (kFalse);
}

/* DoAbout
*/
void CstAFltActionComponent::DoAbout(void)
{
	CAlert::ModalAlert
		(
		kCstAFltAboutBoxStringKey,	 // Alert string
		kOKString,					 // OK button
		kNullString,				 // No second button
		kNullString,				 // No third button
		1,							 // Set OK button to default
		CAlert::eInformationIcon	 // Information icon.
		);
}

/* CanDoAction
*/
bool16 CstAFltActionComponent::CanDoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	// 3rd PARTY TODO: change this to suit your needs
	return kTrue;
}


/* DoPerformAction
	* Find new actionID match from actionFilterHelpers and
	* Get the Orig IActionComponent so we can call it
*/
void CstAFltActionComponent::DoPerformAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	// get the classID that related to the original actionID.
	ActionMapper *actionMapperPtr = ActionMapper::ActionMapperFactory();
	ClassID originalClass = actionMapperPtr->LookUpAction(actionID);
#ifdef DEBUG
	DebugClassUtilsBuffer classBuf;
	TRACEFLOW(kCstAFltPluginName, "CLASSNAME: %s\n\n",DebugClassUtils::GetIDName(&classBuf,originalClass));
#endif
	// we need the action manager to figure out what menu the actions have
	InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> iActionManager(iApplication->QueryActionManager());

	// now let's get the export styles from the workspace, we need these later.
	InterfacePtr<IWorkspace> iWorkspace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IGenStlEdtListMgr> iPDFStyleListMgr(iWorkspace, IID_IPDFEXPORTSTYLELISTMGR);
	if (iPDFStyleListMgr == nil){
		ASSERT_FAIL("Failed to get the pdf excport styles");
		return;
	}

	InterfacePtr<IActionComponent> iOrigActionComponent(CreateObject2<IActionComponent>(originalClass));

	InterfacePtr<IActionIDToUIDData> iActionIDToUIDData(iOrigActionComponent,UseDefaultIID());
	if (iActionIDToUIDData==nil){
		ASSERT_FAIL("No UIDData channel on action component");
		return;
	}
	// here we get the set of action IDs from the ActionMapper and add them to the UIDData interface.
	// We only need the actionID specified on the parameter list, but adding all the actions for all
	// menus defined in the dynamic menu prevents a benign assert that reasons about the number of items
	// on the data interface.
    ActionMapper::size_type numActionClasses = actionMapperPtr->GetNumMaps();
	for (ActionMapper::size_type loop=0;  loop < numActionClasses; loop++){
		K2Pair<ActionID, ClassID> action2Class = actionMapperPtr->GetNthActionClassPair(loop);
		PMString actionName = iActionManager->GetActionName(action2Class.first);
		int32 numStyles = iPDFStyleListMgr->GetNumStyles();
		UIDRef styleUIDRef = UIDRef::gNull;
		// not efficient, given there should be a one-one relationship between ActionMap and style
		for (int32 loop2=0; loop2<numStyles; loop2++){
			PMString styleName;
			if (iPDFStyleListMgr->GetNthStyleName(loop2,&styleName) != kSuccess){
				ASSERT_FAIL("Cannot get style name!");
				break;
			}
			TRACEFLOW(kCstAFltPluginName, "stylename %s\n\n", styleName.GetUTF8String().c_str());
			if (actionName.Contains(styleName)){
				// found a match!
				styleUIDRef = iPDFStyleListMgr->GetNthStyleRef(static_cast<int32>(loop));
				break;
			}
		}
		if (styleUIDRef != UIDRef::gNull){
			iActionIDToUIDData->AddEntry(action2Class.first, styleUIDRef.GetUID());
		}
	}

	// do something before the actionComponent, or implement some logic here to determine whether you should
	// call back to the original action component
	this->PreProcess(PMString(kCstAFltAboutBoxStringKey));

	iOrigActionComponent->DoAction(ac, actionID, mousePoint, widget);
}

/* PreProcess
*/
void CstAFltActionComponent::PreProcess(const PMString& msg)
{
	// this routine does preprcessing... 
	// Modify this to suit your needs

	// display a simple message indicating that we have taken over 
	PMString displayMsg("Processing Action: ", PMString::kEncodingASCII);
	PMString msgCopy(msg);
	msgCopy.Translate();
	displayMsg += msgCopy;

	CAlert::InformationAlert(displayMsg);
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, CstAFltActionComponent.cpp.

