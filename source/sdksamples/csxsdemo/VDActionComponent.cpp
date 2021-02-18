//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/csxsdemo/VDActionComponent.cpp $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================
#include "VCPlugInHeaders.h"
#include "CActionComponent.h"
#include "FileTypeRegistry.h"
#include "CAlert.h"
#include "VDID.h"
#include "ICSXSPlugPlugEventHandler.h"
#include "adobe/unicode.hpp" // for adobe::to_utf8
#include "IPageItemTypeUtils.h"
#include "Utils.h"
#include "ISelectionUtils.h"
#include "ILayoutSelectionSuite.h"
#include "IConcreteSelection.h"
#include "ISelectionUtils.h"
#include "ILayoutUIUtils.h"
#include "ILayoutHitTestSuite.h"
#include "IVDSuite.h"
#include "IActiveContext.h"

/** 
  * Implements IActionComponent which performs the actions that are executed when menu items are selected.
  */
class VDActionComponent : public CActionComponent
{
	public:
		VDActionComponent(IPMUnknown* boss);
		virtual void DoAction(IActiveContext * ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown * widget);

	private:
		void DoAbout();
		void SendSelection(IActiveContext * activeContext);
		UIDList GetSelectedPageItemsUIDs(IActiveContext * activeContext);
		ErrorCode SendCSXSMessage(PMString data);
};

CREATE_PMINTERFACE(VDActionComponent, kVDActionComponentImpl)

VDActionComponent::VDActionComponent(IPMUnknown * boss) : CActionComponent(boss)
{
}

void VDActionComponent::DoAction(IActiveContext * ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown * widget)
{
	switch (actionID.Get())
	{
		case kVDAboutActionID:
		{
			this->DoAbout();
			break;
		}
		case kVDContextMenuActionID:
		{
			this->SendSelection(ac);
			break;
		}
		default:
		{
			break;
		}
	}
}



void VDActionComponent::SendSelection(IActiveContext * activeContext)
{
	do {
		// find out about what has been selected..
		// get list of selected items
		UIDList selectedItems = this->GetSelectedPageItemsUIDs(activeContext);
		if (selectedItems.Length() != 1) 
		{
			// there should only be a single selection
			// TODO: make this support nested objects?
			break;
		}

		// find out what type of page item the user has selected
		// and act accordingly to pull out the data and send it
		UIDRef selectedPageItemRef = selectedItems.GetRef(0);
		if (Utils<IPageItemTypeUtils>()->IsTextFrame(selectedPageItemRef))
		{
			// text frame selected
			// get our custom suite which we can use to get the text in the frame
			InterfacePtr<IVDSuite> suite(activeContext->GetContextSelection(), UseDefaultIID());
			if (!suite)
			{
				break;
			}

			// get the text from the frame using our suite
			PMString selectedText;
			suite->GetTextFromSelectedFrame(selectedPageItemRef, selectedText);

			// send the text to Illustrator
			ErrorCode messageResult = this->SendCSXSMessage(selectedText);
			if (messageResult != kSuccess)
			{
				CAlert::ModalAlert(kVDPlugPlugDispatchFailKey, kOKString, kNullString, kNullString, 1, CAlert::eErrorIcon);
			}
		}
		else
		{
			// temp code till this plug-in supports sending other page item types..
			CAlert::ModalAlert(kVDUnsupportedPageItemTypeKey, kOKString, kNullString, kNullString, 1, CAlert::eErrorIcon);
		}

		// could add support for sending other types of page item..
		/*
		if (Utils<IPageItemTypeUtils>()->IsGraphicFrame(selectedPageItemRef))
		{
			// graphic frame (e.g. a placed image)
			break;
		}
		*/
		/*
		if (Utils<IPageItemTypeUtils>()->IsGraphic(selectedPageItemRef))
		{
			// graphic (not sure what this page item really is!)
			break;
		}
		*/
	} while(false);
}

ErrorCode VDActionComponent::SendCSXSMessage(PMString data)
{
	ErrorCode result = kFailure;

	do {
		InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
		if (!plugPlug)
		{
			break;
		}

		std::string csxsEventUtf8;
        adobe::detail::to_utf8<char>(data.begin(), data.end(), std::back_inserter(csxsEventUtf8), adobe::detail::unicode_size_type_<sizeof(UTF16TextChar)>());

		// create the CSXS event
		ICSXSPlugPlugEventHandler::CSXSEvent csxsEvent;
		csxsEvent.data = csxsEventUtf8.c_str();
		csxsEvent.type = "com.adobe.indesign.html";
		csxsEvent.scope = ICSXSPlugPlugEventHandler::kEventScope_Application;
		csxsEvent.extensionId = nil;

		if (LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS))
		{
			csxsEvent.appId = kIDEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h
		}
		else
		{
			csxsEvent.appId = kICEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h
		}

		// send the event
		ICSXSPlugPlugEventHandler::CSXSEventErrorCode csxsResult = plugPlug->DispatchPlugPlugEvent(&csxsEvent);
		if (csxsResult == ICSXSPlugPlugEventHandler::kEventErrorCode_Success)
		{
			result = kSuccess;
		}

	} while(false);

	return result;
}

UIDList VDActionComponent::GetSelectedPageItemsUIDs(IActiveContext * activeContext)
{
	UIDList list;

	do {
        InterfacePtr<ILayoutHitTestSuite> selection(Utils<ISelectionUtils>()->QueryLayoutHitTestSuite(activeContext->GetContextSelection())); 
        if (!selection)
		{
			// no selection, shouldn't be possible to be in this
			// situation since a user must right click a page item
			// to run this code
			break;
		}

        InterfacePtr<IConcreteSelection> iLayoutCSB(selection, UseDefaultIID());
        InterfacePtr<ILayoutTarget> iLayoutTarget(iLayoutCSB, UseDefaultIID()); 
        list = UIDList(iLayoutTarget->GetUIDList(kStripStandoffs));

	} while(false);

	return list;
}

void VDActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kVDAboutBoxStringKey,				// Alert string
		kOKString,                          // OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,                                  // Set OK button to default
		CAlert::eInformationIcon			// Information icon.
	);
}