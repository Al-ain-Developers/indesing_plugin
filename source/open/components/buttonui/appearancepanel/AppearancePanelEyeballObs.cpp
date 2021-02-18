//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePanelEyeballObs.cpp $
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
//  Based on LayerPanelEyeballObserver.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CObserver.h"

#include "IFormFieldSuite.h"
#include "ISubject.h"
#include "InterfacePtr.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IControlView.h"
#include "IBoolData.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"

#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "LayoutUIID.h"
#include "LayerID.h"
#include "UIDList.h"
#include "widgetid.h"

#include "IStateData.h"
#include "IAppearanceSuite.h"
#include "FormFieldUIID.h"
#include "FormFieldUIUtils.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class AppearancePanelEyeballObserver
//----------------------------------------------------------------------------------------

class AppearancePanelEyeballObserver : public CObserver
{
	public:
		AppearancePanelEyeballObserver(IPMUnknown *boss);
		virtual ~AppearancePanelEyeballObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);


};


//----------------------------------------------------------------------------------------
//
// Class implementation
//
//----------------------------------------------------------------------------------------


//========================================================================================
// CLASS AppearancePanelEyeballObserver
//========================================================================================

CREATE_PMINTERFACE(AppearancePanelEyeballObserver, kAppearancePanelEyeballObserverImpl)

//----------------------------------------------------------------------------------------
// AppearancePanelEyeballObserver constructor 
//----------------------------------------------------------------------------------------

AppearancePanelEyeballObserver::AppearancePanelEyeballObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// AppearancePanelEyeballObserver::~AppearancePanelEyeballObserver: 
//----------------------------------------------------------------------------------------

AppearancePanelEyeballObserver::~AppearancePanelEyeballObserver()
{
}


//----------------------------------------------------------------------------------------
// AppearancePanelEyeballObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void AppearancePanelEyeballObserver::AutoAttach()
{
	// watch for changes in this buttons state (i.e. respond when clicked on)
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// AppearancePanelEyeballObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void AppearancePanelEyeballObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// AppearancePanelEyeballObserver::Update: 
//----------------------------------------------------------------------------------------

void AppearancePanelEyeballObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage || theChange == kFalseStateMessage)
	{
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (data)
		{
			InterfacePtr<IControlView> frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
			IDocument* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();

			if (frontView == nil || frontDoc == nil)
				return;

			// Get the state of the current target
			InterfacePtr<IWidgetParent>	widgetParent(this, IID_IWIDGETPARENT);
			InterfacePtr<IStateData>	listElementStateData(widgetParent->GetParent(), IID_ISTATEDATA);
			Form::AppearanceState	state = listElementStateData->GetState();

			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());

			InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
			ClassID formFieldType; 
			if(iFormFieldSuite && iFormFieldSuite->IsFieldSelectionOfType(kPushButtonItemBoss) )
				formFieldType = kPushButtonItemBoss;
			else if(iFormFieldSuite && iFormFieldSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) )
				formFieldType = kCheckBoxItemBoss;
			else if(iFormFieldSuite && iFormFieldSuite->IsFieldSelectionOfType(kRadioButtonItemBoss) )
				formFieldType = kRadioButtonItemBoss;

			if (iAppearanceSuite && state != Form::kStateInvalid )
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
							iAppearanceSuite->SelectAssociatedAppearanceItemOfType(formFieldType);
					}
					CmdUtils::EndCommandSequence(cmdSeq);
				}
			}
		}
	}
}

