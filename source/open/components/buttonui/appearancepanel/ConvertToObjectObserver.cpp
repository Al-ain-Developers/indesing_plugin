//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ConvertToObjectObserver.cpp $
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
//  Based on DeleteLayerButtonObserver.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "VCPlugInHeaders.h"

#include "ISubject.h"
#include "InterfacePtr.h"
#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "IPalettePanelUtils.h"
#include "IPanelControlData.h"
#include "ITriStateControlData.h"

#include "CAlert.h"
#include "CObserver.h"

#include "EventUtilities.h"
#include "FormFieldUIUtils.h"

#include "FormFieldUIID.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class ConvertToObjectObserver
//----------------------------------------------------------------------------------------

class ConvertToObjectObserver : public CObserver
{
	public:
		ConvertToObjectObserver(IPMUnknown *boss);
		virtual ~ConvertToObjectObserver();
		
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
// CLASS ConvertToObjectObserver
//========================================================================================

CREATE_PMINTERFACE(ConvertToObjectObserver, kConvertToObjectObserverImpl)

//----------------------------------------------------------------------------------------
// ConvertToObjectObserver constructor 
//----------------------------------------------------------------------------------------

ConvertToObjectObserver::ConvertToObjectObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// ConvertToObjectObserver::~ConvertToObjectObserver: 
//----------------------------------------------------------------------------------------

ConvertToObjectObserver::~ConvertToObjectObserver()
{
}


//----------------------------------------------------------------------------------------
// ConvertToObjectObserver::AutoAttach: 
// We also observe IID_ILISTCONTROLDATA, but that is hooked up
// when the listbox is created. See LayerPanelObserver.cpp, AutoAttach.
//----------------------------------------------------------------------------------------

void ConvertToObjectObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// ConvertToObjectObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void ConvertToObjectObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// ConvertToObjectObserver::Update: 
//----------------------------------------------------------------------------------------

void ConvertToObjectObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		
		bool16 outWarnNonEmptyStates = false;
		if ( iFormFieldSuite && iFormFieldSuite->CanDestroyFieldFromSelection(outWarnNonEmptyStates) )
		{
			if ( outWarnNonEmptyStates && !::IsOptionAltKeyPressed() )
			{
				// Display a warning dialog
				PMString alertStr("$$$/Dialog/FormFieldUI/DestroyAlert");
				int16 whatToDo = CAlert::ModalAlert(alertStr,
													kOKString, 
													kCancelString, 
													kNullString, 
													1,                        // pass in 1, 2, or 3 to make that button the default button or 0 for no default
													CAlert::eWarningIcon);
				// If they don't want to continue, then punt
				if ( whatToDo == 2 )
					return;
			}
			
			iFormFieldSuite->DestroyFieldFromSelection();
		}
	}
}



