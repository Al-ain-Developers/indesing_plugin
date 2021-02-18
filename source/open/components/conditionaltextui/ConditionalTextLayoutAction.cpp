//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextLayoutAction.cpp $
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
//  Hooks up an observer to watch for various conditional text adornment changes to inval.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IDocument.h"
#include "ILayoutAction.h"
#include "ILayoutControlData.h"
#include "IObserver.h"
#include "ISubject.h"
#include "IWorkspace.h"

// ----- Include files -----

#include "LocaleSetting.h"

// ----- ID.h files -----

#include "ConditionalTextID.h"
#include "ConditionalTextUIID.h"


class ConditionalTextLayoutAction : public CPMUnknown<ILayoutAction>
{
public:
	ConditionalTextLayoutAction(IPMUnknown *boss);
	
	void SetSpread(ILayoutControlData *layout, const UIDRef& spreadInWindow)
		{}
	void RemoveSpread(ILayoutControlData *layout, const UIDRef& spreadInWindow)
		{}
	void SetDocument(ILayoutControlData *layout, const UIDRef& docInWindow);
	void RemoveDocument(ILayoutControlData *layout, const UIDRef& docInWindow);
};

// =============================================================================
// *** ConditionalTextLayoutAction impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionalTextLayoutAction, kConditionalTextLayoutActionImpl)

ConditionalTextLayoutAction::ConditionalTextLayoutAction(IPMUnknown *boss) :
	CPMUnknown<ILayoutAction>(boss)
{
} // end constructor

// -----------------------------------------------------------------------------

void ConditionalTextLayoutAction::SetDocument(ILayoutControlData *layout, const UIDRef& docInWindow)
{
	InterfacePtr<IDocument> document(docInWindow, UseDefaultIID());
	InterfacePtr<IWorkspace> docWorkSpace(document->GetDocWorkSpace(), UseDefaultIID());
	InterfacePtr<ISubject> docSubject(docWorkSpace, IID_ISUBJECT);
	if (docSubject)
	{
		InterfacePtr<IObserver> pmLayoutObserver(layout, IID_ICONDITIONALTEXTLAYOUTOBSERVER);
		docSubject->AttachObserver(ISubject::kRegularAttachment,pmLayoutObserver, IID_ICONDITIONALTEXTOPTIONS, IID_ICONDITIONALTEXTLAYOUTOBSERVER);

		// If we are in InCopy, we also want to be notified from the app as well,
		// since all prefs in InCopy are app prefs.
		if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		{
			InterfacePtr<IWorkspace> appWorkSpace(GetExecutionContextSession()->QueryWorkspace());
			InterfacePtr<ISubject> appSubject(appWorkSpace, UseDefaultIID());
			appSubject->AttachObserver(pmLayoutObserver, IID_ICONDITIONALTEXTOPTIONS, IID_ICONDITIONALTEXTLAYOUTOBSERVER);
		}

		// Listen for condition tag changes - i.e. color, indicator method, underline indicator appearance
		docSubject->AttachObserver(ISubject::kRegularAttachment,pmLayoutObserver, IID_ICONDITIONTAGLIST, IID_ICONDITIONALTEXTLAYOUTOBSERVER);
	}
} // end SetDocument()

// -----------------------------------------------------------------------------

void ConditionalTextLayoutAction::RemoveDocument(ILayoutControlData *layout, const UIDRef& docInWindow)
{
	InterfacePtr<IDocument> document(docInWindow, UseDefaultIID());
	InterfacePtr<IWorkspace> docWorkSpace(document->GetDocWorkSpace(), UseDefaultIID());
	InterfacePtr<ISubject> docSubject(docWorkSpace, IID_ISUBJECT);
	if (docSubject)
	{
		InterfacePtr<IObserver> pmLayoutObserver(layout, IID_ICONDITIONALTEXTLAYOUTOBSERVER);
		docSubject->DetachObserver(ISubject::kRegularAttachment,pmLayoutObserver, IID_ICONDITIONALTEXTOPTIONS, IID_ICONDITIONALTEXTLAYOUTOBSERVER);

		// If we are in InCopy, we also want to be notified from the app as well,
		// since all prefs in InCopy are app prefs.
		if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		{
			InterfacePtr<IWorkspace> appWorkSpace(GetExecutionContextSession()->QueryWorkspace());
			InterfacePtr<ISubject> appSubject(appWorkSpace, UseDefaultIID());
			appSubject->DetachObserver(pmLayoutObserver, IID_ICONDITIONALTEXTOPTIONS, IID_ICONDITIONALTEXTLAYOUTOBSERVER);
		}

		docSubject->DetachObserver(ISubject::kRegularAttachment,pmLayoutObserver, IID_ICONDITIONTAGLIST, IID_ICONDITIONALTEXTLAYOUTOBSERVER);
	}
} // end RemoveDocument()

