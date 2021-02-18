//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ConvertToButtonObserver.cpp $
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

#include "CObserver.h"

#include "ISubject.h"
#include "InterfacePtr.h"
#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "IPalettePanelUtils.h"
#include "IPanelControlData.h"
#include "ITriStateControlData.h"

#include "FormFieldUIUtils.h"

#include "FormFieldUIID.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class ConvertToButtonObserver
//----------------------------------------------------------------------------------------

class ConvertToButtonObserver : public CObserver
{
	public:
		ConvertToButtonObserver(IPMUnknown *boss);
		virtual ~ConvertToButtonObserver();
		
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
// CLASS ConvertToButtonObserver
//========================================================================================

CREATE_PMINTERFACE(ConvertToButtonObserver, kConvertToButtonObserverImpl)

//----------------------------------------------------------------------------------------
// ConvertToButtonObserver constructor 
//----------------------------------------------------------------------------------------

ConvertToButtonObserver::ConvertToButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// ConvertToButtonObserver::~ConvertToButtonObserver: 
//----------------------------------------------------------------------------------------

ConvertToButtonObserver::~ConvertToButtonObserver()
{
}


//----------------------------------------------------------------------------------------
// ConvertToButtonObserver::AutoAttach: 
// We also observe IID_ILISTCONTROLDATA, but that is hooked up
// when the listbox is created. See LayerPanelObserver.cpp, AutoAttach.
//----------------------------------------------------------------------------------------

void ConvertToButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// ConvertToButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void ConvertToButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// ConvertToButtonObserver::Update: 
//----------------------------------------------------------------------------------------

void ConvertToButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		if ( iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kPushButtonItemBoss) )
			iFormFieldSuite->CreateFieldFromSelection(kPushButtonItemBoss);						
	}
}




