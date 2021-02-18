//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/CaptionLayerObserver.cpp $
//  
//  Owner: lance bushore
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

#include "CObserver.h"
#include "IControlView.h"
#include "Utils.h"
#include "IWidgetUtils.h"
#include "LinksUIID.h"
#include "ISubject.h"
#include "ITriStateControlData.h"

class CaptionLayerObserver : public CObserver
{
public:
					CaptionLayerObserver(IPMUnknown *boss);
		virtual void	AutoAttach();
		virtual void	AutoDetach();

		virtual 	void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);


};


CREATE_PMINTERFACE( CaptionLayerObserver, kCaptionLayerObserverImpl)

CaptionLayerObserver::CaptionLayerObserver(IPMUnknown *boss) :
	CObserver(boss)
{

}

void CaptionLayerObserver::AutoAttach( ) 
{
	CObserver::AutoAttach();
	InterfacePtr<ISubject> checkboxSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kCaptionGroupWithImageCheckboxWidgetID,IID_ISUBJECT));
	checkboxSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITRISTATECONTROLDATA,IID_IOBSERVER);
	
	// set up initial enable state, based on the checkbox
	InterfacePtr<IControlView> dropdownView(this,UseDefaultIID());
	InterfacePtr<IControlView> labelView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kCaptionLayerLabelWidgetID,IID_ICONTROLVIEW));
	InterfacePtr<const ITriStateControlData> checkboxData(checkboxSubject,UseDefaultIID());
	if(checkboxData->IsSelected())
	{
		dropdownView->Disable();
		labelView->Disable();
	}
	else 
	{
		dropdownView->Enable();
		labelView->Enable();
	}
}


void CaptionLayerObserver::AutoDetach( ) 
{
	CObserver::AutoDetach();

	InterfacePtr<ISubject> checkboxSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kCaptionGroupWithImageCheckboxWidgetID,IID_ISUBJECT));
	checkboxSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITRISTATECONTROLDATA,IID_IOBSERVER);
}


void CaptionLayerObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	#pragma unused(theChange,theSubject,protocol,changedBy)
	if(protocol ==IID_ITRISTATECONTROLDATA)
	{
		InterfacePtr<IControlView> dropdownView(this,UseDefaultIID());
		InterfacePtr<IControlView> labelView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kCaptionLayerLabelWidgetID,IID_ICONTROLVIEW));
		if(theChange == kTrueStateMessage)
		{
			dropdownView->Disable();
			labelView->Disable();
		}
		else if(theChange == kFalseStateMessage)
		{
			dropdownView->Enable();
			labelView->Enable();
		}
	}
}
	

